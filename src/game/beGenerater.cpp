#include "dw4/reflected.h"

extern "C" int FUN_00236f80(int, int);
extern "C" int Gap__Bec__beGenerater__vfunc_30(void);
extern "C" int Gap__Bec__beGenerater__vfunc_20(void);
extern "C" int beMessenger_RegisterReceiver(...);
extern "C" void Gap__Bec__beGenerater__vfunc_29(void *a0, void *a1);
extern "C" int g_beLua_metaObject[4];
extern "C" void Gap__Bec__beGenerater__vfunc_32(beGenerater *arg0);
extern "C" int g_beGeneraterInfo_metaObject[4];
extern "C" int g_beGenerater_metaObject[4];
extern "C" int emptyString[4];
extern "C" int DAT_0050e850[4];
/* arg1 message record: +8 is the first argument, +12 a pointer whose +8 word is the optional name. */
typedef struct MessageArgsView { char pad8[8]; int f8; int *f12; } MessageArgsView;

void Gap__Bec__beGenerater__vfunc_32(beGenerater *arg0) {
    if (arg0->_luaManager == 0) {
        arg0->_luaManager = FUN_00236f80(arg0->_insight, g_beLua_metaObject[0]);
    }
}

int Gap__Bec__beGenerater__vfunc_30(void)
{
    return g_beGeneraterInfo_metaObject[0];
}

void Gap__Bec__beGenerater__vfunc_29(void *a0, void *a1) {
    /* matching construct: void* parameters recast so the frame matches */
    beGenerater *arg0 = (beGenerater *)a0;
    MessageArgsView *arg1 = (MessageArgsView *)a1;
    int *v = *(int **)((char *)arg1->f12 + 8);
    int f8 = arg1->f8;
    beMessenger_RegisterReceiver(arg0->_messenger, a1, &DAT_0050e850[0], v ? v : &emptyString[0], f8);
}

int Gap__Bec__beGenerater__vfunc_20(void)
{
    return g_beGenerater_metaObject[0];
}

