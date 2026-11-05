/* 0x003a3900 — FUN_003a3900. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int FUN_001e06c0(int, int, int ( *)());
int FUN_0036e610();
extern int DAT_00562640[4];
int FUN_003a3850();
void FUN_003a3900(void);
}

void FUN_003a3900(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0036e610(), &FUN_003a3850);
}
