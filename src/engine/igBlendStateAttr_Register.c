/* 0x00139730 igBlendStateAttr_Register: registers class igBlendStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendStateAttr_GetVTable[];
extern char thunk_igBlendStateAttr_GetMetaObject[];
extern char igBlendStateAttr_className[];
extern char g_igBlendStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendStateAttr_InitFields();

void igBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendStateAttr_metaObject,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBlendStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igBlendStateAttr_className,             /* class name */
        0x10,                                              /* instance size */
        igBlendStateAttr_GetVTable,                        /* vtable getter */
        &igBlendStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
