#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int DeleteThread(...);
int FUN_00330440(...);
int GetThreadId(...);
int TerminateThread(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct RS { int x; };
struct Sub {
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
    virtual RS get();
};
struct Mgr {
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
    virtual void call(void *);
};
extern Mgr *DAT_005871d0[4];
extern "C" void Gap__Core__igPsx2Thread__vfunc_44(int *arg0, igPsx2Thread *arg1);
void Gap__Core__igPsx2Thread__vfunc_44(int *arg0, igPsx2Thread *arg1) {
    int s0, s1, s0b;
    RS sp5C;
    if (arg1->_isMaster != 0) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (arg1->_isDeferred != 0 && arg1->_atStoppingPoint == 0) {
        arg1->_stopRequested = 1;
        *arg0 = DAT_004fb410[0];
        return;
    }
    s0 = arg1->_threadID;
    if (s0 == GetThreadId()) {
        FUN_00330440(arg1, 0);
    }
    DAT_005871d0[0]->call(arg1);
    s1 = arg1->_threadID;
    s0b = TerminateThread(((const igPsx2Thread *)arg1)->_threadID);
    arg1->_threadID = -1;
    sp5C = ((Sub *)arg1->_threadDoneSema)->get();
    arg1->_refCount--;
    if (((unsigned long long)(long long)arg1->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy((igObject *)arg1);
    }
    DeleteThread(s1);
    int *p = (s0b < 0) ? DAT_004fb418 : DAT_004fb410;
    *arg0 = *p;
}
