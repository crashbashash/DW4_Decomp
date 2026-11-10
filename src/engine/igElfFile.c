#include "dw4/reflected.h"
int memset();
int Gap__Core__igProgramFile__vfunc_23();

int Gap__Core__igArenaMemoryPool__vfunc_109(void *arg0) {
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 124);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2060);
}

int Gap__Core__igArenaMemoryPool__vfunc_110(void *arg0) {
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg0) + 124);
    if (temp_v1 != 0) {
        return temp_v1 + *(int *)((char *)(arg0) + 160);
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2064);
}

static void FUN_00320930(unsigned char *arg0) {
    unsigned short x;
    ((unsigned char *)&x)[0] = arg0[1];
    ((unsigned char *)&x)[1] = arg0[0];
    *(unsigned short *)arg0 = x;
}

static void FUN_00320960(unsigned char *arg0) {
    union { unsigned char b[4]; int w; } u;
    u.b[0] = arg0[3];
    u.b[1] = arg0[2];
    u.b[2] = arg0[1];
    u.b[3] = arg0[0];
    *(int *)arg0 = u.w;
}

void FUN_003209a0(unsigned char *p) {
    FUN_00320930(p + 16);
    FUN_00320930(p + 18);
    FUN_00320960(p + 20);
    FUN_00320960(p + 24);
    FUN_00320960(p + 28);
    FUN_00320960(p + 32);
    FUN_00320960(p + 36);
    FUN_00320930(p + 40);
    FUN_00320930(p + 42);
    FUN_00320930(p + 44);
    FUN_00320930(p + 46);
    FUN_00320930(p + 48);
    FUN_00320930(p + 50);
}

void FUN_00320a20(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        FUN_00320960(p);
        FUN_00320960(p + 4);
        FUN_00320960(p + 8);
        FUN_00320960(p + 12);
        FUN_00320960(p + 16);
        FUN_00320960(p + 20);
        FUN_00320960(p + 24);
        FUN_00320960(p + 28);
        FUN_00320960(p + 32);
        FUN_00320960(p + 36);
        p += 40;
    }
}

void FUN_00320aa0(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        FUN_00320960(p);
        FUN_00320960(p + 4);
        FUN_00320960(p + 8);
        FUN_00320930(p + 14);
        p += 16;
    }
}

void Gap__Core__igElfFile__vfunc_23(igElfFile *arg0) {
    Gap__Core__igProgramFile__vfunc_23();
    memset(arg0->_header, 0, 0x34);
    arg0->_sectionHeaderStringTableSize = 0;
    arg0->_sectionHeaderStringTable = 0;
    arg0->_sectionHeaderCount = 0;
    arg0->_sectionHeaders = 0;
    arg0->_symbolStringTableSize = 0;
    arg0->_symbolStringTable = 0;
    arg0->_symbolCount = 0;
    arg0->_symbols = 0;
}
