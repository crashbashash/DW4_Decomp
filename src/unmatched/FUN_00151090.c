/* 0x00151090 — 8 bytes.
 *   retail: 03e00008  jr  $ra
 *           0080102d  move $v0, $a0
 * Identity function; degenerate but it is a real target and a worked example of
 * the src/<symbol>.c convention. */
int FUN_00151090(int a) { return a; }
