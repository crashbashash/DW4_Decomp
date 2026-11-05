/* 0x0044e270 igGuiSystem_Register: registers class igGuiSystem with the object system, derived from igEventReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventReceiver_GetPublishedMetaObject_00233200[];
extern char igGuiSystem_GetVTable[];
extern char thunk_igGuiSystem_GetMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igGuiSystem_callbackList_004d0190[];
extern char s_igGuiSystem_className_0051df98[];
extern char g_igGuiSystem_metaObject_0058c2e0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igGuiSystem_InitFields();

void igGuiSystem_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiSystem_metaObject_0058c2e0,               /* published MetaObject slot */
        igEventReceiver_Register,                        /* base class registrar */
        igEventReceiver_GetPublishedMetaObject_00233200, /* base class MetaObject accessor */
        thunk_igGuiSystem_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        s_igGuiSystem_className_0051df98,                /* class name */
        0x24,                                            /* instance size */
        igGuiSystem_GetVTable,                           /* vtable getter */
        &igGuiSystem_InitFields,                         /* field adder */
        0,                                               /* extra callback item */
        g_igGuiSystem_callbackList_004d0190              /* callback list */
    );
}
