/* 0x0019a0a0 igVertexBlendMatrixAttrPool_Register: registers class igVertexBlendMatrixAttrPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igVertexBlendMatrixAttrPool_GetVTable[];
extern char thunk_igVertexBlendMatrixAttrPool_GetMetaObject[];
extern char g_igVertexBlendMatrixAttrPool_callbackList_0048b730[];
extern char s_igVertexBlendMatrixAttrPool_className_004e1d60[];
extern char g_igVertexBlendMatrixAttrPool_metaObject_005615a0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igVertexBlendMatrixAttrPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendMatrixAttrPool_metaObject_005615a0, /* published MetaObject slot */
        igObjectPool_Register,                             /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0,      /* base class MetaObject accessor */
        thunk_igVertexBlendMatrixAttrPool_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igVertexBlendMatrixAttrPool_className_004e1d60,  /* class name */
        0x20,                                              /* instance size */
        igVertexBlendMatrixAttrPool_GetVTable,             /* vtable getter */
        0,                                                 /* field adder */
        0,                                                 /* extra callback item */
        g_igVertexBlendMatrixAttrPool_callbackList_0048b730  /* callback list */
    );
}
