/* 0x002cd400 igAliasMemoryPool_Register: registers class igAliasMemoryPool with the object system, derived from igMemoryPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMemoryPool_Register[];
extern char igAliasMemoryPool_GetVTable[];
extern char thunk_igAliasMemoryPool_GetMetaObject[];
extern char igMemoryPool_GetPublishedMetaObject[];
extern char g_igAliasMemoryPool_callbackList[];
extern char igAliasMemoryPool_className[];
extern char g_igAliasMemoryPool_metaObject[];
int igMetaObject_RegisterClass();
int igAliasMemoryPool_InitFields();

void igAliasMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAliasMemoryPool_metaObject,      /* published MetaObject slot */
        igMemoryPool_Register,                        /* base class registrar */
        igMemoryPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAliasMemoryPool_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igAliasMemoryPool_className,       /* class name */
        0xB8,                                         /* instance size */
        igAliasMemoryPool_GetVTable,                  /* vtable getter */
        &igAliasMemoryPool_InitFields,                /* field adder */
        0,                                            /* extra callback item */
        g_igAliasMemoryPool_callbackList     /* callback list */
    );
}
