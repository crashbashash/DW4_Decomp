extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c74f0[4];
extern int DAT_004c7520[4];
extern int DAT_004c7550[4];
extern int DAT_004c7580[4];
extern int DAT_00589a20[4];
void beCriFxXbData_InitFields(void);
}
void beCriFxXbData_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589a20[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c74f0[0], 0xC);
    igMetaObject_NameFields(temp_s0, &DAT_004c7520[0], &DAT_004c7550[0], &DAT_004c7580[0], temp_s1);
}
