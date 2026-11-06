extern char igDataList_GetPublishedMetaObject[];
extern char igMatrixStack_GetVTable[];
extern char thunk_igMatrixStack_GetMetaObject[];
extern char igDataList_Register[];
extern char igMatrixStack_className[];
extern char g_igMatrixStack_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int igMatrixStack_InitFields_001e48b0[4];
void igMatrixStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igMatrixStack_GetMetaObject,
        igMatrixStack_className,
        0x14, /* instance size */
        igMatrixStack_GetVTable,
        &igMatrixStack_InitFields_001e48b0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
