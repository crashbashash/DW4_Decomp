/* 0x0045e4b0 igActorManager_Register: registers class igActorManager with the object system, derived from igInfoManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManager_GetPublishedMetaObject[];
extern char igInfoManager_Register[];
extern char igActorManager_GetVTable[];
extern char thunk_igActorManager_GetMetaObject[];
extern char g_igActorManager_callbackList[];
extern char igActorManager_className[];
extern char g_igActorManager_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igActorManager_InitFields();

void igActorManager_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActorManager_metaObject,          /* published MetaObject slot */
        igInfoManager_Register,                        /* base class registrar */
        igInfoManager_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igActorManager_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        igActorManager_className,           /* class name */
        0x38,                                          /* instance size */
        igActorManager_GetVTable,                      /* vtable getter */
        &igActorManager_InitFields,                    /* field adder */
        0,                                             /* extra callback item */
        g_igActorManager_callbackList         /* callback list */
    );
}
