#include "dw4/fefont.h"
#include "dw4/gl_layer.h"
#include "dw4/gpupolicy.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char **argv)
{
    dw4_gl_layer *g=dw4_gl_layer_open(640,224);
    if(!g){puts("GPU legacy font: GLES unavailable, skipped");return 0;}
    dw4_fefont font={0};assert(!dw4_fefont_load(&font,argc>1?argv[1]:"../../local/extracted"));
    dw4_fb cpu={0},gpu={0};assert(!dw4_fb_init(&cpu,640,224) && !dw4_fb_init(&gpu,640,224));
    const char *text="Now Loading: Cross Retry / Circle Back 0123456789";
    const uint8_t color[3][4]={{128,96,64,96},{128,96,64,96},{128,96,64,96}};
    for(unsigned sample=0;sample<4;sample++){
        float scale=.5f+sample*.25f;
        dw4_fb_clear(&cpu,17,23,37);memcpy(gpu.rgba,cpu.rgba,640*224*4);
        int expected=dw4_fefont_draw(&cpu,&font,11.25f,19.125f,scale,text,color);
        int hardware=dw4_gpu_policy_hardware(dw4_gl_layer_info(g));if(hardware)dw4_gpu_policy_begin(1);
        assert(dw4_fefont_draw_gpu(g,&gpu,&font,11.25f,19.125f,scale,text,color)==expected);
        if(hardware){for(unsigned kind=0;kind<DW4_CPU_KIND_COUNT;kind++)assert(!dw4_gpu_policy_cpu_count(kind));dw4_gpu_policy_begin(0);}
        size_t ink=0,far=0;double sum=0;
        for(unsigned p=0;p<640*224;p++){
            int max=0;ink+=gpu.rgba[4*p]!=17 || gpu.rgba[4*p+1]!=23 || gpu.rgba[4*p+2]!=37;
            for(unsigned c=0;c<3;c++){int d=abs((int)gpu.rgba[4*p+c]-cpu.rgba[4*p+c]);sum+=d;if(d>max)max=d;}far+=max>4;
        }
        assert(expected>30 && ink>200);
        printf("GPU legacy font scale %.2f: %d glyphs, %zu changed pixels, CPU/GPU mean %.4f >4/channel %.3f%% (pixel diagnostics)\n",
            scale,expected,ink,sum/(640*224*3),100.0*far/(640*224));
    }
    dw4_gl_layer_close(g);dw4_fb_free(&cpu);dw4_fb_free(&gpu);dw4_fefont_free(&font);
    puts("GPU legacy font: real atlas, glyph count, visible output and zero CPU calls pass");
}
