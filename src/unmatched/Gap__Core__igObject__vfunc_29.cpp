#include "dw4/reflected.h"
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset (slot 36 of beModelCtrl) */
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void vX(void *); };
extern "C" {
int beMessenger_RegisterReceiverFromInfo(...);
void *igProperty_FindByName(...);
extern int DAT_0050ef10[4];
extern int DAT_0050ef18[4];
extern int DAT_0050ef30[4];
extern int DAT_0050ef40[4];
extern int DAT_0050ef50[4];
extern int DAT_00585be0[4];
void Gap__Core__igObject__vfunc_29(beModelCtrl *arg0, beBaseInfoRam *arg1);
}
void Gap__Core__igObject__vfunc_29(beModelCtrl *arg0, beBaseInfoRam *arg1) {
    beBaseInfo *temp_s0;
    beModelCtrlInfoDataHit *temp_v0;

    temp_s0 = (beBaseInfo *)arg1->_parentInfo;
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef18[0]);
    temp_v0 = (beModelCtrlInfoDataHit *)igProperty_FindByName(temp_s0->_dataList, DAT_00585be0[0], &DAT_0050ef10[0]);
    if (temp_v0 != 0) {
        if (temp_v0->_isHitPlayerBullet != 0) {
            beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef30[0]);
        }
        if (temp_v0->_isHitPlayerTalk != 0) {
            beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef40[0]);
        }
        if (temp_v0->_isHitEnemyBullet != 0) {
            beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef50[0]);
        }
    }
    ((C *)arg0)->vX(arg1);
}
