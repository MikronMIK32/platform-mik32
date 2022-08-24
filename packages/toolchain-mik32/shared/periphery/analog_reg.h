#ifndef ANALOG_REG_H_INCLUDED
#define ANALOG_REG_H_INCLUDED

#define DAC_CFG_EN18_S          0
#define DAC_CFG_EN18_M          (1 << DAC_CFG_EN18_S)
#define DAC_CFG_RESN_S          1
#define DAC_CFG_RESN_M          (1 << DAC_CFG_RESN_S)
#define DAC_CFG_DIV_S           2
#define DAC_CFG_DIV_M           (0xFF << DAC_CFG_DIV_S)
#define DAC_CFG_DIV(v)          (((v) << DAC_CFG_DIV_S) & DAC_CFG_DIV_M)
#define DAC_CFG_EXTEN_S         10
#define DAC_CFG_EXTEN_M         (1 << DAC_CFG_EXTEN_S)
#define DAC_EXTPAD_EN_S         11




#define TSENS_NPD_S             0
#define TSENS_NPD_CLK_S         1
#define TSENS_NRST_S            2
#define TSENS_TRIM_S            3
#define TSENS_DIV               13

#define TSENS_IRQ_EOS_S         3
#define TSENS_IRQ_HI_S          4
#define TSENS_IRQ_LOW_S         5
#define TSENS_IRQ_MASK_EOS_S    0
#define TSENS_IRQ_MASK_HI_S     1
#define TSENS_IRQ_MASK_LOW_S    2

#define TSENS_IRQ_CLEAR_EOS_S   0
#define TSENS_IRQ_CLEAR_HI_S    1
#define TSENS_IRQ_CLEAR_LOW_S   2

#define TSENS_HI_THRESHOLD_S    0
#define TSENS_LOW_THRESHOLD_S   10

 
#define TSENS_VALUE(i)          (uint32_t)((i+273.15)*1024/619.2)

#define ADC_EN_S                0
#define ADC_RESETn_S            1
#define ADC_EXTREF_S            2
#define ADC_EXTPAD_EN_S         3
#define ADC_SEL_S               4
#define ADC_COS_S               7

#define REF_CLB_VCOEF_S         0
#define REF_CLB_ICOEF_S         4
#define REF_CLB_EN_S            8


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t CFG;
        volatile uint32_t VALUE;        
    } DAC_TypeDef;
    
    
    typedef struct
    {
        volatile DAC_TypeDef    DAC0;
        volatile DAC_TypeDef    DAC1;   
        volatile uint32_t       DPF_VALUE;
        volatile uint32_t       PVD_CONFIG;
        volatile uint32_t       PVD_STATUS;
        volatile uint32_t       TSENS_CONFIG;
        volatile uint32_t       TSENS_THRESHOLD;
        volatile uint32_t       TSENS_IRQ;
        volatile uint32_t       TSENS_CLEAR_IRQ;
        volatile uint32_t       TSENS_VALUE;
        volatile uint32_t       TSENS_SINGLE;
        volatile uint32_t       TSENS_CONTINIUS;
        volatile uint32_t       REFV_CONFIG;
        volatile uint32_t       ADC_CONFIG;
        volatile uint32_t       ADC_CONTINIUS;
        volatile uint32_t       ADC_SINGLE;
        volatile uint32_t       ADC_VALID;
        volatile uint32_t       ADC_VALUE;
    } ANALOG_REG_TypeDef;
    
#endif

#endif // ANALOG_REG_H_INCLUDED

    