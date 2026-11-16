#include "dw4/reflected.h"

extern "C" int igInsightCore_FindManager(int, int);
extern "C" int beGenerater_GetInfoMeta(void);
extern "C" int beGenerater_GetMeta(void);
extern "C" int beMessenger_RegisterReceiver(...);
extern "C" void beGenerater_OnAddRam(void *a0, void *a1);
extern "C" int g_beLua_metaObject[4];
extern "C" void beGenerater_Prepare(beGenerater *arg0);
extern "C" int g_beGeneraterInfo_metaObject[4];
extern "C" int g_beGenerater_metaObject[4];
extern "C" int emptyString[4];
extern "C" int GENERATER[4];
/* arg1 message record: +8 is the first argument, +12 a pointer whose +8 word is the optional name. */
typedef struct MessageArgsView { char pad8[8]; int f8; int *f12; } MessageArgsView;

void beGenerater_Prepare(beGenerater *arg0) {
    if (arg0->_luaManager == 0) {
        arg0->_luaManager = igInsightCore_FindManager(arg0->_insight, g_beLua_metaObject[0]);
    }
}

int beGenerater_GetInfoMeta(void)
{
    return g_beGeneraterInfo_metaObject[0];
}

void beGenerater_OnAddRam(void *a0, void *a1) {
    /* matching construct: void* parameters recast so the frame matches */
    beGenerater *arg0 = (beGenerater *)a0;
    MessageArgsView *arg1 = (MessageArgsView *)a1;
    int *v = *(int **)((char *)arg1->f12 + 8);
    int f8 = arg1->f8;
    beMessenger_RegisterReceiver(arg0->_messenger, a1, &GENERATER[0], v ? v : &emptyString[0], f8);
}

int beGenerater_GetMeta(void)
{
    return g_beGenerater_metaObject[0];
}

