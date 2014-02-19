#include "lcd_image.h"

//Start Screen Background
static lcd_image_t map_image = {"Fourele.lcd", 128, 160};

//Walk Mode Avatar Sprite (NEWS)
static lcd_image_t navatar_img = {"Navatar.lcd", 16, 16};
static lcd_image_t eavatar_img = {"Eavatar.lcd", 16, 16};
static lcd_image_t wavatar_img = {"Wavatar.lcd", 16, 16};
static lcd_image_t savatar_img = {"Savatar.lcd", 16, 16};

//Boss sprite (NEWS)
static lcd_image_t Nboss_img = {"Nboss.lcd", 16, 16};
static lcd_image_t Eboss_img = {"Eboss.lcd", 16, 16};
static lcd_image_t Wboss_img = {"Wboss.lcd", 16, 16};
static lcd_image_t Sboss_img = {"Sboss.lcd", 16, 16};


static lcd_image_t Grass_img = {"Grass.lcd", 16, 16};
static lcd_image_t NoGrass_img = {"NoGrass.lcd", 16, 16};

//Crystals
static lcd_image_t Items_img = {"Items.lcd", 16, 16};

//Explosion & Fire Spell
static lcd_image_t Xplo_img = {"xplo.lcd", 16, 16};

//Lives
static lcd_image_t Heart_img = {"Heart.lcd", 16, 16};

//Fight mode Avatar
static lcd_image_t AvBattle_img = {"AvBattle.lcd", 64, 64};

//Fight mode enemies LIGHT, FIRE, WATER, EARTH
static lcd_image_t Lmns_img = {"Lmns.lcd", 64, 64};
static lcd_image_t Fmns_img = {"Fmns.lcd", 64, 64};
static lcd_image_t Wmns_img = {"Wmns.lcd", 64, 64};
static lcd_image_t Emns_img = {"Emns.lcd", 64, 64};

//Spell Runes
static lcd_image_t Fire_img = {"Fire.lcd", 16, 16};
static lcd_image_t Earth_img = {"Earth.lcd", 16, 16};
static lcd_image_t Water_img = {"Water.lcd", 16, 16};
static lcd_image_t Light_img = {"Light.lcd", 16, 16};

//Boss Spell (Explo is used for Fire)
static lcd_image_t Wspell_img = {"Wspell.lcd", 16, 16};
static lcd_image_t Lspell_img = {"Lspell.lcd", 16, 16};
static lcd_image_t Espell_img = {"Espell.lcd", 16, 16};


