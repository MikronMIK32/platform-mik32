#define EXCEPTION_STACK_SPACE 32*4
#define EXCEPTION_SAVED_REGISTERS 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31

.globl trap_entry
.globl trap_handler
.globl raw_trap_handler
.weak trap_handler, raw_trap_handler

.globl MoveMepcToNextInstruction



.text

// .org should be consistent with
// default mtvec value (set in scr1_arch_description.svh)
// .org 0xC0
trap_entry:
    j raw_trap_handler

raw_trap_handler:
    // Save registers
    addi    sp, sp, -(EXCEPTION_STACK_SPACE)
    .irp index, EXCEPTION_SAVED_REGISTERS
        sw      x\index,  4*\index(sp)
    .endr
    
    // Call handler 
    la      ra, trap_handler
    jalr    ra
    
    // restore registers
    .irp index, EXCEPTION_SAVED_REGISTERS
        lw      x\index,  4*\index(sp)
    .endr
    
    addi    sp, sp, EXCEPTION_STACK_SPACE
    mret

// Default handler: infinit loop
// (weak symbol here - may be redefined)
trap_handler:
1:  j       1b
   
   
MoveMepcToNextInstruction:
    csrr    t0, mepc
    // check mepc is not aligned by 4
    andi    t1, t0, 0x3
    li      t2, 0x2
    bne     t1, t2, 1f
    // mepc not aligned by 4
    lw      t1, -2(t0)
    srl     t1, t1, 16
    j       2f
    // mepc aligned by 4
1:  lw      t1, 0(t0)

2:  // determine instruction length (16 or 32 bit)
    andi    t1, t1, 0x3
    li      t2, 0x3     // bits [1:0] == 2'b11 for 32 bit instruction
    bne     t1, t2, 1f
    addi    t0, t0, 4
    j       2f
1:  addi    t0, t0, 2
2:  csrw    mepc, t0
    ret
