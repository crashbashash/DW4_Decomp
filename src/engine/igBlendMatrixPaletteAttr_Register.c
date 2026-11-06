/* 0x00139ac0 igBlendMatrixPaletteAttr_Register: registers class igBlendMatrixPaletteAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendMatrixPaletteAttr_GetVTable[];
extern char thunk_igBlendMatrixPaletteAttr_GetMetaObject[];
extern char igBlendMatrixPaletteAttr_className[];
extern char g_igBlendMatrixPaletteAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendMatrixPaletteAttr_InitFields();

void igBlendMatrixPaletteAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatrixPaletteAttr_metaObject,    /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBlendMatrixPaletteAttr_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igBlendMatrixPaletteAttr_className,     /* class name */
        0x1C,                                              /* instance size */
        igBlendMatrixPaletteAttr_GetVTable,                /* vtable getter */
        &igBlendMatrixPaletteAttr_InitFields,              /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
