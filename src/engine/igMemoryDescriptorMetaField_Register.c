extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igCompoundMetaField_Register[];
extern char igMemoryDescriptorMetaField_GetVTable[];
extern char thunk_igMemoryDescriptorMetaField_GetMetaObject[];
extern char g_igMemoryDescriptorMetaField_callbackList[];
extern char igMemoryDescriptorMetaField_className[];
extern char g_igMemoryDescriptorMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMemoryDescriptorMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMemoryDescriptorMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igMemoryDescriptorMetaField_GetMetaObject,
        igMemoryDescriptorMetaField_className,
        0x38, /* instance size */
        igMemoryDescriptorMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igMemoryDescriptorMetaField_callbackList /* callback list */
    );
}
