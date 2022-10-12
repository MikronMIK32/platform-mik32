#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#define SPI_CONFIG        	0x00
#define SPI_STATUS        	0x04
#define SPI_IEN           	0x08 
#define SPI_IDIS          	0x0C 
#define SPI_IMASK         	0x10 
#define SPI_ENABLE        	0x14
#define SPI_DELAY         	0x18
#define SPI_TXD           	0x1C
#define SPI_RXD           	0x20
#define SPI_SIC           	0x24
#define SPI_THRESHOLD     	0x28
#define SPI_MODULE_ID     	0xFC


#define SPI_CONFIG_Manual_CS_S		14
#define SPI_CONFIG_Manual_CS_M		(1 << SPI_CONFIG_Manual_CS_S)
//
#define SPI_CONFIG_CS_S				10
#define SPI_CONFIG_CS_M				(0xF << SPI_CONFIG_CS_S)
#define SPI_CONFIG_CS_0_M			(0xE << SPI_CONFIG_CS_S)
#define SPI_CONFIG_CS_1_M			(0xD << SPI_CONFIG_CS_S)
#define SPI_CONFIG_CS_2_M			(0xB << SPI_CONFIG_CS_S)
#define SPI_CONFIG_CS_3_M			(0x7 << SPI_CONFIG_CS_S)
#define SPI_CONFIG_CS_NONE_M		(0xF << SPI_CONFIG_CS_S)
//
#define SPI_CONFIG_PERI_SEL_S		9
#define SPI_CONFIG_PERI_SEL_M		(1 << SPI_CONFIG_PERI_SEL_S)
#define SPI_CONFIG_REF_CLK_S		8
#define SPI_CONFIG_REF_CLK_M		(1 << SPI_CONFIG_REF_CLK_S)
//
#define SPI_CONFIG_BAUD_RATE_DIV_S		3
#define SPI_CONFIG_BAUD_RATE_DIV_M		(0x7 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_2_M	(0x0 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_4_M	(0x1 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_8_M	(0x2 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_16_M	(0x3 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_32_M	(0x4 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_64_M	(0x5 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_128_M	(0x6 << SPI_CONFIG_BAUD_RATE_DIV_S)
#define SPI_CONFIG_BAUD_RATE_DIV_256_M	(0x7 << SPI_CONFIG_BAUD_RATE_DIV_S)
//
#define SPI_MAXIMUM_BAUD_RATE_DIV		256
//
#define SPI_CONFIG_CLK_PH_S				2
#define SPI_CONFIG_CLK_PH_M				(1 << SPI_CONFIG_CLK_PH_S)
#define SPI_CONFIG_CLK_POL_S			1
#define SPI_CONFIG_CLK_POL_M			(1 << SPI_CONFIG_CLK_POL_S)
#define SPI_CONFIG_MODE_SEL_S			0
#define SPI_CONFIG_MODE_SEL_M			(1 << SPI_CONFIG_MODE_SEL_S)
#define SPI_CONFIG_MASTER_M				(1 << SPI_CONFIG_MODE_SEL_S)
#define SPI_CONFIG_SLAVE_M				(0 << SPI_CONFIG_MODE_SEL_S)


#define SPI_ENABLE_S		0
#define SPI_ENABLE_M		(1 << SPI_ENABLE_S)


#define SPI_RX_OVERFLOW_S		0
#define SPI_RX_OVERFLOW_M		(1<<SPI_RX_OVERFLOW_S)
#define SPI_MODE_FAIL_S			1
#define SPI_MODE_FAIL_M			(1<<SPI_MODE_FAIL_S)
#define SPI_TX_FIFO_not_full_S	2
#define SPI_TX_FIFO_not_full_M	(1<<SPI_TX_FIFO_not_full_S)
#define SPI_TX_FIFO_full_S		3
#define SPI_TX_FIFO_full_M		(1<<SPI_TX_FIFO_full_S)
#define SPI_RX_FIFO_not_empty_S	4
#define SPI_RX_FIFO_not_empty_M	(1<<SPI_RX_FIFO_not_empty_S)
#define SPI_RX_FIFO_full_S		5
#define SPI_RX_FIFO_full_M		(1<<SPI_RX_FIFO_full_S)
#define SPI_TX_FIFO_underflow_S	6
#define SPI_TX_FIFO_underflow_M	(1<<SPI_TX_FIFO_underflow_S)



#ifndef _ASSEMBLER_
    #include <inttypes.h> 
    typedef struct
    {
      volatile uint32_t Config;            /* Offset: 0x000 (R/W)    */
      volatile uint32_t IntStatus;         /* Offset: 0x004 (R/W)  */
      volatile uint32_t IntEnable;         /* Offset: 0x008 (R/W) */
      volatile uint32_t IntDisable;        /* Offset: 0x00C (R/W)  */
      volatile uint32_t IntMask;           /* Offset: 0x010 (R)  */
      volatile uint32_t Enable;            /* Offset: 0x014 (R/W)  */
      volatile uint32_t Delay;             /* Offset: 0x018 (R/W)  */
      volatile uint32_t TxData;            /* Offset: 0x01C (W)  */
      volatile uint32_t RxData;            /* Offset: 0x020 (R)  */
      volatile uint32_t SIC;               /* Offset: 0x024 (R/W)  Slave_Idle_Count */
      volatile uint32_t TxThr;             /* Offset: 0x028 (R/W)  TX threshold */
      volatile uint32_t Reserved[0x34];    /* Empty array to fill the space*/
      volatile uint32_t ID;                /* Offset: 0x0FC (R)  Module ID 0x01090100 */
    }SPI_TypeDef;
#endif


#endif // SPI_H_INCLUDED
