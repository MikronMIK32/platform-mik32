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
import ctypes

from platformio.public import PlatformBase
from platformio.util import get_systype

# from SCons.Script import DefaultEnvironment

# env = DefaultEnvironment()

from os.path import join, exists, basename


class Mik32Platform(PlatformBase):


    def get_interface_config_path(self, interface_name: str) -> str:

        OPENOCD_DIR = self.get_package_dir("tool-openocd")
        UPLOADER_DIR = self.get_package_dir("tool-mik32-uploader")

        OPENOCD_SCRIPTS_DIR = join(OPENOCD_DIR, 'openocd/scripts/')
        UPLOADER_OPENOCD_SCRIPTS_DIR = join(
            UPLOADER_DIR, 'openocd-scripts/')
        
        interface_find_paths = [
            join(UPLOADER_OPENOCD_SCRIPTS_DIR, 'interface/ftdi/'),
            join(UPLOADER_OPENOCD_SCRIPTS_DIR, 'interface/'),
            join(OPENOCD_SCRIPTS_DIR, 'interface/ftdi/'),
            join(OPENOCD_SCRIPTS_DIR, 'interface/'),
        ]

        for interface in interface_find_paths:
            path = join(os.path.abspath(interface), interface_name + '.cfg') 

            if exists(path):
                return path


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
            assert "Tool not in upload protocols"

        sdk_dir = self.get_package_dir('framework-mik32v0-sdk')
        openocd_scripts = os.path.join(
            sdk_dir, 'openocd/share/openocd/scripts/')
        server_args = [
            "-s", "%s" % openocd_scripts
        ]
        interface = debug.get("interface", "m-link")
        interface_cfg = os.path.join('interface', 'ftdi', interface + '.cfg')

        if os.path.isfile(os.path.join(openocd_scripts, interface_cfg)):
            server_args.extend(['-f', interface_cfg])
        else:
            print('ERROR! No interface cfg file found for interface',
                  debug.get("interface"), interface_cfg)

        board_cfg = os.path.join('target', 'mik32.cfg')

        if os.path.isfile(os.path.join(openocd_scripts, board_cfg)):
            server_args.extend(["-f", board_cfg])
        else:
            print('ERROR! No board cfg file found for',
                  board.id, 'at path', board_cfg)

        debug["tools"][tool] = {
            "server": {
                "package": "tool-openocd",
                "executable": "bin/openocd",
                "arguments": server_args
            },
            "adapter_speed": debug.get("adapter_speed", "500"),
            "onboard": tool in debug.get("onboard_tools", []),
            "init_cmds": debug.get("init_cmds", None),
            "extra_cmds": debug.get("extra_cmds", None),
            "load_cmds": debug.get("load_cmds", "preload"),
            "load_mode": debug.get("load_mode", "modified"),
        }

        board.manifest["debug"] = debug
        return board

    def configure_debug_session(self, debug_config):
        print(dir(debug_config))

        if "openocd" in (debug_config.server or {}).get("executable", ""):

            sdk_dir = self.get_package_dir('framework-mik32v0-sdk')
            openocd_scripts = os.path.join(
                sdk_dir, 'openocd/share/openocd/scripts/')
            server_args = [
                "-s", "%s" % openocd_scripts
            ]

            interface = debug_config.upload_protocol or "m-link"
            interface_cfg = self.get_interface_config_path(interface)

            if os.path.isfile(interface_cfg):
                server_args.extend(['-f', interface_cfg])
            else:
                print('ERROR! No interface cfg file found for interface',
                      interface, interface_cfg)

            board_cfg = os.path.join('target', 'mik32.cfg')

            if os.path.isfile(os.path.join(openocd_scripts, board_cfg)):
                server_args.extend(["-f", board_cfg])
            # else:
            #     print('ERROR! No board cfg file found for', board.id, 'at path', board_cfg)

            debug_config.server["arguments"] = server_args

            debug_config.server["arguments"].extend(
                ["-c", "adapter speed %s" % (debug_config.speed or "500")]
            )

        pass

    pass
