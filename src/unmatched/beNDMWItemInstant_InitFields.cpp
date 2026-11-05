/* 0x003c8540 — beNDMWItemInstant_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc0a8[4];
extern int DAT_004cc0b0[4];
extern int DAT_004cc0b8[4];
extern int DAT_004cc0c0[4];
extern int DAT_0058bf28[4];
void beNDMWItemInstant_InitFields(void);
}
void beNDMWItemInstant_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bf28[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc0a8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc0b0[0], &DAT_004cc0b8[0], &DAT_004cc0c0[0], temp_s1);
}
