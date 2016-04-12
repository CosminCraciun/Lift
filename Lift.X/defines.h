/* 
 * File:   defines.h
 * Author: cosmi
 *
 * Created on 29 martie 2016, 21:06
 */

#ifndef DEFINES_H
#define	DEFINES_H

// general
#define INPUT               1
#define OUTPUT              0

#define WAIT_FOR_MS         5000

#define LAST_LEVEL          3           // last level with ground level

#define NOT_MOVING      0
#define GOING_UP        1
#define GOING_DOWN      2

// main states
enum{
    STATE_STOP,
    STATE_CHECK,
    STATE_RUN,
    STATE_REACHED
};
//#define START_MOVING        

// positions
enum{                  
SAFETY_1_POS,                   
SAFETY_2_POS,                   
SAFETY_3_POS,                   
DELIMITER_DOWN_POS,
DELIMITER_UP_POS,  
COUNTER_POS,
BUTTON_0_POS,
BUTTON_1_POS,                   
BUTTON_2_POS,

INPUT_MAX
};

#endif	/* DEFINES_H */

