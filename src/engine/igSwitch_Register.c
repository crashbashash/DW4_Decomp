/* 0x00196ae0 igSwitch_Register: registers class igSwitch with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igSwitch_GetVTable[];
extern char thunk_igSwitch_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igSwitch_callbackList[];
extern char igSwitch_className[];
extern char g_igSwitch_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igSwitch_InitFields();

void igSwitch_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSwitch_metaObject,          /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSwitch_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igSwitch_className,           /* class name */
        0x24,                                    /* instance size */
        igSwitch_GetVTable,                      /* vtable getter */
        &igSwitch_InitFields,                    /* field adder */
        0,                                       /* extra callback item */
        g_igSwitch_callbackList         /* callback list */
    );
}
