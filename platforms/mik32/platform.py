# Copyright 2014-present PlatformIO <contact@platformio.org>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os

#from platformio.managers.platform import PlatformBase
from platformio import app, exception, fs, util
from platformio.platform.base import PlatformBase
from platformio.project.config import ProjectConfig
from platformio.debug.config.generic import GenericDebugConfig
from platformio.util import get_systype


DEBUG_TARGET = "__debug"
PROTOCOL_FTDI = "ftdi"


# Не поддерживаемые прошивальщики
NOT_SUPPORTED_INTERFACES = [
]


"""
Проверенные прошивальщики:
    - mlink(FT2232H)
    - jlink (Not J-Link ARM)
    - xds100v2
"""


class Mik32Platform(PlatformBase):
    __debug_mode = False

    def is_debug(self) -> bool:
        return self.__debug_mode

    # Применение выбранной конфигурации из platformio.ini в режими отладки
    def configure_debug_session(self, debug_config: GenericDebugConfig):
        cfg = self.config.items(env=debug_config.env_name, as_dict=True)

        board = PlatformBase.get_boards(self, cfg.get("board"))
        self.configure_board(board, debug_config.env_name)

        self.configure_default_packages(cfg, [DEBUG_TARGET])

        with open("out", "w") as f:
            f.write("\n".join(map(str, [os.getcwd(), self.__debug_mode, "", board.manifest])))

        debug_config.tool_settings = (
                board.get("debug", {})
                .get("tools", {})
                .get(debug_config.tool_name, {})
            )

        debug_config.server = debug_config._configure_server()


    # Установка параметров указанной конфигурации
    def configure_board(self, board, env):
        config = self.config.items(env=env, as_dict=True)

        for key, value in config.items():
            if key.startswith("board_"):
                key = key.replace("board_", "", 1)

            board.update(key, value)

        return board


    def configure_default_packages(self, selected_config, targets):
        self.__class__.__selected_config = selected_config

        if DEBUG_TARGET in targets:
            self.__class__.__debug_mode = True

        upload_protocol = selected_config.get(
            "upload_protocol",
            self.board_config(selected_config.get("board")).get("upload.protocol", ""))

        if upload_protocol == "renode" and "debug" not in targets:
            self.packages["tool-renode"]["type"] = "uploader"

        return PlatformBase.configure_default_packages(self, selected_config, targets)


    def get_boards(self, id_=None):
        board = PlatformBase.get_boards(self, id_)

        if not board:
            return board
            
        board = self.configure_board_tools(board)

        return board


    def configure_board_tools(self, board):
        # Различное поведение для загрузки/отладки
        if (self.is_debug()):
            target = "debug"
        else:
            target = "upload"

        # Получение конфигурации
        board_id = board.id
        supported_protocols = board.get(f"{target}.protocols")  # Поддерживаемые протоколы
        protocol = board.get(f"{target}.protocol")              # Выбранный протокол            (ftdi, jlink)
        interface = board.get(f"{target}.interface")            # FTDI Интерфейс                (m-link, xds100v2)
        ldscript = board.get(f"{target}.ldscript")              # Скрипт линкера                (eeprom, ram)
        adapter_speed = board.get(f"{target}.adapter_speed")    # Скорость работы прошивальщика

        # Отображение занятой ПЗУ и ОЗУ
        try:
            board.update("upload.maximum_size", board.get(f"memory_usage.{ldscript}.rom"))
            board.update("upload.maximum_ram_size", board.get(f"memory_usage.{ldscript}.ram"))
        except KeyError:
            # Скрипт линкера не определён. Значения по умолчанию
            board.update("upload.maximum_size", board.get(f"memory_usage.default.rom"))
            board.update("upload.maximum_ram_size", board.get(f"memory_usage.default.ram"))

        # Проверка, поддерживается ли интерфейс
        if protocol not in supported_protocols:
            print(f"Ошибка: Протокол \"{interface}\" не поддерживается! Поддерживаемые протоколы: {', '.join(supported_protocols)}")
            raise exception.InvalidSettingValue(protocol, f"board_{target}.protocol")

        # Проверка, поддерживается ли интерфейс
        if interface in NOT_SUPPORTED_INTERFACES:
            print(f"Ошибка: Интерфейс \"{interface}\" не поддерживается!")
            raise exception.InvalidSettingValue(interface, f"board_{target}.interface")

        if interface in supported_protocols:
            protocol = interface
            print(f"Предупреждение: Протокол \"{interface}\" указан в качестве интерфейса!")

        # Получение путей
        sdk_dir = self.get_package_dir('toolchain-mik32')
        openocd_scripts_dir = os.path.abspath(os.path.join(sdk_dir, 'openocd/share/openocd/scripts/'))
        openocd_target_dir = os.path.join(openocd_scripts_dir, "target")
        openocd_protocols_dir = os.path.join(openocd_scripts_dir, "interface")
        openocd_ftdi_dir = os.path.join(openocd_protocols_dir, "ftdi")

        # Параметры запуска openocd сервера (Параметры прошивки)
        server_args = []

        if f"{board_id}.cfg" in os.listdir(openocd_target_dir):
            board_cfg_file_path = os.path.join(openocd_target_dir, f"{board_id}.cfg")
        else:
            print(f"Ошибка: Файл конфигурации \"{board_id}\" не найден!")
            raise exception.InvalidSettingValue(board_id, f"board")

        # Поиск файла конфигурации прошивальщика
        if protocol == PROTOCOL_FTDI:
            if f"{interface}.cfg" in os.listdir(openocd_ftdi_dir):
                flash_cfg_file_path = os.path.join(openocd_ftdi_dir, f"{interface}.cfg")
            else:
                print(f"Ошибка: Интерфейс \"{interface}\" не найден!")
                raise exception.InvalidSettingValue(interface, f"board_{target}.interface")

        else:
            if f"{protocol}.cfg" in os.listdir(openocd_protocols_dir):
                flash_cfg_file_path = os.path.join(openocd_protocols_dir, f"{interface}.cfg")
            else:
                print(f"Ошибка: Протокол \"{interface}\" не найден!")
                raise exception.InvalidSettingValue(protocol, f"board_{target}.protocol")

        # Установка конфигурации прошивальщика
        server_args.extend(['-f', flash_cfg_file_path])

        # Установка скорости прошивки
        server_args.extend(["-c", f"adapter_khz {adapter_speed}"])

        # Установка конфигурации "платы"
        server_args.extend(['-f', board_cfg_file_path])

        # Особое поведение для прошивальщика xds100v2
        if interface == "xds100v2":
            server_args.extend(["-c", "ftdi_set_signal PWR_RST 1", "-c", "jtag arp_init"])

        # Установка скрипта прошивки
        server_args.extend(["-f", os.path.join(openocd_scripts_dir, "include_eeprom.tcl")])

        # Сохранение параметров запуска сервера
        board.manifest["debug"]["tools"] = {
            protocol: {
                "server": {
                    "package": "tool-openocd-riscv",
                    "executable": "bin/openocd",
                    "arguments": server_args
                },
                "adapter_speed": adapter_speed,
                "onboard": protocol in board.manifest["debug"].get("onboard_tools", []),
                "init_cmds": board.manifest["debug"].get("init_cmds", None),
            }
        }

        board.update(f"debug.protocol", protocol)
        board.update(f"debug.interface", interface)
        board.update(f"debug.ldscript", ldscript)
        board.update(f"debug.adapter_speed", adapter_speed)

        return board
