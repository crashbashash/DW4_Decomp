#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_PopArgContext(int);
int beMessenger_PushArgContext(int);
int beMessenger_SelectGroup(int, int *);
struct A1 { char pad[8]; int f8; };
extern int DAT_0051d4b0[4];
extern int DAT_0051d4f0[4];
extern int DAT_0051d500[4];
void FUN_00445c60(beNDMWMdlPEBase *arg0, struct A1 *arg1, beNDMWMdlPEBaseInfoWork *arg2) {
    if (arg2->_isPlayer != 0) {
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->f8);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d4f0[0]);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->f8);
        beMessenger_AppendInt(arg0->_messenger, 0);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d500[0]);
        beMessenger_PopArgContext(arg0->_messenger);
    }
}
} /* extern "C" */
