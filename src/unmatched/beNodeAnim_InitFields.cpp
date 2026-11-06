/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int FUN_002d3890(void *, int);
int FUN_002e3810(void *, float);
int FUN_002ebc00(void *, long long);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4a70[4];
extern int DAT_004c4aa0[4];
extern int DAT_004c4ad0[4];
extern int DAT_004c4b00[4];
extern int DAT_00588700[4];
void beNodeAnim_InitFields(void);
}
void beNodeAnim_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588700[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4a70[0], 0xA);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0x13DE4355);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0x77359400);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), ((long long)0xEE6B << 0x10) | 0x2800);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6), 1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_004c4aa0[0], &DAT_004c4ad0[0], &DAT_004c4b00[0], temp_s1);
}
