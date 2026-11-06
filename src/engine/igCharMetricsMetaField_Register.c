extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igCompoundMetaField_Register[];
extern char igCharMetricsMetaField_GetVTable[];
extern char thunk_igCharMetricsMetaField_GetMetaObject[];
extern char g_igCharMetricsMetaField_callbackList[];
extern char igCharMetricsMetaField_className[];
extern char g_igCharMetricsMetaField_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igCharMetricsMetaField_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetricsMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igCharMetricsMetaField_GetMetaObject,
        igCharMetricsMetaField_className,
        0x38, /* instance size */
        igCharMetricsMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igCharMetricsMetaField_callbackList /* callback list */
    );
}
