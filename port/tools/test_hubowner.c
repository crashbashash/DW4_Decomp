/* STATUS ownership by player slot (hub). The hubs open one player, so a second pad cannot join them yet: the checks drive the owner plumbing
 * itself. Player 1's records are injected into the live hub (an Agumon "Mate", ISUSE and NINZU 2), then `SUBWND nil 0 GENERATE "STATUS/I<1>"` (the shops'
 * payload form, retail `<MODE>/I<g_messPlayerNo>`) opens STATUS for that player: the tree shows player 1's name, only pad 2 reaches it (Circle on pad 1
 * does not close it, Circle on pad 2 does), a second Start does nothing while it runs, and the world is held. A later Start on pad 1 opens STATUS/I<0>
 * on the first player again. Whether a real Start on pad N sends STATUS/I<N> is an assumption (hubruntime.c start_status). Headless. */
#include "hubtest.h"
/* One frame with a pad word per slot: slot 0 through the main input, slot 1 through the co-op input. */
static void step2(dw4_hubruntime *h,uint32_t analog0,uint32_t pressed0,uint32_t analog1,uint32_t pressed1)
{
    dw4_hubruntime_input(h,0,0,analog0,0,pressed0);
    dw4_hubruntime_input_slot(h,1,0,0,analog1,0,pressed1);
    if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){fprintf(stderr,"tick: %s\n",dw4_hubruntime_error(h));assert(0);}
}
static void idle2(dw4_hubruntime *h,unsigned n){while(n--)step2(h,0,0,0,0);}
/* Whether any visible text of the open menu carries the name of the player in `slot` (the records' PLAYERNAME codes). */
static int name_is(dw4_hubruntime *h,int slot)
{
    dw4_unicode_object name;
    assert(!dw4_property_unicode_object(dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",slot),"PLAYERNAME",0,&name) && name.present && name.count>0);
    size_t n=0;while(n<name.count && name.codes[n])n++;
    const dw4_dialogue *d=dw4_hubruntime_dialogue(h);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++){
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(!t->visible || t->count<n)continue;
        size_t k=0;while(k<n && t->codes[k]==name.codes[k])k++;
        if(k==n)return 1;
    }
    return 0;
}
int main(int argc,char **argv)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubOwn",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    frame=0;
    dw4_hubruntime *h=boot_central(&mount,&initial);
    assert(control(h) && !dw4_hubruntime_status_active(h));
    /* Baseline: Start on pad 1 opens STATUS for the first player, whose name the tree shows. */
    step(h,0,8);
    unsigned k=0;for(;k<400 && dw4_hubruntime_status_active(h)!=2;k++)step(h,0,0);
    assert(k<400 && dw4_hubruntime_status_active(h)==2);
    idle(h,60);
    assert(name_is(h,0));
    /* Pad 2 does not reach player 0's menu (the hub has no second player, but the pad words are tracked): Circle on pad 2 leaves it open. */
    idle2(h,5);step2(h,0,0,0,0x2000);idle2(h,90);
    assert(dw4_hubruntime_status_active(h)==2);
    step(h,0,0x2000);{unsigned c=0;for(;c<900 && dw4_hubruntime_status_active(h);c++)step(h,0,0);assert(c<900);}
    for(unsigned c=0;c<300 && !control(h);c++)step(h,0,0);
    assert(control(h));
    /* Player 1 joins in the records. */
    {   dw4_playerrecords *rec=dw4_hubruntime_records(h);
        assert(!dw4_playerrecords_create(rec,db,1,"p_agumon","Mate",error,sizeof error) && !dw4_property_set_number(dw4_playerrecords_get(rec,"GETPLAYER",1),"ISUSE",1));
        assert(!dw4_property_set_number(dw4_playerrecords_get(rec,"GETCOMMON",0),"NINZU",2));}
    dw4_script_value open1[]={{DW4_SCRIPT_STRING,0,"SUBWND",6},{0},{DW4_SCRIPT_NUMBER,0,NULL,0},{DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,"STATUS/I<1>",11}},r;
    assert(!dw4_hubruntime_sd(h,open1,5,&r,error,sizeof error));
    for(k=0;k<400 && dw4_hubruntime_status_active(h)!=2;k++)step2(h,0,0,0,0);
    assert(k<400 && dw4_hubruntime_status_active(h)==2);
    idle2(h,60);
    assert(name_is(h,1) && !name_is(h,0));   /* the tree runs on player 1's record */
    /* Locked pads: Circle and a second Start on pad 1 do nothing, the world stays held. */
    dw4_lobby_presentation_state held,later;assert(!dw4_lobby_presentation(dw4_hubruntime_world(h),&held));
    step2(h,0,0x2000,0,0);step2(h,0,8,0,0);idle2(h,90);
    assert(dw4_hubruntime_status_active(h)==2 && name_is(h,1));
    assert(!dw4_lobby_presentation(dw4_hubruntime_world(h),&later) && later.tick==held.tick);
    /* The owner's pad closes it. */
    step2(h,0,0,0,0x2000);
    for(k=0;k<900 && dw4_hubruntime_status_active(h);k++)step2(h,0,0,0,0);
    assert(k<900 && !dw4_hubruntime_status_active(h));
    for(k=0;k<300 && !control(h);k++)step2(h,0,0,0,0);
    assert(control(h) && !dw4_hubruntime_input_state(h)->disabled);
    /* Start on pad 1 is the first player's again. */
    step2(h,0,8,0,0);
    for(k=0;k<400 && dw4_hubruntime_status_active(h)!=2;k++)step2(h,0,0,0,0);
    assert(k<400);idle2(h,60);
    assert(name_is(h,0) && !name_is(h,1));
    step2(h,0,0x2000,0,0);
    for(k=0;k<900 && dw4_hubruntime_status_active(h);k++)step2(h,0,0,0,0);
    assert(k<900);
    printf("hub owner: STATUS/I<1> runs on player 1's records and answers only pad 2; other pads and a second Start are locked out; Start on pad 1 reopens player 0\n");
    dw4_hubruntime_close(h);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    return 0;
}
