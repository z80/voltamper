
#ifndef __SERIAL_PIPE_H_
#define __SERIAL_PIPE_H_

#include "ch.h"

void serial_pipe_init( void );
uint8_t serial_decode_byte( uint8_t in, uint8_t * out, uint8_t * eom );

#endif





