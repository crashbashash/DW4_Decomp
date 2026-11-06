/* 0x00138d90 igColorMaskAttr_Register: registers class igColorMaskAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igColorMaskAttr_GetVTable[];
extern char thunk_igColorMaskAttr_GetMetaObject[];
extern char igColorMaskAttr_className[];
extern char g_igColorMaskAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igColorMaskAttr_InitFields();

void igColorMaskAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igColorMaskAttr_metaObject,             /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igColorMaskAttr_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igColorMaskAttr_className,              /* class name */
        0x14,                                              /* instance size */
        igColorMaskAttr_GetVTable,                         /* vtable getter */
        &igColorMaskAttr_InitFields,                       /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
