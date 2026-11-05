/* 0x002ce3d0 igMallocMemoryPool_Register: registers class igMallocMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject_002cd480[];
extern char igMallocMemoryPool_GetVTable[];
extern char thunk_igMallocMemoryPool_GetMetaObject[];
extern char g_igMallocMemoryPool_callbackList_004c1a30[];
extern char s_igMallocMemoryPool_className_004f8c80[];
extern char g_igMallocMemoryPool_metaObject_00586b80[];
int igMetaObject_RegisterClass();
int igMallocMemoryPool_InitFields();

void igMallocMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMallocMemoryPool_metaObject_00586b80,     /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject_002cd480, /* base class MetaObject accessor */
        thunk_igMallocMemoryPool_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMallocMemoryPool_className_004f8c80,      /* class name */
        0xA0,                                         /* instance size */
        igMallocMemoryPool_GetVTable,                 /* vtable getter */
        &igMallocMemoryPool_InitFields,               /* field adder */
        0,                                            /* extra callback item */
        g_igMallocMemoryPool_callbackList_004c1a30    /* callback list */
    );
}
