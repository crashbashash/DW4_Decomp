/* 0x00231540 igMessenger_Register: registers class igMessenger with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMessenger_GetVTable[];
extern char thunk_igMessenger_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMessenger_callbackList_00497fb0[];
extern char s_igMessenger_className_004e8408[];
extern char g_igMessenger_metaObject_0056dac8[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igMessenger_InitFields();

void igMessenger_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessenger_metaObject_0056dac8,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMessenger_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMessenger_className_004e8408,      /* class name */
        0xC,                                   /* instance size */
        igMessenger_GetVTable,                 /* vtable getter */
        &igMessenger_InitFields,               /* field adder */
        0,                                     /* extra callback item */
        g_igMessenger_callbackList_00497fb0    /* callback list */
    );
}
