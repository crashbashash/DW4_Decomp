/* Two optional buffer allocations through a virtual call, summing the sizes; locals declared in
 * the order the allocator needs; alternate compiler. */
struct S;
extern "C" int FUN_0015f350(S *arg0);
class V1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned int * vX(); };
class V2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };

struct S : V1 { char p[4]; char *f8; int f12; char q[8]; V2 *f24; };
int FUN_0015f350(S *arg0) {
    int var_s2;
    int *temp_s1;
    unsigned int temp_s0;
    int n;
    V2 *a;
    temp_s0 = *arg0->vX();
    var_s2 = 0;
    if (temp_s0 & 0x400000) {
        a = arg0->f24;
        temp_s1 = (int *)(arg0->f8 + 0x44);
        n = arg0->f12;
        *temp_s1 = a->vX(n * 12);
        var_s2 += n * 12;
    }
    if (temp_s0 & 0x800000) {
        a = arg0->f24;
        temp_s1 = (int *)(arg0->f8 + 0x48);
        n = arg0->f12 * 12;
        *temp_s1 = a->vX(n);
        var_s2 += n;
    }
    return var_s2;
}

