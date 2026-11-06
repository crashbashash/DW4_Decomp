/* 0x0019da70 igLightStateSet_Register: registers class igLightStateSet with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igLightStateSet_GetVTable[];
extern char thunk_igLightStateSet_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igLightStateSet_callbackList[];
extern char igLightStateSet_className[];
extern char g_igLightStateSet_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igLightStateSet_InitFields();

void igLightStateSet_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLightStateSet_metaObject,   /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igLightStateSet_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igLightStateSet_className,    /* class name */
        0x24,                                    /* instance size */
        igLightStateSet_GetVTable,               /* vtable getter */
        &igLightStateSet_InitFields,             /* field adder */
        0,                                       /* extra callback item */
        g_igLightStateSet_callbackList  /* callback list */
    );
}
