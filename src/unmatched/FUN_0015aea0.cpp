extern "C" {
int memcpy(...);
int Memory_FreeBuffer(...);
}
class O { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
 virtual int v21(unsigned int, int, int, int);
 virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32();
 virtual void v33();
 virtual void v34();
 char pad[8]; void *f0c; unsigned int f10;
};
extern "C" int FUN_0015aea0(O *arg0, unsigned int arg1, int arg2, int arg3, int arg4) {
    unsigned int n;
    int *s1;
    unsigned short *s0;
    int ret;
    unsigned int i;
    int *d4;
    short *d2;

    n = arg0->f10;
    n = (n < arg1) ? n : arg1;
    s1 = 0;
    s0 = 0;
    arg0->v33();
    if (arg3 == 0) {
        s0 = (unsigned short *)arg0->f0c;
    } else {
        s1 = (int *)arg0->f0c;
    }
    arg0->f0c = 0;
    arg0->f10 = 0;
    ret = arg0->v21(arg1, arg2, arg3, arg4);
    if (s0 != 0) {
        if (arg3 == 0) {
            memcpy(arg0->f0c, s0, n * 2);
        } else {
            d4 = (int *)arg0->f0c;
            for (i = 0; i < n; i++) {
                d4[i] = s0[i];
            }
        }
        Memory_FreeBuffer(s0);
    } else {
        if (arg3 == 1) {
            memcpy(arg0->f0c, s1, n * 4);
        } else {
            d2 = (short *)arg0->f0c;
            for (i = 0; i < n; i++) {
                d2[i] = s1[i];
            }
        }
        Memory_FreeBuffer(s1);
    }
    arg0->v34();
    return ret;
}
