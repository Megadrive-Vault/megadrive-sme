#include "sme.h"
#include "resources.h"
#include "data.h"

int ANIM_ANGLES = 12;
Sprite sprites[2];
float position_x = 800.0f;
float position_y = 800.0f;
float roll = 0.0f;

int main(u16 hard)
{
    sme_Initialize(hard);
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    SYS_setVIntCallback(smeCAMERA_UpdateScrolling);
    
    SPR_init(256);
    SPR_initSprite(&sprites[0], &truck, 0, 0, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    VDP_setPalette(2, truck.palette->data);

    smeMAP_Load(&city);
    
    smeCamera camera;
    smeCAMERA_Initialize(&camera, &city, position_x, position_y);
    
    while (1)
    {
        u16 value = JOY_readJoypad(0);
        if (value&BUTTON_LEFT) roll -= 0.02f;
        if (value&BUTTON_RIGHT) roll += 0.02f;        
        if (roll<-PI) roll += 2.0f*PI;
        if (roll>PI) roll -= 2.0f*PI;
        float speed = 0.0f;
        if (value&BUTTON_UP) speed += 2.5f;
        if (value&BUTTON_DOWN) speed -= 2.5f;     
        
        float vec_x = sin(roll)*speed;
        float vec_y = -cos(roll)*speed;
        
        int censor = city.PlaneA->Physics[smeMOD((int)((position_y+vec_y)/8.0f), city.Height)*city.Width+smeMOD((int)((position_x+vec_x)/8.0f), city.Width)];
        if (censor!=0)
        {
            vec_x = 0.0f;
            vec_y = 0.0f;
        }
        
        position_x += vec_x;
        position_y += vec_y;
        
        int sp = (int)(roll*ANIM_ANGLES/PI);
        if (sp<0) { SPR_setAttribut(&sprites[0], TILE_ATTR(PAL2, 0, FALSE, TRUE)); sp = -sp; }
        else SPR_setAttribut(&sprites[0], TILE_ATTR(PAL2, 0, FALSE, FALSE));
        SPR_setAnim(&sprites[0], sp);
                
        if (speed<0.0f) speed = -speed;
        float smooth = 10.0f/(speed/2.0f+0.5f);
        smeCAMERA_Update(&camera, &city, position_x+vec_x*20.0f, position_y+vec_y*20.0f, smooth);
        
        SPR_setPosition(&sprites[0], position_x-camera.PositionX-16+screenWidth/2, position_y-camera.PositionY-16+screenHeight/2);
        SPR_update(sprites, 1);
    }
    
    smeMAP_Unload(&city);
    
    sme_Finalize();    
    return 0;
}
