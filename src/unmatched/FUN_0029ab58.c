/* Stores four values in the work area from FUN_00294a30 (+64..+76). */
typedef struct {
    char pad0[64];
    int f64;
    int f68;
    int f72;
    int f76;
} Work29ab58;
extern Work29ab58 *FUN_00294a30(void);

void FUN_0029ab58(int a, int b, int c, int d) {
    Work29ab58 *work = FUN_00294a30();

    work->f64 = a;
    work->f68 = b;
    work->f72 = c;
    work->f76 = d;
}
