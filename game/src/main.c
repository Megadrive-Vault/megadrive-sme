#include "sme.h"
#include "resources.h"
#include "data.h"

int ANIM_ANGLES = 12;
Sprite sprites[2];
float roll = 0.0f;

int main(u16 hard)
{
    sme_Initialize(hard);
    
    smeWorld* world = smeWORLD_Create();
    smeWORLD_LoadMap(world, &city, 800.0f, 800.0f);
    
    VDP_setPalette(2, truck.palette->data);

    smeSprite* car = smeSPRITE_Create(world, 800.0f, 800.0f, &truck, PAL2, 0, FALSE);
    
    while (1)
    {
        u16 value = JOY_readJoypad(0);
        if (value&BUTTON_LEFT) roll -= 0.03f;
        if (value&BUTTON_RIGHT) roll += 0.03f;        
        if (roll<-PI) roll += 2.0f*PI;
        if (roll>PI) roll -= 2.0f*PI;
        float speed = 0.0f;
        if (value&BUTTON_UP) speed += 2.5f;
        if (value&BUTTON_DOWN) speed -= 2.5f;     
        
        float vec_x = sin(roll)*speed;
        float vec_y = -cos(roll)*speed;
        
        int censor = city.PlaneA->Physics[smeMOD((int)((car->PositionY+vec_y)/8.0f), city.Height)*city.Width+smeMOD((int)((car->PositionX+vec_x)/8.0f), city.Width)];
        if (censor!=0)
        {
            vec_x = 0.0f;
            vec_y = 0.0f;
        }
        
        car->PositionX += vec_x;
        car->PositionY += vec_y;
        
        int animation = (int)(roll*ANIM_ANGLES/PI);
        if (animation<0) { car->Mirrored = TRUE; animation = -animation; }
        else car->Mirrored = FALSE;
        car->Animation = animation;
                
        if (speed<0.0f) speed = -speed;
        float smooth = 10.0f/(speed/2.0f+0.5f);
        
        smeWORLD_Update(world, car->PositionX+vec_x*20.0f, car->PositionY+vec_y*20.0f, smooth);
    }
    
    smeWORLD_UnloadMap(world);
    smeWORLD_Destroy(world);
    
    sme_Finalize();    
    return 0;
}
