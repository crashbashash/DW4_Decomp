/* 0x00458ed0 igStatisticsItem_Register: registers class igStatisticsItem with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igStatisticsItem_GetVTable[];
extern char thunk_igStatisticsItem_GetMetaObject[];
extern char g_igStatisticsItem_callbackList[];
extern char igStatisticsItem_className[];
extern char g_igStatisticsItem_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igStatisticsItem_InitFields();

void igStatisticsItem_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStatisticsItem_metaObject, /* published MetaObject slot */
        igView_Register,                        /* base class registrar */
        igView_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igStatisticsItem_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igStatisticsItem_className,  /* class name */
        0x3C,                                   /* instance size */
        igStatisticsItem_GetVTable,             /* vtable getter */
        &igStatisticsItem_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        g_igStatisticsItem_callbackList  /* callback list */
    );
}
