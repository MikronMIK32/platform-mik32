#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#define GPIO_STATE				0x00 
#define GPIO_SET				0x00 
#define GPIO_CLEAR				0x04 
#define GPIO_DIRECTION_OUT		0x08 
#define GPIO_DIRECTION_IN		0x0C 
#define GPIO_OUTPUT             0x10
#define GPIO_CONTROL			0x14 



#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t SET;                 
        volatile uint32_t CLEAR;               
        volatile uint32_t DIRECTION_OUT;       
        volatile uint32_t DIRECTION_IN;        
        volatile uint32_t OUTPUT;
        volatile uint32_t CONTROL;  
        
    } GPIO_TypeDef;

#endif

#endif    