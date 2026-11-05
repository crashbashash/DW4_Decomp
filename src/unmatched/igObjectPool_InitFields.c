/* 0x00196850 — igObjectPool_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d3890();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048b1d0[4];
extern int DAT_0048b1e0[4];
extern int DAT_0048b1f0[4];
extern int DAT_0048b200[4];
extern int DAT_005612e8[4];
void igObjectPool_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_005612e8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b1d0[0], 3);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 0x32);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1);
    igMetaObject_NameFields(temp_s0, &DAT_0048b1e0[0], &DAT_0048b1f0[0], &DAT_0048b200[0], temp_s1);
}
