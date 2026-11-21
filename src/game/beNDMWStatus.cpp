#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWItemAbilityChip.h"
#include "dw4/game/ndmw/beNDMWItemBlueArmor.h"
#include "dw4/game/ndmw/beNDMWItemWeapon.h"
#include "dw4/game/ndmw/beNDMWItemYellowArmor.h"
#include "dw4/game/ndmw/beNDMWShopCtrl00.h"
#include "dw4/game/ndmw/beNDMWShopCtrlA0.h"
#include "dw4/game/ndmw/beNDMWShopCtrlDigilabo.h"
#include "dw4/game/ndmw/beNDMWStatus.h"
#include "dw4/game/ndmw/beNDMWStatusCtrl00.h"
#include "dw4/game/ndmw/beNDMWStatusInfo.h"
#include "dw4/game/ndmw/beNDMWStatusInfoWork.h"
#include "dw4/game/ndmw/beNDMWWindow.h"
#include "dw4/game/ndmw/beNDMWWindowCtrl.h"
#include "dw4/game/ndmw/beNDMWWindowList.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igTDataList.h"
#include <stdio.h>
#include <string.h>
#include "dw4/support/list-services.h"

/* The SUBWND service menu: beNDMWStatus opens one window per _subWndNo (status, XDATA, lab, bank,
 * CNOS, disk, the four shops and the card window), shows the selected player's parameters, and
 * prepares the shop stock lists in its beNDMWStatusInfoWork. */

enum SubWnd {
    SUBWND_STATUS, SUBWND_XDATA, SUBWND_LABO, SUBWND_BANK, SUBWND_CNOS, SUBWND_DISK,
    SUBWND_WPU, SUBWND_APU, SUBWND_CHIP, SUBWND_JUNK, SUBWND_CARD
};

enum StatusMessage {
    MESSAGE_GENERATE, MESSAGE_REMOVE, MESSAGE_UPDATE, MESSAGE_GETSHOPDATA, MESSAGE_ONPREVIEW,
    MESSAGE_OFPREVIEW, MESSAGE_ISRUN
};

#define RELEASE(type, object) { type *released = (object); if (released) { --released->_refCount; if (!(released->_refCount & 0x7fffff)) igObject_Destroy(released); } }
#define NEXT_STATE(ram) { (ram)->_st0 = (ram)->_st0 + 1; (ram)->_st3 = 0; (ram)->_st2 = 0; (ram)->_st1 = 0; }
#define REPLACE_WINDOW(window, create) { \
    void *allocator; \
    void *ownerAllocator = ((Gap::Core::igObject *)self)->getMemoryPool(); \
    if (g_useOwnerAllocator != 0) { allocator = ownerAllocator; } else { allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); } \
    RELEASE(beNDMWWindow, (window).p) \
    (window).p = (beNDMWWindow *)create((int)allocator); }
/* The 5 and 2 byte copies are the compiler's __memcpy intrinsic, which only the alternate compiler has. */
#if __MWERKS__ >= 0x3000
#define COPY_BYTES(d, s, n) __memcpy(d, (void *)(s), n)
#else
#define COPY_BYTES(d, s, n) { char *cd_ = (char *)(d); const char *cs_ = (const char *)(s); int k_; for (k_ = 0; k_ < (n); k_++) cd_[k_] = cs_[k_]; }
#endif
#define PARAMETERS ((igIntList *)work->_parameter)
#define PARAMETER(i) (((int *)PARAMETERS->_data)[i])
#define APPEND_PARAMETER(idx, value) { igIntList *list = PARAMETERS; idx = list->_count; if (idx < list->_capacity) list->_count = countOf(list) + 1; else ((Gap::Core::igDataList *)list)->resizeAndSetCount(idx + 1, 4); ((int *)list->_data)[idx] = (value); }
#define SET_TEXT(font, label, text) { \
    beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL"); \
    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)font); \
    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)label); \
    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)text); \
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "TEXTSET"); }
#define SELECT_TEXT_COLOR(label) \
    beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL"); \
    beMessenger_AppendString((beMessenger *)self->_messenger, "STWINFONT06"); \
    beMessenger_AppendString((beMessenger *)self->_messenger, label);
/* Shows a parameter row and records the shown value, the base the preview colours compare against. */
#define SHOW_PARAMETER(record, label) { \
    int idx; int value = igProperty_GetRecord((igObject *)player, record)->_data; \
    sprintf(text, "%d", value); \
    SET_TEXT("STWINFONT06", label, text) \
    APPEND_PARAMETER(idx, value) }
#define SHOW_VALUE(record, label) { \
    int value = igProperty_GetRecord((igObject *)player, record)->_data; \
    sprintf(text, "%d", value); \
    SET_TEXT("STWINFONT06", label, text) }
/* Equal: grey; lower than the shown base: red; higher: blue. */
#define PREVIEW_COLOR(value, base) { if (value == base) { r = 0.9f; g = 0.9f; b = 0.9f; } else if (value < base) { r = 0.94f; g = 0.4f; b = 0.25f; } else { g = 0.96f; b = 1.0f; r = 0.0f; } }
#define SHOW_PREVIEW(record, label, index, color) { \
    int value = igProperty_GetRecord((igObject *)player, record)->_data; \
    int base = PARAMETER(index); \
    PREVIEW_COLOR(value, base) \
    sprintf(previewText, "%d", value); \
    SET_TEXT("STWINFONT06", label, previewText) \
    SELECT_TEXT_COLOR(label) \
    color[0] = r; color[1] = g; color[2] = b; \
    beMessenger_AppendVec3((beMessenger *)self->_messenger, color); \
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "COLOR"); }
#define RESTORE_PARAMETER(index, label) \
    sprintf(restoreText, "%d", PARAMETER(index)); \
    SET_TEXT("STWINFONT06", label, restoreText) \
    SELECT_TEXT_COLOR(label) \
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "DEFAULTCOLOR");
#define SALES_LIST(field) ((igObjectList *)work->field)
#define PICK_ALLOCATOR(allocator, selector) { allocator = ((Gap::Core::igObject *)owner)->getMemoryPool(); allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(selector); }
#define STOCK_ITEM(K, T, holder, list, id) { \
    PICK_ALLOCATOR(allocator, kIGMemoryPoolHandleUser0) \
    ItemRef<K> holder((igObject *)T##_Create((int)allocator)); \
    T##_SetRandom((T *)holder.p, id, owner, level); \
    ObjectList_AppendRetained(list, holder.p); }
#define STOCK_CHIP(holder, list, id) { \
    PICK_ALLOCATOR(allocator, kIGMemoryPoolHandleUser0) \
    ItemRef<4> holder((igObject *)beNDMWItemAbilityChip_Create((int)allocator)); \
    beNDMWItemAbilityChip_Set((beNDMWItemAbilityChip *)holder.p, id); \
    ObjectList_AppendRetained(list, holder.p); }
#define COLUMN_KEY(key, column) { key[0] = column / 10 + '0'; key[1] = column % 10 + '0'; key[2] = 0; }

/* kept local: ObjectList_FillRetained has no include/dw4 home (only CoreLibrary.h declares it). */

extern "C" void beNDMWStatus_Prepare(beNDMWStatus *self);
extern "C" int beNDMWStatus__GetInfoMeta(void);
extern "C" void beNDMWStatus_OnAddRam(beNDMWStatus *self, beNDMWStatusInfoRam *ram);
extern "C" void beNDMWStatus_UpdateRam(beNDMWStatus *self, beNDMWStatusInfoRam *ram);
extern "C" int beNDMWStatus_OnMessage(beNDMWStatus *self, beNDMWStatusInfoRam *ram, beBaseInfo *info);
extern "C" void beNDMWStatus__PrepareWork(beNDMWStatus *owner, beNDMWStatusInfoRam *ram);
extern "C" int beNDMWStatus__GetMeta(void);

/* Owning reference to a freshly created shop item: the destructor drops one reference and destroys
 * at zero. Each item kind is its own class, so one destructor is emitted per "kind". */
template <int K> struct ItemRef { igObject *p; ItemRef(igObject *o) : p(o) {} ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };

/* A sales list holds 36 slots. */
struct SalesList { static inline void Reserve(const igObjectList *list) { if (list->_count < 37) ((Gap::Core::igDataList *)list)->setCapacity(36, 4); } };

static inline int countOf(const igIntList *list) { return list->_count; }

#pragma push
#pragma readonly_strings on

void beNDMWStatus_Prepare(beNDMWStatus *self) {
    igObject *window = (igObject *)self->_windowPro;
    if (window != 0) {
        window->_refCount = window->_refCount - 1;
        if ((window->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(window);
        }
    }
    self->_windowPro = 0;
}

int beNDMWStatus__GetInfoMeta(void)
{
    return (int)g_beNDMWStatusInfo_metaObject;
}

void beNDMWStatus_OnAddRam(beNDMWStatus *self, beNDMWStatusInfoRam *ram) {
    if (((beBaseInfoList *)self->_infoList)->_count == 1) {
        beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, (beBaseInfoRam *)ram, "SUBWND");
        ram->_isRun = 0;
    }
}

void beNDMWStatus_UpdateRam(beNDMWStatus *self, beNDMWStatusInfoRam *ram)
{
    int state;
    if (ram->_isRun == 0) return;
    state = ram->_st0;
    switch (state) {
    case 0:
        beNDMWStatus__PrepareWork(self, ram);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "STAGECTL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "ENABLE");
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "PADINPUT");
        {
        igSmartPointer<beNDMWWindow> window(0);
        switch (self->_subWndNo) {
        case SUBWND_STATUS:
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "WN01");
            beMessenger_AppendString((beMessenger *)self->_messenger, "DISPOFF");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
            beMessenger_AppendString((beMessenger *)self->_messenger, "WN00");
            beMessenger_AppendString((beMessenger *)self->_messenger, "DISPOFF");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
            REPLACE_WINDOW(window, beNDMWStatusCtrl00_Create)
            break;
        case SUBWND_XDATA: case SUBWND_BANK: case SUBWND_CNOS: case SUBWND_DISK:
        case SUBWND_WPU: case SUBWND_APU: case SUBWND_CHIP: case SUBWND_JUNK:
            REPLACE_WINDOW(window, beNDMWShopCtrl00_Create)
            break;
        case SUBWND_LABO:
            REPLACE_WINDOW(window, beNDMWShopCtrlDigilabo_Create)
            break;
        case SUBWND_CARD:
            REPLACE_WINDOW(window, beNDMWShopCtrlA0_Create)
            break;
        }
        beNDMWWindow_BindContext(window.p, 0, self->_insight, self->_whoGenerate, 0);
        window.p->_entCode = self->_subWndNo;
        {
            beNDMWWindow *retained = window.p;
            if (retained) ++retained->_refCount;
            RELEASE(beNDMWWindow, (beNDMWWindow *)self->_windowPro)
            self->_windowPro = (int)retained;
        }
        if (self->_subWndNo != SUBWND_STATUS) {
            beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "BGMSTOP");
            beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "ENVSTOP");
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "SOUND");
            beMessenger_AppendString((beMessenger *)self->_messenger, "RM_NSHOP");
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "PLAY");
        }
        }
        NEXT_STATE(ram)
    case 1:
        if (self->_windowPro != 0) beNDMWWindow_UpdateTree((beNDMWWindow *)self->_windowPro);
        if (((beNDMWWindow *)self->_windowPro)->_isRun != 0) return;
        NEXT_STATE(ram)
    default:
        {
            int player;
            RELEASE(beNDMWWindow, (beNDMWWindow *)self->_windowPro)
            self->_windowPro = 0;
            beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "OFFREEZE");
            beMessenger_SendGroup((beMessenger *)self->_messenger, "GENERATER", "OFFREEZE");
            beMessenger_SendGroup((beMessenger *)self->_messenger, "MODELCTRL", "OFFREEZE");
            beMessenger_SetFreezeTime((beMessenger *)self->_messenger, 0);
            ram->_isRun = 0;
            player = 0;
            do {
                beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                beMessenger_AppendInt((beMessenger *)self->_messenger, player);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
                if (igProperty_GetRecordByte(beMessenger_GetObject((beMessenger *)self->_messenger, 0), "ISUSE")->_data != 0) {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                    beMessenger_AppendInt((beMessenger *)self->_messenger, player);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ADDHP");
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                    beMessenger_AppendInt((beMessenger *)self->_messenger, player);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ADDMP");
                }
                player++;
            } while (player < 4);
            if (self->_subWndNo == SUBWND_CARD) {
                beMessenger_SendGroup((beMessenger *)self->_messenger, "STAGECTL", "ISRESETSTART");
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 0) {
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "PLAYERPOINT");
                    beMessenger_AppendInt((beMessenger *)self->_messenger, 4);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SETGENERATEPOS");
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, "STAGECTL");
                    beMessenger_AppendString((beMessenger *)self->_messenger, "stagML12");
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "NEXTSTAGE");
                }
            } else {
                beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
                beMessenger_AppendString((beMessenger *)self->_messenger, "WN01");
                beMessenger_AppendString((beMessenger *)self->_messenger, "DISPON");
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
                beMessenger_SelectGroup((beMessenger *)self->_messenger, "LAYERCTL");
                beMessenger_AppendString((beMessenger *)self->_messenger, "WN00");
                beMessenger_AppendString((beMessenger *)self->_messenger, "DISPON");
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
                if (self->_subWndNo != SUBWND_STATUS)
                    beLua__RunNamedChunk((beLua *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject), "shopexit.lua", 0);
            }
        }
    }
}

int beNDMWStatus_OnMessage(beNDMWStatus *self, beNDMWStatusInfoRam *ram, beBaseInfo *info) {
    unsigned int message = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, StatusMessage_GetMetaEnum(), (const char *)info->_dataList);
    float maxHpColor[3];
    float maxMpColor[3];
    float strengthColor[3];
    float defenseColor[3];
    float wisdomColor[3];
    float spiritColor[3];
    float speedColor[3];
    float fireResistColor[3];
    float iceResistColor[3];
    float thunderResistColor[3];
    float darkResistColor[3];
    char text[16];
    char previewText[16];
    char restoreText[16];
    int playerNo;
    int level;
    int hp;
    int mp;
    beNDMWStatusInfoWork *work;
    int player;
    switch (message) {
    case MESSAGE_ISRUN:
        beMessenger_AppendBool((beMessenger *)self->_messenger, ram->_isRun);
        return 1;
    case MESSAGE_GENERATE:
        if (ram->_isRun == 0) {
            int whoGenerate = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
            int subWndName = (int)beMessenger_GetString((beMessenger *)self->_messenger, 0);
            unsigned int subWndNo = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, SubWnd_GetMetaEnum(), (const char *)subWndName);
            ram->_isRun = 1;
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
            self->_subWndNo = subWndNo;
            self->_whoGenerate = whoGenerate;
            beMessenger_SendGroup((beMessenger *)self->_messenger, "MODELCTRL", "ONFREEZE");
            beMessenger_SendGroup((beMessenger *)self->_messenger, "GENERATER", "ONFREEZE");
            beMessenger_SetFreezeTime((beMessenger *)self->_messenger, 1);
            beMessenger_SendGroup((beMessenger *)self->_messenger, "SOUND", "ONFREEZE");
        }
        return 1;
    case MESSAGE_REMOVE:
        if (ram->_isRun == 1) {
            beNDMWWindow *window = (beNDMWWindow *)self->_windowPro;
            if (window != 0) {
                window->_st0 = 2;
                window->_st3 = 0;
                window->_st2 = 0;
                window->_st1 = 0;
            } else {
                beMessenger_SetFreezeTime((beMessenger *)self->_messenger, 0);
                beMessenger_SendDelayedGroup((beMessenger *)self->_messenger, "SUBWND", "REMOVE", 1);
            }
        }
        return 1;
    case MESSAGE_UPDATE: {
        work = (beNDMWStatusInfoWork *)ram->_work;
        playerNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        if (work == 0) {
            beNDMWStatus__PrepareWork(self, ram);
            work = (beNDMWStatusInfoWork *)ram->_work;
        }
        PARAMETERS->_count = 0;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
        beMessenger_AppendInt((beMessenger *)self->_messenger, playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
        player = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        igSmartPointer<igObject> name(((igObject **)((igObjectList *)igProperty_GetRecordFolder((igObject *)player, "PLAYERNAME")->_data)->_data)[0]);
        if (name.p != 0) name.p->_refCount = name.p->_refCount + 1;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "TEXTCTL");
        beMessenger_AppendString((beMessenger *)self->_messenger, "STWINFONT02");
        beMessenger_AppendString((beMessenger *)self->_messenger, "font000");
        beMessenger_AppendObject((beMessenger *)self->_messenger, name.p);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "TEXTSET");
        level = igProperty_GetRecord((igObject *)player, "LEVEL")->_data;
        if (level > 999) level = 999;
        sprintf(text, "%d", level);
        SET_TEXT("STWINFONT04", "font000", text)
        beMessenger_SendNamed((beMessenger *)self->_messenger, "DATABASE", "shinka", 0, "GETDATABASE");
        {
            int database = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
            int *digimonName = (int *)beDataBase_GetRecordString((beDataBase *)database, igProperty_GetRecord((igObject *)player, "DIGIMONNO")->_data, "NAME");
            SET_TEXT("STWINFONT04", "font001", digimonName)
        }
        hp = igProperty_GetRecord((igObject *)player, "HP")->_data;
        sprintf(text, "%d", hp);
        SET_TEXT("STWINFONT06", "font000", text)
        mp = igProperty_GetRecord((igObject *)player, "MP")->_data;
        sprintf(text, "%d", mp);
        SET_TEXT("STWINFONT06", "font001", text)
        SHOW_PARAMETER("MHP", "font010")
        SHOW_PARAMETER("MMP", "font011")
        SHOW_PARAMETER("TSUYOSA", "font040")
        SHOW_PARAMETER("MAMORI", "font041")
        SHOW_PARAMETER("KASHIKOSA", "font042")
        SHOW_PARAMETER("SEISHIN", "font043")
        SHOW_PARAMETER("SUBAYASA", "font044")
        SHOW_PARAMETER("HONOOTEIKO", "font045")
        SHOW_PARAMETER("KOORITEIKO", "font046")
        SHOW_PARAMETER("KAMINARITEIKO", "font047")
        SHOW_PARAMETER("YAMITEIKO", "font048")
        SHOW_VALUE("XDATA", "font049")
        SHOW_VALUE("BIT", "font070")
        {
            int exp = igProperty_GetRecord((igObject *)player, "EXP")->_data;
            int toNext = igProperty_GetRecord((igObject *)player, "NEXTEXP")->_data - exp;
            if (level >= 999) {
                COPY_BYTES(text, "----", 5);
            } else if (toNext < 0) {
                COPY_BYTES(text, "0", 2);
            } else {
                sprintf(text, "%d", toNext);
            }
            SET_TEXT("STWINFONT06", "font071", text)
        }
        { int idx; APPEND_PARAMETER(idx, hp) }
        { int idx; APPEND_PARAMETER(idx, mp) }
        return 1;
    }
    case MESSAGE_ONPREVIEW: {
        int playerNo;
        int player;
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)ram->_work;
        playerNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        float r, g, b;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
        beMessenger_AppendInt((beMessenger *)self->_messenger, playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
        player = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        SHOW_PREVIEW("MHP", "font010", 0, maxHpColor)
        SHOW_PREVIEW("MMP", "font011", 1, maxMpColor)
        SHOW_PREVIEW("TSUYOSA", "font040", 2, strengthColor)
        SHOW_PREVIEW("MAMORI", "font041", 3, defenseColor)
        SHOW_PREVIEW("KASHIKOSA", "font042", 4, wisdomColor)
        SHOW_PREVIEW("SEISHIN", "font043", 5, spiritColor)
        SHOW_PREVIEW("SUBAYASA", "font044", 6, speedColor)
        SHOW_PREVIEW("HONOOTEIKO", "font045", 7, fireResistColor)
        SHOW_PREVIEW("KOORITEIKO", "font046", 8, iceResistColor)
        SHOW_PREVIEW("KAMINARITEIKO", "font047", 9, thunderResistColor)
        SHOW_PREVIEW("YAMITEIKO", "font048", 10, darkResistColor)
        return 1;
    }
    case MESSAGE_OFPREVIEW: {
        int playerNo;
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)ram->_work;
        playerNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        int *parameters;
        int shownHp, shownMp, player;
        RESTORE_PARAMETER(0, "font010")
        RESTORE_PARAMETER(1, "font011")
        RESTORE_PARAMETER(2, "font040")
        RESTORE_PARAMETER(3, "font041")
        RESTORE_PARAMETER(4, "font042")
        RESTORE_PARAMETER(5, "font043")
        RESTORE_PARAMETER(6, "font044")
        RESTORE_PARAMETER(7, "font045")
        RESTORE_PARAMETER(8, "font046")
        RESTORE_PARAMETER(9, "font047")
        RESTORE_PARAMETER(10, "font048")
        parameters = (int *)PARAMETERS->_data;
        shownHp = parameters[11];
        shownMp = parameters[12];
        beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
        beMessenger_AppendInt((beMessenger *)self->_messenger, playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GETPLAYER");
        player = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        igProperty_GetRecord((igObject *)player, "HP")->_data = shownHp;
        igProperty_GetRecord((igObject *)player, "MP")->_data = shownMp;
        return 1;
    }
    case MESSAGE_GETSHOPDATA: {
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)ram->_work;
        int subWndNo = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        switch (subWndNo) {
        case SUBWND_WPU:
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)(void *)work->_weaponSalesList);
            break;
        case SUBWND_APU:
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)(void *)work->_armorSalesList);
            break;
        case SUBWND_CHIP:
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)(void *)work->_chipSalesList);
            break;
        case SUBWND_JUNK:
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)(void *)work->_junkSalesList);
            beMessenger_AppendInt((beMessenger *)self->_messenger, work->_junkGift);
            break;
        }
        return 1;
    }
    default:
        return 0;
    }
}

void beNDMWStatus__PrepareWork(beNDMWStatus *owner, beNDMWStatusInfoRam *ram) {
    char weaponKey[8];
    char armorKey[8];
    char chipKey[8];
    char junkKey[8];
    beNDMWStatusInfoWork *work;
    void *allocator;
    int partySize;
    int playerNo;
    int player;
    int level;
    int baseRow;
    int row;
    int database;
    int chipRow;
    int weaponColumn, blueColumn, yellowColumn, chipColumn, junkColumn;
    int id;
    int itemKind;
    int weaponRow;
    int common;
    int junkCounter;
    int junkRow;
    beDataObjIntList *counters;

    work = (beNDMWStatusInfoWork *)ram->_work;
    if (work == 0) {
        PICK_ALLOCATOR(allocator, kIGMemoryPoolHandleUser1)
        igSmartPointer<beNDMWStatusInfoWork> created((beNDMWStatusInfoWork *)beNDMWStatusInfoWork_Create((int)allocator));
        igObject *retained = created.p;
        if (retained != 0) retained->_refCount = retained->_refCount + 1;
        RELEASE(igObject, (igObject *)ram->_work)
        ram->_work = (int)retained;
        work = (beNDMWStatusInfoWork *)ram->_work;
    }
    partySize = 0;
    playerNo = 0;
    do {
        beMessenger_SelectGroup((beMessenger *)owner->_messenger, "GAMERAM");
        beMessenger_AppendInt((beMessenger *)owner->_messenger, playerNo);
        beMessenger_DispatchSelected((beMessenger *)owner->_messenger, "GETPLAYER");
        player = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
        if (igProperty_GetRecordByte((igObject *)player, "ISUSE")->_data != 0) {
            partySize += 1;
            if (igProperty_GetRecord((igObject *)player, "BIT")->_data > 9999999) {
                beDataObjInt *bit = igProperty_GetRecord((igObject *)player, "BIT");
                bit->_data = 9999999;
            }
            if (igProperty_GetRecord((igObject *)player, "XDATA")->_data > 9999) {
                beDataObjInt *xdata = igProperty_GetRecord((igObject *)player, "XDATA");
                xdata->_data = 9999;
            }
        }
        playerNo += 1;
    } while (playerNo < 4);
    beMessenger_SelectGroup((beMessenger *)owner->_messenger, "GAMERAM");
    beMessenger_AppendInt((beMessenger *)owner->_messenger, 0);
    beMessenger_DispatchSelected((beMessenger *)owner->_messenger, "GETPLAYER");
    player = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
    level = igProperty_GetRecord((igObject *)player, "LEVEL")->_data;
    switch (owner->_subWndNo) {
    case SUBWND_WPU:
        if (SALES_LIST(_weaponSalesList)->_count <= 0) {
            SalesList::Reserve(SALES_LIST(_weaponSalesList));
            ObjectList_FillRetained((igTDataList<igObject *> *)SALES_LIST(_weaponSalesList), 0);
            if (partySize > 1) {
                baseRow = 150;
            } else {
                switch (igProperty_GetRecord((igObject *)player, "DIGIMONNO")->_data) {
                case 15: default: baseRow = 0; break;
                case 1: case 4: case 12: baseRow = 25; break;
                case 2: case 7: case 14: baseRow = 50; break;
                case 3: case 9: baseRow = 75; break;
                case 8: case 11: case 13: baseRow = 125; break;
                case 6: case 10: baseRow = 100; break;
                }
            }
            if (level < 10) row = 0;
            else if (level < 17) row = 1;
            else if (level < 22) row = 2;
            else if (level < 27) row = 3;
            else if (level < 32) row = 4;
            else if (level < 37) row = 5;
            else if (level < 42) row = 6;
            else if (level < 47) row = 7;
            else if (level < 52) row = 8;
            else if (level < 61) row = 9;
            else if (level < 68) row = 10;
            else if (level < 73) row = 11;
            else if (level < 78) row = 12;
            else if (level < 83) row = 13;
            else if (level < 88) row = 14;
            else if (level < 93) row = 15;
            else if (level < 98) row = 16;
            else if (level < 103) row = 17;
            else if (level < 108) row = 18;
            else if (level < 113) row = 19;
            else if (level < 118) row = 20;
            else if (level < 128) row = 21;
            else if (level < 138) row = 22;
            else if (level < 148) row = 23;
            else row = 24;
            beMessenger_SendNamed((beMessenger *)owner->_messenger, "DATABASE", "shopWeapon", 0, "GETDATABASE");
            database = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
            weaponRow = baseRow + row;
            weaponColumn = 0;
            do {
                COLUMN_KEY(weaponKey, weaponColumn)
                id = beDataBase_GetRecordInt((beDataBase *)database, weaponRow, weaponKey);
                if (id != -1) {
                    STOCK_ITEM(1, beNDMWItemWeapon, weapon, SALES_LIST(_weaponSalesList), id)
                } else {
                    ObjectList_AppendRetained(SALES_LIST(_weaponSalesList), 0);
                }
                weaponColumn += 1;
            } while (weaponColumn < 36);
        }
        break;
    case SUBWND_APU:
        if (SALES_LIST(_armorSalesList)->_count <= 0) {
            SalesList::Reserve(SALES_LIST(_armorSalesList));
            ObjectList_FillRetained((igTDataList<igObject *> *)SALES_LIST(_armorSalesList), 0);
            if (level < 10) row = 0;
            else if (level < 17) row = 1;
            else if (level < 22) row = 2;
            else if (level < 27) row = 3;
            else if (level < 32) row = 4;
            else if (level < 37) row = 5;
            else if (level < 42) row = 6;
            else if (level < 47) row = 7;
            else if (level < 52) row = 8;
            else if (level < 61) row = 9;
            else if (level < 68) row = 10;
            else if (level < 73) row = 11;
            else if (level < 78) row = 12;
            else if (level < 83) row = 13;
            else if (level < 88) row = 14;
            else if (level < 93) row = 15;
            else if (level < 98) row = 16;
            else if (level < 103) row = 17;
            else if (level < 108) row = 18;
            else if (level < 113) row = 19;
            else if (level < 118) row = 20;
            else if (level < 128) row = 21;
            else if (level < 138) row = 22;
            else if (level < 148) row = 23;
            else if (level < 158) row = 24;
            else if (level < 168) row = 25;
            else if (level < 178) row = 26;
            else if (level < 188) row = 27;
            else if (level < 198) row = 28;
            else row = 29;
            beMessenger_SendNamed((beMessenger *)owner->_messenger, "DATABASE", "shopArmor", 0, "GETDATABASE");
            database = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
            blueColumn = 0;
            do {
                COLUMN_KEY(armorKey, blueColumn)
                id = beDataBase_GetRecordInt((beDataBase *)database, row, armorKey);
                STOCK_ITEM(2, beNDMWItemBlueArmor, blueArmor, SALES_LIST(_armorSalesList), id)
                blueColumn += 1;
            } while (blueColumn < 12);
            yellowColumn = 12;
            do {
                COLUMN_KEY(armorKey, yellowColumn)
                itemKind = beDataBase_GetRecordInt((beDataBase *)database, row, armorKey);
                if (itemKind != -1) {
                    STOCK_ITEM(3, beNDMWItemYellowArmor, yellowArmor, SALES_LIST(_armorSalesList), itemKind)
                } else {
                    ObjectList_AppendRetained(SALES_LIST(_armorSalesList), 0);
                }
                yellowColumn += 1;
            } while (yellowColumn < 36);
        }
        break;
    case SUBWND_CHIP:
        if (SALES_LIST(_chipSalesList)->_count <= 0) {
            SalesList::Reserve(SALES_LIST(_chipSalesList));
            ObjectList_FillRetained((igTDataList<igObject *> *)SALES_LIST(_chipSalesList), 0);
            if (level < 10) chipRow = 0;
            else if (level < 17) chipRow = 1;
            else if (level < 22) chipRow = 2;
            else if (level < 27) chipRow = 3;
            else if (level < 32) chipRow = 4;
            else if (level < 37) chipRow = 5;
            else if (level < 42) chipRow = 6;
            else if (level < 47) chipRow = 7;
            else if (level < 52) chipRow = 8;
            else if (level < 61) chipRow = 9;
            else if (level < 68) chipRow = 10;
            else if (level < 73) chipRow = 11;
            else if (level < 78) chipRow = 12;
            else if (level < 83) chipRow = 13;
            else if (level < 88) chipRow = 14;
            else if (level < 93) chipRow = 15;
            else if (level < 98) chipRow = 16;
            else if (level < 103) chipRow = 17;
            else if (level < 108) chipRow = 18;
            else if (level < 113) chipRow = 19;
            else if (level < 118) chipRow = 20;
            else if (level < 128) chipRow = 21;
            else if (level < 138) chipRow = 22;
            else if (level < 148) chipRow = 23;
            else if (level < 158) chipRow = 24;
            else if (level < 168) chipRow = 25;
            else if (level < 178) chipRow = 26;
            else if (level < 188) chipRow = 27;
            else if (level < 198) chipRow = 28;
            else chipRow = 29;
            beMessenger_SendNamed((beMessenger *)owner->_messenger, "DATABASE", "shopChip", 0, "GETDATABASE");
            database = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
            chipColumn = 0;
            do {
                COLUMN_KEY(chipKey, chipColumn)
                id = beDataBase_GetRecordInt((beDataBase *)database, chipRow, chipKey);
                if (id != -1) {
                    STOCK_CHIP(chip, SALES_LIST(_chipSalesList), id)
                } else {
                    ObjectList_AppendRetained(SALES_LIST(_chipSalesList), 0);
                }
                chipColumn += 1;
            } while (chipColumn < 36);
        }
        break;
    case SUBWND_JUNK:
        beMessenger_SendGroup((beMessenger *)owner->_messenger, "GAMERAM", "GETCOMMON");
        common = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
        counters = igProperty_GetRecordIntList((igObject *)common, "COUNTER");
        junkCounter = ((int *)((igIntList *)counters->_data)->_data)[1];
        if (junkCounter >= 3956000) junkRow = 8;
        else if (junkCounter >= 1956000) junkRow = 7;
        else if (junkCounter >= 956000) junkRow = 6;
        else if (junkCounter >= 456000) junkRow = 5;
        else if (junkCounter >= 206000) junkRow = 4;
        else if (junkCounter >= 86000) junkRow = 3;
        else if (junkCounter >= 26000) junkRow = 2;
        else if (junkCounter >= 6000) junkRow = 1;
        else if (junkCounter >= 1000) junkRow = 0;
        else junkRow = -1;
        if (SALES_LIST(_junkSalesList)->_count <= 0) {
            work->_junkGift = junkCounter;
            SalesList::Reserve(SALES_LIST(_junkSalesList));
            ObjectList_FillRetained((igTDataList<igObject *> *)SALES_LIST(_junkSalesList), 0);
            if (junkRow != -1) {
                beMessenger_SendNamed((beMessenger *)owner->_messenger, "DATABASE", "shopJunk", 0, "GETDATABASE");
                database = (int)beMessenger_GetObject((beMessenger *)owner->_messenger, 0);
                junkColumn = 0;
                do {
                    COLUMN_KEY(junkKey, junkColumn)
                    id = beDataBase_GetRecordInt((beDataBase *)database, junkRow, junkKey);
                    if (id != -1) {
                        strcat(junkKey, "kind");
                        itemKind = beDataBase_GetRecordInt((beDataBase *)database, junkRow, junkKey);
                        switch (itemKind) {
                        case 0:
                            STOCK_ITEM(1, beNDMWItemWeapon, junkWeapon, SALES_LIST(_junkSalesList), id)
                            break;
                        case 1:
                            STOCK_ITEM(2, beNDMWItemBlueArmor, junkBlueArmor, SALES_LIST(_junkSalesList), id)
                            break;
                        case 2:
                            STOCK_ITEM(3, beNDMWItemYellowArmor, junkYellowArmor, SALES_LIST(_junkSalesList), id)
                            break;
                        }
                    }
                    junkColumn += 1;
                } while (junkColumn < 36);
            }
        }
        break;
    }
}

int beNDMWStatus__GetMeta(void)
{
    return (int)g_beNDMWStatus_metaObject;
}

#pragma pop
