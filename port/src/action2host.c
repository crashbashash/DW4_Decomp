#include "dw4/action2host.h"
#include "dw4/logoseq.h"
#include "arenalist.h"
#include <string.h>
enum { A2H_FADESET=1,A2H_JOINTSET,A2H_WAITCHECK,A2H_MOTIONSET };
struct logo_a2_component { int kind; const char *name; uint32_t f1,f2; const char *loop; };
struct logo_a2_action { int action,start,count; };
#include "logo_action2_program.h"
enum { MGR=DW4_A2_BASE,SYS=MGR+0x100,ACT=MGR+0x200,WORK=MGR+0x300,
       NODE=MGR+0x400,DATA=MGR+0x500,LIST=MGR+0x600,ARRAY=MGR+0x700,
       PROPS=MGR+0x800,TIMER=MGR+0x900,COMP=MGR+0xa00,VT=MGR+0x1200,
       GETMETA=MGR+0x1300,MSG=MGR+0x1400,RNGSYS=MGR+0x1500,RNG=MGR+0x1600,
       RNGVT=MGR+0x1700,GENRAND=MGR+0x1800,TYPE=0x7000,
       MOTINFO=MGR+0x1900,MOTLIST=MGR+0x1940,MOTROWS=MGR+0x1980,
       MOTELEM=MGR+0x19c0,MOTWORK=MGR+0x1a40,MOTARRAY=MGR+0x1a80,
       MOTION=MGR+0x1b00,MOTTRACK=MGR+0x1c00,INFO=MGR+0x1d00,
       PREVMOTION=MGR+0x1e00,PREVTRACK=MGR+0x1f00,PREVNAME=MGR+0x1f80,MOTNAME=MGR+0x1c80,
       COMPX=MGR+DW4_A2_BYTES };   /* COMP holds DW4_A2_IMAGE_COMPONENTS records of 0x80 bytes; the rest follow the image at COMPX */
static int comp_address(unsigned i){return i<DW4_A2_IMAGE_COMPONENTS?COMP+(int)i*0x80:COMPX+(int)(i-DW4_A2_IMAGE_COMPONENTS)*0x80;}
static int comp_index(int a){
    if(a>=COMP && a<COMP+DW4_A2_IMAGE_COMPONENTS*0x80 && !((a-COMP)&0x7f))return (a-COMP)/0x80;
    if(a>=COMPX && !((a-COMPX)&0x7f))return DW4_A2_IMAGE_COMPONENTS+(a-COMPX)/0x80;
    return -1;
}
/* Translate the recovered rule's bounded addresses at the API boundary. The
 * mapped objects never contain these addresses, even in list/string fields. */
static dw4_action2_mapping *mapping(dw4_action2_host *h,int address,int bytes)
{
    for(unsigned i=0;i<h->mapped;i++)if(address>=h->mapping[i].address &&
       (uint32_t)(address-h->mapping[i].address)<=h->mapping[i].size &&
       (uint32_t)bytes<=h->mapping[i].size-(uint32_t)(address-h->mapping[i].address))return h->mapping+i;
    return NULL;
}
static int real_address(dw4_action2_host *h,int address)
{dw4_action2_mapping *m=mapping(h,address,1);return m?(int)m->object.off+address-m->address:address;}
static int adapter_address(dw4_action2_host *h,int address)
{
    for(unsigned i=0;i<h->mapped;i++)if((uint32_t)address==h->mapping[i].object.off)return h->mapping[i].address;
    return address;
}
static void *mapped_data(dw4_action2_host *h,dw4_action2_mapping *m)
{return dw4_arena_at(h->arena,m->object,m->size);}
static int map_new(dw4_action2_host *h,int address,const char *class_name,uint32_t bytes,uint64_t refs,int kind)
{
    if(h->error)return -1;
    const dw4_metaobject *mo=class_name?dw4_metaobject_find(class_name):NULL;
    if(h->mapped==sizeof h->mapping/sizeof *h->mapping || (class_name && !mo)){h->error=-33;return -1;}
    dw4_handle object=mo?dw4_arena_object_new(h->arena,DW4_REGION_PERSISTENT,mo->vtable):dw4_arena_alloc(h->arena,DW4_REGION_PERSISTENT,bytes);
    if(!object.off){h->error=-33;return -1;}
    h->mapping[h->mapped++]=(dw4_action2_mapping){address,mo?mo->size:bytes,object,refs,!!mo,kind};return 0;
}
static void unmap_to(dw4_action2_host *h,unsigned keep)
{
    while(h->mapped>keep){dw4_action2_mapping *m=h->mapping+--h->mapped;
        if(m->is_object)dw4_arena_object_release(h->arena,m->object);else dw4_arena_free(h->arena,m->object);}
}
static dw4_handle handle_at(const dw4_action2_host *h,int address)
{
    for(unsigned i=0;i<h->mapped;i++)if(h->mapping[i].address==address)return h->mapping[i].object;
    return (dw4_handle){0};
}
dw4_action2_record dw4_action2_host_records(const dw4_action2_host *h)
{
    if(!h)return (dw4_action2_record){0};
    return (dw4_action2_record){h->arena,handle_at(h,MGR),handle_at(h,INFO),handle_at(h,ACT),handle_at(h,WORK),handle_at(h,NODE),handle_at(h,DATA),handle_at(h,TIMER),handle_at(h,MOTION),handle_at(h,MOTTRACK),handle_at(h,PREVMOTION),handle_at(h,PREVTRACK)};
}
void dw4_action2_host_close(dw4_action2_host *h)
{if(h){unmap_to(h,0);memset(h,0,sizeof *h);}}
int dw4_action2_host_started(const dw4_action2_host *h)
{dw4_handle r=h?handle_at(h,ACT):(dw4_handle){0};return r.off?DW4_ARENA_OBJ(h->arena,beAction2InfoRam,r)->_isRun:0;}
int dw4_action2_host_timer_present(const dw4_action2_host *h)
{dw4_handle l=h?handle_at(h,PROPS):(dw4_handle){0};return l.off?al_count(h->arena,(int32_t)l.off)>0:0;}
static int valid(dw4_action2_host *h,int a,int n)
{
    if(n!=1 && n!=4){h->error=a ? a : -30;return 0;}
    if(a>=DW4_A2_BASE && a<=DW4_A2_BASE+DW4_A2_BYTES-n)return 1;
    if(a>=COMPX && mapping(h,a,n))return 1;   /* component records past the image are mapped objects only */
    h->error=a ? a : -30;return 0;
}
static int32_t peek(void *p,int32_t a,int n)
{
    dw4_action2_host *h=p;uint32_t v=0;int i;
    if(n==4) {
        if(a==A2_RHYTHM_GLOBAL && h->rhythm)return (int32_t)*h->rhythm;
        if(a==A2_PROP_TYPE)return TYPE;
        if(a==A2_CLASS_FADESET)return A2H_FADESET;
        if(a==A2_CLASS_JOINTSET)return A2H_JOINTSET;
        if(a==A2_CLASS_WAITCHECK)return A2H_WAITCHECK;
        if(a==A2_CLASS_MOTIONSET)return A2H_MOTIONSET;
        if(a==A2_CLASS_FLASHSET)return -1;
    }
    if(a==A2_GP_FLAG && n==1)return 1;
    if(n==4){if(a==MGR+12)return SYS;if(a==MGR+16)return RNGSYS;if(a==MGR+20)return MSG;}
    if(!valid(h,a,n))return 0;
    dw4_action2_mapping *m=mapping(h,a,n);
    if(m){
        if(n==4 && a==m->address && m->kind)return VT;
        const unsigned char *b=mapped_data(h,m);if(!b){h->error=-34;return 0;}
        for(i=0;i<n;i++)v|=(uint32_t)b[a-m->address+i]<<(8*i);
        if(n==4 && !((a-m->address)&3) && (m->references & (UINT64_C(1)<<((a-m->address)/4))))v=(uint32_t)adapter_address(h,(int)v);
    }else for(i=0;i<n;++i)v|=(uint32_t)h->backend[a-DW4_A2_BASE+i]<<(8*i);
    return (int32_t)v;
}
static void poke(void *p,int32_t a,int n,int32_t v)
{
    dw4_action2_host *h=p;int i;
    if(a==A2_RHYTHM_GLOBAL && n==4 && h->rhythm){*h->rhythm=(uint32_t)v;return;}
    if(!valid(h,a,n))return;
    dw4_action2_mapping *m=mapping(h,a,n);
    if(m){
        unsigned char *b=mapped_data(h,m);if(!b){h->error=-34;return;}
        if(n==4 && !((a-m->address)&3) && (m->references & (UINT64_C(1)<<((a-m->address)/4))))v=real_address(h,v);
        for(i=0;i<n;i++)b[a-m->address+i]=(uint32_t)v>>(8*i);
    }else for(i=0;i<n;++i)h->backend[a-DW4_A2_BASE+i]=(uint32_t)v>>(8*i);
}
static void clock_value(dw4_action2_host *h,int64_t clock)
{
    h->clock=clock;
    poke(h,SYS+0x50,4,(int32_t)(uint64_t)clock);
    poke(h,SYS+0x54,4,(int32_t)((uint64_t)clock>>32));
    /* A MOTIONSET with a blend time (hokanTime) leaves two states in the combiner until the blend has run out: beAction2MOTIONSET_Start adds the new state
     * (FUN_001ae660 -> FUN_001ad990, status 1, blend duration = hokanTime) next to the old one, and the combiner update (FUN_001ac140, run every frame by
     * beAction2MOTIONSET_Update) flags the old state for removal (status 3, FUN_001ae2d0) once elapsed >= duration. The WAITCHECK Motion (case 2) only
     * proceeds when the list holds one state, so the wait ends at max(animation length, blend) after the motion started. */
    if(h->blend_end && peek(h,MOTWORK+8,4))poke(h,MOTWORK+8,4,(int64_t)((uint64_t)clock-(uint64_t)h->blend_end)<0?2:1);
}
static int32_t call(void *p,int32_t addr,const int32_t a[8])
{
    dw4_action2_host *h=p;
    switch(addr) {
    case GENRAND:
        if(h->random && a[0]==RNG)return (int32_t)dw4_random_next(h->random);
        break;
    case GETMETA:{dw4_action2_mapping *m=mapping(h,a[0],1);return m?m->kind:0;}
    case 0x301000:return 1;
    case 0x3022c0:
        if(a[0]!=PROPS || a[1]!=TYPE || a[2]!=A2_TIMER_NAME)break;
        return dw4_action2_host_timer_present(h) ? TIMER : 0;
    case 0x36a510:
        {beBaseInfoRamTimer *t=DW4_ARENA_OBJ(h->arena,beBaseInfoRamTimer,handle_at(h,TIMER));
         memset((unsigned char *)t+8,0,sizeof *t-8);}
        poke(h,TIMER+4,4,1);poke(h,TIMER+A2_T_SCALE,4,0x3f800000);return TIMER;
    case 0x2fecb0:
        if(a[0]!=TIMER || a[1]!=A2_TIMER_NAME)break;
        poke(h,TIMER+8,4,PROPS+0x80);return 0;
    case 0x301e30:
        if(a[0]!=PROPS || a[1]!=TIMER)break;
        {igNamedObjectList *l=DW4_ARENA_OBJ(h->arena,igNamedObjectList,handle_at(h,PROPS));
         l->_count=1;int32_t *v=dw4_arena_at(h->arena,al_handle(l->_data),4);*v=real_address(h,TIMER);}
        poke(h,TIMER+4,4,peek(h,TIMER+4,4)+1);return 0;
    case 0x376680:return 0; /* The native renderer samples typed fade Work in modelctrl. */
    case 0x376930: { /* FADESET remains presentation-only; never gates ISCOMEND. */
        int name=peek(h,a[2]+8,4),frames=ee_f32_trunc_s32((uint32_t)peek(h,a[2]+12,4));
        int first=peek(h,name,1);
        if(first=='H' || first=='I' || first=='O'){h->fade_event++;h->fade_kind=first;h->fade_first_bits=(uint32_t)peek(h,a[2]+12,4);h->fade_limit_bits=(uint32_t)peek(h,a[2]+16,4);}
        if(first=='H'){h->hidden=1;return 1;}
        h->hidden=0;
        if(first=='I')h->fade_in=frames;
        else if(first=='O')h->fade_out=frames;
        else break;
        h->fade_direction=first=='I'?1:2;h->fade_frames=frames;h->fade_serial++;
        return 1;
    }
    case 0x377340: { /* beAction2MOTIONSET_Start (src/unmatched/beAction2MOTIONSET_Start.cpp): the walk reached this MOTIONSET, so its animation starts now. It
                      * always returns 1 (the walk goes on to the WAITCHECK Motion that holds the next component until this animation has played out). */
        int i=a[0]==MGR && a[1]==ACT?comp_index(a[2]):-1;
        dw4_action2_mapping *m=i>=0?mapping(h,a[2],1):NULL,*nm=m?mapping(h,a[2]+0x40,32):NULL,*lm=m?mapping(h,a[2]+0x60,32):NULL;
        if(!m || m->kind!=A2H_MOTIONSET || !nm || !lm)break;
        const char *name=mapped_data(h,nm),*loop=mapped_data(h,lm);
        dw4_action2_host_motion(h,h->clock,h->motionset[i].duration,loop[0]=='L');
        dw4_action2_host_motion_name(h,name,h->motionset[i].blend);
        return 1;
    }
    case 0x36dcd0:return TYPE;
    case 0x38d4a0:
        if(a[0]!=MSG || a[1]!=TYPE || a[2]!=MW_ISCOMEND)break;
        return 0;
    case 0x38f150:
        if(a[0]!=MSG)break;
        h->done=a[1];return 0;
    default:break;
    }
    h->error=addr;return 0;
}
static int32_t call64(void *p,int32_t addr,const int64_t a[8])
{
    dw4_action2_host *h=p;
    if(peek(h,MOTWORK+8,4) && addr==0x1dd4b0 && a[1]>0)return 0;
    if(peek(h,MOTWORK+8,4) && addr==0x1af510 && a[0]==MOTION) {
        igAnimationState *state=DW4_ARENA_OBJ(h->arena,igAnimationState,handle_at(h,MOTION));
        igAnimation *animation=DW4_ARENA_OBJ(h->arena,igAnimation,handle_at(h,MOTTRACK));
        int64_t duration=animation->_duration;
        int64_t elapsed=(int64_t)((uint64_t)a[1]+(uint64_t)state->_timeBias);
        if(elapsed<0)elapsed=0;
        if(h->motion_loop && duration>0)elapsed%=duration;
        else if(elapsed>duration)elapsed=duration;
        poke(h,MOTION+0x28,4,(int32_t)(uint64_t)elapsed);poke(h,MOTION+0x2c,4,(int32_t)((uint64_t)elapsed>>32));return 0;
    }
    h->error=addr;return 0;
}
void dw4_action2_host_motion(dw4_action2_host *h,int64_t start,int64_t duration,int loop)
{
    if(h->error)return;
    h->motion_loop=!!loop;h->motion_start=start;h->blend_end=0;   /* no blend until dw4_action2_host_motion_name names one */
    igAnimationState *state=DW4_ARENA_OBJ(h->arena,igAnimationState,handle_at(h,MOTION));
    igAnimationState *previous=DW4_ARENA_OBJ(h->arena,igAnimationState,handle_at(h,PREVMOTION));
    igAnimation *animation=DW4_ARENA_OBJ(h->arena,igAnimation,handle_at(h,MOTTRACK));
    igAnimation *old_animation=DW4_ARENA_OBJ(h->arena,igAnimation,handle_at(h,PREVTRACK));
    memcpy((unsigned char *)previous+8,(unsigned char *)state+8,sizeof *state-8);
    memcpy((unsigned char *)old_animation+8,(unsigned char *)animation+8,sizeof *animation-8);
    char *old_name=mapped_data(h,mapping(h,PREVNAME,64));memset(old_name,0,64);
    const char *name=al_text(h->arena,animation->_name);if(name)memcpy(old_name,name,strlen(name)+1);
    old_animation->_name=name?real_address(h,PREVNAME):0;
    previous->_animation=real_address(h,PREVTRACK);previous->_baseState=0;
    state->_baseState=name?real_address(h,PREVMOTION):0;
    state->_timeBias=(int64_t)(UINT64_C(0)-((uint64_t)(start>>18)<<18));state->_timeScale=1;
    poke(h,INFO+0x20,4,MOTINFO);poke(h,MOTINFO+0x24,4,MOTLIST);poke(h,MOTLIST+0x10,4,MOTROWS);
    poke(h,MOTLIST+8,4,1);poke(h,MOTLIST+12,4,1);poke(h,MOTWORK+12,4,1);
    poke(h,MOTROWS,4,MOTELEM);poke(h,MOTELEM+0x38,4,MOTWORK);poke(h,MOTWORK+8,4,duration>0);
    poke(h,MOTWORK+0x10,4,MOTARRAY);poke(h,MOTARRAY,4,MOTION);poke(h,MOTION+8,4,MOTTRACK);
    poke(h,MOTION+0x28,4,0);poke(h,MOTION+0x2c,4,0);
    poke(h,MOTTRACK+0x30,4,(int32_t)(uint64_t)duration);poke(h,MOTTRACK+0x34,4,(int32_t)((uint64_t)duration>>32));
}
static void invoke(dw4_action2_host *h,int addr)
{
    const int32_t args[3]={MGR,ACT,MW_ISCOMEND};
    if(h->error)return;
    if(h->invoke){h->invoke(h->oracle_user,addr,&h->api,args);return;}
    if(addr==0x377700)a2_start_components(&h->api,MGR,ACT);
    else if(addr==0x3778d0)a2_update(&h->api,MGR,ACT);
    else if(addr==0x377990)a2_msg_iscomend(&h->api,MGR,ACT,MW_ISCOMEND);
    else h->error=addr;
}
void dw4_action2_host_init(dw4_action2_host *h)
{
    memset(h,0,sizeof(*h));h->arena=dw4_session_arena();
    h->api=(Dw4Action2Api){{h,peek,poke,call},call64};
    if(!h->arena){h->error=-33;return;}
#define REF(off) (UINT64_C(1)<<((off)/4))
    map_new(h,MGR,"beAction2",0,REF(24),0);
    map_new(h,INFO,"beAction2Info",0,REF(24)|REF(32)|REF(36),0);
    map_new(h,ACT,"beAction2InfoRam",0,REF(12)|REF(16)|REF(40)|REF(44)|REF(56),0);
    map_new(h,WORK,"beAction2InfoWork",0,REF(8),0);
    map_new(h,NODE,"beModelCtrlNode2",0,0,0);
    map_new(h,DATA,"beAction2Data",0,REF(8)|REF(12),0);
    map_new(h,LIST,"igObjectList",0,REF(16),0);
    map_new(h,ARRAY,NULL,DW4_A2_MAX_COMPONENTS*4,UINT64_MAX,0);   /* the list's entry words; ARRAY..PROPS holds 64 */
    map_new(h,PROPS,"igNamedObjectList",0,REF(16),0);
    map_new(h,PROPS+0x40,NULL,4,1,0);
    map_new(h,TIMER,"beBaseInfoRamTimer",0,REF(8),0);
    map_new(h,PROPS+0x80,NULL,8,0,0);
    map_new(h,MOTINFO,"igAnimationDatabase",0,REF(36),0);
    map_new(h,MOTLIST,"igAnimationCombinerList",0,REF(16),0);
    map_new(h,MOTROWS,NULL,4,1,0);
    map_new(h,MOTELEM,"igAnimationCombiner",0,REF(56),0);
    map_new(h,MOTWORK,"igAnimationStateList",0,REF(16),0);
    map_new(h,MOTARRAY,NULL,4,1,0);
    map_new(h,MOTION,"igAnimationState",0,REF(8)|REF(24),0);
    map_new(h,MOTTRACK,"igAnimation",0,REF(8),0);
    map_new(h,MGR+0x40,"beAction2InfoList",0,REF(16),0);
    map_new(h,MGR+0x80,NULL,4,1,0);
    map_new(h,INFO+0x40,"beBaseInfoRamList",0,REF(16),0);
    map_new(h,INFO+0x60,NULL,4,1,0);
    map_new(h,INFO+0x80,"beAction2DataList",0,REF(16),0);
    map_new(h,INFO+0xa0,NULL,4,1,0);
    map_new(h,DATA+0x40,NULL,128,0,0);
    map_new(h,PREVMOTION,"igAnimationState",0,REF(8),0);
    map_new(h,PREVTRACK,"igAnimation",0,REF(8),0);
    map_new(h,PREVNAME,NULL,64,0,0);map_new(h,MOTNAME,NULL,64,0,0);
#undef REF
    if(h->error){unmap_to(h,0);return;}
    h->roots=h->mapped;
    memcpy(mapped_data(h,mapping(h,PROPS+0x80,8)),"WAIT",5);
    poke(h,MGR+24,4,MGR+0x40);poke(h,MGR+28,1,1);
    poke(h,MGR+0x40+8,4,1);poke(h,MGR+0x40+12,4,1);poke(h,MGR+0x40+16,4,MGR+0x80);poke(h,MGR+0x80,4,INFO);
    poke(h,INFO+24,4,INFO+0x40);poke(h,INFO+0x40+8,4,1);poke(h,INFO+0x40+12,4,1);poke(h,INFO+0x40+16,4,INFO+0x60);poke(h,INFO+0x60,4,ACT);
    poke(h,INFO+36,4,INFO+0x80);poke(h,INFO+0x80+8,4,1);poke(h,INFO+0x80+12,4,1);poke(h,INFO+0x80+16,4,INFO+0xa0);poke(h,INFO+0xa0,4,DATA);
    poke(h,RNGSYS+0x30,4,RNG);poke(h,RNG,4,RNGVT);poke(h,RNGVT+0x60,4,GENRAND);
    poke(h,ACT+12,4,INFO);poke(h,ACT+16,4,MGR);
    poke(h,ACT+0x28,4,PROPS);poke(h,ACT+0x2c,4,NODE);poke(h,ACT+0x38,4,WORK);
    poke(h,PROPS+12,4,1);poke(h,PROPS+16,4,PROPS+0x40);
    poke(h,NODE+A2_N_SCALE,4,0x3f800000);
    poke(h,DATA+12,4,LIST);poke(h,LIST+12,4,DW4_A2_IMAGE_COMPONENTS);
    poke(h,LIST+16,4,ARRAY);poke(h,VT+0x58,4,GETMETA);
}
void dw4_action2_host_snapshot(const dw4_action2_host *host,unsigned char out[DW4_A2_BYTES])
{
    dw4_action2_host *h=(dw4_action2_host *)host;
    for(int i=0;i<DW4_A2_BYTES;i+=4){uint32_t v=(uint32_t)peek(h,DW4_A2_BASE+i,4);memcpy(out+i,&v,4);}
}
void dw4_action2_host_random(dw4_action2_host *h,dw4_random *random,uint32_t *rhythm)
{h->random=random;h->rhythm=rhythm;}
void dw4_action2_host_start(dw4_action2_host *h,int action,int64_t clock)
{
    const struct logo_a2_action *program=NULL;unsigned k;int i;
    for(k=0;k<sizeof(logo_a2_actions)/sizeof(*logo_a2_actions);++k)
        if(logo_a2_actions[k].action==action)program=&logo_a2_actions[k];
    if(!program || program->count>4){h->error=-31;return;}
    dw4_action2_component components[4];
    for(i=0;i<program->count;i++) {
        const struct logo_a2_component *c=&logo_a2_components[program->start+i];
        components[i]=(dw4_action2_component){c->kind,c->name,c->f1,c->f2,c->loop};
    }
    dw4_action2_host_start_program(h,components,(unsigned)program->count,clock);
}
void dw4_action2_host_start_program(dw4_action2_host *h,
                                    const dw4_action2_component *components,
                                    unsigned count,int64_t clock)
{
    unsigned i;
    if(count>DW4_A2_MAX_COMPONENTS || (count && !components)){h->error=-31;return;}
    for(i=0;i<count;i++) if(!components[i].name || !components[i].loop ||
       components[i].kind<DW4_A2_FADESET || components[i].kind>DW4_A2_MOTIONSET ||
       strlen(components[i].name)>=32 || strlen(components[i].loop)>=32) {
        h->error=-32;return;
    }
    /* Native action replacement boundary: timer storage and node survive;
     * component states/index reset. ACTION message handling is not recovered. */
    if(h->error)return;
    unmap_to(h,h->roots);
    memset(mapped_data(h,mapping(h,ARRAY,DW4_A2_MAX_COMPONENTS*4)),0,DW4_A2_MAX_COMPONENTS*4);
    beAction2InfoWork *work=DW4_ARENA_OBJ(h->arena,beAction2InfoWork,handle_at(h,WORK));
    /* Native presentation fades continue through a later DELAY action. Only
     * their typed values persist; command/joint/wait state starts afresh. */
    int fade=work->_fadeSt0;float limit=work->_fadeLimitValue,add=work->_fadeAddValue,value=work->_fadeValue;
    memset((unsigned char *)work+8,0,sizeof *work-8);
    work->_fadeSt0=fade;work->_fadeLimitValue=limit;work->_fadeAddValue=add;work->_fadeValue=value;
    poke(h,WORK+4,4,1);poke(h,WORK+8,4,DATA);
    poke(h,LIST+8,4,count);poke(h,LIST+12,4,count>DW4_A2_IMAGE_COMPONENTS?(int)count:DW4_A2_IMAGE_COMPONENTS);
    h->fade_in=h->fade_out=0;poke(h,ACT+20,1,1);h->done=0;
    clock_value(h,clock);
    for(i=0;i<count;++i) {
        const dw4_action2_component *c=&components[i];
        int p=comp_address(i);
        const char *class_name=c->kind==A2H_FADESET?"beAction2FADESET":c->kind==A2H_JOINTSET?"beAction2JOINTSET":c->kind==A2H_MOTIONSET?"beAction2MOTIONSET":"beAction2WAITCHECK";
        uint64_t refs=UINT64_C(1)<<2;if(c->kind==A2H_JOINTSET || c->kind==A2H_MOTIONSET)refs|=UINT64_C(1)<<5;
        h->motionset[i].duration=c->duration;h->motionset[i].blend=c->blend;
        map_new(h,p,class_name,0,refs,c->kind);
        map_new(h,p+0x40,NULL,32,0,0);map_new(h,p+0x60,NULL,32,0,0);
        if(h->error)return;
        poke(h,ARRAY+i*4,4,p);poke(h,p+8,4,p+0x40);
        if(c->kind!=A2H_MOTIONSET)poke(h,p+12,4,(int32_t)c->first);   /* a MOTIONSET's +12 is its hokanMode string, which the host does not read */
        if(c->kind!=A2H_WAITCHECK)poke(h,p+16,4,(int32_t)c->last);
        if(c->kind==A2H_JOINTSET || c->kind==A2H_MOTIONSET)poke(h,p+20,4,p+0x60);
        memcpy(mapped_data(h,mapping(h,p+0x40,32)),c->name,strlen(c->name)+1);
        memcpy(mapped_data(h,mapping(h,p+0x60,32)),c->loop,strlen(c->loop)+1);
        if(c->kind==A2H_JOINTSET) {
            h->joint_first=ee_f32_trunc_s32(c->first);h->joint_last=ee_f32_trunc_s32(c->last);
        }
    }
    invoke(h,0x377700);
}
int64_t dw4_action2_host_node_time(const dw4_action2_host *h,int64_t clock)
{
    return a2_node_time(&h->api,NODE,clock);
}

int dw4_action2_host_tick(dw4_action2_host *h,int64_t clock)
{
    clock_value(h,clock);
    if(!dw4_action2_host_started(h) || h->error)return 0;
    invoke(h,0x3778d0);invoke(h,0x377990);
    return !h->error && h->done;
}

int dw4_action2_host_set_name(dw4_action2_host *h,const char *name)
{
    if(!h || h->error)return -1;
    if(name && strlen(name)>=128){h->error=-32;return -1;}
    char *s=mapped_data(h,mapping(h,DATA+0x40,128));memset(s,0,128);
    if(name)memcpy(s,name,strlen(name)+1);
    poke(h,DATA+8,4,name?DATA+0x40:0);return 0;
}
const char *dw4_action2_host_name(const dw4_action2_host *h)
{
    if(!h || !h->mapped)return NULL;
    const beAction2Data *d=DW4_ARENA_OBJ(h->arena,beAction2Data,handle_at(h,DATA));
    return al_text(h->arena,d->_name);
}

int dw4_action2_host_motion_name(dw4_action2_host *h,const char *name,int64_t blend)
{
    if(!h || h->error)return -1;
    if(!name || strlen(name)>=64){h->error=-32;return -1;}
    char *s=mapped_data(h,mapping(h,MOTNAME,64));memset(s,0,64);memcpy(s,name,strlen(name)+1);
    igAnimation *a=DW4_ARENA_OBJ(h->arena,igAnimation,handle_at(h,MOTTRACK));a->_name=real_address(h,MOTNAME);
    igAnimationState *state=DW4_ARENA_OBJ(h->arena,igAnimationState,handle_at(h,MOTION));state->_blendDuration=blend;
    /* only a motion that has a base state to blend from (the first motion of a fresh combiner is the only state, count 1: the new state's base is 0) */
    if(blend>0 && state->_baseState && peek(h,MOTWORK+8,4)){h->blend_end=(int64_t)((uint64_t)h->motion_start+(uint64_t)blend);clock_value(h,h->clock);}   /* two states until the blend has run out */
    return 0;
}
