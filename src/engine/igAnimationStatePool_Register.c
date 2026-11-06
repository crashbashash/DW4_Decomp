/* 0x001a68a0 igAnimationStatePool_Register: registers class igAnimationStatePool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igAnimationStatePool_GetVTable[];
extern char thunk_igAnimationStatePool_GetMetaObject[];
extern char g_igAnimationStatePool_callbackList[];
extern char igAnimationStatePool_className[];
extern char g_igAnimationStatePool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationStatePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationStatePool_metaObject,   /* published MetaObject slot */
        igObjectPool_Register,                        /* base class registrar */
        igObjectPool_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAnimationStatePool_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igAnimationStatePool_className,    /* class name */
        0x20,                                         /* instance size */
        igAnimationStatePool_GetVTable,               /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igAnimationStatePool_callbackList  /* callback list */
    );
}
