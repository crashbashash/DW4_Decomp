/* 0x00346480 — beSeData_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c3bd8[4];
extern int DAT_004c3be0[4];
extern int DAT_004c3be8[4];
extern int DAT_004c3bf0[4];
extern int DAT_00587fd0[4];
void beSeData_InitFields(void);
}
void beSeData_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00587fd0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3bd8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c3be0[0], &DAT_004c3be8[0], &DAT_004c3bf0[0], temp_s1);
}
