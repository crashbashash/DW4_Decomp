#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
extern int DAT_00586f20[];
extern beSystem *DAT_0058a1b8[];
void ShutDown(void);
}

void ShutDown(void) {
    beSystem *s0;
    int s1;
    int *a0;
    int *hdr;
    int v;
    int obj;
    s0 = DAT_0058a1b8[0];
    s0->_isShutDown = 1;
    s0->_isStageLoop = 0;
    if (DAT_00586f20[0] == 0) {
        obj = FUN_002eb010(0x10);
        if (obj != 0) {
            obj = StringPool_Construct(obj);
        }
        DAT_00586f20[0] = obj;
    }
    s1 = StringPool_Intern(DAT_00586f20[0], 0);
    a0 = (int *)s0->_nextStage;
    if (a0 != 0) {
        hdr = a0 - 2;
        v = a0[-1] - 1;
        a0[-1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    s0->_nextStage = s1;
}
