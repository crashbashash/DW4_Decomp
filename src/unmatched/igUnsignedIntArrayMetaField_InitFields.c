int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf318[4];
extern int DAT_004bf320[4];
extern int DAT_004bf328[4];
extern int DAT_004bf330[4];
extern int DAT_00585748[4];
void igUnsignedIntArrayMetaField_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00585748[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf318[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004bf320[0], &DAT_004bf328[0], &DAT_004bf330[0], temp_s1);
}
