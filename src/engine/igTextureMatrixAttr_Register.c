/* 0x00131900 igTextureMatrixAttr_Register: registers class igTextureMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTextureMatrixAttr_GetVTable[];
extern char thunk_igTextureMatrixAttr_GetMetaObject[];
extern char s_igTextureMatrixAttr_className_004d4c40[];
extern char g_igTextureMatrixAttr_metaObject_0055ecd8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureMatrixAttr_InitFields();

void igTextureMatrixAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureMatrixAttr_metaObject_0055ecd8,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTextureMatrixAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igTextureMatrixAttr_className_004d4c40,          /* class name */
        0x54,                                              /* instance size */
        igTextureMatrixAttr_GetVTable,                     /* vtable getter */
        &igTextureMatrixAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
