/* 0x002326b0 igInsightPluginList_Register: registers class igInsightPluginList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igInsightPluginList_GetVTable[];
extern char thunk_igInsightPluginList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igInsightPluginList_callbackList[];
extern char igInsightPluginList_className[];
extern char g_igInsightPluginList_metaObject[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igInsightPluginList_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInsightPluginList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igInsightPluginList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igInsightPluginList_className,  /* class name */
        0x14,                                      /* instance size */
        igInsightPluginList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igInsightPluginList_callbackList  /* callback list */
    );
}
