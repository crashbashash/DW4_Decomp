/* 0x00137900 igGeometryAttr_Register: registers class igGeometryAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char thunk_igGeometryAttr_GetMetaObject[];
extern char g_igGeometryAttr_callbackList_00486580[];
extern char s_igGeometryAttr_className_004d56c8[];
extern char g_igGeometryAttr_metaObject_0055f170[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igGeometryAttr_InitFields();

void igGeometryAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        1,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryAttr_metaObject_0055f170,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igGeometryAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igGeometryAttr_className_004d56c8,               /* class name */
        0x30,                                              /* instance size */
        0,                                                 /* vtable getter */
        &igGeometryAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        g_igGeometryAttr_callbackList_00486580             /* callback list */
    );
}
