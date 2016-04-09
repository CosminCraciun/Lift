
#include <pic.h>
#include <pic16f628a.h>
#include <xc.h>

#include "defines.h"
#include "ports.h"

unsigned char debounceStates[10];

void initPorts()
{
    // everything as input
    TRISA = 0xFF;
    TRISB = 0xFF;
    
    DISPLAY_A_DIR = OUTPUT;
    DISPLAY_B_DIR = OUTPUT;
    DISPLAY_C_DIR = OUTPUT;
    
    BUTTON_0_DIR = INPUT;
    BUTTON_1_DIR = INPUT;
    BUTTON_2_DIR = INPUT;
    
    SAFETY1_DIR = INPUT;
    SAFETY2_DIR = INPUT;
    SAFETY3_DIR = INPUT;        
    
    UP_DIR = OUTPUT;
    DOWN_DIR = OUTPUT;
    
    SAFETY1_DIR = INPUT;
    SAFETY2_DIR = INPUT;
    SAFETY3_DIR = INPUT;
    
    DELIMITER_DOWN_DIR = INPUT;
    DELIMITER_UP_DIR = INPUT;
    
    COUNTER_DIR = INPUT;
}

unsigned char debounceInput(unsigned char input, unsigned char *tempState, unsigned char currentState)
{
    *tempState <<= 1;
    *tempState |= input;
        
    if ( 0 == 0xFF & debounceStates[0])
    { // all 8 bytes are 0 then the button is released
        return RELEASED;
    }
    else if ( 0xFF  == 0xFF & debounceStates[0])
    { // all 8 bytes are 1 then the button is pressed
        return PRESSED;
    }
    else return currentState;    
}
