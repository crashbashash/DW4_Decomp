/* 0x00199c50 igTextureMatrixAttrPool_Register: registers class igTextureMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igTextureMatrixAttrPool_GetVTable[];
extern char thunk_igTextureMatrixAttrPool_GetMetaObject[];
extern char g_igTextureMatrixAttrPool_callbackList[];
extern char igTextureMatrixAttrPool_className[];
extern char g_igTextureMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTextureMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureMatrixAttrPool_metaObject, /* published MetaObject slot */
        igObjectPool_Register,                         /* base class registrar */
        igObjectPool_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igTextureMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igTextureMatrixAttrPool_className,  /* class name */
        0x20,                                          /* instance size */
        igTextureMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igTextureMatrixAttrPool_callbackList  /* callback list */
    );
}
