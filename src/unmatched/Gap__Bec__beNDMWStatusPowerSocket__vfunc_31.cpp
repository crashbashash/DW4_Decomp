#include "dw4/reflected.h"
extern "C" {
int beNDMWStatus_AssignEquipment(void *, int, int, int);
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_31(beNDMWStatusPowerSocket *arg0);
}
/* matching construct: dummy-virtual class (38 slots) so vX() compiles to the retail vtable call; no data. */
class beNDMWStatusPowerSocketVTable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void vX(); };
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_31(beNDMWStatusPowerSocket *arg0) {
    beNDMWStatus_AssignEquipment(arg0, arg0->_powerSocket, arg0->_kindListPos, arg0->_retCode);
    if (arg0->_kindListPos == 0) {
        ((beNDMWStatusPowerSocketVTable *)arg0)->vX();
    }
    ((beNDMWWindow *)((beNDMWWindow *)arg0->_mother)->_mother)->_retCode = 0x64;
}
