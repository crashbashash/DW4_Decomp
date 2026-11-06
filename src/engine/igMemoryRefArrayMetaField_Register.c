extern char igMemoryRefMetaField_Register[];
extern char igMemoryRefArrayMetaField_GetVTable[];
extern char thunk_igMemoryRefArrayMetaField_GetMetaObject[];
extern char igMemoryRefMetaField_GetPublishedMetaObject[];
extern char g_igMemoryRefArrayMetaField_callbackList[];
extern char igMemoryRefArrayMetaField_className[];
extern char g_igMemoryRefArrayMetaField_metaObject_00585de0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryRefArrayMetaField_InitFields();

void igMemoryRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryRefArrayMetaField_metaObject_00585de0,
        igMemoryRefMetaField_Register,
        igMemoryRefMetaField_GetPublishedMetaObject,
        thunk_igMemoryRefArrayMetaField_GetMetaObject,
        igMemoryRefArrayMetaField_className,
        0x54, /* instance size */
        igMemoryRefArrayMetaField_GetVTable,
        &igMemoryRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igMemoryRefArrayMetaField_callbackList /* callback list */
    );
}
