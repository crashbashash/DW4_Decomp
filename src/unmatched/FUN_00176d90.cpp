class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void set(int,int,float *); virtual void get(int,int,float *); int pad[4]; unsigned flags; };
struct V2 { float x, y; };
class W { public: int pad[6]; O *o; };
extern "C" {
int FUN_0015d880(...);
void FUN_00176d90(W *arg0, int arg1, int arg2, float *arg3);
}
void FUN_00176d90(W *arg0, int arg1, int arg2, float *arg3) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    V2 a;
    V2 b;
    if (arg0->o->flags & 0x10) {
        arg0->o->get(0, arg2, &a.x);
        arg0->o->get(1, arg2, &b.x);
        if (arg1 == 0) {
            b.y = arg3[1];
            a.x = arg3[0];
            arg0->o->set(0, arg2, &a.x);
            arg0->o->set(1, arg2, &b.x);
            return;
        }
        a.y = arg3[1];
        b.x = arg3[0];
        arg0->o->set(0, arg2, &a.x);
        arg0->o->set(1, arg2, &b.x);
        return;
    }
    FUN_0015d880(arg0);
}
