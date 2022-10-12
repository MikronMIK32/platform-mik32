#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

//--------------------------
// EEPROM register fields
//--------------------------
//EECON
#define EEPROM_EX_S         0
#define EEPROM_OP_S         1
#define EEPROM_WRBEH_S      3
#define EEPROM_APBNWS_S     5
#define EEPROM_DISECC_S     6
#define EEPROM_BWE_S        7
#define EEPROM_IESERR_S     8
//EESTA
#define EEPROM_BSY_S        0
#define EEPROM_SERR_S       1
//NCYCRL
#define EEPROM_N_LD_S       0
#define EEPROM_N_R_1_S      8
#define EEPROM_N_R_2_S      16
//--------------------------
// EEPROM codes
//--------------------------
#define EEPROM_OP_RD        0
#define EEPROM_OP_ER        1
#define EEPROM_OP_PR        2
#define EEPROM_BEH_EVEN     1
#define EEPROM_BEH_ODD      2
#define EEPROM_BEH_GLOB     3


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
    //--------------------------
    // EEPROM registers
    //--------------------------

    volatile uint32_t EEDAT;
    volatile uint32_t EEA;
    volatile uint32_t EECON;
    volatile uint32_t EESTA;
    volatile uint32_t EERB;
    volatile uint32_t EEADJ;
    volatile uint32_t NCYCRL;
    volatile uint32_t NCYCEP1;
    volatile uint32_t NCYCEP2;

    } EEPROM_REGS_TypeDef;
#endif


#endif // EEPROM_H_INCLUDED

