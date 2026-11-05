#include "menurecord.h"
/* Retail 40ee60/4196c0/41f190 scalar flow, with required owned view leaves.
 * Provenance and controlled-oracle boundaries: docs/status-submenus.md. */
#include "dw4/statussubmenu.h"
#include <stdlib.h>
#include <stdio.h>
static void state(dw4_statusctrl *s,int n){s->state=n;s->sub=s->delay=s->latch=0;}
static void sub(dw4_statusctrl *s,int n){s->sub=n;s->delay=s->latch=0;}
static void delay(dw4_statusctrl *s,int n){s->delay=n;s->latch=0;}
#define CALL(op,name,key,v) io(u,c,op,name,key,v)
#define DO(op,name,key,v) do {if(CALL(op,name,key,v)<0)return -1;} while(0)
static int count(dw4_statussubmenu *c,dw4_submenu_io io,void *u)
{int q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;c->window.previous_count=q;return 0;}
static int close_tick(dw4_statussubmenu *c,dw4_submenu_io io,void *u,int skill)
{
    dw4_statusctrl *s=&c->window;
    if(s->state==2){
        DO(DW4_SUBMENU_CLOSE_MODELS,NULL,NULL,0);DO(DW4_SUBMENU_CLEAR_TEXT,NULL,NULL,0);
        DO(DW4_SUBMENU_CLOSE_CHILDREN,NULL,NULL,0);state(s,3);
        if(skill){DO(DW4_SUBMENU_MODEL,"i_sttitle","SQ_CLOSE",0);DO(DW4_SUBMENU_CLEAR_MESSAGE,"STWINFONT12","font000",0);}
    }else if(s->state==3){int q=CALL(DW4_SUBMENU_FINISHED,NULL,NULL,0);if(q<0)return -1;if(q)s->active=0;}
    return 0;
}
static int menu(dw4_statussubmenu *c,dw4_submenu_io io,void *u,int folder)
{
    dw4_statusctrl *s=&c->window;int q;
    if(s->delay!=2){
        if(s->delay==0){
            if(!folder){q=CALL(DW4_SUBMENU_MODEL,c->mode==1?"i_messwn":"i_sttitle",c->mode==1?"ISSEQNAME/SQ_STOPEN":"ISSEQNAME/SQ_OPEN",0);
                if(q<0)return -1;
                if((uint8_t)q==1)return 0;}
            DO(DW4_SUBMENU_CREATE,NULL,NULL,folder?61:31); /* MENU */
            if(count(c,io,u))return -1;
            delay(s,1);
        }else if(s->delay!=1)return 0;
        if(s->selection!=-1)DO(DW4_SUBMENU_SCRIPT,"txt_status.lua",NULL,s->selection+(folder?81:35));
        delay(s,s->delay+1);s->latch=s->selection;
    }
    q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;
    if(q==s->previous_count){if(s->selection!=-1 && s->latch!=s->selection)delay(s,1);}
    else{
        if(s->selection!=-1)s->last_selection=s->selection;
        if(s->selection>=0 && s->selection<=(folder?3:2))sub(s,s->selection+1);
        else state(s,s->state+1);
    }
    return 0;
}
static int folder_device(dw4_statussubmenu *c,dw4_submenu_io io,void *u)
{
    dw4_statusctrl *s=&c->window;int q;
    if(s->delay==0){
        DO(DW4_SUBMENU_CREATE,NULL,"DEVICE",0);if(count(c,io,u))return -1;
        delay(s,1);
    }
    if(s->delay==1){
        if(!s->latch){DO(DW4_SUBMENU_SCRIPT,"txt_status.lua",NULL,43);s->latch=1;}
        q=CALL(DW4_SUBMENU_FIND_SELECTOR,NULL,NULL,0);if(q<0)return -1;
        if(q){
            if(s->selection==-1){
                DO(DW4_SUBMENU_CLEAR_MESSAGE,"STWINFONT29","font100",0);
                DO(DW4_SUBMENU_SELECTOR_CLOSE,NULL,NULL,0);delay(s,3);
            }else{
                q=CALL(DW4_SUBMENU_SELECTOR_READY,NULL,NULL,0);if(q<0)return -1;
                if(q){DO(DW4_SUBMENU_CLEAR_MESSAGE,"STWINFONT29","font100",0);
                    DO(DW4_SUBMENU_CREATE,NULL,"DEVICE_DETAIL",s->selection);
                    if(count(c,io,u))return -1;
                    delay(s,2);}
            }
        }
    }else if(s->delay==2){
        q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;
        if(q!=s->previous_count){
            s->previous_count=q;s->selection=0;DO(DW4_SUBMENU_CLOSE_MODELS,NULL,NULL,0);
            DO(DW4_SUBMENU_RESET_RESOURCES,NULL,NULL,0);DO(DW4_SUBMENU_CLEAR_TEXT,NULL,NULL,0);
            q=CALL(DW4_SUBMENU_FIND_SELECTOR,NULL,NULL,0);if(q<0)return -1;
            if(q){DO(DW4_SUBMENU_SELECTOR_RESTART,NULL,NULL,0);delay(s,1);}else delay(s,4);
        }
    }else if(s->delay==3){
        q=CALL(DW4_SUBMENU_FIND_SELECTOR,NULL,NULL,0);if(q<0)return -1;
        if(!q){s->selection=s->last_selection;sub(s,0);}
    }else if(s->delay==4){
        q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;if(q!=s->previous_count)delay(s,0);
    }
    return 0;
}
static int skill(dw4_statussubmenu *c,dw4_submenu_io io,void *u)
{
    dw4_statusctrl *s=&c->window;int q;
    if(s->state>=2)return close_tick(c,io,u,1);
    if(s->state==0){DO(DW4_SUBMENU_MODEL,"i_sttitle","GENERATE/SQ_OPEN",0);
        DO(DW4_SUBMENU_SCRIPT,"txt_status.lua",NULL,90);c->mode=0;state(s,s->state+1);}
    if(s->state!=1)return 0;
    if(s->sub==3){
        if(s->delay!=2){
            if(s->delay==0){
                DO(DW4_SUBMENU_SKILL_SETUP,NULL,NULL,c->mode);if(count(c,io,u))return -1;
                delay(s,1);s->selection=0;
            }else if(s->delay!=1)return 0;
            if(s->selection!=-1)DO(DW4_SUBMENU_SKILL_REFRESH,NULL,NULL,0);
            delay(s,s->delay+1);s->latch=s->selection;
        }
        q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;
        if(q==s->previous_count){
            if(s->selection!=-1){
                if(s->latch!=s->selection)delay(s,1);
                else if(c->mode==0){
                    q=CALL(DW4_SUBMENU_FIND_SELECTOR,NULL,NULL,0);if(q<0)return -1;
                    if(q){q=CALL(DW4_SUBMENU_SKILL_TOP,NULL,NULL,0);if(q<0)return -1;
                        if(q){q=CALL(DW4_SUBMENU_SKILL_PREVIOUS,NULL,NULL,0);if(q<0)return -1;
                            if(!q){q=CALL(DW4_SUBMENU_SKILL_NEXT,NULL,NULL,0);if(q<0)return -1;}
                            if(q){DO(DW4_SUBMENU_SKILL_REPAGE,NULL,NULL,0);delay(s,1);s->selection=0;
                                DO(DW4_SUBMENU_SKILL_REFRESH,NULL,NULL,1);}
                        }
                    }
                }
            }
        }else{
            if(c->mode==1)DO(DW4_SUBMENU_SKILL_CLEAR_COLORS,NULL,NULL,9);
            DO(DW4_SUBMENU_CLOSE_MODELS,NULL,NULL,0);DO(DW4_SUBMENU_RESET_RESOURCES,NULL,NULL,0);
            DO(DW4_SUBMENU_CLEAR_TEXT,NULL,NULL,0);s->selection=c->mode;sub(s,0);
        }
    }else if(s->sub>=0 && s->sub<=2){
        if(s->sub==0){DO(DW4_SUBMENU_CREATE,NULL,NULL,91);if(count(c,io,u))return -1;sub(s,1);}
        if(s->sub==1){
            if(s->selection!=-1)DO(DW4_SUBMENU_SCRIPT,"txt_status.lua",NULL,s->selection+98);
            sub(s,2);s->latch=s->selection;
        }
        q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;
        if(q==s->previous_count){if(s->selection!=-1 && s->latch!=s->selection)sub(s,1);}
        else if(s->selection>=0 && s->selection<=2){
            if(!s->selection){q=CALL(DW4_SUBMENU_SKILL_LIST,NULL,NULL,0);if(q<0)return -1;
                c->pages=q<9?1:2;c->page=c->offset=0;}
            c->mode=s->selection;sub(s,3);
        }else state(s,s->state+1);
    }
    return 0;
}
int dw4_statussubmenu_tick(dw4_statussubmenu *c,int kind,dw4_submenu_io io,void *u)
{
    if(!c || !io || kind<DW4_STATUS_EQUIP || kind>DW4_STATUS_SKILL)return -1;
    if(kind==DW4_STATUS_SKILL)return skill(c,io,u);
    dw4_statusctrl *s=&c->window;int folder=kind==DW4_STATUS_FOLDER,q;
    if(s->state>=2)return close_tick(c,io,u,0);
    if(s->state==0){
        /* 40ee60: entry code (+2c) 1 creates StatusTitle02 (3b3900, the i_messwn SQ_STOPEN band) with call 0 instead of
         * the Title04 header (3b3530, call 30); the Digi-Lab binds the equipment check with entry code 1 (431e5c). */
        DO(DW4_SUBMENU_CREATE,NULL,folder?"FOLDER_TITLE":c->mode==1?"BAND":"EQUIP_TITLE",folder?60:c->mode==1?0:30);
        s->last_selection=0;state(s,s->state+1);if(!folder)return 0;
    }
    if(s->state!=1)return 0;
    if(!s->sub)return menu(c,io,u,folder);
    if(folder && s->sub==1)return folder_device(c,io,u);
    if(s->sub>=1 && s->sub<=(folder?4:3)){
        if(s->delay!=1){
            if(s->delay!=0)return 0;
            static const char *const equip[]={"POWER","MAIN","SUB"},*const folders[]={"FLAG","DISK","BANK"};
            DO(DW4_SUBMENU_CREATE,NULL,folder?folders[s->sub-2]:equip[s->sub-1],!folder && s->sub==1?3:0);
            if(count(c,io,u))return -1;
            delay(s,1);
        }
        q=CALL(DW4_SUBMENU_COUNT,NULL,NULL,0);if(q<0)return -1;
        if(q!=s->previous_count){s->selection=s->last_selection;sub(s,0);}
    }
    return 0;
}
struct owner {int kind;dw4_menu_window *w;dw4_submenu_io io;void *user;};
static int owned_io(void *u,dw4_statussubmenu *s,int op,const char *name,const char *key,int32_t v)
{
    struct owner *o=u;
    if(op==DW4_SUBMENU_COUNT)return dw4_menu_window_count(o->w)>INT32_MAX?-1:(int)dw4_menu_window_count(o->w);
    if(op==DW4_SUBMENU_CLOSE_CHILDREN){for(size_t i=0;i<dw4_menu_window_count(o->w);i++)if(dw4_menu_window_data(o->w->children[i])->_st0<2)dw4_menu_window_remove(o->w->children[i]);return 0;}
    size_t before=dw4_menu_window_count(o->w);int q=o->io(o->user,s,op,name,key,v);
    if(q>=0 && (op==DW4_SUBMENU_CREATE || op==DW4_SUBMENU_SKILL_SETUP) && dw4_menu_window_count(o->w)<=before)return -1;
    return op==DW4_SUBMENU_FINISHED && q>0 && dw4_menu_window_count(o->w)?0:q;
}
static int update(dw4_menu_window *w,char *e,size_t n)
{
    struct owner *o=w->user;dw4_statussubmenu projection=menu_submenu_read(w,o->kind);dw4_statusctrl *s=&projection.window;

    int rc=dw4_statussubmenu_tick(&projection,o->kind,owned_io,o);

    if(rc)snprintf(e,n,"STATUS submenu %d failed at %d/%d/%d",o->kind,s->state,s->sub,s->delay);
    menu_submenu_write(w,o->kind,&projection);return rc;
}
dw4_menu_window *dw4_statussubmenu_window_open(int kind,int mode,dw4_submenu_io io,void *u)
{
    if(!io || kind<DW4_STATUS_EQUIP || kind>DW4_STATUS_SKILL)return NULL;
    struct owner *o=calloc(1,sizeof(*o));if(!o)return NULL;
    o->kind=kind;o->io=io;o->user=u;
    o->w=dw4_menu_window_open_class(kind==DW4_STATUS_EQUIP?"beNDMWStatusCtrlEquip":kind==DW4_STATUS_FOLDER?"beNDMWStatusCtrlFolder":"beNDMWStatusCtrlSkill",update,o,free);if(!o->w){free(o);return NULL;}
    dw4_statussubmenu initial={.mode=mode,.window={.active=1,.selection=-1}};
    menu_submenu_write(o->w,o->kind,&initial);return o->w;
}
int dw4_statussubmenu_window_is(const dw4_menu_window *w)
{return w && w->update==update;}
dw4_statussubmenu dw4_statussubmenu_window_state(const dw4_menu_window *w)
{return dw4_statussubmenu_window_is(w)?menu_submenu_read(w,((const struct owner *)w->user)->kind):(dw4_statussubmenu){0};}
