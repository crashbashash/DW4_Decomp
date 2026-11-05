/* Test-only access to the lower model executor, so the oracle can run original
 * title AND common-model instructions over the same bounded engine boundary. */
#include "../src/titlehost.c"
static dw4_title_host hosts[2];
static int (*logo_oracle)(int,int,const Dw4LoadIntf2Api *,const int32_t *);
static int logo_invoke(void *p,int addr,const Dw4LoadIntf2Api *api,const int32_t a[4])
{ return logo_oracle((int)((dw4_title_host *)p-hosts),addr,api,a); }
void bridge_logo_oracle(int (*fn)(int,int,const Dw4LoadIntf2Api *,const int32_t *))
{ logo_oracle=fn; }

static void (*action2_oracle)(int,int,const Dw4Action2Api *,const int32_t *);
static void action2_invoke(void *p,int addr,const Dw4Action2Api *api,const int32_t a[3])
{ action2_oracle((int)((dw4_title_host *)p-hosts),addr,api,a); }
void bridge_action2_oracle(void (*fn)(int,int,const Dw4Action2Api *,const int32_t *))
{ action2_oracle=fn; }
static uint64_t (*clock_oracle)(int,uint32_t,const Dw4SystemClockApi *,uint64_t,uint64_t);
static uint64_t clock_invoke(void *p,uint32_t entry,const Dw4SystemClockApi *api,uint64_t a,uint64_t b)
{ return clock_oracle((int)((dw4_title_host *)p-hosts),entry,api,a,b); }
void bridge_clock_oracle(uint64_t (*fn)(int,uint32_t,const Dw4SystemClockApi *,uint64_t,uint64_t))
{ clock_oracle=fn; }
void bridge_pause(int i) { dw4_clock_host_pause(&hosts[i].clock); }
void bridge_resume(int i) { dw4_clock_host_resume(&hosts[i].clock); }
void bridge_scale(int i,int32_t scale) { dw4_clock_host_scale(&hosts[i].clock,scale); }
int64_t bridge_world(int i) { return hosts[i].clock_ns; }
void bridge_clock(int i,int64_t clock) { dw4_title_host_set_clock(&hosts[i],clock); }
void bridge_model_tick(int i) { tick(&hosts[i]); }
int bridge_logo_done(int i) { return hosts[i].logo_action.done; }
int bridge_error(int i) { return hosts[i].error | hosts[i].logo_action.error; }
void bridge_init(int i) {
    dw4_title_host_close(&hosts[i]);
    dw4_title_host_init(&hosts[i],0,1);
    if(clock_oracle) { hosts[i].clock.invoke=clock_invoke;hosts[i].clock.oracle_user=&hosts[i]; }
    if(logo_oracle)hosts[i].logo_hooks.invoke=logo_invoke;
    if(action2_oracle) {
        hosts[i].logo_action.invoke=action2_invoke;
        hosts[i].logo_action.oracle_user=&hosts[i];
    }
}
void bridge_logo_play(int i,int seq) { schedule(&hosts[i],T_j_startlogo,seq); }

void bridge_advance(int i) { advance_models(&hosts[i]); }
void bridge_tick(int i,unsigned dir,unsigned pressed)
{ Dw4TitleInput in={dir,0,pressed,0};dw4_title_host_tick(&hosts[i],&in,1); }
int bridge_peek(int i,int addr,int width)
{ return hosts[i].common_model.api.peek(&hosts[i].common_model,addr,width); }
void bridge_poke(int i,int addr,int width,int value)
{ hosts[i].common_model.api.poke(&hosts[i].common_model,addr,width,value); }
int bridge_call(int i,int addr,const int a[8])
{
    dw4_title_host *h=&hosts[i];
    switch(addr) {
    case 0x3ebe00:show(h,a[1],a[2]);return 0;
    case 0x3ec050:hide(h,a[1]);return 0;
    case 0x38d860:begin(h,a[1]==CM_MODELCTRL?T_MODELCTRL:a[1],a[2],a[3]);return 0;
    case 0x38e5d0:target(h,a[1]);return 0;
    case 0x38e670:common(h,a[1],a[2]);return 0;
    case 0x38f830:string(h,a[1]);return 0;
    case 0x38f250:integer(h,a[1]);return 0;
    case 0x38e060:end(h,a[1]==CM_ISSEQNAME?T_ISSEQNAME:a[1]);return 0;
    case 0x38e5f0:send(h,a[1]==CM_MODELCTRL?T_MODELCTRL:a[1],a[2],a[3],
        a[4]==CM_GENERATE?T_GENERATE:a[4]==CM_ISRUN?T_ISRUN:a[4]);return 0;
    case 0x38f220:return read_bool(h,a[1]);
    default:return h->common_model.api.call(&h->common_model,addr,a);
    }
}
void bridge_state(int i,int *ctrl,int *opt)
{ memcpy(ctrl,&hosts[i].ctrl,sizeof(hosts[i].ctrl));memcpy(opt,&hosts[i].option,sizeof(hosts[i].option)); }
void bridge_set_state(int i,const int *ctrl,const int *opt)
{ memcpy(&hosts[i].ctrl,ctrl,sizeof(hosts[i].ctrl));memcpy(&hosts[i].option,opt,sizeof(hosts[i].option));
  hosts[i].camera=hosts[i].option._comConf;hosts[i].light=hosts[i].option._lightConf; }
/* Pointer-free observable snapshot; includes complete queue storage and model
 * state, text visibility, handoff and settings, but excludes message scratch. */
int bridge_snapshot(int i,unsigned char *out)
{
    dw4_title_host *h=&hosts[i];int n=0;
#define COPY(x) do { memcpy(out+n,&(x),sizeof(x));n+=sizeof(x); } while(0)
    COPY(h->ctrl);COPY(h->option);COPY(h->model);COPY(h->logo);COPY(h->common_model.memory);
    COPY(h->common_model.used);COPY(h->common_model.error);
    COPY(h->text);COPY(h->frame);COPY(h->handoff);COPY(h->next_stage);COPY(h->error);
    COPY(h->camera);COPY(h->light);COPY(h->clock_ns);COPY(h->clock.memory);COPY(h->clock.raw);COPY(h->clock.external);COPY(h->clock.error);
    unsigned char image[DW4_A2_BYTES];dw4_action2_host_snapshot(&h->logo_action,image);COPY(image);
    int timer_present=dw4_action2_host_timer_present(&h->logo_action),started=dw4_action2_host_started(&h->logo_action);
    COPY(timer_present);COPY(started);
    COPY(h->logo_action.done);COPY(h->logo_action.error);COPY(h->logo_action.fade_in);
    COPY(h->logo_action.fade_out);COPY(h->logo_action.joint_first);COPY(h->logo_action.joint_last);
#undef COPY
    return n;
}
