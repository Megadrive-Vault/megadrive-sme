#ifndef _SME_SPRITE_H_
#define _SME_SPRITE_H_

#include "genesis.h"
#include "sme_world.h"

typedef struct
{
    int ID;
    float PositionX;
    float PositionY;
    SpriteDefinition* Graphics;
    int Palette;
    int Animation;
    int Mirrored;
} smeSprite;

void smeSPRITES_Initialize();
void smeSPRITES_Finalize();
void smeSPRITES_Update(smeWorld* world);

smeSprite* smeSPRITE_Create(smeWorld* world, float position_x, float position_y, const SpriteDefinition* graphics, int palette, int animation, int mirrored);
void smeSPRITE_Destroy(smeWorld* world, smeSprite* sprite);
void smeSPRITE_Update(smeWorld* world, smeSprite* sprite);

#endif
