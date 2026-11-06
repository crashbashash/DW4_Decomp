/* 0x00135c80 igMaterialAttr_Register: registers class igMaterialAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igMaterialAttr_GetVTable[];
extern char thunk_igMaterialAttr_GetMetaObject[];
extern char igMaterialAttr_className[];
extern char g_igMaterialAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMaterialAttr_InitFields();

void igMaterialAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMaterialAttr_metaObject,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMaterialAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igMaterialAttr_className,               /* class name */
        0x54,                                              /* instance size */
        igMaterialAttr_GetVTable,                          /* vtable getter */
        &igMaterialAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
