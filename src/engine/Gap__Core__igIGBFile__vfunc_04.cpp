typedef struct S_ref { char p0[4]; int references; } S_ref;
typedef struct S_list { char p0[8]; int f8; char p1[4]; int *f16; } S_list;
class IObj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();  virtual int vX(int); };
typedef struct S_arg0 { char p0[16]; IObj **f16; char p1[24]; S_list *f44; } S_arg0;
extern "C" {
int Gap__Core__igObject__vfunc_02(...);
int igObject_Destroy(...);
void Gap__Core__igIGBFile__vfunc_04(S_arg0 *arg0);
}
void Gap__Core__igIGBFile__vfunc_04(S_arg0 *arg0) {
    /* matching construct: variant search — decl order [4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s1;
    int temp_s0;
    S_ref *temp_a0_3;
    S_ref *temp_a0_2;
    S_list *temp_v0;

    temp_v0 = arg0->f44;
    if (temp_v0 != 0) {
        temp_s0 = temp_v0->f8;
        for (var_s1 = 0; var_s1 < temp_s0; var_s1++) {
            arg0->f16[var_s1]->vX(arg0->f44->f16[var_s1]);
        }
        temp_a0_2 = (S_ref *)arg0->f44;
        if (temp_a0_2 != 0) {
            temp_a0_2->references = temp_a0_2->references - 1;
            if (((unsigned long long)(long long)temp_a0_2->references & 0x7fffffULL) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->f44 = 0;
    }
    temp_a0_3 = (S_ref *)arg0->f44;
    if (temp_a0_3 != 0) {
        temp_a0_3->references = temp_a0_3->references - 1;
        if (((unsigned long long)(long long)temp_a0_3->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0_3);
        }
    }
    arg0->f44 = 0;
    Gap__Core__igObject__vfunc_02(arg0);
}
