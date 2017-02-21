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

#include <project.h>
#include "filter.h"

int8 filter_sample(int8 reading, queue_t *prev) {
    int temp = (int)reading;
    temp += sum(prev);
    push(prev, reading);
    return (temp >> 2);
}

int filter_count(int8 reading, queue_t *prev, int count) {
    if (filter_sample(reading, prev)) {
        count++;
    }
    else {
        if (count > 0) {
            count--;
        }
    }
    return count;
}

/* [] END OF FILE */
