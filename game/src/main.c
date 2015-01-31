#include "sme.h"
#include "resources.h"
#include "data.h"

int VIEWPORT_WIDTH;
int VIEWPORT_HEIGHT;
int VIEWPORT_BORDER;

int ANIM_ANGLES = 12;

Sprite sprites[2];

float position_x = 800.0f;
float position_y = 800.0f;
float roll = 0.0f;
float camera_position_x = 0.0f;
float camera_position_y = 0.0f;

void vblank()
{
    VDP_setHorizontalScroll(PLAN_A, -(int)(camera_position_x-screenWidth/2));
    VDP_setHorizontalScroll(PLAN_B, -(int)(camera_position_x-screenWidth/2));
    VDP_setVerticalScroll(PLAN_A, (int)(camera_position_y-screenHeight/2));
    VDP_setVerticalScroll(PLAN_B, (int)(camera_position_y-screenHeight/2));      
}

int main(u16 hard)
{
    sme_Initialize(hard);
    
    VIEWPORT_BORDER = 2;
    VIEWPORT_WIDTH = screenWidth/8+VIEWPORT_BORDER*2;
    VIEWPORT_HEIGHT = screenHeight/8+VIEWPORT_BORDER*2;
    //MAP_WIDTH = 252;
    //MAP_HEIGHT = 252;
    
    SPR_init(256);
    SPR_initSprite(&sprites[0], &truck, 0, 0, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    VDP_setPalette(2, truck.palette->data);

    smeMAP_Load(&city);
    
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    
    camera_position_x = position_x;
    camera_position_y = position_y;
    
    smeMAP_Update(&city, (int)(camera_position_x/8-screenWidth/16-VIEWPORT_BORDER), (int)(camera_position_y/8-screenHeight/16-VIEWPORT_BORDER), VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    SYS_setVIntCallback(vblank);
    
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
        
        
        int old_place_x = (int)(camera_position_x/8);
        int old_place_y = (int)(camera_position_y/8);
        
        if (speed<0.0f) speed = -speed;
        float smooth = 10.0f/(speed/2.0f+0.5f);
        camera_position_x = (camera_position_x*smooth+(position_x+vec_x*20.0f))/(smooth+1.0f);
        camera_position_y = (camera_position_y*smooth+(position_y+vec_y*20.0f))/(smooth+1.0f);
        int place_x = (int)(camera_position_x/8);
        int place_y = (int)(camera_position_y/8);
                
        SPR_setPosition(&sprites[0], position_x-camera_position_x-16+screenWidth/2, position_y-camera_position_y-16+screenHeight/2);
        SPR_update(sprites, 1);
        
        int px = place_x-screenWidth/16-VIEWPORT_BORDER;
        int py = place_y-screenHeight/16-VIEWPORT_BORDER;
        
        if (place_x>old_place_x)
            smeMAP_Update(&city, px+VIEWPORT_WIDTH-1, py, VIEWPORT_BORDER, VIEWPORT_HEIGHT);
        else if (place_x<old_place_x)
            smeMAP_Update(&city, px, py, VIEWPORT_BORDER, VIEWPORT_HEIGHT);
        
        if (place_y>old_place_y)
            smeMAP_Update(&city, px, py+VIEWPORT_HEIGHT-1, VIEWPORT_WIDTH, VIEWPORT_BORDER);
        else if (place_y<old_place_y)
            smeMAP_Update(&city, px, py, VIEWPORT_WIDTH, VIEWPORT_BORDER);
    }
    
    smeMAP_Unload(&city);
    
    sme_Finalize();    
    return 0;
}
