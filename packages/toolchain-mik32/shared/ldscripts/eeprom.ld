
OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)


_IRQ_ENTRY = 0xC0;
_IRQ_HANDLER_LENGTH = 0x100;


/*
MEMORY {
  rom : ORIGIN = DEFINED(ROM_ORIGIN) ? ROM_ORIGIN : 0x00000000, LENGTH = DEFINED(ROM_ORIGIN) ? 32K : 8K
  ram : ORIGIN = 0x02000000, LENGTH = 16K
}
*/


MEMORY {
    startup : ORIGIN = 0x0,                                     LENGTH = _IRQ_ENTRY
    irq     : ORIGIN = 0x0 + _IRQ_ENTRY,                        LENGTH = _IRQ_HANDLER_LENGTH
    rom     : ORIGIN = 0x0 + _IRQ_ENTRY + _IRQ_HANDLER_LENGTH,  LENGTH = 8K - _IRQ_ENTRY - _IRQ_HANDLER_LENGTH
    ram     : ORIGIN = 0x02000000,                              LENGTH = 16K
}


STACK_SIZE = 1024;

CL_SIZE = 32;

SECTIONS {
    .startup : {
        PROVIDE(__TEXT_START__ = .);

        KEEP(*core_startup.o(.text));

        . = ALIGN(_IRQ_ENTRY);
    } >startup

    .irq : {
        KEEP(*core_irq.o(.text));

        . = ALIGN(_IRQ_ENTRY + _IRQ_HANDLER_LENGTH);
    } >irq

    .main  : {
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
    ASSERT(__DATA_IMAGE_END__ < ORIGIN(rom) + LENGTH(rom), "Data image overflows rom section")

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
