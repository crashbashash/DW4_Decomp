#include "dw4/reflected.h"
extern "C" {
int ChangeThreadPriority(...);
int ExitDeleteThread(...);
int igObject_Destroy(...);
void FUN_003304e0(void **arg0, igPsx2Thread *arg1);
}
struct DW4SR4 { int w0; };
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
void FUN_003304e0(void **arg0, igPsx2Thread *arg1) {
    DW4SR4 sp3C;
    void **temp_a1;

    ((DW4VC_100_0 *)(arg0))->vX();
    int *tid = &arg1->_threadID;
    ChangeThreadPriority(*tid, 1);
    *tid = -1;
    temp_a1 = (void **)(arg1->_threadDoneSema);
    sp3C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    arg1->_refCount = (int)((int) (arg1->_refCount - 1));
    if (((unsigned long long) ((long long) (int) arg1->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(arg1);
    }
    ExitDeleteThread();
}
