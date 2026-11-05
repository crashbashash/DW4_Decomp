/* 0x00130580 igViewportAttr_Register: registers class igViewportAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igViewportAttr_GetVTable[];
extern char thunk_igViewportAttr_GetMetaObject[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char g_igViewportAttr_callbackList_00485938[];
extern char s_igViewportAttr_className_004d4a18[];
extern char g_igViewportAttr_metaObject_0055ebd8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igViewportAttr_InitFields();

void igViewportAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewportAttr_metaObject_0055ebd8,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igViewportAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igViewportAttr_className_004d4a18,               /* class name */
        0x28,                                              /* instance size */
        igViewportAttr_GetVTable,                          /* vtable getter */
        &igViewportAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        g_igViewportAttr_callbackList_00485938             /* callback list */
    );
}
