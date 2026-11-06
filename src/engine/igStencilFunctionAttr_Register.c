/* 0x001336f0 igStencilFunctionAttr_Register: registers class igStencilFunctionAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igStencilFunctionAttr_GetVTable[];
extern char thunk_igStencilFunctionAttr_GetMetaObject[];
extern char igStencilFunctionAttr_className[];
extern char g_igStencilFunctionAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igStencilFunctionAttr_InitFields();

void igStencilFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStencilFunctionAttr_metaObject,       /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStencilFunctionAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igStencilFunctionAttr_className,        /* class name */
        0x28,                                              /* instance size */
        igStencilFunctionAttr_GetVTable,                   /* vtable getter */
        &igStencilFunctionAttr_InitFields,                 /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
