/* 0x003666f0 — beCriSfpData_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c73d0[4];
extern int DAT_004c73e0[4];
extern int DAT_004c73f0[4];
extern int DAT_004c7400[4];
extern int DAT_00589998[4];
void beCriSfpData_InitFields(void);
}
void beCriSfpData_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589998[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c73d0[0], 4);
    igMetaObject_NameFields(temp_s0, &DAT_004c73e0[0], &DAT_004c73f0[0], &DAT_004c7400[0], temp_s1);
}
