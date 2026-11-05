/* 0x00458ed0 igStatisticsItem_Register: registers class igStatisticsItem with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igStatisticsItem_GetVTable[];
extern char thunk_igStatisticsItem_GetMetaObject[];
extern char g_igStatisticsItem_callbackList_004d09d0[];
extern char s_igStatisticsItem_className_0051e9d0[];
extern char g_igStatisticsItem_metaObject_0058c708[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igStatisticsItem_InitFields();

void igStatisticsItem_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStatisticsItem_metaObject_0058c708, /* published MetaObject slot */
        igView_Register,                        /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20, /* base class MetaObject accessor */
        thunk_igStatisticsItem_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igStatisticsItem_className_0051e9d0,  /* class name */
        0x3C,                                   /* instance size */
        igStatisticsItem_GetVTable,             /* vtable getter */
        &igStatisticsItem_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        g_igStatisticsItem_callbackList_004d09d0  /* callback list */
    );
}
