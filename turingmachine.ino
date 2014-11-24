
/*
**
**	Turing Machine Model 1
**	Zafar Iqbal <mail@zaf.io>
**	September 2014
**
*/


// Include the relevant neopixel library
#include <Adafruit_NeoPixel.h>

// Init the neopixel sub system
// We'll be using the 24 pixel ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel( 24 , 7 , NEO_GRB + NEO_KHZ800);

// Buzzer
int buzzerPin = 12;

// Left, Right, Run/Stop, Toggle Buttons
int buttonLeftPin = 11;
int buttonRunStopPin = 10;
int buttonRightPin = 9;
int buttonTogglePin = 8;

// Neo Pixel
int ringPin = 7;
int brightness = 64 ;

// Speed potentiometer
int speedPin = A7;

// Being lazy and not having to declare it every time
// Don't know if this is wise or not
int i = 0 ;


/*
**	Audio Code
*/

int sfxTickDuration = 5;
int sfxHaltDuration = 1000 ;

void sfxTickRight(){
  tone(buzzerPin,1000,sfxTickDuration);
}

void sfxTickLeft(){
  tone(buzzerPin,1100,sfxTickDuration);
}

void sfxHalt(){
  tone(buzzerPin,400,sfxHaltDuration);
}

/*
**	Strip data structure and related functions
*/

// Total slots on strip
int stripTotal = 24 ;

// Array to hold data (Zeros or Ones)
int stripData [ 24 ] ;

// Init strip to zeros
void stripInit ( ) {
 
  for ( i = 0 ; i < stripTotal ; i++ ) {

	stripData [ i ] = 0 ;    
    
  }

}

// Get data at specific position
int stripGet ( int p ) {

	return ( stripData [ p ] ) ;

}

// Set strip data at specific point
int stripSet ( int p , int s ) {

	stripData [ p ] = s ;

}

// Toggle strip data at specific point
void stripToggle ( int p ) {

	if ( stripGet( p ) == 0 ) {

		stripSet( p , 1 ) ;

	} else {

		stripSet( p , 0 ) ;

	}

}

// Put Zeros in all slots on strip
// And update display
void stripClear( ) {

 for ( i = 0 ; i < stripTotal ; i++ ) {

	stripData [ i ] = 0 ;    

  }

  displayUpdate( );

}

// Put Ones in all slots on strip
// And update display
void stripFill( ) {

	for ( i = 0 ; i < stripTotal ; i++ ) {

		stripData [ i ] = 1 ;    

	}

  	displayUpdate( ) ;

}

// Fill slots with random data
// And update display
void stripRandom( ) {

	randomSeed( analogRead( 0 ) ) ;

	for ( i = 0 ; i < stripTotal ; i++ ) {

		stripData [ i ] = random( 0 , 2 ) ;    

  	}

  	displayUpdate();

}

// Flip strip data
// And update display
void stripFlip( ) {

	for ( i = 0 ; i < stripTotal ; i++ ) {

		if ( stripData [ i ] == 0 ) {

			stripData [ i ] = 1 ;    

 		} else {

		stripData [ i ] = 0 ;    

 		}

  	}

	displayUpdate( ) ;

}

/*
**	Head Code
*/

// Starting head postion
// Note it does not start at 0 or 23
int headPos = 22 ;

// Head cursor flash variables
unsigned int headTick = 0 ;
int headVisualStatus = 1 ;

// Brightness of head pixel
int headBrightness = 128;

// Show head pixel on display 
void headDisplayOn( ) {

	displaySet( headPos , 0 , 0 , headBrightness );

}


// Switch off head pixel on display 
// Note handling of strip data
void headDisplayOff( ) {


	if( stripGet ( headPos ) == 0 ) {

		displaySet( headPos , 0 , 0 , 0 ) ;

	} else {

		displaySet( headPos , brightness , brightness , brightness ) ;

	}


}

// Mimic flashing head cursor
void headUpdate( ) {


	headTick++;

	if( ( headTick % 2000 ) == 0 ) {

		if( headVisualStatus == 1 ) {

			headDisplayOff( ) ;

		} else {

			headDisplayOn( ) ;
		}

		headVisualStatus *= -1 ;

	}
		
}

// Move head right (clockwise)
void headMoveRight( ) {

	headDisplayOff( ) ;
	headPos++ ;

	if( headPos == stripTotal ) headPos = 0 ;

	headDisplayOn( ) ;
	sfxTickRight( ) ;

}

// Move head right (anti-clockwise)
void headMoveLeft( ) {

	headDisplayOff( ) ;

	headPos-- ;	

	if( headPos == -1 ) headPos = stripTotal - 1 ;

	if( headPos > stripTotal ) headPos=stripTotal - 1 ;

	headDisplayOn( ) ;

	sfxTickLeft( ) ;

}

// Get head position
int headGetPos( ) {

	return( headPos ) ;
	
}
/*
**	Machine Code :)
*/

// Heartbeat tracking variables
unsigned int machineTick = 0 ;
int machineRunning = -1;

// Variables to hold previous states of buttons
int lastbuttonRunStopPin = HIGH;
int lastbuttonTogglePin = HIGH;
int lastbuttonRightPin = HIGH;
int lastbuttonLeftPin = HIGH;

// MAchine speed
int speedVal = 0;

// Data coming in from serial
String inData;

// Machine update
void machineUpdate( ) {

	machineTick++;

	// Output hearbeat
	if( ( machineTick % 10000 ) == 0 ) {

		Serial.print( "@" ) ;
		Serial.println( machineTick ) ;

	}

	// Read from serial for remote commands
	if( ( machineTick % 10 ) == 0 ) {

		// Keep reading from serial if data available
    	while( Serial.available( ) > 0 ) {

	        char recieved = Serial.read( ) ;
	        inData += recieved ; 

	        // is last byte a newline?
	        if ( recieved == '\n' ) {

	        	// If payload equals 61 bytes assume code load
	            if( inData.length( ) == 61 ) {

	            	machineRunning = -1 ;
	            	codeHaltSet( 1 ) ;
	            	codeReset( );
	            	codeProgram( inData ) ;
	            	sfxHalt( ) ;

	            }   

	            // RUN command
	            if( inData == "RUN\n" ) { 

	            	machineRunning = 1 ;
	            	codeReset( ) ;
	            	codeHaltSet( 0 ) ;

	            }

	            // STOP command
	            if( inData == "STOP\n" ) {

	            	machineRunning = 0 ;
	            	codeReset( ) ;
	            	codeHaltSet( 1 ) ;

	            }                  

	            // CLEAR command
	            if( inData == "CLEAR\n" ) {

	            	stripClear( ) ;

	            }

	           	// FILL Command 
	            if( inData == "FILL\n" ) {

	            	stripFill( ) ;

	            }

	           	// RANDOM data load command
	            if( inData == "RANDOM\n" ) {

	            	stripRandom( ) ;

	            }

	            // FLIP data command
	            if( inData == "FLIP\n" ) {

	            	stripFlip();

	            }                                                           

	            inData = "";

	        }

	    }	

	    // Set speed accoriding potentiometer reading
		speedVal = map( analogRead( speedPin ) , 0 , 1023 , 1000 , 0 ) ;

		// RUN/STOP button handling
		i = digitalRead( buttonRunStopPin ) ;

		if( i == LOW ) {

			if( lastbuttonRunStopPin == HIGH ) {

				Serial.println( "buttonRunStopPin" ) ;
				machineRunning *= -1 ;

				if( machineRunning == 1 ) codeHaltSet( 0 ) ;

				codeReset( ) ;

			}

		}

		lastbuttonRunStopPin = i;


		// Is machine idle?
		if( machineRunning == -1 ) {

			// Toggle button handling
			i = digitalRead( buttonTogglePin ) ;

			if( i == LOW ) {

				if( lastbuttonTogglePin == HIGH ) {

					stripToggle( headGetPos( ) ) ;

				}

			}

			lastbuttonTogglePin = i;		


			// Left button handling
			i = digitalRead( buttonLeftPin ) ;

			if( i == LOW ) {

				if( lastbuttonLeftPin == HIGH ) {

					headMoveLeft( ) ;

					if( lastbuttonTogglePin == LOW ) {

						stripToggle( headGetPos( ) ) ;

					}

				}

			}

			lastbuttonLeftPin = i ;		

			// Right button handling
			i = digitalRead( buttonRightPin ) ;

			if( i == LOW ) {

				if( lastbuttonRightPin == HIGH ) {

					headMoveRight( );

					if( lastbuttonTogglePin == LOW ) {

						stripToggle( headGetPos( ) ) ;

					}

				}

			}

			lastbuttonRightPin = i ;		

		}

	}
	
}

// Stop machine
void machineStop( ) {

	machineRunning=-1;
	
}

/*
**	Program encoding and execution
*/

// Halt flag
int codeHalt = 0 ;

// Code position
int codeLine = 0 ;
int codePoint = 0 ;

int codeSet = 0 ;

// Code execution speed
unsigned int codeTick = 0 ;

// Example programs

// TOGGLER
char codeString [ 61 ] = "000111011100000000000000000000000000000000000000000000000000" ;

// MUNCHER
//char codeString [ 61 ] = "000000000000000000000000000000000000000000000000000000000000" ;

// PINGPONG
//char codeString [ 61 ] = "000111011100000000000000000000000000000000000000000000000000" ;

// Program execution
void codeUpdate( ) {

	codeTick++ ;

	// Is machine running?
	if( codeTick >= speedVal && codeHalt == 0 && machineRunning == 1 ) {

		// Find code block
		codePoint = codeLine * 6;

		// If data read is One then jump to next instruction
		if( stripGet( headGetPos( ) ) == 1 ) {

			codePoint += 3 ;

		}

		// Set/Reset logic
		if( codeString[ codePoint ] == '0' ) {

			stripSet( headGetPos( ) , 0 ) ;

		} else {

			stripSet( headGetPos( ) , 1 ) ;

		}

		// Move left right logic
		if( codeString[ codePoint + 1 ] == '0' ) {

			headMoveRight( ) ;

		} else {

			headMoveLeft( ) ;

		}

		// Halt & Next instruction logic
		if( codeString[ codePoint + 2 ] == 'H' ) {

			//codeHalt=1;
			machineStop( ) ;
			codeHalt = 1 ;
			codeReset( ) ;
			sfxHalt( ) ;

		} else {

			codeLine = codeString[ codePoint + 2 ] - 48 ;

		}

		codeTick = 0;

	}

}

// Code reset to start
void codeReset( ) {

	codeLine = 0 ;

}

// Set Halt status
void codeHaltSet( int v ) {

	codeHalt = v ;

}

// Set program
void codeProgram(String s){

	s.toCharArray( codeString , 60 ) ;
	
}

/*
**	Display code
*/

// Update display
void displayUpdate( ) {

	for ( i = 0 ; i < 24 ; i++ ) {

		if ( stripData [ i ] == 0 ) {

			pixels.setPixelColor ( i , pixels.Color ( 0 , 0 , 0 ) ) ;

		} else {

			pixels.setPixelColor ( i , pixels.Color ( brightness , brightness  , brightness ) ) ;

		}

	}

	pixels.show( ) ;

}

// Set a specific pixel to some colour
void displaySet ( int p , int r , int g , int b ) {
	
	pixels.setPixelColor ( p , r , g , b );
	pixels.show( ) ;

}
/*
**	Main Setup & Loop
*/

void setup( ) {

	Serial.begin(9600);

	pinMode( buttonRunStopPin , INPUT_PULLUP ) ;
	pinMode( buttonTogglePin , INPUT_PULLUP ) ;
	pinMode( buttonRightPin , INPUT_PULLUP ) ;
	pinMode( buttonLeftPin , INPUT_PULLUP ) ;

	pixels.begin ( ) ;
	stripInit ( ) ;
	displayUpdate ( ) ;

	sfxHalt( ) ;
  
}

void loop() {

	machineUpdate( ) ;
	headUpdate( ) ;
	codeUpdate( ) ;
  
}

