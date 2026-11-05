/* The Digimon info card of a field/dungeon stage (stag0101): its text (DMINFOFONT, FONT layer after WN04) is drawn over its i_dminfown window (WN03) at full
 * brightness; and Start in the practice stage (no beNDMWStatusInfo) opens nothing. Headless. */
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Info",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&initial,"stag0101",0,1,error,sizeof error);assert(h);
    unsigned t=0;for(;t<3000 && !has_text(h,"DMINFOFONT02","font02");t++)step(h,0,0);
    assert(t<3000);idle(h,20);
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);
    unsigned best=0;
    for(int y=369;y<423;y++)for(int x=394;x<562;x++){const uint8_t *p=fb.rgba+4*((size_t)y*640+x);unsigned v=p[0]+p[1]+p[2];if(v>best)best=v;}
    fprintf(stderr,"Digimon info card: brightest text-band pixel sum %u (drawn under its window it was dim)\n",best);
    assert(best>=450);
    dw4_fb_free(&fb);dw4_hubruntime_close(h);
    /* the practice stage carries no beNDMWStatusInfo: Start there opens no menu (a dungeon floor's Start menu is check-fieldstage-startmenu) */
    h=dw4_hubruntime_prepare(&mount,&initial,"stag0001",0,1,error,sizeof error);assert(h);
    for(t=0;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}   /* Cross pages through the lesson text */
    assert(t<6000);idle(h,30);
    for(unsigned k=0;k<60;k++)step(h,0,k==0?8:0);
    assert(!dw4_hubruntime_status_active(h));
    dw4_hubruntime_close(h);
    puts("dminfo text: the Digimon info card text is drawn over its window");
    return 0;
}
