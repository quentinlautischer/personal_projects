#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H


// standard U of A library settings, assuming Atmel Mega SPI pin         
#define SD_CS    5  // Chip select line for SD card                    
#define TFT_CS   6  // Chip select line for TFT display                
#define TFT_DC   7  // Data/command line for TFT                    
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)

// Joystick pins:
#define JOYSTICK_HORIZ 0 // Analog input A0 - horizontal
#define JOYSTICK_VERT 1 // Analog input A1 - vertical
#define JOYSTICK_BUTTON 9 // Digitial input pin 9 for the button
#define JOY_OFFSET 30 //joystick offset
#define hor_rest 506  //Joystick default readings
#define vert_rest 515

#define blocksize 16 //size of drawn blocks 16pixels
#define crystal_num  3 //Number of crystals
#define num_columns 8 //Number of columns
#define num_rows 9 //Number of Rows
#define Spawn_Chance 15 // 15% chance of fight spawn.


#endif