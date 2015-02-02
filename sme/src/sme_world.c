#include "sme_world.h"
#include "sme_sprite.h"

smeWorld* smeWORLD_Create()
{
    smeWorld* world = (smeWorld*)MEM_alloc(sizeof(smeWorld));
    world->Camera = NULL;
    world->Map = NULL;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    SYS_setVIntCallback(smeCAMERA_UpdateScrolling);
    smeSPRITES_Initialize();
    return world;
}

void smeWORLD_Destroy(smeWorld* world)
{
    smeSPRITES_Finalize();
    MEM_free(world);
}

void smeWORLD_LoadMap(smeWorld* world, smeMap* map, float position_x, float position_y)
{
    world->Map = map;
    smeMAP_Load(world->Map);
    world->Camera = smeCAMERA_Create(world->Map, position_x, position_y);
}

void smeWORLD_UnloadMap(smeWorld* world)
{
    smeMAP_Unload(world->Map);
    world->Map = NULL;
    smeCAMERA_Destroy(world->Camera);
    world->Camera = NULL;
}

void smeWORLD_Update(smeWorld* world, float position_x, float position_y, float smooth)
{
    if (world->Map!=NULL && world->Camera!=NULL)
    {
        smeSPRITES_Update(world);
        smeCAMERA_Update(world->Camera, world->Map, position_x, position_y, smooth);
    }
}
