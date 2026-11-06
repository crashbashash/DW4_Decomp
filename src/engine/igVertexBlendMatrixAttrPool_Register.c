/* 0x0019a0a0 igVertexBlendMatrixAttrPool_Register: registers class igVertexBlendMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igVertexBlendMatrixAttrPool_GetVTable[];
extern char thunk_igVertexBlendMatrixAttrPool_GetMetaObject[];
extern char g_igVertexBlendMatrixAttrPool_callbackList[];
extern char igVertexBlendMatrixAttrPool_className[];
extern char g_igVertexBlendMatrixAttrPool_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igVertexBlendMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendMatrixAttrPool_metaObject, /* published MetaObject slot */
        igObjectPool_Register,                             /* base class registrar */
        igObjectPool_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igVertexBlendMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVertexBlendMatrixAttrPool_className,  /* class name */
        0x20,                                              /* instance size */
        igVertexBlendMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                                 /* field adder */
        0,                                                 /* extra callback item */
        g_igVertexBlendMatrixAttrPool_callbackList  /* callback list */
    );
}
