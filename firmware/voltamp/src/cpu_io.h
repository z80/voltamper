
#ifndef __CPU_IO_H_
#define __CPU_IO_H_

#include "ch.h"

void cpu_io_init( void );
void cpu_io_process( void );

typedef void (* TFunc)( uint8_t * args );

uint8_t writeResult( uint8_t v );
void    writeEom( void );

#endif



