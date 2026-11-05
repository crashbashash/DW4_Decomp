#include "dw4/reflected.h"
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
void sprintf(void *, void *, int);
void beMessenger_SelectGroup(int, void *);
void beMessenger_AppendString(int, void *);
void beMessenger_DispatchSelected(int, void *);
extern int DAT_0051c6e8[4];
extern int DAT_0051c710[4];
extern int DAT_0051c720[4];
extern int DAT_0051c730[4];
extern int DAT_0051c738[4];
extern int DAT_0051c740[4];
extern int DAT_0051c750[4];
extern int DAT_0051c760[4];
extern int DAT_0051c770[4];
extern void *DAT_00586f20[4];
}
extern "C" void Gap__Bec__beNDMWShopSelect34__vfunc_22(beNDMWShopSelect34 *arg0);
void Gap__Bec__beNDMWShopSelect34__vfunc_22(beNDMWShopSelect34 *arg0) {
    int sp30[4];
    int i;
    const char *n;
    const char *old;
    i = 0;
    do {
        switch (arg0->_entCode) {
        case 3:
            sprintf(sp30, DAT_0051c710, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c720);
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            break;
        default:
            sprintf(sp30, DAT_0051c710, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c740);
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            sprintf(sp30, DAT_0051c750, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c740);
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            sprintf(sp30, DAT_0051c760, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c740);
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            break;
        }
        i++;
    } while (i < 7);
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    n = StringPool_Intern(DAT_00586f20[0], (const char *)DAT_0051c770);
    old = (const char *)arg0->_infoName;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->_infoName = (int)n;
    arg0->_selectMax = 7;
    arg0->_startPoint = 6;
    arg0->_isNoCancel = 0;
    switch (arg0->_entCode) {
    case 2:
    case 0:
        *(unsigned *)&arg0->_offsetPos[0] = 0xC1A00000;
        *(unsigned *)&arg0->_offsetPos[1] = 0x430A0000;
        arg0->_offsetPos[2] = 0;
        break;
    case 1:
        *(unsigned *)&arg0->_offsetPos[0] = 0xC1A00000;
        *(unsigned *)&arg0->_offsetPos[1] = 0xBF800000;
        arg0->_offsetPos[2] = 0;
        break;
    case 3:
        *(unsigned *)&arg0->_offsetPos[0] = 0x43130000;
        *(unsigned *)&arg0->_offsetPos[1] = 0xC0000000;
        arg0->_offsetPos[2] = 0;
        break;
    }
}
