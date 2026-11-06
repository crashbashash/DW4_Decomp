/* Float second argument (mtc1 zero) of the field-init helper. C++ translation unit: the unit
 * compiled with exceptions on and retail keeps this function's exception index record, which only
 * the C++ front end emits. */
extern "C" {
int FUN_002e3810(void *, float);
int FUN_00356cc0(void);
int FUN_00365550(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5ae0[4];
extern int DAT_004c5b20[4];
extern int DAT_004c5b60[4];
extern int DAT_004c5ba0[4];
extern int DAT_00588eb0[4];
void beMeterCtrlOneData_InitFields(void);
}
void beMeterCtrlOneData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)DAT_00588eb0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5ae0[0], 0xE);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00356cc0();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 0.0f);
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_00365550();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00365550();
    igMetaObject_NameFields(temp_s0, &DAT_004c5b20[0], &DAT_004c5b60[0], &DAT_004c5ba0[0], temp_s2);
}
