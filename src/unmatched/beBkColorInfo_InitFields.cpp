/* 0x00369d50 — beBkColorInfo_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7b58[4];
extern int DAT_004c7b60[4];
extern int DAT_004c7b68[4];
extern int DAT_004c7b70[4];
extern int DAT_00589d00[4];
void beBkColorInfo_InitFields(void);
}
void beBkColorInfo_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589d00[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7b58[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7b60[0], &DAT_004c7b68[0], &DAT_004c7b70[0], temp_s1);
}
