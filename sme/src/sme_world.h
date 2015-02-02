#ifndef _SME_WORLD_H_
#define _SME_WORLD_H_

#include "genesis.h"
#include "sme_camera.h"

typedef struct
{
    smeCamera* Camera;
    smeMap* Map;
} smeWorld;

smeWorld* smeWORLD_Create();
void smeWORLD_Destroy(smeWorld* world);
void smeWORLD_LoadMap(smeWorld* world, smeMap* map, float position_x, float position_y);
void smeWORLD_UnloadMap(smeWorld* world);
void smeWORLD_Update(smeWorld* world, float position_x, float position_y, float smooth);

#endif
