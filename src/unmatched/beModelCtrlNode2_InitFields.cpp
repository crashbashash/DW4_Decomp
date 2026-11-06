/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int FUN_0013af00(void);
int FUN_002e3810(void *, float);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4d50[4];
extern int DAT_004c4d60[4];
extern int DAT_004c4d70[4];
extern int DAT_004c4d80[4];
extern int DAT_00588860[4];
void beModelCtrlNode2_InitFields(void);
}
void beModelCtrlNode2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588860[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4d50[0], 4);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1.0f);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    *(int *)((char *)(temp_s1) + 56) = FUN_0013af00();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c4d60[0], &DAT_004c4d70[0], &DAT_004c4d80[0], temp_s2);
}
