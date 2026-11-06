/* 0x00136ea0 igGeometrySetAttr_Register: registers class igGeometrySetAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igGeometrySetAttr_GetVTable[];
extern char thunk_igGeometrySetAttr_GetMetaObject[];
extern char g_igGeometrySetAttr_callbackList[];
extern char igGeometrySetAttr_className[];
extern char g_igGeometrySetAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igGeometrySetAttr_InitFields();

void igGeometrySetAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometrySetAttr_metaObject,           /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGeometrySetAttr_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igGeometrySetAttr_className,            /* class name */
        0x20,                                              /* instance size */
        igGeometrySetAttr_GetVTable,                       /* vtable getter */
        &igGeometrySetAttr_InitFields,                     /* field adder */
        0,                                                 /* extra callback item */
        g_igGeometrySetAttr_callbackList          /* callback list */
    );
}
