/* 0x0044d980 igHotKeyEventReceiver_Register: registers class igHotKeyEventReceiver with the object system, derived from igEventReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventReceiver_GetPublishedMetaObject[];
extern char igHotKeyEventReceiver_GetVTable[];
extern char thunk_igHotKeyEventReceiver_GetMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igHotKeyEventReceiver_callbackList[];
extern char igHotKeyEventReceiver_className[];
extern char g_igHotKeyEventReceiver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igHotKeyEventReceiver_InitFields();

void igHotKeyEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igHotKeyEventReceiver_metaObject,     /* published MetaObject slot */
        igEventReceiver_Register,                        /* base class registrar */
        igEventReceiver_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igHotKeyEventReceiver_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igHotKeyEventReceiver_className,      /* class name */
        0xC,                                             /* instance size */
        igHotKeyEventReceiver_GetVTable,                 /* vtable getter */
        &igHotKeyEventReceiver_InitFields,               /* field adder */
        0,                                               /* extra callback item */
        g_igHotKeyEventReceiver_callbackList    /* callback list */
    );
}
