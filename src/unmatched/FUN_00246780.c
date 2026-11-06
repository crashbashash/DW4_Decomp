/* The array declaration makes the compiler address the global absolutely (lui/lw) instead of gp-
 * relative. */
extern int D_0056df30[4];
int FUN_00246780(int *p) { if (p) *p = D_0056df30[2]; return D_0056df30[0]; }
