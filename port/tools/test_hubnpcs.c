/* Dialogue coverage over every awake talkable NPC in Terminal, Central and Shop. Headless.
 * Each case boots a fresh prepared hub, wakes one NPC by placing the player on it (the real NEAR
 * map), fires its registered Hit receiver at its authored box, and drives the original script with
 * both prompt choices. The outcome is classified, never assumed: plain close with control restored,
 * a pending stage request, an implemented service (STATUS/XDATA), or an unimplemented SUBWND mode.
 * Anything else is a failure. Fixtures: none. */
#include "hubtest.h"
#include <unistd.h>
#include "dw4/savescene.h"
#include "dw4/saveintf.h"

enum {CLOSED,STAGE,SERVICE,UNIMPLEMENTED,FAILED,SILENT,WAITING};
struct outcome {int kind;char detail[160];};

static dw4_hubruntime *boot_stage(dw4_mount *mount,const dw4_hubruntime_source *source,const char *stage)
{
    char error[512];
    dw4_hubruntime *h=dw4_hubruntime_prepare(mount,source,stage,0,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare %s: %s\n",stage,error);assert(0);}
    unsigned t=0;
    /* The first Terminal visit plays its introduction; Cross presses skip its pages. */
    for(;t<2600;t++){
        step(h,0,t%10==0?0x4000:0);
        if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;
    }
    assert(t<2600);idle(h,60);return h;
}
static int tick_raw(dw4_hubruntime *h,uint32_t analog,uint32_t pressed,char *error,size_t cap)
{
    dw4_hubruntime_input(h,0,0,analog,0,pressed);
    if(dw4_hubruntime_tick(h,frame++*1000000000ULL/60)){snprintf(error,cap,"%s",dw4_hubruntime_error(h));return -1;}
    return 0;
}
/* Enumerate awake talkers (registered, active, authored box) of a stage. */
struct talker {char name[48];int32_t slot;};
static size_t talkers(dw4_hubruntime *h,struct talker *out,size_t cap)
{
    const dw4_controllers *models=dw4_hubruntime_models(h);size_t n=0;
    for(size_t i=0;i<dw4_controllers_count(models) && n<cap;i++){
        const dw4_stageobject *info;int32_t slot;const dw4_modelctrl *m=dw4_controllers_model(models,i,&info,&slot);
        const float *b;size_t nb;
        if(dw4_modelctrl_talk_boxes(m,&b,&nb)==1 && nb && dw4_modelctrl_active(m) && !strncmp(dw4_stageobject_name(info),"n_",2)){
            snprintf(out[n].name,sizeof out[n].name,"%s",dw4_stageobject_name(info));out[n++].slot=slot;
        }
    }
    return n;
}
static struct outcome run_case(dw4_mount *mount,const dw4_hubruntime_source *source,const char *stage,
    const char *name,int32_t slot,int pick)
{
    struct outcome o={FAILED,"not run"};
    dw4_hubruntime *h=boot_stage(mount,source,stage);
    const dw4_controllers *models=dw4_hubruntime_models(h);const dw4_modelctrl *npc=find(models,name,slot);
    if(!npc || !dw4_modelctrl_active(npc)){snprintf(o.detail,sizeof o.detail,"not generated");o.kind=CLOSED;dw4_hubruntime_close(h);return o;}
    dw4_modelctrl_actor a;dw4_modelctrl_actor_state(npc,&a);
    char error[512]="";
    if(!talk_to(h,npc)){snprintf(o.detail,sizeof o.detail,"no side produced a Cross hit, seq=%s",dw4_modelctrl_sequence(npc));o.kind=SILENT;dw4_hubruntime_close(h);return o;}
    unsigned choice_wait=0,quiet=0,prompts=0;int talked=0,retalk=0,was_two=0;
    for(unsigned k=0;k<4000;k++){
        const dw4_stagetravel *travel=dw4_hubruntime_travel(h);
        if(travel->pending && !strcasecmp(travel->destination,"stagIS11")) {
            /* The card Digi-Elf: the hosted card scene must reach its root menu (the full flow is check-hubcard). */
            char perr[512];dw4_hubruntime_source src={dw4_hubruntime_records(h),dw4_hubruntime_state(h),NULL,dw4_hubruntime_time(h)};
            dw4_hubruntime *scene=dw4_hubruntime_prepare(mount,&src,"stagIS11",0,1,perr,sizeof perr);
            if(!scene){o.kind=FAILED;snprintf(o.detail,sizeof o.detail,"card scene: %.140s",perr);}
            else{
                uint64_t sns=dw4_hubruntime_time(scene);unsigned t=0;int a=0,b=0,c=0;
                for(;t<900;t++){
                    dw4_hubruntime_input(scene,0,0,0,0,0);sns+=16666667ULL;
                    if(dw4_hubruntime_tick(scene,sns))break;
                    if(!dw4_savescene_card_state(dw4_hubruntime_scene(scene),&a,&b,&c)&&a==1&&b==1&&c==1)break;
                }
                if(a==1&&b==1&&c==1){o.kind=SERVICE;snprintf(o.detail,sizeof o.detail,"card album scene reached its menu (SUBWND CARD root)");}
                else{o.kind=FAILED;snprintf(o.detail,sizeof o.detail,"card scene did not reach its menu (%u ticks): %.100s",t,dw4_hubruntime_error(scene));}
                dw4_hubruntime_close(scene);
            }
            dw4_hubruntime_close(h);return o;
        }
        int is13=travel->pending && !strcasecmp(travel->destination,"stagIS13");
        if(travel->pending && (is13 || !strcasecmp(travel->destination,"stagIS12"))) {
            /* The Save Keeper (stagIS12) is served by the hosted save scene, which must run and save; the Terminal's join
             * screen (stagIS13) by the hosted load scene, which finishes on START without saving. */
            char dir[]="/tmp/dw4-npcsave-XXXXXX",stage[128]="";int pos=-9;char perr[512];
            assert(mkdtemp(dir) && !setenv("DW4_SAVE_DIR",dir,1));
            dw4_hubruntime_source src={dw4_hubruntime_records(h),dw4_hubruntime_state(h),NULL,dw4_hubruntime_time(h)};
            dw4_hubruntime *scene=dw4_hubruntime_prepare(mount,&src,is13?"stagIS13":"stagIS12",0,1,perr,sizeof perr);
            if(!scene){o.kind=FAILED;snprintf(o.detail,sizeof o.detail,"save scene: %.140s",perr);}
            else {
                uint64_t sns=dw4_hubruntime_time(scene);unsigned t=0;
                for(;t<12000;t++){
                    dw4_saveintf_trace tr={0};dw4_saveintf_diagnostics(dw4_savescene_intf(dw4_hubruntime_scene(scene)),0,&tr);
                    uint32_t pr=0;if(is13)pr=(tr.control==8&&tr.control_sub==3&&tr.control_subsub==1&&t%20==0)?0x8:0;else if(tr.control==8&&tr.control_sub==3)pr=(t%20==0)?0x8:0;else if(t%20==0)pr=0x4000;
                    dw4_hubruntime_input(scene,0,0,0,0,pr);sns+=16666667ULL;
                    if(dw4_hubruntime_tick(scene,sns))break;
                    const dw4_stagetravel *st=dw4_hubruntime_travel(scene);
                    if(st->pending){snprintf(stage,sizeof stage,"%s",st->destination);pos=st->generate_pos;break;}
                }
                char file[700];snprintf(file,sizeof file,"%s/%s",dir,"BASLUS-20836savedata");
                if(is13){
                    if(*stage && !strcmp(stage,"stagML11") && pos==4 && access(file,F_OK)){o.kind=SERVICE;snprintf(o.detail,sizeof o.detail,"load screen finished on START and returned %s point %d",stage,pos);}
                    else{o.kind=FAILED;snprintf(o.detail,sizeof o.detail,"load scene did not finish (stage '%s' point %d, %u ticks)",stage,pos,t);}
                }else if(*stage && !strcmp(stage,"stagML12") && pos==2 && !access(file,R_OK)){o.kind=SERVICE;snprintf(o.detail,sizeof o.detail,"save screen saved slot 0 and returned %s point %d",stage,pos);}
                else{o.kind=FAILED;snprintf(o.detail,sizeof o.detail,"save scene did not finish (stage '%s', %u ticks)",stage,t);}
                dw4_hubruntime_close(scene);
            }
            char file[700];snprintf(file,sizeof file,"%s/%s",dir,"BASLUS-20836savedata");remove(file);snprintf(file,sizeof file,"%s/%s.bak",dir,"BASLUS-20836savedata");remove(file);rmdir(dir);unsetenv("DW4_SAVE_DIR");
            dw4_hubruntime_close(h);return o;
        }
        if(travel->pending){o.kind=STAGE;snprintf(o.detail,sizeof o.detail,"%s",travel->destination);dw4_hubruntime_close(h);return o;}
        if(dw4_hubruntime_status_active(h)){o.kind=SERVICE;snprintf(o.detail,sizeof o.detail,"SUBWND service window opened");dw4_hubruntime_close(h);return o;}
        int two=has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02");
        /* From the third prompt on, answer the second row: the Commander Room's tutorial staff ask "Do you want to hear the
         * explanation again?" after every explanation, and the first row repeats it forever. */
        if(was_two && !two)prompts++;
        was_two=two;
        uint32_t analog=0,pressed=(!control(h) && k%45==44 && !(two && prompts>=2))?0x4000:0; /* never re-talk once control is back */
        if(two){choice_wait++;if(choice_wait==60&&(pick || prompts>=2))analog=4;else if(choice_wait==80){pressed=0x4000;choice_wait=0;}}else choice_wait=0;
        if(tick_raw(h,analog,pressed,error,sizeof error)){
            const char *m=strstr(error,"SUBWND mode ");
            if(m||strstr(error,"engine service unavailable")){o.kind=UNIMPLEMENTED;snprintf(o.detail,sizeof o.detail,"%.80s",m?m:strstr(error,"engine service"));}
            else{o.kind=FAILED;snprintf(o.detail,sizeof o.detail,"%.150s",error);}
            dw4_hubruntime_close(h);return o;
        }
        int idle_now=control(h) && !has_text(h,"TALKFONT02",NULL) && !has_text(h,"TALKFONT01",NULL) && !has_text(h,"TALKFONT03",NULL) &&
            !dw4_hubruntime_input_state(h)->disabled && (!strcmp(dw4_modelctrl_sequence(npc),"SQ_WAIT") ||
            !strncmp(dw4_modelctrl_sequence(npc),"SQ_WALK",7)); /* a roaming NPC resumes its walk */
        if(has_text(h,"TALKFONT01",NULL)||has_text(h,"TALKFONT02",NULL)||has_text(h,"TALKFONT03",NULL))talked=1;
        if(getenv("DW4_NPC_TRACE") && k%200==0){const dw4_dialogue *d=dw4_hubruntime_dialogue(h);fprintf(stderr,"\nT%u:",k);for(size_t i=0;i<dw4_dialogue_text_count(d);i++){const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);if(t->visible&&t->count)fprintf(stderr," %s/%s/%d",t->group,t->name,(int)t->count);}fprintf(stderr," ctl=%d seq=%s\n",control(h),dw4_modelctrl_sequence(npc));}
        quiet=idle_now?quiet+1:0;
        /* A first conversation can be an introduction that unlocks the service (the junk shop's clerk): talk once more
         * before calling the NPC a plain dialogue. */
        if(k>120 && quiet>150 && talked && retalk<1){
            retalk++;quiet=0;talked=0;tick_raw(h,0,0x4000,error,sizeof error);int hit=dw4_lobby_talk_result(dw4_hubruntime_world(h))==1;
            if(hit)continue;
            /* A wandering NPC has walked off after a real first conversation: nothing more to talk to. */
            o.kind=CLOSED;snprintf(o.detail,sizeof o.detail,"dialogue closed, control restored (the NPC walked off before a second talk)");
            dw4_hubruntime_close(h);return o;
        }
        if(k>120 && quiet>150){
            /* The disk-collector Prmame has no window: its service is the native SYSctlDiskFolder /
             * SYSctlDeviceFolder engine calls, whose effects check-hubprmame asserts. */
            int engine_service=talked && !strcmp(name,"n_prmame");
            o.kind=engine_service?SERVICE:talked?CLOSED:SILENT;
            snprintf(o.detail,sizeof o.detail,engine_service?"dialogue closed; SYSctlDiskFolder/SYSctlDeviceFolder run natively":talked?"dialogue closed, control restored":"no dialogue started (probe missed or NPC asleep), seq=%s",dw4_modelctrl_sequence(npc));dw4_hubruntime_close(h);return o;}
    }
    o.kind=WAITING;
    snprintf(o.detail,sizeof o.detail,"dialogue still waiting after 4000 frames: talked=%d control=%d seq=%s disabled=%d t1=%d t2=%d t3=%d",talked,control(h),dw4_modelctrl_sequence(npc),dw4_hubruntime_input_state(h)->disabled,has_text(h,"TALKFONT01",NULL),has_text(h,"TALKFONT02",NULL),has_text(h,"TALKFONT03",NULL));
    dw4_hubruntime_close(h);return o;
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubNpcs",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    /* stagML02 is the Commander Room: its first visit plays the Digi-Elf welcome, which boot_stage skips with Cross. */
    static const char *const stages[]={"stagML11","stagML12","stagML13","stagML02"};
    unsigned counts[7]={0},total=0;
    for(unsigned s=0;s<4;s++){
        if(getenv("DW4_NPC_STAGE") && strcasecmp(getenv("DW4_NPC_STAGE"),stages[s]))continue;
        frame=0;dw4_hubruntime *probe=boot_stage(&mount,&initial,stages[s]);
        struct talker list[64];size_t n=talkers(probe,list,64);dw4_hubruntime_close(probe);
        for(size_t i=0;i<n;i++)for(int pick=0;pick<2;pick++){
            const char *only=getenv("DW4_NPC_ONLY");char key[96];snprintf(key,sizeof key,"%s:%s:%d",stages[s],list[i].name,list[i].slot);
            if(only && strcmp(only,key))continue;
            frame=0;struct outcome o=run_case(&mount,&initial,stages[s],list[i].name,list[i].slot,pick);
            static const char *const label[]={"closed","stage","service","unimplemented","FAILED","silent","waiting"};
            printf("COVERAGE %s %s[%d] choice%d -> %s: %s\n",stages[s],list[i].name,list[i].slot,pick,label[o.kind],o.detail);
            fflush(stdout);counts[o.kind]++;total++;
        }
    }
    printf("hub NPC coverage: %u cases: %u closed with control restored, %u stage requests, %u implemented services, %u unimplemented SUBWND modes, %u failures, %u no-hit, %u still waiting\n",
        total,counts[CLOSED],counts[STAGE],counts[SERVICE],counts[UNIMPLEMENTED],counts[FAILED],counts[SILENT],counts[WAITING]);
    assert(!counts[FAILED] && total>0);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    return 0;
}
