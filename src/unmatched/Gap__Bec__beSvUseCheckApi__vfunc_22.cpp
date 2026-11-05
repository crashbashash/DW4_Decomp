#include "dw4/reflected.h"
extern "C" {
extern int FUN_00119ff0(int, int, void *, int, void *);
extern int DAT_004c91b0[4];
extern int DAT_004c91b4[4];
extern int DAT_0058a834[4];
extern int DAT_0058a894[4];
extern char GPR_00554e60;
extern unsigned char GPR_00554e64;
}
typedef struct beSvUseCheckApiTail { char pad0[60]; int f60; int f64; char p68[4]; int f72; } beSvUseCheckApiTail;
extern "C" {
unsigned char Gap__Bec__beSvUseCheckApi__vfunc_22(beSvUseCheckApi *arg0);
}
unsigned char Gap__Bec__beSvUseCheckApi__vfunc_22(beSvUseCheckApi *arg0) {
    /* fields past the reflected beSvUseCheckApi layout (+60 retry count, +64/+72 out words) */
    beSvUseCheckApiTail *x = (beSvUseCheckApiTail *)arg0;
    int a0;
    int v;
    unsigned char tc;
    if (arg0->_isEnd != 0) return 1;
    if (GPR_00554e64 == 1) return 0;
    switch (arg0->_st0) {
    case 0:
        x->f60 = 0;
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        a0 = arg0->_connect * 8;
        if (FUN_00119ff0(*(int *)((char *)DAT_004c91b0 + a0), *(int *)((char *)DAT_004c91b4 + a0), &x->f64, 0, &x->f72) >= 0) {
            DAT_0058a834[0] = 1;
            arg0->_st0 = arg0->_st0 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        }
        break;
    case 2:
        if (DAT_0058a834[0] == 1) return 0;
        v = DAT_0058a894[0];
        if (v >= 0) {
            switch (x->f64) {
            case 2:
                if (x->f72 == 1) {
                    arg0->_result = 2;
                } else {
                    arg0->_result = 7;
                }
                break;
            case 0:
            case 1:
            case 3:
                arg0->_result = 12;
                break;
            }
            arg0->_isEnd = 1;
        } else {
            x->f60 = x->f60 + 1;
            tc = x->f60 < 3;
            if (tc == 1) {
                arg0->_st0 = 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            } else {
                switch (v) {
                case -5:
                    arg0->_result = 5;
                    break;
                case -1:
                case -2:
                default:
                    arg0->_result = 12;
                    break;
                }
                arg0->_isEnd = 1;
            }
        }
        break;
    default:
        break;
    }
    if (arg0->_isEnd != 0) GPR_00554e60 = 0;
    return arg0->_isEnd;
}
