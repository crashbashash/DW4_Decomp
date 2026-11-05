/* 0x0044dd50 igHotKeyBinding_Register: registers class igHotKeyBinding with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igHotKeyBinding_GetVTable[];
extern char thunk_igHotKeyBinding_GetMetaObject[];
extern char g_igHotKeyBinding_callbackList_004d0130[];
extern char s_igHotKeyBinding_className_0051df70[];
extern char g_igHotKeyBinding_metaObject_0058c2c0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igHotKeyBinding_InitFields();

void igHotKeyBinding_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igHotKeyBinding_metaObject_0058c2c0, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igHotKeyBinding_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igHotKeyBinding_className_0051df70,  /* class name */
        0x14,                                  /* instance size */
        igHotKeyBinding_GetVTable,             /* vtable getter */
        &igHotKeyBinding_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igHotKeyBinding_callbackList_004d0130  /* callback list */
    );
}
