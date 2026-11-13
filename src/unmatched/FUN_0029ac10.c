/* Stores two values in the work area from mwsfd_GetWork (+80, +84). */
typedef struct {
    char pad0[80];
    int f80;
    int f84;
} Work29ac10;
extern Work29ac10 *mwsfd_GetWork(void);

void FUN_0029ac10(int a, int b) {
    Work29ac10 *work = mwsfd_GetWork();

    work->f80 = a;
    work->f84 = b;
}
