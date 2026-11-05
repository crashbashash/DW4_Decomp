/* 0x00133d30 igSetRenderDestinationAttr_Register: registers class igSetRenderDestinationAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igSetRenderDestinationAttr_GetVTable[];
extern char thunk_igSetRenderDestinationAttr_GetMetaObject[];
extern char g_igSetRenderDestinationAttr_callbackList_00485f38[];
extern char s_igSetRenderDestinationAttr_className_004d4fa0[];
extern char g_igSetRenderDestinationAttr_metaObject_0055eea0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igSetRenderDestinationAttr_InitFields();

void igSetRenderDestinationAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSetRenderDestinationAttr_metaObject_0055eea0,  /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igSetRenderDestinationAttr_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igSetRenderDestinationAttr_className_004d4fa0,   /* class name */
        0x10,                                              /* instance size */
        igSetRenderDestinationAttr_GetVTable,              /* vtable getter */
        &igSetRenderDestinationAttr_InitFields,            /* field adder */
        0,                                                 /* extra callback item */
        g_igSetRenderDestinationAttr_callbackList_00485f38  /* callback list */
    );
}
