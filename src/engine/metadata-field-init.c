/* 0x002fbfe0 igMetaField_Init: reset a freshly constructed field descriptor to its
 * defaults (docs/engine/field-factories.md, finding #880).  Every member starts
 * cleared, the type index is -1, and the descriptor is persistent.  The
 * name slot is then given the interned empty token: the shared string pool is created
 * on first use, the previous name token (none for a fresh object) has its reference
 * count dropped, and the pool's token replaces it. */
#include "dw4/reflected.h"
void *igObject_InitHeader(void *);
int FUN_002eb010(int);
int StringPool_Construct(int);
void *StringPool_Intern(int,int);
int StringChunk_ReleaseHeader(int,void *);
/* igMetaField vtable (docs: stamped at +0 by igMetaField_Construct) and the shared
 * string pool singleton (finding #1035); array form keeps the load absolute. */
extern int g_igMetaField_vtable[4];
extern int g_stringPool[4];
igMetaField *igMetaField_Init(igMetaField *field){
    int pool;
    void *emptyToken;
    int oldName,refCount;
    int *oldHeader;
    igObject_InitHeader(field);
    field->_vtable=(int)g_igMetaField_vtable;
    field->_fieldName=0;
    field->_offset=0;
    field->_isRunTime=0;
    field->_typeIndex=-1;
    field->_internalIndex=0;
    field->_size=0;
    field->_default=0;
    field->_externalEnumStorage=0;
    if(g_stringPool[0]==0){
        pool=FUN_002eb010(16);
        if(pool)pool=StringPool_Construct(pool);
        g_stringPool[0]=pool;
    }
    emptyToken=StringPool_Intern(g_stringPool[0],0);
    /* Interned strings carry a header in front of the characters: owner chunk at -8,
     * reference count at -4 (docs/engine/messenger-results.md). */
    oldName=field->_fieldName;
    if(oldName){
        oldHeader=(int *)(oldName-8);
        refCount=*(int *)(oldName-4)-1;
        *(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader(*oldHeader,oldHeader);
    }
    field->_fieldName=(int)emptyToken;
    field->_parentMetaObject=0;
    field->_invarianceFunction=0;
    field->_resetMethod=0;
    field->_shallowCopyMethod=0;
    field->_deepCopyMethod=0;
    field->_constructCopyMethod=0;
    field->_isAlikeExactlyMethod=0;
    /* Method selector codes: the three comparison kinds default to 0, 1 and 2. */
    field->_isAlikeDeepMethod=1;
    field->_isAlikeShallowMethod=2;
    field->_persistent=1;
    return field;
}
