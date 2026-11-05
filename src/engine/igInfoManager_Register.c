/* 0x00233920 igInfoManager_Register: registers class igInfoManager with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char thunk_igInfoManager_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igInfoManager_callbackList_00498248[];
extern char s_igInfoManager_className_004e8788[];
extern char g_igInfoManager_metaObject_0056dc38[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igInfoManager_InitFields();

void igInfoManager_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoManager_metaObject_0056dc38,           /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igInfoManager_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igInfoManager_className_004e8788,            /* class name */
        0x10,                                          /* instance size */
        0,                                             /* vtable getter */
        &igInfoManager_InitFields,                     /* field adder */
        0,                                             /* extra callback item */
        g_igInfoManager_callbackList_00498248          /* callback list */
    );
}
