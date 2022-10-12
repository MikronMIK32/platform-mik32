#ifndef EPIC_H_INCLUDED
#define EPIC_H_INCLUDED


#define EPIC_IRQ_MASK_SET           0x00
#define EPIC_IRQ_MASK_CLEAR         0x04
#define EPIC_IRQ_SW_SET             0x08
#define EPIC_IRQ_SW_CLEAR           0x0C
#define EPIC_IRQ_CLEAR              0x10
#define EPIC_IRQ_STATUS             0x14
#define EPIC_IRQ_RAW_STATUS         0x18




#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {  
        volatile uint32_t MASK_SET;
        volatile uint32_t MASK_CLEAR;
        volatile uint32_t MASK_LEVEL_SET;
        volatile uint32_t MASK_LEVEL_CLEAR;        
        volatile uint32_t SW_SET;
        volatile uint32_t SW_CLEAR;
        volatile uint32_t CLEAR;
        volatile uint32_t STATUS;
        volatile uint32_t RAW_STATUS;      
    } EPIC_TypeDef;
#endif

#endif // EPIC_H_INCLUDED
