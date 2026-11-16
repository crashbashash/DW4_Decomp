#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igWindowDispatchView.h"
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
extern "C" void beNDMWStageCtl_UpdateRam(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram);
extern "C" int g_stringObjEmptyText[4];
extern "C" int g_stringPool[4];
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
            ((igWindowDispatchView *)((igInsightCore *)self->_insight)->_window)->getVisualContext()->setClearColor(0xFF000000);
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
        ((igWindowDispatchView *)((igInsightCore *)self->_insight)->_window)->getVisualContext()->setClearColor(0xFF000000);
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
