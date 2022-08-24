#ifndef OTP_H_INCLUDED
#define OTP_H_INCLUDED

//--------------------------
// OTP register fields
//--------------------------


#define OTP_APBNWS_S                        0
#define OTP_BSY_S                           0
#define OTP_N_RA_S                          8
#define OTP_N_RH_S                          16



#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
    //--------------------------
    // OTP registers
    //--------------------------

    volatile uint32_t OTPDAT;
    volatile uint32_t OTPA;
    volatile uint32_t OTPCON;
    volatile uint32_t OTPSTA;
    volatile uint32_t OTPDEC;
    volatile uint32_t OTPADJ;
    volatile uint32_t OTPWT1;
    volatile uint32_t OTPWT2;
    

    } OTP_TypeDef;
#endif


#endif // OTP_H_INCLUDED

