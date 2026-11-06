/* 0x00231540 igMessenger_Register: registers class igMessenger with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessenger_GetVTable[];
extern char thunk_igMessenger_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMessenger_callbackList[];
extern char igMessenger_className[];
extern char g_igMessenger_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMessenger_InitFields();

void igMessenger_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessenger_metaObject,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMessenger_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igMessenger_className,      /* class name */
        0xC,                                   /* instance size */
        igMessenger_GetVTable,                 /* vtable getter */
        &igMessenger_InitFields,               /* field adder */
        0,                                     /* extra callback item */
        g_igMessenger_callbackList    /* callback list */
    );
}
