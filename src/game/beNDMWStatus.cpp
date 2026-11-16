#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

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
    void *ownerAllocator = igObject_GetAllocator(self); \
    if (g_useOwnerAllocator != 0) { allocator = ownerAllocator; } else { allocator = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]); } \
    RELEASE(beNDMWWindow, (window).p) \
    (window).p = create(allocator); }
/* The 5 and 2 byte copies are the compiler's __memcpy intrinsic, which only the alternate compiler has. */
#if __MWERKS__ >= 0x3000
#define COPY_BYTES(d, s, n) __memcpy(d, (void *)(s), n)
#else
#define COPY_BYTES(d, s, n) { char *cd_ = (char *)(d); const char *cs_ = (const char *)(s); int k_; for (k_ = 0; k_ < (n); k_++) cd_[k_] = cs_[k_]; }
#endif
#define PARAMETERS ((igIntList *)work->_parameter)
#define PARAMETER(i) (((int *)PARAMETERS->_data)[i])
#define APPEND_PARAMETER(idx, value) { igIntList *list = PARAMETERS; idx = list->_count; if (idx < list->_capacity) list->_count = countOf(list) + 1; else List_Resize(list, idx + 1, 4); ((int *)list->_data)[idx] = (value); }
#define SET_TEXT(font, label, text) { \
    beMessenger_SelectGroup(self->_messenger, "TEXTCTL"); \
    beMessenger_AppendString(self->_messenger, font); \
    beMessenger_AppendString(self->_messenger, label); \
    beMessenger_AppendString(self->_messenger, text); \
    beMessenger_DispatchSelected(self->_messenger, "TEXTSET"); }
#define SELECT_TEXT_COLOR(label) \
    beMessenger_SelectGroup(self->_messenger, "TEXTCTL"); \
    beMessenger_AppendString(self->_messenger, "STWINFONT06"); \
    beMessenger_AppendString(self->_messenger, label);
/* Shows a parameter row and records the shown value, the base the preview colours compare against. */
#define SHOW_PARAMETER(record, label) { \
    int idx; int value = igProperty_GetRecord(player, record)->_data; \
    sprintf(text, "%d", value); \
    SET_TEXT("STWINFONT06", label, text) \
    APPEND_PARAMETER(idx, value) }
#define SHOW_VALUE(record, label) { \
    int value = igProperty_GetRecord(player, record)->_data; \
    sprintf(text, "%d", value); \
    SET_TEXT("STWINFONT06", label, text) }
/* Equal: grey; lower than the shown base: red; higher: blue. */
#define PREVIEW_COLOR(value, base) { if (value == base) { r = 0.9f; g = 0.9f; b = 0.9f; } else if (value < base) { r = 0.94f; g = 0.4f; b = 0.25f; } else { g = 0.96f; b = 1.0f; r = 0.0f; } }
#define SHOW_PREVIEW(record, label, index, color) { \
    int value = igProperty_GetRecord(player, record)->_data; \
    int base = PARAMETER(index); \
    PREVIEW_COLOR(value, base) \
    sprintf(previewText, "%d", value); \
    SET_TEXT("STWINFONT06", label, previewText) \
    SELECT_TEXT_COLOR(label) \
    color[0] = r; color[1] = g; color[2] = b; \
    beMessenger_AppendVec3(self->_messenger, color); \
    beMessenger_DispatchSelected(self->_messenger, "COLOR"); }
#define RESTORE_PARAMETER(index, label) \
    sprintf(restoreText, "%d", PARAMETER(index)); \
    SET_TEXT("STWINFONT06", label, restoreText) \
    SELECT_TEXT_COLOR(label) \
    beMessenger_DispatchSelected(self->_messenger, "DEFAULTCOLOR");
#define SALES_LIST(field) ((igObjectList *)work->field)
#define PICK_ALLOCATOR(allocator, selector) { allocator = igObject_GetAllocator(owner); allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(selector); }
#define STOCK_ITEM(K, holder, create, setRandom, list, id) { \
    PICK_ALLOCATOR(allocator, kIGMemoryPoolHandleUser0[0]) \
    ItemRef<K> holder((igObject *)create(allocator)); \
    setRandom(holder.p, id, owner, level); \
    ObjectList_AppendRetained(list, holder.p); }
#define STOCK_CHIP(holder, list, id) { \
    PICK_ALLOCATOR(allocator, kIGMemoryPoolHandleUser0[0]) \
    ItemRef<4> holder((igObject *)beNDMWItemAbilityChip_Create(allocator)); \
    beNDMWItemAbilityChip_Set(holder.p, id); \
    ObjectList_AppendRetained(list, holder.p); }
#define COLUMN_KEY(key, column) { key[0] = column / 10 + '0'; key[1] = column % 10 + '0'; key[2] = 0; }

extern "C" void igObject_Destroy(void *);
extern "C" void *igObject_GetAllocator(...);
extern "C" void *Memory_GetAllocatorBySelector(...);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int beLua__RunNamedChunk(int, const void *, int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, void *, const void *);
extern "C" void beMessenger_SelectGroup(...);
extern "C" void beMessenger_AppendString(...);
extern "C" void beMessenger_AppendInt(...);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_AppendObject(int, void *);
extern "C" void beMessenger_AppendVec3(int, const void *);
extern "C" void beMessenger_DispatchSelected(...);
extern "C" void beMessenger_SendGroup(...);
extern "C" void beMessenger_SendNamed(...);
extern "C" void beMessenger_SendDelayedGroup(int, const void *, const void *, int);
extern "C" void beMessenger_SetFreezeTime(int, int);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_GetString(int, int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" beDataObjInt *igProperty_GetRecord(...);
extern "C" beDataObjBool *igProperty_GetRecordByte(...);
extern "C" beDataObjObjectList *igProperty_GetRecordFolder(int, const void *);
extern "C" beDataObjIntList *igProperty_GetRecordIntList(...);
extern "C" int *beDataBase_GetRecordString(int, int, const void *);
extern "C" int beDataBase_GetRecordInt(...);
extern "C" int List_Resize(void *, int, int);
extern "C" int List_Reserve(...);
extern "C" int ObjectList_FillRetained(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int sprintf(...);
extern "C" int strcat(...);
extern "C" void beNDMWWindow_UpdateTree(int);
extern "C" void beNDMWWindow_BindContext(beNDMWWindow *, int, int, int, int);
extern "C" int SubWnd_GetMetaEnum(void);
extern "C" int StatusMessage_GetMetaEnum(void);
extern "C" beNDMWWindow *beNDMWStatusCtrl00_Create(void *);
extern "C" beNDMWWindow *beNDMWShopCtrl00_Create(void *);
extern "C" beNDMWWindow *beNDMWShopCtrlDigilabo_Create(void *);
extern "C" beNDMWWindow *beNDMWShopCtrlA0_Create(void *);
extern "C" void *beNDMWStatusInfoWork_Create(...);
extern "C" void *beNDMWItemWeapon_Create(...);
extern "C" void *beNDMWItemBlueArmor_Create(...);
extern "C" void *beNDMWItemYellowArmor_Create(...);
extern "C" void *beNDMWItemAbilityChip_Create(...);
extern "C" int beNDMWItemWeapon_SetRandom(...);
extern "C" int beNDMWItemBlueArmor_SetRandom(...);
extern "C" int beNDMWItemYellowArmor_SetRandom(...);
extern "C" int beNDMWItemAbilityChip_Set(...);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int g_beLua_metaObject[4];
extern "C" int g_beNDMWStatusInfo_metaObject[4];
extern "C" int g_beNDMWStatus_metaObject[4];
/* Strings are declared int[4]: an object of 8 bytes or less would be addressed gp-relative, which
 * changes the register allocation of every function here. */

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
struct SalesList { static inline void Reserve(const igObjectList *list) { if (list->_count < 37) List_Reserve(list, 36, 4); } };

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
    return g_beNDMWStatusInfo_metaObject[0];
}

void beNDMWStatus_OnAddRam(beNDMWStatus *self, beNDMWStatusInfoRam *ram) {
    if (((beBaseInfoList *)self->_infoList)->_count == 1) {
        beMessenger_RegisterReceiverFromInfo(self->_messenger, ram, "SUBWND");
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
        beMessenger_SelectGroup(self->_messenger, "STAGECTL");
        beMessenger_AppendString(self->_messenger, "ENABLE");
        beMessenger_DispatchSelected(self->_messenger, "PADINPUT");
        {
        igSmartPointer<beNDMWWindow> window(0);
        switch (self->_subWndNo) {
        case SUBWND_STATUS:
            beMessenger_SelectGroup(self->_messenger, "LAYERCTL");
            beMessenger_AppendString(self->_messenger, "WN01");
            beMessenger_AppendString(self->_messenger, "DISPOFF");
            beMessenger_DispatchSelected(self->_messenger, "SWITCH");
            beMessenger_SelectGroup(self->_messenger, "LAYERCTL");
            beMessenger_AppendString(self->_messenger, "WN00");
            beMessenger_AppendString(self->_messenger, "DISPOFF");
            beMessenger_DispatchSelected(self->_messenger, "SWITCH");
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
            beMessenger_SendGroup(self->_messenger, "SOUND", "BGMSTOP");
            beMessenger_SendGroup(self->_messenger, "SOUND", "ENVSTOP");
            beMessenger_SelectGroup(self->_messenger, "SOUND");
            beMessenger_AppendString(self->_messenger, "RM_NSHOP");
            beMessenger_DispatchSelected(self->_messenger, "PLAY");
        }
        }
        NEXT_STATE(ram)
    case 1:
        if (self->_windowPro != 0) beNDMWWindow_UpdateTree(self->_windowPro);
        if (((beNDMWWindow *)self->_windowPro)->_isRun != 0) return;
        NEXT_STATE(ram)
    default:
        {
            int player;
            RELEASE(beNDMWWindow, (beNDMWWindow *)self->_windowPro)
            self->_windowPro = 0;
            beMessenger_SendGroup(self->_messenger, "SOUND", "OFFREEZE");
            beMessenger_SendGroup(self->_messenger, "GENERATER", "OFFREEZE");
            beMessenger_SendGroup(self->_messenger, "MODELCTRL", "OFFREEZE");
            beMessenger_SetFreezeTime(self->_messenger, 0);
            ram->_isRun = 0;
            player = 0;
            do {
                beMessenger_SelectGroup(self->_messenger, "GAMERAM");
                beMessenger_AppendInt(self->_messenger, player);
                beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
                if (igProperty_GetRecordByte(beMessenger_GetObject(self->_messenger, 0), "ISUSE")->_data != 0) {
                    beMessenger_SelectGroup(self->_messenger, "GAMERAM");
                    beMessenger_AppendInt(self->_messenger, player);
                    beMessenger_AppendInt(self->_messenger, 0);
                    beMessenger_DispatchSelected(self->_messenger, "ADDHP");
                    beMessenger_SelectGroup(self->_messenger, "GAMERAM");
                    beMessenger_AppendInt(self->_messenger, player);
                    beMessenger_AppendInt(self->_messenger, 0);
                    beMessenger_DispatchSelected(self->_messenger, "ADDMP");
                }
                player++;
            } while (player < 4);
            if (self->_subWndNo == SUBWND_CARD) {
                beMessenger_SendGroup(self->_messenger, "STAGECTL", "ISRESETSTART");
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xff) == 0) {
                    beMessenger_SelectGroup(self->_messenger, "PLAYERPOINT");
                    beMessenger_AppendInt(self->_messenger, 4);
                    beMessenger_DispatchSelected(self->_messenger, "SETGENERATEPOS");
                    beMessenger_SelectGroup(self->_messenger, "STAGECTL");
                    beMessenger_AppendString(self->_messenger, "stagML12");
                    beMessenger_DispatchSelected(self->_messenger, "NEXTSTAGE");
                }
            } else {
                beMessenger_SelectGroup(self->_messenger, "LAYERCTL");
                beMessenger_AppendString(self->_messenger, "WN01");
                beMessenger_AppendString(self->_messenger, "DISPON");
                beMessenger_DispatchSelected(self->_messenger, "SWITCH");
                beMessenger_SelectGroup(self->_messenger, "LAYERCTL");
                beMessenger_AppendString(self->_messenger, "WN00");
                beMessenger_AppendString(self->_messenger, "DISPON");
                beMessenger_DispatchSelected(self->_messenger, "SWITCH");
                if (self->_subWndNo != SUBWND_STATUS)
                    beLua__RunNamedChunk(igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]), "shopexit.lua", 0);
            }
        }
    }
}

int beNDMWStatus_OnMessage(beNDMWStatus *self, beNDMWStatusInfoRam *ram, beBaseInfo *info) {
    unsigned int message = beMessenger_ResolveEnumValue(self->_messenger, StatusMessage_GetMetaEnum(), info->_dataList);
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
        beMessenger_AppendBool(self->_messenger, ram->_isRun);
        return 1;
    case MESSAGE_GENERATE:
        if (ram->_isRun == 0) {
            int whoGenerate = beMessenger_GetInt(self->_messenger, 0);
            int subWndName = beMessenger_GetString(self->_messenger, 0);
            unsigned int subWndNo = beMessenger_ResolveEnumValue(self->_messenger, SubWnd_GetMetaEnum(), subWndName);
            ram->_isRun = 1;
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
            self->_subWndNo = subWndNo;
            self->_whoGenerate = whoGenerate;
            beMessenger_SendGroup(self->_messenger, "MODELCTRL", "ONFREEZE");
            beMessenger_SendGroup(self->_messenger, "GENERATER", "ONFREEZE");
            beMessenger_SetFreezeTime(self->_messenger, 1);
            beMessenger_SendGroup(self->_messenger, "SOUND", "ONFREEZE");
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
                beMessenger_SetFreezeTime(self->_messenger, 0);
                beMessenger_SendDelayedGroup(self->_messenger, "SUBWND", "REMOVE", 1);
            }
        }
        return 1;
    case MESSAGE_UPDATE: {
        work = (beNDMWStatusInfoWork *)ram->_work;
        playerNo = beMessenger_GetInt(self->_messenger, 0);
        if (work == 0) {
            beNDMWStatus__PrepareWork(self, ram);
            work = (beNDMWStatusInfoWork *)ram->_work;
        }
        PARAMETERS->_count = 0;
        beMessenger_SelectGroup(self->_messenger, "GAMERAM");
        beMessenger_AppendInt(self->_messenger, playerNo);
        beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
        player = beMessenger_GetObject(self->_messenger, 0);
        igSmartPointer<igObject> name(((igObject **)((igObjectList *)igProperty_GetRecordFolder(player, "PLAYERNAME")->_data)->_data)[0]);
        if (name.p != 0) name.p->_refCount = name.p->_refCount + 1;
        beMessenger_SelectGroup(self->_messenger, "TEXTCTL");
        beMessenger_AppendString(self->_messenger, "STWINFONT02");
        beMessenger_AppendString(self->_messenger, "font000");
        beMessenger_AppendObject(self->_messenger, name.p);
        beMessenger_DispatchSelected(self->_messenger, "TEXTSET");
        level = igProperty_GetRecord(player, "LEVEL")->_data;
        if (level > 999) level = 999;
        sprintf(text, "%d", level);
        SET_TEXT("STWINFONT04", "font000", text)
        beMessenger_SendNamed(self->_messenger, "DATABASE", "shinka", 0, "GETDATABASE");
        {
            int database = beMessenger_GetObject(self->_messenger, 0);
            int *digimonName = beDataBase_GetRecordString(database, igProperty_GetRecord(player, "DIGIMONNO")->_data, "NAME");
            SET_TEXT("STWINFONT04", "font001", digimonName)
        }
        hp = igProperty_GetRecord(player, "HP")->_data;
        sprintf(text, "%d", hp);
        SET_TEXT("STWINFONT06", "font000", text)
        mp = igProperty_GetRecord(player, "MP")->_data;
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
            int exp = igProperty_GetRecord(player, "EXP")->_data;
            int toNext = igProperty_GetRecord(player, "NEXTEXP")->_data - exp;
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
        playerNo = beMessenger_GetInt(self->_messenger, 0);
        float r, g, b;
        beMessenger_SelectGroup(self->_messenger, "GAMERAM");
        beMessenger_AppendInt(self->_messenger, playerNo);
        beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
        player = beMessenger_GetObject(self->_messenger, 0);
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
        playerNo = beMessenger_GetInt(self->_messenger, 0);
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
        beMessenger_SelectGroup(self->_messenger, "GAMERAM");
        beMessenger_AppendInt(self->_messenger, playerNo);
        beMessenger_DispatchSelected(self->_messenger, "GETPLAYER");
        player = beMessenger_GetObject(self->_messenger, 0);
        igProperty_GetRecord(player, "HP")->_data = shownHp;
        igProperty_GetRecord(player, "MP")->_data = shownMp;
        return 1;
    }
    case MESSAGE_GETSHOPDATA: {
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)ram->_work;
        int subWndNo = beMessenger_GetInt(self->_messenger, 0);
        switch (subWndNo) {
        case SUBWND_WPU:
            beMessenger_AppendObject(self->_messenger, (void *)work->_weaponSalesList);
            break;
        case SUBWND_APU:
            beMessenger_AppendObject(self->_messenger, (void *)work->_armorSalesList);
            break;
        case SUBWND_CHIP:
            beMessenger_AppendObject(self->_messenger, (void *)work->_chipSalesList);
            break;
        case SUBWND_JUNK:
            beMessenger_AppendObject(self->_messenger, (void *)work->_junkSalesList);
            beMessenger_AppendInt(self->_messenger, work->_junkGift);
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
        PICK_ALLOCATOR(allocator, kIGMemoryPoolHandleUser1[0])
        igSmartPointer<beNDMWStatusInfoWork> created((beNDMWStatusInfoWork *)beNDMWStatusInfoWork_Create(allocator));
        igObject *retained = created.p;
        if (retained != 0) retained->_refCount = retained->_refCount + 1;
        RELEASE(igObject, (igObject *)ram->_work)
        ram->_work = (int)retained;
        work = (beNDMWStatusInfoWork *)ram->_work;
    }
    partySize = 0;
    playerNo = 0;
    do {
        beMessenger_SelectGroup(owner->_messenger, "GAMERAM");
        beMessenger_AppendInt(owner->_messenger, playerNo);
        beMessenger_DispatchSelected(owner->_messenger, "GETPLAYER");
        player = beMessenger_GetObject(owner->_messenger, 0);
        if (igProperty_GetRecordByte(player, "ISUSE")->_data != 0) {
            partySize += 1;
            if (igProperty_GetRecord(player, "BIT")->_data > 9999999) {
                beDataObjInt *bit = igProperty_GetRecord(player, "BIT");
                bit->_data = 9999999;
            }
            if (igProperty_GetRecord(player, "XDATA")->_data > 9999) {
                beDataObjInt *xdata = igProperty_GetRecord(player, "XDATA");
                xdata->_data = 9999;
            }
        }
        playerNo += 1;
    } while (playerNo < 4);
    beMessenger_SelectGroup(owner->_messenger, "GAMERAM");
    beMessenger_AppendInt(owner->_messenger, 0);
    beMessenger_DispatchSelected(owner->_messenger, "GETPLAYER");
    player = beMessenger_GetObject(owner->_messenger, 0);
    level = igProperty_GetRecord(player, "LEVEL")->_data;
    switch (owner->_subWndNo) {
    case SUBWND_WPU:
        if (SALES_LIST(_weaponSalesList)->_count <= 0) {
            SalesList::Reserve(SALES_LIST(_weaponSalesList));
            ObjectList_FillRetained(SALES_LIST(_weaponSalesList), 0);
            if (partySize > 1) {
                baseRow = 150;
            } else {
                switch (igProperty_GetRecord(player, "DIGIMONNO")->_data) {
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
            beMessenger_SendNamed(owner->_messenger, "DATABASE", "shopWeapon", 0, "GETDATABASE");
            database = beMessenger_GetObject(owner->_messenger, 0);
            weaponRow = baseRow + row;
            weaponColumn = 0;
            do {
                COLUMN_KEY(weaponKey, weaponColumn)
                id = beDataBase_GetRecordInt(database, weaponRow, weaponKey);
                if (id != -1) {
                    STOCK_ITEM(1, weapon, beNDMWItemWeapon_Create, beNDMWItemWeapon_SetRandom, SALES_LIST(_weaponSalesList), id)
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
            ObjectList_FillRetained(SALES_LIST(_armorSalesList), 0);
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
            beMessenger_SendNamed(owner->_messenger, "DATABASE", "shopArmor", 0, "GETDATABASE");
            database = beMessenger_GetObject(owner->_messenger, 0);
            blueColumn = 0;
            do {
                COLUMN_KEY(armorKey, blueColumn)
                id = beDataBase_GetRecordInt(database, row, armorKey);
                STOCK_ITEM(2, blueArmor, beNDMWItemBlueArmor_Create, beNDMWItemBlueArmor_SetRandom, SALES_LIST(_armorSalesList), id)
                blueColumn += 1;
            } while (blueColumn < 12);
            yellowColumn = 12;
            do {
                COLUMN_KEY(armorKey, yellowColumn)
                itemKind = beDataBase_GetRecordInt(database, row, armorKey);
                if (itemKind != -1) {
                    STOCK_ITEM(3, yellowArmor, beNDMWItemYellowArmor_Create, beNDMWItemYellowArmor_SetRandom, SALES_LIST(_armorSalesList), itemKind)
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
            ObjectList_FillRetained(SALES_LIST(_chipSalesList), 0);
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
            beMessenger_SendNamed(owner->_messenger, "DATABASE", "shopChip", 0, "GETDATABASE");
            database = beMessenger_GetObject(owner->_messenger, 0);
            chipColumn = 0;
            do {
                COLUMN_KEY(chipKey, chipColumn)
                id = beDataBase_GetRecordInt(database, chipRow, chipKey);
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
        beMessenger_SendGroup(owner->_messenger, "GAMERAM", "GETCOMMON");
        common = beMessenger_GetObject(owner->_messenger, 0);
        counters = igProperty_GetRecordIntList(common, "COUNTER");
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
            ObjectList_FillRetained(SALES_LIST(_junkSalesList), 0);
            if (junkRow != -1) {
                beMessenger_SendNamed(owner->_messenger, "DATABASE", "shopJunk", 0, "GETDATABASE");
                database = beMessenger_GetObject(owner->_messenger, 0);
                junkColumn = 0;
                do {
                    COLUMN_KEY(junkKey, junkColumn)
                    id = beDataBase_GetRecordInt(database, junkRow, junkKey);
                    if (id != -1) {
                        strcat(junkKey, "kind");
                        itemKind = beDataBase_GetRecordInt(database, junkRow, junkKey);
                        switch (itemKind) {
                        case 0:
                            STOCK_ITEM(1, junkWeapon, beNDMWItemWeapon_Create, beNDMWItemWeapon_SetRandom, SALES_LIST(_junkSalesList), id)
                            break;
                        case 1:
                            STOCK_ITEM(2, junkBlueArmor, beNDMWItemBlueArmor_Create, beNDMWItemBlueArmor_SetRandom, SALES_LIST(_junkSalesList), id)
                            break;
                        case 2:
                            STOCK_ITEM(3, junkYellowArmor, beNDMWItemYellowArmor_Create, beNDMWItemYellowArmor_SetRandom, SALES_LIST(_junkSalesList), id)
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
    return g_beNDMWStatus_metaObject[0];
}

#pragma pop
