int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004859c0[4];
extern int DAT_004859c8[4];
extern int DAT_004859d0[4];
extern int DAT_004859d8[4];
extern int DAT_0055ec18[4];
void igVertexBlendStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ec18[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004859c0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004859c8[0], &DAT_004859d0[0], &DAT_004859d8[0], temp_s1);
}
