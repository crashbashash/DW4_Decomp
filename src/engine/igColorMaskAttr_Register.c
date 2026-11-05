/* 0x00138d90 igColorMaskAttr_Register: registers class igColorMaskAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igColorMaskAttr_GetVTable[];
extern char thunk_igColorMaskAttr_GetMetaObject[];
extern char s_igColorMaskAttr_className_004d5970[];
extern char g_igColorMaskAttr_metaObject_0055f2b0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igColorMaskAttr_InitFields();

void igColorMaskAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igColorMaskAttr_metaObject_0055f2b0,             /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igColorMaskAttr_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        s_igColorMaskAttr_className_004d5970,              /* class name */
        0x14,                                              /* instance size */
        igColorMaskAttr_GetVTable,                         /* vtable getter */
        &igColorMaskAttr_InitFields,                       /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
