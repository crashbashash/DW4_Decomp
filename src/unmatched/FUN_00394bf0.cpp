#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
unsigned char FUN_00392be0(...);
int FUN_00395250(...);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int beMessenger_GetBool(...);
int beMessenger_SendNamed(...);
int strcmp(...);
extern int DAT_004e0858[4];
extern int DAT_0050eff8[4];
extern int DAT_0050f138[4];
extern int DAT_0050f140[4];
extern int DAT_0050f148[4];
extern int DAT_0050f150[4];
extern int DAT_0050f160[4];
extern int DAT_0050f168[4];
extern int DAT_00586f20[4];
}
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(void *); };
#define SETSTR() do { \
    int v; int s4; int old; int *hd; \
    if (DAT_00586f20[0] == 0) { v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); DAT_00586f20[0] = v; } \
    s4 = StringPool_Intern(DAT_00586f20[0], 0); \
    old = arg3->_wCheckName; \
    if (old != 0) { hd = (int *)(old - 8); v = *(int *)(old - 4) - 1; *(int *)(old - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*hd, hd); } \
    arg3->_wCheckName = s4; \
    FUN_00395250(arg0, arg1, arg2, arg3); \
} while (0)
extern "C" void FUN_00394bf0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3);
void FUN_00394bf0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3) {
    if (strcmp(arg3->_wCheckName, DAT_0050f138) == 0 || strcmp(arg3->_wCheckName, DAT_0050f140) == 0) {
        if (!(FUN_00392be0(arg0, arg2, arg3, 2) & 0xFF)) {
            SETSTR();
        }
    } else if (strcmp(arg3->_wCheckName, DAT_0050f148) == 0) {
        int a2 = arg1->_name;
        int a3 = arg2->_ramNo;
        a2 = a2 ? a2 : (int)DAT_004e0858;
        beMessenger_SendNamed(arg0->_messenger, DAT_0050eff8, a2, a3, DAT_0050f150);
        if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
            SETSTR();
        }
    } else if (strcmp(arg3->_wCheckName, DAT_0050f160) == 0) {
        if (!(FUN_00392be0(arg0, arg2, arg3, 0) & 0xFF)) {
            SETSTR();
        }
    } else if (strcmp(arg3->_wCheckName, DAT_0050f168) == 0) {
        if (!(FUN_00392be0(arg0, arg2, arg3, 1) & 0xFF)) {
            SETSTR();
        }
    } else {
        ((VO *)arg0)->vX(arg2);
    }
}
