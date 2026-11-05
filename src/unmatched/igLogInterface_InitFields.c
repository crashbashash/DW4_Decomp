/* 0x00226750 — igLogInterface_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00497c60[4];
extern int DAT_00497c68[4];
extern int DAT_00497c70[4];
extern int DAT_00497c78[4];
extern int DAT_0056d8c8[4];
void igLogInterface_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0056d8c8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497c60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00497c68[0], &DAT_00497c70[0], &DAT_00497c78[0], temp_s1);
}
