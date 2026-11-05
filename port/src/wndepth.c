#include "dw4/wndepth.h"
#include <math.h>
float dw4_wn_depth(float clip_z,float clip_w,float near_z,float far_z)
{
    float normalized=near_z+(clip_z/clip_w+1)*.5f*(far_z-near_z);
    return floorf((1-normalized)*65520.f);
}
