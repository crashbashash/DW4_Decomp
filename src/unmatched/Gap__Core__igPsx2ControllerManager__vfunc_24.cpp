#include "dw4/reflected.h"
class Al { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
class Pd { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void vX(int); };
class Pe { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void vX(int); };
struct Rt { char pad[56]; int f56; };
extern "C" {
int FUN_00117c78(...);
int FUN_00117ed8(...);
int FUN_0012aba0(...);
void *FUN_00147090(...);
int FUN_00225300(...);
void *FUN_002b9500(...);
int FUN_00306770(...);
int FUN_0032cf50(...);
int Memory_FreeBuffer(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(int, int);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int igStrCmp(...);
int sceMtapPortOpen(...);
extern char *DAT_004c22f0[4];
extern int DAT_004d6cc8[4];
extern int DAT_004d6ce0[4];
extern int DAT_004d7020[4];
extern int DAT_004d7030[4];
extern int DAT_004d7040[4];
extern int DAT_004d7050[4];
extern int DAT_004d7058[4];
extern int DAT_004d7060[4];
extern int DAT_004fb410[4];
extern Rt *DAT_00586dc8[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554b18;
extern unsigned char GPR_00554c14;
}
extern "C" void Gap__Core__igPsx2ControllerManager__vfunc_24(igPsx2ControllerManager *arg0, int arg1);
void Gap__Core__igPsx2ControllerManager__vfunc_24(igPsx2ControllerManager *arg0, int arg1) {
    igObject *sp8C;
    void *al;
    char *s0;
    int s3;
    igPsx2Controller * volatile sp88;
    int s2;
    Al *al2;
    int s1;
    int v1;
    int sp84;
    void *base;
    int mem;
    int *pp;
    igObject *q;
    int sp80;
    int sp7C;
    if (GPR_00554b18 == 0) {
        GPR_00554b18 = 1;
        arg0->_validControllerManager = 1;
        if (arg0->_loadIRXs != 0) {
            FUN_0032cf50(&sp84, &DAT_004d7020[0], 1, 0, 0);
            FUN_0032cf50(&sp80, &DAT_004d7030[0], 1, 0, 0);
        }
        FUN_00117c78(0);
        base = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            al = base;
        } else {
            al = Memory_GetAllocatorBySelector(DAT_00587060[0]);
        }
        sp8C = (igObject *)FUN_002b9500(al);
        if (FUN_00306770(DAT_00586dc8[0]->f56, 3, &DAT_004d7040[0], &sp8C, &DAT_004d7050[0], 0) != 0) {
            s0 = *(char **)((char *)sp8C + 8);
            s0 = (s0 == 0) ? DAT_004c22f0[0] : s0;
            if (igStrCmp(s0, &DAT_004d6ce0[0]) == 0) {
                v1 = 0xFFFF;
                arg0->_multitap = v1;
            } else if (igStrCmp(s0, &DAT_004d6cc8[0]) == 0) {
                arg0->_multitap = 0;
            } else if (FUN_0012aba0(s0, &DAT_004d7058[0], 4) == 0) {
                v1 = 2;
                if (*(char *)(s0 + 4) == 0x30) { v1 = 1; arg0->_multitap = v1; } else { arg0->_multitap = v1; }
            }
        }
        q = sp8C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
        sp8C = 0;
        s3 = 0;
        if (arg0->_multitap != 0) {
            if (arg0->_loadIRXs != 0) {
                FUN_0032cf50(&sp7C, &DAT_004d7060[0], 1, 0, 0);
                pp = (int *)((int)&sp7C + 0);
                if (*pp == DAT_004fb410[0]) {
                    FUN_00225300();
                    if (arg0->_multitap & 1) sceMtapPortOpen(0);
                    if (arg0->_multitap & 2) sceMtapPortOpen(1);
                }
            }
            s3 = 0;
        }
        s3 = 0;
        do {
            s1 = 0;
            { unsigned m = arg0->_multitap; s2 = !(m & (1u << s3)) ? 1 : 4; }
            for (; s1 < s2; s1++) {
                base = igObject_GetAllocator(arg0);
                if (GPR_00554c14 != 0) {
                    al2 = (Al *)base;
                } else {
                    al2 = (Al *)Memory_GetAllocatorBySelector(DAT_00587060[0]);
                }
                mem = al2->vX(0x100, 0x40);
                if (FUN_00117ed8(s3, s1, mem) != 1) {
                    Memory_FreeBuffer(mem);
                } else {
                    sp88 = (igPsx2Controller *)FUN_00147090(igObject_GetAllocator(arg0));
                    { igPsx2Controller *t = sp88; t->_port = s3; }
                    { igPsx2Controller *t = sp88; t->_slot = s1; }
                    { igPsx2Controller *t = sp88; ((Pd *)t)->vX((s3 | (s1 * 2)) & 0xFFFF); }
                    { igPsx2Controller *t = sp88; t->_dmaBuffer = mem; }
                    { igPsx2Controller *t = sp88; ((Pe *)t)->vX(arg1); }
                    ObjectList_AppendRetained((int)(igObject *)arg0->_controllers, (int)sp88);
                    q = (igObject *)sp88;
                    if (q != 0) {
                        q->_refCount = q->_refCount - 1;
                        if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
                    }
                }
            }
            s3 += 1;
        } while (s3 < 2);
        q = sp8C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
}
