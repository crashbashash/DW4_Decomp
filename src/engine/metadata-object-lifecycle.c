/* igMetaObject lifecycle: construction, copy-construction, list release and
 * registry index assignment (0x002d3060 and the 0x002fd8xx-0x002fe7xx run).
 * Behaviour is documented in docs/engine/metadata-bootstrap.md; the metadata
 * member offsets come from reflection (include/dw4/reflected.h). */
#include "dw4/reflected.h"

/* The object system whose pointer lives at 0x00586dc8: only the metadata
 * registry (a pointer list of every registered igMetaObject, +24) is used. */
typedef struct ObjectSystemRecord {
    char unknown0[24];
    int metaRegistry;
} ObjectSystemRecord;

void *igObject_ConstructHeader(void *);
void *igObject_CopyConstructHeader(void *,void *);
igMetaObject *igMetaObject_Init(igMetaObject *);
int InternalObjectList_Create(int);
void igObject_Destroy(void *);
int ObjectPointerList_FindIndex(int,igMetaObject *);
void MetaRefList_AppendRetained(void *,void *);
void igObjectSystem_AppendMetaObject(void *,igMetaObject *);
/* igMetaObject's vtable (RTTI-named; docs/engine/rtti-and-vtables.md). */
extern int g_igMetaObject_vtable_00532bb0[4];
extern void *g_objectSystem_00586dc8[4];

/* Register a metaobject in the object system's registry, retaining it. */
void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta){
    MetaRefList_AppendRetained((void *)((ObjectSystemRecord *)system)->metaRegistry,meta);
}

/* Construct a metaobject: base header, igMetaObject vtable, no name or pool
 * name, and an empty field list. */
void *igMetaObject_Construct(igMetaObject *meta){
    igObject_ConstructHeader(meta);
    meta->_vtable=(int)g_igMetaObject_vtable_00532bb0;
    meta->_name=0;
    meta->_poolName=0;
    if(meta)igMetaObject_Init(meta);
    meta->_metaFields=InternalObjectList_Create(0);
    return meta;
}

/* Copy-construct: base header copy, vtable stamp and cleared names; the other
 * metadata members are not copied here. */
void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source){
    igObject_CopyConstructHeader(meta,source);
    meta->_vtable=(int)g_igMetaObject_vtable_00532bb0;
    meta->_name=0;
    meta->_poolName=0;
    return meta;
}

/* Drop the field list and then the child list: decrement the reference count
 * and destroy the list once its 23 low count bits reach zero.  The member cells
 * are left untouched. */
void igMetaObject_ReleaseLists(igMetaObject *meta){
    igObject *list=(igObject *)meta->_metaFields;
    if(list){
        --list->_refCount;
        if(!(list->_refCount&0x7fffff))igObject_Destroy(list);
    }
    list=(igObject *)meta->_children;
    if(list){
        --list->_refCount;
        if(!(list->_refCount&0x7fffff))igObject_Destroy(list);
    }
}

/* Give the metaobject its registry index (_index): search the object system's
 * registry; when absent (-1) append it and search again, since appending can
 * replace the registry (docs/engine/metadata-bootstrap.md, "Registry index
 * assignment"). */
void igMetaObject_AssignTypeId(igMetaObject *meta){
    meta->_index=ObjectPointerList_FindIndex(((ObjectSystemRecord *)g_objectSystem_00586dc8[0])->metaRegistry,meta);
    if(meta->_index==-1){
        igObjectSystem_AppendMetaObject(g_objectSystem_00586dc8[0],meta);
        meta->_index=ObjectPointerList_FindIndex(((ObjectSystemRecord *)g_objectSystem_00586dc8[0])->metaRegistry,meta);
    }
}
