#ifndef BOOT_MANAGER_H_INCLUDED
#define BOOT_MANAGER_H_INCLUDED

#define BOOT_EEPROM                  0
#define BOOT_RAM                     1
#define BOOT_SPIFI                   2

#ifndef _ASSEMBLER_
    #include <inttypes.h> 
    typedef struct
    {   
        volatile uint32_t BOOT;
    } BOOT_MANAGER_TypeDef;
#endif

#endif 

