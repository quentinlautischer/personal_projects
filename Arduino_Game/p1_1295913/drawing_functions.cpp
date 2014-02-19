#include "drawing_functions.h"
#include "definitions.h"
#include "lcd_image.h"

extern Adafruit_ST7735 tft;

//Draw block with color
void block_draw(int xpos, int ypos, int color){
    int i;
    for(i = 0; i < blocksize; i++){
        tft.drawRect(xpos*blocksize + i, ypos*blocksize + i, blocksize - i, blocksize - i, color);
    }}

//Draw block with image
void block_draw_sp(int xpos, int ypos, lcd_image_t *img){
    if(xpos < num_columns && ypos < num_rows && \
       xpos >= 0 && ypos >= 0){
	lcd_image_draw(img, &tft, 0, 0, xpos*blocksize, ypos*blocksize, 16, 16);
    }}

//Draw block with image. Check to see if avatar is hit by spell(Drawing)
void block_draw_spell(Coords *cc, int xpos, int ypos, lcd_image_t *img){
    //Ensure draw is within map limits
    if(xpos < num_columns && ypos < num_rows && \
       xpos >= 0 && ypos >= 0){
	lcd_image_draw(img, &tft, 0, 0, xpos*blocksize, ypos*blocksize, 16, 16);
	
	//If spell hits avatar. Draw flashing death animation and send lose game func.
	if(cc->avatar_xpos == xpos && cc->avatar_ypos == ypos){
	    for(int i = 0; i < 12; i++){
		block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, img);
		delay(50);
		block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &savatar_img);
		delay(50);
	    }
	    for(int i = 0; i < 4; i++){
		block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, img);
		delay(50);
	    }
	    fight_Lose();
	}
    }}

//Draw Avatar in fight mode
void draw_char(){
    lcd_image_draw(&AvBattle_img, &tft, 0,0, 128-64, 160-64, 64,64);}

//Draw Enemy in fight mode
void draw_enemy(lcd_image_t *img){
    lcd_image_draw(img, &tft, 0, 0, 0, 0, 64, 64);}

//Draw fight stage
int draw_fight_stage(){ int r, c;
    //Draw basic grass across screen
    for(r = 0; r < num_rows; r++){ // Rows
        for(c = 0; c < num_columns; c++){ 
            block_draw_sp(c, r, &NoGrass_img);
        }
    }
    
    //Spell Rune interface around borders
    //Elec Spell
    for(int i = num_columns-2; i>num_columns-5 ; i--){
        block_draw_sp(i, 0, &Light_img);
    }
    
    //Water Spell
    for(int i = 3; i < 6; i++){
        block_draw_sp(num_columns-1, i, &Water_img);
    }
    
    //Fire Spell
    for(int i = 1; i < 4; i++){
        block_draw_sp(i, 8, &Fire_img);
    }
    
    //Grass Spell
    for(int i = 4; i < 7; i++){
        block_draw_sp(0, i, &Earth_img);
    }
    
    draw_char();
    block_draw(4, 5, ST7735_BLACK);
    block_draw(5, 5, ST7735_BLACK);
    
    int element = random(1, 5); //Random Generation of Enemy
    Serial.print(element);
    if(element == 1){ //Fire Monster
        draw_enemy(&Fmns_img);
    }
    if(element == 2){ //Water Monster
        draw_enemy(&Wmns_img);
    }
    if(element == 3){ //Lightning Monster
        draw_enemy(&Lmns_img);
    }
    if(element == 4){ //Earth Monster
        draw_enemy(&Emns_img);
    }
    
    
    
    return element;}

//Draw Interface on bottom row.
void draw_interface(Coords *cc){
    for(int i = 0; i < num_columns; i++){
        block_draw(i, num_rows, ST7735_BLACK);
    }
    // Draw lives
    for(int i = 0; i < cc->life_Counter; i++){
        lcd_image_draw(&Heart_img, &tft, 0, 0, (i+1)*blocksize, num_rows*blocksize, 16, 16);
    }}

//Draw Walking mode map
void draw_Map(Coords *cc){
    int r, c, i;
    //Draw Long Grass and Short Grass
    for(r = 0; r < num_rows; r++){ // Rows
        for(c = 0; c < num_columns; c++){ //Columns
            if((cc->blockmap[r][c]) == 0){
                block_draw_sp(c, r, &Grass_img);
            } else {
                block_draw_sp(c, r, &NoGrass_img);
            }
	    
        }
    }
    //Draw Crystals at their locations if not already picked up
    for(i = 0; i < crystal_num; i++){
        if(cc->blockmap[cc->crystals[i][0]][cc->crystals[i][1]] == 0){
            block_draw_sp(cc->crystals[i][1], cc->crystals[i][0], &Items_img);
        } else { //Do nothing Grass is already there
        }   
    }
    draw_interface(cc);}











