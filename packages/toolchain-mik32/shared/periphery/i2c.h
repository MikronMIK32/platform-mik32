#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED


#define I2C_CR1_PE_S                    0
#define I2C_CR1_PE_M                    (1 << I2C_CR1_PE_S)
#define I2C_CR1_TXIE_S                  1
#define I2C_CR1_TXIE_M                  (1 << I2C_CR1_TXIE_S)
#define I2C_CR1_RXIE_S                  2
#define I2C_CR1_RXIE_M                  (1 << I2C_CR1_RXIE_S)
#define I2C_CR1_ADDRIE_S                3
#define I2C_CR1_ADDRIE_M                (1 << I2C_CR1_ADDRIE_S)
#define I2C_CR1_NACKIE_S                4
#define I2C_CR1_NACKIE_M                (1 << I2C_CR1_NACKIE_S)
#define I2C_CR1_STOPIE_S                5
#define I2C_CR1_STOPIE_M                (1 << I2C_CR1_STOPIE_S)
#define I2C_CR1_TCIE_S                  6
#define I2C_CR1_TCIE_M                  (1 << I2C_CR1_TCIE_S)
#define I2C_CR1_ERRIE_S                 7
#define I2C_CR1_ERRIE_M                 (1 << I2C_CR1_ERRIE_S)
#define I2C_CR1_DNF_S                   8
#define I2C_CR1_DNF_M                   (0xF << I2C_CR1_DNF_S)
#define I2C_CR1_DNF(v)                  (((v) << I2C_CR1_DNF_S) & I2C_CR1_DNF_M)
#define I2C_CR1_ANFOFF_S                12
#define I2C_CR1_ANFOFF_M                (1 << I2C_CR1_ANFOFF_S)
//
#define I2C_CR1_TXDMAEN_S               14
#define I2C_CR1_TXDMAEN_M               (1 << I2C_CR1_TXDMAEN_S)
#define I2C_CR1_RXDMAEN_S               15
#define I2C_CR1_RXDMAEN_M               (1 << I2C_CR1_RXDMAEN_S)
#define I2C_CR1_SBC_S                   16
#define I2C_CR1_SBC_M                   (1 << I2C_CR1_SBC_S)
#define I2C_CR1_NOSTRETCH_S             17
#define I2C_CR1_NOSTRETCH_M             (1 << I2C_CR1_NOSTRETCH_S)
//
#define I2C_CR1_GCEN_S                  19
#define I2C_CR1_GCEN_M                  (1 << I2C_CR1_GCEN_S)


#define I2C_CR2_SADD_S                  0
#define I2C_CR2_SADD_M                  (0x3FF << I2C_CR2_SADD_S)
#define I2C_CR2_SADD(v)                 (((v) << I2C_CR2_SADD_S) &I2C_CR2_SADD_M)
#define I2C_CR2_RD_WRN_S                10    
#define I2C_CR2_RD_WRN_M                (1 << I2C_CR2_RD_WRN_S)
#define I2C_CR2_RD_M                    (1 << I2C_CR2_RD_WRN_S)
#define I2C_CR2_WR_M                    (0 << I2C_CR2_RD_WRN_S)
#define I2C_CR2_ADD10_S                 11
#define I2C_CR2_ADD10_M                 (1 << I2C_CR2_ADD10_S)
#define I2C_CR2_HEAD10R_S               12
#define I2C_CR2_HEAD10R_M               (1 << I2C_CR2_HEAD10R_S)
#define I2C_CR2_START_S                 13
#define I2C_CR2_START_M                 (1 << I2C_CR2_START_S)
#define I2C_CR2_STOP_S                  14
#define I2C_CR2_STOP_M                  (1 << I2C_CR2_STOP_S)
#define I2C_CR2_NACK_S                  15
#define I2C_CR2_NACK_M                  (1 << I2C_CR2_NACK_S)
#define I2C_CR2_NBYTES_S                16  
#define I2C_CR2_NBYTES_M                (0xFF << I2C_CR2_NBYTES_S)
#define I2C_CR2_NBYTES(v)               (((v) << I2C_CR2_NBYTES_S) & I2C_CR2_NBYTES_M)
#define I2C_CR2_RELOAD_S                24
#define I2C_CR2_RELOAD_M                (1 << I2C_CR2_RELOAD_S)
#define I2C_CR2_AUTOEND_S               25
#define I2C_CR2_AUTOEND_M               (1 << I2C_CR2_AUTOEND_S)


#define I2C_OAR1_OA1_S                  0
#define I2C_OAR1_OA1_M                  (0x3FF << I2C_OAR1_OA1_S)
#define I2C_OAR1_OA1MODE_S              10
#define I2C_OAR1_OA1MODE_M              (1 << I2C_OAR1_OA1MODE_S)
//
#define I2C_OAR1_OA1EN_S                15
#define I2C_OAR1_OA1EN_M                (1 << I2C_OAR1_OA1EN_S)


#define I2C_OAR2_OA2_S                  1
#define I2C_OAR2_OA2_M                  (0x7F << I2C_OAR2_OA2_S)
#define I2C_OAR2_OA2MSK_S              8
#define I2C_OAR2_OA2MSK_M              (0x7 << I2C_OAR2_OA2MSK_S)
//
#define I2C_OAR2_OA2EN_S                15
#define I2C_OAR2_OA2EN_M                (1 << I2C_OAR2_OA2EN_S)


#define I2C_TIMINGR_SCLL_S              0
#define I2C_TIMINGR_SCLL_M              (0xFF << I2C_TIMINGR_SCLL_S)
#define I2C_TIMINGR_SCLL(v)             (((v) << I2C_TIMINGR_SCLL_S) & I2C_TIMINGR_SCLL_M)
#define I2C_TIMINGR_SCLH_S              8
#define I2C_TIMINGR_SCLH_M              (0xFF << I2C_TIMINGR_SCLH_S)
#define I2C_TIMINGR_SCLH(v)             (((v) << I2C_TIMINGR_SCLH_S) & I2C_TIMINGR_SCLH_M)
#define I2C_TIMINGR_SDADEL_S            16
#define I2C_TIMINGR_SDADEL_M            (0xF << I2C_TIMINGR_SDADEL_S)
#define I2C_TIMINGR_SDADEL(v)           (((v) << I2C_TIMINGR_SDADEL_S) & I2C_TIMINGR_SDADEL_M)
#define I2C_TIMINGR_SCLDEL_S            20
#define I2C_TIMINGR_SCLDEL_M            (0xF << I2C_TIMINGR_SCLDEL_S)
#define I2C_TIMINGR_SCLDEL(v)           (((v) << I2C_TIMINGR_SCLDEL_S) & I2C_TIMINGR_SCLDEL_M)
#define I2C_TIMINGR_PRESC_S             28
#define I2C_TIMINGR_PRESC_M             (0xF << I2C_TIMINGR_PRESC_S)
#define I2C_TIMINGR_PRESC(v)            (((v) << I2C_TIMINGR_PRESC_S) & I2C_TIMINGR_PRESC_M)


#define I2C_ISR_TXE_S                   0
#define I2C_ISR_TXE_M                   (1 << I2C_ISR_TXE_S)
#define I2C_ISR_TXIS_S                  1
#define I2C_ISR_TXIS_M                  (1 << I2C_ISR_TXIS_S)
#define I2C_ISR_RXNE_S                  2
#define I2C_ISR_RXNE_M                  (1 << I2C_ISR_RXNE_S)
#define I2C_ISR_ADDR_S                  3
#define I2C_ISR_ADDR_M                  (1 << I2C_ISR_ADDR_S)
#define I2C_ISR_NACKF_S                 4
#define I2C_ISR_NACKF_M                 (1 << I2C_ISR_NACKF_S)
#define I2C_ISR_STOPF_S                 5
#define I2C_ISR_STOPF_M                 (1 << I2C_ISR_STOPF_S)
#define I2C_ISR_TC_S                    6
#define I2C_ISR_TC_M                    (1 << I2C_ISR_TC_S)
#define I2C_ISR_TCR_S                   7
#define I2C_ISR_TCR_M                   (1 << I2C_ISR_TCR_S)
#define I2C_ISR_BERR_S                  8
#define I2C_ISR_BERR_M                  (1 << I2C_ISR_BERR_S)
#define I2C_ISR_ARLO_S                  9
#define I2C_ISR_ARLO_M                  (1 << I2C_ISR_ARLO_S)
#define I2C_ISR_OVR_S                   10
#define I2C_ISR_OVR_M                   (1 << I2C_ISR_OVR_S)
//
#define I2C_ISR_BUSY_S                  15
#define I2C_ISR_BUSY_M                  (1 << I2C_ISR_BUSY_S)
#define I2C_ISR_DIR_S                   16
#define I2C_ISR_DIR_M                   (1 << I2C_ISR_DIR_S)
#define I2C_ISR_ADDCODE_S               17
#define I2C_ISR_ADDCODE_M               (0x7F << I2C_ISR_ADDCODE_S)


#define I2C_ICR_ADDRCF_S                3
#define I2C_ICR_ADDRCF_M                (1 << I2C_ICR_ADDRCF_S)
#define I2C_ICR_NACKCF_S                4
#define I2C_ICR_NACKCF_M                (1 << I2C_ICR_NACKCF_S)
#define I2C_ICR_STOPCF_S                5
#define I2C_ICR_STOPCF_M                (1 << I2C_ICR_STOPCF_S)
//
#define I2C_ICR_BERRCF_S                8
#define I2C_ICR_BERRCF_M                (1 << I2C_ICR_BERRCF_S)
#define I2C_ICR_ARLOCF_S                9
#define I2C_ICR_ARLOCF_M                (1 << I2C_ICR_ARLOCF_S)
#define I2C_ICR_OVRCF_S                 10
#define I2C_ICR_OVRCF_M                 (1 << I2C_ICR_OVRCF_S)


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t CR1;
        volatile uint32_t CR2;
        volatile uint32_t OAR1;
        volatile uint32_t OAR2;
        volatile uint32_t TIMINGR;
        volatile uint32_t reserved0;
        volatile uint32_t ISR;
        volatile uint32_t ICR;
        volatile uint32_t reserved1;
        volatile uint32_t RXDR;
        volatile uint32_t TXDR;
    } I2C_TypeDef;
#endif

#endif // I2C_H_INCLUDED

