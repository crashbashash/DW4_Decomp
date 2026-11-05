/* ParticleArray::update (3a3c10): authored polynomial coefficients, seconds.
 * EE operations truncate after each multiply/add, including t*t. */
#ifndef DW4_LOBBYPARTICLE_H
#define DW4_LOBBYPARTICLE_H
#include "eefloat.h"
#include <string.h>
static inline float lobby_particle_curve(float a,float b,float c,float time)
{
    ee_f32 av,bv,cv,tv;float result;
    memcpy(&av,&a,4);memcpy(&bv,&b,4);memcpy(&cv,&c,4);memcpy(&tv,&time,4);
    ee_f32 value=ee_f32_add(ee_f32_add(av,ee_f32_mul(bv,tv)),ee_f32_mul(cv,ee_f32_mul(tv,tv)));
    memcpy(&result,&value,4);return result;
}
static inline unsigned lobby_particle_color(float value,int alpha)
{
    if(value<0) value=0;
    if(value>1) value=1;
    ee_f32 bits;memcpy(&bits,&value,4);
    unsigned packed=(unsigned)ee_f32_trunc_s32(ee_f32_add(ee_f32_mul(bits,0x437f0000),0x3f000000));
    return alpha?(packed+1)/2:packed;
}
#endif
