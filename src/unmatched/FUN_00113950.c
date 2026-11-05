/* 0x00113950 — FUN_00113950. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00113990();
int GetMemorySize();
int _InitTLB();

void FUN_00113950(void) {
    if (GetMemorySize() == 0x02000000) {
        FUN_00113990();
        return;
    }
    _InitTLB();
}
