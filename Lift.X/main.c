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

void  debounce();
unsigned char checkLevelChange();

/*
 * 
 */

unsigned char inputs[INPUT_MAX];
unsigned char tempInput[INPUT_MAX];
unsigned char readCurrentState;
unsigned int waiting;

int main(int argc, char** argv) 
{
    unsigned char currentLevel = 0;
    unsigned char mainState = STATE_STOP;
    unsigned char movingDirection = NOT_MOVING;
    unsigned char emergencyStop = 0;
    
    InitPorts();    
    InitTimer();
    
    // infinite loop
    while (1)
    {        
        readCurrentState = mainState;
        
        switch (mainState)
        {
            case STATE_STOP :
            {
                // STOP everything
                UP = DOWN = 0;
                
                if ( 0 == buttonMode )
                {
                    TurnOnButtons();
                }
                
                if (buttonPressed != currentLevel && buttonPressed != 0)
                {
                    TurnOnLeds();
                    
                    if (buttonPressed > currentLevel)
                    {
                        movingDirection = GOING_UP;
                    }
                    else
                    {
                        movingDirection = GOING_DOWN;
                    }
                    
                    mainState = STATE_CHECK;
                }
            }
            break;
            case STATE_CHECK :
            {
                // check for security glitches
                if (    ( PRESSED == inputs[SAFETY_1_POS] ) &&
                        ( PRESSED == inputs[SAFETY_1_POS] ) &&
                        ( PRESSED == inputs[SAFETY_1_POS] ) )
                {
                    mainState = STATE_STOP;
                    UP = DOWN = 0;
                    SetLeds(0); 
                }
                else if ( currentLevel == buttonPressed )
                {
                    waiting = 0;
                    mainState = STATE_REACHED;
                }
                else if ( GOING_DOWN == movingDirection && 0 != inputs[DELIMITER_DOWN] )
                {
                    mainState = STATE_STOP;
                    currentLevel = 1;
                }
                else if ( GOING_UP == movingDirection && 0 != inputs[DELIMITER_UP] )
                {
                    mainState = STATE_STOP;
                    currentLevel = LAST_LEVEL;
                }
                else
                {
                    mainState = STATE_RUN;
                }
            }
            break;
            case STATE_RUN :
            {
                if ( GOING_UP == movingDirection )
                {
                    DOWN = 0;
                    UP = 1;
                }
                else
                {
                    DOWN = 1;
                    UP = 0;
                }
                if ( GOING_UP == movingDirection)
                { // going up
                    currentLevel += checkLevelChange();
                }
                else
                { // going down
                    currentLevel -= checkLevelChange();
                }
                
            }
            break;
            case STATE_REACHED :
            {
                UP = DOWN = 0;
                
                if ( WAIT_FOR_MS < waiting )
                {                 
                    SetLeds(0);   
                    TurnOnButtons();
                    mainState = STATE_STOP;
                }
                else
                {
                    mainState = STATE_REACHED;
                }
                
            }
            break;
            default:
            {
                mainState = STATE_STOP;
            }
        }
    }
    
    return (EXIT_SUCCESS);
}

void Debounce()
{
    inputs[SAFETY_1_POS]         = DebounceInput(SAFETY_1,tempInput + SAFETY_1_POS,             inputs[SAFETY_1_POS]);
    inputs[SAFETY_2_POS]         = DebounceInput(SAFETY_2,tempInput + SAFETY_2_POS,             inputs[SAFETY_2_POS]);
    inputs[SAFETY_3_POS]         = DebounceInput(SAFETY_3,tempInput + SAFETY_3_POS,             inputs[SAFETY_3_POS]);
    inputs[DELIMITER_DOWN_POS]   = DebounceInput(DELIMITER_DOWN,tempInput + DELIMITER_DOWN_POS, inputs[DELIMITER_DOWN_POS]);
    inputs[DELIMITER_UP_POS]     = DebounceInput(DELIMITER_UP,tempInput + DELIMITER_UP_POS,     inputs[DELIMITER_UP_POS]);
    inputs[COUNTER_POS]          = DebounceInput(COUNTER,tempInput + COUNTER_POS,               inputs[COUNTER_POS]); 
    
    if (1 == buttonMode)
    {
        buttonPressed = 0;        
        inputs[BUTTON_0_POS]     = DebounceInput(BUTTON_0,tempInput + BUTTON_0_POS,             inputs[BUTTON_0_POS]);
        buttonPressed = inputs[BUTTON_0_POS];
        inputs[BUTTON_1_POS]     = DebounceInput(BUTTON_1,tempInput + BUTTON_1_POS,             inputs[BUTTON_1_POS]);
        buttonPressed |= (inputs[BUTTON_1_POS] << 1);
        inputs[BUTTON_2_POS]     = DebounceInput(BUTTON_2,tempInput + BUTTON_2_POS,             inputs[BUTTON_2_POS]);
        buttonPressed |= (inputs[BUTTON_2_POS] << 2);
        
    }
}

unsigned char checkLevelChange()
{
    static unsigned char pastCounter;
    unsigned char returnValue = 0;
    
    if ( 1 == pastCounter && 0 == inputs[COUNTER_POS])
    {
        // just passed a counter
    }
    else if ( 0 == pastCounter && 1 == inputs[COUNTER_POS])
    {
        // just arrived at a counter        
        returnValue = 1;
    }
    
    pastCounter = inputs[COUNTER_POS];
    
    return returnValue;
}

void interrupt MainInterrupt()
{
    // timer 1 interrupt
    if ( 1 == PIR1bits.TMR1IF )
    {
        msPassed++;
        
        if ( STATE_REACHED == readCurrentState )
        {
            waiting++;
        }
        
        if (msPassed % 4 == 0)
        {
            Debounce();
        }
    }
    
    // clear all interrupts
    PIR1 = 0;
}
