/* The Commander Room (stagML02, NDMW 815/816) through the normal prepared hub runtime. Headless, CPU frames (GPU compared when a
 * context exists). Everything runs from the original bytecode:
 *   Terminal mate01 (the Commander Room gate) -> confirmation -> STAGECTL NEXTSTAGE stagML02 point 0 -> prepared Commander Room;
 *   first.lua's Digi-Elf welcome (flag 502, demo camera camsp0201), start.lua's NPCs/music (ST_COMMA, AM_LOBBY);
 *   the matg00 point label "Gate to Main Lobby"; matf00's first briefing by Ophanimon (flag 1 -> 2, PLAYatPAUSE/PAUSEOFF DM_OFNI);
 *   Ophanimon's talk script; the mate00 exit prompt (Circle keeps the player, Cross travels) -> stagML11 point 0 -> Terminal.
 * Later story states are entered with progress-flag fixtures only (the flags the field stages would have set) and run the room's
 * other original events: the Leomon report (first.lua, flags 2+20), Ophanimon's ID hand-over (matf00, flag 67), the alarm-off
 * scene with the moving pass and its HITLANDMODEL wall (first.lua/start.lua, flags 3+324), Seraphimon's report (matf02, flags
 * 4+335) and Ophanimon's Lucemon briefing (matf00, flags 5+69). Player placement uses dw4_lobby_place_player (MOVETRANS). */
#include "hubtest.h"
#include "dw4/frontaudio.h"
static int flag(dw4_playerrecords *p,int32_t n)
{
    dw4_script_value a={DW4_SCRIPT_NUMBER,n,NULL,0},r;char e[256];
    assert(!dw4_playerrecords_call(p,"FLGisOn",&a,1,&r,e,sizeof e));return (int)r.number;
}
static void set_flag(dw4_playerrecords *p,int32_t n,int32_t v)
{
    dw4_script_value a[2]={{DW4_SCRIPT_NUMBER,n,NULL,0},{DW4_SCRIPT_NUMBER,v,NULL,0}},r;char e[256];
    assert(!dw4_playerrecords_call(p,"FLGset",a,2,&r,e,sizeof e));
}
/* The clip on the music (0) or ambience (1) voice. */
static const char *track(dw4_hubruntime *h,unsigned voice)
{
    const dw4_frontaudio *a=dw4_lobby_audio(dw4_hubruntime_world(h));
    const char *name=dw4_frontaudio_clip_name(a,dw4_frontaudio_voice_clip(a,voice,NULL));return name?name:"";
}
static const char *speaker(dw4_hubruntime *h){const char *s=has_text(h,"TALKFONT03","font00")?text_value(h,"TALKFONT03","font00"):NULL;return s?s:"";}
static int any_message(dw4_hubruntime *h)
{return has_text(h,"TALKFONT01",NULL) || has_text(h,"TALKFONT02",NULL) || has_text(h,"TALKFONT03",NULL);}
static void shot(dw4_hubruntime *h,const char *tag)
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    int triangles=dw4_hubruntime_draw(h,&fb,NULL);
    if(triangles<=0)fprintf(stderr,"draw %s: %s\n",tag,dw4_lobby_script_error(dw4_hubruntime_world(h)));
    assert(triangles>0);
    unsigned lit=0;for(size_t i=0;i<(size_t)fb.w*fb.h;i++)lit+=fb.rgba[4*i] || fb.rgba[4*i+1] || fb.rgba[4*i+2];
    assert(lit>1000);
    if(capture_dir){char path[512];snprintf(path,sizeof path,"%s/commander-%s.png",capture_dir,tag);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
    dw4_fb_free(&fb);
    gpu_compare(h,tag);
}
/* Press Cross through scripted messages until the player has control again and no window is open. */
static unsigned settle(dw4_hubruntime *h,unsigned max)
{
    unsigned quiet=0,t=0;
    for(;t<max && quiet<30;t++){
        step(h,0,!control(h) && t%45==44?0x4000:0);
        quiet=control(h) && !any_message(h) && !dw4_hubruntime_input_state(h)->disabled?quiet+1:0;
    }
    assert(t<max);return t;
}
/* Collect every distinct message page the run shows (first 24 characters), for assertions on the original texts. */
struct pages {char text[64][28];unsigned n;};
static void collect(dw4_hubruntime *h,struct pages *p)
{
    const char *v=has_text(h,"TALKFONT02","font00")?text_value(h,"TALKFONT02","font00"):has_text(h,"TALKFONT01","font00")?text_value(h,"TALKFONT01","font00"):NULL;
    if(!v || p->n==64)return;
    char key[28];snprintf(key,sizeof key,"%.24s",v);
    for(char *c=key;*c;c++)if((unsigned char)*c<32 || (unsigned char)*c>126)*c=' ';
    for(unsigned i=0;i<p->n;i++)if(!strcmp(p->text[i],key))return;
    strcpy(p->text[p->n++],key);
}
static int shown(const struct pages *p,const char *prefix)
{for(unsigned i=0;i<p->n;i++)if(!strncmp(p->text[i],prefix,strlen(prefix)))return 1;return 0;}
/* Run an event to its end with Cross on every page; keep its pages. */
static unsigned play_event(dw4_hubruntime *h,struct pages *p,unsigned max,const char *tag)
{
    unsigned quiet=0,t=0,talked=0,shown_for=0;
    for(;t<max && quiet<40;t++){
        step(h,0,!control(h) && t%45==44?0x4000:0);
        collect(h,p);talked|=any_message(h);
        if(tag && any_message(h) && ++shown_for==40)shot(h,tag);   /* a frame with the message window open */
        quiet=talked && control(h) && !any_message(h) && !dw4_hubruntime_input_state(h)->disabled?quiet+1:0;
    }
    if(t>=max){fprintf(stderr,"event did not end: control=%d pages=%u\n",control(h),p->n);assert(0);}
    return t;
}
static dw4_hubruntime *boot(dw4_mount *m,const dw4_hubruntime_source *s,const char *stage,int32_t point)
{
    char error[512];dw4_hubruntime *h=dw4_hubruntime_prepare(m,s,stage,point,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare %s: %s\n",stage,error);assert(0);}
    return h;
}
/* Follow a pending original travel request into its destination, as the application consumer does. */
static dw4_hubruntime *follow(dw4_mount *m,dw4_hubruntime *from,const char *stage,int32_t point)
{
    const dw4_stagetravel *t=dw4_hubruntime_travel(from);
    if(!t->pending || strcasecmp(t->destination,stage) || t->generate_pos!=point)
        fprintf(stderr,"travel: pending %d %s point %d, expected %s point %d\n",t->pending,t->destination,t->generate_pos,stage,point);
    assert(t->pending && !strcasecmp(t->destination,stage) && t->generate_pos==point);
    dw4_stageinput input=*dw4_hubruntime_input_state(from);assert(input.disabled);
    dw4_hubruntime_source s={dw4_hubruntime_records(from),dw4_hubruntime_state(from),&input,dw4_hubruntime_time(from)};
    dw4_hubruntime *to=boot(m,&s,t->destination,t->generate_pos);
    dw4_hubruntime_close(from);return to;
}
/* Stand on a gate pad, wait for its travel prompt (the label is cleared first) and answer it. */
static void gate(dw4_hubruntime *h,float x,float y,float z,const char *prompt,uint32_t answer)
{
    assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),x,y,z,0));
    unsigned t=0;for(;t<300 && !has_text(h,"STCHGFONT00","font00");t++)step(h,0,0);
    assert(t<300);
    const char *v=text_value(h,"STCHGFONT00","font00");
    if(!v || !strstr(v,prompt)){fprintf(stderr,"gate prompt '%s', expected '%s'\n",v?v:"",prompt);assert(0);}
    assert(!has_text(h,"POINTFONT00",NULL) && !control(h));
    idle(h,60);step(h,0,answer);
}
static void main_route(dw4_mount *mount,const dw4_hubruntime_source *fresh)
{
    /* The Terminal: the first-visit introduction, then the Commander Room gate (Terminal mate01, flag 424 clear). */
    dw4_hubruntime *h=boot(mount,fresh,"stagML11",0);
    {unsigned t=0;for(;t<2600;t++){step(h,0,t%10==0?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}assert(t<2600);}
    idle(h,60);
    assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),-20,40,0,0));idle(h,90);
    assert(has_text(h,"POINTFONT00","font04") && strstr(text_value(h,"POINTFONT00","font04"),"Gate to Commander Room"));
    gate(h,5,30,15,"Commander Room",0x4000);
    {unsigned t=0;for(;t<400 && !dw4_hubruntime_travel(h)->pending;t++)step(h,0,0);assert(t<400);}
    printf("commander: Terminal mate01 'Gate to Commander Room' -> 'Commander Room' prompt -> NEXTSTAGE stagML02 point 0\n");
    assert(flag(dw4_hubruntime_records(h),502)==0);   /* first.lua sets it during preparation */
    h=follow(mount,h,"stagML02",0);

    /* Arrival: authored environment, regions and the first-visit welcome under demo camera camsp0201. */
    dw4_lobby *world=dw4_hubruntime_world(h);dw4_lobby_world_state info;assert(!dw4_lobby_world_info(world,&info));
    printf("commander: stagML02 point %d, %u camera regions, %u materials, %u floor / %u wall triangles\n",info.arrival_point,info.camera_regions,info.materials,info.floor_triangles,info.wall_triangles);
    assert(!strcmp(info.stage,"stagML02") && info.arrival_point==0 && info.materials==5 && info.camera_regions>1 && info.floor_triangles && info.wall_triangles);
    static const char *regions[]={"mate00","matg00","matf00","matf01","matf02"};
    for(unsigned i=0;i<5;i++)assert(dw4_lobby_material_region(world,regions[i],NULL,NULL)>=0);
    struct pages welcome={0};int demo=0;unsigned t=0,quiet=0,open=0;
    for(;t<3000 && quiet<40;t++){
        step(h,0,!control(h) && t%45==44?0x4000:0);
        dw4_lobby_control_state c;assert(!dw4_lobby_control(world,&c));demo|=!c.box_camera && t>10;
        collect(h,&welcome);
        if(t==120)shot(h,"welcome-camera");   /* camsp0201 follows the Digi-Elf's walk */
        if(any_message(h) && ++open==40)shot(h,"welcome");
        quiet=t>200 && control(h) && !any_message(h)?quiet+1:0;
    }
    assert(t<3000 && demo);
    dw4_playerrecords *r=dw4_hubruntime_records(h);
    assert(flag(r,502)==1 && flag(r,1)==1 && shown(&welcome,"Oh, I almost forgot."));
    dw4_lobby_control_state c;assert(!dw4_lobby_control(world,&c) && c.box_camera && c.player_control && c.material_updates && c.hud);
    printf("commander: first-visit welcome (%u pages, demo camera camsp0201) set flag 502 and returned control\n",welcome.n);
    if(strcmp(track(h,0),"ST_COMMA") || strcmp(track(h,1),"AM_LOBBY"))fprintf(stderr,"music '%s' / ambience '%s'\n",track(h,0),track(h,1));
    assert(!strcmp(track(h,0),"ST_COMMA") && !strcmp(track(h,1),"AM_LOBBY"));
    const dw4_controllers *models=dw4_hubruntime_models(h);
    const dw4_modelctrl *ofanim=find(models,"n_ofanim",0),*seraph=find(models,"n_seraph",0);
    assert(ofanim && dw4_modelctrl_active(ofanim) && seraph && !dw4_modelctrl_active(seraph));
    unsigned elves=0;for(int s=0;s<12;s++){const dw4_modelctrl *m=find(models,"n_digilff",s);elves+=m && dw4_modelctrl_active(m);
        m=find(models,"n_digilfm",s);elves+=m && dw4_modelctrl_active(m);}
    assert(elves==23); /* n_digilfm 0..10 and n_digilff 0..11 (start.lua) */
    idle(h,60);shot(h,"room");

    /* matg00: the room's only point label. */
    assert(!dw4_lobby_place_player(world,10,30,45,0));idle(h,120);
    const char *label=has_text(h,"POINTFONT00","font04")?text_value(h,"POINTFONT00","font04"):NULL;
    if(!label || !strstr(label,"Gate to Main Lobby")){fprintf(stderr,"label '%s'\n",label?label:"(none)");assert(0);}
    const dw4_modelctrl *cursor=find(models,"i_pointcur",4);
    assert(cursor && dw4_modelctrl_active(cursor) && !strcmp(dw4_modelctrl_sequence(cursor),"SQ_OPEN4"));
    shot(h,"label");
    assert(!dw4_lobby_place_player(world,-50,20,0,0));idle(h,120);assert(!has_text(h,"POINTFONT00",NULL));
    printf("commander: matg00 shows 'Gate to Main Lobby' with its arrow and clears it on leaving\n");

    /* matf00 with flag 1: Ophanimon's first briefing (DM_OFNI readied held, released on the first page). */
    struct pages brief={0};
    assert(!dw4_lobby_place_player(world,200,70,-100,0));
    int ofni=0;unsigned quiet2=0,k=0,talked=0;
    for(;k<3000 && quiet2<40;k++){
        step(h,0,!control(h) && k%45==44?0x4000:0);collect(h,&brief);talked|=any_message(h);
        ofni|=!strcmp(track(h,0),"DM_OFNI") && !strcmp(speaker(h),"Ophanimon");
        if(k==200)shot(h,"briefing");
        quiet2=talked && control(h) && !any_message(h)?quiet2+1:0;
    }
    assert(k<3000 && ofni && shown(&brief,"So you have just joined") && shown(&brief,"You are our only hope."));
    assert(flag(r,1)==0 && flag(r,2)==1 && flag(r,320)==1);
    {unsigned w=0;for(;w<300 && strcmp(track(h,0),"ST_COMMA");w++)step(h,0,0);assert(w<300);}   /* DM_OFNI fades out, ST_COMMA returns */
    printf("commander: matf00 first briefing by Ophanimon (%u pages, DM_OFNI) moved flag 1 -> 2; music back on %s\n",brief.n,track(h,0));

    /* Ophanimon's talk script (hit_n_ofanim -> n_ofanim_00) in the new state. */
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(ofanim,&a);
    float yaw=a.rotation[1]*0.0174533f;   /* stand in its authored talk box (10..20 units in front), facing it */
    assert(!dw4_lobby_place_player(world,a.position[0]+17*sinf(yaw),a.position[1],a.position[2]+17*cosf(yaw),a.rotation[1]+180));idle(h,60);
    step(h,0,0x4000);assert(dw4_lobby_talk_result(world)==1);
    struct pages talk={0};play_event(h,&talk,2000,"ophanimon-talk");
    assert(talk.n && control(h) && flag(r,2)==1);
    printf("commander: Ophanimon talk (%u page(s), first '%s') closes with control restored\n",talk.n,talk.text[0]);

    /* mate00: Circle keeps the player in the room, Cross travels to the Terminal point 0. */
    gate(h,40,25,50,"Main Lobby",0x2000);
    {unsigned w=0;for(;w<300 && !control(h);w++)step(h,0,0);assert(w<300 && !dw4_hubruntime_travel(h)->pending);}
    assert(!dw4_lobby_place_player(world,-50,20,0,0));idle(h,60);
    gate(h,40,25,50,"Main Lobby",0x4000);
    {unsigned w=0;for(;w<400 && !dw4_hubruntime_travel(h)->pending;w++)step(h,0,0);assert(w<400);}
    printf("commander: mate00 'Main Lobby' prompt: Circle stays, Cross requests stagML11 point 0\n");
    h=follow(mount,h,"stagML11",0);
    {unsigned w=0;for(;w<900 && !(control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)));w++)step(h,0,0);assert(w<900);}
    assert(flag(dw4_hubruntime_records(h),2)==1 && flag(dw4_hubruntime_records(h),502)==1);
    dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
    printf("commander: back in the Terminal at point 0 (%.0f,%.0f,%.0f) with control and the Commander Room progress\n",w.position[0],w.position[1],w.position[2]);
    idle(h,30);shot(h,"terminal-return");
    dw4_hubruntime_close(h);
}
/* Terminal "Gate to Outside World" (mate00, label region matf00): approach from outside the region, over the label spot, onto the pad. */
static void terminal_outside_pad(dw4_hubruntime *h)
{
    dw4_lobby *w=dw4_hubruntime_world(h);float mn[3],mx[3],on[3],pmn[3],pmx[3];
    assert(dw4_lobby_material_region(w,"matf00",mn,mx)>=0 && dw4_lobby_material_region(w,"mate00",pmn,pmx)>=0);
    on[0]=(pmn[0]+pmx[0])/2;on[1]=100;on[2]=(pmn[2]+pmx[2])/2;
    assert(!dw4_lobby_place_player(w,mn[0]-40,100,on[2],0));idle(h,60);assert(!has_text(h,"POINTFONT00",NULL));
    assert(!dw4_lobby_place_player(w,on[0],100,on[2]+((mx[2]-on[2])>(on[2]-mn[2])?18:-18),0));idle(h,90);
    assert(has_text(h,"POINTFONT00","font04") && strstr(text_value(h,"POINTFONT00","font04"),"Gate to Outside World"));
    assert(!dw4_lobby_place_player(w,on[0],on[1],on[2],0));
}
/* The Outside World gate depends on what Ophanimon's first briefing sets: inert with story flag 1 only, open (accept -> stag0001)
 * after running that briefing and the exit to the Terminal, with no flag set by hand in between. */
static void briefing_opens_gate(dw4_mount *mount,dw4_playerrecords *players,dw4_be_state *state)
{
    static const int32_t clear[]={2,3,4,5,6,320,409,424,503};
    dw4_playerrecords *p=dw4_playerrecords_snapshot(players);assert(p);
    for(unsigned i=0;i<sizeof clear/sizeof *clear;i++)set_flag(p,clear[i],0);
    set_flag(p,1,1);set_flag(p,502,1);   /* 502: the welcome has been seen; flag 1 is its result */
    dw4_hubruntime_source src={p,state,NULL,0};
    /* Before the briefing: the pad runs its script and does nothing. */
    frame=0;dw4_hubruntime *h=boot(mount,&src,"stagML11",0);
    {unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}assert(t<6000);}
    terminal_outside_pad(h);idle(h,180);
    assert(control(h) && !dw4_hubruntime_travel(h)->pending && !has_text(h,"STCHGFONT00",NULL) && !has_text(h,"STCHGFONT01",NULL));
    dw4_hubruntime_close(h);
    /* The briefing, as in main_route. */
    frame=0;h=boot(mount,&src,"stagML02",0);settle(h,3000);
    assert(flag(p,1)==1 && flag(p,2)==0);
    struct pages brief={0};
    assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),200,70,-100,0));
    {unsigned k=0,quiet=0,talked=0;
     for(;k<3000 && quiet<40;k++){
         step(h,0,!control(h) && k%45==44?0x4000:0);collect(h,&brief);talked|=any_message(h);
         quiet=talked && control(h) && !any_message(h)?quiet+1:0;
     }
     assert(k<3000 && shown(&brief,"So you have just joined"));}
    assert(flag(dw4_hubruntime_records(h),1)==0 && flag(dw4_hubruntime_records(h),2)==1);
    /* The exit to the Terminal. */
    gate(h,40,25,50,"Main Lobby",0x4000);
    {unsigned w=0;for(;w<400 && !dw4_hubruntime_travel(h)->pending;w++)step(h,0,0);assert(w<400);}
    h=follow(mount,h,"stagML11",0);
    {unsigned w=0;for(;w<6000;w++){step(h,0,w%45==44?0x4000:0);if(w>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}assert(w<6000);}
    /* Now the same pad opens the field list and accepting requests stag0001. */
    terminal_outside_pad(h);
    {unsigned k=0;for(;k<300 && !has_text(h,"STCHGFONT01",NULL);k++)step(h,0,0);assert(k<300 && !control(h));}
    idle(h,60);press(h,0x4000);
    {unsigned r=0;const dw4_stagetravel *t=dw4_hubruntime_travel(h);for(;r<600 && !t->pending;r++)step(h,0,0);
     assert(t->pending && !strcasecmp(t->destination,"stag0001"));}
    printf("commander: Outside World gate inert with flag 1 only; after the briefing (flag 1 -> 2) and the exit, its field list opens and accept requests stag0001\n");
    dw4_hubruntime_close(h);dw4_playerrecords_close(p);
}
/* One later story state of the room, entered with progress-flag fixtures. */
struct story {const char *name;int32_t set[6];float x,y,z;const char *first,*last;int32_t after_on[4],after_off[4];int folder,pass;};
static void story(dw4_mount *mount,dw4_playerrecords *players,dw4_be_state *state,const struct story *s,unsigned *wall)
{
    dw4_playerrecords *p=dw4_playerrecords_snapshot(players);assert(p);
    set_flag(p,502,1);for(unsigned i=0;i<6 && s->set[i];i++)set_flag(p,s->set[i],1);
    dw4_hubruntime_source src={p,state,NULL,0};frame=0;
    dw4_hubruntime *h=boot(mount,&src,"stagML02",0);
    struct pages pages={0};
    if(s->x==0 && s->y==0)play_event(h,&pages,4000,s->name);   /* first.lua runs it on arrival */
    else {
        settle(h,600);
        assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),s->x,s->y,s->z,0));
        play_event(h,&pages,4000,s->name);
    }
    if(getenv("DW4_COMMANDER_PAGES") || !shown(&pages,s->first) || !shown(&pages,s->last)){
        fprintf(stderr,"%s: pages",s->name);for(unsigned i=0;i<pages.n;i++)fprintf(stderr," '%s'",pages.text[i]);fprintf(stderr,"\n");
        assert(shown(&pages,s->first) && shown(&pages,s->last));
    }
    dw4_playerrecords *r=dw4_hubruntime_records(h);
    for(unsigned i=0;i<4 && s->after_on[i];i++)if(!flag(r,s->after_on[i])){fprintf(stderr,"%s: flag %d clear\n",s->name,s->after_on[i]);assert(0);}
    for(unsigned i=0;i<4 && s->after_off[i];i++)if(flag(r,s->after_off[i])){fprintf(stderr,"%s: flag %d set\n",s->name,s->after_off[i]);assert(0);}
    if(s->folder>=0) {   /* the key item the scene hands over: SYSctlFlagFolder SET <folder> */
        size_t count;const uint8_t *before=dw4_property_bytes(dw4_playerrecords_get(p,"GETCOMMON",0),"FLAGFOLDER",&count);
        const uint8_t *after=dw4_property_bytes(dw4_playerrecords_get(r,"GETCOMMON",0),"FLAGFOLDER",NULL);
        assert(before && after && (size_t)s->folder<count && !before[s->folder] && after[s->folder]==1);
    }
    if(s->pass) {
        /* Walk from the ring toward Seraphimon's desk with the stick: the hitmovepass01z05 wall blocks the way at z = -124 until
         * start.lua turns it off (flag 324, the moving pass switched on). */
        settle(h,900);
        assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),100,70,-90,180));idle(h,60);
        walk_to(h,100,-212,4);
        dw4_lobby_walk_state w;assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        if(s->pass>0?w.position[2]>-190:w.position[2]<-140){fprintf(stderr,"%s: pass walk ended at z %g\n",s->name,w.position[2]);assert(0);}
        printf("commander story: %s: the walk toward Seraphimon %s (z %.1f)\n",s->name,s->pass>0?"crosses the moving pass":"stops at the wall",w.position[2]);
    }
    dw4_lobby_world_state info;assert(!dw4_lobby_world_info(dw4_hubruntime_world(h),&info));
    if(wall)*wall=info.wall_triangles;
    printf("commander story: %s (%u pages, '%s' .. '%s'), control restored, flags as authored\n",s->name,pages.n,s->first,s->last);
    dw4_hubruntime_close(h);dw4_playerrecords_close(p);
}
int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubCmd",error,sizeof error));
    dw4_hubruntime_source fresh={players,&state,NULL,0};
    if(!getenv("DW4_COMMANDER_STORIES_ONLY"))main_route(&mount,&fresh);
    /* Later story states (fixtures: the progress flags the field stages set). Coordinates: matf00 in front of Ophanimon, matf02 in
     * front of Seraphimon; (0,0,0) means first.lua plays the scene on arrival. */
    static const struct story stories[]={
        {"leomon-report",{2,20},0,0,0,"Good job! Currently, Leo","Now we have the Boat Key",{322},{0},2,0},
        {"ophanimon-id",{2,20,67,322},200,70,-100,"Good job! It was a diffi","Now we have the Ophanimo",{3,323},{2},3,0},
        {"alarm-off",{3,324},0,0,0,"Energy fully charged!","That's the only way we c",{325,4},{3},-1,1},
        {"seraphimon-report",{4,335},100,70,-200,"I see. . . A big, red","That's the enemy's true",{326,5},{4},-1,0},
        {"lucemon-briefing",{5,69},200,70,-100,"Server Control Station.","We recovered Lucemon's",{327,6},{5},-1,-1},
    };
    if(!getenv("DW4_COMMANDER_STORIES_ONLY"))briefing_opens_gate(&mount,players,&state);
    unsigned walls[5]={0};
    for(unsigned i=0;i<sizeof stories/sizeof *stories;i++)story(&mount,players,&state,stories+i,walls+i);
    /* start.lua's HITLANDMODEL hitmovepass01z05 OFFHIT (flag 324) removes that wall graph from walking. */
    assert(walls[2] && walls[2]<walls[0]);
    printf("commander: HITLANDMODEL hitmovepass01z05 OFFHIT leaves %u of %u wall triangles once the moving pass is on\n",walls[2],walls[0]);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    printf("hub GPU: %u frames match the CPU oracle within tolerance (%u skipped without a GPU context)\n",gpu_checked,gpu_skipped);
    puts("hub commander: Terminal -> Commander Room -> Terminal, welcome, label, briefing, talk, exit prompt and five story events pass");
    return 0;
}
