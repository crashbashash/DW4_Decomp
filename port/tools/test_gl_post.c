#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
int main(void)
{
    dw4_gl_layer *g=dw4_gl_layer_open(16,16);
    if(!g){puts("GPU pixel transforms: GLES unavailable, skipped");return 0;}
    dw4_fb fb={0};assert(!dw4_fb_init(&fb,16,16));
    unsigned cases=0;uint32_t seed=0x20836;
    for(int mode=DW4_GL_FADE_RGB;mode<=DW4_GL_SHADOW_ALPHA;mode++)for(unsigned sample=0;sample<80;sample++){
        seed=seed*1664525+1013904223;
        float factor=sample==0?0:sample==1?1:sample==2?.5f:sample==3?.4f:sample==4?1.f/3:(seed>>8)/16777215.f;
        uint8_t expected[16*16*4];
        for(unsigned p=0;p<256;p++){
            uint8_t *v=fb.rgba+4*p;v[0]=p;v[1]=255-p;v[2]=(p*37)&255;v[3]=(p*53)&255;
            memcpy(expected+4*p,v,4);
            if(mode==DW4_GL_FADE_RGB)for(unsigned c=0;c<3;c++)expected[4*p+c]=(unsigned)(v[c]*factor);
            else{expected[4*p]=expected[4*p+1]=expected[4*p+2]=0;
                expected[4*p+3]=(unsigned)floorf(v[0]*(128.f/255)*(1-factor)+.5f);}
        }
        assert(!dw4_gl_layer_transform(g,&fb,mode,factor));
        for(unsigned i=0;i<sizeof expected;i++)if(fb.rgba[i]!=expected[i]){
            fprintf(stderr,"GPU pixel transform mismatch mode %d factor %.9g byte %u: %u/%u\n",mode,factor,i,fb.rgba[i],expected[i]);return 1;
        }
        cases++;
    }
    uint8_t before[16*16*4];memcpy(before,fb.rgba,sizeof before);
    for(unsigned keep=0;keep<=30;keep++){
        for(unsigned p=0;p<256;p++)for(unsigned c=0;c<4;c++)fb.rgba[4*p+c]=(p*(c*17+1)+c*31)&255;
        memcpy(before,fb.rgba,sizeof before);assert(!dw4_gl_layer_multiply(g,&fb,keep,30));
        for(unsigned p=0;p<256;p++)for(unsigned c=0;c<4;c++)
            assert(fb.rgba[4*p+c]==(c==3?before[4*p+c]:before[4*p+c]*keep/30));
    }
    memcpy(before,fb.rgba,sizeof before);
    assert(dw4_gl_layer_transform(g,&fb,DW4_GL_FADE_RGB,NAN)<0 && !memcmp(before,fb.rgba,sizeof before));
    assert(dw4_gl_layer_transform(g,&fb,99,.5f)<0 && !memcmp(before,fb.rgba,sizeof before));
    dw4_fb source={0};assert(!dw4_fb_init(&source,5,7));unsigned blits=0;
    for(unsigned sample=0;sample<40;sample++){
        int x=(int)(sample%8)-3,y=(int)(sample%10)-4;float opacity=(sample%11)/10.f;
        uint8_t expected[16*16*4];
        for(unsigned p=0;p<256;p++)for(unsigned c=0;c<4;c++)fb.rgba[4*p+c]=(p*(c*17+1)+c*31)&255;
        for(unsigned p=0;p<35;p++)for(unsigned c=0;c<4;c++)source.rgba[4*p+c]=(p*(c*23+7)+c*13)&255;
        source.rgba[3]=0;source.rgba[7]=255;
        memcpy(expected,fb.rgba,sizeof expected);
        for(int sy=0;sy<7;sy++)for(int sx=0;sx<5;sx++){
            const uint8_t *src=source.rgba+4*(sy*5+sx);int dx=x+sx,dy=y+sy;
            if(!src[3] || dx<0 || dy<0 || dx>=16 || dy>=16)continue;
            uint8_t *dst=expected+4*(dy*16+dx);unsigned alpha=(unsigned)(opacity*src[3]+.5f);
            for(unsigned c=0;c<3;c++)dst[c]=(src[c]*alpha+dst[c]*(255-alpha)+127)/255;
            dst[3]=255;
        }
        assert(!dw4_gl_layer_blit(g,&fb,&source,x,y,opacity));
        assert(!memcmp(expected,fb.rgba,sizeof expected));blits++;
    }
    memcpy(before,fb.rgba,sizeof before);
    assert(!dw4_gl_layer_blit(g,&fb,&source,INT_MIN,INT_MAX,.5f) && !memcmp(before,fb.rgba,sizeof before));
    assert(dw4_gl_layer_blit(g,&fb,&source,0,0,NAN)<0 && !memcmp(before,fb.rgba,sizeof before));
    dw4_fb_free(&source);
    assert(!dw4_fb_init(&source,7,11));
    for(unsigned p=0;p<7*11;p++)for(unsigned c=0;c<4;c++)source.rgba[4*p+c]=(p*(c*13+3)+c*17)&255;
    assert(!dw4_gl_layer_scale(g,&fb,&source));
    for(unsigned y=0;y<16;y++)for(unsigned x=0;x<16;x++)
        assert(!memcmp(fb.rgba+4*(y*16+x),source.rgba+4*((y*11/16)*7+x*7/16),4));
    dw4_fb_free(&source);assert(!dw4_fb_init(&source,23,19));
    for(unsigned p=0;p<23*19;p++)for(unsigned c=0;c<4;c++)source.rgba[4*p+c]=(p*(c*13+3)+c*17)&255;
    assert(!dw4_gl_layer_scale(g,&fb,&source));
    for(unsigned y=0;y<16;y++)for(unsigned x=0;x<16;x++)
        assert(!memcmp(fb.rgba+4*(y*16+x),source.rgba+4*((y*19/16)*23+x*23/16),4));
    dw4_fb_free(&source);
    puts("GPU nearest resize: unequal up/down scales preserve exact source pixel indices and RGBA");
    assert(!dw4_gl_layer_clear(g,&fb,53,79,101,0));
    for(unsigned p=0;p<256;p++)assert(fb.rgba[4*p]==53 && fb.rgba[4*p+1]==79 && fb.rgba[4*p+2]==101 && !fb.rgba[4*p+3]);
    printf("GPU pixel transforms: %u cases, all 256 channel values, %u clipped RGBA blits; byte-exact fade/shadow alpha, portrait blending and rejected inputs pass (%s)\n",cases,blits,dw4_gl_layer_info(g));
    dw4_fb_free(&fb);dw4_gl_layer_close(g);
    g=dw4_gl_layer_open(160,48);assert(g);dw4_fb cpu={0};assert(!dw4_fb_init(&cpu,160,48) && !dw4_fb_init(&fb,160,48));
    const double fps[]={0,20,59,60,165,999};
    for(unsigned sample=0;sample<sizeof fps/sizeof *fps;sample++){
        for(unsigned p=0;p<160*48;p++)for(unsigned c=0;c<4;c++)cpu.rgba[4*p+c]=(p*(c*13+3)+c*17)&255;
        memcpy(fb.rgba,cpu.rgba,160*48*4);dw4_render_fps(&cpu,fps[sample]);
        assert(!dw4_render_fps_gpu(g,&fb,fps[sample]));
        for(unsigned i=0;i<160*48*4;i++)if(cpu.rgba[i]!=fb.rgba[i]){
            fprintf(stderr,"GPU FPS mismatch %.0f byte %u: %u/%u\n",fps[sample],i,fb.rgba[i],cpu.rgba[i]);return 1;
        }
    }
    dw4_fb_free(&cpu);dw4_fb_free(&fb);dw4_gl_layer_close(g);
    puts("GPU FPS: bitmap/shadow order, integer darkening and framebuffer alpha are byte-exact");
}
