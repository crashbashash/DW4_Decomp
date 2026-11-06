extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c44f8[4];
extern int DAT_004c4500[4];
extern int DAT_004c4508[4];
extern int DAT_004c4510[4];
extern int DAT_00588460[4];
void beResetNode_InitFields(void);
}
void beResetNode_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588460[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c44f8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c4500[0], &DAT_004c4508[0], &DAT_004c4510[0], temp_s1);
}
