#include "dw4/reflected.h"

extern "C" void Gap__Bec__beHitLandDeliv__vfunc_32(void);
extern "C" int Gap__Bec__beHitLandDeliv__vfunc_30(void);
extern "C" void Gap__Bec__beHitLandDeliv__vfunc_31(void);
extern "C" int Gap__Bec__beHitLandDeliv__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int g_beHitLandDelivInfo_metaObject[4];
extern "C" int g_beHitLandDeliv_metaObject[4];
extern "C" char DAT_0050ea40[];
extern "C" void Gap__Bec__beHitLandDeliv__vfunc_29(beHitLandDeliv * p0, int p1, char * p2);

void Gap__Bec__beHitLandDeliv__vfunc_32(void)
{
}

int Gap__Bec__beHitLandDeliv__vfunc_30(void)
{
    return g_beHitLandDelivInfo_metaObject[0];
}

void Gap__Bec__beHitLandDeliv__vfunc_29(beHitLandDeliv * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050ea40);
}

void Gap__Bec__beHitLandDeliv__vfunc_31(void)
{
}

int Gap__Bec__beHitLandDeliv__vfunc_20(void)
{
    return g_beHitLandDeliv_metaObject[0];
}

