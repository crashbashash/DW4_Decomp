int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c0f70[4];
extern int DAT_004c0f78[4];
extern int DAT_004c0f80[4];
extern int DAT_004c0f88[4];
extern int DAT_00586598[4];
void igEnumMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00586598[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c0f70[0], 1);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s1)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c0f78[0], &DAT_004c0f80[0], &DAT_004c0f88[0], temp_s1);
}
