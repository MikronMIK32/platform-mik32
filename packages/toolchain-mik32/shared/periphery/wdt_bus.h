#ifndef WDT_BUS_H_INCLUDED
#define WDT_BUS_H_INCLUDED

#define WDT_BUS_EEPROM_S        2
#define WDT_BUS_SPIFI_S         1
#define WDT_BUS_DOM3_S          0



#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
    //--------------------------
    // OTP registers
    //--------------------------

    volatile uint32_t COUNTER;
    volatile uint32_t INT_CLEAR;
    volatile uint32_t ENABLE;
   

    } WDT_BUS_TypeDef;
#endif

#endif // OTP_H_INCLUDED

