/* 0x0045d300 igViewManager_Register: registers class igViewManager with the object system, derived from igEventReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igEventReceiver_GetPublishedMetaObject[];
extern char igEventReceiver_Register[];
extern char igViewManager_GetVTable[];
extern char thunk_igViewManager_GetMetaObject[];
extern char g_igViewManager_callbackList[];
extern char igViewManager_className[];
extern char g_igViewManager_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewManager_InitFields();

void igViewManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewManager_metaObject,             /* published MetaObject slot */
        igEventReceiver_Register,                        /* base class registrar */
        igEventReceiver_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igViewManager_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igViewManager_className,              /* class name */
        0x54,                                            /* instance size */
        igViewManager_GetVTable,                         /* vtable getter */
        &igViewManager_InitFields,                       /* field adder */
        0,                                               /* extra callback item */
        g_igViewManager_callbackList            /* callback list */
    );
}
