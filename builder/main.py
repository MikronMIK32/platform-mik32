from utils import get_memory_type, MemoryType
from os.path import join

from SCons.Script import (ARGUMENTS, COMMAND_LINE_TARGETS, AlwaysBuild,
                          Builder, Default, DefaultEnvironment)


env = DefaultEnvironment()
env.SConscript("compat.py", exports="env")
platform = env.PioPlatform()
board = env.BoardConfig()

env.Replace(
    AR="riscv64-unknown-elf-gcc-ar",
    AS="riscv64-unknown-elf-as",
    CC="riscv64-unknown-elf-gcc",
    LD="riscv64-unknown-elf-ld",
    GDB="riscv64-unknown-elf-gdb",
    CXX="riscv64-unknown-elf-g++",
    OBJCOPY="riscv64-unknown-elf-objcopy",
    RANLIB="riscv64-unknown-elf-gcc-ranlib",
    SIZETOOL="riscv64-unknown-elf-size",

    SIZEPRINTCMD='$SIZETOOL -d $SOURCES',

    PROGSUFFIX=".elf"
)

# Allow user to override via pre:script
if env.get("PROGNAME", "program") == "program":
    env.Replace(PROGNAME="firmware")

env.Append(
    BUILDERS=dict(
        ElfToHex=Builder(
            action=env.VerboseAction(" ".join([
                "$OBJCOPY",
                "-O",
                "ihex",
                "$SOURCES",
                "$TARGET"
            ]), "Building $TARGET"),
            suffix=".hex"
        )
    )
)

pioframework = env.get("PIOFRAMEWORK", [])

if not pioframework:
    env.SConscript("frameworks/_bare.py", exports="env")

env.SConscript("frameworks/custom.py", exports={"env": env})

#
# Target: Build executable and linkable firmware
#

target_elf = None
if "nobuild" in COMMAND_LINE_TARGETS:
    target_elf = join("$BUILD_DIR", "${PROGNAME}.elf")
    target_hex = join("$BUILD_DIR", "${PROGNAME}.hex")
else:
    target_elf = env.BuildProgram()
    target_hex = env.ElfToHex(join("$BUILD_DIR", "${PROGNAME}"), target_elf)
    env.Depends(target_hex, "checkprogsize")

AlwaysBuild(env.Alias("nobuild", target_hex))
target_buildprog = env.Alias("buildprog", target_hex, target_hex)

#
# Target: Print binary size
#

target_size = env.Alias(
    "size", target_elf,
    env.VerboseAction("$SIZEPRINTCMD", "Calculating size $SOURCE"))
AlwaysBuild(target_size)

#
# Target: Upload
#

upload_protocol = env.subst("$UPLOAD_PROTOCOL")
debug_tools = board.get("debug.tools", {})
upload_actions = []
upload_target = target_hex

uploader = "openocd"
tool_args = [
    "-c",
    "debug_level %d" % (2 if int(ARGUMENTS.get("PIOVERBOSE", 2)) else 1),
    # "-s", platform.get_package_dir("tool-openocd-riscv") or ""
]

tool_args.extend(
    debug_tools.get(upload_protocol).get("server").get("arguments", []))

hex_path = target_hex[0].rstr().replace('\\', '/')
command = None
match get_memory_type():
    case MemoryType.RAM:
        print("Memory type is RAM")
        command = "load_image %s %s ihex" % (hex_path, board.get(
            "upload.image_offset", "0x0"))
    case MemoryType.EEPROM:
        print("Memory type is EEPROM")
        command = "eeprom_write_file %s" % hex_path
    case MemoryType.SPIFI:
        print("Memory type is SPI")
        command = ""
    case _:
        print("ERROR: unknown memory type")
tool_args.extend(
    [
        "-c", "reset halt",
        "-c", command,
        "-c", "resume %s" % board.get(
            "upload").get("image_offset", "0x0"),
        "-c", "shutdown"
    ]
)

env.Replace(
    UPLOADER=uploader,
    UPLOADERFLAGS=tool_args,
    UPLOADCMD="$UPLOADER $UPLOADERFLAGS"
)

upload_actions = [env.VerboseAction("$UPLOADCMD", "Uploading $SOURCE")]

AlwaysBuild(env.Alias("upload", upload_target, upload_actions))

#
# Setup default targets
#

Default([target_buildprog, target_size])
