import re
from typing import Union
from SCons.Script import (
    DefaultEnvironment,
)

from os.path import join, exists, basename
from enum import Enum

env = DefaultEnvironment()

platform = env.PioPlatform()
board = env.BoardConfig()

framework_name = env.GetProjectOption("framework")[0]
TOOLCHAIN_DIR = platform.get_package_dir(framework_name)

SHARED_DIR = join(TOOLCHAIN_DIR, "shared")
LDSCRIPTS_DIR = join(SHARED_DIR, "ldscripts")


def get_ldscript_path() -> Union[str, None]:

    ld_build = board.get("build.ldscript", "")
    if ld_build:
        if exists(ld_build):
            return ld_build
        if exists(ld_build + ".ld"):
            return ld_build + ".ld"
        if exists(join(LDSCRIPTS_DIR, ld_build)):
            return join(LDSCRIPTS_DIR, ld_build)
        if exists(join(LDSCRIPTS_DIR, ld_build + ".ld")):
            return join(LDSCRIPTS_DIR, ld_build + ".ld")

    ld_debug = board.get("debug.ldscript", "")
    if ld_debug:
        if exists(ld_debug):
            return ld_debug
        if exists(ld_build + ".ld"):
            return ld_build + ".ld"
        if exists(join(LDSCRIPTS_DIR, ld_debug)):
            return join(LDSCRIPTS_DIR, ld_debug)
        if exists(join(LDSCRIPTS_DIR, ld_debug + ".ld")):
            return join(LDSCRIPTS_DIR, ld_debug + ".ld")
        
    if ld_build != "" or ld_debug != "":
        return None

    default_ld_path = join(SHARED_DIR, "ldscripts", board.get(
        "build.mik32v2-sdk.ldscript"))
    if exists(default_ld_path):
        print("No ld script defined, using default %s" %
              basename(default_ld_path))
        return join(SHARED_DIR, "ldscripts", board.get(
            "build.mik32v2-sdk.ldscript"))

    print("ERROR: Unable to find any ld script")
    return None


class MemoryType(Enum):
    RAM = "ram"
    EEPROM = "eeprom"
    SPIFI = "spifi"


def get_memory_type() -> MemoryType:
    path = get_ldscript_path()
    filename = basename(path)

    pattern = re.compile(r"ram|eeprom|spifi[\d_\-\.]*")
    result = pattern.match(filename).group(0)
    if (result in MemoryType._value2member_map_):
        return MemoryType._value2member_map_[result]

    print("ERROR: Unable to determine memory type")
    return None
