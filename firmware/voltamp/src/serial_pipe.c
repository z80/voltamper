
#include "serial_pipe.h"

int serial_decode( char * in_stri, int * in_sz, char * out_stri, int out_sz, char * eom )
{
	int in_i;
	int out_i = 0;
	char slash = 0;
	for ( in_i=0; in_i<(*in_sz); in_i++ )
	{
		// There was '\' at previous position.
		if ( slash != 0 )
		{
			slash = 0;
			// Only \0 is procesed and it is supposed to be end of message.
			if ( in_stri[in_i] == '\0' )
			{
				*in_sz = in_i+1;
				*eom = 1;
				return out_i+1; // +1 to exclude current '\0' symbol.
			}
			else
			{
				out_stri[out_i++] = in_stri[in_i];
				if ( out_i >= out_sz )
				{
					*eom = 0;
					*in_sz = in_i+1;
					return out_i;
				}
			}
		}
		else
		{
			if ( in_stri[in_i] != '\\' )
			{
				out_stri[out_i++] = in_stri[in_i];
				if ( out_i >= out_sz )
				{
					*eom = 0;
					*in_sz = in_i+1;
					return out_i;
				}
			}
			else
				slash = 1;
		}
	}
	*eom = 0;
	return out_i;
}

int serial_encode( char * in_stri, int * in_sz, char * out_stri, int out_sz )
{
	int in_i;
	int out_i = 0;
	for ( in_i=0; in_i<(*in_sz); in_i++ )
	{
		out_stri[out_i++] = in_stri[in_i];
		if ( in_stri[in_i] == '\\' )
			out_stri[out_i++] = '\\';
	}
	out_stri[out_i++] = '\\';
	out_stri[out_i++] = '\0';
	return out_i;
}





