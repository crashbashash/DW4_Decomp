extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int beMessengerArgData_Clear(int);
extern int DAT_00586f20[16];
}
#include "dw4/reflected.h"
extern "C" {
void beMessengerDelay_Clear(beMessengerDelay *arg0);
}
void beMessengerDelay_Clear(beMessengerDelay *arg0) {
    int v;
    int v0;
    int *old;
    int *hd;
    int *s1;
    arg0->_isUse = 0;
    arg0->_sendTime = 0;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = (int *)arg0->_groupName;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_groupName = (int)s1;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = (int *)arg0->_infoName;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_infoName = (int)s1;
    arg0->_ramNo = 0;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = (int *)arg0->_message;
    if (old != 0) {
        hd = old - 2;
        v0 = old[-1] - 1;
        old[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_message = (int)s1;
    beMessengerArgData_Clear(arg0->_argData);
}
