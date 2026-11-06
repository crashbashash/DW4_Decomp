/* 0x0045a9b0 igViewerSceneInfoManagerController_Register: registers class igViewerSceneInfoManagerController with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igViewerSceneInfoManagerController_GetVTable[];
extern char thunk_igViewerSceneInfoManagerController_GetMetaObject[];
extern char g_igViewerSceneInfoManagerController_callbackList[];
extern char igViewerSceneInfoManagerController_className[];
extern char g_igViewerSceneInfoManagerController_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igViewerSceneInfoManagerController_InitFields();

void igViewerSceneInfoManagerController_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerSceneInfoManagerController_metaObject, /* published MetaObject slot */
        igView_Register,                                          /* base class registrar */
        igView_GetPublishedMetaObject,                   /* base class MetaObject accessor */
        thunk_igViewerSceneInfoManagerController_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerSceneInfoManagerController_className,  /* class name */
        0x14,                                                     /* instance size */
        igViewerSceneInfoManagerController_GetVTable,             /* vtable getter */
        &igViewerSceneInfoManagerController_InitFields,           /* field adder */
        0,                                                        /* extra callback item */
        g_igViewerSceneInfoManagerController_callbackList  /* callback list */
    );
}
