/* 0x00136890 igLightAttr_Register: registers class igLightAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igLightAttr_GetVTable[];
extern char thunk_igLightAttr_GetMetaObject[];
extern char g_igLightAttr_callbackList_00486368[];
extern char s_igLightAttr_className_004d54b0[];
extern char g_igLightAttr_metaObject_0055f088[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igLightAttr_InitFields();

void igLightAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightAttr_metaObject_0055f088,                 /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igLightAttr_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        s_igLightAttr_className_004d54b0,                  /* class name */
        0x94,                                              /* instance size */
        igLightAttr_GetVTable,                             /* vtable getter */
        &igLightAttr_InitFields,                           /* field adder */
        0,                                                 /* extra callback item */
        g_igLightAttr_callbackList_00486368                /* callback list */
    );
}
