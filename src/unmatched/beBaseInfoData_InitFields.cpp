extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7d80[4];
extern int DAT_004c7d88[4];
extern int DAT_004c7d90[4];
extern int DAT_004c7d98[4];
extern int DAT_00589e08[4];
void beBaseInfoData_InitFields(void);
}
void beBaseInfoData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589e08[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7d80[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7d88[0], &DAT_004c7d90[0], &DAT_004c7d98[0], temp_s1);
}
