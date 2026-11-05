/* 0x00130840 igVertexBlendStateAttr_Register: registers class igVertexBlendStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igVertexBlendStateAttr_GetVTable[];
extern char thunk_igVertexBlendStateAttr_GetMetaObject[];
extern char s_igVertexBlendStateAttr_className_004d4a70[];
extern char g_igVertexBlendStateAttr_metaObject_0055ec18[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igVertexBlendStateAttr_InitFields();

void igVertexBlendStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendStateAttr_metaObject_0055ec18,      /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igVertexBlendStateAttr_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igVertexBlendStateAttr_className_004d4a70,       /* class name */
        0x10,                                              /* instance size */
        igVertexBlendStateAttr_GetVTable,                  /* vtable getter */
        &igVertexBlendStateAttr_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
