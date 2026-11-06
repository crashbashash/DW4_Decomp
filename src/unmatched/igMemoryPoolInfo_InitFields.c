int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0060[4];
extern int DAT_004c00a0[4];
extern int DAT_004c00e0[4];
extern int DAT_004c0120[4];
extern int DAT_00585e00[4];
void igMemoryPoolInfo_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00585e00[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0060[0], 0x10);
    igMetaObject_NameFields(temp_s0, &DAT_004c00a0[0], &DAT_004c00e0[0], &DAT_004c0120[0], temp_s1);
}
