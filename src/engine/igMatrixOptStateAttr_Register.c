/* 0x00135ad0 igMatrixOptStateAttr_Register: registers class igMatrixOptStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igMatrixOptStateAttr_GetVTable[];
extern char thunk_igMatrixOptStateAttr_GetMetaObject[];
extern char s_igMatrixOptStateAttr_className_004d53b0[];
extern char g_igMatrixOptStateAttr_metaObject_0055f000[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igMatrixOptStateAttr_InitFields();

void igMatrixOptStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixOptStateAttr_metaObject_0055f000,        /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igMatrixOptStateAttr_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igMatrixOptStateAttr_className_004d53b0,         /* class name */
        0x10,                                              /* instance size */
        igMatrixOptStateAttr_GetVTable,                    /* vtable getter */
        &igMatrixOptStateAttr_InitFields,                  /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
