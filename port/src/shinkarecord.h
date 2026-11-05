/* Typed 443110/4432a0/4435c0 form snapshots shared by STATUS and Digi-Lab. */
#ifndef DW4_SHINKARECORD_H
#define DW4_SHINKARECORD_H
#include "arenalist.h"
#include "dw4/statuscontent.h"
#include "dw4/playerstats.h"
static inline void shinka_drop(dw4_arena *a,int32_t *field)
{
    if(!*field)return;
    beNDMWShinkaCtrl *c=DW4_ARENA_OBJ(a,beNDMWShinkaCtrl,al_handle(*field));
    int n=al_count(a,c->_list);int32_t *v=al_words(a,c->_list);
    for(int i=0;i<n;i++)if(v[i]){
        beNDMWShinkaObject *o=DW4_ARENA_OBJ(a,beNDMWShinkaObject,al_handle(v[i]));
        al_free(a,o->_name);dw4_arena_object_release(a,al_handle(v[i]));
    }
    al_drop(a,&c->_list);dw4_property_list_release(a,al_handle(c->_playerParameter));
    dw4_arena_object_release(a,al_handle(*field));*field=0;
}
static inline int shinka_build(dw4_arena *a,int32_t *field,dw4_playerrecords *players,const dw4_databases *db,int player)
{
    dw4_status_skillrow rows[16];size_t n;dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);
    if(dw4_statuscontent_skill_list(players,db,player,rows,&n))return -1;
    const dw4_metaobject *cm=dw4_metaobject_find("beNDMWShinkaCtrl"),*om=dw4_metaobject_find("beNDMWShinkaObject");
    dw4_handle h=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,cm->vtable);if(!h.off)return -1;
    int32_t result=(int32_t)h.off;beNDMWShinkaCtrl *c=DW4_ARENA_OBJ(a,beNDMWShinkaCtrl,h);
    c->_playerNo=player;c->_playerParameter=(int32_t)dw4_property_folder_acquire(f).off;
    dw4_dbtable table=dw4_databases_table(db,"shinka");c->_dBShinka=(int32_t)table.db.off;
    c->_list=al_new(a,"beNDMWShinkaObjectList",4,(int)n,NULL);
    if(!c->_playerParameter || table.arena!=a || !c->_dBShinka || !c->_list){shinka_drop(a,&result);return -1;}
    int32_t *v=al_words(a,c->_list);
    for(size_t i=0;i<n;i++){
        int32_t stats[16];if(dw4_playerstats_form(db,f,rows[i].species,stats)){shinka_drop(a,&result);return -1;}
        dw4_handle obj=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,om->vtable);
        if(!obj.off){shinka_drop(a,&result);return -1;}v[i]=(int32_t)obj.off;
        beNDMWShinkaObject *o=DW4_ARENA_OBJ(a,beNDMWShinkaObject,obj);
        o->_id=rows[i].species;o->_level=rows[i].level;o->_name=al_string(a,rows[i].name);
        if(!o->_name){shinka_drop(a,&result);return -1;}
        memcpy(&o->_hpMax,stats,sizeof stats);
    }
    shinka_drop(a,field);*field=result;return 0;
}
static inline int shinka_count(dw4_arena *a,int32_t field)
{return field?al_count(a,DW4_ARENA_OBJ(a,beNDMWShinkaCtrl,al_handle(field))->_list):0;}
static inline const beNDMWShinkaObject *shinka_row(dw4_arena *a,int32_t field,int i)
{
    const beNDMWShinkaCtrl *c=field?DW4_ARENA_OBJ(a,beNDMWShinkaCtrl,al_handle(field)):NULL;
    return c && i>=0 && i<al_count(a,c->_list)?DW4_ARENA_OBJ(a,beNDMWShinkaObject,al_handle(al_words(a,c->_list)[i])):NULL;
}
#endif
