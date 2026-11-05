/* 0x004588f0 igViewerStatisticsManager_Register: registers class igViewerStatisticsManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igViewerStatisticsManager_GetVTable[];
extern char thunk_igViewerStatisticsManager_GetMetaObject[];
extern char g_igViewerStatisticsManager_callbackList_004d08a0[];
extern char s_igViewerStatisticsManager_className_0051e840[];
extern char g_igViewerStatisticsManager_metaObject_0058c680[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewerStatisticsManager_InitFields();

void igViewerStatisticsManager_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerStatisticsManager_metaObject_0058c680, /* published MetaObject slot */
        igObject_Register,                               /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,           /* base class MetaObject accessor */
        thunk_igViewerStatisticsManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igViewerStatisticsManager_className_0051e840,  /* class name */
        0x48,                                            /* instance size */
        igViewerStatisticsManager_GetVTable,             /* vtable getter */
        &igViewerStatisticsManager_InitFields,           /* field adder */
        0,                                               /* extra callback item */
        g_igViewerStatisticsManager_callbackList_004d08a0  /* callback list */
    );
}
