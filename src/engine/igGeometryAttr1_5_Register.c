/* 0x001376e0 igGeometryAttr1_5_Register: registers class igGeometryAttr1_5 with the object system, derived from igGeometryAttr.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGeometryAttr1_5_GetVTable[];
extern char thunk_igGeometryAttr1_5_GetMetaObject[];
extern char igGeometryAttr_GetPublishedMetaObject[];
extern char igGeometryAttr_Register[];
extern char g_igGeometryAttr1_5_callbackList[];
extern char igGeometryAttr1_5_className[];
extern char g_igGeometryAttr1_5_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igGeometryAttr1_5_InitFields();

void igGeometryAttr1_5_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometryAttr1_5_metaObject,        /* published MetaObject slot */
        igGeometryAttr_Register,                        /* base class registrar */
        igGeometryAttr_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGeometryAttr1_5_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igGeometryAttr1_5_className,         /* class name */
        0x34,                                           /* instance size */
        igGeometryAttr1_5_GetVTable,                    /* vtable getter */
        &igGeometryAttr1_5_InitFields,                  /* field adder */
        0,                                              /* extra callback item */
        g_igGeometryAttr1_5_callbackList       /* callback list */
    );
}
