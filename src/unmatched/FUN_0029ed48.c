/* 0x0029ed48 — 32 bytes. Wrapper: returns FUN_002adc40(self, 0x31) != 0. The
 * literal is the callee's SECOND argument; its first is this function's incoming a0,
 * passed through untouched (retail: `li a1,49`, not `li a0,49`). */
int FUN_002adc40();

int FUN_0029ed48(int self) {
    return FUN_002adc40(self, 0x31) != 0;
}
