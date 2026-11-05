/* A loading card on the shared GPU layer must show its own stage, not the atlas of a card closed before it: the layer caches uploads by pixel
 * pointer, and the next card's atlas is allocated at the freed one's address (the practice stage showed the Terminal Area card after a hub visit). */
#include "dw4/frontui.h"
#include "dw4/gl_layer.h"
#include "dw4/mount.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static void card(const dw4_mount *m,const char *stage,dw4_gl_layer *gpu,dw4_fb *fb)
{
    dw4_frontui *a=dw4_frontui_open_loading(m,stage);assert(a);
    if(gpu)dw4_frontui_use_gpu(a,gpu);
    for(int f=0;f<150;f++)dw4_frontui_loading_sample(a,(uint64_t)f*1000000000/60);
    if(gpu)assert(!dw4_gl_layer_defer(gpu,fb,1));   /* the engine's resident frame: clear, card, one read-back */
    assert(!dw4_frontui_clear(a,fb,0,0,0));dw4_frontui_draw(a,fb,-1);
    if(gpu)assert(!dw4_gl_layer_defer(gpu,fb,0));
    dw4_frontui_close(a);
}
static double distance(const dw4_fb *a,const dw4_fb *b)
{double d=0;for(size_t i=0;i<(size_t)a->w*a->h*4;i++)d+=abs((int)a->rgba[i]-(int)b->rgba[i]);return d/((double)a->w*a->h*4);}
int main(int argc,char **argv)
{
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../../local/extracted"));
    dw4_gl_layer *gpu=dw4_gl_layer_open(640,448);
    if(!gpu){puts("loading stale texture: no GPU layer here, skipped");return 0;}
    dw4_fb term_cpu,prac_cpu,term_gpu,prac_gpu;
    assert(!dw4_fb_init(&term_cpu,640,448) && !dw4_fb_init(&prac_cpu,640,448) && !dw4_fb_init(&term_gpu,640,448) && !dw4_fb_init(&prac_gpu,640,448));
    card(&m,"stagML11",NULL,&term_cpu);card(&m,"stag0001",NULL,&prac_cpu);
    card(&m,"stagML11",gpu,&term_gpu);card(&m,"stag0001",gpu,&prac_gpu);   /* the second card reuses the first one's freed atlas address */
    double own=distance(&prac_gpu,&prac_cpu),stale=distance(&prac_gpu,&term_cpu);
    fprintf(stderr,"practice card on the shared layer: %.2f from its own CPU render, %.2f from the Terminal card\n",own,stale);
    assert(own<stale/2);
    dw4_gl_layer_close(gpu);
    puts("loading stale texture: a card after a closed card shows its own stage on the shared GPU layer");
    return 0;
}
