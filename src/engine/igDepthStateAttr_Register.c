/* 0x00138580 igDepthStateAttr_Register: registers class igDepthStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igDepthStateAttr_GetVTable[];
extern char thunk_igDepthStateAttr_GetMetaObject[];
extern char s_igDepthStateAttr_className_004d57d0[];
extern char g_igDepthStateAttr_metaObject_0055f228[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igDepthStateAttr_InitFields();

void igDepthStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDepthStateAttr_metaObject_0055f228,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igDepthStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igDepthStateAttr_className_004d57d0,             /* class name */
        0x10,                                              /* instance size */
        igDepthStateAttr_GetVTable,                        /* vtable getter */
        &igDepthStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
