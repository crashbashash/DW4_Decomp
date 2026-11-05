/* Asset-backed menu submission fixture. Private output directory is optional. */
#include "dw4/frontchr.h"
#include "dw4/gpupolicy.h"
#include "dw4/png.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct capture {const char *directory;unsigned frame;int width,height;};
static void observe(void *user,const dw4_ui_draw *draw,size_t count)
{
    struct capture *c=user;
    unsigned summary_vertices=0,label_vertices=0;
    for(size_t i=0;i<count;i++){
        const dw4_tex *t=draw[i].tex;
        if(t && t->w==512 && t->h==512 && draw[i].v[0][1]<90.0f*c->height/448)
            summary_vertices+=3;
        if(t && t->w==64 && t->h==32)label_vertices+=3;
    }
    /* aa, level, species and four numeric values, all seven actual rows. */
    static const unsigned expected[4]={120,114,114,120};
    assert(summary_vertices==expected[c->frame] && label_vertices==18);
    if(!c->directory)return;
    char path[4096];snprintf(path,sizeof path,"%s/root-%u.tsv",c->directory,c->frame);
    FILE *out=fopen(path,"w");assert(out);
    fputs("part\ttexture\ttriangle\tx\ty\tu\tv\tq\tr\tg\tb\ta\tw\th\n",out);
    const dw4_tex *textures[64];size_t nt=0;
    for(size_t i=0;i<count;i++){
        const dw4_tex *tex=draw[i].tex;if(!tex)continue;
        int summary=tex->w==512 && tex->h==512 && draw[i].v[0][1]<90.0f*c->height/448;
        int label=tex->w==64 && tex->h==32;if(!summary && !label)continue;
        size_t t;for(t=0;t<nt;t++)if(textures[t]==tex)break;
        if(t==nt){assert(nt<64);textures[nt++]=tex;
            snprintf(path,sizeof path,"%s/root-%u-%s-%zu.png",c->directory,c->frame,summary?"summary":"labels",t);
            assert(!dw4_png_write(path,tex->rgba,tex->w,tex->h));}
        for(unsigned k=0;k<3;k++)fprintf(out,"%s\t%zu\t%zu\t%.9g\t%.9g\t%.9g\t%.9g\t1\t%u\t%u\t%u\t%u\t%d\t%d\n",
            summary?"summary":"labels",t,i,draw[i].v[k][0]*640/c->width,draw[i].v[k][1]*448/c->height,
            draw[i].v[k][2],draw[i].v[k][3],draw[i].rgba[k][0],draw[i].rgba[k][1],draw[i].rgba[k][2],draw[i].rgba[k][3],tex->w,tex->h);
    }
    assert(!fclose(out));
}
int main(int argc,char **argv)
{
    const char *roms=argc>1?argv[1]:"../../local/extracted",*directory=argc>2?argv[2]:NULL;
    int gpu=argc>3 && !strcmp(argv[3],"--gpu"),w=argc>4?atoi(argv[4]):640,h=argc>5?atoi(argv[5]):448;
    assert(w>0 && h>0);dw4_mount mount;assert(!dw4_mount_open(&mount,roms));
    dw4_frontchr *menu=dw4_frontchr_open(&mount);assert(menu);
    dw4_fefont font={0};assert(!dw4_fefont_load(&font,roms));dw4_fb fb;assert(!dw4_fb_init(&fb,w,h));
    dw4_gpu_policy_begin(gpu);if(gpu){const char *info=dw4_frontchr_enable_gpu(menu,w,h);assert(info);puts(info);}
    struct capture capture={directory,0,w,h};
    for(unsigned species=0;species<4;species++){
        dw4_frontchr_reset(menu);dw4_frontchr_species(menu,species);dw4_frontchr_begin_name(menu);
        dw4_frontchr_name_input(menu,0,0,1,0,0);dw4_frontchr_name_input(menu,0,0,1,0,0);
        dw4_frontchr_name_input(menu,0,0,0,0,1);dw4_frontchr_name_input(menu,0,0,1,0,0);
        dw4_frontchr_name_input(menu,0,0,1,0,0);assert(dw4_frontchr_phase(menu)==DW4_CHR_CREATED);
        capture.frame=species;dw4_frontchr_observe_draws(menu,observe,&capture);
        dw4_frontchr_draw(menu,&fb,0,&font);assert(!dw4_gpu_policy_error()[0]);
        if(directory){char path[4096];snprintf(path,sizeof path,"%s/root-%u.png",directory,species);assert(!dw4_png_write(path,fb.rgba,w,h));}
        dw4_frontchr_name_input(menu,0,0,0,1,0);assert(dw4_frontchr_phase(menu)==DW4_CHR_NAME);
        assert(!strcmp(dw4_frontchr_name(menu),"aa"));
    }
    if(gpu)for(unsigned i=0;i<DW4_CPU_KIND_COUNT;i++)assert(!dw4_gpu_policy_cpu_count(i));
    dw4_frontchr_close(menu);dw4_fefont_free(&font);dw4_fb_free(&fb);dw4_mount_close(&mount);dw4_gpu_policy_begin(0);
    puts("main-menu: four authored summaries, labels and return-to-name passed");return 0;
}
