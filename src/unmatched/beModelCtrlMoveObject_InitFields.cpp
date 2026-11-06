extern "C" {
int FUN_002e3810(int, float);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5390[4];
extern int DAT_004c53c0[4];
extern int DAT_004c53f0[4];
extern int DAT_004c5420[4];
extern int DAT_00588b48[4];
void beModelCtrlMoveObject_InitFields(void);
}
void beModelCtrlMoveObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588b48[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5390[0], 9);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5), 0.0f);
    igMetaObject_NameFields(temp_s0, &DAT_004c53c0[0], &DAT_004c53f0[0], &DAT_004c5420[0], temp_s1);
}
