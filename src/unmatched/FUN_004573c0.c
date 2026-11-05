/* 0x004573c0 — FUN_004573c0. Tail call that forwards a0/a1, inserts the constant 32 and shifts a2 to a3
 * (the m2c draft dropped the leading arguments); verified byte-identical by tools/verify.py. */
int FUN_004573f0();

void FUN_004573c0(int arg0, int arg1, int arg2) {
    FUN_004573f0(arg0, arg1, 32, arg2);
}
