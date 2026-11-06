/* 0x00139450 igClearAttr_Register: registers class igClearAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igClearAttr_GetVTable[];
extern char thunk_igClearAttr_GetMetaObject[];
extern char igClearAttr_className[];
extern char g_igClearAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igClearAttr_InitFields();

void igClearAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igClearAttr_metaObject,                 /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igClearAttr_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        igClearAttr_className,                  /* class name */
        0x48,                                              /* instance size */
        igClearAttr_GetVTable,                             /* vtable getter */
        &igClearAttr_InitFields,                           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
