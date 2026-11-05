/* 0x00246780 — 32 bytes. Copies a global into *p when p is non-null, then returns
 * another global. 4 relocations (two HI16/LO16 pairs) against 0x0056df30 — the
 * array form is what makes MWCC use absolute lui/lw rather than gp-relative
 * addressing, which is how retail addresses it. */
extern int D_0056df30[4];
int FUN_00246780(int *p) { if (p) *p = D_0056df30[2]; return D_0056df30[0]; }
