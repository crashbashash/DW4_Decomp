extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char igMemoryRefMetaField_GetVTable[];
extern char thunk_igMemoryRefMetaField_GetMetaObject[];
extern char g_igMemoryRefMetaField_callbackList[];
extern char igMemoryRefMetaField_className[];
extern char g_igMemoryRefMetaField_metaObject[];
int igMetaObject_RegisterClass();
extern int igMemoryRefMetaField_InitFields_002bf710[4];
void igMemoryRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryRefMetaField_metaObject,
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igMemoryRefMetaField_GetMetaObject,
        igMemoryRefMetaField_className,
        0x50, /* instance size */
        igMemoryRefMetaField_GetVTable,
        &igMemoryRefMetaField_InitFields_002bf710[0],   /* field adder (igMetaObject_CreateFields) */
        0, /* extra callback item */
        g_igMemoryRefMetaField_callbackList /* callback list */
    );
}
