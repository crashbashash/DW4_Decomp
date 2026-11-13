int DIntr(void);
int EIntr(void);
void FUN_00109280(int sema);

long long FUN_00106660(char *d) {
    long long r;
    int n = 0;

    while ((r = *(volatile long long *)0x10002000) < 0 && !(*(volatile unsigned int *)0x10002010 & 0x4000)) {
        if (*(int *)(d + 4256)) {
            int intr = DIntr();
            *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
            *(volatile unsigned int *)0x1000B400 = 0;
            *(volatile unsigned int *)0x1000B000 = 0;
            *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
            if (intr) {
                EIntr();
            }
            *(volatile unsigned int *)0x1000B020 = 0;
            *(volatile unsigned int *)0x1000B420 = 0;
            *(volatile unsigned int *)0x10002010 = 0x40000000;
            break;
        }
        if (n++ > 5000) {
            FUN_00109280(*(int *)(d + 2160));
            n = 0;
        }
    }
    return r;
}
