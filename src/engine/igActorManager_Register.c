/* 0x0045e4b0 igActorManager_Register: registers class igActorManager with the object system, derived from igInfoManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManager_GetPublishedMetaObject_002310d0[];
extern char igInfoManager_Register[];
extern char igActorManager_GetVTable[];
extern char thunk_igActorManager_GetMetaObject[];
extern char g_igActorManager_callbackList_004d19c0[];
extern char s_igActorManager_className_0051f9e8[];
extern char g_igActorManager_metaObject_0058ce60[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igActorManager_InitFields();

void igActorManager_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActorManager_metaObject_0058ce60,          /* published MetaObject slot */
        igInfoManager_Register,                        /* base class registrar */
        igInfoManager_GetPublishedMetaObject_002310d0, /* base class MetaObject accessor */
        thunk_igActorManager_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igActorManager_className_0051f9e8,           /* class name */
        0x38,                                          /* instance size */
        igActorManager_GetVTable,                      /* vtable getter */
        &igActorManager_InitFields,                    /* field adder */
        0,                                             /* extra callback item */
        g_igActorManager_callbackList_004d19c0         /* callback list */
    );
}
