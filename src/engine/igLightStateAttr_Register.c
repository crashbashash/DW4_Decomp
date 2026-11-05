/* 0x00136480 igLightStateAttr_Register: registers class igLightStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igLightStateAttr_GetVTable[];
extern char thunk_igLightStateAttr_GetMetaObject[];
extern char g_igLightStateAttr_callbackList_00486310[];
extern char s_igLightStateAttr_className_004d5470[];
extern char g_igLightStateAttr_metaObject_0055f060[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igLightStateAttr_InitFields();

void igLightStateAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightStateAttr_metaObject_0055f060,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igLightStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igLightStateAttr_className_004d5470,             /* class name */
        0x18,                                              /* instance size */
        igLightStateAttr_GetVTable,                        /* vtable getter */
        &igLightStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        g_igLightStateAttr_callbackList_00486310           /* callback list */
    );
}
