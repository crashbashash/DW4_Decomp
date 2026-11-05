#include "dw4/reflected.h"
extern "C" {
extern int FUN_0011a500(int, int);
extern int DAT_004c91b0[4];
extern int DAT_004c91b4[4];
extern int DAT_0058a870[4];
extern int DAT_0058a8d0[4];
extern char GPR_00554e60;
extern unsigned char GPR_00554e64;
unsigned char Gap__Bec__beSvFormatApi__vfunc_22(beSvFormatApi *arg0);
}
unsigned char Gap__Bec__beSvFormatApi__vfunc_22(beSvFormatApi *arg0) {
    int a0;
    int v;
    int t;
    unsigned char tc;
    if (arg0->_isEnd != 0) return 1;
    if (GPR_00554e64 == 1) return 0;
    switch (arg0->_st0) {
    case 0:
        *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ = 0;
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        a0 = arg0->_connect * 8;
        if (FUN_0011a500(*(int *)((char *)DAT_004c91b0 + a0), *(int *)((char *)DAT_004c91b4 + a0)) >= 0) {
            DAT_0058a870[0] = 1;
            arg0->_st0 = arg0->_st0 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        }
        break;
    case 2:
        if (DAT_0058a870[0] == 1) return 0;
        v = DAT_0058a8d0[0];
        if (v >= 0) {
            arg0->_isEnd = 1;
            arg0->_result = 2;
        } else {
            *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ = *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ + 1;
            tc = *(int *)((char *)arg0 + 60) /* unreflected field past the last reflected member */ < 3;
            if (tc == 1) {
                arg0->_st0 = 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            } else {
                switch (v) {
                case -5:
                    arg0->_result = 12;
                    arg0->_isEnd = 1;
                    break;
                default:
                    arg0->_result = 12;
                    arg0->_isEnd = 1;
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
    if (arg0->_isEnd != 0) GPR_00554e60 = 0;
    return arg0->_isEnd;
}
