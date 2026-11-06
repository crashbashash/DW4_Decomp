/* 0x00136480 igLightStateAttr_Register: registers class igLightStateAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igLightStateAttr_GetVTable[];
extern char thunk_igLightStateAttr_GetMetaObject[];
extern char g_igLightStateAttr_callbackList[];
extern char igLightStateAttr_className[];
extern char g_igLightStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightStateAttr_InitFields();

void igLightStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightStateAttr_metaObject,            /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLightStateAttr_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igLightStateAttr_className,             /* class name */
        0x18,                                              /* instance size */
        igLightStateAttr_GetVTable,                        /* vtable getter */
        &igLightStateAttr_InitFields,                      /* field adder */
        0,                                                 /* extra callback item */
        g_igLightStateAttr_callbackList           /* callback list */
    );
}
