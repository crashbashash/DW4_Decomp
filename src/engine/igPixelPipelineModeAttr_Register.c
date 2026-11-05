/* 0x00134c40 igPixelPipelineModeAttr_Register: registers class igPixelPipelineModeAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igPixelPipelineModeAttr_GetVTable[];
extern char thunk_igPixelPipelineModeAttr_GetMetaObject[];
extern char s_igPixelPipelineModeAttr_className_004d5280[];
extern char g_igPixelPipelineModeAttr_metaObject_0055ef70[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igPixelPipelineModeAttr_InitFields();

void igPixelPipelineModeAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPixelPipelineModeAttr_metaObject_0055ef70,     /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igPixelPipelineModeAttr_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igPixelPipelineModeAttr_className_004d5280,      /* class name */
        0x10,                                              /* instance size */
        igPixelPipelineModeAttr_GetVTable,                 /* vtable getter */
        &igPixelPipelineModeAttr_InitFields,               /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
