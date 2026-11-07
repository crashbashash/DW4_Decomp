extern "C" {
int igStringMetaField_SetDefaultText(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3420[4];
extern int DAT_004c3430[4];
extern int DAT_004c3440[4];
extern int DAT_004c3450[4];
extern int DAT_00587c50[4];
void beTimerData_InitFields(void);
}
void beTimerData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587c50[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3420[0], 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 0);
    igMetaObject_NameFields(temp_s0, &DAT_004c3430[0], &DAT_004c3440[0], &DAT_004c3450[0], temp_s1);
}
