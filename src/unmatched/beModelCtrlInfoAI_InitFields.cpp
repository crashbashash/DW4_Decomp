/* 0x00352360 — beModelCtrlInfoAI_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c5270[4];
extern int DAT_004c5290[4];
extern int DAT_004c52b0[4];
extern int DAT_004c52d0[4];
extern int DAT_00588ad0[4];
void beModelCtrlInfoAI_InitFields(void);
}
void beModelCtrlInfoAI_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588ad0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5270[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c5290[0], &DAT_004c52b0[0], &DAT_004c52d0[0], temp_s1);
}
