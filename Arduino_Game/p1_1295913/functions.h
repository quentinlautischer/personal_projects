#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "definitions.h"
#include "lcd_image.h"
#include "images.h"
 
typedef struct{
    //map array
    int blockmap[num_rows][num_columns]; //[Rows][Columns]

    //Avatar & Boss Position
    int avatar_xpos;
    int avatar_ypos;
	int boss_xpos;
    int boss_ypos; 

    //Crystal Locations   
    int crystals[crystal_num][1]; //Each crystal has a location

    //Gamemode Variables
    int gamemode;
    float countdown;
    int game_speed;
    int life_Counter;

    //Boss spell buffer array
    int att_choice[1];

} Coords;

//Enables movement of avatar if Joystick receives input.
void avatar_move(int speed, Coords *cc);

//Timer that counts down from value of i
void battle_countdown(float i);

//Graphic Animation of Boss Entrance
void boss_entrance_animation(Coords *cc);

//3rd Game Mode. Contains loop for Boss Fight.
void boss_Mode(Coords *cc);

//Using Random, moves boss to a neighboring block
void boss_Move(Coords *cc);

//Checks if Player has beat the boss(This is achieved by stepping on boss)
void check_win(Coords *cc);

//Using Random, chooses from 4 boss attacks. Loads them into a buffer. Where the last spell is chosen.
void choose_boss_att(Coords *cc);

//Checks if all crystals have been retrieved. Returns 1 if true. Returns 0 if false.
int crystal_check(Coords *cc);

//Takes input direction and moves avatar on map accordingly. Checks for Fight Spawn
void cursor_Move(int direction, int speed, Coords *cc);

//Game Over Screen
void fight_Lose();

//2nd Gamemode. Long Grass Battle loop.
void fight_Mode(Coords *cc);

//Returns Values (1234) based on joystick movement (ENWS)
int joy_Move();

//Allows user to scroll through the game difficulty menu.
int scroll_menu(int gamemode);

//Start Menu Prints Title and Gamemodes.
void start_Menu(Coords *cc);

//1st Gamemode. Walking through grass collecting crystals loop.
void walk_Mode(Coords *cc);

//Walks Avatar to position that is input.
void walk_to_postion(Coords *cc, int xpos, int ypos);

//Generates a Seed to be used in RandomSeed()
uint16_t get_seed();

#endif