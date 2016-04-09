
#include <pic.h>
#include <pic16f628a.h>
#include <xc.h>

#include "defines.h"
#include "ports.h"

unsigned char debounceStates[10];
unsigned char buttonMode;
unsigned char buttonPressed;

void InitPorts()
{
    // everything as input
    TRISA = 0xFF;
    TRISB = 0xFF;
    
    DISPLAY_A_DIR = OUTPUT;
    DISPLAY_B_DIR = OUTPUT;
    DISPLAY_C_DIR = OUTPUT;
    
    TurnOnButtons();
    
    SAFETY_1_DIR = INPUT;
    SAFETY_2_DIR = INPUT;
    SAFETY_3_DIR = INPUT;        
    
    UP_DIR = OUTPUT;
    DOWN_DIR = OUTPUT;

    DELIMITER_DOWN_DIR = INPUT;
    DELIMITER_UP_DIR = INPUT;
    
    COUNTER_DIR = INPUT;
}

void TurnOnButtons()
{   
    buttonMode = 1;
    
    BUTTON_0_DIR = INPUT;
    BUTTON_1_DIR = INPUT;
    BUTTON_2_DIR = INPUT;
}

void TurnOnLeds()
{  
    buttonMode = 0;
    
    BUTTON_0_DIR = OUTPUT;
    BUTTON_1_DIR = OUTPUT;
    BUTTON_2_DIR = OUTPUT;
}

void SetLeds(unsigned char leds)
{
    BUTTON_0 =  leds       & 0x01;
    BUTTON_1 = (leds >> 1) & 0x01;
    BUTTON_2 = (leds >> 2) & 0x01;
}

unsigned char DebounceInput(unsigned char input, unsigned char *tempState, unsigned char currentState)
{
    *tempState <<= 1;
    *tempState |= input;
        
    if ( 0 == 0xFF & *tempState)
    { // all 8 bytes are 0 then the button is released
        return RELEASED;
    }
    else if ( 0xFF  == 0xFF & *tempState)
    { // all 8 bytes are 1 then the button is pressed
        return PRESSED;
    }
    else return currentState;    
}
