#include "dw4/gpupolicy.h"
#include "dw4/gl_layer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    dw4_gl_layer *g=dw4_gl_layer_open(16,16);
    if(!g){puts("GPU policy backend: reference GLES unavailable, skipped");return 0;}
    char renderer[256];snprintf(renderer,sizeof renderer,"%s",dw4_gl_layer_info(g));
    dw4_gl_layer_close(g);
    dw4_gpu_policy_begin(1);g=dw4_gl_layer_open(16,16);
    if(dw4_gpu_policy_hardware(renderer)){
        assert(g && !dw4_gpu_policy_error()[0]);
        dw4_fb fb={0};assert(!dw4_fb_init(&fb,16,16));
        memset(fb.rgba,37,16*16*4);
        dw4_ui_draw draw={.stq=1}; /* Invalid framebuffer width forces API failure. */
        fb.w=15;dw4_gl_layer *original=g;
        dw4_gl_layer_ui_or_cpu(&g,&fb,&draw,1,1);
        assert(g==original && dw4_gpu_policy_error()[0]);
        assert(!dw4_gpu_policy_cpu_count(DW4_CPU_UI));
        for(unsigned i=0;i<16*16*4;i++)assert(fb.rgba[i]==37);
        fb.w=16;dw4_fb_free(&fb);dw4_gl_layer_close(g);
        printf("GPU policy backend: %s accepted; failed draw retains GPU and performs no CPU fallback\n",renderer);
    }else{
        assert(!g && dw4_gpu_policy_error()[0]);
        printf("GPU policy backend: %s rejected for normal play\n",renderer);
    }
    dw4_gpu_policy_begin(0);g=dw4_gl_layer_open(16,16);
    assert(g && !dw4_gpu_policy_error()[0]);dw4_gl_layer_close(g);
    dw4_fb fb={0};assert(!dw4_fb_init(&fb,16,16));memset(fb.rgba,37,16*16*4);
    dw4_gpu_policy_begin(1);dw4_fb_clear(&fb,0,0,0);
    assert(dw4_gpu_policy_cpu_count(DW4_CPU_FILL)==1 && dw4_gpu_policy_error()[0]);
    for(unsigned i=0;i<16*16*4;i++)assert(fb.rgba[i]==37);
    dw4_gpu_policy_begin(1);dw4_render_ui_draws(&fb,&(dw4_ui_draw){.stq=1},1,1);
    assert(dw4_gpu_policy_cpu_count(DW4_CPU_UI)==1 && dw4_gpu_policy_error()[0]);
    for(unsigned i=0;i<16*16*4;i++)assert(fb.rgba[i]==37);
    dw4_gpu_policy_begin(0);dw4_fb_clear(&fb,0,0,0);assert(!fb.rgba[0]);dw4_fb_free(&fb);
    puts("GPU policy backend: CPU pixel calls rejected without writes; explicit reference restored");
    puts("GPU policy backend: reference mode restored independently");
}
