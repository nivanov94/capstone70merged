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

typedef enum {
    TYPE_NO_ALARM,
    TYPE_FIRE_ALARM,
    TYPE_AMBULANCE,
} alarm_state_e;

typedef enum {
    INTENSITY_MUTE,
    INTENSITY_LOW,
    INTENSITY_MEDIUM,
    INTENSITY_HIGH,
} vib_intensity_e;

typedef enum {
    DURATION_5S,
    DURATION_10S,
    DURATION_20S,
    DURATION_30S,
} vib_duration_e;

typedef enum {
    VIBTYPE_CONTINUOUS,
    VIBTYPE_INTERVAL,
} vib_type_e;


/* [] END OF FILE */
