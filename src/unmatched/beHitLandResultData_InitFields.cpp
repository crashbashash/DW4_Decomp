extern "C" {
int igStringMetaField_SetDefaultText(int, int *);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c6760[4];
extern int DAT_004c6768[4];
extern int DAT_004c6770[4];
extern int DAT_004c6778[4];
extern int DAT_00502a98[4];
extern int DAT_005893e8[4];
void beHitLandResultData_InitFields(void);
}
void beHitLandResultData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_005893e8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6760[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1), &DAT_00502a98[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004c6768[0], &DAT_004c6770[0], &DAT_004c6778[0], temp_s1);
}
