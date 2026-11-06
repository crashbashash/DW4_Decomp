/* 0x00139010 igColorAttr_Register: registers class igColorAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igColorAttr_GetVTable[];
extern char thunk_igColorAttr_GetMetaObject[];
extern char igColorAttr_className[];
extern char g_igColorAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igColorAttr_InitFields();

void igColorAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igColorAttr_metaObject,                 /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igColorAttr_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        igColorAttr_className,                  /* class name */
        0x20,                                              /* instance size */
        igColorAttr_GetVTable,                             /* vtable getter */
        &igColorAttr_InitFields,                           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
