/* Digi-Lab (SUBWND LABO, retail beNDMWShopCtrlDigilabo 431760 / beNDMWShopCtrlEvolve 42f710) through the normal
 * prepared Central hub runtime. Headless. Central's lab Digi-Elf (n_digilff slot 1) is reached by the live Cross
 * probe and the original script chain (hit_n_digilff -> n_digilff_01 -> prompt -> labo.lua -> SUBWND GENERATE LABO);
 * the menus, the form list, the confirmations and the evolution transaction run natively over the original text.
 * After an evolution the closing script requests stagML14, which runs natively as the digivolution demo to its own exit.
 * Fixtures are limited to unlocking a second form (BASE_ISUSE) and the DEVICEFOLDER item list. */
#include "hubtest.h"
#include "dw4/evodemo.h"
static void up(dw4_hubruntime *h){step(h,1,0);idle(h,8);}
static dw4_property_folder *player(dw4_hubruntime *h){return dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);}
static int32_t number_of(dw4_hubruntime *h,const char *key){int32_t v;assert(!dw4_property_number(player(h),key,&v));return v;}
static void dump(dw4_hubruntime *h,const char *what)
{
    const dw4_dialogue *d=dw4_hubruntime_dialogue(h);fprintf(stderr,"\n[%s] texts:",what);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++){const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(t->visible && t->count)fprintf(stderr," %s/%s",t->group,t->name);}
    fprintf(stderr,"\n");
}
/* Talk to Central's lab Digi-Elf, accept the first prompt entry and wait for the lab menu. */
static void enter_labo(dw4_hubruntime *h)
{
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilff",1);assert(npc);
    assert(talk_to(h,npc));
    unsigned k=0;
    for(;k<3000 && !(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02"));k++)step(h,0,k%45==44?0x4000:0);
    assert(k<3000);
    idle(h,60);press(h,0x4000);
    for(k=0;k<1500 && !has_text(h,"TALKFONT01","font01");k++)step(h,0,0);
    if(k>=1500)dump(h,"no lab menu");
    fprintf(stderr,"\nstatus_active=%d k=%u\n",dw4_hubruntime_status_active(h),k);
    assert(k<1500);
    idle(h,60);
}
/* Choose a row of the current menu. */
static void pick(dw4_hubruntime *h,unsigned entry)
{
    /* The selector consumes the first cursor tap after a move (the move latch clears on the next input frame). */
    idle(h,60);
    for(unsigned i=0;i<entry;i++){if(i){down(h);idle(h,70);}down(h);idle(h,70);}
    press(h,0x4000);idle(h,90);
}
static const dw4_databases *dbs(dw4_hubruntime *h){return dw4_hubruntime_databases(h);}
static const char *species_model(void *u,int32_t row){return dw4_database_string(dw4_databases_get(u,"shinka"),row,"MODEL_NAME");}
static const char *item_string(void *u,const dw4_item_record *i,const char *key){return dw4_statuscontent_item_string(u,i,key);}
/* A second form becomes available (the lab lists the BASE_ISUSE members). Returns its species row. */
static int32_t unlock_form(dw4_hubruntime *h)
{
    int32_t cur=number_of(h,"DIGIMONNO");size_t n;const int32_t *use=dw4_property_array(player(h),"BASE_ISUSE",&n);assert(use && n==16);
    int32_t target=(cur+1)%16,unlocked[16];memcpy(unlocked,use,sizeof unlocked);unlocked[target]=1;
    assert(!dw4_property_set_array(player(h),"BASE_ISUSE",unlocked,16));
    return target;
}
static void expect_list(dw4_hubruntime *h,int32_t selected)
{
    dw4_status_skillrow list[16];size_t n;
    assert(!dw4_statuscontent_skill_list(dw4_hubruntime_records(h),dbs(h),0,list,&n) && n>=2);
    for(size_t i=0;i<8;i++){
        char font[16];snprintf(font,sizeof font,"font%03zu",i);
        assert(has_text(h,"STWINFONT20",font)==(i<n));
        if(i<n){
            char level[16];snprintf(level,sizeof level,"%d",list[i].level);
            const char *name=text_value(h,"STWINFONT20",font);
            assert(name && !strcmp(name,list[i].name) && !strcmp(text_value(h,"STWINFONT43",font),"Lv") && !strcmp(text_value(h,"STWINFONT21",font),level));
        }
    }
    int32_t form[16];assert(!dw4_playerstats_form(dbs(h),player(h),list[selected].species,form));
    static const char *const values[16]={"font030","font031","font040","font041","font042","font043","font044",
        "font050","font051","font052","font053","font054","font055","font056","font057","font058"};
    for(unsigned i=0;i<16;i++){char want[16];snprintf(want,sizeof want,"%d",form[i]);
        const char *shown=text_value(h,"STWINFONT22",values[i]);
        if(!shown || strcmp(shown,want))fprintf(stderr,"form value %s shown '%s' want '%s'\n",values[i],shown?shown:"(none)",want);
        assert(shown && !strcmp(shown,want));}
    assert(has_text(h,"STWINFONT29","font000"));
}
static void wait_menu(dw4_hubruntime *h){unsigned k=0;for(;k<900 && !(has_text(h,"TALKFONT01","font01") && has_text(h,"TALKFONT01","font03"));k++)step(h,0,0);assert(k<900);idle(h,60);}
static void wait_list(dw4_hubruntime *h){assert(wait_text(h,"STWINFONT20","font000",900) && wait_text(h,"STWINFONT20","font001",100));idle(h,90);}
static int has_travel(dw4_hubruntime *h,const char *stage)
{const dw4_stagetravel *t=dw4_hubruntime_travel(h);return t->pending && !strcmp(t->destination,stage);}
static dw4_mount *world_mount;
/* The application's travel step (engine.c begin_hub_load): the pending request prepares the destination from the source runtime's
 * records, state, input and clock, the source is released, and the destination runs its arrival until the player has control. */
static dw4_hubruntime *travel_to(dw4_hubruntime *h)
{
    char stage[128],error[512];int32_t point;
    assert(dw4_stagetravel_pending(dw4_hubruntime_travel(h),stage,sizeof stage,&point)==1);
    dw4_hubruntime_source src={dw4_hubruntime_records(h),dw4_hubruntime_state(h),dw4_hubruntime_input_state(h),dw4_hubruntime_time(h)};
    dw4_hubruntime *next=dw4_hubruntime_prepare(world_mount,&src,stage,point,1,error,sizeof error);
    if(!next){fprintf(stderr,"prepare %s: %s\n",stage,error);assert(0);}
    dw4_hubruntime_close(h);
    return next;
}
static dw4_hubruntime *travel_on(dw4_hubruntime *h)
{
    dw4_hubruntime *next=travel_to(h);
    unsigned t=0;
    for(;t<1500;t++){step(next,0,0);if(t>30 && control(next) && dw4_lobby_intro_done(dw4_hubruntime_world(next)))break;}
    assert(t<1500);idle(next,30);
    return next;
}
/* The digivolution demo stagML14 (dw4/evodemo.h): it opens as a scene host, the original chunk 0 chooses the old and new s_<species>
 * models from COUNTER[8] and SYSgetPlayerDigimon, the demo camera and DM_EVOLV/AM_EVOLV start, the old model enters, the swap
 * effects run, the new model plays SQ_ENJOY, and the script's own exit requests Central point 3. Frames with each model are drawn
 * on the CPU (captured with a capture directory) and must show the model over the authored background. */
static unsigned draw_demo(dw4_hubruntime *h,const char *tag)
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    int draws=dw4_hubruntime_draw(h,&fb,NULL);
    if(draws<0)fprintf(stderr,"draw %s: %s\n",tag,dw4_hubruntime_error(h));
    assert(draws>=0);
    /* Pixels that differ from the clear colour (the first pixel inside the letterbox band's centre row). */
    const uint8_t *bg=fb.rgba+4*((size_t)224*fb.w+2);unsigned drawn=0;
    for(size_t i=0;i<(size_t)fb.w*fb.h;i++)drawn+=abs(fb.rgba[4*i]-bg[0])+abs(fb.rgba[4*i+1]-bg[1])+abs(fb.rgba[4*i+2]-bg[2])>24;
    if(capture_dir){char path[512];snprintf(path,sizeof path,"%s/xdata-%s.png",capture_dir,tag);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
    dw4_fb_free(&fb);
    return drawn;
}
static const char *demo_sequence(dw4_hubruntime *h,const char *model)
{
    const dw4_modelctrl *m=find(dw4_hubruntime_models(h),model,4);assert(m);   /* single player: the joint RAM slot 4 */
    return dw4_modelctrl_drawable(m)?dw4_modelctrl_sequence(m):NULL;
}
static dw4_hubruntime *run_demo(dw4_hubruntime *h,int32_t old_row,int32_t new_row)
{
    h=travel_to(h);
    const dw4_evodemo *demo=dw4_hubruntime_demo(h);
    if(!demo){fprintf(stderr,"stagML14 did not open as the digivolution demo\n");assert(0);}
    assert(!dw4_hubruntime_world(h));
    dw4_evodemo_info info;assert(!dw4_evodemo_info_get(demo,&info));
    char want_old[32],want_new[32];
    snprintf(want_old,sizeof want_old,"s_%s",dw4_lobby_model_name(old_row)+2);snprintf(want_new,sizeof want_new,"s_%s",dw4_lobby_model_name(new_row)+2);
    if(strcmp(info.old_model,want_old) || strcmp(info.new_model,want_new))
        fprintf(stderr,"demo models: old %s new %s (want %s %s)\n",info.old_model,info.new_model,want_old,want_new);
    assert(!strcmp(info.old_model,want_old) && !strcmp(info.new_model,want_new));
    unsigned t=0,old_shown=0,new_shown=0,old_frame=0,new_frame=0,wipe=0;
    for(;t<3000 && !dw4_hubruntime_travel(h)->pending;t++){
        step(h,0,0);
        const char *before=demo_sequence(h,want_old),*after=demo_sequence(h,want_new);
        if(before && !strcmp(before,"SQ_ENTR") && ++old_shown==60)old_frame=draw_demo(h,"evodemo-old");
        if(after && !strcmp(after,"SQ_ENJOY") && ++new_shown==45)new_frame=draw_demo(h,"evodemo-new");
        assert(!(before && after));   /* the swap never shows both forms */
        const char *w=demo_sequence(h,"i_evowipe");if(w && !strcmp(w,"SQ_WTIN20"))wipe=1;
    }
    assert(t<3000);
    assert(!dw4_evodemo_info_get(demo,&info));
    printf("hub LABO demo: camera %s, sounds [%s], old SQ_ENTR %u ticks (%u px), new SQ_ENJOY %u ticks (%u px)\n",
        info.camera_demo?"entry":"none",info.sounds,old_shown,old_frame,new_shown,new_frame);
    assert(info.camera_demo && info.camera_end && info.camera_ns==info.camera_end && info.music[0] && info.music[1]);
    assert(old_shown>=60 && new_shown>=45 && wipe);
    assert(old_frame>640*448/20 && new_frame>640*448/5);
    char stage[64];int32_t point;
    assert(dw4_stagetravel_pending(dw4_hubruntime_travel(h),stage,sizeof stage,&point)==1 && !strcasecmp(stage,"stagML12") && point==3);
    printf("hub LABO demo: stagML14 ran %u ticks (%s -> %s) to its own exit stagML12 point 3\n",t,want_old,want_new);
    return h;
}
/* The world shows the record's form and equipped weapon: the lobby's player model row (which also selects the HUD portrait), the
 * weapon graph from POWERSOCKETNAME[0] (none when unarmed), the HUD level/HP/MP from the record, and a drawn frame with the weapon. */
static void expect_world(dw4_hubruntime *h,const char *tag,int32_t row,const char *weapon_model)
{
    dw4_lobby *world=dw4_hubruntime_world(h);
    const char *model=dw4_database_string(dw4_databases_get(dbs(h),"shinka"),row,"MODEL_NAME");
    const char *name=dw4_property_string(player(h),"DIGIMONNAME"),*socket=dw4_property_string_at(player(h),"POWERSOCKETNAME",0);
    assert(model && name && !strcmp(name,model) && number_of(h,"DIGIMONNO")==row);
    assert(weapon_model?socket && !strcmp(socket,weapon_model):!socket);
    assert(dw4_lobby_player_row(world)==row && !strcmp(dw4_lobby_model_name(row),model));
    dw4_lobby_player_state ps;assert(!dw4_lobby_player(world,&ps));
    if(weapon_model){
        char want[40];snprintf(want,sizeof want,"%s.igb",weapon_model);
        assert(!strcmp(ps.weapon_asset,want) && ps.weapon_triangles>0 && dw4_lobby_weapon_parts(world)>0);
    }else assert(!*ps.weapon_asset && !ps.weapon_triangles && !dw4_lobby_weapon_parts(world));
    assert(ps.motion && *ps.motion && ps.label && *ps.label);
    /* HUD: the record's level/HP/MP were published to the destination's meters. */
    dw4_playerhealth hp;char error[256];assert(!dw4_playerhealth_restore(dw4_hubruntime_records(h),0,&hp,error,sizeof error));
    assert(hp.level==number_of(h,"LEVEL") && hp.max_hp==number_of(h,"MHP") && hp.max_mp==number_of(h,"MMP"));
    for(unsigned m=0;m<2;m++){
        const dw4_hudmeter *meter=dw4_lobby_hud_meter(world,m);assert(meter);
        float target,maximum;memcpy(&target,&meter->target,4);memcpy(&maximum,&meter->maximum,4);
        float want=100.0f*(m?hp.mp:hp.hp)/(float)(m?hp.max_mp:hp.max_hp);
        assert(maximum>0 && fabsf(100.0f*target/maximum-want)<0.5f+100.0f/maximum);
    }
    draw_frame(h,tag);
    assert(!dw4_lobby_player(world,&ps));
    if(weapon_model)assert(ps.weapon_submitted_triangles>0);
    printf("hub LABO world %s: %s (row %d) with %s, Lv %d HP %d/%d MP %d/%d, motion %s\n",tag,model,row,
        weapon_model?ps.weapon_asset:"no weapon",hp.level,hp.hp,hp.max_hp,hp.mp,hp.max_mp,ps.motion);
}
static void accept_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    int32_t target=unlock_form(h),cur=number_of(h,"DIGIMONNO");
    /* The current form has progressed beyond its saved base. */
    assert(!dw4_property_set_number(player(h),"LEVEL",9) && !dw4_property_set_number(player(h),"EXP",77));
    enter_labo(h);
    assert(!has_text(h,"TALKFONT01","font04"));
    draw_frame(h,"labo-menu");
    pick(h,0);wait_list(h);
    expect_list(h,0);draw_frame(h,"labo-list");
    down(h);idle(h,90);expect_list(h,1); /* the detail panel follows the highlighted form */
    press(h,0x4000);idle(h,90);
    assert(has_text(h,"STWINFONT29","font000") && has_text(h,"STWINFONT29","font001")); /* 0x4E7 confirmation */
    draw_frame(h,"labo-confirm");
    pick(h,0);assert(wait_text(h,"STWINFONT29","font000",300));press(h,0x4000);idle(h,60); /* 0x4E9 notice */
    assert(has_text(h,"STWINFONT29","font001")||wait_text(h,"STWINFONT29","font001",300));idle(h,60);
    assert(number_of(h,"DIGIMONNO")==cur);
    press(h,0x4000);unsigned k=0; /* 0x4EA: yes commits */
    for(;k<600 && number_of(h,"DIGIMONNO")==cur;k++)step(h,0,0);
    assert(k<600);
    const char *model=dw4_database_string(dw4_databases_get(dbs(h),"shinka"),target,"MODEL_NAME");int32_t row=0;
    for(int32_t r=0;r<16;r++){const char *m=dw4_database_string(dw4_databases_get(dbs(h),"shinka"),r,"MODEL_NAME");if(m && !strcmp(m,model)){row=r;break;}}
    assert(number_of(h,"DIGIMONNO")==row);
    const int32_t *bl=dw4_property_array(player(h),"BASE_LEVEL",(size_t[]){0});assert(bl && bl[cur]==9);
    draw_frame(h,"labo-evolved");
    /* Notice 0x4EC, then Digilabo's "check weapons?" message (0x4ED) and its yes/no (1262): no returns to the menu. */
    assert(wait_text(h,"STWINFONT29","font100",600));idle(h,60);press(h,0x4000);
    if(!wait_text(h,"TALKFONT01","font00",900))dump(h,"after notice 4EC");
    assert(has_text(h,"TALKFONT01","font00"));idle(h,60);press(h,0x4000);
    assert(wait_text(h,"TALKFONT01","font01",900) && has_text(h,"TALKFONT01","font02") && !has_text(h,"TALKFONT01","font03"));
    pick(h,1);wait_menu(h);
    assert(!has_travel(h,"stagML14") && dw4_hubruntime_status_active(h)==2);
    /* Return to Main Lobby: the changes are confirmed (0x4F3 message, 1268 yes/no) and the closing script runs. */
    pick(h,2);if(!wait_text(h,"TALKFONT01","font00",900))dump(h,"after exit pick");
    assert(has_text(h,"TALKFONT01","font00"));idle(h,60);press(h,0x4000);
    assert(wait_text(h,"TALKFONT01","font01",900) && has_text(h,"TALKFONT01","font02"));
    pick(h,0);
    for(k=0;k<1500 && !has_travel(h,"stagML14");k++)step(h,0,0);
    if(k>=1500)dump(h,"no stage request");
    assert(k<1500 && !dw4_hubruntime_status_active(h));
    assert(number_of(h,"DIGIMONNO")==row);
    printf("hub LABO evolve: list, per-form detail, three confirmations, the evolution transaction, exit confirmation and the closing stage request pass\n");
    /* Central travels on: the destination stands the evolved form with the weapon WEAPONEQUIPSTRONG chose. */
    char weapon[32];const char *socket=dw4_property_string_at(player(h),"POWERSOCKETNAME",0);
    assert(socket && strlen(socket)<sizeof weapon);snprintf(weapon,sizeof weapon,"%s",socket);
    h=run_demo(h,cur,row);
    h=travel_on(h);
    /* The demo's own exit: Central point 3. */
    {dw4_lobby_world_state ws;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&ws) && !strcasecmp(ws.stage,"stagML12") && ws.arrival_point==3);}
    expect_world(h,"labo-evolved-world",row,weapon);
    dw4_hubruntime_close(h);
}
/* Choosing the current form and a form without a usable weapon are refused with their notices. */
static void refusal_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    int32_t target=unlock_form(h),cur=number_of(h,"DIGIMONNO");(void)target;
    enter_labo(h);pick(h,0);wait_list(h);
    /* The first row is the current form (species 3 sorts first only when it is a member). */
    dw4_status_skillrow list[16];size_t n;assert(!dw4_statuscontent_skill_list(dw4_hubruntime_records(h),dbs(h),0,list,&n));
    size_t same=0;while(same<n && list[same].species!=cur)same++;
    assert(same<n);
    for(size_t i=0;i<same;i++){down(h);idle(h,40);}
    press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);
    assert(number_of(h,"DIGIMONNO")==cur && !has_text(h,"STWINFONT29","font001"));
    draw_frame(h,"labo-same");
    press(h,0x4000);wait_list(h); /* the notice closes and the list returns */
    /* No owned weapon: the other form is refused with the second notice. */
    assert(!dw4_property_set_items(player(h),"DEVICEFOLDER",NULL,0));
    {static const int32_t none[5]={-1,-1,-1,-1,-1};
     assert(!dw4_property_set_array(player(h),"POWERSOCKETREF",none,3));}
    while(same>0){up(h);idle(h,40);same--;}
    size_t other=same==0?1:0;for(size_t i=0;i<other;i++){down(h);idle(h,40);}
    press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);
    assert(number_of(h,"DIGIMONNO")==cur);
    press(h,0x4000);wait_list(h);
    /* Cancel returns to the lab menu without changing anything. */
    press(h,0x2000);wait_menu(h);
    assert(number_of(h,"DIGIMONNO")==cur);
    /* Exit with no change: the "nothing changed" message (0x4FB) closes the lab without a stage request. */
    pick(h,2);assert(wait_text(h,"TALKFONT01","font00",900));idle(h,60);press(h,0x4000);
    unsigned k=0;for(;k<900 && dw4_hubruntime_status_active(h);k++)step(h,0,0);
    assert(k<900 && !has_travel(h,"stagML14") && !has_travel(h,"stagML12"));
    idle(h,200);assert(!dw4_hubruntime_travel(h)->pending);
    printf("hub LABO refusals: same form and unusable weapons are refused, cancel and an unchanged exit leave the record alone\n");
    dw4_hubruntime_close(h);
}
/* Declining either confirmation returns to the list; nothing is evolved. */
static void decline_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    int32_t target=unlock_form(h),cur=number_of(h,"DIGIMONNO");(void)target;
    enter_labo(h);pick(h,0);wait_list(h);
    dw4_status_skillrow list[16];size_t n;assert(!dw4_statuscontent_skill_list(dw4_hubruntime_records(h),dbs(h),0,list,&n));
    size_t other=list[0].species==cur?1:0;
    for(size_t i=0;i<other;i++){down(h);idle(h,90);}
    press(h,0x4000);idle(h,90);
    assert(has_text(h,"STWINFONT29","font001"));
    pick(h,1);wait_list(h); /* first confirmation: no */
    assert(number_of(h,"DIGIMONNO")==cur);
    press(h,0x4000);idle(h,90);pick(h,0);assert(wait_text(h,"STWINFONT29","font000",300));press(h,0x4000);idle(h,90);
    assert(has_text(h,"STWINFONT29","font001"));
    pick(h,1);wait_list(h); /* second confirmation: no */
    assert(number_of(h,"DIGIMONNO")==cur);
    press(h,0x2000);wait_menu(h); /* cancel the list */
    assert(number_of(h,"DIGIMONNO")==cur);
    printf("hub LABO decline: refusing either confirmation or cancelling the list leaves the form unchanged\n");
    dw4_hubruntime_close(h);
}
/* "Exchange Weapon Unit" embeds the STATUS equipment menu; a changed weapon set makes the exit ask for confirmation. */
static void check_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    enter_labo(h);
    char header[64];{const char *t=text_value(h,"STWINFONT12","font000");assert(t && *t);snprintf(header,sizeof header,"%s",t);}
    pick(h,1);
    assert(wait_text(h,"STWINFONT09","font000",900));idle(h,60);
    assert(!has_text(h,"TALKFONT01","font01"));
    /* Retail (431e5c) binds the check with entry code 1: the equipment menu opens the bottom band, not its Title04 header,
     * so the "Digi-Lab" header text stays (retail capture of the slot menu). */
    {const char *t=text_value(h,"STWINFONT12","font000");assert(t && !strcmp(t,header));}
    draw_frame(h,"labo-check");
    /* The player swaps the first weapon for another owned one through the normal equipment transaction while the menu is open.
     * Fixture: a second weapon the form can equip, with a different MODEL, is added to DEVICEFOLDER. */
    const char *old=dw4_property_string_at(player(h),"POWERSOCKETNAME",0);assert(old);
    char before[32];snprintf(before,sizeof before,"%s",old);
    const dw4_database *wdb=dw4_databases_get(dbs(h),"weapon");assert(wdb);
    size_t items;const dw4_item_record *folder=dw4_property_items(player(h),"DEVICEFOLDER",&items);assert(folder && items);
    size_t own=0;while(own<items && folder[own].kind!=0)own++;
    assert(own<items);
    dw4_item_record extra=folder[own];extra.equipped=0;extra.record=-1;
    int32_t species=number_of(h,"DIGIMONNO");
    for(int32_t r=0;r<(int32_t)dw4_database_string_rows(wdb) && extra.record<0;r++){
        const char *m=dw4_database_string(wdb,r,"MODEL");int32_t soubi;
        if(m && *m && strcmp(m,before) && !dw4_database_number(wdb,r,"SOUBI",&soubi) && ((uint32_t)soubi>>species&1))extra.record=r;
    }
    assert(extra.record>=0);
    {dw4_item_record list[64];assert(items<64);memcpy(list,folder,items*sizeof *list);list[items]=extra;
     assert(!dw4_property_set_items(player(h),"DEVICEFOLDER",list,items+1));}
    assert(!dw4_playertransactions_equip_database(dw4_hubruntime_records(h),0,"POWERSOCKET",0,(int32_t)items,dbs(h)));
    char after[32];const char *now=dw4_property_string_at(player(h),"POWERSOCKETNAME",0);
    assert(now && strcmp(now,before));snprintf(after,sizeof after,"%s",now);
    unsigned k=0;
    for(;k<12 && !has_text(h,"TALKFONT01","font03");k++){press(h,0x2000);idle(h,120);}
    if(k>=12)dump(h,"equipment menu did not close");
    assert(k<12);idle(h,60);
    /* The lab menu again (retail frame after leaving the equipment screen): the compact base only (no full stat rows), the
     * "Digi-Lab" header and legend back, and no equipment description left behind. */
    assert(has_text(h,"STWINFONT04","font000") && has_text(h,"STWINFONT34","font000") && !has_text(h,"STWINFONT04","font001"));
    assert(has_text(h,"STWINFONT12","font000") && !has_text(h,"STWINFONT29","font000") && !has_text(h,"STWINFONT06","font010"));
    gpu_compare(h,"labo-back");
    pick(h,2);assert(wait_text(h,"TALKFONT01","font00",900));idle(h,60);press(h,0x4000);
    assert(wait_text(h,"TALKFONT01","font01",900) && has_text(h,"TALKFONT01","font02"));
    pick(h,0);
    for(k=0;k<1500 && !has_travel(h,"stagML12");k++)step(h,0,0);
    if(k>=1500)dump(h,"no stage request");
    assert(k<1500);
    printf("hub LABO check: the embedded equipment menu closes back to the lab and its weapon change is confirmed at exit\n");
    /* Central reopens: the same form stands with the newly equipped weapon. */
    int32_t row=number_of(h,"DIGIMONNO");
    h=travel_on(h);
    expect_world(h,"labo-exchange-world",row,after);
    dw4_hubruntime_close(h);
}
/* A form with no equipped weapon (imported/edited state: the lab itself refuses such a form, so here the evolution transaction runs
 * directly with an empty weapon inventory and WEAPONEQUIPSTRONG leaves nothing equipped). The destination opens the unarmed
 * appearance, the player walks, and the live appearance swap goes armed and back to unarmed. */
static void unarmed_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    int32_t target=unlock_form(h);
    assert(!dw4_property_set_items(player(h),"DEVICEFOLDER",NULL,0));
    {static const int32_t none[3]={-1,-1,-1};assert(!dw4_property_set_array(player(h),"POWERSOCKETREF",none,3));}
    int eligible=1;
    assert(!dw4_playertransactions_weapon_check(dw4_hubruntime_records(h),0,target,dw4_playerstats_item_attribute,(void *)dbs(h),&eligible) && !eligible);
    assert(!dw4_playertransactions_evolve(dw4_hubruntime_records(h),0,target,species_model,(void *)dbs(h),
        dw4_playerstats_item_attribute,item_string,(void *)dbs(h),dw4_playerstats_recalculate,(void *)dbs(h)));
    int32_t row=number_of(h,"DIGIMONNO");
    assert(!dw4_property_string_at(player(h),"POWERSOCKETNAME",0));
    dw4_hubruntime_dev_travel(h,"stagML12",0);
    h=travel_on(h);
    expect_world(h,"labo-unarmed-world",row,NULL);
    dw4_lobby_player_state ps;assert(!dw4_lobby_player(dw4_hubruntime_world(h),&ps));
    char label[16];snprintf(label,sizeof label,"%s",ps.label);
    assert(!strcmp(label,"dual"));
    /* The unarmed player still walks on its own run motion. */
    dw4_lobby_walk_state w0,w1;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w0));
    for(unsigned i=0;i<45;i++){dw4_hubruntime_input(h,0,-1,0,0,0);
        if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){fprintf(stderr,"walk: %s\n",dw4_hubruntime_error(h));assert(0);}}
    assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w1));
    assert(fabsf(w1.position[0]-w0.position[0])+fabsf(w1.position[2]-w0.position[2])>1);
    idle(h,30);
    /* Live appearance publication (the STATUS/lab equipment callback): armed, then unarmed again. */
    char error[256];
    assert(!dw4_lobby_weapon(dw4_hubruntime_world(h),mount,"w_common04",error,sizeof error));
    assert(!dw4_lobby_player(dw4_hubruntime_world(h),&ps) && !strcmp(ps.weapon_asset,"w_common04.igb") && ps.weapon_triangles>0);
    assert(!dw4_lobby_weapon(dw4_hubruntime_world(h),mount,"",error,sizeof error));
    assert(!dw4_lobby_player(dw4_hubruntime_world(h),&ps) && !*ps.weapon_asset && !ps.weapon_triangles && !strcmp(ps.label,"dual"));
    draw_frame(h,"labo-unarmed-again");
    printf("hub LABO unarmed: a form with no weapon opens without a weapon graph on its first authored motion section, walks, and swaps live\n");
    dw4_hubruntime_close(h);
}
/* The explicit fallback: with DW4_EVODEMO=skip a stagML14 request is prepared as the demo's authored exit (Central point 3, logged),
 * standing the evolved form, as the port did before the demo was native. */
static void skip_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    int32_t target=unlock_form(h);
    assert(!dw4_playertransactions_evolve(dw4_hubruntime_records(h),0,target,species_model,(void *)dbs(h),
        dw4_playerstats_item_attribute,item_string,(void *)dbs(h),dw4_playerstats_recalculate,(void *)dbs(h)));
    int32_t row=number_of(h,"DIGIMONNO");
    char weapon[32];const char *socket=dw4_property_string_at(player(h),"POWERSOCKETNAME",0);
    assert(socket && strlen(socket)<sizeof weapon);snprintf(weapon,sizeof weapon,"%s",socket);
    assert(!setenv("DW4_EVODEMO","skip",1));
    dw4_hubruntime_dev_travel(h,"stagML14",0);
    h=travel_on(h);
    assert(!unsetenv("DW4_EVODEMO"));
    assert(!dw4_hubruntime_demo(h));
    {dw4_lobby_world_state ws;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&ws) && !strcasecmp(ws.stage,"stagML12") && ws.arrival_point==3);}
    expect_world(h,"labo-skip-world",row,weapon);
    printf("hub LABO demo fallback: DW4_EVODEMO=skip continues a stagML14 request at Central point 3\n");
    dw4_hubruntime_close(h);
}
int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));world_mount=&mount;
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubLabo",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    frame=0;dw4_hubruntime *h=boot_central(&mount,&initial);
    dw4_hubruntime_close(h);
    frame=0;accept_flow(&mount,&initial);
    frame=0;refusal_flow(&mount,&initial);
    frame=0;decline_flow(&mount,&initial);
    frame=0;check_flow(&mount,&initial);
    frame=0;unarmed_flow(&mount,&initial);
    frame=0;skip_flow(&mount,&initial);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts("hub labo: NPC reach, lab menu, form list, evolution, digivolution demo, refusals, declines, weapon exchange, exit and demo fallback pass");
    return 0;
}
