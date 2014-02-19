#include "functions.h"
#include "drawing_functions.h"
#include "boss_spells.h"

Adafruit_ST7735 tft  = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//Enables movement of avatar if Joystick receives input.
void avatar_move(int speed, Coords *cc){
    int direction;
    direction = joy_Move();
    cursor_Move(direction, speed, cc);}

//Timer that counts down from value of i
void battle_countdown(float i){ tft.setCursor(64, 80);   
    tft.setTextSize(1);
    tft.setTextColor(ST7735_WHITE);
    tft.print(i);
    delay(5);
    tft.setCursor(64, 80);
    tft.setTextColor(ST7735_BLACK);
    tft.print(i);}

//Graphic Animation of Boss Entrance
void boss_entrance_animation(Coords *cc){
    // Boss comes crashing in
    for(int m = 0; m < 6; m++){
        block_draw_sp(6, m, &Sboss_img);
        block_draw_sp(6, m-1, &Sboss_img);
        block_draw_sp(6, m-2, &NoGrass_img);
        delay(20);
    }
    block_draw_sp(6, 4, &NoGrass_img);
    block_draw_sp(6, 5, &Wboss_img);
    
    //Explosion Wipes away all grass
    int c = num_columns-3;
    int r = num_rows/2;  //-1
    int j = 1;
    
    block_draw_sp(c+2, r+1, &Xplo_img);
    for(int i = 0; i < 6; i++){
        for(int j =0; j < 3+(2*i); j++){
	    block_draw_sp(c-i+j, r-i, &Xplo_img);
	    block_draw_sp(c-i+j, r+2+i, &Xplo_img);
	    block_draw_sp(c-i, r-j, &Xplo_img);
	    block_draw_sp(c-i, r+j, &Xplo_img);
	    block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &eavatar_img); //Un-Erase Avatar
        }
    }

    //Reducing lives to 1.
    while(cc->life_Counter != 1){
	cc->life_Counter = cc->life_Counter - 1;
	block_draw(cc->life_Counter+1, num_rows, ST7735_BLACK);
    }
    
    //Short Grass is re-displayed after the explosion
    block_draw_sp(c+2, r+1, &NoGrass_img);
    for(int i = 0; i < 6; i++){
        for(int j =0; j < 3+(2*i); j++){
	    block_draw_sp(c-i+j, r-i, &NoGrass_img);
	    block_draw_sp(c-i+j, r+2+i, &NoGrass_img);
	    block_draw_sp(c-i, r-j, &NoGrass_img);
	    block_draw_sp(c-i, r+j, &NoGrass_img);
	    block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &eavatar_img); //Un-Erase Avatar
        }
    }
    
    //Assigns the Entire map as short grass (No Fight Spawns during Boss Fight)
    int y, x;
    for(y = 0; y < num_rows; y++){ // Rows
        for(x = 0; x < num_columns; x++){ //Columns
            cc->blockmap[y][x] = 1; //ALL ZEROS //[Rows][Columns]
        }
    }

    //Ensure Boss is still drawn at his location
    block_draw_sp(6, 5, &Wboss_img);
    cc->boss_xpos = 6;
    cc->boss_ypos = 5;
    
    //player walks to select position
    walk_to_postion(cc, 1, 5);}

//3rd Game Mode. Contains loop for Boss Fight.
void boss_Mode(Coords *cc){
    //Draws Next Spell on interface bar.
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(40, 150);
    tft.setTextSize(1);
    tft.println("Next Spell:");
    
    //Refresh RandomSeed
    randomSeed(get_seed());
    
    //Main Loop
    while(1){
        //Boss Moves at Random
        boss_Move(cc);
        choose_boss_att(cc);
        //Player Moves
        avatar_move(cc->game_speed,cc);
        check_win(cc);
    }
}

//Using Random, moves boss to a neighboring block
void boss_Move(Coords *cc){
    /*Random direction is selected. As long as the Direction is within the map limits
      boss will move in that direction and in his prev. location grass is replaced*/
    
    int direction = random(1,5);
    
    if((direction == 3) && (cc->boss_xpos != 0)){
        cc->boss_xpos = cc->boss_xpos - 1;
        block_draw_sp(cc->boss_xpos, cc->boss_ypos, &Wboss_img);
        block_draw_sp(cc->boss_xpos + 1, cc->boss_ypos, &NoGrass_img);
    }
    
    if((direction == 1) && (cc->boss_xpos != num_columns-1)){
        cc->boss_xpos = cc->boss_xpos + 1;
        block_draw_sp(cc->boss_xpos, cc->boss_ypos, &Eboss_img);
        block_draw_sp(cc->boss_xpos - 1, cc->boss_ypos, &NoGrass_img);
    }
    
    if((direction == 2) && (cc->boss_ypos != 0)){
        cc->boss_ypos = cc->boss_ypos - 1;
        block_draw_sp(cc->boss_xpos, cc->boss_ypos, &Nboss_img);
        block_draw_sp(cc->boss_xpos, cc->boss_ypos+1, &NoGrass_img);
    }
    
    if((direction == 4) && (cc->boss_ypos != num_rows-1)){
        cc->boss_ypos = cc->boss_ypos + 1;
        block_draw_sp(cc->boss_xpos, cc->boss_ypos, &Sboss_img);
        block_draw_sp(cc->boss_xpos, cc->boss_ypos-1, &NoGrass_img);
    }
    
    delay(cc->game_speed);}

/* Checks if Player has beat the boss(This is achieved by stepping on boss)
   If player has won. Small flash animation visually indicates win. Followed by
   the You Win Screen. */
void check_win(Coords *cc){
    if(cc->avatar_xpos == cc->boss_xpos && cc->avatar_ypos == cc->boss_ypos){
        for(int i = 0; i < 12; i++){
	    block_draw_sp(cc->boss_xpos, cc->boss_ypos, &Sboss_img);
	    delay(50);
	    block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &savatar_img);
	    delay(50);
        }
        for(int i = 0; i < 4; i++){
	    block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &savatar_img);
	    delay(50);
        }
        
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(5, 103);
        tft.setTextSize(2);
        tft.println("YOU WIN");
        tft.setTextSize(1);
        tft.println("Thanks for Playing");
        delay(5000000);
    }}

//Using Random, chooses from 4 boss attacks. Loads them into a buffer. Where the last spell is chosen.
void choose_boss_att(Coords *cc){ 
    
    int choice = random(1,5);
    cc->att_choice[0] = cc->att_choice[1]; //Current spell is next spell
    cc->att_choice[1] = choice; //Next spell choice

    //Next Spell is indicated with its Icon in the corner of the interface bar.
    if(cc->att_choice[1] == 1){
        lcd_image_draw(&Xplo_img, &tft, 0, 0, (num_columns-1)*blocksize, num_rows*blocksize, 16, 16);
    }
    if(cc->att_choice[1] == 2){
        lcd_image_draw(&Wspell_img, &tft, 0, 0, (num_columns-1)*blocksize, num_rows*blocksize, 16, 16);
    }
    if(cc->att_choice[1] == 3){
	lcd_image_draw(&Lspell_img, &tft, 0, 0, (num_columns-1)*blocksize, num_rows*blocksize, 16, 16);
    }
    if(cc->att_choice[1] == 4){
        lcd_image_draw(&Espell_img, &tft, 0, 0, (num_columns-1)*blocksize, num_rows*blocksize, 16, 16);
    }
    
    //Current Spell is executed
    if(cc->att_choice[0] == 1){
        cross_attack(cc);
    }
    if(cc->att_choice[0] == 2){
        wall_attack(cc);
    }
    if(cc->att_choice[0] == 3){
        crack_attack(cc);
    }
    if(cc->att_choice[0] == 4){
        pillar_attack(cc);
    }}

//Checks if all crystals have been retrieved. Returns 1 if true. Returns 0 if false.
int crystal_check(Coords *cc){
    int i;
    for(i = 0; i < crystal_num; i++){
        if(cc->blockmap[cc->crystals[i][0]][cc->crystals[i][1]] == 0){
            return 0;
        }
    } 
    return 1;}

//Takes input direction and moves avatar on map accordingly. Checks for Fight Spawn
void cursor_Move(int direction, int speed, Coords *cc){
    if(cc->blockmap[cc->avatar_ypos][cc->avatar_xpos] == 1){ //Short Grass: Nothing happens
    } else {
        //Set Long Grass to short grass
        cc->blockmap[cc->avatar_ypos][cc->avatar_xpos] = 1;
        //Chance at Fight
        if(random(100) < Spawn_Chance){
            fight_Mode(cc);
            draw_Map(cc);
            direction = 0;
            block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &savatar_img);
        }
    }
    
    //Move Avatar and replace grass in his wake.
    if((direction == 3) && (cc->avatar_xpos != 0)){
        cc->avatar_xpos = cc->avatar_xpos - 1;
        block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &wavatar_img);
        block_draw_sp(cc->avatar_xpos + 1, cc->avatar_ypos, &NoGrass_img);
    }
    
    if((direction == 1) && (cc->avatar_xpos != num_columns-1)){
        cc->avatar_xpos = cc->avatar_xpos + 1;
        block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &eavatar_img);
        block_draw_sp(cc->avatar_xpos - 1, cc->avatar_ypos, &NoGrass_img);
    }
    
    if((direction == 2) && (cc->avatar_ypos != 0)){
        cc->avatar_ypos = cc->avatar_ypos - 1;
        block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &navatar_img);
        block_draw_sp(cc->avatar_xpos, cc->avatar_ypos+1, &NoGrass_img);
    }
    
    if((direction == 4) && (cc->avatar_ypos != num_rows-1)){
        cc->avatar_ypos = cc->avatar_ypos + 1;
        block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &savatar_img);
        block_draw_sp(cc->avatar_xpos, cc->avatar_ypos-1, &NoGrass_img);
    }
    
    delay(speed);}

//Game Over Screen.
void fight_Lose(){tft.fillScreen(ST7735_RED);
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(15, 60);
    tft.setTextSize(2);
    tft.println("You Lose");
    tft.setTextSize(1);
    tft.setCursor(25, 77);
    tft.print("(Press Reset)");
    // Infinite Delay
    delay(5000000); }

//2nd Gamemode. Long Grass Battle loop.
void fight_Mode(Coords *cc){
    //Draw Fight Mode
    int element = draw_fight_stage();
    delay(200);
    int direction = 0;
    //For loop through the countdown time
    for(float i = cc->countdown; i > 0; i = i - 0.01){
        direction = joy_Move();
        //If correct spell chosen return to WalkMode, lose .5 on countdown tho.
        if(element == direction){
            direction = 0;
            element = 0;
            if(cc->countdown > 0.48){//Insane
		cc->countdown = cc->countdown - 0.48;
	    } else {
                cc->countdown = 0.05;
            }
            return; 
	    //If time runs low, lose a life.
        } else if(i < 0.02){
            cc->life_Counter = cc->life_Counter - 1;
            block_draw(cc->life_Counter+1, num_rows, ST7735_BLACK);
            if(cc->life_Counter == 0){ // if no life left lose.
                break;
            }
            i = 2.0;
            delay(500);
            continue;
	    //If no joystick input is made continue the for loop (Display timer)
	} else if(direction == 0) {
	    battle_countdown(i);
	    //Else triggers if wrong spell is chosen. Lose a life.
        } else {
            cc->life_Counter = cc->life_Counter - 1;
            block_draw(cc->life_Counter+1, num_rows, ST7735_BLACK);
            if(cc->life_Counter == 0){
                break;
            }
            delay(500);
            continue;
        }
    }
    fight_Lose();}

//Returns a value based on Joystick direction. (ENWS = 1234)
int joy_Move(){
    
    //Joystick variables
    int vert_analog;
    int hor_analog;
    vert_analog = analogRead(JOYSTICK_VERT);
    hor_analog = analogRead(JOYSTICK_HORIZ);
    
    //Reads Joystick return appropriate value.
    if(hor_analog > (hor_rest +JOY_OFFSET)){return 1;}
    if(hor_analog < (hor_rest -JOY_OFFSET)){return 3;}
    if(vert_analog < (vert_rest -JOY_OFFSET)){return 2;}
    if(vert_analog > (vert_rest +JOY_OFFSET)){return 4;}
    else{ return 0;}}

//Allows user to scroll through the game difficulty menu.
int scroll_menu(int scroll){
    
    //Up
    if(joy_Move() == 2){
        if(scroll-1 < 0){
            scroll = 2;
        } else{
	    scroll = (scroll-1)%3;
        }
    }
    //Down
    if(joy_Move() == 4){
        scroll = (scroll+1)%3;
    }
    
    //Redisplay menu with new Highlight
    if(scroll == 0){
	tft.setTextColor(ST7735_YELLOW);
	tft.setCursor(5, 103);
	tft.setTextSize(2);
	tft.println("Easy");
	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(5, 118);
	tft.setTextSize(2);
	tft.println("Hard");
	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(4, 133);
	tft.setTextSize(2);
	tft.println("Insane");
    }
    
    //Redisplay menu with new Highlight
    if(scroll == 1){
	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(5, 103);
	tft.setTextSize(2);
	tft.println("Easy");
	tft.setTextColor(ST7735_YELLOW);
	tft.setCursor(5, 118);
	tft.setTextSize(2);
	tft.println("Hard");
	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(4, 133);
	tft.setTextSize(2);
	tft.println("Insane");
    }
    
    //Redisplay menu with new Highlight
    if(scroll == 2){
	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(5, 103);
	tft.setTextSize(2);
	tft.println("Easy");
	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(5, 118);
	tft.setTextSize(2);
	tft.println("Hard");
	tft.setTextColor(ST7735_YELLOW);
	tft.setCursor(4, 133);
	tft.setTextSize(2);
	tft.println("Insane");
    }
    
    delay(200);
    return scroll;}

//Start Menu Prints Title and Gamemodes.
void start_Menu(Coords *cc){//Initialize LCD
    tft.initR(INITR_BLACKTAB);
    int gamemode = 1;
    lcd_image_draw(&map_image, &tft, 0, 0, 0, 0, 128, 160);
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(10, 0);
    tft.setTextSize(2);
    tft.println("Throne of");
    tft.setCursor(15, 15);
    tft.println("Elements");
    
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(5, 103);
    tft.setTextSize(2);
    tft.println("Easy");
    tft.setCursor(5, 118);
    tft.setTextSize(2); 
    tft.println("Hard");
    tft.setCursor(4, 133);
    tft.setTextSize(2);
    tft.println("Insane");
    
    tft.setTextSize(1);
    tft.setCursor(15, 150);
    tft.print("(Press to Begin)");   
    
    //Allows Gamemode Scroll until joystick is clicked.
    while(digitalRead(JOYSTICK_BUTTON) != 0){
        gamemode = scroll_menu(gamemode);
    } 
    cc->gamemode = gamemode;
    
    //Game Mode variable assignments 
    if(gamemode == 0){ //Easy
        cc->countdown = 10;
        cc->life_Counter =3;
        cc->game_speed = 200;
    }
    if(gamemode == 1){ //Hard
        cc->countdown = 3;
        cc->life_Counter =3;
        cc->game_speed = 100;
    }
    if(gamemode == 2){ //Insane
        cc->countdown = 2;
        cc->life_Counter =3;
        cc->game_speed = 10;
    }}

//1st Gamemode. Walking through grass collecting crystals loop.
void walk_Mode(Coords *cc){int direction;
    draw_Map(cc);
    block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &savatar_img);
    
    //Loop for walking around until all crystals are collected.
    while(1){
	direction = joy_Move();
	cursor_Move(direction, 250, cc);
	if(crystal_check(cc) == 1){
	    boss_entrance_animation(cc);
	    boss_Mode(cc);
        }
    }}

//Walks Avatar to position that is input.
void walk_to_postion(Coords *cc, int xpos, int ypos){
    int direction = 0;
    //Loops until at desired location
    while((cc->avatar_xpos != xpos)){
        if(cc->avatar_xpos < xpos){
            direction = 1;
            cursor_Move(direction, 250, cc);
        }
        if(cc->avatar_xpos > xpos){
            direction = 3;
            cursor_Move(direction, 250, cc);
        }
    }
    while((cc->avatar_ypos != ypos)){
        if(cc->avatar_ypos < ypos){
            direction = 4;
            cursor_Move(direction, 250, cc);
        }
        if(cc->avatar_ypos > ypos){
            direction = 2;
            cursor_Move(direction, 250, cc);
        }
    }    
    block_draw_sp(cc->avatar_xpos, cc->avatar_ypos, &eavatar_img);
    delay(200);}





