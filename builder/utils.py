from SCons.Script import (
    DefaultEnvironment,
)

from os.path import join, exists, basename
from enum import Enum

env = DefaultEnvironment()
env.SConscript("_bare.py")

platform = env.PioPlatform()
board = env.BoardConfig()

TOOLCHAIN_DIR = platform.get_package_dir(
    "framework-mik32v0-sdk"
)
SHARED_DIR = join(TOOLCHAIN_DIR, "shared")
LDSCRIPTS_DIR = join(SHARED_DIR, "ldscripts")


def get_ldscript_path() -> str:
    if board.get("build.ldscript", ""):
        ld = board.get("build.ldscript", "")
        if exists(ld):
            return ld
        if exists(join(LDSCRIPTS_DIR, ld)):
            return join(LDSCRIPTS_DIR, ld)
        if exists(join(LDSCRIPTS_DIR, ld + ".ld")):
            return join(LDSCRIPTS_DIR, ld + ".ld")

    if board.get("debug.ldscript", ""):
        ld = board.get("debug.ldscript", "")
        if exists(join(LDSCRIPTS_DIR, ld)):
            return join(LDSCRIPTS_DIR, ld)
        if exists(join(LDSCRIPTS_DIR, ld + ".ld")):
            return join(LDSCRIPTS_DIR, ld + ".ld")

    print("No ld script defined, using default")
    if exists(join(SHARED_DIR, "ldscripts", board.get(
            "build.mik32v0-sdk.ldscript"))):
        return join(SHARED_DIR, "ldscripts", board.get(
            "build.mik32v0-sdk.ldscript"))

    print("ERROR: Unable to find any ld script")
    return None


class MemoryType(Enum):
    RAM = "ram"
    EEPROM = "eeprom"
    SPIFI = "spifi"


def get_memory_type() -> MemoryType:
    path = get_ldscript_path()
    filename = basename(path)

    type_str = filename.split(".")[0]
    if (type_str in MemoryType._value2member_map_):
        return MemoryType._value2member_map_[type_str]
    type_str = filename.split("_")[0]
    if (type_str in MemoryType):
        return MemoryType._value2member_map_[type_str]

    print("ERROR: Unable to determine memory type")
    return None
