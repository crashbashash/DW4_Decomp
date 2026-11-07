extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc5d8[4];
extern int DAT_004cc5e0[4];
extern int DAT_004cc5e8[4];
extern int DAT_004cc5f0[4];
extern int DAT_0058c130[4];
void beNDMWAfsSetupData_InitFields(void);
}
void beNDMWAfsSetupData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c130[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc5d8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc5e0[0], &DAT_004cc5e8[0], &DAT_004cc5f0[0], temp_s1);
}
