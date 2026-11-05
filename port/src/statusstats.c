#include "dw4/statusstats.h"
#include "statuswork.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
static const char *const fields[]={"MHP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN",
    "SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO","HP","MP"};
static const char *const fonts[]={"font010","font011","font040","font041","font042","font043",
    "font044","font045","font046","font047","font048","font000","font001"};
static int bad(char *e,size_t n,const char *key)
{snprintf(e,n,"STATUS player record/dependency %s unavailable",key);return -1;}
static int number(dw4_property_folder *f,const char *key,int32_t *v,char *e,size_t n)
{return dw4_property_number(f,key,v)?bad(e,n,key):0;}
static int text(dw4_statusstats_io io,void *u,const char *g,const char *font,const char *s)
{dw4_statusstats_command c={.op=DW4_STATS_TEXT,.group=g,.font=font,.text=s};return io(u,&c);}
static int numeric(dw4_statusstats_io io,void *u,const char *g,const char *font,int32_t v)
{char s[16];snprintf(s,sizeof s,"%" PRId32,v);return text(io,u,g,font,s);}
int dw4_statusstats_update(dw4_statusstats_snapshot *snap,dw4_playerrecords *players,int32_t player,
    dw4_statusstats_name name,void *db,dw4_statusstats_io io,void *u,char *e,size_t n)
{
    if(!snap || !io || !name)return bad(e,n,"stat owner/database");
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);
    if(!f)return bad(e,n,"player index");
    dw4_unicode_object unicode;int32_t level,digimon,xdata,bit,exp,next;
    dw4_statusstats_snapshot result={.valid=1,.player=player};
    if(dw4_property_unicode_object(f,"PLAYERNAME",0,&unicode) || !unicode.present)return bad(e,n,"PLAYERNAME Unicode object");
    if(number(f,"LEVEL",&level,e,n) || number(f,"DIGIMONNO",&digimon,e,n) ||
       number(f,"XDATA",&xdata,e,n) || number(f,"BIT",&bit,e,n) ||
       number(f,"EXP",&exp,e,n) || number(f,"NEXTEXP",&next,e,n))return -1;
    for(unsigned i=0;i<13;i++)if(number(f,fields[i],result.value+i,e,n))return -1;
    const char *species=name(db,digimon);if(!species)return bad(e,n,"shinka NAME");
    dw4_statusstats_command c={.op=DW4_STATS_UNICODE,.group="STWINFONT02",.font="font000",.unicode=unicode};
    if(io(u,&c))goto failed;
    if(level>=1000)level=999;
    if(numeric(io,u,"STWINFONT04","font000",level) || text(io,u,"STWINFONT04","font001",species))goto failed;
    if(numeric(io,u,"STWINFONT06",fonts[11],result.value[11]) ||
       numeric(io,u,"STWINFONT06",fonts[12],result.value[12]))goto failed;
    for(unsigned i=0;i<11;i++)if(numeric(io,u,"STWINFONT06",fonts[i],result.value[i]))goto failed;
    if(numeric(io,u,"STWINFONT06","font049",xdata) || numeric(io,u,"STWINFONT06","font070",bit))goto failed;
    /* EE SUBU followed by signed BLTZ; avoid signed host overflow. */
    uint32_t difference=(uint32_t)next-(uint32_t)exp;
    if(level>=999){if(text(io,u,"STWINFONT06","font071","----"))goto failed;}
    else if(difference&0x80000000u){if(text(io,u,"STWINFONT06","font071","0"))goto failed;}
    else if(numeric(io,u,"STWINFONT06","font071",(int32_t)difference))goto failed;
    *snap=result;return 0;
failed:snap->valid=0;return bad(e,n,"text sink");
}
static int preview_folder(dw4_statusstats_snapshot *snap,dw4_property_folder *f,int32_t player,
    int on,dw4_statusstats_io io,void *u,char *e,size_t n)
{
    if(!snap || !snap->valid || snap->player!=player || !io)return bad(e,n,"comparison snapshot");
    int32_t values[11],hp,mp;
    if(!f)return bad(e,n,"player index");
    if(on){for(unsigned i=0;i<11;i++)if(number(f,fields[i],values+i,e,n))return -1;}
    else {
        /* Preflight the two existing scalar records before emitting or writing. */
        if(number(f,"HP",&hp,e,n) || number(f,"MP",&mp,e,n))return -1;
        memcpy(values,snap->value,sizeof values);
    }
    for(unsigned i=0;i<11;i++){
        if(numeric(io,u,"STWINFONT06",fonts[i],values[i]))goto failed;
        dw4_statusstats_command c={.op=on?DW4_STATS_COLOR:DW4_STATS_DEFAULTCOLOR,.group="STWINFONT06",.font=fonts[i]};
        if(values[i]==snap->value[i]){c.color[0]=c.color[1]=c.color[2]=.9f;}
        else if(values[i]<snap->value[i]){c.color[0]=.94f;c.color[1]=.4f;c.color[2]=.25f;}
        else {c.color[0]=0;c.color[1]=.96f;c.color[2]=1;}
        if(io(u,&c))goto failed;
    }
    if(!on){
        if(dw4_property_set_number(f,"HP",snap->value[11]) || dw4_property_set_number(f,"MP",snap->value[12]))goto failed;
    }
    return 0;
failed:snap->valid=0;return bad(e,n,"text sink");
}
int dw4_statusstats_preview(dw4_statusstats_snapshot *snap,dw4_playerrecords *players,int32_t player,
    int on,dw4_statusstats_io io,void *u,char *e,size_t n)
{return preview_folder(snap,dw4_playerrecords_get(players,"GETPLAYER",player),player,on,io,u,e,n);}
static dw4_script_value string(const char *s)
{return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int native(void *u,const dw4_statusstats_command *c)
{
    dw4_statusstats *s=u;
    if(c->op==DW4_STATS_UNICODE)return dw4_dialogue_set_unicode(s->dialogue,c->group,c->font,c->unicode.codes,c->unicode.count);
    char encoded[8192],value[128];const char *key="TEXTSET",*v=c->text;
    if(c->op==DW4_STATS_COLOR){key="COLOR";snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>",c->color[0],c->color[1],c->color[2]);v=value;}
    else if(c->op==DW4_STATS_DEFAULTCOLOR){key="DEFAULTCOLOR";v=NULL;}
    int len=snprintf(encoded,sizeof encoded,v?"%s/%s/%s":"%s/%s",c->group,c->font,v);
    if(len<0 || (size_t)len>=sizeof encoded)return -1;
    dw4_script_value a[]={string("TEXTCTL"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},string(key),string(encoded)},r;
    char error[256];return dw4_scriptservices_call(s->sd,"sd",a,5,&r,error,sizeof error);
}
static beNDMWStatusInfoWork *owner_work(const dw4_statusstats *s)
{return s && s->work.off?DW4_ARENA_OBJ(s->arena,beNDMWStatusInfoWork,s->work):NULL;}
static int owner_prepare(dw4_statusstats *s)
{
    if(s->work.off)return 0;
    s->arena=dw4_session_arena();s->work=s->arena?status_work_new(s->arena):(dw4_handle){0};
    s->owns_work=!!s->work.off;return s->work.off?0:-1;
}
void dw4_statusstats_close(dw4_statusstats *s)
{
    if(!s)return;
    if(s->owns_work)status_work_drop(s->arena,s->work);
    s->work.off=0;s->arena=NULL;s->owns_work=0;
}
int dw4_statusstats_bind(dw4_statusstats *s,dw4_handle h)
{
    if(!s)return -1;
    if(!h.off){if(owner_prepare(s))return -1;h=s->work;}
    dw4_arena *a=dw4_session_arena();const dw4_metaobject *mo=dw4_metaobject_find("beNDMWStatusInfoWork");
    if(!a || !dw4_arena_object_is(a,h,mo->vtable))return -1;
    beNDMWStatusInfoWork *w=DW4_ARENA_OBJ(a,beNDMWStatusInfoWork,h);
    const dw4_metaobject *li=dw4_metaobject_find("igIntList");
    if(!dw4_arena_object_is(a,al_handle(w->_parameter),li->vtable) ||
       !dw4_arena_object_is(a,al_handle(w->_preview),li->vtable))return -1;
    if(s->work.off!=h.off){dw4_statusstats_close(s);s->arena=a;s->work=h;}
    al_list(a,w->_parameter)->_count=0;return 0;
}
dw4_statusstats_snapshot dw4_statusstats_state(const dw4_statusstats *s)
{
    dw4_statusstats_snapshot out={0};beNDMWStatusInfoWork *w=owner_work(s);
    if(w && al_count(s->arena,w->_parameter)==13){out.valid=1;out.player=s->player;memcpy(out.value,al_words(s->arena,w->_parameter),sizeof out.value);}
    return out;
}
static void owner_result(dw4_statusstats *s,const dw4_statusstats_snapshot *out)
{
    igIntList *l=DW4_ARENA_OBJ(s->arena,igIntList,al_handle(owner_work(s)->_parameter));
    if(!out->valid){l->_count=0;return;}
    l->_count=13;memcpy(al_words(s->arena,owner_work(s)->_parameter),out->value,sizeof out->value);s->player=out->player;
}
int dw4_statusstats_refresh(void *u,int32_t player,char *e,size_t n)
{
    dw4_statusstats *s=u;if(!s || !s->sd || !s->dialogue)return bad(e,n,"native stat owner");
    if(owner_prepare(s) || al_reserve(s->arena,owner_work(s)->_parameter,4,13))return bad(e,n,"stat list allocation");
    dw4_statusstats_snapshot result=dw4_statusstats_state(s);
    int rc=dw4_statusstats_update(&result,s->players,player,s->name,s->database,native,s,e,n);
    owner_result(s,&result);return rc;
}
int dw4_statusstats_compare(dw4_statusstats *s,int32_t player,int on,char *e,size_t n)
{
    if(!s || !s->sd || !s->dialogue)return bad(e,n,"native stat owner");
    dw4_statusstats_snapshot result=dw4_statusstats_state(s);
    int rc=dw4_statusstats_preview(&result,s->players,player,on,native,s,e,n);
    if(owner_work(s))owner_result(s,&result);
    return rc;
}
int dw4_statusstats_compare_folder(dw4_statusstats *s,dw4_property_folder *f,char *e,size_t n)
{
    if(!s || !s->sd || !s->dialogue)return bad(e,n,"native stat owner");
    dw4_statusstats_snapshot result=dw4_statusstats_state(s);
    int rc=preview_folder(&result,f,s->player,1,native,s,e,n);
    if(owner_work(s))owner_result(s,&result);
    return rc;
}
