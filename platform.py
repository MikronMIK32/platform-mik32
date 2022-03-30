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

import copy
import os
import platform
import ctypes

from platformio.managers.platform import PlatformBase
from platformio.util import get_systype
# from SCons.Script import DefaultEnvironment

# env = DefaultEnvironment()

class Mik32Platform(PlatformBase):

    def configure_default_packages(self, variables, targets):
        upload_protocol = variables.get(
            "upload_protocol",
            self.board_config(variables.get("board")).get(
                "upload.protocol", ""))

        if upload_protocol == "renode" and "debug" not in targets:
            self.packages["tool-renode"]["type"] = "uploader"

        return PlatformBase.configure_default_packages(self, variables, targets)

    def get_boards(self, id_=None):
        result = PlatformBase.get_boards(self, id_)
        if not result:
            return result
        if id_:
            return self._add_default_debug_tools(result)
        else:
            for key, _ in result.items():
                result[key] = self._add_default_debug_tools(result[key])
        return result

    def _add_default_debug_tools(self, board):
        debug = board.manifest.get("debug", {})
        upload_protocols = board.manifest.get("upload",
                                              {}).get("protocols", [])
        if "tools" not in debug:
            debug["tools"] = {}

        tool = "ftdi"
            
        if (tool not in upload_protocols or tool in debug["tools"]):
            assert "TOol not in upload protocols"
        
        server_args = [
            # "-s", "$PACKAGE_DIR/share/openocd/scripts"
        ]
        sdk_dir = self.get_package_dir('toolchain-mik32')
        openocd_scripts = os.path.join(sdk_dir, 'openocd/share/openocd/scripts/')
        interface = debug.get("interface", "m-link")
        interface_cfg = os.path.join(openocd_scripts, 'interface', 'ftdi', interface + '.cfg')

        if os.path.isfile(interface_cfg):
            server_args.extend(['-f', interface_cfg])
        else:
            print('ERROR! No interface cfg file found for interface', debug.get("interface"), interface_cfg)

        adapter_khz = debug.get("adapter_speed", "500")
        server_args.extend(["-c", "adapter_khz %s" % adapter_khz])

        board_cfg = os.path.join(openocd_scripts, 'target', board.id + '.cfg')

        if os.path.isfile(board_cfg):
            server_args.extend(["-f", board_cfg])
        else:
            print('ERROR! No board cfg file found for', board.id, 'at path', board_cfg)

        server_args.extend(["-f", os.path.join(openocd_scripts, "include_eeprom.tcl")])

        

        # print(env.GetProjectOption("debug_tool"))
        # ctypes.windll.user32.MessageBoxA(0, board.id, "Your title", 1)
        # elif board.id == "e310-arty":
        #     server_args.extend([
        #         "-f", os.path.join("interface", "ftdi", "%s.cfg" % (
        #             "arty-onboard-ftdi" if tool == "ftdi" else tool)),
        #         "-f", os.path.join(
        #             sdk_dir or "", "bsp", "freedom-e310-arty", "openocd.cfg")
        #     ])
        debug["tools"][tool] = {
            "server": {
                "package": "tool-openocd-riscv",
                "executable": "bin/openocd",
                "arguments": server_args
            },
            "adapter_speed": debug.get("adapter_speed", "500"),
            "onboard": tool in debug.get("onboard_tools", []),
            "init_cmds": debug.get("init_cmds", None)
        }

        board.manifest["debug"] = debug
        return board
