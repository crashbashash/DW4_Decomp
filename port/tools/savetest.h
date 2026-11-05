/* Shared headless helpers for the save-scene tests: drive stagIS12 with a scripted pad, render checkpoints, and verify the
 * card against the player's record. */
#ifndef DW4_SAVETEST_H
#define DW4_SAVETEST_H
#include "hubtest.h"
#include "dw4/savescene.h"
#include "dw4/saveintf.h"
#include "dw4/memcard.h"
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

struct scene_run {unsigned ticks;char stage[64];int pos;uint64_t end_ns;int frames;};
/* Pad script: Cross every 20 ticks, START at the final confirmation. Draws CPU frames at the question, the card chooser,
 * the area selector and the confirmation (asserting visible content; PNGs when capture_dir is set). */
static void scene_frame(dw4_savescene *s,const char *tag)
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    int n=dw4_savescene_draw(s,&fb);
    if(n<0)fprintf(stderr,"scene draw %s: %s\n",tag,dw4_savescene_error(s));
    assert(n>=0);
    unsigned lit=0;for(size_t i=0;i<(size_t)fb.w*fb.h;i++)lit+=fb.rgba[4*i]||fb.rgba[4*i+1]||fb.rgba[4*i+2];
    if(lit<=1000)fprintf(stderr,"scene frame %s: only %u lit pixels\n",tag,lit);
    assert(lit>1000);
    if(capture_dir){char path[512];snprintf(path,sizeof path,"%s/save-%s.png",capture_dir,tag);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
    dw4_fb_free(&fb);
}
static int drive_scene(dw4_savescene *s,uint64_t start_ns,struct scene_run *out,int render)
{
    int last=-1,shots=0;uint64_t ns=start_ns;
    memset(out,0,sizeof *out);out->pos=-9;
    for(unsigned k=0;k<12000;k++){
        const dw4_saveintf *si=dw4_savescene_intf(s);dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(si,0,&t);
        uint32_t pressed=0;
        if(t.control==8&&t.control_sub==3)pressed=(k%20==0)?0x8:0;
        else if(k%20==0)pressed=0x4000;
        dw4_savescene_input(s,0,0,pressed);
        ns+=16666667ULL;out->end_ns=ns;
        if(dw4_savescene_tick(s,ns)){fprintf(stderr,"save scene tick %u: %s\n",k,dw4_savescene_error(s));return -1;}
        if(render&&t.control!=last&&k>10){
            static const char *const tag[]={"c0","c1","question","c3","cardchooser","areas","selected","continue","confirm","c9"};
            if((t.control==2||t.control==4||t.control==6||t.control==8)&&shots<8){
                for(int w=0;w<30;w++){dw4_savescene_input(s,0,0,0);ns+=16666667ULL;out->end_ns=ns;if(dw4_savescene_tick(s,ns))return -1;}
                scene_frame(s,tag[t.control]);out->frames++;shots++;
            }
        }
        last=t.control;
        if(dw4_savescene_exit(s,out->stage,sizeof out->stage,&out->pos)){out->ticks=k+1;return 0;}
    }
    return -1;
}
static void remove_dir(const char *dir)
{
    DIR *d=opendir(dir);struct dirent *e;char p[600];
    if(d){while((e=readdir(d))){if(!strcmp(e->d_name,".")||!strcmp(e->d_name,".."))continue;snprintf(p,sizeof p,"%s/%s",dir,e->d_name);unlink(p);}closedir(d);}
    rmdir(dir);
}
/* The card holds player 0's character in slot 0 and loads back into another player with the same key values. */
static void verify_card(dw4_memcard *card,dw4_playerrecords *original)
{
    dw4_memcard_summary sum[DW4_SAVE_SLOTS];char error[256];
    assert(!dw4_memcard_summaries(card,sum,error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(original,"GETPLAYER",0);
    assert(sum[0].used==1 && !sum[1].used && !sum[2].used && !sum[3].used);
    assert(!strcmp(sum[0].model,dw4_property_string(f,"DIGIMONNAME")));
    assert(sum[0].level==number(f,"LEVEL") && sum[0].hp==number(f,"HP") && sum[0].mhp==number(f,"MHP"));
    dw4_playerrecords *copy=dw4_playerrecords_snapshot(original);assert(copy);
    assert(!dw4_memcard_load(card,copy,1,0,error,sizeof error));
    dw4_property_folder *g=dw4_playerrecords_get(copy,"GETPLAYER",1);
    static const char *const keys[]={"ISUSE","UNIQUE","LEVEL","XDATA","BIT","MHP","MMP"};   /* recalculated stats (TSUYOSA...) are not stored in a save */
    for(unsigned i=0;i<sizeof keys/sizeof *keys;i++){
        int32_t a,b;
        if(dw4_property_number(f,keys[i],&a)||dw4_property_number(g,keys[i],&b)){fprintf(stderr,"card round trip: key %s is unavailable\n",keys[i]);assert(0);}
        if(a!=b)fprintf(stderr,"card round trip %s: %d != %d\n",keys[i],a,b);
        assert(a==b);
    }
    assert(!strcmp(dw4_property_string(f,"DIGIMONNAME"),dw4_property_string(g,"DIGIMONNAME")));
    dw4_playerrecords_close(copy);
}
#endif
