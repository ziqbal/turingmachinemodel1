/* Maker Config ino */

/* notes */



/* config */

/*
speedPin = A7 
ringPin = 7 
buttonTogglePin = 8 
buttonLeftPin = 11 
buttonRightPin = 9 
buttonRunStopPin = 10 
*/


/* macros */



/* header */

/***********************************************************************\
* turingmachine [Release tm1.2.ino] (C)2015 Zafar Iqbal < mail@zaf.io > *
* BUILD Sun, 13 Sep 2015 16:40:45 +0000                                 *
* This software is free for personal/educational use.                   *
* If you make/offer a hardware kit using this software,                 *
* please show your appreciation and make a donation by                  *
* sending the author a complimentary kit or                             *
* something from his amazon wish list.                                  *
* For commercial use of this software please contact                    *
* the author directly for licensing terms and conditions.               *
* http://zaf.io/                                                        *
\***********************************************************************/


/* vars */

int _vars_speedVal;
unsigned long _vars_frame = 0 ;
//unsigned int _vars_frameHeartbeatTrigger = 50000 ;
unsigned int _vars_frameHeartbeatTrigger = 10000 ;
void _vars_loop( ) {
	_vars_frame++ ;
	if( ( _vars_frame % _vars_frameHeartbeatTrigger ) == 0 ) {
      _serial_transmit( F( "#" ) , F( "H" ) ) ;  
	}    	
}


/* eeprom */

#include <EEPROM.h>
unsigned int _eeprom_init ;
byte _eeprom_ee1 , _eeprom_ee2 ; 
void _eeprom_setup( ) {
	_eeprom_ee1 = EEPROM.read( 0 ) ;
	_eeprom_ee2 = EEPROM.read( 1 ) ;
	_eeprom_ee2++ ;
	if( _eeprom_ee2 == 256 ) {
		_eeprom_ee2 = 0 ;
		_eeprom_ee1 ++ ;
		if( _eeprom_ee1 == 256 ) _eeprom_ee1 = 0 ;
	}
	EEPROM.write( 0 , _eeprom_ee1 ) ;
	EEPROM.write( 1 , _eeprom_ee2 ) ;
	_eeprom_init = ( _eeprom_ee1 << 8 ) + _eeprom_ee2 ;	
/* 
  EEPROM.write(0, 255);
  EEPROM.write(1, 255);
*/ 	
}


/* serial */

/* Macro Start ( _macroDisabled false ) */
boolean _serial_disabled = false ;
void _serial_broadcast_disable_serial_( ) {
	_serial_disabled = true ;
}
void _serial_broadcast_enable_serial_( ) {
	_serial_disabled = false ;
	_serial_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
byte _serial_inbyte ;
void _serial_broadcast_log( ) {
	_serial_transmit( "L" , "?" ) ;
}
unsigned int _serial_checksum ;
byte dataLen ;
void _serial_transmit( String key , String val ) {
  String data = key + F( "," ) + val
                + F( ",tm1,2," )
                + String( _eeprom_init , HEX )
                + F( "," ) + String( _vars_frame , HEX )
                + F( "," ) + String( millis( ) , HEX ) ;
  _serial_checksum = 0 ;
  dataLen = data.length( ) ;
  for( int i = 0 ; i < dataLen ; i ++ ) {
    _serial_checksum += data.charAt( i ) ;
  }
  _serial_checksum = _serial_checksum % 10 ;
  Serial.println( data + F( "," ) + _serial_checksum ) ;
}
void _serial_setup( ) {
	if( _serial_disabled ) return;
	Serial.begin( 9600 ) ;	
}
void _serial_wakeup( ) { }
void _serial_loop( ) {
/* Macro Start ( _macroTrigger 1000 ) */
if( _serial_disabled ) return ;
static unsigned int _serial_Trigger = 1000 ;	
static unsigned int _serial_Counter = 0 ;
if ( ++_serial_Counter < _serial_Trigger ) return ;
_serial_Counter = 0 ;
/* Macro Start ( _macroTrigger 1000 ) */
	//////
  if( Serial.available( ) > 0 ) {
    _serial_inbyte = Serial.read();
    //Serial.println( _serial_inbyte , DEC ) ;
    if( _serial_inbyte == 116 ) {
      _broadcast_( F("serial") ,  F( "stackeditrun" ) ) ;
    }
    if( _serial_inbyte == 112 ) {
      _broadcast_( F("serial") ,  F( "stackprog" ) ) ;
    }
  } 
}


/* broadcast */

/* Macro Start ( _macroDisabled false ) */
boolean _broadcast_disabled = false ;
void _broadcast_broadcast_disable_broadcast_( ) {
	_broadcast_disabled = true ;
}
void _broadcast_broadcast_enable_broadcast_( ) {
	_broadcast_disabled = false ;
	_broadcast_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
	byte _broadcast_queue1[ 60 ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
byte _broadcast_msgid1 ;
byte _broadcast_pointer1 = 0 ;
	byte _broadcast_queue2[ 60 ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ;
byte _broadcast_msgid2 ;
byte _broadcast_pointer2 = 0 ;
byte _broadcast_pointer3 = 0 ;
void _broadcast_( String module , String message ) {
	if( _broadcast_pointer1 == 60 ) {
		_serial_transmit( F( "$" ) , module + F( ">" ) + F( "pointer out" ) ) ;
		return ;
	}
	if( message == F( "_NOP_" ) ) {
		_broadcast_msgid1 = 0 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "_NOP_ message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_serial" ) ) {
		_broadcast_msgid1 = 1 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_serial message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_serial" ) ) {
		_broadcast_msgid1 = 2 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_serial message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "log" ) ) {
		_broadcast_msgid1 = 3 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "log message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_broadcast" ) ) {
		_broadcast_msgid1 = 4 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_broadcast message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_broadcast" ) ) {
		_broadcast_msgid1 = 5 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_broadcast message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_button" ) ) {
		_broadcast_msgid1 = 6 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_button message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_button" ) ) {
		_broadcast_msgid1 = 7 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_button message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_display" ) ) {
		_broadcast_msgid1 = 8 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_display message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_display" ) ) {
		_broadcast_msgid1 = 9 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_display message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_cursor" ) ) {
		_broadcast_msgid1 = 10 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_cursor message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_cursor" ) ) {
		_broadcast_msgid1 = 11 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_cursor message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_sfx" ) ) {
		_broadcast_msgid1 = 12 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_sfx message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_sfx" ) ) {
		_broadcast_msgid1 = 13 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_sfx message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "button" ) ) {
		_broadcast_msgid1 = 14 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "button message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "runclick" ) ) {
		_broadcast_msgid1 = 15 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "runclick message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "reset" ) ) {
		_broadcast_msgid1 = 16 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "reset message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "beep" ) ) {
		_broadcast_msgid1 = 17 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "beep message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stackSettings" ) ) {
		_broadcast_msgid1 = 18 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stackSettings message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stackSettings" ) ) {
		_broadcast_msgid1 = 19 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stackSettings message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stack" ) ) {
		_broadcast_msgid1 = 20 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stack message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stack" ) ) {
		_broadcast_msgid1 = 21 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stack message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "buttonTogglePin" ) ) {
		_broadcast_msgid1 = 22 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "buttonTogglePin message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		if( !_broadcast_alreadyInQueue( 14 ) ) { 
			_broadcast_queueAdd( 14 ) ;
			//_broadcast_queue1[ _broadcast_pointer1++ ] = 14 ;
		}
		return ;
	}
	if( message == F( "buttonRunStopPin" ) ) {
		_broadcast_msgid1 = 23 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "buttonRunStopPin message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		if( !_broadcast_alreadyInQueue( 14 ) ) { 
			_broadcast_queueAdd( 14 ) ;
			//_broadcast_queue1[ _broadcast_pointer1++ ] = 14 ;
		}
		return ;
	}
	if( message == F( "disable_stateSelectkey" ) ) {
		_broadcast_msgid1 = 24 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectkey message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectkey" ) ) {
		_broadcast_msgid1 = 25 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectkey message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_state" ) ) {
		_broadcast_msgid1 = 26 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_state message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_state" ) ) {
		_broadcast_msgid1 = 27 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_state message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "buttonLeftPin" ) ) {
		_broadcast_msgid1 = 28 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "buttonLeftPin message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		if( !_broadcast_alreadyInQueue( 14 ) ) { 
			_broadcast_queueAdd( 14 ) ;
			//_broadcast_queue1[ _broadcast_pointer1++ ] = 14 ;
		}
		return ;
	}
	if( message == F( "buttonRightPin" ) ) {
		_broadcast_msgid1 = 29 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "buttonRightPin message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		if( !_broadcast_alreadyInQueue( 14 ) ) { 
			_broadcast_queueAdd( 14 ) ;
			//_broadcast_queue1[ _broadcast_pointer1++ ] = 14 ;
		}
		return ;
	}
	if( message == F( "disable_stateSelectval" ) ) {
		_broadcast_msgid1 = 30 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectval message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectval" ) ) {
		_broadcast_msgid1 = 31 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectval message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stackEditrun" ) ) {
		_broadcast_msgid1 = 32 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stackEditrun message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stackEditrun" ) ) {
		_broadcast_msgid1 = 33 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stackEditrun message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateEdit" ) ) {
		_broadcast_msgid1 = 34 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateEdit message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateEdit" ) ) {
		_broadcast_msgid1 = 35 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateEdit message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateRun" ) ) {
		_broadcast_msgid1 = 36 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateRun message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateRun" ) ) {
		_broadcast_msgid1 = 37 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateRun message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "runResetLine" ) ) {
		_broadcast_msgid1 = 38 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "runResetLine message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stackProg" ) ) {
		_broadcast_msgid1 = 39 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stackProg message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stackProg" ) ) {
		_broadcast_msgid1 = 40 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stackProg message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateSelectline" ) ) {
		_broadcast_msgid1 = 41 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectline message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectline" ) ) {
		_broadcast_msgid1 = 42 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectline message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateSelectcurrentsymbol" ) ) {
		_broadcast_msgid1 = 43 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectcurrentsymbol message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectcurrentsymbol" ) ) {
		_broadcast_msgid1 = 44 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectcurrentsymbol message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateSelectnextsymbol" ) ) {
		_broadcast_msgid1 = 45 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectnextsymbol message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectnextsymbol" ) ) {
		_broadcast_msgid1 = 46 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectnextsymbol message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateSelectdir" ) ) {
		_broadcast_msgid1 = 47 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectdir message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectdir" ) ) {
		_broadcast_msgid1 = 48 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectdir message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_stateSelectjump" ) ) {
		_broadcast_msgid1 = 49 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_stateSelectjump message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_stateSelectjump" ) ) {
		_broadcast_msgid1 = 50 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_stateSelectjump message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_main" ) ) {
		_broadcast_msgid1 = 51 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_main message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_main" ) ) {
		_broadcast_msgid1 = 52 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_main message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "settingsupdated" ) ) {
		_broadcast_msgid1 = 53 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "settingsupdated message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "codeupdate" ) ) {
		_broadcast_msgid1 = 54 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "codeupdate message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "stackeditrun" ) ) {
		_broadcast_msgid1 = 55 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "stackeditrun message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "stackprog" ) ) {
		_broadcast_msgid1 = 56 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "stackprog message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "stacksettings" ) ) {
		_broadcast_msgid1 = 57 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "stacksettings message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "disable_blank" ) ) {
		_broadcast_msgid1 = 58 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "disable_blank message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
	if( message == F( "enable_blank" ) ) {
		_broadcast_msgid1 = 59 ;
		if( _broadcast_alreadyInQueue( _broadcast_msgid1 )){
			//_serial_transmit( F( "$" ) , module + F( ">" ) + F( "enable_blank message exists" ) ) ;
			return ;
		}		
		//_broadcast_queue1[ _broadcast_pointer1++ ] = _broadcast_msgid1 ;
		_broadcast_queueAdd( _broadcast_msgid1 ) ;
		return ;
	}
}
void _broadcast_queueAdd( byte v ) {
	// FIXEME TODO is disableFuncsTest required anymore?
	_broadcast_queue1[ _broadcast_pointer1++ ] = v ;
	// If its a disable function then put it at the beginning
	/*
	if(  v == 1  ||  v == 4  ||  v == 6  ||  v == 8  ||  v == 10  ||  v == 12  ||  v == 18  ||  v == 20  ||  v == 24  ||  v == 26  ||  v == 30  ||  v == 32  ||  v == 34  ||  v == 36  ||  v == 39  ||  v == 41  ||  v == 43  ||  v == 45  ||  v == 47  ||  v == 49  ||  v == 51  ||  v == 58  ) {
		// FIXME TODO will this break array size?
		_broadcast_pointer1++ ; 
		// use _broadcast_pointer2
		for( _broadcast_pointer2 = _broadcast_pointer1 ; _broadcast_pointer2!=0 ;_broadcast_pointer2-- ) {
			_broadcast_queue1[_broadcast_pointer2]=_broadcast_queue1[_broadcast_pointer2-1];
		}
		_broadcast_queue1[0]=v;		
		//_broadcast_pointer1++ ; 
		//_broadcast_queue1[ _broadcast_pointer1++ ] = v ;
	}else{
		_broadcast_queue1[ _broadcast_pointer1++ ] = v ;
	}
	*/
}
boolean _broadcast_alreadyInQueue( byte v ) {
	if( _broadcast_pointer1 == 0 ) return( false ) ;
	byte p = _broadcast_pointer1 ;
	do {
		if( _broadcast_queue1[ p - 1 ] == v ) return( true ) ;
		p-- ;
	} while( p != 0 ) ;	
	return( false ) ;
}
void _broadcast_sync( ) {
	_broadcast_pointer2 = 0 ;
	do {
		_broadcast_queue2[ _broadcast_pointer2 ] = _broadcast_queue1[ _broadcast_pointer2 ] ;
		_broadcast_pointer2++ ;
	} while( _broadcast_pointer2 != _broadcast_pointer1 ) ;
	_broadcast_pointer2-- ;
	_broadcast_pointer1 = 0 ;
}
void _broadcast_wakeup( ) { }
void _broadcast_loop( ) {
	// No trigger macro
/* Macro Start ( _macroTrigger 10 ) */
if( _broadcast_disabled ) return ;
static unsigned int _broadcast_Trigger = 10 ;	
static unsigned int _broadcast_Counter = 0 ;
if ( ++_broadcast_Counter < _broadcast_Trigger ) return ;
_broadcast_Counter = 0 ;
/* Macro Start ( _macroTrigger 10 ) */
	//////
	if( _broadcast_pointer1 == 0 ) return ;
	//_serial_transmit( F( "$" ) , F( "!!! BROADCAST !!!" ) ) ;	
	_broadcast_sync( ) ;
	_broadcast_pointer3 = 0 ;
	do {
		_broadcast_msgid2 = _broadcast_queue2[ _broadcast_pointer3 ] ;
		//_serial_transmit( F( "$" ) , String( _broadcast_pointer3 ) + F( " : " ) + String( _broadcast_msgid2 ) ) ;	
		if( _broadcast_msgid2 == 0) {
			delay( 1 ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 1) {
			_serial_broadcast_disable_serial_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 2) {
			_serial_broadcast_enable_serial_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 3) {
			_serial_broadcast_log( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 4) {
			_broadcast_broadcast_disable_broadcast_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 5) {
			_broadcast_broadcast_enable_broadcast_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 6) {
			_button_broadcast_disable_button_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 7) {
			_button_broadcast_enable_button_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 8) {
			_display_broadcast_disable_display_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 9) {
			_display_broadcast_enable_display_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 10) {
			_cursor_broadcast_disable_cursor_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 11) {
			_cursor_broadcast_enable_cursor_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 12) {
			_sfx_broadcast_disable_sfx_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 13) {
			_sfx_broadcast_enable_sfx_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 14) {
			_sfx_broadcast_button( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 15) {
			_sfx_broadcast_runclick( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 16) {
			_sfx_broadcast_reset( ) ; _stackSettings_broadcast_reset( ) ; _stateSelectkey_broadcast_reset( ) ; _stateSelectval_broadcast_reset( ) ; _stackEditrun_broadcast_reset( ) ; _stateEdit_broadcast_reset( ) ; _stateRun_broadcast_reset( ) ; _stackProg_broadcast_reset( ) ; _stateSelectline_broadcast_reset( ) ; _stateSelectcurrentsymbol_broadcast_reset( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 17) {
			_sfx_broadcast_beep( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 18) {
			_stackSettings_broadcast_disable_stackSettings_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 19) {
			_stackSettings_broadcast_enable_stackSettings_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 20) {
			_stackSettings_broadcast_disable_stackSettings_( ) ; _stackEditrun_broadcast_disable_stackEditrun_( ) ; _stackProg_broadcast_disable_stackProg_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 21) {
			_stackSettings_broadcast_enable_stackSettings_( ) ; _stackEditrun_broadcast_enable_stackEditrun_( ) ; _stackProg_broadcast_enable_stackProg_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 22) {
			_stackSettings_broadcast_buttonTogglePin( ) ; _stateSelectkey_broadcast_buttonTogglePin( ) ; _stateSelectval_broadcast_buttonTogglePin( ) ; _stateEdit_broadcast_buttonTogglePin( ) ; _stateRun_broadcast_buttonTogglePin( ) ; _stackProg_broadcast_buttonTogglePin( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 23) {
			_stackSettings_broadcast_buttonRunStopPin( ) ; _stackEditrun_broadcast_buttonRunStopPin( ) ; _stackProg_broadcast_buttonRunStopPin( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 24) {
			_stateSelectkey_broadcast_disable_stateSelectkey_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 25) {
			_stateSelectkey_broadcast_enable_stateSelectkey_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 26) {
			_stateSelectkey_broadcast_disable_stateSelectkey_( ) ; _stateSelectval_broadcast_disable_stateSelectval_( ) ; _stateEdit_broadcast_disable_stateEdit_( ) ; _stateRun_broadcast_disable_stateRun_( ) ; _stateSelectline_broadcast_disable_stateSelectline_( ) ; _stateSelectcurrentsymbol_broadcast_disable_stateSelectcurrentsymbol_( ) ; _stateSelectnextsymbol_broadcast_disable_stateSelectnextsymbol_( ) ; _stateSelectdir_broadcast_disable_stateSelectdir_( ) ; _stateSelectjump_broadcast_disable_stateSelectjump_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 27) {
			_stateSelectkey_broadcast_enable_stateSelectkey_( ) ; _stateSelectval_broadcast_enable_stateSelectval_( ) ; _stateEdit_broadcast_enable_stateEdit_( ) ; _stateRun_broadcast_enable_stateRun_( ) ; _stateSelectline_broadcast_enable_stateSelectline_( ) ; _stateSelectcurrentsymbol_broadcast_enable_stateSelectcurrentsymbol_( ) ; _stateSelectnextsymbol_broadcast_enable_stateSelectnextsymbol_( ) ; _stateSelectdir_broadcast_enable_stateSelectdir_( ) ; _stateSelectjump_broadcast_enable_stateSelectjump_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 28) {
			_stateSelectkey_broadcast_buttonLeftPin( ) ; _stateSelectval_broadcast_buttonLeftPin( ) ; _stateEdit_broadcast_buttonLeftPin( ) ; _stateSelectline_broadcast_buttonLeftPin( ) ; _stateSelectcurrentsymbol_broadcast_buttonLeftPin( ) ; _stateSelectnextsymbol_broadcast_buttonLeftPin( ) ; _stateSelectdir_broadcast_buttonLeftPin( ) ; _stateSelectjump_broadcast_buttonLeftPin( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 29) {
			_stateSelectkey_broadcast_buttonRightPin( ) ; _stateSelectval_broadcast_buttonRightPin( ) ; _stateEdit_broadcast_buttonRightPin( ) ; _stateSelectline_broadcast_buttonRightPin( ) ; _stateSelectcurrentsymbol_broadcast_buttonRightPin( ) ; _stateSelectnextsymbol_broadcast_buttonRightPin( ) ; _stateSelectdir_broadcast_buttonRightPin( ) ; _stateSelectjump_broadcast_buttonRightPin( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 30) {
			_stateSelectval_broadcast_disable_stateSelectval_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 31) {
			_stateSelectval_broadcast_enable_stateSelectval_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 32) {
			_stackEditrun_broadcast_disable_stackEditrun_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 33) {
			_stackEditrun_broadcast_enable_stackEditrun_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 34) {
			_stateEdit_broadcast_disable_stateEdit_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 35) {
			_stateEdit_broadcast_enable_stateEdit_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 36) {
			_stateRun_broadcast_disable_stateRun_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 37) {
			_stateRun_broadcast_enable_stateRun_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 38) {
			_stateRun_broadcast_runResetLine( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 39) {
			_stackProg_broadcast_disable_stackProg_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 40) {
			_stackProg_broadcast_enable_stackProg_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 41) {
			_stateSelectline_broadcast_disable_stateSelectline_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 42) {
			_stateSelectline_broadcast_enable_stateSelectline_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 43) {
			_stateSelectcurrentsymbol_broadcast_disable_stateSelectcurrentsymbol_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 44) {
			_stateSelectcurrentsymbol_broadcast_enable_stateSelectcurrentsymbol_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 45) {
			_stateSelectnextsymbol_broadcast_disable_stateSelectnextsymbol_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 46) {
			_stateSelectnextsymbol_broadcast_enable_stateSelectnextsymbol_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 47) {
			_stateSelectdir_broadcast_disable_stateSelectdir_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 48) {
			_stateSelectdir_broadcast_enable_stateSelectdir_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 49) {
			_stateSelectjump_broadcast_disable_stateSelectjump_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 50) {
			_stateSelectjump_broadcast_enable_stateSelectjump_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 51) {
			_main_broadcast_disable_main_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 52) {
			_main_broadcast_enable_main_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 53) {
			_main_broadcast_settingsupdated( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 54) {
			_main_broadcast_codeupdate( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 55) {
			_main_broadcast_stackeditrun( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 56) {
			_main_broadcast_stackprog( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 57) {
			_main_broadcast_stacksettings( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 58) {
			_blank_broadcast_disable_blank_( ) ;
			continue;	
		}
		if( _broadcast_msgid2 == 59) {
			_blank_broadcast_enable_blank_( ) ;
			continue;	
		}
	} while( ( _broadcast_pointer3++ ) != _broadcast_pointer2 ) ;
}


/* button */

// Setup and configure all buttons
// When button is pressed send a broadcast message
// Keep track of last button state to disable repeat broadcasts
/* Macro Start ( _macroDisabled false ) */
boolean _button_disabled = false ;
void _button_broadcast_disable_button_( ) {
	_button_disabled = true ;
}
void _button_broadcast_enable_button_( ) {
	_button_disabled = false ;
	_button_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
/* Macro Start ( _macroLog */
void _button_log( String msg ) {
	_serial_transmit( F( "_button_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
boolean _button_lastbuttonTogglePin = HIGH ;
unsigned int _button_tickbuttonTogglePin = 0 ;
boolean _button_lastbuttonLeftPin = HIGH ;
unsigned int _button_tickbuttonLeftPin = 0 ;
boolean _button_lastbuttonRightPin = HIGH ;
unsigned int _button_tickbuttonRightPin = 0 ;
boolean _button_lastbuttonRunStopPin = HIGH ;
unsigned int _button_tickbuttonRunStopPin = 0 ;
void _button_setup( ) {
		pinMode( 8 , INPUT_PULLUP ) ;
		pinMode( 11 , INPUT_PULLUP ) ;
		pinMode( 9 , INPUT_PULLUP ) ;
		pinMode( 10 , INPUT_PULLUP ) ;
}
void _button_wakeup( ) { }
void _button_loop( ) {
/* Macro Start ( _macroTrigger 10 ) */
if( _button_disabled ) return ;
static unsigned int _button_Trigger = 10 ;	
static unsigned int _button_Counter = 0 ;
if ( ++_button_Counter < _button_Trigger ) return ;
_button_Counter = 0 ;
/* Macro Start ( _macroTrigger 10 ) */
	if( digitalRead( 8 ) == LOW ) {
		if( _button_lastbuttonTogglePin == HIGH ) _broadcast_( F("button") ,  F( "buttonTogglePin" ) ) ;
		_button_lastbuttonTogglePin= LOW ;
		if( _button_tickbuttonTogglePin < 200 ) {
			//_button_log("t"+String(_button_tickbuttonTogglePin));
			_button_tickbuttonTogglePin++  ;
		}
	} else {
		_button_lastbuttonTogglePin= HIGH ;
		_button_tickbuttonTogglePin = 0 ;		
	}		
	if( digitalRead( 11 ) == LOW ) {
		if( _button_lastbuttonLeftPin == HIGH ) _broadcast_( F("button") ,  F( "buttonLeftPin" ) ) ;
		_button_lastbuttonLeftPin= LOW ;
		if( _button_tickbuttonLeftPin < 200 ) {
			//_button_log("t"+String(_button_tickbuttonLeftPin));
			_button_tickbuttonLeftPin++  ;
		}
	} else {
		_button_lastbuttonLeftPin= HIGH ;
		_button_tickbuttonLeftPin = 0 ;		
	}		
	if( digitalRead( 9 ) == LOW ) {
		if( _button_lastbuttonRightPin == HIGH ) _broadcast_( F("button") ,  F( "buttonRightPin" ) ) ;
		_button_lastbuttonRightPin= LOW ;
		if( _button_tickbuttonRightPin < 200 ) {
			//_button_log("t"+String(_button_tickbuttonRightPin));
			_button_tickbuttonRightPin++  ;
		}
	} else {
		_button_lastbuttonRightPin= HIGH ;
		_button_tickbuttonRightPin = 0 ;		
	}		
	if( digitalRead( 10 ) == LOW ) {
		if( _button_lastbuttonRunStopPin == HIGH ) _broadcast_( F("button") ,  F( "buttonRunStopPin" ) ) ;
		_button_lastbuttonRunStopPin= LOW ;
		if( _button_tickbuttonRunStopPin < 200 ) {
			//_button_log("t"+String(_button_tickbuttonRunStopPin));
			_button_tickbuttonRunStopPin++  ;
		}
	} else {
		_button_lastbuttonRunStopPin= HIGH ;
		_button_tickbuttonRunStopPin = 0 ;		
	}		
}


/* display */

/* Macro Start ( _macroDisabled false ) */
boolean _display_disabled = false ;
void _display_broadcast_disable_display_( ) {
	_display_disabled = true ;
}
void _display_broadcast_enable_display_( ) {
	_display_disabled = false ;
	_display_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
/* Macro Start ( _macroLog */
void _display_log( String msg ) {
	_serial_transmit( F( "_display_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
#include <Adafruit_NeoPixel.h>
#define _display_PIXEL_PIN    7
#define _display_PIXEL_COUNT	24
Adafruit_NeoPixel _display_strip = Adafruit_NeoPixel( 24 , _display_PIXEL_PIN , NEO_GRB + NEO_KHZ800 ) ;
boolean _display_toggle = false ;
uint32_t _display_colours[ 8 ] = {
	_display_strip.Color( 0 , 0 , 0 ) ,
	_display_strip.Color( 255 , 255 , 255 ) ,
	_display_strip.Color( 255 , 0 , 0 ) ,
	_display_strip.Color( 0 , 255 , 0 ) ,
	_display_strip.Color( 0 , 0 , 255 ) ,
	_display_strip.Color( 0 , 255 , 255 ) ,
	_display_strip.Color( 255 , 0 , 255 ) ,
	//_display_strip.Color( 255 , 255 , 0 ) 
	_display_strip.Color( 255 , 255 , 0 ) 
} ;
/*
uint32_t _display_colours[ 8 ] = {
	_display_strip.Color( 0 , 0 , 0 ) ,
	_display_strip.Color( 0 , 0 , 255 ) ,
	_display_strip.Color( 0 , 255 , 255 ) ,
	_display_strip.Color( 0 , 255 , 0 ) ,
	_display_strip.Color( 255 , 255 , 0 ) ,
	_display_strip.Color( 255 , 255 , 255 ) ,
	_display_strip.Color( 255 , 0 , 255 ) ,
	_display_strip.Color( 255 , 0 , 0 ) 
} ;
*/
uint32_t _display_col( byte r , byte g , byte b ) {
	return(_display_strip.Color( r,g,b ) );
}
void _display_setup( ) {
	_display_strip.begin( ) ;
	_display_strip.setBrightness( 8 ) ;
	_display_strip.show( ) ;
	_display_debug( ) ;
}
void _display_wakeup( ) { }
void _display_loop( ) {
/* Macro Start ( _macroTrigger 300 ) */
if( _display_disabled ) return ;
static unsigned int _display_Trigger = 300 ;	
static unsigned int _display_Counter = 0 ;
if ( ++_display_Counter < _display_Trigger ) return ;
_display_Counter = 0 ;
/* Macro Start ( _macroTrigger 300 ) */
	//////
	_display_toggle = !_display_toggle ;
}
void _display_show( ) {
	_display_strip.show( ) ;
}
void _display_clear( ) {
	for( byte i = 0 ; i<24;i++){
		_display_setpixel( i , 0 ) ;
	}
}
void _display_pattern1( ) {
	for( byte i = 0 ; i<24;i++){
		_display_setpixel( i , 7 ) ;
	}
}
void _display_pattern2( ) {
	for( byte i = 0 ; i<24;i++){
		if(i==6 || i==(18)){
		_display_setpixel( i , 0 ) ;
		}else{
		_display_setpixel( i , 7 ) ;
		}
	}
}
void _display_currentsymbols( ){
	for( byte i = 0 ; i < 5;i++){
		int y = ( i * 1 ) - 2 ;
		_display_setpixel( y , i ) ;
	}
}
void _display_selectallcurrentsymbols( byte col ){
	for( byte i = 0 ; i < 5 ; i++ ) {
		int y = ( i * 1 ) - 2 ;
		_display_setpixel( y , col ) ;
	}
}
void _display_nextsymbols( ){
	for( byte i = 0 ; i < 5 ; i++ ) {
		int y = ( i * -1 ) + 14 ;
		_display_setpixel( y , i ) ;
	}
}
void _display_selectallnextsymbols( byte col ) {
	for( byte i = 0 ; i < 5 ; i++ ) {
		int y = ( i * -1 ) + 14 ;
		_display_setpixel( y , col ) ;
	}
}
void _display_setpixel( int x , byte c ) {
	int y = (22 + x)%24;
	_display_strip.setPixelColor( y , _display_colours[ c ] ) ;
}
void _display_togglepixel( int x , byte c ) {
	if(_display_toggle) return;
	int y = (22 + x)%24;
	_display_strip.setPixelColor( y , _display_colours[ c ] ) ;
}
void _display_debug( ) {
	for( byte j = 0 ; j< 5 ; j++ ) {
		for( byte i = 0 ; i< 24 ; i++ ) {
			_display_setpixel( i , j ) ;
			_display_strip.show( ) ;
			delay(5);
		}
	}
}


/* cursor */

/* Macro Start ( _macroDisabled false ) */
boolean _cursor_disabled = false ;
void _cursor_broadcast_disable_cursor_( ) {
	_cursor_disabled = true ;
}
void _cursor_broadcast_enable_cursor_( ) {
	_cursor_disabled = false ;
	_cursor_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
/* Macro Start ( _macroLog */
void _cursor_log( String msg ) {
	_serial_transmit( F( "_cursor_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
boolean _cursor_toggle = false ;
byte _cursor_toggleRate = 4 ;
byte _cursor_toggleCurrent = 1 ;
byte _cursor_col = 0 ;	
void _cursor_highlight( ) {
	_cursor_toggleCurrent = 2  ;
	_cursor_toggle = true;
}
void _cursor_dehighlight( ) {
	_cursor_toggleCurrent = 2 ;
	_cursor_toggle = false ;
}
void _cursor_draw( byte i ) {
	if( _cursor_toggle ) {
		_display_setpixel( i ,  _cursor_col ) ;
	}	
}
void _cursor_setup( ) {
}
void _cursor_wakeup( ) { }
void _cursor_loop( ) {
/* Macro Start ( _macroTrigger 300 ) */
if( _cursor_disabled ) return ;
static unsigned int _cursor_Trigger = 300 ;	
static unsigned int _cursor_Counter = 0 ;
if ( ++_cursor_Counter < _cursor_Trigger ) return ;
_cursor_Counter = 0 ;
/* Macro Start ( _macroTrigger 300 ) */
	//////
	if( _cursor_toggleCurrent-- == 0 ) {
		_cursor_toggleCurrent = _cursor_toggleRate ;
		_cursor_toggle = !_cursor_toggle ;
	}
	_cursor_col++ ;
	if( _cursor_col == 5 ) _cursor_col++ ;				
	if( _cursor_col == 7 ) _cursor_col++ ;				
	if( _cursor_col == 8 ) _cursor_col = 1 ;				
}


/* sfx */

/* Macro Start ( _macroDisabled false ) */
boolean _sfx_disabled = false ;
void _sfx_broadcast_disable_sfx_( ) {
	_sfx_disabled = true ;
}
void _sfx_broadcast_enable_sfx_( ) {
	_sfx_disabled = false ;
	_sfx_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
/* Macro Start ( _macroLog */
void _sfx_log( String msg ) {
	_serial_transmit( F( "_sfx_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
int _sfx_pin = 12;
void _sfx_broadcast_button( ){
	_sfx_play( 700 , 1 ) ;
}
void _sfx_broadcast_runclick( ){
	_sfx_play( 1100 , 1 ) ;
}
void _sfx_broadcast_reset( ){
	_sfx_play( 2000 , 500 ) ;
}
void _sfx_broadcast_beep( ){
	_sfx_play( 2000 , 500 ) ;
}
void _sfx_play( int freq , int duration ) {
	if( _sfx_disabled ) return ;
	tone( _sfx_pin , freq , duration ) ;
}
void _sfx_setup( ) {
	_sfx_play( 1000 , 500 ) ;
}
void _sfx_wakeup( ) { }
void _sfx_loop( ) {
/* Macro Start ( _macroTrigger 10 ) */
if( _sfx_disabled ) return ;
static unsigned int _sfx_Trigger = 10 ;	
static unsigned int _sfx_Counter = 0 ;
if ( ++_sfx_Counter < _sfx_Trigger ) return ;
_sfx_Counter = 0 ;
/* Macro Start ( _macroTrigger 10 ) */
	//////
}


/* stackSettings */

/* Macro Start ( _macroDisabled true ) */
boolean _stackSettings_disabled = true ;
void _stackSettings_broadcast_disable_stackSettings_( ) {
	_stackSettings_disabled = true ;
}
void _stackSettings_broadcast_enable_stackSettings_( ) {
	_stackSettings_disabled = false ;
	_stackSettings_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stackSettings_log( String msg ) {
	_serial_transmit( F( "_stackSettings_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stackSettings_state = 0 ; 
byte _stackSettings_stateLast = 255 ; 
void _stackSettings_broadcast_buttonTogglePin( ) {
	if( _stackSettings_disabled ) return ;
	_broadcast_( F("stackSettings") ,  F( "disable_state" ) ) ;
	_stackSettings_state++ ;
	if( _stackSettings_state == 2 ) {
		_stackSettings_state = 0 ;
		_broadcast_( F("stackSettings") ,  F( "settingsupdated" ) ) ;
		_broadcast_( F("stackSettings") ,  F( "beep" ) ) ;
	}
}
void _stackSettings_broadcast_buttonRunStopPin( ) {
	if( _stackSettings_disabled ) return ;
	if( _stackSettings_state == 0 ) return ;
	_broadcast_( F("stackSettings") ,  F( "disable_state" ) ) ;
	_stackSettings_state-- ;
}
void _stackSettings_broadcast_reset( ) {
	_broadcast_( F("stackSettings") ,  F( "disable_state" ) ) ;
	_stackSettings_state=0 ;	
	_stackSettings_stateLast = 255 ; 	
}
void _stackSettings_setup( ) {
	if( _stackSettings_disabled ) return ;
}
void _stackSettings_wakeup( ) { }
void _stackSettings_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stackSettings_disabled ) return ;
static unsigned int _stackSettings_Trigger = 100 ;	
static unsigned int _stackSettings_Counter = 0 ;
if ( ++_stackSettings_Counter < _stackSettings_Trigger ) return ;
_stackSettings_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	//_stackSettings_log( String(_stackSettings_state) ) ;
	if( _stackSettings_state != _stackSettings_stateLast ) {
		//_broadcast_( F("stackSettings") ,  F( "disable_state" ) ) ;
		_stackSettings_log( String(_stackSettings_state) ) ;
		if( _stackSettings_state == 0 ) {
			_broadcast_( F("stackSettings") ,  F( "enable_stateSelectkey" ) ) ;
		}
		if( _stackSettings_state == 1 ) {
			_broadcast_( F("stackSettings") ,  F( "enable_stateSelectval" ) ) ;
		}
		_stackSettings_stateLast = _stackSettings_state ;
	}
}


/* stateSelectkey */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectkey_disabled = true ;
void _stateSelectkey_broadcast_disable_stateSelectkey_( ) {
	_stateSelectkey_disabled = true ;
}
void _stateSelectkey_broadcast_enable_stateSelectkey_( ) {
	_stateSelectkey_disabled = false ;
	_stateSelectkey_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectkey_log( String msg ) {
	_serial_transmit( F( "_stateSelectkey_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectkey_cursor = 0 ;
void _stateSelectkey_broadcast_reset( ) {
	_stateSelectkey_cursor = 0 ;
}
void _stateSelectkey_broadcast_buttonLeftPin( ) {
	if( _stateSelectkey_disabled ) return ;
	if( _stateSelectkey_cursor == 0 ) {
		_stateSelectkey_cursor = 23 ;
	} else {
		_stateSelectkey_cursor-=1 ;
	}
	_cursor_highlight( );
}
void _stateSelectkey_broadcast_buttonRightPin( ) {
	if( _stateSelectkey_disabled ) return;
	if( _stateSelectkey_cursor == 23 ) {
		_stateSelectkey_cursor = 0 ;
	} else {
		_stateSelectkey_cursor++ ;
	}
	_cursor_highlight( );
}
void _stateSelectkey_broadcast_buttonTogglePin( ) {
	if( _stateSelectkey_disabled ) return;
	_cursor_dehighlight( );
}
void _stateSelectkey_setup( ) {
}
void _stateSelectkey_wakeup( ) { }
void _stateSelectkey_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectkey_disabled ) return ;
static unsigned int _stateSelectkey_Trigger = 100 ;	
static unsigned int _stateSelectkey_Counter = 0 ;
if ( ++_stateSelectkey_Counter < _stateSelectkey_Trigger ) return ;
_stateSelectkey_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern1( ) ;
	_cursor_draw( _stateSelectkey_cursor ) ;
	_display_show();
}


/* stateSelectval */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectval_disabled = true ;
void _stateSelectval_broadcast_disable_stateSelectval_( ) {
	_stateSelectval_disabled = true ;
}
void _stateSelectval_broadcast_enable_stateSelectval_( ) {
	_stateSelectval_disabled = false ;
	_stateSelectval_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectval_log( String msg ) {
	_serial_transmit( F( "_stateSelectval_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectval_cursor = 0 ;
void _stateSelectval_broadcast_reset( ) {
	_stateSelectval_cursor = 0 ;
}
void _stateSelectval_broadcast_buttonLeftPin( ) {
	if( _stateSelectval_disabled ) return ;
	if( _stateSelectval_cursor == 0 ) {
		_stateSelectval_cursor = 23 ;
	} else {
		_stateSelectval_cursor-=1 ;
	}
	_cursor_highlight( );
}
void _stateSelectval_broadcast_buttonRightPin( ) {
	if( _stateSelectval_disabled ) return;
	if( _stateSelectval_cursor == 23 ) {
		_stateSelectval_cursor = 0 ;
	} else {
		_stateSelectval_cursor++ ;
	}
	_cursor_highlight( );
}
void _stateSelectval_broadcast_buttonTogglePin( ) {
	if( _stateSelectval_disabled ) return;
	_cursor_dehighlight( );
}
void _stateSelectval_setup( ) {
}
void _stateSelectval_wakeup( ) { }
void _stateSelectval_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectval_disabled ) return ;
static unsigned int _stateSelectval_Trigger = 100 ;	
static unsigned int _stateSelectval_Counter = 0 ;
if ( ++_stateSelectval_Counter < _stateSelectval_Trigger ) return ;
_stateSelectval_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern1( ) ;
	for(int i = 0 ; i < 24 ; i++ ) {
		if(_stateRun_stateused(i)){
			_display_setpixel( i ,  5 ) ;
		}
	}
	if( _cursor_toggle ) {
		_display_setpixel( _stateSelectval_cursor ,  _cursor_col  ) ;
	} else {
		//_display_setpixel( _stateSelectval_cursor ,  7  ) ;
	}	
	_display_show();
}


/* stackEditrun */

/* Macro Start ( _macroDisabled true ) */
boolean _stackEditrun_disabled = true ;
void _stackEditrun_broadcast_disable_stackEditrun_( ) {
	_stackEditrun_disabled = true ;
}
void _stackEditrun_broadcast_enable_stackEditrun_( ) {
	_stackEditrun_disabled = false ;
	_stackEditrun_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stackEditrun_log( String msg ) {
	_serial_transmit( F( "_stackEditrun_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stackEditrun_state = 0 ; 
byte _stackEditrun_stateLast = 255 ; 
void _stackEditrun_broadcast_buttonRunStopPin( ) {
	if( _stackEditrun_disabled ) return ;
	_broadcast_( F("stackEditrun") ,  F( "disable_state" ) ) ;
	_stackEditrun_state++ ;
	if( _stackEditrun_state == 2 ) _stackEditrun_state = 0 ;
}
void _stackEditrun_broadcast_reset( ) {
	_broadcast_( F("stackEditrun") ,  F( "disable_state" ) ) ;
	_stackEditrun_state=0 ;	
	_stackEditrun_stateLast = 255 ; 
}
void _stackEditrun_setup( ) {
	if( _stackEditrun_disabled ) return ;
}
void _stackEditrun_wakeup( ) {
}
void _stackEditrun_loop( ) {
	//////
	//_stackEditrun_log( String(_stackEditrun_state) ) ;
	if( _stackEditrun_state != _stackEditrun_stateLast ) {
		//_broadcast_( F("stackEditrun") ,  F( "disable_state" ) ) ;
		// _stackEditrun_log( String(_stackEditrun_state) ) ;
		if( _stackEditrun_state == 0 ) {
			_broadcast_( F("stackEditrun") ,  F( "enable_stateEdit" ) ) ;
		}
		if( _stackEditrun_state == 1 ) {
			_broadcast_( F("stackEditrun") ,  F( "enable_stateRun" ) ) ;
		}
		_stackEditrun_stateLast = _stackEditrun_state ;
	}
}


/* stateEdit */

/* Macro Start ( _macroDisabled true ) */
boolean _stateEdit_disabled = true ;
void _stateEdit_broadcast_disable_stateEdit_( ) {
	_stateEdit_disabled = true ;
}
void _stateEdit_broadcast_enable_stateEdit_( ) {
	_stateEdit_disabled = false ;
	_stateEdit_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateEdit_log( String msg ) {
	_serial_transmit( F( "_stateEdit_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateEdit_cursor = 0 ;
byte _stateEdit_tape [ 24 ] ;
boolean _stateEdit_tapeupdated = true ;
void _stateEdit_drawtape( ) {
	if(!_stateEdit_tapeupdated) return;
	for( byte i = 0 ; i<24;i++ ) {
		_display_setpixel(i,_stateEdit_tapeget(i));
	}
	_stateEdit_tapeupdated = false;
}
// Init strip to zeros
void _stateEdit_tapeclear( ) {
  for ( byte i = 0 ; i < 24 ; i++ ) {
	//_stateEdit_tapeset( i , random( 0 , 2 ) ) ;    
	_stateEdit_tapeset( i , 0 ) ;
  }
}
void _stateEdit_broadcast_reset( ) {
	_stateEdit_tapeclear( ) ;
	_stateEdit_cursor = 0 ;
}
// Get data at specific position
byte _stateEdit_tapeget( byte p ) {
	return ( _stateEdit_tape[ p ] ) ;
}
// Set strip data at specific point
void _stateEdit_tapeset( byte p , byte s ) {
	if( _stateEdit_tape[ p ] == s ) return;
	_stateEdit_tape[ p ] = s ;
	_stateEdit_tapeupdated = true ;
}
void _stateEdit_broadcast_buttonLeftPin( ) {
	//return;
	if( _stateEdit_disabled ) return;
	//_stateEdit_log("HEY???");
	if( _stateEdit_cursor == 0 ){
		_stateEdit_cursor = 23 ;
	}else{
		_stateEdit_cursor--;
	}
	_cursor_highlight( );
	_stateEdit_tapeupdated = true;
	_broadcast_( F("stateEdit") ,  F( "runResetLine" ) ) ;
}
void _stateEdit_broadcast_buttonRightPin( ) {
	if( _stateEdit_disabled ) return;
	if( _stateEdit_cursor == 23 ) {
		_stateEdit_cursor = 0 ;
	} else {
		_stateEdit_cursor++;
	}
	_cursor_highlight( );
	_stateEdit_tapeupdated = true;
	_broadcast_( F("stateEdit") ,  F( "runResetLine" ) ) ;
}
void _stateEdit_broadcast_buttonTogglePin( ) {
	if( _stateEdit_disabled ) return;
	byte x = _stateEdit_tapeget(_stateEdit_cursor) + 1 ;
	if(x==5) x = 0 ;
	_stateEdit_tapeset(_stateEdit_cursor,x);
	_cursor_dehighlight( );
	_stateEdit_tapeupdated = true;
	_broadcast_( F("stateEdit") ,  F( "runResetLine" ) ) ;
}
void _stateEdit_setup( ) {
	_stateEdit_tapeclear( ) ;
}
void _stateEdit_wakeup( ) { 
	_stateEdit_tapeupdated=true;
}
void _stateEdit_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateEdit_disabled ) return ;
static unsigned int _stateEdit_Trigger = 100 ;	
static unsigned int _stateEdit_Counter = 0 ;
if ( ++_stateEdit_Counter < _stateEdit_Trigger ) return ;
_stateEdit_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_stateEdit_drawtape( ) ;
	if( _cursor_toggle ) {
		_display_setpixel( _stateEdit_cursor , _cursor_col ) ;
	} else {
		_display_setpixel( _stateEdit_cursor , _stateEdit_tapeget( _stateEdit_cursor ) ) ;
	}
	_display_show( ) ;
}


/* stateRun */

/* Macro Start ( _macroDisabled true ) */
boolean _stateRun_disabled = true ;
void _stateRun_broadcast_disable_stateRun_( ) {
	_stateRun_disabled = true ;
}
void _stateRun_broadcast_enable_stateRun_( ) {
	_stateRun_disabled = false ;
	_stateRun_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateRun_log( String msg ) {
	_serial_transmit( F( "_stateRun_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
//char _stateRun_instructions[ 61 ] = "000111011100000000000000000000000000000000000000000000000000" ;
//char _stateRun_instructions[ 721 ] = "100111011100000000000000000000000000000000000000000000000000" ;
char _stateRun_instructions[ 362 ] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//Chomper
//char _stateRun_instructions[ 721 ] = "00~0~101~0~0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//char _stateRun_instructions[ 721 ] = "00~0~101~0~0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//char _stateRun_instructions[ 541 ] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
// Code position
int _stateRun_line = 0 ;
int _stateRun_pointer = 0 ;
boolean _stateRun_flagToggle  = false ;
/*
void _stateRun_setall( byte line , byte symbol , byte dir , byte jump ) {
	int pointer = line * 15 ;
// FIXME TODO simplify!
	if( symbol == 14 ) symbol = '0' ;
	if( symbol == 13 ) symbol = '1' ;
	if( symbol == 12 ) symbol = '2' ;
	if( symbol == 11 ) symbol = '3' ;
	if( symbol == 10 ) symbol = '4' ;	
	if( dir == 18 ) dir = '0' ;
	if( dir == 255 ) dir = '~' ;
	if( dir == 6 ) dir = '1' ;
	jump += 48 ;
	_stateRun_instructions[ pointer ] = symbol ;
	_stateRun_instructions[ pointer + 1 ] = dir ; 
	_stateRun_instructions[ pointer + 2 ] = jump ;
	_stateRun_instructions[ 3 + pointer ] = symbol ;
	_stateRun_instructions[ 3 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 3 + pointer + 2 ] = jump ;
	_stateRun_instructions[ 6 + pointer ] = symbol ;
	_stateRun_instructions[ 6 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 6 + pointer + 2 ] = jump ;
	_stateRun_instructions[ 9 + pointer ] = symbol ;
	_stateRun_instructions[ 9 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 9 + pointer + 2 ] = jump ;
	_stateRun_instructions[ 12 + pointer ] = symbol ;
	_stateRun_instructions[ 12 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 12 + pointer + 2 ] = jump ;
	_stateRun_line = 0 ;	
}
*/
void _stateRun_setallandnextsymbol( byte line , byte dir , byte jump ) {
	int pointer = line * 15 ;
	if( dir == 18 ) dir = '0' ;
	if( dir == 255 ) dir = '~' ;
	if( dir == 6 ) dir = '1' ;
	jump += 48 ;
	_stateRun_instructions[ pointer ] = '0' ;
	_stateRun_instructions[ pointer + 1 ] = dir ; 
	_stateRun_instructions[ pointer + 2 ] = jump ;
	_stateRun_instructions[ 3 + pointer ] = '1' ;
	_stateRun_instructions[ 3 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 3 + pointer + 2 ] = jump ;
	_stateRun_instructions[ 6 + pointer ] = '2' ;
	_stateRun_instructions[ 6 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 6 + pointer + 2 ] = jump ;
	_stateRun_instructions[ 9 + pointer ] = '3' ;
	_stateRun_instructions[ 9 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 9 + pointer + 2 ] = jump ;
	_stateRun_instructions[ 12 + pointer ] = '4' ;
	_stateRun_instructions[ 12 + pointer + 1 ] = dir ; 
	_stateRun_instructions[ 12 + pointer + 2 ] = jump ;
	_stateRun_line = 0 ;	
}
void _stateRun_setcurrentandnotnextsymbol( byte line , byte symbol , byte dir , byte jump ) {
	int pointer = line * 15 ;
// FIXME TODO simplify!
	if( symbol == 14 ) symbol = '0' ;
	if( symbol == 13 ) symbol = '1' ;
	if( symbol == 12 ) symbol = '2' ;
	if( symbol == 11 ) symbol = '3' ;
	if( symbol == 10 ) symbol = '4' ;	
	if( dir == 18 ) dir = '0' ;
	if( dir == 255 ) dir = '~' ;
	if( dir == 6 ) dir = '1' ;
	//jump += 48 ;
	byte jumpthisline = line + 48 ;
	byte jumpnext = jump + 48 ;
	byte jumpwhat ;
	byte dirthisline;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol=='0'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ pointer ] = '0' ;
	_stateRun_instructions[ pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol=='1'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 3 + pointer ] = '1' ;
	_stateRun_instructions[ 3 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 3 + pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol=='2'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 6 + pointer ] = '2' ;
	_stateRun_instructions[ 6 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 6 + pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol=='3'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 9 + pointer ] = '3' ;
	_stateRun_instructions[ 9 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 9 + pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol=='4'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 12 + pointer ] = '4' ;
	_stateRun_instructions[ 12 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 12 + pointer + 2 ] = jumpwhat ;
	_stateRun_line = 0 ;	
}
void _stateRun_setnotcurrentandnextsymbol( byte line , byte symbol , byte dir , byte jump ) {
	int pointer = line * 15 ;
// FIXME TODO simplify!
	if( symbol == 22 ) symbol = '0' ;
	if( symbol == 23 ) symbol = '1' ;
	if( symbol == 0 ) symbol = '2' ;
	if( symbol == 1 ) symbol = '3' ;
	if( symbol == 2 ) symbol = '4' ;	
	if( dir == 18 ) dir = '0' ;
	if( dir == 255 ) dir = '~' ;
	if( dir == 6 ) dir = '1' ;
	//jump += 48 ;
	byte jumpthisline = line + 48 ;
	byte jumpnext = jump + 48 ;
	byte jumpwhat ;
	byte dirthisline;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol!='0'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}
	_stateRun_instructions[ pointer ] = '0' ;
	_stateRun_instructions[ pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol!='1'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 3 + pointer ] = '1' ;
	_stateRun_instructions[ 3 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 3 + pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol!='2'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 6 + pointer ] = '2' ;
	_stateRun_instructions[ 6 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 6 + pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol!='3'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 9 + pointer ] = '3' ;
	_stateRun_instructions[ 9 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 9 + pointer + 2 ] = jumpwhat ;
	jumpwhat = jumpthisline ;
	dirthisline = dir ;
	if(symbol!='4'){
		jumpwhat = jumpnext ;
		dirthisline = '~' ;
	}	
	_stateRun_instructions[ 12 + pointer ] = '4' ;
	_stateRun_instructions[ 12 + pointer + 1 ] = dirthisline ; 
	_stateRun_instructions[ 12 + pointer + 2 ] = jumpwhat ;
	_stateRun_line = 0 ;	
}
byte _stateRun_getnextsymbol( byte currentsymbol ) {
		// Find code block
		//int pointer = _stateRun_line * 6 ;
		int rel = _stateRun_line * 15 ;
		rel = rel + ( 3 * currentsymbol ) ;
		//return( _stateRun_instructions[ _stateRun_pointer + rel ] - 48 ) ;
		return( _stateRun_instructions[ _stateRun_pointer + rel ] ) ;
}
bool _stateRun_stateused( int line ) {
	int pointer = line * 15 ;
	for( int i = 0 ; i < 16 ; i++ ) {
		if( _stateRun_instructions[ pointer + i ] != '0' ){
			//_stateRun_log(String(i)+" "+_stateRun_instructions[ pointer + i ]);
			return( true ) ;
		}
	}
	return( false) ;
}
byte _stateRun_getnextdir( byte currentsymbol ) {
		// Find code block
		//int pointer = _stateRun_line * 6 ;
		int rel = _stateRun_line * 15 ;
		rel = rel + ( 3 * currentsymbol ) ;
		//return( _stateRun_instructions[ _stateRun_pointer + rel + 1] - 48 ) ;
		return( _stateRun_instructions[ _stateRun_pointer + rel + 1 ]  ) ;
}
void _stateRun_jump( byte currentsymbol ) {
		int rel = _stateRun_line * 15 ;
		rel = rel + ( 3 * currentsymbol ) ;
		int j = _stateRun_instructions[ _stateRun_pointer + rel + 2 ] ;
		if(j!='~') _stateRun_line = _stateRun_instructions[ _stateRun_pointer + rel + 2 ] - 48 ;
}
void _stateRun_left( ) {
	if( _stateRun_disabled ) return;
	// FIXME TODO
	if( _stateEdit_cursor == 0 ){
		_stateEdit_cursor = 23 ;
	}else{
		_stateEdit_cursor--;
	}
	_cursor_highlight();
	_stateEdit_tapeupdated = true;
}
void _stateRun_right( ) {
	if( _stateRun_disabled ) return;
	// FIXME TODO
	if( _stateEdit_cursor == 23 ) {
		_stateEdit_cursor = 0 ;
	} else {
		_stateEdit_cursor++;
	}
	_cursor_highlight();
	_stateEdit_tapeupdated = true;
}
void _stateRun_broadcast_buttonTogglePin( ) {
	if( _stateRun_disabled ) return;
	_stateRun_flagToggle = true ;
/*
	byte y = _stateEdit_tapeget(_stateEdit_cursor) + 1 ;
	if( y == 5 ) y = 0 ;
	_stateEdit_tapeset( _stateEdit_cursor , y ) ;	
*/
/*
	int rel = _stateRun_line * 15 + ( 3 * _stateEdit_tapeget( _stateEdit_cursor ) ) + _stateRun_pointer ;
	//byte nextdir = _stateRun_getnextdir( tv ) ;
	byte x = _stateRun_instructions[ rel + 1 ] ;
	if( x == '0' ) _stateRun_left( ) ;
	if( x == '1' ) _stateRun_right( ) ;
	x = _stateRun_instructions[ rel + 2 ] ; 
	if( x != '~' ) _stateRun_line = x - 48 ;		
*/
	//_stateRun_log("xxx");
	// FIXME TODO
	/*
	if(_stateEdit_tapeget(_stateEdit_cursor)==0){
		_stateEdit_tapeset(_stateEdit_cursor,1);
	}else{
		_stateEdit_tapeset(_stateEdit_cursor,0);
	}
	_cursor_dehighlight();
	_stateEdit_tapeupdated = true;
	*/
}
void _stateRun_broadcast_runResetLine( ) {
	_stateRun_line = 0 ;
}
void _stateRun_broadcast_reset( ) {
	_stateRun_line = 0 ;
	for(int i=0;i<362;i++){
	_stateRun_instructions[i]= '0';
	}
}
void _stateRun_setup( ) {
}
void _stateRun_wakeup( ) { }
void _stateRun_loop( ) {
/* Macro Start ( _macroTrigger 10 ) */
if( _stateRun_disabled ) return ;
static unsigned int _stateRun_Trigger = 10 ;	
static unsigned int _stateRun_Counter = 0 ;
if ( ++_stateRun_Counter < _stateRun_Trigger ) return ;
_stateRun_Counter = 0 ;
/* Macro Start ( _macroTrigger 10 ) */
	_stateRun_Trigger = _vars_speedVal ;
	//////
	int rel = _stateRun_line * 15 + ( 3 * _stateEdit_tapeget( _stateEdit_cursor ) ) + _stateRun_pointer ;
	//_stateEdit_tapeset( _stateEdit_cursor , _stateRun_getnextsymbol( tv ) - 48 );
	if(!_stateRun_flagToggle) {
		_stateEdit_tapeset( _stateEdit_cursor , _stateRun_instructions[ rel ] - 48 );
	}else{
		byte tg = _stateEdit_tapeget( _stateEdit_cursor ) + 1 ;
		if( tg == 5 ) tg = 0 ; 
		_stateEdit_tapeset( _stateEdit_cursor , tg ) ;
		_stateRun_flagToggle=false;
	}
	//byte nextdir = _stateRun_getnextdir( tv ) ;
	byte x = _stateRun_instructions[ rel + 1 ] ;
	if( x == '0' ) _stateRun_left( ) ;
	if( x == '1' ) _stateRun_right( ) ;
	x = _stateRun_instructions[ rel + 2 ] ; 
	if( x != '~' ) _stateRun_line = x - 48 ;	
	_sfx_play( 1000 , 1 );
	_stateEdit_drawtape( ) ;
	_display_setpixel( _stateEdit_cursor , 6 ) ;
	_display_show();
}


/* stackProg */

/* Macro Start ( _macroDisabled true ) */
boolean _stackProg_disabled = true ;
void _stackProg_broadcast_disable_stackProg_( ) {
	_stackProg_disabled = true ;
}
void _stackProg_broadcast_enable_stackProg_( ) {
	_stackProg_disabled = false ;
	_stackProg_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stackProg_log( String msg ) {
	_serial_transmit( F( "_stackProg_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stackProg_state = 0 ; 
byte _stackProg_stateLast = 255 ; 
void _stackProg_broadcast_reset( ) {
	_broadcast_( F("stackProg") ,  F( "disable_state" ) ) ;
	_stackProg_state=0;
	_stackProg_stateLast=255;
}
void _stackProg_broadcast_buttonRunStopPin( ) {
	if( _stackProg_disabled ) return ;
	if(_stackProg_state==0) return;
	_broadcast_( F("stackProg") ,  F( "disable_state" ) ) ;
	_stackProg_state-- ;
}
void _stackProg_broadcast_buttonTogglePin( ) {
	if( _stackProg_disabled ) return ;
	_broadcast_( F("stackProg") ,  F( "disable_state" ) ) ;
	_stackProg_state++ ;
	if( _stackProg_state == 5 ) {
		_stackProg_state = 0 ;
		_broadcast_( F("stackProg") ,  F( "codeupdate" ) ) ;
		_broadcast_( F("stackProg") ,  F( "beep" ) ) ;
	}
	/*
	if(_stackProg_state==5){
		_stackProg_state=0;
		//_broadcast_( F("stackProg") , F("codeupdate"));
	}
	*/
}
void _stackProg_setup( ) {
	if( _stackProg_disabled ) return ;
}
void _stackProg_wakeup( ) { }
void _stackProg_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stackProg_disabled ) return ;
static unsigned int _stackProg_Trigger = 100 ;	
static unsigned int _stackProg_Counter = 0 ;
if ( ++_stackProg_Counter < _stackProg_Trigger ) return ;
_stackProg_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	//_stackProg_log( String(_stackProg_state) ) ;
	if( _stackProg_state != _stackProg_stateLast ) {	
		_stackProg_log( String(_stackProg_state) );
		//_broadcast_( F("stackProg") ,  F( "disable_state" ) ) ;
		if( _stackProg_state == 0 ) {
			_broadcast_( F("stackProg") ,  F( "enable_stateSelectline" ) ) ;
		}
		if( _stackProg_state == 1 ) {
			_broadcast_( F("stackProg") ,  F( "enable_stateSelectcurrentsymbol" ) ) ;
		}
		if( _stackProg_state == 2 ) {
			_broadcast_( F("stackProg") ,  F( "enable_stateSelectnextsymbol" ) ) ;
		}	
		if( _stackProg_state == 3 ) {
			_broadcast_( F("stackProg") ,  F( "enable_stateSelectdir" ) ) ;
		}	
		if( _stackProg_state == 4 ) {
			_broadcast_( F("stackProg") ,  F( "enable_stateSelectjump" ) ) ;
		}	
		_stackProg_stateLast = _stackProg_state ;
	}
}


/* stateSelectline */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectline_disabled = true ;
void _stateSelectline_broadcast_disable_stateSelectline_( ) {
	_stateSelectline_disabled = true ;
}
void _stateSelectline_broadcast_enable_stateSelectline_( ) {
	_stateSelectline_disabled = false ;
	_stateSelectline_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectline_log( String msg ) {
	_serial_transmit( F( "_stateSelectline_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectline_cursor = 0 ;
void _stateSelectline_broadcast_reset( ) {
	_stateSelectline_cursor = 0 ;
}
void _stateSelectline_broadcast_buttonLeftPin( ) {
	if( _stateSelectline_disabled ) return ;
	if( _stateSelectline_cursor == 0 ) {
		_stateSelectline_cursor = 23 ;
	} else {
		_stateSelectline_cursor -= 1 ;
	}
	_cursor_highlight( );
}
void _stateSelectline_broadcast_buttonRightPin( ) {
	if( _stateSelectline_disabled ) return;
	if( _stateSelectline_cursor == 23 ) {
		_stateSelectline_cursor = 0 ;
	} else {
		_stateSelectline_cursor++ ;
	}
	_cursor_highlight( );
}
void _stateSelectline_setup( ) {
}
void _stateSelectline_wakeup( ) { }
void _stateSelectline_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectline_disabled ) return ;
static unsigned int _stateSelectline_Trigger = 100 ;	
static unsigned int _stateSelectline_Counter = 0 ;
if ( ++_stateSelectline_Counter < _stateSelectline_Trigger ) return ;
_stateSelectline_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern1( ) ;
	for( int i = 0 ; i < 24 ; i++ ) {
		if( _stateRun_stateused( i ) ) {
			_display_setpixel( i ,  5 ) ;
		}
	}
	if( _cursor_toggle ) {
		_display_setpixel( _stateSelectline_cursor ,  _cursor_col  ) ;
	} else {
		//_display_setpixel( _stateSelectline_cursor ,  7  ) ;
	}	
	_display_show( ) ;
}


/* stateSelectcurrentsymbol */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectcurrentsymbol_disabled = true ;
void _stateSelectcurrentsymbol_broadcast_disable_stateSelectcurrentsymbol_( ) {
	_stateSelectcurrentsymbol_disabled = true ;
}
void _stateSelectcurrentsymbol_broadcast_enable_stateSelectcurrentsymbol_( ) {
	_stateSelectcurrentsymbol_disabled = false ;
	_stateSelectcurrentsymbol_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectcurrentsymbol_log( String msg ) {
	_serial_transmit( F( "_stateSelectcurrentsymbol_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectcurrentsymbol_cursor = 22 ;
void _stateSelectcurrentsymbol_broadcast_reset( ) {
	_stateSelectcurrentsymbol_cursor = 22 ;
}
void _stateSelectcurrentsymbol_broadcast_buttonLeftPin( ) {
	if( _stateSelectcurrentsymbol_disabled ) return ;
	if( _stateSelectcurrentsymbol_cursor == 22 ){
		_stateSelectcurrentsymbol_cursor = 255 ;
		return;
	}
	if( _stateSelectcurrentsymbol_cursor == 255 ) {
		_stateSelectcurrentsymbol_cursor = 22 ;
		return ;
	}
	if( _stateSelectcurrentsymbol_cursor == 0 ) {
		_stateSelectcurrentsymbol_cursor = 23 ;
	} else {
		_stateSelectcurrentsymbol_cursor -= 1 ;
	}
	_cursor_highlight( );
}
void _stateSelectcurrentsymbol_broadcast_buttonRightPin( ) {
	if( _stateSelectcurrentsymbol_disabled ) return;
	if( _stateSelectcurrentsymbol_cursor == 2 ){
		_stateSelectcurrentsymbol_cursor = 255 ;
		return ;
	}
	if(_stateSelectcurrentsymbol_cursor == 255 ) {
		_stateSelectcurrentsymbol_cursor = 2 ;
		return ;
	}	
	if( _stateSelectcurrentsymbol_cursor == 23 ) {
		_stateSelectcurrentsymbol_cursor = 0 ;
	} else {
		_stateSelectcurrentsymbol_cursor++ ;
	}
	_cursor_highlight( );
}
void _stateSelectcurrentsymbol_setup( ) {
}
void _stateSelectcurrentsymbol_wakeup( ) { }
void _stateSelectcurrentsymbol_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectcurrentsymbol_disabled ) return ;
static unsigned int _stateSelectcurrentsymbol_Trigger = 100 ;	
static unsigned int _stateSelectcurrentsymbol_Counter = 0 ;
if ( ++_stateSelectcurrentsymbol_Counter < _stateSelectcurrentsymbol_Trigger ) return ;
_stateSelectcurrentsymbol_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern2( ) ;
	_display_currentsymbols( ) ;
	_display_nextsymbols( ) ;
	byte line = _stateSelectline_cursor  ;
	byte currentsymbol = _stateSelectcurrentsymbol_cursor ;
	if(currentsymbol==255) currentsymbol = 22;
	int pointer = line * 15 ;
	if( currentsymbol == 22 ) pointer += 0 ;
	if( currentsymbol == 23 ) pointer += 3 ;
	if( currentsymbol == 0 ) pointer += 6 ;
	if( currentsymbol == 1 ) pointer += 9 ;
	if( currentsymbol == 2 ) pointer += 12 ;
	byte nextsymbol = _stateRun_instructions[pointer]-48;
	byte pos = 14 - nextsymbol ;
	_display_togglepixel( pos ,5);
	byte nextdir = _stateRun_instructions[pointer+1];
	if(nextdir=='0') _display_togglepixel( 18 ,5);
	if(nextdir=='1') _display_togglepixel( 6 ,5);
	if(nextdir=='~'){ 
		_display_togglepixel( 18 ,5);
		_display_togglepixel( 6 ,5);
	}
	if( _cursor_toggle ) {
		if( _stateSelectcurrentsymbol_cursor != 255 ) {
			_display_setpixel( _stateSelectcurrentsymbol_cursor ,  _cursor_col  ) ;
		}else{
				_display_selectallcurrentsymbols( _cursor_col ) ;
		}
	} else {
		//_display_setpixel( _stateSelectcurrentsymbol_cursor ,  7  ) ;
	}	
	_display_show();
}


/* stateSelectnextsymbol */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectnextsymbol_disabled = true ;
void _stateSelectnextsymbol_broadcast_disable_stateSelectnextsymbol_( ) {
	_stateSelectnextsymbol_disabled = true ;
}
void _stateSelectnextsymbol_broadcast_enable_stateSelectnextsymbol_( ) {
	_stateSelectnextsymbol_disabled = false ;
	_stateSelectnextsymbol_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectnextsymbol_log( String msg ) {
	_serial_transmit( F( "_stateSelectnextsymbol_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectnextsymbol_cursor = 14 ;
// FIXME TODO swap button directions???
// SWAPPED
void _stateSelectnextsymbol_broadcast_buttonRightPin( ) {
	if( _stateSelectnextsymbol_disabled ) return ;
	//if( _stateSelectnextsymbol_cursor == 22 ) return;
	if( _stateSelectnextsymbol_cursor ==  10 ){
		_stateSelectnextsymbol_cursor = 255 ;
		return;
	}
	if( _stateSelectnextsymbol_cursor ==  255 ){
		_stateSelectnextsymbol_cursor = 10 ;
		return;
	}
	if( _stateSelectnextsymbol_cursor == 0 ) {
		_stateSelectnextsymbol_cursor = 23 ;
	} else {
		_stateSelectnextsymbol_cursor -= 1 ;
	}
	_cursor_highlight( );
}
void _stateSelectnextsymbol_broadcast_buttonLeftPin( ) {
	if( _stateSelectnextsymbol_disabled ) return;
	if( _stateSelectnextsymbol_cursor ==  14 ){
		_stateSelectnextsymbol_cursor=255;
		return;
	}
	if( _stateSelectnextsymbol_cursor ==  255 ){
		_stateSelectnextsymbol_cursor = 14 ;
		return;
	}	
	if( _stateSelectnextsymbol_cursor == 23 ) {
		_stateSelectnextsymbol_cursor = 0 ;
	} else {
		_stateSelectnextsymbol_cursor += 1 ;
	}
	_cursor_highlight( );
}
void _stateSelectnextsymbol_setup( ) {
}
void _stateSelectnextsymbol_wakeup( ) { 
	byte line = _stateSelectline_cursor  ;
	byte currentsymbol = _stateSelectcurrentsymbol_cursor ;
	if(currentsymbol==255) currentsymbol = 22;
	int pointer = line * 15 ;
	if( currentsymbol == 22 ) pointer += 0 ;
	if( currentsymbol == 23 ) pointer += 3 ;
	if( currentsymbol == 0 ) pointer += 6 ;
	if( currentsymbol == 1 ) pointer += 9 ;
	if( currentsymbol == 2 ) pointer += 12 ;
	byte nextsymbol = _stateRun_instructions[pointer]-48;
	_stateSelectnextsymbol_cursor = 14 - nextsymbol ;
}
void _stateSelectnextsymbol_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectnextsymbol_disabled ) return ;
static unsigned int _stateSelectnextsymbol_Trigger = 100 ;	
static unsigned int _stateSelectnextsymbol_Counter = 0 ;
if ( ++_stateSelectnextsymbol_Counter < _stateSelectnextsymbol_Trigger ) return ;
_stateSelectnextsymbol_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern2( ) ;
	_display_nextsymbols( ) ;
	byte line = _stateSelectline_cursor  ;
	byte currentsymbol = _stateSelectcurrentsymbol_cursor ;
	if(currentsymbol==255){
		currentsymbol = 22;
		if(_cursor_toggle ){
			_display_selectallcurrentsymbols( 5 ) ;
		}else{
			_display_currentsymbols( ) ;
		}
	}else{
		_display_currentsymbols( ) ;
		_display_togglepixel( currentsymbol ,5);
	}
	int pointer = line * 15 ;
	if( currentsymbol == 22 ) pointer += 0 ;
	if( currentsymbol == 23 ) pointer += 3 ;
	if( currentsymbol == 0 ) pointer += 6 ;
	if( currentsymbol == 1 ) pointer += 9 ;
	if( currentsymbol == 2 ) pointer += 12 ;
	byte nextsymbol = _stateRun_instructions[pointer]-48;
	byte pos = 14 - nextsymbol ;
	//_display_togglepixel( currentsymbol ,5);
	_display_togglepixel( pos ,5);
	byte nextdir = _stateRun_instructions[pointer+1];
	if(nextdir=='0') _display_togglepixel( 18 ,5);
	if(nextdir=='1') _display_togglepixel( 6 ,5);	
	if(nextdir=='~'){ 
		_display_togglepixel( 18 ,5);
		_display_togglepixel( 6 ,5);
	}	
	if( _cursor_toggle ) {
		if( _stateSelectnextsymbol_cursor != 255 ) {
			_display_setpixel( _stateSelectnextsymbol_cursor ,  _cursor_col  ) ;
		}else{
				_display_selectallnextsymbols( _cursor_col ) ;
		}		
	} else {
		//_display_setpixel( _stateSelectnextsymbol_cursor ,  7  ) ;
	}	
	_display_show();
}


/* stateSelectdir */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectdir_disabled = true ;
void _stateSelectdir_broadcast_disable_stateSelectdir_( ) {
	_stateSelectdir_disabled = true ;
}
void _stateSelectdir_broadcast_enable_stateSelectdir_( ) {
	_stateSelectdir_disabled = false ;
	_stateSelectdir_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectdir_log( String msg ) {
	_serial_transmit( F( "_stateSelectdir_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectdir_cursor = 6 ;
void _stateSelectdir_broadcast_buttonLeftPin( ) {
	if( _stateSelectdir_disabled ) return ;
	if( _stateSelectdir_cursor == 18 ){
		_stateSelectdir_cursor = 255 ;
		return;
	}
	 _stateSelectdir_cursor = 18 ; 
	_cursor_highlight( );
}
void _stateSelectdir_broadcast_buttonRightPin( ) {
	if( _stateSelectdir_disabled ) return;
	if( _stateSelectdir_cursor ==  6 ){
		_stateSelectdir_cursor = 255 ;
		return;
	}
	_stateSelectdir_cursor =  6 ;
	_cursor_highlight( );
}
void _stateSelectdir_setup( ) {
}
void _stateSelectdir_wakeup( ) { 
	byte line = _stateSelectline_cursor  ;
	byte currentsymbol = _stateSelectcurrentsymbol_cursor ;
	if(currentsymbol==255) currentsymbol = 22;
	int pointer = line * 15 ;
	if( currentsymbol == 22 ) pointer += 0 ;
	if( currentsymbol == 23 ) pointer += 3 ;
	if( currentsymbol == 0 ) pointer += 6 ;
	if( currentsymbol == 1 ) pointer += 9 ;
	if( currentsymbol == 2 ) pointer += 12 ;
	byte nextdir = _stateRun_instructions[pointer+1];
	if(nextdir=='0') _stateSelectdir_cursor = 18;
	if(nextdir=='1') _stateSelectdir_cursor = 6;
	if(nextdir=='~') _stateSelectdir_cursor = 255;
}
void _stateSelectdir_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectdir_disabled ) return ;
static unsigned int _stateSelectdir_Trigger = 100 ;	
static unsigned int _stateSelectdir_Counter = 0 ;
if ( ++_stateSelectdir_Counter < _stateSelectdir_Trigger ) return ;
_stateSelectdir_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern2( ) ;
	_display_nextsymbols( ) ;	
	byte currentsymbol = _stateSelectcurrentsymbol_cursor ;
	byte nextsymbol = _stateSelectnextsymbol_cursor ;
	if(currentsymbol==255){
		currentsymbol = 22;
		if(_cursor_toggle ){
			_display_selectallcurrentsymbols( 5 ) ;
		}else{
			_display_currentsymbols( ) ;
		}
	}else{
		_display_currentsymbols( ) ;
		_display_togglepixel( currentsymbol ,5);
	}
	if(nextsymbol==255){
		nextsymbol = 14;
		if(_cursor_toggle ){
			_display_selectallnextsymbols( 5 ) ;
		}else{
			_display_nextsymbols( ) ;
		}
	}else{
		_display_nextsymbols( ) ;
		_display_togglepixel( nextsymbol  ,5);	
	}
	//byte nextsymbol = _stateRun_instructions[pointer]-48;
	if( _cursor_toggle ) {
		if( _stateSelectdir_cursor != 255 ) {
			_display_setpixel( _stateSelectdir_cursor ,  _cursor_col  ) ;
		}else{
			_display_setpixel( 6 ,  _cursor_col  ) ;
			_display_setpixel( 24-6 ,  _cursor_col  ) ;
		}
	} else {
		if( _stateSelectdir_cursor != 255 ) {
			_display_setpixel( _stateSelectdir_cursor ,  5 ) ;
		}else{
			_display_setpixel( 6 ,  5 ) ;
			_display_setpixel( 24-6,  5 ) ;
		}
		//_display_setpixel( _stateSelectdir_cursor ,  7  ) ;
	}	
	_display_show();
}


/* stateSelectjump */

/* Macro Start ( _macroDisabled true ) */
boolean _stateSelectjump_disabled = true ;
void _stateSelectjump_broadcast_disable_stateSelectjump_( ) {
	_stateSelectjump_disabled = true ;
}
void _stateSelectjump_broadcast_enable_stateSelectjump_( ) {
	_stateSelectjump_disabled = false ;
	_stateSelectjump_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _stateSelectjump_log( String msg ) {
	_serial_transmit( F( "_stateSelectjump_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
byte _stateSelectjump_cursor = 0 ;
void _stateSelectjump_broadcast_buttonLeftPin( ) {
	if( _stateSelectjump_disabled ) return ;
	if( _stateSelectjump_cursor == 0 ) {
		_stateSelectjump_cursor = 23 ;
	} else {
		_stateSelectjump_cursor-- ;
	}
	_cursor_highlight( );
}
void _stateSelectjump_broadcast_buttonRightPin( ) {
	if( _stateSelectjump_disabled ) return;
	if( _stateSelectjump_cursor == 23 ) {
		_stateSelectjump_cursor = 0 ;
	} else {
		_stateSelectjump_cursor++ ;
	}
	_cursor_highlight( );
}
void _stateSelectjump_setup( ) {
}
void _stateSelectjump_wakeup( ) {
	byte line = _stateSelectline_cursor  ;
	byte currentsymbol = _stateSelectcurrentsymbol_cursor ;
	if(currentsymbol==255) currentsymbol = 22;
	int pointer = line * 15 ;
	if( currentsymbol == 22 ) pointer += 0 ;
	if( currentsymbol == 23 ) pointer += 3 ;
	if( currentsymbol == 0 ) pointer += 6 ;
	if( currentsymbol == 1 ) pointer += 9 ;
	if( currentsymbol == 2 ) pointer += 12 ;
	_stateSelectjump_cursor = _stateRun_instructions[pointer+2]-48;
}
void _stateSelectjump_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _stateSelectjump_disabled ) return ;
static unsigned int _stateSelectjump_Trigger = 100 ;	
static unsigned int _stateSelectjump_Counter = 0 ;
if ( ++_stateSelectjump_Counter < _stateSelectjump_Trigger ) return ;
_stateSelectjump_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
	_display_pattern1( ) ;
	_display_setpixel( _stateSelectline_cursor ,  5 ) ;
	if( _cursor_toggle ) {
		_display_setpixel( _stateSelectjump_cursor ,  _cursor_col  ) ;
	} else {
		//_display_setpixel( _stateSelectjump_cursor ,  7  ) ;
	}	
	_display_show();
}


/* main */

/* Macro Start ( _macroDisabled false ) */
boolean _main_disabled = false ;
void _main_broadcast_disable_main_( ) {
	_main_disabled = true ;
}
void _main_broadcast_enable_main_( ) {
	_main_disabled = false ;
	_main_wakeup( ) ;
}
/* Macro End ( _macroDisabled false ) */
/* Macro Start ( _macroLog */
void _main_log( String msg ) {
	_serial_transmit( F( "_main_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
void _main_broadcast_settingsupdated( ) {
	byte key = _stateSelectkey_cursor ;
	byte val = _stateSelectval_cursor ;
	if(key==0){
		_display_strip.setBrightness( map(val , 0 , 23 , 1 , 255 ) ) ;
	}
	if(key==1){
		if(val==0) _broadcast_( F("main") ,  F( "disable_sfx" ) ) ;	
		if(val==1) _broadcast_( F("main") ,  F( "enable_sfx" ) ) ;	
	}
}
void _main_broadcast_codeupdate( ) {
	// Reason it be in main since all variables are in scope
	byte line = _stateSelectline_cursor  ;
	byte currentsymbol = _stateSelectcurrentsymbol_cursor  ;
	byte nextsymbol = _stateSelectnextsymbol_cursor   ;
	byte dir = _stateSelectdir_cursor  ;
	byte jump = _stateSelectjump_cursor  ;
	if( ( currentsymbol == 255 ) && ( nextsymbol != 255 ) ) {
		//_stateRun_setall( line , nextsymbol , dir , jump ) ;
		_stateRun_setcurrentandnotnextsymbol( line , nextsymbol , dir , jump ) ;
		return ;		
	}
	if( ( currentsymbol == 255 ) && ( nextsymbol == 255 ) ) {
		_stateRun_setallandnextsymbol( line , dir , jump ) ;
		return ;
	}
	if( ( currentsymbol != 255 ) && ( nextsymbol == 255 ) ) {
		_stateRun_setnotcurrentandnextsymbol( line , currentsymbol , dir , jump ) ;
		return ;
	}	
	//line = ( line + 2 ) % 24 ; 	
	//currentsymbol = ( currentsymbol + 2 ) % 24 ; 	
	//nextsymbol = ( nextsymbol + 2 ) % 24 ; 	
	//dir = ( dir + 2 ) % 24 ; 	
	//jump = ( jump + 2 ) % 24 ; 	
	int pointer = line * 15 ;
	//_main_log( String( pointer ) ) ;
	if( currentsymbol == 22 ) pointer += 0 ;
	if( currentsymbol == 23 ) pointer += 3 ;
	if( currentsymbol == 0 ) pointer += 6 ;
	if( currentsymbol == 1 ) pointer += 9 ;
	if( currentsymbol == 2 ) pointer += 12 ;
	//_main_log( String( pointer ) ) ;
	String cmd = "XXX" ;
	if( nextsymbol == 14 ) cmd[ 0 ] = '0' ;
	if( nextsymbol == 13 ) cmd[ 0 ] = '1' ;
	if( nextsymbol == 12 ) cmd[ 0 ] = '2' ;
	if( nextsymbol == 11 ) cmd[ 0 ] = '3' ;
	if( nextsymbol == 10 ) cmd[ 0 ] = '4' ;
	if( dir == 18 ) cmd[ 1 ] = '0' ;
	if( dir == 255 ) cmd[ 1 ] = '~' ;
	if( dir == 6 ) cmd[ 1 ] = '1' ;
	cmd[ 2 ] = jump + 48 ;
	_stateRun_instructions[ pointer ] = cmd[ 0 ] ;
	_stateRun_instructions[ pointer + 1 ] = cmd[ 1 ] ;
	_stateRun_instructions[ pointer + 2 ] = cmd[ 2 ] ;
	_stateRun_line = 0 ;	
	//_main_log(cmd);
	/*
	String cmd = "XXX" ;
	if(nextsymbol==14){
		cmd[0]='0';
	}else{
		cmd[0]='1';
	}
	if(dir==15){
		cmd[1]='0';
	}else{
		cmd[1]='1';
	}
	cmd[2]=jump+48;
	_stateRun_instructions[pointer]=cmd[0];
	_stateRun_instructions[pointer+1]=cmd[1];
	_stateRun_instructions[pointer+2]=cmd[2];
	_stateRun_line = 0 ;
	_main_log(F("UPDATING CODE!"));
	_main_log(String(line)+F(":")+String(currentsymbol)+F(":")+String(nextsymbol)+F(":")+String(dir)+F(":")+String(jump));
	_main_log(cmd);
	*/
}
void _main_broadcast_stackeditrun( ){
	_broadcast_( F("main") ,  F( "disable_state" ) ) ;
	_broadcast_( F("main") ,  F( "disable_stack" ) ) ;
	_broadcast_( F("main") ,  F( "enable_stackEditrun" ) ) ;
	//FIXME TODO
	_stackEditrun_stateLast=255;
}
void _main_broadcast_stackprog( ){
	_broadcast_( F("main") ,  F( "disable_state" ) ) ;
	_broadcast_( F("main") ,  F( "disable_stack" ) ) ;
	_broadcast_( F("main") ,  F( "enable_stackProg" ) ) ;
	//FIXME TODO
	_stackProg_stateLast=255;
}
void _main_broadcast_stacksettings( ){
	_broadcast_( F("main") ,  F( "disable_state" ) ) ;
	_broadcast_( F("main") ,  F( "disable_stack" ) ) ;
	_broadcast_( F("main") ,  F( "enable_stackSettings" ) ) ;
	//FIXME TODO
	_stackSettings_stateLast=255;
}
void _main_setup( ) {
	randomSeed( analogRead( 0 ) ) ;
	_serial_transmit( F( "#" ) , F( "B" ) ) ;
	_broadcast_( F("main") ,  F( "stackeditrun" ) ) ;
}
void _main_wakeup( ) { }
byte _main_stack = 0 ;
byte _main_stackLast = 255 ;
void _main_loop( ) {
/* Macro Start ( _macroTrigger 100 ) */
if( _main_disabled ) return ;
static unsigned int _main_Trigger = 100 ;	
static unsigned int _main_Counter = 0 ;
if ( ++_main_Counter < _main_Trigger ) return ;
_main_Counter = 0 ;
/* Macro Start ( _macroTrigger 100 ) */
	//////
/*
	if(_stateRun_stateused( 10 )){
		_main_log("!!!!");
		return;
	}
*/
	//_vars_speedVal = map( analogRead( A7 ) , 0 , 1023 , 1 , 25 ) ;	
	//_vars_speedVal = map( analogRead( A7 ) , 0 , 1023 , 500 , 0 ) ;	
		_vars_speedVal = 1024 - analogRead( A7 ) ;
		//_main_log("tick"+String(_button_tickbuttonLeftPin));
	if(
		( _button_tickbuttonLeftPin == 200 )
		&&
		( _button_tickbuttonRightPin == 200 )
		&&
		( _button_tickbuttonTogglePin == 200 )
		&&
		( _button_tickbuttonRunStopPin == 200 )
	) {
		_main_log("settings!");
		_main_stack = 2 ;
		_main_stackLast = 255 ;
		_button_tickbuttonLeftPin = 0 ;
		_button_tickbuttonRightPin = 0 ;
		_button_tickbuttonTogglePin = 0 ;
		_button_tickbuttonRunStopPin = 0 ;
	}
	if(
		( _button_tickbuttonLeftPin == 200 )
		&&
		( _button_tickbuttonRightPin == 200 )
	) {
		//_main_log("tick");
		_main_stack++ ;
		if( _main_stack > 1 ) {
			_main_stack = 0 ;
		}
		_main_stackLast = 255 ;
		_button_tickbuttonLeftPin = 0 ;
		_button_tickbuttonRightPin = 0 ;
	}
	if(
		( _button_tickbuttonTogglePin == 200 )
		&&
		( _button_tickbuttonRunStopPin == 200 )
	) {
		//_main_log("tick");
		_broadcast_( F("main") ,  F( "reset" ) ) ;
		_main_stack = 0 ;
		_main_stackLast = 255 ;
		_button_tickbuttonTogglePin = 0 ;
		_button_tickbuttonRunStopPin = 0 ;
	}
	if( _main_stack == 0 ) {
		if( _main_stackLast != _main_stack ) _broadcast_( F("main") ,  F( "stackeditrun" ) ) ;
		_main_stackLast = _main_stack ;
	}
	if( _main_stack == 1 ) {
		if( _main_stackLast != _main_stack )_broadcast_( F("main") ,  F( "stackprog" ) ) ;
		_main_stackLast = _main_stack ;
	}		
	if( _main_stack == 2 ) {
		if( _main_stackLast != _main_stack )_broadcast_( F("main") ,  F( "stacksettings" ) ) ;
		_main_stackLast = _main_stack ;
	}		
}


/* blank */

/* Macro Start ( _macroDisabled true ) */
boolean _blank_disabled = true ;
void _blank_broadcast_disable_blank_( ) {
	_blank_disabled = true ;
}
void _blank_broadcast_enable_blank_( ) {
	_blank_disabled = false ;
	_blank_wakeup( ) ;
}
/* Macro End ( _macroDisabled true ) */
/* Macro Start ( _macroLog */
void _blank_log( String msg ) {
	_serial_transmit( F( "_blank_" ) , msg ) ;
}
/* Macro End ( _macroLog ) */
void _blank_setup( ) {
}
void _blank_wakeup( ) { }
void _blank_loop( ) {
/* Macro Start ( _macroTrigger 10000 ) */
if( _blank_disabled ) return ;
static unsigned int _blank_Trigger = 10000 ;	
static unsigned int _blank_Counter = 0 ;
if ( ++_blank_Counter < _blank_Trigger ) return ;
_blank_Counter = 0 ;
/* Macro Start ( _macroTrigger 10000 ) */
	//////
}



/* TEMPLATE START */
void setup ( ) {

	_eeprom_setup( ) ;
	_serial_setup( ) ;
	_button_setup( ) ;
	_display_setup( ) ;
	_cursor_setup( ) ;
	_sfx_setup( ) ;
	_stackSettings_setup( ) ;
	_stateSelectkey_setup( ) ;
	_stateSelectval_setup( ) ;
	_stackEditrun_setup( ) ;
	_stateEdit_setup( ) ;
	_stateRun_setup( ) ;
	_stackProg_setup( ) ;
	_stateSelectline_setup( ) ;
	_stateSelectcurrentsymbol_setup( ) ;
	_stateSelectnextsymbol_setup( ) ;
	_stateSelectdir_setup( ) ;
	_stateSelectjump_setup( ) ;
	_main_setup( ) ;
	_blank_setup( ) ;
  
}

void loop ( ) {
  
	_vars_loop( ) ;
	_serial_loop( ) ;
	_broadcast_loop( ) ;
	_button_loop( ) ;
	_display_loop( ) ;
	_cursor_loop( ) ;
	_sfx_loop( ) ;
	_stackSettings_loop( ) ;
	_stateSelectkey_loop( ) ;
	_stateSelectval_loop( ) ;
	_stackEditrun_loop( ) ;
	_stateEdit_loop( ) ;
	_stateRun_loop( ) ;
	_stackProg_loop( ) ;
	_stateSelectline_loop( ) ;
	_stateSelectcurrentsymbol_loop( ) ;
	_stateSelectnextsymbol_loop( ) ;
	_stateSelectdir_loop( ) ;
	_stateSelectjump_loop( ) ;
	_main_loop( ) ;
	_blank_loop( ) ;

}

/* TEMPLATE END */
