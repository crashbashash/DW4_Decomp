/* 0x00133a40 igShadeModelAttr_Register: registers class igShadeModelAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igShadeModelAttr_GetVTable[];
extern char thunk_igShadeModelAttr_GetMetaObject[];
extern char igShadeModelAttr_className[];
extern char g_igShadeModelAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igShadeModelAttr_InitFields();

void igShadeModelAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShadeModelAttr_metaObject,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igShadeModelAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igShadeModelAttr_className,             /* class name */
        0x10,                                              /* instance size */
        igShadeModelAttr_GetVTable,                        /* vtable getter */
        &igShadeModelAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
