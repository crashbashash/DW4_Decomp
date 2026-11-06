/* 0x004588f0 igViewerStatisticsManager_Register: registers class igViewerStatisticsManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igViewerStatisticsManager_GetVTable[];
extern char thunk_igViewerStatisticsManager_GetMetaObject[];
extern char g_igViewerStatisticsManager_callbackList[];
extern char igViewerStatisticsManager_className[];
extern char g_igViewerStatisticsManager_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewerStatisticsManager_InitFields();

void igViewerStatisticsManager_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewerStatisticsManager_metaObject, /* published MetaObject slot */
        igObject_Register,                               /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,           /* base class MetaObject accessor */
        thunk_igViewerStatisticsManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igViewerStatisticsManager_className,  /* class name */
        0x48,                                            /* instance size */
        igViewerStatisticsManager_GetVTable,             /* vtable getter */
        &igViewerStatisticsManager_InitFields,           /* field adder */
        0,                                               /* extra callback item */
        g_igViewerStatisticsManager_callbackList  /* callback list */
    );
}
