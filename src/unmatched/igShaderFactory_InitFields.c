int FUN_002be100();
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00199110(void);
extern int DAT_0048b678[4];
extern int DAT_0048b688[4];
extern int DAT_0048b698[4];
extern int DAT_0048b6a8[4];
extern int DAT_0048b6b8[4];
extern int DAT_00561528[4];
void igShaderFactory_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_00561528[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b678[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_002be100();
    *(unsigned char *)((char *)(temp_s1) + 52) = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_002be100();
    *(unsigned char *)((char *)(temp_s1_2) + 52) = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    FUN_002dc7a0(temp_v0, &DAT_0048b6b8[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(FUN_00199110);
    igMetaObject_NameFields(temp_s0, &DAT_0048b688[0], &DAT_0048b698[0], &DAT_0048b6a8[0], temp_s2);
}
