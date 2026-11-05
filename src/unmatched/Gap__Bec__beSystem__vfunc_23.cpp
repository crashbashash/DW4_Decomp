#include "dw4/reflected.h"
struct GlobalContextRecord { char pad0[8]; char f8; char pad1[47]; igObject *f56; igObject *f60; igObject *f64; };
extern "C" {
int FUN_002eb010(int);
void *Memory_GetAllocatorBySelector(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int *);
int igObject_Destroy(igObject *);
void *igObject_GetAllocator(beSystem *);
extern int DAT_004c22e8[4];
extern int DAT_0050fb10[4];
extern struct GlobalContextRecord *DAT_00586dd0[4];
extern int DAT_00586f20[4];
extern int DAT_00587060[4];
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beSystem__vfunc_23(beSystem *arg0);
}
void Gap__Bec__beSystem__vfunc_23(beSystem *arg0) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    int *temp_v1;
    int *temp_s0;
    igObject *a;
    void *al;
    struct GlobalContextRecord *r;
    void *al2;
    struct GlobalContextRecord *r2;
    igObject *a2;
    void *al3;
    struct GlobalContextRecord *r3;
    igObject *a3;
    arg0->_isFirstTime = 0;
    arg0->_isActive = 1;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050fb10[0]);
    temp_v1 = (int *)arg0->_nextStage;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_nextStage = (int)temp_s0;
    a = (igObject *)arg0->_bootDirectory;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    arg0->_bootDirectory = 0;
    DAT_004c22e8[0] = 0x186A0;
    DAT_00586dd0[0]->f8 = 0;
    al = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        al = (void *)(int)al;
    } else {
        al = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    r = DAT_00586dd0[0];
    if (al != 0) {
        ((igObject *)al)->_refCount = (int)((igObject *)al)->_refCount + 1;
    }
    a = r->f64;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    r->f64 = (igObject *)al;
    al2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        al2 = (void *)(int)al2;
    } else {
        al2 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    r2 = DAT_00586dd0[0];
    if (al2 != 0) {
        ((igObject *)al2)->_refCount = (int)((igObject *)al2)->_refCount + 1;
    }
    a2 = r2->f60;
    if (a2 != 0) {
        a2->_refCount = (int)a2->_refCount - 1;
        if (((unsigned long long)((long long)(int)a2->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a2);
        }
    }
    r2->f60 = (igObject *)al2;
    al2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        al2 = (void *)(int)al2;
    } else {
        al2 = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    r = DAT_00586dd0[0];
    if (al2 != 0) {
        ((igObject *)al2)->_refCount = (int)((igObject *)al2)->_refCount + 1;
    }
    a = r->f56;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    r->f56 = (igObject *)al2;
}
