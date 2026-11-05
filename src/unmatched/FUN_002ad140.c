/* 0x002ad140 — 32 bytes. Wrapper: returns FUN_002b03e8(self, 1) != 0. The literal 1 is
 * the callee's second argument; its first is the incoming a0, passed through. */
int FUN_002b03e8();

int FUN_002ad140(int self) {
    return FUN_002b03e8(self, 1) != 0;
}
