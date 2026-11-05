/* The hub gate pads through the normal prepared hub runtime. Headless.
 * Terminal mate00 (Gate to Outside World), mate01 (Gate to Commander Room), mate02 (Emergency Gate) and the second exits
 * Central mate00 / Shop mate00 run their original pad scripts on changed material membership: each clears the point label
 * (POINTFONT00, i_stpnl06/i_pointcur SQ_CLOSE) and opens its travel prompt under its story-flag guards, accept routes to the
 * authored destination/point, No and Circle return control and the label comes back only on re-entering its region.
 * Players are placed with dw4_lobby_place_player (original MOVETRANS) at the centre of the authored regions; only story flags
 * and the gate-stage record are fixtures. */
#include "hubtest.h"
/* Placement height: above every hub floor, so the player drops onto the floor under the point. */
enum {DROP=100};
static dw4_mount mount;
static dw4_playerrecords *players;
static dw4_be_state state;
static void set_flag(int32_t n,int32_t v)
{
    dw4_script_value a[2]={{DW4_SCRIPT_NUMBER,n,NULL,0},{DW4_SCRIPT_NUMBER,v,NULL,0}},r;char e[256];
    assert(!dw4_playerrecords_call(players,"FLGset",a,2,&r,e,sizeof e));
}
static void set_gate(const char *stage,int32_t no)
{
    dw4_script_value a[2]={{stage?DW4_SCRIPT_STRING:DW4_SCRIPT_NIL,0,stage,stage?strlen(stage):0},{DW4_SCRIPT_NUMBER,no,NULL,0}},r;char e[256];
    assert(!dw4_playerrecords_call(players,"SYSsetGateStage",a,2,&r,e,sizeof e));
}
/* The story flags the pads read; each case sets its own subset on a clean record. */
static const int32_t story_flags[]={2,3,4,5,6,86,409,424,503};
static void clear_story(void){for(unsigned i=0;i<sizeof story_flags/sizeof *story_flags;i++)set_flag(story_flags[i],0);set_gate(NULL,0);}
static dw4_hubruntime *open_stage(const char *stage)
{
    char error[1024];frame=0;
    dw4_hubruntime_source source={players,&state,NULL,0};
    dw4_hubruntime *h=dw4_hubruntime_prepare(&mount,&source,stage,0,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare %s: %s\n",stage,error);assert(0);}
    unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
    assert(t<6000);return h;
}
static void centre(dw4_hubruntime *h,const char *region,float out[3])
{
    float mn[3],mx[3];assert(dw4_lobby_material_region(dw4_hubruntime_world(h),region,mn,mx)>=0);
    out[0]=(mn[0]+mx[0])/2;out[1]=DROP;out[2]=(mn[2]+mx[2])/2;
}
static void place(dw4_hubruntime *h,const float p[3]){assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),p[0],p[1],p[2],0));}
/* Open: the SQ_OPEN<n> sequence or its SQ_WAIT<nn> hold. Closing runs SQ_CLOSE and ends at SQ_END (or erases the model);
 * a band that was never opened rests in the plain SQ_WAIT it was generated with. */
static int band_open(const dw4_modelctrl *m)
{
    const char *q=m && dw4_modelctrl_active(m)?dw4_modelctrl_sequence(m):NULL;
    return q && (!strncmp(q,"SQ_OPEN",7) || (!strncmp(q,"SQ_WAIT",7) && q[7]>='0' && q[7]<='9'));
}
static int label_shown(dw4_hubruntime *h,const char *text)
{
    const char *shown=has_text(h,"POINTFONT00","font04")?text_value(h,"POINTFONT00","font04"):NULL;
    const dw4_modelctrl *cursor=find(dw4_hubruntime_models(h),"i_pointcur",4);
    const dw4_modelctrl *band=find(dw4_hubruntime_models(h),"i_stpnl06",4);
    int arrow=cursor && dw4_modelctrl_active(cursor) && !strcmp(dw4_modelctrl_sequence(cursor),"SQ_OPEN4");
    return shown && strstr(shown,text) && arrow && band_open(band);
}
static int label_cleared(dw4_hubruntime *h)
{
    const dw4_modelctrl *cursor=find(dw4_hubruntime_models(h),"i_pointcur",4),*band=find(dw4_hubruntime_models(h),"i_stpnl06",4);
    int arrow=band_open(cursor),panel=band_open(band);
    return !has_text(h,"POINTFONT00",NULL) && !arrow && !panel;
}
/* Outside the label region, then inside it (label up), then onto the pad. */
static void approach_pad(dw4_hubruntime *h,const char *label_region,const char *label_text,const char *pad)
{
    float away[3],lab[3],on[3];
    float mn[3],mx[3];assert(dw4_lobby_material_region(dw4_hubruntime_world(h),label_region?label_region:pad,mn,mx)>=0);
    centre(h,pad,on);
    away[0]=mn[0]-40;away[1]=DROP;away[2]=on[2];
    place(h,away);idle(h,60);
    if(label_region) {
        assert(!has_text(h,"POINTFONT00",NULL));
        /* inside the label region beside the pad */
        lab[0]=on[0];lab[1]=DROP;lab[2]=on[2]+((mx[2]-on[2])>(on[2]-mn[2])?18:-18);
        place(h,lab);idle(h,90);
        if(!label_shown(h,label_text)){
            dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
            const dw4_modelctrl *cursor=find(dw4_hubruntime_models(h),"i_pointcur",4);
            fprintf(stderr,"%s: label '%s' not shown before the pad: player at %g,%g,%g shows '%s', arrow %s\n",pad,label_text,
                w.position[0],w.position[1],w.position[2],has_text(h,"POINTFONT00","font04")?text_value(h,"POINTFONT00","font04"):"(none)",
                cursor?dw4_modelctrl_sequence(cursor):"(none)");
            assert(0);
        }
    }
    place(h,on);
}
enum {ACCEPT,DECLINE,CANCEL};
static const char *const choice_name[]={"accept","decline","cancel"};
static unsigned party_pads;   /* party tests: the joined players; a selector reads the pad of the player that started it, so the mates press too */
static void press_choice(dw4_hubruntime *h,uint32_t bits)
{
    for(unsigned q=1;q<party_pads;q++)dw4_hubruntime_input_slot(h,q,0,0,0,bits,bits);
    press(h,bits);
}
/* Wait for the prompt group, make the choice and check its route. */
static void prompt_route(dw4_hubruntime *h,const char *pad,const char *prompt_group,int choice,int downs,const char *destination,int point)
{
    unsigned k=0;for(;k<300 && !has_text(h,prompt_group,NULL);k++)step(h,0,0);
    if(k==300){fprintf(stderr,"%s: no %s prompt\n",pad,prompt_group);assert(0);}
    assert(!control(h));
    assert(label_cleared(h)); /* the pad script closed the label before its prompt */
    idle(h,60);
    /* A selector step latches until its line sequence ends; the next stick sample then only releases the latch. */
    for(int i=0;i<downs;i++){if(i){step(h,4,0);idle(h,60);}step(h,4,0);idle(h,60);}
    if(choice==DECLINE)down(h);
    press_choice(h,choice==CANCEL?0x2000:0x4000);
    const dw4_stagetravel *travel=dw4_hubruntime_travel(h);
    if(choice==ACCEPT) {
        unsigned r=0;for(;r<600 && !travel->pending;r++)step(h,0,0);
        if(!travel->pending || strcasecmp(travel->destination,destination) || travel->generate_pos!=point)
            fprintf(stderr,"%s: travel pending %d to %s point %d; expected %s point %d\n",pad,travel->pending,travel->destination,travel->generate_pos,destination,point);
        if(!travel->pending){fprintf(stderr,"  hub error '%s', script error '%s', DM groups %zu\n",dw4_hubruntime_error(h),dw4_lobby_script_error(dw4_hubruntime_world(h)),dw4_scriptengine_pending(dw4_hubruntime_scripts(h)));dw4_scriptengine_describe(dw4_hubruntime_scripts(h),stderr);}
        assert(travel->pending && !strcasecmp(travel->destination,destination) && travel->generate_pos==point && !control(h));
        dw4_script_value gate;char e[256];
        assert(!dw4_playerrecords_call(dw4_hubruntime_records(h),"SYSgetGateStageName",NULL,0,&gate,e,sizeof e));
        /* The Emergency Gate is spent on use: its prompt's accept arm runs gateclear.lua before the travel request. */
        if(!strcmp(pad,"mate02"))assert(gate.type==DW4_SCRIPT_STRING && gate.length==7 && !memcmp(gate.string,"GateOff",7));
    }else {
        unsigned r=0;for(;r<600 && !(control(h) && !dw4_hubruntime_input_state(h)->disabled);r++)step(h,0,0);
        assert(r<600 && !travel->pending && !has_text(h,prompt_group,NULL));
        idle(h,60);
        dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        float mn[3],mx[3];assert(dw4_lobby_material_region(dw4_hubruntime_world(h),pad,mn,mx)>=0);
        /* The player landed on the pad's floor and is still inside it. */
        if(choice==DECLINE)printf("  %s: control back with the player on the pad floor at %g,%g,%g\n",pad,w.position[0],w.position[1],w.position[2]);
        assert(w.position[1]>mn[1] && w.position[1]<mx[1] && w.position[0]>=mn[0] && w.position[0]<=mx[0] && w.position[2]>=mn[2] && w.position[2]<=mx[2]);
        assert(label_cleared(h)); /* still inside the label region: the label stays closed until it is re-entered */
    }
}
/* After No/Circle: leaving the pad but staying in the label region shows nothing; leaving and re-entering the region shows the
 * label again; stepping back on the pad opens the prompt again. */
static void reenter(dw4_hubruntime *h,const char *label_region,const char *label_text,const char *pad,const char *prompt_group)
{
    if(label_region) {
        float on[3];centre(h,pad,on);
        float mn[3],mx[3];assert(dw4_lobby_material_region(dw4_hubruntime_world(h),label_region,mn,mx)>=0);
        float beside[3]={on[0],DROP,on[2]+((mx[2]-on[2])>(on[2]-mn[2])?18:-18)};
        place(h,beside);idle(h,90);
        assert(control(h) && label_cleared(h) && !has_text(h,prompt_group,NULL)); /* off the pad, still in the label region */
    }
    approach_pad(h,label_region,label_text,pad);
    unsigned k=0;for(;k<300 && !has_text(h,prompt_group,NULL);k++)step(h,0,0);
    assert(k<300 && label_cleared(h));
    idle(h,60);press(h,0x2000);
    unsigned r=0;for(;r<600 && !(control(h) && !dw4_hubruntime_input_state(h)->disabled);r++)step(h,0,0);
    assert(r<600 && !dw4_hubruntime_travel(h)->pending);
}
static void gate_case(const char *stage,const char *label_region,const char *label_text,const char *pad,const char *prompt_group,
    int choice,int downs,const char *destination,int point)
{
    dw4_hubruntime *h=open_stage(stage);
    approach_pad(h,label_region,label_text,pad);
    prompt_route(h,pad,prompt_group,choice,downs,destination,point);
    if(choice!=ACCEPT)reenter(h,label_region,label_text,pad,prompt_group);
    printf("hub gate %s %s: %s%s prompt, %s -> %s\n",stage,pad,label_region?"label closed, ":"",prompt_group,choice_name[choice],
        choice==ACCEPT?destination:label_region?"control restored, label back on re-entry":"control restored, prompt again on re-entry");
    dw4_hubruntime_close(h);
}
/* A party at a hub exit: the callback rejects incomplete material membership (MATisAllPlayer), so the first player alone gets no prompt; with every
 * joined player in the region the prompt opens and its accept arm runs the exit chunk (one SQ_EXIT per joined player, staggered) to the travel request. */
static void party_exit_case(const char *stage,const char *pad,const char *destination,int point,unsigned n)
{
    dw4_hubruntime *h=open_stage(stage);
    dw4_lobby *w=dw4_hubruntime_world(h);assert(dw4_lobby_player_count(w)==n);
    float on[3];centre(h,pad,on);
    on[0]-=8;   /* the exit regions at the map edge have floor only on their inner side */
    place(h,on);idle(h,240);
    if(n>1)assert(!dw4_hubruntime_travel(h)->pending && !has_text(h,"STCHGFONT00",NULL) && control(h));   /* mates outside: no prompt */
    for(unsigned q=1;q<n;q++) {
        assert(!dw4_lobby_select_player(w,q) && !dw4_lobby_place_player(w,on[0]+3.0f*(float)q,DROP,on[2],0));
    }
    dw4_lobby_select_player(w,0);
    party_pads=n;idle(h,60);
    {   float mn[3],mx[3];assert(dw4_lobby_material_region(w,pad,mn,mx)>=0);
        fprintf(stderr,"%s %s region x %g..%g y %g..%g z %g..%g\n",stage,pad,mn[0],mx[0],mn[1],mx[1],mn[2],mx[2]);
        for(unsigned q=0;q<n;q++){dw4_lobby_walk_state ws;assert(!dw4_lobby_select_player(w,q) && !dw4_lobby_walk(w,&ws));fprintf(stderr,"  player %u at %g %g %g\n",q,ws.position[0],ws.position[1],ws.position[2]);}
        dw4_lobby_select_player(w,0);}
    prompt_route(h,pad,"STCHGFONT00",ACCEPT,0,destination,point);
    party_pads=0;
    printf("hub gate %s %s with %u players: the prompt waits for the whole party, accept -> %s\n",stage,pad,n,destination);
    dw4_hubruntime_close(h);
}
/* A pad closed by its story flags: the original script runs and does nothing; the label stays, no prompt, control stays. */
static void closed_case(const char *stage,const char *label_region,const char *label_text,const char *pad,const char *why)
{
    dw4_hubruntime *h=open_stage(stage);
    approach_pad(h,label_region,label_text,pad);
    idle(h,180);
    assert(control(h) && !dw4_hubruntime_travel(h)->pending && !has_text(h,"STCHGFONT00",NULL) && !has_text(h,"STCHGFONT01",NULL));
    if(label_region)assert(label_shown(h,label_text));
    printf("hub gate %s %s closed (%s): label stays, no prompt, control kept\n",stage,pad,why);
    dw4_hubruntime_close(h);
}
int main(int argc,char **argv)
{
    assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    players=dw4_playerrecords_open();dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[1024];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","Gates",error,sizeof error));

    /* Gate to Commander Room (030-exit-to-stagml02.lua): open while flag 424 is clear. */
    clear_story();
    for(int c=0;c<3;c++)gate_case("stagML11","matf01","Gate to Commander Room","mate01","STCHGFONT00",c,0,"stagML02",0);
    set_flag(424,1);closed_case("stagML11","matf01","Gate to Commander Room","mate01","flag 424");

    /* Gate to Outside World (037-msg-70000.lua): the field list opens from flag 2 (Leomon saved) on; before it the pad is inert. */
    clear_story();closed_case("stagML11","matf00","Gate to Outside World","mate00","flags 2/4/5/6/86/409 clear");
    set_flag(2,1);
    gate_case("stagML11","matf00","Gate to Outside World","mate00","STCHGFONT01",ACCEPT,0,"stag0001",0);
    gate_case("stagML11","matf00","Gate to Outside World","mate00","STCHGFONT01",CANCEL,0,"",0);
    set_flag(503,1);gate_case("stagML11","matf00","Gate to Outside World","mate00","STCHGFONT01",ACCEPT,0,"stag0101",0);
    clear_story();set_flag(6,1);
    gate_case("stagML11","matf00","Gate to Outside World","mate00","STCHGFONT01",ACCEPT,1,"stag0201",0);
    gate_case("stagML11","matf00","Gate to Outside World","mate00","STCHGFONT01",ACCEPT,3,"stag0401",0);
    set_flag(409,1);gate_case("stagML11","matf00","Gate to Outside World","mate00","STCHGFONT01",ACCEPT,0,"stag0401",3);

    /* Emergency Gate (020-msg-70029.lua): open while flag 3 and 409 are clear and a gate stage is recorded. */
    clear_story();closed_case("stagML11","matf03","Emergency Gate","mate02","gate stage GateOff");
    set_gate("dng101b2",2);
    for(int c=0;c<3;c++)gate_case("stagML11","matf03","Emergency Gate","mate02","STCHGFONT00",c,0,"dng101b2",2);
    /* Flag 3 (the Ophanimon-key hub invasion) also closes it; that Terminal state runs an invasion start-up the port does not
     * prepare yet, so the guard is exercised through flag 409 (a quest under way). */
    set_flag(409,1);closed_case("stagML11","matf03","Emergency Gate","mate02","flag 409");

    /* The second exits (071-exit-to-stagml13-2.lua, 050-exit-to-stagml12-2.lua): no label region, no flag guard. */
    clear_story();
    for(int c=0;c<3;c++)gate_case("stagML12",NULL,NULL,"mate00","STCHGFONT00",c,0,"stagML13",2);
    for(int c=0;c<3;c++)gate_case("stagML13",NULL,NULL,"mate00","STCHGFONT00",c,0,"stagML12",5);

    /* Field and dungeon destinations have no runtime in this build: prepare refuses them by name, without opening anything. */
    static const char *const refused[]={"stag0401","dng412b4","stagGF04"},*const kept[]={"stagML11","StagML12","stagML13","stagML02","stagIS12","stag0001","stag0101","stagGF03","dng101b1","dng101b2","dng102b1","dng102b2","dng102b3","stag0102"};   /* the practice stage, the Goblin Fortress chain, the Humid Cave and dng102b1 have runtimes (docs/combat.md, docs/dungeon-floors.md); dng102b2 (camera from the box rig), dng102b3 (Mammothmon) and stag0102 have runtimes too (dungeonroute2) */
    for(unsigned i=0;i<sizeof refused/sizeof *refused;i++) {
        assert(!dw4_hubruntime_destination_available(refused[i]));
        dw4_hubruntime_source source={players,&state,NULL,0};
        assert(!dw4_hubruntime_prepare(&mount,&source,refused[i],0,1,error,sizeof error) && strstr(error,"not available"));
    }
    for(unsigned i=0;i<sizeof kept/sizeof *kept;i++)assert(dw4_hubruntime_destination_available(kept[i]));
    assert(!dw4_hubruntime_destination_available(NULL));
    puts("hub gates: field and dungeon destinations are refused as not available");

    clear_story();party_exit_case("stagML12","matz00","stagML11",1,1);   /* the one-player baseline of the party exit below */
    /* A party (NINZU 2) is admitted by the four hub worlds and the field worlds; the digivolution demo and the interface scenes still take the
     * single player-zero owner and say so. */
    assert(!dw4_playerrecords_create(players,db,1,"p_agumon","Mate",error,sizeof error));
    set_flag(409,0);
    {
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",2) && !dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",1),"ISUSE",1));
        static const char *const solo[]={"stagML14","stagIS11","stagIS12","stagIS13"};
        for(unsigned i=0;i<4;i++){
            dw4_hubruntime_source source={players,&state,NULL,0};
            assert(!dw4_hubruntime_prepare(&mount,&source,solo[i],0,1,error,sizeof error) && strstr(error,"single joined player-zero owner"));
        }
        dw4_hubruntime_source source={players,&state,NULL,0};
        dw4_hubruntime *party=dw4_hubruntime_prepare(&mount,&source,"stagML11",0,1,error,sizeof error);
        if(!party)fprintf(stderr,"party Terminal: %s\n",error);
        assert(party && dw4_lobby_player_count(dw4_hubruntime_world(party))==2);
        dw4_hubruntime_close(party);
        clear_story();
        party_exit_case("stagML12","matz00","stagML11",1,2);
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",1) && !dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",1),"ISUSE",0));
        assert(!dw4_playerrecords_create(players,db,2,"p_vmon","Mate3",error,sizeof error) && !dw4_playerrecords_create(players,db,3,"p_girumon","Mate4",error,sizeof error));
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",4));
        for(int q=1;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",q),"ISUSE",1));
        party_exit_case("stagML12","matz00","stagML11",1,4);
        for(int q=2;q<4;q++)assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",q),"ISUSE",0));
        assert(!dw4_property_set_number(dw4_playerrecords_get(players,"GETCOMMON",0),"NINZU",1) && !dw4_property_set_number(dw4_playerrecords_get(players,"GETPLAYER",1),"ISUSE",0));
    }
    puts("hub gates: a party opens the hub worlds; the demo and interface scenes keep the single owner");

    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts("hub gates: original pad scripts clear the label, open their prompts and route accept/No/Circle");
    return 0;
}
