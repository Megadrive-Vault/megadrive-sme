#include "sme_map.h"
#include "sme_maths.h"
#include "sme_vdp.h"

void slice(int* ms, int* ps, int* count, int mx, int px, int s, int m_max, int p_max)
{
    // check breaks with each maximum
    int breaks[3];
    int breaks_count = 0;
    
    {
        // check map maximum
        int out = mx+s-m_max;
        if (out>0)
        {
            breaks[0] = s-out;
            ++breaks_count;
        }
    
        // check plan maximum
        out = px+s-p_max;
        if (out>0)
        {
            int b = s-out;
            if (breaks_count==0 || breaks[0]<b)
            {
                breaks[breaks_count] = b;
                ++breaks_count;
            }
            else if (breaks[0]!=b)
            {
                int t = breaks[0];
                breaks[0] = b;
                breaks[1] = t;
                ++breaks_count;
            }        
        }
    
        // add final break if required
        if (breaks_count==0 || breaks[breaks_count-1]!=s)
        {
            breaks[breaks_count] = s;
            ++breaks_count;
        }
    }
    
    // create drawing points
    int i;
    *count = breaks_count*2;
    
    ms[0] = mx;
    ps[0] = px;
    ms[1] = breaks[0];
    ps[1] = breaks[0];
    
    for (i=1 ; i<breaks_count ; ++i)
    {
        ms[i*2] = smeMOD(mx+breaks[i-1], m_max);
        ps[i*2] = smeMOD(px+breaks[i-1], p_max);
        ms[i*2+1] = breaks[i]-breaks[i-1];
        ps[i*2+1] = breaks[i]-breaks[i-1];
    }
}

void smeMAP_Update(smeMap* map, int x, int y, int w, int h)
{
    int mx = smeMOD(x, map->Width);
    int my = smeMOD(y, map->Height);
    int px = smeMOD(x, smePLAN_WIDTH);
    int py = smeMOD(y, smePLAN_HEIGHT);
    
    int mxs[6];
    int pxs[6];    
    int nx = 0;
    slice(mxs, pxs, &nx, mx, px, w, map->Width, smePLAN_WIDTH);
    
    int mys[6];
    int pys[6];    
    int ny = 0;
    slice(mys, pys, &ny, my, py, h, map->Height, smePLAN_HEIGHT);
    
    int i, j;
    for (j=0 ; j<ny ; j+=2)
    {
        int hs = pys[j+1];
        for (i=0 ; i<nx ; i+=2)
        {
            int ws = pxs[i+1];
            VDP_setMapEx(VDP_PLAN_A, map->PlaneA.Data, TILE_ATTR(0, 0, 0, 0), pxs[i], pys[j], mxs[i], mys[j], ws, hs); 
            VDP_setMapEx(VDP_PLAN_B, map->PlaneB.Data, TILE_ATTR(0, 1, 0, 0), pxs[i], pys[j], mxs[i], mys[j], ws, hs); 
        }
    }
}
