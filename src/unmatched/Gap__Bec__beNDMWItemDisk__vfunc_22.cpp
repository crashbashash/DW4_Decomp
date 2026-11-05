#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
int beLua__RunNamedChunk(...);
int FUN_003f9c80(...);
int FUN_003f9e20(...);
int FUN_00447b00(...);
int FUN_00447b40(...);
int SYSsetGateStage(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
void *beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beNDMWItemBase_GetRecordInt(...);
extern int DAT_0051d5a8[4];
extern int DAT_0051d5b0[4];
extern int DAT_0051d5b8[4];
extern int DAT_0051d5c0[4];
extern int DAT_0051d5d0[4];
extern int DAT_0051d5d8[4];
extern int DAT_0051d5e8[4];
extern int DAT_0051d5f8[4];
extern int DAT_0051d600[4];
extern int DAT_00589208[4];
extern int DAT_0058c0a0[4];
int Gap__Bec__beNDMWItemDisk__vfunc_22(beNDMWItemDisk *arg0, beNDMWGameRam *arg1, int arg2);
}
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
int Gap__Bec__beNDMWItemDisk__vfunc_22(beNDMWItemDisk *arg0, beNDMWGameRam *arg1, int arg2) {
    int v = arg0->_recNo;
    switch (v) {
    case 9: {
        int s3 = FUN_00236f80(arg1->_insight, DAT_0058c0a0[0]);
        FUN_003f9c80(s3, arg2, beNDMWItemBase_GetRecordInt(arg0, arg1, &DAT_0051d5a8[0]), -1);
        FUN_003f9e20(s3, arg2, beNDMWItemBase_GetRecordInt(arg0, arg1, &DAT_0051d5b0[0]));
        return 0;
    }
    }
    switch (v) {
    case 0: case 1: case 2: {
        int r = beNDMWItemBase_GetRecordInt(arg0, arg1, &DAT_0051d5a8[0]);
        FUN_003f9c80(FUN_00236f80(arg1->_insight, DAT_0058c0a0[0]), arg2, r, -1);
        return 0;
    }
    }
    switch (v) {
    case 3: case 4: case 5: {
        int r = beNDMWItemBase_GetRecordInt(arg0, arg1, &DAT_0051d5b0[0]);
        FUN_003f9e20(FUN_00236f80(arg1->_insight, DAT_0058c0a0[0]), arg2, r);
        return 0;
    }
    }
    switch (v) {
    case 6: {
        int s0 = arg1->_messenger;
        beMessenger_SendNamed(s0, &DAT_0051d5b8[0], 0, arg2, &DAT_0051d5c0[0]);
        void *t1 = beMessenger_GetObject(s0, 0);
        beNDMWMdlPEBaseInfoWork *t0 = (beNDMWMdlPEBaseInfoWork *)beMessenger_GetObject(s0, 1);
        if (FUN_00447b00(t0) != 0) {
            int a1 = t0->_poisonEndurance;
            DW4VC_96_1 *a0 = (DW4VC_96_1 *)(*(int *)((char *)(arg1->_system) + 48));
            if ((8 - a1) >= (int)(a0->vX(a1) % 10U)) {
                FUN_00447b40(t0, t1);
            }
        }
        return 0;
    }
    case 7: {
        int s1 = arg1->_messenger;
        beMessenger_SelectGroup(s1, &DAT_0051d5d0[0]);
        beMessenger_AppendString(s1, &DAT_0051d5d8[0]);
        beMessenger_AppendInt(s1, arg2);
        beMessenger_AppendInt(s1, arg2);
        beMessenger_AppendInt(s1, -0x32);
        beMessenger_DispatchSelected(s1, &DAT_0051d5e8[0]);
        return 0;
    }
    case 8: {
        int s1 = FUN_00236f80(arg1->_insight, DAT_00589208[0]);
        SYSsetGateStage(&DAT_0051d5f8[0], arg2);
        beLua__RunNamedChunk(s1, &DAT_0051d600[0], 0);
        return 1;
    }
    }
    return 0;
}
