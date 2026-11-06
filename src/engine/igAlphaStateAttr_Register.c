/* 0x0013b3a0 igAlphaStateAttr_Register: registers class igAlphaStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igAlphaStateAttr_GetVTable[];
extern char thunk_igAlphaStateAttr_GetMetaObject[];
extern char igAlphaStateAttr_className[];
extern char g_igAlphaStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAlphaStateAttr_InitFields();

void igAlphaStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAlphaStateAttr_metaObject,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAlphaStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igAlphaStateAttr_className,             /* class name */
        0x10,                                              /* instance size */
        igAlphaStateAttr_GetVTable,                        /* vtable getter */
        &igAlphaStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
