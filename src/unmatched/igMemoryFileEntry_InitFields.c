/* 0x002c0d10 — igMemoryFileEntry_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMetaObject_CreateFields();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c02d8[4];
extern int DAT_004c02e0[4];
extern int DAT_004c02e8[4];
extern int DAT_004c02f0[4];
extern int DAT_00585f48[4];
void igMemoryFileEntry_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00585f48[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c02d8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c02e0[0], &DAT_004c02e8[0], &DAT_004c02f0[0], temp_s1);
}
