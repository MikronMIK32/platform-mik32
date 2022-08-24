import os

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()
board_config = env.BoardConfig()

env.Append(
    ASFLAGS=[
        "-x", "assembler-with-cpp",
        "-Wa,-march=%s" % board_config.get("build.march")
    ],

    CCFLAGS=[
        "-Os",
        "-Wall",  # show warnings
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel")
    ],

    LINKFLAGS=[
        "-Os",
        "-ffunction-sections",
        "-fdata-sections",
        "-nostartfiles",
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-nostdlib",
        # "--specs=nano.specs",
        "-Wl,--gc-sections",
        "-Xlinker", 
        "--print-memory-usage",
    ],

    LIBS=["c"],
)

# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.Append(ASFLAGS=env.get("CCFLAGS", [])[:])