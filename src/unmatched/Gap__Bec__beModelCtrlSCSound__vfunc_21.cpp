/* 0x00399c50 - beModelCtrlSCSound vfunc 21. Asks the messenger of arg1->f16 for a long long value (group select, append string, dispatch, get long); stores it into arg0->f24 when it is neither -1 nor 0 and the int result is 4; typed structs, alternate compiler -O3,p. */
#include "dw4/reflected.h"
/* unidentified owner object: only its messenger word at +20 is read */
typedef struct MessengerOwnerView { char pad[20]; int f20; } MessengerOwnerView;
/* unidentified context object: only the owner pointer at +16 is read */
typedef struct OwnerContextView { char pad[16]; MessengerOwnerView *f16; } OwnerContextView;
extern "C" {
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetInt(int, int);
long long beMessenger_GetLong(int, int);
int beMessenger_SelectGroup(int, void *);
extern int DAT_0050f4a0[4];
extern int DAT_0050f4a8[4];
int Gap__Bec__beModelCtrlSCSound__vfunc_21(beModelCtrlSCSound *arg0, OwnerContextView *arg1);
}
int Gap__Bec__beModelCtrlSCSound__vfunc_21(beModelCtrlSCSound *arg0, OwnerContextView *arg1) {
    MessengerOwnerView *s1 = arg1->f16;
    long long s0;
    beMessenger_SelectGroup(s1->f20, &DAT_0050f4a0[0]);
    beMessenger_AppendString(s1->f20, arg0->_sndName);
    beMessenger_DispatchSelected(s1->f20, &DAT_0050f4a8[0]);
    s0 = beMessenger_GetLong(s1->f20, 0);
    if (s0 == -1) {
        return 0;
    }
    if (s0 == 0) {
        return 0;
    }
    if (beMessenger_GetInt(s1->f20, 0) != 4) {
        return 0;
    }
    arg0->_sndHandle = s0;
    return 1;
}
