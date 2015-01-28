#ifndef _SME_BITMAP_H_
#define _SME_BITMAP_H_

#include "genesis.h"

typedef struct
{
    const u8* PhysicsTiles;
    const u8* PhysicsMap;
    const u8* GraphicsTiles;
    const u8* GraphicsMap;
    const u16* GraphicsPalette;
    TileSet* Tiles;
    Map* Data;
} smePlane;

typedef struct
{
    int Width;
    int Height;
    smePlane PlaneA;
    smePlane PlaneB;    
} smeMap;

void smeMAP_Update(smeMap* map, int x, int y, int w, int h);

#endif
