/* 0x0036bbf0 — beActionStarterData2_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7df8[4];
extern int DAT_004c7e00[4];
extern int DAT_004c7e08[4];
extern int DAT_004c7e10[4];
extern int DAT_00589e48[4];
void beActionStarterData2_InitFields(void);
}
void beActionStarterData2_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589e48[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7df8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7e00[0], &DAT_004c7e08[0], &DAT_004c7e10[0], temp_s1);
}
