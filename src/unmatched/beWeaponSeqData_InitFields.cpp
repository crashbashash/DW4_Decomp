extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c2fd8[4];
extern int DAT_004c2fe0[4];
extern int DAT_004c2fe8[4];
extern int DAT_004c2ff0[4];
extern int DAT_00587a50[4];
void beWeaponSeqData_InitFields(void);
}
void beWeaponSeqData_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00587a50[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c2fd8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c2fe0[0], &DAT_004c2fe8[0], &DAT_004c2ff0[0], temp_s1);
}
