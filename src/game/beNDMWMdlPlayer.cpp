#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beBaseInfoManagerDispatchView.h"
#include "dw4/game/ndmw/listSet.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beBaseInfoRam.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlHITBOX.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/game/beModelCtrlSubCom.h"
#include "dw4/game/ndmw/beNDMWGameRam.h"
#include "dw4/game/ndmw/beNDMWMdlPEBase.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer2InfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlPlayerInfoWork.h"
#include "dw4/game/bePadManager.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igResult.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/support/softfloat.h"
#include <stdio.h>
#include <string.h>
#include "dw4/game/beDBManager.h"
#include <math.h>
#include "dw4/support/emptyString.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igMetaEnum.h"

/* beNDMWMdlPlayer: the model controller of the player's Digimon. It overrides the beModelCtrl
 * slots that resolve its managers, register it as a PLAYER receiver, drive the pad (turn attacks,
 * guard, the panel and lobby buttons), wait for a combo step to finish, create the player's info
 * work on GENERATE and close the status panel when control, freeze, erase or remove arrive. */

/* kept local: no include/dw4 home declares it yet. */


#pragma push
#pragma readonly_strings on

/* Turn attacks: the stick direction (1..15) picks one of eight timers, -1 for none. */
extern "C" {
int g_stickTurnAttackSlot[16] = {-1, 0, 2, 1, 4, -1, 3, -1, 6, 7, -1, -1, 5, -1, -1, -1};
int g_turnAttackTimerStart = 30;
/* "SQ_DLTM01".."SQ_DLTM13": the status panel's attack-delay sequence, by ATTACKDELAY level. */
const char *g_attackDelaySeqNames[13] = { "SQ_DLTM01", "SQ_DLTM02", "SQ_DLTM03", "SQ_DLTM04", "SQ_DLTM05", "SQ_DLTM06", "SQ_DLTM07", "SQ_DLTM08", "SQ_DLTM09", "SQ_DLTM10", "SQ_DLTM11", "SQ_DLTM12", "SQ_DLTM13" };
}
extern "C" {
/* The default names of players 1 to 4. */
const char *g_defaultPlayerNames[4] = { "\202\242\202\277\202\353\202\244", "\202\266\202\353\202\244", "\202\263\202\324\202\353\202\244", "\202\265\202\353\202\244" };
/* Dungeon stages on which the player is told SETMETAL. */
const char *g_metalStageNames[5] = { "dng204b1", "dng204b2", "dng205b1", "dng205b2", "dng205b3" };
const char *g_mainLobbyStageNames[4] = { "stagML02", "stagML11", "stagML12", "stagML13" };
/* "SQ_ENTR1P".."SQ_ENTR4P". */
const char *g_playerEntrySeqNames[4] = { "SQ_ENTR1P", "SQ_ENTR2P", "SQ_ENTR3P", "SQ_ENTR4P" };
unsigned char g_baseIsUseInitial = 1;
}



extern "C" void beNDMWMdlPlayer_Start(beNDMWMdlPlayer *self);
extern "C" unsigned char beNDMWMdlPlayer_IsKind(int self, int kind);
extern "C" void beNDMWMdlPlayer_RegisterReceiver(beNDMWMdlPlayer *self, int info, char *unused);
extern "C" void beNDMWMdlPlayer_UpdateControl(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnWaitCheck(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnGenerate(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnControlOff(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnFreeze(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnSequenceChange(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnErase(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" void beNDMWMdlPlayer_OnRemove(beNDMWMdlPlayer *self, beBaseInfoRam *ram);
extern "C" int beNDMWMdlPlayer__GetMeta(void);

/* Intern `text` through the global string pool and make it the work's key event name. */
#define SET_KEY_EVENT(work, text) { \
    const char *tok_; \
    int *old_; \
    if (((void *)g_stringPool) == 0) { \
        void *pool_ = StringPool_Allocate(0x10); \
        if (pool_ != 0) pool_ = StringPool_Construct((StringPool *)pool_); \
        ((void *)g_stringPool) = pool_; \
    } \
    tok_ = StringPool_Intern((StringPool *)g_stringPool, (text)); \
    old_ = (int *)(work)->_keyEventName; \
    if (old_ != 0) { \
        int *hdr_ = old_ - 2; \
        int n_ = old_[-1] - 1; \
        old_[-1] = n_; \
        if (n_ == 0) StringChunk_ReleaseHeader((StringChunk *)*hdr_, (StringTokenHeader *)hdr_); \
    } \
    (work)->_keyEventName = (int)tok_; }

/* Ask this player's panel to open `request` for the work; a reply marks the panel open. */
#define OPEN_PANEL(messenger, ram, work, request) { \
    beMessenger_SelectReceivers((beMessenger *)((messenger)), "NDMWPANEL", 0, (ram)->_ramNo); \
    beMessenger_AppendObject((beMessenger *)((messenger)), (igObject *)((work))); \
    beMessenger_DispatchSelected((beMessenger *)((messenger)), (request)); \
    if (beMessenger_GetBoolCount((beMessenger *)((messenger))) != 0) (work)->_isPanel = 1; }

static inline void ReleaseObject(igObject *object) {
    igObject::release(object);
}

/* Owning stack reference to the hit box the main lobby builds on the 0x4000 button. */
struct HitBoxRef {
    beModelCtrlHITBOX *p;
    HitBoxRef(beModelCtrlHITBOX *x) { p = x; }
    ~HitBoxRef() { igObject *o = (igObject *)p; igObject::release(o); }
};
/* Owning stack reference to the new player info work. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; igObject::release(o); }
};
/* Owning stack reference to the new turn-attack timer list. */
class IntListRef {
public:
    igIntList *p;
    IntListRef(igIntList *l) : p(l) {}
    ~IntListRef() { igIntList *o = p; igObject::release(o); }
};

/* matching construct: slot order. The data list's holder is a local of this static inline member, allocated below
 * the caller's locals, so `list` (244) sits under the discarded igResult of igMatrix44f_Invert (248) and the caller's
 * HitBoxRef (252). */
struct Locals {
    static inline void CreateDataList(beBaseInfoRam *ram) {
        void *alloc;
        alloc = ((void *)((Gap::Core::igObject *)ram)->getMemoryPool());
        alloc = g_useOwnerAllocator ? alloc : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)alloc));
            (igSmartPointer<igObject> &)ram->_dataList = list;
        }
    }
};
/* matching construct: the new list is held in this inline's own scope, which puts it in the stack slot below
 * the caller's named references (retail's +0x100); written in place, its frame slot and unwind entry differ */
struct Slot { static inline void adopt(beBaseInfoRam *ram, igObject *created) { igSmartPointer<igObject> list(created); (igSmartPointer<igObject> &)ram->_dataList = list; }
};

void beNDMWMdlPlayer_Start(beNDMWMdlPlayer *self) {
    beBaseInfoManager_Start((beBaseInfoManager *)self);
    self->_gameRam = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWGameRam_metaObject);
    self->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
    self->_viewerSIManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
}

unsigned char beNDMWMdlPlayer_IsKind(int self, int kind) {
    return strcmp((const char *)kind, "KIND_PLAYER") == 0;
}

void beNDMWMdlPlayer_RegisterReceiver(beNDMWMdlPlayer *self, int info, char *unused)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, "PLAYER");
}

void beNDMWMdlPlayer_UpdateControl(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    beNDMWMdlPlayerInfoWork *work;
    bePadData *pad;
    float stickX, stickY;
    int stickDir;
    int pressed, held;
    unsigned char handled;
    bool turnTimersFull;
    int messenger;
    float cameraMatrix[18];
    float cameraForward[3];

    if (ram->_dataList == 0) Locals::CreateDataList(ram);
    work = (beNDMWMdlPlayerInfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE"))->_work;
    pad = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, ram->_ramNo);
    stickDir = pad->_lStk;
    stickX = pad->_LStick[0];
    stickY = pad->_LStick[1];
    turnTimersFull = 0;
    if (stickDir != 0) {
        int slot;
        igIntList *timers;
        int running;
        int i;
        timers = (igIntList *)work->_turnAtkTimer;
        slot = g_stickTurnAttackSlot[stickDir];
        if (slot != -1) {
            int count = timers->_count;
            if (count != 0 && slot >= 0 && slot < count) ((int *)timers->_data)[slot] = g_turnAttackTimerStart;
        }
        running = 0;
        for (i = 0; i < 8; i++) {
            int left = ((int *)timers->_data)[i];
            if (left > 0) {
                int next = left - 1;
                if (timers->_count != 0 && i >= 0 && i < timers->_count) ((int *)timers->_data)[i] = next;
                running++;
            }
        }
        if (running >= 8) turnTimersFull = 1;
        igMatrix44f_SetIdentity(cameraMatrix);
        igMatrix44f_Invert(cameraMatrix, (const float *)((int)&((igViewerParameters *)((igViewerSceneInfoManager *)self->_viewerSIManager)->_parameters)->_viewMatrix));
        Vec3f_TransformDirection(cameraForward, (float *)&g_vec3ZAxis, cameraMatrix);
        {
            float cameraYaw = atan2f(cameraForward[0], cameraForward[2]);
            *(float *)&work->_targetDirection[1] = cameraYaw + atan2f(stickX, -stickY);
        }
        work->_keyInput = 1;
    } else {
        work->_keyInput = 0;
    }
    pressed = pad->_trigger;
    held = pad->_button;
    if (work->_isMainLobby == 0) {
        if (strcmp((const char *)work->_seqCodeName, "SQ_JUMP") != 0 && (pressed & 0x8000)) {
            SET_KEY_EVENT(work, "SQ_GUARD")
        }
        if (held & 0x8000) {
            float t = work->_bodyAtkTimer;
            if (!(t <= 0.0f)) {
                float n = t - ((beSystem *)self->_system)->_frameTimeF;
                if (!(n < 0.0f)) work->_bodyAtkTimer = n;
                else work->_bodyAtkTimer = 0.0f;
            }
            switch (work->_bodyAtkSt0) {
            case 0:
                if (work->_keyInput == 0) work->_bodyAtkSt0 = 1;
                break;
            case 1:
                if (work->_keyInput == 1) {
                    work->_bodyAtkTimer = 15.0f;
                    work->_bodyAtkPad = stickDir;
                    work->_bodyAtkSt0 = 2;
                }
                break;
            case 2:
                if (work->_bodyAtkTimer == 0.0f) work->_bodyAtkSt0 = 0;
                else if (work->_keyInput == 0) work->_bodyAtkSt0 = 3;
                break;
            case 3:
                if (work->_bodyAtkTimer == 0.0f) {
                    work->_bodyAtkSt0 = 0;
                } else if (work->_keyInput != 0) {
                    if (stickDir == work->_bodyAtkPad && strcmp((const char *)work->_seqCodeName, "SQ_JUMP") != 0 && strcmp((const char *)work->_seqCodeName, "SQ_FALL") != 0) {
                        SET_KEY_EVENT(work, "SQ_ATCK3")
                        work->_ctrlSt0 = 0;
                        work->_ctrlSt1 = 0;
                    }
                    work->_bodyAtkSt0 = 0;
                }
                break;
            }
        } else {
            work->_bodyAtkSt0 = 0;
        }
    }
    if (strcmp((const char *)work->_seqCodeName, "SQ_JUMP") != 0 && strcmp((const char *)work->_seqCodeName, "SQ_FALL") != 0) {
        unsigned char panelOpen = work->_isPanel;
        if (panelOpen != 0) {
            handled = 0;
            beMessenger_SendNamed((beMessenger *)self->_messenger, "NDMWPANEL", 0, ram->_ramNo, "ISCHECK");
            messenger = self->_messenger;
            if (beMessenger_GetBoolCount((beMessenger *)messenger) == 0 || beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                work->_isPanel = 0;
            } else if (beMessenger_GetBool((beMessenger *)self->_messenger, 2)) {
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 1)) {
                    SET_KEY_EVENT(work, "SQ_ITEM")
                } else {
                    beModelCtrlInfoWork_SetSeqLabel((beModelCtrl *)self, ram, (beModelCtrlInfoWork *)work, "SQ_WAZA", beMessenger_GetString((beMessenger *)self->_messenger, 0));
                    SET_KEY_EVENT(work, "SQ_WAZA")
                }
                handled = 1;
            }
            if (!(handled & 0xFF)) {
                if (pressed & 0x2000) {
                    SET_KEY_EVENT(work, "SQ_JUMP")
                    return;
                }
                if (pressed & 0x1000) {
                    OPEN_PANEL(self->_messenger, ram, work, "GENEEMGHEAL")
                } else if (work->_keyInput == 0 && !(held & ~8) && (pressed & 8)) {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "SOUND");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "CURSOR_NG");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "PLAY");
                }
            }
        } else {
            if (pressed & 0x2000) {
                SET_KEY_EVENT(work, "SQ_JUMP")
                return;
            }
            if (pressed & 0x1000) {
                OPEN_PANEL(self->_messenger, ram, work, "GENEEMGHEAL")
            } else if ((pressed & 0x400) && !(panelOpen & 0xFF)) {
                OPEN_PANEL(self->_messenger, ram, work, "GENERATEITEM")
            } else if ((pressed & 0x800) && !(panelOpen & 0xFF)) {
                OPEN_PANEL(self->_messenger, ram, work, "GENERATEWAZA")
            } else if ((pressed & 0x200) && !(panelOpen & 0xFF)) {
                OPEN_PANEL(self->_messenger, ram, work, "GENERATESTAT")
            } else if (pressed & 0x4000) {
                if (work->_isMainLobby != 0) {
                    beModelCtrlHITBOX *box;
                    void *alloc = ((void *)((Gap::Core::igObject *)self)->getMemoryPool());
                    alloc = g_useOwnerAllocator ? alloc : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
                    {
                        HitBoxRef hitBox((beModelCtrlHITBOX *)beModelCtrlHITBOX_Create((int)alloc));
                        igNamedObject_SetName((igNamedObject *)(void *)hitBox.p, "Set");
                        hitBox.p->_kind = 60000;
                        hitBox.p->_start = 1.0f;
                        hitBox.p->_length = 1.0f;
                        box = hitBox.p;
                        box->_offset[0] = 0.0f;
                        box->_offset[1] = 4.0f;
                        box->_offset[2] = 7.0f;
                        box = hitBox.p;
                        box->_boxSize[0] = 3.0f;
                        box->_boxSize[1] = 3.0f;
                        box->_boxSize[2] = 3.0f;
                        beModelCtrlSubCom_AddHitBox((beModelCtrlSubCom *)work->_subCommand, (beModelCtrlHITBOX *)(void *)hitBox.p);
                    }
                } else {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "DROPITEM");
                    beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
                    beMessenger_SetRunCheck((beMessenger *)self->_messenger, 1);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ACTION1");
                    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) == 0 && beBaseInfoRam_IsTimerExpired(ram, "ATDELAY")) {
                        int delay;
                        int delayStep;
                        if (turnTimersFull) {
                            igIntList *timers;
                            SET_KEY_EVENT(work, "SQ_ATCK2")
                            timers = (igIntList *)work->_turnAtkTimer;
                            if (timers->_count != 0) memset((void *)timers->_data, 0, timers->_count * 4);
                        } else {
                            SET_KEY_EVENT(work, "SQ_ATCK1")
                        }
                        delay = igProperty_GetRecord((igObject *)((int *)((igIntList *)((beNDMWGameRam *)self->_gameRam)->_playerDataListList)->_data)[ram->_ramNo], "ATTACKDELAY")->_data;
                        beBaseInfoRam_StartTimer(ram, "ATDELAY", __divdi3((long long)delay * 1000000000, 60));
                        delayStep = (delay - 22) / 4;
                        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_stpnl05", ram->_ramNo, (const char *)(void *)g_attackDelaySeqNames[delayStep]);
                    }
                }
            } else if (work->_keyInput == 0 && !(held & ~8) && (pressed & 8)) {
                beMessenger_SendNamed((beMessenger *)self->_messenger, "NDMWPANEL", 0, -1, "ISRUN");
                if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0 && beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "SOUND");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "CURSOR_NG");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "PLAY");
                    return;
                }
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, "SUBWND", 0, 0);
                beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, "STATUS");
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
            }
        }
    }
}

/* Finish the pending wait check: clear the work's wait-check name to the pool's empty token. */
static inline void ClearWaitCheck(beNDMWMdlPlayerInfoWork *work) {
    int *token;
    int *old;
    if (g_stringPool == 0) {
        int pool = ((int)StringPool_Allocate(16));
        if (pool != 0) pool = ((int)StringPool_Construct((StringPool *)pool));
        g_stringPool = (StringPool *)pool;
    }
    token = ((int *)StringPool_Intern(g_stringPool, 0));
    old = (int *)work->_wCheckName;
    if (old != 0) {
        int *hdr = old - 2;
        int refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*hdr, (StringTokenHeader *)hdr);
    }
    work->_wCheckName = (int)token;
}

void beNDMWMdlPlayer_OnWaitCheck(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    beBaseInfo *info;
    beNDMWMdlPlayerInfoWork *work;
    int held;
    int *infoName;
    int ramNo;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int owner = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        created = list.p;
        igObject::ref(created);
        ReleaseObject((igObject *)ram->_dataList);
        ram->_dataList = (int)created;
    }
    work = (beNDMWMdlPlayerInfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE"))->_work;
    held = 0;
    if (work->_isOnCtrl != 0) {
        held = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, ram->_ramNo)->_button;
    }
    if (strcmp((const char *)work->_wCheckName, "Atck01") == 0) {
        switch (work->_wCheckSt) {
        case 0:
            work->_wCheckMode = 0;
            work->_wCheckSt = 1;
        case 1:
            if (!(held & 0x4000)) {
                work->_wCheckMode = 1;
            }
            infoName = (int *)info->_name;
            ramNo = ram->_ramNo;
            infoName = infoName ? infoName : (int *)emptyString;
            beMessenger_SendNamed((beMessenger *)self->_messenger, "ACTION", (const char *)infoName, ramNo, "ISCOMEND");
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
                ClearWaitCheck(work);
                work->_wCheckSt = 0;
                if (work->_wCheckMode == 0) {
                    beModelCtrl_RunCommands((beModelCtrl *)self, (beModelCtrlInfo *)info, ram, (beModelCtrlInfoWork *)work);
                    return;
                }
                ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, "SQ_WAIT");
                return;
            }
            break;
        }
    } else if (strcmp((const char *)work->_wCheckName, "Atck02") == 0) {
        if (!(held & 0x4000)) {
            ((beBaseInfoManagerDispatchView *)self)->OnMessageText(ram, "SQ_WAIT");
        }
        infoName = (int *)info->_name;
        ramNo = ram->_ramNo;
        infoName = infoName ? infoName : (int *)emptyString;
        beMessenger_SendNamed((beMessenger *)self->_messenger, "ACTION", (const char *)infoName, ramNo, "ISCOMEND");
        if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
            ClearWaitCheck(work);
            beModelCtrl_RunCommands((beModelCtrl *)self, (beModelCtrlInfo *)info, ram, (beModelCtrlInfoWork *)work);
        }
    } else if (strcmp((const char *)work->_wCheckName, "Atck03") == 0 && !(held & 0x4000)) {
        ClearWaitCheck(work);
        beModelCtrl_RunCommands((beModelCtrl *)self, (beModelCtrlInfo *)info, ram, (beModelCtrlInfoWork *)work);
    }
}

void beNDMWMdlPlayer_OnGenerate(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    float startMatrix[16];
    float pointMatrix[16];
    beBaseInfo *info;
    beModelCtrlInfoRamData *record;
    beNDMWMdlPlayerInfoWork *work;
    igObject *created;
    igIntList *timers;
    info = (beBaseInfo *)ram->_parentInfo;
    if (ram->_dataList == 0) {
        int owner = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        Slot::adopt(ram, beBaseInfoDataList_Create(alloc));
    }
    record = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    {
        int owner = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        InfoWorkRef newWork(beNDMWMdlPlayerInfoWork_Create(alloc));
        created = newWork.p;
        igObject::ref(created);
        ReleaseObject((igObject *)record->_work);
        record->_work = (int)created;
        work = (beNDMWMdlPlayerInfoWork *)newWork.p;
        work->_isPlayer = 1;
        work->_directionLimiter[0] = 0.0f;
        work->_directionLimiter[1] = 7.0f;
        work->_directionLimiter[2] = 0.0f;
        {
            int owner = (int)((Gap::Core::igObject *)self)->getMemoryPool();
            int alloc;
            if (g_useOwnerAllocator != 0) {
                alloc = owner;
            } else {
                alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
            }
            IntListRef newTimers(igIntList_Create(alloc));
            {
                igIntList *t = newTimers.p;
                if (t->_count < 9) {
                    ((Gap::Core::igDataList *)t)->setCapacity(8, 4);
                }
            }
            {
                igIntList *t = newTimers.p;
                if (t->_capacity >= 8) {
                    t->_count = 8;
                } else {
                    ((Gap::Core::igDataList *)t)->resizeAndSetCount(8, 4);
                }
            }
            timers = newTimers.p;
            if (timers->_count != 0) {
                memset((void *)timers->_data, 0, timers->_count * 4);
            }
            timers = newTimers.p;
            igObject::ref(timers);
            ReleaseObject((igObject *)work->_turnAtkTimer);
            work->_turnAtkTimer = (int)timers;
        }
    }
    if (beMessenger_GetVec3Count((beMessenger *)self->_messenger) == 0 && beMessenger_GetMatrixCount((beMessenger *)self->_messenger) == 0) {
        igMatrix44f_SetIdentity(startMatrix);
        beMessenger_PushArgContext((beMessenger *)self->_messenger);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "PLAYERPOINT");
        beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
        beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETMATRIX");
        if (beMessenger_GetMatrixCount((beMessenger *)self->_messenger) != 0) {
            beMessenger_GetMatrix(pointMatrix, (beMessenger *)self->_messenger, 0);
            igMatrix44f_Copy(startMatrix, pointMatrix);
        }
        beMessenger_PopArgContext((beMessenger *)self->_messenger);
        beMessenger_AppendMatrix((beMessenger *)self->_messenger, startMatrix);
    }
    beModelCtrl__OnGenerate((beModelCtrl *)self, ram);
    beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
    beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
    int player = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
    {
        beDataObjInt *hp = igProperty_GetRecord((igObject *)player, "HP");
        if (hp != 0) ((igObject *)hp)->_refCount++;
        ReleaseObject((igObject *)work->_hp);
        work->_hp = (int)hp;
    }
    {
        beDataObjInt *maxHp = igProperty_GetRecord((igObject *)player, "MHP");
        if (maxHp != 0) ((igObject *)maxHp)->_refCount++;
        ReleaseObject((igObject *)work->_mHp);
        work->_mHp = (int)maxHp;
    }
    if (((beDataObjInt *)work->_hp)->_data == 0) {
        int full = igProperty_GetRecord((igObject *)player, "MHP")->_data;
        igProperty_GetRecord((igObject *)player, "HP")->_data = full;
        full = igProperty_GetRecord((igObject *)player, "MMP")->_data;
        igProperty_GetRecord((igObject *)player, "MP")->_data = full;
    }
    {
        int i = 0;
        do {
            ListSet(((igIntList *)igProperty_GetRecordIntList((igObject *)player, "UPDATA")->_data), i, 0);
            i += 1;
        } while (i < 7);
    }
    {
        int i = 0;
        do {
            ListSet(((igIntList *)igProperty_GetRecordIntList((igObject *)player, "DOWNDATA")->_data), i, 0);
            i += 1;
        } while (i < 6);
    }
    if (igProperty_GetRecordByte((igObject *)player, "ISUSE")->_data == 0) {
        int *infoName;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
        beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
        infoName = (int *)info->_name;
        infoName = infoName ? infoName : (int *)emptyString;
        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)infoName);
        beMessenger_AppendString((beMessenger *)self->_messenger, g_defaultPlayerNames[ram->_ramNo]);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GAMESTART");
        igUnsignedCharList *baseUse = ((igUnsignedCharList *)igProperty_GetRecordArray((igObject *)player, "BASE_ISUSE")->_data);
        int n = baseUse->_count;
        unsigned char *flags = (unsigned char *)baseUse->_data;
        for (int i = 0; i < n; i++) {
            flags[i] = g_baseIsUseInitial;
        }
    }
    if (((igStringRefList *)igProperty_GetRecordStringList((igObject *)player, "POWERSOCKETNAME")->_data)->_count != 0) {
        igStringRef socket = StringList_CopyRetained((igStringRefList *)igProperty_GetRecordStringList((igObject *)player, "POWERSOCKETNAME")->_data, 0);
        beMessenger_SendDelayedNamed((beMessenger *)self->_messenger, "PLAYERARMS", socket.p, ram->_ramNo, "GENERATE", 1);
    }
    beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
    beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "RECALCPLAYER");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "NUMBERCTRL", "lvnm", ram->_ramNo);
    beMessenger_AppendInt((beMessenger *)self->_messenger, igProperty_GetRecord((igObject *)player, "LEVEL")->_data);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETVALUE");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "METERCTRL", "hpmt", ram->_ramNo);
    {
        int maxHp = igProperty_GetRecord((igObject *)player, "MHP")->_data;
        beMessenger_AppendFloat((beMessenger *)self->_messenger, (100.0f * (float)igProperty_GetRecord((igObject *)player, "HP")->_data) / (float)maxHp);
    }
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETPERCENT");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "NUMBERCTRL", "hpnm", ram->_ramNo);
    beMessenger_AppendInt((beMessenger *)self->_messenger, igProperty_GetRecord((igObject *)player, "HP")->_data);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETVALUE");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "METERCTRL", "mpmt", ram->_ramNo);
    {
        int mp = igProperty_GetRecord((igObject *)player, "MP")->_data;
        beDataObjInt *maxMp = igProperty_GetRecord((igObject *)player, "MMP");
        beMessenger_AppendFloat((beMessenger *)self->_messenger, (float)(mp * 100 / maxMp->_data));
    }
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETPERCENT");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "NUMBERCTRL", "mpnm", ram->_ramNo);
    beMessenger_AppendInt((beMessenger *)self->_messenger, igProperty_GetRecord((igObject *)player, "MP")->_data);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETVALUE");
    int stageName = ((beSystem *)self->_system)->_stageName;
    for (int j = 0; j < 5; j++) {
        if (strcmp((const char *)((int *)g_metalStageNames)[j], (const char *)stageName) == 0) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, (const char *)((int *)"PLAYER"), 0, ram->_ramNo, "SETMETAL");
            break;
        }
    }
    for (int k = 0; k < 4; k++) {
        if (strcmp((const char *)((int *)g_mainLobbyStageNames)[k], (const char *)stageName) == 0) {
            work->_isMainLobby = 1;
            break;
        }
    }
}

void beNDMWMdlPlayer_OnControlOff(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    beNDMWMdlPlayerInfoWork *work;

    if (ram->_dataList == 0) {
        int owner = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)(g_useOwnerAllocator != 0 ? owner : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1))));
        igObject *created = list.p;
        igObject::ref(created);
        igObject *old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)created;
    }
    work = (beNDMWMdlPlayerInfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE"))->_work;
    if (work->_isPanel != 0) {
        work->_isPanel = 0U;
        beMessenger_SendNamed((beMessenger *)self->_messenger, "NDMWPANEL", 0, ram->_ramNo, "REMOVE");
    }
}

void beNDMWMdlPlayer_OnFreeze(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    if (ram->_dataList == 0) {
        int owner = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int alloc;
        igObject *old;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        created = list.p;
        igObject::ref(created);
        old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)created;
    }
    beNDMWMdlPlayerInfoWork *work = (beNDMWMdlPlayerInfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE"))->_work;
    if (work->_isPanel != 0) {
        work->_isPanel = 0;
        beMessenger_SendNamed((beMessenger *)self->_messenger, "NDMWPANEL", 0, ram->_ramNo, "REMOVE");
    }
}

static inline void EnsureDataList(beBaseInfoRam *ram)
{
    if (ram->_dataList == 0) {
        void *owner = ((void *)((Gap::Core::igObject *)ram)->getMemoryPool());
        void *alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create((int)alloc));
        igObject *created = list.p;
        if (created) created->_refCount++;
        igObject *old = (igObject *)ram->_dataList;
        igObject::release(old);
        ram->_dataList = (int)created;
    }
}

void beNDMWMdlPlayer_OnSequenceChange(beNDMWMdlPlayer *self, beBaseInfoRam *ram)
{
    beNDMWMdlPlayerInfoWork *work;
    beBaseInfo *info = (beBaseInfo *)ram->_parentInfo;
    char seqName[24];
    int badgeOffset[3];
    int enumValue;
    EnsureDataList(ram);
    int list = ram->_dataList;
    work = (beNDMWMdlPlayerInfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)list)->search((Gap::Core::igStringMetaField *)g_propertyNameField, ("ONE")))->_work;
    if (strcmp((const char *)work->_seqCodeName, ("SQ_WAIT")) == 0) {
        const char *infoName = (const char *)info->_name;
        int ramNo = ram->_ramNo;
        const char *receiver = infoName ? infoName : ((char *)emptyString);
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, ("MODELCTRL"), receiver, ramNo);
        beMessenger_AppendString((beMessenger *)self->_messenger, "i_pcnumic");
        sprintf(seqName, "SQ_OPENP%d", ram->_ramNo);
        beMessenger_AppendString((beMessenger *)self->_messenger, seqName);
        beMessenger_AppendFloat((beMessenger *)self->_messenger, 480.0f);
        badgeOffset[0] = 0; badgeOffset[1] = 0x41200000; badgeOffset[2] = 0;
        beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)badgeOffset);
        beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETEFFECT");
    }
    if (work->_isPanel != 0) {
        if (((Gap::Core::igMetaEnum *)(PanelCloseSeqList_GetMetaEnum()))->getEnumValue((const char *)work->_seqCodeName, enumValue) == g_resultSuccess) {
            work->_isPanel = 0;
            beMessenger_SendNamed((beMessenger *)self->_messenger, ("NDMWPANEL"), 0, ram->_ramNo, ("REMOVE"));
        }
    }
    beNDMWMdlPEBase_OnSequenceChange((beNDMWMdlPEBase *)self, ram);
}

void beNDMWMdlPlayer_OnErase(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    beModelCtrlInfoRamData *record;
    beNDMWMdlPlayerInfoWork *work;
    if (ram->_dataList == 0) {
        int owner = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        {
            igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
            created = list.p;
            igObject::ref(created);
            ReleaseObject((igObject *)ram->_dataList);
            ram->_dataList = (int)created;
        }
    }
    record = (beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)ram->_dataList)->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE");
    work = (beNDMWMdlPlayerInfoWork *)record->_work;
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", "g_000bcaps", ram->_ramNo);
    beMessenger_AppendMatrix((beMessenger *)self->_messenger, (void *)(record->_node + 32));
    beMessenger_AppendString((beMessenger *)self->_messenger, g_playerEntrySeqNames[ram->_ramNo]);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "g_000bcaps", ram->_ramNo, "ISRUN");
    if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) != 0 && beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) {
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
        beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "BKCHIPBITEXP");
    }
    if (work->_isPanel != 0) {
        work->_isPanel = 0;
        beMessenger_SendNamed((beMessenger *)self->_messenger, "NDMWPANEL", 0, ram->_ramNo, "REMOVE");
    }
}

void beNDMWMdlPlayer_OnRemove(beNDMWMdlPlayer *self, beBaseInfoRam *ram) {
    igObject *created;
    if (((igObject *)ram->_dataList) == 0) {
        int owner = (int)((Gap::Core::igObject *)ram)->getMemoryPool();
        int alloc;
        if (g_useOwnerAllocator != 0) {
            alloc = owner;
        } else {
            alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        }
        igSmartPointer<igObject> list(beBaseInfoDataList_Create(alloc));
        created = list.p;
        igObject::ref(created);
        ReleaseObject(((igObject *)ram->_dataList));
        ram->_dataList = (int)created;
    }
    beNDMWMdlPlayerInfoWork *work = (beNDMWMdlPlayerInfoWork *)((beModelCtrlInfoRamData *)((Gap::Core::igObjectList *)((igObject *)ram->_dataList))->search((Gap::Core::igStringMetaField *)g_propertyNameField, "ONE"))->_work;
    if (work->_isPanel != 0) {
        work->_isPanel = 0;
        beMessenger_SendNamed((beMessenger *)self->_messenger, "NDMWPANEL", 0, ram->_ramNo, "REMOVE");
    }
}

int beNDMWMdlPlayer__GetMeta(void)
{
    return (int)g_beNDMWMdlPlayer_metaObject;
}

#pragma pop
