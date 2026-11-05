#include "dw4/reflected.h"
extern "C" {
int FUN_001b1cf0(int);
int FUN_001b1dc0(int);
int FUN_0034b980();
int FUN_0039c1c0(bePoint01 *, bePoint01Info *, int, int);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_GetInt(int, int);
unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern int DAT_004e0858[4];
int Gap__Bec__bePoint01__vfunc_34(bePoint01 *arg0, beBaseInfoRam *arg1, void *arg2);
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
                beMessenger_AppendString(arg0->_messenger, a1 ? a1 : &DAT_004e0858[0]);
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
