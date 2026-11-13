#include "dw4/igSmartPointer.h"

extern "C" {
void *FUN_002bc0d0(int);
void *FUN_00304f00(void *, int (*)(), unsigned);
void *Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(void *);
extern int DAT_004c22e8[4];
extern int DAT_00587020[4];
int FUN_00308c00();
}
struct R { int v; };
struct RO : public igObject { };
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vA(); };
class V200 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual R vB(int); };
class V136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual R vC(int); };

struct AsyncListOwner { char pad[28]; unsigned char ready; char pad29[3]; igSmartPointer<RO> list; igSmartPointer<RO> field; };
extern "C" void igResource_StartAsyncLoading(AsyncListOwner *arg0) {
    R a;
    R b;
    arg0->list = igSmartPointer<RO>((RO *)FUN_002bc0d0(igObject_GetAllocator(arg0))).get();
    ((V92 *)arg0->list.get())->vA();
    arg0->field = (RO *)FUN_00304f00(arg0->list.get(), &FUN_00308c00, DAT_004c22e8[0]);
    a = ((V200 *)arg0->field.get())->vB(255);
    arg0->ready = 1;
    b = ((V136 *)Memory_GetAllocatorBySelector(DAT_00587020[0]))->vC(1);
}
