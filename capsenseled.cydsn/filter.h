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
#ifndef FILTER_H
#define FILTER_H
    
#include <project.h>

#include "queue.h"

int8 filter_sample(int8 reading, queue_t *prev);
int filter_count(int8 reading, queue_t *prev, int count);

#endif
/* [] END OF FILE */
