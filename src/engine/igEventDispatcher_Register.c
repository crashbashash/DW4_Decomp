/* 0x00451590 igEventDispatcher_Register: registers class igEventDispatcher with the object system, derived from igInterfaceManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterfaceManager_Register[];
extern char igInterfaceManager_GetPublishedMetaObject_001465e0[];
extern char igEventDispatcher_GetVTable[];
extern char thunk_igEventDispatcher_GetMetaObject[];
extern char g_igEventDispatcher_callbackList_004d0728[];
extern char s_igEventDispatcher_className_0051e580[];
extern char g_igEventDispatcher_metaObject_0058c578[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igEventDispatcher_InitFields();

void igEventDispatcher_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEventDispatcher_metaObject_0058c578,            /* published MetaObject slot */
        igInterfaceManager_Register,                        /* base class registrar */
        igInterfaceManager_GetPublishedMetaObject_001465e0, /* base class MetaObject accessor */
        thunk_igEventDispatcher_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igEventDispatcher_className_0051e580,             /* class name */
        0x14,                                               /* instance size */
        igEventDispatcher_GetVTable,                        /* vtable getter */
        &igEventDispatcher_InitFields,                      /* field adder */
        0,                                                  /* extra callback item */
        g_igEventDispatcher_callbackList_004d0728           /* callback list */
    );
}
