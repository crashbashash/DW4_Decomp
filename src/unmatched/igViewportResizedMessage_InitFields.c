/* 0x00233410 — igViewportResizedMessage_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00498218[4];
extern int DAT_00498220[4];
extern int DAT_00498228[4];
extern int DAT_00498230[4];
extern int DAT_0056dc10[4];
void igViewportResizedMessage_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0056dc10[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498218[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_00498220[0], &DAT_00498228[0], &DAT_00498230[0], temp_s1);
}
