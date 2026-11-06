/* 0x00131900 igTextureMatrixAttr_Register: registers class igTextureMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureMatrixAttr_GetVTable[];
extern char thunk_igTextureMatrixAttr_GetMetaObject[];
extern char igTextureMatrixAttr_className[];
extern char g_igTextureMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureMatrixAttr_InitFields();

void igTextureMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureMatrixAttr_metaObject,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureMatrixAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igTextureMatrixAttr_className,          /* class name */
        0x54,                                              /* instance size */
        igTextureMatrixAttr_GetVTable,                     /* vtable getter */
        &igTextureMatrixAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
