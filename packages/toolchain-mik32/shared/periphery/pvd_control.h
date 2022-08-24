#ifndef PVD_CONTROL_H_INCLUDED
#define PVD_CONTROL_H_INCLUDED

#define PVD_PD_S            0
#define PVD_NRESETU_S       1
#define PVD_NRESETO_S       2
#define PVD_TESTMODE_S      3
#define PVD_SREF_S          4
#define PVD_UNDER_THRESH_S  5
#define PVD_OVER_THRESH_S   9
#define PVD_EN_VREFCLB_S    13

#define PVD_UNDER_VALUE_S   0
#define PVD_OVER_VALUE_S    1
#define PVD_UNDER_FLAG_S    2
#define PVD_OVER_FLAG_S     3

#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t       DPF_VALUE;
        volatile uint32_t       CONFIG;
        volatile uint32_t       STATUS;
    } PVD_CONTROL_TypeDef;
    
#endif

#endif // PVD_CONTROL_H_INCLUDED

