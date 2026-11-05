/* 0x003e4750 — beNDMWLoadIntf2::vfunc_31, the per-frame master update of the
 * Game Start interface for one player (`host`): it looks up the named working
 * set under host->_dataList (COMMONINTF, CTRL, MAKECHR, ...), samples that
 * player's pad, and advances the CtrlData screen state machine (join, new or
 * load, Digimon choice, name, slot, save data, start) plus the per-player
 * card-utility stages. See docs/engine/load-intf2.md for the state and
 * ownership contracts.
 *
 * The local declaration groups preserve the original allocation. Explicit
 * snapshots retain the observed ordering of published controller reads.
 * LoadVec3 is three floats; reference parameter homes remain 16 bytes apart.
 */
#include "dw4/reflected.h"
#pragma inline_depth(1)
struct LoadVec3 {
  float x, y, z;
  LoadVec3(const LoadVec3 &);
};
extern "C" {
struct DW4Sret4 {
  int v;
  DW4Sret4(const DW4Sret4 &o) : v(o.v) {}
};
int DataList_GetData_003e9090(...);
void *DataList_GetWordAt_003e90f0(...);
void *DataList_GetWordAt_003e9240(...);
int FUN_001ae1a0(void *, float, float, float);
int FUN_002294f0(void *);
int FUN_00236f80(...);
void *FUN_003614f0(...);
int beUnicodeObj_AllocateBuffer(...);
int beLua__RunNamedChunk(...);
void *beNDMWDegiData_Create(...);
int FUN_003d9e10(...);
int FUN_003d9e70(...);
int FUN_003d9e90(...);
int FUN_003da7c0(...);
int FUN_003dafb0(...);
int beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(...);
int FUN_003db060(...);
int beNDMWLoadIntf2DataSelIntf__UpdateSelection(...);
int FUN_003dbf90(...);
int beNDMWLoadIntf2Diffselect__Init(...);
int beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *, unsigned char);
int beNDMWLoadIntf2NameSel__Init(...);
int beNDMWLoadIntf2NameSel__SetAnswer(...);
int beNDMWLoadIntf2NameSel__Update(...);
int beNDMWLoadIntf2SelSlot__Init(...);
int beNDMWLoadIntf2SelSlot__Open(...);
int beNDMWLoadIntf2SelSlot__UpdateSelection(...);
int beNDMWLoadIntf2SelSlot__PublishCursor(...);
int beNDMWLoadIntf2SelSlot__Close(...);
int beNDMWLoadIntf2SelSlot__RefreshSlotMarks(...);
int beNDMWLoadIntf2ComMdlCtrl__StartAt(void *, int, void *, void *, LoadVec3 &, int);
int beNDMWLoadIntf2ComMdlCtrl__Play(...);
int beNDMWLoadIntf2ComMdlCtrl__IsSequence(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int beNDMWLoadIntf2ComMdlCtrl__Close(...);
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(void *);
int beNDMWLoadIntf2ComMdlCtrl__Poll(...);
int beNDMWLoadSavePlWork__SetIsCtrl(...);
int beNDMWLoadSavePlWork__GetIsRdy(...);
int beNDMWLoadSavePlWork__GetIsEntry(...);
int FUN_003e9220(...);
void *FUN_003e9280(...);
int FUN_003e92a0(...);
int FUN_003e9330(...);
DW4Sret4 FUN_003e9360(...);
int FUN_003e93b0(...);
int TextOrder_ConfigureFont(...);
int TextOrder_ClearFont(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int TextOrder_PublishLineListOnly(...);
int beNDMWLoadIntf2MesWin__Update(...);
int beNDMWLoadIntf2MesWin__RequestOpen(...);
int beNDMWLoadIntf2MesWin__RequestClose(...);
int FUN_003ecad0(...);
int FUN_003ecae0(...);
int FUN_003ecb00(...);
int FUN_003ecb20(...);
int beNDMWLoadIntf2MesWin__GetIsCtrl(...);
int FUN_003ecb80(...);
int beNDMWLoadIntf2MesWin__RequestMesErase(...);
int FUN_003ecba0(...);
int beNDMWLoadIntf2MesWin__EndSystemMessage(...);
int FUN_003ecdc0(...);
int FUN_003ed050(...);
int FUN_003ed2e0(...);
int beNDMWLoadCtrl2CommonIntf__StepReadMedia(...);
int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(...);
int FUN_003ee250(...);
int beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(...);
int beNDMWDegiData__LoadFromProperties(...);
int beNDMWDegiData__StoreToProperties(...);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int Memory_SelectAllocator_003e9370(...);
void *ObjectList_GetAt_003e9260(...);
int ObjectList_SetAtRetained_003e9160(...);

int ObjectRef_Destruct_0033e9c0(...);
int ObjectRef_Release_003e9110(...);
int ObjectRef_Retain_003e90d0(...);
int beDataBase_GetRecordString(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendObject(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(int, LoadVec3 &);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_GetBoolCount(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
void *bePadManager_GetPadForPlayer(...);
int igObject_GetAllocator(...);
void *igProperty_GetRecord(...);
void *igProperty_GetRecordByte(...);
int igStrCmp(...);
extern int g_starterPreviewModelName_004cd0d0[4];
extern int g_starterPlayerModelName_004cd0e0[4];
extern int g_playerModelRow_004cec70[4];
extern int g_playerModelRowOpenSeq_004cec74[4];
extern int g_playerModelRowSeq_004cec78[4];
extern int s_DATABASE_00516c50[4];
extern int s_shinka_00516c60[4];
extern int s_GETDATABASE_00516c68[4];
extern int s_NAME_00516c78[4];
extern int s_j_digifacewin_00516ca8[4];
extern int s_j_mainstatuswin_00516cc0[4];
extern int s_SQ_OPEN_00516cd0[4];
extern int s_SQ_CLOSE_00516d30[4];
extern int s_SQ_LINEON00_00516d40[4];
extern int s_SQ_CANCEL_00516d50[4];
extern int s_SQ_LINESL00_00516dd8[4];
extern int s_SQ_LINEON01_00516e18[4];
extern int s_j_linewin02_00516eb0[4];
extern int s_SQ_LINEUP00_00516ed0[4];
extern int s_SQ_LINEDW01_00516ef0[4];
extern int s_SQ_ON00_00517028[4];
extern int s_MODELCTRL_005171f8[4];
extern int s_GENERATE_00517208[4];
extern int s_ISRUN_00517228[4];
extern int s_COMMONINTF_005172a0[4];
extern int s_CTRL_005172b0[4];
extern int s_MAKECHR_005172b8[4];
extern int s_COMMDLCTRL_005172c0[4];
extern int s_MESWIN_005172d0[4];
extern int s_SELSLOT_005172d8[4];
extern int s_NAMESEL_005172e0[4];
extern int s_TEXTORDER_005172e8[4];
extern int s_DEGISTATECTRL_005172f8[4];
extern int s_DATASELINTF_00517308[4];
extern int s_DIFFSELECT_00517318[4];
extern int s_j_chrselbase_00517328[4];
extern int s_GAMERAM_00517338[4];
extern int s_GETPLAYER_00517340[4];
extern int s_ISUSE_00517350[4];
extern int s_j_chrselmesswin_00517360[4];
extern int s_j_linewin01_00517370[4];
extern int s_j_digiselcursorleft_00517380[4];
extern int s_j_digiselcursorright_005173a0[4];
extern int s_j_namewin02_005173b8[4];
extern int s_CHRSELFONT14_005173c8[4];
extern int s_MOVETRANS_005173d8[4];
extern int s_SQ_ENTR_005173e8[4];
extern int s_SQ_EXIT_005173f0[4];
extern int s_SQ_LINECG00_005173f8[4];
extern int s_GAMEDATAINIT_00517408[4];
extern int s_GAMESTART_00517418[4];
extern int s_UNIQUE_00517428[4];
extern int s_BASE2CURRENT_00517430[4];
extern int s_RECALCPLAYER_00517440[4];
extern int s_hostLoad_lua_00517450[4];
extern int DAT_00585be0[4];
extern int g_ndmwAllocatorSelector_00587108[4];
extern int g_defaultAllocatorSelector_00587110[4];
extern int g_bePadManager_metaObject_00588518[4];
extern int g_beLua_metaObject_00589208[4];
extern int g_beFont_metaObject_00589678[4];
extern int DAT_0058a1e0[4];
extern unsigned char GPR_00554c14;
}
/* Retail copies the 4-byte value returned by FUN_003e9360 into a temporary
 * reference before handing it to ObjectRef_Assign_003e92b0; these two classes
 * reproduce that copy/destroy pair. */
class RecoveryCopiedRef {
public:
  void *value;
  RecoveryCopiedRef(const DW4Sret4 &);
  ~RecoveryCopiedRef();
};
extern "C" int *ObjectRef_Assign_003e92b0(void *, const RecoveryCopiedRef &);
/* Creates the fresh object for an empty reference (the FUN_003e93b0 == 0
 * test on host->_dataList at the top of the update) and stores it there. */
struct DW4Fresh {
  static int *Assign(void *obj, int alloc) {
    RecoveryCopiedRef c(FUN_003e9360(Memory_SelectAllocator_003e9370(
        &g_defaultAllocatorSelector_00587110[0], alloc)));
    return ObjectRef_Assign_003e92b0(obj, c);
  }
};
extern "C" void igObject_Destroy(void *);
/* Release half of the ref-counted handle: decrement _refCount and destroy the
 * object when its low 23 bits reach zero (same test as the release in
 * src/game/beSystemUpdate.c). */
struct RecoveryTarget {
  int word0;
  int references;
  static void release(RecoveryTarget *object) {
    if (object) {
      --object->references;
      if (((unsigned long long)(long long)object->references & 0x7fffffULL) ==
          0)
        igObject_Destroy(object);
    }
  }
};
/* Scoped holder for a ref-counted object: optionally retains on construction
 * and releases on scope exit. The template index only keeps the instances
 * apart so each scope gets its own destructor, as in the retail code. */
template <int I> class RecoveryRef {
public:
  void *value;
  RecoveryRef(void *p) : value(p) {}
  RecoveryRef(void *p, bool retain) : value(p) {
    if (retain)
      ObjectRef_Retain_003e90d0(value);
  }
  ~RecoveryRef() { RecoveryTarget::release((RecoveryTarget *)value); }
};
/* Header of the growable int list behind SlotPlayer::_accessPlList: the
 * count (+8) is read volatile, the capacity (+12) decides whether List_Resize
 * is needed before a player number is appended. */
struct DW4ListRec {
  int w0, w1;
  volatile int count;
  int cap;
};
/* Pad bits as read from bePadData::_trigger/_repeat (the PS2 libpad button
 * layout). Cross confirms and Circle cancels in the slot/portrait/difficulty
 * screens (docs/engine/load-intf2.md, "Face-button semantics"). The stick
 * bits of _lTrg/_lRpt are paired with the D-pad bit of the same direction in
 * every test below, so they are named by direction. */
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
/* Step bookkeeping for the CtrlData record (docs/engine/load-intf2.md,
 * "Object model": _st0.._st3). _st0 is the screen state, _st1 the step inside
 * it, _st2 and _st3 finer sub-steps. Moving to a new level always clears the
 * levels below it, in the order _st3, _st2, _st1 that the retail code stores.
 * Single-line comma expressions: tools/units.py misreads braces and line
 * continuations inside a #define as the start of a function body. */
/* clang-format off */
#define LOAD_ENTER_STATE(c, n) ((c)->_st0 = (n), (c)->_st3 = 0, (c)->_st2 = 0, (c)->_st1 = 0)
#define LOAD_NEXT_STEP(c) ((c)->_st1 = ((c)->_st1 + 1), (c)->_st3 = 0, (c)->_st2 = 0)
#define LOAD_SET_STEP(c, n) ((c)->_st1 = (n), (c)->_st3 = 0, (c)->_st2 = 0)
#define LOAD_NEXT_SUBSTEP(c) ((c)->_st2 = ((c)->_st2 + 1), (c)->_st3 = 0)
#define LOAD_RESTART_SUBSTEP(c) ((c)->_st2 = 0, (c)->_st3 = 0)
/* The same four-level bookkeeping on the per-player beNDMWLoadSavePlWork
 * (_sysStat0.._sysStat3). */
#define PLAYER_SET_STEP(w, n) ((w)->_sysStat1 = (n), (w)->_sysStat3 = 0, (w)->_sysStat2 = 0)
#define PLAYER_ENTER_STAGE(w, n) ((w)->_sysStat0 = (n), (w)->_sysStat3 = 0, (w)->_sysStat2 = 0, (w)->_sysStat1 = 0)
/* Message/text-order ids: the player number (_ramNo) in the high half and the
 * message token in the low bits (docs/engine/load-intf2.md, "text-order
 * helpers": a control id is (high << 16) | token, matched against the id
 * table at 0x004cda40). */
#define LOAD_TEXT_ID(h, token) (((h)->_ramNo << 0x10) | (token))
/* clang-format on */
/* Accessors the retail code inlined at each use. */
struct LoadHelpers {
  static beNDMWLoadSavePlWork *FlagAt(beNDMWLoadCtrl2CommonIntf *owner,
                                      beBaseInfoRam *host) {
    int player = host->_ramNo;
    return (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260(owner->_flagWork,
                                                             player);
  }
  static beNDMWMcUtilCtrl *McUtil(beNDMWLoadCtrl2CommonIntf *owner) {
    return (beNDMWMcUtilCtrl *)owner->_mcUtilCtrl;
  }
  static bePadData *GetPad(beNDMWLoadIntf2 *owner, beBaseInfoRam *host) {
    int manager =
        FUN_00236f80(owner->_insight, g_bePadManager_metaObject_00588518[0]);
    return (bePadData *)bePadManager_GetPadForPlayer(manager, host->_ramNo);
  }
  static int Selector(const int *sel, int fb) {
    if (GPR_00554c14)
      return fb;
    else
      return Memory_GetAllocatorBySelector(*sel);
  }
  static int GetBool(beNDMWLoadIntf2 *owner) {
    if (beMessenger_GetBoolCount(owner->_messenger) > 0)
      return beMessenger_GetBool(owner->_messenger, 0);
    else
      return 0;
  }
};
/* Offsets of members the reflection dump does not list (no field names are
 * recorded for them): the typed-name text buffer inside NameSel, the 8-char
 * text pointer inside the name object sized by beUnicodeObj_AllocateBuffer, and the byte
 * flag inside an igProperty record (docs/engine/load-intf2.md, NAMESEL and
 * GAMERAM ISUSE). Single-line #defines. */
#define NAMESEL_TEXT_OFFSET 236
#define NAME_OBJECT_TEXT_OFFSET 12
#define PROPERTY_RECORD_BYTE_OFFSET 12
/* Copies the name typed on the name-entry screen: up to 8 UTF-16 characters
 * from the (unreflected) buffer at NameSel+NAMESEL_TEXT_OFFSET into the new
 * name object, zero-padding the rest. */
struct NameCopyHelper {
  static void Copy(unsigned short *destination,
                   beNDMWLoadIntf2NameSel *source) {
    int count = 0;
    unsigned short *cursor = destination;
  copyLoop:
    *cursor = *(unsigned short *)((char *)source + NAMESEL_TEXT_OFFSET);
    if (*(unsigned short *)((char *)source + NAMESEL_TEXT_OFFSET) != 0) {
      count++;
      source = (beNDMWLoadIntf2NameSel *)((char *)source + 2);
      cursor++;
      if (count < 8)
        goto copyLoop;
    }
    for (; count < 8; ++count)
      destination[count] = 0;
  }
};
extern "C" void Gap__Bec__beNDMWLoadIntf2__vfunc_31(beNDMWLoadIntf2 *self,
                                                    beBaseInfoRam *host) {
  float moveTransA[3];
  float moveTransB[3];
  float moveTransC[3];
  float moveTransD[3];
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
  int shinkaRow;
  int shinkaRow_2;
  int shinkaRow_3;
  int *rowCursor_2;
  int *rowCursor_3;
  int *rowCursor;
  int padRepeat;
  unsigned int st2Now;
  unsigned int st2Now_2;
  unsigned int difficultMax;
  unsigned int st2Now_3;
  unsigned int utilResult;
  unsigned int cardStat2;
  unsigned int cardStat2_2;
  unsigned int resultStat2;
  unsigned int hostStat1;
  unsigned int st2Now_4;
  unsigned int utilReturn;
  unsigned int st2Now_5;
  int ramNo;
  unsigned int hostStat1_2;
  int saveAreaIndex;

  int loadedPlayer;
  int font;

  int kindName;
  int ramNoCopy;
  int ramNoCopy_2;

  beNDMWLoadSavePlWork *resultWork;
  unsigned int utilResult_2;

  int shinkaDb;
  int ramNoCopy_3;
  int shinkaDb_2;
  int shinkaDb_3;
  int accessCount;

  int newPlayer;
  unsigned int stepResult;
  int playerTextBase;
  int playerTextBase_2;
  int playerTextBase_3;
  unsigned int stepResult_2;
  unsigned int stepResult_3;
  int playerTextBase_4;
  int playerTextBase_5;
  int playerTextBase_6;
  unsigned int stepResult_4;
  unsigned int stepResult_5;
  unsigned int stepResult_6;
  int gamePlayer;
  int ramNo_2;
  unsigned int messageChoice;
  unsigned int kindHard;
  int stickEdge;
  unsigned int st2Now_6;
  unsigned int st3Now;
  unsigned int kindHard_2;
  unsigned int kindHard_3;
  unsigned int st3Now_2;
  unsigned int st2Now_7;
  unsigned int st3Now_3;
  unsigned int st1Now;
  unsigned int st3Now_4;
  unsigned int st2Now_8;
  unsigned int kindHard_4;
  unsigned int utilResult_3;
  unsigned int kindHard_5;
  unsigned int cardStat2_3;
  unsigned int kindHard_6;
  unsigned int utilResult_4;
  unsigned int utilResult_5;
  unsigned int kindHard_7;
  unsigned int kindHard_8;
  unsigned int kindHard_9;
  unsigned int kindHard_10;
  unsigned int kindHard_11;
  unsigned int kindHard_12;
  unsigned int kindHard_13;
  unsigned int kindHard_14;
  unsigned int kindHard_15;
  unsigned int kindHard_16;
  int countdown;
  unsigned int kindHard_17;
  unsigned int st2Now_9;
  unsigned int st2Now_10;
  unsigned int kindHard_18;
  int messageId;
  int messageId_2;
  int messageId_3;
  int messageId_4;
  int messageId_5;
  int messageId_6;
  int messageId_7;
  int messageId_8;
  int messageId_9;
  int messageId_10;
  int messageId_11;
  int messageId_12;
  int messageId_13;
  int messageId_14;
  int messageId_15;
  int messageId_16;
  bool upHeld;
  int firstTextId;
  int firstTextId_2;
  int secondTextId;
  int secondTextId_2;
  unsigned char modelReady;

  unsigned char needsDifficulty;
  unsigned int difficultyCase;

  void *workList;
  int entryCount;
  int readyCount;
  int workIndex;

  void *workList_2;
  int entryCount_2;
  int readyCount_2;
  int workIndex_2;

  void *workList_3;
  int entryCount_3;
  int readyCount_3;
  int workIndex_3;

  void *workList_4;
  int entryCount_4;
  int readyCount_4;
  int workIndex_4;

  void *workList_5;
  int entryCount_5;
  int readyCount_5;
  int workIndex_5;

  void *workList_6;
  int workIndex_6;

  int playerIndex;
  int nextSel;
  int nextSel_2;
  int rowIndex_2;
  int rowIndex_3;

  int listIndex;
  unsigned char decided;
  int rowIndex;

  int prevDegi;
  int allocator;
  int allocator_2;
  int allocator_3;
  int allocator_4;
  int modelIsRun;
  int nextDegi;
  int modelIsRun_2;
  long long worldTime;
  unsigned int st1Now_2;
  unsigned int st1Now_3;
  unsigned int st1Now_4;
  unsigned int st1Now_5;
  unsigned int st1Now_6;
  unsigned int st1Now_7;
  unsigned int leaveState;
  unsigned int cardStat1;
  unsigned int hostStat0;
  unsigned int screenState;
  unsigned int st1Now_8;
  unsigned int st1Now_9;
  beNDMWMcUtilCtrl *mcUtil;
  beNDMWLoadCtrl2CommonIntf *common;
  beNDMWLoadIntf2CtrlData *control;

  beNDMWLoadIntf2ComMdlCtrl *models;
  DW4ListRec *accessList;

  beNDMWLoadIntf2MesWin *messages;

  beNDMWLoadIntf2SelSlot *slots;

  beNDMWLoadIntf2MakeChr *creation;

  bePadData *pad;
  void *nameObject;
  beNDMWLoadSavePlWork *hostWork_3;
  beNDMWLoadSavePlWork *hostWork_4;
  beNDMWLoadSavePlWork *cardWork;
  beNDMWLoadSavePlWork *eachWork;
  beNDMWLoadSavePlWork *resetWork;
  beNDMWLoadSavePlWork *hostWork;
  beNDMWLoadSavePlWork *hostWork_2;
  beNDMWLoadSavePlWork *countdownWork;
  beNDMWLoadSlotPlayer *slotPlayer;
  beNDMWLoadIntf2NameSel *nameEntry;
  beNDMWLoadSavePlWork *exitWork;

  int dataListRef;
  if (host->_dataList == 0)
    return;
  {
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    common = (beNDMWLoadCtrl2CommonIntf *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_COMMONINTF_005172a0[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    control = (beNDMWLoadIntf2CtrlData *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0], &s_CTRL_005172b0[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    creation = (beNDMWLoadIntf2MakeChr *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_MAKECHR_005172b8[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    models = (beNDMWLoadIntf2ComMdlCtrl *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_COMMDLCTRL_005172c0[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    messages = (beNDMWLoadIntf2MesWin *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_MESWIN_005172d0[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    slots = (beNDMWLoadIntf2SelSlot *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_SELSLOT_005172d8[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    nameEntry = (beNDMWLoadIntf2NameSel *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_NAMESEL_005172e0[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    textOrder = (beNDMWLoadIntf2TextOrder *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_TEXTORDER_005172e8[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    status = (beNDMWLoadIntf2DegiStateCtrl *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_DEGISTATECTRL_005172f8[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    dataSelection = (beNDMWLoadIntf2DataSelIntf *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_DATASELINTF_00517308[0]));
    dataListRef = FUN_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    difficulty = (beNDMWLoadIntf2Diffselect *)(FUN_003e9280(
        FUN_003e92a0(&host->_dataList), DAT_00585be0[0],
        &s_DIFFSELECT_00517318[0]));
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
    if (LoadHelpers::FlagAt(common, host)->_isCtrl == 1) {
      pad = (bePadData *)bePadManager_GetPadForPlayer(self->_padManager,
                                                      host->_ramNo);
      padTrigger = pad->_trigger;
      padRepeat = pad->_repeat;
      stickEdge = pad->_lTrg | pad->_lRpt;
      upHeld = 1;
      if (stickEdge & kStickUp)
        goto upDone;
      if ((padTrigger | padRepeat) & kPadUp)
        goto upDone;
      upHeld = 0;
    upDone:;
      moveUp = upHeld & 0xFF;
      moveDown = ((stickEdge & kStickDown) != 0) ||
                 (((padTrigger | padRepeat) & kPadDown) != 0);
      moveLeft = ((stickEdge & kStickLeft) != 0) ||
                 (((padTrigger | padRepeat) & kPadLeft) != 0);
      moveRight = ((stickEdge & kStickRight) != 0) ||
                  (((padTrigger | padRepeat) & kPadRight) != 0);
    }
    if (control->_isSystem != 0)
      return;
    {
      hostStat0 = LoadHelpers::FlagAt(common, host)->_sysStat0;
      switch ((unsigned int)hostStat0) {
      /* Stage 1: the normal flow. sysStat1 step 0 shows text 0x51C and moves to
       * step 1 (or drops the work back to stage 0 while screen 2 is showing);
       * step 1 counts _sysCount0 down and skips the screens for that frame once
       * it expires; otherwise the CtrlData screen state machine below runs. */
      case 1:
        countdownExpired = 0;
        hostStat1 = LoadHelpers::FlagAt(common, host)->_sysStat1;
        switch ((unsigned int)hostStat1) {
        case 0:
          if (control->_st0 == 2) {
            hostWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_ENTER_STAGE(hostWork, 0);
          } else {
            FUN_003ecba0(messages, LOAD_TEXT_ID(host, 0x51C));
            hostWork_2 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_SET_STEP(hostWork_2, 1);
          }
          break;
        case 1:
          countdownWork = LoadHelpers::FlagAt(common, host);
          countdown = countdownWork->_sysCount0 - 1;
          countdownWork->_sysCount0 = countdown;
          if (countdown <= 0) {
            LoadHelpers::FlagAt(common, host)->_sysCount0 = 0;
            countdownExpired = 1;
          }
          break;
        }
        if (countdownExpired != 1) {
        case 0:
          screenState = control->_st0;
          switch ((unsigned int)screenState) {
          /* Screen 0: open the character-select base window and fetch the
           * player's GAMERAM record (GETPLAYER, ISUSE). A used slot opens the
           * message window and goes straight to screen 8; otherwise the host
           * (player 0) starts at screen 3 and the others at screen 2 (pad
           * connected) or 1. */
          case 0:
            st1Now_2 = control->_st1;
            switch ((unsigned int)st1Now_2) {
            case 0:
              LoadVec3 chrSelBasePos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, &s_j_chrselbase_00517328[0],
                           &s_SQ_OPEN_00516cd0[0], chrSelBasePos, 1);
              LOAD_NEXT_STEP(control);
              break;
            case 1:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                LOAD_NEXT_STEP(control);
              }
              break;
            case 2:
              beMessenger_SelectGroup(self->_messenger, &s_GAMERAM_00517338[0]);
              beMessenger_AppendInt(self->_messenger, host->_ramNo);
              beMessenger_DispatchSelected(self->_messenger,
                                           &s_GETPLAYER_00517340[0]);
              gamePlayer = beMessenger_GetObject(self->_messenger, 0);
              /* ISUSE: the GAMERAM record already holds a character. */
              if (*(unsigned char *)((char *)(igProperty_GetRecordByte(
                                         gamePlayer, &s_ISUSE_00517350[0])) +
                                     PROPERTY_RECORD_BYTE_OFFSET) == 1) {
                beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(common->_gameUseData,
                                                       host->_ramNo),
                             gamePlayer);
                LOAD_NEXT_STEP(control);
              } else {
                if (host->_ramNo == 0) {
                  LOAD_ENTER_STATE(control, 3);
                } else if (LoadHelpers::GetPad(self, host)->_isConnect != 0) {
                  LOAD_ENTER_STATE(control, 2);
                } else {
                  LOAD_ENTER_STATE(control, 1);
                }
                control->_isRdyCancel = 1U;
              }
              break;
            case 3:
              LoadVec3 chrSelMessWinPos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, &s_j_chrselmesswin_00517360[0],
                           &s_SQ_OPEN_00516cd0[0], chrSelMessWinPos, 1);
              beNDMWLoadIntf2MesWin__RequestOpen(messages);
              LoadHelpers::FlagAt(common, host)->_isEntry = 1;
              LOAD_NEXT_STEP(control);
              break;
            case 4:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                control->_isRdyCancel = 0U;
                LOAD_ENTER_STATE(control, 8);
              }
              break;
            }
            break;
          /* Screen 1: wait until this player's pad is connected, then join
           * (screen 2). */
          case 1:
            if ((LoadHelpers::FlagAt(common, host)->_isCtrl == 1) &&
                (LoadHelpers::GetPad(self, host)->_isConnect != 0)) {
              LOAD_ENTER_STATE(control, 2);
            }
            break;
          /* Screen 2: join window (linewin01, text 0x400) for players 2-4.
           * Cross enters (SQ_LINEON00) and continues at screen 3; a missing pad
           * closes it (SQ_CLOSE) and returns to screen 1. */
          case 2:
            st1Now_3 = control->_st1;
            switch ((unsigned int)st1Now_3) {
            case 0:
              LoadVec3 lineWin01Pos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, &s_j_linewin01_00517370[0],
                           &s_SQ_OPEN_00516cd0[0], lineWin01Pos, 1);
              LOAD_NEXT_STEP(control);
              break;
            case 1:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, LOAD_TEXT_ID(host, 0x400), 0);
                LOAD_NEXT_STEP(control);
              }
              break;
            case 2:
              decided = 0;
              if (LoadHelpers::FlagAt(common, host)->_isCtrl == 1) {
                if (LoadHelpers::GetPad(self, host)->_isConnect != 0) {
                  if (padTrigger & kPadCross) {
                    LoadHelpers::FlagAt(common, host)->_isEntry = 1;
                    decided = 1;
                    control->_isEntry = 1U;
                  }
                } else {
                  decided = 1;
                }
              } else {
                decided = 1 & 0xFF;
              }
              if ((decided & 0xFF) == 1) {
                if (control->_isEntry == 1) {
                  beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_linewin01_00517370[0],
                               &s_SQ_LINEON00_00516d40[0], 1);
                } else {
                  beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_linewin01_00517370[0],
                               &s_SQ_CLOSE_00516d30[0], 1);
                }
                TextOrder_PublishLineListOnly(textOrder, LOAD_TEXT_ID(host, 0x400));
                LOAD_NEXT_STEP(control);
              }
              break;
            case 3:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                if (control->_isEntry == 1) {
                  LOAD_ENTER_STATE(control, 3);
                } else {
                  LOAD_ENTER_STATE(control, 1);
                }
              }
              break;
            }
            break;
          /* Screen 3: new-or-load question (linewin02, texts 0x401, 0x523,
           * 0x524). Up/down move _newLoadSel and Cross picks it: 0 creates a
           * character (screen 4), 1 loads a slot (screen 6). */
          case 3:
            st1Now_4 = control->_st1;
            switch ((unsigned int)st1Now_4) {
            case 0:
              if (control->_isMesWin == 0) {
                LoadVec3 chrSelMessWinPos(*(LoadVec3 *)(&models->_pos));
                beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo,
                             &s_j_chrselmesswin_00517360[0],
                             &s_SQ_OPEN_00516cd0[0], chrSelMessWinPos, 1);
                beNDMWLoadIntf2MesWin__RequestOpen(messages);
                control->_isMesWin = 1U;
              }
              LoadHelpers::FlagAt(common, host)->_isEntry = 1;
              LoadVec3 lineWin02Pos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, &s_j_linewin02_00516eb0[0],
                           &s_SQ_OPEN_00516cd0[0], lineWin02Pos, 1);
              control->_newLoadSel = 0;
              LOAD_NEXT_STEP(control);
              break;
            case 1:
              if ((control->_st2 == 0) &&
                  !(beNDMWLoadIntf2ComMdlCtrl__IsSequence(models, host->_ramNo,
                                 &s_j_linewin02_00516eb0[0],
                                 &s_SQ_OPEN_00516cd0[0]) &
                    0xFF)) {
                beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, LOAD_TEXT_ID(host, 0x401), 0);
                LOAD_NEXT_SUBSTEP(control);
                ramNo_2 = host->_ramNo;
                if (ramNo_2 == 0) {
                  FUN_003ecad0(messages, (ramNo_2 << 0x10) | 0x523);
                } else {
                  FUN_003ecad0(messages, (ramNo_2 << 0x10) | 0x524);
                }
              }
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                LOAD_NEXT_STEP(control);
              }
              break;
            case 2:
              st2Now_9 = control->_st2;
              switch ((unsigned int)st2Now_9) {
              case 0:
                if (moveUp) {
                  nextSel = control->_newLoadSel - 1;
                  if (nextSel < 0) {
                    nextSel = 0;
                  } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &s_j_linewin02_00516eb0[0],
                                 &s_SQ_LINEUP00_00516ed0[0], 1);
                  }
                  control->_newLoadSel = nextSel;
                  LOAD_NEXT_SUBSTEP(control);
                } else if (moveDown) {
                  nextSel_2 = control->_newLoadSel + 1;
                  if (1 < nextSel_2) {
                    nextSel_2 = 1;
                  } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &s_j_linewin02_00516eb0[0],
                                 &s_SQ_LINEDW01_00516ef0[0], 1);
                  }
                  control->_newLoadSel = nextSel_2;
                  LOAD_NEXT_SUBSTEP(control);
                } else if (padTrigger & kPadCross) {
                  if (control->_newLoadSel == 0) {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &s_j_linewin02_00516eb0[0],
                                 &s_SQ_LINEON00_00516d40[0], 1);
                  } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &s_j_linewin02_00516eb0[0],
                                 &s_SQ_LINEON01_00516e18[0], 1);
                  }
                  LOAD_NEXT_STEP(control);
                } else if (padTrigger & kPadCircle) {
                  ramNo = host->_ramNo;
                  if (ramNo != 0) {
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, ramNo, &s_j_linewin02_00516eb0[0],
                                 &s_SQ_CANCEL_00516d50[0], 1);
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
                                 &s_j_chrselmesswin_00517360[0],
                                 &s_SQ_CLOSE_00516d30[0], 1);
                    TextOrder_PublishLineListOnly(textOrder, LOAD_TEXT_ID(host, 0x401));
                    beNDMWLoadIntf2MesWin__RequestClose(messages);
                    control->_st1 = (control->_st1 + 2);
                    control->_st3 = 0;
                    control->_st2 = 0;
                  }
                }
                break;
              case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                  LOAD_RESTART_SUBSTEP(control);
                }
                break;
              }
              break;
            case 3:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                TextOrder_PublishLineListOnly(textOrder, LOAD_TEXT_ID(host, 0x401));
                if (control->_newLoadSel == 0) {
                  LOAD_ENTER_STATE(control, 4);
                } else {
                  LOAD_ENTER_STATE(control, 6);
                }
              }
              break;
            case 4:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                LoadHelpers::FlagAt(common, host)->_isEntry = 0;
                control->_isEntry = 0U;
                LOAD_ENTER_STATE(control, 2);
                control->_isMesWin = 0U;
              }
              break;
            }
            break;
          /* Screen 4: starter Digimon choice. Left/right cycle through
           * g_starterPlayerModelName, the preview model is generated through
           * MODELCTRL and the name is read from the "shinka" database row.
           * Cross goes on to the name entry (screen 5), Circle back to the
           * question (screen 3). */
          case 4:
            st1Now_8 = control->_st1;
            switch ((unsigned int)st1Now_8) {
            case 0:
              LoadVec3 cursorLeftPos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo,
                           &s_j_digiselcursorleft_00517380[0],
                           &s_SQ_OPEN_00516cd0[0], cursorLeftPos, 1);
              LoadVec3 cursorRightPos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo,
                           &s_j_digiselcursorright_005173a0[0],
                           &s_SQ_OPEN_00516cd0[0], cursorRightPos, 1);
              LoadVec3 nameWin02Pos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, &s_j_namewin02_005173b8[0],
                           &s_SQ_OPEN_00516cd0[0], nameWin02Pos, 1);
              creation->_chaSelDegi = 3;
              FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x511));
              beMessenger_SendNamed(self->_messenger, &s_DATABASE_00516c50[0],
                                    &s_shinka_00516c60[0], 0,
                                    &s_GETDATABASE_00516c68[0]);
              shinkaDb = beMessenger_GetObject(self->_messenger, 0);
              rowIndex = 0;
              rowCursor = (int *)(&g_playerModelRow_004cec70[0]);
            findRow:
              if (igStrCmp(*rowCursor, g_starterPlayerModelName_004cd0e0
                                           [creation->_chaSelDegi]) == 0) {
                shinkaRow = rowIndex;
              } else {
                rowIndex += 1;
                rowCursor += 3;
                if (rowIndex < 0x10) {
                  goto findRow;
                }
              }
              TextOrder_ConfigureFont(textOrder, &s_CHRSELFONT14_005173c8[0], host->_ramNo,
                           0,
                           beDataBase_GetRecordString(shinkaDb, shinkaRow,
                                                      &s_NAME_00516c78[0]),
                           1, 0);
              LoadVec3 faceWinPos(*(LoadVec3 *)(&models->_pos));
              beNDMWLoadIntf2ComMdlCtrl__StartAt(
                  models, host->_ramNo, &s_j_digifacewin_00516ca8[0],
                  (void *)
                      g_playerModelRowOpenSeq_004cec74[creation->_chaSelDegi *
                                                       3],
                  faceWinPos, 1);
              beMessenger_SendNamed(
                  self->_messenger, &s_MODELCTRL_005171f8[0],
                  g_starterPreviewModelName_004cd0d0[creation->_chaSelDegi],
                  host->_ramNo, &s_GENERATE_00517208[0]);
              beMessenger_SendNamed(
                  self->_messenger, &s_MODELCTRL_005171f8[0],
                  g_starterPreviewModelName_004cd0d0[creation->_chaSelDegi],
                  host->_ramNo, &s_ISRUN_00517228[0]);
              modelIsRun = LoadHelpers::GetBool(self);
              if ((modelIsRun & 0xFF) == 1) {
                FUN_001ae1a0(moveTransA, 0.0f, 0.0f, 0.0f);
                FUN_001ae1a0(moveTransB, 0.0f, 0.0f, 0.0f);
                beMessenger_SelectReceivers(
                    self->_messenger, &s_MODELCTRL_005171f8[0],
                    g_starterPreviewModelName_004cd0d0[creation->_chaSelDegi],
                    host->_ramNo);
                LoadVec3 moveTransArgA(*(LoadVec3 *)(moveTransA));
                beMessenger_AppendVec3(self->_messenger, moveTransArgA);
                LoadVec3 moveTransArgB(*(LoadVec3 *)(moveTransB));
                beMessenger_AppendVec3(self->_messenger, moveTransArgB);
                beMessenger_DispatchSelected(self->_messenger,
                                             &s_MOVETRANS_005173d8[0]);
                beMessenger_SendNamed(
                    self->_messenger, &s_MODELCTRL_005171f8[0],
                    g_starterPreviewModelName_004cd0d0[creation->_chaSelDegi],
                    host->_ramNo, &s_SQ_ENTR_005173e8[0]);
                control->_isNoSelMdl = 0U;
              } else {
                control->_isNoSelMdl = 1U;
              }
              LOAD_NEXT_STEP(control);
              control->_isCansel = 0U;
              break;
            case 1:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                beMessenger_SendNamed(self->_messenger,
                                      &s_MODELCTRL_005171f8[0],
                                      &s_j_namewin02_005173b8[0], host->_ramNo,
                                      &s_SQ_LINESL00_00516dd8[0]);
                LOAD_NEXT_STEP(control);
              }
              break;
            case 2:
              st2Now_4 = control->_st2;
              switch ((unsigned int)st2Now_4) {
              case 0:
                if (moveRight) {
                  if (control->_isNoSelMdl == 0) {
                    beMessenger_SendNamed(
                        self->_messenger, &s_MODELCTRL_005171f8[0],
                        g_starterPreviewModelName_004cd0d0[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &s_ISRUN_00517228[0]);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) ==
                        1) {
                      beMessenger_SendNamed(
                          self->_messenger, &s_MODELCTRL_005171f8[0],
                          g_starterPreviewModelName_004cd0d0[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo, &s_SQ_EXIT_005173f0[0]);
                    }
                  }
                  nextDegi = creation->_chaSelDegi + 1;
                  if (nextDegi >= 4) {
                    nextDegi = 0;
                  }
                  creation->_chaSelDegi = nextDegi;
                  beMessenger_SendNamed(
                      self->_messenger, &s_DATABASE_00516c50[0],
                      &s_shinka_00516c60[0], 0, &s_GETDATABASE_00516c68[0]);
                  shinkaDb_2 = beMessenger_GetObject(self->_messenger, 0);
                  rowIndex_2 = 0;
                  rowCursor_2 = (int *)(&g_playerModelRow_004cec70[0]);
                findRow_2:
                  if (igStrCmp(*rowCursor_2,
                               g_starterPlayerModelName_004cd0e0
                                   [creation->_chaSelDegi]) == 0) {
                    shinkaRow_2 = rowIndex_2;
                  } else {
                    rowIndex_2 += 1;
                    rowCursor_2 += 3;
                    if (rowIndex_2 < 0x10) {
                      goto findRow_2;
                    }
                  }
                  TextOrder_ConfigureFont(
                      textOrder, &s_CHRSELFONT14_005173c8[0], host->_ramNo, 0,
                      beDataBase_GetRecordString(shinkaDb_2, shinkaRow_2,
                                                 &s_NAME_00516c78[0]),
                      1, 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                               &s_j_digiselcursorright_005173a0[0],
                               &s_SQ_ON00_00517028[0], 1);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, &s_j_namewin02_005173b8[0],
                               &s_SQ_LINECG00_005173f8[0], 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(
                      models, host->_ramNo, &s_j_digifacewin_00516ca8[0],
                      g_playerModelRowSeq_004cec78[creation->_chaSelDegi * 3],
                      0);
                  LOAD_NEXT_SUBSTEP(control);
                } else if (moveLeft) {
                  if (control->_isNoSelMdl == 0) {
                    beMessenger_SendNamed(
                        self->_messenger, &s_MODELCTRL_005171f8[0],
                        g_starterPreviewModelName_004cd0d0[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &s_ISRUN_00517228[0]);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) ==
                        1) {
                      beMessenger_SendNamed(
                          self->_messenger, &s_MODELCTRL_005171f8[0],
                          g_starterPreviewModelName_004cd0d0[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo, &s_SQ_EXIT_005173f0[0]);
                    }
                  }
                  prevDegi = creation->_chaSelDegi - 1;
                  if (prevDegi < 0) {
                    prevDegi = 3;
                  }
                  creation->_chaSelDegi = prevDegi;
                  beMessenger_SendNamed(
                      self->_messenger, &s_DATABASE_00516c50[0],
                      &s_shinka_00516c60[0], 0, &s_GETDATABASE_00516c68[0]);
                  shinkaDb_3 = beMessenger_GetObject(self->_messenger, 0);
                  rowIndex_3 = 0;
                  rowCursor_3 = (int *)(&g_playerModelRow_004cec70[0]);
                findRow_3:
                  if (igStrCmp(*rowCursor_3,
                               g_starterPlayerModelName_004cd0e0
                                   [creation->_chaSelDegi]) == 0) {
                    shinkaRow_3 = rowIndex_3;
                  } else {
                    rowIndex_3 += 1;
                    rowCursor_3 += 3;
                    if (rowIndex_3 < 0x10) {
                      goto findRow_3;
                    }
                  }
                  TextOrder_ConfigureFont(
                      textOrder, &s_CHRSELFONT14_005173c8[0], host->_ramNo, 0,
                      beDataBase_GetRecordString(shinkaDb_3, shinkaRow_3,
                                                 &s_NAME_00516c78[0]),
                      1, 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                               &s_j_digiselcursorleft_00517380[0],
                               &s_SQ_ON00_00517028[0], 1);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, &s_j_namewin02_005173b8[0],
                               &s_SQ_LINECG00_005173f8[0], 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(
                      models, host->_ramNo, &s_j_digifacewin_00516ca8[0],
                      g_playerModelRowSeq_004cec78[creation->_chaSelDegi * 3],
                      0);
                  LOAD_NEXT_SUBSTEP(control);
                } else {
                  modelReady = 0;
                  beMessenger_SendNamed(
                      self->_messenger, &s_MODELCTRL_005171f8[0],
                      g_starterPreviewModelName_004cd0d0[creation->_chaSelDegi],
                      host->_ramNo, &s_ISRUN_00517228[0]);
                  if (beMessenger_GetBoolCount(self->_messenger) > 0) {
                    modelReady =
                        beMessenger_GetBool(self->_messenger, 0) & 0xFF;
                  } else if (control->_isNoSelMdl == 1) {
                    modelReady = 1 & 0xFF;
                  }
                  if ((modelReady & 0xFF) == 1) {
                    if (padTrigger & kPadCross) {
                      LOAD_NEXT_STEP(control);
                    } else if (padTrigger & kPadCircle) {
                      control->_isCansel = 1U;
                      LOAD_NEXT_STEP(control);
                    }
                  } else {
                    beMessenger_SendNamed(
                        self->_messenger, &s_MODELCTRL_005171f8[0],
                        g_starterPreviewModelName_004cd0d0[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &s_GENERATE_00517208[0]);
                    beMessenger_SendNamed(
                        self->_messenger, &s_MODELCTRL_005171f8[0],
                        g_starterPreviewModelName_004cd0d0[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &s_ISRUN_00517228[0]);
                    modelIsRun_2 = LoadHelpers::GetBool(self);
                    if ((modelIsRun_2 & 0xFF) == 1) {
                      FUN_001ae1a0(moveTransC, 0, 0, 0);
                      FUN_001ae1a0(moveTransD, 0, 0, 0);
                      beMessenger_SelectReceivers(
                          self->_messenger, &s_MODELCTRL_005171f8[0],
                          g_starterPreviewModelName_004cd0d0[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo);
                      LoadVec3 moveTransArgC(*(LoadVec3 *)(moveTransC));
                      beMessenger_AppendVec3(self->_messenger, moveTransArgC);
                      LoadVec3 moveTransArgD(*(LoadVec3 *)(moveTransD));
                      beMessenger_AppendVec3(self->_messenger, moveTransArgD);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_MOVETRANS_005173d8[0]);
                      beMessenger_SendNamed(
                          self->_messenger, &s_MODELCTRL_005171f8[0],
                          g_starterPreviewModelName_004cd0d0[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo, &s_SQ_ENTR_005173e8[0]);
                      control->_isNoSelMdl = 0U;
                    } else {
                      control->_isNoSelMdl = 1U;
                    }
                  }
                }
                break;
              case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                  LOAD_RESTART_SUBSTEP(control);
                }
                break;
              }
              break;
            case 3:
              if (control->_isCansel != 0) {
                beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_namewin02_005173b8[0],
                             &s_SQ_CANCEL_00516d50[0], 1);
              } else {
                beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_namewin02_005173b8[0],
                             &s_SQ_LINEON00_00516d40[0], 1);
              }
              if (control->_isNoSelMdl == 0) {
                beNDMWLoadIntf2ComMdlCtrl__Close(
                    models, host->_ramNo,
                    g_starterPreviewModelName_004cd0d0[creation->_chaSelDegi],
                    &s_SQ_EXIT_005173f0[0], 1);
              }
              TextOrder_ClearFont(textOrder, &s_CHRSELFONT14_005173c8[0], host->_ramNo,
                           0);
              LOAD_NEXT_STEP(control);
              break;
            case 4:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                LOAD_NEXT_STEP(control);
              }
              break;
            case 5:
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_digifacewin_00516ca8[0],
                           &s_SQ_CLOSE_00516d30[0], 1);
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
                           &s_j_digiselcursorleft_00517380[0],
                           &s_SQ_CLOSE_00516d30[0], 1);
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
                           &s_j_digiselcursorright_005173a0[0],
                           &s_SQ_CLOSE_00516d30[0], 1);
              LOAD_NEXT_STEP(control);
              break;
            case 6:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                if (control->_isCansel == 1) {
                  LOAD_ENTER_STATE(control, 3);
                } else {
                  LOAD_ENTER_STATE(control, 5);
                  beNDMWLoadIntf2NameSel__Init(nameEntry, 1);
                }
              }
              break;
            }
            break;
          /* Screen 5: name entry (NameSel). A finished name (_isMakeName) goes
           * to screen 8 with _isNewMake set, a cancelled one back to screen 4.
           */
          case 5:
            st1Now_6 = control->_st1;
            switch ((unsigned int)st1Now_6) {
            case 0:
            default:
              nameEntry->_selDataNo = creation->_chaSelDegi;
              LOAD_NEXT_STEP(control);
              FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x517));
              break;
            case 1:
              if (beNDMWLoadIntf2NameSel__Update(nameEntry,
                               LoadHelpers::FlagAt(common, host)->_isCtrl) !=
                  0) {
                if (nameEntry->_isMakeName == 1) {
                  control->_isNewMake = 1U;
                  LOAD_ENTER_STATE(control, 8);
                } else {
                  LOAD_ENTER_STATE(control, 4);
                }
              } else if (nameEntry->_isQuestion == 1) {
                LOAD_NEXT_STEP(control);
              }
              break;
            case 2:
              FUN_003ecb00(messages, LOAD_TEXT_ID(host, 0x519));
              LOAD_NEXT_STEP(control);
              break;
            case 3:
              if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(messages) & 0xFF)) {
                LOAD_NEXT_STEP(control);
              }
              break;
            case 4:
              FUN_003ecae0(messages, LOAD_TEXT_ID(host, 0x51B), 0);
              LOAD_NEXT_STEP(control);
              break;
            case 5:
              if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(messages) & 0xFF)) {
                messageChoice = FUN_003ecb80(messages);
                switch ((unsigned int)messageChoice) {
                case 0:
                  beNDMWLoadIntf2NameSel__SetAnswer(nameEntry, 1);
                  break;
                case 1:
                  FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x517));
                  beNDMWLoadIntf2NameSel__SetAnswer(nameEntry, 0);
                  break;
                }
                LOAD_SET_STEP(control, 1);
              }
              break;
            }
            break;
          /* Screen 6: slot selection (SelSlot). A re-open request repeats
           * screen 6, cancel returns to screen 3, a chosen slot continues at
           * screen 7. */
          case 6:
            st1Now_9 = control->_st1;
            switch ((unsigned int)st1Now_9) {
            case 0:
              st2Now_10 = control->_st2;
              switch ((unsigned int)st2Now_10) {
              case 0:
                beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, host->_ramNo, 2);
                beNDMWLoadIntf2SelSlot__Init(slots);
                slots->_st0 = 0;
                slots->_st3 = 0;
                slots->_st2 = 0;
                slots->_st1 = 0;
                kindHard_18 = common->_kindHard;
                messageId_10 = -1;
                switch ((unsigned int)kindHard_18) {
                case 0:
                  messageId_10 = LOAD_TEXT_ID(host, 0x1009);
                  break;
                case 1:
                  messageId_10 = LOAD_TEXT_ID(host, 0x2009);
                  break;
                case 2:
                  messageId_10 = LOAD_TEXT_ID(host, 0x3009);
                  break;
                }
                FUN_003ecad0(messages, messageId_10);
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2SelSlot__Open(slots, -1, 2) & 0xFF) == 1) {
                  slots->_st0 = 1;
                  slots->_st3 = 0;
                  slots->_st2 = 0;
                  slots->_st1 = 0;
                  LOAD_NEXT_STEP(control);
                }
                break;
              }
              break;
            case 1:
              st2Now_6 = control->_st2;
              switch ((unsigned int)st2Now_6) {
              case 0:
                if ((beNDMWLoadIntf2SelSlot__UpdateSelection(
                         slots, LoadHelpers::FlagAt(common, host)->_isCtrl, 1) &
                     0xFF) == 1) {
                  if (slots->_isReOpenReq == 1) {
                    LOAD_NEXT_STEP(control);
                  } else if (slots->_isCansel == 1) {
                    LOAD_NEXT_STEP(control);
                  } else {
                    LOAD_NEXT_SUBSTEP(control);
                  }
                }
                break;
              case 1:
                st3Now = control->_st3;
                switch ((unsigned int)st3Now) {
                case 0:
                  kindHard = common->_kindHard;
                  messageId_11 = -1;
                  switch ((unsigned int)kindHard) {
                  case 0:
                    messageId_11 = LOAD_TEXT_ID(host, 0x1004);
                    break;
                  case 1:
                    messageId_11 = LOAD_TEXT_ID(host, 0x2004);
                    break;
                  case 2:
                    messageId_11 = LOAD_TEXT_ID(host, 0x3004);
                    break;
                  }
                  FUN_003ecad0(messages, messageId_11);
                  FUN_003ee250(common, host->_ramNo, 5);
                  control->_st3 = (control->_st3 + 1);
                  break;
                case 1:
                  utilReturn = LoadHelpers::FlagAt(common, host)->_utilReturn;
                  switch ((unsigned int)utilReturn) {
                  case 0:
                    LOAD_NEXT_STEP(control);
                    break;
                  case 1:
                  case 2:
                    kindHard_2 = common->_kindHard;
                    messageId_12 = -1;
                    switch ((unsigned int)kindHard_2) {
                    case 0:
                      messageId_12 = LOAD_TEXT_ID(host, 0x1009);
                      break;
                    case 1:
                      messageId_12 = LOAD_TEXT_ID(host, 0x2009);
                      break;
                    case 2:
                      messageId_12 = LOAD_TEXT_ID(host, 0x3009);
                      break;
                    }
                    FUN_003ecad0(messages, messageId_12);
                    beNDMWLoadIntf2SelSlot__PublishCursor(slots);
                    LOAD_SET_STEP(control, 1);
                    break;
                  case 4:
                    kindHard_3 = common->_kindHard;
                    messageId_13 = -1;
                    switch ((unsigned int)kindHard_3) {
                    case 0:
                      messageId_13 = LOAD_TEXT_ID(host, 0x1009);
                      break;
                    case 1:
                      messageId_13 = LOAD_TEXT_ID(host, 0x2009);
                      break;
                    case 2:
                      messageId_13 = LOAD_TEXT_ID(host, 0x3009);
                      break;
                    }
                    FUN_003ecad0(messages, messageId_13);
                    beNDMWLoadIntf2SelSlot__PublishCursor(slots);
                    LOAD_SET_STEP(control, 1);
                    break;
                  }
                  break;
                }
                break;
              }
              break;
            case 2:
              st2Now_5 = control->_st2;
              switch ((unsigned int)st2Now_5) {
              case 0:
                slots->_st0 = 2;
                slots->_st3 = 0;
                slots->_st2 = 0;
                slots->_st1 = 0;
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2SelSlot__Close(slots) & 0xFF) == 1) {
                  if (slots->_isReOpenReq == 1) {
                    LOAD_ENTER_STATE(control, 6);
                  } else if (slots->_isCansel == 1) {
                    LOAD_ENTER_STATE(control, 3);
                  } else {
                    LOAD_ENTER_STATE(control, 7);
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
          case 7:
            st1Now_5 = control->_st1;
            switch ((unsigned int)st1Now_5) {
            case 0x0:
              FUN_003dafb0(dataSelection, host->_ramNo, 0);
              LOAD_NEXT_STEP(control);
              break;
            case 0x1:
              st2Now = control->_st2;
              switch ((unsigned int)st2Now) {
              case 0:
                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                if ((FUN_003db060(dataSelection, 0) & 0xFF) == 1) {
                  LOAD_NEXT_SUBSTEP(control);
                }
                break;
              case 2:
                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 3:
                if (LoadHelpers::FlagAt(common, host)->_isCutConnect == 1) {
                  beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                  LOAD_NEXT_SUBSTEP(control);
                  control->_st3 = 1;
                } else if ((beNDMWLoadIntf2DataSelIntf__UpdateSelection(dataSelection, 0) & 0xFF) == 1) {
                  beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                  LOAD_NEXT_SUBSTEP(control);
                  control->_st3 = 0;
                }
                break;
              case 4:
                if ((FUN_003dbf90(dataSelection, 0) & 0xFF) == 1) {
                  st3Now_2 = control->_st3;
                  switch ((unsigned int)st3Now_2) {
                  case 0:
                    LOAD_NEXT_STEP(control);
                    break;
                  case 1:
                    LOAD_SET_STEP(control, 0x64);
                    break;
                  }
                }
                break;
              }
              break;
            case 0x2:
              if (dataSelection->_isCancel == 1) {
                LOAD_ENTER_STATE(control, 6);
              } else {
                control->_isNewMake = 0U;
                LOAD_ENTER_STATE(control, 8);
              }
              break;
            case 0x64:
              st2Now_2 = control->_st2;
              switch ((unsigned int)st2Now_2) {
              case 0:
                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                if ((FUN_003dbf90(dataSelection, 0) & 0xFF) == 1) {
                  allocator = LoadHelpers::Selector(
                      &g_defaultAllocatorSelector_00587110[0],
                      igObject_GetAllocator(self));
                  {
                    RecoveryRef<0> freshDataRef(
                        (void *)(beNDMWDegiData_Create(allocator)));
                    ObjectList_SetAtRetained_003e9160(
                        common->_gameUseData, host->_ramNo, freshDataRef.value);
                  }
                  LOAD_ENTER_STATE(control, 6);
                }
                break;
              }
              break;
            }
            break;
          /* Screen 8: start. Builds the player record (a new character through
           * GAMESTART/UNIQUE, or the saved one through
           * GAMEDATAINIT/BASE2CURRENT/ RECALCPLAYER), then the difficulty
           * choice and status display; START with every entered player ready
           * ends the interface (common->_intfStat = 3). */
          case 8:
            st1Now_7 = control->_st1;
            switch ((unsigned int)st1Now_7) {
            case 0:
              st2Now_7 = control->_st2;
              switch ((unsigned int)st2Now_7) {
              case 0:
                st3Now_3 = control->_st3;
                switch ((unsigned int)st3Now_3) {
                case 0:
                  if (control->_isRdyCancel == 1) {
                    if (control->_isNewMake == 1) {
                      beMessenger_SelectGroup(self->_messenger,
                                              &s_GAMERAM_00517338[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_GAMEDATAINIT_00517408[0]);
                      allocator_2 = LoadHelpers::Selector(
                          &g_ndmwAllocatorSelector_00587108[0],
                          igObject_GetAllocator(self));
                      nameObject = (void *)FUN_003614f0(allocator_2);
                      {
                        RecoveryRef<1> nameRef(nameObject);
                        beUnicodeObj_AllocateBuffer(nameRef.value, 8);
                        /* Hypothesis: the word at nameRef+12 points at the
                         * 8-character buffer sized by beUnicodeObj_AllocateBuffer(nameRef, 8). */
                        NameCopyHelper::Copy(
                            (unsigned short *)*(int *)((char *)nameRef.value +
                                                       NAME_OBJECT_TEXT_OFFSET),
                            nameEntry);
                        beMessenger_SelectGroup(self->_messenger,
                                                &s_GAMERAM_00517338[0]);
                        beMessenger_AppendInt(self->_messenger, host->_ramNo);
                        beMessenger_AppendString(
                            self->_messenger,
                            g_playerModelRow_004cec70[creation->_chaSelDegi *
                                                      3]);
                        beMessenger_AppendObject(self->_messenger,
                                                 nameRef.value);
                        beMessenger_DispatchSelected(self->_messenger,
                                                     &s_GAMESTART_00517418[0]);
                      }
                      beMessenger_SelectGroup(self->_messenger,
                                              &s_GAMERAM_00517338[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_GETPLAYER_00517340[0]);
                      newPlayer = beMessenger_GetObject(self->_messenger, 0);
                      /* Stamp the new character with the low word of the world
                       * clock as its UNIQUE property. */
                      worldTime = ((igInsightCore *)self->_insight)->_worldTime;
                      {
                        void *record = igProperty_GetRecord(
                            newPlayer, &s_UNIQUE_00517428[0]);
                        *(int *)((char *)record + 12) = (int)worldTime;
                      }
                      beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(
                                       common->_gameUseData, host->_ramNo),
                                   newPlayer);
                    } else {
                      beMessenger_SelectGroup(self->_messenger,
                                              &s_GAMERAM_00517338[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_GAMEDATAINIT_00517408[0]);
                      saveAreaIndex = *(volatile const int *)&dataSelection
                                           ->_svDataSelPoint;
                      {
                        RecoveryRef<0> savedDataRef(
                            (void *)(DataList_GetWordAt_003e90f0(
                                ((beNDMWLoadSlotPlayer
                                      *)((beNDMWLoadSavePlWork *)
                                             DataList_GetWordAt_003e9240(
                                                 common->_flagWork,
                                                 host->_ramNo))
                                     ->_haveSaveData)
                                    ->_saveDataList,
                                saveAreaIndex)),
                            true);
                        ObjectList_SetAtRetained_003e9160(common->_gameUseData,
                                                          host->_ramNo,
                                                          savedDataRef.value);
                        beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, host->_ramNo);
                      }
                      beMessenger_SelectGroup(self->_messenger,
                                              &s_GAMERAM_00517338[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_GETPLAYER_00517340[0]);
                      loadedPlayer = beMessenger_GetObject(self->_messenger, 0);
                      font = FUN_00236f80(self->_insight,
                                          g_beFont_metaObject_00589678[0]);
                      beNDMWDegiData__StoreToProperties(ObjectList_GetAt_003e9260(
                                       common->_gameUseData, host->_ramNo),
                                   loadedPlayer, font);
                      kindName = ((beNDMWDegiData *)ObjectList_GetAt_003e9260(
                                      common->_gameUseData, host->_ramNo))
                                     ->_dmkind;
                      beMessenger_SelectGroup(self->_messenger,
                                              &s_GAMERAM_00517338[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_AppendString(self->_messenger, kindName);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_BASE2CURRENT_00517430[0]);
                      beMessenger_SelectGroup(self->_messenger,
                                              &s_GAMERAM_00517338[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &s_RECALCPLAYER_00517440[0]);
                    }
                  }
                  needsDifficulty = 0;
                  difficultyCase = 0;
                  if ((host->_ramNo == 0) && (control->_isRdyCancel == 1)) {
                    common->_difficultMode = 0;
                    self->_difficultMax = 0;
                    DAT_0058a1e0[0] = 0;
                    beLua__RunNamedChunk(FUN_00236f80(self->_insight,
                                              g_beLua_metaObject_00589208[0]),
                                 &s_hostLoad_lua_00517450[0], 0);
                    difficultMax = self->_difficultMax;
                    switch ((unsigned int)difficultMax) {
                    case 0:
                      break;
                    case 1:
                      needsDifficulty = 1 & 0xFF;
                      difficultyCase = 1;
                      break;
                    case 2:
                      difficultyCase = 2;
                      needsDifficulty = 1;
                      break;
                    }
                  }
                  if (!(needsDifficulty & 0xFF)) {
                    ramNoCopy = *(volatile const int *)&host->_ramNo;
                    FUN_003d9e10(
                        ObjectList_GetAt_003e9260(status->_statDataList, 0), 1,
                        ramNoCopy);
                    LOAD_NEXT_SUBSTEP(control);
                  } else {
                    switch ((unsigned int)difficultyCase) {
                    case 1:
                      beNDMWLoadIntf2Diffselect__Init(difficulty, 0, host->_ramNo);
                      break;
                    case 2:
                      beNDMWLoadIntf2Diffselect__Init(difficulty, 1, host->_ramNo);
                      break;
                    }
                    control->_st3 = (control->_st3 + 1);
                  }
                  break;
                case 1:
                  if ((beNDMWLoadIntf2Diffselect__Update(
                           difficulty,
                           LoadHelpers::FlagAt(common, host)->_isCtrl) &
                       0xFF) == 1) {
                    if (difficulty->_isCancel == 1) {
                      allocator_3 = LoadHelpers::Selector(
                          &g_defaultAllocatorSelector_00587110[0],
                          igObject_GetAllocator(self));
                      {
                        RecoveryRef<0> freshDataRef_2(
                            (void *)(beNDMWDegiData_Create(allocator_3)));
                        ObjectList_SetAtRetained_003e9160(common->_gameUseData,
                                                          host->_ramNo,
                                                          freshDataRef_2.value);
                      }
                      LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                      LOAD_ENTER_STATE(control, 6);
                    } else {
                      common->_difficultMode = difficulty->_selectPoint;
                      ramNoCopy_2 = *(volatile const int *)&host->_ramNo;
                      FUN_003d9e10(
                          ObjectList_GetAt_003e9260(status->_statDataList, 0),
                          1, ramNoCopy_2);
                      LOAD_NEXT_SUBSTEP(control);
                    }
                  }
                  break;
                }
                break;
              case 1:
                if ((FUN_003da7c0(
                         ObjectList_GetAt_003e9260(status->_statDataList, 0)) &
                     0xFF) == 1) {
                  LoadHelpers::FlagAt(common, host)->_isRdy = 1;
                  if (host->_ramNo == 0) {
                    workList = (void *)common->_flagWork;
                    entryCount = 0;
                    workIndex = 0;
                    readyCount = 0;
                    if (0 < FUN_002294f0(workList)) {
                      do {
                        if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(
                                 workList, workIndex)) &
                             0xFF) == 1) {
                          entryCount += 1;
                        }
                        if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(
                                 workList, workIndex)) &
                             0xFF) == 1) {
                          readyCount += 1;
                        }
                        workIndex += 1;
                      } while (workIndex < FUN_002294f0(workList));
                    }
                    if ((entryCount == readyCount) == 1) {
                      LOAD_SET_STEP(control, 3);
                    } else {
                      LOAD_SET_STEP(control, 1);
                    }
                  } else {
                    LOAD_SET_STEP(control, 1);
                  }
                }
                break;
              }
              break;
            case 1:
              st1Now = control->_st2;
              switch ((unsigned int)st1Now) {
              case 0:
                if (control->_isRdyCancel == 1) {
                  FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x530));
                } else {
                  FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x52F));
                }
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                st3Now_4 = control->_st3;
                switch ((unsigned int)st3Now_4) {
                case 0:
                  if (host->_ramNo == 0) {
                    workList_2 = (void *)common->_flagWork;
                    entryCount_2 = 0;
                    readyCount_2 = 0;
                    workIndex_2 = 0;
                    if (0 < FUN_002294f0(workList_2)) {
                      do {
                        if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(
                                 workList_2, workIndex_2)) &
                             0xFF) == 1) {
                          entryCount_2 += 1;
                        }
                        if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(
                                 workList_2, workIndex_2)) &
                             0xFF) == 1) {
                          readyCount_2 += 1;
                        }
                        workIndex_2 += 1;
                      } while (workIndex_2 < FUN_002294f0(workList_2));
                    }
                    if ((entryCount_2 == readyCount_2) == 1) {
                      LOAD_SET_STEP(control, 3);
                    } else if ((padTrigger & kPadCircle) &&
                               (control->_isRdyCancel == 1)) {
                      LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                      LOAD_NEXT_STEP(control);
                    }
                  } else {
                    workList_3 = (void *)common->_flagWork;
                    entryCount_3 = 0;
                    readyCount_3 = 0;
                    workIndex_3 = 0;
                    if (0 < FUN_002294f0(workList_3)) {
                      do {
                        if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(
                                 workList_3, workIndex_3)) &
                             0xFF) == 1) {
                          entryCount_3 += 1;
                        }
                        if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(
                                 workList_3, workIndex_3)) &
                             0xFF) == 1) {
                          readyCount_3 += 1;
                        }
                        workIndex_3 += 1;
                      } while (workIndex_3 < FUN_002294f0(workList_3));
                    }
                    if ((entryCount_3 == readyCount_3) == 1) {
                      if (control->_isRdyCancel == 1) {
                        FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x51F));
                      } else {
                        FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x522));
                      }
                      control->_st3 = (control->_st3 + 1);
                    } else if ((padTrigger & kPadCircle) &&
                               (control->_isRdyCancel == 1)) {
                      LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                      LOAD_NEXT_STEP(control);
                    }
                  }
                  break;
                case 1:
                  workList_4 = (void *)common->_flagWork;
                  entryCount_4 = 0;
                  readyCount_4 = 0;
                  workIndex_4 = 0;
                  if (0 < FUN_002294f0(workList_4)) {
                    do {
                      if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(
                               workList_4, workIndex_4)) &
                           0xFF) == 1) {
                        entryCount_4 += 1;
                      }
                      if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(
                               workList_4, workIndex_4)) &
                           0xFF) == 1) {
                        readyCount_4 += 1;
                      }
                      workIndex_4 += 1;
                    } while (workIndex_4 < FUN_002294f0(workList_4));
                  }
                  if ((entryCount_4 == readyCount_4) == 0) {
                    if (control->_isRdyCancel == 1) {
                      FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x530));
                    } else {
                      FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x52F));
                    }
                    control->_st3 = 0;
                  } else if ((padTrigger & kPadCircle) &&
                             (control->_isRdyCancel == 1)) {
                    LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                    LOAD_NEXT_STEP(control);
                  }
                  break;
                }
                break;
              }
              break;
            case 2:
              st2Now_8 = control->_st2;
              switch ((unsigned int)st2Now_8) {
              case 0:
                beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                             &s_j_mainstatuswin_00516cc0[0],
                             &s_SQ_CANCEL_00516d50[0], 1);
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models, 3) & 0xFF) == 1) {
                  LOAD_NEXT_SUBSTEP(control);
                }
                break;
              case 2:
                FUN_003d9e70(
                    ObjectList_GetAt_003e9260(status->_statDataList, 0), 0);
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 3:
                if ((FUN_003da7c0(
                         ObjectList_GetAt_003e9260(status->_statDataList, 0)) &
                     0xFF) == 1) {
                  if (control->_isNewMake == 1) {
                    LOAD_ENTER_STATE(control, 5);
                    beNDMWLoadIntf2NameSel__Init(nameEntry, 0);
                  } else {
                    allocator_4 = LoadHelpers::Selector(
                        &g_defaultAllocatorSelector_00587110[0],
                        igObject_GetAllocator(self));
                    {
                      RecoveryRef<0> freshDataRef_3(
                          (void *)(beNDMWDegiData_Create(allocator_4)));
                      ObjectList_SetAtRetained_003e9160(common->_gameUseData,
                                                        host->_ramNo,
                                                        freshDataRef_3.value);
                    }
                    LOAD_ENTER_STATE(control, 6);
                  }
                }
                break;
              }
              break;
            case 3:
              st2Now_3 = control->_st2;
              switch ((unsigned int)st2Now_3) {
              case 0:
                if (control->_isRdyCancel == 1) {
                  FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x51D));
                } else {
                  FUN_003ecad0(messages, LOAD_TEXT_ID(host, 0x521));
                }
                LOAD_NEXT_SUBSTEP(control);
                break;
              case 1:
                if ((padTrigger & kPadCircle) && (control->_isRdyCancel == 1)) {
                  LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                  LOAD_SET_STEP(control, 2);
                } else {
                  workList_5 = (void *)common->_flagWork;
                  entryCount_5 = 0;
                  readyCount_5 = 0;
                  workIndex_5 = 0;
                  if (0 < FUN_002294f0(workList_5)) {
                    do {
                      if ((beNDMWLoadSavePlWork__GetIsEntry(DataList_GetWordAt_003e9240(
                               workList_5, workIndex_5)) &
                           0xFF) == 1) {
                        entryCount_5 += 1;
                      }
                      if ((beNDMWLoadSavePlWork__GetIsRdy(DataList_GetWordAt_003e9240(
                               workList_5, workIndex_5)) &
                           0xFF) == 1) {
                        readyCount_5 += 1;
                      }
                      workIndex_5 += 1;
                    } while (workIndex_5 < FUN_002294f0(workList_5));
                  }
                  if ((entryCount_5 == readyCount_5) == 1) {
                    if (padTrigger & kPadStart) {
                      workIndex_6 = 0;
                      common->_intfStat = 3;
                      workList_6 = (void *)common->_flagWork;
                      if (0 < FUN_002294f0(workList_6)) {
                        do {
                          beNDMWLoadSavePlWork__SetIsCtrl(DataList_GetWordAt_003e9240(workList_6,
                                                                   workIndex_6),
                                       0);
                          workIndex_6 += 1;
                        } while (workIndex_6 < FUN_002294f0(workList_6));
                      }
                      ((beSystem *)common->_system)->_isSResetEnable = 0;
                      LOAD_NEXT_SUBSTEP(control);
                    }
                  } else {
                    LOAD_SET_STEP(control, 1);
                  }
                }
                break;

              case 3:
                goto done;
              }
              break;
            }
            break;
          }
        }
        break;
      /* Stage 2: leaving. Close the windows of the screen that was active
       * (leaveState); once they are closed _isClose is set and the work moves
       * on to step 3. */
      case 2:
        hostStat1_2 = LoadHelpers::FlagAt(common, host)->_sysStat1;
        switch ((unsigned int)hostStat1_2) {
        case 0:
          leaveState = control->_st0;
          switch (leaveState) {
          default:
            exitWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_SET_STEP(exitWork, 1);
            break;
          case 2:
            exitWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_SET_STEP(exitWork, 1);
            break;
          case 8:
            beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_chrselmesswin_00517360[0],
                         &s_SQ_CLOSE_00516d30[0], 1);
            beNDMWLoadIntf2MesWin__RequestClose(messages);
            FUN_003d9e90(ObjectList_GetAt_003e9260(status->_statDataList, 0));
            exitWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_SET_STEP(exitWork, 2);
            break;
          }
          beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, &s_j_chrselbase_00517328[0],
                       &s_SQ_CLOSE_00516d30[0], 1);
          break;
        case 1:
          if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
            LoadHelpers::FlagAt(common, host)->_isClose = 1;
            hostWork_3 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_SET_STEP(hostWork_3, 3);
          }
          break;
        case 2:
          if (((FUN_003da7c0(
                    ObjectList_GetAt_003e9260(status->_statDataList, 0)) &
                0xFF) == 1) &&
              ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1)) {
            LoadHelpers::FlagAt(common, host)->_isClose = 1;
            hostWork_4 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                common->_flagWork, host->_ramNo));
            PLAYER_SET_STEP(hostWork_4, 3);
          }
          break;

        case 3:
          goto done;
        }
        break;
      /* Stage 5: memory-card utility steps (common->_mcUtilCtrl). Each step
       * calls one shared card helper per frame until it reports 1 (done) or 2
       * (failed). */
      case 5:
        if (LoadHelpers::McUtil(common)->_isUseUtil == 1) {
          cardWork = LoadHelpers::FlagAt(common, host);
          cardStat1 = cardWork->_sysStat1;
          switch ((unsigned int)cardStat1) {
          case 0:
            stepResult = FUN_003ed050(common, host->_ramNo, messages,
                                      slots->_mcSelPoint, 3);
            switch ((unsigned int)stepResult) {
            case 0:
              break;
            case 1:
              PLAYER_SET_STEP(cardWork, 5);
              break;
            case 2:
              utilResult = LoadHelpers::McUtil(common)->_result;
              switch ((unsigned int)utilResult) {
              case 2:
                PLAYER_SET_STEP(cardWork, 5);
                break;
              case 7:
                if (common->_kindHard == 1) {
                  PLAYER_SET_STEP(cardWork, 3);
                } else {
                  PLAYER_ENTER_STAGE(cardWork, 6);
                }
                break;
              case 12:
                PLAYER_ENTER_STAGE(cardWork, 6);
                break;
              default:
              case 4:
              case 3:
                PLAYER_ENTER_STAGE(cardWork, 6);
                break;
              }
              break;
            }
            break;
          case 1:
            if (((beNDMWMcSlot *)ObjectList_GetAt_003e9260(
                     LoadHelpers::McUtil(common)->_slot, slots->_mcSelPoint))
                    ->_isConnect != 1) {
              FUN_003ecb20(messages);
              PLAYER_ENTER_STAGE(cardWork, 7);
              cardWork->_utilReturn = 2;
            } else {
              kindHard_4 = common->_kindHard;
              firstTextId = -1;
              secondTextId = -1;
              switch ((unsigned int)kindHard_4) {
              case 0:
                playerTextBase = host->_ramNo << 0x10;
                firstTextId = playerTextBase | 0x1000;
                secondTextId = playerTextBase | 0x1002;
                break;
              case 1:
                playerTextBase_2 = host->_ramNo << 0x10;
                firstTextId = playerTextBase_2 | 0x2000;
                secondTextId = playerTextBase_2 | 0x2002;
                break;
              case 2:
                playerTextBase_3 = host->_ramNo << 0x10;
                firstTextId = playerTextBase_3 | 0x3000;
                secondTextId = playerTextBase_3 | 0x3002;
                break;
              }
              stepResult_2 = FUN_003ecdc0(common, host->_ramNo, messages,
                                          firstTextId, secondTextId, 0, 3);
              switch ((unsigned int)stepResult_2) {
              case 0:
                break;
              case 1:
                PLAYER_SET_STEP(cardWork, 2);
                break;
              case 2:
                PLAYER_ENTER_STAGE(cardWork, 7);
                cardWork->_utilReturn = 1;
                break;
              }
            }
            break;
          case 2:
            cardStat2 = cardWork->_sysStat2;
            switch ((unsigned int)cardStat2) {
            case 0:
              if (common->_isTitle == 0) {
                ((beSystem *)self->_system_)->_isSResetEnable = 0;
              }
              ((beSystem *)self->_system_)->_isResetEnable = 0;
              cardWork->_sysStat2 = (*(volatile int *)&cardWork->_sysStat2 + 1);
              cardWork->_sysStat3 = 0;
              break;
            case 1:
              stepResult_3 = FUN_003ed2e0(common, host->_ramNo, messages,
                                          slots->_mcSelPoint, 3);
              switch ((unsigned int)stepResult_3) {
              case 0:
                break;
              case 1:
                PLAYER_SET_STEP(cardWork, 5);
                break;
              case 2:
                utilResult_3 = LoadHelpers::McUtil(common)->_result;
                switch (utilResult_3 - 3U) {
                case 4:
                  PLAYER_SET_STEP(cardWork, 3);
                  break;
                case 6:
                case 7:
                  PLAYER_ENTER_STAGE(cardWork, 6);
                  cardWork->_utilReturn = 1;
                  break;
                default:
                case 0:
                case 1:
                case 2:
                case 3:
                case 5:
                case 8:
                case 9:
                  PLAYER_ENTER_STAGE(cardWork, 6);
                  cardWork->_utilReturn = 1;
                  break;
                }
                break;
              }
              if (stepResult_3 != 0) {
                if (common->_isTitle == 0) {
                  ((beSystem *)self->_system_)->_isSResetEnable = 1;
                }
                ((beSystem *)self->_system_)->_isResetEnable = 1;
              }
              break;
            }
            break;
          case 3:
            if (((beNDMWMcSlot *)ObjectList_GetAt_003e9260(
                     LoadHelpers::McUtil(common)->_slot, slots->_mcSelPoint))
                    ->_isConnect != 1) {
              FUN_003ecb20(messages);
              PLAYER_ENTER_STAGE(cardWork, 7);
              cardWork->_utilReturn = 2;
            } else {
              kindHard_5 = common->_kindHard;
              firstTextId_2 = -1;
              secondTextId_2 = -1;
              switch ((unsigned int)kindHard_5) {
              case 0:
                playerTextBase_4 = host->_ramNo << 0x10;
                firstTextId_2 = playerTextBase_4 | 0x1005;
                secondTextId_2 = playerTextBase_4 | 0x1007;
                break;
              case 1:
                playerTextBase_5 = host->_ramNo << 0x10;
                firstTextId_2 = playerTextBase_5 | 0x2005;
                secondTextId_2 = playerTextBase_5 | 0x2007;
                break;
              case 2:
                playerTextBase_6 = host->_ramNo << 0x10;
                firstTextId_2 = playerTextBase_6 | 0x3005;
                secondTextId_2 = playerTextBase_6 | 0x3007;
                break;
              }
              stepResult_4 = FUN_003ecdc0(common, host->_ramNo, messages,
                                          firstTextId_2, secondTextId_2, 1, 3);
              switch ((unsigned int)stepResult_4) {
              case 0:
                break;
              case 1:
                PLAYER_SET_STEP(cardWork, 4);
                break;
              case 2:
                PLAYER_ENTER_STAGE(cardWork, 7);
                cardWork->_utilReturn = 1;
                break;
              }
            }
            break;
          case 4:
            cardStat2_3 = cardWork->_sysStat2;
            switch ((unsigned int)cardStat2_3) {
            case 0:
              kindHard_6 = common->_kindHard;
              messageId_14 = -1;
              switch ((unsigned int)kindHard_6) {
              case 0:
                messageId_14 = LOAD_TEXT_ID(host, 0x1008);
                break;
              case 1:
                messageId_14 = LOAD_TEXT_ID(host, 0x2008);
                break;
              case 2:
                messageId_14 = LOAD_TEXT_ID(host, 0x3008);
                break;
              }
              FUN_003ecad0(messages, messageId_14);
              if (common->_isTitle == 0) {
                ((beSystem *)self->_system_)->_isSResetEnable = 0;
              }
              ((beSystem *)self->_system_)->_isResetEnable = 0;
              cardWork->_sysStat2 = (*(volatile int *)&cardWork->_sysStat2 + 1);
              cardWork->_sysStat3 = 0;
              break;
            case 1:
              stepResult_5 = beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(common, host->_ramNo, messages,
                                          slots->_mcSelPoint, 3);
              switch ((unsigned int)stepResult_5) {
              case 0:
                break;
              case 1:
                cardWork->_utilReturn = 4;
                PLAYER_ENTER_STAGE(cardWork, 7);
                break;
              case 2:
                utilResult_4 = LoadHelpers::McUtil(common)->_result;
                switch (utilResult_4 - 3U) {
                case 1:
                  PLAYER_ENTER_STAGE(cardWork, 6);
                  cardWork->_utilReturn = 2;
                  break;
                default:
                case 0:
                case 2:
                case 4:
                case 3:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                  cardWork->_utilReturn = 2;
                  PLAYER_ENTER_STAGE(cardWork, 6);
                  break;
                }
                break;
              }
              if (stepResult_5 != 0) {
                if (common->_isTitle == 0) {
                  ((beSystem *)self->_system_)->_isSResetEnable = 1;
                }
                ((beSystem *)self->_system_)->_isResetEnable = 1;
              }
              break;
            }
            break;
          case 5:
            slotPlayer = (beNDMWLoadSlotPlayer *)(0);
            listIndex = 0;
            if (0 < ((beNDMWLoadSlotPlayerList *)*(
                         void *volatile *)&common->_slotSaveData)
                        ->_count) {
            findSlotPlayer:
              {
                int connection =
                    ((beNDMWLoadSlotPlayer *)ObjectList_GetAt_003e9260(
                         common->_slotSaveData, listIndex))
                        ->_connectNO;
                if (connection == slots->_mcSelPoint) {
                  slotPlayer =
                      (beNDMWLoadSlotPlayer *)ObjectList_GetAt_003e9260(
                          common->_slotSaveData, listIndex);
                } else {
                  listIndex += 1;
                  if (listIndex < ((beNDMWLoadSlotPlayerList *)*(
                                       void *volatile *)&common->_slotSaveData)
                                      ->_count) {
                    goto findSlotPlayer;
                  }
                }
              }
            }
            if (slotPlayer == 0) {
              if (LoadHelpers::McUtil(common)->_isUseUtil != 0) {
                cardWork->_sysStat1 = (cardWork->_sysStat1 + 1);
                cardWork->_sysStat3 = 0;
                cardWork->_sysStat2 = 0;
              }
            } else {
              accessList = (DW4ListRec *)slotPlayer->_accessPlList;
              accessCount = accessList->count;
              ramNoCopy_3 = *(volatile const int *)&host->_ramNo;
              if (accessCount < accessList->cap) {
                accessList->count = accessList->count + 1;
              } else {
                List_Resize(accessList, accessCount + 1, 4);
              }
              ((int *)DataList_GetData_003e9090(accessList))[accessCount] =
                  ramNoCopy_3;
              cardWork->_haveSaveData = (int)slotPlayer;
              PLAYER_ENTER_STAGE(cardWork, 7);
              cardWork->_utilReturn = 0;
            }
            break;
          case 6:
            cardStat2_2 = cardWork->_sysStat2;
            switch ((unsigned int)cardStat2_2) {
            case 0:
              cardWork->_sysStat2 = (*(volatile int *)&cardWork->_sysStat2 + 1);
              cardWork->_sysStat3 = 0;
              break;
            case 1:
              stepResult_6 = beNDMWLoadCtrl2CommonIntf__StepReadMedia(common, host->_ramNo, messages,
                                          slots->_mcSelPoint, 3);
              switch ((unsigned int)stepResult_6) {
              case 0:
                break;
              case 1:
                PLAYER_ENTER_STAGE(cardWork, 7);
                cardWork->_utilReturn = 0;
                break;
              case 2:
                utilResult_5 = LoadHelpers::McUtil(common)->_result;
                switch (utilResult_5 - 3U) {
                case 4:
                  PLAYER_SET_STEP(cardWork, 3);
                  break;
                case 6:
                case 7:
                  PLAYER_ENTER_STAGE(cardWork, 6);
                  cardWork->_utilReturn = 1;
                  break;
                default:
                case 0:
                case 1:
                case 2:
                case 3:
                case 5:
                case 8:
                case 9:
                  PLAYER_ENTER_STAGE(cardWork, 6);
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
      case 6:
        resultWork =
            (beNDMWLoadSavePlWork *)(LoadHelpers::FlagAt(common, host));
        if (common->_kindHard == 2) {
          beNDMWLoadIntf2SelSlot__UpdateSelection(slots, 0U, 0);
        }
        switch (resultWork->_sysStat1) {
        default:
          break;
        case 0: {
          resultStat2 = resultWork->_sysStat2;
          switch ((unsigned int)resultStat2) {
          case 0:
            mcUtil = LoadHelpers::McUtil(common);
            if (mcUtil->_isFormatRun == 1) {
              if (mcUtil->_result == 0xC) {
                beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, slots->_mcSelPoint);
              } else {
                beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, -1);
              }
              kindHard_7 = common->_kindHard;
              messageId_15 = -1;
              switch ((unsigned int)kindHard_7) {
              case 0:
                messageId_15 = LOAD_TEXT_ID(host, 0x100E);
                break;
              case 1:
                messageId_15 = LOAD_TEXT_ID(host, 0x200E);
                break;
              case 2:
                messageId_15 = LOAD_TEXT_ID(host, 0x300E);
                break;
              }
              FUN_003ecb00(messages, messageId_15);
            } else if (((beNDMWMcSlot *)ObjectList_GetAt_003e9260(
                            mcUtil->_slot, slots->_mcSelPoint))
                           ->_isConnect == 1) {
              utilResult_2 = LoadHelpers::McUtil(common)->_result;
              if (common->_kindHard != 2) {
                if (utilResult_2 == 0xC) {
                  beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, slots->_mcSelPoint);
                } else {
                  beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, -1);
                }
              }
              switch (utilResult_2 - 3U) {
              case 4:
                kindHard_8 = common->_kindHard;
                messageId_16 = -1;
                switch ((unsigned int)kindHard_8) {
                case 0:
                  messageId_16 = LOAD_TEXT_ID(host, 0x1028);
                  break;
                case 1:
                  messageId_16 = LOAD_TEXT_ID(host, 0x2012);
                  break;
                case 2:
                  messageId_16 = LOAD_TEXT_ID(host, 0x3012);
                  break;
                }
                FUN_003ecb00(messages, messageId_16);
                break;
              case 6:
                kindHard_9 = common->_kindHard;
                messageId = -1;
                switch ((unsigned int)kindHard_9) {
                case 0:
                  messageId = LOAD_TEXT_ID(host, 0x1014);
                  break;
                case 1:
                  messageId = LOAD_TEXT_ID(host, 0x2014);
                  break;
                case 2:
                  messageId = LOAD_TEXT_ID(host, 0x3014);
                  break;
                }
                FUN_003ecb00(messages, messageId);
                break;
              case 7:
                kindHard_10 = common->_kindHard;
                messageId_2 = -1;
                switch ((unsigned int)kindHard_10) {
                case 0:
                  messageId_2 = LOAD_TEXT_ID(host, 0x1015);
                  break;
                case 1:
                  messageId_2 = LOAD_TEXT_ID(host, 0x2015);
                  break;
                case 2:
                  messageId_2 = LOAD_TEXT_ID(host, 0x3015);
                  break;
                }
                FUN_003ecb00(messages, messageId_2);
                break;
              case 2:
                kindHard_11 = common->_kindHard;
                messageId_3 = -1;
                switch ((unsigned int)kindHard_11) {
                case 0:
                  messageId_3 = LOAD_TEXT_ID(host, 0x1010);
                  break;
                case 1:
                  messageId_3 = LOAD_TEXT_ID(host, 0x2010);
                  break;
                case 2:
                  messageId_3 = LOAD_TEXT_ID(host, 0x3010);
                  break;
                }
                FUN_003ecb00(messages, messageId_3);
                break;
              case 3:
                kindHard_12 = common->_kindHard;
                messageId_4 = -1;
                switch ((unsigned int)kindHard_12) {
                case 0:
                  messageId_4 = LOAD_TEXT_ID(host, 0x1011);
                  break;
                case 1:
                  messageId_4 = LOAD_TEXT_ID(host, 0x2011);
                  break;
                case 2:
                  messageId_4 = LOAD_TEXT_ID(host, 0x3011);
                  break;
                }
                FUN_003ecb00(messages, messageId_4);
                break;
              case 5:
                kindHard_13 = common->_kindHard;
                messageId_5 = -1;
                switch ((unsigned int)kindHard_13) {
                case 0:
                  messageId_5 = LOAD_TEXT_ID(host, 0x1013);
                  break;
                case 1:
                  messageId_5 = LOAD_TEXT_ID(host, 0x2013);
                  break;
                case 2:
                  messageId_5 = LOAD_TEXT_ID(host, 0x3013);
                  break;
                }
                FUN_003ecb00(messages, messageId_5);
                break;
              case 9:
                kindHard_14 = common->_kindHard;
                messageId_6 = -1;
                switch ((unsigned int)kindHard_14) {
                case 0:
                  messageId_6 = LOAD_TEXT_ID(host, 0x1016);
                  break;
                case 1:
                  messageId_6 = LOAD_TEXT_ID(host, 0x2016);
                  break;
                case 2:
                  messageId_6 = LOAD_TEXT_ID(host, 0x3016);
                  break;
                }
                FUN_003ecb00(messages, messageId_6);
                break;
              case 1:
                kindHard_15 = common->_kindHard;
                messageId_7 = -1;
                switch ((unsigned int)kindHard_15) {
                case 0:
                  messageId_7 = LOAD_TEXT_ID(host, 0x1028);
                  break;
                case 1:
                  messageId_7 = LOAD_TEXT_ID(host, 0x2028);
                  break;
                case 2:
                  messageId_7 = LOAD_TEXT_ID(host, 0x3028);
                  break;
                }
                FUN_003ecb00(messages, messageId_7);
                break;
              case 0:
              default:
                kindHard_16 = common->_kindHard;
                messageId_8 = -1;
                switch ((unsigned int)kindHard_16) {
                case 0:
                  messageId_8 = LOAD_TEXT_ID(host, 0x100D);
                  break;
                case 1:
                  messageId_8 = LOAD_TEXT_ID(host, 0x200D);
                  break;
                case 2:
                  messageId_8 = LOAD_TEXT_ID(host, 0x300D);
                  break;
                }
                FUN_003ecb00(messages, messageId_8);
                break;
              }
            } else {
              if (common->_kindHard != 2) {
                beNDMWLoadIntf2SelSlot__RefreshSlotMarks(slots, slots->_mcSelPoint);
              }
              kindHard_17 = common->_kindHard;
              messageId_9 = -1;
              switch ((unsigned int)kindHard_17) {
              case 0:
                messageId_9 = LOAD_TEXT_ID(host, 0x1016);
                break;
              case 1:
                messageId_9 = LOAD_TEXT_ID(host, 0x2016);
                break;
              case 2:
                messageId_9 = LOAD_TEXT_ID(host, 0x3016);
                break;
              }
              FUN_003ecb00(messages, messageId_9);
            }
            resultWork->_sysStat2 = (resultWork->_sysStat2 + 1);
            resultWork->_sysStat3 = 0;
            break;
          case 1:
            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(messages) & 0xFF)) {
              resultWork->_utilReturn = 1;
              PLAYER_ENTER_STAGE(resultWork, 7);
            }
            break;
          }
        }
        }
        break;
      /* Stage 7: put the work records of all four players into stage 8. */
      case 7:
        playerIndex = 0;
        do {
          eachWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
              common->_flagWork, playerIndex));
          playerIndex += 1;
          PLAYER_ENTER_STAGE(eachWork, 8);
        } while (playerIndex < 4);
        break;
      /* Stage 8: clear the message window, reset this player's stages and hand
       * the pad back to the screens (_isCtrl = 1). */
      case 8:
        beNDMWLoadIntf2MesWin__EndSystemMessage(messages);
        resetWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
            common->_flagWork, host->_ramNo));
        PLAYER_ENTER_STAGE(resetWork, 0);
        LoadHelpers::FlagAt(common, host)->_isCtrl = 1;
        break;
      }
    }
  }
done:
  return;
}
