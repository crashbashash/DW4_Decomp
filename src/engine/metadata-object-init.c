/* 0x002fd820 igMetaObject_Init: reset a freshly constructed metaobject to its
 * defaults (docs/engine/metadata-bootstrap.md): version 1.0, persistent, required
 * alignment 4, declared size -1, every name, list, proxy and callback cleared.  It then
 * interns the empty string as the pool name, creating the shared string pool on first
 * use.  The object is assumed fresh: no previous lists are released. */
#include "dw4/reflected.h"
void *igObject_InitHeader(void *);
int FUN_002eb010(int);
int StringPool_Construct(int);
void *StringPool_Intern(int,int);
int StringChunk_ReleaseHeader(int,void *);
/* igMetaObject vtable (docs/engine/metadata-bootstrap.md, vtable 532bb0) and the
 * shared string pool singleton (finding #1035); array form keeps the load absolute. */
extern int g_igMetaObject_vtable[4],g_stringPool[4];
igMetaObject *igMetaObject_Init(igMetaObject *meta){
    int pool,oldName,refCount;int *oldHeader;void *emptyToken;
    igObject_InitHeader(meta);meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    meta->_metaFields=0;
    meta->_instances=0;
    meta->_children=0;
    meta->_parent=0;
    meta->_abstractProxy=0;
    meta->_writeProxy=0;
    meta->_templateObject=0;
    meta->_volatile=0;
    meta->_persistent=1;
    meta->_abstractState=0;
    meta->_majorVersion=1;
    meta->_minorVersion=0;
    meta->_index=0;
    meta->_id=0;
    meta->_metaFields=0;
    meta->_runTimeSize=0;
    meta->_instanceCount=0;
    meta->_validity=0;
    meta->_sizeofSize=-1;
    meta->_setupFunction=0;
    meta->_cleanupFunction=0;
    meta->_getMetaObjectFunction=0;
    meta->_requiredAlignment=4;
    meta->_vTablePointer=0;
    if(g_stringPool[0]==0){
        pool=FUN_002eb010(16);if(pool)pool=StringPool_Construct(pool);
        g_stringPool[0]=pool;
    }
    emptyToken=StringPool_Intern(g_stringPool[0],0);
    /* Drop the old pool-name token: owner chunk at -8, reference count at -4. */
    oldName=meta->_poolName;
    if(oldName){oldHeader=(int *)(oldName-8);refCount=*(int *)(oldName-4)-1;*(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader(*oldHeader,oldHeader);
    }
    meta->_poolName=(int)emptyToken;return meta;
}
