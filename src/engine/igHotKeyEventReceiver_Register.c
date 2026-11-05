/* 0x0044d980 igHotKeyEventReceiver_Register: registers class igHotKeyEventReceiver with the object system, derived from igEventReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventReceiver_GetPublishedMetaObject_00233200[];
extern char igHotKeyEventReceiver_GetVTable[];
extern char thunk_igHotKeyEventReceiver_GetMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igHotKeyEventReceiver_callbackList_004d0100[];
extern char s_igHotKeyEventReceiver_className_0051df20[];
extern char g_igHotKeyEventReceiver_metaObject_0058c2a8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igHotKeyEventReceiver_InitFields();

void igHotKeyEventReceiver_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igHotKeyEventReceiver_metaObject_0058c2a8,     /* published MetaObject slot */
        igEventReceiver_Register,                        /* base class registrar */
        igEventReceiver_GetPublishedMetaObject_00233200, /* base class MetaObject accessor */
        thunk_igHotKeyEventReceiver_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igHotKeyEventReceiver_className_0051df20,      /* class name */
        0xC,                                             /* instance size */
        igHotKeyEventReceiver_GetVTable,                 /* vtable getter */
        &igHotKeyEventReceiver_InitFields,               /* field adder */
        0,                                               /* extra callback item */
        g_igHotKeyEventReceiver_callbackList_004d0100    /* callback list */
    );
}
