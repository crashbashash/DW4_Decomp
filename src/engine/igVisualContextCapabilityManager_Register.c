/* 0x00149d60 igVisualContextCapabilityManager_Register: registers class igVisualContextCapabilityManager with the object system, derived from igCapabilityManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualContextCapabilityManager_GetVTable[];
extern char thunk_igVisualContextCapabilityManager_GetMetaObject[];
extern char igCapabilityManager_GetPublishedMetaObject[];
extern char igCapabilityManager_Register[];
extern char g_igVisualContextCapabilityManager_callbackList[];
extern char igVisualContextCapabilityManager_className[];
extern char g_igVisualContextCapabilityManager_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVisualContextCapabilityManager_InitFields();

void igVisualContextCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVisualContextCapabilityManager_metaObject, /* published MetaObject slot */
        igCapabilityManager_Register,                           /* base class registrar */
        igCapabilityManager_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igVisualContextCapabilityManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igVisualContextCapabilityManager_className,  /* class name */
        0xC,                                                    /* instance size */
        igVisualContextCapabilityManager_GetVTable,             /* vtable getter */
        &igVisualContextCapabilityManager_InitFields,           /* field adder */
        0,                                                      /* extra callback item */
        g_igVisualContextCapabilityManager_callbackList  /* callback list */
    );
}
