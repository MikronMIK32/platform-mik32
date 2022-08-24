#ifndef GPIO_IRQ_H_INCLUDED
#define GPIO_IRQ_H_INCLUDED

#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t STATE;
        volatile uint32_t CFG;
        volatile uint32_t INTERRUPTS;
        volatile uint32_t ENABLE_SET;
        volatile uint32_t ENABLE_CLEAR;
        volatile uint32_t EDGE;
        volatile uint32_t LEVEL;
        volatile uint32_t LEVEL_SET;
        volatile uint32_t LEVEL_CLEAR;
        volatile uint32_t ANYEDGE_SET;
        volatile uint32_t ANYEDGE_CLEAR;
        volatile uint32_t CLEAR;        
    } GPIO_IRQ_TypeDef;

#endif

#endif    