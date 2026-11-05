/* 0x001350a0 igNormalizeNormalsStateAttr_Register: registers class igNormalizeNormalsStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igNormalizeNormalsStateAttr_GetVTable[];
extern char thunk_igNormalizeNormalsStateAttr_GetMetaObject[];
extern char s_igNormalizeNormalsStateAttr_className_004d5320[];
extern char g_igNormalizeNormalsStateAttr_metaObject_0055efc0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igNormalizeNormalsStateAttr_InitFields();

void igNormalizeNormalsStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNormalizeNormalsStateAttr_metaObject_0055efc0, /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igNormalizeNormalsStateAttr_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igNormalizeNormalsStateAttr_className_004d5320,  /* class name */
        0x10,                                              /* instance size */
        igNormalizeNormalsStateAttr_GetVTable,             /* vtable getter */
        &igNormalizeNormalsStateAttr_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
