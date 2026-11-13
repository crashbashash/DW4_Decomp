#include "dw4/reflected.h"

extern "C" int igInsightCore_FindManager(int, int);
extern "C" int __dl__FPv(void *);
extern "C" int igObject_Destroy(void *);
extern "C" int beLua__RunNamedChunk(int, int *, int);
extern "C" void beMessenger_SelectReceivers(int, const char *, const char *, int);
extern "C" void beMessenger_AppendString(int, const char *);
extern "C" void beMessenger_DispatchSelected(int, const char *);
extern "C" int Gap__Bec__beNDMWLogo__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWLogo__vfunc_20(void);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, int, int *);
extern "C" int FUN_003c22e0(...);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" void Gap__Bec__beNDMWLogo__vfunc_32(beNDMWLogo *arg0);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_0044a7f0(struct Ref **self, short flag);
extern "C" int text_txt_Tar_lua[4];
extern "C" int g_beLua_metaObject[4];
extern "C" int g_mdlEntity[4];
extern "C" int g_txtCallNo[4];
extern "C" void FUN_0044a870(beNDMWLogo *arg0, int arg1);
typedef struct O { char p0[20]; int m; } O;
extern "C" char TEXTCTL_11[];
extern "C" char TALKFONT01_3[];
extern "C" char text_font00[];
extern "C" char CLR_7[];
extern "C" char SWITCH_11[];
extern "C" char text_font01_2[];
extern "C" char text_font02_2[];
extern "C" char TALKFONT06[];
extern "C" char text_font03_2[];
extern "C" char text_font04_2[];
extern "C" char text_font05[];
extern "C" void FUN_0044a8d0(O *arg0);
extern "C" int g_beNDMWLogoInfo_metaObject[4];
extern "C" int g_beNDMWLogo_metaObject[4];
extern "C" int LOGO[4];
extern "C" void Gap__Bec__beNDMWLogo__vfunc_29(beNDMWLogo *self, int info);
extern "C" int Gap__Bec__beNDMWLogo__vfunc_34(beNDMWLogo *arg0, beBaseInfoRam *arg1, void *arg2);

void Gap__Bec__beNDMWLogo__vfunc_32(beNDMWLogo *arg0) {
    if (arg0->_padManager == 0) {
        arg0->_padManager = igInsightCore_FindManager(arg0->_insight, g_bePadManager_metaObject[0]);
    }
    if (arg0->_system_ == 0) {
        arg0->_system_ = igInsightCore_FindManager(arg0->_insight, g_beSystem_metaObject[0]);
    }
}

void **FUN_0044a7f0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void FUN_0044a870(beNDMWLogo *arg0, int arg1) {
    int temp_v0;

    temp_v0 = igInsightCore_FindManager(arg0->_insight, g_beLua_metaObject[0]);
    g_txtCallNo[0] = arg1;
    g_mdlEntity[0] = 0;
    beLua__RunNamedChunk(temp_v0, &text_txt_Tar_lua[0], 0);
}

void FUN_0044a8d0(O *arg0) {
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT01_3);
    beMessenger_AppendString(arg0->m, text_font00);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT01_3);
    beMessenger_AppendString(arg0->m, text_font01_2);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT01_3);
    beMessenger_AppendString(arg0->m, text_font02_2);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT06);
    beMessenger_AppendString(arg0->m, text_font01_2);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT06);
    beMessenger_AppendString(arg0->m, text_font02_2);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT06);
    beMessenger_AppendString(arg0->m, text_font03_2);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT06);
    beMessenger_AppendString(arg0->m, text_font04_2);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
    beMessenger_SelectReceivers(arg0->m, TEXTCTL_11, 0, -1);
    beMessenger_AppendString(arg0->m, TALKFONT06);
    beMessenger_AppendString(arg0->m, text_font05);
    beMessenger_AppendString(arg0->m, CLR_7);
    beMessenger_DispatchSelected(arg0->m, SWITCH_11);
}

int Gap__Bec__beNDMWLogo__vfunc_30(void)
{
    return g_beNDMWLogoInfo_metaObject[0];
}

/* Registers the logo controller with its messenger as the receiver named by the "LOGO" string.
 * Same one-call wrapper as beNDMWTitle2 and beFont slot 29. */
void Gap__Bec__beNDMWLogo__vfunc_29(beNDMWLogo *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &LOGO[0]);
}

int Gap__Bec__beNDMWLogo__vfunc_34(beNDMWLogo *arg0, beBaseInfoRam *arg1, void *arg2) {
    if (arg1->_dataList == 0) {
        return 1;
    }
    beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003c22e0(), *(int *)((char *)(arg2) + 20));
    return 1;
}

int Gap__Bec__beNDMWLogo__vfunc_20(void)
{
    return g_beNDMWLogo_metaObject[0];
}

