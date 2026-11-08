typedef struct { char p0[456]; int a; char p1[1636]; int b; } M;
int FUN_00113f20(void);
int FUN_00113f78(void);
void sceIpuSync(int, int);
void FUN_00109a00(M *m) {
    int s;
    m->b = 1;
    m->a = 0;
    s = FUN_00113f20();
    *(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 | 0x10000;
    *(volatile unsigned int *)0x1000b000 = 0;
    *(volatile unsigned int *)0x1000b400 = 0;
    *(volatile unsigned int *)0x1000d400 = 0;
    *(volatile unsigned int *)0x1000f590 = *(volatile unsigned int *)0x1000f520 & ~0x10000;
    if (s) FUN_00113f78();
    *(volatile unsigned int *)0x1000b020 = 0;
    *(volatile unsigned int *)0x1000b420 = 0;
    *(volatile unsigned int *)0x1000d420 = 0;
    *(volatile unsigned int *)0x10002010 = 0x40000000;
    sceIpuSync(0, 0);
}
