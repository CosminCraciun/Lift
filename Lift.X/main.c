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
    unsigned char mainState = STATE_IDLE;
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
            case STATE_IDLE :
            {
                // do nothing
                ;
            }
            break;
            case STOP :
            {
                // STOP everything
                UP = DOWN = 0;
                // check for button press
                if (NOT_MOVING != movingDirection)
                {
                    TurnOnButtons();
                    movingDirection = NOT_MOVING;
                }
                
                if (buttonPressed != currentLevel && buttonPressed != 0)
                {
                    TurnOnLeds();
                    SetLeds(buttonPressed);
                    
                    if (buttonPressed > currentLevel)
                    {
                        movingDirection = GOING_UP;
                    }
                    else
                    {
                        movingDirection = GOING_DOWN;
                    }
                    
                    mainState = CHECK;
                }
            }
            break;
            case CHECK :
            {
                // check for security glitches
                if (    ( PRESSED == inputs[SAFETY_1_POS] ) &&
                        ( PRESSED == inputs[SAFETY_1_POS] ) &&
                        ( PRESSED == inputs[SAFETY_1_POS] ) )
                {
                    mainState = STOP;
                    emergencyStop = 1;
                    UP = DOWN = 0;
                    SetLeds(0);
                }
                else if ( currentLevel == buttonPressed )
                {
                    waiting = 0;
                    UP = DOWN = 0;
                    mainState = REACHED;
                }
                else
                {
                    mainState = GO;
                }
            }
            break;
            case GO :
            {
                emergencyStop = 0;
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
                
                // just go and check for destination
                mainState = CHECK;
                
                //currentLevel = getLevel();
                ;
            }            
            break;
            case REACHED :
            {
                UP = DOWN = 0;
                
                if ( WAIT_FOR_MS < waiting )
                {                 
                    SetLeds(0);   
                    TurnOnButtons();
                    mainState = STOP;
                }
                else
                {
                    mainState = REACHED;
                }
                
            }
            break;
            default:
            {
                mainState = STATE_IDLE;
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

void interrupt MainInterrupt()
{
    // timer 1 interrupt
    if ( 1 == PIR1bits.TMR1IF )
    {
        msPassed++;
        
        if ( REACHED == readCurrentState )
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
