int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00487160[4];
extern int DAT_004871a0[4];
extern int DAT_004871e0[4];
extern int DAT_00487220[4];
extern int DAT_0055f610[4];
void igDefaultInterfaceManager_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055f610[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487160[0], 0x10);
    igMetaObject_NameFields(temp_s0, &DAT_004871a0[0], &DAT_004871e0[0], &DAT_00487220[0], temp_s1);
}
