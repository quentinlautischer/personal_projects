/* Quentin & Stefan Throne of the Elements Project */
/* MAIN FUNCTION */

#include <Arduino.h>
#include <SD.h>
#include "definitions.h"
#include "functions.h"
#include "drawing_functions.h"

Sd2Card card;
extern Adafruit_ST7735 tft;

//Generates a seed for Random.
uint16_t get_seed(){
    uint16_t seed = 0;
    for (int i=0; i<16; i++) {
        seed = seed << 1;
        seed = seed ^ analogRead(7);
        delay(1);
    }
    return seed;
}

void setup(){
    //Initialize Serial and Pins
    Serial.begin(9600);
    pinMode(JOYSTICK_BUTTON,INPUT);
    digitalWrite(JOYSTICK_BUTTON,HIGH);
    
    //Initialize Structure Variable
    Coords cc;
    
    //Initialize Map Array all to 0. Which indicates long grass & uncollected crystals.
    int r, c, i;
    for(r = 0; r < num_rows; r++){ // Rows
        for(c = 0; c < num_columns; c++){ //Columns
            cc.blockmap[r][c] = 0; //ALL ZEROS //[Rows][Columns]
        }
    }
    
    //Init Random seed.
    randomSeed(get_seed());
    
    //Generate Crystals crystals will be assigned a location on the map.
    for(i = 0; i < crystal_num; i++){
        cc.crystals[i][0] = random(num_rows-2); // -2 b/c crystals cant be on last row
        cc.crystals[i][1] = random(num_columns-1);
    }
    
    //Avatar Starting position
    cc.avatar_xpos = num_columns/2;
    cc.avatar_ypos = num_rows-1;
    cc.blockmap[cc.avatar_ypos][cc.avatar_xpos] = 1; //Ensures placement is in short grass.
        
    //Initialize SD Card
    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
        Serial.println("failed!");
        return;
    }
    Serial.println("OK!");
    
    //Initialize RAW SD
    Serial.print("Raw SD Initialization ...");
    if (!card.init(SPI_HALF_SPEED, SD_CS)){
        Serial.println("failed");
        return;
    }
    Serial.println("SD Raw OK!");

    //Init Struct Address
    Coords *coords = &cc;
    
    start_Menu(coords);
    
    walk_Mode(coords);
    
}

void loop(){}





