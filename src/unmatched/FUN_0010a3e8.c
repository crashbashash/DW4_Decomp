/* 0x0010a3e8 — 12 bytes. Tail-calls FUN_00109b10 forwarding its own incoming a0 as the
 * callee's FIRST argument and passing &DAT_004d2388 as the SECOND (retail: `lui a1,0x4d`); the
 * one-argument spelling puts the pointer in a0 and misses. */
int FUN_00109b10();
extern int DAT_004d2388[4];
void FUN_0010a3e8(int self) {
    FUN_00109b10(self, &DAT_004d2388[0]);
}
