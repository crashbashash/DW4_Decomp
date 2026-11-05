#include "../src/menurecord.h"
#include "dw4/statussubmenu.h"
#include "dw4/statusscene.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct fixture {dw4_menu_window *root;int fail,finished,opening,created,released,selector,ready,page;};
static int leaf(dw4_menu_window *w,char *e,size_t n)
{(void)e;(void)n;if(dw4_menu_window_data(w)->_st0>=2)dw4_menu_window_data(w)->_isRun=0;return 0;}
static void release(void *u){((struct fixture *)u)->released++;}
static int io(void *u,dw4_statussubmenu *s,int op,const char *name,const char *key,int32_t v)
{
    struct fixture *f=u;(void)name;(void)key;(void)v;
    if(f->fail==op+1)return -1;
    if(op==DW4_SUBMENU_CREATE || op==DW4_SUBMENU_SKILL_SETUP){
        dw4_menu_window *w=dw4_menu_window_open(leaf,f,release);assert(w);
        assert(!dw4_menu_window_add(f->root,w));f->created++;return 0;
    }
    if(op==DW4_SUBMENU_MODEL)return f->opening;
    if(op==DW4_SUBMENU_FINISHED)return f->finished;
    if(op==DW4_SUBMENU_FIND_SELECTOR)return f->selector;
    if(op==DW4_SUBMENU_SELECTOR_READY)return f->ready;
    if(op==DW4_SUBMENU_SELECTOR_CLOSE){dw4_menu_window_remove(f->root->children[1]);return 0;}
    if(op==DW4_SUBMENU_SKILL_LIST)return 10;
    if(op==DW4_SUBMENU_SKILL_TOP)return 1;
    if(op==DW4_SUBMENU_SKILL_NEXT){if(f->page){s->page=1;f->page=0;return 1;}return 0;}
    return 0;
}
static void tick(struct fixture *f)
{char e[256];int rc=dw4_menu_window_tick(f->root,e,sizeof e);if(rc)fprintf(stderr,"%s\n",e);assert(!rc);}
static void finish_child(struct fixture *f)
{dw4_menu_window_remove(f->root->children[dw4_menu_window_count(f->root)-1]);tick(f);tick(f);}
static void tree(int kind)
{
    struct fixture f={.finished=1};f.root=dw4_statussubmenu_window_open(kind,0,io,&f);assert(f.root);
    dw4_menu_window *s=dw4_statussubmenu_window_is(f.root)?f.root:NULL;assert(s);
    tick(&f);if(kind==DW4_STATUS_EQUIP)tick(&f);
    assert(dw4_menu_window_count(f.root)==(kind==DW4_STATUS_SKILL?1:2));
    dw4_menu_window_data(s)->_retCode=2;finish_child(&f);
    assert(dw4_menu_window_data(f.root)->_st1==(kind==DW4_STATUS_SKILL?3:3));tick(&f);
    if(kind==DW4_STATUS_SKILL){assert(dw4_menu_window_data(f.root)->_st2==2);dw4_menu_window_data(s)->_retCode=-1;finish_child(&f);}
    else finish_child(&f);
    assert(dw4_menu_window_data(f.root)->_st1==0);tick(&f);
    dw4_menu_window_data(s)->_retCode=-1;finish_child(&f);assert(dw4_menu_window_data(f.root)->_st0==2);
    f.finished=0;tick(&f);assert(dw4_menu_window_data(f.root)->_st0==3 && dw4_menu_window_data(f.root)->_isRun);
    for(int i=0;i<10;i++)tick(&f);
    assert(dw4_menu_window_data(f.root)->_isRun);
    f.finished=1;tick(&f);assert(!dw4_menu_window_data(f.root)->_isRun && !dw4_menu_window_count(f.root));
    dw4_menu_window_close(f.root);assert(f.created==f.released);
}
struct scene_fixture {int calls,fail,health,hold;};
static int scene_io(void *u,const dw4_statusscene_command *c,char *e,size_t n)
{
    struct scene_fixture *f=u;(void)e;(void)n;f->calls++;
    if(f->fail==f->calls)return -1;
    if(c->op==DW4_STATUSSCENE_HEALTH){assert(c->hp==10+c->player && c->mp==20+c->player);f->health++;}
    if(c->op==DW4_STATUSSCENE_HOLD)f->hold=atoi(c->value);
    return 0;
}
static void scene(void)
{
    dw4_playerrecords *p=dw4_playerrecords_open();assert(p);char e[256];
    for(int i=0;i<4;i++){
        dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",i);
        const char *keys[]={"ISUSE","BIT","XDATA","HP","MP","MHP","MMP"};
        int32_t values[]={257,10000000,10000,10+i,20+i,100,200};
        for(int j=0;j<7;j++)assert(!dw4_property_set_number(f,keys[j],values[j]));
    }
    for(int k=0;k<128;k++){
        struct scene_fixture f={0};dw4_statusscene s={.players=p,.io=scene_io,.user=&f};
        assert(dw4_statusscene_restore(&s,e,sizeof e)==-1 && !f.calls);
        assert(!dw4_statusscene_freeze(&s,e,sizeof e) && f.hold && s.phase==1);
        assert(!dw4_statusscene_enter(&s,e,sizeof e) && s.phase==2);
        for(int i=0;i<4;i++){
            int32_t v;dw4_property_folder *r=dw4_playerrecords_get(p,"GETPLAYER",i);
            assert(!dw4_property_number(r,"BIT",&v) && v==9999999);
            assert(!dw4_property_number(r,"XDATA",&v) && v==9999);
        }
        assert(!dw4_statusscene_restore(&s,e,sizeof e) && !s.phase && !f.hold && f.health==4);
        assert(dw4_statusscene_restore(&s,e,sizeof e)==-1);
    }
    for(int failure=1;failure<=17;failure++){
        struct scene_fixture f={.fail=failure};dw4_statusscene s={.players=p,.io=scene_io,.user=&f};
        int rc=dw4_statusscene_freeze(&s,e,sizeof e);
        if(!rc)rc=dw4_statusscene_enter(&s,e,sizeof e);
        if(!rc)rc=dw4_statusscene_restore(&s,e,sizeof e);
        assert(rc==-1 && s.failed);int calls=f.calls;
        assert(dw4_statusscene_restore(&s,e,sizeof e)==-1 && calls==f.calls);
    }
    dw4_playerrecords_close(p);
}
int main(void)
{
    for(int i=0;i<128;i++)for(int kind=DW4_STATUS_EQUIP;kind<=DW4_STATUS_SKILL;kind++)tree(kind);
    struct fixture f={.fail=DW4_SUBMENU_CREATE+1};f.root=dw4_statussubmenu_window_open(DW4_STATUS_EQUIP,0,io,&f);
    char e[256];assert(dw4_menu_window_tick(f.root,e,sizeof e)==-1 && dw4_menu_window_data(f.root)->_isRun);dw4_menu_window_close(f.root);
    scene();puts("STATUS submenus/scene: 384 owned trees, 128 four-player restoration cycles and failure holds pass");return 0;
}
