/* 0x00136ea0 igGeometrySetAttr_Register: registers class igGeometrySetAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igGeometrySetAttr_GetVTable[];
extern char thunk_igGeometrySetAttr_GetMetaObject[];
extern char g_igGeometrySetAttr_callbackList_00486498[];
extern char s_igGeometrySetAttr_className_004d55d0[];
extern char g_igGeometrySetAttr_metaObject_0055f118[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igGeometrySetAttr_InitFields();

void igGeometrySetAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometrySetAttr_metaObject_0055f118,           /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igGeometrySetAttr_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igGeometrySetAttr_className_004d55d0,            /* class name */
        0x20,                                              /* instance size */
        igGeometrySetAttr_GetVTable,                       /* vtable getter */
        &igGeometrySetAttr_InitFields,                     /* field adder */
        0,                                                 /* extra callback item */
        g_igGeometrySetAttr_callbackList_00486498          /* callback list */
    );
}
