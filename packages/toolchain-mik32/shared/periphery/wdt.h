#ifndef WDT_H_INCLUDED
#define WDT_H_INCLUDED


#define WDT_KEY                 0x9C
#define WDT_CON                 0x84
#define WDT_STA                 0x9C


#define WDT_KEY_UNLOCK          0x1E
#define WDT_KEY_START           0x71
#define WDT_KEY_STOP            0xE8

#define WDT_INTERRUPT_THRESHOLD 0x100

#define WDT_CON_PRESCALE_S      12
#define WDT_CON_PRESCALE_M      (0x7 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_1_M    (0x0 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_2_M    (0x1 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_4_M    (0x2 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_16_M   (0x3 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_64_M   (0x4 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_256_M  (0x5 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_1024_M (0x6 << WDT_CON_PRESCALE_S)
#define WDT_CON_PRESCALE_4096_M (0x7 << WDT_CON_PRESCALE_S)

#define WDT_CON_PRELOAD_S       0
#define WDT_CON_PRELOAD_M       (0xFFF << WDT_CON_PRELOAD_S)
#define WDT_CON_PRELOAD(v)      (((v) << WDT_CON_PRELOAD_S) & WDT_CON_PRELOAD_M)

#define WDT_STA_RST_FLAG_S      8
#define WDT_STA_RST_FLAG_M      (1 << WDT_STA_RST_FLAG_S)
#define WDT_STA_LOADING_S       1
#define WDT_STA_LOADING_M       (1 << WDT_STA_LOADING_S)
#define WDT_STA_ENABLED_S       0
#define WDT_STA_ENABLED_M       (1 << WDT_STA_ENABLED_S)



#ifndef _ASSEMBLER_
    #include <inttypes.h> 
    typedef struct
    {
        union 
        {
            struct 
            {
                volatile uint8_t _space_Key[WDT_KEY];
                volatile uint8_t Key;
            };
            struct 
            {
                volatile uint8_t _space_Con[WDT_CON];
                volatile uint32_t Con;
            };
            struct 
            {
                volatile uint8_t _space_Sta[WDT_STA];
                volatile uint32_t Sta;
            };
        };
    } WDT_TypeDef;
#endif

#endif // WDT_H_INCLUDED
