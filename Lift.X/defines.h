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

// main states
enum{
    STATE_IDLE,
    STOP
};
//#define START_MOVING        


/// ports ----------------------------------------------------------------------

// inputs

// Button inputs
#define BUTTON_0                        PORTAbits.RA5
#define BUTTON_1                        PORTBbits.RB0
#define BUTTON_2                        PORTBbits.RB3
// port direction
#define BUTTON_0_DIR                    TRISAbits.TRISA5
#define BUTTON_1_DIR                    TRISBbits.TRISB0
#define BUTTON_2_DIR                    TRISBbits.TRISB3

// Safety circuit
#define SAFETY1                         PORTBbits.RB6
#define SAFETY2                         PORTBbits.RB7
#define SAFETY3                         PORTAbits.RA6
// port direction
#define SAFETY1_DIR                     TRISBbits.TRISB6
#define SAFETY2_DIR                     TRISBbits.TRISB7
#define SAFETY3_DIR                     TRISAbits.TRISA6

// delimiter
#define DELIMITER_DOWN                  PORTAbits.RA7
#define DELIMITER_UP                    PORTAbits.RA0
// port direction
#define DELIMITER_DOWN_DIR              TRISAbits.TRISA7
#define DELIMITER_UP_DIR                TRISAbits.TRISA0

// counter
#define COUNTER                         PORTAbits.RA1
// port direction
#define COUNTER_DIR                     TRISAbits.TRISA1


// outputs  

// A, B, C display
#define DISPLAY_A                       PORTAbits.RA2
#define DISPLAY_B                       PORTAbits.RA3
#define DISPLAY_C                       PORTAbits.RA4
// port directions
#define DISPLAY_A_DIR                   TRISAbits.TRISA2
#define DISPLAY_B_DIR                   TRISAbits.TRISA3
#define DISPLAY_C_DIR                   TRISAbits.TRISA4

// Up/Down
#define UP                              PORTBbits.RB4
#define DOWN                            PORTBbits.RB5
// port direction
#define UP_DIR                          PORTBbits.RB4
#define DOWN_DIR                        PORTBbits.RB5


// positions
enum{
BUTTON_0_POS,
BUTTON_1_POS,                   
BUTTON_2_POS,                   
SAFETY_1_POS,                   
SAFETY_2_POS,                   
SAFETY_3_POS,                   
DELIMITER_DOWN_POS,
DELIMITER_UP_POS,  
COUNTER_POS,
INPUT_MAX
};

#endif	/* DEFINES_H */

