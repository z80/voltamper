
#include "cpu_io.h"
#include "serial_pipe.h"

#include "ch.h"
#include "hal.h"

#include "led_ctrl.h"
#include "dac.h"

#define BUFFER_SZ   32
#define ARGS_SZ     32
#define IO_DELAY_MS 1
#define SERIAL 		SD1

#define CMD_SET_ARGS  1
#define CMD_EXEC_FUNC 2

static uint8_t buffer_raw[ BUFFER_SZ ];
static uint8_t buffer[ BUFFER_SZ ];
static uint8_t args[ ARGS_SZ ];
static int     args_cnt; // This is for easy output to CPU.

static void process_command( uint8_t * buf, int sz );

void cpu_io_init( void )
{
	serial_pipe_init();
	// Initialize serial driver.
	sdStart( &SERIAL, 0 );
}

void cpu_io_process( void )
{
	while ( 1 )
	{
		// Try reading serial.
		int in_sz;
		in_sz = sdAsynchronousRead( &SERIAL, buffer_raw, BUFFER_SZ );
		if ( in_sz < 1 )
			chThdSleepMilliseconds( IO_DELAY_MS );
		else
		{
			uint8_t eom;
			uint8_t shift;
			int     out_index, i;
			out_index = 0;
			for ( i=0; i<in_sz; i++ )
			{
				shift = serial_decode_byte( buffer_raw[i], &(buffer[out_index]), &eom );
				out_index += shift;
				// Just in case of crazy command
				out_index = ( out_index < BUFFER_SZ ) ? out_index : BUFFER_SZ;
				if ( eom )
				{
					// if EOM process command.
				}
			}


		}
	}
}

static void write_args( void );
static void exec_func( void );

static void process_command( uint8_t * buf, int sz )
{
	int i;
	uint8_t cmd;
	cmd = buf[0];
	uint8_t * data = &(buf[1]);
	switch ( cmd )
	{
	case CMD_SET_ARGS:
		for ( i=0; i<(sz-1); i++ )
			args[i] = data[i];
		break;
	case CMD_EXEC_FUNC:
		// Execute function by it's index.
		exec_func();
		break;
	}
}

static void write_args( void )
{
	int i;
	for ( i=0; i<args_cnt; i++ )
	{
			sdPut( &SERIAL, args[i] );
			if ( args[i] == '\\' )
				sdPut( &SERIAL, args[i] );
			// To give USB ability to read.
			// chThdSleepMilliseconds( IO_DELAY_MS );
	}
	// End of message.
	sdPut( &SERIAL, '\\' );
	sdPut( &SERIAL, '\0' );
}

static void set_leds( uint8_t * args );
static void leds( uint8_t * args );
static void set_dac( uint8_t * args );
static void dac( uint8_t * args );

static TFunc funcs[] =
{
	set_leds,
	leds,
	set_dac,
	dac
};

static void exec_func( void )
{
	int func_index = (int)buffer[1] + ((int)buffer[2]) * 256;
	// Just to avoid troubles.
	int funcs_sz = (int)(sizeof(funcs)/sizeof(TFunc));
    func_index = (func_index < funcs_sz) ? func_index : 0;
	funcs[func_index]( args );
}

static void set_leds( uint8_t * args )
{
	setLeds( args[0] );
}

static void leds( uint8_t * args )
{

}

static void set_dac( uint8_t * args )
{
	DacCfg dacs;
	dacs.dac1 = 0;
	dacs.dac2 = 0;
	dacSet( &dacs );
}

static void dac( uint8_t * args )
{

}






