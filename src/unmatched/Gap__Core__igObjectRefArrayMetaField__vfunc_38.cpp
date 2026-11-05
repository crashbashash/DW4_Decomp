extern "C" {
int FUN_00300770(...);
int FUN_00302780(...);
int igObject_Destroy(...);
}
struct R { int w0; int refs; };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int clone(int); };
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_38(int *arg0, int arg1, int arg2) {
    int var_s0;
    int v1;
    int p1;
    int p2;
    int off;
    R *a0;
    C *a1;

    var_s0 = 0;
    while (var_s0 < arg0[17]) {
        v1 = arg0[2];
        off = var_s0 * 4;
        p1 = arg1 + v1;
        p2 = arg2 + v1;
        a0 = *(R **)(p1 + off);
        a1 = *(C **)(p2 + off);
        if (a0 != 0 || a1 != 0) {
            if (a0 != 0 && a1 != 0) {
                FUN_00300770(a0, a1);
            } else if (a0 == 0) {
                FUN_00302780(arg0, arg1, var_s0, a1->clone(1));
            } else if (a1 == 0) {
                a0->refs = a0->refs - 1;
                if ((a0->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(a0);
                }
                FUN_00302780(arg0, arg1, var_s0, 0);
            }
            var_s0 += 1;
        } else {
            break;
        }
    }
}
