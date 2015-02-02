#include "sme_camera.h"
#include "sme_vdp.h"

smeCamera* _Camera = NULL;

smeCamera* smeCAMERA_Create(smeMap* map, float position_x, float position_y)
{
    smeCamera* camera = (smeCamera*)MEM_alloc(sizeof(smeCamera));
    camera->ViewportBorder = 2;
    camera->ViewportWidth = screenWidth/8+camera->ViewportBorder*2;
    camera->ViewportHeight = screenHeight/8+camera->ViewportBorder*2;
    camera->PositionX = position_x;
    camera->PositionY = position_y;
    
    smeMAP_Render(map, (int)(camera->PositionX/8-screenWidth/16-camera->ViewportBorder),
        (int)(camera->PositionY/8-screenHeight/16-camera->ViewportBorder),
        camera->ViewportWidth, camera->ViewportHeight);
        
    _Camera = camera;
    return camera;
}

void smeCAMERA_Destroy(smeCamera* camera)
{
    MEM_free(camera);
    _Camera = NULL;
}

void smeCAMERA_Update(smeCamera* camera, smeMap* map, float position_x, float position_y, float smooth)
{
    int old_place_x = (int)(camera->PositionX/8);
    int old_place_y = (int)(camera->PositionY/8);
    
    camera->PositionX = (camera->PositionX*smooth+position_x)/(smooth+1.0f);
    camera->PositionY = (camera->PositionY*smooth+position_y)/(smooth+1.0f);
    
    int place_x = (int)(camera->PositionX/8);
    int place_y = (int)(camera->PositionY/8);
    int px = place_x-screenWidth/16-camera->ViewportBorder;
    int py = place_y-screenHeight/16-camera->ViewportBorder;
    
    if (place_x>old_place_x)
        smeMAP_Render(map, px+camera->ViewportWidth-1, py, camera->ViewportBorder, camera->ViewportHeight);
    else if (place_x<old_place_x)
        smeMAP_Render(map, px, py, camera->ViewportBorder, camera->ViewportHeight);
    
    if (place_y>old_place_y)
        smeMAP_Render(map, px, py+camera->ViewportHeight-1, camera->ViewportWidth, camera->ViewportBorder);
    else if (place_y<old_place_y)
        smeMAP_Render(map, px, py, camera->ViewportWidth, camera->ViewportBorder);
}

void smeCAMERA_UpdateScrolling()
{
    if (_Camera!=NULL)
    {
        VDP_setHorizontalScroll(PLAN_A, -(int)(_Camera->PositionX-screenWidth/2));
        VDP_setHorizontalScroll(PLAN_B, -(int)(_Camera->PositionX-screenWidth/2));
        VDP_setVerticalScroll(PLAN_A, (int)(_Camera->PositionY-screenHeight/2));
        VDP_setVerticalScroll(PLAN_B, (int)(_Camera->PositionY-screenHeight/2));  
    }
}
