from os.path import join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()
board_config = env.BoardConfig()


env.AppendUnique(
    ASFLAGS=[
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-nostartfiles",
        "-nostdlib",
    ],

    CCFLAGS=[
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-nostartfiles",
        "-nostdlib",
        "-ffunction-sections",
    ],

    LINKFLAGS=[
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-Xlinker",
        "-Map=%s.map" % join("$BUILD_DIR", "${PROGNAME}"),
        "-nostartfiles",
        "-nostdlib",
        "-Wl,--gc-sections",
    ],
)
