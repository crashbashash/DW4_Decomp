#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/windowinput/igWindowDispatchView.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWStageCtl.h"
#include "dw4/game/ndmw/beNDMWStageCtlInfo.h"
#include "dw4/game/bePadManager.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igStringObj.h"
#include <string.h>
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((StringChunk *)h_[0], (StringTokenHeader *)h_); }
#define POOL() if (!g_stringPool) { StringPool *p_ = (StringPool *)StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool = p_; }

extern "C" void beNDMWStageCtl_Prepare(void);
extern "C" int beNDMWStageCtl_GetInfoMeta(void);
extern "C" int beNDMWStageCtl_GetMeta(void);
extern "C" void beNDMWStageCtl_OnAddRam(beNDMWStageCtl * p0, int p1, char * p2, int p3, int p4);
extern "C" void beNDMWStageCtl_UpdateRam(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram);
extern "C" int beNDMWStageCtl_OnMessage(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram, beMessengerWork *message);

#pragma push
#pragma readonly_strings on

void beNDMWStageCtl_Prepare(void)
{
}

void beNDMWStageCtl_OnAddRam(beNDMWStageCtl * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, ("STAGECTL"), 0, -1);
}

int beNDMWStageCtl_GetInfoMeta(void)
{
    return (int)g_beNDMWStageCtlInfo_metaObject;
}

void beNDMWStageCtl_UpdateRam(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram) {
    bePadData *pad;
    bool ok;
    switch (ram->_st0) {
    case 0: {
        if (((beSystem *)self->_system)->_isSResetEnable == 0) return;
        pad = bePadManager_GetPadForPlayer((bePadManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject), 0);
        int a = pad->_trigger;
        int b = pad->_button;
        ok = (a & 8) != 0 && (b & 1) != 0;
        if (!ok) return;
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        return;
    }
    case 1:
        if (((beSystem *)self->_system)->_isSResetEnable == 0) {
            ram->_st0 = 0;
            ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
            return;
        }
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "BGMSTOP");
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "ENVSTOP");
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "SESTOP");
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SUBWND", "ISRUN");
        if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) != 0) {
            beMessenger_SendGroup((beMessenger *)self->_messenger, "SUBWND", "REMOVE");
            ((igWindowDispatchView *)((igInsightCore *)self->_insight)->_window)->getVisualContext()->setClearColor(0xFF000000);
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "ALL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "DISPOFF");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
        }
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        return;
    case 2:
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SUBWND", "ISRUN");
        if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) != 0) return;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "ALL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "DISPOFF");
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
        beMessenger_SendGroup((beMessenger *)self->_messenger, "MODELCTRL", "ONFREEZE");
        beMessenger_SendGroup((beMessenger *)self->_messenger, "GENERATER", "ONFREEZE");
        beMessenger_SetFreezeTime((beMessenger *)self->_messenger, 1);
    case 3:
    case 4:
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0; ram->_st2 = 0; ram->_st1 = 0;
        return;
    case 5:
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "STAGECTL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "stagis10");
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "NEXTSTAGE");
        break;
    }
}

int beNDMWStageCtl_OnMessage(beNDMWStageCtl *self, beNDMWStageCtlInfoRam *ram, beMessengerWork *message) {
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beNDMWStageCtlInfo_GetMessageEnum(), (const char *)message->_message)) {
    case 0: {
        igSmartPointer<igStringObj> stageName((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
        igStringObj_Set(stageName.p, beMessenger_GetString((beMessenger *)self->_messenger, 0));
        void *t = stageName.p;
        int length = ((igStringObj *)t)->_length;
        igStringObj_Insert((igStringObj *)t, (char *)".igb", length, strlen(".igb"));
        ((igWindowDispatchView *)((igInsightCore *)self->_insight)->_window)->getVisualContext()->setClearColor(0xFF000000);
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "SESTOP");
        beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "ENVSTOP");
        const char *text = (stageName.p->_buffer == 0) ? g_stringObjEmptyText : (const char *)stageName.p->_buffer;
        beSystem *system = (beSystem *)self->_system;
        POOL();
        char *interned = StringPool_Intern(g_stringPool, text);
        STR_RELEASE(system->_nextStage);
        system->_nextStage = (int)interned;
        ((beSystem *)self->_system)->_isStageLoop = 0;
        return 1;
    }
    case 1:
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) > 0) {
            const char *command = beMessenger_GetString((beMessenger *)self->_messenger, 0);
            bePadManager *padManager = (bePadManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
            if (strcmp(command, "ENABLE") == 0) {
                padManager->_isPadDisable = 0;
            } else if (strcmp(command, "DISABLE") == 0) {
                padManager->_isPadDisable = 1;
            } else if (strcmp(command, "STATUS") == 0) {
                beMessenger_ClearBool((beMessenger *)self->_messenger);
                beMessenger_AppendBool((beMessenger *)self->_messenger, padManager->_isPadDisable);
            }
        }
        return 1;
    case 2:
        beMessenger_AppendBool((beMessenger *)self->_messenger, ram->_st0 != 0);
        return 1;
    default:
        return 0;
    }
}

int beNDMWStageCtl_GetMeta(void)
{
    return (int)g_beNDMWStageCtl_metaObject;
}

#pragma pop
