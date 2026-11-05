/* 0x00344180 — beSoundData_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int FUN_002ea4b0(int, int);
int FUN_0030a520(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3830[4];
extern int DAT_004c3850[4];
extern int DAT_004c3870[4];
extern int DAT_004c3890[4];
extern int DAT_00587e68[4];
void beSoundData_InitFields(void);
}
void beSoundData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00587e68[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3830[0], 6);
    FUN_0030a520(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    FUN_0030a520(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), -1);
    FUN_0030a520(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c3850[0], &DAT_004c3870[0], &DAT_004c3890[0], temp_s1);
}
