#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int Matrix44_Copy(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
igObject *beMessenger_GetObject(...);
int beMessenger_SendNamed(...);
void igObject_Destroy(igObject *);
extern int DAT_0050ef18[4];
extern int DAT_0050f000[4];
extern int DAT_00586f20[4];
}
extern "C" void FUN_00392050(beModelCtrlInfoRideOn *arg0, int arg1, int arg2, int arg3);
void FUN_00392050(beModelCtrlInfoRideOn *arg0, int arg1, int arg2, int arg3) {
    int sp60[16];
    igObject *s1;
    int s0, v;
    int *hd;
    int old;
    igObject *a0;
    beMessenger_SendNamed(arg3, &DAT_0050ef18[0], arg1, arg2, &DAT_0050f000[0]);
    s1 = beMessenger_GetObject(arg3, 0);
    Matrix44_Copy(sp60, (char *)s1 + 32);
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s0 = StringPool_Intern(DAT_00586f20[0], arg1);
    old = arg0->_modelName;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_modelName = s0;
    arg0->_modelRamNo = arg2;
    if (s1 != 0) {
        s1->_refCount = s1->_refCount + 1;
    }
    a0 = (igObject *)arg0->_modelNode;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if (((unsigned long long)(long long)a0->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(a0);
    }
    arg0->_modelNode = (int)s1;
    Matrix44_Copy(&arg0->_oldMatrix, sp60);
}
