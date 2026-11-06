/* 0x001350a0 igNormalizeNormalsStateAttr_Register: registers class igNormalizeNormalsStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igNormalizeNormalsStateAttr_GetVTable[];
extern char thunk_igNormalizeNormalsStateAttr_GetMetaObject[];
extern char igNormalizeNormalsStateAttr_className[];
extern char g_igNormalizeNormalsStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igNormalizeNormalsStateAttr_InitFields();

void igNormalizeNormalsStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNormalizeNormalsStateAttr_metaObject, /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNormalizeNormalsStateAttr_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igNormalizeNormalsStateAttr_className,  /* class name */
        0x10,                                              /* instance size */
        igNormalizeNormalsStateAttr_GetVTable,             /* vtable getter */
        &igNormalizeNormalsStateAttr_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
