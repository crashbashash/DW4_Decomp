int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf2e8[4];
extern int DAT_004bf2f0[4];
extern int DAT_004bf2f8[4];
extern int DAT_004bf300[4];
extern int DAT_00585720[4];
void igUnsignedLongArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585720[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf2e8[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004bf2f0[0], &DAT_004bf2f8[0], &DAT_004bf300[0], temp_s1);
}
