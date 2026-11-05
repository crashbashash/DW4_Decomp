extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
struct Buf { char pad[2036]; int f2036; int pad2; int f2044; int f2048; int pad3; int f2056; };
class Pool { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void v51();
    char pad0[105 - 4]; char f105; char pad1[6]; Buf *buf; unsigned char busy; char pad3[7]; int f124; char f128; char pad4[7]; long long f136; char pad5[16]; long long f160;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_24(int *out, Pool *p, int a2, long long a3, char t0) {
    if (p->busy == 0) {
        p->f124 = a2;
        p->buf->f2036 = a2;
        unsigned long long m = a3 & 0xFFFFFFFFFFFFFFFCULL;
        p->f160 = m;
        p->f128 = t0;
        p->buf->f2044 = (int)m;
        p->buf->f2048 = (int)m;
        p->buf->f2056 = (int)m;
        p->v51();
        p->f136 = 0;
        p->f105 = t0;
        *out = DAT_004fb410[0];
    } else {
        *out = DAT_004fb418[0];
    }
}
