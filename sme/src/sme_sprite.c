#include "sme_sprite.h"
#include "sme_world.h"

#define smeSPRITE_MAXIMUM_COUNT   40

#define VISIBILITY_ALWAYS_FLAG  0x40000000
#define VISIBILITY_ALWAYS_ON    (VISIBILITY_ALWAYS_FLAG | 0x3FFFFFFF)
#define VISIBILITY_ALWAYS_OFF   (VISIBILITY_ALWAYS_FLAG | 0x00000000)

smeSprite** smeSprites;
Sprite* graphicsSprites;
int smeSpritesCount = 0;

void smeSPRITES_Initialize()
{
    SPR_init(smeSPRITE_MAXIMUM_COUNT);
    smeSprites = (smeSprite**)MEM_alloc(sizeof(smeSprite*)*smeSPRITE_MAXIMUM_COUNT);
    graphicsSprites = (Sprite*)MEM_alloc(sizeof(Sprite)*smeSPRITE_MAXIMUM_COUNT);
    
    int i;
    for (i=0 ; i<smeSPRITE_MAXIMUM_COUNT ; ++i)
        graphicsSprites[i].visibility = VISIBILITY_ALWAYS_OFF;
}

void smeSPRITES_Finalize()
{
    MEM_free(graphicsSprites);
    MEM_free(smeSprites);
}

void smeSPRITES_Update(smeWorld* world)
{
    int i;
    for (i=0 ; i<smeSpritesCount ; ++i)
        smeSPRITE_Update(world, smeSprites[i]);
    SPR_update(graphicsSprites, smeSpritesCount);
}

smeSprite* smeSPRITE_Create(smeWorld* world, float position_x, float position_y, const SpriteDefinition* graphics, int palette, int animation, int mirrored)
{
    if (smeSpritesCount>=smeSPRITE_MAXIMUM_COUNT)
        return NULL;
    
    smeSprite* sprite = (smeSprite*)MEM_alloc(sizeof(smeSprite));
    sprite->ID = smeSpritesCount;
    sprite->PositionX = position_x;
    sprite->PositionY = position_y;
    sprite->Graphics = (SpriteDefinition*)graphics;
    sprite->Palette = palette;
    sprite->Animation = animation;
    sprite->Mirrored = mirrored;
    
    SPR_initSprite(&graphicsSprites[smeSpritesCount], sprite->Graphics, 
        sprite->PositionX-world->Camera->PositionX-16+screenWidth/2,
        sprite->PositionY-world->Camera->PositionY-16+screenHeight/2,
        TILE_ATTR(sprite->Palette, 0, FALSE, sprite->Mirrored));
    SPR_setAnim(&graphicsSprites[smeSpritesCount], sprite->Animation);

    smeSprites[smeSpritesCount++] = sprite;
    return sprite;
}

void smeSPRITE_Destroy(smeWorld* world, smeSprite* sprite)
{
    --smeSpritesCount;
    int i;
    for (i=sprite->ID ; i<smeSpritesCount ; ++i)
    {
        smeSprites[i] = smeSprites[i+1];
        smeSprites[i]->ID = i;
        graphicsSprites[i] = graphicsSprites[i+1];
        graphicsSprites[i].visibility = -1;
    }
    graphicsSprites[i].visibility = VISIBILITY_ALWAYS_OFF;
    MEM_free(sprite);
}

void smeSPRITE_Update(smeWorld* world, smeSprite* sprite)
{
    SPR_setAttribut(&graphicsSprites[sprite->ID], TILE_ATTR(sprite->Palette, 0, FALSE, sprite->Mirrored));
    SPR_setAnim(&graphicsSprites[sprite->ID], sprite->Animation);
    SPR_setPosition(&graphicsSprites[sprite->ID],
        sprite->PositionX-world->Camera->PositionX-16+screenWidth/2,
        sprite->PositionY-world->Camera->PositionY-16+screenHeight/2);
}
