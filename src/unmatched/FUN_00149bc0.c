/* 0x00149bc0 — FUN_00149bc0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0014bbb0();
int FUN_0014bd20();
int FUN_0014c670();
int FUN_0014d5c0();
int FUN_0014d6d0();
int FUN_0014f810();
int FUN_0014f920();
int FUN_0014ff00();
extern unsigned char DAT_00554b1c[4];
void FUN_00149bc0(void) {
    if (DAT_00554b1c[0] == 0) {
        DAT_00554b1c[0] = 1;
        FUN_0014bbb0();
        FUN_0014bd20();
        FUN_0014c670();
        FUN_0014d5c0();
        FUN_0014d6d0();
        FUN_0014f810();
        FUN_0014f920();
        FUN_0014ff00();
    }
}
