/* 0x00139cf0 igBlendMatricesAttr_Register: registers class igBlendMatricesAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendMatricesAttr_GetVTable[];
extern char thunk_igBlendMatricesAttr_GetMetaObject[];
extern char igBlendMatricesAttr_className[];
extern char g_igBlendMatricesAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igBlendMatricesAttr_InitFields();

void igBlendMatricesAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBlendMatricesAttr_metaObject,         /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBlendMatricesAttr_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igBlendMatricesAttr_className,          /* class name */
        0x18,                                              /* instance size */
        igBlendMatricesAttr_GetVTable,                     /* vtable getter */
        &igBlendMatricesAttr_InitFields,                   /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
