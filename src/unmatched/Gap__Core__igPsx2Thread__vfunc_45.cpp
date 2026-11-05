extern "C" {
int DeleteThread(...);
int FUN_00330440(...);
int GetThreadId(...);
int TerminateThread(...);
int igObject_Destroy(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
class DW4VC_100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(void *); };
struct H4 { int w; };
class DW4VC_124 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual H4 vX(); };
struct R { int w0; int rc; };
struct O { char pad4[4]; int rc4; char pad[36]; unsigned char f44; char pad2[3]; DW4VC_124 *f48; char pad3[4]; unsigned char f56; unsigned char f57; unsigned char f58; char pad4b; int f60; };
extern DW4VC_100 * DAT_005871d0[4];
extern "C" void Gap__Core__igPsx2Thread__vfunc_45(int *arg0, O *arg1);
void Gap__Core__igPsx2Thread__vfunc_45(int *arg0, O *arg1) {
    /* matching construct: variant search — decl order [4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    H4 sp5C;
    int temp_s1;
    int temp_s0_2;
    int temp_s0;
    int *var_v1_2;

    if (arg1->f44 != 0) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if ((arg1->f56 != 0) && (arg1->f58 == 0)) {
        arg1->f57 = 1;
        *arg0 = DAT_004fb410[0];
        return;
    }
    temp_s0 = arg1->f60;
    if (temp_s0 == GetThreadId()) {
        FUN_00330440(arg1, 0);
    }
    DAT_005871d0[0]->vX(arg1);
    temp_s1 = *(volatile int *)&arg1->f60;
    temp_s0_2 = TerminateThread(arg1->f60);
    arg1->f60 = -1;
    sp5C = arg1->f48->vX();
    arg1->rc4 = arg1->rc4 - 1;
    if ((arg1->rc4 & 0x7FFFFF) == 0) {
        igObject_Destroy(arg1);
    }
    DeleteThread(temp_s1);
    if (temp_s0_2 < 0) {
        var_v1_2 = (int *)(&DAT_004fb418[0]);
    } else {
        var_v1_2 = (int *)(&DAT_004fb410[0]);
    }
    *arg0 = *var_v1_2;
}
