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

#ifndef ADC_H
#define ADC_H
    
void ADC_init(void);
void ADC_flush(void);
void ADC_sleep(void);
void ADC_wakeup(void);
float ADC_read(int channel);

#endif

/* [] END OF FILE */
