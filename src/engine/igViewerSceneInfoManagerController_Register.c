/* 0x0045a9b0 igViewerSceneInfoManagerController_Register: registers class igViewerSceneInfoManagerController with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igViewerSceneInfoManagerController_GetVTable[];
extern char thunk_igViewerSceneInfoManagerController_GetMetaObject[];
extern char g_igViewerSceneInfoManagerController_callbackList_004d0e58[];
extern char s_igViewerSceneInfoManagerController_className_0051ef00[];
extern char g_igViewerSceneInfoManagerController_metaObject_0058c928[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewerSceneInfoManagerController_InitFields();

void igViewerSceneInfoManagerController_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerSceneInfoManagerController_metaObject_0058c928, /* published MetaObject slot */
        igView_Register,                                          /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,                   /* base class MetaObject accessor */
        thunk_igViewerSceneInfoManagerController_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igViewerSceneInfoManagerController_className_0051ef00,  /* class name */
        0x14,                                                     /* instance size */
        igViewerSceneInfoManagerController_GetVTable,             /* vtable getter */
        &igViewerSceneInfoManagerController_InitFields,           /* field adder */
        0,                                                        /* extra callback item */
        g_igViewerSceneInfoManagerController_callbackList_004d0e58  /* callback list */
    );
}
