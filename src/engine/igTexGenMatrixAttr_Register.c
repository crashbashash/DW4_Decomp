/* 0x001332a0 igTexGenMatrixAttr_Register: registers class igTexGenMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTexGenMatrixAttr_GetVTable[];
extern char thunk_igTexGenMatrixAttr_GetMetaObject[];
extern char igTexGenMatrixAttr_className[];
extern char g_igTexGenMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTexGenMatrixAttr_InitFields();

void igTexGenMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTexGenMatrixAttr_metaObject,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTexGenMatrixAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igTexGenMatrixAttr_className,           /* class name */
        0x50,                                              /* instance size */
        igTexGenMatrixAttr_GetVTable,                      /* vtable getter */
        &igTexGenMatrixAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
