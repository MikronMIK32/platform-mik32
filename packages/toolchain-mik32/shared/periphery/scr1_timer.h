#ifndef SCR1_TIMER_H_INCLUDED
#define SCR1_TIMER_H_INCLUDED


#define SCR1_TIMER_ENABLE_S             0
#define SCR1_TIMER_ENABLE_M             (1 << SCR1_TIMER_ENABLE_S)

#define SCR1_TIMER_CLKSRC_S             1
#define SCR1_TIMER_CLKSRC_M             (1 << SCR1_TIMER_CLKSRC_S)
#define SCR1_TIMER_CLKSRC_INTERNAL_M    (0 << SCR1_TIMER_CLKSRC_S)
#define SCR1_TIMER_CLKSRC_RTC_M         (1 << SCR1_TIMER_CLKSRC_S)


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t TIMER_CTRL;
        volatile uint32_t TIMER_DIV;
        volatile uint32_t MTIME;
        volatile uint32_t MTIMEH;        
        volatile uint32_t MTIMECMP;
        volatile uint32_t MTIMECMPH;        
    } SCR1_TIMER_TypeDef;
#endif

#endif // SCR1_TIMER_H_INCLUDED
