/* 0x00134c40 igPixelPipelineModeAttr_Register: registers class igPixelPipelineModeAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igPixelPipelineModeAttr_GetVTable[];
extern char thunk_igPixelPipelineModeAttr_GetMetaObject[];
extern char igPixelPipelineModeAttr_className[];
extern char g_igPixelPipelineModeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPixelPipelineModeAttr_InitFields();

void igPixelPipelineModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPixelPipelineModeAttr_metaObject,     /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPixelPipelineModeAttr_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igPixelPipelineModeAttr_className,      /* class name */
        0x10,                                              /* instance size */
        igPixelPipelineModeAttr_GetVTable,                 /* vtable getter */
        &igPixelPipelineModeAttr_InitFields,               /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
