/* 0x00195c90 — igTransformRecorder_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b140[4];
extern int DAT_0048b148[4];
extern int DAT_0048b150[4];
extern int DAT_0048b158[4];
extern int DAT_00561280[4];
void igTransformRecorder_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00561280[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b140[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_0048b148[0], &DAT_0048b150[0], &DAT_0048b158[0], temp_s1);
}
