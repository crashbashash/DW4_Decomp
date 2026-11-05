/* Original bytecode -> localized rows -> stable renderer-neutral geometry. */
#include "dw4/fronttext.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char **argv)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_fronttext *text=dw4_fronttext_open(&mount);assert(text);
    const dw4_ui_draw *draw;size_t count;
    assert(!dw4_fronttext_draw(text,640,448,&draw,&count) && !count);
    const int callbacks[]={161,225,232,235,236,240};
    for(unsigned i=0;i<sizeof callbacks/sizeof *callbacks;i++){
        dw4_fronttext_clear(text);assert(!dw4_fronttext_event(text,callbacks[i]));
        if(callbacks[i]==161)assert(!dw4_fronttext_event(text,250));
        assert(!dw4_fronttext_draw(text,640,448,&draw,&count) && count);
        if(callbacks[i]==161)assert(count==94);
        if(callbacks[i]==232)assert(count==180);
        if(callbacks[i]==240)assert(count==122);
        dw4_ui_draw *copy=malloc(count*sizeof(*copy));assert(copy);memcpy(copy,draw,count*sizeof(*copy));size_t n=count;
        assert(!dw4_fronttext_draw(text,640,448,&draw,&count) && count==n && !memcmp(draw,copy,count*sizeof(*copy)));
        free(copy);
        for(size_t j=0;j<count;j++){
            assert(draw[j].tex && draw[j].tex->w==512 && draw[j].tex->h==512);
            for(unsigned k=0;k<3;k++){
                assert(draw[j].v[k][4]==1 && draw[j].rgba[k][0]==114 && draw[j].rgba[k][3]==121);
                if(callbacks[i]!=161)assert(draw[j].v[k][1]>=146 && draw[j].v[k][1]<224);
            }
        }
        dw4_fronttext_clear(text);assert(!dw4_fronttext_draw(text,640,448,&draw,&count) && !count);
    }
    /* Undefined original call reaches MsgBox and fails explicitly. */
    assert(dw4_fronttext_event(text,9999) && dw4_fronttext_error(text)[0]);
    assert(dw4_fronttext_draw(text,640,448,&draw,&count));dw4_fronttext_close(text);
    text=dw4_fronttext_open(&mount);assert(text && !dw4_fronttext_event(text,232));
    assert(!dw4_fronttext_draw(text,1280,960,&draw,&count) && count==180);
    dw4_fronttext_close(text);dw4_mount_close(&mount);
    puts("front-end text: original txt_mem callbacks, cached stable glyphs, visibility, resize and explicit failure passed");return 0;
}
