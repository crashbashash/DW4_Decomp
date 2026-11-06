/* Forwards its eleven arguments to FUN_0025ffd0 when DAT_00499cd0 is set, otherwise to
 * FUN_00260398. */
extern int DAT_00499cd0;
void FUN_0025ffd0(int a0, int a1, int a2, int a3, int a4, int a5, short a6, short a7, int a8, short a9, short a10);
void FUN_00260398(int a0, int a1, int a2, int a3, int a4, int a5, short a6, short a7, int a8, short a9, short a10);

void FUN_002606e0(int a0, int a1, int a2, int a3, int a4, int a5, short a6, short a7, int a8, short a9, short a10) {
    if (DAT_00499cd0 == 0) {
        FUN_00260398(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
        return;
    }
    FUN_0025ffd0(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
