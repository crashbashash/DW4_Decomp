extern char igInfo_GetPublishedMetaObject[];
extern char igMetaFieldInfo_GetVTable[];
extern char thunk_igMetaFieldInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char igMetaFieldInfo_className[];
extern char g_igMetaFieldInfo_metaObject_00585cb8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaFieldInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMetaFieldInfo_metaObject_00585cb8,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMetaFieldInfo_GetMetaObject,
        igMetaFieldInfo_className,
        0x14, /* instance size */
        igMetaFieldInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
