/* 0x0023c5a0 igLuaState_Register: registers class igLuaState with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igLuaState_GetVTable[];
extern char thunk_igLuaState_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igLuaState_callbackList_00498640[];
extern char s_igLuaState_className_004ea180[];
extern char g_igLuaState_metaObject_0056de10[];
int GpFlag_SetOnce_0023c440();
int igMetaObject_RegisterClass();
int igLuaState_InitFields();

void igLuaState_Register(void) {
    GpFlag_SetOnce_0023c440();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLuaState_metaObject_0056de10,              /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igLuaState_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igLuaState_className_004ea180,               /* class name */
        0x14,                                          /* instance size */
        igLuaState_GetVTable,                          /* vtable getter */
        &igLuaState_InitFields,                        /* field adder */
        0,                                             /* extra callback item */
        g_igLuaState_callbackList_00498640             /* callback list */
    );
}
