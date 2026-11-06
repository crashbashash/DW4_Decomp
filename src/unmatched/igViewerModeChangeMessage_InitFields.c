int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0e18[4];
extern int DAT_004d0e20[4];
extern int DAT_004d0e28[4];
extern int DAT_004d0e30[4];
extern int DAT_0058c8f8[4];
void igViewerModeChangeMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c8f8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e18[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e20[0], &DAT_004d0e28[0], &DAT_004d0e30[0], temp_s1);
}
