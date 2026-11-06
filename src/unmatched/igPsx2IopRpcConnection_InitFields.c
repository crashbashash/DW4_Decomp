int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c1dd0[4];
extern int DAT_004c1de0[4];
extern int DAT_004c1df0[4];
extern int DAT_004c1e00[4];
extern int DAT_00586d48[4];
void igPsx2IopRpcConnection_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00586d48[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1dd0[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c1de0[0], &DAT_004c1df0[0], &DAT_004c1e00[0], temp_s1);
}
