/* 0x001e5290 igDataPumpManager_Register: registers class igDataPumpManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataPumpManager_GetVTable[];
extern char thunk_igDataPumpManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDataPumpManager_callbackList[];
extern char igDataPumpManager_className[];
extern char g_igDataPumpManager_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDataPumpManager_InitFields();

void igDataPumpManager_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataPumpManager_metaObject, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igDataPumpManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDataPumpManager_className,  /* class name */
        0xC,                                     /* instance size */
        igDataPumpManager_GetVTable,             /* vtable getter */
        &igDataPumpManager_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igDataPumpManager_callbackList  /* callback list */
    );
}
