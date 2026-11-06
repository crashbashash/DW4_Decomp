int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048ad70[4];
extern int DAT_0048ad78[4];
extern int DAT_0048ad80[4];
extern int DAT_0048ad88[4];
extern int DAT_00560f48[4];
void igVec4fArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00560f48[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048ad70[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048ad78[0], &DAT_0048ad80[0], &DAT_0048ad88[0], temp_s1);
}
