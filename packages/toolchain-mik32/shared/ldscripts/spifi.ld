
OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)

ENTRY(_start)


MEMORY {
  boot  : ORIGIN = 0x00000000, LENGTH = 16K
  ram   : ORIGIN = 0x02000000, LENGTH = 16K
  spifi : ORIGIN = 0x80000000, LENGTH = DEFINED(SPIFI_LENGTH) ? SPIFI_LENGTH : 256M
}

STACK_SIZE = 1024;

CL_SIZE = 32;

SECTIONS {
    .boot : 
    AT(ORIGIN(spifi)) {
        PROVIDE(__BOOT_START__ = .);
        *crt0.o(.text .text.*)
        *(.boot)
        . = ALIGN(CL_SIZE);
        PROVIDE(__BOOT_END__ = .);
    } > boot
    
    
    /* Placeholder for boot section */
    .text ORIGIN(spifi) + SIZEOF(.boot) : {    
    
        PROVIDE(__TEXT_START__ = .);
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)      
        . = ALIGN(CL_SIZE);
        PROVIDE(__TEXT_END__ = .);
    } > spifi

    .data : 
    AT( ALIGN(__TEXT_END__, CL_SIZE) ) {
        PROVIDE(__DATA_START__ = .);
        _gp = .;
        *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
        *(.sdata .sdata.* .gnu.linkonce.s.*)
        *(.data .data.*)
        . = ALIGN(CL_SIZE);
    } > ram
    
    __DATA_IMAGE_START__ = LOADADDR(.data);
    __DATA_IMAGE_END__ = LOADADDR(.data) + SIZEOF(.data);
    ASSERT(__DATA_IMAGE_END__ < ORIGIN(spifi) + LENGTH(spifi), "Data image overflows spifi section")
    
    /* bss segment */
    .sbss : {
        PROVIDE(__BSS_START__ = .);
        *(.sbss .sbss.* .gnu.linkonce.sb.*)
        *(.scommon)
    } > ram

    .bss : {
        *(.bss .bss.*)
        . = ALIGN(CL_SIZE);
        PROVIDE(__BSS_END__ = .);
    } > ram
    
    
    /* Code intended to be copied to RAM before execution */
    .ram_text : 
    AT( ALIGN(__DATA_IMAGE_END__, CL_SIZE) ) {
        PROVIDE(__RAM_TEXT_START__ = .);
        *(.ram_text)
        . = ALIGN(CL_SIZE);
        PROVIDE(__RAM_TEXT_END__ = .);
    } > ram
    
    __RAM_TEXT_IMAGE_START__ = LOADADDR(.ram_text);
    __RAM_TEXT_IMAGE_END__ = LOADADDR(.ram_text) + SIZEOF(.ram_text);
    ASSERT(__RAM_TEXT_IMAGE_END__ < ORIGIN(spifi) + LENGTH(spifi), "RAM text image overflows spifi section")

    _end = .;
    PROVIDE(__end = .);

    /* End of uninitalized data segement */

    .stack ORIGIN(ram) + LENGTH(ram) - STACK_SIZE : {
        FILL(0);
        PROVIDE(__STACK_START__ = .);
        . += STACK_SIZE;
        PROVIDE(__C_STACK_TOP__ = .);
        PROVIDE(__STACK_END__ = .);
    } > ram

    /DISCARD/ : {
        *(.eh_frame .eh_frame.*)
    }
}
