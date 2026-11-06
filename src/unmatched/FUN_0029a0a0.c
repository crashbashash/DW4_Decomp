/* Calls FUN_0027e748(2, a, b, c) and records `a` in DAT_0057fa84. */
extern void FUN_0027e748(int kind, int a, int b, int c);
extern int DAT_0057fa84;

void FUN_0029a0a0(int a, int b, int c) {
    FUN_0027e748(2, a, b, c);
    DAT_0057fa84 = a;
}
