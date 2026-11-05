/* 0x0014f3a0 igGenericCapabilityManager_Register: registers class igGenericCapabilityManager with the object system, derived from igCapabilityManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCapabilityManager_GetPublishedMetaObject_00149df0[];
extern char igGenericCapabilityManager_GetVTable[];
extern char thunk_igGenericCapabilityManager_GetMetaObject[];
extern char igCapabilityManager_Register[];
extern char s_igGenericCapabilityManager_className_004dcd20[];
extern char g_igGenericCapabilityManager_metaObject_0055fe90[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igGenericCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGenericCapabilityManager_metaObject_0055fe90,    /* published MetaObject slot */
        igCapabilityManager_Register,                        /* base class registrar */
        igCapabilityManager_GetPublishedMetaObject_00149df0, /* base class MetaObject accessor */
        thunk_igGenericCapabilityManager_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igGenericCapabilityManager_className_004dcd20,     /* class name */
        8,                                                   /* instance size */
        igGenericCapabilityManager_GetVTable,                /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
