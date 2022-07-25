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


NOT_SUPPORTED_INTERFACES = [
    "stlink",
    "stlink-v1",
    "stlink-v2",
    "stlink-v2-1"
]


"""
Verified flashers:
    - mlink(FT2232H)
    - jlink (Not J-Link ARM)
    - xds100v2
"""


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
            assert "Tool not in upload protocols"
        
        server_args = [
            # "-s", "$PACKAGE_DIR/share/openocd/scripts"
        ]
        
        sdk_dir = self.get_package_dir('toolchain-mik32')
        openocd_scripts = os.path.abspath(os.path.join(sdk_dir, 'openocd/share/openocd/scripts/'))

        # Interface
        interface = debug.get("interface", "m-link")

        ## Not supported interfaces
        if interface in NOT_SUPPORTED_INTERFACES:
            print(f"Error: Interface '{interface}' not supported")
            raise Exception(f"Interface '{interface}' not supported")
        
        openocd_interfaces = os.path.join(openocd_scripts, "interface")

        ## If not FTDI interface (jlink, ...)
        if f"{interface}.cfg" in os.listdir(openocd_interfaces):
            interface_cfg = os.path.join(openocd_scripts, 'interface', f"{interface}.cfg")

        ## If FTDI interface (m-link, xds100v2, ...)
        elif f"{interface}.cfg" in os.listdir(os.path.join(openocd_interfaces, "ftdi")):
            interface_cfg = os.path.join(openocd_scripts, 'interface', 'ftdi', f"{interface}.cfg")

        ## Interface not found
        else:
            print(f"Error: Interface '{interface}' not found.",
                  f"  Fix:",
                  f"    Edit field 'board_debug.interface = {interface}' in 'platformio.ini'",
                  f"    OR",
                  f"    add your interface to '{openocd_interfaces}'",
                  sep="\n")

            raise Exception(f"Interface '{interface}' not found")

        server_args.extend(['-f', interface_cfg])

        # Flash speed
        adapter_khz = debug.get("adapter_speed", "500")
        server_args.extend(["-c", f"adapter_khz {adapter_khz}"])

        # Board cfg file
        board_cfg = os.path.join(openocd_scripts, 'target', f"{board.id}.cfg")

        if not os.path.isfile(board_cfg):
            print(f"Error: No board cfg file found for {board.id}.",
                  f"  Fix:"
                  f"    Edit field 'board = {board.id}' in 'platformio.ini'",
                  f"    OR",
                  f"    add cfg file to '{openocd_interfaces}'",
                  sep="\n")

            raise Exception(f"Interface '{interface}' not found")

        server_args.extend(["-f", board_cfg])

        ## Special behavior for xds100v2
        if interface == "xds100v2":
            server_args.extend(["-c", "ftdi_set_signal PWR_RST 1", "-c", "jtag arp_init"])

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
