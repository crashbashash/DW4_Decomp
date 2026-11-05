/* 0x002c2600 — igLibrary_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c05a0[4];
extern int DAT_004c05a8[4];
extern int DAT_004c05b0[4];
extern int DAT_004c05b8[4];
extern int DAT_005860c0[4];
void igLibrary_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005860c0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c05a0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c05a8[0], &DAT_004c05b0[0], &DAT_004c05b8[0], temp_s1);
}
