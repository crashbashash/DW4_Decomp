/* 0x00109ac8 — 16 bytes. Tail call: passes the incoming argument as the second
 * parameter and the constant string "[MPEG ERROR]%s\n" (0x004d22e8) as the first.
 * First verified function with a call (R_MIPS_26). */
extern char DAT_004d22e8[];
extern int FUN_0010d108(const char *, int);
int FUN_00109ac8(int a) { return FUN_0010d108(DAT_004d22e8, a); }
