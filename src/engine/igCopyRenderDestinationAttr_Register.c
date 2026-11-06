/* 0x00138b30 igCopyRenderDestinationAttr_Register: registers class igCopyRenderDestinationAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igCopyRenderDestinationAttr_GetVTable[];
extern char thunk_igCopyRenderDestinationAttr_GetMetaObject[];
extern char g_igCopyRenderDestinationAttr_callbackList[];
extern char igCopyRenderDestinationAttr_className[];
extern char g_igCopyRenderDestinationAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCopyRenderDestinationAttr_InitFields();

void igCopyRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCopyRenderDestinationAttr_metaObject, /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCopyRenderDestinationAttr_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCopyRenderDestinationAttr_className,  /* class name */
        0x34,                                              /* instance size */
        igCopyRenderDestinationAttr_GetVTable,             /* vtable getter */
        &igCopyRenderDestinationAttr_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        g_igCopyRenderDestinationAttr_callbackList  /* callback list */
    );
}
