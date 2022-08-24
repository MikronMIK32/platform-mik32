#ifndef DMA_MC_H_INCLUDED
#define DMA_MC_H_INCLUDED

#define DMA_CHANNEL_COUNT                   4


#define DMA_CFG_CH_ENABLE_S                 0
#define DMA_CFG_CH_ENABLE_M                 (1 << DMA_CFG_CH_ENABLE_S)  
#define DMA_CFG_CH_DISABLE_M                (0 << DMA_CFG_CH_ENABLE_S)  

#define DMA_CFG_CH_PRIOR_S                  1
#define DMA_CFG_CH_PRIOR_M                  (0x3 << DMA_CFG_CH_PRIOR_S)

#define DMA_CFG_CH_READ_MODE_S              3
#define DMA_CFG_CH_READ_MODE_memory_M       (1 << DMA_CFG_CH_READ_MODE_S)
#define DMA_CFG_CH_READ_MODE_periphery_M    (0 << DMA_CFG_CH_READ_MODE_S)

#define DMA_CFG_CH_WRITE_MODE_S             4
#define DMA_CFG_CH_WRITE_MODE_memory_M      (1 << DMA_CFG_CH_WRITE_MODE_S)
#define DMA_CFG_CH_WRITE_MODE_periphery_M   (0 << DMA_CFG_CH_WRITE_MODE_S)

#define DMA_CFG_CH_READ_INCREMENT_S         5
#define DMA_CFG_CH_READ_INCREMENT_M         (1 << DMA_CFG_CH_READ_INCREMENT_S)
#define DMA_CFG_CH_READ_no_INCREMENT_M      (0 << DMA_CFG_CH_READ_INCREMENT_S)

#define DMA_CFG_CH_WRITE_INCREMENT_S        6
#define DMA_CFG_CH_WRITE_INCREMENT_M        (1 << DMA_CFG_CH_WRITE_INCREMENT_S)
#define DMA_CFG_CH_WRITE_no_INCREMENT_M     (0 << DMA_CFG_CH_WRITE_INCREMENT_S)

#define DMA_CFG_CH_READ_SIZE_S              7
#define DMA_CFG_CH_READ_SIZE_byte_M         (0B00 << DMA_CFG_CH_READ_SIZE_S)      // байт
#define DMA_CFG_CH_READ_SIZE_2byte_M        (0B01 << DMA_CFG_CH_READ_SIZE_S)     // полуслово
#define DMA_CFG_CH_READ_SIZE_4byte_M        (0B10 << DMA_CFG_CH_READ_SIZE_S)     // слово
#define DMA_CFG_CH_READ_SIZE_rez_M          (0B11 << DMA_CFG_CH_READ_SIZE_S)      // резерв

#define DMA_CFG_CH_WRITE_SIZE_S             9
#define DMA_CFG_CH_WRITE_SIZE_byte_M        (0B00 << DMA_CFG_CH_WRITE_SIZE_S)  // байт
#define DMA_CFG_CH_WRITE_SIZE_2byte_M       (0B01 << DMA_CFG_CH_WRITE_SIZE_S)  // полуслово
#define DMA_CFG_CH_WRITE_SIZE_4byte_M       (0B10 << DMA_CFG_CH_WRITE_SIZE_S)  // слово
#define DMA_CFG_CH_WRITE_SIZE_rez_M         (0B11 << DMA_CFG_CH_WRITE_SIZE_S)  // резерв

#define DMA_CFG_CH_READ_BURST_SIZE_S        11    //Кол-во байт пакетной передачи:   2^Read_burst_size
#define DMA_CFG_CH_WRITE_BURST_SIZE_S       14    //Кол-во байт пакетной передачи:   2^Write_burst_size

#define DMA_CFG_CH_READ_REQ_S               17    // выбор канала чтения 
#define DMA_CFG_CH_READ_REQ_M               (0xF << DMA_CFG_CH_READ_REQ_S)
#define DMA_CFG_CH_READ_REQ(v)              (((v) << DMA_CFG_CH_READ_REQ_S) & DMA_CFG_CH_READ_REQ_M)

#define DMA_CFG_CH_WRITE_REQ_S              21    // выбор канала записи 
#define DMA_CFG_CH_WRITE_REQ_M              (0xF << DMA_CFG_CH_WRITE_REQ_S)
#define DMA_CFG_CH_WRITE_REQ(v)             (((v) << DMA_CFG_CH_WRITE_REQ_S) & DMA_CFG_CH_WRITE_REQ_M)


#define DMA_CFG_CH_ACK_READ_S               25
#define DMA_CFG_CH_ACK_READ_M               (1 << DMA_CFG_CH_ACK_READ_S)
#define DMA_CFG_CH_ACK_WRITE_S              26
#define DMA_CFG_CH_ACK_WRITE_M              (1 << DMA_CFG_CH_ACK_WRITE_S)
#define DMA_CFG_CH_EN_IRQ_S                 27
#define DMA_CFG_CH_EN_IRQ_M                 (1 << DMA_CFG_CH_EN_IRQ_S)

#define DMA_CHANNEL_M                       ((1 << DMA_CHANNEL_COUNT) - 1) 

#define DMA_STATUS_READY_S                  0
#define DMA_STATUS_READY_M                  (DMA_CHANNEL_M << DMA_STATUS_READY_S)
#define DMA_STATUS_READY(i)                 ((1 << (DMA_STATUS_READY_S + (i))) & DMA_STATUS_READY_M)
#define DMA_STATUS_IRQ_S                    1*DMA_CHANNEL_COUNT
#define DMA_STATUS_IRQ_M                    (DMA_CHANNEL_M << DMA_STATUS_IRQ_S)
#define DMA_CLEAR_IRQ_S                     0
#define DMA_STATUS_ERROR_S                  2*DMA_CHANNEL_COUNT
#define DMA_STATUS_ERROR_M                  (DMA_CHANNEL_M << DMA_STATUS_ERROR_S)

#define DMA_CONTROL_CLEAR_LOCAL_IRQ_S       0
#define DMA_CONTROL_CLEAR_LOCAL_IRQ_M       (DMA_CHANNEL_M << DMA_CONTROL_CLEAR_LOCAL_IRQ_S)
#define DMA_CONTROL_CLEAR_LOCAL_IRQ(i)      ((1 << (DMA_CONTROL_CLEAR_LOCAL_IRQ_S + (i))) & DMA_CONTROL_CLEAR_LOCAL_IRQ_M)
#define DMA_CONTROL_CLEAR_GLOBAL_IRQ_S      (DMA_CHANNEL_COUNT + 0)
#define DMA_CONTROL_CLEAR_GLOBAL_IRQ_M      (1 << DMA_CONTROL_CLEAR_GLOBAL_IRQ_S)
#define DMA_CONTROL_CLEAR_ERROR_IRQ_S       (DMA_CHANNEL_COUNT + 1)
#define DMA_CONTROL_CLEAR_ERROR_IRQ_M       (1 << DMA_CONTROL_CLEAR_ERROR_IRQ_S)
#define DMA_CONTROL_GLOBAL_IRQ_ENA_S        (DMA_CHANNEL_COUNT + 2)
#define DMA_CONTROL_GLOBAL_IRQ_ENA_M        (1 << DMA_CONTROL_GLOBAL_IRQ_ENA_S)
#define DMA_CONTROL_ERROR_IRQ_ENA_S         (DMA_CHANNEL_COUNT + 3)
#define DMA_CONTROL_ERROR_IRQ_ENA_M         (1 << DMA_CONTROL_ERROR_IRQ_ENA_S)
#define DMA_CONTROL_CURRENT_VALUE_S         (DMA_CHANNEL_COUNT + 4)
#define DMA_CONTROL_CURRENT_VALUE_M         (1 << DMA_CONTROL_CURRENT_VALUE_S)

#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {

        volatile uint32_t DESTINATIONS ;  // 0x00
        volatile uint32_t SOURCE ;        // 0x04
        volatile uint32_t LEN  ;          // 0x08        
        volatile uint32_t CONFIG ;        // 0x0c
    } DMA_CHANNEL_TypeDef  ;
    
    typedef struct
    { 
    
        DMA_CHANNEL_TypeDef CHANNELS[DMA_CHANNEL_COUNT];
        volatile uint32_t ConfigStatus ;  // 0x80
            
    } DMA_CONFIG_TypeDef;
#endif


#endif //
