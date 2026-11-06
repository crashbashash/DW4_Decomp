int FUN_0030e9b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486530[4];
extern int DAT_00486538[4];
extern int DAT_00486540[4];
extern int DAT_00486548[4];
extern int DAT_0055f148[4];
void igGeometryMaskAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055f148[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486530[0], 1);
    FUN_0030e9b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_00486538[0], &DAT_00486540[0], &DAT_00486548[0], temp_s1);
}
