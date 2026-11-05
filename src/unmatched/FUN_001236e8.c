/* 0x1236e8 — FUN_001236e8, m2c draft + manual source-shape fix (finding #663),
 * verified byte-identical to retail by tools/verify.py. */
long long FUN_0012c218();
long long FUN_001236e8(int arg0) {
    return (long long) (FUN_0012c218(arg0, 0, 0xA) << 0x20) >> 0x20;
}
