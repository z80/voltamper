
#ifndef __SERIAL_PIPE_H_
#define __SERIAL_PIPE_H_

int serial_decode( char * in_stri, int * in_sz, char * out_stri, int out_sz, char * eom );
int serial_encode( char * in_stri, int * in_sz, char * out_stri, int out_sz );

#endif





