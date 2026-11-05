/* 0x001387c0 igCullFaceAttr_Register: registers class igCullFaceAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igCullFaceAttr_GetVTable[];
extern char thunk_igCullFaceAttr_GetMetaObject[];
extern char s_igCullFaceAttr_className_004d57e8[];
extern char g_igCullFaceAttr_metaObject_0055f238[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igCullFaceAttr_InitFields();

void igCullFaceAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCullFaceAttr_metaObject_0055f238,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igCullFaceAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igCullFaceAttr_className_004d57e8,               /* class name */
        0x14,                                              /* instance size */
        igCullFaceAttr_GetVTable,                          /* vtable getter */
        &igCullFaceAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
