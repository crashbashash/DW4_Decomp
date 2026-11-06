int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d00b8[4];
extern int DAT_004d00c0[4];
extern int DAT_004d00c8[4];
extern int DAT_004d00d0[4];
extern int DAT_0058c288[4];
void igOnOffModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c288[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d00b8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004d00c0[0], &DAT_004d00c8[0], &DAT_004d00d0[0], temp_s1);
}
