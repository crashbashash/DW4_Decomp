extern long long DAT_0056c190[];
void FUN_0020d290(long long *arg0) {
    unsigned int t;
    float f;
    unsigned int u;
    t = *(unsigned int *)0x10000800;
    f = 1.08506942f * (float)t;
    u = (unsigned int)f;
    *arg0 = (DAT_0056c190[0] + u) * 100;
}
