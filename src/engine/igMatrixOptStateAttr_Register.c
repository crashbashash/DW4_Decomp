/* 0x00135ad0 igMatrixOptStateAttr_Register: registers class igMatrixOptStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igMatrixOptStateAttr_GetVTable[];
extern char thunk_igMatrixOptStateAttr_GetMetaObject[];
extern char igMatrixOptStateAttr_className[];
extern char g_igMatrixOptStateAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igMatrixOptStateAttr_InitFields();

void igMatrixOptStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixOptStateAttr_metaObject,        /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMatrixOptStateAttr_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igMatrixOptStateAttr_className,         /* class name */
        0x10,                                              /* instance size */
        igMatrixOptStateAttr_GetVTable,                    /* vtable getter */
        &igMatrixOptStateAttr_InitFields,                  /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
