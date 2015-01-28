#include "sme.h"

void sme_Initialize(u16 hard)
{
    if (hard==0)
    {
        // handle reset
    }
    
    smeVDP_Initialize();
}

void sme_Finalize()
{
    smeVDP_Finalize();
}

