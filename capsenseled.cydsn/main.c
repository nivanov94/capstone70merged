
#include <project.h>
#include <stdio.h>
#include "stdbool.h"
#include "CyBLE_custom.h"
#include "main.h"
#include "fsm.h"
#include "PWM.h"
#include "IDAC.h"
#include "adc.h"
#include "PGA.h"
#include "print.h"


/* LED control defines (active low)*/
#define LIGHT_OFF                       (1u)
#define LIGHT_ON                        (0u)

#define LOW_FILT  0
#define MID_FILT  1
#define HIGH_FILT 2

#define MIC_GAIN 68/2.2

// Flag to indicate when to sample digital lines.
uint8 sample_lines;

/*******************************************************************************
* Defines the interrupt service routine and allocates a vector to the interrupt.
* We use one handler for both the Capture and Terminal Count interrupts
* We toggle the active LED upon each Terminal Count interrupt
* We toggle the color (active LED) between blue and green upon each Capture 
* interrupt
********************************************************************************/

CY_ISR(InterruptHandler)
{    
    if (Timer_INTR_MASK_TC == Timer_GetInterruptSource()) {
        // Timer has overflowed, 1ms has elapsed.
        // Clear interrupt, then set flag to execute finite state control loop.
        Timer_ClearInterrupt(Timer_INTR_MASK_TC);
        sample_lines = 1;        
    }
}

/***************************************************************
 * Main
 **************************************************************/
int main()
{
#if !defined(__ARMCC_VERSION)
    InitializeBootloaderSRAM();
#endif
    
    CyGlobalIntEnable;
    
    UART_Start();
    
    /* Start BLE stack and register the callback function */
    CyBle_Start(AppCallBack);
    
    CyDelay(100u);

    char str[100];
    sprintf(str, "Application entered \n");
    UART_PutString(str);
    
    ConfigureSharedPins();
    
    LED_RED_Write(0);
        
    PGA_set_gain(MIC_GAIN);
    
    /*enable ADC, PWM, and IDAC for threshold initialization */
    init_PWM();
    init_IDAC();
    ADC_init();
    
    /*set comparator thresholds*/
    CyDelay(5);
    set_PWM_threshold(LOW_FILT);
    set_PWM_threshold(MID_FILT);
    set_PWM_threshold(HIGH_FILT);
    set_IDAC_threshold();
    
    /*put ADC to sleep*/
    ADC_sleep();
     
    /* Enable interrupt component connected to interrupt */
    TC_CC_ISR_StartEx(InterruptHandler);

    /* Start sampling timer */
    Timer_Start();
    
    fsm_init();

    for(;;)
    {        
        if (sample_lines) {
            sample_lines = 0;
            fsm_tick();
        }
            
        CyBle_ProcessEvents();
        BootloaderSwitch();
           
    }
}
