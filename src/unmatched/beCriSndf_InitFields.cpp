/* 0x00367660 — beCriSndf_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7600[4];
extern int DAT_004c7610[4];
extern int DAT_004c7620[4];
extern int DAT_004c7630[4];
extern int DAT_00589ab0[4];
void beCriSndf_InitFields(void);
}
void beCriSndf_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00589ab0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7600[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c7610[0], &DAT_004c7620[0], &DAT_004c7630[0], temp_s1);
}
