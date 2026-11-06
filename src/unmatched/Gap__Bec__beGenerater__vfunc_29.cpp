#include "dw4/reflected.h"
extern "C" {
int beMessenger_RegisterReceiver(...);
extern int DAT_004e0858[4];
extern int DAT_0050e850[4];
void Gap__Bec__beGenerater__vfunc_29(void *arg0, void *arg1);
}
/* arg1 message record: +8 is the first argument, +12 a pointer whose +8 word is the optional name. */
typedef struct MessageArgsView { char pad8[8]; int f8; int *f12; } MessageArgsView;
void Gap__Bec__beGenerater__vfunc_29(void *a0, void *a1) {
    /* matching construct: void* parameters recast so the frame matches */
    beGenerater *arg0 = (beGenerater *)a0;
    MessageArgsView *arg1 = (MessageArgsView *)a1;
    int *v = *(int **)((char *)arg1->f12 + 8);
    int f8 = arg1->f8;
    beMessenger_RegisterReceiver(arg0->_messenger, a1, &DAT_0050e850[0], v ? v : &DAT_004e0858[0], f8);
}
