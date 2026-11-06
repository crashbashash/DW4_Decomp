/* 0x00138580 igDepthStateAttr_Register: registers class igDepthStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igDepthStateAttr_GetVTable[];
extern char thunk_igDepthStateAttr_GetMetaObject[];
extern char igDepthStateAttr_className[];
extern char g_igDepthStateAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igDepthStateAttr_InitFields();

void igDepthStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDepthStateAttr_metaObject,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDepthStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igDepthStateAttr_className,             /* class name */
        0x10,                                              /* instance size */
        igDepthStateAttr_GetVTable,                        /* vtable getter */
        &igDepthStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
