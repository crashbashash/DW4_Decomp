#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_07(void *, int);
int Memory_AllocateBufferDirect(int, int);
int Memory_GetAllocatorBySelector(int);
int igMetaObject_CountInstances(int, int);
int igObject_GetAllocator(void *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWDegiData__vfunc_07(beNDMWDegiData *arg0, int arg1);
}
/* matching construct: dummy-virtual class supplies the vtable call at +88 */
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void Gap__Bec__beNDMWDegiData__vfunc_07(beNDMWDegiData *arg0, int arg1) {
    int a;

    Gap__Core__igObject__vfunc_07(arg0, arg1);
    igMetaObject_CountInstances(((Obj *)arg0)->vX(), 1);
    if (!(arg1 & 0xFF)) {
        arg0->_dataSize = 0x2000;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        arg0->_data = Memory_AllocateBufferDirect(0x2000, a);
    }
}
