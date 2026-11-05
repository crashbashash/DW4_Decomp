#include "dw4/reflected.h"
extern "C" {
int FUN_00119ff0(int, int, int *, int *, int *);
extern int DAT_004c91b0[4];
extern int DAT_004c91b4[4];
extern beSvPlatBaseData * DAT_0058a600[4];
extern int DAT_0058a834[4];
extern int DAT_0058a894[4];
extern char GPR_00554e60;
extern unsigned char GPR_00554e64;
unsigned char Gap__Bec__beSvGetFreeSizeApi__vfunc_22(beSvGetFreeSizeApi *arg0);
}

unsigned char Gap__Bec__beSvGetFreeSizeApi__vfunc_22(beSvGetFreeSizeApi *arg0) {
    int temp_a0;
    int v;
    beSvPlatBaseData *q;
    int e;

    if (arg0->_isEnd != 0) {
        return 1U;
    }
    if (GPR_00554e64 == 1) {
        return 0U;
    }
    q = DAT_0058a600[0];
    switch (arg0->_st0) {
    case 0:
        *(int *)((char *)arg0 + 60) = 0;
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        temp_a0 = arg0->_connect * 8;
        if (FUN_00119ff0(*(int *)((char *)DAT_004c91b0 + temp_a0), *(int *)((char *)DAT_004c91b4 + temp_a0), (int *)((char *)arg0 + 76), (int *)((char *)arg0 + 80), (int *)((char *)arg0 + 84)) >= 0) {
            DAT_0058a834[0] = 1;
            arg0->_st0 = arg0->_st0 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        }
        break;
    case 2:
        if (DAT_0058a834[0] == 1) {
            return 0U;
        }
        e = DAT_0058a894[0];
        if (e >= 0) {
            switch (*(int *)((char *)arg0 + 76)) {
            case 2:
                arg0->_result = 2;
                arg0->_fileCapa = 0x80;
                arg0->_isEnd = 1U;
                switch (*(int *)((char *)arg0 + 84)) {
                case 0:
                    arg0->_memCapa = 0x04E00000U;
                    break;
                case 1:
                    arg0->_memCapa = *(int *)((char *)arg0 + 80) << 0xA;
                    break;
                }
                if (!(q->_memNeed > (unsigned int) arg0->_memCapa)) {
                    arg0->_result = 2;
                } else {
                    arg0->_result = 9;
                }
                break;
            case 0:
            case 3:
            case 1:
                arg0->_result = 0xC;
                break;
            }
            arg0->_isEnd = 1U;
            break;
        }
        *(int *)((char *)arg0 + 60) = *(int *)((char *)arg0 + 60) + 1;
        if ((unsigned char)(*(int *)((char *)arg0 + 60) < 3) == 1) {
            arg0->_st0 = 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            arg0->_st1 = 0;
        } else {
            switch (e) {
            case -2:
                arg0->_memCapa = 0x04E00000U;
                arg0->_fileCapa = 0x80;
                arg0->_result = 2;
                arg0->_isEnd = 1U;
                break;
            case -5:
                arg0->_result = 5;
                arg0->_isEnd = 1U;
                break;
            default:
            case -1:
                arg0->_result = 0xC;
                arg0->_isEnd = 1U;
                break;
            }
        }
        break;
    }
    if (arg0->_isEnd == 1) {
        GPR_00554e60 = 0;
    }
    return arg0->_isEnd;
}
