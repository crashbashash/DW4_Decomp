#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((void *)h_[0], (int)h_); }
#define POOL() if (!g_stringPool[0]) { int p_ = StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool[0] = p_; }

extern "C" void beNDMWStageCtl_Prepare(void);
extern "C" int beNDMWStageCtl_GetInfoMeta(void);
extern "C" int beNDMWStageCtl_GetMeta(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_SetFreezeTime(...);
extern "C" int strlen(const char *);
extern "C" void * igInsightCore_FindManager(...);
extern "C" int StringPool_Allocate(int);
extern "C" int igStringObj_Set(void *, int);
extern "C" int igStringObj_Insert(void *, const char *, int, int);
extern "C" int beNDMWStageCtlInfo_GetMessageEnum(void);
extern "C" void StringChunk_ReleaseHeader(void *, int);
extern "C" int StringPool_Construct(int);
extern "C" char *StringPool_Intern(int, int);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_ClearBool(int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_GetStringCount(int);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int strcmp(int, const void *);
extern "C" int g_beNDMWStageCtlInfo_metaObject[4];
extern "C" int g_beNDMWStageCtl_metaObject[4];
extern "C" void beNDMWStageCtl_OnAddRam(beNDMWStageCtl * p0, int p1, char * p2, int p3, int p4);
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" int g_bePadManager_metaObject[4];
/* matching construct: dummy-virtual classes so the window chain dispatches through retail vtable slots */
extern "C" void beNDMWStageCtl_UpdateRam(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram);
extern "C" int g_stringObjEmptyText[4];
extern "C" int g_stringPool[4];
struct Col { virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44(); virtual void e45(); virtual void e46(); virtual void e47(); virtual void e48(); virtual void e49(); virtual void e50(); virtual void e51(); virtual void e52(); virtual void e53(); virtual void e54(); virtual void e55(); virtual void e56(); virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60(); virtual void e61(); virtual void e62(); virtual void e63(); virtual void e64(); virtual void e65(); virtual void e66(); virtual void e67(); virtual void e68(); virtual void e69(); virtual void e70(); virtual void e71(); virtual void e72(); virtual void e73(); virtual void e74(); virtual void e75(); virtual void e76(); virtual void e77(); virtual void e78(); virtual void e79(); virtual void e80(); virtual void e81(); virtual void e82(); virtual void e83(); virtual void e84(); virtual void e85(); virtual void e86(); virtual void e87(); virtual void e88(); virtual void e89(); virtual void e90(); virtual void e91(); virtual void e92(); virtual void e93(); virtual void e94(); virtual void e95(); virtual void e96(); virtual void e97(); virtual void e98(); virtual void e99(); virtual void e100(); virtual void e101(); virtual void e102(); virtual void e103(); virtual void e104(); virtual void e105(); virtual void e106(); virtual void e107(); virtual void e108(); virtual void e109(); virtual void e110(); virtual void e111(); virtual void e112(); virtual void e113(); virtual void e114(); virtual void e115(); virtual void e116(); virtual void e117(); virtual void e118(); virtual void e119(); virtual void e120(); virtual void e121(); virtual void e122(); virtual void e123(); virtual void e124(); virtual void e125(); virtual void e126(); virtual void e127(); virtual void e128(); virtual void e129(); virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174(); virtual void e175(); virtual void setColor(int); };
struct Cam { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual Col *getCol(); };
extern "C" int beNDMWStageCtl_OnMessage(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram, beMessengerWork *message);

#pragma push
#pragma readonly_strings on

void beNDMWStageCtl_Prepare(void)
{
}

void beNDMWStageCtl_OnAddRam(beNDMWStageCtl * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, ("STAGECTL"), 0, -1);
}

int beNDMWStageCtl_GetInfoMeta(void)
{
    return g_beNDMWStageCtlInfo_metaObject[0];
}

void beNDMWStageCtl_UpdateRam(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram) {
    bePadData *pad;
    bool ok;
    switch (ram->_st0) {
    case 0:
        if (((beSystem *)self->_system)->_isSResetEnable == 0) return;
        pad = bePadManager_GetPadForPlayer(((int)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0])), 0);
        int a = pad->_trigger;
        int b = pad->_button;
        ok = (a & 8) != 0 && (b & 1) != 0;
        if (!ok) return;
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        return;
    case 1:
        if (((beSystem *)self->_system)->_isSResetEnable == 0) {
            ram->_st0 = 0;
            ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
            return;
        }
        beMessenger_SendGroup(self->_messenger, "SOUND", "BGMSTOP");
        beMessenger_SendGroup(self->_messenger, "SOUND", "ENVSTOP");
        beMessenger_SendGroup(self->_messenger, "SOUND", "SESTOP");
        beMessenger_SendGroup(self->_messenger, "SUBWND", "ISRUN");
        if (beMessenger_GetBool(self->_messenger, 0) & 0xFF) {
            beMessenger_SendGroup(self->_messenger, "SUBWND", "REMOVE");
            ((Cam *)((igInsightCore *)self->_insight)->_window)->getCol()->setColor(0xFF000000);
            beMessenger_SelectGroup(self->_messenger, "LAYERCTL");
            beMessenger_AppendString(self->_messenger, "ALL");
            beMessenger_AppendString(self->_messenger, "DISPOFF");
            beMessenger_DispatchSelected(self->_messenger, "SWITCH");
        }
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        return;
    case 2:
        beMessenger_SendGroup(self->_messenger, "SUBWND", "ISRUN");
        if (beMessenger_GetBool(self->_messenger, 0) & 0xFF) return;
        beMessenger_SelectGroup(self->_messenger, "LAYERCTL");
        beMessenger_AppendString(self->_messenger, "ALL");
        beMessenger_AppendString(self->_messenger, "DISPOFF");
        beMessenger_DispatchSelected(self->_messenger, "SWITCH");
        beMessenger_SendGroup(self->_messenger, "MODELCTRL", "ONFREEZE");
        beMessenger_SendGroup(self->_messenger, "GENERATER", "ONFREEZE");
        beMessenger_SetFreezeTime(self->_messenger, 1);
    case 3:
    case 4:
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        return;
    case 5:
        beMessenger_SelectGroup(self->_messenger, "STAGECTL");
        beMessenger_AppendString(self->_messenger, "stagis10");
        beMessenger_DispatchSelected(self->_messenger, "NEXTSTAGE");
        break;
    }
}

int beNDMWStageCtl_OnMessage(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram, beMessengerWork *message) {
    switch (beMessenger_ResolveEnumValue(self->_messenger, beNDMWStageCtlInfo_GetMessageEnum(), message->_message)) {
    case 0: {
        igSmartPointer<igStringObj> stageName((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
        igStringObj_Set(stageName.p, beMessenger_GetString(self->_messenger, 0));
        void *t = stageName.p;
        int length = ((igStringObj *)t)->_length;
        igStringObj_Insert(t, ".igb", length, strlen(".igb"));
        ((Cam *)((igInsightCore *)self->_insight)->_window)->getCol()->setColor(0xFF000000);
        beMessenger_SendGroup(self->_messenger, "SOUND", "SESTOP");
        beMessenger_SendGroup(self->_messenger, "SOUND", "ENVSTOP");
        int text = (stageName.p->_buffer == 0) ? g_stringObjEmptyText[0] : stageName.p->_buffer;
        beSystem *system = (beSystem *)self->_system;
        POOL();
        char *interned = (char *)StringPool_Intern(g_stringPool[0], text);
        STR_RELEASE(system->_nextStage);
        system->_nextStage = (int)interned;
        ((beSystem *)self->_system)->_isStageLoop = 0;
        return 1;
    }
    case 1:
        if (beMessenger_GetStringCount(self->_messenger) > 0) {
            int command = beMessenger_GetString(self->_messenger, 0);
            bePadManager *padManager = (bePadManager *)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
            if (strcmp(command, "ENABLE") == 0) {
                padManager->_isPadDisable = 0;
            } else if (strcmp(command, "DISABLE") == 0) {
                padManager->_isPadDisable = 1;
            } else if (strcmp(command, "STATUS") == 0) {
                beMessenger_ClearBool(self->_messenger);
                beMessenger_AppendBool(self->_messenger, padManager->_isPadDisable);
            }
        }
        return 1;
    case 2:
        beMessenger_AppendBool(self->_messenger, ram->_st0 != 0);
        return 1;
    default:
        return 0;
    }
}

int beNDMWStageCtl_GetMeta(void)
{
    return g_beNDMWStageCtl_metaObject[0];
}

#pragma pop
