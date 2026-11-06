/* 0x002cdd00 igArenaMemoryPool_Register: registers class igArenaMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char thunk_igArenaMemoryPool_GetMetaObject[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igArenaMemoryPool_GetVTable[];
extern char g_igArenaMemoryPool_callbackList[];
extern char igArenaMemoryPool_className[];
extern char g_igArenaMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igArenaMemoryPool_InitFields();

void igArenaMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igArenaMemoryPool_metaObject,      /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igArenaMemoryPool_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igArenaMemoryPool_className,       /* class name */
        0xD0,                                         /* instance size */
        igArenaMemoryPool_GetVTable,                  /* vtable getter */
        &igArenaMemoryPool_InitFields,                /* field adder */
        0,                                            /* extra callback item */
        g_igArenaMemoryPool_callbackList     /* callback list */
    );
}
