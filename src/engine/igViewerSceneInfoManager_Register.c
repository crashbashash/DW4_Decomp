/* 0x00459e50 igViewerSceneInfoManager_Register: registers class igViewerSceneInfoManager with the object system, derived from igInfoManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManager_GetPublishedMetaObject_002310d0[];
extern char igInfoManager_Register[];
extern char igViewerSceneInfoManager_GetVTable[];
extern char thunk_igViewerSceneInfoManager_GetMetaObject[];
extern char g_igViewerSceneInfoManager_callbackList_004d0b00[];
extern char s_igViewerSceneInfoManager_className_0051eb00[];
extern char g_igViewerSceneInfoManager_metaObject_0058c790[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
extern int igViewerSceneInfoManager_InitFields_00459ee0[4];
void igViewerSceneInfoManager_Register(void) {
    GpFlag_SetOnce_00458680();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerSceneInfoManager_metaObject_0058c790, /* published MetaObject slot */
        igInfoManager_Register,                         /* base class registrar */
        igInfoManager_GetPublishedMetaObject_002310d0,  /* base class MetaObject accessor */
        thunk_igViewerSceneInfoManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igViewerSceneInfoManager_className_0051eb00,  /* class name */
        0xC8,                                           /* instance size */
        igViewerSceneInfoManager_GetVTable,             /* vtable getter */
        &igViewerSceneInfoManager_InitFields_00459ee0[0],                               /* field adder: InitFields, registers the reflected fields */
        0,                                              /* extra callback item */
        g_igViewerSceneInfoManager_callbackList_004d0b00  /* callback list */
    );
}
