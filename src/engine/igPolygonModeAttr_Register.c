/* 0x00134a30 igPolygonModeAttr_Register: registers class igPolygonModeAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igPolygonModeAttr_GetVTable[];
extern char thunk_igPolygonModeAttr_GetMetaObject[];
extern char s_igPolygonModeAttr_className_004d5260[];
extern char g_igPolygonModeAttr_metaObject_0055ef60[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igPolygonModeAttr_InitFields();

void igPolygonModeAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPolygonModeAttr_metaObject_0055ef60,           /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igPolygonModeAttr_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igPolygonModeAttr_className_004d5260,            /* class name */
        0x10,                                              /* instance size */
        igPolygonModeAttr_GetVTable,                       /* vtable getter */
        &igPolygonModeAttr_InitFields,                     /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
