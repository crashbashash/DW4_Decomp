/* GS ALPHA applies alpha once; a ZMSK glow tests depth without occluding later geometry. */
#include "dw4/render.h"
#include "../src/lobbyclip.h"
#include "../src/lobbyfade.h"
#include "../src/lobbyparticle.h"
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
static dw4_layer_draw tri(const dw4_tex *tex, float z)
{
    dw4_layer_draw d = {0};
    const float v[3][5] = {{0,0,0,0,1},{8,0,0,0,1},{0,8,0,0,1}};
    memcpy(d.v,v,sizeof v); memset(d.rgba,128,sizeof d.rgba);
    d.tex=tex; d.aref=12; d.straight_rgb=1;
    d.z[0]=d.z[1]=d.z[2]=z;
    return d;
}
int main(void)
{
    assert(lobby_particle_curve(1,1,-2,.5f)==1);
    assert(lobby_particle_curve(1,.5f,-1,.5f)==1);
    assert(lobby_particle_curve(0,8,-5,.5f)==2.75f);
    assert(lobby_particle_color(lobby_particle_curve(1,1,-2,.7007936f),0)==183);
    assert(lobby_particle_color(lobby_particle_curve(1,.5f,-1,.7007936f),1)==110);
    float input[3][10]={{0,0,0,0},{12,0,30,3},{0,12,15,1.5f}},output[5][10];
    unsigned depth_count=lobby_clip_depth(input,10,20,output);
    assert(depth_count==5);
    for(unsigned i=0;i<depth_count;i++) {
        assert(output[i][2]>=10 && output[i][2]<=20);
        assert(fabsf(output[i][3]-.1f*output[i][2])<.00001f);
    }
    dw4_fb fb;
    uint8_t half[] = {200,100,40,64}, red[] = {240,0,0,128};
    dw4_tex a={.rgba=half,.w=1,.h=1}, b={.rgba=red,.w=1,.h=1};
    dw4_layer_draw draws[2];
    /* Running-game FADESET checkpoints, independent of nominal tick ratios. */
    lobby_fade fade;lobby_fade_start(&fade,1,0x42480000,0);
    lobby_fade_tick(&fade,0);assert(fade.value==0x3ca3d70a);
    lobby_fade_tick(&fade,20185088);assert(fade.value==0x3d35223c);
    lobby_fade_tick(&fade,33292288);assert(fade.value==0x3d758ee8);
    lobby_fade_tick(&fade,33292288);assert(fade.value==0x3d758ee8);
    assert(!dw4_fb_init(&fb,8,8));
    draws[0]=tri(&a,100); draws[0].blend=1;
    dw4_fb_clear(&fb,20,20,20); dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);
    unsigned pixel=4*(1*8+1);
    assert(fb.rgba[pixel]==110 && fb.rgba[pixel+1]==60 && fb.rgba[pixel+2]==30);
    draws[0].blend=0;
    dw4_fb_clear(&fb,20,20,20); dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);
    assert(fb.rgba[pixel]==200); /* opaque ignores alpha after the alpha test */
    draws[0].blend=2; draws[0].no_depth_write=1;
    draws[1]=tri(&b,50);
    dw4_fb_clear(&fb,20,20,20); dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,2,4);
    assert(fb.rgba[pixel]==240 && fb.rgba[pixel+1]==0);
    draws[0].no_depth_write=0;
    dw4_fb_clear(&fb,20,20,20); dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,2,1);
    assert(fb.rgba[pixel]==120 && fb.rgba[pixel+1]==70); /* nearer glow blocked the red */
    draws[0]=tri(&b,100); draws[0].fog=2;
    draws[0].fog_color[0]=0; draws[0].fog_color[1]=25; draws[0].fog_color[2]=63;
    draws[0].f[0]=draws[0].f[1]=draws[0].f[2]=0;
    dw4_fb_clear(&fb,20,20,20); dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);
    assert(fb.rgba[pixel]==0 && fb.rgba[pixel+1]==25 && fb.rgba[pixel+2]==63);
    /* GS linear fractions have four bits; each axis truncates separately.
     * wx=5, wy=11: rows 32 and 154, final sample 115. */
    uint8_t grid[]={1,1,1,128,101,101,101,128,201,201,201,128,51,51,51,128};
    dw4_tex filtered={.rgba=grid,.w=2,.h=2};
    draws[0]=tri(&filtered,100);draws[0].gs_raster=1;
    for(unsigned e=0;e<3;e++) {draws[0].v[e][2]=.43f;draws[0].v[e][3]=.62f;}
    int old_linear=dw4_render_tex_linear;dw4_render_tex_linear=1;
    dw4_fb_clear(&fb,20,20,20);dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);assert(fb.rgba[pixel]==115);
    for(unsigned e=0;e<3;e++) memset(draws[0].rgba[e],65,3);
    draws[0].fog=2;memcpy(draws[0].fog_color,(uint8_t[]){25,25,63},3);
    for(unsigned e=0;e<3;e++) draws[0].f[e]=255;
    dw4_fb_clear(&fb,20,20,20);dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);
    assert(fb.rgba[pixel]==57 && fb.rgba[pixel+2]==58);
    draws[0].blend=1;for(unsigned e=0;e<3;e++) draws[0].rgba[e][3]=64;
    dw4_fb_clear(&fb,20,20,20);dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);assert(fb.rgba[pixel]==38);
    dw4_render_tex_linear=old_linear;
    draws[0]=tri(&b,100);draws[0].gs_raster=1;
    for(unsigned e=0;e<3;e++) {draws[0].v[e][0]+=.25f;draws[0].v[e][1]+=.25f;}
    dw4_fb_clear(&fb,20,20,20);dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,1,1);
    assert(fb.rgba[0]==20 && fb.rgba[pixel]==240); /* integer samples, not +0.5 */
    /* Shared diagonal: translucent triangles must cover every pixel once.
     * Reverse winding and banded replay must retain the same coverage. */
    draws[0]=tri(&a,100);draws[0].gs_raster=1;draws[0].blend=1;
    draws[1]=draws[0];
    memcpy(draws[1].v[0],(float[5]){8,8,0,0,1},sizeof draws[1].v[0]);
    memcpy(draws[1].v[1],(float[5]){0,8,0,0,1},sizeof draws[1].v[1]);
    memcpy(draws[1].v[2],(float[5]){8,0,0,0,1},sizeof draws[1].v[2]);
    dw4_fb_clear(&fb,20,20,20);dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,2,1);
    for(unsigned p=0;p<64;p++) assert(fb.rgba[4*p]==110 && fb.rgba[4*p+1]==60);
    for(unsigned i=0;i<2;i++) {
        float swap[5];memcpy(swap,draws[i].v[1],sizeof swap);
        memcpy(draws[i].v[1],draws[i].v[2],sizeof swap);memcpy(draws[i].v[2],swap,sizeof swap);
    }
    dw4_fb_clear(&fb,20,20,20);dw4_render_zbuf_clear(&fb);
    dw4_render_layer_draws(&fb,draws,2,4);
    for(unsigned p=0;p<64;p++) assert(fb.rgba[4*p]==110);
    dw4_layer_draw clipped[5];
    draws[0]=tri(&b,100);draws[0].v[0][0]=-1000000;draws[0].v[0][1]=-1000000;
    draws[0].v[1][0]=1000000;draws[0].v[2][1]=1000000;
    unsigned count=lobby_clip_screen(draws,8,8,clipped);
    assert(count && count<=5);
    for(unsigned i=0;i<count;i++) for(unsigned e=0;e<3;e++) {
        assert(clipped[i].v[e][0]>=0 && clipped[i].v[e][0]<=8);
        assert(clipped[i].v[e][1]>=0 && clipped[i].v[e][1]<=8);
        assert(clipped[i].z[e]==100 && clipped[i].v[e][4]==1);
    }
    /* Clipping must preserve affine STQ/depth/fog gradients. */
    draws[0]=tri(&b,100);
    memcpy(draws[0].v[0],(float[5]){-8,-8,0,0,1},sizeof draws[0].v[0]);
    draws[0].v[1][0]=24;draws[0].v[2][1]=24;
    for(unsigned e=0;e<3;e++) {
        float x=draws[0].v[e][0],y=draws[0].v[e][1];
        draws[0].v[e][2]=x*.25f+2;draws[0].v[e][4]=y*.125f+3;
        draws[0].z[e]=3*x+200;draws[0].f[e]=2*y+10;
    }
    count=lobby_clip_screen(draws,8,8,clipped);assert(count);
    for(unsigned i=0;i<count;i++) for(unsigned e=0;e<3;e++) {
        float x=clipped[i].v[e][0],y=clipped[i].v[e][1];
        assert(fabsf(clipped[i].v[e][2]-(x*.25f+2))<1e-5f);
        assert(fabsf(clipped[i].v[e][4]-(y*.125f+3))<1e-5f);
        assert(fabsf(clipped[i].z[e]-(3*x+200))<1e-5f);
        assert(fabsf(clipped[i].f[e]-(2*y+10))<1e-5f);
    }
    draws[0]=tri(&b,100);
    for(unsigned e=0;e<3;e++) draws[0].v[e][0]-=20;
    assert(!lobby_clip_screen(draws,8,8,clipped));
    dw4_fb_free(&fb);
    puts("lobby raster: straight GS alpha, opaque alpha, additive depth mask, coloured fog, exact shared edges and bounded attribute clipping OK");
    return 0;
}
