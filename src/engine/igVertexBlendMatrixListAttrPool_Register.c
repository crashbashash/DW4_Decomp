/* 0x00199f30 igVertexBlendMatrixListAttrPool_Register: registers class igVertexBlendMatrixListAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject[];
extern char igVertexBlendMatrixListAttrPool_GetVTable[];
extern char thunk_igVertexBlendMatrixListAttrPool_GetMetaObject[];
extern char g_igVertexBlendMatrixListAttrPool_callbackList[];
extern char igVertexBlendMatrixListAttrPool_className[];
extern char g_igVertexBlendMatrixListAttrPool_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igVertexBlendMatrixListAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendMatrixListAttrPool_metaObject, /* published MetaObject slot */
        igObjectPool_Register,                                 /* base class registrar */
        igObjectPool_GetPublishedMetaObject,          /* base class MetaObject accessor */
        thunk_igVertexBlendMatrixListAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVertexBlendMatrixListAttrPool_className,  /* class name */
        0x20,                                                  /* instance size */
        igVertexBlendMatrixListAttrPool_GetVTable,             /* vtable getter */
        0,                                                     /* field adder */
        0,                                                     /* extra callback item */
        g_igVertexBlendMatrixListAttrPool_callbackList  /* callback list */
    );
}
