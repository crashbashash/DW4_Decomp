/* 0x001347d0 igProjectionMatrixAttr_Register: registers class igProjectionMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igProjectionMatrixAttr_GetVTable[];
extern char thunk_igProjectionMatrixAttr_GetMetaObject[];
extern char igProjectionMatrixAttr_className[];
extern char g_igProjectionMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igProjectionMatrixAttr_InitFields();

void igProjectionMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igProjectionMatrixAttr_metaObject,      /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igProjectionMatrixAttr_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igProjectionMatrixAttr_className,       /* class name */
        0x4C,                                              /* instance size */
        igProjectionMatrixAttr_GetVTable,                  /* vtable getter */
        &igProjectionMatrixAttr_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
