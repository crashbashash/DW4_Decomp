#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
}
/* matching construct: inline release helper reproduces the retail inlined refcount release (release then clear) */
struct RefRelease {
    static inline void rel(int &r) {
        igObject *object = (igObject *)r;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
        r = 0;
    }
};
extern "C" void Gap__Bec__beNDMWGameRam__vfunc_32(beNDMWGameRam *arg0);
void Gap__Bec__beNDMWGameRam__vfunc_32(beNDMWGameRam *arg0) {
    RefRelease::rel(arg0->_dBShinka);
    RefRelease::rel(arg0->_dBPcTech);
    RefRelease::rel(arg0->_dBWeapon);
    RefRelease::rel(arg0->_dBArmor1);
    RefRelease::rel(arg0->_dBArmor2);
    RefRelease::rel(arg0->_dBAbChip);
    RefRelease::rel(arg0->_dBEnemy);
    RefRelease::rel(arg0->_dBEneatk);
}
