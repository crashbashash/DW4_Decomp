/* beNDMWWindow tree (3f6350/3f6490) on authoritative arena objects.
 * Host wrappers own callbacks and map child handles to their resource owners;
 * scalar state, parent links and child counts/handles belong to the arena. */
#include "dw4/subwindow.h"
#include "dw4/object.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
struct window {dw4_menu_window pub;dw4_menu_window *parent;int busy;};
static struct window *native(dw4_menu_window *w){return (struct window *)w;}
beNDMWWindow *dw4_menu_window_data(const dw4_menu_window *w)
{return w?DW4_ARENA_OBJ(w->arena,beNDMWWindow,w->object):NULL;}
static beNDMWWindowList *list(const dw4_menu_window *w)
{
    const beNDMWWindow *o=dw4_menu_window_data(w);
    return o?DW4_ARENA_OBJ(w->arena,beNDMWWindowList,((dw4_handle){(uint32_t)o->_subWindow})):NULL;
}
size_t dw4_menu_window_count(const dw4_menu_window *w)
{const beNDMWWindowList *l=list(w);return l && l->_count>0?(size_t)l->_count:0;}
static int32_t *handles(const dw4_menu_window *w,beNDMWWindowList *l)
{return l->_capacity>0?dw4_arena_at(w->arena,(dw4_handle){(uint32_t)l->_data},(uint32_t)l->_capacity*4):NULL;}
dw4_menu_window *dw4_menu_window_open_class(const char *name,dw4_menu_update update,void *user,void (*release)(void *))
{
    if(!update || !name)return NULL;
    dw4_arena *a=dw4_session_arena();
    const dw4_metaobject *m=dw4_metaobject_find(name),*base=dw4_metaobject_find("beNDMWWindow"),*lm=dw4_metaobject_find("beNDMWWindowList");
    if(!a || !m || !base || !lm || !dw4_class_is(a,m->vtable,base->vtable))return NULL;
    struct window *w=calloc(1,sizeof(*w));if(!w)return NULL;
    dw4_handle object=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,m->vtable);
    dw4_handle children=object.off?dw4_arena_object_new(a,DW4_REGION_PERSISTENT,lm->vtable):(dw4_handle){0};
    if(!object.off || !children.off){if(object.off)dw4_arena_object_release(a,object);free(w);return NULL;}
    w->pub.arena=a;w->pub.object=object;w->pub.update=update;w->pub.user=user;w->pub.release=release;
    beNDMWWindow *o=dw4_menu_window_data(&w->pub);o->_isRun=1;o->_subWindow=(int32_t)children.off;
    return &w->pub;
}
dw4_menu_window *dw4_menu_window_open(dw4_menu_update update,void *user,void (*release)(void *))
{return dw4_menu_window_open_class("beNDMWWindow",update,user,release);}
int dw4_menu_window_add(dw4_menu_window *p,dw4_menu_window *c)
{
    if(!p || !c || p->arena!=c->arena || native(c)->parent || native(c)->busy)return -1;
    for(dw4_menu_window *a=p;a;a=native(a)->parent)if(a==c)return -1;
    beNDMWWindowList *l=list(p);beNDMWWindow *child=dw4_menu_window_data(c);
    if(!l || !child || l->_count<0 || l->_count>=INT32_MAX || l->_count>l->_capacity)return -1;
    if(l->_count==l->_capacity){
        uint32_t capacity=l->_capacity<4?4u:(uint32_t)l->_capacity*2;
        if(capacity>INT32_MAX/4)return -1;
        dw4_menu_window **rows=calloc(capacity,sizeof(*rows));if(!rows)return -1;
        dw4_handle data=dw4_arena_alloc(p->arena,DW4_REGION_PERSISTENT,capacity*4);
        if(!data.off){free(rows);return -1;}
        int32_t *old=handles(p,l),*next=dw4_arena_at(p->arena,data,capacity*4);
        if(l->_count){memcpy(rows,p->children,(size_t)l->_count*sizeof(*rows));memcpy(next,old,(size_t)l->_count*4);}
        if(l->_data)dw4_arena_free(p->arena,(dw4_handle){(uint32_t)l->_data});
        free(p->children);p->children=rows;l->_data=(int32_t)data.off;l->_capacity=(int32_t)capacity;
    }
    p->children[l->_count]=c;handles(p,l)[l->_count]=(int32_t)c->object.off;l->_count++;
    child->_mother=(int32_t)p->object.off;native(c)->parent=p;return 0;
}
int dw4_menu_window_is_root(const dw4_menu_window *w)
{const beNDMWWindow *o=dw4_menu_window_data(w);return o && !o->_mother;}
void dw4_menu_window_remove(dw4_menu_window *w)
{beNDMWWindow *o=dw4_menu_window_data(w);if(o){o->_st0=2;o->_st1=o->_st2=o->_st3=0;}}
dw4_menu_window *dw4_menu_window_retain(dw4_menu_window *w)
{return w && dw4_arena_object_addref(w->arena,w->object)>0?w:NULL;}
static void detach(dw4_menu_window *w)
{native(w)->parent=NULL;dw4_menu_window_data(w)->_mother=0;}
void dw4_menu_window_close(dw4_menu_window *w)
{
    if(!w)return;
    if(dw4_arena_object_refcount(w->arena,w->object)>1){dw4_arena_object_release(w->arena,w->object);return;}
    size_t count=dw4_menu_window_count(w);
    for(size_t i=0;i<count;i++){detach(w->children[i]);dw4_menu_window_close(w->children[i]);}
    if(w->release)w->release(w->user);
    beNDMWWindowList *l=list(w);dw4_handle children={(uint32_t)dw4_menu_window_data(w)->_subWindow};
    if(l->_data)dw4_arena_free(w->arena,(dw4_handle){(uint32_t)l->_data});
    dw4_arena_object_release(w->arena,children);dw4_arena_object_release(w->arena,w->object);
    free(w->children);free(native(w));
}
int dw4_menu_window_tick(dw4_menu_window *w,char *error,size_t cap)
{
    if(!w || !dw4_menu_window_data(w) || !list(w) || native(w)->busy){snprintf(error,cap,"invalid or reentrant menu window update");return -1;}
    native(w)->busy=1;
    if(dw4_menu_window_data(w)->_isRun && w->update(w,error,cap))goto bad;
    if(!dw4_menu_window_data(w)->_isRun || dw4_menu_window_data(w)->_st0>=2)
        for(size_t i=0;i<dw4_menu_window_count(w);i++)
            if(dw4_menu_window_data(w->children[i])->_st0<2)dw4_menu_window_remove(w->children[i]);
    size_t limit=dw4_menu_window_count(w);
    for(size_t i=0;i<limit;){
        dw4_menu_window *c=w->children[i];
        if(dw4_menu_window_tick(c,error,cap))goto bad;
        if(!dw4_menu_window_data(c)->_isRun){
            detach(c);dw4_menu_window_close(c);
            beNDMWWindowList *l=list(w);int32_t *data=handles(w,l);size_t count=(size_t)l->_count;
            memmove(w->children+i,w->children+i+1,(count-i-1)*sizeof(*w->children));
            memmove(data+i,data+i+1,(count-i-1)*4);w->children[count-1]=NULL;data[count-1]=0;l->_count--;limit--;
        }else i++;
    }
    native(w)->busy=0;return 0;
bad:native(w)->busy=0;return -1;
}
void dw4_subwindow_generate(dw4_subwindow_state *s,int32_t mode,int32_t player)
{
    if(s && !s->active){s->active=1;s->state=s->sub=s->delay=s->latch=0;s->mode=mode;s->player=player;}
}
int dw4_subwindow_remove(dw4_subwindow_state *s,dw4_menu_window *root)
{
    if(!s || !s->active)return 0;
    if(!root)return 1;
    dw4_menu_window_remove(root);return 0;
}
