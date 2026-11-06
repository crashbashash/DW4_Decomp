/* 0x0019a210 igProjectionMatrixAttrPool_Register: registers class igProjectionMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igProjectionMatrixAttrPool_GetVTable[];
extern char thunk_igProjectionMatrixAttrPool_GetMetaObject[];
extern char g_igProjectionMatrixAttrPool_callbackList[];
extern char igProjectionMatrixAttrPool_className[];
extern char g_igProjectionMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igProjectionMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProjectionMatrixAttrPool_metaObject, /* published MetaObject slot */
        igObjectPool_Register,                            /* base class registrar */
        igObjectPool_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igProjectionMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igProjectionMatrixAttrPool_className,  /* class name */
        0x20,                                             /* instance size */
        igProjectionMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                                /* field adder */
        0,                                                /* extra callback item */
        g_igProjectionMatrixAttrPool_callbackList  /* callback list */
    );
}
