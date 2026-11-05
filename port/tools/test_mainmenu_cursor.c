/* Export original-asset character-menu submissions at an explicit diagnostic pose.
 * ROMS DIRECTORY STATE [SECONDS] [WIDTH HEIGHT] [--gpu]. */
#define _POSIX_C_SOURCE 200809L
#include "dw4/frontchr.h"
#include "dw4/frontui.h"
#include "dw4/gpupolicy.h"
#include "dw4/png.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct capture {const char *directory;unsigned width,height;int center_y,name_brackets;};
static void capture(void *user,const dw4_ui_draw *draw,size_t count)
{
    struct capture *c=user;
    if(c->name_brackets){
        unsigned brackets=0;
        for(size_t i=0;i<count;i++){
            const dw4_ui_draw *d=draw+i;
            if(!d->tex || d->tex->w!=32 || d->tex->h!=32)continue;
            int selected=1;
            for(unsigned k=0;k<3;k++){
                float x=d->v[k][0]*640/c->width,y=d->v[k][1]*448/c->height;
                if(x<=75 || x>=235 || y<=0 || y>=50 ||
                   d->v[k][2]!=.96875f || d->v[k][3]!=.03125f)selected=0;
            }
            if(!selected)continue;
            brackets++;
            for(unsigned k=0;k<3;k++){
                for(unsigned channel=0;channel<3;channel++)assert(d->rgba[k][channel]==127);
                assert(d->rgba[k][3]==128 && d->v[k][4]==1);
            }
        }
        assert(brackets==34);
    }
    if(c->center_y){
        unsigned cursor=0,untextured=0;
        for(size_t i=0;i<count;i++){
            const dw4_ui_draw *d=draw+i;if(!d->tex){untextured++;continue;}
            if(d->tex->w!=32 || d->tex->h!=32)continue;
            int selected=1;
            for(unsigned k=0;k<3;k++){
                float x=d->v[k][0]*640/c->width,y=d->v[k][1]*448/c->height,v=d->v[k][3];
                if(x<=5 || x>=55 || y<=c->center_y-25 || y>=c->center_y+25 ||
                    (v!=.0625f && v!=.09375f))selected=0;
            }
            if(!selected)continue;
            cursor++;
            for(unsigned k=0;k<3;k++){
                for(unsigned channel=0;channel<3;channel++)assert(d->rgba[k][channel]==127);
                assert(d->rgba[k][3]==128 && d->v[k][4]==1);
            }
        }
        assert(cursor==40 && !untextured);
    }
    if(!c->directory)return;
    char path[4096];snprintf(path,sizeof path,"%s/draws.tsv",c->directory);
    FILE *out=fopen(path,"w");assert(out);fputs("texture\ttriangle\tx\ty\tu\tv\tq\tr\tg\tb\ta\n",out);
    const dw4_tex *textures[64];size_t nt=0;
    for(size_t i=0;i<count;i++){
        const dw4_tex *tex=draw[i].tex;int texture=-1;
        if(tex){size_t t;for(t=0;t<nt;t++)if(textures[t]==tex)break;
            if(t==nt){assert(nt<64);textures[nt++]=tex;snprintf(path,sizeof path,"%s/tex-%zu.png",c->directory,t);assert(!dw4_png_write(path,tex->rgba,tex->w,tex->h));}texture=t;}
        for(unsigned k=0;k<3;k++){
            float q=draw[i].stq?draw[i].v[k][4]:1;
            fprintf(out,"%d\t%zu\t%.9g\t%.9g\t%.9g\t%.9g\t%.9g\t%u\t%u\t%u\t%u\n",texture,i,
                draw[i].v[k][0]*640/c->width,draw[i].v[k][1]*448/c->height,draw[i].v[k][2]/q,draw[i].v[k][3]/q,q,
                draw[i].rgba[k][0],draw[i].rgba[k][1],draw[i].rgba[k][2],draw[i].rgba[k][3]);}
    }
    assert(!fclose(out));printf("captured %zu UI triangles, %zu textures\n",count,nt);
}
int main(int argc,char **argv)
{
    if(argc==4 && !strcmp(argv[2],"--navigation")){
        dw4_mount mount;assert(!dw4_mount_open(&mount,argv[1]));dw4_frontchr *menu=dw4_frontchr_open(&mount);assert(menu);
        dw4_frontchr_species(menu,0);dw4_frontchr_begin_name(menu);
        for(const char *p=argv[3];*p;p++){
            assert(strchr("LRUDCB",*p));
            dw4_frontchr_name_input(menu,*p=='L'?-1:*p=='R'?1:0,*p=='U'?-1:*p=='D'?1:0,*p=='C',*p=='B',0);
            int mode,first,column;dw4_frontchr_name_selection(menu,&mode,&first,&column);
            printf("NAV %c %d %d %d %zu\n",*p,mode,first,column,strlen(dw4_frontchr_name(menu)));
        }
        dw4_frontchr_close(menu);dw4_mount_close(&mount);return 0;
    }
    if(argc==2){
        unsetenv("DW4_CHR_T");dw4_mount mount;assert(!dw4_mount_open(&mount,argv[1]));
        dw4_frontchr *menu=dw4_frontchr_open(&mount);assert(menu);dw4_fefont font={0};
        assert(!dw4_fefont_load(&font,argv[1]));dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
        int gpu=getenv("DW4_MAINMENU_GPU_LOOP")!=NULL;dw4_gpu_policy_begin(gpu);
        if(gpu)assert(dw4_frontchr_enable_gpu(menu,640,448));
        struct capture c={.width=640,.height=448};dw4_frontchr_observe_draws(menu,capture,&c);
        for(unsigned row=0;row<2;row++){
            c.center_y=row?114:92;
            for(unsigned tick=0;tick<60;tick++)dw4_frontchr_draw(menu,&fb,row,&font);
        }
        dw4_frontchr_species(menu,0);dw4_frontchr_begin_name(menu);
        dw4_frontchr_name_input(menu,0,0,1,0,0);dw4_frontchr_name_input(menu,0,0,0,0,1);
        dw4_frontchr_name_input(menu,0,0,1,0,0);c.center_y=159;
        for(unsigned tick=0;tick<60;tick++)dw4_frontchr_draw(menu,&fb,0,&font);
        dw4_frontchr_name_input(menu,0,1,0,0,0);c.center_y=176;
        for(unsigned tick=0;tick<60;tick++)dw4_frontchr_draw(menu,&fb,0,&font);
        dw4_frontchr_name_input(menu,0,0,0,1,0);c.center_y=0;c.name_brackets=1;
        for(unsigned state=0;state<4;state++){
            if(state==1)dw4_frontchr_name_input(menu,0,0,1,0,0);
            if(state==2)dw4_frontchr_name_input(menu,1,0,0,0,0);
            if(state==3)dw4_frontchr_name_input(menu,0,0,0,1,0);
            dw4_frontchr_draw(menu,&fb,0,&font);
        }
        assert(!dw4_gpu_policy_error()[0]);
        if(gpu)for(unsigned i=0;i<DW4_CPU_KIND_COUNT;i++)assert(!dw4_gpu_policy_cpu_count(i));
        dw4_frontchr_close(menu);dw4_fefont_free(&font);dw4_fb_free(&fb);dw4_mount_close(&mount);dw4_gpu_policy_begin(0);
        puts("main-menu cursor: 240 ticks preserve diamond/ring; four naming states retain all 34 bracket triangles and retail neutral colors");return 0;
    }
    assert(argc>=4);const char *state=argv[3];int width=argc>5?atoi(argv[5]):640,height=argc>6?atoi(argv[6]):448;
    static const char *const states[]={"create","call","name-empty","name-aa","name-moved","name-backspace","after-no","question","yes","no","created","title-press","title-create","title-option"};
    int valid=!strncmp(state,"species-",8) && strlen(state)==9 && state[8]>='0' && state[8]<='3';
    for(unsigned i=0;i<sizeof states/sizeof *states;i++)valid|=!strcmp(state,states[i]);
    if(!valid){fprintf(stderr,"unknown menu capture state: %s\n",state);return 2;}
    int gpu=argc>7 && !strcmp(argv[7],"--gpu");
    assert(width>0 && height>0);setenv("DW4_CHR_T",argc>4?argv[4]:"1",1);
    dw4_mount mount;assert(!dw4_mount_open(&mount,argv[1]));dw4_frontchr *menu=dw4_frontchr_open(&mount);assert(menu);
    dw4_fefont font={0};assert(!dw4_fefont_load(&font,argv[1]));dw4_fb fb;assert(!dw4_fb_init(&fb,width,height));
    int sel=!strcmp(state,"call");
    int title=!strncmp(state,"title-",6);
    if(!title && strcmp(state,"create") && strcmp(state,"call")){
        int species=!strncmp(state,"species-",8)?atoi(state+8):0;dw4_frontchr_species(menu,species);
        if(strncmp(state,"species-",8)){
            dw4_frontchr_begin_name(menu);
            if(strcmp(state,"name-empty")){
                dw4_frontchr_name_input(menu,0,0,1,0,0);
                dw4_frontchr_name_input(menu,0,0,1,0,0);}
            if(!strcmp(state,"name-moved") || !strcmp(state,"name-backspace") || !strcmp(state,"after-no"))for(unsigned i=0;i<3;i++)dw4_frontchr_name_input(menu,1,0,0,0,0);
            if(!strcmp(state,"name-backspace") || !strcmp(state,"after-no"))dw4_frontchr_name_input(menu,0,0,0,1,0);
            if(!strcmp(state,"after-no")){
                dw4_frontchr_name_input(menu,0,0,0,0,1);dw4_frontchr_name_input(menu,0,0,1,0,0);
                dw4_frontchr_name_input(menu,0,1,0,0,0);dw4_frontchr_name_input(menu,0,0,1,0,0);
            }
            if(!strcmp(state,"question") || !strcmp(state,"yes") || !strcmp(state,"no") || !strcmp(state,"created")){
                dw4_frontchr_name_input(menu,0,0,0,0,1);
                if(strcmp(state,"question"))dw4_frontchr_name_input(menu,0,0,1,0,0);
                if(!strcmp(state,"no"))dw4_frontchr_name_input(menu,0,1,0,0,0);
                if(!strcmp(state,"created"))dw4_frontchr_name_input(menu,0,0,1,0,0);
            }
        }
    }
    dw4_gpu_policy_begin(gpu);if(gpu){const char *info=dw4_frontchr_enable_gpu(menu,width,height);assert(info);puts(info);}
    struct capture c={.directory=argv[2],.width=width,.height=height};dw4_frontchr_observe_draws(menu,capture,&c);
    if(title){
        dw4_frontui *ui=dw4_frontui_open(&mount);assert(ui);
        if(gpu)assert(dw4_frontui_enable_gpu(ui,width,height));
        dw4_frontui_set_engine(ui,1000000000LL);
        if(strcmp(state,"title-press"))dw4_frontui_start(ui,1000000000LL);
        dw4_frontui_set_engine(ui,2000000000LL);
        dw4_frontui_draw(ui,&fb,!strcmp(state,"title-option"));
        dw4_frontui_set_engine(ui,2500000000LL);
        dw4_frontui_observe_draws(ui,capture,&c);
        dw4_frontui_draw(ui,&fb,!strcmp(state,"title-option"));
        dw4_frontui_close(ui);
    }else dw4_frontchr_draw(menu,&fb,sel,&font);
    assert(!dw4_gpu_policy_error()[0]);
    if(gpu)for(unsigned i=0;i<DW4_CPU_KIND_COUNT;i++)assert(!dw4_gpu_policy_cpu_count(i));
    char path[4096];snprintf(path,sizeof path,"%s/frame.png",argv[2]);assert(!dw4_png_write(path,fb.rgba,width,height));
    snprintf(path,sizeof path,"%s/capture.tsv",argv[2]);FILE *metadata=fopen(path,"w");assert(metadata);
    fprintf(metadata,"state\tpose_seconds\twidth\theight\tgpu\n%s\t%.9g\t%d\t%d\t%d\n",state,atof(argc>4?argv[4]:"1"),width,height,gpu);
    assert(!fclose(metadata));
    dw4_frontchr_close(menu);dw4_fefont_free(&font);dw4_fb_free(&fb);dw4_mount_close(&mount);dw4_gpu_policy_begin(0);return 0;
}
