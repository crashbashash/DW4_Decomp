int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004bf348[4];
extern int DAT_004bf350[4];
extern int DAT_004bf358[4];
extern int DAT_004bf360[4];
extern int DAT_00585770[4];
void igUnsignedCharArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585770[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004bf348[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004bf350[0], &DAT_004bf358[0], &DAT_004bf360[0], temp_s1);
}
