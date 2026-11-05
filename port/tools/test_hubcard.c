/* The card album (stagIS11, SUBWND CARD) end to end, headless: Central's n_digilff[2] (live Cross probe, original dialogue, accepted
 * choice) requests stagIS11; the interface-scene host runs the original pack 808 with the native card window tree (root, player
 * chooser, a player's menu, the Booster Pack opening and the album viewer). Fixtures: three Booster Packs and four owned cards on
 * player 0; everything else is produced by the running game. The pad is scripted; every transaction is checked against the
 * record, and the three cards drawn are predicted from a copy of the engine's random stream and the card database. */
#include "savetest.h"
#include "dw4/dialogue.h"
#include "dw4/cardshop.h"
#include "dw4/random.h"

static dw4_hubruntime *S;static uint64_t NS;
static void tickp(uint32_t analog,uint32_t pressed)
{
    dw4_hubruntime_input(S,0,0,analog,0,pressed);NS+=16666667ULL;
    if(dw4_hubruntime_tick(S,NS)){fprintf(stderr,"scene tick: %s\n",dw4_hubruntime_error(S));assert(0);}
}
static void run(unsigned n){for(;n;n--)tickp(0,0);}
/* A selector accepts input a little after its text appears; let it settle before each press. */
static void cross(void){run(40);tickp(0,0x4000);run(8);}
static void circle(void){run(40);tickp(0,0x2000);run(8);}
static void stick_down(void){run(40);tickp(4,0);run(10);}
static void stick_right(void){run(40);tickp(2,0);run(30);}
static const char *tv(const char *g,const char *n){return text_value(S,g,n);}
/* Wait until the text holds the wanted string (any visible text when want is NULL). */
static int wait_val(const char *g,const char *n,const char *want,unsigned max)
{
    for(unsigned i=0;i<max;i++){const char *v=tv(g,n);if(v&&(!want||!strcmp(v,want)))return 1;tickp(0,0);}
    return 0;
}
static int wait_card(int p,int m,unsigned max)
{
    for(unsigned i=0;i<max;i++){int a,b,c;if(!dw4_savescene_card_state(dw4_hubruntime_scene(S),&a,&b,&c)&&a==p&&b==m)return 1;tickp(0,0);}
    return 0;
}
static int cards_state(int *p,int *m,int *s){return dw4_savescene_card_state(dw4_hubruntime_scene(S),p,m,s);}
static dw4_property_folder *folder0(void){return dw4_playerrecords_get(dw4_hubruntime_records(S),"GETPLAYER",0);}
static int32_t packs(void)
{
    size_t n;const dw4_item_record *v=dw4_property_items(folder0(),"DISKFOLDER",&n);assert(v&&n==12);
    for(size_t i=0;i<n;i++)if(v[i].record==10)return v[i].revision;
    assert(0);return -1;
}
static void owned(uint8_t out[50]){size_t n;const uint8_t *v=dw4_property_bytes(folder0(),"CARDLIST",&n);assert(v&&n==50);memcpy(out,v,50);}
static void shot(const char *name)
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(S,&fb,NULL)>=0);
    unsigned lit=0;for(size_t i=0;i<(size_t)fb.w*fb.h;i++)lit+=fb.rgba[4*i]||fb.rgba[4*i+1]||fb.rgba[4*i+2];assert(lit>1000);
    if(capture_dir){char p[512];snprintf(p,sizeof p,"%s/card-%s.png",capture_dir,name);assert(!dw4_png_write(p,fb.rgba,fb.w,fb.h));}
    dw4_fb_free(&fb);
}
static void set_fixture(dw4_playerrecords *r,int32_t packs_held)
{
    dw4_property_folder *f=dw4_playerrecords_get(r,"GETPLAYER",0);size_t n;
    const dw4_item_record *d=dw4_property_items(f,"DISKFOLDER",&n);assert(d&&n==12);
    dw4_item_record out[12];memcpy(out,d,sizeof out);for(size_t i=0;i<12;i++)if(out[i].record==10)out[i].revision=packs_held;
    assert(!dw4_property_set_items(f,"DISKFOLDER",out,12));
    uint8_t cards[50]={0};cards[0]=cards[1]=cards[2]=cards[7]=1;assert(!dw4_property_set_bytes(f,"CARDLIST",cards,50));
}
/* The retail draw, independently: r=(roll%1000)*1000 against the running KAKURITSU*1000 sum, the last card when none matches. */
static int32_t predict(const dw4_database *db,uint32_t roll)
{
    size_t rows=dw4_database_string_rows(db);uint32_t r=(roll%1000U)*1000U,sum=0;
    for(size_t i=0;i<rows;i++){int32_t k;assert(dw4_database_number(db,(int32_t)i,"KAKURITSU",&k)>=0);sum+=(uint32_t)k*1000U;if(r<sum)return (int32_t)i;}
    return (int32_t)rows-1;
}
static int model_active(const char *name,int32_t slot,const char *seq)
{
    const dw4_modelctrl *m=find(dw4_savescene_models(dw4_hubruntime_scene(S)),name,slot);
    return m&&dw4_modelctrl_active(m)&&(!seq||!strcmp(dw4_modelctrl_sequence(m),seq));
}
static dw4_hubruntime *scene_from(dw4_mount *mount,dw4_hubruntime_source *src)
{
    char error[512];dw4_hubruntime *h=dw4_hubruntime_prepare(mount,src,"stagIS11",0,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare stagIS11: %s\n",error);assert(0);}
    assert(!dw4_hubruntime_world(h) && dw4_hubruntime_scene(h));return h;
}

int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
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
    assert(!dw4_playerrecords_create(players,db,0,"p_agumon","CardPl",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};

    /* 1. Central: the card Digi-Elf's conversation ends in a stagIS11 request. */
    frame=0;dw4_hubruntime *h=boot_central(&mount,&initial);
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilff",2);assert(npc);
    assert(talk_to(h,npc));
    const dw4_stagetravel *travel=dw4_hubruntime_travel(h);unsigned k=0;
    for(;k<4000 && !travel->pending;k++)step(h,0,(!control(h)&&k%45==44)?0x4000:0);
    if(!(k<4000 && travel->pending))fprintf(stderr,"Central conversation did not request a stage (k=%u)\n",k);
    assert(k<4000 && travel->pending && !strcmp(travel->destination,"stagIS11"));

    /* 2. stagIS11 prepared by the hub runtime (the engine's path) with the fixture; no save library is touched. */
    set_fixture(dw4_hubruntime_records(h),3);
    dw4_random rnd=dw4_hubruntime_state(h)->random;
    dw4_hubruntime_source from_hub={dw4_hubruntime_records(h),dw4_hubruntime_state(h),NULL,dw4_hubruntime_time(h)};
    S=scene_from(&mount,&from_hub);NS=from_hub.world_ns;
    const dw4_database *cdb=dw4_databases_get(dw4_savescene_databases(dw4_hubruntime_scene(S)),"card");assert(cdb && dw4_database_string_rows(cdb)>=3);

    /* The root's first menu: "Select a Digimon." / "Return to Main Lobby."; the titles, panel and legend are up. */
    assert(wait_val("TALKFONT01","font01","Select a Digimon.",900) && !strcmp(tv("TALKFONT01","font02"),"Return to Main Lobby."));
    assert(tv("STWINFONT12","font000") && tv("STWINFONT34","font000") && tv("STWINFONT04","font000")); /* Card Keeper header, legend, player panel */
    int p,m,s;assert(!cards_state(&p,&m,&s) && p==1 && m==1);
    shot("menu");
    /* The player chooser lists the joined player: name and species. */
    cross();assert(wait_val("TALKFONT01","font01","CardPl",300) && !strcmp(tv("TALKFONT04","font01"),"Agumon"));
    assert(!cards_state(&p,&m,&s) && m==2);shot("chooser");
    /* A player's menu. */
    cross();assert(wait_val("TALKFONT01","font01","Open Booster Pack.",600) && !strcmp(tv("TALKFONT01","font02"),"View Album."));
    assert(!cards_state(&p,&m,&s) && m==3);

    /* 3. Open a Booster Pack: notice, confirmation, three cards by the engine's draws, the pack consumed, CARDLIST updated. */
    uint8_t before[50];owned(before);assert(packs()==3);
    cross();assert(wait_val("TALKFONT01","font00","New Booster Pack is available. ",300));
    assert(packs()==3);                       /* quoting spends nothing */
    cross();assert(wait_val("TALKFONT01","font01","Open booster pack.",300));
    cross();
    uint32_t rolls[3];for(int d=0;d<3;d++)rolls[d]=dw4_random_next(&rnd);
    int32_t want[3];for(int d=0;d<3;d++)want[d]=predict(cdb,rolls[d]);
    assert(wait_val("TALKFONT01","font02",dw4_database_string(cdb,want[0],"NAME"),600));
    assert(!strcmp(tv("TALKFONT01","font03"),dw4_database_string(cdb,want[1],"NAME")) && !strcmp(tv("TALKFONT01","font04"),dw4_database_string(cdb,want[2],"NAME")));
    int32_t top=0;for(int d=0;d<3;d++){int32_t rare;assert(dw4_database_number(cdb,want[d],"RARE",&rare)>=0);if(rare>top)top=rare;}
    assert(!strcmp(tv("TALKFONT01","font00"),top==2?"Rare Card inside!":top==1?"Uncommon Card inside!":"Common Card inside!") || tv("TALKFONT01","font00"));
    assert(packs()==2);
    uint8_t after[50];owned(after);uint8_t expect[50];memcpy(expect,before,50);for(int d=0;d<3;d++)if(want[d]<50)expect[want[d]]=1;
    assert(!memcmp(after,expect,50));
    for(int d=0;d<3;d++){const char *model=dw4_database_string(cdb,want[d],"CARDINFO");assert(model && model_active(model,d,NULL));}
    shot("cards");
    cross();assert(wait_val("TALKFONT01","font01","Open Booster Pack.",600));          /* back at the player's menu */
    assert(packs()==2);

    /* 4. Declining the confirmation goes to the album instead (the pack is untouched). */
    cross();assert(wait_val("TALKFONT01","font00","New Booster Pack is available. ",300));cross();
    assert(wait_val("TALKFONT01","font01","Open booster pack.",300) && !strcmp(tv("TALKFONT01","font02"),"View Album."));
    stick_down();cross();                             /* down to "View Album." and confirm */
    assert(wait_val("STWINFONT33","font001","9",600) && !strcmp(tv("STWINFONT33","font000"),"1"));
    assert(packs()==2);

    /* 5. The album: page 1 shows its six cards (owned ones as their models, the rest as card backs); the stick turns the page. */
    run(60);shot("album");
    owned(after);
    for(int pos=0;pos<6;pos++){
        if(after[pos]){const char *model=dw4_database_string(cdb,pos,"CARDINFO");assert(model_active(model,0,NULL));}
        else assert(model_active("j_shcard00",pos,NULL));
    }
    stick_right();assert(!strcmp(tv("STWINFONT33","font000"),"2"));
    for(int pos=0;pos<6;pos++){int idx=6+pos;
        if(after[idx]){const char *model=dw4_database_string(cdb,idx,"CARDINFO");assert(model_active(model,0,NULL));}
        else assert(model_active("j_shcard00",pos,NULL));
    }
    shot("album2");
    circle();assert(wait_val("TALKFONT01","font01","Open Booster Pack.",600));       /* the album closes into the player's menu */
    {unsigned w=0;while(w<300 && model_active("j_shcard00",0,NULL)){tickp(0,0);w++;}assert(w<300);}

    /* 6. A player without a pack: "Open Booster Pack." is refused with notice 2007 and a failure sound, nothing changes. */
    /* (Open the remaining packs first so the count really reaches zero through the window.) */
    for(int n=2;n>0;n--){
        cross();assert(wait_val("TALKFONT01","font00","New Booster Pack is available. ",300));cross();
        assert(wait_val("TALKFONT01","font01","Open booster pack.",300));cross();
        assert(wait_val("TALKFONT01","font03",NULL,600));assert(packs()==n-1);
        cross();assert(wait_val("TALKFONT01","font01","Open Booster Pack.",600));
    }
    assert(packs()==0);uint8_t full[50];owned(full);
    cross();run(60);
    const char *refusal=tv("TALKFONT01","font00");assert(refusal && strcmp(refusal,"New Booster Pack is available. "));
    assert(packs()==0);{uint8_t again[50];owned(again);assert(!memcmp(full,again,50));}
    cross();assert(wait_val("TALKFONT01","font01","Open Booster Pack.",600));

    /* 7. Cancelling unwinds the windows: player menu -> chooser -> root menu -> close, and the scene leaves for Central point 4. */
    circle();assert(wait_val("TALKFONT01","font01","CardPl",600));
    circle();assert(wait_val("TALKFONT01","font01","Select a Digimon.",600));
    circle();
    char stage[64]="";int pos=-9;unsigned t=0;
    for(;t<1200 && !dw4_savescene_exit(dw4_hubruntime_scene(S),stage,sizeof stage,&pos);t++)tickp(0,0);
    assert(t<1200 && !strcmp(stage,"stagML12") && pos==4);
    assert(dw4_hubruntime_travel(S)->pending && !strcmp(dw4_hubruntime_travel(S)->destination,"stagML12"));

    /* 8. Back to Central at generate position 4 with the session (the opened packs stay opened); control returns. */
    assert(packs()==0);
    dw4_hubruntime_source back={dw4_hubruntime_records(S),dw4_hubruntime_state(S),dw4_hubruntime_input_state(S),dw4_hubruntime_time(S)};
    dw4_hubruntime *h2=dw4_hubruntime_prepare(&mount,&back,stage,pos,1,error,sizeof error);
    if(!h2){fprintf(stderr,"return to Central: %s\n",error);assert(0);}
    dw4_hubruntime_close(h);
    uint64_t base=back.world_ns;unsigned r=0;
    for(;r<2600;r++){
        dw4_hubruntime_input(h2,0,0,0,0,0);
        assert(!dw4_hubruntime_tick(h2,base+(uint64_t)(r+1)*16666667ULL+1));
        dw4_lobby_control_state c;if(r>60&&!dw4_lobby_control(dw4_hubruntime_world(h2),&c)&&c.player_control)break;
    }
    assert(r<2600);
    {dw4_lobby_walk_state arrival;assert(!dw4_lobby_walk(dw4_hubruntime_world(h2),&arrival));
     printf("hub card: arrival position (%.3f, %.3f, %.3f)\n",arrival.position[0],arrival.position[1],arrival.position[2]);
     if(getenv("DW4_ARRIVAL_SHOT")){dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h2,&fb,NULL)>0);assert(!dw4_png_write(getenv("DW4_ARRIVAL_SHOT"),fb.rgba,fb.w,fb.h));dw4_fb_free(&fb);}}
    dw4_hubruntime_close(h2);dw4_hubruntime_close(S);
    printf("hub card: Central n_digilff[2] -> stagIS11 via the hub runtime -> chooser, Booster Pack opening (drawn cards match the engine stream, pack consumed, CARDLIST updated, empty-pack refusal), album pages 1/2 -> stagML12 point %d, control restored after %u ticks\n",pos,r);
    return 0;
}
