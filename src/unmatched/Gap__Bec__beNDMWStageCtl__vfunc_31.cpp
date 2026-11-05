#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendGroup(...);
int beMessenger_SetFreezeTime(...);
bePadData *bePadManager_GetPadForPlayer(...);
extern int DAT_005155c0[4];
extern int DAT_005155d0[4];
extern int DAT_005155d8[4];
extern int DAT_005155e0[4];
extern int DAT_005155e8[4];
extern int DAT_005155f0[4];
extern int DAT_005155f8[4];
extern int DAT_00515600[4];
extern int DAT_00515608[4];
extern int DAT_00515618[4];
extern int DAT_00515620[4];
extern int DAT_00515628[4];
extern int DAT_00515630[4];
extern int DAT_00515640[4];
extern int DAT_00515650[4];
extern int DAT_00515660[4];
extern int DAT_00515670[4];
extern int DAT_00588518[4];
}
/* matching construct: dummy-virtual classes so the window chain dispatches through retail vtable slots */
struct Obj2 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void v712(unsigned); };
struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual Obj2 *v152(); };
extern "C" void Gap__Bec__beNDMWStageCtl__vfunc_31(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1) {
    bePadData *pad;
    bool ok;
    switch (arg1->_st0) {
    case 0:
        if (((beSystem *)arg0->_system)->_isSResetEnable == 0) return;
        pad = bePadManager_GetPadForPlayer(FUN_00236f80(arg0->_insight, DAT_00588518[0]), 0);
        int a = pad->_trigger;
        int b = pad->_button;
        ok = (a & 8) != 0 && (b & 1) != 0;
        if (!ok) return;
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
        return;
    case 1:
        if (((beSystem *)arg0->_system)->_isSResetEnable == 0) {
            arg1->_st0 = 0;
            arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
            return;
        }
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155d8[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e0[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e8[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155f0[0], &DAT_005155f8[0]);
        if (beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) {
            beMessenger_SendGroup(arg0->_messenger, &DAT_005155f0[0], &DAT_00515600[0]);
            ((Obj *)((igInsightCore *)arg0->_insight)->_window)->v152()->v712(0xFF000000);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_00515608[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00515618[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00515620[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00515628[0]);
        }
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
        return;
    case 2:
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155f0[0], &DAT_005155f8[0]);
        if (beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) return;
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00515608[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515618[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515620[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00515628[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_00515630[0], &DAT_00515640[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_00515650[0], &DAT_00515640[0]);
        beMessenger_SetFreezeTime(arg0->_messenger, 1);
    case 3:
    case 4:
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
        return;
    case 5:
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005155c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515660[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00515670[0]);
        break;
    }
}
