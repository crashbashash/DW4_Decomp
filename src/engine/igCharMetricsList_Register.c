extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igCharMetricsList_GetVTable[];
extern char thunk_igCharMetricsList_GetMetaObject[];
extern char igCharMetricsList_className[];
extern char g_igCharMetricsList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
void FUN_00452900(void);
void igCharMetricsList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetricsList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igCharMetricsList_GetMetaObject,
        igCharMetricsList_className,
        0x14, /* instance size */
        igCharMetricsList_GetVTable,
        FUN_00452900,
        0, /* extra callback item */
        0 /* callback list */
    );
}
