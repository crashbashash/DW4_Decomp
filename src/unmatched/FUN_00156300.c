/* 0x00156300 — FUN_00156300. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMemoryRefMetaField_SetAlignmentType();
int FUN_00308860();
extern int DAT_004dee80[4];
extern int DAT_0055fde0[4];
extern int DAT_00586dd0[4];
void FUN_00156300(void) {
    FUN_00308860(DAT_00586dd0[0], &DAT_004dee80[0], 0x10);
    igMemoryRefMetaField_SetAlignmentType(DAT_0055fde0[0], &DAT_004dee80[0]);
}
