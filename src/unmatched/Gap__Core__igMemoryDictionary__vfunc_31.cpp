struct R { int v; R() {} R(int x) { v = x; } R(const R &o) : v(o.v) {} };
struct E { int key; int val; };
struct S { char pad[8]; int f8; char pad2[4]; E *f10; };
class D { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int v132(int); virtual R v136(int); char pad[8]; int f12; S *f10; };
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
R Gap__Core__igMemoryDictionary__vfunc_31(D *arg1, int key, int val);
}
R Gap__Core__igMemoryDictionary__vfunc_31(D *arg1, int key, int val) {
    int probes = 0;
    int cap = arg1->f10->f8 / 2;
    int half = cap / 2;
    int idx;
    S *s;
    E *e;
    if (cap != 0) {
        idx = arg1->v132(key);
        s = arg1->f10;
        e = &s->f10[idx];
        do {
            if (e->key == key) {
                e->val = val;
                return R(DAT_004fb410[0]);
            }
            if (e->key == 0) {
                e->key = key;
                e->val = val;
                arg1->f12 = arg1->f12 + 1;
                if (probes >= half) {
                    return arg1->v136(cap * 2);
                }
                return R(DAT_004fb410[0]);
            }
            idx++;
            if (idx >= cap) {
                e = *(E *volatile *)&s->f10;
                idx = 0;
            } else {
                e++;
            }
            probes++;
        } while (probes < cap);
    }
    return R(DAT_004fb418[0]);
}
