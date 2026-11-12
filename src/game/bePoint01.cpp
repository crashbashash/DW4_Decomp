#include "dw4/reflected.h"

extern "C" void Gap__Bec__bePoint01__vfunc_32(void);
extern "C" int Gap__Bec__bePoint01__vfunc_30(void);
extern "C" void Gap__Bec__bePoint01__vfunc_31(void);
extern "C" int Gap__Bec__bePoint01__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int Matrix44_Copy(int *, int *);
extern "C" int beMessenger_AppendMatrix(int, void *);
extern "C" int FUN_001b1cf0(int);
extern "C" int FUN_001b1dc0(int);
extern "C" int FUN_0034b980(...);
extern "C" int beMessenger_AppendInt(int, int);
extern "C" int beMessenger_AppendString(int, int *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int g_bePoint01Info_metaObject[4];
extern "C" int g_bePoint01_metaObject[4];
extern "C" char DAT_0050f6e0[];
extern "C" void Gap__Bec__bePoint01__vfunc_29(bePoint01 * p0, int p1, char * p2);
extern "C" int DAT_004e0ef0[4];
extern "C" void FUN_0039c1c0(bePoint01 *arg0, bePoint01Info *arg1, int arg2, int arg3);
extern "C" int emptyString[4];
extern "C" int Gap__Bec__bePoint01__vfunc_34(bePoint01 *arg0, beBaseInfoRam *arg1, void *arg2);

void Gap__Bec__bePoint01__vfunc_32(void)
{
}

int Gap__Bec__bePoint01__vfunc_30(void)
{
    return g_bePoint01Info_metaObject[0];
}

void Gap__Bec__bePoint01__vfunc_29(bePoint01 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050f6e0);
}

void Gap__Bec__bePoint01__vfunc_31(void)
{
}

void FUN_0039c1c0(bePoint01 *arg0, bePoint01Info *arg1, int arg2, int arg3) {
    int sp20[16];
    beGroupKeepList *l;
    beGroupKeep *it;
    l = (beGroupKeepList *)arg1->_dataList_;
    if (l->_count - 1 < arg2) {
        arg2 = 0;
    }
    it = ((beGroupKeep **)l->_data)[arg2];
    if (it != 0) {
        beMessenger_AppendMatrix(arg0->_messenger, ((igTransform **)((igObjectList *)it->_childList)->_data)[arg3]->_m);
        return;
    }
    Matrix44_Copy(sp20, &DAT_004e0ef0[0]);
    beMessenger_AppendMatrix(arg0->_messenger, sp20);
}

int Gap__Bec__bePoint01__vfunc_34(bePoint01 *arg0, beBaseInfoRam *arg1, void *arg2) {
    unsigned int v;
    int ent;
    bePoint01Info *s0;
    s0 = (bePoint01Info *)arg1->_parentInfo;
    v = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0034b980(), *(int *)((char *)arg2 + 20));
    switch (v) {
    case 0:
        FUN_001b1cf0(*(int *)((char *)s0->_switch + 32));
        return 1;
    case 1:
        FUN_001b1dc0(*(int *)((char *)s0->_switch + 32));
        return 1;
    case 2: {
        int t = arg0->_pointNo;
        FUN_0039c1c0(arg0, s0, t, beMessenger_GetInt(arg0->_messenger, 1));
        return 1;
    }
    case 3: {
        int t = beMessenger_GetInt(arg0->_messenger, 0);
        FUN_0039c1c0(arg0, s0, t, beMessenger_GetInt(arg0->_messenger, 1));
        return 1;
    }
    case 4: {
        igObjectList *l = (igObjectList *)s0->_dataList_;
        int n = l->_count;
        int i = 0;
        if (0 < n) {
            int off = 0;
            do {
                int *a1 = (int *)(((beBaseInfoData *)(*(int *)((char *)l->_data + off)))->_name);
                beMessenger_AppendString(arg0->_messenger, a1 ? a1 : &emptyString[0]);
                i += 1;
                off += 4;
            } while (i < n);
        }
        return 1;
    }
    case 5:
        arg0->_pointNo = beMessenger_GetInt(arg0->_messenger, 0);
        return 1;
    case 6:
        beMessenger_AppendInt(arg0->_messenger, arg0->_pointNo);
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__bePoint01__vfunc_20(void)
{
    return g_bePoint01_metaObject[0];
}
