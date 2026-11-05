/* 0x00138390 igDepthWriteStateAttr_Register: registers class igDepthWriteStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igDepthWriteStateAttr_GetVTable[];
extern char thunk_igDepthWriteStateAttr_GetMetaObject[];
extern char s_igDepthWriteStateAttr_className_004d57b0[];
extern char g_igDepthWriteStateAttr_metaObject_0055f218[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igDepthWriteStateAttr_InitFields();

void igDepthWriteStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDepthWriteStateAttr_metaObject_0055f218,       /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igDepthWriteStateAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igDepthWriteStateAttr_className_004d57b0,        /* class name */
        0x10,                                              /* instance size */
        igDepthWriteStateAttr_GetVTable,                   /* vtable getter */
        &igDepthWriteStateAttr_InitFields,                 /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
