int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486660[4];
extern int DAT_00486668[4];
extern int DAT_00486670[4];
extern int DAT_00486678[4];
extern int DAT_0055f1c8[4];
void igFogStateAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055f1c8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486660[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486668[0], &DAT_00486670[0], &DAT_00486678[0], temp_s1);
}
