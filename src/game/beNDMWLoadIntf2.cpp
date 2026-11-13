#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define SLOT_ROW(ci, pl) ((beNDMWLoadSavePlWork *)((int *)((beNDMWLoadSavePlWorkList *)(ci)->_flagWork)->_data)[pl])
#define SLOT_ITEMS(ci, pl) ((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)SLOT_ROW(ci, pl)->_haveSaveData)->_saveDataList)->_data)
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define DEGI(common, i) (((beNDMWDegiData **)((beNDMWDegiDataList *)(common)->_gameUseData)->_data)[i])
#define AREAS(common, pl) (((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)PLW(common, pl)->_haveSaveData)->_saveDataList)->_data))
#define SLOT_DEGI(bk, pl, i) \
    ((beNDMWDegiData *)((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork *)((int *)((beNDMWLoadSavePlWorkList *)(bk)->_flagWork)->_data)[pl])->_haveSaveData)->_saveDataList)->_data)[i])
#define BIND(P, I, F) do { int a = igObject_GetAllocator(arg0); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); igSmartPointer<Obj> r(((Obj *)FUN_003614f0(a))); beUnicodeObj_AllocateBuffer(r.p, 1); *(unsigned short *)r.p->_buffer = arg0->t.name[I]; FUN_003ec120(arg0->n._textOrder, P, arg0->n._ramNo, I, r.p, 1, F); } while (0)
#define MC_UTIL(owner) ((beNDMWMcUtilCtrl *)(owner)->_mcUtilCtrl)
#define MC_SLOTS(owner) ((beNDMWMcSlotList *)MC_UTIL(owner)->_slot)
#define MC_SLOT(list, i) (((beNDMWMcSlot **)(list)->_data)[i])
#define MC_SLOTS_3e3070(owner) ((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)(owner)->_mcUtilCtrl)->_slot)
#define TGT ((Target *)self->_comMdlCtrl)
#define WAIT_TRACKED 1
#define RELEASE_STR(s) { int *q = (int *)(s); if (q) { int *h = q - 2; int c = q[-1] - 1; q[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*h, h); } }

extern "C" int beUnicodeObj_AllocateBuffer(...);
extern "C" int sprintf(...);
extern "C" int TextOrder_ConfigureFont(...);
extern "C" int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
extern "C" int FUN_003ec120(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int *beDataBase_GetRecordString(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int strcmp(...);
extern "C" int TextOrder_ClearFont(...);
extern "C" int TextOrder_PublishLineListOnly(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestMessage(...);
extern "C" void *FUN_002eb010(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" void *StringPool_Construct(...);
extern "C" void * StringPool_Intern(...);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_DispatchSelected(int, int *);
extern "C" int beMessenger_SelectReceivers(int, int *, int, int);
extern "C" int beMessenger_AppendString(int, int);
extern "C" int beMessenger_GetBool(int, int);
extern "C" void igObject_Destroy(void *);
extern "C" void FUN_003e9220(void *arg0, void *arg1);
extern "C" void *igProperty_FindByName(...);
extern "C" void *DataList_FindProperty_003e9280(int list, int meta, int *name);
extern "C" int ObjectRef_Get_003e92a0(int *p);
extern "C" int beBaseInfoDataList_Create(int);
struct DW4Sret4 {
  int v;
  DW4Sret4(int value) : v(value) {}
  DW4Sret4(const DW4Sret4 &o) : v(o.v) {}
};
extern "C" DW4Sret4 AllocatorValue_Make_003e9360(int allocator);
extern "C" int Memory_SelectAllocator_003e9370(const int *selector, int fallback);
extern "C" int ObjectRef_Get_003e93b0(int *p);
extern "C" int Gap__Bec__beNDMWLoadIntf2__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWLoadIntf2__vfunc_20(void);
extern "C" int FUN_00100610(...);
extern "C" void beNDMWLoadIntf2DegiState__Init(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern "C" void beNDMWLoadIntf2DegiState__RequestOpen(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2);
extern "C" void FUN_003d9e40(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2);
extern "C" void beNDMWLoadIntf2DegiState__RequestClose(beNDMWLoadIntf2DegiState *arg0, int arg1);
extern "C" void beNDMWLoadIntf2DegiState__RequestConfirmClose(beNDMWLoadIntf2DegiState *arg0);
extern "C" beUnicodeObj * FUN_003614f0(...);
typedef struct SlotEnt { int name; int val; int val2; } SlotEnt;
extern "C" int DAT_00516c40[4];
extern "C" int DATABASE[4];
extern "C" int shinka[4];
extern "C" int GETDATABASE[4];
extern "C" int NAME[4];
extern "C" int DAT_00516c80[4];
extern "C" int DAT_00516c90[4];
extern "C" int DAT_00516c98[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
struct SlotDisplay { char p0[40]; unsigned char used; char p2[7]; int model; char p3[4]; int level; int hp; int maxHp; int mp; int maxMp; };
struct AreaCell { char p[12]; igObjectList *displays; };
struct AreaRow { char p[32]; AreaCell *cell; };
struct SlotBackend { char p[36]; igObjectList *ownDisplays; igObjectList *areas; };
struct SlotPanel { char p0[8]; int messenger; char p1[4]; int textCtrl; SlotBackend *backend; int player; int side; char p2[8]; int source; int index; };
extern "C" void FUN_003d9ec0(SlotPanel *arg0);
extern "C" void FUN_003da5f0(beNDMWLoadIntf2DegiState *arg0);
typedef struct Ent { int name; int val; int val2; } Ent;
extern "C" Ent g_playerModelRow[16];
extern "C" int j_digifacewin[4];
extern "C" int j_mainstatuswin[4];
extern "C" int SQ_OPEN[4];
extern "C" int DAT_00516cd8[4];
extern "C" int DAT_00516ce8[4];
extern "C" int DAT_00516cf8[4];
extern "C" int DAT_00516d08[4];
extern "C" int DAT_00516d10[4];
extern "C" int DAT_00516d20[4];
extern "C" int SQ_CLOSE[4];
extern "C" int SQ_LINEON00[4];
extern "C" int SQ_CANCEL[4];
extern "C" int DAT_00516d60[4];
struct Item { char p0[40]; unsigned char b40; char p1[7]; int f48; };
struct IL { char p[16]; Item **arr; };
struct Cell { char p[12]; IL *f12; };
struct Row { char p[32]; Cell *f32; };
struct RL { char p[16]; Row **arr; };
struct Bk { char p[36]; IL *f36; RL *f40; };
struct Ob { char p[28]; float v28; float v32; float v36; };
struct V3 { float x; float y; float z; };
extern "C" unsigned char beNDMWLoadIntf2DegiState__Update(beNDMWLoadIntf2DegiState *arg0);
extern "C" void beNDMWLoadIntf2DataSelIntf__Init(beNDMWLoadIntf2DataSelIntf *arg0, int arg1, int arg2);
extern "C" void beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
extern "C" int DAT_00516db0[4];
extern "C" int DAT_00516dc8[4];
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__OpenSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
/* Receiver: beNDMWLoadIntf2DataSelIntf; host is its _commonIntf. _flagWork holds the per-player beNDMWLoadSavePlWork records
 * (_isCtrl, _haveSaveData, a beNDMWLoadSlotPlayer whose _saveDataList holds the four save areas); _gameUseData is a
 * beNDMWDegiDataList of the per-player Digimon records. The class behind _statDisp is not reflected. */




typedef struct Node { int f0; char p0[12]; struct Node *n16; } Node;
extern "C" int DAT_00516e48[4];
extern "C" void *DAT_004cc840[4];
extern "C" void *DAT_004cc850[4];
extern "C" void *g_stringPool[4];
extern "C" bePadData * bePadManager_GetPadForPlayer(...);
extern "C" int FUN_003ee190(beNDMWLoadCtrl2CommonIntf *, int);
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__UpdateSelection(beNDMWLoadIntf2DataSelIntf *c, int sel);
typedef struct M { void *f0; void *f4; } M;
typedef struct L { char p[16]; M *n16; } L;
typedef struct K { char p[16]; L *n16; } K;
extern "C" int DAT_00516d70[4];
extern "C" int DAT_00516d80[4];
extern "C" int DAT_00516d90[4];
extern "C" int DAT_00516da0[4];
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__CloseAll(beNDMWLoadIntf2DataSelIntf *c, int sel);
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__ShowSelectedStatus(beNDMWLoadIntf2DataSelIntf *c, int sel);
struct Ob_3dc590 { char p[28]; float x; float y; float z; };
struct Ent_3dc590 { int name; int val; int val2; };
extern "C" int DAT_004cc830[4];
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__RestoreSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
typedef struct Pair { void *a; void *b; } Pair;
typedef struct Inner { char p[16]; Pair *pair; } Inner;
typedef struct Link { char p[16]; Inner *inner; } Link;
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__CloseStatusWindows(beNDMWLoadIntf2DataSelIntf *c, int sel);
struct V3_3dcc60 { float x, y, z; };
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__OpenSlotSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
typedef struct P { char p0[28]; float x, y, z; } P;
extern "C" int DAT_00516e70[4];
extern "C" int DAT_00516e80[4];
extern "C" int DAT_00516e90[4];
extern "C" int DAT_00516ea0[4];
extern "C" bool beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
extern "C" unsigned char beNDMWLoadIntf2DataSelIntf__CloseSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
/* Arena handles are 4-byte ints and are cast to pointers where followed. */


struct Tab { int name; int f4; int *f8; };
extern "C" int beNDMWLoadIntf2DataSelIntf__ShowAccessPlayers(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
extern "C" void beNDMWLoadIntf2Diffselect__Init(beNDMWLoadIntf2Diffselect *arg0, int arg1, int arg2);
/* The pad object is a bePadData: _lTrg/_lRpt are held, _trigger/_repeat are edges. */
typedef struct VecSrc { char p0[28]; float x, y, z; } VecSrc;
extern "C" int SQ_LINEON01[4];
extern "C" int DAT_00516e28[4];
extern "C" int j_linewin02[4];
extern "C" int DAT_00516ec0[4];
extern "C" int SQ_LINEUP00[4];
extern "C" int DAT_00516ee0[4];
extern "C" int SQ_LINEDW01[4];
extern "C" int DAT_00516f00[4];
extern "C" unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, unsigned char usePad);
struct R { int a, b, c; };
struct H { char pad[236]; short a, b, c; };
struct Q { char pad[200]; int a, b, c; };
/* Tail of the NameSel object past the reflected fields (+100): selection table state. */
struct NameSelTail {
    char p0[104];
    struct R rows[8];
    int ints[9];
    short shorts[9];
    char c254, c255, c256, c257, c258, c259;
};
extern "C" void beNDMWLoadIntf2NameSel__Init(beNDMWLoadIntf2NameSel *arg0, unsigned char arg1);
/* The last wrap must be written as if/else on the unwrapped n (if (n >= f44) s0 = f48; else s0 =
 * n;): the if-without-else spelling pads the join label with a nop. */



typedef beUnicodeObj Obj;
typedef struct CharRow { int mod; unsigned short v[32]; } CharRow;
extern "C" CharRow DAT_004cc860[];
extern "C" int DAT_00516f10[4];
extern "C" void FUN_003de480(beNDMWLoadIntf2NameSel *arg0, int arg1);
extern "C" int DAT_00516f20[4];
extern "C" void FUN_003de7a0(beNDMWLoadIntf2NameSel *arg0, int arg1);
/* The reflected beNDMWLoadIntf2NameSel registers 288 bytes; reflection lists its fields up to +100
 * and the per-cell save area is the unlisted tail of the same object (+104..), so NameSelTail is
 * laid over it. */
struct NameSelSave { int tate, yoko, cur; };
struct NameSelTail_3de990 { char _reflected[104]; NameSelSave save[8]; int mode[9]; unsigned short name[9]; };
union NameSelRam { beNDMWLoadIntf2NameSel n; NameSelTail_3de990 t; };
extern "C" int DAT_00516f30[4];
extern "C" int DAT_00516f40[4];
extern "C" void FUN_003de990(NameSelRam *arg0, int arg1);
extern "C" void beNDMWLoadIntf2NameSel__SetAnswer(beNDMWLoadIntf2NameSel *arg0, char arg1);
extern "C" int beNDMWLoadIntf2NameSel__Update(NameSelRam *s, int arg1);
extern "C" void beNDMWLoadIntf2SelSlot__Reset(beNDMWLoadIntf2SelSlot *arg0);
extern "C" void beNDMWLoadIntf2SelSlot__Init(beNDMWLoadIntf2SelSlot *arg0);
typedef struct TE { int *name; int mark; } TE;
extern "C" TE DAT_004cd060[5];
extern "C" TE DAT_004cd090[2];
extern "C" int DAT_00517118[4];
extern "C" int DAT_00517128[4];
extern "C" int DAT_00517138[4];
extern "C" int DAT_00517150[4];
extern "C" int DAT_00517160[4];
extern "C" int DAT_00517170[4];
extern "C" int DAT_00517180[4];
extern "C" int DAT_00517190[4];
extern "C" int DAT_005171a0[4];
extern "C" int DAT_005171b0[4];
extern "C" int DAT_005171c0[4];
extern "C" int DAT_005171d0[4];
extern "C" int DAT_005171e0[4];
typedef struct V3_3e0c40 { float x, y, z; } V3_3e0c40;
typedef struct Own { char p[28]; V3_3e0c40 pos; } Own;
extern "C" unsigned char beNDMWLoadIntf2SelSlot__Open(beNDMWLoadIntf2SelSlot *self, int mark);
extern "C" int DAT_005171f0[4];
struct OptEnt {
    int *w0; /* the label string passed to Play */
    int idx;
};
extern "C" unsigned char beNDMWLoadIntf2SelSlot__UpdateSelection(beNDMWLoadIntf2SelSlot *self, unsigned char usePad, unsigned char checkDone);
struct Entry { int w0; int w4; };
extern "C" void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *arg0);
extern "C" unsigned char beNDMWLoadIntf2SelSlot__Close(beNDMWLoadIntf2SelSlot *self);
typedef struct SlotEntry { int a; int idx; } SlotEntry;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Target { char p[28]; float x, y, z; } Target;
extern "C" void beNDMWLoadIntf2SelSlot__RefreshSlotMarks(beNDMWLoadIntf2SelSlot *self, int arg1);
extern "C" beLoadIntf2ComMdlData * beLoadIntf2ComMdlData__Create(...);
extern "C" int MODELCTRL[4];
extern "C" int GENERATE[4];
extern "C" int g_defaultAllocatorSelector[4];
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Start(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, int recordOpen);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, float *position, int recordOpen);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int *modelName, int *sequenceName, int wait);
extern "C" int ISSEQNAME[4];
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, const char *infoName, const char *sqName);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose);
extern "C" int ISRUN[4];
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const char *name);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self);
extern "C" int List_RemoveWordAt(beLoadIntf2ComMdlDataList *, int);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Poll(beNDMWLoadIntf2ComMdlCtrl *self);
extern "C" igObject *FUN_00236f80(int, int);
extern "C" int g_bePadManager_metaObject[4];
extern "C" void Gap__Bec__beNDMWLoadIntf2__vfunc_32(beNDMWLoadIntf2 *arg0);
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" int DataList_GetData_003e9090(igDataList *list);
extern "C" void beNDMWLoadSavePlWork__SetIsCtrl(beNDMWLoadSavePlWork *a0, int a1);
extern "C" unsigned char beNDMWLoadSavePlWork__GetIsRdy(beNDMWLoadSavePlWork *p);
extern "C" unsigned char beNDMWLoadSavePlWork__GetIsEntry(beNDMWLoadSavePlWork *p);
extern "C" void ObjectRef_Retain_003e90d0(ObjectRefTarget *object);
extern "C" int DataList_GetWordAt_003e90f0(igDataList *list, int index);
extern "C" void ObjectList_SetAtRetained_003e9160(igDataList *list, int index, ObjectRefTarget *replacement);
extern "C" int DataList_GetWordAt_003e9240(igDataList *list, int index);
extern "C" int ObjectList_GetAt_003e9260(igDataList *list, int index);
extern "C" ObjectRefTarget **ObjectRef_Assign_003e92b0(ObjectRefTarget **destination,ObjectRefTarget **source);
extern "C" int g_beNDMWLoadIntf2Info_metaObject[4];
extern "C" int g_beNDMWLoadIntf2_metaObject[4];
extern "C" int beMessenger_RegisterReceiver(int, beBaseInfoRam *, int *, int, int);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, beBaseInfoRam *, int *);
extern "C" int DAT_005175d8[4];
extern "C" int DAT_005175e8[4];
extern "C" void Gap__Bec__beNDMWLoadIntf2__vfunc_29(beNDMWLoadIntf2 *arg0, beBaseInfoRam *arg1);

void beNDMWLoadIntf2DegiState__Init(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    arg0->_comMdlCtrl = arg4;
    arg0->_commonIntf = arg2;
    arg0->_textOrder = arg3;
    arg0->_plNo = arg1;
    arg0->_messenger = arg5;
    arg0->_dispPos = arg6;
    arg0->_isEnd = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

/* Per-frame master update of the Game Start interface for one player (`host`): looks up the named
 * working set under host->_dataList (COMMONINTF, CTRL, MAKECHR, ...), samples that player's pad,
 * and advances the CtrlData screen state machine (join, new or load, Digimon choice, name, slot,
 * save data, start) plus the per-player card-utility stages. The local declaration groups preserve
 * the original allocation, and explicit snapshots keep the observed ordering of controller reads.
 * LoadVec3 is three floats; reference parameter homes remain 16 bytes apart. */
static inline int sysStat2(const beNDMWLoadSavePlWork *self) { return self->_sysStat2; }
struct LoadVec3 {
  float x, y, z;
};
extern "C" int FUN_001ae1a0(void *, float, float, float);
extern "C" int igDataList_GetCount(void *);
extern "C" int beLua__RunNamedChunk(...);
extern "C" void *beNDMWDegiData_Create(...);
extern "C" int beNDMWLoadIntf2MesWin__Update(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestOpen(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestClose(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestQuestion(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestPrompt(...);
extern "C" int beNDMWLoadIntf2MesWin__Cancel(...);
extern "C" int beNDMWLoadIntf2MesWin__GetIsCtrl(...);
extern "C" int beNDMWLoadIntf2MesWin__GetCurPoint(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestMesErase(...);
extern "C" int beNDMWLoadIntf2MesWin__RequestSystemMessage(...);
extern "C" int beNDMWLoadIntf2MesWin__EndSystemMessage(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepReadMedia(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__StartUtilFor(...);
extern "C" int beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(...);
extern "C" int beNDMWDegiData__LoadFromProperties(...);
extern "C" int beNDMWDegiData__StoreToProperties(...);
extern "C" int List_Resize(...);
extern "C" int ObjectRef_Destruct_0033e9c0(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" void *igProperty_GetRecord(...);
extern "C" void *igProperty_GetRecordByte(...);
extern "C" int text_0rQ[4];
extern "C" int g_starterPlayerModelName_004cd0e0[4];
extern "C" int g_playerModelRowOpenSeq[4];
extern "C" int g_playerModelRowSeq[4];
extern "C" int DATABASE[4];
extern "C" int shinka[4];
extern "C" int GETDATABASE[4];
extern "C" int NAME[4];
extern "C" int j_digifacewin[4];
extern "C" int j_mainstatuswin[4];
extern "C" int SQ_OPEN[4];
extern "C" int SQ_CLOSE[4];
extern "C" int SQ_LINEON00[4];
extern "C" int SQ_CANCEL[4];
extern "C" char SQ_LINESL00[];
extern "C" int SQ_LINEON01[4];
extern "C" int j_linewin02[4];
extern "C" int SQ_LINEUP00[4];
extern "C" int SQ_LINEDW01[4];
extern "C" char SQ_ON00[];
extern "C" int COMMONINTF[4];
extern "C" int CTRL[4];
extern "C" int MAKECHR[4];
extern "C" int COMMDLCTRL[4];
extern "C" int MESWIN[4];
extern "C" int SELSLOT[4];
extern "C" int NAMESEL[4];
extern "C" int TEXTORDER[4];
extern "C" int DEGISTATECTRL[4];
extern "C" int DATASELINTF[4];
extern "C" int DIFFSELECT[4];
extern "C" int j_chrselbase[4];
extern "C" int GAMERAM_2[4];
extern "C" int GETPLAYER[4];
extern "C" int ISUSE_2[4];
extern "C" int j_chrselmesswin[4];
extern "C" int j_linewin01[4];
extern "C" int j_digiselcursorleft[4];
extern "C" int j_digiselcursorright[4];
extern "C" int j_namewin02[4];
extern "C" int CHRSELFONT14[4];
extern "C" int MOVETRANS[4];
extern "C" int SQ_ENTR[4];
extern "C" int SQ_EXIT[4];
extern "C" int SQ_LINECG00[4];
extern "C" int GAMEDATAINIT[4];
extern "C" int GAMESTART[4];
extern "C" int UNIQUE[4];
extern "C" int BASE2CURRENT[4];
extern "C" int RECALCPLAYER[4];
extern "C" int hostLoad_lua[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" int g_beFont_metaObject[4];
extern "C" int g_mdlEntity[4];
/* The 4-byte value returned by AllocatorValue_Make_003e9360 is copied into a temporary reference before it is
 * handed to ObjectRef_Assign_003e92b0; these two classes reproduce that copy/destroy pair. */
class RecoveryCopiedRef {
public:
  void *value;
  RecoveryCopiedRef(const DW4Sret4 &source) : value((void *)beBaseInfoDataList_Create(source.v)) {}
  ~RecoveryCopiedRef();
};
/* Creates the fresh object for an empty reference (the ObjectRef_Get_003e93b0 == 0
 * test on host->_dataList at the top of the update) and stores it there. */
struct DW4Fresh {
  static ObjectRefTarget **Assign(void *obj, int alloc) {
    RecoveryCopiedRef c(AllocatorValue_Make_003e9360(Memory_SelectAllocator_003e9370(
        &g_defaultAllocatorSelector[0], alloc)));
    return ObjectRef_Assign_003e92b0((ObjectRefTarget **)obj, (ObjectRefTarget **)&c);
  }
};
/* Scoped holder for a ref-counted object: optionally retains on construction and releases on scope
 * exit. The template index only keeps the instances apart so each scope gets its own destructor. */
template <int I> class RecoveryRef {
public:
  void *value;
  RecoveryRef(void *p) : value(p) {}
  RecoveryRef(void *p, bool retain) : value(p) {
    if (retain)
      ObjectRef_Retain_003e90d0((ObjectRefTarget *)value);
  }
  ~RecoveryRef() { igRelease((igObject *)value); }
};
/* Header of the growable int list behind SlotPlayer::_accessPlList: the
 * count (+8) and the capacity (+12), which decides whether List_Resize is
 * needed before a player number is appended. */
struct DW4ListRec {
  int w0, w1;
  int count;
  int cap;
  int getCount() const { return count; }
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
/* Step bookkeeping for the CtrlData record: _st0 is the screen state, _st1 the step inside it,
 * _st2 and _st3 finer sub-steps. Moving to a new level always clears the levels below it, in the
 * order _st3, _st2, _st1. */
static inline void EnterState(beNDMWLoadIntf2CtrlData *c, int n) { c->_st0 = n; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
static inline void NextStep(beNDMWLoadIntf2CtrlData *c) { c->_st1 = c->_st1 + 1; c->_st3 = 0; c->_st2 = 0; }
static inline void SetStep(beNDMWLoadIntf2CtrlData *c, int n) { c->_st1 = n; c->_st3 = 0; c->_st2 = 0; }
static inline void NextSubstep(beNDMWLoadIntf2CtrlData *c) { c->_st2 = c->_st2 + 1; c->_st3 = 0; }
static inline void RestartSubstep(beNDMWLoadIntf2CtrlData *c) { c->_st2 = 0; c->_st3 = 0; }
/* The same bookkeeping on the per-player beNDMWLoadSavePlWork (_sysStat0.._sysStat3). */
static inline void SetPlayerStep(beNDMWLoadSavePlWork *w, int n) { w->_sysStat1 = n; w->_sysStat3 = 0; w->_sysStat2 = 0; }
static inline void EnterPlayerStage(beNDMWLoadSavePlWork *w, int n) { w->_sysStat0 = n; w->_sysStat3 = 0; w->_sysStat2 = 0; w->_sysStat1 = 0; }
/* Message/text-order ids: the player number (_ramNo) in the high half and the message token in the
 * low bits (a control id is (high << 16) | token). */
static inline int TextId(beBaseInfoRam *h, int token) { return (h->_ramNo << 0x10) | token; }
/* Starts the first entry of the Digimon status list on a kind and the player's data number. */
static inline void OpenDegiState(beNDMWLoadIntf2DegiStateCtrl *status, int kind, int player) {
  beNDMWLoadIntf2DegiState *degiState = (beNDMWLoadIntf2DegiState *)ObjectList_GetAt_003e9260((igDataList *)status->_statDataList, 0);
  beNDMWLoadIntf2DegiState__RequestOpen((beNDMWLoadIntf2DegiState *)degiState, kind, player);
}
/* The save data the player picked: entry saveIndex of the save-data list of the slot player held by
 * the player's work record. */
static inline void *PlayerSaveData(beNDMWLoadCtrl2CommonIntf *common, int player, int saveIndex) {
  beNDMWLoadSavePlWork *work =
      (beNDMWLoadSavePlWork *)DataList_GetWordAt_003e9240((igDataList *)common->_flagWork, player);
  return (void *)DataList_GetWordAt_003e90f0((igDataList *)(((beNDMWLoadSlotPlayer *)work->_haveSaveData)->_saveDataList), saveIndex);
}
/* Accessors the retail code inlined at each use. */
struct LoadHelpers {
  static beNDMWLoadSavePlWork *FlagAt(beNDMWLoadCtrl2CommonIntf *owner,
                                      beBaseInfoRam *host) {
    int player = host->_ramNo;
    return (beNDMWLoadSavePlWork *)ObjectList_GetAt_003e9260((igDataList *)owner->_flagWork,
                                                             player);
  }
  static beNDMWMcUtilCtrl *McUtil(beNDMWLoadCtrl2CommonIntf *owner) {
    return (beNDMWMcUtilCtrl *)owner->_mcUtilCtrl;
  }
  static bePadData *GetPad(beNDMWLoadIntf2 *owner, beBaseInfoRam *host) {
    igObject *manager =
        FUN_00236f80(owner->_insight, g_bePadManager_metaObject[0]);
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
/* Offsets of members the reflection dump does not list: the typed-name text buffer inside NameSel,
 * and the byte flag inside an igProperty record. */
#define NAMESEL_TEXT_OFFSET 236
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
  void *savedData;

  int loadedPlayer;
  igObject *font;

  int kindName;

  beNDMWLoadSavePlWork *resultWork;
  unsigned int utilResult_2;

  int shinkaDb;
  int accessCount;
  int shinkaDb_2;
  int shinkaDb_3;
  int accessPlayer;

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
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    common = (beNDMWLoadCtrl2CommonIntf *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &COMMONINTF[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    control = (beNDMWLoadIntf2CtrlData *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0], &CTRL[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    creation = (beNDMWLoadIntf2MakeChr *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &MAKECHR[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    models = (beNDMWLoadIntf2ComMdlCtrl *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &COMMDLCTRL[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    messages = (beNDMWLoadIntf2MesWin *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &MESWIN[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    slots = (beNDMWLoadIntf2SelSlot *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &SELSLOT[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    nameEntry = (beNDMWLoadIntf2NameSel *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &NAMESEL[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    textOrder = (beNDMWLoadIntf2TextOrder *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &TEXTORDER[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    status = (beNDMWLoadIntf2DegiStateCtrl *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &DEGISTATECTRL[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    dataSelection = (beNDMWLoadIntf2DataSelIntf *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &DATASELINTF[0]));
    dataListRef = ObjectRef_Get_003e93b0(&host->_dataList);
    if (dataListRef == 0) {
      DW4Fresh::Assign(&host->_dataList, igObject_GetAllocator(host));
    }
    difficulty = (beNDMWLoadIntf2Diffselect *)(DataList_FindProperty_003e9280(
        ObjectRef_Get_003e92a0(&host->_dataList), g_propertyNameField[0],
        &DIFFSELECT[0]));
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
                (igDataList *)common->_flagWork, host->_ramNo));
            EnterPlayerStage(hostWork, 0);
          } else {
            beNDMWLoadIntf2MesWin__RequestSystemMessage(messages, TextId(host, 0x51C));
            hostWork_2 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                (igDataList *)common->_flagWork, host->_ramNo));
            SetPlayerStep(hostWork_2, 1);
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
              LoadVec3 chrSelBasePos;
              FUN_003e9220(&chrSelBasePos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)&j_chrselbase[0],
                           (const char *)&SQ_OPEN[0], (float *)&chrSelBasePos, 1);
              NextStep(control);
              break;
            case 1:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                NextStep(control);
              }
              break;
            case 2:
              beMessenger_SelectGroup(self->_messenger, &GAMERAM_2[0]);
              beMessenger_AppendInt(self->_messenger, host->_ramNo);
              beMessenger_DispatchSelected(self->_messenger,
                                           &GETPLAYER[0]);
              gamePlayer = beMessenger_GetObject(self->_messenger, 0);
              /* ISUSE: the GAMERAM record already holds a character. */
              if (*(unsigned char *)((char *)(igProperty_GetRecordByte(
                                         gamePlayer, &ISUSE_2[0])) +
                                     PROPERTY_RECORD_BYTE_OFFSET) == 1) {
                beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260((igDataList *)common->_gameUseData,
                                                       host->_ramNo),
                             gamePlayer);
                NextStep(control);
              } else {
                if (host->_ramNo == 0) {
                  EnterState(control, 3);
                } else if (LoadHelpers::GetPad(self, host)->_isConnect != 0) {
                  EnterState(control, 2);
                } else {
                  EnterState(control, 1);
                }
                control->_isRdyCancel = 1U;
              }
              break;
            case 3:
              LoadVec3 chrSelMessWinPos;
              FUN_003e9220(&chrSelMessWinPos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)&j_chrselmesswin[0],
                           (const char *)&SQ_OPEN[0], (float *)&chrSelMessWinPos, 1);
              beNDMWLoadIntf2MesWin__RequestOpen(messages);
              LoadHelpers::FlagAt(common, host)->_isEntry = 1;
              NextStep(control);
              break;
            case 4:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                control->_isRdyCancel = 0U;
                EnterState(control, 8);
              }
              break;
            }
            break;
          /* Screen 1: wait until this player's pad is connected, then join
           * (screen 2). */
          case 1:
            if ((LoadHelpers::FlagAt(common, host)->_isCtrl == 1) &&
                (LoadHelpers::GetPad(self, host)->_isConnect != 0)) {
              EnterState(control, 2);
            }
            break;
          /* Screen 2: join window (linewin01, text 0x400) for players 2-4.
           * Cross enters (SQ_LINEON00) and continues at screen 3; a missing pad
           * closes it (SQ_CLOSE) and returns to screen 1. */
          case 2:
            st1Now_3 = control->_st1;
            switch ((unsigned int)st1Now_3) {
            case 0:
              LoadVec3 lineWin01Pos;
              FUN_003e9220(&lineWin01Pos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)&j_linewin01[0],
                           (const char *)&SQ_OPEN[0], (float *)&lineWin01Pos, 1);
              NextStep(control);
              break;
            case 1:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, TextId(host, 0x400), 0);
                NextStep(control);
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
                  beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_linewin01[0],
                               (const char *)&SQ_LINEON00[0], 1);
                } else {
                  beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_linewin01[0],
                               (const char *)&SQ_CLOSE[0], 1);
                }
                TextOrder_PublishLineListOnly(textOrder, TextId(host, 0x400));
                NextStep(control);
              }
              break;
            case 3:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                if (control->_isEntry == 1) {
                  EnterState(control, 3);
                } else {
                  EnterState(control, 1);
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
                LoadVec3 chrSelMessWinPos;
                FUN_003e9220(&chrSelMessWinPos, &models->_pos);
                beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo,
                             (const char *)&j_chrselmesswin[0],
                             (const char *)&SQ_OPEN[0], (float *)&chrSelMessWinPos, 1);
                beNDMWLoadIntf2MesWin__RequestOpen(messages);
                control->_isMesWin = 1U;
              }
              LoadHelpers::FlagAt(common, host)->_isEntry = 1;
              LoadVec3 lineWin02Pos;
              FUN_003e9220(&lineWin02Pos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)&j_linewin02[0],
                           (const char *)&SQ_OPEN[0], (float *)&lineWin02Pos, 1);
              control->_newLoadSel = 0;
              NextStep(control);
              break;
            case 1:
              if ((control->_st2 == 0) &&
                  !(beNDMWLoadIntf2ComMdlCtrl__IsSequence((beNDMWSaveIntfComMdlCtrl *)models, host->_ramNo,
                                 (const char *)&j_linewin02[0],
                                 (const char *)&SQ_OPEN[0]) &
                    0xFF)) {
                beNDMWLoadIntf2TextOrder_PublishIdLines(textOrder, TextId(host, 0x401), 0);
                NextSubstep(control);
                ramNo_2 = host->_ramNo;
                if (ramNo_2 == 0) {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, (ramNo_2 << 0x10) | 0x523);
                } else {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, (ramNo_2 << 0x10) | 0x524);
                }
              }
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                NextStep(control);
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
                                 &j_linewin02[0],
                                 &SQ_LINEUP00[0], 1);
                  }
                  control->_newLoadSel = nextSel;
                  NextSubstep(control);
                } else if (moveDown) {
                  nextSel_2 = control->_newLoadSel + 1;
                  if (1 < nextSel_2) {
                    nextSel_2 = 1;
                  } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &j_linewin02[0],
                                 &SQ_LINEDW01[0], 1);
                  }
                  control->_newLoadSel = nextSel_2;
                  NextSubstep(control);
                } else if (padTrigger & kPadCross) {
                  if (control->_newLoadSel == 0) {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &j_linewin02[0],
                                 &SQ_LINEON00[0], 1);
                  } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                                 &j_linewin02[0],
                                 &SQ_LINEON01[0], 1);
                  }
                  NextStep(control);
                } else if (padTrigger & kPadCircle) {
                  ramNo = host->_ramNo;
                  if (ramNo != 0) {
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, ramNo, (const char *)&j_linewin02[0],
                                 (const char *)&SQ_CANCEL[0], 1);
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
                                 (const char *)&j_chrselmesswin[0],
                                 (const char *)&SQ_CLOSE[0], 1);
                    TextOrder_PublishLineListOnly(textOrder, TextId(host, 0x401));
                    beNDMWLoadIntf2MesWin__RequestClose(messages);
                    control->_st1 = (control->_st1 + 2);
                    control->_st3 = 0;
                    control->_st2 = 0;
                  }
                }
                break;
              case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                  RestartSubstep(control);
                }
                break;
              }
              break;
            case 3:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                TextOrder_PublishLineListOnly(textOrder, TextId(host, 0x401));
                if (control->_newLoadSel == 0) {
                  EnterState(control, 4);
                } else {
                  EnterState(control, 6);
                }
              }
              break;
            case 4:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                LoadHelpers::FlagAt(common, host)->_isEntry = 0;
                control->_isEntry = 0U;
                EnterState(control, 2);
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
              LoadVec3 cursorLeftPos;
              FUN_003e9220(&cursorLeftPos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo,
                           (const char *)&j_digiselcursorleft[0],
                           (const char *)&SQ_OPEN[0], (float *)&cursorLeftPos, 1);
              LoadVec3 cursorRightPos;
              FUN_003e9220(&cursorRightPos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo,
                           (const char *)&j_digiselcursorright[0],
                           (const char *)&SQ_OPEN[0], (float *)&cursorRightPos, 1);
              LoadVec3 nameWin02Pos;
              FUN_003e9220(&nameWin02Pos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(models, host->_ramNo, (const char *)&j_namewin02[0],
                           (const char *)&SQ_OPEN[0], (float *)&nameWin02Pos, 1);
              creation->_chaSelDegi = 3;
              beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x511));
              beMessenger_SendNamed(self->_messenger, &DATABASE[0],
                                    &shinka[0], 0,
                                    &GETDATABASE[0]);
              shinkaDb = beMessenger_GetObject(self->_messenger, 0);
              rowIndex = 0;
              rowCursor = (int *)(&g_playerModelRow[0]);
            findRow:
              if (strcmp(*rowCursor, g_starterPlayerModelName_004cd0e0
                                           [creation->_chaSelDegi]) == 0) {
                shinkaRow = rowIndex;
              } else {
                rowIndex += 1;
                rowCursor += 3;
                if (rowIndex < 0x10) {
                  goto findRow;
                }
              }
              TextOrder_ConfigureFont(textOrder, &CHRSELFONT14[0], host->_ramNo,
                           0,
                           beDataBase_GetRecordString(shinkaDb, shinkaRow,
                                                      &NAME[0]),
                           1, 0);
              LoadVec3 faceWinPos;
              FUN_003e9220(&faceWinPos, &models->_pos);
              beNDMWLoadIntf2ComMdlCtrl__StartAt(
                  models, host->_ramNo, (const char *)&j_digifacewin[0],
                  (const char *)((void *)
                      g_playerModelRowOpenSeq[creation->_chaSelDegi *
                                                       3]),
                  (float *)&faceWinPos, 1);
              beMessenger_SendNamed(
                  self->_messenger, &MODELCTRL[0],
                  text_0rQ[creation->_chaSelDegi],
                  host->_ramNo, &GENERATE[0]);
              beMessenger_SendNamed(
                  self->_messenger, &MODELCTRL[0],
                  text_0rQ[creation->_chaSelDegi],
                  host->_ramNo, &ISRUN[0]);
              modelIsRun = LoadHelpers::GetBool(self);
              if ((modelIsRun & 0xFF) == 1) {
                FUN_001ae1a0(moveTransA, 0.0f, 0.0f, 0.0f);
                FUN_001ae1a0(moveTransB, 0.0f, 0.0f, 0.0f);
                beMessenger_SelectReceivers(
                    self->_messenger, &MODELCTRL[0],
                    text_0rQ[creation->_chaSelDegi],
                    host->_ramNo);
                LoadVec3 moveTransArgA;
                FUN_003e9220(&moveTransArgA, moveTransA);
                beMessenger_AppendVec3(self->_messenger, (float *)&moveTransArgA);
                LoadVec3 moveTransArgB;
                FUN_003e9220(&moveTransArgB, moveTransB);
                beMessenger_AppendVec3(self->_messenger, (float *)&moveTransArgB);
                beMessenger_DispatchSelected(self->_messenger,
                                             &MOVETRANS[0]);
                beMessenger_SendNamed(
                    self->_messenger, &MODELCTRL[0],
                    text_0rQ[creation->_chaSelDegi],
                    host->_ramNo, &SQ_ENTR[0]);
                control->_isNoSelMdl = 0U;
              } else {
                control->_isNoSelMdl = 1U;
              }
              NextStep(control);
              control->_isCansel = 0U;
              break;
            case 1:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                beMessenger_SendNamed(self->_messenger,
                                      &MODELCTRL[0],
                                      &j_namewin02[0], host->_ramNo,
                                      &SQ_LINESL00[0]);
                NextStep(control);
              }
              break;
            case 2:
              st2Now_4 = control->_st2;
              switch ((unsigned int)st2Now_4) {
              case 0:
                if (moveRight) {
                  if (control->_isNoSelMdl == 0) {
                    beMessenger_SendNamed(
                        self->_messenger, &MODELCTRL[0],
                        text_0rQ[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &ISRUN[0]);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) ==
                        1) {
                      beMessenger_SendNamed(
                          self->_messenger, &MODELCTRL[0],
                          text_0rQ[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo, &SQ_EXIT[0]);
                    }
                  }
                  nextDegi = creation->_chaSelDegi + 1;
                  if (nextDegi >= 4) {
                    nextDegi = 0;
                  }
                  creation->_chaSelDegi = nextDegi;
                  beMessenger_SendNamed(
                      self->_messenger, &DATABASE[0],
                      &shinka[0], 0, &GETDATABASE[0]);
                  shinkaDb_2 = beMessenger_GetObject(self->_messenger, 0);
                  rowIndex_2 = 0;
                  rowCursor_2 = (int *)(&g_playerModelRow[0]);
                findRow_2:
                  if (strcmp(*rowCursor_2,
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
                      textOrder, &CHRSELFONT14[0], host->_ramNo, 0,
                      beDataBase_GetRecordString(shinkaDb_2, shinkaRow_2,
                                                 &NAME[0]),
                      1, 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                               &j_digiselcursorright[0],
                               (int *)SQ_ON00, 1);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, &j_namewin02[0],
                               &SQ_LINECG00[0], 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(
                      models, host->_ramNo, &j_digifacewin[0],
                      (int *)(g_playerModelRowSeq[creation->_chaSelDegi * 3]),
                      0);
                  NextSubstep(control);
                } else if (moveLeft) {
                  if (control->_isNoSelMdl == 0) {
                    beMessenger_SendNamed(
                        self->_messenger, &MODELCTRL[0],
                        text_0rQ[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &ISRUN[0]);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) ==
                        1) {
                      beMessenger_SendNamed(
                          self->_messenger, &MODELCTRL[0],
                          text_0rQ[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo, &SQ_EXIT[0]);
                    }
                  }
                  prevDegi = creation->_chaSelDegi - 1;
                  if (prevDegi < 0) {
                    prevDegi = 3;
                  }
                  creation->_chaSelDegi = prevDegi;
                  beMessenger_SendNamed(
                      self->_messenger, &DATABASE[0],
                      &shinka[0], 0, &GETDATABASE[0]);
                  shinkaDb_3 = beMessenger_GetObject(self->_messenger, 0);
                  rowIndex_3 = 0;
                  rowCursor_3 = (int *)(&g_playerModelRow[0]);
                findRow_3:
                  if (strcmp(*rowCursor_3,
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
                      textOrder, &CHRSELFONT14[0], host->_ramNo, 0,
                      beDataBase_GetRecordString(shinkaDb_3, shinkaRow_3,
                                                 &NAME[0]),
                      1, 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo,
                               &j_digiselcursorleft[0],
                               (int *)SQ_ON00, 1);
                  beNDMWLoadIntf2ComMdlCtrl__Play(models, host->_ramNo, &j_namewin02[0],
                               &SQ_LINECG00[0], 0);
                  beNDMWLoadIntf2ComMdlCtrl__Play(
                      models, host->_ramNo, &j_digifacewin[0],
                      (int *)(g_playerModelRowSeq[creation->_chaSelDegi * 3]),
                      0);
                  NextSubstep(control);
                } else {
                  modelReady = 0;
                  beMessenger_SendNamed(
                      self->_messenger, &MODELCTRL[0],
                      text_0rQ[creation->_chaSelDegi],
                      host->_ramNo, &ISRUN[0]);
                  if (beMessenger_GetBoolCount(self->_messenger) > 0) {
                    modelReady =
                        beMessenger_GetBool(self->_messenger, 0) & 0xFF;
                  } else if (control->_isNoSelMdl == 1) {
                    modelReady = 1 & 0xFF;
                  }
                  if ((modelReady & 0xFF) == 1) {
                    if (padTrigger & kPadCross) {
                      NextStep(control);
                    } else if (padTrigger & kPadCircle) {
                      control->_isCansel = 1U;
                      NextStep(control);
                    }
                  } else {
                    beMessenger_SendNamed(
                        self->_messenger, &MODELCTRL[0],
                        text_0rQ[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &GENERATE[0]);
                    beMessenger_SendNamed(
                        self->_messenger, &MODELCTRL[0],
                        text_0rQ[creation
                                                               ->_chaSelDegi],
                        host->_ramNo, &ISRUN[0]);
                    modelIsRun_2 = LoadHelpers::GetBool(self);
                    if ((modelIsRun_2 & 0xFF) == 1) {
                      FUN_001ae1a0(moveTransC, 0, 0, 0);
                      FUN_001ae1a0(moveTransD, 0, 0, 0);
                      beMessenger_SelectReceivers(
                          self->_messenger, &MODELCTRL[0],
                          text_0rQ[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo);
                      LoadVec3 moveTransArgC;
                      FUN_003e9220(&moveTransArgC, moveTransC);
                      beMessenger_AppendVec3(self->_messenger, (float *)&moveTransArgC);
                      LoadVec3 moveTransArgD;
                      FUN_003e9220(&moveTransArgD, moveTransD);
                      beMessenger_AppendVec3(self->_messenger, (float *)&moveTransArgD);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &MOVETRANS[0]);
                      beMessenger_SendNamed(
                          self->_messenger, &MODELCTRL[0],
                          text_0rQ[creation
                                                                 ->_chaSelDegi],
                          host->_ramNo, &SQ_ENTR[0]);
                      control->_isNoSelMdl = 0U;
                    } else {
                      control->_isNoSelMdl = 1U;
                    }
                  }
                }
                break;
              case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                  RestartSubstep(control);
                }
                break;
              }
              break;
            case 3:
              if (control->_isCansel != 0) {
                beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_namewin02[0],
                             (const char *)&SQ_CANCEL[0], 1);
              } else {
                beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_namewin02[0],
                             (const char *)&SQ_LINEON00[0], 1);
              }
              if (control->_isNoSelMdl == 0) {
                beNDMWLoadIntf2ComMdlCtrl__Close(
                    models, host->_ramNo,
                    (const char *)(text_0rQ[creation->_chaSelDegi]),
                    (const char *)&SQ_EXIT[0], 1);
              }
              TextOrder_ClearFont(textOrder, &CHRSELFONT14[0], host->_ramNo,
                           0);
              NextStep(control);
              break;
            case 4:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                NextStep(control);
              }
              break;
            case 5:
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_digifacewin[0],
                           (const char *)&SQ_CLOSE[0], 1);
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
                           (const char *)&j_digiselcursorleft[0],
                           (const char *)&SQ_CLOSE[0], 1);
              beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo,
                           (const char *)&j_digiselcursorright[0],
                           (const char *)&SQ_CLOSE[0], 1);
              NextStep(control);
              break;
            case 6:
              if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                if (control->_isCansel == 1) {
                  EnterState(control, 3);
                } else {
                  EnterState(control, 5);
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
              NextStep(control);
              beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x517));
              break;
            case 1:
              if (beNDMWLoadIntf2NameSel__Update((NameSelRam *)nameEntry,
                               LoadHelpers::FlagAt(common, host)->_isCtrl) !=
                  0) {
                if (nameEntry->_isMakeName == 1) {
                  control->_isNewMake = 1U;
                  EnterState(control, 8);
                } else {
                  EnterState(control, 4);
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
              if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(messages) & 0xFF)) {
                NextStep(control);
              }
              break;
            case 4:
              beNDMWLoadIntf2MesWin__RequestQuestion(messages, TextId(host, 0x51B), 0);
              NextStep(control);
              break;
            case 5:
              if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(messages) & 0xFF)) {
                messageChoice = beNDMWLoadIntf2MesWin__GetCurPoint(messages);
                switch ((unsigned int)messageChoice) {
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
                  messageId_10 = TextId(host, 0x1009);
                  break;
                case 1:
                  messageId_10 = TextId(host, 0x2009);
                  break;
                case 2:
                  messageId_10 = TextId(host, 0x3009);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestMessage(messages, messageId_10);
                NextSubstep(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2SelSlot__Open(slots, -1) & 0xFF) == 1) {
                  slots->_st0 = 1;
                  slots->_st3 = 0;
                  slots->_st2 = 0;
                  slots->_st1 = 0;
                  NextStep(control);
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
                    NextStep(control);
                  } else if (slots->_isCansel == 1) {
                    NextStep(control);
                  } else {
                    NextSubstep(control);
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
                    messageId_11 = TextId(host, 0x1004);
                    break;
                  case 1:
                    messageId_11 = TextId(host, 0x2004);
                    break;
                  case 2:
                    messageId_11 = TextId(host, 0x3004);
                    break;
                  }
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, messageId_11);
                  beNDMWLoadCtrl2CommonIntf__StartUtilFor(common, host->_ramNo, 5);
                  control->_st3 = (control->_st3 + 1);
                  break;
                case 1:
                  utilReturn = LoadHelpers::FlagAt(common, host)->_utilReturn;
                  switch ((unsigned int)utilReturn) {
                  case 0:
                    NextStep(control);
                    break;
                  case 1:
                  case 2:
                    kindHard_2 = common->_kindHard;
                    messageId_12 = -1;
                    switch ((unsigned int)kindHard_2) {
                    case 0:
                      messageId_12 = TextId(host, 0x1009);
                      break;
                    case 1:
                      messageId_12 = TextId(host, 0x2009);
                      break;
                    case 2:
                      messageId_12 = TextId(host, 0x3009);
                      break;
                    }
                    beNDMWLoadIntf2MesWin__RequestMessage(messages, messageId_12);
                    beNDMWLoadIntf2SelSlot__PublishCursor(slots);
                    SetStep(control, 1);
                    break;
                  case 4:
                    kindHard_3 = common->_kindHard;
                    messageId_13 = -1;
                    switch ((unsigned int)kindHard_3) {
                    case 0:
                      messageId_13 = TextId(host, 0x1009);
                      break;
                    case 1:
                      messageId_13 = TextId(host, 0x2009);
                      break;
                    case 2:
                      messageId_13 = TextId(host, 0x3009);
                      break;
                    }
                    beNDMWLoadIntf2MesWin__RequestMessage(messages, messageId_13);
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
              st2Now_5 = control->_st2;
              switch ((unsigned int)st2Now_5) {
              case 0:
                slots->_st0 = 2;
                slots->_st3 = 0;
                slots->_st2 = 0;
                slots->_st1 = 0;
                NextSubstep(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2SelSlot__Close(slots) & 0xFF) == 1) {
                  if (slots->_isReOpenReq == 1) {
                    EnterState(control, 6);
                  } else if (slots->_isCansel == 1) {
                    EnterState(control, 3);
                  } else {
                    EnterState(control, 7);
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
              beNDMWLoadIntf2DataSelIntf__Init(dataSelection, host->_ramNo, 0);
              NextStep(control);
              break;
            case 0x1:
              st2Now = control->_st2;
              switch ((unsigned int)st2Now) {
              case 0:
                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                NextSubstep(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2DataSelIntf__OpenSaveArea(dataSelection, 0) & 0xFF) == 1) {
                  NextSubstep(control);
                }
                break;
              case 2:
                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                NextSubstep(control);
                break;
              case 3:
                if (LoadHelpers::FlagAt(common, host)->_isCutConnect == 1) {
                  beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                  NextSubstep(control);
                  control->_st3 = 1;
                } else if ((beNDMWLoadIntf2DataSelIntf__UpdateSelection(dataSelection, 0) & 0xFF) == 1) {
                  beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                  NextSubstep(control);
                  control->_st3 = 0;
                }
                break;
              case 4:
                if ((beNDMWLoadIntf2DataSelIntf__CloseAll(dataSelection, 0) & 0xFF) == 1) {
                  st3Now_2 = control->_st3;
                  switch ((unsigned int)st3Now_2) {
                  case 0:
                    NextStep(control);
                    break;
                  case 1:
                    SetStep(control, 0x64);
                    break;
                  }
                }
                break;
              }
              break;
            case 0x2:
              if (dataSelection->_isCancel == 1) {
                EnterState(control, 6);
              } else {
                control->_isNewMake = 0U;
                EnterState(control, 8);
              }
              break;
            case 0x64:
              st2Now_2 = control->_st2;
              switch ((unsigned int)st2Now_2) {
              case 0:
                beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(dataSelection, 0);
                NextSubstep(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2DataSelIntf__CloseAll(dataSelection, 0) & 0xFF) == 1) {
                  allocator = LoadHelpers::Selector(
                      &g_defaultAllocatorSelector[0],
                      igObject_GetAllocator(self));
                  {
                    RecoveryRef<0> freshDataRef(
                        (void *)(beNDMWDegiData_Create(allocator)));
                    ObjectList_SetAtRetained_003e9160(
                        (igDataList *)common->_gameUseData, host->_ramNo, (ObjectRefTarget *)freshDataRef.value);
                  }
                  EnterState(control, 6);
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
                                              &GAMERAM_2[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &GAMEDATAINIT[0]);
                      allocator_2 = LoadHelpers::Selector(
                          &g_ndmwAllocatorSelector[0],
                          igObject_GetAllocator(self));
                      nameObject = (void *)FUN_003614f0(allocator_2);
                      {
                        igSmartPointer<beUnicodeObj> nameRef((beUnicodeObj *)nameObject);
                        beUnicodeObj_AllocateBuffer(nameRef.p, 8);
                        NameCopyHelper::Copy(
                            (unsigned short *)nameRef.p->_buffer,
                            nameEntry);
                        beMessenger_SelectGroup(self->_messenger,
                                                &GAMERAM_2[0]);
                        beMessenger_AppendInt(self->_messenger, host->_ramNo);
                        beMessenger_AppendString(
                            self->_messenger,
                            g_playerModelRow[creation->_chaSelDegi].name);
                        beMessenger_AppendObject(self->_messenger,
                                                 nameRef.p);
                        beMessenger_DispatchSelected(self->_messenger,
                                                     &GAMESTART[0]);
                      }
                      beMessenger_SelectGroup(self->_messenger,
                                              &GAMERAM_2[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &GETPLAYER[0]);
                      newPlayer = beMessenger_GetObject(self->_messenger, 0);
                      /* Stamp the new character with the low word of the world
                       * clock as its UNIQUE property. */
                      worldTime = ((igInsightCore *)self->_insight)->_worldTime;
                      {
                        void *record = igProperty_GetRecord(
                            newPlayer, &UNIQUE[0]);
                        *(int *)((char *)record + 12) = (int)worldTime;
                      }
                      beNDMWDegiData__LoadFromProperties(ObjectList_GetAt_003e9260(
                                       (igDataList *)common->_gameUseData, host->_ramNo),
                                   newPlayer);
                    } else {
                      beMessenger_SelectGroup(self->_messenger,
                                              &GAMERAM_2[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &GAMEDATAINIT[0]);
                      savedData = PlayerSaveData(common, host->_ramNo,
                                                 dataSelection->_svDataSelPoint);
                      {
                        RecoveryRef<0> savedDataRef(savedData, true);
                        ObjectList_SetAtRetained_003e9160((igDataList *)common->_gameUseData,
                                                          host->_ramNo,
                                                          (ObjectRefTarget *)savedDataRef.value);
                        beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(common, host->_ramNo);
                      }
                      beMessenger_SelectGroup(self->_messenger,
                                              &GAMERAM_2[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &GETPLAYER[0]);
                      loadedPlayer = beMessenger_GetObject(self->_messenger, 0);
                      font = FUN_00236f80(self->_insight,
                                          g_beFont_metaObject[0]);
                      beNDMWDegiData__StoreToProperties(ObjectList_GetAt_003e9260(
                                       (igDataList *)common->_gameUseData, host->_ramNo),
                                   loadedPlayer, font);
                      kindName = ((beNDMWDegiData *)ObjectList_GetAt_003e9260(
                                      (igDataList *)common->_gameUseData, host->_ramNo))
                                     ->_dmkind;
                      beMessenger_SelectGroup(self->_messenger,
                                              &GAMERAM_2[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_AppendString(self->_messenger, kindName);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &BASE2CURRENT[0]);
                      beMessenger_SelectGroup(self->_messenger,
                                              &GAMERAM_2[0]);
                      beMessenger_AppendInt(self->_messenger, host->_ramNo);
                      beMessenger_DispatchSelected(self->_messenger,
                                                   &RECALCPLAYER[0]);
                    }
                  }
                  needsDifficulty = 0;
                  difficultyCase = 0;
                  if ((host->_ramNo == 0) && (control->_isRdyCancel == 1)) {
                    common->_difficultMode = 0;
                    self->_difficultMax = 0;
                    g_mdlEntity[0] = 0;
                    beLua__RunNamedChunk(FUN_00236f80(self->_insight,
                                              g_beLua_metaObject[0]),
                                 &hostLoad_lua[0], 0);
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
                    OpenDegiState(status, 1, host->_ramNo);
                    NextSubstep(control);
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
                          &g_defaultAllocatorSelector[0],
                          igObject_GetAllocator(self));
                      {
                        RecoveryRef<0> freshDataRef_2(
                            (void *)(beNDMWDegiData_Create(allocator_3)));
                        ObjectList_SetAtRetained_003e9160((igDataList *)common->_gameUseData,
                                                          host->_ramNo,
                                                          (ObjectRefTarget *)freshDataRef_2.value);
                      }
                      LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                      EnterState(control, 6);
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
                if ((beNDMWLoadIntf2DegiState__Update(
                         (beNDMWLoadIntf2DegiState *)(ObjectList_GetAt_003e9260((igDataList *)status->_statDataList, 0))) &
                     0xFF) == 1) {
                  LoadHelpers::FlagAt(common, host)->_isRdy = 1;
                  if (host->_ramNo == 0) {
                    workList = (void *)common->_flagWork;
                    entryCount = 0;
                    workIndex = 0;
                    readyCount = 0;
                    if (0 < igDataList_GetCount(workList)) {
                      do {
                        if ((beNDMWLoadSavePlWork__GetIsEntry((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                                 (igDataList *)workList, workIndex))) &
                             0xFF) == 1) {
                          entryCount += 1;
                        }
                        if ((beNDMWLoadSavePlWork__GetIsRdy((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                                 (igDataList *)workList, workIndex))) &
                             0xFF) == 1) {
                          readyCount += 1;
                        }
                        workIndex += 1;
                      } while (workIndex < igDataList_GetCount(workList));
                    }
                    if ((entryCount == readyCount) == 1) {
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
              st1Now = control->_st2;
              switch ((unsigned int)st1Now) {
              case 0:
                if (control->_isRdyCancel == 1) {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x530));
                } else {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x52F));
                }
                NextSubstep(control);
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
                    if (0 < igDataList_GetCount(workList_2)) {
                      do {
                        if ((beNDMWLoadSavePlWork__GetIsEntry((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                                 (igDataList *)workList_2, workIndex_2))) &
                             0xFF) == 1) {
                          entryCount_2 += 1;
                        }
                        if ((beNDMWLoadSavePlWork__GetIsRdy((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                                 (igDataList *)workList_2, workIndex_2))) &
                             0xFF) == 1) {
                          readyCount_2 += 1;
                        }
                        workIndex_2 += 1;
                      } while (workIndex_2 < igDataList_GetCount(workList_2));
                    }
                    if ((entryCount_2 == readyCount_2) == 1) {
                      SetStep(control, 3);
                    } else if ((padTrigger & kPadCircle) &&
                               (control->_isRdyCancel == 1)) {
                      LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                      NextStep(control);
                    }
                  } else {
                    workList_3 = (void *)common->_flagWork;
                    entryCount_3 = 0;
                    readyCount_3 = 0;
                    workIndex_3 = 0;
                    if (0 < igDataList_GetCount(workList_3)) {
                      do {
                        if ((beNDMWLoadSavePlWork__GetIsEntry((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                                 (igDataList *)workList_3, workIndex_3))) &
                             0xFF) == 1) {
                          entryCount_3 += 1;
                        }
                        if ((beNDMWLoadSavePlWork__GetIsRdy((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                                 (igDataList *)workList_3, workIndex_3))) &
                             0xFF) == 1) {
                          readyCount_3 += 1;
                        }
                        workIndex_3 += 1;
                      } while (workIndex_3 < igDataList_GetCount(workList_3));
                    }
                    if ((entryCount_3 == readyCount_3) == 1) {
                      if (control->_isRdyCancel == 1) {
                        beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x51F));
                      } else {
                        beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x522));
                      }
                      control->_st3 = (control->_st3 + 1);
                    } else if ((padTrigger & kPadCircle) &&
                               (control->_isRdyCancel == 1)) {
                      LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                      NextStep(control);
                    }
                  }
                  break;
                case 1:
                  workList_4 = (void *)common->_flagWork;
                  entryCount_4 = 0;
                  readyCount_4 = 0;
                  workIndex_4 = 0;
                  if (0 < igDataList_GetCount(workList_4)) {
                    do {
                      if ((beNDMWLoadSavePlWork__GetIsEntry((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                               (igDataList *)workList_4, workIndex_4))) &
                           0xFF) == 1) {
                        entryCount_4 += 1;
                      }
                      if ((beNDMWLoadSavePlWork__GetIsRdy((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                               (igDataList *)workList_4, workIndex_4))) &
                           0xFF) == 1) {
                        readyCount_4 += 1;
                      }
                      workIndex_4 += 1;
                    } while (workIndex_4 < igDataList_GetCount(workList_4));
                  }
                  if ((entryCount_4 == readyCount_4) == 0) {
                    if (control->_isRdyCancel == 1) {
                      beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x530));
                    } else {
                      beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x52F));
                    }
                    control->_st3 = 0;
                  } else if ((padTrigger & kPadCircle) &&
                             (control->_isRdyCancel == 1)) {
                    LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                    NextStep(control);
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
                             &j_mainstatuswin[0],
                             &SQ_CANCEL[0], 1);
                NextSubstep(control);
                break;
              case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                  NextSubstep(control);
                }
                break;
              case 2:
                beNDMWLoadIntf2DegiState__RequestClose(
                    (beNDMWLoadIntf2DegiState *)(ObjectList_GetAt_003e9260((igDataList *)status->_statDataList, 0)), 0);
                NextSubstep(control);
                break;
              case 3:
                if ((beNDMWLoadIntf2DegiState__Update(
                         (beNDMWLoadIntf2DegiState *)(ObjectList_GetAt_003e9260((igDataList *)status->_statDataList, 0))) &
                     0xFF) == 1) {
                  if (control->_isNewMake == 1) {
                    EnterState(control, 5);
                    beNDMWLoadIntf2NameSel__Init(nameEntry, 0);
                  } else {
                    allocator_4 = LoadHelpers::Selector(
                        &g_defaultAllocatorSelector[0],
                        igObject_GetAllocator(self));
                    {
                      RecoveryRef<0> freshDataRef_3(
                          (void *)(beNDMWDegiData_Create(allocator_4)));
                      ObjectList_SetAtRetained_003e9160((igDataList *)common->_gameUseData,
                                                        host->_ramNo,
                                                        (ObjectRefTarget *)freshDataRef_3.value);
                    }
                    EnterState(control, 6);
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
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x51D));
                } else {
                  beNDMWLoadIntf2MesWin__RequestMessage(messages, TextId(host, 0x521));
                }
                NextSubstep(control);
                break;
              case 1:
                if ((padTrigger & kPadCircle) && (control->_isRdyCancel == 1)) {
                  LoadHelpers::FlagAt(common, host)->_isRdy = 0;
                  SetStep(control, 2);
                } else {
                  workList_5 = (void *)common->_flagWork;
                  entryCount_5 = 0;
                  readyCount_5 = 0;
                  workIndex_5 = 0;
                  if (0 < igDataList_GetCount(workList_5)) {
                    do {
                      if ((beNDMWLoadSavePlWork__GetIsEntry((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                               (igDataList *)workList_5, workIndex_5))) &
                           0xFF) == 1) {
                        entryCount_5 += 1;
                      }
                      if ((beNDMWLoadSavePlWork__GetIsRdy((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                               (igDataList *)workList_5, workIndex_5))) &
                           0xFF) == 1) {
                        readyCount_5 += 1;
                      }
                      workIndex_5 += 1;
                    } while (workIndex_5 < igDataList_GetCount(workList_5));
                  }
                  if ((entryCount_5 == readyCount_5) == 1) {
                    if (padTrigger & kPadStart) {
                      workIndex_6 = 0;
                      common->_intfStat = 3;
                      workList_6 = (void *)common->_flagWork;
                      if (0 < igDataList_GetCount(workList_6)) {
                        do {
                          beNDMWLoadSavePlWork__SetIsCtrl((beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240((igDataList *)workList_6,
                                                                   workIndex_6)),
                                       0);
                          workIndex_6 += 1;
                        } while (workIndex_6 < igDataList_GetCount(workList_6));
                      }
                      ((beSystem *)common->_system)->_isSResetEnable = 0;
                      NextSubstep(control);
                    }
                  } else {
                    SetStep(control, 1);
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
                (igDataList *)common->_flagWork, host->_ramNo));
            SetPlayerStep(exitWork, 1);
            break;
          case 2:
            exitWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                (igDataList *)common->_flagWork, host->_ramNo));
            SetPlayerStep(exitWork, 1);
            break;
          case 8:
            beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_chrselmesswin[0],
                         (const char *)&SQ_CLOSE[0], 1);
            beNDMWLoadIntf2MesWin__RequestClose(messages);
            beNDMWLoadIntf2DegiState__RequestConfirmClose((beNDMWLoadIntf2DegiState *)(ObjectList_GetAt_003e9260((igDataList *)status->_statDataList, 0)));
            exitWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                (igDataList *)common->_flagWork, host->_ramNo));
            SetPlayerStep(exitWork, 2);
            break;
          }
          beNDMWLoadIntf2ComMdlCtrl__Close(models, host->_ramNo, (const char *)&j_chrselbase[0],
                       (const char *)&SQ_CLOSE[0], 1);
          break;
        case 1:
          if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
            LoadHelpers::FlagAt(common, host)->_isClose = 1;
            hostWork_3 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                (igDataList *)common->_flagWork, host->_ramNo));
            SetPlayerStep(hostWork_3, 3);
          }
          break;
        case 2:
          if (((beNDMWLoadIntf2DegiState__Update(
                    (beNDMWLoadIntf2DegiState *)(ObjectList_GetAt_003e9260((igDataList *)status->_statDataList, 0))) &
                0xFF) == 1) &&
              ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1)) {
            LoadHelpers::FlagAt(common, host)->_isClose = 1;
            hostWork_4 = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
                (igDataList *)common->_flagWork, host->_ramNo));
            SetPlayerStep(hostWork_4, 3);
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
            stepResult = beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(common, host->_ramNo, messages,
                                      slots->_mcSelPoint, 3);
            switch ((unsigned int)stepResult) {
            case 0:
              break;
            case 1:
              SetPlayerStep(cardWork, 5);
              break;
            case 2:
              utilResult = LoadHelpers::McUtil(common)->_result;
              switch ((unsigned int)utilResult) {
              case 2:
                SetPlayerStep(cardWork, 5);
                break;
              case 7:
                if (common->_kindHard == 1) {
                  SetPlayerStep(cardWork, 3);
                } else {
                  EnterPlayerStage(cardWork, 6);
                }
                break;
              case 12:
                EnterPlayerStage(cardWork, 6);
                break;
              default:
              case 4:
              case 3:
                EnterPlayerStage(cardWork, 6);
                break;
              }
              break;
            }
            break;
          case 1:
            if (((beNDMWMcSlot *)ObjectList_GetAt_003e9260(
                     (igDataList *)(LoadHelpers::McUtil(common)->_slot), slots->_mcSelPoint))
                    ->_isConnect != 1) {
              beNDMWLoadIntf2MesWin__Cancel(messages);
              EnterPlayerStage(cardWork, 7);
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
              stepResult_2 = beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(common, host->_ramNo, messages,
                                          firstTextId, secondTextId, 0, 3);
              switch ((unsigned int)stepResult_2) {
              case 0:
                break;
              case 1:
                SetPlayerStep(cardWork, 2);
                break;
              case 2:
                EnterPlayerStage(cardWork, 7);
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
              cardWork->_sysStat2 = (cardWork->_sysStat2 + 1);
              cardWork->_sysStat3 = 0;
              break;
            case 1:
              stepResult_3 = beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(common, host->_ramNo, messages,
                                          slots->_mcSelPoint, 3);
              switch ((unsigned int)stepResult_3) {
              case 0:
                break;
              case 1:
                SetPlayerStep(cardWork, 5);
                break;
              case 2:
                utilResult_3 = LoadHelpers::McUtil(common)->_result;
                switch (utilResult_3 - 3U) {
                case 4:
                  SetPlayerStep(cardWork, 3);
                  break;
                case 6:
                case 7:
                  EnterPlayerStage(cardWork, 6);
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
                  EnterPlayerStage(cardWork, 6);
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
                     (igDataList *)(LoadHelpers::McUtil(common)->_slot), slots->_mcSelPoint))
                    ->_isConnect != 1) {
              beNDMWLoadIntf2MesWin__Cancel(messages);
              EnterPlayerStage(cardWork, 7);
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
              stepResult_4 = beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(common, host->_ramNo, messages,
                                          firstTextId_2, secondTextId_2, 1, 3);
              switch ((unsigned int)stepResult_4) {
              case 0:
                break;
              case 1:
                SetPlayerStep(cardWork, 4);
                break;
              case 2:
                EnterPlayerStage(cardWork, 7);
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
                messageId_14 = TextId(host, 0x1008);
                break;
              case 1:
                messageId_14 = TextId(host, 0x2008);
                break;
              case 2:
                messageId_14 = TextId(host, 0x3008);
                break;
              }
              beNDMWLoadIntf2MesWin__RequestMessage(messages, messageId_14);
              if (common->_isTitle == 0) {
                ((beSystem *)self->_system_)->_isSResetEnable = 0;
              }
              ((beSystem *)self->_system_)->_isResetEnable = 0;
              cardWork->_sysStat2 = (cardWork->_sysStat2 + 1);
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
                EnterPlayerStage(cardWork, 7);
                break;
              case 2:
                utilResult_4 = LoadHelpers::McUtil(common)->_result;
                switch (utilResult_4 - 3U) {
                case 1:
                  EnterPlayerStage(cardWork, 6);
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
                  EnterPlayerStage(cardWork, 6);
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
                         void **)&common->_slotSaveData)
                        ->_count) {
            findSlotPlayer:
              {
                int connection =
                    ((beNDMWLoadSlotPlayer *)ObjectList_GetAt_003e9260(
                         (igDataList *)common->_slotSaveData, listIndex))
                        ->_connectNO;
                if (connection == slots->_mcSelPoint) {
                  slotPlayer =
                      (beNDMWLoadSlotPlayer *)ObjectList_GetAt_003e9260(
                          (igDataList *)common->_slotSaveData, listIndex);
                } else {
                  listIndex += 1;
                  if (listIndex < ((beNDMWLoadSlotPlayerList *)*(
                                       void **)&common->_slotSaveData)
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
              accessPlayer = host->_ramNo;
              if (accessCount < accessList->cap) {
                accessList->count = accessList->getCount() + 1;
              } else {
                List_Resize(accessList, accessCount + 1, 4);
              }
              ((int *)DataList_GetData_003e9090((igDataList *)accessList))[accessCount] =
                  accessPlayer;
              cardWork->_haveSaveData = (int)slotPlayer;
              EnterPlayerStage(cardWork, 7);
              cardWork->_utilReturn = 0;
            }
            break;
          case 6:
            cardStat2_2 = cardWork->_sysStat2;
            switch ((unsigned int)cardStat2_2) {
            case 0:
              cardWork->_sysStat2 = (sysStat2(cardWork) + 1);
              cardWork->_sysStat3 = 0;
              break;
            case 1:
              stepResult_6 = beNDMWLoadCtrl2CommonIntf__StepReadMedia(common, host->_ramNo, messages,
                                          slots->_mcSelPoint, 3);
              switch ((unsigned int)stepResult_6) {
              case 0:
                break;
              case 1:
                EnterPlayerStage(cardWork, 7);
                cardWork->_utilReturn = 0;
                break;
              case 2:
                utilResult_5 = LoadHelpers::McUtil(common)->_result;
                switch (utilResult_5 - 3U) {
                case 4:
                  SetPlayerStep(cardWork, 3);
                  break;
                case 6:
                case 7:
                  EnterPlayerStage(cardWork, 6);
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
                  EnterPlayerStage(cardWork, 6);
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
                messageId_15 = TextId(host, 0x100E);
                break;
              case 1:
                messageId_15 = TextId(host, 0x200E);
                break;
              case 2:
                messageId_15 = TextId(host, 0x300E);
                break;
              }
              beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_15);
            } else if (((beNDMWMcSlot *)ObjectList_GetAt_003e9260(
                            (igDataList *)mcUtil->_slot, slots->_mcSelPoint))
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
                  messageId_16 = TextId(host, 0x1028);
                  break;
                case 1:
                  messageId_16 = TextId(host, 0x2012);
                  break;
                case 2:
                  messageId_16 = TextId(host, 0x3012);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_16);
                break;
              case 6:
                kindHard_9 = common->_kindHard;
                messageId = -1;
                switch ((unsigned int)kindHard_9) {
                case 0:
                  messageId = TextId(host, 0x1014);
                  break;
                case 1:
                  messageId = TextId(host, 0x2014);
                  break;
                case 2:
                  messageId = TextId(host, 0x3014);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId);
                break;
              case 7:
                kindHard_10 = common->_kindHard;
                messageId_2 = -1;
                switch ((unsigned int)kindHard_10) {
                case 0:
                  messageId_2 = TextId(host, 0x1015);
                  break;
                case 1:
                  messageId_2 = TextId(host, 0x2015);
                  break;
                case 2:
                  messageId_2 = TextId(host, 0x3015);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_2);
                break;
              case 2:
                kindHard_11 = common->_kindHard;
                messageId_3 = -1;
                switch ((unsigned int)kindHard_11) {
                case 0:
                  messageId_3 = TextId(host, 0x1010);
                  break;
                case 1:
                  messageId_3 = TextId(host, 0x2010);
                  break;
                case 2:
                  messageId_3 = TextId(host, 0x3010);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_3);
                break;
              case 3:
                kindHard_12 = common->_kindHard;
                messageId_4 = -1;
                switch ((unsigned int)kindHard_12) {
                case 0:
                  messageId_4 = TextId(host, 0x1011);
                  break;
                case 1:
                  messageId_4 = TextId(host, 0x2011);
                  break;
                case 2:
                  messageId_4 = TextId(host, 0x3011);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_4);
                break;
              case 5:
                kindHard_13 = common->_kindHard;
                messageId_5 = -1;
                switch ((unsigned int)kindHard_13) {
                case 0:
                  messageId_5 = TextId(host, 0x1013);
                  break;
                case 1:
                  messageId_5 = TextId(host, 0x2013);
                  break;
                case 2:
                  messageId_5 = TextId(host, 0x3013);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_5);
                break;
              case 9:
                kindHard_14 = common->_kindHard;
                messageId_6 = -1;
                switch ((unsigned int)kindHard_14) {
                case 0:
                  messageId_6 = TextId(host, 0x1016);
                  break;
                case 1:
                  messageId_6 = TextId(host, 0x2016);
                  break;
                case 2:
                  messageId_6 = TextId(host, 0x3016);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_6);
                break;
              case 1:
                kindHard_15 = common->_kindHard;
                messageId_7 = -1;
                switch ((unsigned int)kindHard_15) {
                case 0:
                  messageId_7 = TextId(host, 0x1028);
                  break;
                case 1:
                  messageId_7 = TextId(host, 0x2028);
                  break;
                case 2:
                  messageId_7 = TextId(host, 0x3028);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_7);
                break;
              case 0:
              default:
                kindHard_16 = common->_kindHard;
                messageId_8 = -1;
                switch ((unsigned int)kindHard_16) {
                case 0:
                  messageId_8 = TextId(host, 0x100D);
                  break;
                case 1:
                  messageId_8 = TextId(host, 0x200D);
                  break;
                case 2:
                  messageId_8 = TextId(host, 0x300D);
                  break;
                }
                beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_8);
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
                messageId_9 = TextId(host, 0x1016);
                break;
              case 1:
                messageId_9 = TextId(host, 0x2016);
                break;
              case 2:
                messageId_9 = TextId(host, 0x3016);
                break;
              }
              beNDMWLoadIntf2MesWin__RequestPrompt(messages, messageId_9);
            }
            resultWork->_sysStat2 = (resultWork->_sysStat2 + 1);
            resultWork->_sysStat3 = 0;
            break;
          case 1:
            if (!(beNDMWLoadIntf2MesWin__GetIsCtrl(messages) & 0xFF)) {
              resultWork->_utilReturn = 1;
              EnterPlayerStage(resultWork, 7);
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
              (igDataList *)common->_flagWork, playerIndex));
          playerIndex += 1;
          EnterPlayerStage(eachWork, 8);
        } while (playerIndex < 4);
        break;
      /* Stage 8: clear the message window, reset this player's stages and hand
       * the pad back to the screens (_isCtrl = 1). */
      case 8:
        beNDMWLoadIntf2MesWin__EndSystemMessage(messages);
        resetWork = (beNDMWLoadSavePlWork *)(DataList_GetWordAt_003e9240(
            (igDataList *)common->_flagWork, host->_ramNo));
        EnterPlayerStage(resetWork, 0);
        LoadHelpers::FlagAt(common, host)->_isCtrl = 1;
        break;
      }
    }
  }
done:
  return;
}


void beNDMWLoadIntf2DegiState__RequestOpen(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2) {
    arg0->_kind = arg1;
    arg0->_dataNo = arg2;
    arg0->_isEnd = 0;
    arg0->_st0 = 1;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

void FUN_003d9e40(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2) {
    arg0->_kind = arg1;
    arg0->_dataNo = arg2;
    arg0->_isEnd = 0;
    arg0->_st0 = 3;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

void beNDMWLoadIntf2DegiState__RequestClose(beNDMWLoadIntf2DegiState *arg0, int arg1) {
    arg0->_isEnd = 0;
    arg0->_closeKind = arg1;
    arg0->_st0 = 2;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

void beNDMWLoadIntf2DegiState__RequestConfirmClose(beNDMWLoadIntf2DegiState *arg0) {
    arg0->_isEnd = 0;
    arg0->_closeKind = 1;
    arg0->_st0 = 2;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

/* Owning stack reference to the slot's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

void FUN_003d9ec0(SlotPanel *arg0) {
    SlotBackend *v1 = arg0->backend;
    unsigned short *dA, *dB, *srcA, *srcB; int iA, iB;
    if (arg0->side == 0) {
        SlotDisplay *s0;
        int sp90[8];
        if (arg0->source == 0) {
            s0 = ((SlotDisplay **)((AreaRow **)v1->areas->_data)[arg0->player]->cell->displays->_data)[arg0->index];
        } else {
            s0 = ((SlotDisplay **)v1->ownDisplays->_data)[arg0->player];
        }
        if (s0->used == 1) {
            int a, s5, s4, s3;
            SlotEnt *s2;
            a = igObject_GetAllocator(arg0);
            {
                igSmartPointer<beUnicodeObj> text(FUN_003614f0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
                beUnicodeObj_AllocateBuffer(text.p, 8);
                srcA = (unsigned short *)((char *)s0 + 8);
                iA = 0;
                dA = (unsigned short *)text.p->_buffer;
                for (;;) {
                    dA[iA] = srcA[iA + 1];
                    if (dA[iA] == 0) break;
                    iA += 1;
                    if (iA >= 8) break;
                }
                for (; iA < 8; iA++) {
                    dA[iA] = 0;
                }
                FUN_003ec120(arg0->textCtrl, DAT_00516c40, arg0->player, 0, text.p, 0, 0);
            }
            beMessenger_SendNamed(arg0->messenger, DATABASE, shinka, 0, GETDATABASE);
            s4 = beMessenger_GetObject(arg0->messenger, 0);
            s3 = 0;
            s2 = ((SlotEnt *)g_playerModelRow);
        lsA:
            if (strcmp(s2->name, s0->model) == 0) {
                s5 = s3;
            } else {
                s3 += 1;
                s2 += 1;
                if (s3 < 16) goto lsA;
            }
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 10, beDataBase_GetRecordString(s4, s5, NAME), 0, 0);
            sprintf(sp90, DAT_00516c90, s0->level);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 0, sp90, 1, 0);
            sprintf(sp90, DAT_00516c90, s0->hp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 0, sp90, 2, 0);
            sprintf(sp90, DAT_00516c90, s0->maxHp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 10, sp90, 2, 0);
            sprintf(sp90, DAT_00516c90, s0->mp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 1, sp90, 2, 0);
            sprintf(sp90, DAT_00516c90, s0->maxMp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 11, sp90, 2, 0);
        } else {
            beNDMWLoadIntf2TextOrder_PublishIdLines(arg0->textCtrl, (arg0->player << 16) | 0x10, 0);
        }
    } else {
        SlotDisplay *s0;
        int sp70[8];
        if (arg0->source == 0) {
            s0 = ((SlotDisplay **)((AreaRow **)v1->areas->_data)[arg0->player]->cell->displays->_data)[arg0->index];
        } else {
            s0 = ((SlotDisplay **)v1->ownDisplays->_data)[arg0->player];
        }
        if (s0->used == 1) {
            int a, s5, s4, s3;
            SlotEnt *s2;
            a = igObject_GetAllocator(arg0);
            {
                igSmartPointer<beUnicodeObj> text(FUN_003614f0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
                beUnicodeObj_AllocateBuffer(text.p, 8);
                srcB = (unsigned short *)((char *)s0 + 8);
                iB = 0;
                dB = (unsigned short *)text.p->_buffer;
                for (;;) {
                    dB[iB] = srcB[iB + 1];
                    if (dB[iB] == 0) break;
                    iB += 1;
                    if (iB >= 8) break;
                }
                for (; iB < 8; iB++) {
                    dB[iB] = 0;
                }
                FUN_003ec120(arg0->textCtrl, DAT_00516c40, arg0->player, 10, text.p, 0, 0);
            }
            beMessenger_SendNamed(arg0->messenger, DATABASE, shinka, 0, GETDATABASE);
            s4 = beMessenger_GetObject(arg0->messenger, 0);
            s3 = 0;
            s2 = ((SlotEnt *)g_playerModelRow);
        lsB:
            if (strcmp(s2->name, s0->model) == 0) {
                s5 = s3;
            } else {
                s3 += 1;
                s2 += 1;
                if (s3 < 16) goto lsB;
            }
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 11, beDataBase_GetRecordString(s4, s5, NAME), 0, 0);
            sprintf(sp70, DAT_00516c90, s0->level);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 1, sp70, 1, 0);
            sprintf(sp70, DAT_00516c90, s0->hp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 2, sp70, 2, 0);
            sprintf(sp70, DAT_00516c90, s0->maxHp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 12, sp70, 2, 0);
            sprintf(sp70, DAT_00516c90, s0->mp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 3, sp70, 2, 0);
            sprintf(sp70, DAT_00516c90, s0->maxMp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 13, sp70, 2, 0);
        } else {
            beNDMWLoadIntf2TextOrder_PublishIdLines(arg0->textCtrl, (arg0->player << 16) | 0x110, 0);
        }
    }
}

void FUN_003da5f0(beNDMWLoadIntf2DegiState *arg0) {
    if (arg0->_dispPos == 0) {
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c40[0], arg0->_plNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 0xA);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xA);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xB);
        TextOrder_PublishLineListOnly(arg0->_textOrder, (arg0->_plNo << 0x10) | 0x10);
        return;
    }
    if (arg0->_isUseData == 1) {
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c40[0], arg0->_plNo, 0xA);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 0xB);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 2);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xC);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 3);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xD);
        return;
    }
    TextOrder_PublishLineListOnly(arg0->_textOrder, (arg0->_plNo << 0x10) | 0x110);
}

unsigned char beNDMWLoadIntf2DegiState__Update(beNDMWLoadIntf2DegiState *arg0) {

    if (arg0->_isEnd == 1) {
        return 1;
    }
    Bk *a1 = (Bk *)arg0->_commonIntf;
    switch (arg0->_st0) {
    case 0:
        break;
    case 1:
        switch (arg0->_st1) {
        case 0: {
            Item *s1;
            if (arg0->_kind == 0) {
                s1 = a1->f40->arr[arg0->_plNo]->f32->f12->arr[arg0->_dataNo];
            } else {
                s1 = a1->f36->arr[arg0->_plNo];
            }
            if (s1->b40 == 1) {
                arg0->_isUseData = 1;
            } else {
                arg0->_isUseData = 0;
            }
            if (arg0->_isUseData == 1) {
                int s0 = 0;
                int s4 = 0;
                Ent *s3 = g_playerModelRow;
            loop_22:
                if (strcmp(s3->name, s1->f48) == 0) {
                    s0 = s4;
                } else {
                    s4 += 1;
                    s3 += 1;
                    if (s4 < 16) {
                        goto loop_22;
                    }
                }
                if (arg0->_dispPos == 0) {
                    V3 vb; V3 va;
                    Ob *o = (Ob *)arg0->_comMdlCtrl;
                    vb.x = o->v28; vb.y = o->v32; vb.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_digifacewin, (const char *)g_playerModelRow[s0].val, (float *)&vb, 1);
                    o = (Ob *)arg0->_comMdlCtrl;
                    va.x = o->v28; va.y = o->v32; va.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_mainstatuswin, (const char *)SQ_OPEN, (float *)&va, 1);
                } else {
                    V3 vc;
                    Ob *o = (Ob *)arg0->_comMdlCtrl;
                    vc.x = o->v28; vc.y = o->v32; vc.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cd8, (const char *)g_playerModelRow[s0].val, (float *)&vc, 1);
                }
            } else if (arg0->_dispPos == 0) {
                V3 vd; V3 ve;
                Ob *o = (Ob *)arg0->_comMdlCtrl;
                vd.x = o->v28; vd.y = o->v32; vd.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_digifacewin, (const char *)DAT_00516ce8, (float *)&vd, 1);
                o = (Ob *)arg0->_comMdlCtrl;
                ve.x = o->v28; ve.y = o->v32; ve.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_mainstatuswin, (const char *)DAT_00516cf8, (float *)&ve, 1);
            } else {
                V3 vf;
                Ob *o = (Ob *)arg0->_comMdlCtrl;
                vf.x = o->v28; vf.y = o->v32; vf.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cd8, (const char *)DAT_00516ce8, (float *)&vf, 1);
            }
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        }
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl) & 0xFF) == 1) {
                FUN_003d9ec0((SlotPanel *)arg0);
                arg0->_isEnd = 1;
                arg0->_st0 = 0;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            }
            break;
        }
        break;
    case 3: {
        Item *s1;
        if (arg0->_kind == 0) {
            s1 = a1->f40->arr[arg0->_plNo]->f32->f12->arr[arg0->_dataNo];
        } else {
            s1 = a1->f36->arr[arg0->_plNo];
        }
        if (s1->b40 == 1) {
            arg0->_isUseData = 1;
        } else {
            arg0->_isUseData = 0;
        }
        if (arg0->_isUseData == 1) {
            int s0 = 0;
            int s4 = 0;
            Ent *s3 = g_playerModelRow;
        loop_46:
            if (strcmp(s3->name, s1->f48) == 0) {
                s0 = s4;
            } else {
                s4 += 1;
                s3 += 1;
                if (s4 < 16) {
                    goto loop_46;
                }
            }
            if (arg0->_dispPos == 0) {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)j_digifacewin, (int *)g_playerModelRow[s0].val2, 0);
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)j_mainstatuswin, (int *)DAT_00516d08, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516cd8, (int *)g_playerModelRow[s0].val2, 0);
            }
        } else if (arg0->_dispPos == 0) {
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)j_digifacewin, (int *)DAT_00516d10, 0);
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)j_mainstatuswin, (int *)DAT_00516d20, 0);
        } else {
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516cd8, (int *)DAT_00516d10, 0);
        }
        FUN_003da5f0((beNDMWLoadIntf2DegiState *)arg0);
        FUN_003d9ec0((SlotPanel *)arg0);
        arg0->_isEnd = 1;
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    }
    case 2: {
        Item *s1;
        if (arg0->_kind == 0) {
            s1 = a1->f40->arr[arg0->_plNo]->f32->f12->arr[arg0->_dataNo];
        } else {
            s1 = a1->f36->arr[arg0->_plNo];
        }
        if (s1->b40 == 1) {
            arg0->_isUseData = 1;
        } else {
            arg0->_isUseData = 0;
        }
        switch (arg0->_st1) {
        case 0:
            if (arg0->_dispPos == 0) {
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_digifacewin, (const char *)SQ_CLOSE, 1);
                if (arg0->_isUseData == 1) {
                    switch (arg0->_closeKind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_mainstatuswin, (const char *)SQ_CLOSE, 1);
                        break;
                    case 1:
                        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_mainstatuswin, (const char *)SQ_LINEON00, 1);
                        break;
                    case 2:
                        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_mainstatuswin, (const char *)SQ_CANCEL, 1);
                        break;
                    }
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)j_mainstatuswin, (const char *)DAT_00516d60, 1);
                }
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cd8, (const char *)SQ_CLOSE, 1);
            }
            FUN_003da5f0((beNDMWLoadIntf2DegiState *)arg0);
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl) & 0xFF) == 1) {
                arg0->_isEnd = 1;
                arg0->_st0 = 0;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
            }
            break;
        }
        break;
    }
    }
    return arg0->_isEnd;
}

void beNDMWLoadIntf2DataSelIntf__Init(beNDMWLoadIntf2DataSelIntf *arg0, int arg1, int arg2) {
    arg0->_plNo = arg1;
    arg0->_isEnd = 0;
    arg0->_kind = arg2;
    arg0->_svDataSelPoint = 0;
    arg0->_isSaveArea = 0;
    arg0->_isUpStatWin = 0;
    arg0->_isDownStatWin = 0;
    arg0->_isSelCur = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

void beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    switch (arg1) {
    default:
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 1:
        arg0->_st1 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        return;
    case 2:
        arg0->_st2 = 0;
        arg0->_st3 = 0;
        return;
    case 3:
        arg0->_st3 = 0;
        return;
    }
}

/* Owning stack reference to the slot's name text; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

unsigned char beNDMWLoadIntf2DataSelIntf__OpenSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    int sp11C;
    beNDMWLoadCtrl2CommonIntf *sp100;
    int spF0;
    beNDMWLoadIntf2DegiStateCtrl *spE0;
    unsigned char spD0;
    int spC0;
    int spB0;
    int spA0;
    int al;
    unsigned short *a2;
    unsigned short *src;
    int n;
    unsigned short *v1;
    Ob *s0;
    int s2;
    sp11C = arg1;
    sp100 = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    s0 = (Ob *)arg0->_comMdlCtrl;
    spD0 = 0;
    s2 = arg0->_textOrder;
    spF0 = arg0->_mesWin;
    spE0 = (beNDMWLoadIntf2DegiStateCtrl *)arg0->_statDisp;
    switch (sp11C) {
    default:
        spC0 = arg0->_st0;
        break;
    case 1:
        spC0 = arg0->_st1;
        break;
    case 2:
        spC0 = arg0->_st2;
        break;
    case 3:
        spC0 = arg0->_st3;
        break;
    }
    switch (spC0) {
    case 0: {
        Ent *s8;
        int s5;
        int s4;
        beNDMWDegiData *it;
        int **s2p;
        spB0 = 0;
        s2p = ((int * *)DAT_004cc830);
        spA0 = 0;
        do {
            it = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[spB0];
            if (it->_isUse == 1) {
                if (*(char *)it->_dmkind != 0) {
                    s5 = 0;
                    s4 = 0;
                    s8 = g_playerModelRow;
                    V3 v1;
                loop_19:
                    if (strcmp(s8->name, it->_dmkind) == 0) {
                        s5 = s4;
                    } else {
                        s4 += 1;
                        s8 += 1;
                        if (s4 < 16) goto loop_19;
                    }
                    v1.x = s0->v28; v1.y = s0->v32; v1.z = s0->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s2p), (const char *)g_playerModelRow[s5].val, (float *)&v1, 1);
                } else {
                    V3 v2;
                    it->_isUse = 0;
                    v2.x = s0->v28; v2.y = s0->v32; v2.z = s0->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s2p), (const char *)DAT_00516cf8, (float *)&v2, 1);
                }
            } else {
                V3 v3;
                it->_isUse = 0;
                v3.x = s0->v28; v3.y = s0->v32; v3.z = s0->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s2p), (const char *)DAT_00516cf8, (float *)&v3, 1);
            }
            spA0 = spA0 + 4;
            spB0 = spB0 + 1;
            s2p++;
        } while (spB0 < 4);
        arg0->_isSaveArea = 1;
        {
            V3 v4;
            v4.x = s0->v28; v4.y = s0->v32; v4.z = s0->v36;
            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)DAT_00516db0, (const char *)SQ_OPEN, (float *)&v4, 1);
        }
        arg0->_isSelCur = 1;
        if (arg0->_kind == 0) {
            unsigned char fl;
            int s3;
            beNDMWDegiData *it2;
            int s0b;
            it2 = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[arg0->_svDataSelPoint];
            fl = 1;
            if (it2->_isUse == 1) {
                s3 = 0;
                s0b = 0;
            loop_31:
                {
                    beNDMWDegiData *o;
                    char *ca, *cb;
                    if (s3 != arg0->_plNo && (o = (beNDMWDegiData *)((int *)((beNDMWDegiDataList *)sp100->_gameUseData)->_data)[s3], o->_isUse == 1) && o->_id == it2->_id && (ca = (char *)o->_dmName, cb = (char *)it2->_dmName, ca != 0) && cb != 0 && strcmp(ca, cb) == 0) {
                        fl = 0;
                    } else {
                        s3 += 1;
                        s0b += 4;
                        if (s3 < 4) goto loop_31;
                    }
                }
            }
            if (fl == 1) {
                arg0->_mesKind = 0;
                beNDMWLoadIntf2MesWin__RequestMessage(spF0, (arg0->_plNo << 16) | 0x513);
            } else {
                arg0->_mesKind = 1;
                beNDMWLoadIntf2MesWin__RequestMessage(spF0, (arg0->_plNo << 16) | 0x515);
            }
            beNDMWLoadIntf2DegiState__RequestOpen((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]), 0, (int)arg0->_svDataSelPoint);
        } else {
            arg0->_mesKind = 0;
            beNDMWLoadIntf2MesWin__RequestMessage(spF0, (arg0->_plNo << 16) | 0x503);
            beNDMWLoadIntf2DegiState__RequestOpen((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]), 1, (int)arg0->_plNo);
        }
        arg0->_isUpStatWin = 1;
        spC0 = spC0 + 1;
        break;
    }
    case 1:
        if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]))) & 0xFF) == 1 && (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)s0) & 0xFF) == 1) {
            int s4;
            beNDMWDegiData *it;
            int s0c;
            s4 = 0;
            s0c = 0;
            do {
                it = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[s4];
                if (it->_isUse == 1) {
                    al = igObject_GetAllocator(arg0);
                    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beUnicodeObj> text((beUnicodeObj *)((int)FUN_003614f0(al)));
                    beUnicodeObj_AllocateBuffer(text.p, 8);
                    src = (unsigned short *)it->_dmNameUni;
                    n = 0;
                    a2 = (unsigned short *)text.p->_buffer;
                    v1 = a2;
                    for (n = 0; n < 8; n++) {
                        *v1 = src[1];
                        if (*v1 == 0) break;
                        src++;
                        v1++;
                    }
                    for (; n < 8; n++) a2[n] = 0;
                    FUN_003ec120(s2, DAT_00516dc8, arg0->_plNo, s4, text.p, 1, 0);
                } else {
                    it->_isUse = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(s2, (arg0->_plNo << 16) | 0x300 | s4, 0);
                }
                s4 += 1;
                s0c += 4;
            } while (s4 < 4);
            spD0 = 1;
            spC0 = spC0 + 1;
        }
        break;
    case 2:
        spD0 = 1;
        break;
    }
    switch (sp11C) {
    default:
        arg0->_st0 = spC0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = spC0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = spC0;
        arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = spC0;
        break;
    }
    return spD0;
}

unsigned char beNDMWLoadIntf2DataSelIntf__UpdateSelection(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    unsigned char uniq;
    beNDMWLoadCtrl2CommonIntf *host = (beNDMWLoadCtrl2CommonIntf *)c->_commonIntf;
    int bits;
    beNDMWDegiData *s4;
    int up;
    int a = c->_comMdlCtrl;
    unsigned char dn;
    int i;
    int v;
    unsigned char rt;
    int h40 = c->_mesWin;
    unsigned char lf;
    unsigned char r = 0;
        Node *n = (Node *)c->_statDisp;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    bits = 0;
    up = 0;
    dn = 0;
    rt = 0;
    lf = 0;
    if (PLW(host, c->_plNo)->_isCtrl == 1) {
            unsigned char u;
        bePadData *p = bePadManager_GetPadForPlayer(c->_padManager, c->_plNo);
        int m;
        int y;
        bits = p->_trigger;
        y = p->_repeat;
        m = p->_lTrg | p->_lRpt;
        u = 1;
        if ((m & 1) || ((bits | y) & 0x10)) {} else u = 0;
        up = u;
        dn = (m & 4) || ((bits | y) & 0x40);
        rt = (m & 8) || ((bits | y) & 0x80);
        lf = (m & 2) || ((bits | y) & 0x20);
    }
    switch (v) {
    case 0: {
        int nw;
        int cur;
        cur = c->_svDataSelPoint;
        nw = cur;
        if (up) {
            if (cur == 2) nw = 0; else if (cur == 3) nw = 1;
        } else if (dn) {
            if (cur == 0) nw = 2; else if (cur == 1) nw = 3;
        } else if (lf) {
            if (cur == 0) nw = 1; else if (cur == 2) nw = 3;
        } else if (rt) {
            if (cur == 1) nw = 0; else if (cur == 3) nw = 2;
        }
        if (nw != cur) {
            c->_svDataSelPoint = nw;
            if (c->_kind == 0) FUN_003d9e40((beNDMWLoadIntf2DegiState *)n->n16->n16->f0, 0, c->_svDataSelPoint);
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (int *)DAT_00516db0, (int *)DAT_00516e48, 0);
            v = 1;
        } else if (bits & 0x4000) {
            if (c->_kind == 0) {
                s4 = AREAS(host, c->_plNo)[cur];
                if (s4->_isUse == 1) {
                    uniq = 1;
                    for (i = 0; i < 4; i++) {
                        char *y;
                        char *x;
                        beNDMWDegiData *o;
                        if (i == c->_plNo) continue;
                        o = DEGI(host, i);
                        if (o->_isUse != 1) continue;
                        if (o->_id != s4->_id) continue;
                        x = (char *)o->_dmName;
                        y = (char *)s4->_dmName;
                        if (x == 0 || y == 0) continue;
                        if (strcmp(x, y) == 0) { uniq = 0; break; }
                    }
                    if (uniq == 1) {
                        beNDMWDegiData *d;
                        char *old;
                        char *nw2;
                        char *src;
                        DEGI(host, c->_plNo)->_isUse = 1;
                        DEGI(host, c->_plNo)->_id = s4->_id;
                        d = DEGI(host, c->_plNo);
                        src = (char *)s4->_dmName;
                        if (g_stringPool[0] == 0) {
                            void *q = (void *)FUN_002eb010(16);
                            if (q != 0) q = ((void *)StringPool_Construct(q));
                            g_stringPool[0] = q;
                        }
                        nw2 = ((char *)StringPool_Intern(g_stringPool[0], src));
                        old = (char *)d->_dmName;
                        if (old != 0) {
                            int *hd = (int *)old - 2;
                            int rc = ((int *)old)[-1] - 1;
                            ((int *)old)[-1] = rc;
                            if (rc == 0) StringChunk_ReleaseHeader(*hd, hd);
                        }
                        d->_dmName = (int)nw2;
                        c->_isCancel = 0;
                        v = 2;
                    }
                }
            } else {
                FUN_003ee190(host, c->_plNo);
                c->_isCancel = 0;
                v = 2;
            }
        } else if (bits & 0x2000) {
            v = 4;
            c->_isCancel = 1;
        }
        if (c->_kind == 0) {
        unsigned char uniq2;
        int i2;
        beNDMWDegiData *s42;
            FUN_003d9e40((beNDMWLoadIntf2DegiState *)n->n16->n16->f0, 0, c->_svDataSelPoint);
            s42 = AREAS(host, c->_plNo)[c->_svDataSelPoint];
            if (s42->_isUse == 1) {
                uniq2 = 1;
                for (i2 = 0; i2 < 4; i2++) {
                    beNDMWDegiData *o;
                    char *x;
                    char *y;
                    if (i2 == c->_plNo) continue;
                    o = DEGI(host, i2);
                    if (o->_isUse != 1) continue;
                    if (o->_id != s42->_id) continue;
                    x = (char *)o->_dmName;
                    y = (char *)s42->_dmName;
                    if (x == 0 || y == 0) continue;
                    if (strcmp(x, y) == 0) { uniq2 = 0; break; }
                }
                if (uniq2 == 1) {
                    if (c->_mesKind != 0) { c->_mesKind = 0; beNDMWLoadIntf2MesWin__RequestMessage(h40, (c->_plNo << 16) | 0x513); }
                } else if (c->_mesKind != 1) {
                    c->_mesKind = 1; beNDMWLoadIntf2MesWin__RequestMessage(h40, (c->_plNo << 16) | 0x515);
                }
            } else if (c->_mesKind != 0) {
                c->_mesKind = 0; beNDMWLoadIntf2MesWin__RequestMessage(h40, (c->_plNo << 16) | 0x513);
            }
        }
        break;
    }
    case 1:
        if (c->_kind == 0) {
            if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)n->n16->n16->f0)) & 0xFF) != 1) break;
        }
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a) & 0xFF) == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (int *)DAT_00516db0, (int *)(DAT_004cc840[c->_svDataSelPoint]), 0);
            v = 0;
        }
        break;
    case 2:
        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516db0, (const char *)(DAT_004cc850[c->_svDataSelPoint]), 1);
        c->_isSelCur = 0;
        v = 3;
        break;
    case 3:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a) & 0xFF) == 1) v = 6;
        break;
    case 4:
        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516db0, (const char *)SQ_CANCEL, 1);
        c->_isSelCur = 0;
        v = 5;
        break;
    case 5:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a) & 0xFF) == 1) v = 6;
        break;
    case 6:
        r = 1;
        break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}

unsigned char beNDMWLoadIntf2DataSelIntf__CloseAll(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    int a = c->_comMdlCtrl;
    int b = c->_textOrder;
    K *n = (K *)c->_statDisp;
    unsigned char r = 0;
    int v;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    switch (v) {
    case 0:
        if (c->_isSaveArea == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d70, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d80, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d90, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516da0, (const char *)SQ_CLOSE, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 0);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 2);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 3);
            c->_isSaveArea = 0;
        }
        if (c->_isUpStatWin == 1) {
            beNDMWLoadIntf2DegiState__RequestClose((beNDMWLoadIntf2DegiState *)n->n16->n16->f0, 0);
        }
        if (c->_isDownStatWin == 1) {
            beNDMWLoadIntf2DegiState__RequestClose((beNDMWLoadIntf2DegiState *)n->n16->n16->f4, 0);
        }
        if (c->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516db0, (const char *)SQ_CLOSE, 1);
        }
        v++;
        break;
    case 1:
        if (c->_isUpStatWin == 1) {
            if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)n->n16->n16->f0)) & 0xFF) != 1) break;
            c->_isUpStatWin = 0;
        }
        if (c->_isDownStatWin == 1) {
            if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)n->n16->n16->f4)) & 0xFF) != 1) break;
            c->_isDownStatWin = 0;
        }
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a) & 0xFF) == 1) {
            r = 1;
            v++;
        }
        break;
    case 2:
        r = 1;
        break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}

unsigned char beNDMWLoadIntf2DataSelIntf__ShowSelectedStatus(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    int a = c->_comMdlCtrl;
    int b = c->_textOrder;
    beNDMWLoadIntf2DegiStateCtrl *n = (beNDMWLoadIntf2DegiStateCtrl *)c->_statDisp;
    unsigned char r = 0;
    int v;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    switch (v) {
    case 0:
        if (c->_isSaveArea == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d70, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d80, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d90, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516da0, (const char *)SQ_CLOSE, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 0);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 2);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 3);
            c->_isSaveArea = 0;
        }
        v++;
        break;
    case 1:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a) & 0xFF) == 1) {
            v++;
            beNDMWLoadIntf2DegiState__RequestOpen((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)n->_statDataList)->_data)[1]), 0, c->_svDataSelPoint);
            c->_isDownStatWin = 1;
        }
        break;
    case 2:
        if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)n->_statDataList)->_data)[1]))) & 0xFF) == 1) {
            r = 1;
            v++;
        }
        break;
    case 3: break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}

unsigned char beNDMWLoadIntf2DataSelIntf__RestoreSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    beNDMWLoadCtrl2CommonIntf *bk = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    Ob_3dc590 *ob = (Ob_3dc590 *)arg0->_comMdlCtrl;
    int snd = arg0->_textOrder;
    beNDMWLoadIntf2DegiStateCtrl *nd = (beNDMWLoadIntf2DegiStateCtrl *)arg0->_statDisp;
    unsigned char r = 0;
    int v;
    switch (arg1) {
    default: v = arg0->_st0; break;
    case 1: v = arg0->_st1; break;
    case 2: v = arg0->_st2; break;
    case 3: v = arg0->_st3; break;
    }
    switch (v) {
    case 0:
        beNDMWLoadIntf2DegiState__RequestClose((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)nd->_statDataList)->_data)[1]), 0);
        arg0->_isDownStatWin = 0;
        v++;
        break;
    case 1:
        if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)nd->_statDataList)->_data)[1]))) & 0xFF) == 1) v++;
        break;
    case 2: {
        int i;
        int off = 0;
        for (i = 0; i < 4; i++) {
            beNDMWDegiData *it = SLOT_DEGI(bk, arg0->_plNo, i);
            if (it->_isUse == 1) {
                int j = 0;
                int k = 0;
                for (; k < 16; k++) {
                    if (strcmp(((Ent_3dc590 *)g_playerModelRow)[k].name, it->_dmkind) == 0) { j = k; break; }
                }
                float v1[3];
                v1[0] = ob->x; v1[1] = ob->y; v1[2] = ob->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)ob, (int)arg0->_plNo, (const char *)DAT_004cc830[i], (const char *)(((Ent_3dc590 *)g_playerModelRow)[j].val), (float *)v1, 1);
            } else {
                float v2[3];
                v2[0] = ob->x; v2[1] = ob->y; v2[2] = ob->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)ob, (int)arg0->_plNo, (const char *)DAT_004cc830[i], (const char *)DAT_00516cf8, (float *)v2, 1);
            }
        }
        arg0->_isSaveArea = 1;
        v++;
        break;
    }
    case 3:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)ob) & 0xFF) == 1) {
            int i;
            for (i = 0; i < 4; i++) {
                beNDMWDegiData *it = SLOT_DEGI(bk, arg0->_plNo, i);
                if (it->_isUse == 1) {
                    int a = igObject_GetAllocator(arg0);
                    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beUnicodeObj> rp(FUN_003614f0(a));
                    beUnicodeObj_AllocateBuffer(rp.p, 8);
                    unsigned short *dst = (unsigned short *)rp.p->_buffer;
                    unsigned short *src = (unsigned short *)it->_dmNameUni;
                    int n;
                    for (n = 0; n < 8; n++) {
                        dst[n] = src[n + 1];
                        if (dst[n] == 0) break;
                    }
                    for (; n < 8; n++) dst[n] = 0;
                    FUN_003ec120(snd, DAT_00516dc8, arg0->_plNo, i, rp.p, 1, 0);
                } else {
                    beNDMWLoadIntf2TextOrder_PublishIdLines(snd, (arg0->_plNo << 16) | 0x300 | i, 0);
                }
            }
            v++;
        }
        break;
    case 4:
        r = 1;
        break;
    }
    switch (arg1) {
    default:
        arg0->_st0 = v; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = v; arg0->_st3 = 0; arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = v; arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = v;
        break;
    }
    return r;
}

unsigned char beNDMWLoadIntf2DataSelIntf__CloseStatusWindows(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    Link *n = (Link *)c->_statDisp;
    unsigned char r = 0;
    int v;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    switch (v) {
    case 0:
        beNDMWLoadIntf2DegiState__RequestClose((beNDMWLoadIntf2DegiState *)n->inner->pair->a, 0);
        beNDMWLoadIntf2DegiState__RequestClose((beNDMWLoadIntf2DegiState *)n->inner->pair->b, 0);
        c->_isDownStatWin = 0;
        v++;
        c->_isUpStatWin = 0;
        break;
    case 1:
        if ((((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)n->inner->pair->a)) & 0xFF) == 1 && (((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)n->inner->pair->b)) & 0xFF) == 1) {
            v++;
        }
        break;
    case 2:
        r = 1;
        break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}

/* Owning stack reference to the area's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

unsigned char beNDMWLoadIntf2DataSelIntf__OpenSlotSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    beNDMWLoadCtrl2CommonIntf *spF0;
    beNDMWLoadIntf2DegiStateCtrl *spE0;
    unsigned char r;
    beNDMWLoadIntf2ComMdlCtrl *s0;
    int s2;
    int mode;
    int i;
    beNDMWDegiData *it;
    int off;
    unsigned short *dst0;
    unsigned short *src;
    int n;
    unsigned short *dst;
    int al;
    int a0;
    spF0 = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    s0 = (beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl;
    r = 0;
    s2 = arg0->_textOrder;
    spE0 = (beNDMWLoadIntf2DegiStateCtrl *)arg0->_statDisp;
    switch (arg1) {
    default: mode = arg0->_st0; break;
    case 1: mode = arg0->_st1; break;
    case 2: mode = arg0->_st2; break;
    case 3: mode = arg0->_st3; break;
    }
    switch (mode) {
    case 0: {
        beNDMWDegiData *it;
        int i;
        int s5;
        int s4;
        int *s3;
        int off;
        i = 0;
        off = 0;
        s3 = DAT_004cc830;
        do {
            it = *(beNDMWDegiData **)((char *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)spF0->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_saveDataList)->_data + off);
            if (it->_isUse == 1) {
                V3_3dcc60 va;
                s5 = 0;
                for (s4 = 0; s4 < 16; s4++) {
                    if (strcmp(g_playerModelRow[s4].name, it->_dmkind) == 0) { s5 = s4; break; }
                }
                va.x = s0->_pos[0]; va.y = s0->_pos[1]; va.z = s0->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s3), (const char *)g_playerModelRow[s5].val, (float *)&va, 1);
            } else {
                V3_3dcc60 vb;
                vb.x = s0->_pos[0]; vb.y = s0->_pos[1]; vb.z = s0->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s3), (const char *)DAT_00516cf8, (float *)&vb, 1);
            }
            i += 1;
            off += 4;
            s3 += 1;
        } while (i < 4);
        arg0->_isSaveArea = 1;
        beNDMWLoadIntf2DegiState__RequestOpen((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]), 1, (int)arg0->_plNo);
        arg0->_isUpStatWin = 1;
        mode += 1;
        break;
    }
    case 1:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)s0) & 0xFF) == 1 && (((int)beNDMWLoadIntf2DegiState__Update((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]))) & 0xFF) == 1) {
            i = 0;
            off = 0;
            mode += 1;
            do {
                it = *(beNDMWDegiData **)((char *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)spF0->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_saveDataList)->_data + off);
                if (it->_isUse == 1) {
                    al = igObject_GetAllocator(arg0, arg0->_plNo);
                    if (GPR_00554c14 != 0) a0 = al; else a0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beUnicodeObj> rcs((beUnicodeObj *)((int)FUN_003614f0(a0)));
                    beUnicodeObj_AllocateBuffer(rcs.p, 8);
                    src = (unsigned short *)it->_dmNameUni;
                    n = 0;
                    dst0 = (unsigned short *)rcs.p->_buffer;
                    dst = dst0;
                    for (n = 0; n < 8; n++) {
                        *dst = src[1];
                        if (*dst == 0) break;
                        src++;
                        dst++;
                    }
                    for (; n < 8; n++) dst0[n] = 0;
                    FUN_003ec120(s2, DAT_00516dc8, arg0->_plNo, i, rcs.p, 1, 0);
                } else {
                    beNDMWLoadIntf2TextOrder_PublishIdLines(s2, (arg0->_plNo << 0x10) | 0x300 | i, 0);
                }
                i += 1;
                off += 4;
            } while (i < 4);
        }
        break;
    case 2:
        r = 1;
        break;
    }
    switch (arg1) {
    default: arg0->_st0 = mode; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0; break;
    case 1: arg0->_st1 = mode; arg0->_st3 = 0; arg0->_st2 = 0; break;
    case 2: arg0->_st2 = mode; arg0->_st3 = 0; break;
    case 3: arg0->_st3 = mode; break;
    }
    return r;
}

bool beNDMWLoadIntf2DataSelIntf__OpenAreaCursor(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    float v0[3], v1[3], v2[3], v3[3];
    int s2;
    bool s1;
    int s0;
    P *a0;
    a0 = (P *)arg0->_comMdlCtrl;
    s2 = arg0->_mesWin;
    s1 = 0;
    switch (arg1) {
    default: s0 = arg0->_st0; break;
    case 1: s0 = arg0->_st1; break;
    case 2: s0 = arg0->_st2; break;
    case 3: s0 = arg0->_st3; break;
    }
    switch (s0) {
    case 0:
        if (arg0->_isSelCur == 0) {
            switch (arg0->_svDataSelPoint) {
            case 0: v0[0] = a0->x; v0[1] = a0->y; v0[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)arg0->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516e70, (float *)v0, 1); break;
            case 1: v1[0] = a0->x; v1[1] = a0->y; v1[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)arg0->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516e80, (float *)v1, 1); break;
            case 2: v2[0] = a0->x; v2[1] = a0->y; v2[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)arg0->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516e90, (float *)v2, 1); break;
            case 3: v3[0] = a0->x; v3[1] = a0->y; v3[2] = a0->z; beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)arg0->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516ea0, (float *)v3, 1); break;
            }
            arg0->_isSelCur = 1;
        }
        s0 += 1;
        break;
    case 1:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a0) & 0xFF) == 1) {
            s0 += 1;
            if (arg0->_kind == 0) beNDMWLoadIntf2MesWin__RequestMessage(s2, (arg0->_plNo << 0x10) | 0x513);
            else beNDMWLoadIntf2MesWin__RequestMessage(s2, (arg0->_plNo << 0x10) | 0x503);
        }
        break;
    case 2:
        s1 = 1;
        break;
    }
    switch (arg1) {
    default:
        arg0->_st0 = s0; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = s0; arg0->_st3 = 0; arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = s0; arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = s0;
        break;
    }
    return s1;
}

unsigned char beNDMWLoadIntf2DataSelIntf__CloseSaveArea(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    int s3; int s2; bool s1; int s0;

    s3 = arg0->_comMdlCtrl;
    s2 = arg0->_textOrder;
    s1 = 0;
    switch (arg1) {
    default:
        s0 = arg0->_st0;
        break;
    case 1:
        s0 = arg0->_st1;
        break;
    case 2:
        s0 = arg0->_st2;
        break;
    case 3:
        s0 = arg0->_st3;
        break;
    }
    switch (s0) {
    case 0:
        if (arg0->_isSaveArea == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516d70, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516d80, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516d90, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516da0, (const char *)SQ_CLOSE, 1);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 0);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 1);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 2);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 3);
            arg0->_isSaveArea = 0;
        }
        if (arg0->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516db0, (const char *)SQ_CLOSE, 1);
        }
        s0 += 1;
        break;
    case 1:
        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)s3)) == 1) {
            s1 = 1;
            s0 += 1;
        }
        break;
    case 2:
        s1 = 1;
        break;
    }
    switch (arg1) {
    default:
        arg0->_st0 = s0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = s0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = s0;
        arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = s0;
        break;
    }
    return s1;
}

/* Owning stack reference to the area's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

int beNDMWLoadIntf2DataSelIntf__ShowAccessPlayers(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    beNDMWLoadCtrl2CommonIntf *ctx = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    int s4 = arg0->_comMdlCtrl;
    int s8 = arg0->_textOrder;
    int sel;
    switch (arg1) {
    default:
        sel = arg0->_st0;
        break;
    case 1:
        sel = arg0->_st1;
        break;
    case 2:
        sel = arg0->_st2;
        break;
    case 3:
        sel = arg0->_st3;
        break;
    }
    int i;
    igIntList *lst = (igIntList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ctx->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_accessPlList;
    for (i = 0; i < lst->_count; i++) {
        {
            int s3 = ((int *)lst->_data)[i];
            int j = 0;
            do {
                beNDMWDegiData *e = ((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ctx->_flagWork)->_data)[s3]->_haveSaveData)->_saveDataList)->_data)[j];
                if (e->_isUse == 1) {
                    int k = 0;
                    int m;
                    for (m = 0; m < 16; m++) {
                        if (strcmp(((Tab *)g_playerModelRow)[m].name, e->_dmkind) == 0) { k = m; break; }
                    }
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)s4, s3, (int *)DAT_004cc830[j], ((Tab *)g_playerModelRow)[k].f8, 0);
                    int a = igObject_GetAllocator(arg0);
                    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beUnicodeObj> r(FUN_003614f0(a));
                    beUnicodeObj_AllocateBuffer(r.p, 8);
                    unsigned short *base;
                    unsigned short *src;
                    unsigned short *dp;
                    int n;
                    src = (unsigned short *)e->_dmNameUni;
                    base = (unsigned short *)r.p->_buffer;
                    n = 0;
                    dp = base;
                    for (n = 0; n < 8; n++) {
                        *dp = src[1];
                        if (*dp == 0) break;
                        src++;
                        dp++;
                    }
                    for (; n < 8; n++) base[n] = 0;
                    FUN_003ec120(s8, DAT_00516dc8, s3, j, r.p, 1, 0);
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)s4, s3, (int *)DAT_004cc830[j], DAT_00516cf8, 0);
                    beNDMWLoadIntf2TextOrder_PublishIdLines(s8, (s3 << 16) | 0x300 | j, 0);
                }
                j++;
            } while (j < 4);
        }
    }
    switch (arg1) {
    default:
        arg0->_st0 = sel;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = sel;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = sel;
        arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = sel;
        break;
    }
    return 1;
}

void beNDMWLoadIntf2Diffselect__Init(beNDMWLoadIntf2Diffselect *arg0, int arg1, int arg2) {
    arg0->_selectPoint = 0;
    arg0->_result = 0;
    arg0->_plNo = arg2;
    arg0->_result = 0;
    arg0->_kind = arg1;
    arg0->_isEnd = 0;
    arg0->_isCancel = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    switch (arg0->_kind) { case 0: arg0->_maxSel = 2; break; case 1: arg0->_maxSel = 3; break; }
}

unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, unsigned char usePad) {
    float v0[3], v1[3];
    int up, down; /* matching construct: declaration-order search — up/down declared first keep the pad repeat word in a2 */
    int buttons, h, e;
    bool u, d;
    VecSrc *a0;
    void *s1;
    void *s0;
    if (self->_isEnd == 1) return 1;
    a0 = (VecSrc *)self->_comMdlCtrl;
    s1 = (void *)self->_textOrder;
    s0 = (void *)self->_mesWin;
    buttons = 0;
    up = 0;
    down = 0;
    if ((usePad & 0xff) == 1) {
        bePadData *pad = bePadManager_GetPadForPlayer(self->_padManager, self->_plNo);
        buttons = pad->_trigger;
        e = pad->_repeat;
        h = pad->_lTrg | pad->_lRpt;
        u = 1;
        if (h & 1) goto Lu;
        if ((buttons | e) & 0x10) goto Lu;
        u = 0;
    Lu:
        up = u & 0xff;
        d = (h & 4) || ((buttons | e) & 0x40);
        down = d;
    }
    switch (self->_st0) {
    case 0:
        switch (self->_st1) {
        case 0:
            switch (self->_kind) {
            case 0:
                v0[0] = a0->x; v0[1] = a0->y; v0[2] = a0->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)j_linewin02, (const char *)SQ_OPEN, (float *)v0, 1);
                break;
            case 1:
                v1[0] = a0->x; v1[1] = a0->y; v1[2] = a0->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)SQ_OPEN, (float *)v1, 1);
                break;
            }
            self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a0) & 0xff) == 1) {
                switch (self->_kind) {
                case 0: beNDMWLoadIntf2TextOrder_PublishIdLines(s1, (self->_plNo << 16) | 0x402, 0); break;
                case 1: beNDMWLoadIntf2TextOrder_PublishIdLines(s1, (self->_plNo << 16) | 0x403, 0); break;
                }
                beNDMWLoadIntf2MesWin__RequestMessage(s0, (self->_plNo << 16) | 0x404);
                self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            }
            break;
        }
        break;
    case 1:
        switch (self->_st1) {
        case 0:
            if (up != 0) {
                self->_selectPoint = self->_selectPoint - 1;
                if (self->_selectPoint < 0) { self->_selectPoint = 0; }
                else {
                    switch (self->_kind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)j_linewin02, (int *)SQ_LINEUP00, 1);
                        break;
                    case 1:
                        if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516ec0, (int *)SQ_LINEUP00, 1);
                        else beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516ec0, (int *)DAT_00516ee0, 1);
                        break;
                    }
                    self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
                }
            } else if (down != 0) {
                self->_selectPoint = self->_selectPoint + 1;
                if (self->_maxSel - 1 < self->_selectPoint) { self->_selectPoint = self->_maxSel - 1; }
                else {
                    switch (self->_kind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)j_linewin02, (int *)SQ_LINEDW01, 1);
                        break;
                    case 1:
                        if (self->_selectPoint == 1) beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516ec0, (int *)SQ_LINEDW01, 1);
                        else beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516ec0, (int *)DAT_00516f00, 1);
                        break;
                    }
                    self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
                }
            } else if (buttons & 0x4000) {
                self->_result = self->_selectPoint;
                self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            } else if (buttons & 0x2000) {
                self->_isCancel = 1;
                self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            }
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a0) & 0xff) == 1) { self->_st1 = 0; self->_st3 = 0; self->_st2 = 0; }
            break;
        }
        break;
    case 2:
        switch (self->_st1) {
        case 0:
            switch (self->_kind) {
            case 0:
                TextOrder_PublishLineListOnly(s1, (self->_plNo << 16) | 0x402);
                if (self->_isCancel == 0) {
                    if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)j_linewin02, (const char *)SQ_LINEON00, 1);
                    else beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)j_linewin02, (const char *)SQ_LINEON01, 1);
                } else beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)j_linewin02, (const char *)SQ_CANCEL, 1);
                break;
            case 1:
                TextOrder_PublishLineListOnly(s1, (self->_plNo << 16) | 0x403);
                if (self->_isCancel == 0) {
                    switch (self->_selectPoint) {
                    case 0: beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)SQ_LINEON00, 1); break;
                    case 1: beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)SQ_LINEON01, 1); break;
                    case 2: beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)DAT_00516e28, 1); break;
                    }
                } else beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)SQ_CANCEL, 1);
                break;
            }
            self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)a0) & 0xff) == 1) self->_isEnd = 1;
            break;
        }
        break;
    }
    return self->_isEnd;
}

void beNDMWLoadIntf2NameSel__Init(beNDMWLoadIntf2NameSel *arg0, unsigned char arg1) {
    struct NameSelTail *T = (struct NameSelTail *)arg0;
    int i;
    int j;
    struct Q *q;
    struct H *h;
    arg0->_langID = 1;
    switch (arg0->_langID) {
    case 0:
        arg0->_nameMojiMax = 6; arg0->_tateMax = 24; arg0->_tateMin = 0;
        break;
    case 1:
        arg0->_nameMojiMax = 8; arg0->_tateMax = 4; arg0->_tateMin = 0;
        break;
    default:
        arg0->_nameMojiMax = 8; arg0->_tateMax = 30; arg0->_tateMin = 24;
        break;
    }
    if (arg1 == 1) {
        T->c254 = 0; T->c255 = 0; T->c256 = 0; T->c257 = 0; T->c258 = 0; T->c259 = 0;
        arg0->_nameCurPos = -1;
        i = 0;
        q = (struct Q *)arg0;
        do {
            q->a = 0; q->b = 0; q->c = 0;
            i += 3;
            q = (struct Q *)((char *)q + 12);
        } while (i < 9);
        j = 0;
        h = (struct H *)arg0;
        do {
            h->a = 0; h->b = 0; h->c = 0;
            j += 3;
            h = (struct H *)((char *)h + 6);
        } while (j < 9);
    }
    switch (arg0->_langID) {
    case 0:
        if (arg0->_nameCurPos == -1) { T->rows[0].a = 4; T->rows[0].b = 0; T->rows[0].c = 0; arg0->_nameCurPos = 0; }
        break;
    case 1:
        if (arg0->_nameCurPos == -1) { T->rows[0].a = 0; T->rows[0].b = 0; T->rows[0].c = 0; arg0->_nameCurPos = 0; }
        break;
    default:
    case 2:
        if (arg0->_nameCurPos == -1) { T->rows[0].a = 28; T->rows[0].b = 0; T->rows[0].c = 0; arg0->_nameCurPos = 0; }
        break;
    }
    arg0->_tatePoint = T->rows[arg0->_nameCurPos].a;
    arg0->_yokoPoint = T->rows[arg0->_nameCurPos].b;
    arg0->_yokoCurPos = T->rows[arg0->_nameCurPos].c;
    T->ints[arg0->_nameCurPos] = 1;
    arg0->_isEnd = 0; arg0->_isMakeName = 0; arg0->_isQuestion = 0; arg0->_isAnswer = 0; arg0->_isNameOK = 0; arg0->_isSideCur = 0;
    arg0->_st0 = 0; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0;
}

/* Owning stack reference to the slot's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

void FUN_003de480(beNDMWLoadIntf2NameSel *arg0, int arg1) {
    int s0;
    int a;
    switch (arg1) {
    case 1:
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 2);
        return;
    case 0: {
        {
        s0 = arg0->_tatePoint - 1;
        if (s0 < arg0->_tateMin) s0 = arg0->_tateMax - 1;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<Obj> r0(((Obj *)FUN_003614f0(a)));
        beUnicodeObj_AllocateBuffer(r0.p, 1);
        *(unsigned short *)r0.p->_buffer = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 0, r0.p, 1, 0);
        }
        {
        s0 = arg0->_tatePoint;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<Obj> r1(((Obj *)FUN_003614f0(a)));
        beUnicodeObj_AllocateBuffer(r1.p, 1);
        *(unsigned short *)r1.p->_buffer = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 1, r1.p, 1, 0);
        }
        {
        int n = arg0->_tatePoint + 1;
        if (n >= arg0->_tateMax) s0 = arg0->_tateMin; else s0 = n;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<Obj> r2(((Obj *)FUN_003614f0(a)));
        beUnicodeObj_AllocateBuffer(r2.p, 1);
        *(unsigned short *)r2.p->_buffer = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 2, r2.p, 1, 0);
        }
    }
    }
}

/* Owning stack reference to the slot's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

void FUN_003de7a0(beNDMWLoadIntf2NameSel *arg0, int arg1) {
    int s1;
    int s3;
    int i;
    int a;
    switch (arg1) {
    case 1:
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 2);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 3);
        TextOrder_ClearFont(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, 4);
        return;
    case 0:
        s1 = arg0->_yokoPoint;
        for (i = 0; i < 5; i++) {
            s3 = (s1 + i) % DAT_004cc860[arg0->_tatePoint].mod;
            a = igObject_GetAllocator(arg0);
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igSmartPointer<beUnicodeObj> r(FUN_003614f0(a));
            beUnicodeObj_AllocateBuffer(r.p, 1);
            *(unsigned short *)r.p->_buffer = DAT_004cc860[arg0->_tatePoint].v[s3];
            FUN_003ec120(arg0->_textOrder, DAT_00516f20, arg0->_ramNo, i, r.p, 1, 0);
        }
    }
}

/* Owning stack reference to a slot's value object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */


void FUN_003de990(NameSelRam *arg0, int arg1) {
    int i;
    int j;
    switch (arg0->n._langID) {
    case 0:
        switch (arg1) {
        case 1:
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 0);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 1);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 2);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 3);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 4);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, 5);
            return;
        case 0:
            i = 0;
            do {
                if (arg0->t.name[i] == 0) break;
                switch (arg0->t.mode[i]) {
                case 0: break;
                default: break;
                case 1: BIND(DAT_00516f30, i, 1); break;
                case 2: BIND(DAT_00516f30, i, 0); break;
                }
                i++;
            } while (i < 6);
            for (; i < 6; i++) TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f30, arg0->n._ramNo, i);
            return;
        }
        break;
    case 1:
    default:
        switch (arg1) {
        case 1:
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 0);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 1);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 2);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 3);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 4);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 5);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 6);
            TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, 7);
            return;
        case 0:
            j = 0;
            do {
                if (arg0->t.name[j] == 0) break;
                switch (arg0->t.mode[j]) {
                case 0: break;
                default: break;
                case 1: BIND(DAT_00516f40, j, 1); break;
                case 2: BIND(DAT_00516f40, j, 0); break;
                }
                j++;
            } while (j < 8);
            for (; j < 8; j++) TextOrder_ClearFont(arg0->n._textOrder, DAT_00516f40, arg0->n._ramNo, j);
            break;
        }
        break;
    }
}

void beNDMWLoadIntf2NameSel__SetAnswer(beNDMWLoadIntf2NameSel *arg0, char arg1) {
    arg0->_isNameOK = arg1;
    arg0->_isAnswer = 1;
}

/* NameSel update: one step of the name-entry state machine (_st0 selects the phase, _st1 the step
 * inside it). Phases: 0 open the windows, 1 typing (D-pad moves the cursor, Cross enters, Circle
 * erases, START leaves), 2 close, 3 question (_isQuestion until _isAnswer), 4 leave early, 5 shut
 * every window and set _isEnd. Returns _isEnd. The receiver is the reflected
 * beNDMWLoadIntf2NameSel (288 bytes registered); reflection lists its fields up to +100 and the
 * per-cell save area below is the unlisted tail of the same object (+104..), so NameSelRam is that
 * tail laid over it. */
struct Vec3f { float x, y, z; };
extern "C" char DAT_00516f50[], DAT_00516f60[], DAT_00516f70[], DAT_00516f80[], DAT_00516f98[], DAT_00516fb0[], DAT_00516fd0[];
extern "C" char DAT_00516fe8[], DAT_00516ff8[], DAT_00517008[], DAT_00517018[], DAT_00517030[], DAT_00517040[];
extern "C" char DAT_00517050[], DAT_00517060[], DAT_00517070[];
#define NS (s->n)
#define CM ((beNDMWLoadIntf2ComMdlCtrl *)NS._comMdlCtrl)
#define POS(v) { Vec3f *u = (Vec3f *)&CM->_pos; v.x = u->x; v.y = u->y; v.z = u->z; }
#define DRAWPOS(v, nm, md, fl) POS(v) beNDMWLoadIntf2ComMdlCtrl__StartAt(CM, NS._ramNo, nm, md, (float *)&v, fl);
#define LANG(A, B) switch (NS._langID) { case 0: A; break; default: case 1: B; break; }
#define LANGDRAW(b, fl) LANG(beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516ff8, (int *)b, fl), beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00517008, (int *)b, fl))
#define LANGDRAW0(b, fl) LANG(beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516ff8, b, fl), beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00517008, b, fl))
#define SETCH s->t.name[NS._nameCurPos] = DAT_004cc860[NS._tatePoint].v[(NS._yokoPoint + NS._yokoCurPos) % DAT_004cc860[NS._tatePoint].mod];
#define NEXT NS._st1++; NS._st3 = 0; NS._st2 = 0;
int beNDMWLoadIntf2NameSel__Update(NameSelRam *s, int arg1) {
    /* matching construct: declaration-order search — the order of the pad locals sets their registers */
    int trigger;
    bePadData *pad;
    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char upTmp;
    int repeat;
    unsigned char right;
    int edge;
    Vec3f pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    char buf0[80], buf1[80], buf2[80], buf3[80], buf4[80], buf5[80], buf6[80], buf7[80], buf8[80], buf9[80], buf10[80], buf11[80], buf12[80], buf13[80], buf14[80], buf15[80];
    if (NS._isEnd == 1) return 1;
    trigger = 0; up = 0; down = 0; left = 0; right = 0;
    if ((arg1 & 0xFF) == 1) {
        pad = bePadManager_GetPadForPlayer(NS._padManager, NS._ramNo);
        trigger = pad->_trigger;
        repeat = pad->_repeat;
        edge = pad->_lTrg | pad->_lRpt;
        upTmp = 1;
        if ((edge & 1) == 0 && ((trigger | repeat) & 0x10) == 0) upTmp = 0;
        up = upTmp;
        down = (edge & 4) || ((trigger | repeat) & 0x40);
        left = (edge & 8) || ((trigger | repeat) & 0x80);
        right = (edge & 2) || ((trigger | repeat) & 0x20);
    }
    switch (NS._st0) {
    case 0:
        switch (NS._st1) {
        case 0:
            POS(pos0) beNDMWLoadIntf2ComMdlCtrl__StartAt(CM, NS._ramNo, (const char *)j_digifacewin, (const char *)g_playerModelRow[NS._selDataNo].val, (float *)&pos0, 1);
            DRAWPOS(pos1, DAT_00516f50, (const char *)SQ_OPEN, 1)
            DRAWPOS(pos2, DAT_00516f60, (const char *)SQ_OPEN, 1)
            DRAWPOS(pos3, DAT_00516f70, (const char *)SQ_OPEN, 1)
            DRAWPOS(pos4, DAT_00516f80, (const char *)SQ_OPEN, 1)
            DRAWPOS(pos5, DAT_00516f98, (const char *)SQ_OPEN, 1)
            DRAWPOS(pos6, DAT_00516fb0, (const char *)SQ_OPEN, 1)
            DRAWPOS(pos7, DAT_00516fd0, (const char *)SQ_OPEN, 1)
            NS._isSideCur = 1;
            SETCH
            sprintf(buf0, DAT_00516fe8, NS._nameCurPos);
            switch (NS._langID) {
            case 0: DRAWPOS(pos8, DAT_00516ff8, buf0, 0) break;
            default: case 1: DRAWPOS(pos9, DAT_00517008, buf0, 0) break;
            }
            FUN_003de480(&NS, 0);
            FUN_003de7a0(&NS, 0);
            FUN_003de990(s, 0);
            NEXT
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM) & 0xFF) == 1) { NEXT }
            break;
        case 2:
            if (NS._nameCurPos >= NS._nameMojiMax) NS._nameCurPos = NS._nameMojiMax - 1;
            sprintf(buf1, DAT_00517018, NS._yokoCurPos);
            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f60, (int *)buf1, 1);
            NEXT
            break;
        case 3:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM) & 0xFF) == 1) { NS._st0 = 1; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 1:
        switch (NS._st1) {
        case 0:
            if (right) {
                NS._yokoCurPos++;
                if (NS._yokoCurPos >= 5) {
                    NS._yokoCurPos = 4;
                    if (DAT_004cc860[NS._tatePoint].mod > 5) {
                        NS._yokoPoint++;
                        if (NS._yokoPoint >= DAT_004cc860[NS._tatePoint].mod) NS._yokoPoint = 0;
                        if (NS._isSideCur == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fd0, (int *)SQ_ON00, 1);
                            sprintf(buf2, DAT_00517030, NS._nameCurPos);
                            LANGDRAW(buf2, 1)
                        }
                        FUN_003de7a0(&NS, 0);
                    }
                } else {
                    sprintf(buf3, DAT_00517018, NS._yokoCurPos);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f60, (int *)buf3, 1);
                    sprintf(buf4, DAT_00517030, NS._nameCurPos);
                    LANGDRAW(buf4, 1)
                }
                SETCH
                FUN_003de990(s, 0);
                NEXT
            } else if (left) {
                NS._yokoCurPos--;
                if (NS._yokoCurPos < 0) {
                    NS._yokoCurPos = 0;
                    if (DAT_004cc860[NS._tatePoint].mod > 5) {
                        NS._yokoPoint--;
                        if (0 > NS._yokoPoint) NS._yokoPoint = DAT_004cc860[NS._tatePoint].mod - 1;
                        FUN_003de7a0(&NS, 0);
                        if (NS._isSideCur == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fb0, (int *)SQ_ON00, 1);
                            sprintf(buf5, DAT_00517030, NS._nameCurPos);
                            LANGDRAW(buf5, 1)
                        }
                    }
                } else {
                    sprintf(buf6, DAT_00517018, NS._yokoCurPos);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f60, (int *)buf6, 1);
                    sprintf(buf7, DAT_00517030, NS._nameCurPos);
                    LANGDRAW(buf7, 1)
                }
                SETCH
                FUN_003de990(s, 0);
                NEXT
            } else if (up) {
                beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f98, (int *)SQ_ON00, 1);
                sprintf(buf8, DAT_00517030, NS._nameCurPos);
                LANGDRAW(buf8, 1)
                NS._tatePoint--;
                if (NS._tatePoint < NS._tateMin) NS._tatePoint = NS._tateMax - 1;
                if (DAT_004cc860[NS._tatePoint].mod > 5) {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fb0, (int *)DAT_00517040, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fd0, (int *)DAT_00517040, 0);
                    NS._isSideCur = 1;
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fb0, (int *)DAT_00517050, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fd0, (int *)DAT_00517050, 0);
                    NS._isSideCur = 0;
                }
                NS._yokoPoint = 0;
                SETCH
                NEXT
                FUN_003de990(s, 0);
                FUN_003de480(&NS, 0);
                FUN_003de7a0(&NS, 0);
            } else if (down) {
                beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f80, (int *)SQ_ON00, 1);
                sprintf(buf9, DAT_00517030, NS._nameCurPos);
                LANGDRAW(buf9, 1)
                NS._tatePoint++;
                if (NS._tatePoint >= NS._tateMax) NS._tatePoint = NS._tateMin;
                if (DAT_004cc860[NS._tatePoint].mod > 5) {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fb0, (int *)DAT_00517040, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fd0, (int *)DAT_00517040, 0);
                    NS._isSideCur = 1;
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fb0, (int *)DAT_00517050, 0);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fd0, (int *)DAT_00517050, 0);
                    NS._isSideCur = 0;
                }
                NS._yokoPoint = 0;
                SETCH
                NEXT
                FUN_003de990(s, 0);
                FUN_003de7a0(&NS, 0);
                FUN_003de480(&NS, 0);
            } else if (trigger & 0x4000) {
                if (NS._nameCurPos < NS._nameMojiMax) {
                    s->t.save[NS._nameCurPos].tate = NS._tatePoint;
                    s->t.save[NS._nameCurPos].yoko = NS._yokoPoint;
                    s->t.save[NS._nameCurPos].cur = NS._yokoCurPos;
                    s->t.mode[NS._nameCurPos] = 2;
                    SETCH
                    sprintf(buf10, DAT_00517060, NS._nameCurPos);
                    LANGDRAW(buf10, 1)
                    NS._nameCurPos++;
                    s->t.name[NS._nameCurPos + 1] = 0;
                    s->t.mode[NS._nameCurPos] = 1;
                    NS._st1 = 3; NS._st3 = 0; NS._st2 = 0;
                }
                FUN_003de990(s, 0);
            } else if (trigger & 0x2000) {
                s->t.name[NS._nameCurPos] = 0;
                NS._nameCurPos--;
                LANG(beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516ff8, (int *)DAT_00517070, 1), beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00517008, (int *)DAT_00517070, 1))
                if (NS._nameCurPos < 0) {
                    NS._nameCurPos = -1; NS._st0 = 4; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0;
                } else {
                    NS._tatePoint = s->t.save[NS._nameCurPos].tate;
                    NS._yokoPoint = s->t.save[NS._nameCurPos].yoko;
                    NS._yokoCurPos = s->t.save[NS._nameCurPos].cur;
                    SETCH
                    sprintf(buf11, DAT_00517018, NS._yokoCurPos);
                    beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f60, (int *)buf11, 1);
                    FUN_003de7a0(&NS, 0);
                    FUN_003de480(&NS, 0);
                    NS._st1 = 2; NS._st3 = 0; NS._st2 = 0;
                }
                FUN_003de990(s, 0);
            } else if (trigger & 8) {
                if (NS._nameCurPos > 0) {
                    sprintf(buf12, DAT_00517060, NS._nameCurPos);
                    LANGDRAW(buf12, 1)
                    s->t.name[NS._nameCurPos] = 0;
                    NS._nameCurPos--;
                    FUN_003de990(s, 0);
                    NS._st1 = 4; NS._st3 = 0; NS._st2 = 0;
                }
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM) & 0xFF) { NS._st1 = 0; NS._st3 = 0; NS._st2 = 0; }
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM) & 0xFF) {
                sprintf(buf13, DAT_00516fe8, NS._nameCurPos);
                LANGDRAW(buf13, 0)
                s->t.mode[NS._nameCurPos] = 1;
                FUN_003de990(s, 0);
                NS._st1 = 0; NS._st3 = 0; NS._st2 = 0;
            }
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM) & 0xFF) {
                if (NS._nameCurPos >= NS._nameMojiMax) {
                    NS._nameCurPos = NS._nameMojiMax - 1; NS._st0 = 2; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0;
                } else {
                    sprintf(buf14, DAT_00516fe8, NS._nameCurPos);
                    LANGDRAW(buf14, 0)
                    SETCH
                    FUN_003de990(s, 0);
                }
                {
                    int i;
                    for (i = NS._nameCurPos + 1; i < NS._nameMojiMax; i++) s->t.name[i] = 0;
                }
                NS._st1 = 0; NS._st3 = 0; NS._st2 = 0;
            }
            break;
        case 4:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(CM) & 0xFF) { NS._st0 = 2; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 2:
        switch (NS._st1) {
        case 0:
            LANGDRAW(SQ_LINESL00, 1)
            NEXT
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM) & 0xFF) == 1) { NS._st0 = 3; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 3:
        switch (NS._st1) {
        case 0:
            NS._isQuestion = 1;
            NS._isAnswer = 0;
            NEXT
            break;
        case 1:
            if (NS._isAnswer == 1) {
                NS._isQuestion = 0;
                if (NS._isNameOK == 1) { NEXT NS._isMakeName = 1; }
                else { NS._isMakeName = 0; NS._st1 = 4; NS._st3 = 0; NS._st2 = 0; }
            }
            break;
        case 2:
            LANGDRAW0((const char *)SQ_LINEON00, 1)
            NEXT
            break;
        case 3:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM) & 0xFF) == 1) { NS._st0 = 5; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        case 4:
            NS._tatePoint = s->t.save[NS._nameCurPos].tate;
            NS._yokoPoint = s->t.save[NS._nameCurPos].yoko;
            NS._yokoCurPos = s->t.save[NS._nameCurPos].cur;
            s->t.mode[NS._nameCurPos] = 1;
            sprintf(buf15, DAT_00516fe8, NS._nameCurPos);
            LANGDRAW(buf15, 0)
            sprintf(buf15, DAT_00517018, NS._yokoCurPos);
            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f60, (int *)buf15, 1);
            FUN_003de7a0(&NS, 0);
            FUN_003de480(&NS, 0);
            FUN_003de990(s, 0);
            NEXT
            break;
        case 5:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM) & 0xFF) == 1) { NS._st0 = 1; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 4:
        switch (NS._st1) {
        case 0:
            LANGDRAW0((const char *)SQ_CLOSE, 1)
            NEXT
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM) & 0xFF) == 1) { NS._st0 = 5; NS._st3 = 0; NS._st2 = 0; NS._st1 = 0; }
            break;
        }
        break;
    case 5:
        switch (NS._st1) {
        case 0:
            FUN_003de480(&NS, 1);
            FUN_003de7a0(&NS, 1);
            FUN_003de990(s, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, (const char *)j_digifacewin, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f70, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f50, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f60, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f80, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f98, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516fb0, (const char *)SQ_CLOSE, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516fd0, (const char *)SQ_CLOSE, 1);
            NEXT
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(CM) & 0xFF) == 1) NS._isEnd = 1;
            break;
        }
        break;
    }
    return NS._isEnd;
}
#undef NS
#undef CM
#undef POS
#undef DRAWPOS
#undef LANG
#undef LANGDRAW
#undef LANGDRAW0
#undef SETCH
#undef NEXT

void beNDMWLoadIntf2SelSlot__Reset(beNDMWLoadIntf2SelSlot *arg0) {
    arg0->_isOpen = 0;
    arg0->_isCansel = 0;
    arg0->_isEnd = 0;
    arg0->_isSelect = 0;
    arg0->_isEnd = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

void beNDMWLoadIntf2SelSlot__Init(beNDMWLoadIntf2SelSlot *arg0) {
    int temp_a1;
    beNDMWLoadCtrl2CommonIntf *temp_s0;

    temp_s0 = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    beNDMWLoadIntf2SelSlot__Reset((beNDMWLoadIntf2SelSlot *)((beNDMWLoadIntf2SelSlot *)arg0));
    arg0->_selPoint = 0;
    temp_a1 = temp_s0->_kindHard;
    switch (temp_a1) {
    case 0:
        arg0->_selMax = 5;
        arg0->_kindHard = 0;
        return;
    case 1:
        arg0->_selMax = 2;
        arg0->_kindHard = 1;
        return;
    case 2:
        arg0->_selMax = 9;
        arg0->_kindHard = 2;
        break;
    }
}

/* _commonIntf -> _mcUtilCtrl -> _slot is the memory-card slot list; _isConnect is the per-slot card-present flag. */




unsigned char beNDMWLoadIntf2SelSlot__Open(beNDMWLoadIntf2SelSlot *self, int mark) {
    float va[3], vb[3], vc[3], vd[3], ve[3], vf[3];
    float v0a[3], v0b[3], v0c[3], v0d[3], v0e[3], v0f[3];
    beNDMWLoadCtrl2CommonIntf *ci;
    Own *o;
    TE *tb2;
    TE *tbl;
    int i;
    int j;
    beNDMWMcSlotList *ml;
    int to;
    if (self->_st0 != 0) {
        return 0;
    }
    ci = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    /* matching construct: variant search — the 'case 0:' label (its compare folds away) gives the default block a
       second edge, so the phase switch materialises its own compare constants */
    switch (self->_kindHard) {
    case 0:
    default:
        switch (self->_st1) {
        case 0:
            if (mark != -1) {
                self->_selPoint = mark;
            }
            if (MC_UTIL(ci)->_isMtap == 0) {
                o = (Own *)self->_comMdlCtrl; va[0] = o->pos.x; va[1] = o->pos.y; va[2] = o->pos.z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517118, (const char *)DAT_00517128, va, 1);
                self->_mode = 0;
            } else {
                o = (Own *)self->_comMdlCtrl; vb[0] = o->pos.x; vb[1] = o->pos.y; vb[2] = o->pos.z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517118, (const char *)DAT_00517138, vb, 1);
                self->_mode = 1;
            }
            o = (Own *)self->_comMdlCtrl; vc[0] = o->pos.x; vc[1] = o->pos.y; vc[2] = o->pos.z;
            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517150, (const char *)SQ_OPEN, vc, 1);
            self->_isReOpenReq = 0;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl) & 0xFF) == 1) {
                if (self->_mode == 0) {
                    tbl = DAT_004cd090;
                    o = (Own *)self->_comMdlCtrl; vd[0] = o->pos.x; vd[1] = o->pos.y; vd[2] = o->pos.z;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517160, (const char *)(tbl[self->_selPoint].name), vd, 1);
                    for (i = 0; i < 2; i++) {
                        if (MC_SLOT(MC_SLOTS(ci), tbl[i].mark)->_isConnect == 1) {
                            switch (i) {
                            case 0:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; ve[0] = o->pos.x; ve[1] = o->pos.y; ve[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00517180, ve, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517180, 0);
                                }
                                break;
                            case 1:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; vf[0] = o->pos.x; vf[1] = o->pos.y; vf[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170, (const char *)DAT_00517190, vf, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00517190, 0);
                                }
                                break;
                            }
                        }
                    }
                    to = self->_textOrder;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x100C, 0);
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1100, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                    ml = MC_SLOTS(ci);
                    if (MC_SLOT(ml, tbl[self->_selPoint].mark)->_isConnect != 1) {
                        self->_mcStat = 0;
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x102E, 0);
                    } else {
                        self->_mcStat = 1;
                        TextOrder_PublishLineListOnly(to, (self->_ramNo << 16) | 0x102E);
                    }
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                } else {
                    tb2 = DAT_004cd060;
                    o = (Own *)self->_comMdlCtrl; v0a[0] = o->pos.x; v0a[1] = o->pos.y; v0a[2] = o->pos.z;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517160, (const char *)(tb2[self->_selPoint].name), v0a, 1);
                    for (j = 0; j < 5; j++) {
                        if (MC_SLOT(MC_SLOTS(ci), tb2[j].mark)->_isConnect == 1) {
                            switch (j) {
                            case 0:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0b[0] = o->pos.x; v0b[1] = o->pos.y; v0b[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0, (const char *)DAT_005171b0, v0b, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_005171b0, 0);
                                }
                                break;
                            case 1:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0c[0] = o->pos.x; v0c[1] = o->pos.y; v0c[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0, (const char *)DAT_005171c0, v0c, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_005171c0, 0);
                                }
                                break;
                            case 2:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0d[0] = o->pos.x; v0d[1] = o->pos.y; v0d[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0, (const char *)DAT_005171d0, v0d, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_005171d0, 0);
                                }
                                break;
                            case 3:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0e[0] = o->pos.x; v0e[1] = o->pos.y; v0e[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0, (const char *)DAT_005171e0, v0e, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_005171e0, 0);
                                }
                                break;
                            case 4:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0f[0] = o->pos.x; v0f[1] = o->pos.y; v0f[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00517190, v0f, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517190, 0);
                                }
                                break;
                            }
                        }
                    }
                    to = self->_textOrder;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x100C, 0);
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1102, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1103, 0);
                        break;
                    case 2:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1104, 0);
                        break;
                    case 3:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1105, 0);
                        break;
                    case 4:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                    ml = MC_SLOTS(ci);
                    if (MC_SLOT(ml, tb2[self->_selPoint].mark)->_isConnect != 1) {
                        self->_mcStat = 0;
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x102E, 0);
                    } else {
                        self->_mcStat = 1;
                        TextOrder_PublishLineListOnly(to, (self->_ramNo << 16) | 0x102E);
                    }
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            }
            break;
        case 2:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl) & 0xFF) == 1) {
                self->_isOpen = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            }
            break;
        }
        break;
    case 1:
    case 2:
        break;
    }
    return self->_isOpen;
}

unsigned char beNDMWLoadIntf2SelSlot__UpdateSelection(beNDMWLoadIntf2SelSlot *self, unsigned char usePad, unsigned char checkDone) {
    beNDMWLoadCtrl2CommonIntf *owner;
    bePadData *pad;
    int held;
    int h1;
    int e;
    unsigned char t;
    unsigned char bU;
    unsigned char bD;
    unsigned char bL;
    unsigned char bR;
    struct OptEnt *tbl;
    int i;
    struct OptEnt *ent;
    beNDMWMcSlotList *ls;
    int wa;
    int wb;
    int wc;
    if (checkDone == 1) {
        if (self->_st0 != 1) {
            return 0;
        }
        if (self->_isSelect == 1) {
            return 1;
        }
    }
    owner = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    held = 0;
    bU = 0;
    bD = 0;
    bL = 0;
    bR = 0;
    if (usePad == 1) {
        pad = bePadManager_GetPadForPlayer(self->_padManager, self->_ramNo);
        held = pad->_trigger;
        h1 = pad->_repeat;
        e = pad->_lTrg | pad->_lRpt;
        t = 1;
        if ((e & 1) == 0 && ((held | h1) & 0x10) == 0)
            t = 0;
        bU = t;
        bD = ((e & 4) != 0) || (((held | h1) & 0x40) != 0);
        bL = ((e & 8) != 0) || (((held | h1) & 0x80) != 0);
        bR = ((e & 2) != 0) || (((held | h1) & 0x20) != 0);
    }
    switch (self->_kindHard) {
    default: {
        if (self->_mode == 0) {
            tbl = ((struct OptEnt *)DAT_004cd090);
            i = 0;
            ent = tbl;
            do {
                if (((beNDMWMcSlot **)((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot)->_data)[ent->idx]->_isConnect == 1) {
                    switch (i) {
                    case 0: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF)) {
                            struct V3 v0;
                            beNDMWLoadIntf2ComMdlCtrl *m0 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v0.x = ((float *)&m0->_pos)[0];
                            v0.y = ((float *)&m0->_pos)[1];
                            v0.z = ((float *)&m0->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00517180, (float *)&v0, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517180, 0);
                        }
                        break;
                    }
                    case 1: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170) & 0xFF)) {
                            struct V3 v1;
                            beNDMWLoadIntf2ComMdlCtrl *m1 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v1.x = ((float *)&m1->_pos)[0];
                            v1.y = ((float *)&m1->_pos)[1];
                            v1.z = ((float *)&m1->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170, (const char *)DAT_00517190, (float *)&v1, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00517190, 0);
                        }
                        break;
                    }
                    }
                } else {
                    switch (i) {
                    case 0:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    }
                }
                i++;
                ent++;
            } while (i < 2);
            wa = self->_textOrder;
            if (self->_mcStat == 0) {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                    self->_mcStat = 1;
                    TextOrder_PublishLineListOnly(wa, (self->_ramNo << 16) | 0x102E);
                }
            } else {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect != 1) {
                    self->_mcStat = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(wa, (self->_ramNo << 16) | 0x102E, 0);
                }
            }
            if (((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_isMtap == 1) {
                self->_isReOpenReq = 1;
                self->_isSelect = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                goto out;
            }
        } else {
            tbl = ((struct OptEnt *)DAT_004cd060);
            i = 0;
            ent = tbl;
            do {
                if (((beNDMWMcSlot **)((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot)->_data)[ent->idx]->_isConnect == 1) {
                    switch (i) {
                    case 0: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0) & 0xFF)) {
                            struct V3 v0;
                            beNDMWLoadIntf2ComMdlCtrl *m0 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v0.x = ((float *)&m0->_pos)[0];
                            v0.y = ((float *)&m0->_pos)[1];
                            v0.z = ((float *)&m0->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0, (const char *)DAT_005171b0, (float *)&v0, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_005171b0, 0);
                        }
                        break;
                    }
                    case 1: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0) & 0xFF)) {
                            struct V3 v1;
                            beNDMWLoadIntf2ComMdlCtrl *m1 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v1.x = ((float *)&m1->_pos)[0];
                            v1.y = ((float *)&m1->_pos)[1];
                            v1.z = ((float *)&m1->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0, (const char *)DAT_005171c0, (float *)&v1, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_005171c0, 0);
                        }
                        break;
                    }
                    case 2: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0) & 0xFF)) {
                            struct V3 v2;
                            beNDMWLoadIntf2ComMdlCtrl *m2 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v2.x = ((float *)&m2->_pos)[0];
                            v2.y = ((float *)&m2->_pos)[1];
                            v2.z = ((float *)&m2->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0, (const char *)DAT_005171d0, (float *)&v2, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_005171d0, 0);
                        }
                        break;
                    }
                    case 3: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0) & 0xFF)) {
                            struct V3 v3;
                            beNDMWLoadIntf2ComMdlCtrl *m3 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v3.x = ((float *)&m3->_pos)[0];
                            v3.y = ((float *)&m3->_pos)[1];
                            v3.z = ((float *)&m3->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0, (const char *)DAT_005171e0, (float *)&v3, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_005171e0, 0);
                        }
                        break;
                    }
                    case 4: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF)) {
                            struct V3 v4;
                            beNDMWLoadIntf2ComMdlCtrl *m4 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v4.x = ((float *)&m4->_pos)[0];
                            v4.y = ((float *)&m4->_pos)[1];
                            v4.z = ((float *)&m4->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00517190, (float *)&v4, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517190, 0);
                        }
                        break;
                    }
                    }
                } else {
                    switch (i) {
                    case 0:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    case 2:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    case 3:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    case 4:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)SQ_CLOSE, 0);
                        }
                        break;
                    }
                }
                i++;
                ent++;
            } while (i < 5);
            if (((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_isMtap == 0) {
                self->_isReOpenReq = 1;
                self->_isSelect = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                goto out;
            }
            wa = self->_textOrder;
            if (self->_mcStat == 0) {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                    self->_mcStat = 1;
                    TextOrder_PublishLineListOnly(wa, (self->_ramNo << 16) | 0x102E);
                }
            } else {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect != 1) {
                    self->_mcStat = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(wa, (self->_ramNo << 16) | 0x102E, 0);
                }
            }
        }
        switch (self->_st1) {
        case 0:
            if (self->_mode == 0) {
                if (bU) {
                    if (self->_selPoint != 0) {
                        self->_selPoint = 0;
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                        self->_st1 = self->_st1 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    }
                } else if (bD) {
                    if (self->_selPoint != 1) {
                        self->_selPoint = 1;
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                        self->_st1 = self->_st1 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    }
                } else if (held & 0x4000) {
                    ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                    if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                        FUN_003ee190(owner, self->_ramNo);
                        self->_mcSelPoint = tbl[self->_selPoint].idx;
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_005171f0, 1);
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    }
                } else if (held & 0x2000) {
                    self->_isCansel = 1;
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, SQ_CANCEL, 1);
                    self->_st1 = 2;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else if (held & 0x4000) {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                    FUN_003ee190(owner, self->_ramNo);
                    self->_mcSelPoint = tbl[self->_selPoint].idx;
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_005171f0, 1);
                    self->_st1 = 2;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else if (held & 0x2000) {
                self->_isCansel = 1;
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, SQ_CANCEL, 1);
                self->_st1 = 2;
                self->_st3 = 0;
                self->_st2 = 0;
            } else if (bU) {
                if (self->_selPoint != 0) {
                    self->_selPoint = 0;
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else if (bD) {
                int last = self->_selMax - 1;
                if (self->_selPoint != last) {
                    self->_selPoint = last;
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else {
                if (self->_selPoint != self->_selMax - 1) {
                    if (bR) {
                        self->_selPoint = self->_selPoint + 1;
                        if (self->_selPoint >= self->_selMax - 1) {
                            self->_selPoint = self->_selMax - 2;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                            self->_st1 = self->_st1 + 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        }
                    } else if (bL) {
                        self->_selPoint = self->_selPoint - 1;
                        if (self->_selPoint < 0) {
                            self->_selPoint = 0;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                            self->_st1 = self->_st1 + 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        }
                    }
                }
            }
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl)) == 1) {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, tbl[self->_selPoint].w0, 0);
                wb = self->_textOrder;
                if (self->_mode == 0) {
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1100, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                } else {
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1102, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1103, 0);
                        break;
                    case 2:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1104, 0);
                        break;
                    case 3:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1105, 0);
                        break;
                    case 4:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                }
                wc = self->_textOrder;
                if (self->_mcStat == 0) {
                    ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                    if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                        self->_mcStat = 1;
                        TextOrder_PublishLineListOnly(wc, (self->_ramNo << 16) | 0x102E);
                    }
                } else {
                    ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                    if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect != 1) {
                        self->_mcStat = 0;
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wc, (self->_ramNo << 16) | 0x102E, 0);
                    }
                }
                self->_st1 = 0;
                self->_st3 = 0;
                self->_st2 = 0;
            }
            break;
        case 2:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl)) == 1) {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, tbl[self->_selPoint].w0, 0);
                self->_isSelect = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            }
            break;
        }
    }
    case 1:
    case 2:
        break;
    }
out:
    return self->_isSelect;
}

void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *arg0) {
    Entry *tbl;
    arg0->_st0 = 1;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    arg0->_isSelect = 0;
    switch (arg0->_kindHard) {
    default:
        if (arg0->_mode == 0) tbl = (Entry *)((int *)DAT_004cd090);
        else tbl = (Entry *)((int *)DAT_004cd060);
        break;
    case 1:
    case 2:
        break;
    }
    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, arg0->_ramNo, DAT_00517160, (int *)(tbl[arg0->_selPoint].w0), 0);
}

unsigned char beNDMWLoadIntf2SelSlot__Close(beNDMWLoadIntf2SelSlot *self) {
    if (self->_st0 != 2) return 0;
    if (self->_isEnd == 1) return 1;
    switch (self->_kindHard) {
    case 0:
    default:
        switch (self->_st1) {
        case 0:
            if (self->_mode == 0) {
                int i;
                int c;
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517118, (const char *)SQ_CLOSE, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517160, (const char *)SQ_CLOSE, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517150, (const char *)SQ_CLOSE, 1);
                c = self->_textOrder;
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x100c);
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x1100);
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x102e);
                for (i = 0; i < 2; i++) {
                    switch (i) {
                    case 0:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)SQ_CLOSE, 0);
                        break;
                    case 1:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170, (const char *)SQ_CLOSE, 0);
                        break;
                    }
                }
            } else {
                int j;
                int d;
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517118, (const char *)SQ_CLOSE, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517160, (const char *)SQ_CLOSE, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517150, (const char *)SQ_CLOSE, 1);
                d = self->_textOrder;
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x100c);
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x1100);
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x102e);
                for (j = 0; j < 5; j++) {
                    switch (j) {
                    case 0:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        break;
                    case 1:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        break;
                    case 2:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        break;
                    case 3:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0, (const char *)SQ_CLOSE, 0);
                        break;
                    case 4:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)SQ_CLOSE, 0);
                        break;
                    }
                }
            }
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl)) == 1) {
                self->_isEnd = 1;
                self->_st1 = self->_st1 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
            }
            break;
        }
        break;
    case 1:
    case 2:
        break;
    }
    return self->_isEnd;
}

/* _commonIntf -> _mcUtilCtrl -> _slot is the memory-card slot list; _isConnect is the per-slot card-present flag. */


/* _comMdlCtrl: its class is not reflected; the vec3 at +28 is all this function reads. */

void beNDMWLoadIntf2SelSlot__RefreshSlotMarks(beNDMWLoadIntf2SelSlot *self, int arg1) {
    beNDMWMcSlotList *r;
    beNDMWLoadCtrl2CommonIntf *owner = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    SlotEntry *base;
    switch (self->_kindHard) {
    default: {
    if (self->_mode == 0) {
        int i;
        SlotEntry *e;
        int h;
        base = ((SlotEntry *)DAT_004cd090);
        e = base;
        for (i = 0; i < 2; i++) {
            unsigned char st = MC_SLOT(MC_SLOTS_3e3070(owner), e->idx)->_isConnect;
            if (arg1 == i) st = 0;
            if (st == 1) {
        switch (i) {
        case 0:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)))) == 0) {
                Vec3 va;
                Target *t = TGT; va.x = t->x; va.y = t->y; va.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)DAT_00517180)), (float *)&va, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (int *)(((char *)DAT_00517170)), (int *)(((char *)DAT_00517180)), 0);
            }
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (const char *)(((char *)DAT_00517170)))) == 0) {
                Vec3 vb;
                Target *t = TGT; vb.x = t->x; vb.y = t->y; vb.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)DAT_00517190)), (float *)&vb, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (int *)(((char *)DAT_00517170)), (int *)(((char *)DAT_00517190)), 0);
            }
            break;
        }
            } else {
        switch (i) {
        case 0:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (const char *)(((char *)DAT_00517170)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        }
            }
            e++;
        }
        h = self->_textOrder;
        if (self->_mcStat == 0) {
            r = MC_SLOTS_3e3070(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect == 1) {
                self->_mcStat = 1;
                TextOrder_PublishLineListOnly(h, (self->_ramNo << 16) | 0x102e);
            }
        } else {
            r = MC_SLOTS_3e3070(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect != 1) {
                self->_mcStat = 0;
                beNDMWLoadIntf2TextOrder_PublishIdLines(h, (self->_ramNo << 16) | 0x102e, 0);
            }
        }
    } else {
        int i;
        SlotEntry *e;
        int h;
        base = ((SlotEntry *)DAT_004cd060);
        e = base;
        for (i = 0; i < 5; i++) {
            unsigned char st = MC_SLOT(MC_SLOTS_3e3070(owner), e->idx)->_isConnect;
            if (arg1 == i) st = 0;
            if (st == 1) {
        switch (i) {
        case 0:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (const char *)(((char *)DAT_005171a0)))) == 0) {
                Vec3 va;
                Target *t = TGT; va.x = t->x; va.y = t->y; va.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_005171b0)), (float *)&va, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (int *)(((char *)DAT_005171a0)), (int *)(((char *)DAT_005171b0)), 0);
            }
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (const char *)(((char *)DAT_005171a0)))) == 0) {
                Vec3 vb;
                Target *t = TGT; vb.x = t->x; vb.y = t->y; vb.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_005171c0)), (float *)&vb, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (int *)(((char *)DAT_005171a0)), (int *)(((char *)DAT_005171c0)), 0);
            }
            break;
        case 2:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (const char *)(((char *)DAT_005171a0)))) == 0) {
                Vec3 vc;
                Target *t = TGT; vc.x = t->x; vc.y = t->y; vc.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_005171d0)), (float *)&vc, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (int *)(((char *)DAT_005171a0)), (int *)(((char *)DAT_005171d0)), 0);
            }
            break;
        case 3:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (const char *)(((char *)DAT_005171a0)))) == 0) {
                Vec3 vd;
                Target *t = TGT; vd.x = t->x; vd.y = t->y; vd.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_005171e0)), (float *)&vd, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (int *)(((char *)DAT_005171a0)), (int *)(((char *)DAT_005171e0)), 0);
            }
            break;
        case 4:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)))) == 0) {
                Vec3 ve;
                Target *t = TGT; ve.x = t->x; ve.y = t->y; ve.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)DAT_00517190)), (float *)&ve, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (int *)(((char *)DAT_00517170)), (int *)(((char *)DAT_00517190)), 0);
            }
            break;
        }
            } else {
        switch (i) {
        case 0:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        case 2:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        case 3:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        case 4:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)SQ_CLOSE)), 0);
            break;
        }
            }
            e++;
        }
        h = self->_textOrder;
        if (self->_mcStat == 0) {
            r = MC_SLOTS_3e3070(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect == 1) {
                self->_mcStat = 1;
                TextOrder_PublishLineListOnly(h, (self->_ramNo << 16) | 0x102e);
            }
        } else {
            r = MC_SLOTS_3e3070(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect != 1) {
                self->_mcStat = 0;
                beNDMWLoadIntf2TextOrder_PublishIdLines(h, (self->_ramNo << 16) | 0x102e, 0);
            }
        }
    }
    break;
    }
    case 1: case 2: break;
    }
}

void beNDMWLoadIntf2ComMdlCtrl__Start(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, int recordOpen) {
    /* matching construct: declaration-order sweep (40 random orders) — sets the s-register colouring of the reused parameter registers */
    void *internedInfoName;
    int newRefCount;
    StringTokenHeader *oldOpenSQHeader;
    void *oldInfoName;
    StringTokenHeader *oldNameHeader;
    void *pool2;
    int newRefCount2;
    void *pool;
    void *internedOpenSQ;
    beLoadIntf2ComMdlData *record;
    int allocator;
    void *oldOpenSQ;

    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], infoName, ramNo, &GENERATE[0]);
    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], infoName, ramNo, (int *)openSQ);
    if ((recordOpen & 0xFF) == 1) {
        int objectAllocator = igObject_GetAllocator(self);
        if (GPR_00554c14 != 0) { allocator = objectAllocator; } else { allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
        igSmartPointer<beLoadIntf2ComMdlData> newRecord(beLoadIntf2ComMdlData__Create(allocator));
        newRecord.p->_ramNo = ramNo;
        record = newRecord.p;
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        internedInfoName = (void *)(StringPool_Intern(g_stringPool[0], infoName));
        oldInfoName = (void *)(record->_infoName);
        if (oldInfoName != 0) {
            oldNameHeader = (StringTokenHeader *)((char *)oldInfoName - 8);
            newRefCount = oldNameHeader->refCount - 1;
            oldNameHeader->refCount = newRefCount;
            if (newRefCount == 0) {
                StringChunk_ReleaseHeader(oldNameHeader->owner, oldNameHeader);
            }
        }
        record->_infoName = (int)(internedInfoName);
        record = newRecord.p;
        if (g_stringPool[0] == 0) {
            pool2 = FUN_002eb010(0x10);
            if (pool2 != 0) {
                pool2 = StringPool_Construct(pool2);
            }
            g_stringPool[0] = pool2;
        }
        internedOpenSQ = (void *)(StringPool_Intern(g_stringPool[0], openSQ));
        oldOpenSQ = (void *)(record->_openSQ);
        if (oldOpenSQ != 0) {
            oldOpenSQHeader = (StringTokenHeader *)((char *)oldOpenSQ - 8);
            newRefCount2 = oldOpenSQHeader->refCount - 1;
            oldOpenSQHeader->refCount = newRefCount2;
            if (newRefCount2 == 0) {
                StringChunk_ReleaseHeader(oldOpenSQHeader->owner, oldOpenSQHeader);
            }
        }
        record->_openSQ = (int)(internedOpenSQ);
        ObjectList_AppendRetained(self->_openDataList, newRecord.p);
    }
}

/* Owning stack reference to the new open-request record: constructed from the object and released
 * on scope exit, after the open list has retained it (reference count in the low 23 bits of
 * _refCount). Its destructor is emitted out of line. */

/* Ask the MODELCTRL receivers named (infoName, ramNo) to GENERATE at `position`, then send them
 * `openSQ` as a named message. When `recordOpen` is 1 the request is also remembered as a
 * beLoadIntf2ComMdlData record (ram number, info name, open sequence) on the controller's open
 * list; the two names are interned in the shared string pool, releasing whatever the fresh record
 * held; the creating reference is released when the block ends. */
void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, float *position, int recordOpen) {
    struct { float x, y, z; } v3;
    StringTokenHeader *oldNameHeader;
    StringTokenHeader *oldOpenSQHeader;
    int newRefCount;
    int newRefCount2;
    int allocator;
    void *pool;
    void *pool2;
    void *internedOpenSQ;
    void *internedInfoName;
    void *oldInfoName;
    void *oldOpenSQ;
    beLoadIntf2ComMdlData *record;

    beMessenger_SelectReceivers(self->_messenger, &MODELCTRL[0], (int)infoName, ramNo);
    v3.x = position[0];
    v3.y = position[1];
    v3.z = position[2];
    beMessenger_AppendVec3(self->_messenger, (float*)&v3);
    beMessenger_DispatchSelected(self->_messenger, &GENERATE[0]);
    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], infoName, ramNo, openSQ);
    if ((recordOpen & 0xFF) == 1) {
        int objectAllocator = igObject_GetAllocator(self);
        if (GPR_00554c14 != 0) { allocator = objectAllocator; } else { allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
        igSmartPointer<beLoadIntf2ComMdlData> newRecord(beLoadIntf2ComMdlData__Create(allocator));
        newRecord.p->_ramNo = ramNo;
        record = newRecord.p;
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        internedInfoName = (void *)(StringPool_Intern(g_stringPool[0], infoName));
        oldInfoName = (void *)(record->_infoName);
        if (oldInfoName != 0) {
            oldNameHeader = (StringTokenHeader *)((char *)oldInfoName - 8);
            newRefCount = oldNameHeader->refCount - 1;
            oldNameHeader->refCount = newRefCount;
            if (newRefCount == 0) {
                StringChunk_ReleaseHeader(oldNameHeader->owner, oldNameHeader);
            }
        }
        record->_infoName = (int)(internedInfoName);
        record = newRecord.p;
        if (g_stringPool[0] == 0) {
            pool2 = FUN_002eb010(0x10);
            if (pool2 != 0) {
                pool2 = StringPool_Construct(pool2);
            }
            g_stringPool[0] = pool2;
        }
        internedOpenSQ = (void *)(StringPool_Intern(g_stringPool[0], openSQ));
        oldOpenSQ = (void *)(record->_openSQ);
        if (oldOpenSQ != 0) {
            oldOpenSQHeader = (StringTokenHeader *)((char *)oldOpenSQ - 8);
            newRefCount2 = oldOpenSQHeader->refCount - 1;
            oldOpenSQHeader->refCount = newRefCount2;
            if (newRefCount2 == 0) {
                StringChunk_ReleaseHeader(oldOpenSQHeader->owner, oldOpenSQHeader);
            }
        }
        record->_openSQ = (int)(internedOpenSQ);
        ObjectList_AppendRetained(self->_openDataList, newRecord.p);
    }
}

/* Only `wait == 1` (low byte) tracks the request; 2 and 255 do not, 257 does. */

/* Owning stack reference to the tracked entry: constructed from the object and released on scope
 * exit (reference count in the low 23 bits of _refCount); the open list owns the entry afterwards.
 * Its destructor is emitted out of line. */

void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int *modelName, int *sequenceName, int wait) {
    int *interned;
    beLoadIntf2ComMdlData *entry;
    int allocator;
    int objectAllocator;
    void *pool;
    int *oldToken;
    int *oldTokenHeader;
    int refCount;
    beMessenger_SendNamed(self->_messenger, MODELCTRL, modelName, slot, sequenceName);
    if ((wait & 0xFF) == WAIT_TRACKED) {
        objectAllocator = igObject_GetAllocator(self);
        if (GPR_00554c14 != 0) {
            allocator = objectAllocator;
        } else {
            allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<beLoadIntf2ComMdlData> trackedEntry((beLoadIntf2ComMdlData *)((int *)beLoadIntf2ComMdlData__Create(allocator)));
        trackedEntry.p->_ramNo = slot;
        entry = trackedEntry.p;
        /* Lazily create the shared string pool, intern the model name and
         * drop the entry's previous token (owner at -8, count at -4). */
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        interned = ((int *)StringPool_Intern(g_stringPool[0], modelName));
        oldToken = (int *)entry->_infoName;
        if (oldToken != 0) {
            oldTokenHeader = oldToken - 2;
            refCount = oldToken[-1] - 1;
            oldToken[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader(*oldTokenHeader, oldTokenHeader);
            }
        }
        entry->_infoName = (int)interned;
        entry = trackedEntry.p;
        /* Same for the sequence name. */
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        interned = ((int *)StringPool_Intern(g_stringPool[0], sequenceName));
        oldToken = (int *)entry->_openSQ;
        if (oldToken != 0) {
            oldTokenHeader = oldToken - 2;
            refCount = oldToken[-1] - 1;
            oldToken[-1] = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader(*oldTokenHeader, oldTokenHeader);
            }
        }
        entry->_openSQ = (int)interned;
        ObjectList_AppendRetained(self->_openDataList, trackedEntry.p);
        /* The stack reference is released here; the open list now owns the entry. */
    }
}

int beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, const char *infoName, const char *sqName) {
    beMessenger_SelectReceivers(self->_messenger, &MODELCTRL[0], (int)infoName, ramNo);
    beMessenger_AppendString(self->_messenger, (int)sqName);
    beMessenger_DispatchSelected(self->_messenger, &ISSEQNAME[0]);
    return beMessenger_GetBool(self->_messenger, 0);
}

/* True when the open queue is empty. _openDataList (+0x14) is a beLoadIntf2ComMdlDataList whose
 * _count (+8) is tested. */

int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self) {
    return ((beLoadIntf2ComMdlDataList *)self->_openDataList)->_count <= 0;
}

/* Owning stack reference to the new close record: constructed from the creating call and released
 * on scope exit once the close list holds its own reference (reference count in the low 23 bits of
 * _refCount). Its destructor is emitted out of line. */

/* drop one reference on an interned string token; its header (owner, refCount) sits just before the text */

void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose) {
    beMessenger_SendNamed((void *)self->_messenger, &MODELCTRL[0], infoName, ramNo, openSequence);
    if (trackClose == 1) {
        int base = igObject_GetAllocator(self); /* used as-is when GPR_00554c14 is set, else the default selector's allocator */
        int allocator;
        const char *infoNameToken;
        beLoadIntf2ComMdlData *infoOwner;
        const char *openSequenceToken;
        beLoadIntf2ComMdlData *sequenceOwner;
        if (GPR_00554c14 != 0) { allocator = base; } else { allocator = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
        igSmartPointer<beLoadIntf2ComMdlData> record((beLoadIntf2ComMdlData *)((void *)beLoadIntf2ComMdlData__Create(allocator)));
        record.p->_ramNo = ramNo;
        infoOwner = record.p;
        if (g_stringPool[0] == 0) {
            void *pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        infoNameToken = ((const char *)StringPool_Intern(g_stringPool[0], infoName));
        RELEASE_STR(infoOwner->_infoName)
        infoOwner->_infoName = (int)infoNameToken;
        sequenceOwner = record.p;
        if (g_stringPool[0] == 0) {
            void *pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        openSequenceToken = ((const char *)StringPool_Intern(g_stringPool[0], openSequence));
        RELEASE_STR(sequenceOwner->_openSQ)
        sequenceOwner->_openSQ = (int)openSequenceToken;
        ObjectList_AppendRetained((void *)self->_closeDataList, record.p);
    }
}

int beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const char *name) {
    beMessenger_SendNamed(self->_messenger, &MODELCTRL[0], name, slot, &ISRUN[0]);
    return beMessenger_GetBool(self->_messenger, 0);
}

/* True when the close queue is empty: the COMMDLCTRL record's _closeDataList (an igObjectList) has
 * no entries. Shared by the LoadIntf2 and SaveIntf screens (identical ComMdlCtrl layout). */

int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self) {
    return ((igObjectList *)self->_closeDataList)->_count <= 0;
}

void beNDMWLoadIntf2ComMdlCtrl__Poll(beNDMWLoadIntf2ComMdlCtrl *self) {
    int i;
    int n;
    beLoadIntf2ComMdlDataList *l;
    beLoadIntf2ComMdlData *e;
    beLoadIntf2ComMdlData *t;
    int i2;
    int n2;
    beLoadIntf2ComMdlDataList *l2;
    beLoadIntf2ComMdlData *e2;
    beLoadIntf2ComMdlData *t2;
    n = ((beLoadIntf2ComMdlDataList *)self->_openDataList)->_count;
    if (n > 0) {
        for (i = n - 1; i >= 0; i--) {
            e = ((beLoadIntf2ComMdlData **)((beLoadIntf2ComMdlDataList *)self->_openDataList)->_data)[i];
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsSequence((beNDMWSaveIntfComMdlCtrl *)self, e->_ramNo, (const char *)e->_infoName, (const char *)e->_openSQ)) == 1) break;
            l = (beLoadIntf2ComMdlDataList *)self->_openDataList;
            t = ((beLoadIntf2ComMdlData **)l->_data)[i];
            if (t != 0) {
                t->_refCount = (int)t->_refCount - 1;
                if (((unsigned long long)(long long)(int)t->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy((void *)t);
            }
            List_RemoveWordAt(l, i);
            ((beLoadIntf2ComMdlData **)l->_data)[l->_count] = 0;
        }
    }
    n2 = ((beLoadIntf2ComMdlDataList *)self->_closeDataList)->_count;
    if (n2 > 0) {
        for (i2 = n2 - 1; i2 >= 0; i2--) {
            e2 = ((beLoadIntf2ComMdlData **)((beLoadIntf2ComMdlDataList *)self->_closeDataList)->_data)[i2];
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning(self, e2->_ramNo, (const char *)e2->_infoName)) == 1) break;
            l2 = (beLoadIntf2ComMdlDataList *)self->_closeDataList;
            t2 = ((beLoadIntf2ComMdlData **)l2->_data)[i2];
            if (t2 != 0) {
                t2->_refCount = (int)t2->_refCount - 1;
                if (((unsigned long long)(long long)(int)t2->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy((void *)t2);
            }
            List_RemoveWordAt(l2, i2);
            ((beLoadIntf2ComMdlData **)l2->_data)[l2->_count] = 0;
        }
    }
}

void Gap__Bec__beNDMWLoadIntf2__vfunc_32(beNDMWLoadIntf2 *arg0) {
    igObject *temp_a0;
    igObject *temp_v0;

    if (arg0->_padManager == 0) {
        temp_v0 = FUN_00236f80(arg0->_insight, g_bePadManager_metaObject[0]);
        if (temp_v0 != 0) {
            temp_v0->_refCount = (int)temp_v0->_refCount + 1;
        }
        temp_a0 = (igObject *)arg0->_padManager;
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        arg0->_padManager = (int)temp_v0; /* matching construct: 4-byte reference field stores the object pointer */
    }
}

/* Return the data address as a guest word, preserving the original ABI. */

int DataList_GetData_003e9090(igDataList *list)
{
    return list->_data;
}

void beNDMWLoadSavePlWork__SetIsCtrl(beNDMWLoadSavePlWork *a0, int a1)
{
    a0->_isCtrl = a1;
}

unsigned char beNDMWLoadSavePlWork__GetIsRdy(beNDMWLoadSavePlWork *p)
{
    return p->_isRdy;
}

unsigned char beNDMWLoadSavePlWork__GetIsEntry(beNDMWLoadSavePlWork *p)
{
    return p->_isEntry;
}

void ObjectRef_Retain_003e90d0(ObjectRefTarget *object) {
    if(object) ++object->references;
}

/* Unchecked guest-word list access; declaring base is igDataList. */

int DataList_GetWordAt_003e90f0(igDataList *list, int index)
{
    return *(int *)(list->_data + index * 4);
}

void ObjectList_SetAtRetained_003e9160(igDataList *list, int index, ObjectRefTarget *replacement) {
    ObjectRefTarget *previous;
    if(replacement) ++replacement->references;
    previous=((ObjectRefTarget **)list->_data)[index];
    if(previous) {
        --previous->references;
        if(((unsigned long long)(long long)previous->references & 0x7fffffULL)==0)
            igObject_Destroy((void *)previous);
    }
    if(list->_count && index>=0 && index<list->_count)
        ((ObjectRefTarget **)list->_data)[index]=replacement;
}

void FUN_003e9220(void *arg0, void *arg1) {
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 4) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 8) = (float) *(float *)((char *)(arg1) + 8);
}

/* Unchecked guest-word list access; declaring base is igDataList. */

int DataList_GetWordAt_003e9240(igDataList *list, int index)
{
    return *(int *)(list->_data + index * 4);
}

/* Object-reference word at an unchecked list index. Object lists and lists of lists share the
 * declaring base igDataList::_data. */

int ObjectList_GetAt_003e9260(igDataList *list, int index)
{
    return *(int *)(list->_data + index * 4);
}

void *DataList_FindProperty_003e9280(int list, int meta, int *name)
{
    return igProperty_FindByName(list, meta, name);
}

int ObjectRef_Get_003e92a0(int *p)
{
    return *(int *)((char *)p + 0);
}

ObjectRefTarget **ObjectRef_Assign_003e92b0(ObjectRefTarget **destination,ObjectRefTarget **source) {
    ObjectRefTarget *incoming=*source;
    ObjectRefTarget *outgoing;
    if(incoming) ++incoming->references;
    outgoing=*destination;
    if(outgoing) {
        --outgoing->references;
        if(((unsigned long long)(long long)outgoing->references & 0x7fffffULL)==0)
            igObject_Destroy((void *)outgoing);
    }
    *destination=incoming;
    return destination;
}

DW4Sret4 AllocatorValue_Make_003e9360(int allocator)
{
    return DW4Sret4(allocator);
}

int Memory_SelectAllocator_003e9370(const int *selector, int fallback)
{
    if(GPR_00554c14)
        return fallback;
    else
        return Memory_GetAllocatorBySelector(*selector);
}

int ObjectRef_Get_003e93b0(int *p)
{
    return *p;
}

int Gap__Bec__beNDMWLoadIntf2__vfunc_30(void)
{
    return g_beNDMWLoadIntf2Info_metaObject[0];
}

void Gap__Bec__beNDMWLoadIntf2__vfunc_29(beNDMWLoadIntf2 *arg0, beBaseInfoRam *arg1) {
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_005175d8[0]);
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_005175e8[0], 0, arg1->_ramNo);
}

extern "C" {
void *FUN_003c27c0(...);
void *beNDMWLoadIntf2SelSlot_Create(...);
void *FUN_003c31e0(...);
void *beNDMWLoadIntf2DataSelIntf_Create(...);
void *beNDMWLoadIntf2DegiStateCtrl_Create(...);
void *beNDMWLoadIntf2DegiState_Create(...);
void *FUN_003c40c0(...);
void *FUN_003c43c0(...);
int FUN_003c46a0(...);
void *beNDMWLoadIntf2MesWin_Create(...);
void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
void *beNDMWLoadIntf2TextOrder_Create(...);
int beMessenger_AppendInt(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
unsigned int beMessenger_ResolveEnumValue(...);
int beMessenger_SelectGroup(...);
int beMessenger_SetInt(...);
extern float DAT_004cd0a0[4][3];
extern int COMMONINTF[4];
extern int CTRL[4];
extern int MAKECHR[4];
extern int COMMDLCTRL[4];
extern int MESWIN[4];
extern int TEXTORDER[4];
extern int DEGISTATECTRL[4];
extern int GAMERAM_2[4];
extern int DAT_005175f8[4];
extern int DAT_00517608[4];
extern int DAT_00517618[4];
extern int g_propertyNameField[4];
extern int g_beSystem_metaObject[4];
extern int g_beLua_metaObject[4];

int Gap__Bec__beNDMWLoadIntf2__vfunc_34(beNDMWLoadIntf2 *self, void *ctx, void *msg);
}

struct Rc : public igObject { };
/* Owning stack references to the freshly created controller objects while the list is wired up;
 * each releases its object on scope exit (reference count in the low 23 bits of _refCount). Each
 * object kind has its own class, one per destructor copy. */

class CtrlDataRef {
public:
    Rc *p;
    CtrlDataRef(Rc *o) : p(o) {}
    ~CtrlDataRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class ItemListRef {
public:
    Rc *p;
    ItemListRef(Rc *o) : p(o) {}
    ~ItemListRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class ComMdlRef {
public:
    Rc *p;
    ComMdlRef(Rc *o) : p(o) {}
    ~ComMdlRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class TextOrderRef {
public:
    Rc *p;
    TextOrderRef(Rc *o) : p(o) {}
    ~TextOrderRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class SelSlotRef {
public:
    Rc *p;
    SelSlotRef(Rc *o) : p(o) {}
    ~SelSlotRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class NameSelRef {
public:
    Rc *p;
    NameSelRef(Rc *o) : p(o) {}
    ~NameSelRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class MesWinRef {
public:
    Rc *p;
    MesWinRef(Rc *o) : p(o) {}
    ~MesWinRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DegiStateRef {
public:
    Rc *p;
    DegiStateRef(Rc *o) : p(o) {}
    ~DegiStateRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class StatDataRef {
public:
    Rc *p;
    StatDataRef(Rc *o) : p(o) {}
    ~StatDataRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DataSelRef {
public:
    Rc *p;
    DataSelRef(Rc *o) : p(o) {}
    ~DataSelRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DiffSelRef {
public:
    Rc *p;
    DiffSelRef(Rc *o) : p(o) {}
    ~DiffSelRef() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Ctx { int p0; int p4; int kind; int p12[7]; Rc *list; };
struct Msg { int p[5]; int f20; };
struct CommonSlot { char p[13]; unsigned char b13; };
struct CommonSlotList { char p[16]; CommonSlot **f16; };
struct Rec { char p[40]; CommonSlotList *f40; };

#define ALLOC(a, o) { a = igObject_GetAllocator(o); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define REL(o) { Rc *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
struct ListInstall { static inline void go(Ctx *o, const igSmartPointer<Rc> &fresh) {
    Rc *n = fresh.p;
    if (n != 0) n->_refCount = n->_refCount + 1;
    REL(o->list)
    o->list = n;
}
static inline void make(Ctx *o, int al) { igSmartPointer<Rc> fresh((Rc *)beBaseInfoDataList_Create(al)); go(o, fresh); }
};
#define ENSURE(o) { int al; ALLOC(al, o) ListInstall::make(o, al); }
#define FIND(n) igProperty_FindByName(a1->list, g_propertyNameField[0], &n[0])

int Gap__Bec__beNDMWLoadIntf2__vfunc_34(beNDMWLoadIntf2 *self, void *ctx, void *msg) {
    Ctx *a1 = (Ctx *)ctx;
    Msg *a2 = (Msg *)msg;
    int al;
    unsigned int v;
    void *s0;
    void *s4;
    void *s3;
    void *s0b;
    void *s4b;
    float fx;
    float fy;
    float fz;
    beNDMWLoadIntf2CtrlData *fl;

    v = beMessenger_ResolveEnumValue(self->_messenger, FUN_003c46a0(), a2->f20);
    if (v == 0) {
        if (a1->list == 0) {
            ALLOC(al, self)
            {
            igSmartPointer<Rc> spFC((Rc *)beBaseInfoDataList_Create(al));
            { Rc *n = spFC.p; if (n != 0) n->_refCount = n->_refCount + 1; REL(a1->list) a1->list = n; }
            self->_system_ = (int)FUN_00236f80(self->_insight, g_beSystem_metaObject[0]);
            ALLOC(al, self)
            {
            CtrlDataRef spF8((Rc *)FUN_003c43c0(al));
            ObjectList_AppendRetained(a1->list, spF8.p);
            ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isRun = 1;
            if (a1->kind == 0) {
                ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isRdy = 0;
                ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isEntry = 1;
                ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isCtrl = 1;
            } else {
                ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isRdy = 0;
                ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isEntry = 0;
                ((beNDMWLoadIntf2CtrlData *)spF8.p)->_isCtrl = 1;
            }
            }
            beMessenger_SendNamed(self->_messenger, &DAT_005175f8[0], 0, 0, &DAT_00517608[0]);
            ObjectList_AppendRetained(a1->list, beMessenger_GetObject(self->_messenger, 0));
            ALLOC(al, self)
            {
            ItemListRef spF4((Rc *)FUN_003c40c0(al));
            ObjectList_AppendRetained(a1->list, spF4.p);
            }
            ALLOC(al, self)
            {
            ComMdlRef spF0((Rc *)beNDMWLoadIntf2ComMdlCtrl_Create(al));
            ObjectList_AppendRetained(a1->list, spF0.p);
            ((beNDMWLoadIntf2ComMdlCtrl *)spF0.p)->_messenger = self->_messenger;
            { beNDMWLoadIntf2ComMdlCtrl *t = (beNDMWLoadIntf2ComMdlCtrl *)spF0.p;
            /* matching construct: hand search — the table's declared bound keeps the three loads ahead of the stores */
            fz = DAT_004cd0a0[a1->kind][2]; fy = DAT_004cd0a0[a1->kind][1]; fx = DAT_004cd0a0[a1->kind][0];
            t->_pos[0] = fx; t->_pos[1] = fy; t->_pos[2] = fz; }
            }
            ALLOC(al, self)
            {
            TextOrderRef spEC((Rc *)beNDMWLoadIntf2TextOrder_Create(al));
            ((beNDMWLoadIntf2TextOrder *)spEC.p)->_messenger = self->_messenger;
            { beNDMWLoadIntf2TextOrder *t = (beNDMWLoadIntf2TextOrder *)spEC.p; t->_lua = (int)FUN_00236f80(self->_insight, g_beLua_metaObject[0]); }
            ObjectList_AppendRetained(a1->list, spEC.p);
            }
            ALLOC(al, self)
            {
            SelSlotRef spE8((Rc *)beNDMWLoadIntf2SelSlot_Create(al));
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_ramNo = a1->kind;
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_messenger = self->_messenger;
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_padManager = (int)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_comMdlCtrl = (int)FIND(COMMDLCTRL);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_textOrder = (int)FIND(TEXTORDER);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_commonIntf = (int)FIND(COMMONINTF);
            ObjectList_AppendRetained(a1->list, spE8.p);
            }
            ALLOC(al, self)
            {
            NameSelRef spE4((Rc *)FUN_003c27c0(al));
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_ramNo = a1->kind;
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_messenger = self->_messenger;
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_padManager = (int)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
            if (a1->list == 0) ENSURE(a1)
            s3 = FIND(COMMDLCTRL);
            if (a1->list == 0) ENSURE(a1)
            s0 = FIND(TEXTORDER);
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_comMdlCtrl = (int)s3;
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_textOrder = (int)s0;
            ObjectList_AppendRetained(a1->list, spE4.p);
            }
            ALLOC(al, self)
            {
            MesWinRef spE0((Rc *)beNDMWLoadIntf2MesWin_Create(al));
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_ramNo = a1->kind;
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_messenger = self->_messenger;
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_padManager = (int)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
            ObjectList_AppendRetained(a1->list, spE0.p);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_textOrder = (int)FIND(TEXTORDER);
            }
            ALLOC(al, self)
            {
            DegiStateRef spDC((Rc *)beNDMWLoadIntf2DegiStateCtrl_Create(al));
            ALLOC(al, self)
            {
            StatDataRef spD8((Rc *)beNDMWLoadIntf2DegiState_Create(al));
            if (a1->list == 0) ENSURE(a1)
            s0 = FIND(COMMONINTF);
            if (a1->list == 0) ENSURE(a1)
            s4 = FIND(TEXTORDER);
            if (a1->list == 0) ENSURE(a1)
            beNDMWLoadIntf2DegiState__Init((beNDMWLoadIntf2DegiState *)spD8.p, a1->kind, (int)s0, (int)s4, (int)FIND(COMMDLCTRL), self->_messenger, 0);
            ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)spDC.p)->_statDataList, spD8.p);
            }
            ALLOC(al, self)
            {
            StatDataRef spD4((Rc *)beNDMWLoadIntf2DegiState_Create(al));
            if (a1->list == 0) ENSURE(a1)
            s0b = FIND(COMMONINTF);
            if (a1->list == 0) ENSURE(a1)
            s4b = FIND(TEXTORDER);
            if (a1->list == 0) ENSURE(a1)
            beNDMWLoadIntf2DegiState__Init((beNDMWLoadIntf2DegiState *)spD4.p, a1->kind, (int)s0b, (int)s4b, (int)FIND(COMMDLCTRL), self->_messenger, 1);
            ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)spDC.p)->_statDataList, spD4.p);
            }
            ObjectList_AppendRetained(a1->list, spDC.p);
            }
            ALLOC(al, self)
            {
            DataSelRef spD0((Rc *)beNDMWLoadIntf2DataSelIntf_Create(al));
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_padManager = (int)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_comMdlCtrl = (int)FIND(COMMDLCTRL);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_textOrder = (int)FIND(TEXTORDER);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_commonIntf = (int)FIND(COMMONINTF);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_mesWin = (int)FIND(MESWIN);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_statDisp = (int)FIND(DEGISTATECTRL);
            ObjectList_AppendRetained(a1->list, spD0.p);
            }
            ALLOC(al, self)
            {
            DiffSelRef spCC((Rc *)FUN_003c31e0(al));
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_padManager = (int)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_comMdlCtrl = (int)FIND(COMMDLCTRL);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_textOrder = (int)FIND(TEXTORDER);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_commonIntf = (int)FIND(COMMONINTF);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_mesWin = (int)FIND(MESWIN);
            ObjectList_AppendRetained(a1->list, spCC.p);
            }
            }
        }
        return 1;
    }
    if (a1->list == 0) return 1;
    if (a1->list == 0) ENSURE(a1)
    fl = (beNDMWLoadIntf2CtrlData *)FIND(CTRL);
    if (a1->list == 0) ENSURE(a1)
    FIND(MAKECHR);
    switch (v) {
    case 2:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, 0);
        }
        if (fl->_isEntry == 1) {
            beMessenger_SetInt(self->_messenger, 0, beMessenger_GetInt(self->_messenger, 0) + 1);
        }
        return 1;
    case 3:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, 0);
        }
        if (fl->_isRdy == 1) {
            beMessenger_SetInt(self->_messenger, 0, beMessenger_GetInt(self->_messenger, 0) + 1);
        }
        return 1;
    case 4:
        fl->_isCtrl = 1;
        return 1;
    case 5:
        fl->_isCtrl = 0;
        return 1;
    case 6:
        if (a1->list == 0) ENSURE(a1)
        if (((Rec *)FIND(COMMONINTF))->f40->f16[a1->kind]->b13 != 1) {
            beMessenger_SelectGroup(self->_messenger, &GAMERAM_2[0]);
            beMessenger_AppendInt(self->_messenger, a1->kind);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00517618[0]);
        }
        return 1;
    case 7:
        if (beMessenger_GetIntCount(self->_messenger) == 0) {
            beMessenger_AppendInt(self->_messenger, 0);
        }
        self->_difficultMax = beMessenger_GetInt(self->_messenger, 0);
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beNDMWLoadIntf2__vfunc_20(void)
{
    return g_beNDMWLoadIntf2_metaObject[0];
}
