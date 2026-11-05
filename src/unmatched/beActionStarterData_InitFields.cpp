/* 0x0036bfc0 — beActionStarterData_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7e20[4];
extern int DAT_004c7e40[4];
extern int DAT_004c7e60[4];
extern int DAT_004c7e80[4];
extern int DAT_00589e60[4];
void beActionStarterData_InitFields(void);
}
void beActionStarterData_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589e60[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7e20[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c7e40[0], &DAT_004c7e60[0], &DAT_004c7e80[0], temp_s1);
}
