#include "dw4/reflected.h"
struct Vobj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual int v41();
};
struct L4 { char pad[180]; unsigned char b180; };
struct L2 { char pad[12]; L4 *p12; };
struct L1 { char pad[44]; L2 *p44; };
struct B { char pad[16]; long long ll16; };
struct S {
    igInsightCore *a; L1 *p4; char pad8[8]; unsigned char f16; char pad17[3]; B *b20; Vobj *c24;
};
extern "C" void FUN_00237730(igInsightCore *);
extern "C" void FUN_00236f30(igInsightCore *, B *);
extern "C" int FUN_00463bc0(S *s) {
    FUN_00237730(s->a);
    if (s->f16) {
        igInsightCore *t = s->a;
        long long v = t->_currentTime;
        if (v > 4000000000LL) {
            FUN_00236f30(t, s->b20);
            s->f16 = 0;
        } else {
            s->b20->ll16 = v;
        }
    }
    int r = (s->p4->p44->p12->b180 != 0) ^ 1;
    if (r) {
        r = s->c24->v41() != 0;
    }
    return r;
}
