
#ifndef __ADC_CTRL_H_
#define __ADC_CTRL_H_

#include "ch.h"

// Modes of operation.
#define TDAC      0
#define TONEPULSE 1
#define TMEANDR   2
#define TSWEEP    3
#define TFEEDBACK 4

void initAdc( void );

void setOscPeriod( uint32_t t );
void setContinuousOsc( uint8_t en );
void startOsc( void );
uint8_t oscStopped( void );

OutputQueue * commandQueue( void );
InputQueue * eauxQueue( void );
InputQueue * erefQueue( void );
InputQueue * iauxQueue( void );

void setCurrentGain( int fbgain );
void setCurrent( int fbsp );

#endif



