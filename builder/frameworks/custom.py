# Copyright 2020-present PlatformIO <contact@platformio.org>
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


from os.path import join, isdir, exists, dirname

from colorama import Fore, Style

from SCons.Script import (
    ARGUMENTS,
    COMMAND_LINE_TARGETS,
    DefaultEnvironment,
)

env = DefaultEnvironment()

env.SConscript("_bare.py")

platform = env.PioPlatform()
board = env.BoardConfig()


# Prepare paths to the framework directories

framework_name = env.GetProjectOption("framework")[0]
FRAMEWORK_DIR = platform.get_package_dir(framework_name)

BUILD_DIR = env.subst("$BUILD_DIR")
PROJECT_DIR = env.subst("$PROJECT_DIR")
PROJECT_SRC_DIR = env.subst("$PROJECT_SRC_DIR")

SHARED_DIR = join(FRAMEWORK_DIR, "shared")
LDSCRIPTS_DIR = join(SHARED_DIR, "ldscripts")
RUNTIME_DIR = join(SHARED_DIR, "runtime")
HAL_DIR = join(FRAMEWORK_DIR, "hal")


# Add header file search directories

env.AppendUnique(
    CPPPATH=[
        "$PROJECT_SRC_DIR",
        join(SHARED_DIR, "include"),
        join(SHARED_DIR, "periphery"),
        join(SHARED_DIR, "runtime"),
        join(SHARED_DIR, "libs"),
        join(HAL_DIR, "core", "Include"),
        join(HAL_DIR, "peripherals", "Include"),
        join(HAL_DIR, "utilities", "Include"),
    ],
    LIBS=[
        "c"
    ]
)


# Add startup file and HAL library source code directories

libs = [
    env.BuildLibrary(
        join("$BUILD_DIR", "runtime"),
        join(SHARED_DIR, "runtime"),
    ),
    env.BuildLibrary(
        join("$BUILD_DIR", "libs"),
        join(SHARED_DIR, "libs"),
    ),
    env.BuildLibrary(
        join("$BUILD_DIR", "hal_core"),
        join(HAL_DIR, "core", "Source"),
    ),
    env.BuildLibrary(
        join("$BUILD_DIR", "hal_peripherals"),
        join(HAL_DIR, "peripherals", "Source"),
    ),
    env.BuildLibrary(
        join("$BUILD_DIR", "hal_utilities"),
        join(HAL_DIR, "utilities", "Source"),
    ),
]

env.Prepend(LIBS=libs)


# Defining path to selected linker script and adding library search path 
# for correct search of nested scripts

ld_build = board.get("build.ldscript", "").removesuffix(".ld")

for path in [
    "",             # $PROJECT_DIR or path from board_build.ldscript
    LDSCRIPTS_DIR,  # framework/shared/ldscripts
]:
    file_path = join(path, ld_build) + ".ld"
    ld_path = dirname(file_path)

    if exists(file_path):
        if ld_path != "":
            env.PrependUnique(LIBPATH=ld_path)

        env.Replace(LDSCRIPT_PATH=file_path)
        break
else:
    print(f"{Fore.RED}ERROR: Unable to find linker script: {file_path}{Style.RESET_ALL}")
    print(f"{Fore.RED}Specify correct linker script name or path in platformio.ini"
        f" parameter: board_build.ldscript{Style.RESET_ALL}")
    env.Exit(1)
