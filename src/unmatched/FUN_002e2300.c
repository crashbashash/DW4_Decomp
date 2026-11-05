/* 0x002e2300 — FUN_002e2300. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int Memory_FreeBufferAlias_002ed5c0();

int FUN_002e2300(int arg0, long long arg1) {
    if (arg0 != 0) {
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAlias_002ed5c0();
        }
    }
    return arg0;
}
