#include "dw4/wnprojection.h"
#include "eefloat.h"
#include <stdint.h>
#include <string.h>
static uint32_t bits(float x){uint32_t b;memcpy(&b,&x,4);return b;}
static float number(uint32_t b){float x;memcpy(&x,&b,4);return x;}
void dw4_wn_projection_normalize(const float projection[16],float normalized[16])
{
    memcpy(normalized,projection,16*sizeof *normalized);
    /* The source upload computes 1/6 once, then multiplies only XY columns.
     * DIV's nearest reference result is 3e2aaaab; division of each coefficient
     * or normalization after projection changes the rounding boundaries. */
    for(unsigned row=0;row<4;row++)for(unsigned column=0;column<2;column++)
        normalized[row*4+column]=number(ee_f32_mul(bits(projection[row*4+column]),0x3e2aaaab));
}
void dw4_wn_projection_xy(const float camera[4],const float normalized[16],float xy[2])
{
    /* TRANS_MVPS_TEXTURE seeds ACC with the translation row, then accumulates
     * X/Y/Z. Keep each product and addition at the reference VU precision. */
    for(unsigned column=0;column<2;column++){
        uint32_t acc=ee_f32_mul(bits(normalized[12+column]),bits(camera[3]));
        for(unsigned row=0;row<3;row++)
            acc=ee_f32_add(acc,ee_f32_mul(bits(normalized[row*4+column]),bits(camera[row])));
        xy[column]=number(acc);
    }
}
float dw4_wn_viewport(float normalized,float clip_w,float dimension,float origin)
{
    uint32_t reciprocal=ee_f32_div(0x3f800000,bits(clip_w));
    /* VU constants are (1920,-1344) for the logical 640x448 viewport:
     * half the dimension, multiplied by the guard-band factor six. */
    uint32_t scaled=ee_f32_mul(ee_f32_mul(bits(dimension),0x40400000),reciprocal);
    uint32_t raw=ee_f32_add(bits(origin),ee_f32_mul(scaled,bits(normalized)));
    return (float)ee_f32_trunc_s32(ee_f32_mul(raw,0x41800000))/16;
}
