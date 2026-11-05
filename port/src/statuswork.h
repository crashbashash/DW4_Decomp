/* Shared STATUS Work allocation. The retail constructor declares both stat
 * buffers as igIntList; stock fields own item lists with their item closure. */
#ifndef DW4_STATUSWORK_H
#define DW4_STATUSWORK_H
#include "arenalist.h"
#include "dw4/playerrecords.h"
static inline dw4_handle status_work_new(dw4_arena *a)
{
    const dw4_metaobject *mo=dw4_metaobject_find("beNDMWStatusInfoWork");
    dw4_handle h=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,mo->vtable);
    if(!h.off)return h;
    beNDMWStatusInfoWork *w=DW4_ARENA_OBJ(a,beNDMWStatusInfoWork,h);
    w->_parameter=al_new(a,"igIntList",4,0,NULL);w->_preview=al_new(a,"igIntList",4,0,NULL);
    if(!w->_parameter || !w->_preview){al_drop(a,&w->_parameter);al_drop(a,&w->_preview);dw4_arena_object_release(a,h);h.off=0;}
    return h;
}
static inline void status_work_drop(dw4_arena *a,dw4_handle h)
{
    if(!h.off)return;
    beNDMWStatusInfoWork *w=DW4_ARENA_OBJ(a,beNDMWStatusInfoWork,h);
    al_drop(a,&w->_parameter);al_drop(a,&w->_preview);
    dw4_property_list_release(a,al_handle(w->_weaponSalesList));
    dw4_property_list_release(a,al_handle(w->_armorSalesList));
    dw4_property_list_release(a,al_handle(w->_chipSalesList));
    dw4_property_list_release(a,al_handle(w->_junkSalesList));
    dw4_arena_object_release(a,h);
}
#endif
