/* The title's Game Start slot screen (DW4_SCENE_TITLE): LoadCtrl2 + LoadIntf2 from the Create/Call window over the pack of
 * stagIS13, a card holding two saved characters, and a scripted pad. The card chooser, the "Accessing memory card" notice, the data
 * grid, the difficulty window and the log-in prompt run on the real MODELCTRL/TEXTCTL services. Headless; DW4_TITLECALL_FRAMES=<dir>
 * writes a PNG of each screen. */
#include "savetest.h"

static const char *capture;
static void shot(dw4_savescene *s,const char *tag)
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));
    int n=dw4_savescene_draw(s,&fb);assert(n>=0);
    unsigned lit=0;for(size_t i=0;i<(size_t)fb.w*fb.h;i++)lit+=fb.rgba[4*i]||fb.rgba[4*i+1]||fb.rgba[4*i+2];
    assert(lit>1000);
    if(capture){char path[512];snprintf(path,sizeof path,"%s/titlecall-%s.png",capture,tag);assert(!dw4_png_write(path,fb.rgba,fb.w,fb.h));}
    dw4_fb_free(&fb);
}
static uint64_t now_ns;
static void run_pad(dw4_savescene *s,unsigned ticks,uint32_t stick,uint32_t pressed)
{
    for(unsigned k=0;k<ticks;k++){
        dw4_savescene_input(s,k==0?stick:0,0,k==0?pressed:0);now_ns+=16666667ULL;
        if(dw4_savescene_tick(s,now_ns)){fprintf(stderr,"tick: %s\n",dw4_savescene_error(s));assert(0);}
    }
}
static void run(dw4_savescene *s,unsigned ticks,uint32_t pressed){run_pad(s,ticks,0,pressed);}
#define STICK_DOWN 4u

struct flow {const char *tag;int moves_down;int expect_cap;int hard;int expect_area,expect_level,expect_row;};
static void wait_ctrl(dw4_savescene *s,int control,int sub,int subsub)
{
    for(int guard=0;guard<900;guard++){
        const dw4_saveintf *si=dw4_savescene_intf(s);dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(si,0,&t);
        if(t.control==control&&(sub<0||t.control_sub==sub)&&t.control_subsub>=subsub)return;
        run(s,1,0);
    }
    fprintf(stderr,"timed out waiting for control %d.%d.%d\n",control,sub,subsub);assert(0);
}
static void trace(dw4_savescene *s,dw4_saveintf_trace *t){*t=(dw4_saveintf_trace){0};dw4_saveintf_diagnostics(dw4_savescene_intf(s),0,t);}
/* The warmed scene shows the Create/Call window (control 3.2) with the cursor on Create. Down moves it to Call, Cross opens the chooser. */
static void choose_call(dw4_savescene *s,const char *tag)
{
    dw4_saveintf_trace t;trace(s,&t);assert(t.control==3&&t.control_sub==2);
    run(s,10,0);
    if(tag){char name[64];snprintf(name,sizeof name,"%s-0-create",tag);shot(s,name);}
    run_pad(s,1,STICK_DOWN,0);run(s,24,0);
    if(tag){char name[64];snprintf(name,sizeof name,"%s-0-call",tag);shot(s,name);}
    run_pad(s,1,STICK_DOWN,0);run(s,24,0);                                   /* no wrap: the cursor stays on Call */
    run(s,1,0x4000);wait_ctrl(s,6,1,0);
}
static void flow(dw4_mount *mount,dw4_playerrecords *players,dw4_be_state *state,dw4_memcard *card,const struct flow *fl)
{
    char error[512];
    dw4_savescene_source src={players,state,0,card,DW4_SCENE_TITLE};
    dw4_savescene *s=dw4_savescene_open(mount,&src,error,sizeof error);
    if(!s){fprintf(stderr,"open: %s\n",error);assert(0);}
    int used=dw4_savescene_warm(s,now_ns=16666667ULL,16666667ULL,600);assert(used>=0);now_ns+=(uint64_t)used*16666667ULL;
    char tag[64];
    choose_call(s,fl->tag);
    run(s,40,0);snprintf(tag,sizeof tag,"%s-1-chooser",fl->tag);shot(s,tag);
    run(s,1,0x4000);run(s,6,0);snprintf(tag,sizeof tag,"%s-2-accessing",fl->tag);shot(s,tag);
    wait_ctrl(s,7,1,3);run(s,30,0);
    for(int d=0;d<fl->moves_down;d++){run_pad(s,1,STICK_DOWN,0);run(s,24,0);}          /* down in the 2x2 grid: area 0 -> 2 */
    snprintf(tag,sizeof tag,"%s-3-grid",fl->tag);shot(s,tag);
    run(s,1,0x4000);                                                         /* take the highlighted area */
    wait_ctrl(s,8,-1,0);run(s,30,0);
    {
        const dw4_saveintf *si=dw4_savescene_intf(s);dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(si,0,&t);
        int shows=t.control_sub==0&&t.control_subsub==0&&t.control_subsub==0;
        (void)shows;
        run(s,30,0);
        dw4_saveintf_diagnostics(si,0,&t);
        if(fl->expect_cap){                                                 /* hostLoad.lua cap: the difficulty window is up */
            if(!(t.control==8&&t.control_sub==0))fprintf(stderr,"control %d.%d.%d.%d item %d\n",t.control,t.control_sub,t.control_subsub,0,t.state);
            assert(t.control==8&&t.control_sub==0);
            snprintf(tag,sizeof tag,"%s-4-difficulty",fl->tag);shot(s,tag);
            if(fl->hard){run_pad(s,1,STICK_DOWN,0);run(s,24,0);snprintf(tag,sizeof tag,"%s-4b-difficulty-hard",fl->tag);shot(s,tag);}
            run(s,1,0x4000);run(s,40,0);
        }
    }
    wait_ctrl(s,8,3,1);run(s,20,0);snprintf(tag,sizeof tag,"%s-5-login",fl->tag);shot(s,tag);
    int cs=-1,area=-1,dif=-1;
    assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
    run(s,1,0x8);                                                            /* START */
    char stage[64];int pos=0,guard=0;
    while(guard++<1200&&!dw4_savescene_exit(s,stage,sizeof stage,&pos))run(s,1,0);
    assert(guard<1200);
    assert(dw4_savescene_title_state(s,&cs,&area,&dif)==1 && area==fl->expect_area && cs==0);
    assert(dif==fl->expect_row);
    assert(!strcmp(stage,"stagML11") && pos==4);
    int32_t lv=0;assert(!dw4_property_number(dw4_playerrecords_get(dw4_savescene_records(s),"GETPLAYER",0),"LEVEL",&lv) && lv==fl->expect_level);
    printf("title call (%s): chooser -> card access -> data grid -> %s -> log-in prompt -> START: slot %d area %d difficulty row %d, Lv.%d, exit %s point %d\n",
           fl->tag,fl->expect_cap?"difficulty":"(no difficulty window)",cs,area,dif,lv,stage,pos);
    dw4_savescene_close(s);
}

/* Cancel paths and a card without a game file: Circle on the grid returns to the chooser, Circle on the chooser returns to the
 * Create/Call window inside the scene (Circle there does nothing), Create reports title state 3 and resumes, and a card with no file shows the "no Digimon World 4 game file" notice (item state 6) and returns to the chooser. */
static void paths(dw4_mount *mount,dw4_playerrecords *players,dw4_be_state *state,dw4_memcard *full,dw4_memcard *empty)
{
    char error[512];int cs,area,dif;
    {
        dw4_savescene_source src={players,state,0,full,DW4_SCENE_TITLE};
        dw4_savescene *s=dw4_savescene_open(mount,&src,error,sizeof error);assert(s);
        int used=dw4_savescene_warm(s,now_ns=16666667ULL,16666667ULL,600);assert(used>=0);now_ns+=(uint64_t)used*16666667ULL;
        choose_call(s,NULL);
        run(s,40,0);run(s,1,0x4000);wait_ctrl(s,7,1,3);run(s,30,0);
        run(s,1,0x2000);                                                     /* Circle on the grid: back to the chooser */
        wait_ctrl(s,6,1,0);run(s,40,0);
        assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
        run(s,1,0x2000);                                                     /* Circle on the chooser: the Create/Call window, in the scene */
        wait_ctrl(s,3,2,0);run(s,10,0);
        assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
        dw4_saveintf_trace t;trace(s,&t);assert(t.control==3&&t.control_sub==2);
        shot(s,"cancel-createcall");
        run(s,1,0x2000);run(s,30,0);                                         /* Circle at Create/Call does nothing for player 0 */
        trace(s,&t);assert(t.control==3&&t.control_sub==2&&dw4_savescene_title_state(s,&cs,&area,&dif)==0);
        char stage[64];int pos;assert(!dw4_savescene_exit(s,stage,sizeof stage,&pos));
        run(s,1,0x4000);                                                     /* Cross on Create (the cursor came back on Create) */
        wait_ctrl(s,4,2,0);run(s,30,0);                                      /* the starter choice runs in the scene */
        assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
        run(s,1,0x2000);                                                     /* Circle out of the starter choice: the window reopens */
        wait_ctrl(s,3,2,0);assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
        run(s,10,0);choose_call(s,NULL);                                     /* and still reaches the chooser */
        printf("title call (cancel): grid -> chooser -> Create/Call (Circle ignored) -> Create -> starter choice -> Circle -> Call\n");
        dw4_savescene_close(s);
    }
    {
        dw4_savescene_source src={players,state,0,empty,DW4_SCENE_TITLE};
        dw4_savescene *s=dw4_savescene_open(mount,&src,error,sizeof error);assert(s);
        int used=dw4_savescene_warm(s,now_ns=16666667ULL,16666667ULL,600);assert(used>=0);now_ns+=(uint64_t)used*16666667ULL;
        choose_call(s,NULL);
        run(s,40,0);run(s,1,0x4000);
        wait_ctrl(s,6,1,1);                                                  /* the card is being read */
        for(int g=0;g<600;g++){                                              /* item state 6: the notice waits for Cross */
            const dw4_saveintf *si=dw4_savescene_intf(s);dw4_saveintf_trace t={0};dw4_saveintf_diagnostics(si,0,&t);
            if(t.state==6&&t.subsub==1)break;
            run(s,1,0);
        }
        run(s,30,0);shot(s,"nofile-notice");
        run(s,1,0x4000);                                                     /* Cross continues */
        wait_ctrl(s,6,1,0);
        assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
        printf("title call (no game file): the notice, Cross, back to the chooser\n");
        dw4_savescene_close(s);
    }
}

/* ---- Create: the starter choice (control state 4), the name entry (5, NameSel) and GAMESTART + log-in (8) ---- */
#define STICK_UP 1u
#define STICK_RIGHT 2u
#define STICK_LEFT 8u
static const char *scene_text(dw4_savescene *s,const char *group,const char *font)
{
    static char out[64];const dw4_dialogue *d=dw4_savescene_dialogue(s);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++){
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(t->visible&&t->count&&!strcmp(t->group,group)&&!strcmp(t->name,font)){
            size_t n=t->count<sizeof out-1?t->count:sizeof out-1;
            for(size_t k=0;k<n;k++)out[k]=dw4_name_char((uint16_t)t->codes[k]);
            out[n]=0;return out;
        }
    }
    return "";
}
static dw4_saveintf_create_trace ctrace(dw4_savescene *s){dw4_saveintf_create_trace c;dw4_saveintf_create_diagnostics(dw4_savescene_intf(s),0,&c);return c;}
static void name_ascii(const uint16_t *codes,char out[9]){int i=0;for(;i<8&&codes[i];i++)out[i]=dw4_name_char(codes[i]);out[i]=0;}
/* One pad event in the name entry, then wait until the NameSel takes the pad again (st0 1, the window animations done). */
static void ns_press(dw4_savescene *s,uint32_t stick,uint32_t pressed){run_pad(s,1,stick,pressed);run(s,20,0);}
static void starter(dw4_savescene *s,uint32_t stick,int species,const char *name)
{
    run_pad(s,1,stick,0);run(s,40,0);
    dw4_saveintf_trace t;trace(s,&t);assert(t.control==4&&t.control_sub==2);
    assert(ctrace(s).species==species);
    if(strcmp(scene_text(s,"CHRSELFONT14","font000"),name)){fprintf(stderr,"starter %d shows '%s', not %s\n",species,scene_text(s,"CHRSELFONT14","font000"),name);assert(0);}
}
static void wait_question(dw4_savescene *s)
{for(int g=0;g<300;g++){dw4_saveintf_trace t;trace(s,&t);if(t.control==5&&t.control_sub==3)return;run(s,1,0);}assert(!"the name question did not show");}
static void create(dw4_mount *mount,dw4_playerrecords *players,dw4_be_state *state,dw4_memcard *card)
{
    char error[512],nm[9];int cs,area,dif;
    dw4_savescene_source src={players,state,0,card,DW4_SCENE_TITLE};
    dw4_savescene *s=dw4_savescene_open(mount,&src,error,sizeof error);assert(s);
    int used=dw4_savescene_warm(s,now_ns=16666667ULL,16666667ULL,600);assert(used>=0);now_ns+=(uint64_t)used*16666667ULL;
    dw4_saveintf_trace t;trace(s,&t);assert(t.control==3&&t.control_sub==2);
    run(s,10,0);
    run_pad(s,1,STICK_DOWN,0);run(s,24,0);run_pad(s,1,STICK_UP,0);run(s,24,0);   /* down to Call, up back to Create */
    run_pad(s,1,STICK_UP,0);run(s,24,0);                                     /* no wrap: the cursor stays on Create */
    run(s,1,0x4000);wait_ctrl(s,4,2,0);run(s,40,0);
    assert(ctrace(s).species==3&&!strcmp(scene_text(s,"CHRSELFONT14","font000"),"Dorumon"));
    shot(s,"create-1-dorumon");
    starter(s,STICK_RIGHT,0,"Agumon");shot(s,"create-2-agumon");
    starter(s,STICK_LEFT,3,"Dorumon");                                       /* left wraps 0 -> 3 */
    starter(s,STICK_LEFT,2,"Guilmon");
    starter(s,STICK_RIGHT,3,"Dorumon");starter(s,STICK_RIGHT,0,"Agumon");      /* right wraps 3 -> 0 */
    starter(s,STICK_RIGHT,1,"Veemon");starter(s,STICK_LEFT,0,"Agumon");
    run(s,1,0x4000);                                                         /* Cross: the name entry */
    wait_ctrl(s,5,1,0);
    for(int g=0;g<300&&ctrace(s).st0!=1;g++)run(s,1,0);
    dw4_saveintf_create_trace c=ctrace(s);assert(c.st0==1&&c.pos==0&&c.row==0&&c.name[0]==0xFF41);   /* the preview is 'a' */
    run(s,10,0);shot(s,"create-3-name");
    assert(!strcmp(scene_text(s,"CHRSELFONT11","font000"),"a")&&!strcmp(scene_text(s,"CHRSELFONT11","font004"),"e"));
    ns_press(s,STICK_DOWN,0);c=ctrace(s);assert(c.row==1&&c.name[0]==0xFF21);  /* down: the upper-case row, 'A' */
    assert(!strcmp(scene_text(s,"CHRSELFONT10","font001"),"A"));
    ns_press(s,0,0x4000);c=ctrace(s);assert(c.pos==1&&c.name[0]==0xFF21&&c.name[1]==0xFF21);   /* typed 'A', the next cell previews 'A' */
    ns_press(s,STICK_UP,0);c=ctrace(s);assert(c.row==0&&c.name[1]==0xFF41);
    for(int k=0;k<6;k++)ns_press(s,STICK_RIGHT,0);                             /* the strip scrolls after the fifth key: 'g' */
    c=ctrace(s);assert(c.column==4&&c.first==2&&c.name[1]==0xFF47);
    assert(!strcmp(scene_text(s,"CHRSELFONT11","font000"),"c")&&!strcmp(scene_text(s,"CHRSELFONT11","font004"),"g"));
    ns_press(s,0,0x4000);
    for(int k=0;k<14;k++)ns_press(s,STICK_RIGHT,0);                            /* 'u' */
    ns_press(s,0,0x4000);ns_press(s,0,0x4000);                               /* 'u' twice */
    c=ctrace(s);name_ascii(c.name,nm);assert(c.pos==4&&!strcmp(nm,"Aguuu"));
    ns_press(s,0,0x2000);c=ctrace(s);name_ascii(c.name,nm);assert(c.pos==3&&!strcmp(nm,"Aguu"));  /* Circle: back to the fourth cell */
    shot(s,"create-4-typed");
    ns_press(s,0,0x8);                                                       /* START: the cell being edited is dropped */
    wait_question(s);c=ctrace(s);name_ascii(c.name,nm);assert(c.pos==2&&!strcmp(nm,"Agu")&&c.question==1);
    run(s,20,0);shot(s,"create-5-question");
    run(s,1,0x4000);run(s,40,0);                                             /* Cross on "continue": the Yes/No choice */
    shot(s,"create-6-confirm");
    run_pad(s,1,STICK_DOWN,0);run(s,20,0);run(s,1,0x4000);                   /* No: back to the name, its last cell under edit */
    for(int g=0;g<300&&ctrace(s).st0!=1;g++)run(s,1,0);
    run(s,20,0);trace(s,&t);c=ctrace(s);assert(t.control==5&&c.st0==1&&c.pos==2&&c.question==0);
    ns_press(s,0,0x4000);ns_press(s,0,0x8);wait_question(s);                 /* Cross keeps 'u', START asks again */
    run(s,1,0x4000);run(s,40,0);run(s,1,0x4000);                             /* continue, Yes */
    wait_ctrl(s,8,3,1);run(s,30,0);shot(s,"create-7-login");
    assert(dw4_savescene_title_state(s,&cs,&area,&dif)==0);
    dw4_property_folder *rec=dw4_playerrecords_get(dw4_savescene_records(s),"GETPLAYER",0);
    int32_t use=0,lv=0,unique=0;dw4_unicode_object name={0};
    assert(!dw4_property_number(rec,"ISUSE",&use)&&use==1&&!dw4_property_number(rec,"LEVEL",&lv)&&lv==1);
    assert(!strcmp(dw4_property_string(rec,"DIGIMONNAME"),"p_agumon"));
    assert(!dw4_property_unicode_object(rec,"PLAYERNAME",0,&name)&&name.present);
    name_ascii(name.codes,nm);assert(!strcmp(nm,"Agu"));
    assert(!dw4_property_number(rec,"UNIQUE",&unique)&&unique!=0);
    run(s,1,0x2000);                                                         /* Circle at the log-in prompt: back to the name entry */
    wait_ctrl(s,5,1,0);
    for(int g=0;g<300&&ctrace(s).st0!=1;g++)run(s,1,0);
    c=ctrace(s);name_ascii(c.name,nm);assert(c.pos==2&&!strcmp(nm,"Agu"));
    ns_press(s,0,0x4000);ns_press(s,0,0x8);wait_question(s);
    run(s,1,0x4000);run(s,40,0);run(s,1,0x4000);
    wait_ctrl(s,8,3,1);run(s,20,0);
    run(s,1,0x8);                                                            /* START */
    char stage[64];int pos=0,guard=0;
    while(guard++<1200&&!dw4_savescene_exit(s,stage,sizeof stage,&pos))run(s,1,0);
    assert(guard<1200&&!strcmp(stage,"stagML11")&&pos==4);
    assert(dw4_savescene_title_state(s,&cs,&area,&dif)==1&&cs==-1&&area==-1&&dif==0);
    rec=dw4_playerrecords_get(dw4_savescene_records(s),"GETPLAYER",0);
    assert(!strcmp(dw4_property_string(rec,"DIGIMONNAME"),"p_agumon"));
    assert(!dw4_property_unicode_object(rec,"PLAYERNAME",0,&name)&&name.present);name_ascii(name.codes,nm);assert(!strcmp(nm,"Agu"));
    printf("title create: Create/Call (down, up, no wrap) -> starter choice (Dorumon; right/left wrap) -> Agumon -> name entry "
           "(rows, strip scroll, Cross, Circle, START) -> question: No -> name -> Yes -> GAMESTART p_agumon \"%s\" UNIQUE %d -> "
           "log-in prompt -> Circle -> name -> Yes -> START: exit %s point %d\n",nm,(int)unique,stage,pos);
    dw4_savescene_close(s);
}

int main(int argc,char **argv)
{
    capture=getenv("DW4_TITLECALL_FRAMES");
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
    /* A card with two characters: a grown p_agumon in area 0 and, in area 2, a p_dorumon whose story flag 711 (Hard unlocked) is set. */
    char dir[]="/tmp/dw4-titlecall-XXXXXX";assert(mkdtemp(dir));
    dw4_memcard *card=dw4_memcard_open(dir);assert(card && dw4_memcard_ready(card));
    {
        dw4_playerrecords *a=dw4_playerrecords_open(),*b=dw4_playerrecords_open();assert(a && b);
        assert(!dw4_playerrecords_create(a,db,0,"p_agumon","Agu",error,sizeof error));
        dw4_property_folder *fa=dw4_playerrecords_get(a,"GETPLAYER",0);
        assert(!dw4_property_set_number(fa,"LEVEL",17) && !dw4_playertransactions_current_to_base(a,0));
        assert(!dw4_playerrecords_create(b,db,2,"p_dorumon","Dorumon",error,sizeof error));
        dw4_property_folder *fb=dw4_playerrecords_get(b,"GETPLAYER",2);size_t n=0;
        const uint8_t *old=dw4_property_bytes(fb,"BASE_FLAG",&n);assert(old && n==1024);
        uint8_t flags[1024];memcpy(flags,old,sizeof flags);flags[711]=1;assert(!dw4_property_set_bytes(fb,"BASE_FLAG",flags,sizeof flags));
        int32_t m0[DW4_SAVE_SLOTS]={0,-1,-1,-1},m2[DW4_SAVE_SLOTS]={-1,-1,2,-1};
        assert(!dw4_memcard_save(card,a,m0,error,sizeof error) && !dw4_memcard_save(card,b,m2,error,sizeof error));
        dw4_playerrecords_close(a);dw4_playerrecords_close(b);
    }
    struct flow plain={"agumon",0,0,0,0,17,0},hard={"hard",2,1,1,2,1,1};
    flow(&mount,players,&state,card,&plain);
    flow(&mount,players,&state,card,&hard);
    char edir[]="/tmp/dw4-titlecall-empty-XXXXXX";assert(mkdtemp(edir));
    dw4_memcard *empty=dw4_memcard_open(edir);assert(empty && dw4_memcard_ready(empty));
    paths(&mount,players,&state,card,empty);
    create(&mount,players,&state,empty);
    dw4_memcard_close(empty);remove_dir(edir);
    dw4_memcard_close(card);remove_dir(dir);
    return 0;
}
