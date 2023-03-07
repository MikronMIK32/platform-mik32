from utils import get_ldscript_path
from os.path import join, isdir

from SCons.Script import (
    ARGUMENTS,
    COMMAND_LINE_TARGETS,
    DefaultEnvironment,
)

from platformio import fs
from platformio.proc import exec_command
from platformio.util import get_systype
from platformio.builder.tools.piolib import ProjectAsLibBuilder
from platformio.package.version import get_original_version, pepver_to_semver

env = DefaultEnvironment()
env.SConscript("_bare.py")

platform = env.PioPlatform()

TOOLCHAIN_DIR = platform.get_package_dir(
    "framework-mik32v0-sdk"
)

assert isdir(TOOLCHAIN_DIR)

SHARED_DIR = join(TOOLCHAIN_DIR, "shared")
HAL_DIR = join(TOOLCHAIN_DIR, "hal")

ldscript_path = get_ldscript_path()
print("LDscript: %s" % ldscript_path)
env.Replace(
    LDSCRIPT_PATH=ldscript_path
)

env.AppendUnique(
    CPPPATH=[
        '-v',
        "$PROJECT_SRC_DIR",
        join(SHARED_DIR, "include"),
        join(SHARED_DIR, "periphery"),
        join(SHARED_DIR, "runtime"),
        join(HAL_DIR, "core", "Include"),
        join(HAL_DIR, "peripherals", "Include"),
        join(SHARED_DIR, "libs"),
    ],
    LIBS=[
        "c"
    ]
)

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
]

env.Prepend(LIBS=libs)
