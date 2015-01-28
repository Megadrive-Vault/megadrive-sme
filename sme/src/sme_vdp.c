#include "sme_vdp.h"

int smePLAN_WIDTH;
int smePLAN_HEIGHT;

void smeVDP_Initialize()
{
    VDP_init();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);
    VDP_setScreenWidth320(); 
    
    smePLAN_WIDTH = VDP_getPlanWidth();
    smePLAN_HEIGHT = VDP_getPlanHeight();
}

void smeVDP_Finalize()
{
}

void smeVDP_SetScrollMode(u8 horizontal, u8 vertical)
{
    VDP_setReg(0x0b, horizontal|vertical);
} 

