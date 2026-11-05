extern long long DAT_0056c190[];
extern float GPR_005548b8;
void FUN_0020d290(long long *arg0) {
    unsigned int t;
    float f;
    unsigned int u;
    t = *(volatile unsigned int *)0x10000800;
    f = GPR_005548b8 * (float)t;
    u = (unsigned int)f;
    *arg0 = (DAT_0056c190[0] + u) * 100;
}
