#ifndef TIMER16_H_INCLUDED
#define TIMER16_H_INCLUDED


#define TIMER16_SYNC_CLOCKS 2

#define TIMER16_ISR		    0x00
#define TIMER16_ICR			0x04
#define TIMER16_IER		    0x08
#define TIMER16_CFGR		0x0C
#define TIMER16_CR          0x10
#define TIMER16_CMP       	0x14   
#define TIMER16_ARR      	0x18   
#define TIMER16_CNT         0x1C   

#define TIMER16_ENABLE_S                    0
#define TIMER16_ENABLE_M                    (1 << TIMER16_ENABLE_S)
#define TIMER16_DISABLE_M                   (0 << TIMER16_ENABLE_S)
#define TIMER16_START_SINGLE_MODE_S         1
#define TIMER16_START_SINGLE_MODE_M         (1 << TIMER16_START_SINGLE_MODE_S)
#define TIMER16_START_CONTIN_MODE_S         2
#define TIMER16_START_CONTIN_MODE_M         (1 << TIMER16_START_CONTIN_MODE_S)


#define TIMER16_PRESCALER_S                 9
#define TIMER16_PRESCALER_1_M               (0x0 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_2_M               (0x1 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_4_M               (0x2 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_8_M               (0x3 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_16_M              (0x4 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_32_M              (0x5 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_64_M              (0x6 << TIMER16_PRESCALER_S)
#define TIMER16_PRESCALER_128_M             (0x7 << TIMER16_PRESCALER_S)

// Alias for CFGR.ENC bit
#define TIMER16_ENCODER_S                   24
#define TIMER16_ENCODER_DISABLE_M           (0x0 << TIMER16_ENCODER_S)
#define TIMER16_ENCODER_ENABLE_M            (0x1 << TIMER16_ENCODER_S)

#define TIMER16_INT_CMP_MATCH_S             0
#define TIMER16_INT_CMP_MATCH_M             (0x1 << TIMER16_INT_CMP_MATCH_S)
#define TIMER16_INT_ARR_MATCH_S             1
#define TIMER16_INT_ARR_MATCH_M             (0x1 << TIMER16_INT_ARR_MATCH_S)
#define TIMER16_INT_EXT_TRIG_S              2
#define TIMER16_INT_EXT_TRIG_M              (0x1 << TIMER16_INT_EXT_TRIG_S)
#define TIMER16_INT_CMP_OK_S                3
#define TIMER16_INT_CMP_OK_M                (0x1 << TIMER16_INT_CMP_OK_S)
#define TIMER16_INT_ARR_OK_S                4
#define TIMER16_INT_ARR_OK_M                (0x1 << TIMER16_INT_ARR_OK_S)
#define TIMER16_INT_UP_S                    5
#define TIMER16_INT_UP_M                    (0x1 << TIMER16_INT_UP_S)
#define TIMER16_INT_DOWN_S                  6
#define TIMER16_INT_DOWN_M                  (0x1 << TIMER16_INT_DOWN_S)


#define TIMER16_CFGR_ENC_S                  24
#define TIMER16_CFGR_ENC_M                  (1 << TIMER16_CFGR_ENC_S)
#define TIMER16_CFGR_COUNTMODE_S            23
#define TIMER16_CFGR_COUNTMODE_M            (1 << TIMER16_CFGR_COUNTMODE_S)
#define TIMER16_CFGR_PRELOAD_S              22
#define TIMER16_CFGR_PRELOAD_M              (1 << TIMER16_CFGR_PRELOAD_S)
#define TIMER16_CFGR_WAVPOL_S               21
#define TIMER16_CFGR_WAVPOL_M               (1 << TIMER16_CFGR_WAVPOL_S)
#define TIMER16_CFGR_WAVE_S                 20
#define TIMER16_CFGR_WAVE_M                 (1 << TIMER16_CFGR_WAVE_S)
#define TIMER16_CFGR_TIMOUT_S               19
#define TIMER16_CFGR_TIMOUT_M               (1 << TIMER16_CFGR_TIMOUT_S)
#define TIMER16_CFGR_TRIGEN_S               17
#define TIMER16_CFGR_TRIGEN_M               (0x3 << TIMER16_CFGR_TRIGEN_S)
//
#define TIMER16_CFGR_TRIGSEL_S              13
#define TIMER16_CFGR_TRIGSEL_M              (0x7 << TIMER16_CFGR_TRIGSEL_S)
//
#define TIMER16_CFGR_TRGFLT_S               6
#define TIMER16_CFGR_TRGFLT_M               (0x3 << TIMER16_CFGR_TRGFLT_S)
#define TIMER16_CFGR_TRGFLT_DISABLED_M      (0x0 << TIMER16_CFGR_TRGFLT_S)
#define TIMER16_CFGR_TRGFLT_2_M             (0x1 << TIMER16_CFGR_TRGFLT_S)
#define TIMER16_CFGR_TRGFLT_4_M             (0x2 << TIMER16_CFGR_TRGFLT_S)
#define TIMER16_CFGR_TRGFLT_8_M             (0x3 << TIMER16_CFGR_TRGFLT_S)
#define TIMER16_CFGR_CKFLT_S                3
#define TIMER16_CFGR_CKFLT_M                (0x3 << TIMER16_CFGR_CKFLT_S)
#define TIMER16_CFGR_CKFLT_DISABLED_M       (0x0 << TIMER16_CFGR_CKFLT_S)
#define TIMER16_CFGR_CKFLT_2_M              (0x1 << TIMER16_CFGR_CKFLT_S)
#define TIMER16_CFGR_CKFLT_4_M              (0x2 << TIMER16_CFGR_CKFLT_S)
#define TIMER16_CFGR_CKFLT_8_M              (0x3 << TIMER16_CFGR_CKFLT_S)
#define TIMER16_CFGR_CKPOL_S                1
#define TIMER16_CFGR_CKPOL_M                (0x3 << TIMER16_CFGR_CKPOL_S)
#define TIMER16_CFGR_CKPOL_RISING_M         (0x0 << TIMER16_CFGR_CKPOL_S)
#define TIMER16_CFGR_CKPOL_FALLING_M        (0x1 << TIMER16_CFGR_CKPOL_S)
#define TIMER16_CFGR_CKPOL_ANY_M            (0x2 << TIMER16_CFGR_CKPOL_S)
#define TIMER16_CFGR_CKSEL_S                0
#define TIMER16_CFGR_CKSEL_M                (1 << TIMER16_CFGR_CKSEL_S)
#define TIMER16_CFGR_CKSEL_INTERNAL_M       (0x0 << TIMER16_CFGR_CKSEL_S)
#define TIMER16_CFGR_CKSEL_EXTERNAL_M       (0x1 << TIMER16_CFGR_CKSEL_S)


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t ISR;
        volatile uint32_t ICR;
        volatile uint32_t IER;
        volatile uint32_t CFGR;
        volatile uint32_t CR;
        volatile uint32_t CMP;
        volatile uint32_t ARR;
        volatile uint32_t CNT;
    
        
    } TIMER16_TypeDef;
#endif

#endif // TIMER16_H_INCLUDED
