class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void v108(void *,int); virtual void v112(void *,int); };
extern "C" {
extern float DAT_00554914;
extern float DAT_00554918;
int FUN_0015db90(...);
}
struct Acc { int f0; int f4; int f8; unsigned int cnt; char *data; int stride; };
struct G { char pad0[12]; VC *f12; char pad1[12]; int f28; };
extern "C" void Gap__Core__igGeometryAttr1_5__vfunc_34(G *arg0, float *arg1, float *arg2);
void Gap__Core__igGeometryAttr1_5__vfunc_34(G *arg0, float *arg1, float *arg2) {
    Acc acc;
    float mz = DAT_00554914;
    float my = mz;
    float mx = mz;
    float nz = DAT_00554918;
    float ny = nz;
    float nx = nz;
    unsigned int i;
    int st;
    char *d;
    unsigned int n;
    volatile float *p;
    float t;
    FUN_0015db90(&acc);
    acc.f4 = 0;
    acc.f0 = 0;
    acc.f8 = arg0->f28;
    acc.cnt = 0;
    arg0->f12->v108(&acc, 0);
    n = acc.cnt;
    st = acc.stride;
    d = acc.data;
    for (i = 0; i < n; i++) {
        p = (volatile float *)(d + i * st);
        t = p[0];
        if (!(mx <= t)) { mx = t; }
        t = p[1];
        if (!(my <= t)) { my = t; }
        t = p[2];
        if (!(mz <= t)) { mz = t; }
        t = p[0];
        if (nx < t) { nx = t; }
        t = p[1];
        if (ny < t) { ny = t; }
        t = p[2];
        if (nz < t) { nz = t; }
    }
    arg1[0] = mx;
    arg1[1] = my;
    arg1[2] = mz;
    arg2[0] = nx;
    arg2[1] = ny;
    arg2[2] = nz;
    arg0->f12->v112(&acc, 0);
}
