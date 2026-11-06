/* 0x00137900 igGeometryAttr_Register: registers class igGeometryAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char thunk_igGeometryAttr_GetMetaObject[];
extern char g_igGeometryAttr_callbackList[];
extern char igGeometryAttr_className[];
extern char g_igGeometryAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGeometryAttr_InitFields();

void igGeometryAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryAttr_metaObject,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGeometryAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        igGeometryAttr_className,               /* class name */
        0x30,                                              /* instance size */
        0,                                                 /* vtable getter */
        &igGeometryAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        g_igGeometryAttr_callbackList             /* callback list */
    );
}
