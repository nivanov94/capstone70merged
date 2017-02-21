/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include "adc.h"

#define VOLT_SCALING 5.0/3.3

void ADC_init(void) {
    ADC_SAR_Seq_1_Enable();
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
}

void ADC_flush(void) {
 
    int i;
    
    for (i = 0; i < 8; i++) {
        ADC_SAR_Seq_1_GetResult16(i%4);
    }
}

void ADC_sleep(void) {
    ADC_SAR_Seq_1_Sleep();
}

void ADC_wakeup(void) {
    ADC_SAR_Seq_1_Wakeup();
}

float ADC_read(int channel) {
    return ADC_SAR_Seq_1_CountsTo_Volts(channel, ADC_SAR_Seq_1_GetResult16(channel))*VOLT_SCALING;
}

/* [] END OF FILE */
