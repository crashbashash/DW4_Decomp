#include "dw4/reflected.h"
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define MCU(common) ((beNDMWMcUtilCtrl *)(common)->_mcUtilCtrl)
#define MCSLOT(common, i) (((beNDMWMcSlot **)((beNDMWMcSlotList *)MCU(common)->_slot)->_data)[i])
#define REFS(o) (*(int *)&(o)->_refCount)
#define NODE(s, i) (((Node **)((igObjectList *)(s)->_flagWork)->_data)[i])
#define CFG(s) ((beNDMWMcUtilCtrl *)(s)->_mcUtilCtrl)
#define GRP(p) ((beNDMWLoadSlotPlayer *)(p))
#define DD(p) ((beNDMWDegiData *)(p))
#define DNAME(d) ((unsigned short *)(d)->_dmNameUni)
#define REL(o) { Rc *rr = (o); if (rr != 0) { REFS(rr) = REFS(rr) - 1; if (((unsigned long long)((long long)REFS(rr) << 0x29) >> 0x29) == 0) { igObject_Destroy((void *)rr); } } }
#define ALLOC(a, self) { a = ((void *)igObject_GetAllocator(self)); a = GPR_00554c14 ? a : ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])); }
#define PLW_3ee250(list, off) (*(beNDMWLoadSavePlWork **)((char *)((beNDMWLoadSavePlWorkList *)(list))->_data + (off)))
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#define IDS(DST, REC, CAP, RESIZE) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; int i; if (RESIZE) { if (l->_count > CAP) ObjectList_ResizeRetained(l, CAP); } i = 0; if (0 < l->_count) { do { DST[i] = ((IdObject **)l->_data)[i]->GetId(); i++; } while (i < l->_count); } if (i < CAP) { do { DST[i] = -1; i++; } while (i < CAP); } }
#define BYTES(DST, FN, REC) { igTDataList<unsigned char> *l = FN(arg1, REC)->v; int i = 0; if (0 < l->_count) { do { DST[i] = l->_data[i]; i++; } while (i < l->_count); } }
#define FINDN(DST, REC, N) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)igProperty_GetRecordFolder(arg1, &DAT_00517ec0[0])->v; int a; for (a = 0; a < N; a++) { IdObject *v = ((IdObject **)l->_data)[a]; if (v == 0) { DST[a] = -1; } else { DST[a] = t->find(v); } } }
#define FIND1(DSTV, REC) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)igProperty_GetRecordFolder(arg1, &DAT_00517ec0[0])->v; IdObject *v = ((IdObject **)l->_data)[0]; if (v == 0) { DSTV = -1; } else { DSTV = t->find(v); } }
#define FINDV(DST, REC) { igObjectList *l = igProperty_GetRecordFolder(arg1, REC)->v; igTDataList<IdObject *> *t = (igTDataList<IdObject *> *)igProperty_GetRecordFolder(arg1, &DAT_00517ec0[0])->v; int a; for (a = 0; a < l->_count; a++) { IdObject *v = ((IdObject **)l->_data)[a]; if (v == 0) { DST[a] = -1; } else { DST[a] = t->find(v); } } }
#define INTS(DST, FN, REC) { igIntList *l = FN(arg1, REC)->v; int i = 0; if (0 < l->_count) { do { DST[i] = ((int *)l->_data)[i]; i++; } while (i < l->_count); } }
#define ALLOC_3f2490(dst, obj) { int alloc = igObject_GetAllocator(obj); if (GPR_00554c14 != 0) { dst = alloc; } else { dst = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); } }

extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" void TextOrder_ConfigureFont(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern "C" void TextOrder_ClearFont(int arg0, const char *arg1, int arg2, int arg3);
extern "C" int beLua__RunNamedChunk(int, int *, int);
extern "C" void TextOrder_PublishLineListOnly(int arg0, int arg1);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beBaseInfoRam_StartTimer(int, void *, unsigned long long);
extern "C" int beBaseInfoRam_IsTimerExpired(int, int *);
extern "C" int FUN_00236f80(...);
extern "C" int FUN_00382eb0(...);
extern "C" void *beNDMWLoadSlotPlayer_Create(...);
extern "C" void * beNDMWDegiData_Create(...);
extern "C" int List_Resize(void *, int, int);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void igObject_Destroy(void *);
extern "C" int List_RemoveWordAt(void *, int);
extern "C" int memcpy(...);
extern "C" void FUN_003ee490(void *arg0, void *arg1);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" void strcpy(void *, void *);
extern "C" void ObjectList_ResizeRetained(void *, int);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void * FUN_002eb010(...);
extern "C" void * StringPool_Construct(...);
extern "C" char * StringPool_Intern(...);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int memset(int, int, int);
extern "C" int beMessenger_GetInt(...);
extern "C" int FUN_002ff820(...);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, int, int *);
extern "C" int Gap__Bec__beNDMWLoadCtrl2__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWLoadCtrl2__vfunc_20(void);
extern "C" int beMessenger_SendGroup(int, int *, int *);
extern "C" void * beBaseInfoDataList_Create(...);
extern "C" void * igProperty_FindByName(...);
extern "C" int FUN_003c7d40(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_GetIntCount(...);
extern "C" int beMessenger_ResolveEnumValue(...);
extern "C" void TextOrder_Configure(beNDMWLoadIntf2TextOrder *arg0, char *arg1, char *arg2, char *arg3, int arg4, int arg5);
typedef struct S0 { char pad16[16]; int f10; } S0;
extern "C" int DAT_005179b0[4];
extern "C" int DAT_00517a08[4];
extern "C" int DAT_00517a10[4];
extern "C" void TextOrder_PublishLine(S0 *arg0, int *arg1, int *arg2);
struct E { int w[20]; };
extern "C" int *DAT_004ceb30[][20];
/* Passes the first two arguments through and appends table[arg2].f[arg3] (80-byte rows) to the
 * worker call. C++ keeps the call a real jal. */
struct E_3ebdc0 { int f[20]; };
extern "C" int DAT_004cda44[4];
extern "C" int DAT_004cda48[4];
extern "C" int DAT_00517a18[4];
extern "C" int DAT_00517a28[4];
extern "C" int g_mdlEntity[4];
extern "C" int g_txtCallNo[4];
extern "C" void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *arg0, int arg1, int arg2);
struct Q { int a; int b; int c; };
struct E_3ec050 { unsigned int id:20; unsigned int pad:12; int w4; struct Q *list; };
struct R { int w[20]; };
extern "C" struct E_3ec050 DAT_004cda40[];
extern "C" int DAT_005179b8[4];
extern "C" int DAT_005179c0[4];
extern "C" int DAT_005179c8[4];
extern "C" int DAT_005179d0[4];
extern "C" int DAT_005179d8[4];
extern "C" int DAT_005179e8[4];
extern "C" int DAT_005179f8[4];
extern "C" int DAT_00517a00[4];
extern "C" int DAT_00517a38[4];
extern "C" void FUN_003ec120(beNDMWLoadIntf2TextOrder *arg0, int *arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" char DAT_005176a0[];
extern "C" char DAT_005176b0[];
extern "C" char DAT_00517a70[];
extern "C" char DAT_00517a80[];
extern "C" char DAT_00517a90[];
extern "C" char DAT_00517aa0[];
extern "C" char DAT_00517ab0[];
extern "C" char DAT_00517ac0[];
extern "C" char DAT_00517ad0[];
extern "C" char DAT_00517ae0[];
extern "C" void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *t);
extern "C" int DAT_00517a48[4];
extern "C" int DAT_00517af8[4];
extern "C" int FUN_003eca00(beNDMWLoadIntf2MesWin *arg0, int arg1, int arg2, int arg3);
extern "C" void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *arg0);
extern "C" void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *arg0);
extern "C" void beNDMWLoadIntf2MesWin__RequestMessage(beNDMWLoadIntf2MesWin *arg0, int arg1);
extern "C" void beNDMWLoadIntf2MesWin__RequestQuestion(beNDMWLoadIntf2MesWin *arg0, int arg1, int arg2);
extern "C" void beNDMWLoadIntf2MesWin__RequestPrompt(beNDMWLoadIntf2MesWin *arg0, int arg1);
extern "C" int DAT_00517a60[4];
extern "C" int DAT_00517af0[4];
extern "C" void beNDMWLoadIntf2MesWin__Cancel(beNDMWLoadIntf2MesWin *arg0);
extern "C" unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *p);
extern "C" int beNDMWLoadIntf2MesWin__GetCurPoint(beNDMWLoadIntf2MesWin *p);
extern "C" void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *arg0);
extern "C" void beNDMWLoadIntf2MesWin__RequestSystemMessage(beNDMWLoadIntf2MesWin *arg0, int arg1);
extern "C" void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *arg0);
extern "C" void FUN_003ecc60(beNDMWLoadCtrl2CommonIntf *arg0);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int DAT_00517e38[4];
extern "C" int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int g_beFont_metaObject[4];
extern "C" unsigned char GPR_00554c14;
typedef igObject Rc;
/* matching construct: the code reads the reference count as a signed int (igObject._refCount is reflected unsigned) */

struct Node { int p[8]; int f32; int st0; int st1; int st2; int st3; };
struct Meta { int p[2]; int f8; };
class SlotPlayerRef {
public:
    Rc *p;
    SlotPlayerRef(Rc *o) : p(o) {}
    ~SlotPlayerRef() { Rc *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
/* Owning stack reference to one Digimon record (a new one appended to the slot player, then each
 * one re-read from its list): released at the end of each loop pass. Its destructor is emitted out
 * of line. */
class DegiDataRef {
public:
    Rc *p;
    DegiDataRef(Rc *o) : p(o) {}
    ~DegiDataRef() { Rc *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
extern "C" int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *self, int idx, int unused, int val, int mode);
typedef struct C { char pad0[8]; int f8; } C;
extern "C" int DAT_00517e48[4];
extern "C" int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *o, int idx, int arg2, int arg3, int mode);
extern "C" void FUN_003ee190(beNDMWLoadCtrl2CommonIntf *self, int idx);
extern "C" void beNDMWLoadCtrl2CommonIntf__StartUtilFor(beNDMWLoadCtrl2CommonIntf *a, int arg1, int arg2);
extern "C" void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *w, int key);
extern "C" int g_stringPool[4];
typedef struct S { unsigned char b0; char p0[3]; int f4; char p1[32]; unsigned short s40[9]; char p2[14]; int f72, f76, f80, f84, f88; } S;
extern "C" void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *a);
extern "C" void FUN_003ee690(beNDMWDegiData *arg0, int arg1);
/* Property-record loader. Copies the scalar, string, id-list and index-list records of the property
 * set arg1 into the data block of the beNDMWDegiData arg0 (its _data field, +28), then calls
 * beNDMWDegiData__UpdateFieldsFromData(arg0). PropDest is a private view of that block.
 */



class IdObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22();
    virtual int GetId();
};
struct StrObj : public igObject { int p8; unsigned short *chars; };
struct PropByteRecord { int p[3]; unsigned char v; };
struct PropIntRecord { int p[3]; int v; };
struct PropObjListRecord { int p[3]; igObjectList *v; };
struct PropByteListRecord { int p[3]; igTDataList<unsigned char> *v; };
struct PropIntListRecord { int p[3]; igIntList *v; };
struct PropStrListRecord { int p[3]; igStringObjList *v; };
struct PropDest {
    unsigned char b0; char p1[3]; int f4; int f8[8]; unsigned short s40[9]; char p58[14];
    int f72, f76, f80, f84, f88, f92, f96;
    int ids100[36]; int ids244[12]; unsigned char b292[52]; int ids344[96];
    int f728; int idx732[3]; int idx744[5]; int f764; int idx768[5]; int f788;
    unsigned char b792[1024]; unsigned char b1816[12]; int w1828[16]; unsigned char b1892[16];
    int w1908[16]; int w1972[16]; int w2036[16]; char pad2100[512]; int w2612[16];
};
extern "C" PropByteRecord * igProperty_GetRecordByte(...);
extern "C" PropIntRecord * igProperty_GetRecord(...);
extern "C" PropObjListRecord * igProperty_GetRecordFolder(...);
extern "C" PropByteListRecord * igProperty_GetRecordArray(...);
extern "C" PropStrListRecord * FUN_003a92e0(...);
extern "C" PropIntListRecord * FUN_003a9250(...);
extern "C" int DAT_00517e58[4];
extern "C" int DAT_00517e60[4];
extern "C" int DAT_00517e68[4];
extern "C" int DAT_00517e70[4];
extern "C" int DAT_00517e78[4];
extern "C" int DAT_00517e80[4];
extern "C" int DAT_00517e88[4];
extern "C" int DAT_00517e90[4];
extern "C" int DAT_00517ea0[4];
extern "C" int DAT_00517eb0[4];
extern "C" int DAT_00517eb8[4];
extern "C" int DAT_00517ec0[4];
extern "C" int DAT_00517ed0[4];
extern "C" int DAT_00517ee0[4];
extern "C" int DAT_00517ef0[4];
extern "C" int DAT_00517f00[4];
extern "C" int DAT_00517f08[4];
extern "C" int DAT_00517f18[4];
extern "C" int DAT_00517f28[4];
extern "C" int DAT_00517f38[4];
extern "C" int DAT_00517f48[4];
extern "C" int DAT_00517f50[4];
extern "C" int DAT_00517f60[4];
extern "C" int DAT_00517f70[4];
extern "C" int DAT_00517f80[4];
extern "C" int DAT_00517f90[4];
extern "C" int DAT_00517fa0[4];
extern "C" int DAT_00517fb0[4];
extern "C" int DAT_00517fc0[4];
extern "C" void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *arg0, int arg1);
/* Copy a saved-record block (arg0->saved) into the property tree arg1.
 * Matching constructs: the held item/chunk objects are RAII holders (ChunkRef, ItemRef) so the unwind
 * table names the right destructors. */

static inline int countOf_3ef5d0(const igObjectList *l) { return l->_count; }
struct Obj { int word0; int references; };
struct H {
    static inline void Rel(Obj *o) {
        if (o) {
            --o->references;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0)
                igObject_Destroy((void *)o);
        }
    }
};
/* matching construct: one RAII releasing holder per retail destructor copy; the cleanup table at 0x544c5c names 0x3832d0 (chunk buffer) and 0x1363f0 (list element / created item) */
struct ChunkRef { Obj *p; ChunkRef(Obj *x) : p(x) {} ~ChunkRef() { Obj *o = p; if (o != 0) { --o->references; if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy((void *)o); } } };
struct ItemRef { Obj *p; ItemRef() {} ItemRef(Obj *x) : p(x) {} ItemRef(Obj *x, RetainReference) : p(x) { Obj *o = p; if (o != 0) ++o->references; } ~ItemRef() { Obj *o = p; if (o != 0) { --o->references; if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) igObject_Destroy((void *)o); } } };
struct Lst {
    static inline void ReleaseAll(igObjectList *l) {
        int n = l->_count;
        int i;
        for (i = 0; i < n; i++)
            H::Rel(((Obj **)l->_data)[i]);
    }
    static inline void ZeroAll(igObjectList *l) {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++)
            ((Obj **)l->_data)[j] = 0;
    }
    static inline void Clear(igObjectList *l) {
        if (countOf_3ef5d0(l) > 0) {
            ReleaseAll(l);
            ZeroAll(l);
            l->_count = 0;
        }
    }
};
struct Chunk { int word0; int references; int count; unsigned short *chars; };
struct RecByte { int w0, w1, w2; unsigned char value; };
struct RecInt { int w0, w1, w2; int value; };
struct RecStr { int w0, w1, w2; char *value; };
struct RecLst { int w0, w1, w2; igObjectList *value; };
struct RecArr8 { int w0, w1, w2; igUnsignedCharList *value; };
struct RecArr32 { int w0, w1, w2; igIntList *value; };
struct Saved {
    unsigned char b0; char pad1[3];
    int i4;
    char name[32];
    struct Str16 { unsigned short sel; unsigned short chars[15]; } nm;
    int i72, i76, i80, i84, i88, i92, i96;
    int l0[36];
    int l1[12];
    unsigned char a0[50]; char pad3[2];
    int l2[96];
    int i728;
    int l3[3];
    int l4[5];
    int i764;
    int l5[5];
    int i788;
    unsigned char a1[1024];
    unsigned char a2[12];
    int a3[16];
    unsigned char a4[16];
    int a5[16];
    int a6[16];
    int a7[144];
    int a8[176];
};
struct Host { int w0[7]; Saved *saved; int w1[5]; int dword52; };
extern "C" Chunk *FUN_003614f0(int);
extern "C" void beUnicodeObj_AllocateBuffer(Chunk *, int);
extern "C" ItemRef FUN_003ef1e0(void *owner, int id);
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" void beNDMWDegiData__StoreToProperties(Host *arg0, void *arg1, int arg2);
typedef struct E_3f0d60 { char pad28[28]; int a28; char pad36[4]; int a36; } E_3f0d60;
typedef struct L { char pad8[8]; int n; char pad12[4]; E_3f0d60 **data; } L;
typedef struct O { char pad12[12]; L *list; } O;
extern "C" void FUN_003f0d60(O *arg0, int arg1, int arg2, E_3f0d60 *arg3);
extern "C" void FUN_003f0e30(beNDMWLoadSlotPlayer *arg0, int arg1);
extern "C" igObject *FUN_003c5aa0(int);
extern "C" igObject *FUN_003c5cf0(int);
extern "C" igObject *FUN_003c5ee0(int);
/* Owning stack reference to a new slot window of one of the three slot classes (kind 0..2 follows
 * the arg2 case), released on scope exit (reference count in the low 23 bits of _refCount). */
template <int kind> class SlotRef {
public:
    igObject *p;
    SlotRef(igObject *o) : p(o) {}
    ~SlotRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
extern "C" void FUN_003f0ed0(beNDMWMcUtilCtrl *arg0, int arg1, int arg2);
extern "C" int DAT_00517fd0[4];
extern "C" int DAT_00517fe0[4];
extern "C" void FUN_003f1270(beNDMWMcUtilCtrl *arg0);
extern "C" int DAT_00517ff0[4];
extern "C" unsigned char FUN_003f12f0(beNDMWMcUtilCtrl *arg0);
extern "C" int DAT_00517ff8[4];
extern "C" void FUN_003f1380(beNDMWMcUtilCtrl *arg0);
extern "C" bool FUN_003f13d0(beNDMWMcUtilCtrl *arg0);
extern "C" void FUN_003f1460(beNDMWMcUtilCtrl *arg0, int arg1, int arg2);
extern "C" int DAT_00518000[4];
extern "C" int DAT_00518010[4];
extern "C" int DAT_00518030[4];
extern "C" int DAT_00518048[4];
extern "C" int DAT_00518060[4];
extern "C" int DAT_00518080[4];
extern "C" int DAT_005180a0[4];
extern "C" int DAT_005180c0[4];
extern "C" int DAT_005180e0[4];
extern "C" int DAT_005180f0[4];
extern "C" int DAT_005180f8[4];
extern "C" beSvDeliver * beMessenger_GetObject(...);
extern "C" void FUN_003f1490(beNDMWMcUtilCtrl *op);
extern "C" int g_beNDMWLoadCtrl2Info_metaObject[4];
extern "C" int g_beNDMWLoadCtrl2_metaObject[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" int LOADCTRL2[4];
extern "C" void Gap__Bec__beNDMWLoadCtrl2__vfunc_32(beNDMWLoadCtrl2 *self);
extern "C" void Gap__Bec__beNDMWLoadCtrl2__vfunc_29(beNDMWLoadCtrl2 *self, int info);
struct S_ref;
struct Host_3f1a80;
extern "C" int DAT_00518130[4];
extern "C" int DAT_00518138[4];
extern "C" int DAT_00518148[4];
extern "C" int DAT_00518158[4];
extern "C" int DAT_00518160[4];
extern "C" int DAT_00518170[4];
extern "C" int DAT_00518178[4];
extern "C" int DAT_00518188[4];
extern "C" int DAT_00518198[4];
extern "C" int DAT_005181a8[4];
extern "C" int DAT_005181b8[4];
extern "C" int DAT_005181c8[4];
extern "C" int DAT_005181d0[4];
extern "C" int DAT_005181e0[4];
extern "C" int DAT_005181e8[4];
extern "C" int DAT_005181f8[4];
extern "C" int DAT_00518208[4];
extern "C" int DAT_00518218[4];
extern "C" int DAT_00518220[4];
extern "C" int DAT_00518230[4];
extern "C" int DAT_00518240[4];
extern "C" int DAT_00518250[4];
extern "C" int DAT_00518260[4];
extern "C" int DAT_00518270[4];
extern "C" int DAT_00518280[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_beLua_metaObject[4];
struct S_ref : public igObject { };
struct Host_3f1a80 { char pad40[40]; S_ref *f40; };
extern "C" void Gap__Bec__beNDMWLoadCtrl2__vfunc_31(beNDMWLoadCtrl2 *arg0, Host_3f1a80 *arg1);
extern "C" igObject *FUN_003c7a40(int);
extern "C" igObject *FUN_003c4be0(int);
extern "C" igObject *FUN_003c56b0(int);
struct Rec { char p[12]; unsigned char b12; };
extern "C" int DAT_005182a0[4];
extern "C" int DAT_005182b0[4];
extern "C" int g_beSystem_metaObject[4];
/* Owning stack references while the controller list is wired up; each releases its object on scope
 * exit. */

class CtrlDataRef {
public:
    igObject *p;
    CtrlDataRef(igObject *o) : p(o) {}
    ~CtrlDataRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class CommonIntfRef {
public:
    igObject *p;
    CommonIntfRef(igObject *o) : p(o) {}
    ~CommonIntfRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class FlagWorkRef {
public:
    igObject *p;
    FlagWorkRef(igObject *o) : p(o) {}
    ~FlagWorkRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Releases an object reference, used for the old list during the list install. */
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if ((object->_refCount & 0x7fffff) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" int Gap__Bec__beNDMWLoadCtrl2__vfunc_34(beNDMWLoadCtrl2 *arg0, beBaseInfoRam *arg1, beBaseInfo *arg2);

void TextOrder_Configure(beNDMWLoadIntf2TextOrder *arg0, char *arg1, char *arg2, char *arg3, int arg4, int arg5) {
    switch (arg4) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_AppendString(arg0->_messenger, ((char *)DAT_005179b8));
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_005179c0));
        break;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_AppendString(arg0->_messenger, ((char *)DAT_005179c8));
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_005179c0));
        break;
    case 2:
        beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_AppendString(arg0->_messenger, ((char *)DAT_005179d0));
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_005179c0));
        break;
    }
    switch (arg5) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_005179d8));
        break;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, arg2);
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_005179e8));
        break;
    case 2:
        break;
    }
    beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg3);
    beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_005179f8));
    beMessenger_SelectReceivers(arg0->_messenger, ((char *)DAT_005179b0), 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, ((char *)DAT_00517a00));
    beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_00517a08));
}

void TextOrder_PublishLine(S0 *arg0, int *arg1, int *arg2) {
    beMessenger_SelectReceivers(arg0->f10, &DAT_005179b0[0], 0, -1);
    beMessenger_AppendString(arg0->f10, arg1);
    beMessenger_AppendString(arg0->f10, arg2);
    beMessenger_AppendString(arg0->f10, &DAT_00517a10[0]);
    beMessenger_DispatchSelected(arg0->f10, &DAT_00517a08[0]);
}

void TextOrder_ConfigureFont(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    TextOrder_Configure((beNDMWLoadIntf2TextOrder *)arg0, (char *)arg1, (char *)(((E *)DAT_004ceb30)[arg2].w[arg3]), (char *)arg4, (int)arg5, (int)arg6);
}

void TextOrder_ClearFont(int arg0, const char *arg1, int arg2, int arg3) {
    TextOrder_PublishLine((S0 *)arg0, (int *)arg1, (int *)(((E_3ebdc0 *)DAT_004ceb30)[arg2].f[arg3]));
}

void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *arg0, int arg1, int arg2) {
    int s0;
    int s2;
    int i;
    int off;
    int v;
    int *e;
    int *p;
    s2 = -1;
    i = 0;
    e = ((int *)DAT_004cda40);
    for (;;) {
        v = *e;
        if (v == -1) break;
        if ((v & 0xFFFFF) == arg1) { s2 = i; break; }
        e += 3;
        i++;
    }
    if (s2 != -1) {
        off = s2 * 12;
        p = (int *)*(int *)((char *)DAT_004cda48 + off);
        for (;;) {
            if (p[0] == 0) break;
            TextOrder_PublishLine((S0 *)arg0, (int *)p[0], (int *)((&((int *)DAT_004ceb30)[p[1] * 20])[p[2]]));
            p += 3;
        }
        s0 = arg1 & 0xF000;
        g_txtCallNo[0] = *(int *)((char *)DAT_004cda44 + off);
        g_mdlEntity[0] = 0;
        switch (s0) {
        case 0:
            beLua__RunNamedChunk(arg0->_lua, DAT_00517a18, 0);
            break;
        case 0x1000:
        case 0x2000:
        case 0x3000:
            beLua__RunNamedChunk(arg0->_lua, DAT_00517a28, 0);
            break;
        }
        if (arg2 == 1 && (*(int *)((char *)((int *)DAT_004cda40) + off) & 0x100000)) {
            g_txtCallNo[0] = *(int *)((char *)DAT_004cda44 + (s2 + 1) * 12);
            g_mdlEntity[0] = 0;
            switch (s0) {
            case 0:
                beLua__RunNamedChunk(arg0->_lua, DAT_00517a18, 0);
                break;
            case 0x1000:
            case 0x2000:
            case 0x3000:
                beLua__RunNamedChunk(arg0->_lua, DAT_00517a28, 0);
                break;
            }
        }
    }
}

void TextOrder_PublishLineListOnly(int arg0, int arg1) {
    struct E_3ec050 *e; int i; struct Q *q;
    i = 0;
    e = DAT_004cda40;
    for (;;) { if (e->id == arg1) break; e = e + 1; i = i + 1; }
    if (i != -1) {
        q = DAT_004cda40[i].list;
        for (;;) {
            if (q->a == 0) break;
            TextOrder_PublishLine((S0 *)arg0, (int *)q->a, (int *)(((struct R *)DAT_004ceb30)[q->b].w[q->c]));
            q = q + 1;
        }
    }
}

void FUN_003ec120(beNDMWLoadIntf2TextOrder *arg0, int *arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int *temp_s0;

    beMessenger_SelectGroup(arg0->_messenger, &DAT_005179b0[0]);
    beMessenger_AppendObject(arg0->_messenger, arg4);
    beMessenger_AppendInt(arg0->_messenger, 0x3F);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517a38[0]);
    temp_s0 = DAT_004ceb30[arg2][arg3];
    switch (arg5) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_AppendString(arg0->_messenger, &DAT_005179b8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179c0[0]);
        break;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_AppendString(arg0->_messenger, &DAT_005179c8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179c0[0]);
        break;
    case 2:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_AppendString(arg0->_messenger, &DAT_005179d0[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179c0[0]);
        break;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005179b0[0]);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, temp_s0);
    beMessenger_AppendObject(arg0->_messenger, arg4);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179f8[0]);
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, temp_s0);
    beMessenger_AppendString(arg0->_messenger, &DAT_00517a00[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517a08[0]);
    switch (arg6) {
    case 0:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179d8[0]);
        return;
    case 1:
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_005179b0[0], 0, -1);
        beMessenger_AppendString(arg0->_messenger, arg1);
        beMessenger_AppendString(arg0->_messenger, temp_s0);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005179e8[0]);
    case 2:
        ;
    }
}

void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *t) {
    int s;
    if (t->_isWinOpen == 1) {
        if (t->_isSystemMes != 1) {
            if (t->_isCtrl == 1) {
                switch (t->_kindCtrl) {
                case 0:
                    switch (t->_statCtrl) {
                    case 0:
                        if (t->_curPoint == 0) {
                            beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517a70);
                        } else {
                            beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517a80);
                        }
                        t->_statCtrl = t->_statCtrl + 1;
                        break;
                    case 1: {
                        bePadData *pad = bePadManager_GetPadForPlayer(t->_padManager, t->_ramNo, 1);
                        int a3 = pad->_trigger;
                        int a2 = pad->_repeat;
                        int a0 = pad->_lTrg | pad->_lRpt;
                        bool a1 = true;
                        if (!(a0 & 1) && !((a3 | a2) & 0x10)) a1 = false;
                        bool a0b = true;
                        if (!(a0 & 4) && !((a3 | a2) & 0x40)) a0b = false;
                        if (a1) {
                            if (t->_curPoint == 1) {
                                t->_curPoint = 0;
                                beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517a90);
                                t->_statCtrl = 2;
                            }
                        } else if (a0b) {
                            if (t->_curPoint == 0) {
                                t->_curPoint = 1;
                                beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517aa0);
                                t->_statCtrl = 3;
                            }
                        } else if (a3 & 0x4000) {
                            if (t->_curPoint == 0) {
                                beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517ab0);
                            } else {
                                beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517ac0);
                            }
                            t->_statCtrl = 4;
                        }
                        break;
                    }
                    case 2:
                        if (!(FUN_003eca00((beNDMWLoadIntf2MesWin *)t, (int)t->_ramNo, (int)(((char *)DAT_00517a60)), (int)DAT_00517a90) & 0xFF)) t->_statCtrl = 1;
                        break;
                    case 3:
                        if (!(FUN_003eca00((beNDMWLoadIntf2MesWin *)t, (int)t->_ramNo, (int)(((char *)DAT_00517a60)), (int)DAT_00517aa0) & 0xFF)) t->_statCtrl = 1;
                        break;
                    case 4:
                        if (t->_curPoint == 0) {
                            if (!(FUN_003eca00((beNDMWLoadIntf2MesWin *)t, (int)t->_ramNo, (int)(((char *)DAT_00517a60)), (int)DAT_00517ab0) & 0xFF)) {
                                beNDMWLoadIntf2MesWin__RequestMesErase((beNDMWLoadIntf2MesWin *)t);
                                t->_isSelect = 1;
                                t->_isCtrl = 0;
                            }
                        } else if (!(FUN_003eca00((beNDMWLoadIntf2MesWin *)t, (int)t->_ramNo, (int)(((char *)DAT_00517a60)), (int)DAT_00517ac0) & 0xFF)) {
                            beNDMWLoadIntf2MesWin__RequestMesErase((beNDMWLoadIntf2MesWin *)t);
                            t->_isSelect = 1;
                            t->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                case 1:
                    switch (t->_statCtrl) {
                    case 0:
                        beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517ad0);
                        t->_statCtrl = t->_statCtrl + 1;
                        break;
                    case 1:
                        if (bePadManager_GetPadForPlayer(t->_padManager, t->_ramNo, 1)->_trigger & 0x4000) {
                            beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, DAT_00517ae0);
                            t->_statCtrl = t->_statCtrl + 1;
                        }
                        break;
                    case 2:
                        if (!(FUN_003eca00((beNDMWLoadIntf2MesWin *)t, (int)t->_ramNo, (int)(((char *)DAT_00517a60)), (int)DAT_00517ae0) & 0xFF)) {
                            beNDMWLoadIntf2MesWin__RequestMesErase((beNDMWLoadIntf2MesWin *)t);
                            t->_isSelect = 1;
                            t->_isCtrl = 0;
                        }
                        break;
                    }
                    break;
                }
            }
        } else {
            switch (t->_sysStat) {
            case 0:
                beMessenger_SendNamed(t->_messenger, ((char *)DAT_00517a48), ((char *)DAT_00517a60), t->_ramNo, ((char *)DAT_00517af0));
                t->_sysStat = t->_sysStat + 1;
                break;
            case 1:
                break;
            }
        }
        if (t->_isMesCom == 1) {
            if (t->_isSystemMes == 1) {
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)t->_textOrder, (int)t->_sysMesNo, 1);
            } else if (t->_isMesErase == 0) {
                t->_isDisp = 1;
                beNDMWLoadIntf2TextOrder_PublishIdLines((beNDMWLoadIntf2TextOrder *)t->_textOrder, (int)t->_mesNo, 1);
            } else {
                s = 0;
                do {
                    TextOrder_ClearFont((int)t->_textOrder, (const char *)DAT_005176a0, (int)t->_ramNo, (int)s);
                    s += 1;
                } while (s < 4);
                s = 4;
                do {
                    TextOrder_ClearFont((int)t->_textOrder, (const char *)DAT_005176b0, (int)t->_ramNo, (int)(s - 4));
                    s += 1;
                } while (s < 6);
                t->_isMesErase = 0;
                t->_isDisp = 0;
                if (t->_isWinClose == 1) {
                    t->_isWinOpen = 0;
                }
            }
            t->_isMesCom = 0;
        }
    }
}

int FUN_003eca00(beNDMWLoadIntf2MesWin *arg0, int arg1, int arg2, int arg3) {
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00517a48[0], arg2, arg1);
    beMessenger_AppendString(arg0->_messenger, arg3);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517af8[0]);
    return beMessenger_GetBool(arg0->_messenger, 0);
}

void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isWinOpen = 1;
    arg0->_isWinClose = 0;
    arg0->_isSelect = 0;
    arg0->_isCtrl = 0;
    arg0->_isSystemMes = 0;
    arg0->_isMesErase = 0;
    arg0->_isMesCom = 0;
}

void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *arg0) {
    beNDMWLoadIntf2MesWin__RequestMesErase((beNDMWLoadIntf2MesWin *)((beNDMWLoadIntf2MesWin *)arg0));
    arg0->_isWinClose = 1;
}

void beNDMWLoadIntf2MesWin__RequestMessage(beNDMWLoadIntf2MesWin *arg0, int arg1) {
    arg0->_isMesCom = 1;
    arg0->_mesNo = arg1;
}

void beNDMWLoadIntf2MesWin__RequestQuestion(beNDMWLoadIntf2MesWin *arg0, int arg1, int arg2) {
    arg0->_isMesCom = 1;
    arg0->_isCtrl = 1;
    arg0->_mesNo = arg1;
    arg0->_curPoint = arg2;
    arg0->_statCtrl = 0;
    arg0->_kindCtrl = 0;
}

void beNDMWLoadIntf2MesWin__RequestPrompt(beNDMWLoadIntf2MesWin *arg0, int arg1) {
    arg0->_isMesCom = 1;
    arg0->_isCtrl = 1;
    arg0->_mesNo = arg1;
    arg0->_statCtrl = 0;
    arg0->_kindCtrl = 1;
}

void beNDMWLoadIntf2MesWin__Cancel(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isCtrl = 0;
    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00517a60[0], arg0->_ramNo, &DAT_00517af0[0]);
    beNDMWLoadIntf2MesWin__RequestMesErase(arg0);
}

/* Reads the _isCtrl flag (+34), the byte beNDMWLoadIntf2MesWin__RequestQuestion/beNDMWLoadIntf2MesWin__RequestPrompt set to 1 when a choice/continue
 * message opens. */
unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *p)
{
    return p->_isCtrl;
}

int beNDMWLoadIntf2MesWin__GetCurPoint(beNDMWLoadIntf2MesWin *p)
{
    return p->_curPoint;
}

void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isMesErase = 1;
    arg0->_isMesCom = 1;
}

void beNDMWLoadIntf2MesWin__RequestSystemMessage(beNDMWLoadIntf2MesWin *arg0, int arg1) {
    arg0->_isMesCom = 1;
    arg0->_isSystemMes = 1;
    arg0->_sysMesNo = arg1;
    arg0->_sysStat = 0;
}

void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *arg0) {
    arg0->_isSystemMes = 0;
    if (arg0->_isDisp == 1) {
        if (arg0->_isCtrl == 1) {
            switch (arg0->_kindCtrl) {
            case 0:
                beNDMWLoadIntf2MesWin__RequestQuestion(arg0, arg0->_mesNo, arg0->_curPoint);
                return;
            case 1:
                beNDMWLoadIntf2MesWin__RequestPrompt(arg0, arg0->_mesNo);
                return;
            }
        } else {
            beNDMWLoadIntf2MesWin__RequestMessage(arg0, arg0->_mesNo);
        }
    } else {
        beNDMWLoadIntf2MesWin__RequestMesErase(arg0);
    }
}

void FUN_003ecc60(beNDMWLoadCtrl2CommonIntf *arg0) {
    int i;
    int j;
    igIntList *il;
    int k;
    FUN_003f1490((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl);
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[0]->_isCutConnect = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[1]->_isCutConnect = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[2]->_isCutConnect = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[3]->_isCutConnect = 0;
    for (i = 0; i < ((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)*(int *)&arg0->_mcUtilCtrl)->_slot)->_count; i++) {
        if (((beNDMWMcSlotPS2 **)((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl)->_slot)->_data)[i]->_isConnect == 0) {
            for (j = 0; j < ((beNDMWLoadSlotPlayerList *)arg0->_slotSaveData)->_count; j++) {
                if (i == ((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)arg0->_slotSaveData)->_data)[j]->_connectNO) {
                    il = (igIntList *)((beNDMWLoadSlotPlayer **)((beNDMWLoadSlotPlayerList *)arg0->_slotSaveData)->_data)[j]->_accessPlList;
                    for (k = 0; k < il->_count; k++) {
                        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)arg0->_flagWork)->_data)[((int *)il->_data)[k]]->_isCutConnect = 1;
                    }
                }
            }
        }
    }
}

int beNDMWLoadCtrl2CommonIntf__StepNoticeQuestion(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int temp_v0;
    int var_s1;
    int var_s0;
    beNDMWLoadSavePlWork *temp_v0_2;
    beNDMWLoadSavePlWork *temp_v0_3;
    beNDMWLoadSavePlWork *temp_v0_4;

    var_s1 = 0;
    var_s0 = 0;
    switch (arg6) {
    case 0:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat0;
        break;
    case 1:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat1;
        break;
    case 2:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat2;
        break;
    case 3:
        var_s0 = (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat3;
        break;
    }
    switch (var_s0) {
    case 0:
        beNDMWLoadIntf2MesWin__RequestPrompt((beNDMWLoadIntf2MesWin *)arg2, arg3);
        var_s0 += 1;
        break;
    case 1:
        if (!(((int)beNDMWLoadIntf2MesWin__GetIsCtrl((beNDMWLoadIntf2MesWin *)arg2)) & 0xFF)) {
            var_s0 += 1;
        }
        break;
    case 2:
        beNDMWLoadIntf2MesWin__RequestQuestion((beNDMWLoadIntf2MesWin *)arg2, arg4, arg5);
        var_s0 += 1;
        break;
    case 3:
        if (!(((int)beNDMWLoadIntf2MesWin__GetIsCtrl((beNDMWLoadIntf2MesWin *)arg2)) & 0xFF)) {
            temp_v0 = beNDMWLoadIntf2MesWin__GetCurPoint((beNDMWLoadIntf2MesWin *)arg2);
            switch (temp_v0) {
            case 0:
                var_s1 = 1;
                break;
            case 1:
                var_s1 = 2;
                break;
            }
        }
        break;
    }
    switch (arg6) {
    case 0:
        temp_v0_2 = (beNDMWLoadSavePlWork *)(((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1]);
        temp_v0_2->_sysStat0 = var_s0;
        temp_v0_2->_sysStat3 = 0;
        temp_v0_2->_sysStat2 = 0;
        temp_v0_2->_sysStat1 = 0;
        break;
    case 1:
        temp_v0_3 = (beNDMWLoadSavePlWork *)(((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1]);
        temp_v0_3->_sysStat1 = var_s0;
        temp_v0_3->_sysStat3 = 0;
        temp_v0_3->_sysStat2 = 0;
        break;
    case 2:
        temp_v0_4 = (beNDMWLoadSavePlWork *)(((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1]);
        temp_v0_4->_sysStat2 = var_s0;
        temp_v0_4->_sysStat3 = 0;
        break;
    case 3:
        (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(arg0->_flagWork))->_data)[arg1])->_sysStat3 = var_s0;
        break;
    }
    return var_s1;
}

int beNDMWLoadCtrl2CommonIntf__StepCheckMemoryCard(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4) {
    int s1;
    int s0;
    beNDMWMcUtilCtrl *m;
    s1 = 0;
    s0 = 0;
    switch (arg4) {
    case 0: s0 = PLW(arg0, arg1)->_sysStat0; break;
    case 1: s0 = PLW(arg0, arg1)->_sysStat1; break;
    case 2: s0 = PLW(arg0, arg1)->_sysStat2; break;
    case 3: s0 = PLW(arg0, arg1)->_sysStat3; break;
    }
    switch (s0) {
    case 0:
        FUN_003f1460((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl, 3, arg3);
        s0 += 1;
        break;
    case 1:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s0 += 1; break;
            default: s1 = 2; break;
            }
        }
        break;
    case 2:
        FUN_003f1460((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl, 1, arg3);
        s0 += 1;
        break;
    case 3:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s1 = 1; break;
            default: s1 = 2; break;
            }
        }
        break;
    }
    switch (arg4) {
    case 0: {
        beNDMWLoadSavePlWork *r = PLW(arg0, arg1);
        r->_sysStat0 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break; }
    case 1: {
        beNDMWLoadSavePlWork *r = PLW(arg0, arg1);
        r->_sysStat1 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break; }
    case 2: {
        beNDMWLoadSavePlWork *r = PLW(arg0, arg1);
        r->_sysStat2 = s0; r->_sysStat3 = 0;
        break; }
    case 3:
        PLW(arg0, arg1)->_sysStat3 = s0;
        break;
    }
    return s1;
}

int beNDMWLoadCtrl2CommonIntf__StepCreateSaveFile(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4) {
    int s1;
    int s0;
    int a1;
    beNDMWLoadSavePlWork *r;
    beNDMWMcUtilCtrl *m;
    s1 = 0;
    s0 = 0;
    switch (arg4) {
    case 0: s0 = PLW(arg0, arg1)->_sysStat0; break;
    case 1: s0 = PLW(arg0, arg1)->_sysStat1; break;
    case 2: s0 = PLW(arg0, arg1)->_sysStat2; break;
    case 3: s0 = PLW(arg0, arg1)->_sysStat3; break;
    }
    switch (s0) {
    case 0:
        a1 = -1;
        switch (arg0->_kindHard) {
        case 0: a1 = (arg1 << 16) | 0x1003; break;
        case 1: a1 = (arg1 << 16) | 0x2003; break;
        case 2: a1 = (arg1 << 16) | 0x3003; break;
        }
        beNDMWLoadIntf2MesWin__RequestMessage((beNDMWLoadIntf2MesWin *)arg2, a1);
        FUN_003f1460((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl, 6, arg3);
        s0 += 1;
        break;
    case 1:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s0 += 1; break;
            default: s1 = 2; break;
            }
        }
        break;
    case 2:
        FUN_003f1460((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl, 0, arg3);
        beBaseInfoRam_StartTimer(arg0->_inforam, &DAT_00517e38[0], 0xB2D05E00ULL);
        s0 += 1;
        break;
    case 3:
        if (MCSLOT(arg0, arg3)->_isConnect == 1) {
            if ((beBaseInfoRam_IsTimerExpired(arg0->_inforam, &DAT_00517e38[0]) & 0xFF) == 1) {
                s0 += 1;
                goto L4;
            }
            break;
        } else {
            s0 += 1;
        }
    case 4:
    L4:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s1 = 1; break;
            default: s1 = 2; break;
            }
        }
        break;
    }
    switch (arg4) {
    case 0:
        r = PLW(arg0, arg1);
        r->_sysStat0 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break;
    case 1:
        r = PLW(arg0, arg1);
        r->_sysStat1 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break;
    case 2:
        r = PLW(arg0, arg1);
        r->_sysStat2 = s0; r->_sysStat3 = 0;
        break;
    case 3:
        PLW(arg0, arg1)->_sysStat3 = s0;
        break;
    }
    return s1;
}

/* Owning stack reference to the new slot player: constructed from the creating call and released
 * on scope exit (reference count in the low 23 bits of _refCount). Its destructor is emitted out
 * of line. */
static inline int countOf(const igIntList *list) { return list->_count; }

int beNDMWLoadCtrl2CommonIntf__StepReadMedia(beNDMWLoadCtrl2CommonIntf *self, int idx, int unused, int val, int mode) {
    int ret;
    int state;
    void *alloc;
    int n;
    igIntList *accessList;
    int i;
    int j;
    Node *node;
    unsigned short *unicodeText;
    int charIndex;
    int nextState;
    unsigned short *digimonName;

    ret = 0;
    state = 0;
    switch (mode) {
    case 0: state = NODE(self, idx)->st0; break;
    case 1: state = NODE(self, idx)->st1; break;
    case 2: state = NODE(self, idx)->st2; break;
    case 3: state = NODE(self, idx)->st3; break;
    }
    switch (state) {
    case 0:
        FUN_003f1460((beNDMWMcUtilCtrl *)self->_mcUtilCtrl, 4, (int)val);
        nextState = state + 1;
        goto storeState;
    case 1:
        if (CFG(self)->_isResult == 1) {
            ret = 2;
            switch (CFG(self)->_result) {
            case 2: {
                ret = 1;
                ALLOC(alloc, self);
                SlotPlayerRef grp((Rc *)beNDMWLoadSlotPlayer_Create(alloc));
                for (i = 0; i < 4; i++) {
                    ALLOC(alloc, self);
                    DegiDataRef tmp((Rc *)beNDMWDegiData_Create(alloc));
                    ObjectList_AppendRetained(GRP(grp.p)->_saveDataList, tmp.p);
                }
                FUN_003f0e30((beNDMWLoadSlotPlayer *)grp.p, (int)(((Meta *)CFG(self)->_svData)->f8));
                GRP(grp.p)->_connectNO = val;
                accessList = (igIntList *)GRP(grp.p)->_accessPlList;
                n = accessList->_count;
                if (n < accessList->_capacity) accessList->_count = countOf(accessList) + 1;
                else List_Resize(accessList, n + 1, 4);
                ((int *)accessList->_data)[n] = idx;
                ObjectList_AppendRetained(self->_slotSaveData, grp.p);
                for (j = 0; j < 4; j++) {
                    DegiDataRef el((Rc *)((beNDMWDegiData **)((igObjectList *)GRP(grp.p)->_saveDataList)->_data)[j]);
                    if (el.p != 0) REFS(el.p) = REFS(el.p) + 1;
                    if (DD(el.p)->_isUse == 1 && DNAME(DD(el.p))[0] != 0xFFFF) {
                        Rc *str; /* the unicode text FUN_00382eb0 hands back (declared here: its slot sits below the record reference) */
                        digimonName = (unsigned short *)DD(el.p)->_dmName;
                        {
                            int insightEntry = FUN_00236f80(self->_insight, g_beFont_metaObject[0]);
                            FUN_00382eb0(&str, insightEntry, digimonName);
                        }
                        unicodeText = (unsigned short *)((beUnicodeObj *)str)->_buffer;
                        for (charIndex = 0; ; ) {
                            ((unsigned short *)DD(el.p) + 5)[charIndex] /* matching construct: object-based index keeps the addu operand order */ = unicodeText[charIndex];
                            if (unicodeText[charIndex] == 0) break;
                            charIndex++;
                            if (charIndex >= 8) break;
                        }
                        for (; charIndex < 8; charIndex++) {
                            ((unsigned short *)DD(el.p) + 5)[charIndex] = 0;
                        }
                        DNAME(DD(el.p))[0] = 0xFFFF;
                        REL(str);
                    }
                }
                NODE(self, idx)->f32 = (int)grp.p;
                /* matching construct: leaving the block through this jump to the state store releases the slot
                 * player on the jump path, which keeps retail's branch after the release; falling out of the
                 * switch folds it away */
                nextState = state;
                goto storeState;
            }
            }
        }
        break;
    }
    nextState = state;
storeState:
    state = nextState;
    switch (mode) {
    case 0:
        node = NODE(self, idx);
        node->st0 = state;
        node->st3 = 0;
        node->st2 = 0;
        node->st1 = 0;
        break;
    case 1:
        node = NODE(self, idx);
        node->st1 = state;
        node->st3 = 0;
        node->st2 = 0;
        break;
    case 2:
        node = NODE(self, idx);
        node->st2 = state;
        node->st3 = 0;
        break;
    case 3:
        NODE(self, idx)->st3 = state;
        break;
    }
    return ret;
}

int beNDMWLoadCtrl2CommonIntf__StepWriteSaveData(beNDMWLoadCtrl2CommonIntf *arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int s1;
    int s0;
    beNDMWLoadSavePlWork *r;
    beNDMWMcUtilCtrl *m;
    s1 = 0;
    s0 = 0;
    switch (arg5) {
    case 0: s0 = PLW(arg0, arg1)->_sysStat0; break;
    case 1: s0 = PLW(arg0, arg1)->_sysStat1; break;
    case 2: s0 = PLW(arg0, arg1)->_sysStat2; break;
    case 3: s0 = PLW(arg0, arg1)->_sysStat3; break;
    }
    switch (s0) {
    case 0:
        FUN_003f0d60((O *)(PLW(arg0, arg1)->_haveSaveData), ((C *)MCU(arg0)->_svData)->f8, arg4, (E_3f0d60 *)(((int *)((beNDMWDegiDataList *)arg0->_gameUseData)->_data)[arg1]));
        FUN_003f1460((beNDMWMcUtilCtrl *)arg0->_mcUtilCtrl, 5, arg3);
        beBaseInfoRam_StartTimer(arg0->_inforam, &DAT_00517e48[0], 0xB2D05E00ULL);
        s0 += 1;
        break;
    case 1:
        if (MCSLOT(arg0, arg3)->_isConnect == 1) {
            if ((beBaseInfoRam_IsTimerExpired(arg0->_inforam, &DAT_00517e48[0]) & 0xFF) == 1) {
                s0 += 1;
                goto L2;
            }
            break;
        } else {
            s0 += 1;
        }
    case 2:
    L2:
        m = MCU(arg0);
        if (m->_isResult == 1) {
            switch (m->_result) {
            case 2: s1 = 1; FUN_003ee490((void *)(((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)PLW(arg0, arg1)->_haveSaveData)->_saveDataList)->_data)[arg4]), (void *)(((int *)((beNDMWDegiDataList *)arg0->_gameUseData)->_data)[arg1])); break;
            default: s1 = 2; break;
            }
        }
        break;
    }
    switch (arg5) {
    case 0:
        r = PLW(arg0, arg1);
        r->_sysStat0 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0; r->_sysStat1 = 0;
        break;
    case 1:
        r = PLW(arg0, arg1);
        r->_sysStat1 = s0; r->_sysStat3 = 0; r->_sysStat2 = 0;
        break;
    case 2:
        r = PLW(arg0, arg1);
        r->_sysStat2 = s0; r->_sysStat3 = 0;
        break;
    case 3:
        PLW(arg0, arg1)->_sysStat3 = s0;
        break;
    }
    return s1;
}

int beNDMWLoadCtrl2CommonIntf__StepFormatMemoryCard(beNDMWLoadCtrl2CommonIntf *o, int idx, int arg2, int arg3, int mode) {
    int r = 0;
    int v = 0;
    switch (mode) {
    case 0: v = PLW(o, idx)->_sysStat0; break;
    case 1: v = PLW(o, idx)->_sysStat1; break;
    case 2: v = PLW(o, idx)->_sysStat2; break;
    case 3: v = PLW(o, idx)->_sysStat3; break;
    }
    switch (v) {
    case 0:
        FUN_003f1460((beNDMWMcUtilCtrl *)o->_mcUtilCtrl, 2, arg3);
        v++;
        MCU(o)->_isFormatRun = 1;
        break;
    case 1: {
        beNDMWMcUtilCtrl *s = MCU(o);
        if (s->_isResult == 1) {
            switch (s->_result) { case 2: r = 1; break; default: r = 2; break; }
        }
        break;
    }
    }
    switch (mode) {
    case 0: {
        beNDMWLoadSavePlWork *it = PLW(o, idx);
        it->_sysStat0 = v;
        it->_sysStat3 = 0;
        it->_sysStat2 = 0;
        it->_sysStat1 = 0;
        break;
    }
    case 1: {
        beNDMWLoadSavePlWork *it = PLW(o, idx);
        it->_sysStat1 = v;
        it->_sysStat3 = 0;
        it->_sysStat2 = 0;
        break;
    }
    case 2: {
        beNDMWLoadSavePlWork *it = PLW(o, idx);
        it->_sysStat2 = v;
        it->_sysStat3 = 0;
        break;
    }
    case 3:
        PLW(o, idx)->_sysStat3 = v;
        break;
    }
    return r;
}

void FUN_003ee190(beNDMWLoadCtrl2CommonIntf *self, int idx) {
    int i;
    beNDMWLoadSavePlWork *e;
    i = 0;
    do {
        e = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[i];
        e->_sysStat0 = 1;
        e->_sysStat3 = 0;
        e->_sysStat2 = 0;
        e->_sysStat1 = 0;
        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[i]->_isCtrl = 0;
        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[i]->_sysCount0 = 60;
        i++;
    } while (i < 4);
    e = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx];
    e->_sysStat0 = 0;
    e->_sysStat3 = 0;
    e->_sysStat2 = 0;
    e->_sysStat1 = 0;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx]->_isCtrl = 1;
    ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)self->_flagWork)->_data)[idx]->_sysCount0 = 0;
}

void beNDMWLoadCtrl2CommonIntf__StartUtilFor(beNDMWLoadCtrl2CommonIntf *a, int arg1, int arg2) {
    int temp_a4;
    int var_a7;
    int var_a6;
    int *cnt;
    beNDMWLoadSavePlWork *temp_v1;
    beNDMWLoadSavePlWork *temp_v1_2;
    beNDMWLoadSavePlWork *temp_v1_3;

    var_a7 = 0;
    var_a6 = 0;
    do {
        temp_v1 = PLW_3ee250(a->_flagWork, var_a6);
        temp_v1->_sysStat0 = 1;
        temp_v1->_sysStat3 = 0;
        temp_v1->_sysStat2 = 0;
        temp_v1->_sysStat1 = 0;
        PLW_3ee250(a->_flagWork, var_a6)->_isCtrl = 0;
        temp_v1_2 = PLW_3ee250(a->_flagWork, var_a6);
        cnt = &temp_v1_2->_sysCount0;
        if (*cnt <= 0) {
            *cnt = 0xA;
        }
        var_a7 += 1;
        var_a6 += 4;
    } while (var_a7 < 4);
    temp_a4 = arg1 * 4;
    temp_v1_3 = PLW_3ee250(a->_flagWork, temp_a4);
    temp_v1_3->_sysStat0 = arg2;
    temp_v1_3->_sysStat3 = 0;
    temp_v1_3->_sysStat2 = 0;
    temp_v1_3->_sysStat1 = 0;
    PLW_3ee250(a->_flagWork, temp_a4)->_isCtrl = 1;
    PLW_3ee250(a->_flagWork, temp_a4)->_sysCount0 = 0;
    a->_utilUsePlNo = arg1;
}

void beNDMWLoadCtrl2CommonIntf__RemoveAccessPlayer(beNDMWLoadCtrl2CommonIntf *w, int key) {
    bool found = false;
    beNDMWLoadSlotPlayerList *l = (beNDMWLoadSlotPlayerList *)w->_slotSaveData;
    for (int i = l->_count - 1; i >= 0; i--) {
        int off; igIntList *in; int j; int n; igIntList *in2;
        in = (igIntList *)((beNDMWLoadSlotPlayer **)l->_data)[i]->_accessPlList; n = in->_count; in2 = in; j = 0;
        if (j < n) { off = 0;
          do { if (key == *(int*)(in2->_data + off)) { List_RemoveWordAt(in, j); found = true; break; } j++; off += 4; in2 = in; } while (j < n); }
        if (found == true) break;
    }
    if (found == true) {
        for (int i = l->_count - 1; i >= 0; i--) {
            beNDMWLoadSlotPlayer *e = ((beNDMWLoadSlotPlayer **)l->_data)[i];
            if (((igIntList *)e->_accessPlList)->_count == 0) {
                if (e != 0) {
                    e->_refCount = e->_refCount - 1;
                    if ((e->_refCount & 0x7FFFFF) == 0) igObject_Destroy(e);
                }
                List_RemoveWordAt(l, i);
                ((beNDMWLoadSlotPlayer **)l->_data)[l->_count] = 0;
            }
        }
    }
}

void FUN_003ee490(void *arg0, void *arg1)
{
  unsigned int new_var;
  new_var = *((int *) (((char *) arg0) + 36));
  memcpy(*((int *) (((char *) arg0) + 28)), *((int *) (((char *) arg1) + 28)), new_var);
  beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)arg0);
}

void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *a) {
    S *s0;
    int s2, v, old;
    int *hd;
    s0 = (S *)a->_data;
    a->_isUse = s0->b0;
    a->_lv = s0->f72;
    a->_hp = s0->f76;
    a->_maxHp = s0->f80;
    a->_mp = s0->f84;
    a->_maxMp = s0->f88;
    if (g_stringPool[0] == 0) {
        v = ((int)FUN_002eb010(16));
        if (v != 0) v = ((int)StringPool_Construct(v));
        g_stringPool[0] = v;
    }
    s2 = ((int)StringPool_Intern(g_stringPool[0], (char *)s0 + 8));
    old = a->_dmkind;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    a->_dmkind = s2;
    if (g_stringPool[0] == 0) {
        v = ((int)FUN_002eb010(16));
        if (v != 0) v = ((int)StringPool_Construct(v));
        g_stringPool[0] = v;
    }
    s2 = ((int)StringPool_Intern(g_stringPool[0], (char *)s0 + 40));
    old = a->_dmName;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    a->_dmName = s2;
    {
        int n;
        unsigned short *pa;
        char *p;
        pa = s0->s40;
        n = 0;
        p = (char *)a;
        a->_id = s0->f4;
        do {
            unsigned short v = *pa;
            if (v == 0) break;
            *(unsigned short *)(p + 8) = v;
            n += 1;
            pa += 1;
            p += 2;
        } while (n < 9);
        for (; n < 9; n++) {
            *(unsigned short *)((char *)a + n * 2 + 8) = 0;
        }
    }
}

/* The size reads as unsigned so it is issued before the copy of arg0. */

static inline unsigned dataSize(const beNDMWDegiData *data) { return data->_dataSize; }

void FUN_003ee690(beNDMWDegiData *arg0, int arg1) {
    memcpy(arg0->_data, arg1, dataSize(arg0));
    beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)arg0);
}

void beNDMWDegiData__LoadFromProperties(beNDMWDegiData *arg0, int arg1) {
    PropDest *d = (PropDest *)arg0->_data;
    d->b0 = igProperty_GetRecordByte(arg1, &DAT_00517e58[0])->v;
    d->f4 = igProperty_GetRecord(arg1, &DAT_00517e60[0])->v;
    d->f72 = igProperty_GetRecord(arg1, &DAT_00517e68[0])->v;
    d->f76 = igProperty_GetRecord(arg1, &DAT_00517e70[0])->v;
    d->f80 = igProperty_GetRecord(arg1, &DAT_00517e78[0])->v;
    d->f84 = igProperty_GetRecord(arg1, &DAT_00517e80[0])->v;
    d->f88 = igProperty_GetRecord(arg1, &DAT_00517e88[0])->v;
    {
        igStringObjList *sl = (igStringObjList *)igProperty_GetRecordFolder(arg1, &DAT_00517e90[0])->v;
        if (sl->_count != 0) {
            igSmartPointer<StrObj> s(((StrObj **)sl->_data)[0]);
            if (s.p != 0) s.p->_refCount = s.p->_refCount + 1;
            {
                unsigned short *src;
                unsigned short *base;
                int i;
                unsigned short *dst;
                base = &d->s40[0];
                i = 0;
                dst = base;
                src = s.p->chars;
            L1: dst[1] = *src;
                if (*src == 0) { dst = base + i; goto T; }
                src++; dst++; i++; goto L1;
            B:  dst[1] = 0; dst++; i++;
            T:  if (i < 8) goto B;
                base[0] = 0xffff;
            }
        }
    }
    {
        PropStrListRecord *rs = FUN_003a92e0(arg1, &DAT_00517ea0[0]);
        void *str = (void *)rs->v;
        if (str != 0) strcpy(&d->f8[0], str);
    }
    d->f92 = igProperty_GetRecord(arg1, &DAT_00517eb0[0])->v;
    d->f96 = igProperty_GetRecord(arg1, &DAT_00517eb8[0])->v;
    IDS(d->ids100, &DAT_00517ec0[0], 36, 1)
    IDS(d->ids244, &DAT_00517ed0[0], 12, 1)
    BYTES(d->b292, igProperty_GetRecordArray, &DAT_00517ee0[0])
    IDS(d->ids344, &DAT_00517ef0[0], 96, 0)
    d->f728 = igProperty_GetRecord(arg1, &DAT_00517f00[0])->v;
    FINDN(d->idx732, &DAT_00517f08[0], 3)
    FINDN(d->idx744, &DAT_00517f18[0], 5)
    FIND1(d->f764, &DAT_00517f28[0])
    FINDV(d->idx768, &DAT_00517f38[0])
    FIND1(d->f788, &DAT_00517f48[0])
    BYTES(d->b792, igProperty_GetRecordArray, &DAT_00517f50[0])
    BYTES(d->b1816, igProperty_GetRecordArray, &DAT_00517f60[0])
    INTS(d->w1828, FUN_003a9250, &DAT_00517f70[0])
    BYTES(d->b1892, igProperty_GetRecordArray, &DAT_00517f80[0])
    INTS(d->w1908, FUN_003a9250, &DAT_00517f90[0])
    INTS(d->w1972, FUN_003a9250, &DAT_00517fa0[0])
    INTS(d->w2036, FUN_003a9250, &DAT_00517fb0[0])
    INTS(d->w2612, FUN_003a9250, &DAT_00517fc0[0])
    beNDMWDegiData__UpdateFieldsFromData((beNDMWDegiData *)arg0);
}

extern "C" igObject *FUN_003c85b0(int);
extern "C" igObject *FUN_003c87f0(int);
extern "C" igObject *FUN_003c8970(int);
extern "C" igObject *FUN_003c8b00(int);
extern "C" igObject *FUN_003c8c90(int);
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset */
struct ItemVirtual { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
/* matching construct: one releasing holder class per retail destructor copy (the table at 0x544c20 names 0x3d9d50, 0x3d9cd0, 0x3d9c50, 0x3d9bd0 and 0x3b9ba0; the last is not the copy other members of this file name for their holders) */
template <int K> struct CreatedItemRef { igObject *p; CreatedItemRef(igObject *o) : p(o) {} ~CreatedItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };

static inline int itemAllocator(void *owner) {
    int alloc = igObject_GetAllocator(owner);
    int a;
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    }
    return a;
}

ItemRef FUN_003ef1e0(void *owner, int id) {
    int k = (id >> 12) & 0xF;
    if (k == 0) {
        {
            CreatedItemRef<1> sp((igObject *)FUN_003c8c90(itemAllocator(owner)));
            ((ItemVirtual *)sp.p)->vX(id);
            return ItemRef((Obj *)sp.p, kRetainReference);
        }
    } else if (k == 1) {
        {
            CreatedItemRef<2> sp((igObject *)FUN_003c8b00(itemAllocator(owner)));
            ((ItemVirtual *)sp.p)->vX(id);
            return ItemRef((Obj *)sp.p, kRetainReference);
        }
    } else if (k == 2) {
        {
            CreatedItemRef<3> sp((igObject *)FUN_003c8970(itemAllocator(owner)));
            ((ItemVirtual *)sp.p)->vX(id);
            return ItemRef((Obj *)sp.p, kRetainReference);
        }
    } else if (k == 3) {
        {
            CreatedItemRef<4> sp((igObject *)FUN_003c87f0(itemAllocator(owner)));
            ((ItemVirtual *)sp.p)->vX(id);
            return ItemRef((Obj *)sp.p, kRetainReference);
        }
    } else if (k == 4) {
        {
            CreatedItemRef<5> sp((igObject *)FUN_003c85b0(itemAllocator(owner)));
            ((ItemVirtual *)sp.p)->vX(id);
            return ItemRef((Obj *)sp.p, kRetainReference);
        }
    } else {
        return ItemRef(0, kRetainReference);
    }
}

void beNDMWDegiData__StoreToProperties(Host *arg0, void *arg1, int arg2) {
    Saved *s = arg0->saved;
    ((RecByte *)igProperty_GetRecordByte(arg1, DAT_00517e58))->value = s->b0;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517e60))->value = s->i4;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517e68))->value = s->i72;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517e70))->value = s->i76;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517e78))->value = s->i80;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517e80))->value = s->i84;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517e88))->value = s->i88;
    char *nm = s->name;
    RecStr *rs = ((RecStr *)FUN_003a92e0(arg1, DAT_00517ea0));
    if (((void * *)g_stringPool)[0] == 0) {
        void *p = FUN_002eb010(16);
        if (p != 0)
            p = StringPool_Construct(p);
        ((void * *)g_stringPool)[0] = p;
    }
    char *interned = StringPool_Intern(((void * *)g_stringPool)[0], nm);
    char *old = rs->value;
    if (old != 0) {
        int *hdr = (int *)old - 2;
        int rc = hdr[1] - 1;
        hdr[1] = rc;
        if (rc == 0)
            StringChunk_ReleaseHeader(hdr[0], hdr);
    }
    rs->value = interned;
    igObjectList *l0 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517e90))->value;
    Lst::Clear(l0);
    int alloc = igObject_GetAllocator(arg0);
    int a;
    if (GPR_00554c14 != 0)
        a = alloc;
    else
        a = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    {
    ChunkRef sp188((Obj *)FUN_003614f0(a));
    Obj * sp184;
    beUnicodeObj_AllocateBuffer((Chunk *)sp188.p, 8);
    unsigned short *dst = ((Chunk *)sp188.p)->chars;
    Saved::Str16 *q = &s->nm;
    if (q->sel != 0xffff) {
        FUN_00382eb0((void *)&sp184, arg2, arg0->dword52);
        unsigned short *src = ((Chunk *)sp184)->chars;
        int ia = 0;
        for (; ia < 8; ia++) {
            dst[ia] = src[ia];
            if (src[ia] == 0)
                break;
        }
        for (; ia < 8; ia++)
            dst[ia] = 0;
        { Obj *r = sp184; H::Rel(r); }
    } else {
        int ib = 0;
        for (; ib < 8; ib++) {
            dst[ib] = q->chars[ib];
            if (dst[ib] == 0)
                break;
        }
        for (; ib < 8; ib++)
            dst[ib] = 0;
    }
    ObjectList_AppendRetained(l0, sp188.p);
    }
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517eb0))->value = s->i92;
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517eb8))->value = s->i96;
    igObjectList *l1 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ec0))->value;
    Lst::Clear(l1);
    for (int i1 = 0; i1 < 36; i1++) {
        int id = s->l0[i1];
        if (id == -1)
            break;
        ItemRef sp180 = FUN_003ef1e0(arg0, id);
        ObjectList_AppendRetained(l1, sp180.p);
    }
    igObjectList *l2 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ed0))->value;
    Lst::Clear(l2);
    for (int i2 = 0; i2 < 12; i2++) {
        int id = s->l1[i2];
        if (id == -1)
            break;
        ItemRef sp176 = FUN_003ef1e0(arg0, id);
        ObjectList_AppendRetained(l2, sp176.p);
    }
    igUnsignedCharList *a0 = ((RecArr8 *)igProperty_GetRecordArray(arg1, DAT_00517ee0))->value;
    for (int i3 = 0; i3 < 50; i3++) {
        unsigned char v = s->a0[i3];
        if (a0->_count != 0 && i3 >= 0 && i3 < a0->_count)
            ((unsigned char *)a0->_data)[i3] = v;
    }
    igObjectList *l3 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ef0))->value;
    Lst::Clear(l3);
    for (int i4 = 0; i4 < 96; i4++) {
        int id = s->l2[i4];
        if (id == -1)
            break;
        ItemRef sp172 = FUN_003ef1e0(arg0, id);
        ObjectList_AppendRetained(l3, sp172.p);
    }
    ((RecInt *)igProperty_GetRecord(arg1, DAT_00517f00))->value = s->i728;
    igObjectList *l4 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517f08))->value;
    Lst::Clear(l4);
    for (int i5 = 0; i5 < 3; i5++) {
        int id = s->l3[i5];
        if (id != -1) {
            ItemRef sp168(((Obj **)((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ec0))->value->_data)[id]);
            if (sp168.p)
                sp168.p->references++;
            ObjectList_AppendRetained(l4, sp168.p);
        } else {
            ObjectList_AppendRetained(l4, 0);
        }
    }
    igObjectList *l5 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517f18))->value;
    Lst::Clear(l5);
    for (int i6 = 0; i6 < 5; i6++) {
        int id = s->l4[i6];
        if (id != -1) {
            ItemRef sp164(((Obj **)((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ec0))->value->_data)[id]);
            if (sp164.p)
                sp164.p->references++;
            ObjectList_AppendRetained(l5, sp164.p);
        } else {
            ObjectList_AppendRetained(l5, 0);
        }
    }
    igObjectList *l6 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517f28))->value;
    Lst::Clear(l6);
    {
        int id = s->i764;
        if (id != -1) {
            ItemRef sp160(((Obj **)((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ec0))->value->_data)[id]);
            if (sp160.p)
                sp160.p->references++;
            ObjectList_AppendRetained(l6, sp160.p);
        } else {
            ObjectList_AppendRetained(l6, 0);
        }
    }
    igObjectList *l7 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517f38))->value;
    Lst::Clear(l7);
    for (int i7 = 0; i7 < 5; i7++) {
        int id = s->l5[i7];
        if (id != -1) {
            ItemRef sp156(((Obj **)((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ec0))->value->_data)[id]);
            if (sp156.p)
                sp156.p->references++;
            ObjectList_AppendRetained(l7, sp156.p);
        } else {
            ObjectList_AppendRetained(l7, 0);
        }
    }
    igObjectList *l8 = ((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517f48))->value;
    int id8 = s->i788;
    Lst::Clear(l8);
    if (id8 != -1) {
        ItemRef sp152(((Obj **)((RecLst *)igProperty_GetRecordFolder(arg1, DAT_00517ec0))->value->_data)[id8]);
        if (sp152.p)
            sp152.p->references++;
        ObjectList_AppendRetained(l8, sp152.p);
    } else {
        ObjectList_AppendRetained(l8, 0);
    }
    igUnsignedCharList *a1 = ((RecArr8 *)igProperty_GetRecordArray(arg1, DAT_00517f50))->value;
    for (int i8 = 0; i8 < 1024; i8++) {
        unsigned char v = s->a1[i8];
        if (a1->_count != 0 && i8 >= 0 && i8 < a1->_count)
            ((unsigned char *)a1->_data)[i8] = v;
    }
    igUnsignedCharList *a2 = ((RecArr8 *)igProperty_GetRecordArray(arg1, DAT_00517f60))->value;
    for (int i9 = 0; i9 < 12; i9++) {
        unsigned char v = s->a2[i9];
        if (a2->_count != 0 && i9 >= 0 && i9 < a2->_count)
            ((unsigned char *)a2->_data)[i9] = v;
    }
    igIntList *a3 = ((RecArr32 *)FUN_003a9250(arg1, DAT_00517f70))->value;
    for (int i10 = 0; i10 < 16; i10++) {
        int v = s->a3[i10];
        if (a3->_count != 0 && i10 >= 0 && i10 < a3->_count)
            ((int *)a3->_data)[i10] = v;
    }
    igUnsignedCharList *a4 = ((RecArr8 *)igProperty_GetRecordArray(arg1, DAT_00517f80))->value;
    for (int i11 = 0; i11 < 16; i11++) {
        unsigned char v = s->a4[i11];
        if (a4->_count != 0 && i11 >= 0 && i11 < a4->_count)
            ((unsigned char *)a4->_data)[i11] = v;
    }
    igIntList *a5 = ((RecArr32 *)FUN_003a9250(arg1, DAT_00517f90))->value;
    for (int i12 = 0; i12 < 16; i12++) {
        int v = s->a5[i12];
        if (a5->_count != 0 && i12 >= 0 && i12 < a5->_count)
            ((int *)a5->_data)[i12] = v;
    }
    igIntList *a6 = ((RecArr32 *)FUN_003a9250(arg1, DAT_00517fa0))->value;
    for (int i13 = 0; i13 < 16; i13++) {
        int v = s->a6[i13];
        if (a6->_count != 0 && i13 >= 0 && i13 < a6->_count)
            ((int *)a6->_data)[i13] = v;
    }
    igIntList *a7 = ((RecArr32 *)FUN_003a9250(arg1, DAT_00517fb0))->value;
    for (int i14 = 0; i14 < 144; i14++) {
        int v = s->a7[i14];
        if (a7->_count != 0 && i14 >= 0 && i14 < a7->_count)
            ((int *)a7->_data)[i14] = v;
    }
    igIntList *a8 = ((RecArr32 *)FUN_003a9250(arg1, DAT_00517fc0))->value;
    for (int i15 = 0; i15 < 176; i15++) {
        if (a8->_count != 0 && i15 >= 0 && i15 < a8->_count)
            ((int *)a8->_data)[i15] = s->a8[i15];
    }
}

void FUN_003f0d60(O *arg0, int arg1, int arg2, E_3f0d60 *arg3) {
    int idx = arg2;
    E_3f0d60 *rec = arg3;
    int pos = arg1;
    L *l = arg0->list;
    int i = 0;
    int a, w;
    E_3f0d60 *e;
    while (i < l->n) {
        if (i == idx) {
            a = rec->a28;
            w = rec->a36;
        } else {
            e = l->data[i];
            a = e->a28;
            w = e->a36;
        }
        memcpy(pos, a, w);
        l = arg0->list;
        i++;
        pos += w;
    }
}

void FUN_003f0e30(beNDMWLoadSlotPlayer *arg0, int arg1) {
    int i;
    int k;
    beNDMWDegiDataList *l;

    l = (beNDMWDegiDataList *)arg0->_saveDataList;
    i = 0;
    if (0 < l->_count) {
        k = 0;
        do {
            FUN_003ee690((beNDMWDegiData *)(*(int *)(l->_data + k)), arg1);
            l = (beNDMWDegiDataList *)arg0->_saveDataList;
            i += 1;
            arg1 += ((beNDMWDegiData *)*(int *)(l->_data + k))->_dataSize;
            k += 4;
        } while (i < l->_count);
    }
}

void FUN_003f0ed0(beNDMWMcUtilCtrl *arg0, int arg1, int arg2) {
    int s0;
    int v;

    arg0->_messenger = arg1;
    arg0->_isRun = 0;
    arg0->_isResult = 0;
    arg0->_isRdy = 0;
    switch (arg2) {
    case 0:
        for (s0 = 0; s0 < 5; s0++) {
            v = igObject_GetAllocator(arg0);
            if (GPR_00554c14 != 0) {
                v = (int)v;
            } else {
                v = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            }
            SlotRef<0> slot(FUN_003c5ee0(v));
            ObjectList_AppendRetained(arg0->_slot, slot.p);
        }
        return;
    case 1:
        for (s0 = 0; s0 < 2; s0++) {
            v = igObject_GetAllocator(arg0);
            if (GPR_00554c14 != 0) {
                v = (int)v;
            } else {
                v = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            }
            SlotRef<1> slot(FUN_003c5cf0(v));
            ObjectList_AppendRetained(arg0->_slot, slot.p);
        }
        return;
    case 2:
        for (s0 = 0; s0 < 9; s0++) {
            v = igObject_GetAllocator(arg0);
            if (GPR_00554c14 != 0) {
                v = (int)v;
            } else {
                v = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            }
            SlotRef<2> slot(FUN_003c5aa0(v));
            ObjectList_AppendRetained(arg0->_slot, slot.p);
        }
        break;
    }
}

void FUN_003f1270(beNDMWMcUtilCtrl *arg0) {
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00517fd0[0], 0, -1);
    beMessenger_AppendInt(arg0->_messenger, 4);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517fe0[0]);
    if (beMessenger_GetBoolCount(arg0->_messenger) > 0) {
        arg0->_isUseUtil = 1;
    } else {
        arg0->_isUseUtil = 0;
    }
}

unsigned char FUN_003f12f0(beNDMWMcUtilCtrl *arg0) {
    unsigned char var_s0;
    unsigned char one = 1;

    var_s0 = 0;
    if (arg0->_isUseUtil == one) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff0[0]);
        if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == one) {
            arg0->_isRdy = one;
            var_s0 = one;
        }
    } else {
        arg0->_isRdy = one;
        var_s0 = one;
    }
    return var_s0;
}

void FUN_003f1380(beNDMWMcUtilCtrl *arg0) {
    if (arg0->_isUseUtil == 1) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff8[0]);
    }
}

bool FUN_003f13d0(beNDMWMcUtilCtrl *arg0) {
    bool r = false;
    if (arg0->_isUseUtil == 1) {
        beMessenger_SendNamed(arg0->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00517ff0[0]);
        if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
            r = true;
        }
    } else {
        r = true;
    }
    return r;
}

void FUN_003f1460(beNDMWMcUtilCtrl *arg0, int arg1, int arg2) {
    arg0->_tgCon = arg2;
    arg0->_kind = arg1;
    arg0->_result = 0;
    arg0->_isResult = 0;
    arg0->_isRun = 1;
    arg0->_isFormatRun = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}

static inline unsigned int sizeOf(const beSaveDataDeliver *d) { return d->_size; }

void FUN_003f1490(beNDMWMcUtilCtrl *op) {
    if (op->_isRdy == 1) {
        if (op->_isUseUtil == 1) {
            beSvDeliver *r;
            beNDMWMcSlotList *sl;
            int i;
            int off;
            beMessenger_SendNamed(op->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_00518000[0]);
            r = beMessenger_GetObject(op->_messenger, 0);
            sl = (beNDMWMcSlotList *)op->_slot;
            i = 0;
            if (i < sl->_count) {
                off = 0;
                do {
                    if (*(int *)((char *)((igIntList *)r->_actConnect)->_data + off) == 1) {
                        (*(beNDMWMcSlot **)((char *)sl->_data + off))->_isConnect = 1;
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_totalSize = *(int *)((char *)((igIntList *)r->_totalSizeList)->_data + off);
                        (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_freeSize = *(int *)((char *)((igIntList *)r->_freeSizeList)->_data + off);
                        if (*(int *)((char *)((igIntList *)r->_formatList)->_data + off) == 1) {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_isFormat = 1;
                        } else {
                            (*(beNDMWMcSlot **)((char *)((beNDMWMcSlotList *)op->_slot)->_data + off))->_isFormat = 0;
                        }
                    } else {
                        (*(beNDMWMcSlot **)((char *)sl->_data + off))->_isConnect = 0;
                    }
                    sl = (beNDMWMcSlotList *)op->_slot;
                    i++;
                    off += 4;
                } while (i < sl->_count);
            }
            if (r->_useMtap == 1) {
                op->_isMtap = 1;
            } else {
                op->_isMtap = 0;
            }
        } else {
            int j;
            int off2;
            beNDMWMcSlotList *s2;
            op->_isMtap = 1;
            s2 = (beNDMWMcSlotList *)op->_slot;
            j = 0;
            if (j < s2->_count) {
                off2 = 0;
                do {
                    j++;
                    (*(beNDMWMcSlot **)((char *)s2->_data + off2))->_isConnect = 1;
                    s2 = (beNDMWMcSlotList *)op->_slot;
                    off2 += 4;
                } while (j < s2->_count);
            }
        }
    }
    if (op->_isRun == 1) {
        if (op->_isUseUtil == 1) {
            switch (op->_st0) {
            default:
                break;
            case 0:
                switch (op->_kind) {
                case 0:
                    memset(((beSaveDataDeliver *)op->_svData)->_data, 0, sizeOf((beSaveDataDeliver *)op->_svData));
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_AppendObject(op->_messenger, op->_svData);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518010[0]);
                    break;
                case 1:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518030[0]);
                    break;
                case 2:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518048[0]);
                    break;
                case 3:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518060[0]);
                    break;
                case 4:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_AppendObject(op->_messenger, op->_svData);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_00518080[0]);
                    break;
                case 5:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_AppendObject(op->_messenger, op->_svData);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_005180a0[0]);
                    break;
                case 6:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_005180c0[0]);
                    break;
                case 7:
                    beMessenger_SelectReceivers(op->_messenger, &DAT_00517fd0[0], 0, -1);
                    beMessenger_AppendInt(op->_messenger, op->_tgCon);
                    beMessenger_DispatchSelected(op->_messenger, &DAT_005180e0[0]);
                    break;
                }
                op->_st0 = op->_st0 + 1;
                op->_st3 = 0;
                op->_st2 = 0;
                op->_st1 = 0;
                break;
            case 1:
                beMessenger_SendNamed(op->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_005180f0[0]);
                if ((beMessenger_GetBool(op->_messenger, 0) & 0xFF) == 0) {
                    op->_st0 = op->_st0 + 1;
                    op->_st3 = 0;
                    op->_st2 = 0;
                    op->_st1 = 0;
                }
                break;
            case 2:
                beMessenger_SendNamed(op->_messenger, &DAT_00517fd0[0], 0, -1, &DAT_005180f8[0]);
                op->_result = beMessenger_GetInt(op->_messenger, 0);
                op->_isRun = 0;
                op->_isResult = 1;
                op->_st0 = op->_st0 + 1;
                op->_st3 = 0;
                op->_st2 = 0;
                op->_st1 = 0;
                break;
            case 3:
                break;
            }
        } else {
            op->_result = 2;
            op->_isRun = 0;
            op->_isResult = 1;
        }
    }
}

void Gap__Bec__beNDMWLoadCtrl2__vfunc_32(beNDMWLoadCtrl2 *self) {
    igObject *found;
    igObject *previous;
    if (self->_padManager == 0) {
        found = (igObject *)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
        if (found != 0) {
            found->_refCount = found->_refCount + 1;
        }
        previous = (igObject *)self->_padManager;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                FUN_002ff820();
            }
        }
        self->_padManager = (int)found;
    }
}

/* Owning stack reference to a freshly created property data list, released on scope exit
 * (reference count in the low 23 bits of f4). */
static inline int st1(const beNDMWLoadCtrl2CtrlData *data) { return data->_st1; }

void Gap__Bec__beNDMWLoadCtrl2__vfunc_31(beNDMWLoadCtrl2 *arg0, Host_3f1a80 *arg1) {
    beNDMWLoadCtrl2CtrlData *st;
    beNDMWLoadCtrl2CommonIntf *ci;
    int i;
    int cnt;
    unsigned char ok;
    int j;
    beNDMWLoadSavePlWorkList *fw;
    int kk;
    beNDMWLoadSavePlWorkList *fw2;

    if (arg1->f40 == 0) return;
    {
        if (arg1->f40 == 0) {
            S_ref *o;
            S_ref *old;
            int base = igObject_GetAllocator(arg1);
            int a;
            if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
            igSmartPointer<igObject> list((igObject *)beBaseInfoDataList_Create(a));
            o = (S_ref *)list.p;
            if (o != 0) o->_refCount = (int)((int) (o->_refCount + 1));
            old = arg1->f40;
            if (old != 0) {
                old->_refCount = (int)((int) (old->_refCount - 1));
                if ((old->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg1->f40 = o;
        }
        st = (beNDMWLoadCtrl2CtrlData *)igProperty_FindByName(arg1->f40, g_propertyNameField[0], &DAT_00518130[0]);
        if (arg1->f40 == 0) {
            S_ref *o;
            S_ref *old;
            int base = igObject_GetAllocator(arg1);
            int a;
            if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
            igSmartPointer<igObject> list((igObject *)beBaseInfoDataList_Create(a));
            o = (S_ref *)list.p;
            if (o != 0) o->_refCount = (int)((int) (o->_refCount + 1));
            old = arg1->f40;
            if (old != 0) {
                old->_refCount = (int)((int) (old->_refCount - 1));
                if ((old->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg1->f40 = o;
        }
        ci = (beNDMWLoadCtrl2CommonIntf *)igProperty_FindByName(arg1->f40, g_propertyNameField[0], &DAT_00518138[0]);
        switch (st->_st0) {
        case 0:
            break;
        case 1:
            switch (st->_st1) {
            case 0:
                FUN_003f1270((beNDMWMcUtilCtrl *)ci->_mcUtilCtrl);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 1:
                if ((((int)FUN_003f12f0((beNDMWMcUtilCtrl *)ci->_mcUtilCtrl)) & 0xFF) == 1) {
                    st->_st0 = 2;
                    st->_st3 = 0;
                    st->_st2 = 0;
                    st->_st1 = 0;
                }
                break;
            }
            break;
        case 2:
            switch (st1(st)) {
            case 0:
                beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_00517fe0[0]);
                beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_00518158[0]);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 1:
                switch (st->_st2) {
                case 0:
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0);
                    beMessenger_AppendString(arg0->_messenger, &DAT_00518158[0]);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00517af8[0]);
                    if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
                        if (st->_isTitle == 1) {
                            st->_st2 = (int)((int) (st->_st2 + 1));
                            st->_st3 = 0;
                        } else {
                            st->_st1 = (int)((int) (st->_st1 + 1));
                            st->_st3 = 0;
                            st->_st2 = 0;
                        }
                    }
                    break;
                case 1:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518170[0]);
                    if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                        beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518178[0]);
                    }
                    st->_st2 = (int)((int) (st->_st2 + 1));
                    st->_st3 = 0;
                    break;
                case 2:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518170[0]);
                    if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
                        st->_st1 = (int)((int) (st->_st1 + 1));
                        st->_st3 = 0;
                        st->_st2 = 0;
                    }
                    break;
                }
                break;
            case 2:
                beMessenger_SendNamed(arg0->_messenger, &DAT_00518188[0], 0, -1, &DAT_00517fe0[0]);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 3:
                switch (ci->_intfStat) {
                case 0:
                    FUN_003ecc60(ci);
                    break;
                case 2:
                    break;
                case 3:
                    st->_st1 = (int)((int) (st->_st1 + 1));
                    st->_st3 = 0;
                    st->_st2 = 0;
                    break;
                }
                break;
            case 4:
                switch (*(int *)&st->_st2) {
                case 0:
                    i = 0;
                    do {
                        beNDMWLoadSavePlWork *u;
                        ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ci->_flagWork)->_data)[i]->_isClose = 0;
                        u = ((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ci->_flagWork)->_data)[i];
                        i++;
                        u->_sysStat0 = 2;
                        u->_sysStat3 = 0;
                        u->_sysStat2 = 0;
                        u->_sysStat1 = 0;
                    } while (i < 4);
                    st->_st2 = (int)((int) (st->_st2 + 1));
                    st->_st3 = 0;
                    break;
                case 1:
                    ok = 1;
                    j = 0;
                    fw = (beNDMWLoadSavePlWorkList *)ci->_flagWork;
                    do {
                        if (((beNDMWLoadSavePlWork **)fw->_data)[j]->_isClose != 1) { ok = 0; break; }
                        j++;
                        fw = (beNDMWLoadSavePlWorkList *)ci->_flagWork;
                    } while (j < 4);
                    if ((ok & 0xFF) == 1) {
                        st->_st2 = (int)((int) (st->_st2 + 1));
                        st->_st3 = 0;
                    }
                    break;
                case 2:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00517fe0[0]);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518160[0], 0, &DAT_00518198[0]);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_005181a8[0]);
                    st->_st2 = (int)((int) (st->_st2 + 1));
                    st->_st3 = 0;
                    break;
                case 3:
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00517a48[0], &DAT_00518148[0], 0, &DAT_00518170[0]);
                    if (!(beMessenger_GetBool(arg0->_messenger, 0) & 0xFF)) {
                        st->_st2 = (int)((int) (st->_st2 + 1));
                        st->_st3 = 0;
                    }
                    break;
                case 4: {
                    int obj;
                    int t1, t2, t3;
                    beMessenger_SendNamed(arg0->_messenger, &DAT_00518188[0], 0, -1, &DAT_005181b8[0]);
                    {
                    cnt = 0;
                    kk = 0;
                    goto cnt_pre;
                cnt_body:
                    if (((beNDMWLoadSavePlWork **)fw2->_data)[kk]->_isRdy == 1) cnt++;
                    kk++;
                cnt_test:
                    if (kk < 4) goto cnt_body;
                    }
                    beMessenger_SendGroup(arg0->_messenger, &DAT_005181c8[0], &DAT_005181d0[0]);
                    obj = ((int)beMessenger_GetObject(arg0->_messenger, 0));
                    *(int *)((char *)((void *)igProperty_GetRecord(obj, &DAT_005181e0[0])) + 12) = cnt;
                    if (st->_isTitle == 1) {
                        t1 = ci->_difficultMode;
                        *(int *)((char *)((void *)igProperty_GetRecord(obj, &DAT_005181e8[0])) + 12) = t1;
                        t2 = arg0->_cameraMode;
                        *(int *)((char *)((void *)igProperty_GetRecord(obj, &DAT_005181f8[0])) + 12) = t2;
                        t3 = arg0->_lightMode;
                        *(int *)((char *)((void *)igProperty_GetRecord(obj, &DAT_00518208[0])) + 12) = t3;
                        beMessenger_SendGroup(arg0->_messenger, &DAT_00518218[0], &DAT_00518220[0]);
                    }
                    st->_st0 = 3;
                    st->_st3 = 0;
                    st->_st2 = 0;
                    st->_st1 = 0;
                    break;
                }
                }
                break;
            }
            break;
        case 3:
            switch (st->_st1) {
            case 0:
                FUN_003f1380((beNDMWMcUtilCtrl *)ci->_mcUtilCtrl);
                st->_st1 = (int)((int) (st->_st1 + 1));
                st->_st3 = 0;
                st->_st2 = 0;
                break;
            case 1:
                if ((((int)FUN_003f13d0((beNDMWMcUtilCtrl *)ci->_mcUtilCtrl)) & 0xFF) == 1) {
                    if (st->_isTitle == 0) {
                        beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518230[0], 0, -1);
                        beMessenger_AppendInt(arg0->_messenger, 4);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518240[0]);
                    } else {
                        g_mdlEntity[0] = 0;
                        beLua__RunNamedChunk(FUN_00236f80(arg0->_insight, g_beLua_metaObject[0]), &DAT_00518250[0], 0);
                        beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518230[0], 0, -1);
                        beMessenger_AppendInt(arg0->_messenger, 0);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518240[0]);
                    }
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_00518260[0]);
                    beMessenger_AppendString(arg0->_messenger, &DAT_00518270[0]);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518280[0]);
                    st->_st0 = (int)((int) (st->_st0 + 1));
                    st->_st3 = 0;
                    st->_st2 = 0;
                    st->_st1 = 0;
                }
                break;
            }
            break;
        }
    }
    return;
cnt_pre:
    fw2 = (beNDMWLoadSavePlWorkList *)ci->_flagWork;
    goto cnt_test;
}

int Gap__Bec__beNDMWLoadCtrl2__vfunc_30(void)
{
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}

/* Registers the load controller with its messenger as the receiver named by the "LOADCTRL2" string
 * (same wrapper shape as beNDMWTitle2 slot 29). */
void Gap__Bec__beNDMWLoadCtrl2__vfunc_29(beNDMWLoadCtrl2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &LOADCTRL2[0]);
}

int Gap__Bec__beNDMWLoadCtrl2__vfunc_34(beNDMWLoadCtrl2 *arg0, beBaseInfoRam *arg1, beBaseInfo *arg2) {
    int e;
    int j;
    int i;
    e = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003c7d40(), arg2->_dataList);
    if (e == 0 || e == 1) {
        if (e == 1) {
            if (beMessenger_GetIntCount(arg0->_messenger) > 0) {
                arg0->_cameraMode = beMessenger_GetInt(arg0->_messenger, 0);
                arg0->_lightMode = beMessenger_GetInt(arg0->_messenger, 1);
            } else {
                arg0->_cameraMode = 0;
                arg0->_lightMode = 0;
            }
        }
        if (arg1->_dataList == 0) {
            int a;
            ALLOC_3f2490(a, arg0);
            {
            igSmartPointer<igObject> list(((igObject *)beBaseInfoDataList_Create(a)));
            igObject *t = list.p;
            if (t != 0) t->_refCount++;
            Rel::go((igObject *)arg1->_dataList);
            arg1->_dataList = (int)t;
            ALLOC_3f2490(a, arg0);
            {
            CtrlDataRef ctrl(FUN_003c7a40(a));
            ObjectList_AppendRetained((int)(igObject *)arg1->_dataList, (int)ctrl.p);
            beNDMWLoadCtrl2CtrlData *o = (beNDMWLoadCtrl2CtrlData *)ctrl.p;
            i = 1;
            o->_st0 = i;
            o->_st3 = 0;
            o->_st2 = 0;
            o->_st1 = 0;
            if (e == 1) {
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = i;
                j = 0;
                do {
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_005181c8[0]);
                    beMessenger_AppendInt(arg0->_messenger, j);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005182a0[0]);
                    j++;
                } while (j < 4);
            } else {
                do {
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_005181c8[0]);
                    beMessenger_AppendInt(arg0->_messenger, i);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005182b0[0]);
                    if (((Rec *)igProperty_GetRecordByte(((int)beMessenger_GetObject(arg0->_messenger, 0)), &DAT_00517e58[0]))->b12 != 1) {
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_005181c8[0]);
                        beMessenger_AppendInt(arg0->_messenger, i);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005182a0[0]);
                    }
                    i++;
                } while (i < 4);
                ((beNDMWLoadCtrl2CtrlData *)ctrl.p)->_isTitle = 0;
            }
            }
            ALLOC_3f2490(a, arg0);
            {
            CommonIntfRef common(FUN_003c4be0(a));
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_system = FUN_00236f80(arg0->_insight, g_beSystem_metaObject[0]);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_inforam = (int)arg1;
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_insight = arg0->_insight;
            if (e == 1) {
                ((beNDMWLoadCtrl2CommonIntf *)common.p)->_isTitle = 1;
            }
            i = 0;
            do {
                ALLOC_3f2490(a, arg0);
                {
                DegiDataRef degi(((igObject *)beNDMWDegiData_Create(a)));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_gameUseData, (int)degi.p);
                }
                ALLOC_3f2490(a, arg0);
                {
                FlagWorkRef flag(FUN_003c56b0(a));
                ObjectList_AppendRetained(((beNDMWLoadCtrl2CommonIntf *)common.p)->_flagWork, (int)flag.p);
                }
                i++;
            } while (i < 4);
            ((beNDMWLoadCtrl2CommonIntf *)common.p)->_kindHard = 0;
            FUN_003f0ed0((beNDMWMcUtilCtrl *)(((beNDMWLoadCtrl2CommonIntf *)common.p)->_mcUtilCtrl), (int)arg0->_messenger, 0);
            ObjectList_AppendRetained((int)(igObject *)arg1->_dataList, (int)common.p);
            }
            }
        }
        return 1;
    }
    igObject *p = (igObject *)arg1->_dataList;
    if (p == 0) return 1;
    if (p == 0) {
        int a;
        ALLOC_3f2490(a, arg1);
        {
        igSmartPointer<igObject> fresh(((igObject *)beBaseInfoDataList_Create(a)));
        igObject *t = fresh.p;
        if (t != 0) t->_refCount++;
        Rel::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)t;
        }
    }
    igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], &DAT_00518130[0]);
    switch (e) {
    case 2:
        return 1;
    case 3:
        if (beMessenger_GetObjectCount(arg0->_messenger) == 0) {
            if (arg1->_dataList == 0) {
                int a;
                ALLOC_3f2490(a, arg1);
                {
                igSmartPointer<igObject> fresh(((igObject *)beBaseInfoDataList_Create(a)));
                igObject *t = fresh.p;
                if (t != 0) t->_refCount++;
                Rel::go((igObject *)arg1->_dataList);
                arg1->_dataList = (int)t;
                }
            }
            beMessenger_AppendObject(arg0->_messenger, ((int)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], &DAT_00518138[0])));
        }
        return 1;
    default:
        return 0;
    }
}

int Gap__Bec__beNDMWLoadCtrl2__vfunc_20(void)
{
    return g_beNDMWLoadCtrl2_metaObject[0];
}
