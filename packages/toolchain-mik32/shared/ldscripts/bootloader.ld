
OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)


MEMORY {
  rom : ORIGIN = DEFINED(ROM_ORIGIN) ? ROM_ORIGIN : 0x02001000, LENGTH = 8K
  /* ram : ORIGIN = 0x02010000, LENGTH = 8K */
  ram : ORIGIN = 0x02002000, LENGTH = 8K
}

STACK_SIZE = 1024;

CL_SIZE = 32;
RESERVED_ROM_SPACE = 4096;

SECTIONS {
    .text  : {
		. = RESERVED_ROM_SPACE;
		
        PROVIDE(__TEXT_START__ = .);
        *crt0.o(.text .text.*)

        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)      
        . = ALIGN(CL_SIZE);
        PROVIDE(__TEXT_END__ = .);
    } >rom 

    .data : 
    AT( __TEXT_END__ ) {
        PROVIDE(__DATA_START__ = .);
        _gp = .;
        *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
        *(.sdata .sdata.* .gnu.linkonce.s.*)
        *(.data .data.*)
        . = ALIGN(CL_SIZE);
    } >ram
    
    __DATA_IMAGE_START__ = LOADADDR(.data);
    __DATA_IMAGE_END__ = LOADADDR(.data) + SIZEOF(.data);

    /* thread-local data segment */
    .tdata : {
        PROVIDE(_tls_data = .);
        PROVIDE(_tdata_begin = .);
        *(.tdata .tdata.*)
        PROVIDE(_tdata_end = .);
        . = ALIGN(CL_SIZE);
    } >ram

    .tbss : {
        PROVIDE(__BSS_START__ = .);
        *(.tbss .tbss.*)
        . = ALIGN(CL_SIZE);
        PROVIDE(_tbss_end = .);
    } >ram

    /* bss segment */
    .sbss : {
        *(.sbss .sbss.* .gnu.linkonce.sb.*)
        *(.scommon)
    } >ram

    .bss : {
        *(.bss .bss.*)
        . = ALIGN(CL_SIZE);
        PROVIDE(__BSS_END__ = .);
    } >ram

    _end = .;
    PROVIDE(__end = .);

    /* End of uninitalized data segement */

    .stack ORIGIN(ram) + LENGTH(ram) - STACK_SIZE : {
        FILL(0);
        PROVIDE(__STACK_START__ = .);
        . += STACK_SIZE;
        PROVIDE(__C_STACK_TOP__ = .);
        PROVIDE(__STACK_END__ = .);
    } >ram

    /DISCARD/ : {
        *(.eh_frame .eh_frame.*)
    }
}
