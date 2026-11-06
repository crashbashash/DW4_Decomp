/* Virtual call whose result may be replaced by a hook; running totals updated. */
struct S; struct A;
extern "C" { int FUN_002fe600(...); int igObject_GetSerializedSize(...); }
extern "C" void Gap__Core__igObjectDirEntry__vfunc_39(S *arg0, A *arg1);
struct R { char p[64]; void *(*f64)(); };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual R * vX(); };

struct S { char p[24]; V *f24; char q[20]; int f48; };
struct A { char p[144]; int f144; int f148; char q[40]; int f192; };
void Gap__Core__igObjectDirEntry__vfunc_39(S *arg0, A *arg1) {
    int temp_s0_2;
    void *(*temp_v1)();
    V *temp_s0;
    void *var_v0;

    temp_s0 = arg0->f24;
    R *r = temp_s0->vX();
    var_v0 = r;
    temp_v1 = r->f64;
    if (temp_v1 != 0) {
        var_v0 = temp_v1();
    }
    arg0->f48 = FUN_002fe600(arg1->f192, var_v0);
    temp_s0_2 = arg1->f148;
    arg1->f148 = temp_s0_2 + igObject_GetSerializedSize(temp_s0);
    arg1->f144 = arg1->f144 + 1;
}
