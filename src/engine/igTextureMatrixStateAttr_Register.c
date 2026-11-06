/* 0x001316b0 igTextureMatrixStateAttr_Register: registers class igTextureMatrixStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureMatrixStateAttr_GetVTable[];
extern char thunk_igTextureMatrixStateAttr_GetMetaObject[];
extern char igTextureMatrixStateAttr_className[];
extern char g_igTextureMatrixStateAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igTextureMatrixStateAttr_InitFields();

void igTextureMatrixStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureMatrixStateAttr_metaObject,    /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureMatrixStateAttr_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igTextureMatrixStateAttr_className,     /* class name */
        0x14,                                              /* instance size */
        igTextureMatrixStateAttr_GetVTable,                /* vtable getter */
        &igTextureMatrixStateAttr_InitFields,              /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
