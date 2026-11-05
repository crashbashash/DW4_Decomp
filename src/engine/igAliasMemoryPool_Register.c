/* 0x002cd400 igAliasMemoryPool_Register: registers class igAliasMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igAliasMemoryPool_GetVTable[];
extern char thunk_igAliasMemoryPool_GetMetaObject[];
extern char igMemoryPool_GetPublishedMetaObject_002cd480[];
extern char g_igAliasMemoryPool_callbackList_004c15a0[];
extern char s_igAliasMemoryPool_className_004f8830[];
extern char g_igAliasMemoryPool_metaObject_005869b0[];
int igMetaObject_RegisterClass();
int igAliasMemoryPool_InitFields();

void igAliasMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAliasMemoryPool_metaObject_005869b0,      /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject_002cd480, /* base class MetaObject accessor */
        thunk_igAliasMemoryPool_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igAliasMemoryPool_className_004f8830,       /* class name */
        0xB8,                                         /* instance size */
        igAliasMemoryPool_GetVTable,                  /* vtable getter */
        &igAliasMemoryPool_InitFields,                /* field adder */
        0,                                            /* extra callback item */
        g_igAliasMemoryPool_callbackList_004c15a0     /* callback list */
    );
}
