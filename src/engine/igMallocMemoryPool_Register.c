/* 0x002ce3d0 igMallocMemoryPool_Register: registers class igMallocMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igMallocMemoryPool_GetVTable[];
extern char thunk_igMallocMemoryPool_GetMetaObject[];
extern char g_igMallocMemoryPool_callbackList[];
extern char igMallocMemoryPool_className[];
extern char g_igMallocMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igMallocMemoryPool_InitFields();

void igMallocMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMallocMemoryPool_metaObject,     /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMallocMemoryPool_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igMallocMemoryPool_className,      /* class name */
        0xA0,                                         /* instance size */
        igMallocMemoryPool_GetVTable,                 /* vtable getter */
        &igMallocMemoryPool_InitFields,               /* field adder */
        0,                                            /* extra callback item */
        g_igMallocMemoryPool_callbackList    /* callback list */
    );
}
