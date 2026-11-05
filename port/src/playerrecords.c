/* Session-owned GAMERAM property folders on typed arena objects (docs/arena-object-model.md, P3).
 *
 * A folder is the decomp's `beDataObjList` (an igObjectList) of named property records, held in the session arena. The record classes
 * are the recovered beDataObj family (`_name` at +8 from igNamedObject, `_data` at +12):
 *
 *   number   beDataObjInt         `_data` is the value
 *   string   beDataObjString      `_data` -> NUL-terminated string block (0 = NULL string)
 *   array    beDataObjIntList     `_data` -> igIntList
 *   bytes    beDataObjBoolList    `_data` -> igBoolList
 *   floats   beDataObjFloatList   `_data` -> igFloatList
 *   strings  beDataObjStringList  `_data` -> igStringRefList of string blocks (0 = NULL entry)
 *   items    beDataObjObjectList  `_data` -> beNDMWItemBaseList of beNDMWItem* objects (a NULL element is a null slot, kind -1)
 *   unicode  beDataObjObjectList  `_data` -> beUnicodeObjList of beUnicodeObj ({u32 count}{u16 codes...} buffer; a NULL element is absent)
 *   folder   beDataObjObjectList  `_data` -> beDataObjList (the child folder)
 *
 * The object-list records share one class; the class of the list that `_data` points at tells folders, items and unicode arrays apart
 * even when empty. Item kinds follow the port's records and the class hierarchy (0 Weapon, 1 BlueArmor, 2 YellowArmor, 3 AbilityChip,
 * 4 Disk, 9 Waza; other kinds are held in a beNDMWItemInstant with their `_kindNo`): `_kindNo` +8, `_recNo` +12, `_isEquip` +16 (a byte),
 * `_revision` / `_baseNo` / `_kazu` / `_value` +20, `_pocket` +24.
 *
 * Behavior is that of the earlier host implementation: setters copy, a record keeps its kind, borrowed arrays and strings live until the
 * record is replaced, nested folder addresses are stable, common FLAG/FLAGFOLDER/COUNTER alias player zero's BASE_* rows, commits swap
 * payloads after a complete preflight. Folder host structs stay outside the arena (they hold an arena pointer and a handle). */
#include "dw4/playerrecords.h"
#include "dw4/arena.h"
#include "dw4/object.h"
#include "dw4/reflected.h"
#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum kind {NUMBER,STRING,ARRAY,FOLDER,STRINGS,UNICODES,ITEMS,BYTES,FLOATS};

/* the retail vtable word of every class used here, resolved once from the generated schema */
static struct {
    uint32_t named,folder,dobj_int,dobj_string,dobj_intlist,dobj_stringlist,dobj_objlist,dobj_boollist,dobj_floatlist,
             int_list,string_list,bool_list,float_list,item_list,unicode_list,unicode_obj,
             weapon,blue,yellow,chip,disk,waza,instant;
} C;
static pthread_once_t classes_once=PTHREAD_ONCE_INIT;
static uint32_t vt(const char *name){const dw4_metaobject *m=dw4_metaobject_find(name);return m?m->vtable:0;}
static void resolve_classes(void)
{
    C.named=vt("igNamedObject");C.folder=vt("beDataObjList");C.dobj_int=vt("beDataObjInt");C.dobj_string=vt("beDataObjString");
    C.dobj_intlist=vt("beDataObjIntList");C.dobj_stringlist=vt("beDataObjStringList");C.dobj_objlist=vt("beDataObjObjectList");
    C.dobj_boollist=vt("beDataObjBoolList");C.dobj_floatlist=vt("beDataObjFloatList");C.int_list=vt("igIntList");
    C.string_list=vt("igStringRefList");C.bool_list=vt("igBoolList");C.float_list=vt("igFloatList");C.item_list=vt("beNDMWItemBaseList");
    C.unicode_list=vt("beUnicodeObjList");C.unicode_obj=vt("beUnicodeObj");C.weapon=vt("beNDMWItemWeapon");C.blue=vt("beNDMWItemBlueArmor");
    C.yellow=vt("beNDMWItemYellowArmor");C.chip=vt("beNDMWItemAbilityChip");C.disk=vt("beNDMWItemDisk");C.waza=vt("beNDMWItemWaza");
    C.instant=vt("beNDMWItemInstant");
}

struct dw4_property_folder {dw4_arena *a;int32_t list;dw4_property_folder *alias_peer;};
struct dw4_playerrecords {dw4_property_folder common,player[4];dw4_script_object view[5];};

/* ---- process-wide side tables: nested-folder host structs and item-record views, both keyed by (arena, handle) so their lifetime follows
 * the data wherever a folder is published ---------------------------------------------------------------------------------------- */
struct childnode {dw4_arena *a;int32_t list;dw4_property_folder f;struct childnode *next;};
struct itemview {dw4_arena *a;int32_t list;dw4_item_record *rec;size_t n;struct itemview *next;};
static pthread_mutex_t side_lock=PTHREAD_MUTEX_INITIALIZER;
static struct childnode *children;
static struct itemview *views;

static dw4_property_folder *child_struct(dw4_arena *a,int32_t list)
{
    pthread_mutex_lock(&side_lock);
    struct childnode *n;for(n=children;n;n=n->next)if(n->a==a && n->list==list)break;
    if(!n && (n=calloc(1,sizeof(*n)))){n->a=a;n->list=list;n->f.a=a;n->f.list=list;n->next=children;children=n;}
    pthread_mutex_unlock(&side_lock);
    return n?&n->f:NULL;
}
static void drop_child(dw4_arena *a,int32_t list)
{
    pthread_mutex_lock(&side_lock);
    for(struct childnode **p=&children;*p;p=&(*p)->next)if((*p)->a==a && (*p)->list==list){struct childnode *d=*p;*p=d->next;free(d);break;}
    pthread_mutex_unlock(&side_lock);
}
static void drop_view(dw4_arena *a,int32_t list)
{
    pthread_mutex_lock(&side_lock);
    for(struct itemview **p=&views;*p;p=&(*p)->next)if((*p)->a==a && (*p)->list==list){struct itemview *d=*p;*p=d->next;free(d->rec);free(d);break;}
    pthread_mutex_unlock(&side_lock);
}

/* ---- arena helpers ---------------------------------------------------------------------------------------------------------- */
static dw4_handle H(int32_t off){dw4_handle h={(uint32_t)off};return h;}
static void *at(dw4_arena *a,int32_t h,uint32_t n){return h?dw4_arena_at(a,H(h),n):NULL;}
static void release(dw4_arena *a,int32_t h){if(h)dw4_arena_free(a,H(h));}
static igIntList *LV(dw4_arena *a,int32_t h){return h?(igIntList *)at(a,h,sizeof(igIntList)):NULL;}   /* the igDataList layout every list shares */
static uint8_t *block(dw4_arena *a,igIntList *l,uint32_t width)
{return l && l->_count>0 && l->_data?(uint8_t *)at(a,l->_data,(uint32_t)l->_count*width):NULL;}
static int32_t elem(dw4_arena *a,igIntList *l,size_t i)
{uint8_t *b=block(a,l,4);int32_t v;if(!b||i>=(size_t)l->_count)return 0;memcpy(&v,b+4*i,4);return v;}

static int str_new(dw4_arena *a,const char *s,int32_t *out)
{
    *out=0;if(!s)return 0;
    size_t n=strlen(s)+1;if(n>0xffffffffu)return -1;
    dw4_handle h=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,(uint32_t)n);if(!h.off)return -1;
    memcpy(dw4_arena_at(a,h,(uint32_t)n),s,n);*out=(int32_t)h.off;return 0;
}
static const char *str_at(dw4_arena *a,int32_t h){return h?(const char *)at(a,h,1):NULL;}

/* a list object of class `cls` holding `n` elements of `width` bytes (copied from src, else zero); 0 or -1 */
static int list_make(dw4_arena *a,uint32_t cls,uint32_t width,size_t n,const void *src,int32_t *out)
{
    *out=0;
    if(n>0x7fffffffu/width)return -1;
    dw4_handle o=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,cls),d={0};if(!o.off)return -1;
    if(n){d=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,(uint32_t)(n*width));if(!d.off){dw4_arena_free(a,o);return -1;}
        if(src)memcpy(dw4_arena_at(a,d,(uint32_t)(n*width)),src,n*width);}
    igIntList *l=(igIntList *)dw4_arena_at(a,o,sizeof(igIntList));
    l->_count=l->_capacity=(int32_t)n;l->_data=(int32_t)d.off;*out=(int32_t)o.off;return 0;
}
static void list_release(dw4_arena *a,int32_t h)
{igIntList *l=LV(a,h);if(!l)return;release(a,l->_data);dw4_arena_object_release(a,H(h));}
/* append one element handle, growing the block as List_Resize does (minimum 4, doubling below 1024, then +1024) */
static int list_reserve(dw4_arena *a,int32_t h,size_t want)
{
    igIntList *l=LV(a,h);if(!l)return -1;
    if(want<=(size_t)l->_capacity)return 0;
    size_t cap=(size_t)l->_capacity;
    while(cap<want)cap=cap<4?4:cap<1024?cap*2:cap+1024;
    if(cap>0x1fffffffu)return -1;
    dw4_handle d=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,(uint32_t)(cap*4));if(!d.off)return -1;
    l=LV(a,h);
    if(l->_count>0)memcpy(dw4_arena_at(a,d,(uint32_t)(cap*4)),at(a,l->_data,(uint32_t)l->_count*4),(size_t)l->_count*4);
    release(a,l->_data);l->_data=(int32_t)d.off;l->_capacity=(int32_t)cap;return 0;
}
static int list_append(dw4_arena *a,int32_t h,int32_t v)
{
    if(list_reserve(a,h,(size_t)LV(a,h)->_count+1))return -1;
    igIntList *l=LV(a,h);
    uint8_t *b=(uint8_t *)at(a,l->_data,(uint32_t)(l->_count+1)*4);memcpy(b+4*(size_t)l->_count,&v,4);l->_count++;return 0;
}

/* ---- records ---------------------------------------------------------------------------------------------------------------- */
static beDataObjInt *R(dw4_arena *a,int32_t h){return h?(beDataObjInt *)at(a,h,sizeof(beDataObjInt)):NULL;}   /* name +8, data +12 */
static const char *rec_name(dw4_arena *a,int32_t rec){beDataObjInt *r=R(a,rec);return r?str_at(a,r->_name):NULL;}
static int rec_kind(dw4_arena *a,int32_t rec)
{
    beDataObjInt *r=R(a,rec);if(!r)return -1;
    uint32_t c=(uint32_t)r->_vtable;
    if(c==C.dobj_int)return NUMBER;
    if(c==C.dobj_string)return STRING;
    if(c==C.dobj_intlist)return ARRAY;
    if(c==C.dobj_stringlist)return STRINGS;
    if(c==C.dobj_boollist)return BYTES;
    if(c==C.dobj_floatlist)return FLOATS;
    if(c==C.dobj_objlist){igIntList *l=LV(a,r->_data);if(!l)return -1;
        if((uint32_t)l->_vtable==C.folder)return FOLDER;
        if((uint32_t)l->_vtable==C.item_list)return ITEMS;
        if((uint32_t)l->_vtable==C.unicode_list)return UNICODES;}
    return -1;
}
static uint32_t rec_class(int kind){
    switch(kind){case NUMBER:return C.dobj_int;case STRING:return C.dobj_string;case ARRAY:return C.dobj_intlist;
    case STRINGS:return C.dobj_stringlist;case BYTES:return C.dobj_boollist;case FLOATS:return C.dobj_floatlist;default:return C.dobj_objlist;}
}

static void folder_release(dw4_arena *a,int32_t list);
/* free what a record's `_data` owns */
static void value_release(dw4_arena *a,int kind,int32_t data)
{
    igIntList *l;
    if(data && kind!=NUMBER && kind!=STRING && dw4_arena_object_refcount(a,H(data))>1){
        dw4_arena_object_release(a,H(data));return;
    }
    switch(kind){
    case NUMBER:break;
    case STRING:release(a,data);break;
    case ARRAY:case BYTES:case FLOATS:list_release(a,data);break;
    case STRINGS:l=LV(a,data);for(int32_t i=0;l && i<l->_count;i++)release(a,elem(a,l,(size_t)i));list_release(a,data);break;
    case ITEMS:l=LV(a,data);for(int32_t i=0;l && i<l->_count;i++){int32_t h=elem(a,l,(size_t)i);if(h)dw4_arena_object_release(a,H(h));}drop_view(a,data);list_release(a,data);break;
    case UNICODES:l=LV(a,data);
        for(int32_t i=0;l && i<l->_count;i++){int32_t o=elem(a,l,(size_t)i);beUnicodeObj *u=o?(beUnicodeObj *)at(a,o,sizeof(beUnicodeObj)):NULL;
            if(u)release(a,u->_buffer);
            release(a,o);}
        list_release(a,data);break;
    case FOLDER:folder_release(a,data);break;
    }
}
static void rec_release(dw4_arena *a,int32_t rec)
{
    beDataObjInt *r=R(a,rec);if(!r)return;
    if(dw4_arena_object_refcount(a,H(rec))>1){dw4_arena_object_release(a,H(rec));return;}
    int kind=rec_kind(a,rec);if(kind>=0)value_release(a,kind,r->_data);
    release(a,r->_name);dw4_arena_object_release(a,H(rec));
}
/* free every record of a folder and its list (nested folders recurse) */
static void folder_release(dw4_arena *a,int32_t list)
{
    igIntList *l=LV(a,list);if(!l)return;
    if(dw4_arena_object_refcount(a,H(list))>1){dw4_arena_object_release(a,H(list));return;}
    for(int32_t i=0;i<l->_count;i++)rec_release(a,elem(a,l,(size_t)i));
    release(a,l->_data);dw4_arena_object_release(a,H(list));drop_child(a,list);
}
static int folder_new(dw4_arena *a,int32_t *out){return list_make(a,C.folder,4,0,NULL,out);}

static int32_t find_raw(const dw4_property_folder *f,const char *key)
{
    if(!f || !key)return 0;
    igIntList *l=LV(f->a,f->list);
    for(int32_t i=0;l && i<l->_count;i++){int32_t rec=elem(f->a,l,(size_t)i);const char *n=rec_name(f->a,rec);if(n && !strcmp(n,key))return rec;}
    return 0;
}
static int32_t find(const dw4_property_folder *f,const char *key)
{
    static const char *const common[]={"FLAG","FLAGFOLDER","COUNTER"};
    static const char *const base[]={"BASE_FLAG","BASE_FLAGFOLDER","BASE_COUNTER"};
    if(f && f->alias_peer && key)for(unsigned i=0;i<3;i++)if(!strcmp(key,common[i])){
        int32_t p=find_raw(f->alias_peer,base[i]);if(p)return p;
    }
    return find_raw(f,key);
}
/* set a record's value: replace an existing record of the same kind (its old payload is freed), or create a new one. Takes ownership of
 * `data` (it is freed on failure). */
static int upsert(dw4_property_folder *f,const char *key,int kind,int32_t data)
{
    pthread_once(&classes_once,resolve_classes);
    if(!f || !key || !*key){value_release(f?f->a:NULL,kind,data);return -1;}
    int32_t rec=find(f,key);
    if(rec){
        if(rec_kind(f->a,rec)!=kind){value_release(f->a,kind,data);return -1;}
        beDataObjInt *r=R(f->a,rec);int32_t old=r->_data;r->_data=data;value_release(f->a,kind,old);return 0;
    }
    dw4_handle o=dw4_arena_object_new(f->a,DW4_REGION_PERSISTENT,rec_class(kind));int32_t name=0;
    if(!o.off || str_new(f->a,key,&name) || list_append(f->a,f->list,(int32_t)o.off)){
        release(f->a,name);release(f->a,(int32_t)o.off);value_release(f->a,kind,data);return -1;
    }
    beDataObjInt *r=R(f->a,(int32_t)o.off);r->_name=name;r->_data=data;return 0;
}

/* ---- the owner -------------------------------------------------------------------------------------------------------------- */
dw4_playerrecords *dw4_playerrecords_open(void)
{
    pthread_once(&classes_once,resolve_classes);
    dw4_arena *a=dw4_session_arena();if(!a)return NULL;
    dw4_playerrecords *o=calloc(1,sizeof(*o));if(!o)return NULL;
    dw4_property_folder *roots[5]={&o->common,o->player,o->player+1,o->player+2,o->player+3};
    for(unsigned i=0;i<5;i++){roots[i]->a=a;if(folder_new(a,&roots[i]->list)){dw4_playerrecords_close(o);return NULL;}}
    /* 4ced40 through 3f6620: scalar zero, byte/int/float arrays zero,
     * null strings and four null checkpoint-name slots. */
    uint8_t bytes[1024]={0};int32_t ints[16]={0};float positions[12]={0};const char *strings[4]={0};
    const char *const numbers[]={"NINZU","DIFFICULTY","CAMERAMODE","LIGHTMODE","GATESTAGENO"};
    for(unsigned i=0;i<5;i++)if(dw4_property_set_number(&o->common,numbers[i],0))goto bad;
    if(dw4_property_set_bytes(&o->common,"FLAG",bytes,1024) ||
       dw4_property_set_bytes(&o->common,"FLAGFOLDER",bytes,12) ||
       dw4_property_set_array(&o->common,"COUNTER",ints,16) ||
       dw4_property_set_strings(&o->common,"BKCHIPSTAGE",strings,4) ||
       dw4_property_set_floats(&o->common,"BKCHIPPOS",positions,12) ||
       dw4_property_set_array(&o->common,"BKCHIPDATA",ints,8) ||
       dw4_property_set_strings(&o->common,"BKCHIPNAME",strings,4) ||
       dw4_property_set_string(&o->common,"GATESTAGENAME",NULL))goto bad;
    for(unsigned i=0;i<4;i++)if(dw4_property_set_number(&o->player[i],"ISUSE",0))goto bad;
    return o;
bad:dw4_playerrecords_close(o);return NULL;
}
void dw4_playerrecords_close(dw4_playerrecords *o)
{
    if(!o)return;
    folder_release(o->common.a,o->common.list);
    for(unsigned i=0;i<4;i++)folder_release(o->player[i].a,o->player[i].list);
    free(o);
}
dw4_property_folder *dw4_playerrecords_get(dw4_playerrecords *o,const char *method,int32_t player)
{
    if(!o || !method)return NULL;
    if(!strcmp(method,"GETCOMMON"))return &o->common;
    if(!strcmp(method,"GETPLAYER"))return player>=0 && player<4?&o->player[player]:NULL;
    static const char *keys[]={"GETPLAYER1","GETPLAYER2","GETPLAYER3","GETPLAYER4"};
    for(unsigned i=0;i<4;i++)if(!strcmp(method,keys[i]))return &o->player[i];
    return NULL;
}

/* ---- typed reads and writes -------------------------------------------------------------------------------------------------- */
dw4_property_ref dw4_property_reference(const dw4_property_folder *f,const char *key,dw4_property_type type)
{
    int32_t rec=find(f,key);
    if(!rec || rec_kind(f->a,rec)!=(int)type)return (dw4_property_ref){0};
    return (dw4_property_ref){f->a,H(rec)};
}
int dw4_property_number(dw4_property_folder *f,const char *key,int32_t *out)
{int32_t rec=find(f,key);if(!rec || rec_kind(f->a,rec)!=NUMBER || !out)return -1;*out=R(f->a,rec)->_data;return 0;}
const char *dw4_property_string(const dw4_property_folder *f,const char *key)
{int32_t rec=find(f,key);return rec && rec_kind(f->a,rec)==STRING?str_at(f->a,R(f->a,rec)->_data):NULL;}
int dw4_property_set_number(dw4_property_folder *f,const char *key,int32_t v){return upsert(f,key,NUMBER,v);}
int dw4_property_set_string(dw4_property_folder *f,const char *key,const char *v)
{int32_t d;if(!f || str_new(f->a,v,&d))return -1;return upsert(f,key,STRING,d);}
static int set_plain(dw4_property_folder *f,const char *key,int kind,uint32_t cls,uint32_t width,const void *v,size_t n)
{
    int32_t d;
    if(!f || (n && !v) || list_make(f->a,cls,width,n,v,&d))return -1;
    return upsert(f,key,kind,d);
}
int dw4_property_set_array(dw4_property_folder *f,const char *key,const int32_t *v,size_t n)
{pthread_once(&classes_once,resolve_classes);return set_plain(f,key,ARRAY,C.int_list,4,v,n);}
int dw4_property_set_bytes(dw4_property_folder *f,const char *key,const uint8_t *v,size_t n)
{pthread_once(&classes_once,resolve_classes);return set_plain(f,key,BYTES,C.bool_list,1,v,n);}
int dw4_property_set_floats(dw4_property_folder *f,const char *key,const float *v,size_t n)
{pthread_once(&classes_once,resolve_classes);return set_plain(f,key,FLOATS,C.float_list,4,v,n);}
static const void *get_plain(const dw4_property_folder *f,const char *key,int kind,uint32_t width,size_t *count)
{
    int32_t rec=find(f,key);
    if(!rec || rec_kind(f->a,rec)!=kind){if(count)*count=0;return NULL;}
    igIntList *l=LV(f->a,R(f->a,rec)->_data);
    if(count)*count=l && l->_count>0?(size_t)l->_count:0;
    return block(f->a,l,width);
}
const int32_t *dw4_property_array(const dw4_property_folder *f,const char *key,size_t *count){return get_plain(f,key,ARRAY,4,count);}
const uint8_t *dw4_property_bytes(const dw4_property_folder *f,const char *key,size_t *count){return get_plain(f,key,BYTES,1,count);}
const float *dw4_property_floats(const dw4_property_folder *f,const char *key,size_t *count){return get_plain(f,key,FLOATS,4,count);}
int dw4_property_describe(const dw4_property_folder *f,const char *key,dw4_property_type *type,size_t *count)
{
    int32_t rec=find(f,key);if(!rec || !type || !count)return -1;
    int kind=rec_kind(f->a,rec);if(kind<0)return -1;
    *type=(dw4_property_type)kind;
    if(kind==NUMBER || kind==STRING || kind==FOLDER)*count=1;
    else{igIntList *l=LV(f->a,R(f->a,rec)->_data);*count=l && l->_count>0?(size_t)l->_count:0;}
    return 0;
}

int dw4_property_set_strings(dw4_property_folder *f,const char *key,const char *const *v,size_t n)
{
    pthread_once(&classes_once,resolve_classes);
    int32_t d;if(!f || (n && !v) || list_make(f->a,C.string_list,4,n,NULL,&d))return -1;
    for(size_t i=0;i<n;i++){
        int32_t s;
        if(str_new(f->a,v[i],&s)){value_release(f->a,STRINGS,d);return -1;}
        memcpy(block(f->a,LV(f->a,d),4)+4*i,&s,4);
    }
    return upsert(f,key,STRINGS,d);
}
const char *dw4_property_string_at(const dw4_property_folder *f,const char *key,size_t i)
{
    int32_t rec=find(f,key);if(!rec || rec_kind(f->a,rec)!=STRINGS)return NULL;
    igIntList *l=LV(f->a,R(f->a,rec)->_data);return l && i<(size_t)l->_count?str_at(f->a,elem(f->a,l,i)):NULL;
}

int dw4_property_set_unicode_objects(dw4_property_folder *f,const char *key,const dw4_unicode_object *v,size_t n)
{
    pthread_once(&classes_once,resolve_classes);
    if(!f || (n && !v))return -1;
    for(size_t i=0;i<n;i++){
        if(!v[i].present){if(v[i].count || v[i].codes)return -1;continue;}
        if(v[i].count>0x7fffffffu/sizeof(uint16_t) || (v[i].count && !v[i].codes))return -1;
    }
    int32_t d;if(list_make(f->a,C.unicode_list,4,n,NULL,&d))return -1;
    for(size_t i=0;i<n;i++){
        if(!v[i].present)continue;
        dw4_handle o=dw4_arena_object_new(f->a,DW4_REGION_PERSISTENT,C.unicode_obj);
        uint32_t bytes=4u+(uint32_t)v[i].count*2u;dw4_handle b=o.off?dw4_arena_alloc(f->a,DW4_REGION_PERSISTENT,bytes):(dw4_handle){0};
        if(!o.off || !b.off){release(f->a,(int32_t)o.off);value_release(f->a,UNICODES,d);return -1;}
        uint8_t *p=(uint8_t *)dw4_arena_at(f->a,b,bytes);uint32_t cnt=(uint32_t)v[i].count;memcpy(p,&cnt,4);
        if(cnt)memcpy(p+4,v[i].codes,(size_t)cnt*2);
        ((beUnicodeObj *)dw4_arena_at(f->a,o,sizeof(beUnicodeObj)))->_buffer=(int32_t)b.off;
        int32_t oh=(int32_t)o.off;memcpy(block(f->a,LV(f->a,d),4)+4*i,&oh,4);
    }
    return upsert(f,key,UNICODES,d);
}
int dw4_property_unicode_object(const dw4_property_folder *f,const char *key,size_t i,dw4_unicode_object *v)
{
    int32_t rec=find(f,key);if(!v || !rec || rec_kind(f->a,rec)!=UNICODES)return -1;
    igIntList *l=LV(f->a,R(f->a,rec)->_data);if(!l || i>=(size_t)l->_count)return -1;
    int32_t o=elem(f->a,l,i);
    if(!o){*v=(dw4_unicode_object){0};return 0;}
    beUnicodeObj *u=(beUnicodeObj *)at(f->a,o,sizeof(beUnicodeObj));
    const uint8_t *p=u?(const uint8_t *)at(f->a,u->_buffer,4):NULL;uint32_t cnt=0;if(!p)return -1;memcpy(&cnt,p,4);
    *v=(dw4_unicode_object){cnt?(const uint16_t *)(const void *)(p+4):NULL,cnt,1};return 0;
}

/* items: beNDMWItem* objects; a kind -1 record is a null slot (a NULL element) */
static uint32_t item_class(int32_t kind)
{
    switch(kind){case 0:return C.weapon;case 1:return C.blue;case 2:return C.yellow;case 3:return C.chip;case 4:return C.disk;case 9:return C.waza;default:return C.instant;}
}
dw4_handle dw4_item_list_new(dw4_arena *a,const dw4_item_record *v,size_t n)
{
    pthread_once(&classes_once,resolve_classes);
    int32_t d;if(!a || (n && !v) || list_make(a,C.item_list,4,n,NULL,&d))return (dw4_handle){0};
    for(size_t i=0;i<n;i++){
        if(v[i].kind==-1)continue;
        dw4_handle o=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,item_class(v[i].kind));
        if(!o.off){value_release(a,ITEMS,d);return (dw4_handle){0};}
        beNDMWItemRevisionPocketBase *it=(beNDMWItemRevisionPocketBase *)dw4_arena_at(a,o,sizeof(*it));
        it->_kindNo=v[i].kind;it->_recNo=v[i].record;it->_isEquip=(unsigned char)v[i].equipped;it->_revision=v[i].revision;it->_pocket=v[i].pocket;
        int32_t oh=(int32_t)o.off;memcpy(block(a,LV(a,d),4)+4*i,&oh,4);
    }
    return H(d);
}
int dw4_property_set_items(dw4_property_folder *f,const char *key,const dw4_item_record *v,size_t n)
{
    if(!f)return -1;
    dw4_handle h=dw4_item_list_new(f->a,v,n);
    return h.off?upsert(f,key,ITEMS,(int32_t)h.off):-1;
}
const dw4_item_record *dw4_item_list_view(dw4_arena *a,dw4_handle h,size_t *n)
{
    int32_t list=(int32_t)h.off;igIntList *l=LV(a,list);size_t count=l && l->_count>0?(size_t)l->_count:0;
    if(n)*n=count;
    if(!count)return NULL;
    pthread_mutex_lock(&side_lock);
    struct itemview *w;for(w=views;w;w=w->next)if(w->a==a && w->list==list)break;
    if(!w && (w=calloc(1,sizeof(*w))) && (w->rec=calloc(count,sizeof(*w->rec)))){
        w->a=a;w->list=list;w->n=count;
        for(size_t i=0;i<count;i++){
            int32_t o=elem(a,l,i);beNDMWItemRevisionPocketBase *it=o?(beNDMWItemRevisionPocketBase *)at(a,o,sizeof(*it)):NULL;
            w->rec[i]=it?(dw4_item_record){it->_kindNo,it->_recNo,it->_isEquip,it->_revision,it->_pocket}:(dw4_item_record){.kind=-1};
        }
        w->next=views;views=w;
    }else if(w && !w->rec){free(w);w=NULL;}
    pthread_mutex_unlock(&side_lock);
    return w?w->rec:NULL;
}

const dw4_item_record *dw4_property_items(const dw4_property_folder *f,const char *key,size_t *n)
{
    int32_t rec=find(f,key);if(!rec || rec_kind(f->a,rec)!=ITEMS){if(n)*n=0;return NULL;}
    return dw4_item_list_view(f->a,H(R(f->a,rec)->_data),n);
}
int dw4_item_list_set(dw4_arena *a,dw4_handle h,size_t slot,const dw4_item_record *value)
{
    igIntList *l=LV(a,(int32_t)h.off);if(!l || slot>=(size_t)l->_count || !value)return -1;
    dw4_handle one=dw4_item_list_new(a,value,1);if(!one.off)return -1;
    int32_t replacement=elem(a,LV(a,(int32_t)one.off),0),old=elem(a,l,slot),zero=0;
    memcpy(block(a,l,4)+slot*4,&replacement,4);memcpy(block(a,LV(a,(int32_t)one.off),4),&zero,4);
    value_release(a,ITEMS,(int32_t)one.off);if(old)dw4_arena_object_release(a,H(old));drop_view(a,(int32_t)h.off);return 0;
}
int dw4_property_item_count(const dw4_property_folder *f,const char *key,size_t *n)
{
    int32_t rec=find(f,key);if(!rec || rec_kind(f->a,rec)!=ITEMS || !n)return -1;
    igIntList *l=LV(f->a,R(f->a,rec)->_data);*n=l && l->_count>0?(size_t)l->_count:0;return 0;
}

dw4_property_folder *dw4_property_child(dw4_property_folder *f,const char *key,int create)
{
    pthread_once(&classes_once,resolve_classes);
    int32_t rec=find(f,key);
    if(rec)return rec_kind(f->a,rec)==FOLDER?child_struct(f->a,R(f->a,rec)->_data):NULL;
    if(!create || !f)return NULL;
    int32_t list;if(folder_new(f->a,&list))return NULL;
    if(upsert(f,key,FOLDER,list))return NULL;
    return child_struct(f->a,list);
}

/* ---- the GAMERAM native bindings -------------------------------------------------------------------------------------------- */
int dw4_playerrecords_call(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    *r=(dw4_script_value){0};
    if((!strcmp(method,"FLGisOn") && n==1) || (!strcmp(method,"FLGset") && n==2)) {
        if(a[0].type!=DW4_SCRIPT_NUMBER || !isfinite(a[0].number) || a[0].number<0 ||
           a[0].number>=1024 || floor(a[0].number)!=a[0].number)goto dependency;
        size_t count=0;uint8_t *flags=(uint8_t *)(uintptr_t)dw4_property_bytes(dw4_playerrecords_get(user,"GETCOMMON",0),"FLAG",&count);
        if(!flags || count!=1024)goto dependency;
        if(n==1)*r=(dw4_script_value){DW4_SCRIPT_NUMBER,flags[(int)a[0].number],NULL,0};
        else {
            if(a[1].type!=DW4_SCRIPT_NUMBER || !isfinite(a[1].number) || a[1].number<INT32_MIN || a[1].number>INT32_MAX)goto dependency;
            flags[(int)a[0].number]=(uint8_t)(int32_t)a[1].number;
        }
        return 0;
    }
    if(!strcmp(method,"SYSgetPlayerNinzu") && !n) {
        int32_t count;
        if(dw4_property_number(dw4_playerrecords_get(user,"GETCOMMON",0),"NINZU",&count))goto dependency;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,count,NULL,0};return 0;
    }
    if(!strcmp(method,"SYSgetGateStageName") && !n) {
        const char *name=dw4_property_string(dw4_playerrecords_get(user,"GETCOMMON",0),"GATESTAGENAME");
        if(name)*r=(dw4_script_value){DW4_SCRIPT_STRING,0,name,strlen(name)};
        return 0;
    }
    if(!strcmp(method,"SYSgetGateStageNo") && !n) {
        int32_t no;
        if(dw4_property_number(dw4_playerrecords_get(user,"GETCOMMON",0),"GATESTAGENO",&no))goto dependency;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,no,NULL,0};return 0;
    }
    if(!strcmp(method,"SYSsetGateStage") && n==2 &&
       (a[0].type==DW4_SCRIPT_NIL || (a[0].type==DW4_SCRIPT_STRING && a[0].string && !memchr(a[0].string,0,a[0].length))) &&
       a[1].type==DW4_SCRIPT_NUMBER && isfinite(a[1].number) && a[1].number>=INT32_MIN && a[1].number<=INT32_MAX) {
        dw4_property_folder *common=dw4_playerrecords_get(user,"GETCOMMON",0);
        if(dw4_property_set_string(common,"GATESTAGENAME",a[0].type==DW4_SCRIPT_NIL?"GateOff":a[0].string) ||
           dw4_property_set_number(common,"GATESTAGENO",(int32_t)a[1].number))goto dependency;
        return 0;
    }
    if(!strcmp(method,"SYSisGetShinkaDigimon") && n==2 && a[0].type==DW4_SCRIPT_NUMBER &&
       a[1].type==DW4_SCRIPT_NUMBER && a[0].number>=0 && a[0].number<4 && floor(a[0].number)==a[0].number &&
       a[1].number>=0 && a[1].number<16 && floor(a[1].number)==a[1].number) {
        size_t count;const int32_t *use=dw4_property_array(dw4_playerrecords_get(user,"GETPLAYER",(int32_t)a[0].number),"BASE_ISUSE",&count);
        if(!use || count!=16)goto dependency;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,(uint8_t)use[(int)a[1].number],NULL,0};return 0;
    }
    if(!strcmp(method,"SYSctlCardFolder") && n==2 && a[0].type==DW4_SCRIPT_STRING && a[0].string &&
       a[0].length==4 && !memcmp(a[0].string,"KAZU",4) && a[1].type==DW4_SCRIPT_NUMBER) {
        size_t count=0;const uint8_t *cards=dw4_property_bytes(dw4_playerrecords_get(user,"GETPLAYER",0),"CARDLIST",&count);
        dw4_property_type type;size_t c2;
        if(dw4_property_describe(dw4_playerrecords_get(user,"GETPLAYER",0),"CARDLIST",&type,&c2) || type!=DW4_PROPERTY_BYTES)goto dependency;
        int32_t total=0;for(size_t i=0;cards && i<count;i++)total+=cards[i]==1;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,total,NULL,0};return 0;
    }
    if(!strcmp(method,"SYSctlPlayer")) {
        const char *key=NULL;
        if(n==4 && a[0].type==DW4_SCRIPT_STRING && a[0].string && a[1].type==DW4_SCRIPT_STRING && a[1].string &&
           a[2].type==DW4_SCRIPT_NUMBER && isfinite(a[2].number) && a[2].number>=0 && a[2].number<4 && floor(a[2].number)==a[2].number &&
           a[3].type==DW4_SCRIPT_NUMBER && a[3].number==0) {
            if(!strcmp(a[0].string,"HP"))key=!strcmp(a[1].string,"GETHP")?"HP":!strcmp(a[1].string,"GETMHP")?"MHP":NULL;
            if(!strcmp(a[0].string,"MP"))key=!strcmp(a[1].string,"GETMP")?"MP":!strcmp(a[1].string,"GETMMP")?"MMP":NULL;
        }
        int32_t value;
        if(!key || dw4_property_number(dw4_playerrecords_get(user,"GETPLAYER",(int32_t)a[2].number),key,&value))goto dependency;
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,value,NULL,0};return 0;
    }
    const char *key=NULL;int byte=0,text=0,weapons=0;
    if(!strcmp(method,"SYSisJoinPlayer")){key="ISUSE";byte=1;}
    else if(!strcmp(method,"SYSgetPlayerName")){key="DIGIMONNAME";text=1;}
    else if(!strcmp(method,"SYSgetPlayerLevel"))key="LEVEL";
    else if(!strcmp(method,"SYSgetPlayerDigimon"))key="DIGIMONNO";
    else if(!strcmp(method,"SYSgetWeaponName")){key="POWERSOCKETNAME";weapons=1;}
    else return 1;
    *r=(dw4_script_value){0};
    if(n!=(weapons?2u:1u) || a[0].type!=DW4_SCRIPT_NUMBER || !isfinite(a[0].number) ||
       a[0].number<0 || a[0].number>3 || floor(a[0].number)!=a[0].number){
        snprintf(error,cap,"%s requires player index 0..3",method);return -1;}
    dw4_property_folder *f=dw4_playerrecords_get(user,"GETPLAYER",(int32_t)a[0].number);
    if(weapons){
        if(a[1].type!=DW4_SCRIPT_NUMBER || !isfinite(a[1].number) || a[1].number<0 ||
           a[1].number>INT32_MAX || floor(a[1].number)!=a[1].number){
            snprintf(error,cap,"%s requires a nonnegative socket index",method);return -1;}
        dw4_property_type type;size_t count;
        if(dw4_property_describe(f,key,&type,&count) || type!=DW4_PROPERTY_STRINGS){snprintf(error,cap,"%s: player record %s is unavailable",method,key);return -1;}
        const char *s=dw4_property_string_at(f,key,(size_t)a[1].number);
        if(s)*r=(dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};
        return 0;
    }
    if(text){const char *s=dw4_property_string(f,key);if(s){*r=(dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};return 0;}}
    else {int32_t v;if(!dw4_property_number(f,key,&v)){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,byte?(uint8_t)v:v,NULL,0};return 0;}}
    snprintf(error,cap,"%s: player record %s is unavailable",method,key);return -1;
dependency:
    snprintf(error,cap,"%s: session record dependency unavailable",method);return -1;
}

/* ---- publication, staging and snapshots ------------------------------------------------------------------------------------- */
int dw4_playerrecords_publish(dw4_playerrecords *o,dw4_playerrecords *staged,int32_t slot)
{
    if(!o || !staged || o==staged || slot<0 || slot>3 || o->common.a!=staged->common.a)return -1;
    int32_t ninzu=find(&o->common,"NINZU");if(!ninzu || rec_kind(o->common.a,ninzu)!=NUMBER)return -1;
    int aliases=0;
    if(!slot){
        const char *keys[]={"BASE_FLAG","BASE_FLAGFOLDER","BASE_COUNTER"};
        const size_t counts[]={1024,12,16};
        for(unsigned i=0;i<3;i++){
            int32_t p=find_raw(staged->player,keys[i]);if(!p)continue;
            dw4_property_type type;size_t count;
            if(dw4_property_describe(staged->player,keys[i],&type,&count) || type!=(i==2?DW4_PROPERTY_ARRAY:DW4_PROPERTY_BYTES) || count!=counts[i])return -1;
            aliases++;
        }
        if(aliases && aliases!=3)return -1;
    }
    int32_t list=o->player[slot].list;o->player[slot].list=staged->player[slot].list;staged->player[slot].list=list;
    dw4_property_folder *peer=o->player[slot].alias_peer;o->player[slot].alias_peer=staged->player[slot].alias_peer;staged->player[slot].alias_peer=peer;
    /* 3f82a0 binds the common views only for player zero. Resolve by stable
     * folder/key so later private record commits cannot leave stale buffers. */
    if(!slot)o->common.alias_peer=aliases?o->player:NULL;
    int32_t count=0,v;
    for(unsigned i=0;i<4;i++)if(!dw4_property_number(o->player+i,"ISUSE",&v) && (uint8_t)v)count++;
    R(o->common.a,ninzu)->_data=count;return 0;
}

int dw4_playerrecords_join(dw4_playerrecords *o,int32_t slot,int joined)
{
    if(!o || slot<0 || slot>3)return -1;
    int32_t use=find(o->player+slot,"ISUSE"),ninzu=find(&o->common,"NINZU");
    if(!use || rec_kind(o->common.a,use)!=NUMBER || !ninzu || rec_kind(o->common.a,ninzu)!=NUMBER)return -1;
    R(o->common.a,use)->_data=joined!=0;int32_t count=0,v;
    for(unsigned i=0;i<4;i++)if(!dw4_property_number(o->player+i,"ISUSE",&v) && (uint8_t)v)count++;
    R(o->common.a,ninzu)->_data=count;return 0;
}

/* copy one record's payload into `to` under the same key (folders are not copied by dw4_property_copy_values) */
static int copy_record(dw4_property_folder *to,dw4_property_folder *from,const char *key,int kind,int32_t rec,int with_folders)
{
    dw4_arena *a=from->a;beDataObjInt *r=R(a,rec);igIntList *l;size_t n=0;
    switch(kind){
    case NUMBER:return dw4_property_set_number(to,key,r->_data);
    case STRING:return dw4_property_set_string(to,key,str_at(a,r->_data));
    case ARRAY:{const int32_t *p=dw4_property_array(from,key,&n);return dw4_property_set_array(to,key,p,n);}
    case BYTES:{const uint8_t *p=dw4_property_bytes(from,key,&n);return dw4_property_set_bytes(to,key,p,n);}
    case FLOATS:{const float *p=dw4_property_floats(from,key,&n);return dw4_property_set_floats(to,key,p,n);}
    case STRINGS:{
        l=LV(a,r->_data);n=l && l->_count>0?(size_t)l->_count:0;
        const char **s=n?calloc(n,sizeof(*s)):NULL;if(n && !s)return -1;
        for(size_t i=0;i<n;i++)s[i]=str_at(a,elem(a,l,i));
        int rc=dw4_property_set_strings(to,key,s,n);free(s);return rc;}
    case UNICODES:{
        l=LV(a,r->_data);n=l && l->_count>0?(size_t)l->_count:0;
        dw4_unicode_object *u=n?calloc(n,sizeof(*u)):NULL;if(n && !u)return -1;
        for(size_t i=0;i<n;i++)dw4_property_unicode_object(from,key,i,u+i);
        int rc=dw4_property_set_unicode_objects(to,key,u,n);free(u);return rc;}
    case ITEMS:{const dw4_item_record *p=dw4_property_items(from,key,&n);return dw4_property_set_items(to,key,p,n);}
    case FOLDER:{
        if(!with_folders)return 0;
        dw4_property_folder *child=dw4_property_child(to,key,1),*src=child_struct(a,r->_data);
        if(!child || !src)return -1;
        igIntList *cl=LV(a,src->list);
        for(int32_t i=0;cl && i<cl->_count;i++){
            int32_t crec=elem(a,cl,(size_t)i);const char *cname=rec_name(a,crec);int ck=rec_kind(a,crec);
            if(!cname || ck<0 || copy_record(child,src,cname,ck,crec,1))return -1;
        }
        return 0;}
    }
    return -1;
}
int dw4_property_copy_values(dw4_property_folder *to,const dw4_property_folder *from)
{
    if(!to || !from || to==from)return -1;
    igIntList *l=LV(from->a,from->list);
    for(int32_t i=0;l && i<l->_count;i++){
        int32_t rec=elem(from->a,l,(size_t)i);const char *key=rec_name(from->a,rec);
        int32_t p=find(from,key);   /* alias rows resolve exactly as the host did */
        if(!p || copy_record(to,(dw4_property_folder *)from,key,rec_kind(from->a,p),p,0))return -1;
    }
    return 0;
}

static int prepare_commit(dw4_property_folder *to,dw4_property_folder *updates)
{
    if(!to || !updates || to==updates || updates->alias_peer)return -1;
    igIntList *u=LV(updates->a,updates->list);size_t extra=0;
    for(int32_t i=0;u && i<u->_count;i++){
        int32_t p=elem(updates->a,u,(size_t)i),old=find(to,rec_name(updates->a,p));
        int pk=rec_kind(updates->a,p);
        if(pk==FOLDER || pk<0 || (old && rec_kind(to->a,old)!=pk))return -1;
        if(!old)extra++;
    }
    igIntList *t=LV(to->a,to->list);
    if(extra>0x7fffffffu-(size_t)t->_count)return -1;
    /* reserve the complete destination table before publishing any payload */
    return list_reserve(to->a,to->list,(size_t)t->_count+extra);
}
static void apply_commit(dw4_property_folder *to,dw4_property_folder *updates)
{
    igIntList *u=LV(updates->a,updates->list);
    for(int32_t i=0;u && i<u->_count;i++){
        int32_t p=elem(updates->a,u,(size_t)i),old=find(to,rec_name(updates->a,p));
        if(old){
            /* Keep destination keys when a common alias targets BASE_*; the update row owns the old payload, never the live key. */
            beDataObjInt *ro=R(to->a,old),*rp=R(updates->a,p);int32_t d=ro->_data;ro->_data=rp->_data;rp->_data=d;
        }else{
            list_append(to->a,to->list,p);   /* capacity was reserved */
            uint8_t *b=block(updates->a,u,4);int32_t zero=0;memcpy(b+4*(size_t)i,&zero,4);
        }
    }
    /* transferred rows leave the staging folder */
    size_t keep=0;uint8_t *b=block(updates->a,u,4);
    for(int32_t i=0;u && i<u->_count;i++){int32_t v=elem(updates->a,u,(size_t)i);if(v){memcpy(b+4*keep,&v,4);keep++;}}
    if(u)u->_count=(int32_t)keep;
}
int dw4_property_commit_values(dw4_property_folder *to,dw4_property_folder *updates)
{
    if(prepare_commit(to,updates))return -1;
    apply_commit(to,updates);return 0;
}
int dw4_property_commit_pair(dw4_property_folder *a,dw4_property_folder *sa,dw4_property_folder *b,dw4_property_folder *sb)
{
    if(!a || !b || !sa || !sb || a==b || a==sb || b==sa || sa==sb || a->alias_peer==b || b->alias_peer==a)return -1;
    if(prepare_commit(a,sa))return -1;
    if(prepare_commit(b,sb))return -1;
    apply_commit(a,sa);apply_commit(b,sb);return 0;
}

int dw4_playerrecords_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_playerrecords *p=user;int32_t player=0;
    if(!p || (strcmp(method,"sd") && strcmp(method,"querySD")) || n<4 || n>5 || a[3].type!=DW4_SCRIPT_STRING)goto bad;
    const char *key=a[3].string;
    if(!strcmp(key,"GETPLAYER") && n==5){
        if(a[4].type==DW4_SCRIPT_NUMBER){
            if(!isfinite(a[4].number) || floor(a[4].number)!=a[4].number || a[4].number<0 || a[4].number>3)goto bad;
            player=(int32_t)a[4].number;
        }else if(a[4].type==DW4_SCRIPT_STRING){
            const char *v=a[4].string;if(a[4].length!=4 || v[0]!='I' || v[1]!='<' || v[2]<'0' || v[2]>'3' || v[3]!='>')goto bad;
            player=v[2]-'0';
        }else goto bad;
    }else if(n!=4)goto bad;
    dw4_property_folder *f=dw4_playerrecords_get(p,key,player);if(!f)goto bad;
    unsigned index=f==&p->common?0:(unsigned)(f-p->player)+1;
    p->view[index]=(dw4_script_object){DW4_SCRIPT_PROPERTY_FOLDER,f,p};
    *r=dw4_script_object_value(&p->view[index]);return 0;
 bad:snprintf(error,cap,"GAMERAM requires GETCOMMON or GETPLAYER[1..4] with a valid player");return -1;
}

/* A destination starts against a private session image. Unlike copy_values,
 * this preserves nested folders and raw common rows before restoring aliases. */
static int snapshot_folder(dw4_property_folder *to,dw4_property_folder *from)
{
    igIntList *l=LV(from->a,from->list);
    for(int32_t i=0;l && i<l->_count;i++){
        int32_t rec=elem(from->a,l,(size_t)i);const char *name=rec_name(from->a,rec);int kind=rec_kind(from->a,rec);
        if(!name || kind<0 || copy_record(to,from,name,kind,rec,1))return -1;
    }
    return 0;
}
dw4_playerrecords *dw4_playerrecords_snapshot(const dw4_playerrecords *from)
{
    if(!from || (from->common.alias_peer && from->common.alias_peer!=from->player))return NULL;
    dw4_playerrecords *copy=dw4_playerrecords_open();if(!copy)return NULL;
    /* open() seeds the retail templates; the snapshot replaces every row with the source's, in the source's order */
    folder_release(copy->common.a,copy->common.list);folder_new(copy->common.a,&copy->common.list);
    for(unsigned i=0;i<4;i++){folder_release(copy->player[i].a,copy->player[i].list);folder_new(copy->player[i].a,&copy->player[i].list);}
    if(snapshot_folder(&copy->common,(dw4_property_folder *)&from->common))goto bad;
    for(unsigned i=0;i<4;i++)if(snapshot_folder(copy->player+i,(dw4_property_folder *)(from->player+i)))goto bad;
    copy->common.alias_peer=from->common.alias_peer?copy->player:NULL;
    /* Typed Lua identity views intentionally start empty in the new owner. */
    return copy;
bad:dw4_playerrecords_close(copy);return NULL;
}

/* Explicit retained reference closures for recovered owner fields. The property
 * owner releases its share on replacement; retained old payloads stay live until
 * their final holder releases them. Ordinary borrowed reads keep their old ABI. */
dw4_handle dw4_property_list_acquire(const dw4_property_folder *f,const char *key,dw4_property_type type)
{
    if(type==DW4_PROPERTY_NUMBER || type==DW4_PROPERTY_STRING)return (dw4_handle){0};
    dw4_property_ref r=dw4_property_reference(f,key,type);
    if(!r.record.off)return (dw4_handle){0};
    beDataObjInt *v=R(r.arena,(int32_t)r.record.off);dw4_handle h=H(v->_data);
    return h.off && dw4_arena_object_addref(r.arena,h)>0?h:(dw4_handle){0};
}
dw4_handle dw4_property_folder_acquire(const dw4_property_folder *f)
{
    if(!f || !f->list || dw4_arena_object_addref(f->a,H(f->list))<1)return (dw4_handle){0};
    return H(f->list);
}
void dw4_property_list_release(dw4_arena *a,dw4_handle h)
{
    if(!h.off)return;
    igObject *o=DW4_ARENA_OBJ(a,igObject,h);if(!o)return;
    uint32_t c=(uint32_t)o->_vtable;
    if(c==C.folder)folder_release(a,(int32_t)h.off);
    else if(c==C.int_list)value_release(a,ARRAY,(int32_t)h.off);
    else if(c==C.bool_list)value_release(a,BYTES,(int32_t)h.off);
    else if(c==C.float_list)value_release(a,FLOATS,(int32_t)h.off);
    else if(c==C.string_list)value_release(a,STRINGS,(int32_t)h.off);
    else if(c==C.item_list)value_release(a,ITEMS,(int32_t)h.off);
    else if(c==C.unicode_list)value_release(a,UNICODES,(int32_t)h.off);
    else dw4_arena_object_release(a,h); /* retained item leaf */
}
