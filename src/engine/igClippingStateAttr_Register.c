/* 0x00139260 igClippingStateAttr_Register: registers class igClippingStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igClippingStateAttr_GetVTable[];
extern char thunk_igClippingStateAttr_GetMetaObject[];
extern char igClippingStateAttr_className[];
extern char g_igClippingStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igClippingStateAttr_InitFields();

void igClippingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igClippingStateAttr_metaObject,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igClippingStateAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igClippingStateAttr_className,          /* class name */
        0x10,                                              /* instance size */
        igClippingStateAttr_GetVTable,                     /* vtable getter */
        &igClippingStateAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
