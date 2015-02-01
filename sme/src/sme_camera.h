#ifndef _SME_CAMERA_H_
#define _SME_CAMERA_H_

#include "genesis.h"
#include "sme_map.h"

typedef struct
{
    float PositionX;
    float PositionY;
    int ViewportWidth;
    int ViewportHeight;
    int ViewportBorder;
} smeCamera;

void smeCAMERA_Initialize(smeCamera* camera, smeMap* map, float position_x, float position_y);
void smeCAMERA_Update(smeCamera* camera, smeMap* map, float position_x, float position_y, float smooth);
void smeCAMERA_UpdateScrolling();

#endif
