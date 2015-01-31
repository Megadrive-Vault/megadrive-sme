#ifndef _SME_MAP_H_
#define _SME_MAP_H_

#include "genesis.h"

typedef struct
{
    const u8* Physics;
    const u8* Graphics;
    const u16* Palette;
    TileSet* Tiles;
    Map* Data;
} smePlane;

typedef struct
{
    int Width;
    int Height;
    const u8* Solids;
    smePlane* PlaneA;
    smePlane* PlaneB;    
} smeMap;

void smeMAP_Load(smeMap* map);
void smeMAP_Unload(smeMap* map);
void smeMAP_Update(smeMap* map, int x, int y, int w, int h);

#endif
