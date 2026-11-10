extern "C" {
int FUN_00337630(int, int, int, int, int, int, int, int);
void FUN_003378e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
}

extern "C" void FUN_00337410(unsigned long long *arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned arg6) {
    *arg0 = (unsigned long long)arg6 | (((unsigned long long)arg5 << 26) | (((unsigned long long)arg4 << 28) | (((unsigned long long)arg3 << 31) | (((unsigned long long)arg1 << 63) | ((unsigned long long)(arg2 & ~0xFU) << 32)))));
}

extern "C" void FUN_00337480(void *arg0, unsigned long long arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    unsigned long long m;
    int *p = (int *)arg0;
    p[0] = (arg6 << 0xF) | arg7;
    p[1] = (arg2 << 0x1C) | ((arg3 << 0x1A) | ((arg5 << 0xE) | (arg4 << 0xF)));
    m = 0xFFFF;
    m = (m << 16) | 0xFFFF;
    p[2] = (int)(arg1 & m);
    p[3] = (int)(arg1 >> 32);
}

extern "C" static void FUN_003374e0(int *arg0, int arg1, unsigned long long arg2) {
    arg0[0] = (int)(arg2 & 0xFFFFFFFF); arg0[1] = (int)(arg2 >> 32);
    arg0[2] = arg1;
    arg0[3] = 0;
}

extern "C" void FUN_00337520(int *arg0, unsigned int dbp, unsigned int dbw, unsigned int dpsm) {
    FUN_003374e0(arg0, 0x50, (unsigned long long)dbp << 32 | ((unsigned long long)dpsm << 56 | (unsigned long long)dbw << 48));
}

extern "C" void FUN_00337570(int *arg0, unsigned int dir, unsigned int dsax, unsigned int dsay) {
    FUN_003374e0(arg0, 0x51, (unsigned long long)dsax << 32 | ((unsigned long long)dir << 59 | (unsigned long long)dsay << 48));
}

extern "C" void FUN_003375c0(int *arg0, unsigned int rrw, unsigned int rrh) {
    FUN_003374e0(arg0, 0x52, (unsigned long long)rrh << 32 | rrw);
}

extern "C" void FUN_00337600(int arg0, unsigned int arg1) {
    FUN_003374e0((int *)arg0, 0x53, arg1);
}

void FUN_003378e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    FUN_00337630(a0, a1, 0x400, a2, a3, a4, a5, a6);
}
