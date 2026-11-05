/* 0x0019d580 — igModelViewMatrixBoneSelect_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ea4b0();
int igMetaObject_CreateFields();
int igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048bcd8[4];
extern int DAT_0048bce0[4];
extern int DAT_0048bce8[4];
extern int DAT_0048bcf0[4];
extern int DAT_00561888[4];
void igModelViewMatrixBoneSelect_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00561888[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048bcd8[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_0048bce0[0], &DAT_0048bce8[0], &DAT_0048bcf0[0], temp_s1);
}
