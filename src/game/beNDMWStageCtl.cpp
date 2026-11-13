#include "dw4/reflected.h"
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((void *)h_[0], (int)h_); }
#define POOL() if (!g_stringPool[0]) { int p_ = StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool[0] = p_; }

extern "C" void Gap__Bec__beNDMWStageCtl__vfunc_32(void);
extern "C" int Gap__Bec__beNDMWStageCtl__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWStageCtl__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_SetFreezeTime(...);
extern "C" int strlen(void *);
extern "C" void * igInsightCore_FindManager(...);
extern "C" int StringPool_Allocate(int);
extern "C" int igStringObj_Set(void *, int);
extern "C" int igStringObj_Insert(void *, void *, int, int);
extern "C" int FUN_003bbd40(void);
extern "C" void StringChunk_ReleaseHeader(void *, int);
extern "C" int StringPool_Construct(int);
extern "C" char *StringPool_Intern(int, int);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_ClearBool(int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_GetStringCount(int);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int igObject_Destroy(void *);
extern "C" int strcmp(int, void *);
extern "C" int g_beNDMWStageCtlInfo_metaObject[4];
extern "C" int g_beNDMWStageCtl_metaObject[4];
extern "C" void Gap__Bec__beNDMWStageCtl__vfunc_29(beNDMWStageCtl * p0, int p1, char * p2, int p3, int p4);
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" int DAT_005155c0[4];
extern "C" int DAT_005155d0[4];
extern "C" int DAT_005155d8[4];
extern "C" int DAT_005155e0[4];
extern "C" int DAT_005155e8[4];
extern "C" int DAT_005155f0[4];
extern "C" int DAT_005155f8[4];
extern "C" int DAT_00515600[4];
extern "C" int DAT_00515608[4];
extern "C" int DAT_00515618[4];
extern "C" int DAT_00515620[4];
extern "C" int DAT_00515628[4];
extern "C" int DAT_00515630[4];
extern "C" int DAT_00515640[4];
extern "C" int DAT_00515650[4];
extern "C" int DAT_00515660[4];
extern "C" int DAT_00515670[4];
extern "C" int g_bePadManager_metaObject[4];
/* matching construct: dummy-virtual classes so the window chain dispatches through retail vtable slots */
struct Obj2 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void v712(unsigned); };
struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual Obj2 *v152(); };
extern "C" void Gap__Bec__beNDMWStageCtl__vfunc_31(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1);
extern "C" int g_stringObjEmptyText[4];
extern "C" int DAT_00515698[4];
extern "C" int DAT_005156a0[4];
extern "C" int DAT_005156a8[4];
extern "C" int DAT_005156b0[4];
extern "C" int g_stringPool[4];
struct Col { virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44(); virtual void e45(); virtual void e46(); virtual void e47(); virtual void e48(); virtual void e49(); virtual void e50(); virtual void e51(); virtual void e52(); virtual void e53(); virtual void e54(); virtual void e55(); virtual void e56(); virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60(); virtual void e61(); virtual void e62(); virtual void e63(); virtual void e64(); virtual void e65(); virtual void e66(); virtual void e67(); virtual void e68(); virtual void e69(); virtual void e70(); virtual void e71(); virtual void e72(); virtual void e73(); virtual void e74(); virtual void e75(); virtual void e76(); virtual void e77(); virtual void e78(); virtual void e79(); virtual void e80(); virtual void e81(); virtual void e82(); virtual void e83(); virtual void e84(); virtual void e85(); virtual void e86(); virtual void e87(); virtual void e88(); virtual void e89(); virtual void e90(); virtual void e91(); virtual void e92(); virtual void e93(); virtual void e94(); virtual void e95(); virtual void e96(); virtual void e97(); virtual void e98(); virtual void e99(); virtual void e100(); virtual void e101(); virtual void e102(); virtual void e103(); virtual void e104(); virtual void e105(); virtual void e106(); virtual void e107(); virtual void e108(); virtual void e109(); virtual void e110(); virtual void e111(); virtual void e112(); virtual void e113(); virtual void e114(); virtual void e115(); virtual void e116(); virtual void e117(); virtual void e118(); virtual void e119(); virtual void e120(); virtual void e121(); virtual void e122(); virtual void e123(); virtual void e124(); virtual void e125(); virtual void e126(); virtual void e127(); virtual void e128(); virtual void e129(); virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174(); virtual void e175(); virtual void setColor(int); };
struct Cam { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual Col *getCol(); };
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
extern "C" int Gap__Bec__beNDMWStageCtl__vfunc_34(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1, void *arg2);

void Gap__Bec__beNDMWStageCtl__vfunc_32(void)
{
}

void Gap__Bec__beNDMWStageCtl__vfunc_29(beNDMWStageCtl * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, ((char *)DAT_005155c0), 0, -1);
}

int Gap__Bec__beNDMWStageCtl__vfunc_30(void)
{
    return g_beNDMWStageCtlInfo_metaObject[0];
}

void Gap__Bec__beNDMWStageCtl__vfunc_31(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1) {
    bePadData *pad;
    bool ok;
    switch (arg1->_st0) {
    case 0:
        if (((beSystem *)arg0->_system)->_isSResetEnable == 0) return;
        pad = bePadManager_GetPadForPlayer(((int)igInsightCore_FindManager(arg0->_insight, g_bePadManager_metaObject[0])), 0);
        int a = pad->_trigger;
        int b = pad->_button;
        ok = (a & 8) != 0 && (b & 1) != 0;
        if (!ok) return;
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
        return;
    case 1:
        if (((beSystem *)arg0->_system)->_isSResetEnable == 0) {
            arg1->_st0 = 0;
            arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
            return;
        }
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155d8[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e0[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e8[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155f0[0], &DAT_005155f8[0]);
        if (beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) {
            beMessenger_SendGroup(arg0->_messenger, &DAT_005155f0[0], &DAT_00515600[0]);
            ((Obj *)((igInsightCore *)arg0->_insight)->_window)->v152()->v712(0xFF000000);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_00515608[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00515618[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00515620[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_00515628[0]);
        }
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
        return;
    case 2:
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155f0[0], &DAT_005155f8[0]);
        if (beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) return;
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00515608[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515618[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515620[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00515628[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_00515630[0], &DAT_00515640[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_00515650[0], &DAT_00515640[0]);
        beMessenger_SetFreezeTime(arg0->_messenger, 1);
    case 3:
    case 4:
        arg1->_st0 = arg1->_st0 + 1;
        arg1->_st3 = 0; arg1->_st2 = 0; arg1->_st1 = 0;
        return;
    case 5:
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005155c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00515660[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00515670[0]);
        break;
    }
}

int Gap__Bec__beNDMWStageCtl__vfunc_34(beNDMWStageCtl *arg0, beNDMWStageCtlInfoRam *arg1, void *arg2) {
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003bbd40(), *(int *)((char *)arg2 + 20))) {
    case 0: {
        Ref sp;
        sp.p = (igObject *)((beSystem *)arg0->_system)->_globalStrObj;
        if (sp.p != 0) {
            sp.p->_refCount = sp.p->_refCount + 1;
        }
        igStringObj_Set(sp.p, beMessenger_GetString(arg0->_messenger, 0));
        void *t = sp.p;
        int temp_s0 = ((igStringObj *)t)->_length;
        igStringObj_Insert(t, &DAT_00515698[0], temp_s0, strlen(&DAT_00515698[0]));
        ((Cam *)((igInsightCore *)arg0->_insight)->_window)->getCol()->setColor(0xFF000000);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e8[0]);
        beMessenger_SendGroup(arg0->_messenger, &DAT_005155d0[0], &DAT_005155e0[0]);
        int var_s2 = (((igStringObj *)sp.p)->_buffer == 0) ? g_stringObjEmptyText[0] : ((igStringObj *)sp.p)->_buffer;
        beSystem *temp_s0_2 = (beSystem *)arg0->_system;
        POOL();
        char *temp_s2 = (char *)StringPool_Intern(g_stringPool[0], var_s2);
        STR_RELEASE(temp_s0_2->_nextStage);
        temp_s0_2->_nextStage = (int)temp_s2;
        ((beSystem *)arg0->_system)->_isStageLoop = 0;
        return 1;
    }
    case 1:
        if (beMessenger_GetStringCount(arg0->_messenger) > 0) {
            int temp_s2_2 = beMessenger_GetString(arg0->_messenger, 0);
            bePadManager *temp_s0_3 = (bePadManager *)igInsightCore_FindManager(arg0->_insight, g_bePadManager_metaObject[0]);
            if (strcmp(temp_s2_2, &DAT_005156a0[0]) == 0) {
                temp_s0_3->_isPadDisable = 0;
            } else if (strcmp(temp_s2_2, &DAT_005156a8[0]) == 0) {
                temp_s0_3->_isPadDisable = 1;
            } else if (strcmp(temp_s2_2, &DAT_005156b0[0]) == 0) {
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

int Gap__Bec__beNDMWStageCtl__vfunc_20(void)
{
    return g_beNDMWStageCtl_metaObject[0];
}
