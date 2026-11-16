#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/be.h"
#include "dw4/beBaseInfoDataList.h"
#include "dw4/beLua.h"
#include "dw4/beMessenger.h"
#include "dw4/beNDMWLogo.h"
#include "dw4/beNDMWLogoCtrlData.h"
#include "dw4/beNDMWLogoInfo.h"
#include "dw4/beNDMWMcUtilCtrl.h"
#include "dw4/bePadManager.h"
#include "dw4/beSystem.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igNamedObject.h"
#include "dw4/igObject.h"

#pragma push
#pragma readonly_strings on


extern "C" void beNDMWLogo_Prepare(beNDMWLogo *self);
extern "C" void beNDMWLogo_UpdateRam(beNDMWLogo *self, beBaseInfoRam *infoRam);
extern "C" void beNDMWLogo_RunMessageScript(beNDMWLogo *self, int callNo);
extern "C" void beNDMWLogo_ClearMessageText(beNDMWLogo *self);
extern "C" int beNDMWLogo_GetInfoMeta(void);
extern "C" void beNDMWLogo_OnAddRam(beNDMWLogo *self, int info);
extern "C" int beNDMWLogo_OnMessage(beNDMWLogo *self, beBaseInfoRam *infoRam, beMessengerWork *message);
extern "C" int beNDMWLogo_GetMeta(void);

/* CTRL._st0: the boot-time memory-card check, the dialogue about a card it cannot use, the logo. */
enum LogoState { LogoStateCardCheck = 0, LogoStateCardError = 1, LogoStateRunLogo = 2, LogoStateDone = 3 };
/* CTRL._st1 under LogoStateCardCheck. */
enum CardCheckStep { CardCheckOpen = 0, CardCheckUse = 1, CardCheckFreeSize = 2, CardCheckClose = 100 };
/* CTRL._st1 under LogoStateCardError. The question's first answer (_select 0) goes on to the logo;
 * the other shows one more message and checks the cards again. */
enum CardErrorStep {
    CardErrorOpen = 0,
    CardErrorExplain = 1,
    CardErrorAcknowledge = 2,
    CardErrorAsk = 3,
    CardErrorCloseAsk = 4,
    CardErrorDecide = 5,
    CardErrorRetryOpen = 6,
    CardErrorRetryExplain = 7,
    CardErrorRetryAcknowledge = 8,
    CardErrorRetryClose = 9,
    CardErrorSkip = 10
};
/* beNDMWMcUtilCtrl request kinds, and the result of a request that succeeded. */
enum McRequest { McRequestFileFind = 1, McRequestUseCheck = 3, McRequestGetFreeSize = 6 };
enum { McResultOk = 2 };
/* Bits of a slot's card result. */
enum CardFlag { CardUnusable = 0x04, CardFull = 0x08, CardPresent = 0x80 };

#define ENTER_STATE(ctrl, state) { (ctrl)->_st0 = (state); (ctrl)->_st3 = 0; (ctrl)->_st2 = 0; (ctrl)->_st1 = 0; }
#define NEXT_STEP(ctrl) { (ctrl)->_st1 = (ctrl)->_st1 + 1; (ctrl)->_st3 = 0; (ctrl)->_st2 = 0; }
#define ENTER_STEP(ctrl, step) { (ctrl)->_st1 = (step); (ctrl)->_st3 = 0; (ctrl)->_st2 = 0; }
#define NEXT_PHASE(ctrl) { (ctrl)->_st2 = (ctrl)->_st2 + 1; (ctrl)->_st3 = 0; }
#define ENTER_PHASE(ctrl, phase) { (ctrl)->_st2 = (phase); (ctrl)->_st3 = 0; }

/* The owner's allocator, or the default selector's when owner allocation is off. */
#define PICK_ALLOCATOR(allocator, owner) { \
    allocator = igObject_GetAllocator(owner); \
    allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); }

/* The step read afresh: `_st1 = CurrentStep(ctrl) + 1` reloads the value the switch tested. */
static inline int CurrentStep(const beNDMWLogoCtrlData *ctrl) {
    return ctrl->_st1;
}

static inline beNDMWMcUtilCtrl *mcUtil(beNDMWLogo *self) {
    return (beNDMWMcUtilCtrl *)self->_mcUtilCtrl;
}

/* The five words at +72 (not reflected fields) are the card results of slots 0..4. */
static inline int &cardResult(beNDMWLogo *self, int slot) {
    return *(int *)&self->_pad72[slot * 4];
}

/* The card result of the slot being checked (_connect).
 * matching construct: hand trial — indexing from the array start puts the index first in the
 * address `addu`; cardResult's byte offset keeps the loops' pointer at `self`. */
static inline int &connectResult(beNDMWLogo *self) {
    return ((int *)self->_pad72)[self->_connect];
}

/* Stores `list` as the ram's data list, retaining it and releasing the old one. */
static inline void setDataList(beBaseInfoRam *ram, igObject *list) {
    if (list != 0) list->_refCount = list->_refCount + 1;
    igRelease((igObject *)ram->_dataList);
    ram->_dataList = (int)list;
}

/* Moves on to the next slot: back to phase 1, or to `doneStep` after the last one. */
static inline void nextSlot(beNDMWLogo *self, beNDMWLogoCtrlData *ctrl, int doneStep) {
    self->_connect = self->_connect + 1;
    if (self->_isMtap == 1) {
        if (self->_connect >= 5) {
            ENTER_STEP(ctrl, doneStep);
        } else {
            ENTER_PHASE(ctrl, 1);
        }
    } else if (self->_connect >= 2) {
        ENTER_STEP(ctrl, doneStep);
    } else {
        ENTER_PHASE(ctrl, 1);
    }
}

/* Picks the error to report: the first full card, else the first unusable one. */
static inline void findCardError(beNDMWLogo *self) {
    bool found = false;
    self->_errTarget = 2;
    self->_errType = -1;
    for (int kind = 0; kind < 2 && found == false; kind++) {
        for (int slot = 0; slot < 5 && found == false; slot++) {
            switch (kind) {
            case 0:
                if (cardResult(self, slot) & CardFull) {
                    self->_errType = CardFull;
                    found = true;
                    self->_errTarget = slot;
                }
                break;
            case 1:
                if (cardResult(self, slot) & CardUnusable) {
                    self->_errType = CardUnusable;
                    found = true;
                    self->_errTarget = slot;
                }
                break;
            }
        }
    }
}

/* Names slot `slot` of a multitap (five slots). */
static inline void showMultitapSlot(beNDMWLogo *self, int slot) {
    switch (slot) {
    case 0: beNDMWLogo_RunMessageScript(self, 91302); break;
    case 1: beNDMWLogo_RunMessageScript(self, 91306); break;
    case 2: beNDMWLogo_RunMessageScript(self, 91303); break;
    case 3: beNDMWLogo_RunMessageScript(self, 91304); break;
    case 4: beNDMWLogo_RunMessageScript(self, 91305); break;
    }
}

/* Names slot `slot` without a multitap (two slots). */
static inline void showSlot(beNDMWLogo *self, int slot) {
    switch (slot) {
    case 0: beNDMWLogo_RunMessageScript(self, 91300); break;
    case 1: beNDMWLogo_RunMessageScript(self, 91301); break;
    }
}

/* Names every slot whose card result has `flag`. */
static inline void showFlaggedSlots(beNDMWLogo *self, int flag) {
    if (self->_isMtap == 1) {
        for (int i = 0; i < 5; i++) {
            if (cardResult(self, i) & flag) {
                showMultitapSlot(self, i);
            }
        }
    } else {
        for (int i = 0; i < 2; i++) {
            if (cardResult(self, i) & flag) {
                showSlot(self, i);
            }
        }
    }
}

/* Names every slot. */
static inline void showAllSlots(beNDMWLogo *self) {
    if (self->_isMtap == 1) {
        for (int i = 0; i < 5; i++) {
            showMultitapSlot(self, i);
        }
    } else {
        for (int i = 0; i < 2; i++) {
            showSlot(self, i);
        }
    }
}

void beNDMWLogo_Prepare(beNDMWLogo *self) {
    if (self->_padManager == 0) {
        self->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
    }
    if (self->_system_ == 0) {
        self->_system_ = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject);
    }
}

/* Per-frame update. Each slot's card is checked for use, then for a save (FILEFIND); a second pass
 * asks the usable cards for room (GETFREESIZE). A save or room for one sets _isUseSave and goes on
 * to logo.lua; otherwise the first full or unusable card is reported and the player chooses to go
 * on without saving or to check again. The numbers given to beNDMWLogo_RunMessageScript are
 * txt_Tar.lua call numbers. */
void beNDMWLogo_UpdateRam(beNDMWLogo *self, beBaseInfoRam *infoRam) {
    igMemoryPoolView *allocator;
    beNDMWLogoCtrlData *ctrl;
    beNDMWMcUtilCtrl *util;

    if (infoRam->_dataList == 0) {
        PICK_ALLOCATOR(allocator, self);
        igSmartPointer<igObject> createdList(beBaseInfoDataList_Create((int)allocator));
        setDataList(infoRam, createdList.p);
        PICK_ALLOCATOR(allocator, self);
        igSmartPointer<beNDMWLogoCtrlData> createdCtrl(beNDMWLogoCtrlData_Create((int)allocator));
        ObjectList_AppendRetained((igObjectList *)infoRam->_dataList, createdCtrl.p);
    }
    if (infoRam->_dataList == 0) {
        PICK_ALLOCATOR(allocator, infoRam);
        igSmartPointer<igObject> createdList(beBaseInfoDataList_Create((int)allocator));
        setDataList(infoRam, createdList.p);
    }
    ctrl = (beNDMWLogoCtrlData *)igProperty_FindByName((igObjectList *)infoRam->_dataList, g_propertyNameField, "CTRL");
    bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, 0);
    switch (ctrl->_st0) {
    case LogoStateCardCheck:
        switch (ctrl->_st1) {
        case CardCheckOpen:
            switch (ctrl->_st2) {
            case 0:
                switch (ctrl->_st3) {
                case 0:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "GENERATE");
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "SQ_OPEN");
                    ctrl->_st3 = ctrl->_st3 + 1;
                    break;
                case 1:
                    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0);
                    beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_OPEN");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                        beNDMWLogo_RunMessageScript(self, 91200);
                        NEXT_PHASE(ctrl);
                    }
                    break;
                }
                break;
            case 1:
                PICK_ALLOCATOR(allocator, self);
                igRelease((igObject *)self->_mcUtilCtrl);
                self->_mcUtilCtrl = (int)beNDMWMcUtilCtrl_Create((int)allocator);
                beNDMWMcUtilCtrl__Init(mcUtil(self), self->_messenger, 0);
                NEXT_PHASE(ctrl);
                break;
            case 2:
                beNDMWMcUtilCtrl__Generate(mcUtil(self));
                NEXT_PHASE(ctrl);
                break;
            case 3:
                if (beNDMWMcUtilCtrl__CheckReady(mcUtil(self)) == 1) {
                    ENTER_STEP(ctrl, CardCheckUse);
                }
                break;
            }
            break;
        case CardCheckUse:
            beNDMWMcUtilCtrl__Update(mcUtil(self));
            switch (ctrl->_st2) {
            case 0:
                self->_errTarget = -1;
                self->_errType = 2;
                self->_connect = 0;
                self->_isUseSave = 0;
                cardResult(self, 0) = 0;
                cardResult(self, 1) = 0;
                cardResult(self, 2) = 0;
                cardResult(self, 3) = 0;
                cardResult(self, 4) = 0;
                self->_isMtap = mcUtil(self)->_isMtap;
                NEXT_PHASE(ctrl);
                break;
            case 1:
                switch (ctrl->_st3) {
                case 0:
                    beNDMWMcUtilCtrl__Request(mcUtil(self), McRequestUseCheck, self->_connect);
                    self->_isMtap = mcUtil(self)->_isMtap;
                    if (self->_isMtap == 0) {
                        cardResult(self, 2) = 0;
                        cardResult(self, 3) = 0;
                        cardResult(self, 4) = 0;
                    }
                    ctrl->_st3 = ctrl->_st3 + 1;
                    break;
                case 1:
                    util = mcUtil(self);
                    if (util->_isResult == 1) {
                        switch (util->_result) {
                        case McResultOk:
                            connectResult(self) |= CardPresent;
                            NEXT_PHASE(ctrl);
                            break;
                        case 5:
                        case 12:
                            ENTER_PHASE(ctrl, 3);
                            break;
                        case 7:
                            self->_isUseSave = 1;
                            ENTER_STEP(ctrl, CardCheckClose);
                            break;
                        default:
                            connectResult(self) |= CardUnusable;
                            ENTER_PHASE(ctrl, 3);
                            break;
                        }
                    }
                    break;
                }
                break;
            case 2:
                switch (ctrl->_st3) {
                case 0:
                    beNDMWMcUtilCtrl__Request(mcUtil(self), McRequestFileFind, self->_connect);
                    ctrl->_st3 = ctrl->_st3 + 1;
                    break;
                case 1:
                    util = mcUtil(self);
                    if (util->_isResult == 1) {
                        switch (util->_result) {
                        case McResultOk:
                            self->_isUseSave = 1;
                            ENTER_STEP(ctrl, CardCheckClose);
                            break;
                        default:
                        case 5:
                        case 12:
                            NEXT_PHASE(ctrl);
                            break;
                        }
                    }
                    break;
                }
                break;
            case 3:
                nextSlot(self, ctrl, CardCheckFreeSize);
                break;
            }
            break;
        case CardCheckFreeSize:
            beNDMWMcUtilCtrl__Update(mcUtil(self));
            switch (ctrl->_st2) {
            case 0:
                self->_connect = 0;
                NEXT_PHASE(ctrl);
                if (self->_isMtap == 0) {
                    cardResult(self, 2) = 0;
                    cardResult(self, 3) = 0;
                    cardResult(self, 4) = 0;
                }
                break;
            case 1:
                if (connectResult(self) & CardPresent) {
                    switch (ctrl->_st3) {
                    case 0:
                        beNDMWMcUtilCtrl__Request(mcUtil(self), McRequestGetFreeSize, self->_connect);
                        ctrl->_st3 = ctrl->_st3 + 1;
                        break;
                    case 1:
                        util = mcUtil(self);
                        if (util->_isResult == 1) {
                            switch (util->_result) {
                            case McResultOk:
                                self->_isUseSave = 1;
                                ENTER_STEP(ctrl, CardCheckClose);
                                break;
                            case 5:
                            case 12:
                                ENTER_PHASE(ctrl, 2);
                                break;
                            default:
                                connectResult(self) |= CardFull;
                                NEXT_PHASE(ctrl);
                                break;
                            }
                        }
                        break;
                    }
                } else {
                    ENTER_PHASE(ctrl, 2);
                }
                break;
            case 2:
                nextSlot(self, ctrl, CardCheckClose);
                break;
            }
            break;
        case CardCheckClose:
            switch (ctrl->_st2) {
            case 0:
                self->_isMtap = mcUtil(self)->_isMtap;
                beNDMWMcUtilCtrl__Remove(mcUtil(self));
                NEXT_PHASE(ctrl);
                break;
            case 1:
                if (beNDMWMcUtilCtrl__IsRemoved(mcUtil(self)) == true) {
                    igRelease((igObject *)self->_mcUtilCtrl);
                    self->_mcUtilCtrl = 0;
                    NEXT_PHASE(ctrl);
                }
                break;
            case 2:
                switch (ctrl->_st3) {
                case 0:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "SQ_CLOSE");
                    beNDMWLogo_ClearMessageText(self);
                    ctrl->_st3 = ctrl->_st3 + 1;
                    break;
                case 1:
                    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "ISRUN");
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                        if (self->_isUseSave == 1) {
                            ENTER_STATE(ctrl, LogoStateRunLogo);
                        } else {
                            ENTER_STATE(ctrl, LogoStateCardError);
                        }
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    case LogoStateCardError:
        switch (ctrl->_st1) {
        case CardErrorOpen:
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "GENERATE");
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "SQ_OPEN");
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_memchkwn", 0, "GENERATE");
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_memchkwn", 0, "SQ_OPEN");
            findCardError(self);
            NEXT_STEP(ctrl);
            break;
        case CardErrorExplain:
            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0);
            beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_OPEN");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                switch (self->_errType) {
                case CardUnusable:
                    showFlaggedSlots(self, CardUnusable);
                    beNDMWLogo_RunMessageScript(self, 91020);
                    break;
                case CardFull:
                    showFlaggedSlots(self, CardFull);
                    beNDMWLogo_RunMessageScript(self, 91010);
                    break;
                default:
                    showAllSlots(self);
                    beNDMWLogo_RunMessageScript(self, 91000);
                    break;
                }
                NEXT_STEP(ctrl);
            }
            break;
        case CardErrorAcknowledge:
            switch (ctrl->_st2) {
            case 0:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "SELECTCTRL", "i_messky", 0, "GENERATE");
                NEXT_PHASE(ctrl);
                break;
            case 1:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "SELECTCTRL", "i_messky", 0, "ISEND");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == true) {
                    beNDMWLogo_ClearMessageText(self);
                    NEXT_PHASE(ctrl);
                }
                break;
            case 2:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_memchkwn", 0, "SQ_CLOSE");
                beNDMWLogo_ClearMessageText(self);
                NEXT_PHASE(ctrl);
                break;
            case 3:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_memchkwn", 0, "ISRUN");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                    NEXT_STEP(ctrl);
                }
                break;
            }
            break;
        case CardErrorAsk:
            switch (ctrl->_st2) {
            case 0:
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, "SELECTCTRL", "i_messcr", 0);
                beMessenger_AppendInt((beMessenger *)self->_messenger, 2);
                beMessenger_AppendString((beMessenger *)self->_messenger, "NOCANCEL");
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
                if (self->_errType == CardUnusable) {
                    beNDMWLogo_RunMessageScript(self, 91021);
                } else if (self->_errType == CardFull) {
                    beNDMWLogo_RunMessageScript(self, 91011);
                } else {
                    beNDMWLogo_RunMessageScript(self, 91001);
                }
                NEXT_PHASE(ctrl);
                break;
            case 1:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "SELECTCTRL", "i_messcr", 0, "ISEND");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == true) {
                    NEXT_PHASE(ctrl);
                }
                break;
            case 2:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "SELECTCTRL", "i_messcr", 0, "GETSELECT");
                self->_select = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
                NEXT_STEP(ctrl);
                break;
            }
            break;
        case CardErrorCloseAsk:
            switch (ctrl->_st2) {
            case 0:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "SQ_CLOSE");
                beNDMWLogo_ClearMessageText(self);
                NEXT_PHASE(ctrl);
                break;
            case 1:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "ISRUN");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                    NEXT_STEP(ctrl);
                }
                break;
            }
            break;
        case CardErrorDecide:
            if (self->_select == 0) {
                ENTER_STEP(ctrl, CardErrorSkip);
            } else {
                ctrl->_st1 = CurrentStep(ctrl) + 1;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
            }
            break;
        case CardErrorRetryOpen:
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "GENERATE");
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "SQ_OPEN");
            NEXT_STEP(ctrl);
            break;
        case CardErrorRetryExplain:
            beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0);
            beMessenger_AppendString((beMessenger *)self->_messenger, "SQ_OPEN");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                beNDMWLogo_RunMessageScript(self, 91100);
                NEXT_STEP(ctrl);
            }
            break;
        case CardErrorRetryAcknowledge:
            switch (ctrl->_st2) {
            case 0:
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, "SELECTCTRL", "i_messky", 0);
                beMessenger_AppendString((beMessenger *)self->_messenger, "NOCANCEL");
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
                NEXT_PHASE(ctrl);
                break;
            case 1:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "SELECTCTRL", "i_messky", 0, "ISEND");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == true) {
                    NEXT_STEP(ctrl);
                }
                break;
            }
            break;
        case CardErrorRetryClose:
            switch (ctrl->_st2) {
            case 0:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "SQ_CLOSE");
                beNDMWLogo_ClearMessageText(self);
                NEXT_PHASE(ctrl);
                break;
            case 1:
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "i_messwn", 0, "ISRUN");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == false) {
                    ENTER_STATE(ctrl, LogoStateCardCheck);
                }
                break;
            }
            break;
        case CardErrorSkip:
            ENTER_STATE(ctrl, LogoStateRunLogo);
            break;
        }
        break;
    case LogoStateRunLogo:
        g_mdlEntity = 0;
        beLua__RunNamedChunk((beLua *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject), "logo.lua", 0);
        ENTER_STATE(ctrl, LogoStateDone);
        break;
    case LogoStateDone:
        break;
    }
}

/* Shows message `callNo` through txt_Tar.lua. */
void beNDMWLogo_RunMessageScript(beNDMWLogo *self, int callNo) {
    igObject *lua = igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
    g_txtCallNo = callNo;
    g_mdlEntity = 0;
    beLua__RunNamedChunk((beLua *)lua, "txt_Tar.lua", 0);
}

static inline void clearTextElement(beNDMWLogo *self, const char *textType, const char *textName) {
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, "CLR");
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
}

/* Clears every text element the message scripts write. */
void beNDMWLogo_ClearMessageText(beNDMWLogo *self) {
    clearTextElement(self, "TALKFONT01", "font00");
    clearTextElement(self, "TALKFONT01", "font01");
    clearTextElement(self, "TALKFONT01", "font02");
    clearTextElement(self, "TALKFONT06", "font01");
    clearTextElement(self, "TALKFONT06", "font02");
    clearTextElement(self, "TALKFONT06", "font03");
    clearTextElement(self, "TALKFONT06", "font04");
    clearTextElement(self, "TALKFONT06", "font05");
}

int beNDMWLogo_GetInfoMeta(void) {
    return (int)g_beNDMWLogoInfo_metaObject;
}

void beNDMWLogo_OnAddRam(beNDMWLogo *self, int info) {
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)info, "LOGO");
}

/* The controller's one message is resolved and ignored. */
int beNDMWLogo_OnMessage(beNDMWLogo *self, beBaseInfoRam *infoRam, beMessengerWork *message) {
    if (infoRam->_dataList == 0) {
        return 1;
    }
    beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beNDMWLogoCtrlData_GetMessageEnum(), (const char *)message->_message);
    return 1;
}

int beNDMWLogo_GetMeta(void) {
    return (int)g_beNDMWLogo_metaObject;
}

#pragma pop
