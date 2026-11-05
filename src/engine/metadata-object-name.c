/* 0x002fddb0 igMetaObject_SetName: give a metaobject its (interned) class name.
 * The shared string pool is created on first use even for a null name; the new name
 * is interned first, then the metaobject's previous name token is released (token
 * reference count at -4, owning chunk at -8) and the interned token is published
 * (docs/engine/metadata-bootstrap.md, "Names and ownership"). */
#include "dw4/reflected.h"
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int,int);
int StringChunk_ReleaseHeader(int,void *);
/* Shared string pool singleton (finding #1035); array form keeps the load absolute. */
extern int g_stringPool_00586f20[4];
void igMetaObject_SetName(igMetaObject *meta, int name) {
    int pool, internedName, oldName, refCount;
    int *oldHeader;

    if (g_stringPool_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool_00586f20[0] = pool;
    }
    internedName = StringPool_Intern(g_stringPool_00586f20[0], name);
    oldName = meta->_name;
    if (oldName) {
        oldHeader = (int *)(oldName - 8);
        refCount = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader(*oldHeader, oldHeader);
        }
    }
    meta->_name = internedName;
}
