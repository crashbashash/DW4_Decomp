#include "dw4/support/reflected.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2ComMdlCtrl.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2DataSelIntf.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2DegiState.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2SelSlot.h"
#include "dw4/game/ndmw/beNDMWLoadSavePlWork.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/be.h"
#include "dw4/game/beBaseInfoDataList.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beFont.h"
#include "dw4/game/ndmw/beLoadIntf2ComMdlData.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWDegiData.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2CommonIntf.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2CtrlData.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2DegiStateCtrl.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2Diffselect.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2Info.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2MakeChr.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2MesWin.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2NameSel.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2TextOrder.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beSystem.h"
#include "dw4/game/beUnicodeObj.h"
#include "dw4/scenegraph/igAnimationCombiner.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include <stdio.h>
#include <string.h>

/* An allocator handle returned by value. */
struct AllocatorValue {
  int allocator;
  AllocatorValue(int value) : allocator(value) {}
  AllocatorValue(const AllocatorValue &o) : allocator(o.allocator) {}
};
extern "C" int beNDMWLoadIntf2__GetInfoMeta(void);
extern "C" int beNDMWLoadIntf2__GetMeta(void);
extern "C" void beNDMWLoadIntf2DegiState__RequestChange(beNDMWLoadIntf2DegiState *self, int kind, int dataNo);
extern "C" void beNDMWLoadIntf2DegiState__DrawStatusText(beNDMWLoadIntf2DegiState *self);
extern "C" void beNDMWLoadIntf2DegiState__ClearStatusText(beNDMWLoadIntf2DegiState *self);




extern "C" void beNDMWLoadIntf2Diffselect__Init(beNDMWLoadIntf2Diffselect *self, int kind, int plNo);
extern "C" unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, unsigned char usePad);
extern "C" void beNDMWLoadIntf2NameSel__Init(beNDMWLoadIntf2NameSel *nameSel, unsigned char resetName);



/* One row of the name-entry letter grid (row = tate, column = yoko): letterCount full-width UTF-16
 * letters. Rows 0-3 are lower case, upper case, digits and symbols, 4-23 hiragana and katakana,
 * 24-27 the Latin rows again and 28-29 accented letters. */
struct NameEntryLetterRow { int letterCount; unsigned short letters[32]; };
extern "C" void beNDMWLoadIntf2NameSel__DrawRowLetters(beNDMWLoadIntf2NameSel *nameSel, int clear);
extern "C" void beNDMWLoadIntf2NameSel__DrawColumnLetters(beNDMWLoadIntf2NameSel *nameSel, int clear);
/* Where the letter cursor stood when a character of the name was entered; erasing the character
 * puts the cursor back there. */
struct NameSelLetterCursor { int tatePoint; int yokoPoint; int yokoCurPos; };
/* The reflected beNDMWLoadIntf2NameSel registers 288 bytes but lists its fields only up to +100;
 * the rest of the object is this name-entry work area. */
struct NameSelWork {
    char reflectedFields[104];
    NameSelLetterCursor enteredAt[8]; /* per character of the name */
    int letterState[9];               /* per character: a NameSelLetterState */
    unsigned short name[9];           /* the typed name, UTF-16, zero-terminated */
    unsigned char unusedFlags[6];     /* cleared with the name; nothing reads them */
};
union NameSelRam { beNDMWLoadIntf2NameSel n; NameSelWork t; };
extern "C" void beNDMWLoadIntf2NameSel__DrawEnteredName(NameSelRam *nameSel, int clear);
extern "C" void beNDMWLoadIntf2NameSel__SetAnswer(beNDMWLoadIntf2NameSel *nameSel, char isNameOK);
extern "C" int beNDMWLoadIntf2NameSel__Update(NameSelRam *nameSel, int usePad);
/* One entry of the slot screen: the slot-cursor sequence that points at it (SQ_SELECT..) and its
 * index in beNDMWMcUtilCtrl::_slot. g_slotMarkSelectSeqs lists the multitap layout (ports 1A-1D,
 * then slot 2), g_slotModeSelectSeqs the two-slot layout. */
struct SlotCursorEntry { const char *sequence; int mcSlot; };
#pragma push
#pragma readonly_strings on

extern "C" {
const char *g_saveAreaWindowNames[4] = { "j_saveareawin01", "j_saveareawin02", "j_saveareawin03", "j_saveareawin04" };
const char *g_saveAreaLineSelectSeqs[4] = { "SQ_LINESL00", "SQ_LINESL01", "SQ_LINESL02", "SQ_LINESL03" };
const char *g_saveAreaLineOnSeqs[4] = { "SQ_LINEON00", "SQ_LINEON01", "SQ_LINEON02", "SQ_LINEON03" };
NameEntryLetterRow g_nameEntryLetterRows[30] = {
    {26, {0xFF41, 0xFF42, 0xFF43, 0xFF44, 0xFF45, 0xFF46, 0xFF47, 0xFF48, 0xFF49, 0xFF4A, 0xFF4B, 0xFF4C, 0xFF4D, 0xFF4E, 0xFF4F, 0xFF50, 0xFF51, 0xFF52, 0xFF53, 0xFF54, 0xFF55, 0xFF56, 0xFF57, 0xFF58, 0xFF59, 0xFF5A}},
    {26, {0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 0xFF38, 0xFF39, 0xFF3A}},
    {10, {0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15, 0xFF16, 0xFF17, 0xFF18, 0xFF19}},
    {7, {0xFF06, 0xFF01, 0xFF1F, 0xFF5E, 0x30FC, 0x30FB, 0xFF1A}},
    {10, {0x3042, 0x3044, 0x3046, 0x3048, 0x304A, 0x3041, 0x3043, 0x3045, 0x3047, 0x3049}},
    {10, {0x304B, 0x304D, 0x304F, 0x3051, 0x3053, 0x304C, 0x304E, 0x3050, 0x3052, 0x3054}},
    {10, {0x3055, 0x3057, 0x3059, 0x305B, 0x305D, 0x3056, 0x3058, 0x305A, 0x305C, 0x305E}},
    {12, {0x305F, 0x3061, 0x3064, 0x3066, 0x3068, 0x3063, 0x3060, 0x3062, 0x3065, 0x3067, 0x3069, 0x3063}},
    {5, {0x306A, 0x306B, 0x306C, 0x306D, 0x306E}},
    {15, {0x306F, 0x3072, 0x3075, 0x3078, 0x307B, 0x3070, 0x3073, 0x3076, 0x3079, 0x307C, 0x3071, 0x3074, 0x3077, 0x307A, 0x307D}},
    {5, {0x307E, 0x307F, 0x3080, 0x3081, 0x3082}},
    {6, {0x3084, 0x3086, 0x3088, 0x3083, 0x3085, 0x3087}},
    {5, {0x3089, 0x308A, 0x308B, 0x308C, 0x308D}},
    {5, {0x308F, 0x3092, 0x3093, 0x3000, 0x3000}},
    {10, {0x30A2, 0x30A4, 0x30A6, 0x30A8, 0x30AA, 0x30A1, 0x30A3, 0x30A5, 0x30A7, 0x30A9}},
    {10, {0x30AB, 0x30AD, 0x30AF, 0x30B1, 0x30B3, 0x30AC, 0x30AE, 0x30B0, 0x30B2, 0x30B4}},
    {10, {0x30B5, 0x30B7, 0x30B9, 0x30BB, 0x30BD, 0x30B6, 0x30B8, 0x30BA, 0x30BC, 0x30BE}},
    {12, {0x30BF, 0x30C1, 0x30C4, 0x30C6, 0x30C8, 0x30C3, 0x30C0, 0x30C2, 0x30C5, 0x30C7, 0x30C9, 0x30C3}},
    {5, {0x30CA, 0x30CB, 0x30CC, 0x30CD, 0x30CE}},
    {15, {0x30CF, 0x30D2, 0x30D5, 0x30D8, 0x30DB, 0x30D0, 0x30D3, 0x30D6, 0x30D9, 0x30DC, 0x30D1, 0x30D4, 0x30D7, 0x30DA, 0x30DD}},
    {5, {0x30DE, 0x30DF, 0x30E0, 0x30E1, 0x30E2}},
    {6, {0x30E4, 0x30E6, 0x30E8, 0x30E3, 0x30E5, 0x30E7}},
    {5, {0x30E9, 0x30EA, 0x30EB, 0x30EC, 0x30ED}},
    {5, {0x30EF, 0x30F2, 0x30F3, 0x3000, 0x3000}},
    {26, {0xFF41, 0xFF42, 0xFF43, 0xFF44, 0xFF45, 0xFF46, 0xFF47, 0xFF48, 0xFF49, 0xFF4A, 0xFF4B, 0xFF4C, 0xFF4D, 0xFF4E, 0xFF4F, 0xFF50, 0xFF51, 0xFF52, 0xFF53, 0xFF54, 0xFF55, 0xFF56, 0xFF57, 0xFF58, 0xFF59, 0xFF5A}},
    {26, {0xFF21, 0xFF22, 0xFF23, 0xFF24, 0xFF25, 0xFF26, 0xFF27, 0xFF28, 0xFF29, 0xFF2A, 0xFF2B, 0xFF2C, 0xFF2D, 0xFF2E, 0xFF2F, 0xFF30, 0xFF31, 0xFF32, 0xFF33, 0xFF34, 0xFF35, 0xFF36, 0xFF37, 0xFF38, 0xFF39, 0xFF3A}},
    {10, {0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14, 0xFF15, 0xFF16, 0xFF17, 0xFF18, 0xFF19}},
    {7, {0xFF06, 0xFF01, 0xFF1F, 0xFF5E, 0x30FC, 0x30FB, 0xFF1A}},
    {28, {0x00A1, 0x00A3, 0x00A7, 0x00B5, 0x00BF, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00D1, 0x00D5, 0x00D6, 0x00D8, 0x00DC, 0x00DF, 0x00E0, 0x00E2, 0x00E3, 0x00E4, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00EE, 0x00EF}},
    {28, {0x00F1, 0x00F2, 0x00F4, 0x00F5, 0x00F6, 0x00F9, 0x00FB, 0x00FC, 0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00C2, 0x00CA, 0x00D4, 0x00CD, 0x00CF, 0x00C1, 0x00C9, 0x00CD, 0x00D3, 0x00DA, 0x00C0, 0x00C8, 0x00CC, 0x00D2, 0x00D9, 0x00B0}}
};
SlotCursorEntry g_slotMarkSelectSeqs[5] = { {"SQ_SELECT1A", 0}, {"SQ_SELECT1B", 2}, {"SQ_SELECT1C", 3}, {"SQ_SELECT1D", 4}, {"SQ_SELECT02", 1} };
SlotCursorEntry g_slotModeSelectSeqs[2] = { {"SQ_SELECT01", 0}, {"SQ_SELECT02", 1} };
float g_interfaceKindPositions[4][3] = {
    {-315.0f, 240.0f, 0.0f},
    {-5.0f, 240.0f, 0.0f},
    {-315.0f, 20.0f, 0.0f},
    {-5.0f, 20.0f, 0.0f}
};
const char *g_starterSelectModelNames[4] = { "h_agumon", "h_vmon", "h_girumon", "h_dorumon" };
const char *g_starterPlayerModelNames[4] = { "p_agumon", "p_vmon", "p_girumon", "p_dorumon" };
}
extern "C" unsigned char beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, const char *infoName, const char *sqName);
extern "C" void beNDMWLoadIntf2_Prepare(beNDMWLoadIntf2 *self);
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
extern "C" int beNDMWLoadIntf2_beNDMWDegiDataList_Get(igDataList *list, int index);
extern "C" void beNDMWLoadIntf2_OnAddRam(beNDMWLoadIntf2 *self, beBaseInfoRam *ram);

/* The request a beNDMWLoadIntf2DegiState is carrying out (_st0). */
enum DegiStateRequest {
    DEGI_STATE_IDLE = 0,
    DEGI_STATE_OPEN = 1,
    DEGI_STATE_CLOSE = 2,
    DEGI_STATE_CHANGE = 3
};

static inline void EnterDegiState(beNDMWLoadIntf2DegiState *self, int request) {
    self->_st0 = request;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
}

static inline void NextDegiStep(beNDMWLoadIntf2DegiState *self) {
    self->_st1 = self->_st1 + 1;
    self->_st3 = 0;
    self->_st2 = 0;
}

/* The Digimon record the state shows: kind 0 is save area _dataNo of the player's memory-card
 * slot, any other kind the player's in-game record. */
static inline beNDMWDegiData *ShownDegiData(beNDMWLoadIntf2DegiState *self, beNDMWLoadCtrl2CommonIntf *common) {
    if (self->_kind == 0) {
        beNDMWLoadSavePlWork *work = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)common->_flagWork)->_data)[self->_plNo];
        beNDMWLoadSlotPlayer *slot = (beNDMWLoadSlotPlayer *)work->_haveSaveData;
        return ((beNDMWDegiData **)((beNDMWDegiDataList *)slot->_saveDataList)->_data)[self->_dataNo];
    }
    return ((beNDMWDegiData **)((beNDMWDegiDataList *)common->_gameUseData)->_data)[self->_plNo];
}

/* Stores in *index the row of g_playerModelRow whose model is the record's kind; leaves *index
 * alone when no row is. */
static inline void FindPlayerModel(beNDMWDegiData *data, int *index) {
    int row = 0;
    PlayerModelRow *entry = g_playerModelRow;
    do {
        if (strcmp(entry->model, (const char *)data->_dmkind) == 0) {
            *index = row;
            break;
        }
        row += 1;
        entry += 1;
    } while (row < 16);
}

/* Records whether the shown record is in use (_isUseData). */
static inline void NoteUseData(beNDMWLoadIntf2DegiState *self, beNDMWDegiData *data) {
    if (data->_isUse == 1) {
        self->_isUseData = 1;
    } else {
        self->_isUseData = 0;
    }
}

/* Writes the record's name (the text after the leading marker unit of _dmNameUni, at most eight
 * characters) into status text slot nameSlot. */
static inline void DrawName(beNDMWLoadIntf2DegiState *self, beNDMWDegiData *data, int nameSlot) {
    int allocator = (int)igObject_GetAllocator(self);
    igSmartPointer<beUnicodeObj> text(beUnicodeObj_Create(g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1)));
    beUnicodeObj_AllocateBuffer(text.p, 8);
    unsigned short *dst = (unsigned short *)text.p->_buffer;
    const unsigned short *name = data->_dmNameUni;
    int i = 0;
    do {
        dst[i] = name[i + 1];
        if (dst[i] == 0) break;
        i += 1;
    } while (i < 8);
    for (; i < 8; i++) {
        dst[i] = 0;
    }
    TextOrder_ConfigureUnicode((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT03", self->_plNo, nameSlot, text.p, 0, 0);
}

/* Writes the database name of the record's Digimon kind into status text slot kindSlot. */
static inline void DrawKindName(beNDMWLoadIntf2DegiState *self, beNDMWDegiData *data, int kindSlot) {
    int modelIndex;
    int database;
    beMessenger_SendNamed((beMessenger *)self->_messenger, "DATABASE", "shinka", 0, "GETDATABASE");
    database = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
    FindPlayerModel(data, &modelIndex);
    TextOrder_ConfigureFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT04", self->_plNo, kindSlot, beDataBase_GetRecordString((beDataBase *)database, modelIndex, "NAME"), 0, 0);
}

/* Writes the record's level, HP/max HP and MP/max MP as numbers into their status text slots. */
static inline void DrawStats(beNDMWLoadIntf2DegiState *self, beNDMWDegiData *data, int levelSlot, int hpSlot, int maxHpSlot, int mpSlot, int maxMpSlot) {
    char number[32];
    sprintf(number, "%d", data->_lv);
    TextOrder_ConfigureFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT04", self->_plNo, levelSlot, number, 1, 0);
    sprintf(number, "%d", data->_hp);
    TextOrder_ConfigureFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, hpSlot, number, 2, 0);
    sprintf(number, "%d", data->_maxHp);
    TextOrder_ConfigureFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, maxHpSlot, number, 2, 0);
    sprintf(number, "%d", data->_mp);
    TextOrder_ConfigureFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, mpSlot, number, 2, 0);
    sprintf(number, "%d", data->_maxMp);
    TextOrder_ConfigureFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, maxMpSlot, number, 2, 0);
}

/* Opens a window of the player's face/status model at the model controller's position. */
static inline void OpenWindow(beNDMWLoadIntf2DegiState *self, const void *window, const void *openSequence) {
    beNDMWLoadIntf2ComMdlCtrl *ctrl = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    float pos[3];
    pos[0] = ctrl->_pos[0];
    pos[1] = ctrl->_pos[1];
    pos[2] = ctrl->_pos[2];
    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_plNo, (const char *)window, (const char *)openSequence, pos, 1);
}

static inline void PlayWindow(beNDMWLoadIntf2DegiState *self, const void *window, const void *sequence) {
    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_plNo, (int *)window, (int *)sequence, 0);
}

static inline void CloseWindow(beNDMWLoadIntf2DegiState *self, const void *window, const void *closeSequence) {
    beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_plNo, (const char *)window, (const char *)closeSequence, 1);
}

void beNDMWLoadIntf2DegiState__Init(beNDMWLoadIntf2DegiState *self, int plNo, int commonIntf, int textOrder, int comMdlCtrl, int messenger, int dispPos) {
    self->_comMdlCtrl = comMdlCtrl;
    self->_commonIntf = commonIntf;
    self->_textOrder = textOrder;
    self->_plNo = plNo;
    self->_messenger = messenger;
    self->_dispPos = dispPos;
    self->_isEnd = 0;
    EnterDegiState(self, DEGI_STATE_IDLE);
}

#include "dw4/maths/igVec3f.h"
/* kept local: igDataList_GetCount has no include/dw4 home (only BaseLibrary.h declares it). */
/* Owning reference to a newly created data list, built from the allocator handle passed by value;
 * its out-of-line destructor releases it once beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign has taken its own reference. */
class NewDataListRef {
public:
  void *value;
  NewDataListRef(const AllocatorValue &source) : value((void *)beBaseInfoDataList_Create(source.allocator)) {}
  ~NewDataListRef();
};
/* Gives an empty info-record reference (host->_dataList) a fresh data list. */
struct FreshDataList {
  static ObjectRefTarget **Assign(void *slot, int allocator) {
    NewDataListRef created(
        beNDMWLoadIntf2_beBaseInfoDataList_MakeAllocatorValue(beNDMWLoadIntf2_Memory_SelectAllocator(&kIGMemoryPoolHandleUser1, allocator)));
    return beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign((ObjectRefTarget **)slot, (ObjectRefTarget **)&created);
  }
};
/* Stack reference to a Digimon record while it is stored into the in-game data list: optionally
 * retains it on construction and releases it on scope exit. */
class DegiDataRef {
public:
  void *value;
  DegiDataRef(void *data) : value(data) {}
  DegiDataRef(void *data, bool retain) : value(data) {
    if (retain)
      beNDMWLoadIntf2_igObject_Retain((ObjectRefTarget *)value);
  }
  ~DegiDataRef() { igRelease((igObject *)value); }
};
/* Pad bits as read from bePadData::_trigger/_repeat (the PS2 libpad button layout). Cross confirms
 * and Circle cancels in the slot/portrait/difficulty screens. The stick bits of _lTrg/_lRpt are
 * paired with the D-pad bit of the same direction in every test below, so they are named by
 * direction. */
enum LoadPadMask {
  kPadStart = 0x0008,
  kPadUp = 0x0010,
  kPadRight = 0x0020,
  kPadDown = 0x0040,
  kPadLeft = 0x0080,
  kPadCircle = 0x2000,
  kPadCross = 0x4000
};
enum LoadStickMask {
  kStickUp = 0x1,
  kStickRight = 0x2,
  kStickDown = 0x4,
  kStickLeft = 0x8
};
/* beNDMWLoadIntf2CtrlData::_st0: the screen a player is on. */
enum LoadScreen {
  LOAD_SCREEN_OPEN = 0,
  LOAD_SCREEN_WAIT_PAD = 1,
  LOAD_SCREEN_JOIN = 2,
  LOAD_SCREEN_NEW_OR_LOAD = 3,
  LOAD_SCREEN_CHOOSE_DIGIMON = 4,
  LOAD_SCREEN_NAME = 5,
  LOAD_SCREEN_SLOT = 6,
  LOAD_SCREEN_SAVE_DATA = 7,
  LOAD_SCREEN_START = 8
};
/* beNDMWLoadSavePlWork::_sysStat0: what a player's work record is doing. */
enum LoadPlayerStage {
  LOAD_STAGE_SCREENS = 0,
  LOAD_STAGE_SYSTEM_MESSAGE = 1,
  LOAD_STAGE_CLOSE = 2,
  LOAD_STAGE_CARD_UTIL = 5,
  LOAD_STAGE_UTIL_ERROR = 6,
  LOAD_STAGE_UTIL_DONE = 7,
  LOAD_STAGE_RESUME = 8
};
/* beNDMWLoadSavePlWork::_sysStat1 in LOAD_STAGE_CARD_UTIL: the memory-card step being run. */
enum LoadCardStep {
  CARD_STEP_CHECK = 0,
  CARD_STEP_ASK_CREATE = 1,
  CARD_STEP_CREATE = 2,
  CARD_STEP_ASK_FORMAT = 3,
  CARD_STEP_FORMAT = 4,
  CARD_STEP_ATTACH = 5,
  CARD_STEP_READ = 6
};
/* The step of the save-data screen that leaves it after the memory card was pulled out (_isCutConnect):
 * the player's Digimon record is replaced by a fresh one and the slot screen reopens. */
enum { SAVE_DATA_STEP_CARD_PULLED = 100 };
/* Step bookkeeping for the CtrlData record: _st0 is the screen state, _st1 the step inside it,
 * _st2 and _st3 finer sub-steps. Moving to a new level always clears the levels below it, in the
 * order _st3, _st2, _st1. */
static inline void EnterState(beNDMWLoadIntf2CtrlData *c, int n) { c->_st0 = n; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
static inline void NextStep(beNDMWLoadIntf2CtrlData *c) { c->_st1 = c->_st1 + 1; c->_st3 = 0; c->_st2 = 0; }
static inline void SetStep(beNDMWLoadIntf2CtrlData *c, int n) { c->_st1 = n; c->_st3 = 0; c->_st2 = 0; }
static inline void NextSubstep(beNDMWLoadIntf2CtrlData *c) { c->_st2 = c->_st2 + 1; c->_st3 = 0; }
static inline void NextTick(beNDMWLoadIntf2CtrlData *c) { c->_st3 = c->_st3 + 1; }
static inline void RestartSubstep(beNDMWLoadIntf2CtrlData *c) { c->_st2 = 0; c->_st3 = 0; }
/* The same bookkeeping on the SelSlot record. */
static inline void EnterSlotState(beNDMWLoadIntf2SelSlot *c, int n) { c->_st0 = n; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
/* The same bookkeeping on the per-player beNDMWLoadSavePlWork (_sysStat0.._sysStat3). */
static inline void SetPlayerStep(beNDMWLoadSavePlWork *w, int n) { w->_sysStat1 = n; w->_sysStat3 = 0; w->_sysStat2 = 0; }
static inline void NextPlayerStep(beNDMWLoadSavePlWork *w) { w->_sysStat1 = w->_sysStat1 + 1; w->_sysStat3 = 0; w->_sysStat2 = 0; }
/* matching construct: the substep is read through PlayerSubstep so the increment reloads it instead
 * of reusing the value the enclosing switch tested. */
static inline int PlayerSubstep(const beNDMWLoadSavePlWork *w) { return w->_sysStat2; }
static inline void NextPlayerSubstep(beNDMWLoadSavePlWork *w) { w->_sysStat2 = PlayerSubstep(w) + 1; w->_sysStat3 = 0; }
static inline void EnterPlayerStage(beNDMWLoadSavePlWork *w, int n) { w->_sysStat0 = n; w->_sysStat3 = 0; w->_sysStat2 = 0; w->_sysStat1 = 0; }
/* Message/text-order ids: the player number (_ramNo) in the high half and the message token in the
 * low bits (a control id is (high << 16) | token). */
static inline int TextId(beBaseInfoRam *h, int token) { return (h->_ramNo << 0x10) | token; }
/* The message for the console's save hardware: _kindHard 0, 1 or 2 selects the 0x1000, 0x2000 or
 * 0x3000 text bank (the player number in the high half as in TextId); -1 for any other kind. */
static inline int HardwareTextId(beNDMWLoadCtrl2CommonIntf *common, beBaseInfoRam *host, int bank0Token, int bank1Token, int bank2Token) {
  int textId = -1;
  switch (common->_kindHard) {
  case 0:
    textId = (host->_ramNo << 0x10) | bank0Token;
    break;
  case 1:
    textId = (host->_ramNo << 0x10) | bank1Token;
    break;
  case 2:
    textId = (host->_ramNo << 0x10) | bank2Token;
    break;
  }
  return textId;
}
/* Shows the starter's name: its row in the "shinka" database is the row of g_playerModelRow whose
 * model is the starter's player model. */
static inline void ShowStarterName(beNDMWLoadIntf2 *self, beNDMWLoadIntf2TextOrder *textOrder,
    beBaseInfoRam *host, beNDMWLoadIntf2MakeChr *creation) {
  int database;
  int row;
  int index;
  const PlayerModelRow *entry;
  beMessenger_SendNamed((beMessenger *)self->_messenger, "DATABASE", "shinka", 0, "GETDATABASE");
  database = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
  for (index = 0, entry = g_playerModelRow; index < 16; index++, entry++) {
    if (strcmp(entry->model, g_starterPlayerModelNames[creation->_chaSelDegi]) == 0) {
      row = index;
      break;
    }
  }
  TextOrder_ConfigureFont(textOrder, "CHRSELFONT14", host->_ramNo, 0, beDataBase_GetRecordString((beDataBase *)database, row, "NAME"), 1, 0);
}
/* Plays the exit of the starter's select-screen model if it is shown and running. */
static inline void ExitStarterModel(beNDMWLoadIntf2 *self, beBaseInfoRam *host,
    beNDMWLoadIntf2CtrlData *control, beNDMWLoadIntf2MakeChr *creation) {
  if (control->_isNoSelMdl == 0) {
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", g_starterSelectModelNames[creation->_chaSelDegi], host->_ramNo, "ISRUN");
    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) {
      beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", g_starterSelectModelNames[creation->_chaSelDegi], host->_ramNo, "SQ_EXIT");
    }
  }
}
/* The first entry of the Digimon status list. */
static inline beNDMWLoadIntf2DegiState *FirstDegiState(beNDMWLoadIntf2DegiStateCtrl *status) {
  return (beNDMWLoadIntf2DegiState *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)status->_statDataList, 0);
}
/* Sends a GAMERAM request about this player (the player number is its only argument). */
static inline void RequestGameRam(beNDMWLoadIntf2 *self, beBaseInfoRam *host, const void *request) {
  beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
  beMessenger_AppendInt((beMessenger *)self->_messenger, host->_ramNo);
  beMessenger_DispatchSelected((beMessenger *)self->_messenger, (const char *)request);
}
/* Opens the first Digimon status entry on a kind and the player's data number. */
static inline void OpenDegiState(beNDMWLoadIntf2DegiStateCtrl *status, int kind, int player) {
  beNDMWLoadIntf2DegiState__RequestOpen(FirstDegiState(status), kind, player);
}
/* A player's work record in _flagWork. */
static inline beNDMWLoadSavePlWork *WorkAt(beNDMWLoadCtrl2CommonIntf *common, int player) {
  return (beNDMWLoadSavePlWork *)beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get((igDataList *)common->_flagWork, player);
}
/* The player's Digimon record in the in-game data list (_gameUseData). */
static inline beNDMWDegiData *PlayerDegiData(beNDMWLoadCtrl2CommonIntf *common, beBaseInfoRam *host) {
  return (beNDMWDegiData *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)common->_gameUseData, host->_ramNo);
}
/* The per-card slot-player list held by the _slotSaveData reference. */
static inline beNDMWLoadSlotPlayerList *SlotSaveData(beNDMWLoadCtrl2CommonIntf *common) {
  return *(beNDMWLoadSlotPlayerList **)&common->_slotSaveData;
}
static inline int IntListCount(const igIntList *list) { return list->_count; }
/* The save data the player picked: entry saveIndex of the save-data list of the slot player held by
 * the player's work record. */
static inline void *PlayerSaveData(beNDMWLoadCtrl2CommonIntf *common, int player, int saveIndex) {
  beNDMWLoadSavePlWork *work =
      (beNDMWLoadSavePlWork *)beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get((igDataList *)common->_flagWork, player);
  return (void *)beNDMWLoadIntf2_beNDMWDegiDataList_Get((igDataList *)(((beNDMWLoadSlotPlayer *)work->_haveSaveData)->_saveDataList), saveIndex);
}
/* The host player's work record in _flagWork (as an object-list entry). */
static inline beNDMWLoadSavePlWork *HostWork(beNDMWLoadCtrl2CommonIntf *common, beBaseInfoRam *host) {
  int player = host->_ramNo;
  return (beNDMWLoadSavePlWork *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)common->_flagWork, player);
}
static inline beNDMWMcUtilCtrl *McUtil(beNDMWLoadCtrl2CommonIntf *common) {
  return (beNDMWMcUtilCtrl *)common->_mcUtilCtrl;
}
/* The host player's pad, looked up through the insight's pad manager. */
static inline bePadData *HostPad(beNDMWLoadIntf2 *self, beBaseInfoRam *host) {
  igObject *manager = igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
  return (bePadData *)bePadManager_GetPadForPlayer((bePadManager *)manager, host->_ramNo);
}
/* The object's own allocator when g_useOwnerAllocator is set, else the selected one. */
static inline int SelectAllocator(const igMemoryPoolHandle *selector, int ownAllocator) {
  if (g_useOwnerAllocator)
    return ownAllocator;
  else
    return (int)Memory_GetAllocatorBySelector(*selector);
}
/* The first boolean reply of the last messenger request, or 0 when there is none. */
static inline unsigned char FirstBoolReply(beNDMWLoadIntf2 *self) {
  if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) > 0)
    return beMessenger_GetBool((beMessenger *)self->_messenger, 0);
  else
    return 0;
}
/* The name-entry object past its reflected fields (+100): the per-row cursor save area, then the
 * name typed so far (UTF-16, up to 8 characters and a terminator) at +236. */
struct NameSelTypedName {
  char reflectedAndCursors[236];
  unsigned short name[9];
};
/* Copies the typed name into the new name object's 8-character buffer, zero-padding the rest. */
static inline void CopyTypedName(unsigned short *destination, beNDMWLoadIntf2NameSel *nameEntry) {
  NameSelTypedName *typed = (NameSelTypedName *)nameEntry;
  int count;
  for (count = 0; count < 8; count++) {
    destination[count] = typed->name[count];
    if (typed->name[count] == 0)
      break;
  }
  for (; count < 8; ++count)
    destination[count] = 0;
}
/* One named object of the player's working set (host->_dataList). */
static inline void *FindWorkObject(beBaseInfoRam *host, const void *name) {
  return beNDMWLoadIntf2_beBaseInfoDataList_FindProperty(beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Deref(&host->_dataList), (int)g_propertyNameField, name);
}
/* The memory-card slot picked on the slot screen. */
static inline beNDMWMcSlot *SelectedCardSlot(beNDMWLoadCtrl2CommonIntf *common, beNDMWLoadIntf2SelSlot *slots) {
  return (beNDMWMcSlot *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)McUtil(common)->_slot, slots->_mcSelPoint);
}
/* Allows or blocks the console reset around a memory-card operation (the soft reset only when not
 * reached from the title). */
static inline void SetResetEnable(beNDMWLoadIntf2 *self, beNDMWLoadCtrl2CommonIntf *common, unsigned char enable) {
  if (common->_isTitle == 0) {
    ((beSystem *)self->_system_)->_isSResetEnable = enable;
  }
  ((beSystem *)self->_system_)->_isResetEnable = enable;
}
/* Whether every player who has entered is also ready. */
static inline int AllEntriesReady(beNDMWLoadCtrl2CommonIntf *common) {
  void *works = (void *)common->_flagWork;
  int entryCount = 0;
  int readyCount = 0;
  int index;
  for (index = 0; index < igDataList_GetCount((igDataList *)works); index++) {
    if (beNDMWLoadSavePlWork__GetIsEntry((beNDMWLoadSavePlWork *)beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get((igDataList *)works, index)) == 1) {
      entryCount += 1;
    }
    if (beNDMWLoadSavePlWork__GetIsRdy((beNDMWLoadSavePlWork *)beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get((igDataList *)works, index)) == 1) {
      readyCount += 1;
    }
  }
  return entryCount == readyCount;
}
/* Ends the interface (_intfStat 3) and takes the pad away from every player. */
static inline void EndInterface(beNDMWLoadCtrl2CommonIntf *common) {
  void *works;
  int index = 0;
  common->_intfStat = 3;
  works = (void *)common->_flagWork;
  for (; index < igDataList_GetCount((igDataList *)works); index++) {
    beNDMWLoadSavePlWork__SetIsCtrl((beNDMWLoadSavePlWork *)beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get((igDataList *)works, index), 0);
  }
}
/* Per-frame master update of the Game Start interface for one player (`host`): looks up the named
 * working set under host->_dataList ("COMMONINTF", "CTRL", "MAKECHR", ...), samples that player's pad,
 * and advances the player's stage (_sysStat0: screens, system message, close, card utility, utility
 * error, utility done, resume) and, while the screens run, the CtrlData screen state machine (open,
 * wait for a pad, join, new or load, Digimon choice, name, slot, save data, start). */
extern "C" void beNDMWLoadIntf2_UpdateRam(beNDMWLoadIntf2 *self, beBaseInfoRam *host) {
  /* These locals keep the original declaration order, which decides their register and stack
   * assignment; moving most of them to their first use or into the scope that uses them changes
   * the allocation. */
  igVec3f previewPosition;
  igVec3f previewRotation;
  igVec3f retryPosition;
  igVec3f retryRotation;
  beNDMWLoadIntf2TextOrder *textOrder;
  beNDMWLoadIntf2DegiStateCtrl *status;
  beNDMWLoadIntf2DataSelIntf *dataSelection;
  beNDMWLoadIntf2Diffselect *difficulty;
  int padTrigger;
  unsigned char moveUp;
  unsigned char moveDown;
  unsigned char moveLeft;
  unsigned char moveRight;
  unsigned char countdownExpired;
  int padRepeat;
  beNDMWLoadSavePlWork *resultWork;
  int accessCount;
  int accessPlayer;
  int listIndex;
  beNDMWLoadCtrl2CommonIntf *common;
  beNDMWLoadIntf2CtrlData *control;
  beNDMWLoadIntf2ComMdlCtrl *models;
  igIntList *accessList;
  beNDMWLoadIntf2MesWin *messages;
  beNDMWLoadIntf2SelSlot *slots;
  beNDMWLoadIntf2MakeChr *creation;
  beNDMWLoadIntf2NameSel *nameEntry;

  if (host->_dataList == 0)
    return;
  /* matching construct: each lookup repeats the empty-reference check here; moving it into an
   * inline helper changes the exception cleanup emitted for FreshDataList::Assign's temporary. */
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  common = (beNDMWLoadCtrl2CommonIntf *)FindWorkObject(host, "COMMONINTF");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  control = (beNDMWLoadIntf2CtrlData *)FindWorkObject(host, "CTRL");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  creation = (beNDMWLoadIntf2MakeChr *)FindWorkObject(host, "MAKECHR");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  models = (beNDMWLoadIntf2ComMdlCtrl *)FindWorkObject(host, "COMMDLCTRL");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  messages = (beNDMWLoadIntf2MesWin *)FindWorkObject(host, "MESWIN");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  slots = (beNDMWLoadIntf2SelSlot *)FindWorkObject(host, "SELSLOT");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  nameEntry = (beNDMWLoadIntf2NameSel *)FindWorkObject(host, "NAMESEL");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  textOrder = (beNDMWLoadIntf2TextOrder *)FindWorkObject(host, "TEXTORDER");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  status = (beNDMWLoadIntf2DegiStateCtrl *)FindWorkObject(host, "DEGISTATECTRL");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  dataSelection = (beNDMWLoadIntf2DataSelIntf *)FindWorkObject(host, "DATASELINTF");
  if (beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(&host->_dataList) == 0) {
    FreshDataList::Assign(&host->_dataList, (int)igObject_GetAllocator(host));
  }
  difficulty = (beNDMWLoadIntf2Diffselect *)FindWorkObject(host, "DIFFSELECT");
  beNDMWLoadIntf2ComMdlCtrl__Poll(models);
  beNDMWLoadIntf2MesWin__Update(messages);
  /* This frame's input for the player: pad trigger/repeat bits plus the
   * four direction flags (D-pad or left stick); only read while the
   * player's work has _isCtrl. */
  padTrigger = 0;
  moveUp = 0;
  moveDown = 0;
  moveLeft = 0;
  moveRight = 0;
  if (HostWork(common, host)->_isCtrl == 1) {
    bePadData *pad = (bePadData *)bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, host->_ramNo);
    padTrigger = pad->_trigger;
    padRepeat = pad->_repeat;
    int stickEdge = pad->_lTrg | pad->_lRpt;
    /* matching construct: up starts held and only the final else clears it; the direct ||
     * spelling used for the other directions emits a different branch shape here. */
    bool upHeld = 1;
    if (stickEdge & kStickUp) {
    } else if ((padTrigger | padRepeat) & kPadUp) {
    } else {
      upHeld = 0;
    }
    moveUp = upHeld;
    moveDown = ((stickEdge & kStickDown) != 0) || (((padTrigger | padRepeat) & kPadDown) != 0);
    moveLeft = ((stickEdge & kStickLeft) != 0) || (((padTrigger | padRepeat) & kPadLeft) != 0);
    moveRight = ((stickEdge & kStickRight) != 0) || (((padTrigger | padRepeat) & kPadRight) != 0);
  }
  if (control->_isSystem != 0)
    return;
  switch (HostWork(common, host)->_sysStat0) {
  /* Stage 1: the normal flow. sysStat1 step 0 shows text 0x51C and moves to
   * step 1 (or drops the work back to stage 0 while screen 2 is showing);
   * step 1 counts _sysCount0 down and skips the screens for that frame once
   * it expires; otherwise the CtrlData screen state machine below runs. */
  case LOAD_STAGE_SYSTEM_MESSAGE:
    countdownExpired = 0;
    switch (HostWork(common, host)->_sysStat1) {
    case 0:
      if (control->_st0 == LOAD_SCREEN_JOIN) {
        EnterPlayerStage(WorkAt(common, host->_ramNo), LOAD_STAGE_SCREENS);
      } else {
        beNDMWLoadIntf2MesWin__RequestSystemMessage(messages, TextId(host, 0x51C));
        SetPlayerStep(WorkAt(common, host->_ramNo), 1);
      }
      break;
    case 1:
      beNDMWLoadSavePlWork *countdownWork = HostWork(common, host);
      int countdown = countdownWork->_sysCount0 - 1;
      countdownWork->_sysCount0 = countdown;
      if (countdown <= 0) {
        HostWork(common, host)->_sysCount0 = 0;
        countdownExpired = 1;
      }
      break;
    }
    if (countdownExpired == 1)
      break;
    /* The screens keep running under the system message. */
  case LOAD_STAGE_SCREENS:
    switch (control->_st0) {
    /* Screen 0: open the character-select base window and fetch the
     * player's GAMERAM record ("GETPLAYER", ISUSE). A used slot opens the
     * message window and goes straight to screen 8; otherwise the host
     * (player 0) starts at screen 3 and the others at screen 2 (pad
     * connected) or 1. */
    case LOAD_SCREEN_OPEN:
      switch (control->_st1) {
      case 0: {
        igVec3f chrSelBasePos;
        Vec3f_Copy(&chrSelBasePos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_chrselbase",
            (const char *)"SQ_OPEN", (float *)&chrSelBasePos, 1);
        NextStep(control);
        break;
      }
      case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
          NextStep(control);
        }
        break;
      case 2: {
        RequestGameRam(self, host, "GETPLAYER");
        int gamePlayer = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        /* ISUSE: the GAMERAM record already holds a character. */
        if (igProperty_GetRecordByte((igObject *)gamePlayer, "ISUSE")->_data == 1) {
          beNDMWDegiData__LoadFromProperties(PlayerDegiData(common, host), gamePlayer);
          NextStep(control);
        } else {
          if (host->_ramNo == 0) {
            EnterState(control, LOAD_SCREEN_NEW_OR_LOAD);
          } else if (HostPad(self, host)->_isConnect != 0) {
            EnterState(control, LOAD_SCREEN_JOIN);
          } else {
            EnterState(control, LOAD_SCREEN_WAIT_PAD);
          }
          control->_isRdyCancel = 1;
        }
        break;
      }
      case 3: {
        igVec3f chrSelMessWinPos;
        Vec3f_Copy(&chrSelMessWinPos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_chrselmesswin",
            (const char *)"SQ_OPEN", (float *)&chrSelMessWinPos, 1);
        beNDMWLoadIntf2MesWin__RequestOpen(messages);
        HostWork(common, host)->_isEntry = 1;
        NextStep(control);
        break;
      }
      case 4:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
          control->_isRdyCancel = 0;
          EnterState(control, LOAD_SCREEN_START);
        }
        break;
      }
      break;
    /* Screen 1: wait until this player's pad is connected, then join
     * (screen 2). */
    case LOAD_SCREEN_WAIT_PAD:
      if ((HostWork(common, host)->_isCtrl == 1) && (HostPad(self, host)->_isConnect != 0)) {
        EnterState(control, LOAD_SCREEN_JOIN);
      }
      break;
    /* Screen 2: join window (linewin01, text 0x400) for players 2-4.
     * Cross enters ("SQ_LINEON00") and continues at screen 3; a missing pad
     * closes it ("SQ_CLOSE") and returns to screen 1. */
    case LOAD_SCREEN_JOIN:
      switch (control->_st1) {
      case 0: {
        igVec3f lineWin01Pos;
        Vec3f_Copy(&lineWin01Pos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_linewin01",
            (const char *)"SQ_OPEN", (float *)&lineWin01Pos, 1);
        NextStep(control);
        break;
      }
      case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
          beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, TextId(host, 0x400), 0);
          NextStep(control);
        }
        break;
      case 2: {
        unsigned char decided = 0;
        if (HostWork(common, host)->_isCtrl == 1) {
          if (HostPad(self, host)->_isConnect != 0) {
            if (padTrigger & kPadCross) {
              HostWork(common, host)->_isEntry = 1;
              decided = 1;
              control->_isEntry = 1;
            }
          } else {
            decided = 1;
          }
        } else {
          decided = 1;
        }
        if (decided == 1) {
          if (control->_isEntry == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_linewin01",
                (const char *)"SQ_LINEON00", 1);
          } else {
            beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_linewin01",
                (const char *)"SQ_CLOSE", 1);
          }
          TextOrder_PublishLineListOnly(textOrder, TextId(host, 0x400));
          NextStep(control);
        }
        break;
      }
      case 3:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
          if (control->_isEntry == 1) {
            EnterState(control, LOAD_SCREEN_NEW_OR_LOAD);
          } else {
            EnterState(control, LOAD_SCREEN_WAIT_PAD);
          }
        }
        break;
      }
      break;
    /* Screen 3: new-or-load question (linewin02, texts 0x401, 0x523,
     * 0x524). Up/down move _newLoadSel and Cross picks it: 0 creates a
     * character (screen 4), 1 loads a slot (screen 6). */
    case LOAD_SCREEN_NEW_OR_LOAD:
      switch (control->_st1) {
      case 0: {
        if (control->_isMesWin == 0) {
          igVec3f chrSelMessWinPos;
          Vec3f_Copy(&chrSelMessWinPos, &models->_pos);
          beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_chrselmesswin",
              (const char *)"SQ_OPEN", (float *)&chrSelMessWinPos, 1);
          beNDMWLoadIntf2MesWin__RequestOpen(messages);
          control->_isMesWin = 1;
        }
        HostWork(common, host)->_isEntry = 1;
        igVec3f lineWin02Pos;
        Vec3f_Copy(&lineWin02Pos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_linewin02",
            (const char *)"SQ_OPEN", (float *)&lineWin02Pos, 1);
        control->_newLoadSel = 0;
        NextStep(control);
        break;
      }
      case 1:
        if ((control->_st2 == 0) &&
            beNDMWLoadIntf2ComMdlCtrl__IsSequence((beNDMWSaveIntfComMdlCtrl *)models, host->_ramNo,
            (const char *)"j_linewin02", (const char *)"SQ_OPEN") == 0) {
          beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, TextId(host, 0x401), 0);
          NextSubstep(control);
          int player = host->_ramNo;
          if (player == 0) {
            beNDMWLoadIntf2MesWin__RequestMessage(messages, (player << 0x10) | 0x523);
          } else {
            beNDMWLoadIntf2MesWin__RequestMessage(messages, (player << 0x10) | 0x524);
          }
        }
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
          NextStep(control);
        }
        break;
      case 2:
        switch (control->_st2) {
        case 0:
          if (moveUp) {
            int selection = control->_newLoadSel - 1;
            if (selection < 0) {
              selection = 0;
            } else {
              beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_linewin02", "SQ_LINEUP00", 1);
            }
            control->_newLoadSel = selection;
            NextSubstep(control);
          } else if (moveDown) {
            int selection = control->_newLoadSel + 1;
            if (1 < selection) {
              selection = 1;
            } else {
              beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_linewin02", "SQ_LINEDW01", 1);
            }
            control->_newLoadSel = selection;
            NextSubstep(control);
          } else if (padTrigger & kPadCross) {
            if (control->_newLoadSel == 0) {
              beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_linewin02", "SQ_LINEON00", 1);
            } else {
              beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_linewin02", "SQ_LINEON01", 1);
            }
            NextStep(control);
          } else if (padTrigger & kPadCircle) {
            int player = host->_ramNo;
            if (player != 0) {
              beNDMWLoadIntf2ComMdlCtrl__Close(models, player, (const char *)"j_linewin02",
                  (const char *)"SQ_CANCEL", 1);
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_chrselmesswin",
                  (const char *)"SQ_CLOSE", 1);
              TextOrder_PublishLineListOnly(textOrder, TextId(host, 0x401));
              beNDMWLoadIntf2MesWin__RequestClose(messages);
              SetStep(control, control->_st1 + 2);
            }
          }
          break;
        case 1:
          if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            RestartSubstep(control);
          }
          break;
        }
        break;
      case 3:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
          TextOrder_PublishLineListOnly(textOrder, TextId(host, 0x401));
          if (control->_newLoadSel == 0) {
            EnterState(control, LOAD_SCREEN_CHOOSE_DIGIMON);
          } else {
            EnterState(control, LOAD_SCREEN_SLOT);
          }
        }
        break;
      case 4:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
          HostWork(common, host)->_isEntry = 0;
          control->_isEntry = 0;
          EnterState(control, LOAD_SCREEN_JOIN);
          control->_isMesWin = 0;
        }
        break;
      }
      break;
    /* Screen 4: starter Digimon choice. Left/right cycle through
     * g_starterPlayerModelName, the preview model is generated through
     * MODELCTRL and the name is read from the "shinka" database row.
     * Cross goes on to the name entry (screen 5), Circle back to the
     * question (screen 3). */
    case LOAD_SCREEN_CHOOSE_DIGIMON:
      switch (control->_st1) {
      case 0: {
        igVec3f cursorLeftPos;
        Vec3f_Copy(&cursorLeftPos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_digiselcursorleft",
            (const char *)"SQ_OPEN", (float *)&cursorLeftPos, 1);
        igVec3f cursorRightPos;
        Vec3f_Copy(&cursorRightPos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_digiselcursorright",
            (const char *)"SQ_OPEN", (float *)&cursorRightPos, 1);
        igVec3f nameWin02Pos;
        Vec3f_Copy(&nameWin02Pos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_namewin02",
            (const char *)"SQ_OPEN", (float *)&nameWin02Pos, 1);
        creation->_chaSelDegi = 3;
        beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x511));
        ShowStarterName(self, textOrder, host, creation);
        igVec3f faceWinPos;
        Vec3f_Copy(&faceWinPos, &models->_pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)"j_digifacewin",
            g_playerModelRow[creation->_chaSelDegi].openSequence, (float *)&faceWinPos, 1);
        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", g_starterSelectModelNames[creation->_chaSelDegi],
            host->_ramNo, "GENERATE");
        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", g_starterSelectModelNames[creation->_chaSelDegi],
            host->_ramNo, "ISRUN");
        unsigned char modelRunning = FirstBoolReply(self);
        if (modelRunning == 1) {
          Vec3f_Set(&previewPosition, 0.0f, 0.0f, 0.0f);
          Vec3f_Set(&previewRotation, 0.0f, 0.0f, 0.0f);
          beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL",
              g_starterSelectModelNames[creation->_chaSelDegi], host->_ramNo);
          igVec3f positionArg;
          Vec3f_Copy(&positionArg, &previewPosition);
          beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&positionArg);
          igVec3f rotationArg;
          Vec3f_Copy(&rotationArg, &previewRotation);
          beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&rotationArg);
          beMessenger_DispatchSelected((beMessenger *)self->_messenger, "MOVETRANS");
          beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", g_starterSelectModelNames[creation->_chaSelDegi],
              host->_ramNo, "SQ_ENTR");
          control->_isNoSelMdl = 0;
        } else {
          control->_isNoSelMdl = 1;
        }
        NextStep(control);
        control->_isCansel = 0;
        break;
      }
      case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
          beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", "j_namewin02", host->_ramNo, "SQ_LINESL00");
          NextStep(control);
        }
        break;
      case 2:
        switch (control->_st2) {
        case 0:
          if (moveRight) {
            ExitStarterModel(self, host, control, creation);
            int starter = creation->_chaSelDegi + 1;
            if (starter >= 4) {
              starter = 0;
            }
            creation->_chaSelDegi = starter;
            ShowStarterName(self, textOrder, host, creation);
            beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_digiselcursorright", (int *)"SQ_ON00", 1);
            beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_namewin02", "SQ_LINECG00", 0);
            beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_digifacewin",
                (int *)g_playerModelRow[creation->_chaSelDegi].faceSequence, 0);
            NextSubstep(control);
          } else if (moveLeft) {
            ExitStarterModel(self, host, control, creation);
            int starter = creation->_chaSelDegi - 1;
            if (starter < 0) {
              starter = 3;
            }
            creation->_chaSelDegi = starter;
            ShowStarterName(self, textOrder, host, creation);
            beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_digiselcursorleft", (int *)"SQ_ON00", 1);
            beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_namewin02", "SQ_LINECG00", 0);
            beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_digifacewin",
                (int *)g_playerModelRow[creation->_chaSelDegi].faceSequence, 0);
            NextSubstep(control);
          } else {
            unsigned char modelReady = 0;
            beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL",
                g_starterSelectModelNames[creation->_chaSelDegi], host->_ramNo, "ISRUN");
            if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) > 0) {
              modelReady = beMessenger_GetBool((beMessenger *)self->_messenger, 0);
            } else if (control->_isNoSelMdl == 1) {
              modelReady = 1;
            }
            if (modelReady == 1) {
              if (padTrigger & kPadCross) {
                NextStep(control);
              } else if (padTrigger & kPadCircle) {
                control->_isCansel = 1;
                NextStep(control);
              }
            } else {
              beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL",
                  g_starterSelectModelNames[creation ->_chaSelDegi], host->_ramNo, "GENERATE");
              beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL",
                  g_starterSelectModelNames[creation ->_chaSelDegi], host->_ramNo, "ISRUN");
              unsigned char modelRunning = FirstBoolReply(self);
              if (modelRunning == 1) {
                Vec3f_Set(&retryPosition, 0, 0, 0);
                Vec3f_Set(&retryRotation, 0, 0, 0);
                beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL",
                    g_starterSelectModelNames[creation ->_chaSelDegi], host->_ramNo);
                igVec3f positionArg;
                Vec3f_Copy(&positionArg, &retryPosition);
                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&positionArg);
                igVec3f rotationArg;
                Vec3f_Copy(&rotationArg, &retryRotation);
                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&rotationArg);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "MOVETRANS");
                beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL",
                    g_starterSelectModelNames[creation ->_chaSelDegi], host->_ramNo, "SQ_ENTR");
                control->_isNoSelMdl = 0;
              } else {
                control->_isNoSelMdl = 1;
              }
            }
          }
          break;
        case 1:
          if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            RestartSubstep(control);
          }
          break;
        }
        break;
      case 3:
        if (control->_isCansel != 0) {
          beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_namewin02",
              (const char *)"SQ_CANCEL", 1);
        } else {
          beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_namewin02",
              (const char *)"SQ_LINEON00", 1);
        }
        if (control->_isNoSelMdl == 0) {
          beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
              (const char *)(g_starterSelectModelNames[creation->_chaSelDegi]), (const char *)"SQ_EXIT", 1);
        }
        TextOrder_ClearFont(textOrder, "CHRSELFONT14", host->_ramNo, 0);
        NextStep(control);
        break;
      case 4:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
          NextStep(control);
        }
        break;
      case 5:
        beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_digifacewin",
            (const char *)"SQ_CLOSE", 1);
        beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_digiselcursorleft",
            (const char *)"SQ_CLOSE", 1);
        beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_digiselcursorright",
            (const char *)"SQ_CLOSE", 1);
        NextStep(control);
        break;
      case 6:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
          if (control->_isCansel == 1) {
            EnterState(control, LOAD_SCREEN_NEW_OR_LOAD);
          } else {
            EnterState(control, LOAD_SCREEN_NAME);
            beNDMWLoadIntf2NameSel__Init(nameEntry, 1);
          }
        }
        break;
      }
      break;
    /* Screen 5: name entry (NameSel). A finished name (_isMakeName) goes
     * to screen 8 with _isNewMake set, a cancelled one back to screen 4.
     */
    case LOAD_SCREEN_NAME:
      switch (control->_st1) {
      case 0:
      default:
        nameEntry->_selDataNo = creation->_chaSelDegi;
        NextStep(control);
        beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x517));
        break;
      case 1:
        if (beNDMWLoadIntf2NameSel__Update((NameSelRam *)nameEntry, HostWork(common, host)->_isCtrl) != 0) {
          if (nameEntry->_isMakeName == 1) {
            control->_isNewMake = 1;
            EnterState(control, LOAD_SCREEN_START);
          } else {
            EnterState(control, LOAD_SCREEN_CHOOSE_DIGIMON);
          }
        } else if (nameEntry->_isQuestion == 1) {
          NextStep(control);
        }
        break;
      case 2:
        beNDMWLoadIntf2MesWin__RequestPrompt(messages, TextId(host, 0x519));
        NextStep(control);
        break;
      case 3:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(messages) == 0) {
          NextStep(control);
        }
        break;
      case 4:
        beNDMWLoadIntf2MesWin__RequestQuestion(messages, TextId(host, 0x51B), 0);
        NextStep(control);
        break;
      case 5:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(messages) == 0) {
          switch (beNDMWLoadIntf2MesWin__GetCurPoint(messages)) {
          case 0:
            beNDMWLoadIntf2NameSel__SetAnswer(nameEntry, 1);
            break;
          case 1:
            beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x517));
            beNDMWLoadIntf2NameSel__SetAnswer(nameEntry, 0);
            break;
          }
          SetStep(control, 1);
        }
        break;
      }
      break;
    /* Screen 6: slot selection (SelSlot). A re-open request repeats
     * screen 6, cancel returns to screen 3, a chosen slot continues at
     * screen 7. */
    case LOAD_SCREEN_SLOT:
      switch (control->_st1) {
      case 0:
        switch (control->_st2) {
        case 0:
          beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, host->_ramNo);
          beNDMWLoadIntf2SelSlot__Init(slots);
          EnterSlotState(slots, 0);
          beNDMWLoadIntf2MesWin__RequestMessage(messages, HardwareTextId(common, host, 0x1009, 0x2009, 0x3009));
          NextSubstep(control);
          break;
        case 1:
          if (beNDMWLoadIntf2SelSlot__Open(slots, -1) == 1) {
            EnterSlotState(slots, 1);
            NextStep(control);
          }
          break;
        }
        break;
      case 1:
        switch (control->_st2) {
        case 0:
          if (beNDMWLoadIntf2SelSlot__UpdateSelection(slots, HostWork(common, host)->_isCtrl, 1) == 1) {
            if (slots->_isReOpenReq == 1) {
              NextStep(control);
            } else if (slots->_isCansel == 1) {
              NextStep(control);
            } else {
              NextSubstep(control);
            }
          }
          break;
        case 1:
          switch (control->_st3) {
          case 0:
            beNDMWLoadIntf2MesWin__RequestMessage(messages, HardwareTextId(common, host, 0x1004, 0x2004, 0x3004));
            beNDMWLoadCtrl2CommonIntf__StartUtilFor(common, host->_ramNo, LOAD_STAGE_CARD_UTIL);
            NextTick(control);
            break;
          case 1:
            switch (HostWork(common, host)->_utilReturn) {
            case 0:
              NextStep(control);
              break;
            case 1:
            case 2:
              beNDMWLoadIntf2MesWin__RequestMessage(messages, HardwareTextId(common, host, 0x1009, 0x2009, 0x3009));
              beNDMWLoadIntf2SelSlot__PublishCursor(slots);
              SetStep(control, 1);
              break;
            case 4:
              beNDMWLoadIntf2MesWin__RequestMessage(messages, HardwareTextId(common, host, 0x1009, 0x2009, 0x3009));
              beNDMWLoadIntf2SelSlot__PublishCursor(slots);
              SetStep(control, 1);
              break;
            }
            break;
          }
          break;
        }
        break;
      case 2:
        switch (control->_st2) {
        case 0:
          EnterSlotState(slots, 2);
          NextSubstep(control);
          break;
        case 1:
          if (beNDMWLoadIntf2SelSlot__Close(slots) == 1) {
            if (slots->_isReOpenReq == 1) {
              EnterState(control, LOAD_SCREEN_SLOT);
            } else if (slots->_isCansel == 1) {
              EnterState(control, LOAD_SCREEN_NEW_OR_LOAD);
            } else {
              EnterState(control, LOAD_SCREEN_SAVE_DATA);
            }
            beNDMWLoadIntf2MesWin__RequestMesErase(messages);
          }
          break;
        }
        break;
      }
      break;
    /* Screen 7: save-data selection (DataSelIntf). Cancel returns to the
     * slot screen, otherwise the flow continues at screen 8. */
    case LOAD_SCREEN_SAVE_DATA:
      switch (control->_st1) {
      case 0:
        beNDMWLoadIntf2DataSelIntf__Init(dataSelection, host->_ramNo, 0);
        NextStep(control);
        break;
      case 1:
        switch (control->_st2) {
        case 0:
          beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
          NextSubstep(control);
          break;
        case 1:
          if (beNDMWLoadIntf2DataSelIntf__OpenSaveArea(dataSelection, 0) == 1) {
            NextSubstep(control);
          }
          break;
        case 2:
          beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
          NextSubstep(control);
          break;
        case 3:
          if (HostWork(common, host)->_isCutConnect == 1) {
            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
            NextSubstep(control);
            control->_st3 = 1;
          } else if (beNDMWLoadIntf2DataSelIntf__UpdateSelection(dataSelection, 0) == 1) {
            beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
            NextSubstep(control);
            control->_st3 = 0;
          }
          break;
        case 4:
          if (beNDMWLoadIntf2DataSelIntf__CloseAll(dataSelection, 0) == 1) {
            switch (control->_st3) {
            case 0:
              NextStep(control);
              break;
            case 1:
              SetStep(control, SAVE_DATA_STEP_CARD_PULLED);
              break;
            }
          }
          break;
        }
        break;
      case 2:
        if (dataSelection->_isCancel == 1) {
          EnterState(control, LOAD_SCREEN_SLOT);
        } else {
          control->_isNewMake = 0;
          EnterState(control, LOAD_SCREEN_START);
        }
        break;
      case SAVE_DATA_STEP_CARD_PULLED:
        switch (control->_st2) {
        case 0:
          beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
          NextSubstep(control);
          break;
        case 1:
          if (beNDMWLoadIntf2DataSelIntf__CloseAll(dataSelection, 0) == 1) {
            int allocator = SelectAllocator(&kIGMemoryPoolHandleUser1, (int)igObject_GetAllocator(self));
            {
              DegiDataRef freshData(beNDMWDegiData_Create(allocator));
              beNDMWLoadIntf2_igObjectList_Set((igDataList *)common->_gameUseData, host->_ramNo, (ObjectRefTarget *)freshData.value);
            }
            EnterState(control, LOAD_SCREEN_SLOT);
          }
          break;
        }
        break;
      }
      break;
    /* Screen 8: start. Builds the player record (a new character through
     * "GAMESTART"/"UNIQUE", or the saved one through
     * "GAMEDATAINIT"/"BASE2CURRENT"/ "RECALCPLAYER"), then the difficulty
     * choice and status display; START with every entered player ready
     * ends the interface (common->_intfStat = 3). */
    case LOAD_SCREEN_START:
      switch (control->_st1) {
      case 0:
        switch (control->_st2) {
        case 0:
          switch (control->_st3) {
          case 0: {
            if (control->_isRdyCancel == 1) {
              if (control->_isNewMake == 1) {
                RequestGameRam(self, host, "GAMEDATAINIT");
                int allocator = SelectAllocator(&kIGMemoryPoolHandleUser0, (int)igObject_GetAllocator(self));
                beUnicodeObj *nameObject = beUnicodeObj_Create(allocator);
                {
                  igSmartPointer<beUnicodeObj> nameRef(nameObject);
                  beUnicodeObj_AllocateBuffer(nameRef.p, 8);
                  CopyTypedName((unsigned short *)nameRef.p->_buffer, nameEntry);
                  beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                  beMessenger_AppendInt((beMessenger *)self->_messenger, host->_ramNo);
                  beMessenger_AppendString((beMessenger *)self->_messenger, g_playerModelRow[creation->_chaSelDegi].model);
                  beMessenger_AppendObject((beMessenger *)self->_messenger, nameRef.p);
                  beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GAMESTART");
                }
                RequestGameRam(self, host, "GETPLAYER");
                int newPlayer = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                /* Stamp the new character with the low word of the world
                 * clock as its UNIQUE property. */
                long long worldTime = ((igInsightCore *)self->_insight)->_worldTime;
                beDataObjInt *unique = igProperty_GetRecord((igObject *)newPlayer, "UNIQUE");
                unique->_data = (int)worldTime;
                beNDMWDegiData__LoadFromProperties(PlayerDegiData(common, host), newPlayer);
              } else {
                RequestGameRam(self, host, "GAMEDATAINIT");
                void *savedData = PlayerSaveData(common, host->_ramNo, dataSelection->_svDataSelPoint);
                {
                  DegiDataRef savedDataRef(savedData, true);
                  beNDMWLoadIntf2_igObjectList_Set((igDataList *)common->_gameUseData, host->_ramNo, (ObjectRefTarget *)savedDataRef.value);
                  beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, host->_ramNo);
                }
                RequestGameRam(self, host, "GETPLAYER");
                int loadedPlayer = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                igObject *font = igInsightCore_FindManager((igInsightCore *)self->_insight, g_beFont_metaObject);
                beNDMWDegiData__StoreToProperties(PlayerDegiData(common, host), (void *)loadedPlayer, (int)font);
                int kindName = PlayerDegiData(common, host)->_dmkind;
                beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
                beMessenger_AppendInt((beMessenger *)self->_messenger, host->_ramNo);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)kindName);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, "BASE2CURRENT");
                RequestGameRam(self, host, "RECALCPLAYER");
              }
            }
            unsigned char needsDifficulty = 0;
            int difficultyMenu = 0;
            if ((host->_ramNo == 0) && (control->_isRdyCancel == 1)) {
              common->_difficultMode = 0;
              self->_difficultMax = 0;
              g_mdlEntity = 0;
              beLua__RunNamedChunk((beLua *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject), "hostLoad.lua", 0);
              switch (self->_difficultMax) {
              case 0:
                break;
              case 1:
                needsDifficulty = 1;
                difficultyMenu = 1;
                break;
              case 2:
                difficultyMenu = 2;
                needsDifficulty = 1;
                break;
              }
            }
            if (needsDifficulty == 0) {
              OpenDegiState(status, 1, host->_ramNo);
              NextSubstep(control);
            } else {
              switch (difficultyMenu) {
              case 1:
                beNDMWLoadIntf2Diffselect__Init(difficulty, 0, host->_ramNo);
                break;
              case 2:
                beNDMWLoadIntf2Diffselect__Init(difficulty, 1, host->_ramNo);
                break;
              }
              NextTick(control);
            }
            break;
          }
          case 1:
            if (beNDMWLoadIntf2Diffselect__Update(difficulty, HostWork(common, host)->_isCtrl) == 1) {
              if (difficulty->_isCancel == 1) {
                int allocator = SelectAllocator(&kIGMemoryPoolHandleUser1, (int)igObject_GetAllocator(self));
                {
                  DegiDataRef freshData(beNDMWDegiData_Create(allocator));
                  beNDMWLoadIntf2_igObjectList_Set((igDataList *)common->_gameUseData, host->_ramNo, (ObjectRefTarget *)freshData.value);
                }
                HostWork(common, host)->_isRdy = 0;
                EnterState(control, LOAD_SCREEN_SLOT);
              } else {
                common->_difficultMode = difficulty->_selectPoint;
                OpenDegiState(status, 1, host->_ramNo);
                NextSubstep(control);
              }
            }
            break;
          }
          break;
        case 1:
          if (beNDMWLoadIntf2DegiState__Update(FirstDegiState(status)) == 1) {
            HostWork(common, host)->_isRdy = 1;
            if (host->_ramNo == 0) {
              if (AllEntriesReady(common) == 1) {
                SetStep(control, 3);
              } else {
                SetStep(control, 1);
              }
            } else {
              SetStep(control, 1);
            }
          }
          break;
        }
        break;
      case 1:
        switch (control->_st2) {
        case 0:
          if (control->_isRdyCancel == 1) {
            beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x530));
          } else {
            beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x52F));
          }
          NextSubstep(control);
          break;
        case 1:
          switch (control->_st3) {
          case 0:
            if (host->_ramNo == 0) {
              if (AllEntriesReady(common) == 1) {
                SetStep(control, 3);
              } else if ((padTrigger & kPadCircle) && (control->_isRdyCancel == 1)) {
                HostWork(common, host)->_isRdy = 0;
                NextStep(control);
              }
            } else {
              if (AllEntriesReady(common) == 1) {
                if (control->_isRdyCancel == 1) {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x51F));
                } else {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x522));
                }
                NextTick(control);
              } else if ((padTrigger & kPadCircle) && (control->_isRdyCancel == 1)) {
                HostWork(common, host)->_isRdy = 0;
                NextStep(control);
              }
            }
            break;
          case 1:
            if (AllEntriesReady(common) == 0) {
              if (control->_isRdyCancel == 1) {
                beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x530));
              } else {
                beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x52F));
              }
              control->_st3 = 0;
            } else if ((padTrigger & kPadCircle) && (control->_isRdyCancel == 1)) {
              HostWork(common, host)->_isRdy = 0;
              NextStep(control);
            }
            break;
          }
          break;
        }
        break;
      case 2:
        switch (control->_st2) {
        case 0:
          beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, "j_mainstatuswin", "SQ_CANCEL", 1);
          NextSubstep(control);
          break;
        case 1:
          if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            NextSubstep(control);
          }
          break;
        case 2:
          beNDMWLoadIntf2DegiState__RequestClose(FirstDegiState(status), 0);
          NextSubstep(control);
          break;
        case 3:
          if (beNDMWLoadIntf2DegiState__Update(FirstDegiState(status)) == 1) {
            if (control->_isNewMake == 1) {
              EnterState(control, LOAD_SCREEN_NAME);
              beNDMWLoadIntf2NameSel__Init(nameEntry, 0);
            } else {
              int allocator = SelectAllocator(&kIGMemoryPoolHandleUser1, (int)igObject_GetAllocator(self));
              {
                DegiDataRef freshData(beNDMWDegiData_Create(allocator));
                beNDMWLoadIntf2_igObjectList_Set((igDataList *)common->_gameUseData, host->_ramNo, (ObjectRefTarget *)freshData.value);
              }
              EnterState(control, LOAD_SCREEN_SLOT);
            }
          }
          break;
        }
        break;
      case 3:
        switch (control->_st2) {
        case 0:
          if (control->_isRdyCancel == 1) {
            beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x51D));
          } else {
            beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x521));
          }
          NextSubstep(control);
          break;
        case 1:
          if ((padTrigger & kPadCircle) && (control->_isRdyCancel == 1)) {
            HostWork(common, host)->_isRdy = 0;
            SetStep(control, 2);
          } else {
            if (AllEntriesReady(common) == 1) {
              if (padTrigger & kPadStart) {
                EndInterface(common);
                ((beSystem *)common->_system)->_isSResetEnable = 0;
                NextSubstep(control);
              }
            } else {
              SetStep(control, 1);
            }
          }
          break;

        case 3:
          break;
        }
        break;
      }
      break;
    }
    break;
  /* Stage 2: leaving. Close the windows of the screen that was active
   * (leaveState); once they are closed _isClose is set and the work moves
   * on to step 3. */
  case LOAD_STAGE_CLOSE:
    switch (HostWork(common, host)->_sysStat1) {
    case 0:
      switch (control->_st0) {
      default:
        SetPlayerStep(WorkAt(common, host->_ramNo), 1);
        break;
      case LOAD_SCREEN_JOIN:
        SetPlayerStep(WorkAt(common, host->_ramNo), 1);
        break;
      case LOAD_SCREEN_START:
        beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_chrselmesswin",
            (const char *)"SQ_CLOSE", 1);
        beNDMWLoadIntf2MesWin__RequestClose(messages);
        beNDMWLoadIntf2DegiState__RequestConfirmClose(FirstDegiState(status));
        SetPlayerStep(WorkAt(common, host->_ramNo), 2);
        break;
      }
      beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)"j_chrselbase",
          (const char *)"SQ_CLOSE", 1);
      break;
    case 1:
      if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
        HostWork(common, host)->_isClose = 1;
        SetPlayerStep(WorkAt(common, host->_ramNo), 3);
      }
      break;
    case 2:
      if ((beNDMWLoadIntf2DegiState__Update(FirstDegiState(status)) == 1) &&
          (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1)) {
        HostWork(common, host)->_isClose = 1;
        SetPlayerStep(WorkAt(common, host->_ramNo), 3);
      }
      break;

    case 3:
      break;
    }
    break;
  /* Stage 5: memory-card utility steps (common->_mcUtilCtrl). Each step
   * calls one shared card helper per frame until it reports 1 (done) or 2
   * (failed). */
  case LOAD_STAGE_CARD_UTIL:
    if (McUtil(common)->_isUseUtil == 1) {
      beNDMWLoadSavePlWork *cardWork = HostWork(common, host);
      switch (cardWork->_sysStat1) {
      case CARD_STEP_CHECK: {
        int stepResult = beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(common, host->_ramNo, messages,
            slots->_mcSelPoint, 3);
        switch (stepResult) {
        case 0:
          break;
        case 1:
          SetPlayerStep(cardWork, CARD_STEP_ATTACH);
          break;
        case 2:
          switch (McUtil(common)->_result) {
          case 2:
            SetPlayerStep(cardWork, CARD_STEP_ATTACH);
            break;
          case 7:
            if (common->_kindHard == 1) {
              SetPlayerStep(cardWork, CARD_STEP_ASK_FORMAT);
            } else {
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
            }
            break;
          case 12:
            EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
            break;
          default:
          case 4:
          case 3:
            EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
            break;
          }
          break;
        }
        break;
      }
      case CARD_STEP_ASK_CREATE:
        if (SelectedCardSlot(common, slots)->_isConnect != 1) {
          beNDMWLoadIntf2MesWin__Cancel(messages);
          EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
          cardWork->_utilReturn = 2;
        } else {
          int noticeText = -1;
          int questionText = -1;
          switch (common->_kindHard) {
          case 0:
            noticeText = TextId(host, 0x1000);
            questionText = TextId(host, 0x1002);
            break;
          case 1:
            noticeText = TextId(host, 0x2000);
            questionText = TextId(host, 0x2002);
            break;
          case 2:
            noticeText = TextId(host, 0x3000);
            questionText = TextId(host, 0x3002);
            break;
          }
          int stepResult = beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(common, host->_ramNo, messages,
              noticeText, questionText, 0, 3);
          switch (stepResult) {
          case 0:
            break;
          case 1:
            SetPlayerStep(cardWork, CARD_STEP_CREATE);
            break;
          case 2:
            EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
            cardWork->_utilReturn = 1;
            break;
          }
        }
        break;
      case CARD_STEP_CREATE:
        switch (cardWork->_sysStat2) {
        case 0:
          SetResetEnable(self, common, 0);
          NextPlayerSubstep(cardWork);
          break;
        case 1:
          int stepResult = beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(common, host->_ramNo, messages,
              slots->_mcSelPoint, 3);
          switch (stepResult) {
          case 0:
            break;
          case 1:
            SetPlayerStep(cardWork, CARD_STEP_ATTACH);
            break;
          case 2:
            switch (McUtil(common)->_result) {
            case 7:
              SetPlayerStep(cardWork, CARD_STEP_ASK_FORMAT);
              break;
            case 9:
            case 10:
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
              cardWork->_utilReturn = 1;
              break;
            default:
            case 3:
            case 4:
            case 5:
            case 6:
            case 8:
            case 11:
            case 12:
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
              cardWork->_utilReturn = 1;
              break;
            }
            break;
          }
          if (stepResult != 0) {
            SetResetEnable(self, common, 1);
          }
          break;
        }
        break;
      case CARD_STEP_ASK_FORMAT:
        if (SelectedCardSlot(common, slots)->_isConnect != 1) {
          beNDMWLoadIntf2MesWin__Cancel(messages);
          EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
          cardWork->_utilReturn = 2;
        } else {
          int noticeText = -1;
          int questionText = -1;
          switch (common->_kindHard) {
          case 0:
            noticeText = TextId(host, 0x1005);
            questionText = TextId(host, 0x1007);
            break;
          case 1:
            noticeText = TextId(host, 0x2005);
            questionText = TextId(host, 0x2007);
            break;
          case 2:
            noticeText = TextId(host, 0x3005);
            questionText = TextId(host, 0x3007);
            break;
          }
          int stepResult = beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(common, host->_ramNo, messages,
              noticeText, questionText, 1, 3);
          switch (stepResult) {
          case 0:
            break;
          case 1:
            SetPlayerStep(cardWork, CARD_STEP_FORMAT);
            break;
          case 2:
            EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
            cardWork->_utilReturn = 1;
            break;
          }
        }
        break;
      case CARD_STEP_FORMAT:
        switch (cardWork->_sysStat2) {
        case 0:
          beNDMWLoadIntf2MesWin__RequestMessage(messages, HardwareTextId(common, host, 0x1008, 0x2008, 0x3008));
          SetResetEnable(self, common, 0);
          NextPlayerSubstep(cardWork);
          break;
        case 1:
          int stepResult = beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(common, host->_ramNo, messages,
              slots->_mcSelPoint, 3);
          switch (stepResult) {
          case 0:
            break;
          case 1:
            cardWork->_utilReturn = 4;
            EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
            break;
          case 2:
            switch (McUtil(common)->_result) {
            case 4:
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
              cardWork->_utilReturn = 2;
              break;
            default:
            case 3:
            case 5:
            case 7:
            case 6:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
              cardWork->_utilReturn = 2;
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
              break;
            }
            break;
          }
          if (stepResult != 0) {
            SetResetEnable(self, common, 1);
          }
          break;
        }
        break;
      case CARD_STEP_ATTACH: {
        beNDMWLoadSlotPlayer *slotPlayer = 0;
        for (listIndex = 0; listIndex < SlotSaveData(common)->_count; listIndex++) {
          int connection = ((beNDMWLoadSlotPlayer *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)common->_slotSaveData, listIndex))->_connectNO;
          if (connection == slots->_mcSelPoint) {
            slotPlayer = (beNDMWLoadSlotPlayer *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)common->_slotSaveData, listIndex);
            break;
          }
        }
        if (slotPlayer == 0) {
          if (McUtil(common)->_isUseUtil != 0) {
            NextPlayerStep(cardWork);
          }
        } else {
          accessList = (igIntList *)slotPlayer->_accessPlList;
          accessCount = accessList->_count;
          accessPlayer = host->_ramNo;
          if (accessCount < accessList->_capacity) {
            accessList->_count = IntListCount(accessList) + 1;
          } else {
            List_Resize(accessList, accessCount + 1, 4);
          }
          ((int *)beNDMWLoadIntf2_igIntList_GetData((igDataList *)accessList))[accessCount] = accessPlayer;
          cardWork->_haveSaveData = (int)slotPlayer;
          EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
          cardWork->_utilReturn = 0;
        }
        break;
      }
      case CARD_STEP_READ:
        switch (cardWork->_sysStat2) {
        case 0:
          NextPlayerSubstep(cardWork);
          break;
        case 1:
          int stepResult = beNDMWLoadCtrl2CommonIntf__StepReadMedia(common, host->_ramNo, messages,
              slots->_mcSelPoint, 3);
          switch (stepResult) {
          case 0:
            break;
          case 1:
            EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_DONE);
            cardWork->_utilReturn = 0;
            break;
          case 2:
            switch (McUtil(common)->_result) {
            case 7:
              SetPlayerStep(cardWork, CARD_STEP_ASK_FORMAT);
              break;
            case 9:
            case 10:
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
              cardWork->_utilReturn = 1;
              break;
            default:
            case 3:
            case 4:
            case 5:
            case 6:
            case 8:
            case 11:
            case 12:
              EnterPlayerStage(cardWork, LOAD_STAGE_UTIL_ERROR);
              cardWork->_utilReturn = 1;
              break;
            }
            break;
          }
          break;
        }
        break;
      }
    }
    break;
  /* Stage 6: after a card utility ends, choose the message-window text from
   * the utility result (mcUtil->_result) and the hardware kind. */
  case LOAD_STAGE_UTIL_ERROR:
    /* matching construct: the redundant cast (a fresh temporary) keeps resultWork in its original
     * register. */
    resultWork = (beNDMWLoadSavePlWork *)HostWork(common, host);
    if (common->_kindHard == 2) {
      beNDMWLoadIntf2SelSlot__UpdateSelection(slots, 0, 0);
    }
    switch (resultWork->_sysStat1) {
    default:
      break;
    case 0:
      switch (resultWork->_sysStat2) {
      case 0: {
        beNDMWMcUtilCtrl *mcUtil = McUtil(common);
        if (mcUtil->_isFormatRun == 1) {
          if (mcUtil->_result == 0xC) {
            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, slots->_mcSelPoint);
          } else {
            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, -1);
          }
          beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x100E, 0x200E, 0x300E));
        } else if (SelectedCardSlot(common, slots)->_isConnect == 1) {
          int cardResult = McUtil(common)->_result;
          if (common->_kindHard != 2) {
            if (cardResult == 0xC) {
              beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, slots->_mcSelPoint);
            } else {
              beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, -1);
            }
          }
          switch (cardResult) {
          case 7:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1028, 0x2012, 0x3012));
            break;
          case 9:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1014, 0x2014, 0x3014));
            break;
          case 10:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1015, 0x2015, 0x3015));
            break;
          case 5:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1010, 0x2010, 0x3010));
            break;
          case 6:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1011, 0x2011, 0x3011));
            break;
          case 8:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1013, 0x2013, 0x3013));
            break;
          case 12:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1016, 0x2016, 0x3016));
            break;
          case 4:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1028, 0x2028, 0x3028));
            break;
          case 3:
          default:
            beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x100D, 0x200D, 0x300D));
            break;
          }
        } else {
          if (common->_kindHard != 2) {
            beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, slots->_mcSelPoint);
          }
          beNDMWLoadIntf2MesWin__RequestPrompt(messages, HardwareTextId(common, host, 0x1016, 0x2016, 0x3016));
        }
        NextPlayerSubstep(resultWork);
        break;
      }
      case 1:
        if (beNDMWLoadIntf2MesWin__GetIsCtrl(messages) == 0) {
          resultWork->_utilReturn = 1;
          EnterPlayerStage(resultWork, LOAD_STAGE_UTIL_DONE);
        }
        break;
      }
      break;
    }
    break;
  /* Stage 7: put the work records of all four players into stage 8. */
  case LOAD_STAGE_UTIL_DONE:
    int player;
    for (player = 0; player < 4; player++) {
      EnterPlayerStage(WorkAt(common, player), LOAD_STAGE_RESUME);
    }
    break;
  /* Stage 8: clear the message window, reset this player's stages and hand
   * the pad back to the screens (_isCtrl = 1). */
  case LOAD_STAGE_RESUME:
    beNDMWLoadIntf2MesWin__EndSystemMessage(messages);
    EnterPlayerStage(WorkAt(common, host->_ramNo), LOAD_STAGE_SCREENS);
    HostWork(common, host)->_isCtrl = 1;
    break;
  }
}


void beNDMWLoadIntf2DegiState__RequestOpen(beNDMWLoadIntf2DegiState *self, int kind, int dataNo) {
    self->_kind = kind;
    self->_dataNo = dataNo;
    self->_isEnd = 0;
    EnterDegiState(self, DEGI_STATE_OPEN);
}

void beNDMWLoadIntf2DegiState__RequestChange(beNDMWLoadIntf2DegiState *self, int kind, int dataNo) {
    self->_kind = kind;
    self->_dataNo = dataNo;
    self->_isEnd = 0;
    EnterDegiState(self, DEGI_STATE_CHANGE);
}

void beNDMWLoadIntf2DegiState__RequestClose(beNDMWLoadIntf2DegiState *self, int closeKind) {
    self->_isEnd = 0;
    self->_closeKind = closeKind;
    EnterDegiState(self, DEGI_STATE_CLOSE);
}

void beNDMWLoadIntf2DegiState__RequestConfirmClose(beNDMWLoadIntf2DegiState *self) {
    self->_isEnd = 0;
    self->_closeKind = 1;
    EnterDegiState(self, DEGI_STATE_CLOSE);
}

/* Fills the status window with the shown record, or shows its empty-window lines when the record
 * is unused; the two display positions use different text slots. */
void beNDMWLoadIntf2DegiState__DrawStatusText(beNDMWLoadIntf2DegiState *self) {
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    if (self->_dispPos == 0) {
        beNDMWDegiData *data = ShownDegiData(self, common);
        if (data->_isUse == 1) {
            DrawName(self, data, 0);
            DrawKindName(self, data, 10);
            DrawStats(self, data, 0, 0, 10, 1, 11);
        } else {
            beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)self->_textOrder, (self->_plNo << 16) | 0x10, 0);
        }
    } else {
        beNDMWDegiData *data = ShownDegiData(self, common);
        if (data->_isUse == 1) {
            DrawName(self, data, 10);
            DrawKindName(self, data, 11);
            DrawStats(self, data, 1, 2, 12, 3, 13);
        } else {
            beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)self->_textOrder, (self->_plNo << 16) | 0x110, 0);
        }
    }
}

void beNDMWLoadIntf2DegiState__ClearStatusText(beNDMWLoadIntf2DegiState *self) {
    if (self->_dispPos == 0) {
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT03", self->_plNo, 0);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT04", self->_plNo, 0);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT04", self->_plNo, 10);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 0);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 10);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 1);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 11);
        TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)self->_textOrder, (self->_plNo << 16) | 0x10);
        return;
    }
    if (self->_isUseData == 1) {
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT03", self->_plNo, 10);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT04", self->_plNo, 11);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT04", self->_plNo, 1);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 2);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 12);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 3);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)self->_textOrder, "CHRSELFONT05", self->_plNo, 13);
        return;
    }
    TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)self->_textOrder, (self->_plNo << 16) | 0x110);
}

/* Each request ends with _isEnd set and the state back to idle; Update returns _isEnd. */
unsigned char beNDMWLoadIntf2DegiState__Update(beNDMWLoadIntf2DegiState *self) {
    if (self->_isEnd == 1) {
        return 1;
    }
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    switch (self->_st0) {
    case DEGI_STATE_IDLE:
        break;
    case DEGI_STATE_OPEN:
        switch (self->_st1) {
        case 0: {
            beNDMWDegiData *data = ShownDegiData(self, common);
            NoteUseData(self, data);
            if (self->_isUseData == 1) {
                int modelIndex = 0;
                FindPlayerModel(data, &modelIndex);
                if (self->_dispPos == 0) {
                    OpenWindow(self, "j_digifacewin", g_playerModelRow[modelIndex].openSequence);
                    OpenWindow(self, "j_mainstatuswin", "SQ_OPEN");
                } else {
                    OpenWindow(self, "j_savecheckwin", g_playerModelRow[modelIndex].openSequence);
                }
            } else if (self->_dispPos == 0) {
                OpenWindow(self, "j_digifacewin", "SQ_nofaceOPEN");
                OpenWindow(self, "j_mainstatuswin", "SQ_NOOPEN");
            } else {
                OpenWindow(self, "j_savecheckwin", "SQ_nofaceOPEN");
            }
            NextDegiStep(self);
            break;
        }
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl) == 1) {
                beNDMWLoadIntf2DegiState__DrawStatusText(self);
                self->_isEnd = 1;
                EnterDegiState(self, DEGI_STATE_IDLE);
            }
            break;
        }
        break;
    case DEGI_STATE_CHANGE: {
        beNDMWDegiData *data = ShownDegiData(self, common);
        NoteUseData(self, data);
        if (self->_isUseData == 1) {
            int modelIndex = 0;
            FindPlayerModel(data, &modelIndex);
            if (self->_dispPos == 0) {
                PlayWindow(self, "j_digifacewin", g_playerModelRow[modelIndex].faceSequence);
                PlayWindow(self, "j_mainstatuswin", "SQ_WAIT");
            } else {
                PlayWindow(self, "j_savecheckwin", g_playerModelRow[modelIndex].faceSequence);
            }
        } else if (self->_dispPos == 0) {
            PlayWindow(self, "j_digifacewin", "SQ_noface");
            PlayWindow(self, "j_mainstatuswin", "SQ_NOWAIT");
        } else {
            PlayWindow(self, "j_savecheckwin", "SQ_noface");
        }
        beNDMWLoadIntf2DegiState__ClearStatusText(self);
        beNDMWLoadIntf2DegiState__DrawStatusText(self);
        self->_isEnd = 1;
        EnterDegiState(self, DEGI_STATE_IDLE);
        break;
    }
    case DEGI_STATE_CLOSE:
        NoteUseData(self, ShownDegiData(self, common));
        switch (self->_st1) {
        case 0:
            if (self->_dispPos == 0) {
                CloseWindow(self, "j_digifacewin", "SQ_CLOSE");
                if (self->_isUseData == 1) {
                    switch (self->_closeKind) {
                    case 0:
                        CloseWindow(self, "j_mainstatuswin", "SQ_CLOSE");
                        break;
                    case 1:
                        CloseWindow(self, "j_mainstatuswin", "SQ_LINEON00");
                        break;
                    case 2:
                        CloseWindow(self, "j_mainstatuswin", "SQ_CANCEL");
                        break;
                    }
                } else {
                    CloseWindow(self, "j_mainstatuswin", "SQ_NOCLOSE");
                }
            } else {
                CloseWindow(self, "j_savecheckwin", "SQ_CLOSE");
            }
            beNDMWLoadIntf2DegiState__ClearStatusText(self);
            NextDegiStep(self);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl) == 1) {
                self->_isEnd = 1;
                EnterDegiState(self, DEGI_STATE_IDLE);
            }
            break;
        }
        break;
    }
    return self->_isEnd;
}

/* beNDMWLoadIntf2DataSelIntf::_kind: what the player picks a save area for. */
enum DataSelKind {
    kDataSelLoad = 0, /* take the area's Digimon into the game */
    kDataSelSave = 1  /* write the player's Digimon into the area */
};
/* beNDMWLoadIntf2DataSelIntf::_mesKind: which prompt the message window shows. */
enum DataSelMesKind {
    kMesKindPrompt = 0,
    kMesKindInUse = 1
};
/* Message-window texts (the player number goes in the high half-word). */
enum DataSelMessage {
    kMesSaveSelectArea = 0x503,
    kMesLoadSelectArea = 0x513,
    kMesLoadAreaInUse = 0x515
};
/* Text lines shown in place of the name of an unused area: one id per area. */
enum { kTextUnusedAreaName = 0x300 };
/* The save areas sit in a 2x2 grid: 0 1 over 2 3 (windows A B over C D). */
enum { kSaveAreaCount = 4, kPlayerCount = 4, kAreaNameLength = 8, kPlayerModelRowCount = 16 };
/* The two beNDMWLoadIntf2DegiState windows of _statDisp, and what beNDMWLoadIntf2DegiState::_kind
 * shows in them. */
enum StatusWindow { kUpperStatus = 0, kLowerStatus = 1 };
enum StatusSource { kStatusSaveArea = 0, kStatusGameUse = 1 };
/* beNDMWLoadIntf2DataSelIntf__UpdateSelection steps. */
enum SelectionStep {
    kSelectChoose = 0,
    kSelectWaitMove = 1,
    kSelectConfirm = 2,
    kSelectWaitConfirm = 3,
    kSelectCancel = 4,
    kSelectWaitCancel = 5,
    kSelectDone = 6
};

static inline int PlayerTextId(int player, int token) { return (player << 16) | token; }
static inline int UnusedAreaTextId(int player, int area) { return (player << 16) | kTextUnusedAreaName | area; }

/* _st0.._st3 hold the step of each nesting level of the selector's routines; a routine runs at one
 * level, and storing its step resets every deeper level. */
/* matching construct: stack-slot order — the step comes back through a reference: returned by
 * value it takes the last stack slot instead of the first in ShowAccessPlayers. */
static inline void LoadStep(beNDMWLoadIntf2DataSelIntf *self, int level, int &step) {
    switch (level) {
    default: step = self->_st0; break;
    case 1: step = self->_st1; break;
    case 2: step = self->_st2; break;
    case 3: step = self->_st3; break;
    }
}
static inline void StoreStep(beNDMWLoadIntf2DataSelIntf *self, int level, int step) {
    switch (level) {
    default: self->_st0 = step; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; break;
    case 1: self->_st1 = step; self->_st3 = 0; self->_st2 = 0; break;
    case 2: self->_st2 = step; self->_st3 = 0; break;
    case 3: self->_st3 = step; break;
    }
}

static inline beNDMWLoadSavePlWork *PlayerWork(beNDMWLoadCtrl2CommonIntf *common, int player) {
    return ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)common->_flagWork)->_data)[player];
}
static inline beNDMWLoadSlotPlayer *PlayerSlot(beNDMWLoadCtrl2CommonIntf *common, int player) {
    return (beNDMWLoadSlotPlayer *)PlayerWork(common, player)->_haveSaveData;
}
static inline beNDMWDegiData *SaveAreaData(beNDMWLoadCtrl2CommonIntf *common, int player, int area) {
    return ((beNDMWDegiData **)((beNDMWDegiDataList *)PlayerSlot(common, player)->_saveDataList)->_data)[area];
}
static inline beNDMWDegiData *GameUseData(beNDMWLoadCtrl2CommonIntf *common, int player) {
    return ((beNDMWDegiData **)((beNDMWDegiDataList *)common->_gameUseData)->_data)[player];
}
static inline beNDMWLoadIntf2DegiState *StatusWindowOf(beNDMWLoadIntf2DegiStateCtrl *statusCtrl, int which) {
    return ((beNDMWLoadIntf2DegiState **)((beNDMWLoadIntf2DegiStateList *)statusCtrl->_statDataList)->_data)[which];
}

/* Index of the player-model row whose model is the record's _dmkind (row 0 when none is). */
static inline int FindPlayerModelRow(beNDMWDegiData *data) {
    int row = 0;
    int index;
    for (index = 0; index < kPlayerModelRowCount; index++) {
        if (strcmp(g_playerModelRow[index].model, (const char *)data->_dmkind) == 0) { row = index; break; }
    }
    return row;
}

/* Starts `sequence` on the model window `window`, placed at the model controller's position. */
static inline void OpenWindowAtModels(beNDMWLoadIntf2DataSelIntf *self, beNDMWLoadIntf2ComMdlCtrl *models, const char *window, const char *sequence) {
    float position[3];
    position[0] = models->_pos[0];
    position[1] = models->_pos[1];
    position[2] = models->_pos[2];
    beNDMWLoadIntf2ComMdlCtrl__StartAt(models, self->_plNo, window, sequence, position, 1);
}

static inline void PlaySequence(beNDMWLoadIntf2ComMdlCtrl *models, int player, const char *window, const char *sequence) {
    beNDMWLoadIntf2ComMdlCtrl__Play(models, player, (int *)window, (int *)sequence, 0);
}

/* Clears `isFree` when another player already has the area's Digimon (same id and name) in play. */
static inline void CheckDigimonFree(beNDMWLoadIntf2DataSelIntf *self, beNDMWLoadCtrl2CommonIntf *common, beNDMWDegiData *area, unsigned char &isFree) {
    int other;
    for (other = 0; other < kPlayerCount; other++) {
        beNDMWDegiData *inGame;
        const char *inGameName;
        const char *areaName;
        if (other == self->_plNo) continue;
        inGame = GameUseData(common, other);
        if (inGame->_isUse != 1) continue;
        if (inGame->_id != area->_id) continue;
        inGameName = (const char *)inGame->_dmName;
        areaName = (const char *)area->_dmName;
        if (inGameName == 0 || areaName == 0) continue;
        if (strcmp(inGameName, areaName) == 0) { isFree = 0; break; }
    }
}

/* Whether no other player already has the area's Digimon in play. */
static inline unsigned char IsDigimonFree(beNDMWLoadIntf2DataSelIntf *self, beNDMWLoadCtrl2CommonIntf *common, beNDMWDegiData *area) {
    unsigned char isFree = 1;
    CheckDigimonFree(self, common, area, isFree);
    return isFree;
}

static inline void RequestPrompt(beNDMWLoadIntf2DataSelIntf *self, int mesWin, int mesKind, int message) {
    self->_mesKind = mesKind;
    beNDMWLoadIntf2MesWin__RequestMessage((beNDMWLoadIntf2MesWin *)mesWin, PlayerTextId(self->_plNo, message));
}

/* A text object for the selector's windows, from the selector's allocator.
 * matching construct: one expression and the handle's .value, not its conversion operator: every
 * extra node here stops the save-area callers from inlining this and ShowSaveAreaName's other callees. */
static inline beUnicodeObj *CreateUnicodeText(beNDMWLoadIntf2DataSelIntf *self) {
    int allocator = (int)igObject_GetAllocator(self);
    return beUnicodeObj_Create(g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1.value));
}

/* Fills `text` with the Digimon name of an area: the characters of _dmNameUni after its first, at
 * most kAreaNameLength of them, zero-padded. */
static inline void SetAreaName(igSmartPointer<beUnicodeObj> &text, beNDMWDegiData *data) {
    beUnicodeObj_AllocateBuffer(text.p, kAreaNameLength);
    unsigned short *name = (unsigned short *)text.p->_buffer;
    unsigned short *source = data->_dmNameUni;
    int length;
    for (length = 0; length < kAreaNameLength; length++) {
        name[length] = source[length + 1];
        if (name[length] == 0) break;
    }
    for (; length < kAreaNameLength; length++) name[length] = 0;
}

/* Opens the window of one of the player's save areas, with its Digimon's model when it is used. */
static inline void OpenSaveAreaWindow(beNDMWLoadIntf2DataSelIntf *self, beNDMWLoadIntf2ComMdlCtrl *models, int area, beNDMWDegiData *data) {
    if (data->_isUse == 1) {
        int row = FindPlayerModelRow(data);
        OpenWindowAtModels(self, models, g_saveAreaWindowNames[area], g_playerModelRow[row].openSequence);
    } else {
        OpenWindowAtModels(self, models, g_saveAreaWindowNames[area], (const char *)"SQ_NOOPEN");
    }
}

/* Shows the name line of one of the player's save areas: its Digimon's name, or the unused-area
 * line. */
static inline void ShowSaveAreaName(beNDMWLoadIntf2DataSelIntf *self, beNDMWLoadIntf2TextOrder *textOrder, int area, beNDMWDegiData *data) {
    if (data->_isUse == 1) {
        igSmartPointer<beUnicodeObj> name(CreateUnicodeText(self));
        SetAreaName(name, data);
        TextOrder_ConfigureUnicode(textOrder, "CHRSELFONT08", self->_plNo, area, name.p, 1, 0);
    } else {
        beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, UnusedAreaTextId(self->_plNo, area), 0);
    }
}

/* Closes the four save-area windows and clears their name lines, if they are open. */
static inline void CloseSaveAreaWindows(beNDMWLoadIntf2DataSelIntf *self, beNDMWLoadIntf2ComMdlCtrl *models, int textOrder) {
    if (self->_isSaveArea == 1) {
        beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareawin01", (const char *)"SQ_CLOSE", 1);
        beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareawin02", (const char *)"SQ_CLOSE", 1);
        beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareawin03", (const char *)"SQ_CLOSE", 1);
        beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareawin04", (const char *)"SQ_CLOSE", 1);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)textOrder, "CHRSELFONT08", self->_plNo, 0);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)textOrder, "CHRSELFONT08", self->_plNo, 1);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)textOrder, "CHRSELFONT08", self->_plNo, 2);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)textOrder, "CHRSELFONT08", self->_plNo, 3);
        self->_isSaveArea = 0;
    }
}

/* The string pool shared by every interned name, created on first use. */
static inline void *SharedStringPool(void) {
    if (g_stringPool == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    return g_stringPool;
}

/* The pooled copy of `text` (as the word a string field stores), holding one reference. */
static inline int InternString(const char *text) {
    return (int)StringPool_Intern((StringPool *)SharedStringPool(), text);
}

/* Drops one reference on an interned string; its StringTokenHeader sits just before the text. */
static inline void ReleaseStringToken(int token) {
    if (token != 0) {
        StringTokenHeader *header = (StringTokenHeader *)token - 1;
        int refCount = header->refCount - 1;
        header->refCount = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header->owner, header);
        }
    }
}

void beNDMWLoadIntf2DataSelIntf__Init(beNDMWLoadIntf2DataSelIntf *self, int player, int kind) {
    self->_plNo = player;
    self->_isEnd = 0;
    self->_kind = kind;
    self->_svDataSelPoint = 0;
    self->_isSaveArea = 0;
    self->_isUpStatWin = 0;
    self->_isDownStatWin = 0;
    self->_isSelCur = 0;
    StoreStep(self, 0, 0);
}

void beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(beNDMWLoadIntf2DataSelIntf *self, int level) {
    StoreStep(self, level, 0);
}

unsigned char beNDMWLoadIntf2DataSelIntf__OpenSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level) {
    /* matching construct: stack-slot order — the stack locals are declared in the order mesWin,
     * statusCtrl, done, and assigned in field order. */
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    int mesWin;
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl;
    unsigned char done;
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder;
    int step;
    done = 0;
    textOrder = self->_textOrder;
    mesWin = self->_mesWin;
    statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    LoadStep(self, level, step);
    switch (step) {
    case 0: {
        /* matching construct: register order — the model-row search is written out here so its
         * counters are declared before the area record. */
        int row;
        int index;
        beNDMWDegiData *data;
        int area;
        for (area = 0; area < kSaveAreaCount; area++) {
            data = SaveAreaData(common, self->_plNo, area);
            if (data->_isUse == 1) {
                if (*(const char *)data->_dmkind != 0) {
                    row = 0;
                    for (index = 0; index < kPlayerModelRowCount; index++) {
                        if (strcmp(g_playerModelRow[index].model, (const char *)data->_dmkind) == 0) { row = index; break; }
                    }
                    OpenWindowAtModels(self, models, g_saveAreaWindowNames[area], g_playerModelRow[row].openSequence);
                } else {
                    data->_isUse = 0;
                    OpenWindowAtModels(self, models, g_saveAreaWindowNames[area], (const char *)"SQ_NOOPEN");
                }
            } else {
                data->_isUse = 0;
                OpenWindowAtModels(self, models, g_saveAreaWindowNames[area], (const char *)"SQ_NOOPEN");
            }
        }
        self->_isSaveArea = 1;
        OpenWindowAtModels(self, models, (const char *)"j_saveareacursorr", (const char *)"SQ_OPEN");
        self->_isSelCur = 1;
        if (self->_kind == kDataSelLoad) {
            beNDMWDegiData *selected = SaveAreaData(common, self->_plNo, self->_svDataSelPoint);
            unsigned char isFree = 1;
            if (selected->_isUse == 1) CheckDigimonFree(self, common, selected, isFree);
            if (isFree == 1) {
                RequestPrompt(self, mesWin, kMesKindPrompt, kMesLoadSelectArea);
            } else {
                RequestPrompt(self, mesWin, kMesKindInUse, kMesLoadAreaInUse);
            }
            beNDMWLoadIntf2DegiState__RequestOpen(StatusWindowOf(statusCtrl, kUpperStatus), kStatusSaveArea, self->_svDataSelPoint);
        } else {
            RequestPrompt(self, mesWin, kMesKindPrompt, kMesSaveSelectArea);
            beNDMWLoadIntf2DegiState__RequestOpen(StatusWindowOf(statusCtrl, kUpperStatus), kStatusGameUse, self->_plNo);
        }
        self->_isUpStatWin = 1;
        step++;
        break;
    }
    case 1:
        if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kUpperStatus)) == 1 && beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            int area;
            for (area = 0; area < kSaveAreaCount; area++) {
                beNDMWDegiData *data = SaveAreaData(common, self->_plNo, area);
                if (data->_isUse == 1) {
                    igSmartPointer<beUnicodeObj> name(CreateUnicodeText(self));
                    SetAreaName(name, data);
                    TextOrder_ConfigureUnicode((beNDMWLoadIntf2TextOrder *)textOrder, "CHRSELFONT08", self->_plNo, area, name.p, 1, 0);
                } else {
                    data->_isUse = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, UnusedAreaTextId(self->_plNo, area), 0);
                }
            }
            done = 1;
            step++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__UpdateSelection(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    int trigger;
    int moveUp;
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    unsigned char moveDown;
    int step;
    unsigned char moveLeft;
    int mesWin = self->_mesWin;
    unsigned char moveRight;
    unsigned char done = 0;
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    LoadStep(self, level, step);
    trigger = 0;
    moveUp = 0;
    moveDown = 0;
    moveLeft = 0;
    moveRight = 0;
    if (PlayerWork(common, self->_plNo)->_isCtrl == 1) {
        bePadData *pad = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, self->_plNo);
        unsigned char pressedUp;
        int repeat;
        int stick;
        trigger = pad->_trigger;
        repeat = pad->_repeat;
        stick = pad->_lTrg | pad->_lRpt;
        /* matching construct: branch shape — up is set and then cleared, where the other directions
         * are a single test. */
        pressedUp = 1;
        if ((stick & kStickUp) == 0 && ((trigger | repeat) & kPadUp) == 0) pressedUp = 0;
        moveUp = pressedUp;
        moveDown = (stick & kStickDown) || ((trigger | repeat) & kPadDown);
        moveLeft = (stick & kStickLeft) || ((trigger | repeat) & kPadLeft);
        moveRight = (stick & kStickRight) || ((trigger | repeat) & kPadRight);
    }
    switch (step) {
    case kSelectChoose: {
        int next;
        int current;
        current = self->_svDataSelPoint;
        next = current;
        if (moveUp) {
            if (current == 2) next = 0; else if (current == 3) next = 1;
        } else if (moveDown) {
            if (current == 0) next = 2; else if (current == 1) next = 3;
        } else if (moveRight) {
            if (current == 0) next = 1; else if (current == 2) next = 3;
        } else if (moveLeft) {
            if (current == 1) next = 0; else if (current == 3) next = 2;
        }
        if (next != current) {
            self->_svDataSelPoint = next;
            if (self->_kind == kDataSelLoad) beNDMWLoadIntf2DegiState__RequestChange(StatusWindowOf(statusCtrl, kUpperStatus), kStatusSaveArea, self->_svDataSelPoint);
            PlaySequence(models, self->_plNo, (const char *)"j_saveareacursorr", (const char *)"SQ_MOVE");
            step = kSelectWaitMove;
        } else if (trigger & kPadCross) {
            if (self->_kind == kDataSelLoad) {
                beNDMWDegiData *selected = SaveAreaData(common, self->_plNo, current);
                if (selected->_isUse == 1 && IsDigimonFree(self, common, selected) == 1) {
                    beNDMWDegiData *inGame;
                    int name;
                    GameUseData(common, self->_plNo)->_isUse = 1;
                    GameUseData(common, self->_plNo)->_id = selected->_id;
                    inGame = GameUseData(common, self->_plNo);
                    name = InternString((const char *)selected->_dmName);
                    ReleaseStringToken(inGame->_dmName);
                    inGame->_dmName = name;
                    self->_isCancel = 0;
                    step = kSelectConfirm;
                }
            } else {
                beNDMWLoadCtrl2CommonIntf__GiveCtrlTo(common, self->_plNo);
                self->_isCancel = 0;
                step = kSelectConfirm;
            }
        } else if (trigger & kPadCircle) {
            step = kSelectCancel;
            self->_isCancel = 1;
        }
        if (self->_kind == kDataSelLoad) {
            beNDMWDegiData *selected;
            beNDMWLoadIntf2DegiState__RequestChange(StatusWindowOf(statusCtrl, kUpperStatus), kStatusSaveArea, self->_svDataSelPoint);
            selected = SaveAreaData(common, self->_plNo, self->_svDataSelPoint);
            if (selected->_isUse == 1) {
                if (IsDigimonFree(self, common, selected) == 1) {
                    if (self->_mesKind != kMesKindPrompt) RequestPrompt(self, mesWin, kMesKindPrompt, kMesLoadSelectArea);
                } else if (self->_mesKind != kMesKindInUse) {
                    RequestPrompt(self, mesWin, kMesKindInUse, kMesLoadAreaInUse);
                }
            } else if (self->_mesKind != kMesKindPrompt) {
                RequestPrompt(self, mesWin, kMesKindPrompt, kMesLoadSelectArea);
            }
        }
        break;
    }
    case kSelectWaitMove:
        if (self->_kind == kDataSelLoad) {
            if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kUpperStatus)) != 1) break;
        }
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            PlaySequence(models, self->_plNo, (const char *)"j_saveareacursorr", g_saveAreaLineSelectSeqs[self->_svDataSelPoint]);
            step = kSelectChoose;
        }
        break;
    case kSelectConfirm:
        beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareacursorr", g_saveAreaLineOnSeqs[self->_svDataSelPoint], 1);
        self->_isSelCur = 0;
        step = kSelectWaitConfirm;
        break;
    case kSelectWaitConfirm:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) step = kSelectDone;
        break;
    case kSelectCancel:
        beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareacursorr", (const char *)"SQ_CANCEL", 1);
        self->_isSelCur = 0;
        step = kSelectWaitCancel;
        break;
    case kSelectWaitCancel:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) step = kSelectDone;
        break;
    case kSelectDone:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__CloseAll(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder = self->_textOrder;
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    unsigned char done = 0;
    int step;
    LoadStep(self, level, step);
    switch (step) {
    case 0:
        CloseSaveAreaWindows(self, models, textOrder);
        if (self->_isUpStatWin == 1) {
            beNDMWLoadIntf2DegiState__RequestClose(StatusWindowOf(statusCtrl, kUpperStatus), 0);
        }
        if (self->_isDownStatWin == 1) {
            beNDMWLoadIntf2DegiState__RequestClose(StatusWindowOf(statusCtrl, kLowerStatus), 0);
        }
        if (self->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareacursorr", (const char *)"SQ_CLOSE", 1);
        }
        step++;
        break;
    case 1:
        if (self->_isUpStatWin == 1) {
            if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kUpperStatus)) != 1) break;
            self->_isUpStatWin = 0;
        }
        if (self->_isDownStatWin == 1) {
            if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kLowerStatus)) != 1) break;
            self->_isDownStatWin = 0;
        }
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
            done = 1;
            step++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__ShowSelectedStatus(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder = self->_textOrder;
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    unsigned char done = 0;
    int step;
    LoadStep(self, level, step);
    switch (step) {
    case 0:
        CloseSaveAreaWindows(self, models, textOrder);
        step++;
        break;
    case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
            step++;
            beNDMWLoadIntf2DegiState__RequestOpen(StatusWindowOf(statusCtrl, kLowerStatus), kStatusSaveArea, self->_svDataSelPoint);
            self->_isDownStatWin = 1;
        }
        break;
    case 2:
        if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kLowerStatus)) == 1) {
            done = 1;
            step++;
        }
        break;
    case 3: break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__RestoreSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder = self->_textOrder;
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    unsigned char done = 0;
    int step;
    LoadStep(self, level, step);
    switch (step) {
    case 0:
        beNDMWLoadIntf2DegiState__RequestClose(StatusWindowOf(statusCtrl, kLowerStatus), 0);
        self->_isDownStatWin = 0;
        step++;
        break;
    case 1:
        if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kLowerStatus)) == 1) step++;
        break;
    case 2: {
        int area;
        for (area = 0; area < kSaveAreaCount; area++) {
            OpenSaveAreaWindow(self, models, area, SaveAreaData(common, self->_plNo, area));
        }
        self->_isSaveArea = 1;
        step++;
        break;
    }
    case 3:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            int area;
            for (area = 0; area < kSaveAreaCount; area++) {
                ShowSaveAreaName(self, (beNDMWLoadIntf2TextOrder *)textOrder, area, SaveAreaData(common, self->_plNo, area));
            }
            step++;
        }
        break;
    case 4:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__CloseStatusWindows(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    unsigned char done = 0;
    int step;
    LoadStep(self, level, step);
    switch (step) {
    case 0:
        beNDMWLoadIntf2DegiState__RequestClose(StatusWindowOf(statusCtrl, kUpperStatus), 0);
        beNDMWLoadIntf2DegiState__RequestClose(StatusWindowOf(statusCtrl, kLowerStatus), 0);
        self->_isDownStatWin = 0;
        step++;
        self->_isUpStatWin = 0;
        break;
    case 1:
        if (beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kUpperStatus)) == 1 && beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kLowerStatus)) == 1) {
            step++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__OpenSlotSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level) {
    /* matching construct: stack-slot order — statusCtrl is declared before done, and both are
     * assigned in field order. */
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    beNDMWLoadIntf2DegiStateCtrl *statusCtrl;
    unsigned char done;
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder;
    int step;
    done = 0;
    textOrder = self->_textOrder;
    statusCtrl = (beNDMWLoadIntf2DegiStateCtrl *)self->_statDisp;
    LoadStep(self, level, step);
    switch (step) {
    case 0: {
        int area;
        for (area = 0; area < kSaveAreaCount; area++) {
            OpenSaveAreaWindow(self, models, area, SaveAreaData(common, self->_plNo, area));
        }
        self->_isSaveArea = 1;
        beNDMWLoadIntf2DegiState__RequestOpen(StatusWindowOf(statusCtrl, kUpperStatus), kStatusGameUse, self->_plNo);
        self->_isUpStatWin = 1;
        step++;
        break;
    }
    case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1 && beNDMWLoadIntf2DegiState__Update(StatusWindowOf(statusCtrl, kUpperStatus)) == 1) {
            int area;
            step++;
            for (area = 0; area < kSaveAreaCount; area++) {
                ShowSaveAreaName(self, (beNDMWLoadIntf2TextOrder *)textOrder, area, SaveAreaData(common, self->_plNo, area));
            }
        }
        break;
    case 2:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

bool beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int mesWin = self->_mesWin;
    bool done = 0;
    int step;
    LoadStep(self, level, step);
    switch (step) {
    case 0:
        if (self->_isSelCur == 0) {
            switch (self->_svDataSelPoint) {
            case 0: OpenWindowAtModels(self, models, (const char *)"j_saveareacursorr", (const char *)"SQ_AAREAOPEN"); break;
            case 1: OpenWindowAtModels(self, models, (const char *)"j_saveareacursorr", (const char *)"SQ_BAREAOPEN"); break;
            case 2: OpenWindowAtModels(self, models, (const char *)"j_saveareacursorr", (const char *)"SQ_CAREAOPEN"); break;
            case 3: OpenWindowAtModels(self, models, (const char *)"j_saveareacursorr", (const char *)"SQ_DAREAOPEN"); break;
            }
            self->_isSelCur = 1;
        }
        step++;
        break;
    case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) == 1) {
            step++;
            if (self->_kind == kDataSelLoad) beNDMWLoadIntf2MesWin__RequestMessage((beNDMWLoadIntf2MesWin *)mesWin, PlayerTextId(self->_plNo, kMesLoadSelectArea));
            else beNDMWLoadIntf2MesWin__RequestMessage((beNDMWLoadIntf2MesWin *)mesWin, PlayerTextId(self->_plNo, kMesSaveSelectArea));
        }
        break;
    case 2:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__CloseSaveArea(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder = self->_textOrder;
    bool done = 0;
    int step;
    LoadStep(self, level, step);
    switch (step) {
    case 0:
        CloseSaveAreaWindows(self, models, textOrder);
        if (self->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(models, self->_plNo, (const char *)"j_saveareacursorr", (const char *)"SQ_CLOSE", 1);
        }
        step++;
        break;
    case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) == 1) {
            done = 1;
            step++;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    StoreStep(self, level, step);
    return done;
}

unsigned char beNDMWLoadIntf2DataSelIntf__ShowAccessPlayers(beNDMWLoadIntf2DataSelIntf *self, int level) {
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    beNDMWLoadIntf2ComMdlCtrl *models = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    int textOrder = self->_textOrder;
    int step;
    LoadStep(self, level, step);
    int index;
    igIntList *accessPlayers = (igIntList *)PlayerSlot(common, self->_plNo)->_accessPlList;
    for (index = 0; index < accessPlayers->_count; index++) {
        int player = ((int *)accessPlayers->_data)[index];
        int area;
        for (area = 0; area < kSaveAreaCount; area++) {
            beNDMWDegiData *data = SaveAreaData(common, player, area);
            if (data->_isUse == 1) {
                int row = FindPlayerModelRow(data);
                PlaySequence(models, player, g_saveAreaWindowNames[area], g_playerModelRow[row].faceSequence);
                igSmartPointer<beUnicodeObj> name(CreateUnicodeText(self));
                SetAreaName(name, data);
                TextOrder_ConfigureUnicode((beNDMWLoadIntf2TextOrder *)textOrder, "CHRSELFONT08", player, area, name.p, 1, 0);
            } else {
                PlaySequence(models, player, g_saveAreaWindowNames[area], (const char *)"SQ_NOOPEN");
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, UnusedAreaTextId(player, area), 0);
            }
        }
    }
    StoreStep(self, level, step);
    return 1;
}

/* A Diffselect is a small line-choice window: kind 0 offers two lines ("j_linewin02"), kind 1 three
 * ("j_linewin03"). */
enum DiffselectKind {
    kDiffselectTwoLines = 0,
    kDiffselectThreeLines = 1
};
/* Diffselect::_st0: open the window, let the player choose a line, close the window. */
enum DiffselectPhase {
    kDiffselectOpen = 0,
    kDiffselectChoose = 1,
    kDiffselectClose = 2
};
/* Text ids of the Diffselect windows; the player number goes in the high half. */
enum DiffselectText {
    kDiffselectTwoLineText = 0x402,
    kDiffselectThreeLineText = 0x403,
    kDiffselectPromptMessage = 0x404
};
/* beNDMWLoadIntf2NameSel::_langID: the letter rows, the name length and the language cursor window
 * (j_namecursorjp for Japanese, j_namecursorus otherwise). */
enum NameSelLanguage {
    kNameLangJapanese = 0,
    kNameLangEnglish = 1,
    kNameLangEuropean = 2
};
/* Rows of g_nameEntryLetterRows: Japanese uses rows 0-23, English 0-3, European 24-29. */
enum NameEntryRow {
    kRowLowerCase = 0,
    kRowHiragana = 4,
    kRowEuropeanFirst = 24,
    kRowAccented = 28,
    kRowCount = 30
};
/* NameSelWork::letterState: how a character of the name is drawn (and whether it exists). */
enum NameSelLetterState {
    kLetterEmpty = 0,
    kLetterChoosing = 1,
    kLetterEntered = 2
};
/* beNDMWLoadIntf2NameSel::_st0. */
enum NameSelPhase {
    kNameSelOpen = 0,
    kNameSelTyping = 1,
    kNameSelFinishTyping = 2,
    kNameSelQuestion = 3,
    kNameSelGiveUp = 4,
    kNameSelShut = 5
};
/* beNDMWLoadIntf2NameSel::_st1 inside kNameSelTyping. */
enum NameSelTypingStep {
    kTypingInput = 0,
    kTypingAfterMove = 1,
    kTypingAfterErase = 2,
    kTypingAfterEnter = 3,
    kTypingAfterStart = 4
};
/* beNDMWLoadIntf2NameSel::_st1 inside kNameSelQuestion. */
enum NameSelQuestionStep {
    kQuestionAsk = 0,
    kQuestionWaitAnswer = 1,
    kQuestionAccept = 2,
    kQuestionAcceptWait = 3,
    kQuestionReject = 4,
    kQuestionRejectWait = 5
};
/* The letter window shows five columns of the current row. */
enum { kVisibleColumns = 5 };

static inline void DiffselectNextStep(beNDMWLoadIntf2Diffselect *self) {
    self->_st1 = self->_st1 + 1;
    self->_st3 = 0;
    self->_st2 = 0;
}

static inline void DiffselectNextPhase(beNDMWLoadIntf2Diffselect *self) {
    self->_st0 = self->_st0 + 1;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
}

void beNDMWLoadIntf2Diffselect__Init(beNDMWLoadIntf2Diffselect *self, int kind, int plNo) {
    self->_selectPoint = 0;
    self->_result = 0;
    self->_plNo = plNo;
    self->_result = 0;
    self->_kind = kind;
    self->_isEnd = 0;
    self->_isCancel = 0;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
    switch (self->_kind) {
    case kDiffselectTwoLines: self->_maxSel = 2; break;
    case kDiffselectThreeLines: self->_maxSel = 3; break;
    }
}

/* One step of the line choice: open the window and its text, move the cursor with up/down, Cross
 * takes the line into _result, Circle sets _isCancel; then close with the chosen line's sequence.
 * Returns _isEnd. */
unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, unsigned char usePad) {
    float twoLinePos[3], threeLinePos[3];
    int up, down; /* matching construct: declaration-order search — up/down declared first keep the pad repeat word in a2 */
    int trigger, stickEdge, repeat;
    bool upHeld, downHeld;
    beNDMWLoadIntf2ComMdlCtrl *comMdl;
    void *textOrder;
    void *mesWin;
    if (self->_isEnd == 1) return 1;
    comMdl = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
    textOrder = (void *)self->_textOrder;
    mesWin = (void *)self->_mesWin;
    trigger = 0;
    up = 0;
    down = 0;
    if ((usePad & 0xff) == 1) {
        bePadData *pad = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, self->_plNo);
        trigger = pad->_trigger;
        repeat = pad->_repeat;
        stickEdge = pad->_lTrg | pad->_lRpt;
        upHeld = 1;
        if ((stickEdge & kStickUp) == 0 && ((trigger | repeat) & kPadUp) == 0) upHeld = 0;
        up = upHeld & 0xff;
        downHeld = (stickEdge & kStickDown) || ((trigger | repeat) & kPadDown);
        down = downHeld;
    }
    switch (self->_st0) {
    case kDiffselectOpen:
        switch (self->_st1) {
        case 0:
            switch (self->_kind) {
            case kDiffselectTwoLines:
                twoLinePos[0] = comMdl->_pos[0]; twoLinePos[1] = comMdl->_pos[1]; twoLinePos[2] = comMdl->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt(comMdl, self->_plNo, (const char *)"j_linewin02", (const char *)"SQ_OPEN", twoLinePos, 1);
                break;
            case kDiffselectThreeLines:
                threeLinePos[0] = comMdl->_pos[0]; threeLinePos[1] = comMdl->_pos[1]; threeLinePos[2] = comMdl->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt(comMdl, self->_plNo, (const char *)"j_linewin03", (const char *)"SQ_OPEN", threeLinePos, 1);
                break;
            }
            DiffselectNextStep(self);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(comMdl) == 1) {
                switch (self->_kind) {
                case kDiffselectTwoLines: beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, (self->_plNo << 16) | kDiffselectTwoLineText, 0); break;
                case kDiffselectThreeLines: beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, (self->_plNo << 16) | kDiffselectThreeLineText, 0); break;
                }
                beNDMWLoadIntf2MesWin__RequestMessage((beNDMWLoadIntf2MesWin *)mesWin, (self->_plNo << 16) | kDiffselectPromptMessage);
                DiffselectNextPhase(self);
            }
            break;
        }
        break;
    case kDiffselectChoose:
        switch (self->_st1) {
        case 0:
            if (up != 0) {
                self->_selectPoint = self->_selectPoint - 1;
                if (self->_selectPoint < 0) { self->_selectPoint = 0; }
                else {
                    switch (self->_kind) {
                    case kDiffselectTwoLines:
                        beNDMWLoadIntf2ComMdlCtrl__Play(comMdl, self->_plNo, "j_linewin02", "SQ_LINEUP00", 1);
                        break;
                    case kDiffselectThreeLines:
                        if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Play(comMdl, self->_plNo, "j_linewin03", "SQ_LINEUP00", 1);
                        else beNDMWLoadIntf2ComMdlCtrl__Play(comMdl, self->_plNo, "j_linewin03", "SQ_LINEUP01", 1);
                        break;
                    }
                    DiffselectNextStep(self);
                }
            } else if (down != 0) {
                self->_selectPoint = self->_selectPoint + 1;
                if (self->_maxSel - 1 < self->_selectPoint) { self->_selectPoint = self->_maxSel - 1; }
                else {
                    switch (self->_kind) {
                    case kDiffselectTwoLines:
                        beNDMWLoadIntf2ComMdlCtrl__Play(comMdl, self->_plNo, "j_linewin02", "SQ_LINEDW01", 1);
                        break;
                    case kDiffselectThreeLines:
                        if (self->_selectPoint == 1) beNDMWLoadIntf2ComMdlCtrl__Play(comMdl, self->_plNo, "j_linewin03", "SQ_LINEDW01", 1);
                        else beNDMWLoadIntf2ComMdlCtrl__Play(comMdl, self->_plNo, "j_linewin03", "SQ_LINEDW02", 1);
                        break;
                    }
                    DiffselectNextStep(self);
                }
            } else if (trigger & kPadCross) {
                self->_result = self->_selectPoint;
                DiffselectNextPhase(self);
            } else if (trigger & kPadCircle) {
                self->_isCancel = 1;
                DiffselectNextPhase(self);
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(comMdl) == 1) { self->_st1 = 0; self->_st3 = 0; self->_st2 = 0; }
            break;
        }
        break;
    case kDiffselectClose:
        switch (self->_st1) {
        case 0:
            switch (self->_kind) {
            case kDiffselectTwoLines:
                TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, (self->_plNo << 16) | kDiffselectTwoLineText);
                if (self->_isCancel == 0) {
                    if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin02", (const char *)"SQ_LINEON00", 1);
                    else beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin02", (const char *)"SQ_LINEON01", 1);
                } else beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin02", (const char *)"SQ_CANCEL", 1);
                break;
            case kDiffselectThreeLines:
                TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, (self->_plNo << 16) | kDiffselectThreeLineText);
                if (self->_isCancel == 0) {
                    switch (self->_selectPoint) {
                    case 0: beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin03", (const char *)"SQ_LINEON00", 1); break;
                    case 1: beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin03", (const char *)"SQ_LINEON01", 1); break;
                    case 2: beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin03", (const char *)"SQ_LINEON02", 1); break;
                    }
                } else beNDMWLoadIntf2ComMdlCtrl__Close(comMdl, self->_plNo, (const char *)"j_linewin03", (const char *)"SQ_CANCEL", 1);
                break;
            }
            DiffselectNextStep(self);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(comMdl) == 1) self->_isEnd = 1;
            break;
        }
        break;
    }
    return self->_isEnd;
}

/* Starts a fresh name: the first character's cursor goes to the language's first letter row. */
static inline void NameSelBeginName(beNDMWLoadIntf2NameSel *nameSel, NameSelWork *work, int firstRow) {
    if (nameSel->_nameCurPos == -1) {
        work->enteredAt[0].tatePoint = firstRow;
        work->enteredAt[0].yokoPoint = 0;
        work->enteredAt[0].yokoCurPos = 0;
        nameSel->_nameCurPos = 0;
    }
}

void beNDMWLoadIntf2NameSel__Init(beNDMWLoadIntf2NameSel *nameSel, unsigned char resetName) {
    NameSelWork *work = &((NameSelRam *)nameSel)->t;
    int i;
    int j;
    nameSel->_langID = kNameLangEnglish;
    switch (nameSel->_langID) {
    case kNameLangJapanese:
        nameSel->_nameMojiMax = 6; nameSel->_tateMax = kRowEuropeanFirst; nameSel->_tateMin = kRowLowerCase;
        break;
    case kNameLangEnglish:
        nameSel->_nameMojiMax = 8; nameSel->_tateMax = kRowHiragana; nameSel->_tateMin = kRowLowerCase;
        break;
    default:
        nameSel->_nameMojiMax = 8; nameSel->_tateMax = kRowCount; nameSel->_tateMin = kRowEuropeanFirst;
        break;
    }
    if (resetName == 1) {
        for (i = 0; i < 6; i++) work->unusedFlags[i] = 0;
        nameSel->_nameCurPos = -1;
        for (i = 0; i < 9; i++) work->letterState[i] = kLetterEmpty;
        for (j = 0; j < 9; j++) work->name[j] = 0;
    }
    switch (nameSel->_langID) {
    case kNameLangJapanese:
        NameSelBeginName(nameSel, work, kRowHiragana);
        break;
    case kNameLangEnglish:
        NameSelBeginName(nameSel, work, kRowLowerCase);
        break;
    default:
    case kNameLangEuropean:
        NameSelBeginName(nameSel, work, kRowAccented);
        break;
    }
    nameSel->_tatePoint = work->enteredAt[nameSel->_nameCurPos].tatePoint;
    nameSel->_yokoPoint = work->enteredAt[nameSel->_nameCurPos].yokoPoint;
    nameSel->_yokoCurPos = work->enteredAt[nameSel->_nameCurPos].yokoCurPos;
    work->letterState[nameSel->_nameCurPos] = kLetterChoosing;
    nameSel->_isEnd = 0; nameSel->_isMakeName = 0; nameSel->_isQuestion = 0; nameSel->_isAnswer = 0; nameSel->_isNameOK = 0; nameSel->_isSideCur = 0;
    nameSel->_st0 = 0; nameSel->_st3 = 0; nameSel->_st2 = 0; nameSel->_st1 = 0;
}

/* A new text object for one letter of the name-entry fonts, from the owner's allocator when
 * g_useOwnerAllocator is set. */
static inline beUnicodeObj *NameSelNewLetterText(beNDMWLoadIntf2NameSel *nameSel) {
    int allocator = (int)igObject_GetAllocator(nameSel);
    allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    return beUnicodeObj_Create(allocator);
}

/* Shows one letter in text slot `slot` of the font line `font` of the player's text order; color 1
 * marks the character being chosen. */
static inline void NameSelShowLetter(beNDMWLoadIntf2NameSel *nameSel, const void *font, int slot, const unsigned short *letters, int index, int color) {
    igSmartPointer<beUnicodeObj> text(NameSelNewLetterText(nameSel));
    beUnicodeObj_AllocateBuffer(text.p, 1);
    *(unsigned short *)text.p->_buffer = letters[index];
    TextOrder_ConfigureUnicode((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, (const char *)font, nameSel->_ramNo, slot, text.p, 1, color);
}

/* The row column: the first letter of the previous, current and next row (wrapping inside the
 * language's rows). */
void beNDMWLoadIntf2NameSel__DrawRowLetters(beNDMWLoadIntf2NameSel *nameSel, int clear) {
    int row;
    switch (clear) {
    case 1:
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT10", nameSel->_ramNo, 0);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT10", nameSel->_ramNo, 1);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT10", nameSel->_ramNo, 2);
        return;
    case 0: {
        row = nameSel->_tatePoint - 1;
        if (row < nameSel->_tateMin) row = nameSel->_tateMax - 1;
        NameSelShowLetter(nameSel, "CHRSELFONT10", 0, g_nameEntryLetterRows[row].letters, 0, 0);
        row = nameSel->_tatePoint;
        NameSelShowLetter(nameSel, "CHRSELFONT10", 1, g_nameEntryLetterRows[row].letters, 0, 0);
        int nextRow = nameSel->_tatePoint + 1;
        /* matching construct: if/else on the unwrapped row — the if-without-else spelling pads the join label with a nop */
        if (nextRow >= nameSel->_tateMax) row = nameSel->_tateMin; else row = nextRow;
        NameSelShowLetter(nameSel, "CHRSELFONT10", 2, g_nameEntryLetterRows[row].letters, 0, 0);
    }
    }
}

/* The letter window: five letters of the current row starting at column _yokoPoint (wrapping
 * around the row). */
void beNDMWLoadIntf2NameSel__DrawColumnLetters(beNDMWLoadIntf2NameSel *nameSel, int clear) {
    int firstColumn;
    int column;
    int slot;
    switch (clear) {
    case 1:
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT11", nameSel->_ramNo, 0);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT11", nameSel->_ramNo, 1);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT11", nameSel->_ramNo, 2);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT11", nameSel->_ramNo, 3);
        TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT11", nameSel->_ramNo, 4);
        return;
    case 0:
        firstColumn = nameSel->_yokoPoint;
        for (slot = 0; slot < kVisibleColumns; slot++) {
            column = (firstColumn + slot) % g_nameEntryLetterRows[nameSel->_tatePoint].letterCount;
            igSmartPointer<beUnicodeObj> text(NameSelNewLetterText(nameSel));
            beUnicodeObj_AllocateBuffer(text.p, 1);
            *(unsigned short *)text.p->_buffer = g_nameEntryLetterRows[nameSel->_tatePoint].letters[column];
            TextOrder_ConfigureUnicode((beNDMWLoadIntf2TextOrder *)nameSel->_textOrder, "CHRSELFONT11", nameSel->_ramNo, slot, text.p, 1, 0);
        }
    }
}

/* Shows the characters typed so far (the one being chosen highlighted) and clears the slots past
 * the end of the name; Japanese names have six slots, the others eight. */
void beNDMWLoadIntf2NameSel__DrawEnteredName(NameSelRam *nameSel, int clear) {
    int japaneseSlot;
    int slot;
    switch (nameSel->n._langID) {
    case kNameLangJapanese:
        switch (clear) {
        case 1:
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, 0);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, 1);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, 2);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, 3);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, 4);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, 5);
            return;
        case 0:
            japaneseSlot = 0;
            do {
                if (nameSel->t.name[japaneseSlot] == 0) break;
                switch (nameSel->t.letterState[japaneseSlot]) {
                case kLetterEmpty: break;
                default: break;
                case kLetterChoosing: NameSelShowLetter(&nameSel->n, "CHRSELFONT12", japaneseSlot, nameSel->t.name, japaneseSlot, 1); break;
                case kLetterEntered: NameSelShowLetter(&nameSel->n, "CHRSELFONT12", japaneseSlot, nameSel->t.name, japaneseSlot, 0); break;
                }
                japaneseSlot++;
            } while (japaneseSlot < 6);
            for (; japaneseSlot < 6; japaneseSlot++) TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT12", nameSel->n._ramNo, japaneseSlot);
            return;
        }
        break;
    case kNameLangEnglish:
    default:
        switch (clear) {
        case 1:
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 0);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 1);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 2);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 3);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 4);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 5);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 6);
            TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, 7);
            return;
        case 0:
            slot = 0;
            do {
                if (nameSel->t.name[slot] == 0) break;
                switch (nameSel->t.letterState[slot]) {
                case kLetterEmpty: break;
                default: break;
                case kLetterChoosing: NameSelShowLetter(&nameSel->n, "CHRSELFONT13", slot, nameSel->t.name, slot, 1); break;
                case kLetterEntered: NameSelShowLetter(&nameSel->n, "CHRSELFONT13", slot, nameSel->t.name, slot, 0); break;
                }
                slot++;
            } while (slot < 8);
            for (; slot < 8; slot++) TextOrder_ClearFont((beNDMWLoadIntf2TextOrder *)nameSel->n._textOrder, "CHRSELFONT13", nameSel->n._ramNo, slot);
            break;
        }
        break;
    }
}

/* The answer to the "is this name right?" question asked while _isQuestion is set. */
void beNDMWLoadIntf2NameSel__SetAnswer(beNDMWLoadIntf2NameSel *nameSel, char isNameOK) {
    nameSel->_isNameOK = isNameOK;
    nameSel->_isAnswer = 1;
}


static inline beNDMWLoadIntf2ComMdlCtrl *NameSelComMdl(beNDMWLoadIntf2NameSel *sel) {
    return (beNDMWLoadIntf2ComMdlCtrl *)sel->_comMdlCtrl;
}

/* Opens one of the name-entry windows at the model controller's position. */
static inline void NameSelOpen(beNDMWLoadIntf2NameSel *sel, const char *window, const char *sequence, int track) {
    float pos[3];
    const float *at = NameSelComMdl(sel)->_pos;
    pos[0] = at[0]; pos[1] = at[1]; pos[2] = at[2];
    beNDMWLoadIntf2ComMdlCtrl__StartAt(NameSelComMdl(sel), sel->_ramNo, window, sequence, pos, track);
}

/* Opens the Digimon face window with the selected model's open sequence. */
static inline void NameSelOpenFace(beNDMWLoadIntf2NameSel *sel) {
    float pos[3];
    const float *at = NameSelComMdl(sel)->_pos;
    pos[0] = at[0]; pos[1] = at[1]; pos[2] = at[2];
    beNDMWLoadIntf2ComMdlCtrl__StartAt(NameSelComMdl(sel), sel->_ramNo, (const char *)"j_digifacewin", g_playerModelRow[sel->_selDataNo].openSequence, pos, 1);
}

static inline void NameSelPlay(beNDMWLoadIntf2NameSel *sel, char *window, char *sequence, int track) {
    beNDMWLoadIntf2ComMdlCtrl__Play(NameSelComMdl(sel), sel->_ramNo, (int *)window, (int *)sequence, track);
}

static inline void NameSelClose(beNDMWLoadIntf2NameSel *sel, const char *window, const char *sequence) {
    beNDMWLoadIntf2ComMdlCtrl__Close(NameSelComMdl(sel), sel->_ramNo, window, sequence, 1);
}

/* Opens the language's name cursor window on the character being chosen. */
static inline void NameSelOpenCursor(beNDMWLoadIntf2NameSel *sel) {
    char sequence[80];
    sprintf(sequence, "SQ_NAMESL0%d", sel->_nameCurPos);
    switch (sel->_langID) {
    case kNameLangJapanese: NameSelOpen(sel, "j_namecursorjp", sequence, 0); break;
    default: case kNameLangEnglish: NameSelOpen(sel, "j_namecursorus", sequence, 0); break;
    }
}

/* Plays a sequence on the language's name cursor window. */
static inline void NameSelPlayCursor(beNDMWLoadIntf2NameSel *sel, char *sequence, int track) {
    switch (sel->_langID) {
    case kNameLangJapanese: NameSelPlay(sel, "j_namecursorjp", sequence, track); break;
    default: case kNameLangEnglish: NameSelPlay(sel, "j_namecursorus", sequence, track); break;
    }
}

/* Plays the numbered cursor sequence (format + name position) on the language's cursor window. */
static inline void NameSelPlayCursorAt(beNDMWLoadIntf2NameSel *sel, char *format, int track) {
    char sequence[80];
    sprintf(sequence, format, sel->_nameCurPos);
    NameSelPlayCursor(sel, sequence, track);
}

static inline void NameSelCloseCursor(beNDMWLoadIntf2NameSel *sel, const char *sequence) {
    switch (sel->_langID) {
    case kNameLangJapanese: NameSelClose(sel, "j_namecursorjp", sequence); break;
    default: case kNameLangEnglish: NameSelClose(sel, "j_namecursorus", sequence); break;
    }
}

/* Moves the letter cursor ("j_namecursor02") to column _yokoCurPos of the letter window. */
static inline void NameSelMoveLetterCursor(beNDMWLoadIntf2NameSel *sel) {
    char sequence[80];
    sprintf(sequence, "SQ_SELECT0%d", sel->_yokoCurPos);
    NameSelPlay(sel, "j_namecursor02", sequence, 1);
}

/* Back from the question to typing: the cursor windows return to the character being chosen. */
static inline void NameSelShowCursorsAgain(beNDMWLoadIntf2NameSel *sel) {
    char sequence[80];
    sprintf(sequence, "SQ_NAMESL0%d", sel->_nameCurPos);
    NameSelPlayCursor(sel, sequence, 0);
    sprintf(sequence, "SQ_SELECT0%d", sel->_yokoCurPos);
    NameSelPlay(sel, "j_namecursor02", sequence, 1);
}

/* Puts the letter under the cursor into the name at the current position. */
static inline void NameSelTakeLetter(NameSelRam *nameSel) {
    nameSel->t.name[nameSel->n._nameCurPos] =
        g_nameEntryLetterRows[nameSel->n._tatePoint].letters[(nameSel->n._yokoPoint + nameSel->n._yokoCurPos) % g_nameEntryLetterRows[nameSel->n._tatePoint].letterCount];
}

/* Puts the cursor back where it stood when the current character was entered. */
static inline void NameSelRestoreCursor(NameSelRam *nameSel) {
    nameSel->n._tatePoint = nameSel->t.enteredAt[nameSel->n._nameCurPos].tatePoint;
    nameSel->n._yokoPoint = nameSel->t.enteredAt[nameSel->n._nameCurPos].yokoPoint;
    nameSel->n._yokoCurPos = nameSel->t.enteredAt[nameSel->n._nameCurPos].yokoCurPos;
}

/* After a row change: the side arrows are live only when the row is wider than the letter window. */
static inline void NameSelShowSideArrows(beNDMWLoadIntf2NameSel *sel) {
    if (g_nameEntryLetterRows[sel->_tatePoint].letterCount > kVisibleColumns) {
        NameSelPlay(sel, "j_namecursorleft", "SQ_SELECT00", 0);
        NameSelPlay(sel, "j_namecursorright", "SQ_SELECT00", 0);
        sel->_isSideCur = 1;
    } else {
        NameSelPlay(sel, "j_namecursorleft", "SQ_NOSELECT", 0);
        NameSelPlay(sel, "j_namecursorright", "SQ_NOSELECT", 0);
        sel->_isSideCur = 0;
    }
}

static inline void NameSelNextStep(beNDMWLoadIntf2NameSel *sel) {
    sel->_st1++;
    sel->_st3 = 0;
    sel->_st2 = 0;
}

static inline void NameSelGoToStep(beNDMWLoadIntf2NameSel *sel, int step) {
    sel->_st1 = step;
    sel->_st3 = 0;
    sel->_st2 = 0;
}

static inline void NameSelGoToPhase(beNDMWLoadIntf2NameSel *sel, int phase) {
    sel->_st0 = phase;
    sel->_st3 = 0;
    sel->_st2 = 0;
    sel->_st1 = 0;
}

/* One step of the name-entry state machine (_st0 the phase, _st1 the step inside it): open the
 * windows; type (up/down change the row, left/right the column, Cross enters the letter, Circle
 * erases, START finishes); ask whether the name is right (_isQuestion until SetAnswer); close
 * everything and set _isEnd (also when Circle erases past the first character). Returns _isEnd. */
int beNDMWLoadIntf2NameSel__Update(NameSelRam *nameSel, int usePad) {
    /* matching construct: declaration-order search — the order of the pad locals sets their registers */
    int trigger;
    bePadData *pad;
    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char upHeld;
    int repeat;
    unsigned char right;
    int stickEdge;
    beNDMWLoadIntf2NameSel *sel = &nameSel->n;
    if (sel->_isEnd == 1) return 1;
    trigger = 0; up = 0; down = 0; left = 0; right = 0;
    if ((usePad & 0xFF) == 1) {
        pad = bePadManager_GetPadForPlayer((bePadManager *)sel->_padManager, sel->_ramNo);
        trigger = pad->_trigger;
        repeat = pad->_repeat;
        stickEdge = pad->_lTrg | pad->_lRpt;
        upHeld = 1;
        if ((stickEdge & kStickUp) == 0 && ((trigger | repeat) & kPadUp) == 0) upHeld = 0;
        up = upHeld;
        down = (stickEdge & kStickDown) || ((trigger | repeat) & kPadDown);
        left = (stickEdge & kStickLeft) || ((trigger | repeat) & kPadLeft);
        right = (stickEdge & kStickRight) || ((trigger | repeat) & kPadRight);
    }
    switch (sel->_st0) {
    case kNameSelOpen:
        switch (sel->_st1) {
        case 0:
            NameSelOpenFace(sel);
            NameSelOpen(sel, "j_namecursor01", (const char *)"SQ_OPEN", 1);
            NameSelOpen(sel, "j_namecursor02", (const char *)"SQ_OPEN", 1);
            NameSelOpen(sel, "j_namewin01", (const char *)"SQ_OPEN", 1);
            NameSelOpen(sel, "j_namecursordown", (const char *)"SQ_OPEN", 1);
            NameSelOpen(sel, "j_namecursorup", (const char *)"SQ_OPEN", 1);
            NameSelOpen(sel, "j_namecursorleft", (const char *)"SQ_OPEN", 1);
            NameSelOpen(sel, "j_namecursorright", (const char *)"SQ_OPEN", 1);
            sel->_isSideCur = 1;
            NameSelTakeLetter(nameSel);
            NameSelOpenCursor(sel);
            beNDMWLoadIntf2NameSel__DrawRowLetters(sel, 0);
            beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
            beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
            NameSelNextStep(sel);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(NameSelComMdl(sel)) == 1) NameSelNextStep(sel);
            break;
        case 2:
            if (sel->_nameCurPos >= sel->_nameMojiMax) sel->_nameCurPos = sel->_nameMojiMax - 1;
            NameSelMoveLetterCursor(sel);
            NameSelNextStep(sel);
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(NameSelComMdl(sel)) == 1) NameSelGoToPhase(sel, kNameSelTyping);
            break;
        }
        break;
    case kNameSelTyping:
        switch (sel->_st1) {
        case kTypingInput:
            if (right) {
                sel->_yokoCurPos++;
                if (sel->_yokoCurPos >= kVisibleColumns) {
                    sel->_yokoCurPos = kVisibleColumns - 1;
                    if (g_nameEntryLetterRows[sel->_tatePoint].letterCount > kVisibleColumns) {
                        sel->_yokoPoint++;
                        if (sel->_yokoPoint >= g_nameEntryLetterRows[sel->_tatePoint].letterCount) sel->_yokoPoint = 0;
                        if (sel->_isSideCur == 1) {
                            NameSelPlay(sel, "j_namecursorright", "SQ_ON00", 1);
                            NameSelPlayCursorAt(sel, "SQ_NAMECG0%d", 1);
                        }
                        beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
                    }
                } else {
                    NameSelMoveLetterCursor(sel);
                    NameSelPlayCursorAt(sel, "SQ_NAMECG0%d", 1);
                }
                NameSelTakeLetter(nameSel);
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                NameSelNextStep(sel);
            } else if (left) {
                sel->_yokoCurPos--;
                if (sel->_yokoCurPos < 0) {
                    sel->_yokoCurPos = 0;
                    if (g_nameEntryLetterRows[sel->_tatePoint].letterCount > kVisibleColumns) {
                        sel->_yokoPoint--;
                        if (0 > sel->_yokoPoint) sel->_yokoPoint = g_nameEntryLetterRows[sel->_tatePoint].letterCount - 1;
                        beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
                        if (sel->_isSideCur == 1) {
                            NameSelPlay(sel, "j_namecursorleft", "SQ_ON00", 1);
                            NameSelPlayCursorAt(sel, "SQ_NAMECG0%d", 1);
                        }
                    }
                } else {
                    NameSelMoveLetterCursor(sel);
                    NameSelPlayCursorAt(sel, "SQ_NAMECG0%d", 1);
                }
                NameSelTakeLetter(nameSel);
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                NameSelNextStep(sel);
            } else if (up) {
                NameSelPlay(sel, "j_namecursorup", "SQ_ON00", 1);
                NameSelPlayCursorAt(sel, "SQ_NAMECG0%d", 1);
                sel->_tatePoint--;
                if (sel->_tatePoint < sel->_tateMin) sel->_tatePoint = sel->_tateMax - 1;
                NameSelShowSideArrows(sel);
                sel->_yokoPoint = 0;
                NameSelTakeLetter(nameSel);
                NameSelNextStep(sel);
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                beNDMWLoadIntf2NameSel__DrawRowLetters(sel, 0);
                beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
            } else if (down) {
                NameSelPlay(sel, "j_namecursordown", "SQ_ON00", 1);
                NameSelPlayCursorAt(sel, "SQ_NAMECG0%d", 1);
                sel->_tatePoint++;
                if (sel->_tatePoint >= sel->_tateMax) sel->_tatePoint = sel->_tateMin;
                NameSelShowSideArrows(sel);
                sel->_yokoPoint = 0;
                NameSelTakeLetter(nameSel);
                NameSelNextStep(sel);
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
                beNDMWLoadIntf2NameSel__DrawRowLetters(sel, 0);
            } else if (trigger & kPadCross) {
                if (sel->_nameCurPos < sel->_nameMojiMax) {
                    nameSel->t.enteredAt[sel->_nameCurPos].tatePoint = sel->_tatePoint;
                    nameSel->t.enteredAt[sel->_nameCurPos].yokoPoint = sel->_yokoPoint;
                    nameSel->t.enteredAt[sel->_nameCurPos].yokoCurPos = sel->_yokoCurPos;
                    nameSel->t.letterState[sel->_nameCurPos] = kLetterEntered;
                    NameSelTakeLetter(nameSel);
                    NameSelPlayCursorAt(sel, "SQ_NAMEON0%d", 1);
                    sel->_nameCurPos++;
                    nameSel->t.name[sel->_nameCurPos + 1] = 0;
                    nameSel->t.letterState[sel->_nameCurPos] = kLetterChoosing;
                    NameSelGoToStep(sel, kTypingAfterEnter);
                }
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
            } else if (trigger & kPadCircle) {
                nameSel->t.name[sel->_nameCurPos] = 0;
                sel->_nameCurPos--;
                NameSelPlayCursor(sel, "SQ_NAMECANCEL", 1);
                if (sel->_nameCurPos < 0) {
                    sel->_nameCurPos = -1;
                    NameSelGoToPhase(sel, kNameSelGiveUp);
                } else {
                    NameSelRestoreCursor(nameSel);
                    NameSelTakeLetter(nameSel);
                    NameSelMoveLetterCursor(sel);
                    beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
                    beNDMWLoadIntf2NameSel__DrawRowLetters(sel, 0);
                    NameSelGoToStep(sel, kTypingAfterErase);
                }
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
            } else if (trigger & kPadStart) {
                if (sel->_nameCurPos > 0) {
                    NameSelPlayCursorAt(sel, "SQ_NAMEON0%d", 1);
                    nameSel->t.name[sel->_nameCurPos] = 0;
                    sel->_nameCurPos--;
                    beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                    NameSelGoToStep(sel, kTypingAfterStart);
                }
            }
            break;
        case kTypingAfterMove:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(NameSelComMdl(sel)) != 0) NameSelGoToStep(sel, kTypingInput);
            break;
        case kTypingAfterErase:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(NameSelComMdl(sel)) != 0) {
                NameSelPlayCursorAt(sel, "SQ_NAMESL0%d", 0);
                nameSel->t.letterState[sel->_nameCurPos] = kLetterChoosing;
                beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                NameSelGoToStep(sel, kTypingInput);
            }
            break;
        case kTypingAfterEnter:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(NameSelComMdl(sel)) != 0) {
                if (sel->_nameCurPos >= sel->_nameMojiMax) {
                    sel->_nameCurPos = sel->_nameMojiMax - 1;
                    NameSelGoToPhase(sel, kNameSelFinishTyping);
                } else {
                    NameSelPlayCursorAt(sel, "SQ_NAMESL0%d", 0);
                    NameSelTakeLetter(nameSel);
                    beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
                }
                {
                    int i;
                    for (i = sel->_nameCurPos + 1; i < sel->_nameMojiMax; i++) nameSel->t.name[i] = 0;
                }
                NameSelGoToStep(sel, kTypingInput);
            }
            break;
        case kTypingAfterStart:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(NameSelComMdl(sel)) != 0) NameSelGoToPhase(sel, kNameSelFinishTyping);
            break;
        }
        break;
    case kNameSelFinishTyping:
        switch (sel->_st1) {
        case 0:
            NameSelPlayCursor(sel, "SQ_LINESL00", 1);
            NameSelNextStep(sel);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(NameSelComMdl(sel)) == 1) NameSelGoToPhase(sel, kNameSelQuestion);
            break;
        }
        break;
    case kNameSelQuestion:
        switch (sel->_st1) {
        case kQuestionAsk:
            sel->_isQuestion = 1;
            sel->_isAnswer = 0;
            NameSelNextStep(sel);
            break;
        case kQuestionWaitAnswer:
            if (sel->_isAnswer == 1) {
                sel->_isQuestion = 0;
                if (sel->_isNameOK == 1) { NameSelNextStep(sel); sel->_isMakeName = 1; }
                else { sel->_isMakeName = 0; NameSelGoToStep(sel, kQuestionReject); }
            }
            break;
        case kQuestionAccept:
            NameSelCloseCursor(sel, (const char *)"SQ_LINEON00");
            NameSelNextStep(sel);
            break;
        case kQuestionAcceptWait:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(NameSelComMdl(sel)) == 1) NameSelGoToPhase(sel, kNameSelShut);
            break;
        case kQuestionReject:
            NameSelRestoreCursor(nameSel);
            nameSel->t.letterState[sel->_nameCurPos] = kLetterChoosing;
            NameSelShowCursorsAgain(sel);
            beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 0);
            beNDMWLoadIntf2NameSel__DrawRowLetters(sel, 0);
            beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 0);
            NameSelNextStep(sel);
            break;
        case kQuestionRejectWait:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(NameSelComMdl(sel)) == 1) NameSelGoToPhase(sel, kNameSelTyping);
            break;
        }
        break;
    case kNameSelGiveUp:
        switch (sel->_st1) {
        case 0:
            NameSelCloseCursor(sel, (const char *)"SQ_CLOSE");
            NameSelNextStep(sel);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(NameSelComMdl(sel)) == 1) NameSelGoToPhase(sel, kNameSelShut);
            break;
        }
        break;
    case kNameSelShut:
        switch (sel->_st1) {
        case 0:
            beNDMWLoadIntf2NameSel__DrawRowLetters(sel, 1);
            beNDMWLoadIntf2NameSel__DrawColumnLetters(sel, 1);
            beNDMWLoadIntf2NameSel__DrawEnteredName(nameSel, 1);
            NameSelClose(sel, (const char *)"j_digifacewin", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namewin01", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namecursor01", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namecursor02", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namecursordown", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namecursorup", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namecursorleft", (const char *)"SQ_CLOSE");
            NameSelClose(sel, "j_namecursorright", (const char *)"SQ_CLOSE");
            NameSelNextStep(sel);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(NameSelComMdl(sel)) == 1) sel->_isEnd = 1;
            break;
        }
        break;
    }
    return sel->_isEnd;
}

/* beNDMWLoadIntf2SelSlot::_kindHard: which console's memory-card screen this is. Only the PS2
 * screen is built into this executable; the GameCube and Xbox cases do nothing. */
enum SelSlotHardware {
    SELSLOT_PS2 = 0,
    SELSLOT_GAMECUBE = 1,
    SELSLOT_XBOX = 2
};
/* beNDMWLoadIntf2SelSlot::_mode: the two plain card slots, or a multitap in slot 1 (four
 * multitap ports and slot 2). */
enum SelSlotLayout {
    SLOT_LAYOUT_TWO_SLOTS = 0,
    SLOT_LAYOUT_MULTITAP = 1
};
/* beNDMWLoadIntf2SelSlot::_st0: which of Open, UpdateSelection and Close is running. */
enum SelSlotState {
    SELSLOT_OPEN = 0,
    SELSLOT_SELECT = 1,
    SELSLOT_CLOSE = 2
};
/* Text-order line tokens of the slot screen. */
enum SelSlotText {
    SELSLOT_TEXT_TITLE = 0x100C,
    SELSLOT_TEXT_NO_CARD = 0x102E,
    SELSLOT_TEXT_SLOT1 = 0x1100,
    SELSLOT_TEXT_SLOT2 = 0x1101,
    SELSLOT_TEXT_SLOT1A = 0x1102,
    SELSLOT_TEXT_SLOT1B = 0x1103,
    SELSLOT_TEXT_SLOT1C = 0x1104,
    SELSLOT_TEXT_SLOT1D = 0x1105
};

static inline void EnterState(beNDMWLoadIntf2SelSlot *self, int n) { self->_st0 = n; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
static inline void NextState(beNDMWLoadIntf2SelSlot *self) { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
static inline void NextStep(beNDMWLoadIntf2SelSlot *self) { self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0; }
static inline void SetStep(beNDMWLoadIntf2SelSlot *self, int n) { self->_st1 = n; self->_st3 = 0; self->_st2 = 0; }
static inline int SlotTextId(beNDMWLoadIntf2SelSlot *self, int token) { return (self->_ramNo << 16) | token; }
static inline beNDMWLoadIntf2ComMdlCtrl *ModelCtrl(beNDMWLoadIntf2SelSlot *self) { return (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl; }
static inline beNDMWMcSlotList *McSlots(beNDMWLoadCtrl2CommonIntf *common) { return (beNDMWMcSlotList *)McUtil(common)->_slot; }
static inline beNDMWMcSlot *McSlotAt(beNDMWMcSlotList *slots, int index) { return ((beNDMWMcSlot **)slots->_data)[index]; }

/* The windows open at the model controller's position. */
static inline void CopyModelPos(beNDMWLoadIntf2SelSlot *self, float *pos) {
    beNDMWLoadIntf2ComMdlCtrl *mdl = ModelCtrl(self);
    pos[0] = mdl->_pos[0];
    pos[1] = mdl->_pos[1];
    pos[2] = mdl->_pos[2];
}

/* Model-controller slot of a window: each player owns perPlayer consecutive slots. */
static inline int ModelSlot(beNDMWLoadIntf2SelSlot *self, int perPlayer, int index) { return self->_ramNo * perPlayer + index; }

/* Opens a window at the model controller's position. */
static inline void OpenWindow(beNDMWLoadIntf2SelSlot *self, int perPlayer, int index, const void *model, const void *sequence, int recordOpen) {
    float pos[3];
    CopyModelPos(self, pos);
    beNDMWLoadIntf2ComMdlCtrl__StartAt(ModelCtrl(self), ModelSlot(self, perPlayer, index), (const char *)model, (const char *)sequence, pos, recordOpen);
}

/* Shows a card-present mark: opens its window, or replays the open sequence if it is already up. */
static inline void ShowMark(beNDMWLoadIntf2SelSlot *self, int perPlayer, int index, const void *model, const void *sequence) {
    if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(ModelCtrl(self), ModelSlot(self, perPlayer, index), (const char *)model) == 0) {
        float pos[3];
        CopyModelPos(self, pos);
        beNDMWLoadIntf2ComMdlCtrl__StartAt(ModelCtrl(self), ModelSlot(self, perPlayer, index), (const char *)model, (const char *)sequence, pos, 0);
    } else {
        beNDMWLoadIntf2ComMdlCtrl__Play(ModelCtrl(self), ModelSlot(self, perPlayer, index), model, sequence, 0);
    }
}

static inline void HideMark(beNDMWLoadIntf2SelSlot *self, int perPlayer, int index, const void *model) {
    if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(ModelCtrl(self), ModelSlot(self, perPlayer, index), (const char *)model) == 1) {
        beNDMWLoadIntf2ComMdlCtrl__Close(ModelCtrl(self), ModelSlot(self, perPlayer, index), (const char *)model, (const char *)"SQ_CLOSE", 0);
    }
}

/* Opens the slot cursor on the selected entry. */
static inline void OpenCursor(beNDMWLoadIntf2SelSlot *self, SlotCursorEntry *entries) {
    float pos[3];
    CopyModelPos(self, pos);
    beNDMWLoadIntf2ComMdlCtrl__StartAt(ModelCtrl(self), self->_ramNo, (const char *)"j_slotcursor", (const char *)entries[self->_selPoint].sequence, pos, 1);
}

/* Sets the "no memory card" line for the card under the cursor. */
static inline void ShowNoCardText(beNDMWLoadIntf2SelSlot *self, beNDMWLoadCtrl2CommonIntf *common, SlotCursorEntry *entries, int textOrder) {
    beNDMWMcSlotList *slots = McSlots(common);
    if (McSlotAt(slots, entries[self->_selPoint].mcSlot)->_isConnect != 1) {
        self->_mcStat = 0;
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_NO_CARD), 0);
    } else {
        self->_mcStat = 1;
        TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_NO_CARD));
    }
}

/* Shows or clears the "no memory card" line as the card under the cursor comes and goes. */
static inline void RefreshNoCardText(beNDMWLoadIntf2SelSlot *self, beNDMWLoadCtrl2CommonIntf *common, SlotCursorEntry *entries) {
    int textOrder = self->_textOrder;
    beNDMWMcSlotList *slots;
    if (self->_mcStat == 0) {
        slots = McSlots(common);
        if (McSlotAt(slots, entries[self->_selPoint].mcSlot)->_isConnect == 1) {
            self->_mcStat = 1;
            TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_NO_CARD));
        }
    } else {
        slots = McSlots(common);
        if (McSlotAt(slots, entries[self->_selPoint].mcSlot)->_isConnect != 1) {
            self->_mcStat = 0;
            beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_NO_CARD), 0);
        }
    }
}

/* Publishes the name line of the entry under the cursor. */
static inline void ShowTwoSlotName(beNDMWLoadIntf2SelSlot *self, int textOrder) {
    switch (self->_selPoint) {
    case 0:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT1), 0);
        break;
    case 1:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT2), 0);
        break;
    }
}

static inline void ShowMultitapName(beNDMWLoadIntf2SelSlot *self, int textOrder) {
    switch (self->_selPoint) {
    case 0:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT1A), 0);
        break;
    case 1:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT1B), 0);
        break;
    case 2:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT1C), 0);
        break;
    case 3:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT1D), 0);
        break;
    case 4:
        beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT2), 0);
        break;
    }
}

static inline void PlayCursor(beNDMWLoadIntf2SelSlot *self, const void *sequence, int wait) {
    beNDMWLoadIntf2ComMdlCtrl__Play(ModelCtrl(self), self->_ramNo, "j_slotcursor", sequence, wait);
}

void beNDMWLoadIntf2SelSlot__Reset(beNDMWLoadIntf2SelSlot *self) {
    self->_isOpen = 0;
    self->_isCansel = 0;
    self->_isEnd = 0;
    self->_isSelect = 0;
    self->_isEnd = 0;
    self->_st0 = 0;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st1 = 0;
}

void beNDMWLoadIntf2SelSlot__Init(beNDMWLoadIntf2SelSlot *self) {
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    beNDMWLoadIntf2SelSlot__Reset(self);
    self->_selPoint = 0;
    switch (common->_kindHard) {
    case SELSLOT_PS2:
        self->_selMax = 5;
        self->_kindHard = SELSLOT_PS2;
        break;
    case SELSLOT_GAMECUBE:
        self->_selMax = 2;
        self->_kindHard = SELSLOT_GAMECUBE;
        break;
    case SELSLOT_XBOX:
        self->_selMax = 9;
        self->_kindHard = SELSLOT_XBOX;
        break;
    }
}

unsigned char beNDMWLoadIntf2SelSlot__Open(beNDMWLoadIntf2SelSlot *self, int selPoint) {
    beNDMWLoadCtrl2CommonIntf *common;
    if (self->_st0 != SELSLOT_OPEN) {
        return 0;
    }
    common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    /* matching construct: variant search — the 'case SELSLOT_PS2:' label (its compare folds away) gives the default block a
       second edge, so the phase switch materialises its own compare constants */
    switch (self->_kindHard) {
    case SELSLOT_PS2:
    default:
        switch (self->_st1) {
        case 0:
            if (selPoint != -1) {
                self->_selPoint = selPoint;
            }
            if (McUtil(common)->_isMtap == 0) {
                OpenWindow(self, 1, 0, "j_slotbase", "SQ_OPENPS01", 1);
                self->_mode = SLOT_LAYOUT_TWO_SLOTS;
            } else {
                OpenWindow(self, 1, 0, "j_slotbase", "SQ_OPENPS02", 1);
                self->_mode = SLOT_LAYOUT_MULTITAP;
            }
            OpenWindow(self, 1, 0, "j_memoryiconwin", "SQ_OPEN", 1);
            self->_isReOpenReq = 0;
            NextStep(self);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(ModelCtrl(self)) == 1) {
                if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) {
                    SlotCursorEntry *entries = g_slotModeSelectSeqs;
                    int entry;
                    int textOrder;
                    OpenCursor(self, entries);
                    for (entry = 0; entry < 2; entry++) {
                        if (McSlotAt(McSlots(common), entries[entry].mcSlot)->_isConnect == 1) {
                            switch (entry) {
                            case 0:
                                ShowMark(self, 2, 0, "j_slotmark02", "SQ_OPEN01");
                                break;
                            case 1:
                                ShowMark(self, 2, 1, "j_slotmark02", "SQ_OPEN02");
                                break;
                            }
                        }
                    }
                    textOrder = self->_textOrder;
                    beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_TITLE), 0);
                    ShowTwoSlotName(self, textOrder);
                    ShowNoCardText(self, common, entries, textOrder);
                    NextStep(self);
                } else {
                    SlotCursorEntry *entries = g_slotMarkSelectSeqs;
                    int entry;
                    int textOrder;
                    OpenCursor(self, entries);
                    for (entry = 0; entry < 5; entry++) {
                        if (McSlotAt(McSlots(common), entries[entry].mcSlot)->_isConnect == 1) {
                            switch (entry) {
                            case 0:
                                ShowMark(self, 5, 0, "j_slotmark01", "SQ_OPEN1A");
                                break;
                            case 1:
                                ShowMark(self, 5, 1, "j_slotmark01", "SQ_OPEN1B");
                                break;
                            case 2:
                                ShowMark(self, 5, 2, "j_slotmark01", "SQ_OPEN1C");
                                break;
                            case 3:
                                ShowMark(self, 5, 3, "j_slotmark01", "SQ_OPEN1D");
                                break;
                            case 4:
                                ShowMark(self, 2, 0, "j_slotmark02", "SQ_OPEN02");
                                break;
                            }
                        }
                    }
                    textOrder = self->_textOrder;
                    beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_TITLE), 0);
                    ShowMultitapName(self, textOrder);
                    ShowNoCardText(self, common, entries, textOrder);
                    NextStep(self);
                }
            }
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(ModelCtrl(self)) == 1) {
                self->_isOpen = 1;
                NextState(self);
            }
            break;
        }
        break;
    case SELSLOT_GAMECUBE:
    case SELSLOT_XBOX:
        break;
    }
    return self->_isOpen;
}

/* Cross on a slot with a card hands the card to this player and picks the slot. */
static inline void ConfirmSlot(beNDMWLoadIntf2SelSlot *self, beNDMWLoadCtrl2CommonIntf *common, SlotCursorEntry *entries) {
    beNDMWMcSlotList *slots = McSlots(common);
    if (McSlotAt(slots, entries[self->_selPoint].mcSlot)->_isConnect == 1) {
        beNDMWLoadCtrl2CommonIntf__GiveCtrlTo(common, self->_ramNo);
        self->_mcSelPoint = entries[self->_selPoint].mcSlot;
        PlayCursor(self, "SQ_ON", 1);
        SetStep(self, 2);
    }
}

static inline void CancelSelection(beNDMWLoadIntf2SelSlot *self) {
    self->_isCansel = 1;
    PlayCursor(self, "SQ_CANCEL", 1);
    SetStep(self, 2);
}

static inline void MoveCursorTo(beNDMWLoadIntf2SelSlot *self, int selPoint) {
    if (self->_selPoint != selPoint) {
        self->_selPoint = selPoint;
        PlayCursor(self, "SQ_MOVE", 1);
        NextStep(self);
    }
}

unsigned char beNDMWLoadIntf2SelSlot__UpdateSelection(beNDMWLoadIntf2SelSlot *self, unsigned char usePad, unsigned char checkDone) {
    beNDMWLoadCtrl2CommonIntf *common;
    bePadData *pad;
    int trigger;
    int repeat;
    int stick;
    unsigned char upPressed;
    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char right;
    SlotCursorEntry *entries;
    int entry;
    SlotCursorEntry *cursor;
    if (checkDone == 1) {
        if (self->_st0 != SELSLOT_SELECT) {
            return 0;
        }
        if (self->_isSelect == 1) {
            return 1;
        }
    }
    common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    trigger = 0;
    up = 0;
    down = 0;
    left = 0;
    right = 0;
    if (usePad == 1) {
        pad = bePadManager_GetPadForPlayer((bePadManager *)self->_padManager, self->_ramNo);
        trigger = pad->_trigger;
        repeat = pad->_repeat;
        stick = pad->_lTrg | pad->_lRpt;
        /* matching construct: manual variant — up is preset and cleared; the || spelling used for the other
           directions drops an instruction here */
        upPressed = 1;
        if ((stick & kStickUp) == 0 && ((trigger | repeat) & kPadUp) == 0)
            upPressed = 0;
        up = upPressed;
        down = ((stick & kStickDown) != 0) || (((trigger | repeat) & kPadDown) != 0);
        left = ((stick & kStickLeft) != 0) || (((trigger | repeat) & kPadLeft) != 0);
        right = ((stick & kStickRight) != 0) || (((trigger | repeat) & kPadRight) != 0);
    }
    switch (self->_kindHard) {
    default: {
        if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) {
            entries = g_slotModeSelectSeqs;
            for (entry = 0, cursor = entries; entry < 2; entry++, cursor++) {
                if (McSlotAt(McSlots(common), cursor->mcSlot)->_isConnect == 1) {
                    switch (entry) {
                    case 0:
                        ShowMark(self, 2, 0, "j_slotmark02", "SQ_OPEN01");
                        break;
                    case 1:
                        ShowMark(self, 2, 1, "j_slotmark02", "SQ_OPEN02");
                        break;
                    }
                } else {
                    switch (entry) {
                    case 0:
                        HideMark(self, 2, 0, "j_slotmark02");
                        break;
                    case 1:
                        HideMark(self, 2, 1, "j_slotmark02");
                        break;
                    }
                }
            }
            RefreshNoCardText(self, common, entries);
            /* a multitap was plugged in: reopen the screen in the multitap layout */
            if (McUtil(common)->_isMtap == 1) {
                self->_isReOpenReq = 1;
                self->_isSelect = 1;
                NextState(self);
                break;
            }
        } else {
            entries = g_slotMarkSelectSeqs;
            for (entry = 0, cursor = entries; entry < 5; entry++, cursor++) {
                if (McSlotAt(McSlots(common), cursor->mcSlot)->_isConnect == 1) {
                    switch (entry) {
                    case 0:
                        ShowMark(self, 5, 0, "j_slotmark01", "SQ_OPEN1A");
                        break;
                    case 1:
                        ShowMark(self, 5, 1, "j_slotmark01", "SQ_OPEN1B");
                        break;
                    case 2:
                        ShowMark(self, 5, 2, "j_slotmark01", "SQ_OPEN1C");
                        break;
                    case 3:
                        ShowMark(self, 5, 3, "j_slotmark01", "SQ_OPEN1D");
                        break;
                    case 4:
                        ShowMark(self, 2, 0, "j_slotmark02", "SQ_OPEN02");
                        break;
                    }
                } else {
                    switch (entry) {
                    case 0:
                        HideMark(self, 5, 0, "j_slotmark01");
                        break;
                    case 1:
                        HideMark(self, 5, 1, "j_slotmark01");
                        break;
                    case 2:
                        HideMark(self, 5, 2, "j_slotmark01");
                        break;
                    case 3:
                        HideMark(self, 5, 3, "j_slotmark01");
                        break;
                    case 4:
                        HideMark(self, 2, 0, "j_slotmark02");
                        break;
                    }
                }
            }
            /* the multitap was pulled out: reopen the screen in the two-slot layout */
            if (McUtil(common)->_isMtap == 0) {
                self->_isReOpenReq = 1;
                self->_isSelect = 1;
                NextState(self);
                break;
            }
            RefreshNoCardText(self, common, entries);
        }
        switch (self->_st1) {
        case 0:
            if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) {
                if (up) {
                    MoveCursorTo(self, 0);
                } else if (down) {
                    MoveCursorTo(self, 1);
                } else if (trigger & kPadCross) {
                    ConfirmSlot(self, common, entries);
                } else if (trigger & kPadCircle) {
                    CancelSelection(self);
                }
            } else if (trigger & kPadCross) {
                ConfirmSlot(self, common, entries);
            } else if (trigger & kPadCircle) {
                CancelSelection(self);
            } else if (up) {
                MoveCursorTo(self, 0);
            } else if (down) {
                /* down jumps to slot 2, the last entry */
                MoveCursorTo(self, self->_selMax - 1);
            } else if (self->_selPoint != self->_selMax - 1) {
                /* left/right move along the multitap ports, never onto slot 2 */
                if (right) {
                    self->_selPoint = self->_selPoint + 1;
                    if (self->_selPoint >= self->_selMax - 1) {
                        self->_selPoint = self->_selMax - 2;
                    } else {
                        PlayCursor(self, "SQ_MOVE", 1);
                        NextStep(self);
                    }
                } else if (left) {
                    self->_selPoint = self->_selPoint - 1;
                    if (self->_selPoint < 0) {
                        self->_selPoint = 0;
                    } else {
                        PlayCursor(self, "SQ_MOVE", 1);
                        NextStep(self);
                    }
                }
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(ModelCtrl(self)) == 1) {
                int textOrder;
                PlayCursor(self, entries[self->_selPoint].sequence, 0);
                textOrder = self->_textOrder;
                if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) {
                    ShowTwoSlotName(self, textOrder);
                } else {
                    ShowMultitapName(self, textOrder);
                }
                RefreshNoCardText(self, common, entries);
                SetStep(self, 0);
            }
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(ModelCtrl(self)) == 1) {
                PlayCursor(self, entries[self->_selPoint].sequence, 0);
                self->_isSelect = 1;
                NextState(self);
            }
            break;
        }
        break;
    }
    case SELSLOT_GAMECUBE:
    case SELSLOT_XBOX:
        break;
    }
    return self->_isSelect;
}

void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *self) {
    SlotCursorEntry *entries;
    EnterState(self, SELSLOT_SELECT);
    self->_isSelect = 0;
    switch (self->_kindHard) {
    default:
        if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) entries = g_slotModeSelectSeqs;
        else entries = g_slotMarkSelectSeqs;
        break;
    case SELSLOT_GAMECUBE:
    case SELSLOT_XBOX:
        break;
    }
    PlayCursor(self, entries[self->_selPoint].sequence, 0);
}

static inline void CloseSlotWindows(beNDMWLoadIntf2SelSlot *self) {
    int textOrder;
    beNDMWLoadIntf2ComMdlCtrl__Close(ModelCtrl(self), self->_ramNo, (const char *)"j_slotbase", (const char *)"SQ_CLOSE", 1);
    beNDMWLoadIntf2ComMdlCtrl__Close(ModelCtrl(self), self->_ramNo, (const char *)"j_slotcursor", (const char *)"SQ_CLOSE", 1);
    beNDMWLoadIntf2ComMdlCtrl__Close(ModelCtrl(self), self->_ramNo, (const char *)"j_memoryiconwin", (const char *)"SQ_CLOSE", 1);
    textOrder = self->_textOrder;
    TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_TITLE));
    TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_SLOT1));
    TextOrder_PublishLineListOnly((beNDMWLoadIntf2TextOrder *)textOrder, SlotTextId(self, SELSLOT_TEXT_NO_CARD));
}

unsigned char beNDMWLoadIntf2SelSlot__Close(beNDMWLoadIntf2SelSlot *self) {
    if (self->_st0 != SELSLOT_CLOSE) return 0;
    if (self->_isEnd == 1) return 1;
    switch (self->_kindHard) {
    case SELSLOT_PS2:
    default:
        switch (self->_st1) {
        case 0:
            if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) {
                int entry;
                CloseSlotWindows(self);
                for (entry = 0; entry < 2; entry++) {
                    switch (entry) {
                    case 0:
                        HideMark(self, 2, 0, "j_slotmark02");
                        break;
                    case 1:
                        HideMark(self, 2, 1, "j_slotmark02");
                        break;
                    }
                }
            } else {
                int entry;
                CloseSlotWindows(self);
                for (entry = 0; entry < 5; entry++) {
                    switch (entry) {
                    case 0:
                        HideMark(self, 5, 0, "j_slotmark01");
                        break;
                    case 1:
                        HideMark(self, 5, 1, "j_slotmark01");
                        break;
                    case 2:
                        HideMark(self, 5, 2, "j_slotmark01");
                        break;
                    case 3:
                        HideMark(self, 5, 3, "j_slotmark01");
                        break;
                    case 4:
                        HideMark(self, 2, 0, "j_slotmark02");
                        break;
                    }
                }
            }
            NextStep(self);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(ModelCtrl(self)) == 1) {
                self->_isEnd = 1;
                NextStep(self);
            }
            break;
        }
        break;
    case SELSLOT_GAMECUBE:
    case SELSLOT_XBOX:
        break;
    }
    return self->_isEnd;
}

void beNDMWLoadIntf2SelSlot__RefreshSlotMarks(beNDMWLoadIntf2SelSlot *self, int lostEntry) {
    beNDMWLoadCtrl2CommonIntf *common = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    SlotCursorEntry *entries;
    switch (self->_kindHard) {
    default: {
        if (self->_mode == SLOT_LAYOUT_TWO_SLOTS) {
            int entry;
            SlotCursorEntry *cursor;
            entries = g_slotModeSelectSeqs;
            for (entry = 0, cursor = entries; entry < 2; entry++, cursor++) {
                unsigned char connected = McSlotAt(McSlots(common), cursor->mcSlot)->_isConnect;
                if (lostEntry == entry) connected = 0;
                if (connected == 1) {
                    switch (entry) {
                    case 0:
                        ShowMark(self, 2, 0, "j_slotmark02", "SQ_OPEN01");
                        break;
                    case 1:
                        ShowMark(self, 2, 1, "j_slotmark02", "SQ_OPEN02");
                        break;
                    }
                } else {
                    switch (entry) {
                    case 0:
                        HideMark(self, 2, 0, "j_slotmark02");
                        break;
                    case 1:
                        HideMark(self, 2, 1, "j_slotmark02");
                        break;
                    }
                }
            }
            RefreshNoCardText(self, common, entries);
        } else {
            int entry;
            SlotCursorEntry *cursor;
            entries = g_slotMarkSelectSeqs;
            for (entry = 0, cursor = entries; entry < 5; entry++, cursor++) {
                unsigned char connected = McSlotAt(McSlots(common), cursor->mcSlot)->_isConnect;
                if (lostEntry == entry) connected = 0;
                if (connected == 1) {
                    switch (entry) {
                    case 0:
                        ShowMark(self, 5, 0, "j_slotmark01", "SQ_OPEN1A");
                        break;
                    case 1:
                        ShowMark(self, 5, 1, "j_slotmark01", "SQ_OPEN1B");
                        break;
                    case 2:
                        ShowMark(self, 5, 2, "j_slotmark01", "SQ_OPEN1C");
                        break;
                    case 3:
                        ShowMark(self, 5, 3, "j_slotmark01", "SQ_OPEN1D");
                        break;
                    case 4:
                        ShowMark(self, 2, 0, "j_slotmark02", "SQ_OPEN02");
                        break;
                    }
                } else {
                    switch (entry) {
                    case 0:
                        HideMark(self, 5, 0, "j_slotmark01");
                        break;
                    case 1:
                        HideMark(self, 5, 1, "j_slotmark01");
                        break;
                    case 2:
                        HideMark(self, 5, 2, "j_slotmark01");
                        break;
                    case 3:
                        HideMark(self, 5, 3, "j_slotmark01");
                        break;
                    case 4:
                        HideMark(self, 2, 0, "j_slotmark02");
                        break;
                    }
                }
            }
            RefreshNoCardText(self, common, entries);
        }
        break;
    }
    case SELSLOT_GAMECUBE:
    case SELSLOT_XBOX:
        break;
    }
}

#include "dw4/core/igobject_release.h"

extern "C" {
/* The model position of each interface kind (one per player). */

int beNDMWLoadIntf2_OnMessage(beNDMWLoadIntf2 *self, beBaseInfoRam *ram, beMessengerWork *message);
}

/* The values of the LoadIntf2 Message enum (LoadIntf2Message_GetMetaEnum). */
enum LoadIntf2Message {
    MSG_GENERATE = 0,
    MSG_LINKCOMMON = 1,
    MSG_ISENTRY = 2,
    MSG_ISRDY = 3,
    MSG_ONCTRL = 4,
    MSG_OFFCTRL = 5,
    MSG_SETSELECT_DATA = 6,
    MSG_SETDIFFICULTMAX = 7
};

/* The allocator for objects an owner creates: its own, or the default selector's. */
static inline int OwnerAllocator(void *owner) {
    int ownAllocator = (int)igObject_GetAllocator((igObject *)owner);
    if (g_useOwnerAllocator != 0) {
        return ownAllocator;
    }
    return (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
}

/* The model request at `index` of one of the controller's queues. */
static inline beLoadIntf2ComMdlData *QueuedRequest(int queue, int index) {
    return ((beLoadIntf2ComMdlData **)((beLoadIntf2ComMdlDataList *)queue)->_data)[index];
}

/* Releases the request at `index` and removes it from the queue, clearing the vacated last slot. */
static inline void DropQueuedRequest(beLoadIntf2ComMdlDataList *queue, int index) {
    igRelease(((igObject **)queue->_data)[index]);
    List_RemoveWordAt((igDataList *)queue, index);
    ((beLoadIntf2ComMdlData **)queue->_data)[queue->_count] = 0;
}

/* Drops one reference on an object, destroying it when the count (low 23 bits) reaches zero. */
static inline void ReleaseReference(ObjectRefTarget *object)
{
    if (object) {
        --object->references;
        if ((object->references & 0x7fffff) == 0)
            igObject_Destroy((igObject *)object);
    }
}

/* Replaces the info record's child list with `list`: retains it and releases the old one. */
static inline void SetDataList(beBaseInfoRam *ram, beBaseInfoDataList *list) {
    igObject *previous;

    if (list != 0) {
        list->_refCount = list->_refCount + 1;
    }
    previous = (igObject *)ram->_dataList;
    igRelease(previous);
    ram->_dataList = (int)list;
}

/* The info record's child list: created on first use with the record's own allocator, and
 * searched by child name. */
struct ChildList {
    static inline void Create(beBaseInfoRam *ram, int allocator) {
        igSmartPointer<beBaseInfoDataList> created((beBaseInfoDataList *)beBaseInfoDataList_Create(allocator));
        SetDataList(ram, created.p);
    }
    static inline void Ensure(beBaseInfoRam *ram) {
        if (ram->_dataList == 0) {
            Create(ram, OwnerAllocator(ram));
        }
    }
    static inline void *Find(beBaseInfoRam *ram, const void *name) {
        Ensure(ram);
        return (void *)igProperty_FindByName((igObjectList *)ram->_dataList, g_propertyNameField, (const char *)name);
    }
};

/* Asks the MODELCTRL receivers named (infoName, ramNo) to "GENERATE", then sends them `openSQ`. When
 * `recordOpen` is 1 the request (ram number and the pooled names) is also queued on the open list,
 * which Poll empties once the model is in that sequence. */
void beNDMWLoadIntf2ComMdlCtrl__Start(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, int recordOpen) {
    /* matching construct: declaration-order sweep — the pooled names as function-scope pointers,
     * declared before the request, set the s-register colouring of the reused parameter registers */
    const char *infoToken;
    const char *sequenceToken;
    beLoadIntf2ComMdlData *request;

    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", infoName, ramNo, "GENERATE");
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", infoName, ramNo, openSQ);
    if ((recordOpen & 0xFF) == 1) {
        igSmartPointer<beLoadIntf2ComMdlData> created(beLoadIntf2ComMdlData__Create(OwnerAllocator(self)));
        created.p->_ramNo = ramNo;
        request = created.p;
        infoToken = (const char *)InternString(infoName);
        ReleaseStringToken(request->_infoName);
        request->_infoName = (int)infoToken;
        request = created.p;
        sequenceToken = (const char *)InternString(openSQ);
        ReleaseStringToken(request->_openSQ);
        request->_openSQ = (int)sequenceToken;
        ObjectList_AppendRetained((igObjectList *)self->_openDataList, (igObject *)created.p);
    }
}

/* Start, with the model generated at `position`. */
void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, float *position, int recordOpen) {
    /* matching construct: declaration-order sweep — as in Start */
    const char *infoToken;
    const char *sequenceToken;
    beLoadIntf2ComMdlData *request;
    igVec3f at;

    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", infoName, ramNo);
    at.x = position[0];
    at.y = position[1];
    at.z = position[2];
    beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&at);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", infoName, ramNo, openSQ);
    if ((recordOpen & 0xFF) == 1) {
        igSmartPointer<beLoadIntf2ComMdlData> created(beLoadIntf2ComMdlData__Create(OwnerAllocator(self)));
        created.p->_ramNo = ramNo;
        request = created.p;
        infoToken = (const char *)InternString(infoName);
        ReleaseStringToken(request->_infoName);
        request->_infoName = (int)infoToken;
        request = created.p;
        sequenceToken = (const char *)InternString(openSQ);
        ReleaseStringToken(request->_openSQ);
        request->_openSQ = (int)sequenceToken;
        ObjectList_AppendRetained((igObjectList *)self->_openDataList, (igObject *)created.p);
    }
}

/* Sends `sequenceName` to the model `modelName` of `slot`; with `wait` 1 the request is queued on
 * the open list like an opening sequence. */
void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const void *modelName, const void *sequenceName, int wait) {
    /* matching construct: declaration-order sweep — as in Start */
    const char *infoToken;
    const char *sequenceToken;
    beLoadIntf2ComMdlData *request;

    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", (const char *)modelName, slot, (const char *)sequenceName);
    if ((wait & 0xFF) == 1) {
        igSmartPointer<beLoadIntf2ComMdlData> created(beLoadIntf2ComMdlData__Create(OwnerAllocator(self)));
        created.p->_ramNo = slot;
        request = created.p;
        infoToken = (const char *)InternString((const char *)modelName);
        ReleaseStringToken(request->_infoName);
        request->_infoName = (int)infoToken;
        request = created.p;
        sequenceToken = (const char *)InternString((const char *)sequenceName);
        ReleaseStringToken(request->_openSQ);
        request->_openSQ = (int)sequenceToken;
        ObjectList_AppendRetained((igObjectList *)self->_openDataList, (igObject *)created.p);
    }
}

/* Whether the model (infoName, ramNo) is playing the sequence `sqName` (the ISSEQNAME query). */
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, const char *infoName, const char *sqName) {
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", infoName, ramNo);
    beMessenger_AppendString((beMessenger *)self->_messenger, sqName);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ISSEQNAME");
    return beMessenger_GetBool((beMessenger *)self->_messenger, 0);
}

/* True once every queued opening sequence has started. */
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self) {
    return ((beLoadIntf2ComMdlDataList *)self->_openDataList)->_count <= 0;
}

/* Sends `openSequence` (the closing sequence) to the model (infoName, ramNo); with `trackClose` 1
 * the request is queued on the close list, which Poll empties once the model stops running. */
void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose) {
    /* matching construct: declaration-order sweep — as in Start */
    const char *infoToken;
    const char *sequenceToken;
    beLoadIntf2ComMdlData *request;

    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", infoName, ramNo, openSequence);
    if (trackClose == 1) {
        igSmartPointer<beLoadIntf2ComMdlData> created(beLoadIntf2ComMdlData__Create(OwnerAllocator(self)));
        created.p->_ramNo = ramNo;
        request = created.p;
        infoToken = (const char *)InternString(infoName);
        ReleaseStringToken(request->_infoName);
        request->_infoName = (int)infoToken;
        request = created.p;
        sequenceToken = (const char *)InternString(openSequence);
        ReleaseStringToken(request->_openSQ);
        request->_openSQ = (int)sequenceToken;
        ObjectList_AppendRetained((igObjectList *)self->_closeDataList, (igObject *)created.p);
    }
}

/* Whether the model (name, slot) is still running (the ISRUN query). */
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const char *name) {
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", name, slot, "ISRUN");
    return beMessenger_GetBool((beMessenger *)self->_messenger, 0);
}

/* True once every queued closing model has stopped. */
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self) {
    return ((beLoadIntf2ComMdlDataList *)self->_closeDataList)->_count <= 0;
}

/* Retires queued requests from the newest back: open requests whose model has reached its
 * sequence, then close requests whose model has stopped; each pass stops at the first request
 * still pending. */
void beNDMWLoadIntf2ComMdlCtrl__Poll(beNDMWLoadIntf2ComMdlCtrl *self) {
    int openIndex;
    int openCount;
    beLoadIntf2ComMdlData *opening;
    int closeIndex;
    int closeCount;
    beLoadIntf2ComMdlData *closing;

    openCount = ((beLoadIntf2ComMdlDataList *)self->_openDataList)->_count;
    if (openCount > 0) {
        for (openIndex = openCount - 1; openIndex >= 0; openIndex--) {
            opening = QueuedRequest(self->_openDataList, openIndex);
            if (beNDMWLoadIntf2ComMdlCtrl__IsSequence((beNDMWSaveIntfComMdlCtrl *)self, opening->_ramNo, (const char *)opening->_infoName, (const char *)opening->_openSQ) == 1) break;
            DropQueuedRequest((beLoadIntf2ComMdlDataList *)self->_openDataList, openIndex);
        }
    }
    closeCount = ((beLoadIntf2ComMdlDataList *)self->_closeDataList)->_count;
    if (closeCount > 0) {
        for (closeIndex = closeCount - 1; closeIndex >= 0; closeIndex--) {
            closing = QueuedRequest(self->_closeDataList, closeIndex);
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self, closing->_ramNo, (const char *)closing->_infoName) == 1) break;
            DropQueuedRequest((beLoadIntf2ComMdlDataList *)self->_closeDataList, closeIndex);
        }
    }
}

/* Looks the pad manager up through the insight on first use and keeps a reference to it. */
void beNDMWLoadIntf2_Prepare(beNDMWLoadIntf2 *self) {
    igObject *found;
    igObject *previous;

    if (self->_padManager == 0) {
        found = igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
        if (found != 0) {
            found->_refCount = (int)found->_refCount + 1;
        }
        previous = (igObject *)self->_padManager;
        IG_OBJECT_RELEASE(previous);
        self->_padManager = (int)found;
    }
}

int beNDMWLoadIntf2_igIntList_GetData(igDataList *list)
{
    return list->_data;
}

void beNDMWLoadSavePlWork__SetIsCtrl(beNDMWLoadSavePlWork *work, int isCtrl)
{
    work->_isCtrl = isCtrl;
}

unsigned char beNDMWLoadSavePlWork__GetIsRdy(beNDMWLoadSavePlWork *work)
{
    return work->_isRdy;
}

unsigned char beNDMWLoadSavePlWork__GetIsEntry(beNDMWLoadSavePlWork *work)
{
    return work->_isEntry;
}

void beNDMWLoadIntf2_igObject_Retain(ObjectRefTarget *object)
{
    if (object) ++object->references;
}

/* The word at `index` of a list, unchecked. */
int beNDMWLoadIntf2_beNDMWDegiDataList_Get(igDataList *list, int index)
{
    return ((int *)list->_data)[index];
}

/* Stores `replacement` at `index` of an object list: retains it, releases the object it replaces,
 * and writes the slot only when the index is in range. */
void beNDMWLoadIntf2_igObjectList_Set(igDataList *list, int index, ObjectRefTarget *replacement)
{
    ObjectRefTarget *previous;

    if (replacement) ++replacement->references;
    previous = ((ObjectRefTarget **)list->_data)[index];
    ReleaseReference(previous);
    if (list->_count && index >= 0 && index < list->_count)
        ((ObjectRefTarget **)list->_data)[index] = replacement;
}

/* Copies a three-float vector. */
void Vec3f_Copy(void *destination, const void *source)
{
    float *to = (float *)destination;
    const float *from = (const float *)source;

    to[0] = from[0];
    to[1] = from[1];
    to[2] = from[2];
}

/* The word at `index` of a list, unchecked. */
int beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get(igDataList *list, int index)
{
    return ((int *)list->_data)[index];
}

/* The object at `index` of an object list, unchecked. */
int beNDMWLoadIntf2_igObjectList_Get(igDataList *list, int index)
{
    return ((int *)list->_data)[index];
}

/* The child of `list` whose name field (`nameField`) is `name`. */
void *beNDMWLoadIntf2_beBaseInfoDataList_FindProperty(int list, int nameField, const void *name)
{
    return (void *)igProperty_FindByName((igObjectList *)list, (igMetaField *)nameField, (const char *)name);
}

int beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Deref(int *reference)
{
    return *reference;
}

/* Assigns an object reference: retains the incoming object, releases the outgoing one. */
ObjectRefTarget **beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign(ObjectRefTarget **destination, ObjectRefTarget **source)
{
    ObjectRefTarget *incoming = *source;
    ObjectRefTarget *outgoing;

    if (incoming) ++incoming->references;
    outgoing = *destination;
    ReleaseReference(outgoing);
    *destination = incoming;
    return destination;
}

AllocatorValue beNDMWLoadIntf2_beBaseInfoDataList_MakeAllocatorValue(int allocator)
{
    return AllocatorValue(allocator);
}

/* The owner's allocator when g_useOwnerAllocator is set, else the selector's. */
int beNDMWLoadIntf2_Memory_SelectAllocator(const igMemoryPoolHandle *selector, int ownAllocator)
{
    if (g_useOwnerAllocator)
        return ownAllocator;
    else
        return (int)Memory_GetAllocatorBySelector(*selector);
}

int beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(int *reference)
{
    return *reference;
}

int beNDMWLoadIntf2__GetInfoMeta(void)
{
    return (int)g_beNDMWLoadIntf2Info_metaObject;
}

/* Registers the info record as a receiver of LOADINTF2_ALL and of LOADINTF2 for its ram number. */
void beNDMWLoadIntf2_OnAddRam(beNDMWLoadIntf2 *self, beBaseInfoRam *ram) {
    beMessenger_RegisterReceiverFromInfo((beMessenger *)self->_messenger, ram, "LOADINTF2_ALL");
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, ram, "LOADINTF2", 0, ram->_ramNo);
}

/* Answers the messages sent to one player's load interface (`ram`, whose _ramNo is the player):
 * GENERATE builds its controller family under the info record's child list (control data, the
 * shared common interface fetched from LOADCTRL2, character maker, model control, text order,
 * slot, name, message, status, data and difficulty selectors); the rest read or set the control
 * data, and SETSELECT_DATA removes a player whose save data is not ready from the game. */
int beNDMWLoadIntf2_OnMessage(beNDMWLoadIntf2 *self, beBaseInfoRam *ram, beMessengerWork *message) {
    unsigned int command;
    beNDMWLoadIntf2CtrlData *control;
    beNDMWLoadCtrl2CommonIntf *common;

    command = beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, LoadIntf2Message_GetMetaEnum(), (const char *)message->_message);
    if (command == MSG_GENERATE) {
        if (ram->_dataList == 0) {
            igSmartPointer<beBaseInfoDataList> dataList((beBaseInfoDataList *)beBaseInfoDataList_Create(OwnerAllocator(self)));
            SetDataList(ram, dataList.p);
            self->_system_ = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject);
            {
                igSmartPointer<beNDMWLoadIntf2CtrlData> ctrl(beNDMWLoadIntf2CtrlData_Create(OwnerAllocator(self)));
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)ctrl.p);
                ctrl.p->_isRun = 1;
                /* matching construct: hand search — each branch stores all three flags (player 1
                 * starts entered) */
                if (ram->_ramNo == 0) {
                    ctrl.p->_isRdy = 0;
                    ctrl.p->_isEntry = 1;
                    ctrl.p->_isCtrl = 1;
                } else {
                    ctrl.p->_isRdy = 0;
                    ctrl.p->_isEntry = 0;
                    ctrl.p->_isCtrl = 1;
                }
            }
            beMessenger_SendNamed((beMessenger *)self->_messenger, "LOADCTRL2", 0, 0, "GETCOMMON");
            ObjectList_AppendRetained((igObjectList *)ram->_dataList, beMessenger_GetObject((beMessenger *)self->_messenger, 0));
            {
                igSmartPointer<beNDMWLoadIntf2MakeChr> maker(beNDMWLoadIntf2MakeChr_Create(OwnerAllocator(self)));
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)maker.p);
            }
            {
                igSmartPointer<beNDMWLoadIntf2ComMdlCtrl> models(beNDMWLoadIntf2ComMdlCtrl_Create(OwnerAllocator(self)));
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)models.p);
                models.p->_messenger = self->_messenger;
                {
                    /* matching construct: hand search — the controller read once into a local, and the
                     * table's declared bound keeps the three loads ahead of the stores */
                    beNDMWLoadIntf2ComMdlCtrl *modelCtrl = models.p;
                    float x, y, z;
                    z = g_interfaceKindPositions[ram->_ramNo][2];
                    y = g_interfaceKindPositions[ram->_ramNo][1];
                    x = g_interfaceKindPositions[ram->_ramNo][0];
                    modelCtrl->_pos[0] = x;
                    modelCtrl->_pos[1] = y;
                    modelCtrl->_pos[2] = z;
                }
            }
            {
                igSmartPointer<beNDMWLoadIntf2TextOrder> text(beNDMWLoadIntf2TextOrder_Create(OwnerAllocator(self)));
                text.p->_messenger = self->_messenger;
                {
                    /* matching construct: hand search — the text order read once into a local */
                    beNDMWLoadIntf2TextOrder *order = text.p;
                    order->_lua = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
                }
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)text.p);
            }
            {
                igSmartPointer<beNDMWLoadIntf2SelSlot> slots(beNDMWLoadIntf2SelSlot_Create(OwnerAllocator(self)));
                slots.p->_ramNo = ram->_ramNo;
                slots.p->_messenger = self->_messenger;
                slots.p->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
                slots.p->_comMdlCtrl = (int)ChildList::Find(ram, "COMMDLCTRL");
                slots.p->_textOrder = (int)ChildList::Find(ram, "TEXTORDER");
                slots.p->_commonIntf = (int)ChildList::Find(ram, "COMMONINTF");
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)slots.p);
            }
            {
                igSmartPointer<beNDMWLoadIntf2NameSel> names(beNDMWLoadIntf2NameSel_Create(OwnerAllocator(self)));
                void *comMdlCtrl;
                void *textOrder;
                names.p->_ramNo = ram->_ramNo;
                names.p->_messenger = self->_messenger;
                names.p->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
                comMdlCtrl = ChildList::Find(ram, "COMMDLCTRL");
                textOrder = ChildList::Find(ram, "TEXTORDER");
                names.p->_comMdlCtrl = (int)comMdlCtrl;
                names.p->_textOrder = (int)textOrder;
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)names.p);
            }
            {
                igSmartPointer<beNDMWLoadIntf2MesWin> window(beNDMWLoadIntf2MesWin_Create(OwnerAllocator(self)));
                window.p->_ramNo = ram->_ramNo;
                window.p->_messenger = self->_messenger;
                window.p->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)window.p);
                window.p->_textOrder = (int)ChildList::Find(ram, "TEXTORDER");
            }
            {
                igSmartPointer<beNDMWLoadIntf2DegiStateCtrl> status(beNDMWLoadIntf2DegiStateCtrl_Create(OwnerAllocator(self)));
                {
                    igSmartPointer<beNDMWLoadIntf2DegiState> upper(beNDMWLoadIntf2DegiState_Create(OwnerAllocator(self)));
                    void *commonIntf;
                    void *textOrder;
                    commonIntf = ChildList::Find(ram, "COMMONINTF");
                    textOrder = ChildList::Find(ram, "TEXTORDER");
                    beNDMWLoadIntf2DegiState__Init(upper.p, ram->_ramNo, (int)commonIntf, (int)textOrder, (int)ChildList::Find(ram, "COMMDLCTRL"), self->_messenger, 0);
                    ObjectList_AppendRetained((igObjectList *)status.p->_statDataList, (igObject *)upper.p);
                }
                {
                    igSmartPointer<beNDMWLoadIntf2DegiState> lower(beNDMWLoadIntf2DegiState_Create(OwnerAllocator(self)));
                    void *commonIntf;
                    void *textOrder;
                    commonIntf = ChildList::Find(ram, "COMMONINTF");
                    textOrder = ChildList::Find(ram, "TEXTORDER");
                    beNDMWLoadIntf2DegiState__Init(lower.p, ram->_ramNo, (int)commonIntf, (int)textOrder, (int)ChildList::Find(ram, "COMMDLCTRL"), self->_messenger, 1);
                    ObjectList_AppendRetained((igObjectList *)status.p->_statDataList, (igObject *)lower.p);
                }
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)status.p);
            }
            {
                igSmartPointer<beNDMWLoadIntf2DataSelIntf> dataSel(beNDMWLoadIntf2DataSelIntf_Create(OwnerAllocator(self)));
                dataSel.p->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
                dataSel.p->_comMdlCtrl = (int)ChildList::Find(ram, "COMMDLCTRL");
                dataSel.p->_textOrder = (int)ChildList::Find(ram, "TEXTORDER");
                dataSel.p->_commonIntf = (int)ChildList::Find(ram, "COMMONINTF");
                dataSel.p->_mesWin = (int)ChildList::Find(ram, "MESWIN");
                dataSel.p->_statDisp = (int)ChildList::Find(ram, "DEGISTATECTRL");
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)dataSel.p);
            }
            {
                igSmartPointer<beNDMWLoadIntf2Diffselect> difficulty(beNDMWLoadIntf2Diffselect_Create(OwnerAllocator(self)));
                difficulty.p->_padManager = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_bePadManager_metaObject);
                difficulty.p->_comMdlCtrl = (int)ChildList::Find(ram, "COMMDLCTRL");
                difficulty.p->_textOrder = (int)ChildList::Find(ram, "TEXTORDER");
                difficulty.p->_commonIntf = (int)ChildList::Find(ram, "COMMONINTF");
                difficulty.p->_mesWin = (int)ChildList::Find(ram, "MESWIN");
                ObjectList_AppendRetained((igObjectList *)ram->_dataList, (igObject *)difficulty.p);
            }
        }
        return 1;
    }
    if (ram->_dataList == 0) return 1;
    control = (beNDMWLoadIntf2CtrlData *)ChildList::Find(ram, "CTRL");
    ChildList::Find(ram, "MAKECHR"); /* looked up, not used */
    switch (command) {
    case MSG_ISENTRY:
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
        }
        if (control->_isEntry == 1) {
            beMessenger_SetInt((beMessenger *)self->_messenger, 0, beMessenger_GetInt((beMessenger *)self->_messenger, 0) + 1);
        }
        return 1;
    case MSG_ISRDY:
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
        }
        if (control->_isRdy == 1) {
            beMessenger_SetInt((beMessenger *)self->_messenger, 0, beMessenger_GetInt((beMessenger *)self->_messenger, 0) + 1);
        }
        return 1;
    case MSG_ONCTRL:
        control->_isCtrl = 1;
        return 1;
    case MSG_OFFCTRL:
        control->_isCtrl = 0;
        return 1;
    case MSG_SETSELECT_DATA:
        common = (beNDMWLoadCtrl2CommonIntf *)ChildList::Find(ram, "COMMONINTF");
        if (PlayerWork(common, ram->_ramNo)->_isRdy != 1) {
            beMessenger_SelectGroup((beMessenger *)self->_messenger, "GAMERAM");
            beMessenger_AppendInt((beMessenger *)self->_messenger, ram->_ramNo);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GAMEREMOVE");
        }
        return 1;
    case MSG_SETDIFFICULTMAX:
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) {
            beMessenger_AppendInt((beMessenger *)self->_messenger, 0);
        }
        self->_difficultMax = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        return 1;
    default:
        return 0;
    }
}

int beNDMWLoadIntf2__GetMeta(void)
{
    return (int)g_beNDMWLoadIntf2_metaObject;
}

#pragma pop
