extern char igInfo_GetPublishedMetaObject[];
extern char igMemoryPoolContextInfo_GetVTable[];
extern char thunk_igMemoryPoolContextInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igMemoryPoolContextInfo_callbackList[];
extern char igMemoryPoolContextInfo_className[];
extern char g_igMemoryPoolContextInfo_metaObject_00585e88[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryPoolContextInfo_InitFields();

void igMemoryPoolContextInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryPoolContextInfo_metaObject_00585e88,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMemoryPoolContextInfo_GetMetaObject,
        igMemoryPoolContextInfo_className,
        0x18, /* instance size */
        igMemoryPoolContextInfo_GetVTable,
        &igMemoryPoolContextInfo_InitFields,
        0, /* extra callback item */
        g_igMemoryPoolContextInfo_callbackList /* callback list */
    );
}
