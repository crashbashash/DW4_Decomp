#include "dw4/reflected.h"
extern "C" {
int strlen(void *);
void *FUN_00236f80(int, int);
int FUN_002eb010(int);
int FUN_0030b3c0(void *, int);
int FUN_0030b460(void *, void *, int, int);
int FUN_003bbd40(void);
void StringChunk_ReleaseHeader(void *, int);
int StringPool_Construct(int);
char *StringPool_Intern(int, int);
void beMessenger_AppendBool(int, unsigned char);
void beMessenger_ClearBool(int);
int beMessenger_GetString(int, int);
int beMessenger_GetStringCount(int);
int beMessenger_ResolveEnumValue(int, int, int);
int beMessenger_SendGroup(int, void *, void *);
int igObject_Destroy(void *);
int igStrCmp(int, void *);
extern int DAT_004c22f0[4];
extern int DAT_005155d0[4];
extern int DAT_005155e0[4];
extern int DAT_005155e8[4];
extern int DAT_00515698[4];
extern int DAT_005156a0[4];
extern int DAT_005156a8[4];
extern int DAT_005156b0[4];
extern int DAT_00586f20[4];
extern int DAT_00588518[4];
int Gap__Bec__beNDMWStageCtl__vfunc_34(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1, void *arg2);
}

struct Col { virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44(); virtual void e45(); virtual void e46(); virtual void e47(); virtual void e48(); virtual void e49(); virtual void e50(); virtual void e51(); virtual void e52(); virtual void e53(); virtual void e54(); virtual void e55(); virtual void e56(); virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60(); virtual void e61(); virtual void e62(); virtual void e63(); virtual void e64(); virtual void e65(); virtual void e66(); virtual void e67(); virtual void e68(); virtual void e69(); virtual void e70(); virtual void e71(); virtual void e72(); virtual void e73(); virtual void e74(); virtual void e75(); virtual void e76(); virtual void e77(); virtual void e78(); virtual void e79(); virtual void e80(); virtual void e81(); virtual void e82(); virtual void e83(); virtual void e84(); virtual void e85(); virtual void e86(); virtual void e87(); virtual void e88(); virtual void e89(); virtual void e90(); virtual void e91(); virtual void e92(); virtual void e93(); virtual void e94(); virtual void e95(); virtual void e96(); virtual void e97(); virtual void e98(); virtual void e99(); virtual void e100(); virtual void e101(); virtual void e102(); virtual void e103(); virtual void e104(); virtual void e105(); virtual void e106(); virtual void e107(); virtual void e108(); virtual void e109(); virtual void e110(); virtual void e111(); virtual void e112(); virtual void e113(); virtual void e114(); virtual void e115(); virtual void e116(); virtual void e117(); virtual void e118(); virtual void e119(); virtual void e120(); virtual void e121(); virtual void e122(); virtual void e123(); virtual void e124(); virtual void e125(); virtual void e126(); virtual void e127(); virtual void e128(); virtual void e129(); virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174(); virtual void e175(); virtual void setColor(int); };
struct Cam { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual Col *getCol(); };
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((void *)h_[0], (int)h_); }
#define POOL() if (!DAT_00586f20[0]) { int p_ = FUN_002eb010(16); if (p_) p_ = StringPool_Construct(p_); DAT_00586f20[0] = p_; }
struct Ref {
    igObject *p;
    ~Ref() {
        igObject *q = p;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
};

int Gap__Bec__beNDMWStageCtl__vfunc_34(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1, void *arg2) {
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003bbd40(), *(int *)((char *)arg2 + 20))) {
    case 0: {
        Ref sp;
        sp.p = (igObject *)((beSystem *)arg0->_system)->_globalStrObj;
        if (sp.p != 0) {
            sp.p->_refCount = sp.p->_refCount + 1;
        }
        FUN_0030b3c0(sp.p, beMessenger_GetString(arg0->_messenger, 0));
        void *t = sp.p;
        int temp_s0 = ((igStringObj *)t)->_length;
        FUN_0030b460(t, &DAT_00515698[0], temp_s0, strlen(&DAT_00515698[0]));
        ((Cam *)((igInsightCore *)arg0->_insight)->_window)->getCol()->setColor(0xFF000000);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e8[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e0[0]);
        int var_s2 = (((igStringObj *)sp.p)->_buffer == 0) ? DAT_004c22f0[0] : ((igStringObj *)sp.p)->_buffer;
        beSystem *temp_s0_2 = (beSystem *)arg0->_system;
        POOL();
        char *temp_s2 = (char *)StringPool_Intern(DAT_00586f20[0], var_s2);
        STR_RELEASE(temp_s0_2->_nextStage);
        temp_s0_2->_nextStage = (int)temp_s2;
        ((beSystem *)arg0->_system)->_isStageLoop = 0;
        return 1;
    }
    case 1:
        if (beMessenger_GetStringCount(arg0->_messenger) > 0) {
            int temp_s2_2 = beMessenger_GetString(arg0->_messenger, 0);
            bePadManager *temp_s0_3 = (bePadManager *)FUN_00236f80(arg0->_insight, DAT_00588518[0]);
            if (igStrCmp(temp_s2_2, &DAT_005156a0[0]) == 0) {
                temp_s0_3->_isPadDisable = 0;
            } else if (igStrCmp(temp_s2_2, &DAT_005156a8[0]) == 0) {
                temp_s0_3->_isPadDisable = 1;
            } else if (igStrCmp(temp_s2_2, &DAT_005156b0[0]) == 0) {
                beMessenger_ClearBool(arg0->_messenger);
                beMessenger_AppendBool(arg0->_messenger, temp_s0_3->_isPadDisable);
            }
        }
        return 1;
    case 2:
        beMessenger_AppendBool(arg0->_messenger, arg1->_st0 != 0);
        return 1;
    default:
        return 0;
    }
}
