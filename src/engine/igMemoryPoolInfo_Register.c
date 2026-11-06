extern char igInfo_GetPublishedMetaObject[];
extern char igMemoryPoolInfo_GetVTable[];
extern char thunk_igMemoryPoolInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char igMemoryPoolInfo_className[];
extern char g_igMemoryPoolInfo_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMemoryPoolInfo_InitFields();

void igMemoryPoolInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryPoolInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMemoryPoolInfo_GetMetaObject,
        igMemoryPoolInfo_className,
        0x54, /* instance size */
        igMemoryPoolInfo_GetVTable,
        &igMemoryPoolInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
