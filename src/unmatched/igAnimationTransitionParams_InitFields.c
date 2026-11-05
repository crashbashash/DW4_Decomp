/* 0x001a9d20 — igAnimationTransitionParams_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048d620[4];
extern int DAT_0048d630[4];
extern int DAT_0048d640[4];
extern int DAT_0048d650[4];
extern int DAT_00562400[4];
void igAnimationTransitionParams_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00562400[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d620[0], 4);
    igMetaObject_NameFields(temp_s0, &DAT_0048d630[0], &DAT_0048d640[0], &DAT_0048d650[0], temp_s1);
}
