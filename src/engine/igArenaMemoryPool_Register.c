/* 0x002cdd00 igArenaMemoryPool_Register: registers class igArenaMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char thunk_igArenaMemoryPool_GetMetaObject[];
extern char igMemoryPool_GetPublishedMetaObject_002cd480[];
extern char igArenaMemoryPool_GetVTable[];
extern char g_igArenaMemoryPool_callbackList_004c1800[];
extern char s_igArenaMemoryPool_className_004f8b50[];
extern char g_igArenaMemoryPool_metaObject_00586a88[];
int igMetaObject_RegisterClass();
int igArenaMemoryPool_InitFields();

void igArenaMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igArenaMemoryPool_metaObject_00586a88,      /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject_002cd480, /* base class MetaObject accessor */
        thunk_igArenaMemoryPool_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igArenaMemoryPool_className_004f8b50,       /* class name */
        0xD0,                                         /* instance size */
        igArenaMemoryPool_GetVTable,                  /* vtable getter */
        &igArenaMemoryPool_InitFields,                /* field adder */
        0,                                            /* extra callback item */
        g_igArenaMemoryPool_callbackList_004c1800     /* callback list */
    );
}
