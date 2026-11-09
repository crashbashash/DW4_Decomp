#include "dw4/igSmartPointer.h"
extern "C" {
void *FUN_002ba650(...);
int FUN_00326330(...);
int igObject_GetAllocator(...);
extern int DAT_004fb410[4];
}
struct R4 { int v; R4() {} R4(int x) { v = x; } };
class Ob : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R4 a92(); virtual R4 a96(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual R4 a132(int); };

struct Pool { char pad[116]; igSmartPointer<Ob> f116; char p2[20]; int f140; };
extern "C" R4 Gap__Core__igPageMemoryPool__vfunc_34(Pool *arg1, int arg2) {
    int a1;
    if (arg2 != 0) {
        a1 = arg1->f140 | 4;
    } else {
        a1 = arg1->f140 & ~4;
    }
    FUN_00326330(arg1, a1);
    if ((arg2 & 0xFF) == 0) {
        igSmartPointer<Ob> held(arg1->f116);
        arg1->f116.clear();
        if (held.p != 0) {
            held.p->a132(1);
            held.p->a96();
        }
    } else if ((arg2 & 0xFF) == 1) {
        if (arg1->f116.p != 0) {
            return DAT_004fb410[0];
        }
        igSmartPointer<Ob> created((Ob *)FUN_002ba650(igObject_GetAllocator(arg1)));
        created.p->a92();
        arg1->f116 = created;
    }
    return DAT_004fb410[0];
}
