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
    ],

    ASPPFLAGS=[
        # "-x", "assembler-with-cpp",
    ],

    CCFLAGS=[
        # "-Os",
        "-Og",
        "-g",
        "-Wall",
        "-march=%s" % board_config.get("build.march"),
        "-mabi=%s" % board_config.get("build.mabi"),
        "-mcmodel=%s" % board_config.get("build.mcmodel"),
        # "-fmessage-length=0",
        # "-fsigned-char",
        # "-ffunction-sections",
        # "-fdata-sections",
        # "-fno-common"
    ],

    # CFLAGS = [
    #     "-std=gnu11"
    # ],

    # CXXFLAGS = [
    #     "-std=gnu++17"
    # ],

    LINKFLAGS=[
        "-Xlinker",
        "-Map=%s.map" % join("$BUILD_DIR", "${PROGNAME}"),
        # "--oformat elf32-littleriscv",
        # "-Os",
        # "-ffunction-sections",
        # "-fdata-sections",
        # "-nostartfiles",
        # "-Xlinker",
        # "-march=%s" % board_config.get("build.march"),
        # "-mabi=%s" % board_config.get("build.mabi"),
        # "-mcmodel=%s" % board_config.get("build.mcmodel"),
        # "-nostdlib",
        # "--specs=nano.specs",
        # "-Wl,--gc-sections"
    ],

    LIBS=["c"],
)

# copy CCFLAGS to ASFLAGS (-x assembler-with-cpp mode)
env.AppendUnique(ASFLAGS=env.get("CCFLAGS", [])[:])
