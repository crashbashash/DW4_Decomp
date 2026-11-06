#include "dw4/reflected.h"
extern "C" { int igObject_Destroy(igObject *); }
class C29 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vX(); };
class C23 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void vX(int); };
class C28 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual igObject *vX(); };
extern "C" void Gap__Gui__igGuiSystemRenderer__vfunc_25(int *arg0) {
    igObject *temp_v0;
    igObject *temp_a0_4;
    ((C29 *)arg0[5])->vX();
    ((C23 *)arg0[5])->vX(arg0[3]);
    temp_v0 = ((C28 *)arg0[5])->vX();
    if (temp_v0 != 0) {
        temp_v0->_refCount = temp_v0->_refCount + 1;
    }
    temp_a0_4 = (igObject *)arg0[6];
    if (temp_a0_4 != 0) {
        temp_a0_4->_refCount = temp_a0_4->_refCount - 1;
        if ((temp_a0_4->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0_4);
        }
    }
    arg0[6] = (int)temp_v0;
}

