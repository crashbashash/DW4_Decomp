/* 0x00458bd0 igStatisticsItemList_Register: registers class igStatisticsItemList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igStatisticsItemList_GetVTable[];
extern char thunk_igStatisticsItemList_GetMetaObject[];
extern char g_igStatisticsItemList_callbackList[];
extern char igStatisticsItemList_className[];
extern char g_igStatisticsItemList_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();

void igStatisticsItemList_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStatisticsItemList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igStatisticsItemList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igStatisticsItemList_className,  /* class name */
        0x14,                                       /* instance size */
        igStatisticsItemList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igStatisticsItemList_callbackList  /* callback list */
    );
}
