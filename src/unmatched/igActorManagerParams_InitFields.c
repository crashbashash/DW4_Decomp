/* 0x0045e8c0 — igActorManagerParams_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004d1aa8[4];
extern int DAT_004d1ab0[4];
extern int DAT_004d1ab8[4];
extern int DAT_004d1ac0[4];
extern int DAT_0058ceb8[4];
void igActorManagerParams_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058ceb8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1aa8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004d1ab0[0], &DAT_004d1ab8[0], &DAT_004d1ac0[0], temp_s1);
}
