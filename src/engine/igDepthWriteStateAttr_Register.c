/* 0x00138390 igDepthWriteStateAttr_Register: registers class igDepthWriteStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igDepthWriteStateAttr_GetVTable[];
extern char thunk_igDepthWriteStateAttr_GetMetaObject[];
extern char igDepthWriteStateAttr_className[];
extern char g_igDepthWriteStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDepthWriteStateAttr_InitFields();

void igDepthWriteStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDepthWriteStateAttr_metaObject,       /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDepthWriteStateAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igDepthWriteStateAttr_className,        /* class name */
        0x10,                                              /* instance size */
        igDepthWriteStateAttr_GetVTable,                   /* vtable getter */
        &igDepthWriteStateAttr_InitFields,                 /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
