int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00486c70[4];
extern int DAT_00486c78[4];
extern int DAT_00486c80[4];
extern int DAT_00486c88[4];
extern int DAT_0055f480[4];
void igAlphaStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f480[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486c70[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486c78[0], &DAT_00486c80[0], &DAT_00486c88[0], temp_s1);
}
