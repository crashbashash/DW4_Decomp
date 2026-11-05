/* Arena identity, publication, pruning, failure and teardown of menu owners. */
#include "../src/menurecord.h"
#include "dw4/subwindow.h"
#include "dw4/object.h"
#include <assert.h>
#include <stdio.h>

struct fixture;
struct node {struct fixture *f;int id;};
struct fixture {dw4_menu_window *root;struct node node[4];int events[16],n,closed[4],append;};
static void release(void *u){struct node *n=u;n->f->closed[n->id]++;}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    (void)error;(void)cap;struct node *n=w->user;struct fixture *f=n->f;
    f->events[f->n++]=n->id;
    if(n->id==1 && f->append){
        f->append=0;dw4_menu_window *next=dw4_menu_window_open(update,f->node+3,release);assert(next);
        assert(!dw4_menu_window_add(f->root,next));dw4_menu_window_data(w)->_isRun=0;
    }
    return 0;
}
static void tree(void)
{
    dw4_arena *a=dw4_session_arena();assert(a);uint32_t baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    struct fixture f={.append=1};for(int i=0;i<4;i++)f.node[i]=(struct node){&f,i};
    f.root=dw4_menu_window_open_class("beNDMWStatusCtrl00",update,f.node,release);assert(f.root);
    assert(dw4_arena_object_is(a,f.root->object,dw4_metaobject_find("beNDMWStatusCtrl00")->vtable));
    beNDMWWindow *root=dw4_menu_window_data(f.root);assert(root && root->_isRun==1 && !root->_mother && !root->_st0);
    beNDMWWindowList *list=DW4_ARENA_OBJ(a,beNDMWWindowList,((dw4_handle){(uint32_t)root->_subWindow}));
    assert(list && !list->_count && !list->_data);
    dw4_handle dead={0};
    for(int i=1;i<3;i++){
        dw4_menu_window *w=dw4_menu_window_open(update,f.node+i,release);assert(w);
        if(i==1)dead=w->object;
        assert(!dw4_menu_window_add(f.root,w));
        assert(dw4_menu_window_data(w)->_mother==(int32_t)f.root->object.off);
        assert(dw4_menu_window_add(f.root,w)==-1 && dw4_menu_window_add(w,f.root)==-1);
    }
    int32_t *data=dw4_arena_at(a,(dw4_handle){(uint32_t)list->_data},(uint32_t)list->_capacity*4);
    assert(list->_count==2 && data[0]==(int32_t)f.root->children[0]->object.off && data[1]==(int32_t)f.root->children[1]->object.off);
    char error[128];assert(!dw4_menu_window_tick(f.root,error,sizeof error));
    assert(f.n==3 && f.events[0]==0 && f.events[1]==1 && f.events[2]==2 && f.closed[1]==1);
    assert(!dw4_arena_at(a,dead,1) && list->_count==2 && !data[2] && !f.root->children[2]);
    for(int i=0;i<2;i++)assert(data[i]==(int32_t)f.root->children[i]->object.off);
    f.n=0;assert(!dw4_menu_window_tick(f.root,error,sizeof error));assert(f.n==3 && f.events[1]==2 && f.events[2]==3);
    dw4_menu_window_remove(f.root);assert(root->_st0==2 && !root->_st1 && !root->_st2 && !root->_st3);
    dw4_menu_window_close(f.root);for(int i=0;i<4;i++)assert(f.closed[i]==1);
    assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
}
static int noop(dw4_menu_window *w,char *error,size_t cap){(void)w;(void)error;(void)cap;return 0;}
static void failures(void)
{
    dw4_arena *a=dw4_session_arena();uint32_t baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    assert(!dw4_menu_window_open_class("igObject",noop,NULL,NULL));
    assert(!dw4_menu_window_open_class("missing",noop,NULL,NULL));
    dw4_menu_window *parent=dw4_menu_window_open(noop,NULL,NULL),*child=dw4_menu_window_open(noop,NULL,NULL);
    assert(parent && child);
    for(int i=0;i<4;i++){
        dw4_menu_window *w=dw4_menu_window_open(noop,NULL,NULL);assert(w && !dw4_menu_window_add(parent,w));
    }
    size_t remaining=DW4_ARENA_RETAIL_BYTES-DW4_ARENA_BASE-dw4_arena_used(a,DW4_REGION_PERSISTENT);
    assert(remaining>1024);
    dw4_handle fill=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,(uint32_t)remaining-1024);assert(fill.off);
    dw4_menu_window *windows[64];size_t n=0;
    for(;n<64;n++){
        uint32_t before=dw4_arena_live(a,DW4_REGION_PERSISTENT);
        windows[n]=dw4_menu_window_open(noop,NULL,NULL);
        if(!windows[n]){assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==before);break;}
    }
    assert(n<64 && dw4_arena_status_last(a)==DW4_ARENA_EXHAUSTED);
    /* Exhaust the next handle-array size too: even a reusable list-object block
     * must not let this test depend on allocator history. */
    dw4_handle blocks[64];size_t nb=0;
    for(;nb<64;nb++){blocks[nb]=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,32);if(!blocks[nb].off)break;}
    assert(nb<64);
    beNDMWWindowList *list=DW4_ARENA_OBJ(a,beNDMWWindowList,((dw4_handle){(uint32_t)dw4_menu_window_data(parent)->_subWindow}));
    int32_t data=list->_data,capacity=list->_capacity;dw4_menu_window **owners=parent->children;
    assert(dw4_menu_window_add(parent,child)==-1);
    assert(list->_count==4 && list->_data==data && list->_capacity==capacity && parent->children==owners);
    assert(dw4_menu_window_is_root(child));
    for(size_t i=0;i<n;i++)dw4_menu_window_close(windows[i]);
    for(size_t i=0;i<nb;i++)assert(!dw4_arena_free(a,blocks[i]));
    dw4_menu_window_close(parent);dw4_menu_window_close(child);
    assert(!dw4_arena_free(a,fill) && dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
}
static int submenu_finish(void *u,dw4_statussubmenu *s,int op,const char *name,const char *key,int32_t value)
{(void)u;(void)s;(void)name;(void)key;(void)value;return op==DW4_SUBMENU_FINISHED;}
static int equipment_finish(void *u,dw4_statusequip *s,int op,int32_t value)
{(void)u;(void)s;(void)value;return op==DW4_EQUIP_FINISHED;}
static void records(void)
{
    dw4_arena *a=dw4_session_arena();uint32_t baseline=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    char error[128];
    for(int i=0;i<128;i++){
        dw4_menu_window *w=dw4_statussubmenu_window_open(DW4_STATUS_SKILL,0,submenu_finish,NULL);assert(w);
        beNDMWStatusCtrlSkill *skill=DW4_ARENA_OBJ(a,beNDMWStatusCtrlSkill,w->object);assert(skill);
        assert(dw4_arena_object_is(a,w->object,dw4_metaobject_find("beNDMWStatusCtrlSkill")->vtable));
        dw4_statussubmenu before=dw4_statussubmenu_window_state(w);
        skill->_nowPage=1;skill->_maxPage=2;skill->_cursor=8;skill->_skillMenu=2;skill->_st0=3;
        assert(!dw4_menu_window_tick(w,error,sizeof error) && !skill->_isRun);
        dw4_statussubmenu after=dw4_statussubmenu_window_state(w);
        assert(!before.page && !before.offset && after.page==1 && after.pages==2 && after.offset==8 && after.mode==2);
        dw4_menu_window_close(w);
        w=dw4_statusequip_window_open(1,3,equipment_finish,NULL);assert(w);
        beNDMWStatusCtrlBaseEquip *equip=DW4_ARENA_OBJ(a,beNDMWStatusCtrlBaseEquip,w->object);assert(equip);
        equip->_kindListPos=2;equip->_pocketPos=4;equip->_st0=3;
        assert(!dw4_menu_window_tick(w,error,sizeof error));
        dw4_statusequip selected=dw4_statusequip_window_state(w);
        assert(selected.slot==2 && selected.pocket==4 && selected.slots==3 && selected.mode==1 && !selected.window.active);
        dw4_menu_window_close(w);assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
    }
    dw4_menu_window *w=dw4_menu_window_open_class("beNDMWStatusCtrlBit",noop,NULL,NULL);assert(w);
    beNDMWStatusCtrlBit *bit=DW4_ARENA_OBJ(a,beNDMWStatusCtrlBit,w->object);
    int32_t players[]={3,1,2};assert(!menu_int_set(w,&bit->_playerNoList,players,3));
    int32_t old=bit->_playerNoList;assert(menu_int_count(w,old)==3 && !memcmp(players,menu_int_data(w,old),sizeof players));
    uint32_t live=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    /* No list may replace a published field on invalid input or exhaustion. */
    assert(menu_int_set(w,&bit->_playerNoList,NULL,3)==-1 && bit->_playerNoList==old);
    assert(menu_list_set(w,&bit->_playerNoList,"igIntList",4,players,INT32_MAX/4)==-1);
    assert(bit->_playerNoList==old && dw4_arena_live(a,DW4_REGION_PERSISTENT)==live);
    menu_int_release(w,&bit->_playerNoList);assert(!bit->_playerNoList);
    dw4_menu_window_close(w);assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==baseline);
}
static void retained_window(void)
{
    dw4_arena *a=dw4_session_arena();uint32_t base=dw4_arena_live(a,DW4_REGION_PERSISTENT);
    struct fixture f={0};f.node[1]=(struct node){&f,1};
    f.root=dw4_menu_window_open(noop,NULL,NULL);dw4_menu_window *child=dw4_menu_window_open(update,f.node+1,release);
    assert(f.root && child && !dw4_menu_window_add(f.root,child));dw4_handle h=child->object;
    assert(dw4_menu_window_retain(child)==child && dw4_arena_object_refcount(a,h)==2);
    dw4_menu_window_data(child)->_isRun=0;char error[128];assert(!dw4_menu_window_tick(f.root,error,sizeof error));
    assert(!dw4_menu_window_count(f.root) && !f.closed[1] && dw4_menu_window_is_root(child));
    assert(dw4_arena_object_refcount(a,h)==1);dw4_menu_window_close(f.root);
    assert(dw4_menu_window_data(child) && !dw4_menu_window_data(child)->_isRun);
    dw4_menu_window_close(child);assert(f.closed[1]==1 && !dw4_arena_at(a,h,1));
    assert(dw4_arena_live(a,DW4_REGION_PERSISTENT)==base);
}
int main(void)
{
    tree();records();retained_window();failures();dw4_session_arena_close();
    puts("menu arena: typed classes, four-byte parent/child handles, bounded append/prune, cleared tails, allocation failure, authoritative submenu/equipment records, snapshot isolation, scalar-list failure and complete teardown pass");
    return 0;
}
