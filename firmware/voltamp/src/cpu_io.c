
#include "cpu_io.h"
#include "serial_pipe.h"

#include "ch.h"
#include "hal.h"

#include "led_ctrl.h"
#include "dac.h"

#define BUFFER_SZ    32
#define ARGS_SZ      32
#define OUT_QUEUE_SZ 32

#define IO_DELAY_MS 1
#define SERIAL 		SD1

#define CMD_SET_ARGS  1
#define CMD_EXEC_FUNC 2

static uint8_t buffer_raw[ BUFFER_SZ ];
static uint8_t buffer[ BUFFER_SZ ];
static uint8_t args[ ARGS_SZ ];
static int     args_cnt; // This is for easy output to CPU.


static void process_command( uint8_t * buf, int sz );
static void initOutput( void );

void cpu_io_init( void )
{
	serial_pipe_init();
	// Initialize serial driver.
	sdStart( &SERIAL, 0 );

	initOutput();
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
					// If EOM process command.
					process_command( buffer, out_index );
					// Start writing from the beginning.
					out_index = 0;
				}
			}


		}
	}
}

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

static void set_leds( uint8_t * args );
static void set_dac( uint8_t * args );

static TFunc funcs[] =
{
	set_leds,
	set_dac,
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

static void set_dac( uint8_t * args )
{
	DacCfg dacs;
	dacs.dac1 = (uint16_t)args[0] + ((uint16_t)args[1] << 8);
	dacs.dac2 = (uint16_t)args[2] + ((uint16_t)args[3] << 8);
	dacSet( &dacs );
}





// Output queue for writing out of MCU.
static InputQueue queue;
static uint8_t    queueBuffer[ OUT_QUEUE_SZ ];

uint8_t writeResult( uint8_t v )
{
	chIQPutI( &queue, v );
	if ( v == '\\' )
		chIQPutI( &queue, v );

	// If too little space left write "End Of Message" and return 1.
	size_t space = chIQGetEmptyI( &queue );
	if (space < 4)
	{
		writeEom();
		return 1;
	}
	// If space left is fine return 0.
	return 0;
}

void writeEom( void )
{
	chQPutI( &queue, '\\' );
	chQPutI( &queue, '\0' );
}

static WORKING_AREA( waOutput, 256 );
static msg_t outputThread( void *arg )
{
    (void)arg;
    chRegSetThreadName( "o" );
    // Continuous writing out of MCU.
    while ( 1 )
    {
    	uint8_t data_byte;
    	size_t cnt;
    	cnt = chIQReadTimeout( &queue, &data_byte, 1, TIME_INFINITE );
    	if ( cnt )
    		sdPut( &SERIAL, data_byte );
    }

    return 0;
}

static void initOutput( void )
{
	// Initializing input queue.
	chIQInit( &queue, queueBuffer, OUT_QUEUE_SZ, 0 );
	// Creating thread.
	chThdCreateStatic( waOutput, sizeof(waOutput), NORMALPRIO, outputThread, NULL );
}






