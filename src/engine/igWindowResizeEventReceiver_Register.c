/* 0x00233170 igWindowResizeEventReceiver_Register: registers class igWindowResizeEventReceiver with the object system, derived from igEventReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igWindowResizeEventReceiver_GetVTable[];
extern char thunk_igWindowResizeEventReceiver_GetMetaObject[];
extern char igEventReceiver_GetPublishedMetaObject_00233200[];
extern char igEventReceiver_Register[];
extern char g_igWindowResizeEventReceiver_callbackList_004981f0[];
extern char s_igWindowResizeEventReceiver_className_004e86f0[];
extern char g_igWindowResizeEventReceiver_metaObject_0056dc00[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igWindowResizeEventReceiver_InitFields();

void igWindowResizeEventReceiver_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igWindowResizeEventReceiver_metaObject_0056dc00, /* published MetaObject slot */
        igEventReceiver_Register,                          /* base class registrar */
        igEventReceiver_GetPublishedMetaObject_00233200,   /* base class MetaObject accessor */
        thunk_igWindowResizeEventReceiver_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igWindowResizeEventReceiver_className_004e86f0,  /* class name */
        0xC,                                               /* instance size */
        igWindowResizeEventReceiver_GetVTable,             /* vtable getter */
        &igWindowResizeEventReceiver_InitFields,           /* field adder */
        0,                                                 /* extra callback item */
        g_igWindowResizeEventReceiver_callbackList_004981f0  /* callback list */
    );
}
