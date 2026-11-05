int FUN_0018e2f0();
int FUN_004505b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d0238[4];
extern int DAT_004d0240[4];
extern int DAT_004d0248[4];
extern int DAT_004d0250[4];
extern int DAT_0058c320[4];
void igMouseCursor_InitFields(void) {
    void *temp_s0;
    void *temp_a0;
    void *temp_s1;
    int buf[2];
    int temp_s2;

    temp_s0 = (void *)DAT_0058c320[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0238[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_004505b0();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    buf[0] = 0;
    buf[1] = 0;
    FUN_0018e2f0(temp_a0, buf);
    igMetaObject_NameFields(temp_s0, &DAT_004d0240[0], &DAT_004d0248[0], &DAT_004d0250[0], temp_s2);
}
