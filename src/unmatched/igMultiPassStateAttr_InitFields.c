int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486200[4];
extern int DAT_00486208[4];
extern int DAT_00486210[4];
extern int DAT_00486218[4];
extern int DAT_0055efd0[4];
void igMultiPassStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055efd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486200[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486208[0], &DAT_00486210[0], &DAT_00486218[0], temp_s1);
}
