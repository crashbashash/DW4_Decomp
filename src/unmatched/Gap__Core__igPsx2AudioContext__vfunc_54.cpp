#include "dw4/reflected.h"
struct R { int v; R() {} };
struct T { int word0; int references; };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R a92(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual R a120(); virtual void d29(); virtual void d30(); virtual R a132(void *); virtual void d32(); virtual R a140(int); };
extern "C" {
void *FUN_002ba650(...);
T *FUN_002b7f40(...);
void igObject_Destroy(T *);
int FUN_00113f20(...);
int FUN_0010d4c8(...);
int FUN_00113f78(...);
int FUN_00143840(...);
int FUN_00143880(...);
extern int DAT_0055f5b0[4];
extern C * DAT_0055f5b8[4];
void Gap__Core__igPsx2AudioContext__vfunc_54(igPsx2AudioContext *arg0, int arg1);
}
void Gap__Core__igPsx2AudioContext__vfunc_54(igPsx2AudioContext *arg0, int arg1) {
    T *s0;
    T *a0;
    C *p;
    if (arg0->_streamingThread == 0) {
        p = (C *)FUN_002ba650(0);
        DAT_0055f5b8[0] = p;
        p->a92();
        DAT_0055f5b8[0]->a132((void *)1);
        s0 = FUN_002b7f40(0);
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = (T *)arg0->_streamingThread;
        if (a0 != 0) {
            --a0->references;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy(a0);
            }
        }
        arg0->_streamingThread = (int)s0;
        ((C *)arg0->_streamingThread)->a132((void *)&FUN_00143880);
        ((C *)arg0->_streamingThread)->a140(arg1);
        ((C *)arg0->_streamingThread)->a120();
        FUN_00113f20();
        FUN_0010d4c8(0, &FUN_00143840, &DAT_0055f5b0[0]);
        FUN_00113f78();
    }
}
