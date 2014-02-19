#ifndef _DRAWING_FUNCTIONS_H
#define _DRAWING_FUNCTIONS_H

#include "functions.h"

//Draw block with color
void block_draw(int xpos, int ypos, int color);

//Draw block with image
void block_draw_sp(int xpos, int ypos, lcd_image_t *img);

//Draw block with image. Check to see if avatar is hit by spell(Drawing)
void block_draw_spell(Coords *cc, int xpos, int ypos, lcd_image_t *img);

//Draw Avatar in fight mode
void draw_char();

//Draw Enemy in fight mode
void draw_enemy(lcd_image_t *img);

//Draw fight stage
int draw_fight_stage();

//Draw interface on bottom row
void draw_interface(Coords *cc);

//Draw Walking mode map
void draw_Map(Coords *cc);

#endif 