int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004862e8[4];
extern int DAT_004862f0[4];
extern int DAT_004862f8[4];
extern int DAT_00486300[4];
extern int DAT_0055f048[4];
void igLightingStateAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055f048[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004862e8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004862f0[0], &DAT_004862f8[0], &DAT_00486300[0], temp_s1);
}
