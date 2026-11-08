struct ArraySizeOwner;
extern "C" int FUN_0015f350(ArraySizeOwner *arg0);
class ArraySizeOwnerBase { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned int * vX(); };
class ArraySizeAllocator { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };

struct ArraySizeOwner : ArraySizeOwnerBase { char p[4]; char *f8; int f12; char q[8]; ArraySizeAllocator *f24; };
int FUN_0015f350(ArraySizeOwner *arg0) {
    int total;
    int *dst;
    unsigned int flags;
    int n;
    flags = *arg0->vX();
    total = 0;
    if (flags & 0x400000) { dst = (int *)(arg0->f8 + 0x44); n = arg0->f12 * 12; *dst = arg0->f24->vX(n); total += n; }
    if (flags & 0x800000) { dst = (int *)(arg0->f8 + 0x48); n = arg0->f12 * 12; *dst = arg0->f24->vX(n); total += n; }
    return total;
}
