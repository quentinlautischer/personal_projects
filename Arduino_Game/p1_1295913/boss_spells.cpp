#include "boss_spells.h"

//Lightning attack. * shaped attack. Quick and short.
void crack_attack(Coords *cc){
    int c = cc->boss_xpos;
    int r = cc->boss_ypos;
    int lazer_size = 2;
    int i = 1;
    
    mid_spell_move(cc, i);
    for(i = 1; i<lazer_size*2; i++){
	if(i == 1){
	    block_draw_spell(cc,c+1, r+1, &Lspell_img);
            block_draw_spell(cc,c-1, r+1, &Lspell_img);
            block_draw_spell(cc,c-1, r-1, &Lspell_img);
            block_draw_spell(cc,c+1, r-1, &Lspell_img);
            block_draw_spell(cc,c+1, r, &Lspell_img);
            block_draw_spell(cc,c-1, r, &Lspell_img);
	    
        }
        if(i == 2){
            for(int j = 2; j<4; j++){
		block_draw_spell(cc,c+j, r+j, &Lspell_img);
		block_draw_spell(cc,c-j, r+j, &Lspell_img);
		block_draw_spell(cc,c-j, r-j, &Lspell_img);
		block_draw_spell(cc,c+j, r-j, &Lspell_img);
		block_draw_spell(cc,c+j, r, &Lspell_img);
		block_draw_spell(cc,c-j, r, &Lspell_img);
		mid_spell_move(cc, i);
            }
	    
        }
        if(i == 3){
            block_draw_spell(cc,c+1, r+1, &NoGrass_img);
            block_draw_spell(cc,c-1, r+1, &NoGrass_img);
            block_draw_spell(cc,c-1, r-1, &NoGrass_img);
            block_draw_spell(cc,c+1, r-1, &NoGrass_img);
	    
            block_draw_spell(cc,c+1, r, &NoGrass_img);
            block_draw_spell(cc,c-1, r, &NoGrass_img);
            for(int j = 2; j<4; j++){
		block_draw_spell(cc,c+j, r+j, &NoGrass_img);
		block_draw_spell(cc,c-j, r+j, &NoGrass_img);
		block_draw_spell(cc,c-j, r-j, &NoGrass_img);
		block_draw_spell(cc,c+j, r-j, &NoGrass_img);
		block_draw_spell(cc,c+j, r, &NoGrass_img);    
		block_draw_spell(cc,c-j, r, &NoGrass_img);
		mid_spell_move(cc, i);
            }
        }
        mid_spell_move(cc, i);
    }
}

//Fire attack. + shaped attack. Slow but long.
void cross_attack(Coords *cc){
    int c = cc->boss_xpos;
    int r = cc->boss_ypos;
    int lazer_size = 2;
    int i = 0;
    
    mid_spell_move(cc, i);
    for(i = 0; i<lazer_size*3; i++){
        if(i < lazer_size*2){
	    block_draw_spell(cc,c, r+1+i, &Xplo_img);//bottom beam
	    block_draw_spell(cc,c, r-1-i, &Xplo_img);//top beam
	    block_draw_spell(cc,c+1+i, r, &Xplo_img);//right beam
	    block_draw_spell(cc,c-1-i, r, &Xplo_img);//left beam
        }
        if(i > lazer_size-1){
            block_draw_spell(cc,c, r+1+i-lazer_size, &NoGrass_img);//bottom beam
            block_draw_spell(cc,c, r-1-i+lazer_size, &NoGrass_img);//top beam
            block_draw_spell(cc,c+1+i-lazer_size, r, &NoGrass_img);//right beam
            block_draw_spell(cc,c-1-i+lazer_size, r, &NoGrass_img);//left beam
        }
	
        mid_spell_move(cc, i);
	
    }
}

//Earth attack. # shaped attack. Quick and Short.
void pillar_attack(Coords *cc){
    int c = cc->boss_xpos;
    int r = cc->boss_ypos;
    int lazer_size = 2;
    int i = 1;
    
    mid_spell_move(cc, i);
    for(i = 1; i<lazer_size*2; i++){
        if(i == 1){
            block_draw_spell(cc,c+1, r+1, &Espell_img);
            block_draw_spell(cc,c-1, r+1, &Espell_img);
            block_draw_spell(cc,c-1, r-1, &Espell_img);
            block_draw_spell(cc,c+1, r-1, &Espell_img);
        }
        if(i == 2){
            block_draw_spell(cc,c+2, r+2, &Espell_img);
            block_draw_spell(cc,c-2, r+2, &Espell_img);
            block_draw_spell(cc,c-2, r-2, &Espell_img);
            block_draw_spell(cc,c+2, r-2, &Espell_img);
            for(int j = 2; j<4; j++){
		block_draw_spell(cc,c+j, r+1, &Espell_img);
		block_draw_spell(cc,c-j, r-1, &Espell_img);
		block_draw_spell(cc,c-1, r+j, &Espell_img);
		block_draw_spell(cc,c+1, r-j, &Espell_img);
		
		block_draw_spell(cc,c-j, r+1, &Espell_img);
		block_draw_spell(cc,c+j, r-1, &Espell_img);
		block_draw_spell(cc,c-1, r-j, &Espell_img);
		block_draw_spell(cc,c+1, r+j, &Espell_img);
                mid_spell_move(cc, i);
            }
	    
        }
        if(i == 3){
            block_draw_spell(cc,c+1, r+1, &NoGrass_img);
            block_draw_spell(cc,c-1, r+1, &NoGrass_img);
            block_draw_spell(cc,c-1, r-1, &NoGrass_img);
            block_draw_spell(cc,c+1, r-1, &NoGrass_img);
            block_draw_spell(cc,c+2, r+2, &NoGrass_img);
            block_draw_spell(cc,c-2, r+2, &NoGrass_img);
            block_draw_spell(cc,c-2, r-2, &NoGrass_img);
            block_draw_spell(cc,c+2, r-2, &NoGrass_img);
            for(int j = 2; j<4; j++){
		block_draw_spell(cc,c+j, r+1, &NoGrass_img);
		block_draw_spell(cc,c-j, r-1, &NoGrass_img);
		block_draw_spell(cc,c-1, r+j, &NoGrass_img);
		block_draw_spell(cc,c+1, r-j, &NoGrass_img);
		
		block_draw_spell(cc,c-j, r+1, &NoGrass_img);
		block_draw_spell(cc,c+j, r-1, &NoGrass_img);
		block_draw_spell(cc,c-1, r-j, &NoGrass_img);
		block_draw_spell(cc,c+1, r+j, &NoGrass_img);
		mid_spell_move(cc, i);
            }
        }
	
        mid_spell_move(cc, i);
	
    }
}

//Water attack. = shaped attack. Slow but long.
void wall_attack(Coords *cc){
    int c = cc->boss_xpos;
    int r = cc->boss_ypos;
    int lazer_size = 2;
    int i = 1;
    
    mid_spell_move(cc, i);
    for(i = 1; i<lazer_size*4+1; i++){
	if(i < 8){
	    block_draw_spell(cc,c, r+i, &Wspell_img);
	    block_draw_spell(cc,c-1, r+i, &Wspell_img);
	    block_draw_spell(cc,c+1, r+i, &Wspell_img);
	    block_draw_spell(cc,c, r-i, &Wspell_img);
	    block_draw_spell(cc,c-1, r-i, &Wspell_img);
	    block_draw_spell(cc,c+1, r-i, &Wspell_img);
	    
	}
	if(i > 1){
	    block_draw_spell(cc,c, r+i-1, &NoGrass_img);
	    block_draw_spell(cc,c-1, r+i-1, &NoGrass_img);
	    block_draw_spell(cc,c+1, r+i-1, &NoGrass_img);
	    block_draw_spell(cc,c, r-i+1, &NoGrass_img);
	    block_draw_spell(cc,c-1, r-i+1, &NoGrass_img);
	    block_draw_spell(cc,c+1, r-i+1, &NoGrass_img);
	}
	
	mid_spell_move(cc, i);
	
    }
}

//Allow both avatar and boss to move during spell animations.
void mid_spell_move(Coords *cc, int i){
    avatar_move(cc->game_speed,cc);
    check_win(cc);
    if(i > 2){
        boss_Move(cc); 
        check_win(cc);
    }
    check_win(cc);
}
