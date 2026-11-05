/* 0x0045bfb0 igViewerDataPumpManager_Register: registers class igViewerDataPumpManager with the object system, derived from igInfoManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfoManager_GetPublishedMetaObject_002310d0[];
extern char igInfoManager_Register[];
extern char igViewerDataPumpManager_GetVTable[];
extern char thunk_igViewerDataPumpManager_GetMetaObject[];
extern char g_igViewerDataPumpManager_callbackList_004d1350[];
extern char s_igViewerDataPumpManager_className_0051f4c0[];
extern char g_igViewerDataPumpManager_metaObject_0058cb70[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
extern int igViewerDataPumpManager_InitFields_0045c040[4];
void igViewerDataPumpManager_Register(void) {
    GpFlag_SetOnce_00458680();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerDataPumpManager_metaObject_0058cb70, /* published MetaObject slot */
        igInfoManager_Register,                        /* base class registrar */
        igInfoManager_GetPublishedMetaObject_002310d0, /* base class MetaObject accessor */
        thunk_igViewerDataPumpManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igViewerDataPumpManager_className_0051f4c0,  /* class name */
        0x14,                                          /* instance size */
        igViewerDataPumpManager_GetVTable,             /* vtable getter */
        &igViewerDataPumpManager_InitFields_0045c040[0],                              /* field adder: InitFields, registers the reflected fields */
        0,                                             /* extra callback item */
        g_igViewerDataPumpManager_callbackList_004d1350  /* callback list */
    );
}
