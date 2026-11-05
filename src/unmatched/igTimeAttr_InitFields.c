/* 0x001310d0 — igTimeAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ebc00();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485a90[4];
extern int DAT_00485a98[4];
extern int DAT_00485aa0[4];
extern int DAT_00485aa8[4];
extern int DAT_0055ec80[4];
void igTimeAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055ec80[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485a90[0], 1);
    FUN_002ebc00(igMetaObject_GetFieldAt(temp_s0, temp_s1), 0);
    igMetaObject_NameFields(temp_s0, &DAT_00485a98[0], &DAT_00485aa0[0], &DAT_00485aa8[0], temp_s1);
}
