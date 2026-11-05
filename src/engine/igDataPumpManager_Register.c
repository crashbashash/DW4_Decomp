/* 0x001e5290 igDataPumpManager_Register: registers class igDataPumpManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataPumpManager_GetVTable[];
extern char thunk_igDataPumpManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDataPumpManager_callbackList_0048db80[];
extern char s_igDataPumpManager_className_004e49b0[];
extern char g_igDataPumpManager_metaObject_00562bf0[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
int igDataPumpManager_InitFields();

void igDataPumpManager_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataPumpManager_metaObject_00562bf0, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igDataPumpManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igDataPumpManager_className_004e49b0,  /* class name */
        0xC,                                     /* instance size */
        igDataPumpManager_GetVTable,             /* vtable getter */
        &igDataPumpManager_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igDataPumpManager_callbackList_0048db80  /* callback list */
    );
}
