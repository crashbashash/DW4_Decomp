#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(...);
extern void * DAT_005871d0[4];
void FUN_0030e540(void);
}
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
void FUN_0030e540(void) {
    igObject *temp_v0;
    igObject *o;

    temp_v0 = (igObject *)(((DW4VC_92_0 *)(((char *)(DAT_005871d0[0]) + 0)))->vX());
    ((DW4VC_100_1 *)(((char *)(DAT_005871d0[0]) + 0)))->vX((int)(temp_v0));
    temp_v0->_refCount = (int)((int) temp_v0->_refCount - 1);
    if (((unsigned long long) ((long long) (int) temp_v0->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    o = (igObject *)DAT_005871d0[0];
    o->_refCount = (int) o->_refCount - 1;
    if (((unsigned long long) ((long long) (int) o->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(o);
    }
    DAT_005871d0[0] = (void *)(0);
}
