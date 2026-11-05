#include "dw4/gl_render.h"
#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef DW4_ENABLE_GL
#include <EGL/egl.h>
static const float view[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
static const float ambient[3]={1,1,1},tint[3]={1,0,0};
static const float pos[9]={-.5f,-.5f,2,.5f,-.5f,2,0,.5f,2};
static const uint32_t tris[3]={0,1,2};
static int draw(dw4_gl *g,dw4_fb *fb)
{return dw4_gl_render(g,fb,pos,NULL,NULL,tris,3,1,view,.9f,1,ambient,NULL,0,tint,NULL);}
static void gouraud_check(void)
{
    dw4_gl *g=dw4_gl_open(64,64);assert(g);dw4_gl_clear_color(g,0,0,0,255);
    dw4_fb cpu={0},gpu={0};assert(!dw4_fb_init(&cpu,64,64) && !dw4_fb_init(&gpu,64,64));
    const float p[9]={-.7f,-.6f,1.5f,1.8f,-1.2f,4,.3f,1.4f,3};
    const float n[9]={0,0,1,1,0,0,0,1,0},amb[3]={.2f,.2f,.2f};
    float white[3]={1,1,1};dw4_light light={.type=DW4_LIGHT_DIRECTIONAL,.dir={0,0,-1},.diffuse={.6f,.6f,.6f},.att_const=1};
    dw4_render_set_unlit(0);dw4_render_set_gouraud(1);dw4_render_set_ambient(.2f,.2f,.2f);dw4_render_set_lights(&light,1);
    dw4_render_set_view(view,.9f,1);dw4_fb_clear(&cpu,0,0,0);
    assert(dw4_render_mesh_n(&cpu,(const uint8_t *)p,(const uint8_t *)n,NULL,3,tris,1,0,0,white,NULL)>=0);
    assert(!dw4_gl_render(g,&gpu,p,n,NULL,tris,3,1,view,.9f,1,amb,&light,1,white,NULL));
    unsigned compared=0;int max=0;
    for(unsigned y=1;y<63;y++)for(unsigned x=1;x<63;x++){
        int inside=1;for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)
            if(!cpu.rgba[4*((y+dy)*64+x+dx)] || !gpu.rgba[4*((y+dy)*64+x+dx)])inside=0;
        if(!inside)continue;
        for(unsigned c=0;c<3;c++){int d=(int)cpu.rgba[4*(y*64+x)+c]-gpu.rgba[4*(y*64+x)+c];if(d<0)d=-d;if(d>max)max=d;}
        compared++;
    }
    assert(compared>200 && max<=1);printf("GPU mesh Gouraud: %u interior pixels, maximum channel delta %d; varying depth retains affine color\n",compared,max);
    dw4_render_clear_view();dw4_gl_close(g);dw4_fb_free(&cpu);dw4_fb_free(&gpu);
}
#endif
int main(void)
{
#ifndef DW4_ENABLE_GL
    puts("GPU mesh: GLES not compiled, skipped");
#else
    EGLContext initial=eglGetCurrentContext();
    dw4_gl *small=dw4_gl_open(16,16);if(!small){puts("GPU mesh: GLES unavailable, skipped");return 0;}
    assert(eglGetCurrentContext()==initial);
    dw4_fb a={0},b={0};assert(!dw4_fb_init(&a,16,16) && !dw4_fb_init(&b,37,29));
    dw4_render_set_unlit(1);
    assert(!dw4_gl_frame_begin(small,view,.9f,1,ambient,NULL,0));
    EGLContext peer=eglGetCurrentContext();assert(peer!=EGL_NO_CONTEXT);
    dw4_gl *large=dw4_gl_open(37,29);assert(large && eglGetCurrentContext()==peer);
    dw4_gl_layer *layer=dw4_gl_layer_open(16,16);assert(layer && eglGetCurrentContext()==peer);
    dw4_gl_clear_color(large,17,23,49,128);
    assert(!draw(large,&b) && eglGetCurrentContext()==peer);
    assert(b.rgba[0]==17 && b.rgba[1]==23 && b.rgba[2]==49 && b.rgba[3]==128);
    assert(!dw4_gl_layer_clear(layer,&a,7,13,31,0) && eglGetCurrentContext()==peer);
    assert(!dw4_gl_frame_mesh(small,pos,NULL,NULL,tris,3,1,tint,NULL));
    assert(!dw4_gl_frame_end(small,&a) && eglGetCurrentContext()==initial);
    assert(a.rgba[4*(8*16+8)]==255 && a.rgba[4*(8*16+8)+1]==0);
    dw4_gl_close(large);assert(eglGetCurrentContext()==initial);
    assert(!dw4_gl_layer_clear(layer,&a,37,41,43,255)); /* Closing a peer must not terminate EGL. */
    assert(!draw(small,&a));
    assert(!dw4_gl_frame_begin(small,view,.9f,1,ambient,NULL,0));
    memset(a.rgba,71,16*16*4);a.w=15;
    assert(dw4_gl_frame_end(small,&a)<0 && eglGetCurrentContext()==initial);
    for(unsigned i=0;i<16*16*4;i++)assert(a.rgba[i]==71);
    a.w=16;assert(!draw(small,&a));
    const uint32_t invalid[3]={0,1,3};
    assert(dw4_gl_render(small,&a,pos,NULL,NULL,invalid,3,1,view,.9f,1,ambient,NULL,0,tint,NULL)<0);
    assert(eglGetCurrentContext()==initial && !draw(small,&a));
    dw4_gl_layer_close(layer);assert(!draw(small,&a));
    dw4_gl_close(small);assert(eglGetCurrentContext()==initial);
    dw4_fb_free(&a);dw4_fb_free(&b);dw4_render_set_unlit(0);
    gouraud_check();
    puts("GPU mesh: different-size readbacks, nested mesh/layer contexts, peer teardown, failure recovery and custom clear pass");
#endif
}
