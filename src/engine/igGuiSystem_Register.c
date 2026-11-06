/* 0x0044e270 igGuiSystem_Register: registers class igGuiSystem with the object system, derived from igEventReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventReceiver_GetPublishedMetaObject[];
extern char igGuiSystem_GetVTable[];
extern char thunk_igGuiSystem_GetMetaObject[];
extern char igEventReceiver_Register[];
extern char g_igGuiSystem_callbackList[];
extern char igGuiSystem_className[];
extern char g_igGuiSystem_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGuiSystem_InitFields();

void igGuiSystem_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiSystem_metaObject,               /* published MetaObject slot */
        igEventReceiver_Register,                        /* base class registrar */
        igEventReceiver_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igGuiSystem_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        igGuiSystem_className,                /* class name */
        0x24,                                            /* instance size */
        igGuiSystem_GetVTable,                           /* vtable getter */
        &igGuiSystem_InitFields,                         /* field adder */
        0,                                               /* extra callback item */
        g_igGuiSystem_callbackList              /* callback list */
    );
}
