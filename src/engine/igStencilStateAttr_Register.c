/* 0x00133520 igStencilStateAttr_Register: registers class igStencilStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igStencilStateAttr_GetVTable[];
extern char thunk_igStencilStateAttr_GetMetaObject[];
extern char igStencilStateAttr_className[];
extern char g_igStencilStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igStencilStateAttr_InitFields();

void igStencilStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStencilStateAttr_metaObject,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStencilStateAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igStencilStateAttr_className,           /* class name */
        0x10,                                              /* instance size */
        igStencilStateAttr_GetVTable,                      /* vtable getter */
        &igStencilStateAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
