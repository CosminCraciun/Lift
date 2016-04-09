#include <pic16f628a.h>
#include <xc.h>

#include "timer.h"

void initTimer()
{
    // clear the register
    T1CON = 0;
    
    // set the frequency of the interrupt
    T1CONbits.T1CKPS = 0b11;    // 1:8 Prescaler value
    TMR1 = 0xFFFF - 625;        // for 1 KHz frequency (1ms period interrupt)
    
    // clear the interrupt flag
    PIR1bits.TMR1IF = 0;
    
    // start the timer
    T1CONbits.TMR1ON = 1;   
    
    // enable the interrupt
    PIE1bits.TMR1IE = 1; 
}