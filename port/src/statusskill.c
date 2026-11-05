#include "menurecord.h"
#include "shinkarecord.h"
#include "dw4/statusskill.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct skill {
    dw4_statusskill_context c;
    dw4_statussubmenu *state; /* borrowed only during update */
    dw4_menu_window *root,*title,*page;
    int rows,failed;
    dw4_statuspage_input input;
    char error[256];
};
static dw4_script_value str(const char *s)
{return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int sequence(void *u,const char *name,const char *key)
{
    struct skill *s=u;
    dw4_script_value a[]={str("MODELCTRL"),str(name),{DW4_SCRIPT_NUMBER,0,NULL,0},str(key)},r;
    return dw4_scriptservices_call(s->c.view.sd,"sd",a,4,&r,s->error,sizeof s->error);
}
static int emit(struct skill *s,dw4_menu_window *w,int op,const char *group,const char *name,int call)
{
    (void)s;
    dw4_statusview_command c={op,group,name,NULL,NULL,call};
    return dw4_statusview_window_emit(w,&c);
}
static int title_setup(void *u,dw4_statusview_io io,void *user)
{
    (void)u;
    dw4_statusview_command model={DW4_VIEW_MODEL,NULL,"i_sttitle","SQ_OPEN","SQ_CLOSE",0};
    dw4_statusview_command text={DW4_VIEW_TRACK_TEXT,"STWINFONT12","font000",NULL,NULL,0};
    return io(user,&model) || io(user,&text)?-1:0;
}
static int menu_setup(void *u,dw4_statusview_io io,void *user)
{
    (void)u;
    dw4_statusview_command text={DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0};
    return io(user,&text);
}
static int page_setup(void *u,dw4_statusview_io io,void *user)
{
    struct skill *s=u;
    if(s->state->mode==0){
        dw4_statusview_command left={DW4_VIEW_MODEL,NULL,"i_stcursorleft","SQ_HIDE/V<-146,65,0>","SQ_CLOSE",0};
        dw4_statusview_command right={DW4_VIEW_MODEL,NULL,"i_stcursorright",
            s->state->pages<2?"SQ_HIDE/V<127,65,0>":"SQ_SELECT/V<127,65,0>","SQ_CLOSE",0};
        if(io(user,&left) || io(user,&right))return -1;
    }
    return dw4_statuscontent_skill_setup(s->c.view.players,s->c.databases,s->c.view.player,
        s->state->mode,s->state->mode?1:s->state->pages,&s->rows,io,user);
}
static int resource_open(struct skill *s,dw4_menu_window **out,int page)
{
    if(*out)return -1;
    dw4_statusview_context c=s->c.view;c.initialize=page?page_setup:title_setup;c.user=s;
    *out=dw4_statusview_window_open(DW4_STATUS_CONTENT,&c);
    return *out?dw4_menu_window_tick(*out,s->error,sizeof s->error):-1;
}
static int resource_close(struct skill *s,dw4_menu_window *w)
{
    if(!w || dw4_menu_window_data(w)->_st0>=2)return 0;
    dw4_menu_window_remove(w);
    /* Retail closes models and clears text during the parent's callback. */
    return dw4_menu_window_tick(w,s->error,sizeof s->error);
}
static int drain(struct skill *s,dw4_menu_window **w)
{
    if(!*w)return 0;
    if(dw4_menu_window_data((*w))->_st0>=2 && dw4_menu_window_tick(*w,s->error,sizeof s->error))return -1;
    if(!dw4_menu_window_data((*w))->_isRun){dw4_menu_window_close(*w);*w=NULL;}
    return 0;
}
static dw4_menu_window *selector(struct skill *s)
{
    for(size_t i=0;i<dw4_menu_window_count(s->root);i++)if(dw4_menu_window_data(s->root->children[i])->_isRun)return s->root->children[i];
    return NULL;
}
static int add_selector(struct skill *s,int page)
{
    dw4_statusview_context c=s->c.view;c.parent=NULL;c.parent_window=s->root;
    c.callno=page?0:91;c.selected=page?0:s->state->window.selection<0?0:s->state->window.selection;
    c.rows=s->rows;c.position[0]=-121;c.position[1]=128;c.position[2]=0;c.enabled=NULL;
    c.selection_initialize=page?NULL:menu_setup;c.user=s;
    dw4_menu_window *w=dw4_statusview_window_open(page?DW4_STATUS_SELECTE1:DW4_STATUS_SELECT01,&c);
    if(!w)return -1;
    if(dw4_menu_window_add(s->root,w)){dw4_menu_window_close(w);return -1;}return 0;
}
static int leaf(void *u,dw4_statussubmenu *c,int op,const char *name,const char *key,int32_t value)
{
    struct skill *s=u;(void)name;
    switch(op){
    case DW4_SUBMENU_COUNT:return dw4_menu_window_count(s->root)>INT32_MAX?-1:(int)dw4_menu_window_count(s->root);
    case DW4_SUBMENU_CREATE:return key?-1:add_selector(s,0);
    case DW4_SUBMENU_MODEL:
        if(!strcmp(key,"GENERATE/SQ_OPEN"))return resource_open(s,&s->title,0);
        if(!strcmp(key,"SQ_CLOSE"))return resource_close(s,s->title);
        return -1;
    case DW4_SUBMENU_SCRIPT:return emit(s,s->title,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",value);
    case DW4_SUBMENU_SKILL_LIST:{
        beNDMWStatusCtrlSkill *d=DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlSkill,s->root->object);
        return shinka_build(s->root->arena,&d->_shinkaCtrl,s->c.view.players,s->c.databases,s->c.view.player)?-1:shinka_count(s->root->arena,d->_shinkaCtrl);
    }
    case DW4_SUBMENU_SKILL_SETUP:
        if(resource_open(s,&s->page,1))return -1;
        return add_selector(s,1);
    case DW4_SUBMENU_SKILL_REFRESH:return dw4_statuscontent_skill(s->c.view.players,s->c.databases,s->c.view.player,
        c->mode,c->mode?0:c->page,c->mode?1:c->pages,c->window.selection,value,!value,dw4_statusview_window_emit,s->page);
    case DW4_SUBMENU_FIND_SELECTOR:return selector(s)!=NULL;
    case DW4_SUBMENU_SKILL_TOP:return dw4_statusview_selector_ready(selector(s));
    case DW4_SUBMENU_SKILL_PREVIOUS:case DW4_SUBMENU_SKILL_NEXT:
        return dw4_statuspage_turn(&c->page,c->pages,op==DW4_SUBMENU_SKILL_NEXT,&s->input,sequence,s);
    case DW4_SUBMENU_SKILL_REPAGE:{
        beNDMWStatusCtrlSkill *d=DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlSkill,s->root->object);
        int count=shinka_count(s->root->arena,d->_shinkaCtrl);
        int n=c->page==1?count-8:8;
        if(n<1 || n>8)return -1;
        c->offset=c->page*8;return dw4_statusview_selector_repage(selector(s),n);
    }
    case DW4_SUBMENU_SKILL_CLEAR_COLORS:return dw4_statuscontent_skill_clear_colors(dw4_statusview_window_emit,s->page);
    case DW4_SUBMENU_CLOSE_MODELS:return resource_close(s,s->page);
    case DW4_SUBMENU_RESET_RESOURCES:case DW4_SUBMENU_CLEAR_TEXT:case DW4_SUBMENU_CLEAR_MESSAGE:return 0;
    case DW4_SUBMENU_CLOSE_CHILDREN:
        for(size_t i=0;i<dw4_menu_window_count(s->root);i++)if(dw4_menu_window_data(s->root->children[i])->_st0<2)dw4_menu_window_remove(s->root->children[i]);
        return 0;
    case DW4_SUBMENU_FINISHED:return !s->page && !s->title && !dw4_menu_window_count(s->root);
    default:return -1;
    }
}
static int io(void *u,dw4_statussubmenu *c,int op,const char *name,const char *key,int32_t value)
{
    struct skill *s=u;int rc=leaf(u,c,op,name,key,value);
    if(rc<0 && !s->error[0])snprintf(s->error,sizeof s->error,"operation %d failed at %d/%d/%d, mode %d",op,c->window.state,c->window.sub,c->window.delay,c->mode);
    return rc;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct skill *s=w->user;dw4_statussubmenu projection=menu_submenu_read(w,DW4_STATUS_SKILL);s->state=&projection;int rc=0;
    if(s->failed){snprintf(error,cap,"STATUS skill failed; scene reset required");s->state=NULL;return -1;}
    if(drain(s,&s->page) || drain(s,&s->title))rc=-1;
    /* A retiring sidecar must release shared resources before a new page/menu
     * reopens them. This is an ownership gate, not an elapsed-time guess. */
    if(!rc && s->page && dw4_menu_window_data(s->page)->_st0>=2 && dw4_menu_window_data(w)->_st0<2){menu_submenu_write(w,DW4_STATUS_SKILL,&projection);s->state=NULL;return 0;}
    if(!rc){
        memset(&s->input,0,sizeof s->input);
        if(s->c.input(s->c.user,s->c.view.player,&s->input))rc=-1;
        else rc=dw4_statussubmenu_tick(s->state,DW4_STATUS_SKILL,io,s);
    }
    if(rc){s->failed=1;snprintf(error,cap,"STATUS skill: %.200s",s->error[0]?s->error:"required view/input service failed");}
    menu_submenu_write(w,DW4_STATUS_SKILL,&projection);s->state=NULL;return rc;
}
static void release(void *u)
{struct skill *s=u;dw4_menu_window_close(s->page);dw4_menu_window_close(s->title);shinka_drop(s->root->arena,&DW4_ARENA_OBJ(s->root->arena,beNDMWStatusCtrlSkill,s->root->object)->_shinkaCtrl);free(s);}
dw4_menu_window *dw4_statusskill_window_open(const dw4_statusskill_context *c)
{
    if(!c || !c->view.sd || !c->view.engine || !c->view.players || !c->databases || !c->input || c->view.player<0 || c->view.player>3)return NULL;
    struct skill *s=calloc(1,sizeof(*s));if(!s)return NULL;
    s->c=*c;
    s->root=dw4_menu_window_open_class("beNDMWStatusCtrlSkill",update,s,release);if(!s->root){free(s);return NULL;}
    dw4_statussubmenu initial={.window={.active=1,.selection=-1}};
    menu_submenu_write(s->root,DW4_STATUS_SKILL,&initial);dw4_menu_window_data(s->root)->_playerNo=c->view.player;return s->root;
}
int dw4_statusskill_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statussubmenu dw4_statusskill_window_state(const dw4_menu_window *w)
{return dw4_statusskill_window_is(w)?menu_submenu_read(w,DW4_STATUS_SKILL):(dw4_statussubmenu){0};}
