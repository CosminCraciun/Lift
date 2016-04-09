/* 
 * File:   main.c
 * Author: cosmi
 *
 * Created on 29 martie 2016, 21:04
 */

#include <stdio.h>
#include <stdlib.h>

#include <pic.h>
#include <pic16f628a.h>

#include "defines.h"
#include "ports.h"
#include "timer.h"

/*
 * 
 */

unsigned char mainState;
unsigned int msPassed;
unsigned char inputs[INPUT_MAX];
unsigned char tempInput[INPUT_MAX];
unsigned char moving = 0;

int main(int argc, char** argv) 
{
    initPorts();    
    initTimer();
    
    mainState = STATE_IDLE;
    moving = 0;
    
    // infinite loop
    while (1)
    {
        mainState = setState(mainState);
        
        switch (mainState)
        {
            case STATE_IDLE :
            {
                // do nothing
                ;
            }
            break;
            
            break;
            default:
            {
                mainState = STATE_IDLE;
            }
        }
    }
    
    return (EXIT_SUCCESS);
}

unsigned char setState(unsigned char currentState)
{
    if (RELEASED == inputs[SAFETY_1_POS] || RELEASED == inputs[SAFETY_2_POS] || RELEASED == inputs[SAFETY_3_POS])
    {
        return STOP;
    }
    else
        if(1 == moving && PRESSED);
        
        return STATE_IDLE;
}


void interrupt mainInterrupt()
{
    // timer 1 interrupt
    if ( 1 == PIR1bits.TMR1IF )
    {
        msPassed++;
        
        if (0 == msPassed % 4)
        {
            inputs[BUTTON_0_POS]         = debounceInput(BUTTON_0,tempInput + BUTTON_0_POS,         inputs[BUTTON_0_POS]);
            inputs[BUTTON_1_POS]         = debounceInput(BUTTON_0,tempInput + BUTTON_1_POS,         inputs[BUTTON_1_POS]);
            inputs[BUTTON_2_POS]         = debounceInput(BUTTON_0,tempInput + BUTTON_2_POS,         inputs[BUTTON_2_POS]);
            inputs[SAFETY_1_POS]         = debounceInput(BUTTON_0,tempInput + SAFETY_1_POS,         inputs[SAFETY_1_POS]);
            inputs[SAFETY_2_POS]         = debounceInput(BUTTON_0,tempInput + SAFETY_2_POS,         inputs[SAFETY_2_POS]);
            inputs[SAFETY_3_POS]         = debounceInput(BUTTON_0,tempInput + SAFETY_3_POS,         inputs[SAFETY_3_POS]);
            inputs[DELIMITER_DOWN_POS]   = debounceInput(BUTTON_0,tempInput + DELIMITER_DOWN_POS,   inputs[DELIMITER_DOWN_POS]);
            inputs[DELIMITER_UP_POS]     = debounceInput(BUTTON_0,tempInput + DELIMITER_UP_POS,     inputs[DELIMITER_UP_POS]);
            inputs[COUNTER_POS]          = debounceInput(BUTTON_0,tempInput + COUNTER_POS,          inputs[COUNTER_POS]);
        }
    }
    
    // clear all interrupts
    PIR1 = 0;
}
