/* 0x00134a30 igPolygonModeAttr_Register: registers class igPolygonModeAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igPolygonModeAttr_GetVTable[];
extern char thunk_igPolygonModeAttr_GetMetaObject[];
extern char igPolygonModeAttr_className[];
extern char g_igPolygonModeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPolygonModeAttr_InitFields();

void igPolygonModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPolygonModeAttr_metaObject,           /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPolygonModeAttr_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igPolygonModeAttr_className,            /* class name */
        0x10,                                              /* instance size */
        igPolygonModeAttr_GetVTable,                       /* vtable getter */
        &igPolygonModeAttr_InitFields,                     /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
