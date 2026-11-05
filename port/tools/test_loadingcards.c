/* Every loadingUSA/ld*.igb card in the manifest opens as the card of its stage and draws: the animated cards (a beLoadingNode with a loop) and the
 * plain still cards (stagML14, stagIS07/09/10/20: no loading node) that used to fall back to the text "Now Loading". Headless; optional PNG dir. */
#include "dw4/frontui.h"
#include "dw4/manifest.h"
#include "dw4/mount.h"
#include "dw4/png.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
int main(int argc,char **argv)
{
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../../local/extracted"));
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    unsigned cards=0,still=0;
    for(uint32_t i=0;i<m.man.nfiles;i++) {
        const char *path=m.man.files[i].path;
        if(strncasecmp(path,"loadingusa/ld",13) || strlen(path)<17)continue;
        char stage[64];snprintf(stage,sizeof stage,"st%.*s",(int)(strlen(path)-13-4),path+13);   /* ldag0001.igb -> stag0001 */
        dw4_frontui *a=dw4_frontui_open_loading(&m,stage);
        if(!a){fprintf(stderr,"card %s (%s): does not open\n",stage,path);assert(0);}
        for(int f=0;f<150;f++)dw4_frontui_loading_sample(a,(uint64_t)f*1000000000/60);
        dw4_fb_clear(&fb,0,0,0);dw4_frontui_draw(a,&fb,-1);
        unsigned lit=0;for(size_t p=0;p<(size_t)fb.w*fb.h;p++)lit+=fb.rgba[4*p]>40 || fb.rgba[4*p+1]>40 || fb.rgba[4*p+2]>40;
        /* the plain cards are one opaque black 32x32 quad: retail shows a black screen for them, not the text fallback; every other card is a picture */
        int plain=dw4_frontui_items(a)==1 && dw4_frontui_textures(a)==1 && lit==0;
        if(!plain && lit<1000){fprintf(stderr,"card %s: only %u lit pixels\n",stage,lit);assert(0);}
        if(plain){still++;assert(dw4_frontui_loading_ready(a)==1);
            assert(!strcasecmp(stage,"stagML14") || !strcasecmp(stage,"stagIS07") || !strcasecmp(stage,"stagIS09") || !strcasecmp(stage,"stagIS10") || !strcasecmp(stage,"stagIS20"));}
        if(argc>2){char out[512];snprintf(out,sizeof out,"%s/card-%s.png",argv[2],stage);assert(!dw4_png_write(out,fb.rgba,fb.w,fb.h));}
        dw4_frontui_close(a);cards++;
    }
    printf("loading cards: all %u loadingUSA cards open; %u plain black cards (retail draws no text for them)\n",cards,still);
    assert(cards>=60 && still==5);
    dw4_fb_free(&fb);return 0;
}
