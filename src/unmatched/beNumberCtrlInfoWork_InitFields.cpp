extern "C" {
int FUN_002ea4b0(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4900[4];
extern int DAT_004c4910[4];
extern int DAT_004c4920[4];
extern int DAT_004c4930[4];
extern int DAT_00588630[4];
void beNumberCtrlInfoWork_InitFields(void);
}
void beNumberCtrlInfoWork_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588630[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4900[0], 3);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004c4910[0], &DAT_004c4920[0], &DAT_004c4930[0], temp_s1);
}
