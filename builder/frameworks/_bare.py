from os.path import join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
board_config = env.BoardConfig()


env.AppendUnique(
    ASFLAGS=[
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-g",
    ],

    ASPPFLAGS=[
        "-x", "assembler-with-cpp",
    ],

    CCFLAGS=[
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-Os",
        "-g3",
        "-Wall",
        "-fsigned-char",
        "-ffunction-sections",
    ],

    CFLAGS = [
        "-std=gnu11"
    ],

    CXXFLAGS = [
        "-std=gnu++17",
        "-fabi-version=0",
        "-fno-exceptions",
        "-fno-rtti",
        "-fno-use-cxa-atexit",
        "-fno-threadsafe-statics",
    ],

    LINKFLAGS=[
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        "-nostartfiles",
        "-Xlinker",
        "-Map=\"%s.map\"" % join("$BUILD_DIR", "${PROGNAME}"),
        "-Wl,--gc-sections",
    ],

    LIBS=["c"]
)

# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.AppendUnique(ASFLAGS=env.get("CCFLAGS", [])[:])
