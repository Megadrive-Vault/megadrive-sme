#ifndef _SME_H_
#define _SME_H_

#include "sme_sound.h"
#include "sme_screen.h"

void sme_Init(u16 hard);
void sme_Exit();

#define smeMOD(a, b)  ((a) % (b) + (b)) % (b)

#endif
