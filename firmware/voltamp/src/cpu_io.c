
#include "cpu_io.h"

#include "ch.h"
#include "hal.h"

#include "led_ctrl.h"
#include "adc_ctrl.h"
#include "dac.h"

#define BUFFER_SZ    32
#define ARGS_SZ      32
#define OUT_QUEUE_SZ 32

#define IO_DELAY_MS 1
#define SERIAL 		SD1

#define CMD_SET_ARGS  1
#define CMD_EXEC_FUNC 2

static uint8_t buffer[ BUFFER_SZ ];
static uint8_t args[ ARGS_SZ ];


static void process_command( uint8_t * buf, int sz );
static void writeResult( uint8_t v );
static void writeEom( void );


void cpu_io_init( void )
{
	// Initialize serial driver.
	sdStart( &SERIAL, 0 );
}

void cpu_io_process( void )
{
	while ( 1 )
	{
		uint8_t slash;
		int     out_index;
		out_index = 0;
		slash     = 0;

		// Try reading serial.
		msg_t msg;
		msg = sdGetTimeout( &SERIAL, TIME_IMMEDIATE );
		uint8_t noData = ( ( msg == Q_TIMEOUT ) || ( msg == Q_RESET ) ) ? 1 : 0;
		if ( !noData )
		{
			uint8_t v = (uint8_t)msg;
			//shift = serial_decode_byte( msg, &(buffer[out_index]), &eom );
			if ( !slash )
			{
				if ( v != '\\' )
					buffer[ out_index++ ] = v;
				else
					slash = 1;
			}
			else
			{
				slash = 0;
				if ( v == '\0' )
				{
					// Execute command
					process_command( buffer, out_index );
					out_index = 0;
				}
				else
					buffer[ out_index++ ] = v;
			}
			// Just in case of crazy command
			out_index = ( out_index < BUFFER_SZ ) ? out_index : BUFFER_SZ;
		}
	}
}

uint8_t * funcArgs( void )
{
	return args;
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

static void osc_eaux( uint8_t * args );
static void osc_eref( uint8_t * args );
static void osc_iaux( uint8_t * args );
static void set_leds( uint8_t * args );
static void set_dac( uint8_t * args );

static TFunc funcs[] =
{
	osc_eaux,
	osc_eref,
	osc_iaux,
	set_leds,
	set_dac
};

static void exec_func( void )
{
	int func_index = (int)buffer[1];// + ((int)buffer[2]) * 256;
	// Just to avoid troubles.
	int funcs_sz = (int)(sizeof(funcs)/sizeof(TFunc));
    func_index = (func_index < funcs_sz) ? func_index : 0;
	funcs[func_index]( args );
}

static void writeOscQueue( InputQueue * q )
{
	msg_t msg;
	uint8_t noData;
	size_t cnt, i;
	chSysLock();
		cnt = (chQSpaceI( q ) / 2) * 2;
	chSysUnlock();
	for ( i=0; i<cnt; i++ )
	{
		msg = chIQGetTimeout( q, TIME_IMMEDIATE );
		noData = ( ( msg == Q_TIMEOUT ) || ( msg == Q_RESET ) ) ? 1 : 0;
		uint8_t v;
		v = ( noData ) ? 0 : (uint8_t)msg;
		writeResult( v );
	}
	writeEom();
}

static void osc_eaux( uint8_t * args )
{
	(void)args;
	InputQueue * q = eauxQueue();
	writeOscQueue( q );
}

static void osc_eref( uint8_t * args )
{
	(void)args;
	InputQueue * q = erefQueue();
	writeOscQueue( q );
}

static void osc_iaux( uint8_t * args )
{
	(void)args;
	InputQueue * q = iauxQueue();
	writeOscQueue( q );
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






static void writeResult( uint8_t v )
{
	sdPut( &SERIAL, v );
	if ( v == '\\' )
		sdPut( &SERIAL, v );
}

static void writeEom( void )
{
	sdPut( &SERIAL, '\\' );
	sdPut( &SERIAL, '\0' );
}







