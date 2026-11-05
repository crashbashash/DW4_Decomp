/* 0x00134380 igRenderDestinationAttr_Register: registers class igRenderDestinationAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igRenderDestinationAttr_GetVTable[];
extern char thunk_igRenderDestinationAttr_GetMetaObject[];
extern char g_igRenderDestinationAttr_callbackList_00485fb8[];
extern char s_igRenderDestinationAttr_className_004d5160[];
extern char g_igRenderDestinationAttr_metaObject_0055eed8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igRenderDestinationAttr_InitFields();

void igRenderDestinationAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderDestinationAttr_metaObject_0055eed8,     /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igRenderDestinationAttr_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igRenderDestinationAttr_className_004d5160,      /* class name */
        0x44,                                              /* instance size */
        igRenderDestinationAttr_GetVTable,                 /* vtable getter */
        &igRenderDestinationAttr_InitFields,               /* field adder */
        0,                                                 /* extra callback item */
        g_igRenderDestinationAttr_callbackList_00485fb8    /* callback list */
    );
}
