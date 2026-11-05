#include "dw4/logoseq.h"
#include <stddef.h>
#include "title-menu.h"
enum { LOGO_ACTION,LOGO_WCHECK,LOGO_JUMP };
struct logo_command { int op,name; };
struct logo_sequence { int name,start,count; };
#include "logo_program.h"
enum { OWNER=0x1300000,INFO=0x1300100,NODE=0x1300200,WORK=0x1300300,
       CMD=0x1300400,VT=0x1300500,JUMP=0x1300600,FALLBACK=0x1300610,
       STRING=0x1300708,POOL=0x1300800 };
typedef struct { dw4_logo_seq *s; const dw4_logo_hooks *hooks; Dw4LoadIntf2Api api; } Context;
static void dispatch(Context *);
static int invoke(Context *c,int addr,const int32_t args[4])
{
    if(c->hooks->invoke)return c->hooks->invoke(c->hooks->user,addr,&c->api,args);
    if(addr==0x394ae0)return mw_jump(&c->api,args[0],args[1],args[2]);
    if(addr==0x394b30)return mw_start(&c->api,args[0],args[1],args[2]);
    mw_update(&c->api,args[0],args[1],args[2],args[3]);return 0;
}
static int32_t peek(void *p,int32_t a,int width)
{
    Context *c=p;dw4_logo_seq *s=c->s;
    if(width!=4){s->error=-20;return 0;}
    switch(a) {
    case OWNER:return VT;
    case VT+0x8c:return JUMP;
    case VT+0xa4:return FALLBACK;
    case OWNER+20:return POOL;
    case INFO+8:return T_j_startlogo;
    case NODE+8:return 0;
    case CMD+8:return s->command;
    case WORK+0x4c:return s->wait;
    case STRING-4:return s->refs;
    case STRING-8:return POOL;
    case 0x586f20:return POOL;
    default:s->error=a;return 0;
    }
}
static void poke(void *p,int32_t a,int width,int32_t value)
{
    Context *c=p;
    if(width!=4)c->s->error=-20;
    else if(a==WORK+0x4c)c->s->wait=value;
    else if(a==STRING-4)c->s->refs=value;
    else c->s->error=a;
}
static int32_t call(void *p,int32_t addr,const int32_t a[8])
{
    Context *c=p;dw4_logo_seq *s=c->s;
    switch(addr) {
    case 0x12a4a4:
        if(a[0]!=STRING){s->error=-21;return 1;}
        return a[1]!=MW_ACTION;
    case 0x2eaf60:
        if(!a[1])return 0;
        if(a[1]!=MW_ACTION){s->error=-22;return 0;}
        ++s->refs;return STRING;
    case 0x30c940:return 0;
    case 0x38e5f0:
        if(a[0]!=POOL || a[1]!=MW_ACTION2 || a[2]!=T_j_startlogo || a[3]!=0 || a[4]!=MW_ISCOMEND)s->error=-23;
        return 0;
    case 0x38f220:return s->done;
    case 0x395250:
        if(s->wait){s->error=-24;return 0;}
        dispatch(c);return 0;
    case JUMP:
        s->sequence=a[2];s->index=0;
        if(a[2]==LOGO_SQ_ERAS)s->removed=1;
        else if(a[2]!=LOGO_SQ_WAIT)s->error=-25;
        return 0;
    default:s->error=addr;return 0;
    }
}
static void dispatch(Context *c)
{
    dw4_logo_seq *s=c->s;const struct logo_sequence *seq=NULL;unsigned i;
    for(i=0;i<sizeof(logo_sequences)/sizeof(*logo_sequences);++i)
        if(logo_sequences[i].name==s->sequence)seq=&logo_sequences[i];
    if(!seq){s->error=-26;return;}
    while(!s->error && s->index<seq->count) {
        const struct logo_command *cmd=&logo_commands[seq->start+s->index];
        s->command=cmd->name;
        if(cmd->op==LOGO_ACTION){s->done=0;c->hooks->action(c->hooks->user,cmd->name);++s->index;}
        else if(cmd->op==LOGO_WCHECK){invoke(c,0x394b30,(int32_t[4]){OWNER,WORK,CMD,0});++s->index;return;}
        else if(cmd->op==LOGO_JUMP){invoke(c,0x394ae0,(int32_t[4]){OWNER,WORK,CMD,0});return;}
        else {s->error=-27;return;}
    }
}
static Context context(dw4_logo_seq *s,const dw4_logo_hooks *hooks)
{
    Context c={s,hooks,{NULL,peek,poke,call}};return c;
}
void dw4_logo_start(dw4_logo_seq *s,int sequence,const dw4_logo_hooks *hooks)
{
    Context c=context(s,hooks);c.api.user=&c;
    s->sequence=sequence;s->index=0;s->removed=0;
    /* Replacement retains the old wait until recovered WCHECK assignment
     * interns the new string and releases the previous reference. */
    dispatch(&c);
}
void dw4_logo_tick(dw4_logo_seq *s,int done,const dw4_logo_hooks *hooks)
{
    Context c=context(s,hooks);c.api.user=&c;s->done=done;
    if(s->wait && !s->error)invoke(&c,0x394bf0,(int32_t[4]){OWNER,INFO,NODE,WORK});
}
