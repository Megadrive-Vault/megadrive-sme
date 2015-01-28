#ifndef _SME_VDP_H_
#define _SME_VDP_H_

#include "genesis.h"

void smeVDP_Initialize();
void smeVDP_Finalize();

#define smeVDP_HSCROLL_Plane  0
#define smeVDP_HSCROLL_Row    2
#define smeVDP_HSCROLL_Line   3
#define smeVDP_VSCROLL_Plane  0
#define smeVDP_VSCROLL_Column 4

void smeVDP_SetScrollMode(u8 horizontal, u8 vertical);

extern int smePLAN_WIDTH;
extern int smePLAN_HEIGHT;

#endif
