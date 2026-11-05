#include "dw4/subwindow.h"
#include "dw4/object.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
struct slot {
    dw4_subwindows *owner;const dw4_stageobject *info;int32_t index;
    uint64_t token;dw4_arena *arena;dw4_handle manager,ram;
    dw4_menu_window *root,*prepared;
};
struct dw4_subwindows {
    dw4_scriptservices *sd;struct slot **slot;size_t n;int busy,failed,preparing;
    dw4_subwindow_factory factory;
    dw4_script_binding override;void *override_user;
    char error[256];
};
static beNDMWStatusInfoRam *ram(const struct slot *s)
{return DW4_ARENA_OBJ(s->arena,beNDMWStatusInfoRam,s->ram);}
static beNDMWStatus *manager(const struct slot *s)
{return DW4_ARENA_OBJ(s->arena,beNDMWStatus,s->manager);}
static dw4_subwindow_state snapshot(const struct slot *s)
{
    const beNDMWStatusInfoRam *r=ram(s);const beNDMWStatus *m=manager(s);
    return (dw4_subwindow_state){r->_isRun,r->_st0,r->_st1,r->_st2,r->_st3,m->_whoGenerate,m->_subWndNo};
}
static int equal(dw4_script_value v,const char *s)
{return v.type==DW4_SCRIPT_STRING && v.string && v.length==strlen(s) && !memcmp(v.string,s,v.length);}
static dw4_script_value string(const char *s)
{return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int parse(dw4_script_value v,int32_t *mode,int32_t *player)
{
    static const char *names[]={"STATUS","XDATA","LABO","BANK","CNOS","DISK","WPU","APU","CHIP","JUNK","CARD"};
    if(v.type!=DW4_SCRIPT_STRING || !v.string || v.length>=128 || memchr(v.string,0,v.length))return -1;
    char text[128];memcpy(text,v.string,v.length);text[v.length]=0;
    char *opt=strchr(text,'/');*player=0;
    if(opt){*opt++=0;
        if(strncmp(opt,"I<",2))return -1;
        char *end;errno=0;long value=strtol(opt+2,&end,10);
        if(errno || end==opt+2 || strcmp(end,">") || value<0 || value>=4)return -1;
        *player=(int32_t)value;}
    for(unsigned i=0;i<sizeof(names)/sizeof(*names);i++)if(!strcmp(text,names[i])){*mode=(int32_t)i;return 0;}
    return -1;
}
static int service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct slot *s=user;dw4_subwindows *o=s->owner;*r=(dw4_script_value){0};
    if(o->override)return o->override(o->override_user,method,a,n,r,error,cap);
    if(n==4 && equal(a[3],"ISRUN")){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,ram(s)->_isRun,NULL,0};return 0;}
    if(strcmp(method,"sd")){snprintf(error,cap,"SUBWND requires ISRUN for queries");return -1;}
    if((n==4 || n==5) && (equal(a[3],"UPDATE") || equal(a[3],"ONPREVIEW") || equal(a[3],"OFPREVIEW"))){
        int32_t player=0;
        if(n==5){
            dw4_script_value value=a[4];
            if(value.type!=DW4_SCRIPT_STRING || !value.string || value.length!=4 || value.string[0]!='I' || value.string[1]!='<' || value.string[2]<'0' || value.string[2]>'3' || value.string[3]!='>'){
                snprintf(error,cap,"SUBWND stat command requires player I<0..3>");return -1;
            }
            player=value.string[2]-'0';
        }
        if(equal(a[3],"UPDATE")){
            if(o->factory.update)return o->factory.update(o->factory.user,player,error,cap);
        }else if(o->factory.preview)return o->factory.preview(o->factory.user,player,equal(a[3],"ONPREVIEW"),error,cap);
        snprintf(error,cap,"SUBWND stat command requires its actual stat/preview owner");return -1;
    }
    if(n==4 && equal(a[3],"REMOVE")) {
        dw4_subwindow_state value=snapshot(s);
        if(dw4_subwindow_remove(&value,s->root)) {
            /* 3d6240..3d62a0: keep active and retry through the actual SD queue. */
            dw4_script_value next[]={string("SUBWND"),dw4_stageobject_name(s->info)?string(dw4_stageobject_name(s->info)):(dw4_script_value){0},
                {DW4_SCRIPT_NUMBER,s->index,NULL,0},string("REMOVE"),{DW4_SCRIPT_NUMBER,1,NULL,0}};
            return dw4_scriptservices_call(o->sd,"sd",next,5,r,error,cap);
        }
        return 0;
    }
    if(n==5 && equal(a[3],"GENERATE")) {
        /* Retail ignores a second GENERATE before decoding its payload. */
        if(ram(s)->_isRun)return 0;
        int32_t mode,player;if(parse(a[4],&mode,&player))goto unsupported;
        if(!o->factory.prepare || !o->factory.begin || !o->factory.end) {
            snprintf(error,cap,"SUBWND %.*s needs a native menu tree and player inventory/save records",(int)a[4].length,a[4].string);return -1;
        }
        if(o->preparing || o->failed){snprintf(error,cap,"SUBWND menu preparation is reentrant or failed; recreate the scene");return -1;}
        dw4_menu_window *root=NULL;o->preparing=1;
        int rc=o->factory.prepare(o->factory.user,mode,player,&root,error,cap);o->preparing=0;
        if(rc) {
            if(dw4_menu_window_is_root(root))dw4_menu_window_close(root);
            return -1;
        }
        if(root && !dw4_menu_window_is_root(root)){snprintf(error,cap,"SUBWND factory returned a borrowed child instead of a private root");return -1;}
        if(!root || !dw4_menu_window_data(root)->_isRun){dw4_menu_window_close(root);snprintf(error,cap,"SUBWND factory returned an invalid menu root");return -1;}
        s->prepared=root;ram(s)->_isRun=1;ram(s)->_st0=ram(s)->_st1=ram(s)->_st2=ram(s)->_st3=0;
        manager(s)->_whoGenerate=player;manager(s)->_subWndNo=mode;
        dw4_scriptservices_active(o->sd,s->token,1);
        if(o->factory.activate){
            o->preparing=1;
            int activated=o->factory.activate(o->factory.user,mode,player,error,cap);o->preparing=0;
            if(activated){snprintf(o->error,sizeof(o->error),"%s",error);o->failed=1;return -1;}
        }
        return 0;
    }
unsupported:
    snprintf(error,cap,"unsupported SUBWND command/arguments; shop data requires its gameplay owner");return -1;
}
static uint32_t field(const dw4_igb_record *r,unsigned ord)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].raw;return UINT32_MAX;}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}
dw4_subwindows *dw4_subwindows_open(dw4_scriptservices *sd,uint64_t scope,const dw4_stageobjects *objects)
{
    if(!sd || !objects)return NULL;
    dw4_subwindows *o=calloc(1,sizeof(*o));if(!o)return NULL;o->sd=sd;
    for(size_t i=0;i<dw4_stageobjects_count(objects);i++) {
        const dw4_stageobject *info=dw4_stageobjects_at(objects,i);
        if(strcmp(dw4_stageobject_class(info),"beNDMWStatusInfo"))continue;
        int duplicate=0;for(size_t j=0;j<i;j++)if(dw4_stageobject_same(dw4_stageobjects_at(objects,j),info))duplicate=1;
        if(duplicate)continue;
        dw4_igb_record r={0};const dw4_igb *g=(info)->igb;
        if(!record(g,info->id,&r))goto bad;
        uint32_t id=field(&r,6);dw4_igb_record_free(&r);
        if(!record(g,id,&r))goto bad;
        int valid=!strcmp(r.class_name,"beBaseInfoRamList");uint32_t count=field(&r,2),bytes=0;
        const uint8_t *ids=dw4_igb_block(g,field(&r,4),&bytes);dw4_igb_record_free(&r);
        if(!valid || count>INT32_MAX || (count && (!ids || count>bytes/4)))goto bad;
        for(uint32_t j=0;j<count;j++) {
            memcpy(&id,ids+4*j,4);if(!record(g,id,&r))goto bad;
            valid=!strcmp(r.class_name,"beNDMWStatusInfoRam");uint32_t ram_no=field(&r,2);dw4_igb_record_free(&r);if(!valid)goto bad;
            struct slot *s=calloc(1,sizeof(*s));if(!s)goto bad;
            struct slot **rows=realloc(o->slot,(o->n+1)*sizeof(*rows));if(!rows){free(s);goto bad;}
            o->slot=rows;rows[o->n++]=s;s->owner=o;s->info=info;s->index=(int32_t)j;
            s->arena=info->arena;
            const dw4_metaobject *mc=dw4_metaobject_find("beNDMWStatus"),*rc=dw4_metaobject_find("beNDMWStatusInfoRam");
            if(!s->arena || !mc || !rc)goto bad;
            s->manager=dw4_arena_object_new(s->arena,DW4_REGION_PERSISTENT,mc->vtable);
            s->ram=dw4_arena_object_new(s->arena,DW4_REGION_PERSISTENT,rc->vtable);
            if(!s->manager.off || !s->ram.off)goto bad;
            ram(s)->_ramNo=(int32_t)ram_no;ram(s)->_parentInfo=(int32_t)info->object.off;ram(s)->_parentManager=(int32_t)s->manager.off;
            s->token=dw4_scriptservices_register(sd,scope,"SUBWND",dw4_stageobject_name(info),s->index,0,service,s);if(!s->token)goto bad;
        }
    }
    return o;
bad:dw4_subwindows_close(o);return NULL;
}
void dw4_subwindows_close(dw4_subwindows *o)
{
    if(!o)return;
    for(size_t i=0;i<o->n;i++){struct slot *s=o->slot[i];dw4_scriptservices_unregister(o->sd,s->token);
        dw4_menu_window_close(s->root);dw4_menu_window_close(s->prepared);
        if(s->ram.off)dw4_arena_object_release(s->arena,s->ram);
        if(s->manager.off)dw4_arena_object_release(s->arena,s->manager);
        free(s);}
    free(o->slot);free(o);
}
static int inactive(const dw4_subwindows *o)
{if(o->busy || o->failed || o->preparing)return 0;for(size_t i=0;i<o->n;i++)if(ram(o->slot[i])->_isRun)return 0;return 1;}
int dw4_subwindows_factory(dw4_subwindows *o,const dw4_subwindow_factory *f)
{
    if(!o || !inactive(o) || o->override)return -1;
    o->factory=f?*f:(dw4_subwindow_factory){0};return 0;
}
int dw4_subwindows_override(dw4_subwindows *o,dw4_script_binding f,void *u)
{if(!o || !o->n || !inactive(o))return -1;o->override=f;o->override_user=u;return 0;}
int dw4_subwindows_tick(dw4_subwindows *o)
{
    if(!o || o->override)return 0;
    if(o->busy || o->failed || o->preparing)return -1;
    o->busy=1;
    for(size_t i=0;i<o->n;i++) {
        struct slot *s=o->slot[i];if(!ram(s)->_isRun)continue;
        if(ram(s)->_st0==0) {
            s->root=s->prepared;s->prepared=NULL;manager(s)->_windowPro=(int32_t)s->root->object.off;
            if(o->factory.begin(o->factory.user,manager(s)->_subWndNo,manager(s)->_whoGenerate,o->error,sizeof(o->error)))goto bad;
            ram(s)->_st0=1;ram(s)->_st1=ram(s)->_st2=ram(s)->_st3=0;
        }
        if(dw4_menu_window_tick(s->root,o->error,sizeof(o->error)))goto bad;
        if(!dw4_menu_window_data(s->root)->_isRun) {
            /* Parent active, not a draw/timer estimate, is the completion oracle. */
            dw4_menu_window_close(s->root);s->root=NULL;manager(s)->_windowPro=0;
            if(o->factory.end(o->factory.user,manager(s)->_subWndNo,manager(s)->_whoGenerate,o->error,sizeof(o->error)))goto bad;
            ram(s)->_isRun=0;ram(s)->_st0=2;
            ram(s)->_st1=ram(s)->_st2=ram(s)->_st3=0;dw4_scriptservices_active(o->sd,s->token,0);
        }
    }
    o->busy=0;return 0;
bad:o->busy=0;o->failed=1;return -1;
}
const char *dw4_subwindows_error(const dw4_subwindows *o){return o?o->error:"no SUBWND owner";}
size_t dw4_subwindows_count(const dw4_subwindows *o){return o?o->n:0;}
const dw4_menu_window *dw4_subwindows_root(const dw4_subwindows *o,size_t i){return o && i<o->n?o->slot[i]->root:NULL;}
dw4_subwindow_state dw4_subwindows_at(const dw4_subwindows *o,size_t i){return o && i<o->n?snapshot(o->slot[i]):(dw4_subwindow_state){0};}

int dw4_subwindows_bind_work(dw4_subwindows *o,size_t i,dw4_handle work)
{
    if(!o || i>=o->n)return -1;
    const dw4_metaobject *mo=dw4_metaobject_find("beNDMWStatusInfoWork");
    if(work.off && !dw4_arena_object_is(o->slot[i]->arena,work,mo->vtable))return -1;
    ram(o->slot[i])->_work=(int32_t)work.off;return 0;
}
