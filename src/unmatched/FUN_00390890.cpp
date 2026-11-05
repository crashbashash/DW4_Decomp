/* 0x00390890 — FUN_00390890. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int FUN_001e06c0(int, int, void (*)(void));
int FUN_00356d10();
void FUN_003902f0(void);  /* code at 0x3902f0, passed by address (was DAT_3902f0; docs/engine/function-inventory.md) */
extern int DAT_00562640[4];
void FUN_00390890(void);
}
void FUN_00390890(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_00356d10(), FUN_003902f0);
}
