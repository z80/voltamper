
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
// Oscilloscope replacement for parametric plots.
void setBufferPeriod( uint32_t t );
void setBufferSigMask( uint8_t mask );

void setFbSetpoint( int sp );
void setFbInput( int ind );
void setFbGain( int num, int den );
void setFbEn( int en );

OutputQueue * commandQueue( void );
InputQueue * eauxQueue( void );
InputQueue * erefQueue( void );
InputQueue * iauxQueue( void );
InputQueue * bufferQueue( void );

#endif



