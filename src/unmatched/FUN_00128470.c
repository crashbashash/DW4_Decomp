/* 0x00128470 — FUN_00128470. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001251c8();
int FUN_00126df8();
extern int DAT_004d4050[4];
void FUN_00128470(void *arg0, int arg1) {
    FUN_001251c8(*(int *)((char *)(arg0) + 12), &DAT_004d4050[0], arg1);
    FUN_00126df8(arg0);
}
