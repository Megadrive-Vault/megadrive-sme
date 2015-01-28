#include "sme_maths.h"

float cos(float a)
{
    int v = (int)(a*512.0f/PI);
    if (v<0) v += 1024;
    return ((int)cosFix32(v))/1024.0f;
}

float sin(float a)
{
    int v = (int)(a*512.0f/PI);
    if (v<0) v += 1024;
    return ((int)sinFix32(v))/1024.0f;
}
