#ifndef _BOSS_SPELLS_H
#define _BOSS_SPELLS_H

#include "functions.h"
#include "drawing_functions.h"

//Lightning attack. * shaped attack. Quick and short.
void crack_attack(Coords *cc);

//Fire attack. + shaped attack. Slow but long.
void cross_attack(Coords *cc);

//Earth attack. # shaped attack. Quick and Short.
void pillar_attack(Coords *cc);

//Water attack. = shaped attack. Slow but long.
void wall_attack(Coords *cc);

//Allow both avatar and boss to move during spell animations.
void mid_spell_move(Coords *cc, int i);

#endif