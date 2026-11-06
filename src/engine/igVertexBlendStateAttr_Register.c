/* 0x00130840 igVertexBlendStateAttr_Register: registers class igVertexBlendStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igVertexBlendStateAttr_GetVTable[];
extern char thunk_igVertexBlendStateAttr_GetMetaObject[];
extern char igVertexBlendStateAttr_className[];
extern char g_igVertexBlendStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igVertexBlendStateAttr_InitFields();

void igVertexBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexBlendStateAttr_metaObject,      /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igVertexBlendStateAttr_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igVertexBlendStateAttr_className,       /* class name */
        0x10,                                              /* instance size */
        igVertexBlendStateAttr_GetVTable,                  /* vtable getter */
        &igVertexBlendStateAttr_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
