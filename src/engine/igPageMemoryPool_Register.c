/* 0x002cd7d0 igPageMemoryPool_Register: registers class igPageMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igMemoryPool_GetPublishedMetaObject_002cd480[];
extern char igPageMemoryPool_GetVTable[];
extern char thunk_igPageMemoryPool_GetMetaObject[];
extern char g_igPageMemoryPool_callbackList_004c16d0[];
extern char s_igPageMemoryPool_className_004f8a10[];
extern char g_igPageMemoryPool_metaObject_00586a30[];
int igMetaObject_RegisterClass();
int igPageMemoryPool_InitFields();

void igPageMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPageMemoryPool_metaObject_00586a30,       /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject_002cd480, /* base class MetaObject accessor */
        thunk_igPageMemoryPool_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPageMemoryPool_className_004f8a10,        /* class name */
        0x110,                                        /* instance size */
        igPageMemoryPool_GetVTable,                   /* vtable getter */
        &igPageMemoryPool_InitFields,                 /* field adder */
        0,                                            /* extra callback item */
        g_igPageMemoryPool_callbackList_004c16d0      /* callback list */
    );
}
