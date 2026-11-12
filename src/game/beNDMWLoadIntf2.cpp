#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define SLOT_ROW(ci, pl) ((beNDMWLoadSavePlWork *)((int *)((beNDMWLoadSavePlWorkList *)(ci)->_flagWork)->_data)[pl])
#define SLOT_ITEMS(ci, pl) ((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)SLOT_ROW(ci, pl)->_haveSaveData)->_saveDataList)->_data)
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define DEGI(common, i) (((beNDMWDegiData **)((beNDMWDegiDataList *)(common)->_gameUseData)->_data)[i])
#define AREAS(common, pl) (((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)PLW(common, pl)->_haveSaveData)->_saveDataList)->_data))
#define SLOT_DEGI(bk, pl, i) \
    ((beNDMWDegiData *)((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork *)((int *)((beNDMWLoadSavePlWorkList *)(bk)->_flagWork)->_data)[pl])->_haveSaveData)->_saveDataList)->_data)[i])
#define BIND(P, I, F) do { int a = igObject_GetAllocator(arg0); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); igSmartPointer<Obj> r(((Obj *)FUN_003614f0(a))); beUnicodeObj_AllocateBuffer(r.p, 1); *(unsigned short *)r.p->_buffer = arg0->t.name[I]; FUN_003ec120(arg0->n._textOrder, P, arg0->n._ramNo, I, r.p, 1, F); } while (0)
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
extern "C" int FUN_003ecad0(...);
extern "C" int FUN_002eb010(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" void * StringPool_Intern(...);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_DispatchSelected(int, int *);
extern "C" int beMessenger_SelectReceivers(int, int *, int, int);
extern "C" int beMessenger_AppendString(int, int);
extern "C" int beMessenger_GetBool(int, int);
extern "C" void igObject_Destroy(void *);
extern "C" void FUN_003e9220(void *arg0, void *arg1);
extern "C" void igProperty_FindByName(void);
extern "C" void FUN_003e9280(void);
extern "C" int FUN_003e92a0(int *p);
extern "C" int beBaseInfoDataList_Create(int);
extern "C" int *FUN_003e9330(int *arg0, int *arg1);
extern "C" void FUN_003e9360(int a0, int a1);
extern "C" int Memory_SelectAllocator_003e9370(const int *selector, int fallback);
extern "C" int FUN_003e93b0(int *p);
extern "C" int Gap__Bec__beNDMWLoadIntf2__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWLoadIntf2__vfunc_20(void);
extern "C" int FUN_00100610(...);
extern "C" void **FUN_003eb480(void **arg0, long long arg1);
extern "C" void **FUN_003eb580(void **arg0, short arg1);
extern "C" void **FUN_003eb600(void **arg0, short arg1);
extern "C" void **FUN_003eb700(void **arg0, short arg1);
extern "C" void **FUN_003eb900(void **arg0, int arg1);
extern "C" void **FUN_003eb980(void **arg0, short arg1);
extern "C" void FUN_003d9de0(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern "C" void FUN_003d9e10(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2);
extern "C" void FUN_003d9e40(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2);
extern "C" void FUN_003d9e70(beNDMWLoadIntf2DegiState *arg0, int arg1);
extern "C" void FUN_003d9e90(beNDMWLoadIntf2DegiState *arg0);
extern "C" beUnicodeObj * FUN_003614f0(...);
typedef struct SlotEnt { int name; int val; int val2; } SlotEnt;
extern "C" int DAT_00516c40[4];
extern "C" int DAT_00516c50[4];
extern "C" int DAT_00516c60[4];
extern "C" int DAT_00516c68[4];
extern "C" int DAT_00516c78[4];
extern "C" int DAT_00516c80[4];
extern "C" int DAT_00516c90[4];
extern "C" int DAT_00516c98[4];
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
struct SlotDisplay { char p0[40]; unsigned char used; char p2[7]; int model; char p3[4]; int level; int hp; int maxHp; int mp; int maxMp; };
struct AreaCell { char p[12]; igObjectList *displays; };
struct AreaRow { char p[32]; AreaCell *cell; };
struct SlotBackend { char p[36]; igObjectList *ownDisplays; igObjectList *areas; };
struct SlotPanel { char p0[8]; int messenger; char p1[4]; int textCtrl; SlotBackend *backend; int player; int side; char p2[8]; int source; int index; };
extern "C" void FUN_003d9ec0(SlotPanel *arg0);
extern "C" void FUN_003da5f0(beNDMWLoadIntf2DegiState *arg0);
typedef struct Ent { int name; int val; int val2; } Ent;
extern "C" Ent DAT_004cec70[16];
extern "C" int DAT_00516ca8[4];
extern "C" int DAT_00516cc0[4];
extern "C" int DAT_00516cd0[4];
extern "C" int DAT_00516cd8[4];
extern "C" int DAT_00516ce8[4];
extern "C" int DAT_00516cf8[4];
extern "C" int DAT_00516d08[4];
extern "C" int DAT_00516d10[4];
extern "C" int DAT_00516d20[4];
extern "C" int DAT_00516d30[4];
extern "C" int DAT_00516d40[4];
extern "C" int DAT_00516d50[4];
extern "C" int DAT_00516d60[4];
struct Item { char p0[40]; unsigned char b40; char p1[7]; int f48; };
struct IL { char p[16]; Item **arr; };
struct Cell { char p[12]; IL *f12; };
struct Row { char p[32]; Cell *f32; };
struct RL { char p[16]; Row **arr; };
struct Bk { char p[36]; IL *f36; RL *f40; };
struct Ob { char p[28]; float v28; float v32; float v36; };
struct V3 { float x; float y; float z; };
extern "C" unsigned char FUN_003da7c0(beNDMWLoadIntf2DegiState *arg0);
extern "C" void FUN_003dafb0(beNDMWLoadIntf2DataSelIntf *arg0, int arg1, int arg2);
extern "C" void beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
extern "C" int DAT_00516db0[4];
extern "C" int DAT_00516dc8[4];
extern "C" unsigned char FUN_003db060(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
/* Receiver: beNDMWLoadIntf2DataSelIntf; host is its _commonIntf. _flagWork holds the per-player beNDMWLoadSavePlWork records
 * (_isCtrl, _haveSaveData, a beNDMWLoadSlotPlayer whose _saveDataList holds the four save areas); _gameUseData is a
 * beNDMWDegiDataList of the per-player Digimon records. The class behind _statDisp is not reflected. */




typedef struct Node { int f0; char p0[12]; struct Node *n16; } Node;
extern "C" int DAT_00516e48[4];
extern "C" void *DAT_004cc840[4];
extern "C" void *DAT_004cc850[4];
extern "C" void *DAT_00586f20[4];
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
extern "C" unsigned char FUN_003dbf90(beNDMWLoadIntf2DataSelIntf *c, int sel);
extern "C" unsigned char FUN_003dc2e0(beNDMWLoadIntf2DataSelIntf *c, int sel);
struct Ob_3dc590 { char p[28]; float x; float y; float z; };
struct Ent_3dc590 { int name; int val; int val2; };
extern "C" int DAT_004cc830[4];
extern "C" unsigned char FUN_003dc590(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
typedef struct Pair { void *a; void *b; } Pair;
typedef struct Inner { char p[16]; Pair *pair; } Inner;
typedef struct Link { char p[16]; Inner *inner; } Link;
extern "C" unsigned char FUN_003dcab0(beNDMWLoadIntf2DataSelIntf *c, int sel);
struct V3_3dcc60 { float x, y, z; };
extern "C" unsigned char FUN_003dcc60(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
typedef struct P { char p0[28]; float x, y, z; } P;
extern "C" int DAT_00516e70[4];
extern "C" int DAT_00516e80[4];
extern "C" int DAT_00516e90[4];
extern "C" int DAT_00516ea0[4];
extern "C" bool FUN_003dd160(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
extern "C" unsigned char FUN_003dd440(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
/* Arena handles are 4-byte ints and are cast to pointers where followed. */


struct Tab { int name; int f4; int *f8; };
extern "C" int FUN_003dd6d0(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
extern "C" void beNDMWLoadIntf2Diffselect__Init(beNDMWLoadIntf2Diffselect *arg0, int arg1, int arg2);
/* The pad object is a bePadData: _lTrg/_lRpt are held, _trigger/_repeat are edges. */
typedef struct VecSrc { char p0[28]; float x, y, z; } VecSrc;
extern "C" int DAT_00516e18[4];
extern "C" int DAT_00516e28[4];
extern "C" int DAT_00516eb0[4];
extern "C" int DAT_00516ec0[4];
extern "C" int DAT_00516ed0[4];
extern "C" int DAT_00516ee0[4];
extern "C" int DAT_00516ef0[4];
extern "C" int DAT_00516f00[4];
extern "C" unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, int usePad, int e);
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
extern "C" unsigned char beNDMWLoadIntf2NameSel__Update(NameSelRam *s, int arg1);
extern "C" void FUN_003e0b80(beNDMWLoadIntf2SelSlot *arg0);
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
extern "C" void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *arg0, int arg1, int arg2, Entry *arg3);
extern "C" unsigned char beNDMWLoadIntf2SelSlot__Close(beNDMWLoadIntf2SelSlot *self);
typedef struct SlotEntry { int a; int idx; } SlotEntry;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Target { char p[28]; float x, y, z; } Target;
extern "C" void beNDMWLoadIntf2SelSlot__RefreshSlotMarks(beNDMWLoadIntf2SelSlot *self, int arg1);
extern "C" beLoadIntf2ComMdlData * beLoadIntf2ComMdlData__Create(...);
extern "C" int MODELCTRL[4];
extern "C" int GENERATE[4];
extern "C" int g_stringPool[4];
extern "C" int g_defaultAllocatorSelector[4];
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Start(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, int recordOpen);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__StartAt(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSQ, float *position, int recordOpen);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Play(beNDMWLoadIntf2ComMdlCtrl *self, int slot, int *modelName, int *sequenceName, int wait);
extern "C" int ISSEQNAME[4];
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, int infoName, int sqName);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Close(beNDMWLoadIntf2ComMdlCtrl *self, int ramNo, const char *infoName, const char *openSequence, unsigned char trackClose);
extern "C" int ISRUN[4];
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsRunning(beNDMWLoadIntf2ComMdlCtrl *self, int slot, const char *name);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(beNDMWLoadIntf2ComMdlCtrl *self);
extern "C" int List_RemoveWordAt(beLoadIntf2ComMdlDataList *, int);
extern "C" void beNDMWLoadIntf2ComMdlCtrl__Poll(beNDMWLoadIntf2ComMdlCtrl *self);
extern "C" igObject *FUN_00236f80(int, int);
extern "C" int DAT_00588518[4];
extern "C" void Gap__Bec__beNDMWLoadIntf2__vfunc_32(beNDMWLoadIntf2 *arg0);
/* Deleting destructor; the deletion flag is a signed short. */

typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *ObjectRef_Destruct_003e9010(ObjectRefWord *self,int delete_storage);
extern "C" int DataList_GetData_003e9090(igDataList *list);
extern "C" void beNDMWLoadSavePlWork__SetIsCtrl(beNDMWLoadSavePlWork *a0, int a1);
extern "C" unsigned char beNDMWLoadSavePlWork__GetIsRdy(beNDMWLoadSavePlWork *p);
extern "C" unsigned char beNDMWLoadSavePlWork__GetIsEntry(beNDMWLoadSavePlWork *p);
extern "C" void ObjectRef_Retain_003e90d0(ObjectRefTarget *object);
extern "C" int DataList_GetWordAt_003e90f0(igDataList *list, int index);
extern "C" void ObjectRef_Release_003e9110(ObjectRefTarget *object);
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
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *FUN_003eb500(O *arg0, short arg1);
typedef struct S_temp_a0_3eb580 { char pad4[4]; int f4; } S_temp_a0_3eb580;
typedef struct S_temp_a0_3eb600 { char pad4[4]; int f4; } S_temp_a0_3eb600;
extern "C" ObjectRefWord *FUN_003eb680(ObjectRefWord *self,int delete_storage);
extern "C" ObjectRefWord *FUN_003eb780(ObjectRefWord *self,int delete_storage);
struct R_3eb800 { int vt; unsigned int rc; };
extern "C" struct R_3eb800 **FUN_003eb800(struct R_3eb800 **arg0, short arg1);
extern "C" ObjectRefWord *FUN_003eb880(ObjectRefWord *self,int delete_storage);

void FUN_003d9de0(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
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

void FUN_003d9e10(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2) {
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

void FUN_003d9e70(beNDMWLoadIntf2DegiState *arg0, int arg1) {
    arg0->_isEnd = 0;
    arg0->_closeKind = arg1;
    arg0->_st0 = 2;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

void FUN_003d9e90(beNDMWLoadIntf2DegiState *arg0) {
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
                igSmartPointer<beUnicodeObj> text(FUN_003614f0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
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
            beMessenger_SendNamed(arg0->messenger, DAT_00516c50, DAT_00516c60, 0, DAT_00516c68);
            s4 = beMessenger_GetObject(arg0->messenger, 0);
            s3 = 0;
            s2 = ((SlotEnt *)DAT_004cec70);
        lsA:
            if (strcmp(s2->name, s0->model) == 0) {
                s5 = s3;
            } else {
                s3 += 1;
                s2 += 1;
                if (s3 < 16) goto lsA;
            }
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 10, beDataBase_GetRecordString(s4, s5, DAT_00516c78), 0, 0);
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
                igSmartPointer<beUnicodeObj> text(FUN_003614f0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
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
            beMessenger_SendNamed(arg0->messenger, DAT_00516c50, DAT_00516c60, 0, DAT_00516c68);
            s4 = beMessenger_GetObject(arg0->messenger, 0);
            s3 = 0;
            s2 = ((SlotEnt *)DAT_004cec70);
        lsB:
            if (strcmp(s2->name, s0->model) == 0) {
                s5 = s3;
            } else {
                s3 += 1;
                s2 += 1;
                if (s3 < 16) goto lsB;
            }
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 11, beDataBase_GetRecordString(s4, s5, DAT_00516c78), 0, 0);
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

unsigned char FUN_003da7c0(beNDMWLoadIntf2DegiState *arg0) {

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
                Ent *s3 = DAT_004cec70;
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
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516ca8, (const char *)DAT_004cec70[s0].val, (float *)&vb, 1);
                    o = (Ob *)arg0->_comMdlCtrl;
                    va.x = o->v28; va.y = o->v32; va.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cc0, (const char *)DAT_00516cd0, (float *)&va, 1);
                } else {
                    V3 vc;
                    Ob *o = (Ob *)arg0->_comMdlCtrl;
                    vc.x = o->v28; vc.y = o->v32; vc.z = o->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cd8, (const char *)DAT_004cec70[s0].val, (float *)&vc, 1);
                }
            } else if (arg0->_dispPos == 0) {
                V3 vd; V3 ve;
                Ob *o = (Ob *)arg0->_comMdlCtrl;
                vd.x = o->v28; vd.y = o->v32; vd.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516ca8, (const char *)DAT_00516ce8, (float *)&vd, 1);
                o = (Ob *)arg0->_comMdlCtrl;
                ve.x = o->v28; ve.y = o->v32; ve.z = o->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cc0, (const char *)DAT_00516cf8, (float *)&ve, 1);
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
            Ent *s3 = DAT_004cec70;
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
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516ca8, (int *)DAT_004cec70[s0].val2, 0);
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516cc0, (int *)DAT_00516d08, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516cd8, (int *)DAT_004cec70[s0].val2, 0);
            }
        } else if (arg0->_dispPos == 0) {
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516ca8, (int *)DAT_00516d10, 0);
            beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (int *)DAT_00516cc0, (int *)DAT_00516d20, 0);
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
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516ca8, (const char *)DAT_00516d30, 1);
                if (arg0->_isUseData == 1) {
                    switch (arg0->_closeKind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cc0, (const char *)DAT_00516d30, 1);
                        break;
                    case 1:
                        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cc0, (const char *)DAT_00516d40, 1);
                        break;
                    case 2:
                        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cc0, (const char *)DAT_00516d50, 1);
                        break;
                    }
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cc0, (const char *)DAT_00516d60, 1);
                }
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl, (int)arg0->_plNo, (const char *)DAT_00516cd8, (const char *)DAT_00516d30, 1);
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

void FUN_003dafb0(beNDMWLoadIntf2DataSelIntf *arg0, int arg1, int arg2) {
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

unsigned char FUN_003db060(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
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
                    s8 = DAT_004cec70;
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
                    beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s2p), (const char *)DAT_004cec70[s5].val, (float *)&v1, 1);
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
            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516cd0, (float *)&v4, 1);
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
                FUN_003ecad0(spF0, (arg0->_plNo << 16) | 0x513);
            } else {
                arg0->_mesKind = 1;
                FUN_003ecad0(spF0, (arg0->_plNo << 16) | 0x515);
            }
            FUN_003d9e10((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]), 0, (int)arg0->_svDataSelPoint);
        } else {
            arg0->_mesKind = 0;
            FUN_003ecad0(spF0, (arg0->_plNo << 16) | 0x503);
            FUN_003d9e10((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]), 1, (int)arg0->_plNo);
        }
        arg0->_isUpStatWin = 1;
        spC0 = spC0 + 1;
        break;
    }
    case 1:
        if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]))) & 0xFF) == 1 && (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)s0) & 0xFF) == 1) {
            int s4;
            beNDMWDegiData *it;
            int s0c;
            s4 = 0;
            s0c = 0;
            do {
                it = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[s4];
                if (it->_isUse == 1) {
                    al = igObject_GetAllocator(arg0);
                    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
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
                        if (DAT_00586f20[0] == 0) {
                            void *q = (void *)FUN_002eb010(16);
                            if (q != 0) q = ((void *)StringPool_Construct(q));
                            DAT_00586f20[0] = q;
                        }
                        nw2 = ((char *)StringPool_Intern(DAT_00586f20[0], src));
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
                    if (c->_mesKind != 0) { c->_mesKind = 0; FUN_003ecad0(h40, (c->_plNo << 16) | 0x513); }
                } else if (c->_mesKind != 1) {
                    c->_mesKind = 1; FUN_003ecad0(h40, (c->_plNo << 16) | 0x515);
                }
            } else if (c->_mesKind != 0) {
                c->_mesKind = 0; FUN_003ecad0(h40, (c->_plNo << 16) | 0x513);
            }
        }
        break;
    }
    case 1:
        if (c->_kind == 0) {
            if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)n->n16->n16->f0)) & 0xFF) != 1) break;
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
        beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516d50, 1);
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

unsigned char FUN_003dbf90(beNDMWLoadIntf2DataSelIntf *c, int sel) {
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
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d70, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d80, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d90, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516da0, (const char *)DAT_00516d30, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 0);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 1);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 2);
            TextOrder_ClearFont(b, DAT_00516dc8, c->_plNo, 3);
            c->_isSaveArea = 0;
        }
        if (c->_isUpStatWin == 1) {
            FUN_003d9e70((beNDMWLoadIntf2DegiState *)n->n16->n16->f0, 0);
        }
        if (c->_isDownStatWin == 1) {
            FUN_003d9e70((beNDMWLoadIntf2DegiState *)n->n16->n16->f4, 0);
        }
        if (c->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516d30, 1);
        }
        v++;
        break;
    case 1:
        if (c->_isUpStatWin == 1) {
            if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)n->n16->n16->f0)) & 0xFF) != 1) break;
            c->_isUpStatWin = 0;
        }
        if (c->_isDownStatWin == 1) {
            if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)n->n16->n16->f4)) & 0xFF) != 1) break;
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

unsigned char FUN_003dc2e0(beNDMWLoadIntf2DataSelIntf *c, int sel) {
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
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d70, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d80, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516d90, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a, c->_plNo, (const char *)DAT_00516da0, (const char *)DAT_00516d30, 1);
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
            FUN_003d9e10((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)n->_statDataList)->_data)[1]), 0, c->_svDataSelPoint);
            c->_isDownStatWin = 1;
        }
        break;
    case 2:
        if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)n->_statDataList)->_data)[1]))) & 0xFF) == 1) {
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

unsigned char FUN_003dc590(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
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
        FUN_003d9e70((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)nd->_statDataList)->_data)[1]), 0);
        arg0->_isDownStatWin = 0;
        v++;
        break;
    case 1:
        if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)nd->_statDataList)->_data)[1]))) & 0xFF) == 1) v++;
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
                    if (strcmp(((Ent_3dc590 *)DAT_004cec70)[k].name, it->_dmkind) == 0) { j = k; break; }
                }
                float v1[3];
                v1[0] = ob->x; v1[1] = ob->y; v1[2] = ob->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)ob, (int)arg0->_plNo, (const char *)DAT_004cc830[i], (const char *)(((Ent_3dc590 *)DAT_004cec70)[j].val), (float *)v1, 1);
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
                    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
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

unsigned char FUN_003dcab0(beNDMWLoadIntf2DataSelIntf *c, int sel) {
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
        FUN_003d9e70((beNDMWLoadIntf2DegiState *)n->inner->pair->a, 0);
        FUN_003d9e70((beNDMWLoadIntf2DegiState *)n->inner->pair->b, 0);
        c->_isDownStatWin = 0;
        v++;
        c->_isUpStatWin = 0;
        break;
    case 1:
        if ((((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)n->inner->pair->a)) & 0xFF) == 1 && (((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)n->inner->pair->b)) & 0xFF) == 1) {
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

unsigned char FUN_003dcc60(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
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
                    if (strcmp(DAT_004cec70[s4].name, it->_dmkind) == 0) { s5 = s4; break; }
                }
                va.x = s0->_pos[0]; va.y = s0->_pos[1]; va.z = s0->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)s0, (int)arg0->_plNo, (const char *)(*s3), (const char *)DAT_004cec70[s5].val, (float *)&va, 1);
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
        FUN_003d9e10((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]), 1, (int)arg0->_plNo);
        arg0->_isUpStatWin = 1;
        mode += 1;
        break;
    }
    case 1:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty((beNDMWLoadIntf2ComMdlCtrl *)s0) & 0xFF) == 1 && (((int)FUN_003da7c0((beNDMWLoadIntf2DegiState *)(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]))) & 0xFF) == 1) {
            i = 0;
            off = 0;
            mode += 1;
            do {
                it = *(beNDMWDegiData **)((char *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)spF0->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_saveDataList)->_data + off);
                if (it->_isUse == 1) {
                    al = igObject_GetAllocator(arg0, arg0->_plNo);
                    if (GPR_00554c14 != 0) a0 = al; else a0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
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

bool FUN_003dd160(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
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
            if (arg0->_kind == 0) FUN_003ecad0(s2, (arg0->_plNo << 0x10) | 0x513);
            else FUN_003ecad0(s2, (arg0->_plNo << 0x10) | 0x503);
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

unsigned char FUN_003dd440(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
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
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516d70, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516d80, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516d90, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516da0, (const char *)DAT_00516d30, 1);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 0);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 1);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 2);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 3);
            arg0->_isSaveArea = 0;
        }
        if (arg0->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)s3, arg0->_plNo, (const char *)DAT_00516db0, (const char *)DAT_00516d30, 1);
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

int FUN_003dd6d0(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
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
                        if (strcmp(((Tab *)DAT_004cec70)[m].name, e->_dmkind) == 0) { k = m; break; }
                    }
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)s4, s3, (int *)DAT_004cc830[j], ((Tab *)DAT_004cec70)[k].f8, 0);
                    int a = igObject_GetAllocator(arg0);
                    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
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

unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, int usePad, int e) {
    float v0[3], v1[3];
    int buttons, h;
    bool u, d;
    int up, down;
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
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516eb0, (const char *)DAT_00516cd0, (float *)v0, 1);
                break;
            case 1:
                v1[0] = a0->x; v1[1] = a0->y; v1[2] = a0->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)DAT_00516cd0, (float *)v1, 1);
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
                FUN_003ecad0(s0, (self->_plNo << 16) | 0x404);
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
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516eb0, (int *)DAT_00516ed0, 1);
                        break;
                    case 1:
                        if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516ec0, (int *)DAT_00516ed0, 1);
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
                        beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516eb0, (int *)DAT_00516ef0, 1);
                        break;
                    case 1:
                        if (self->_selectPoint == 1) beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (int *)DAT_00516ec0, (int *)DAT_00516ef0, 1);
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
                    if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516eb0, (const char *)DAT_00516d40, 1);
                    else beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516eb0, (const char *)DAT_00516e18, 1);
                } else beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516eb0, (const char *)DAT_00516d50, 1);
                break;
            case 1:
                TextOrder_PublishLineListOnly(s1, (self->_plNo << 16) | 0x403);
                if (self->_isCancel == 0) {
                    switch (self->_selectPoint) {
                    case 0: beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)DAT_00516d40, 1); break;
                    case 1: beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)DAT_00516e18, 1); break;
                    case 2: beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)DAT_00516e28, 1); break;
                    }
                } else beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)a0, (int)self->_plNo, (const char *)DAT_00516ec0, (const char *)DAT_00516d50, 1);
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
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<Obj> r0(((Obj *)FUN_003614f0(a)));
        beUnicodeObj_AllocateBuffer(r0.p, 1);
        *(unsigned short *)r0.p->_buffer = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 0, r0.p, 1, 0);
        }
        {
        s0 = arg0->_tatePoint;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<Obj> r1(((Obj *)FUN_003614f0(a)));
        beUnicodeObj_AllocateBuffer(r1.p, 1);
        *(unsigned short *)r1.p->_buffer = DAT_004cc860[s0].v[0];
        FUN_003ec120(arg0->_textOrder, DAT_00516f10, arg0->_ramNo, 1, r1.p, 1, 0);
        }
        {
        int n = arg0->_tatePoint + 1;
        if (n >= arg0->_tateMax) s0 = arg0->_tateMin; else s0 = n;
        a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
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
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
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
extern "C" char DAT_00516dd8[], DAT_00516f50[], DAT_00516f60[], DAT_00516f70[], DAT_00516f80[], DAT_00516f98[], DAT_00516fb0[], DAT_00516fd0[];
extern "C" char DAT_00516fe8[], DAT_00516ff8[], DAT_00517008[], DAT_00517018[], DAT_00517028[], DAT_00517030[], DAT_00517040[];
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
unsigned char beNDMWLoadIntf2NameSel__Update(NameSelRam *s, int arg1) {
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
            POS(pos0) beNDMWLoadIntf2ComMdlCtrl__StartAt(CM, NS._ramNo, (const char *)DAT_00516ca8, (const char *)DAT_004cec70[NS._selDataNo].val, (float *)&pos0, 1);
            DRAWPOS(pos1, DAT_00516f50, (const char *)DAT_00516cd0, 1)
            DRAWPOS(pos2, DAT_00516f60, (const char *)DAT_00516cd0, 1)
            DRAWPOS(pos3, DAT_00516f70, (const char *)DAT_00516cd0, 1)
            DRAWPOS(pos4, DAT_00516f80, (const char *)DAT_00516cd0, 1)
            DRAWPOS(pos5, DAT_00516f98, (const char *)DAT_00516cd0, 1)
            DRAWPOS(pos6, DAT_00516fb0, (const char *)DAT_00516cd0, 1)
            DRAWPOS(pos7, DAT_00516fd0, (const char *)DAT_00516cd0, 1)
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
                            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fd0, (int *)DAT_00517028, 1);
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
                            beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516fb0, (int *)DAT_00517028, 1);
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
                beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f98, (int *)DAT_00517028, 1);
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
                beNDMWLoadIntf2ComMdlCtrl__Play(CM, NS._ramNo, (int *)DAT_00516f80, (int *)DAT_00517028, 1);
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
            LANGDRAW(DAT_00516dd8, 1)
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
            LANGDRAW0((const char *)DAT_00516d40, 1)
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
            LANGDRAW0((const char *)DAT_00516d30, 1)
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
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, (const char *)DAT_00516ca8, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f70, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f50, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f60, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f80, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516f98, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516fb0, (const char *)DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(CM, NS._ramNo, DAT_00516fd0, (const char *)DAT_00516d30, 1);
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

void FUN_003e0b80(beNDMWLoadIntf2SelSlot *arg0) {
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
    FUN_003e0b80((beNDMWLoadIntf2SelSlot *)((beNDMWLoadIntf2SelSlot *)arg0));
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
            beNDMWLoadIntf2ComMdlCtrl__StartAt((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517150, (const char *)DAT_00516cd0, vc, 1);
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
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00516d30, 0);
                        }
                        break;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170, (const char *)DAT_00516d30, 0);
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
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        }
                        break;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        }
                        break;
                    case 2:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        }
                        break;
                    case 3:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        }
                        break;
                    case 4:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00516d30, 0);
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
                    beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516d50, 1);
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
                beNDMWLoadIntf2ComMdlCtrl__Play((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516d50, 1);
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

void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *arg0, int arg1, int arg2, Entry *arg3) {
    Entry *tbl;
    tbl = arg3;
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
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517118, (const char *)DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517160, (const char *)DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517150, (const char *)DAT_00516d30, 1);
                c = self->_textOrder;
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x100c);
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x1100);
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x102e);
                for (i = 0; i < 2; i++) {
                    switch (i) {
                    case 0:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00516d30, 0);
                        break;
                    case 1:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2 + 1, (const char *)DAT_00517170, (const char *)DAT_00516d30, 0);
                        break;
                    }
                }
            } else {
                int j;
                int d;
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517118, (const char *)DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517160, (const char *)DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo, (const char *)DAT_00517150, (const char *)DAT_00516d30, 1);
                d = self->_textOrder;
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x100c);
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x1100);
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x102e);
                for (j = 0; j < 5; j++) {
                    switch (j) {
                    case 0:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        break;
                    case 1:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 1, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        break;
                    case 2:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 2, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        break;
                    case 3:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 5 + 3, (const char *)DAT_005171a0, (const char *)DAT_00516d30, 0);
                        break;
                    case 4:
                        if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170)) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl, self->_ramNo * 2, (const char *)DAT_00517170, (const char *)DAT_00516d30, 0);
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
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)DAT_00516d30)), 0);
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (const char *)(((char *)DAT_00517170)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2+1, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)DAT_00516d30)), 0);
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
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_00516d30)), 0);
            break;
        case 1:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+1, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_00516d30)), 0);
            break;
        case 2:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+2, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_00516d30)), 0);
            break;
        case 3:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (const char *)(((char *)DAT_005171a0)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*5+3, (const char *)(((char *)DAT_005171a0)), (const char *)(((char *)DAT_00516d30)), 0);
            break;
        case 4:
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsRunning((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)))) == 1) beNDMWLoadIntf2ComMdlCtrl__Close((beNDMWLoadIntf2ComMdlCtrl *)TGT, self->_ramNo*2, (const char *)(((char *)DAT_00517170)), (const char *)(((char *)DAT_00516d30)), 0);
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
    int pool2;
    int newRefCount2;
    int pool;
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
    int pool;
    int pool2;
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
    int pool;
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

int beNDMWLoadIntf2ComMdlCtrl__IsSequence(beNDMWSaveIntfComMdlCtrl *self, int ramNo, int infoName, int sqName) {
    beMessenger_SelectReceivers(self->_messenger, &MODELCTRL[0], infoName, ramNo);
    beMessenger_AppendString(self->_messenger, sqName);
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
            int pool = FUN_002eb010(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        infoNameToken = ((const char *)StringPool_Intern(g_stringPool[0], infoName));
        RELEASE_STR(infoOwner->_infoName)
        infoOwner->_infoName = (int)infoNameToken;
        sequenceOwner = record.p;
        if (g_stringPool[0] == 0) {
            int pool = FUN_002eb010(0x10);
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
            if (((unsigned char)beNDMWLoadIntf2ComMdlCtrl__IsSequence((beNDMWSaveIntfComMdlCtrl *)self, e->_ramNo, e->_infoName, e->_openSQ)) == 1) break;
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
        temp_v0 = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
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

ObjectRefWord *ObjectRef_Destruct_003e9010(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
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

void ObjectRef_Release_003e9110(ObjectRefTarget *object) {
    if(object) {
        --object->references;
        if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
            igObject_Destroy((void *)object);
    }
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

void FUN_003e9280(void)
{
    igProperty_FindByName();
}

int FUN_003e92a0(int *p)
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

int *FUN_003e9330(int *arg0, int *arg1) {
    *arg0 = beBaseInfoDataList_Create(*arg1);
    return arg0;
}

void FUN_003e9360(int a0, int a1)
{
    *(int *)((char *)a0 + 0) = a1;
}

int Memory_SelectAllocator_003e9370(const int *selector, int fallback)
{
    if(GPR_00554c14)
        return fallback;
    else
        return Memory_GetAllocatorBySelector(*selector);
}

int FUN_003e93b0(int *p)
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

void **FUN_003eb480(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_003eb500(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void **FUN_003eb580(void **arg0, short arg1) {
    S_temp_a0_3eb580 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3eb580 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_003eb600(void **arg0, short arg1) {
    S_temp_a0_3eb600 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3eb600 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_003eb680(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_003eb700(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((void *)r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_003eb780(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

struct R_3eb800 **FUN_003eb800(struct R_3eb800 **arg0, short arg1) {
    struct R_3eb800 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_003eb880(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_003eb900(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_003eb980(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

int Gap__Bec__beNDMWLoadIntf2__vfunc_20(void)
{
    return g_beNDMWLoadIntf2_metaObject[0];
}
