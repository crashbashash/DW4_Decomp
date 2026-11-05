/* 0x00138b30 igCopyRenderDestinationAttr_Register: registers class igCopyRenderDestinationAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igCopyRenderDestinationAttr_GetVTable[];
extern char thunk_igCopyRenderDestinationAttr_GetMetaObject[];
extern char g_igCopyRenderDestinationAttr_callbackList_004867d0[];
extern char s_igCopyRenderDestinationAttr_className_004d58d0[];
extern char g_igCopyRenderDestinationAttr_metaObject_0055f258[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igCopyRenderDestinationAttr_InitFields();

void igCopyRenderDestinationAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCopyRenderDestinationAttr_metaObject_0055f258, /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igCopyRenderDestinationAttr_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCopyRenderDestinationAttr_className_004d58d0,  /* class name */
        0x34,                                              /* instance size */
        igCopyRenderDestinationAttr_GetVTable,             /* vtable getter */
        &igCopyRenderDestinationAttr_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        g_igCopyRenderDestinationAttr_callbackList_004867d0  /* callback list */
    );
}
