/* 0x00137150 igGeometryMaskAttr_Register: registers class igGeometryMaskAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igGeometryMaskAttr_GetVTable[];
extern char thunk_igGeometryMaskAttr_GetMetaObject[];
extern char s_igGeometryMaskAttr_className_004d5660[];
extern char g_igGeometryMaskAttr_metaObject_0055f148[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igGeometryMaskAttr_InitFields();

void igGeometryMaskAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryMaskAttr_metaObject_0055f148,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igGeometryMaskAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igGeometryMaskAttr_className_004d5660,           /* class name */
        0x10,                                              /* instance size */
        igGeometryMaskAttr_GetVTable,                      /* vtable getter */
        &igGeometryMaskAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
