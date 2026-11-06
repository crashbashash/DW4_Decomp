/* Source: beNDMWGameRam::vfunc_34 (0x3fca10), its beDataObjInt/IntList projections, and
 * beNDMWGameRam_FindTechniqueRow (0x3fc6f0). The recovered four-byte references resolve in the
 * owning arena. */
#include "fightrecord.h"
#include "dw4/reflected.h"

int dw4_fight_record_number(const dw4_property_folder *f,const char *key,int32_t *out)
{
    dw4_property_ref ref=dw4_property_reference(f,key,DW4_PROPERTY_NUMBER);
    const beDataObjInt *r=DW4_ARENA_OBJ(ref.arena,beDataObjInt,ref.record);
    if(!r || !out)return -1;
    *out=r->_data;return 0;
}

const int32_t *dw4_fight_record_array(const dw4_property_folder *f,const char *key,size_t *count)
{
    if(count)*count=0;
    dw4_property_ref ref=dw4_property_reference(f,key,DW4_PROPERTY_ARRAY);
    const beDataObjIntList *r=DW4_ARENA_OBJ(ref.arena,beDataObjIntList,ref.record);
    const igIntList *list=r?DW4_ARENA_OBJ(ref.arena,igIntList,((dw4_handle){(uint32_t)r->_data})):NULL;
    if(!list || list->_count<=0 || list->_count>list->_capacity || (uint32_t)list->_count>UINT32_MAX/4)return NULL;
    const int32_t *values=dw4_arena_at(ref.arena,(dw4_handle){(uint32_t)list->_data},(uint32_t)list->_count*4);
    if(values && count)*count=(size_t)list->_count;
    return values;
}

int dw4_fight_record_technique(const dw4_property_folder *f,int32_t base,int32_t *row)
{
    dw4_property_ref ref=dw4_property_reference(f,"WAZALIST",DW4_PROPERTY_ITEMS);
    const beDataObjObjectList *r=DW4_ARENA_OBJ(ref.arena,beDataObjObjectList,ref.record);
    const beNDMWItemBaseList *list=r?DW4_ARENA_OBJ(ref.arena,beNDMWItemBaseList,((dw4_handle){(uint32_t)r->_data})):NULL;
    if(!row || !list || list->_count<=0 || list->_count>list->_capacity || (uint32_t)list->_count>UINT32_MAX/4)return -1;
    const int32_t *items=dw4_arena_at(ref.arena,(dw4_handle){(uint32_t)list->_data},(uint32_t)list->_count*4);
    if(!items)return -1;
    for(int32_t i=0;i<list->_count;i++){
        /* Preserve the old item view's null-slot projection (base and row zero).
         * Authored WAZALISTs have actual beNDMWItemWaza instances. */
        if(!items[i]){if(!base){*row=0;return 0;}continue;}
        const beNDMWItemWaza *item=DW4_ARENA_OBJ(ref.arena,beNDMWItemWaza,((dw4_handle){(uint32_t)items[i]}));
        if(!item)return -1;
        if(item->_baseNo==base){*row=item->_recNo;return 0;}
    }
    return -1;
}
