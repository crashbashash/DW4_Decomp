class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int v112(int, int *, int); };
struct S { char p0[24]; int f24; char p1[16]; unsigned char f44; char p2[7]; int f52; int f56; unsigned char *f60; V *f64; };
extern "C" {
int Gap__Core__igMediaFile__vfunc_33(S *arg0);
int Gap__Core__igMediaFile__vfunc_33(S *arg0) {
    int sp1C;
    int t;
    if (arg0->f44 != 0) {
        int a = *(unsigned int *)&arg0->f24;
        V *v = arg0->f64;
        if (v->v112(a, &sp1C, 1) != 0) {
            return sp1C;
        }
        return -1;
    }
    t = arg0->f56;
    if (t >= arg0->f52) {
        return -1;
    }
    arg0->f56 = t + 1;
    return arg0->f60[arg0->f56 - 1];
}
}
