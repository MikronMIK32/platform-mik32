#ifndef TIMER32_H_INCLUDED
#define TIMER32_H_INCLUDED


#define TIMER32_VALUE			    0x00
#define TIMER32_TOP				    0x04
#define TIMER32_PRESCALER		    0x08
#define TIMER32_CONTROL			    0x0C
#define TIMER32_ENABLE              0x10

#define TIMER32_INT_MASK       	    0x14   
#define TIMER32_INT_CLEAR      	    0x18   
#define TIMER32_INT_FLAGS           0x1C   

#define TIMER32_CH_BASE			    0x80
#define TIMER32_CH_CONTROL_OFFSET	0x00
#define TIMER32_CH_OCR_OFFSET		0x04
#define TIMER32_CH_ICR_OFFSET		0x08
#define TIMER32_CH_SIZE			    0x10


#define TIMER32_CONTROL_MODE_S	        	0
#define TIMER32_CONTROL_MODE_M		        (0x3 << TIMER32_CONTROL_MODE_S)
#define TIMER32_CONTROL_CLOCK_S	    	    2
#define TIMER32_CONTROL_CLOCK_M		        (0x3 << TIMER32_CONTROL_CLOCK_S)
//
#define TIMER32_CONTROL_MODE_UP_M	        (0 << TIMER32_CONTROL_MODE_S)
#define TIMER32_CONTROL_MODE_DOWN_M	        (1 << TIMER32_CONTROL_MODE_S)
#define TIMER32_CONTROL_MODE_BIDIR_M	    (2 << TIMER32_CONTROL_MODE_S)	
//
#define TIMER32_CONTROL_CLOCK_M			    (0x3 << TIMER32_CONTROL_CLOCK_S)
#define TIMER32_CONTROL_CLOCK_PRESCALER_M	(0x0 << TIMER32_CONTROL_CLOCK_S)
#define TIMER32_CONTROL_CLOCK_TIM1_M		(0x1 << TIMER32_CONTROL_CLOCK_S)
#define TIMER32_CONTROL_CLOCK_TX_PIN_M		(0x2 << TIMER32_CONTROL_CLOCK_S)
#define TIMER32_CONTROL_CLOCK_TIM2_M		(0x3 << TIMER32_CONTROL_CLOCK_S)


#define TIMER32_PRESCALER_ENABLE_S	        8
#define TIMER32_PRESCALER_ENABLE_M	        (1 << TIMER32_PRESCALER_ENABLE_S)
#define TIMER32_PRESCALER_DISABLE_M	        (0 << TIMER32_PRESCALER_ENABLE_S)
//
#define TIMER32_PRESCALER_S			        0
#define TIMER32_PRESCALER_M			        (0xFF << TIMER32_PRESCALER_S)


#define TIMER32_ENABLE_S				    0
#define TIMER32_ENABLE_M				    (1 << TIMER32_ENABLE_S)
#define TIMER32_DISABLE_M				    (0 << TIMER32_ENABLE_S)
#define TIMER32_RESET_VALUE_S			    1
#define TIMER32_RESET_VALUE_M			    (1 << TIMER32_RESET_VALUE_S)


#define TIMER32_INT_OVERFLOW_S		        0
#define TIMER32_INT_OVERFLOW_M		        (1 << TIMER32_INT_OVERFLOW_S)
#define TIMER32_INT_UNDERFLOW_S		        1
#define TIMER32_INT_UNDERFLOW_M		        (1 << TIMER32_INT_UNDERFLOW_S)


#define TIMER32_CH_CONTROL_CAPTURE_EDGE_S	4
#define TIMER32_CH_CONTROL_CAPTURE_EDGE_M	(1 << TIMER32_CH_CONTROL_CAPTURE_EDGE_S)
#define TIMER32_CH_CONTROL_CAPTURE_POS_M	(0 << TIMER32_CH_CONTROL_CAPTURE_EDGE_S)
#define TIMER32_CH_CONTROL_CAPTURE_NEG_M	(1 << TIMER32_CH_CONTROL_CAPTURE_EDGE_S)
//
#define TIMER32_CH_CONTROL_MODE_S			5
#define TIMER32_CH_CONTROL_MODE_M			(3 << TIMER32_CH_CONTROL_MODE_S)
#define TIMER32_CH_CONTROL_MODE_COMPARE_M	(1 << TIMER32_CH_CONTROL_MODE_S)
#define TIMER32_CH_CONTROL_MODE_CAPTURE_M	(2 << TIMER32_CH_CONTROL_MODE_S)
#define TIMER32_CH_CONTROL_MODE_PWM_M		(3 << TIMER32_CH_CONTROL_MODE_S)
//
#define TIMER32_CH_CONTROL_ENABLE_S		    7
#define TIMER32_CH_CONTROL_ENABLE_M		    (1 << TIMER32_CH_CONTROL_ENABLE_S)
#define TIMER32_CH_CONTROL_DISABLE_M		(0 << TIMER32_CH_CONTROL_ENABLE_S)
//
#define TIMER32_CH_CONTROL_INVERTED_PWM_S	8
#define TIMER32_CH_CONTROL_INVERTED_PWM_M	(1 << TIMER32_CH_CONTROL_INVERTED_PWM_S)


#ifndef _ASSEMBLER_
    #include <inttypes.h>

    typedef struct
    {
        volatile uint32_t Control;
        volatile uint32_t OCR;
        volatile uint32_t ICR;
        volatile uint32_t reserved0;
    } TIMER32_CHANNEL_TypeDef;
    
    typedef struct
    {
        volatile uint32_t Value;        /* Offset: 0x000 (R)  */
        volatile uint32_t Top;          /* Offset: 0x004 (R/W)  */
        volatile uint32_t Prescaler;    /* Offset: 0x008 (R/W)  */
        volatile uint32_t Control;      /* Offset: 0x00C (R/W)  */
        volatile uint32_t Enable;       /* Offset: 0x010 (R/W)  */
        volatile uint32_t IntMask;      /* Offset: 0x014 (R/W)  */
        volatile uint32_t IntClear;     /* Offset: 0x018 (R/W)  */
        volatile uint32_t IntFlags;     /* Offset: 0x01C (R)  */
        
        volatile uint8_t  reserved0[0x60];
        TIMER32_CHANNEL_TypeDef Channels[4];
        
    } TIMER32_TypeDef;
#endif

#endif // TIMER32_H_INCLUDED
