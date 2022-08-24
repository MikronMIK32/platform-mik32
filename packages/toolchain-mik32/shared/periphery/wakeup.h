#ifndef WU_H_INCLUDED
#define WU_H_INCLUDED

#define WU_Dom0_Mask_OFFSET             0x00
#define WU_Dom0_Level_OFFSET            0x04
#define WU_Dom0_PowerOff_OFFSET         0x08
#define WU_PowerSwitch_On_Bat_OFFSET    0x0C
#define WU_Clocks_OFFSET                0x10
#define WU_RTC_Control_OFFSET           0x14
#define WU_BOOT                         0x28

#define WU_RTC_RESET_S                  0
#define WU_RTC_RESET_SET_M              0<<WU_RTC_RESET_S
#define WU_RTC_RESET_CLEAR_M            1<<WU_RTC_RESET_S

#define WU_OSC32K_S                     0
#define WU_LSI32K_S                     1


#define WU_RTC_ALARM_S            0
#define WU_EXT_LINE_S             1

#define WU_RTC_ALARM_M    (0x1 << WU_RTC_ALARM_S)
#define WU_EXT_LINE_M     (0x1 << WU_EXT_LINE_S)

#define WU_CLOCKS_BU_OSC32K_PD_S           0
#define WU_CLOCKS_BU_LSI32K_PD_S           1
#define WU_CLOCKS_BU_ADJ_LSI32K_S          2
#define WU_CLOCKS_BU_ADJ_LSI32K_M          (0xFF << WU_CLOCKS_BU_ADJ_LSI32K_S)
#define WU_CLOCKS_BU_ADJ_LSI32K(v)         (((v) << WU_CLOCKS_BU_ADJ_LSI32K_S) & WU_CLOCKS_BU_ADJ_LSI32K_M)
#define WU_CLOCKS_BU_ADJ_LSI32K_S          2
#define WU_CLOCKS_BU_ADJ_LSI32K_M          (0xFF << WU_CLOCKS_BU_ADJ_LSI32K_S)
#define WU_CLOCKS_BU_RTC_CLK_MUX_S         10
#define WU_CLOCKS_BU_RTC_CLK_MUX_M         (0x3 << WU_CLOCKS_BU_RTC_CLK_MUX_S)
#define WU_CLOCKS_BU_RTC_CLK_MUX_LSI32K_M  (0x1 << WU_CLOCKS_BU_RTC_CLK_MUX_S)
#define WU_CLOCKS_BU_RTC_CLK_MUX_OSC32K_M  (0x2 << WU_CLOCKS_BU_RTC_CLK_MUX_S)

#define WU_CLOCKS_SYS_OSC32M_PD_S           0
#define WU_CLOCKS_SYS_HSI32M_PD_S           1
#define WU_CLOCKS_SYS_ADJ_HSI32M_S          2

#define WU_MASK_WAKEUP_RTC_S                0
#define WU_MASK_WAKEUP_EXT_S                1
#define WU_MASK_SYS_RESET_LDO_S             2
#define WU_MASK_SYS_RESET_VOLTMON_S         3
#define WU_MASK_SYS_RESET_BOR_S             4

#define WU_MASK_BU_RESET_BOR_S              5

    
#ifndef _ASSEMBLER_
    #include <inttypes.h> 
    typedef struct
    {   
       
        volatile uint32_t DOM0_MASK;  
        volatile uint32_t DOM0_LEVEL;         
        volatile uint32_t DOM0_POWEROFF;         
        volatile uint32_t POWER_SWITCH_ON;
        volatile uint32_t CLOCKS_BU;  
        volatile uint32_t CLOCKS_SYS;  
        volatile uint32_t RTC_CONRTOL;
        volatile uint32_t STOP_MODE;
    } WU_TypeDef;
#endif

#endif 

