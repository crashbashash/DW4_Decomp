/* 0x00199ae0 igBlendMatricesAttrPool_Register: registers class igBlendMatricesAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igBlendMatricesAttrPool_GetVTable[];
extern char thunk_igBlendMatricesAttrPool_GetMetaObject[];
extern char g_igBlendMatricesAttrPool_callbackList[];
extern char igBlendMatricesAttrPool_className[];
extern char g_igBlendMatricesAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igBlendMatricesAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatricesAttrPool_metaObject, /* published MetaObject slot */
        igObjectPool_Register,                         /* base class registrar */
        igObjectPool_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igBlendMatricesAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igBlendMatricesAttrPool_className,  /* class name */
        0x20,                                          /* instance size */
        igBlendMatricesAttrPool_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igBlendMatricesAttrPool_callbackList  /* callback list */
    );
}
