/* 0x003c9080 — beNDMWItemRevisionBase_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc108[4];
extern int DAT_004cc110[4];
extern int DAT_004cc118[4];
extern int DAT_004cc120[4];
extern int DAT_0058bf78[4];
void beNDMWItemRevisionBase_InitFields(void);
}
void beNDMWItemRevisionBase_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058bf78[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc108[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc110[0], &DAT_004cc118[0], &DAT_004cc120[0], temp_s1);
}
