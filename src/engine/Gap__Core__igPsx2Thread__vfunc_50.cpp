#include "dw4/reflected.h"

struct DW4SR4 { int w0; };
struct SR24 { int w; };
struct RS44 { int x; };
struct H4 { int w; };
struct Result { int v; Result() {} Result(const Result &o) : v(o.v) {}
  bool operator==(const Result &o) const { return v == o.v; }
  bool operator!=(const Result &o) const { return v != o.v; }
};
struct R30 { int v; R30() {} R30(int x) { v = x; } R30(const R30 &o) : v(o.v) {} };
struct R31 { int v; R31(int x) { v = x; } };
struct R41 { int v; R41(int x) { v = x; } R41() {} };

class ThreadMgr { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22(void *); virtual void v23(void *); };

struct T24 { char p0[48]; void *f48; char p1[8]; int f60; };
struct O45;
struct Thread50 { char pad[24]; int priority; char pad2[32]; int id; };
class Obj30;
struct S32 { char pad[60]; int f60; };
class C31;
struct O41;
struct T56 { char p[44]; unsigned char f44; char p2[11]; char f56; };

extern "C" {
int FUN_00300db0(...);
int FUN_00300f50(...);
int FUN_0020d360(int);
int FUN_0032f7f0(...);
void FUN_003304e0(ThreadMgr *, igPsx2Thread *);
Result FUN_0030e430(void *);
long long __udivdi3(int, int);
int GetThreadId(...);
int ReferThreadStatus(int, int);
int SleepThread();
int WakeupThread(int);
int iWakeupThread(int);
int SuspendThread(int);
int iSuspendThread(int);
int ResumeThread(int);
int iResumeThread(int);
int ChangeThreadPriority(int, int);
int iChangeThreadPriority(int, int);
int TerminateThread(...);
int DeleteThread(...);
int CreateThread(...);
int _StartThread(...);
int memset(...);
void igObject_Destroy(...);
extern Result g_statusSucceeded;
extern Result g_allocatorFailureStatus;
extern int _gp[4];
extern unsigned char GPR_00554ddc;
extern ThreadMgr *DAT_005871d0[4];

int Gap__Core__igPsx2Thread__vfunc_23(void *arg0, void *arg1);
void Gap__Core__igPsx2Thread__vfunc_11(void *arg0);
void Gap__Core__igPsx2Thread__vfunc_55(igPsx2Thread *self);
void Gap__Core__igPsx2Thread__vfunc_24(int *arg0, void *arg1, T24 *arg2);
void Gap__Core__igPsx2Thread__vfunc_25(int *arg0, int arg1, int arg2);
void Gap__Core__igPsx2Thread__vfunc_26(void *arg0, int arg1);
void Gap__Core__igPsx2Thread__vfunc_29(int *arg0);
void Gap__Core__igPsx2Thread__vfunc_44(int *arg0, igPsx2Thread *arg1);
void Gap__Core__igPsx2Thread__vfunc_27(int *arg0, void *arg1);
void Gap__Core__igPsx2Thread__vfunc_46(int *status, igPsx2Thread *self);
void Gap__Core__igPsx2Thread__vfunc_48(int *status, igPsx2Thread *self);
Result Gap__Core__igPsx2Thread__vfunc_50(Thread50 *t);
void Gap__Core__igPsx2Thread__vfunc_45(int *arg0, O45 *arg1);
void Gap__Core__igPsx2Thread__vfunc_28(int *arg0, void *arg1);
void Gap__Core__igPsx2Thread__vfunc_47(int *status, igPsx2Thread *thread);
void Gap__Core__igPsx2Thread__vfunc_49(int *status, igPsx2Thread *self);
Result Gap__Core__igPsx2Thread__vfunc_51(Thread50 *t);
void Gap__Core__igPsx2Thread__vfunc_30(int *out, Obj30 *o);
unsigned char Gap__Core__igPsx2Thread__vfunc_32(S32 *arg0);
R31 Gap__Core__igPsx2Thread__vfunc_31(C31 *arg1);
R41 Gap__Core__igPsx2Thread__vfunc_41(O41 *arg1, int arg2, int *arg3);
void Gap__Core__igPsx2Thread__vfunc_56(int *arg0, T56 *arg1, int arg2);
void Gap__Core__igPsx2Thread__vfunc_57(igPsx2Thread *self);
void FUN_003303f0(void *arg0);
void FUN_00330430(void *arg0);
void FUN_00330440(igPsx2Thread *arg0, int arg1);
}

static inline int threadID(const igPsx2Thread *self) { return self->_threadID; }

class DW4VC_168_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(); };
class DW4VCSR_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual DW4SR4 vX(int); };
class VC1_24 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual SR24 vX(int); };
class VC2_24 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual SR24 vX(); };
struct Sub44 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual RS44 get();
};
class DW4VC_124 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual H4 vX(); };
struct O45 { char pad4[4]; int rc4; char pad[36]; unsigned char f44; char pad2[3]; DW4VC_124 *f48; char pad3[4]; unsigned char f56; unsigned char f57; unsigned char f58; char pad4b; int f60; };
class Sub30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R30 v21(); virtual R30 v22(); virtual int v23(); };
class Obj30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int v30(); char p4[20]; int w24; char p28[4]; int w32; int w36; int w40; char p44[4]; Sub30 *sub; char p52[4]; char f56; char f57; char p58[2]; int th; };
struct TP30 { int w[12]; };
class C31 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vA(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual R31 vB(); char pad4[40]; unsigned char f44; };
class C41 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R41 v124(); virtual void d30(); virtual R41 v132(int); };
struct O41 { char p[48]; C41 *c; int f52; };

int Gap__Core__igPsx2Thread__vfunc_23(void *arg0, void *arg1);

void Gap__Core__igPsx2Thread__vfunc_11(void *arg0);

void Gap__Core__igPsx2Thread__vfunc_55(igPsx2Thread *self);

void Gap__Core__igPsx2Thread__vfunc_24(int *arg0, void *arg1, T24 *arg2);

void Gap__Core__igPsx2Thread__vfunc_25(int *arg0, int arg1, int arg2);

void Gap__Core__igPsx2Thread__vfunc_26(void *arg0, int arg1);

void Gap__Core__igPsx2Thread__vfunc_29(int *arg0);

void Gap__Core__igPsx2Thread__vfunc_44(int *arg0, igPsx2Thread *arg1);

void Gap__Core__igPsx2Thread__vfunc_27(int *arg0, void *arg1);

void Gap__Core__igPsx2Thread__vfunc_46(int *status, igPsx2Thread *self);

void Gap__Core__igPsx2Thread__vfunc_48(int *status, igPsx2Thread *self);

Result Gap__Core__igPsx2Thread__vfunc_50(Thread50 *t) {
    if (FUN_0030e430(t) != g_statusSucceeded) {
        return g_allocatorFailureStatus;
    }
    if (t->id != -1) {
        return ChangeThreadPriority(t->id, t->priority / 2) < 0 ? g_allocatorFailureStatus : g_statusSucceeded;
    }
    return g_statusSucceeded;
}

void Gap__Core__igPsx2Thread__vfunc_45(int *arg0, O45 *arg1);

void Gap__Core__igPsx2Thread__vfunc_28(int *arg0, void *arg1);

void Gap__Core__igPsx2Thread__vfunc_47(int *status, igPsx2Thread *thread);

void Gap__Core__igPsx2Thread__vfunc_49(int *status, igPsx2Thread *self);

Result Gap__Core__igPsx2Thread__vfunc_51(Thread50 *t);

void Gap__Core__igPsx2Thread__vfunc_30(int *out, Obj30 *o);

unsigned char Gap__Core__igPsx2Thread__vfunc_32(S32 *arg0);

R31 Gap__Core__igPsx2Thread__vfunc_31(C31 *arg1);

R41 Gap__Core__igPsx2Thread__vfunc_41(O41 *arg1, int arg2, int *arg3);

void Gap__Core__igPsx2Thread__vfunc_56(int *arg0, T56 *arg1, int arg2);

void Gap__Core__igPsx2Thread__vfunc_57(igPsx2Thread *self);

void FUN_003303f0(void *arg0);

void FUN_00330430(void *arg0);

void FUN_00330440(igPsx2Thread *arg0, int arg1);
