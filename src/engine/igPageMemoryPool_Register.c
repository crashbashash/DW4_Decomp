/* 0x002cd7d0 igPageMemoryPool_Register: registers class igPageMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char igPageMemoryPool_GetVTable[];
extern char thunk_igPageMemoryPool_GetMetaObject[];
extern char g_igPageMemoryPool_callbackList[];
extern char igPageMemoryPool_className[];
extern char g_igPageMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igPageMemoryPool_InitFields();

void igPageMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPageMemoryPool_metaObject,       /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPageMemoryPool_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPageMemoryPool_className,        /* class name */
        0x110,                                        /* instance size */
        igPageMemoryPool_GetVTable,                   /* vtable getter */
        &igPageMemoryPool_InitFields,                 /* field adder */
        0,                                            /* extra callback item */
        g_igPageMemoryPool_callbackList      /* callback list */
    );
}
