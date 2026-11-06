/* Callback dispatch with two virtual calls and a function-pointer table; vtable result held in a
 * local before the compare; alternate compiler. */
struct S; struct V;
extern "C" { int FUN_001e07a0(...); extern int DAT_00561838[4]; }
extern "C" int FUN_001e04c0(S *arg0, V *arg1);
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };

struct L { char p[16]; int (**tab)(S *, V *); };
struct S { char p[8]; unsigned char f8; char q[3]; int (*f12)(...); char r[12]; L *f28; };
struct W : V { char p[20]; int f24; };
int FUN_001e04c0(S *arg0, V *arg1) {
    int temp_v0;
    int temp_s0;
    if (arg0->f8 != 0) {
        temp_v0 = arg0->f12();
        if (temp_v0 != 0) {
            if (temp_v0 == 2) {
                temp_s0 = DAT_00561838[0];
                int rr = arg1->vX();
                if (rr != temp_s0) {
                    if (FUN_001e07a0(arg0, arg1) == 2) {
                        temp_v0 = 2;
                    } else {
                        temp_v0 = 0;
                    }
                    return temp_v0;
                }
                goto block_9;
            }
            return 0;
        }
    }
block_9:
    return arg0->f28->tab[((W *)arg1)->f24](arg0, arg1);
}

