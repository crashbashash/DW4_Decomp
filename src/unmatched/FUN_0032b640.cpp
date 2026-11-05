extern "C" {
int FUN_0010f738(...);
int FUN_0010f970(...);
int memcpy(...);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(); char pad[20]; int f18; char pad2[24]; int f34; int f38; int f3c; };
extern "C" int FUN_0032b640(A *arg0, int arg1, int arg2, int arg3);
int FUN_0032b640(A *arg0, int arg1, int arg2, int arg3) {
    int base;
    int r;
    int q;
    int bytes;
    int a1;
    int lim;
    if (arg0->f18 < 0) {
        return -1;
    }
    base = arg0->vX();
    if (arg0->f3c == 1) {
        r = FUN_0010f970(arg0->f18, arg1, arg3 * arg2);
        arg3 = r / arg2;
        q = arg3 * arg2;
        if (r != q) {
            FUN_0010f738(arg0->f18, base + q, 0);
        }
        return arg3;
    }
    a1 = arg0->f34;
    bytes = arg2 * arg3;
    lim = arg0->f38;
    if (lim < a1 + bytes) {
        arg3 = (lim - a1) / arg2;
        bytes = arg3 * arg2;
    }
    memcpy(arg1, *(int *)((char *)arg0 + 44) + a1, bytes);
    arg0->f34 = arg0->f34 + bytes;
    return arg3;
}
