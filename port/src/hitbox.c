#include "dw4/hitbox.h"
#include "eefloat.h"
#include <string.h>
static ee_f32 bits(float f){ee_f32 u;memcpy(&u,&f,4);return u;}
static float value(ee_f32 u){float f;memcpy(&f,&u,4);return f;}
void dw4_hitbox_center(const float box[6],float center[3])
{
    for(unsigned i=0;i<3;i++)center[i]=value(ee_f32_add(ee_f32_mul(0x3f000000,bits(box[i])),ee_f32_mul(0x3f000000,bits(box[3+i]))));
}
void dw4_hitbox_transform(float box[6],const float matrix[16])
{
    ee_f32 lo[3],span[3],m[16],p[8][3],edge[3][3],base[4];
    for(unsigned i=0;i<16;i++)m[i]=bits(matrix[i]);
    if(ee_f32_cmp(bits(box[0]),bits(box[3]))>0)return;
    for(unsigned i=0;i<3;i++){lo[i]=bits(box[i]);span[i]=ee_f32_sub(bits(box[i+3]),lo[i]);}
    for(unsigned i=0;i<4;i++) {
        ee_f32 sum=ee_f32_add(ee_f32_mul(lo[0],m[i]),ee_f32_mul(lo[1],m[4+i]));
        sum=ee_f32_add(sum,ee_f32_mul(lo[2],m[8+i]));base[i]=ee_f32_add(m[12+i],sum);
    }
    /* 192fc0 preserves signed W unless its magnitude is below epsilon. */
    if(ee_f32_cmp(base[3],0x3f800000)) {
        ee_f32 w=ee_f32_cmp(base[3]&0x7fffffff,0x350637bd)<0?0x350637bd:base[3];
        ee_f32 inverse=ee_f32_div(0x3f800000,w);
        for(unsigned i=0;i<3;i++)base[i]=ee_f32_mul(base[i],inverse);
    }
    for(unsigned i=0;i<3;i++) {
        for(unsigned axis=0;axis<3;axis++)edge[axis][i]=ee_f32_mul(span[axis],m[axis*4+i]);
        p[0][i]=base[i];p[1][i]=ee_f32_add(base[i],edge[2][i]);p[2][i]=ee_f32_add(base[i],edge[1][i]);
        p[3][i]=ee_f32_add(base[i],edge[0][i]);p[4][i]=ee_f32_add(p[2][i],edge[2][i]);
        p[5][i]=ee_f32_add(p[3][i],edge[1][i]);p[6][i]=ee_f32_add(p[3][i],edge[2][i]);
        p[7][i]=ee_f32_add(p[5][i],edge[2][i]);
        ee_f32 min=0x7f7fffff,max=0xff7fffff;
        for(unsigned j=0;j<8;j++){if(ee_f32_cmp(p[j][i],min)<0)min=p[j][i];if(ee_f32_cmp(max,p[j][i])<0)max=p[j][i];}
        box[i]=value(min);box[3+i]=value(max);
    }
}
void dw4_hitbox_fixed_world(const float local[6],const float matrix[16],float world[6])
{
    float centre[3],transformed[3];dw4_hitbox_center(local,centre);
    memcpy(world,local,6*sizeof(float));dw4_hitbox_transform(world,matrix);dw4_hitbox_center(world,transformed);
    for(unsigned i=0;i<3;i++) {
        ee_f32 negative=ee_f32_sub(bits(centre[i]),bits(local[i]))&0x7fffffff;
        ee_f32 positive=ee_f32_sub(bits(local[3+i]),bits(centre[i]))&0x7fffffff;
        world[i]=value(ee_f32_sub(bits(transformed[i]),negative));world[3+i]=value(ee_f32_add(bits(transformed[i]),positive));
    }
}
int dw4_hitbox_intersects(const float a[6],const float b[6])
{
    for(unsigned i=0;i<3;i++)if(ee_f32_cmp(bits(b[i]),bits(a[3+i]))>0 || ee_f32_cmp(bits(a[i]),bits(b[3+i]))>0)return 0;
    return 1;
}
void dw4_hitbox_talk_probe(const float matrix[16],float world[6])
{
    const float offset[6]={0,4,7,0,4,7};float transformed[6],centre[3];memcpy(transformed,offset,sizeof transformed);
    dw4_hitbox_transform(transformed,matrix);dw4_hitbox_center(transformed,centre);
    for(unsigned i=0;i<3;i++){world[i]=value(ee_f32_sub(bits(centre[i]),0x3fc00000));world[3+i]=value(ee_f32_add(bits(centre[i]),0x3fc00000));}
}
void dw4_hitbox_bullet(const float matrix[16],const float offset[3],const float size[3],float world[6])
{
    float transformed[6],centre[3];
    memcpy(transformed,offset,3*sizeof(float));memcpy(transformed+3,offset,3*sizeof(float));
    dw4_hitbox_transform(transformed,matrix);dw4_hitbox_center(transformed,centre);
    for(unsigned i=0;i<3;i++){
        ee_f32 half=ee_f32_mul(bits(size[i]),0x3f000000);
        world[i]=value(ee_f32_sub(bits(centre[i]),half));world[3+i]=value(ee_f32_add(bits(centre[i]),half));
    }
}
