/* Stores two values in the work area from FUN_00294a30 (+80, +84). */
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
