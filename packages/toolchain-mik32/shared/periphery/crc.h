#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#define CRC_DATA                    0x00 
#define CRC_POLY                    0x04 
#define CRC_CTRL                    0x08 

#define CRC_CTRL_TOT_S              30
#define CRC_CTRL_TOT_M              (3 << CRC_CTRL_TOT_S)
#define CRC_CTRL_TOT_NONE_M         (0 << CRC_CTRL_TOT_S)
#define CRC_CTRL_TOT_BITS_M         (1 << CRC_CTRL_TOT_S)
#define CRC_CTRL_TOT_BITS_BYTES_M   (2 << CRC_CTRL_TOT_S)
#define CRC_CTRL_TOT_BYTES_M        (3 << CRC_CTRL_TOT_S)

//
#define CRC_CTRL_TOTR_S             28
#define CRC_CTRL_TOTR_M             (3 << CRC_CTRL_TOTR_S)
#define CRC_CTRL_TOTR_NONE_M        (0 << CRC_CTRL_TOTR_S)
#define CRC_CTRL_TOTR_BITS_M        (1 << CRC_CTRL_TOTR_S)
#define CRC_CTRL_TOTR_BITS_BYTES_M  (2 << CRC_CTRL_TOTR_S)
#define CRC_CTRL_TOTR_BYTES_M       (3 << CRC_CTRL_TOTR_S)
//
#define CRC_CTRL_FXOR_S             26
#define CRC_CTRL_FXOR_M             (1 << CRC_CTRL_FXOR_S)
#define CRC_CTRL_WAS_S              25
#define CRC_CTRL_WAS_M              (1 << CRC_CTRL_WAS_S)
//
#define CRC_CTRL_TCRC_S             24
#define CRC_CTRL_TCRC_M             (1 << CRC_CTRL_TCRC_S)
#define CRC_CTRL_TCRC_16_M          (0 << CRC_CTRL_TCRC_S)
#define CRC_CTRL_TCRC_32_M          (1 << CRC_CTRL_TCRC_S)
//
#define CRC_CTRL_BUSY_S             0
#define CRC_CTRL_BUSY_M             (1 << CRC_CTRL_BUSY_S)


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        union
        {
            volatile uint8_t DATA8;
            volatile uint16_t DATA16;
            volatile uint32_t DATA32;            
        };
        volatile uint32_t POLY;               
        volatile uint32_t CTRL;       
    } CRC_TypeDef;

#endif

#endif // CRC_H_INCLUDED