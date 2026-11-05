/* 0x001335a0 — igStencilStateAttr_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00485e48[4];
extern int DAT_00485e50[4];
extern int DAT_00485e58[4];
extern int DAT_00485e60[4];
extern int DAT_0055ee40[4];
void igStencilStateAttr_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0055ee40[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485e48[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_00485e50[0], &DAT_00485e58[0], &DAT_00485e60[0], temp_s1);
}
