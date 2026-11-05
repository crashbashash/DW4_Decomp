/* 0x00139ac0 igBlendMatrixPaletteAttr_Register: registers class igBlendMatrixPaletteAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igBlendMatrixPaletteAttr_GetVTable[];
extern char thunk_igBlendMatrixPaletteAttr_GetMetaObject[];
extern char s_igBlendMatrixPaletteAttr_className_004d5a60[];
extern char g_igBlendMatrixPaletteAttr_metaObject_0055f360[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igBlendMatrixPaletteAttr_InitFields();

void igBlendMatrixPaletteAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatrixPaletteAttr_metaObject_0055f360,    /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igBlendMatrixPaletteAttr_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igBlendMatrixPaletteAttr_className_004d5a60,     /* class name */
        0x1C,                                              /* instance size */
        igBlendMatrixPaletteAttr_GetVTable,                /* vtable getter */
        &igBlendMatrixPaletteAttr_InitFields,              /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
