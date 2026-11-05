/* Temporary rule projections of authoritative menu records. References and
 * persistent scalar state stay in the arena; these values live only for a call. */
#ifndef DW4_MENURECORD_H
#define DW4_MENURECORD_H
#include "dw4/object.h"
#include <string.h>
#include "dw4/statussubmenu.h"
#include "dw4/statusequip.h"
#include "dw4/statusdevice.h"
#include "dw4/statusdetailctrl.h"
#include "dw4/statusdiskctrl.h"
#include "dw4/statusbitctrl.h"
static inline dw4_statusctrl menu_base_read(const dw4_menu_window *w)
{
    const beNDMWWindowCtrl *d=DW4_ARENA_OBJ(w->arena,beNDMWWindowCtrl,w->object);
    return (dw4_statusctrl){d->_isRun,d->_st0,d->_st1,d->_st2,d->_st3,d->_retCode,d->_nowProcKazu,0};
}
static inline void menu_base_write(dw4_menu_window *w,const dw4_statusctrl *s)
{
    beNDMWWindowCtrl *d=DW4_ARENA_OBJ(w->arena,beNDMWWindowCtrl,w->object);
    d->_isRun=(unsigned char)s->active;d->_st0=s->state;d->_st1=s->sub;d->_st2=s->delay;d->_st3=s->latch;d->_retCode=s->selection;d->_nowProcKazu=s->previous_count;
}
static inline dw4_statussubmenu menu_submenu_read(const dw4_menu_window *w,int kind)
{
    dw4_statussubmenu s={.window=menu_base_read(w)};
    if(kind==DW4_STATUS_SKILL){const beNDMWStatusCtrlSkill *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlSkill,w->object);s.mode=d->_skillMenu;s.page=d->_nowPage;s.pages=d->_maxPage;s.offset=d->_cursor;}
    else if(kind==DW4_STATUS_EQUIP){const beNDMWStatusCtrlEquip *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlEquip,w->object);s.mode=d->_entCode;s.window.last_selection=d->_equipMenu;}
    else{const beNDMWStatusCtrlFolder *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlFolder,w->object);s.mode=d->_entCode;s.window.last_selection=d->_folderMenu;}
    return s;
}
static inline void menu_submenu_write(dw4_menu_window *w,int kind,const dw4_statussubmenu *s)
{
    menu_base_write(w,&s->window);
    if(kind==DW4_STATUS_SKILL){beNDMWStatusCtrlSkill *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlSkill,w->object);d->_skillMenu=s->mode;d->_nowPage=s->page;d->_maxPage=s->pages;d->_cursor=s->offset;}
    else if(kind==DW4_STATUS_EQUIP){beNDMWStatusCtrlEquip *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlEquip,w->object);d->_entCode=s->mode;d->_equipMenu=s->window.last_selection;}
    else{beNDMWStatusCtrlFolder *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlFolder,w->object);d->_entCode=s->mode;d->_folderMenu=s->window.last_selection;}
}
static inline dw4_statusequip menu_equip_read(const dw4_menu_window *w)
{
    const beNDMWStatusCtrlBaseEquip *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlBaseEquip,w->object);
    return (dw4_statusequip){menu_base_read(w),d->_kindListPos,d->_kindListMax,d->_pocketPos,d->_entCode};
}
static inline void menu_equip_write(dw4_menu_window *w,const dw4_statusequip *s)
{
    beNDMWStatusCtrlBaseEquip *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlBaseEquip,w->object);
    menu_base_write(w,&s->window);d->_kindListPos=s->slot;d->_kindListMax=s->slots;d->_pocketPos=s->pocket;d->_entCode=s->mode;
}
static inline dw4_statusdevice menu_device_read(const dw4_menu_window *w)
{
    const beNDMWStatusCtrlD0 *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlD0,w->object);
    return (dw4_statusdevice){menu_base_read(w),d->_nowPage,d->_maxPage,d->_cursor,d->_isAutoClose};
}
static inline void menu_device_write(dw4_menu_window *w,const dw4_statusdevice *s)
{
    beNDMWStatusCtrlD0 *d=DW4_ARENA_OBJ(w->arena,beNDMWStatusCtrlD0,w->object);
    menu_base_write(w,&s->window);d->_nowPage=s->page;d->_maxPage=s->pages;d->_cursor=s->row;d->_isAutoClose=(unsigned char)s->auto_close;
}
/* Scalar list fields are real igIntList/igBoolList objects with their recovered
 * element widths.
 * Each controller owns its list, including its data block. Replace only after
 * complete allocation so failure leaves the previous field intact. */
static inline int menu_int_count(const dw4_menu_window *w,int32_t field)
{
    const igIntList *l=field?DW4_ARENA_OBJ(w->arena,igIntList,((dw4_handle){(uint32_t)field})):NULL;
    return l?l->_count:0;
}
static inline int32_t *menu_int_data(const dw4_menu_window *w,int32_t field)
{
    igIntList *l=field?DW4_ARENA_OBJ(w->arena,igIntList,((dw4_handle){(uint32_t)field})):NULL;
    return l && l->_count?dw4_arena_at(w->arena,(dw4_handle){(uint32_t)l->_data},(uint32_t)l->_count*4):NULL;
}
static inline void menu_int_release(dw4_menu_window *w,int32_t *field)
{
    if(!*field)return;
    dw4_handle h={(uint32_t)*field};igIntList *l=DW4_ARENA_OBJ(w->arena,igIntList,h);
    if(l->_data)dw4_arena_free(w->arena,(dw4_handle){(uint32_t)l->_data});
    dw4_arena_object_release(w->arena,h);*field=0;
}
static inline int menu_list_set(dw4_menu_window *w,int32_t *field,const char *class_name,uint32_t width,const void *v,int n)
{
    const dw4_metaobject *mo=dw4_metaobject_find(class_name);
    if(!mo || !width || n<0 || (uint32_t)n>INT32_MAX/width || (n && !v))return -1;
    dw4_handle h=dw4_arena_object_new(w->arena,DW4_REGION_PERSISTENT,mo->vtable),data={0};
    if(!h.off)return -1;
    if(n){data=dw4_arena_alloc(w->arena,DW4_REGION_PERSISTENT,(uint32_t)n*width);
        if(!data.off){dw4_arena_object_release(w->arena,h);return -1;}
        memcpy(dw4_arena_at(w->arena,data,(uint32_t)n*width),v,(size_t)n*width);}
    igIntList *l=DW4_ARENA_OBJ(w->arena,igIntList,h);l->_count=l->_capacity=n;l->_data=(int32_t)data.off;
    menu_int_release(w,field);*field=(int32_t)h.off;return 0;
}
static inline int menu_int_set(dw4_menu_window *w,int32_t *field,const int32_t *v,int n)
{return menu_list_set(w,field,"igIntList",4,v,n);}
static inline uint8_t *menu_bool_data(const dw4_menu_window *w,int32_t field)
{
    igBoolList *l=field?DW4_ARENA_OBJ(w->arena,igBoolList,((dw4_handle){(uint32_t)field})):NULL;
    return l && l->_count?dw4_arena_at(w->arena,(dw4_handle){(uint32_t)l->_data},(uint32_t)l->_count):NULL;
}
static inline int menu_records_bind(dw4_menu_window *w,dw4_property_folder *f,const char *const *keys,const dw4_property_type *types,int32_t **fields,int n)
{
    dw4_handle acquired[8]={{0}};if(n<0 || n>8)return -1;
    for(int i=0;i<n;i++){
        acquired[i]=keys[i]?dw4_property_list_acquire(f,keys[i],types[i]):dw4_property_folder_acquire(f);
        if(!acquired[i].off){for(int j=0;j<i;j++)dw4_property_list_release(w->arena,acquired[j]);return -1;}
    }
    for(int i=0;i<n;i++){dw4_handle old={(uint32_t)*fields[i]};*fields[i]=(int32_t)acquired[i].off;dw4_property_list_release(w->arena,old);}return 0;
}
static inline void menu_record_release(dw4_menu_window *w,int32_t *field)
{dw4_property_list_release(w->arena,(dw4_handle){(uint32_t)*field});*field=0;}
#endif
