#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED


#define RTC_TIME_OFFSET         0x00
#define RTC_DATE_OFFSET         0x04
#define RTC_TALRM_OFFSET        0x08
#define RTC_DALRM_OFFSET        0x0C
#define RTC_CTRL_OFFSET         0x10
#define RTC_BACKUP_REG_OFFSET   0x20



#define RTC_CTRL_EN_S           31
#define RTC_CTRL_EN_M           (1 << RTC_CTRL_EN_S)
#define RTC_CTRL_ALRM_S         30
#define RTC_CTRL_ALRM_M         (1 << RTC_CTRL_ALRM_S)
#define RTC_CTRL_INTE_S         29
#define RTC_CTRL_INTE_M         (1 << RTC_CTRL_INTE_S)
#define RTC_CTRL_FLAG_S         28
#define RTC_CTRL_FLAG_M         (1 << RTC_CTRL_FLAG_S)
#define RTC_CTRL_RESET_STROBE_S 27
#define RTC_CTRL_RESET_STROBE_M (1 << RTC_CTRL_RESET_STROBE_S)


#define RTC_TALRM_CDOW_S        31
#define RTC_TALRM_CDOW_M        (1 << RTC_TALRM_CDOW_S)
#define RTC_TALRM_CH_S          30
#define RTC_TALRM_CH_M          (1 << RTC_TALRM_CH_S)
#define RTC_TALRM_CM_S          29
#define RTC_TALRM_CM_M          (1 << RTC_TALRM_CM_S)
#define RTC_TALRM_CS_S          28
#define RTC_TALRM_CS_M          (1 << RTC_TALRM_CS_S)
#define RTC_TALRM_CTOS_S        27
#define RTC_TALRM_CTOS_M        (1 << RTC_TALRM_CTOS_S)

#define RTC_DALRM_CC_S          30
#define RTC_DALRM_CC_M          (1 << RTC_DALRM_CC_S)
#define RTC_DALRM_CY_S          29
#define RTC_DALRM_CY_M          (1 << RTC_DALRM_CY_S)
#define RTC_DALRM_CM_S          28
#define RTC_DALRM_CM_M          (1 << RTC_DALRM_CM_S)
#define RTC_DALRM_CD_S          27
#define RTC_DALRM_CD_M          (1 << RTC_DALRM_CD_S)

#define RTC_TIME_DOW_S          24
#define RTC_TIME_DOW_M          (0x7 << RTC_TIME_DOW_S)

#define RTC_TIME_TH_S           22
#define RTC_TIME_TH_M           (0x3 << RTC_TIME_TH_S)
#define RTC_TIME_H_S            18
#define RTC_TIME_H_M            (0xF << RTC_TIME_H_S)
#define RTC_TIME_TM_S           15
#define RTC_TIME_TM_M           (0x7 << RTC_TIME_TM_S)
#define RTC_TIME_M_S            11
#define RTC_TIME_M_M            (0xF << RTC_TIME_M_S)
#define RTC_TIME_TS_S           8
#define RTC_TIME_TS_M           (0x7 << RTC_TIME_TS_S)
#define RTC_TIME_S_S            4
#define RTC_TIME_S_M            (0xF << RTC_TIME_S_S)
#define RTC_TIME_TOS_S          0
#define RTC_TIME_TOS_M          (0xF << RTC_TIME_TOS_S)

#define RTC_DATE_TC_S           23
#define RTC_DATE_TC_M           (0xF << RTC_DATE_TC_S)
#define RTC_DATE_C_S            19
#define RTC_DATE_C_M            (0xF << RTC_DATE_C_S)
#define RTC_DATE_TY_S           15
#define RTC_DATE_TY_M           (0xF << RTC_DATE_TY_S)
#define RTC_DATE_Y_S            11
#define RTC_DATE_Y_M            (0xF << RTC_DATE_Y_S)
#define RTC_DATE_TM_S           10
#define RTC_DATE_TM_M           (0x1 << RTC_DATE_TM_S)
#define RTC_DATE_M_S            6
#define RTC_DATE_M_M            (0xF << RTC_DATE_M_S)
#define RTC_DATE_TD_S           4
#define RTC_DATE_TD_M           (0x3 << RTC_DATE_TD_S)
#define RTC_DATE_D_S            0
#define RTC_DATE_D_M            (0xF << RTC_DATE_D_S)



#ifndef _ASSEMBLER_
    #include <inttypes.h> 
    typedef struct
    {   
       
        union
        {
            struct {
                volatile uint32_t TOS:4;
                volatile uint32_t S:4;
                volatile uint32_t TS:3;
                volatile uint32_t M:4;
                volatile uint32_t TM:3;
                volatile uint32_t H:4;
                volatile uint32_t TH:2;
                volatile uint32_t DOW:3;
            };
            uint32_t TIME;
        };
        
        volatile uint32_t DATE;  
        volatile uint32_t TALRM;         
        volatile uint32_t DALRM;         
        volatile uint32_t CTRL;         
        volatile uint32_t _space[3];
        volatile uint32_t REG[16];
    } RTC_TypeDef;
#endif

#endif 

