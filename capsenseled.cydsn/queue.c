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
#include "queue.h"

int sum(queue_t *queue) {
    int sum = 0;
    int i;
    for(i = 0; i < QUEUE_SIZE; i++) {
        sum += (int)(queue->data[i]);
    }
    return sum;
}

void push(queue_t *queue, int8 val) {
    queue->head = (queue->head + 1) % QUEUE_SIZE;
    queue->data[queue->head] = val;
}

void init_queue(queue_t *queue) {
    int i;
    queue->head = -1;
    for (i = 0; i < QUEUE_SIZE; i++) {
        queue->data[i] = 0;
    }
}

int8 peek(queue_t *queue) {
    return queue->data[queue->head];
}



/* [] END OF FILE */
