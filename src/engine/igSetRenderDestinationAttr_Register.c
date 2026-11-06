/* 0x00133d30 igSetRenderDestinationAttr_Register: registers class igSetRenderDestinationAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igSetRenderDestinationAttr_GetVTable[];
extern char thunk_igSetRenderDestinationAttr_GetMetaObject[];
extern char g_igSetRenderDestinationAttr_callbackList[];
extern char igSetRenderDestinationAttr_className[];
extern char g_igSetRenderDestinationAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSetRenderDestinationAttr_InitFields();

void igSetRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSetRenderDestinationAttr_metaObject,  /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSetRenderDestinationAttr_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igSetRenderDestinationAttr_className,   /* class name */
        0x10,                                              /* instance size */
        igSetRenderDestinationAttr_GetVTable,              /* vtable getter */
        &igSetRenderDestinationAttr_InitFields,            /* field adder */
        0,                                                 /* extra callback item */
        g_igSetRenderDestinationAttr_callbackList  /* callback list */
    );
}
