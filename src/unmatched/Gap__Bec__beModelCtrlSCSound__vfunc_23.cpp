extern "C" {
int beMessenger_AppendLong(int, long long);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_0050f4a0[4];
extern int DAT_0050f4b0[4];
extern int DAT_0050f4b8[4];
}
#include "dw4/reflected.h"
/* Only the messenger word at +20 of the owner object is read. */
struct MessengerOwnerView { char pad[20]; int msg; };
/* Only the owner pointer at +16 of the context object is read. */
struct OwnerContextView { char pad[16]; struct MessengerOwnerView *m; };
extern "C" {
void Gap__Bec__beModelCtrlSCSound__vfunc_23(beModelCtrlSCSound *arg0, struct OwnerContextView *arg1);
}
void Gap__Bec__beModelCtrlSCSound__vfunc_23(beModelCtrlSCSound *arg0, struct OwnerContextView *arg1) {
    struct MessengerOwnerView *m = arg1->m;
    if (arg0->_sndHandle != 0) {
        beMessenger_SelectGroup(m->msg, &DAT_0050f4a0[0]);
        beMessenger_AppendString(m->msg, &DAT_0050f4b0[0]);
        beMessenger_AppendLong(m->msg, arg0->_sndHandle);
        beMessenger_DispatchSelected(m->msg, &DAT_0050f4b8[0]);
    }
}
