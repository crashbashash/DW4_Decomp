#include "dw4/reflected.h"
struct VO { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" {
unsigned char FUN_00391a10(...);
unsigned char FUN_00391fe0(...);
unsigned char FUN_00393260(...);
unsigned char FUN_00393b20(...);
unsigned char FUN_003943c0(...);
unsigned char FUN_00394640(...);
unsigned char FUN_00394920(...);
unsigned char FUN_00394ad0(...);
unsigned char FUN_00394b30(...);
unsigned char FUN_00394fa0(...);
unsigned char FUN_00395070(...);
unsigned char FUN_00394ae0(...);
extern int DAT_00588df8[4];
extern int DAT_00588e08[4];
extern int DAT_00588dd8[4];
extern int DAT_00588da0[4];
extern int DAT_00588d88[4];
extern int DAT_00588d70[4];
extern int DAT_00588d68[4];
extern int DAT_00588d20[4];
extern int DAT_00588d50[4];
extern int DAT_00588e10[4];
extern int DAT_00588e28[4];
extern int DAT_00588d60[4];
extern int DAT_00588df0[4];
extern int DAT_00588e20[4];
extern int DAT_00588e00[4];
void FUN_00395250(int arg0, int arg1, int arg2, beModelCtrlInfoWork *arg3);
}
extern "C" void FUN_00395250(int arg0, int arg1, int arg2, beModelCtrlInfoWork *arg3) {
    int s7;
    volatile beModelCtrlData *spA0;
    int s2;
    unsigned char s1;
    VO *s0;
    s7 = 0;
    spA0 = (beModelCtrlData *)arg3->_comData;
    s2 = arg3->_comIndex;
    if (s2 != ((igObjectList *)spA0->_comList)->_count) {
        do {
            s1 = 1;
            s0 = ((VO **)((igObjectList *)spA0->_comList)->_data)[s2];
            if (DAT_00588df8[0] == s0->vX()) {
                s1 = FUN_00391a10(arg0, arg3, s0);
                s2 += 1;
            } else if (DAT_00588e08[0] == s0->vX()) {
                s1 = FUN_00391fe0(arg0, arg1, arg2, s0);
                s2 += 1;
            } else if (DAT_00588dd8[0] == s0->vX()) {
                s1 = FUN_00393260(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588da0[0] == s0->vX()) {
                s1 = FUN_00393260(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588d88[0] == s0->vX()) {
                s1 = FUN_00393260(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588d70[0] == s0->vX()) {
                s1 = FUN_00393b20(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588d68[0] == s0->vX()) {
                s1 = FUN_00394b30(arg0, arg3, s0);
                s2 += 1;
            } else if (DAT_00588d20[0] == s0->vX()) {
                s1 = FUN_00394fa0(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588d50[0] == s0->vX()) {
                s1 = FUN_00395070(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588e10[0] == s0->vX()) {
                s1 = FUN_003943c0(arg0, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588e28[0] == s0->vX()) {
                s1 = FUN_00394640(arg0, arg1, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588d60[0] == s0->vX()) {
                s1 = FUN_00394920(arg0, arg1, arg2, arg3, s0);
                s2 += 1;
            } else if (DAT_00588df0[0] == s0->vX()) {
                s1 = FUN_00394ad0(arg0, arg1, arg3, s0);
                s2 += 1;
            } else if (DAT_00588e20[0] == s0->vX()) {
                if (arg3->_comLabelCount != 0) {
                    s1 = 0;
                } else {
                    arg3->_comLabelCount = 1;
                    s2 += 1;
                }
            } else if (DAT_00588e00[0] == s0->vX()) {
                s7 = FUN_00394ae0(arg0, arg2, s0) & 0xFF;
            }
        } while (s7 == 0 && (s1 & 0xFF) && s2 != ((igObjectList *)spA0->_comList)->_count);
    }
    if (!(s7 & 0xFF)) {
        arg3->_comIndex = s2;
    }
}
