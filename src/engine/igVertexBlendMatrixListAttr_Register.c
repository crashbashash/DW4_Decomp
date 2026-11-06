/* 0x00130a80 igVertexBlendMatrixListAttr_Register: registers class igVertexBlendMatrixListAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igVertexBlendMatrixListAttr_GetVTable[];
extern char thunk_igVertexBlendMatrixListAttr_GetMetaObject[];
extern char g_igVertexBlendMatrixListAttr_callbackList[];
extern char igVertexBlendMatrixListAttr_className[];
extern char g_igVertexBlendMatrixListAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igVertexBlendMatrixListAttr_InitFields();

void igVertexBlendMatrixListAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendMatrixListAttr_metaObject, /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVertexBlendMatrixListAttr_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVertexBlendMatrixListAttr_className,  /* class name */
        0x9C,                                              /* instance size */
        igVertexBlendMatrixListAttr_GetVTable,             /* vtable getter */
        &igVertexBlendMatrixListAttr_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        g_igVertexBlendMatrixListAttr_callbackList  /* callback list */
    );
}
