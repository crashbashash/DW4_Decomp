/* 0x00451590 igEventDispatcher_Register: registers class igEventDispatcher with the object system, derived from igInterfaceManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaceManager_Register[];
extern char igInterfaceManager_GetPublishedMetaObject[];
extern char igEventDispatcher_GetVTable[];
extern char thunk_igEventDispatcher_GetMetaObject[];
extern char g_igEventDispatcher_callbackList[];
extern char igEventDispatcher_className[];
extern char g_igEventDispatcher_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igEventDispatcher_InitFields();

void igEventDispatcher_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventDispatcher_metaObject,            /* published MetaObject slot */
        igInterfaceManager_Register,                        /* base class registrar */
        igInterfaceManager_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igEventDispatcher_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igEventDispatcher_className,             /* class name */
        0x14,                                               /* instance size */
        igEventDispatcher_GetVTable,                        /* vtable getter */
        &igEventDispatcher_InitFields,                      /* field adder */
        0,                                                  /* extra callback item */
        g_igEventDispatcher_callbackList           /* callback list */
    );
}
