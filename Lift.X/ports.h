/* 
 * File:   ports.h
 * Author: cosmi
 *
 * Created on 29 martie 2016, 22:07
 */

#ifndef PORTS_H
#define	PORTS_H

#define RELEASED                    0
#define PRESSED                     1

void initPorts(void);
unsigned char debounceInput(unsigned char input, unsigned char *tempState, unsigned char currentState);

#endif	/* PORTS_H */

