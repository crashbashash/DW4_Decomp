/* 0x00130d00 igVertexBlendMatrixAttr_Register: registers class igVertexBlendMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igVertexBlendMatrixAttr_GetVTable[];
extern char thunk_igVertexBlendMatrixAttr_GetMetaObject[];
extern char igVertexBlendMatrixAttr_className[];
extern char g_igVertexBlendMatrixAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igVertexBlendMatrixAttr_InitFields();

void igVertexBlendMatrixAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendMatrixAttr_metaObject,     /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVertexBlendMatrixAttr_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igVertexBlendMatrixAttr_className,      /* class name */
        0x50,                                              /* instance size */
        igVertexBlendMatrixAttr_GetVTable,                 /* vtable getter */
        &igVertexBlendMatrixAttr_InitFields,               /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
