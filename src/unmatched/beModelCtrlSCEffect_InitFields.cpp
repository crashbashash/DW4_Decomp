extern "C" {
int FUN_002ea4b0(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4c80[4];
extern int DAT_004c4ca0[4];
extern int DAT_004c4cc0[4];
extern int DAT_004c4ce0[4];
extern int DAT_00588800[4];
void beModelCtrlSCEffect_InitFields(void);
}
void beModelCtrlSCEffect_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588800[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4c80[0], 7);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004c4ca0[0], &DAT_004c4cc0[0], &DAT_004c4ce0[0], temp_s1);
}
