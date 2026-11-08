#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int FUN_00394400(beModelCtrl *, beBaseInfoRam *, int *, int, int *, int, int, int, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int *);
int strcmp(int, int *);
extern int DAT_004e0858[4];
extern int DAT_0050f038[4];
extern int DAT_0050f078[4];
extern int DAT_0050f120[4];
extern int DAT_00586f20[4];
}
#define SETSTR(fld, lit) { \
    int *p; \
    s = (int *)arg4->_name; \
    if (s != 0) { s = (int *)s; } else { s = &DAT_004e0858[0]; } \
    if (DAT_00586f20[0] == 0) { \
        int pool = FUN_002eb010(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        DAT_00586f20[0] = pool; \
    } \
    s = (int *)StringPool_Intern(DAT_00586f20[0], s); \
    p = (int *)arg3->fld; \
    if (p != 0) { \
        int *hd = p - 2; \
        int c = p[-1] - 1; \
        p[-1] = c; \
        if (c == 0) StringChunk_ReleaseHeader(*hd, hd); \
    } \
    arg3->fld = (int)s; }
extern "C" {
int FUN_00394640(beModelCtrl *arg0, beBaseInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlLUACALL *arg4);
}
int FUN_00394640(beModelCtrl *arg0, beBaseInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlLUACALL *arg4) {
    unsigned char ok;
    int *a2;
    int *a4;
    int t;
    int *s;
    ok = 0;
    t = arg4->_modeName;
    if (t == 0) {
        ok = 1;
    } else if (strcmp(t, &DAT_0050f120[0]) == 0) {
        SETSTR(_luaBHit, 0)
    } else if (strcmp(arg4->_modeName, &DAT_0050f038[0]) == 0) {
        SETSTR(_luaWHit, 0)
    } else if (strcmp(arg4->_modeName, &DAT_0050f078[0]) == 0) {
        SETSTR(_luaFHit, 0)
    } else {
        ok = 1;
    }
    if (ok) {
        a4 = (int *)arg1->_name;
        if (a4 != 0) { a4 = (int *)a4; } else { a4 = &DAT_004e0858[0]; }
        t = arg4->_modeName;
        a2 = (int *)arg4->_name;
        if (a2 != 0) { a2 = (int *)a2; } else { a2 = &DAT_004e0858[0]; }
        FUN_00394400(arg0, arg2, a2, t, a4, 0, 0, 0, 0, 0);
    }
    return 1;
}
