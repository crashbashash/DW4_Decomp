#include "hubtest.h"
int main(int argc,char **argv)

{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Prac",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,"stag0001",0,1,error,sizeof error);assert(h);
    /* The tutorial window sits in WN03 and its text in the FONT layer after WN04: the text is drawn over the window, at full brightness. */
    unsigned t=0;for(;t<3000 && !has_text(h,"TALKFONT05","font00");t++)step(h,0,t%60==59?0x4000:0);
    assert(t<3000);idle(h,60);
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);
    unsigned best=0;
    for(int y=330;y<428;y++)for(int x=70;x<470;x++){const uint8_t *p=fb.rgba+4*((size_t)y*640+x);unsigned v=p[0]+p[1]+p[2];if(v>best)best=v;}
    fprintf(stderr,"practice tutorial text: brightest text-band pixel sum %u (the Digi-Elf's text reads 590; drawn under the window it was 172)\n",best);
    assert(best>=450);
    /* The window's yellow rules fade out through the wrapped texture alpha (retail: the top rule is flat to x=300 and gone by x=535, the bottom rule ramps in over
     * x=108..160); with a clamped texture they came out opaque and full length (sum of RGB 590 up to x=529 and from x=108). */
    {
        unsigned top[2]={0,0},bottom[3]={0,0,0};const int tx[2]={300,520},bx[3]={112,140,300};
        for(unsigned k=0;k<2;k++)for(int y=307;y<=313;y++){const uint8_t *p=fb.rgba+4*((size_t)y*640+tx[k]);unsigned v=p[0]+p[1]+p[2];if(v>top[k])top[k]=v;}
        for(unsigned k=0;k<3;k++)for(int y=431;y<=442;y++){const uint8_t *p=fb.rgba+4*((size_t)y*640+bx[k]);unsigned v=p[0]+p[1]+p[2];if(v>bottom[k])bottom[k]=v;}
        fprintf(stderr,"practice window rules: top x300 %u x520 %u, bottom x112 %u x140 %u x300 %u\n",top[0],top[1],bottom[0],bottom[1],bottom[2]);
        assert(top[1]*2<top[0] && bottom[0]*2<bottom[2] && bottom[1]<bottom[2]);
    }
    dw4_fb_free(&fb);dw4_hubruntime_close(h);
    puts("practice text: the tutorial message is drawn over its window");
    return 0;
}
