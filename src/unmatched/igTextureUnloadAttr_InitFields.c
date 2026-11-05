int FUN_00132ba0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485ab8[4];
extern int DAT_00485ac0[4];
extern int DAT_00485ac8[4];
extern int DAT_00485ad0[4];
extern void * DAT_0055ec90[4];
int FUN_00141840();

void igTextureUnloadAttr_InitFields(void) {
    void *temp_s0;
    int temp_s2;
    void *temp_s1;
    void *temp_s3;

    temp_s0 = DAT_0055ec90[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485ab8[0], 2);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2);
    *(int *)((char *)temp_s1 + 56) = FUN_00132ba0();
    *(char *)((char *)temp_s1 + 60) = 0;
    temp_s3 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(int *)((char *)temp_s3 + 48) = (int)FUN_00141840;
    igMetaObject_NameFields(temp_s0, &DAT_00485ac0[0], &DAT_00485ac8[0], &DAT_00485ad0[0], temp_s2);
}
