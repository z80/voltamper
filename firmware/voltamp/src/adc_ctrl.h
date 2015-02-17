
#ifndef __ADC_CTRL_H_
#define __ADC_CTRL_H_

#include "ch.h"

void initAdc( void );



void setOscPeriod( uint32_t t );

void setFbSetpoint( int sp );
void setFbInput( int ind );
void setFbGain( int num, int den );
void setFbEn( int en );

InputQueue * eauxQueue( void );
InputQueue * erefQueue( void );
InputQueue * iauxQueue( void );


#endif



