#include "dw4/reflected.h"
extern "C" {
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
extern int DAT_00519ba0[4];
extern int DAT_00519c10[4];
extern int DAT_00519c40[4];
extern int DAT_00519c50[4];
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_28(beNDMWStatusPowerSocket *arg0);
}
/* matching construct: dummy-virtual receivers (DW4VC_*) for the vX() calls */
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class DW4VC_132_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_28(beNDMWStatusPowerSocket *arg0) {
    int temp_a2;

    temp_a2 = arg0->_retCode;
    switch (temp_a2) {
    case 0:
        /* matching construct: cast from the 4-byte _mother reference to its window type */
        beNDMWWindow *mother = (beNDMWWindow *)arg0->_mother;
        switch (mother->_entCode) {
        case 0:
            arg0->_st1 = 3;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        default:
            arg0->_st1 = 4;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        }
        break;
    case 1:
        arg0->_st1 = 2;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_retCode = -1;
        ((DW4VC_132_2 *)(((char *)(arg0) + 0)))->vX((int)(2), (int)(temp_a2));
        arg0->_retCode = (int)((int) arg0->_kindListPos);
        ((DW4VC_104_0 *)(((char *)(arg0) + 0)))->vX();
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_00519ba0[0], 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519c40[0]);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c10[0]);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519c50[0]);
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    }
}
