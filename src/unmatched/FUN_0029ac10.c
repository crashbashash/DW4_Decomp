/* 0x0029ac10 — FUN_0029ac10 (56 bytes). Stores two values in the work area from FUN_00294a30 (+80, +84). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct {
    char pad0[80];
    int f80;
    int f84;
} Work29ac10;
extern Work29ac10 *FUN_00294a30(void);

void FUN_0029ac10(int a, int b) {
    Work29ac10 *work = FUN_00294a30();

    work->f80 = a;
    work->f84 = b;
}
