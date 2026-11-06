/* 0x00137150 igGeometryMaskAttr_Register: registers class igGeometryMaskAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igGeometryMaskAttr_GetVTable[];
extern char thunk_igGeometryMaskAttr_GetMetaObject[];
extern char igGeometryMaskAttr_className[];
extern char g_igGeometryMaskAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igGeometryMaskAttr_InitFields();

void igGeometryMaskAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryMaskAttr_metaObject,          /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGeometryMaskAttr_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igGeometryMaskAttr_className,           /* class name */
        0x10,                                              /* instance size */
        igGeometryMaskAttr_GetVTable,                      /* vtable getter */
        &igGeometryMaskAttr_InitFields,                    /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
