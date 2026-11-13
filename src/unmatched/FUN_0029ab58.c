/* Stores four values in the work area from mwsfd_GetWork (+64..+76). */
typedef struct {
    char pad0[64];
    int f64;
    int f68;
    int f72;
    int f76;
} Work29ab58;
extern Work29ab58 *mwsfd_GetWork(void);

void FUN_0029ab58(int a, int b, int c, int d) {
    Work29ab58 *work = mwsfd_GetWork();

    work->f64 = a;
    work->f68 = b;
    work->f72 = c;
    work->f76 = d;
}
