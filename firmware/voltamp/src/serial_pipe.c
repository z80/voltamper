
#include "serial_pipe.h"

char slash = 0;

void serial_pipe_init( void )
{
	slash = 0;
}

uint8_t serial_decode_byte( uint8_t in, uint8_t * out, uint8_t * eom )
{
	if ( slash )
	{
		slash = 0;
		if ( in == '\0' )
		{
			*eom = 1;
			return 0;
		}
		else
		{
			*eom = 0;
			*out = in;
			return 1;
		}
	}
	else
	{
		if (in != '\\')
		{
			*out = in;
			*eom = 0;
			return 1;
		}
		else
		{
			slash = 1;
			*eom = 0;
			return 0;
		}
	}
}




