#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define ALLOC(var, arg) { int base_ = igObject_GetAllocator(arg); if (GPR_00554c14 != 0) var = base_; else var = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
#define REL(q) { igObject *o_ = (igObject *)(q); if (o_) { o_->_refCount = o_->_refCount - 1; if ((o_->_refCount & 0x7fffff) == 0) igObject_Destroy(o_); } }
#define RET(q) { igObject *o_ = (igObject *)(q); if (o_) o_->_refCount = o_->_refCount + 1; }

extern "C" int FUN_001e06c0(int, int, void (*)(void));
extern "C" int FUN_00356d10(...);
extern "C" void FUN_00390890(void);
extern "C" void FUN_003908d0(void);
extern "C" int thunk_FUN_0018ac80(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int List_Resize(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int FUN_00236f80(...);
extern "C" int Gap__Core__igObject__vfunc_30(void);
extern "C" void Gap__Core__igObject__vfunc_39(void);
extern "C" void Gap__Core__igObject__vfunc_46(void);
extern "C" void Gap__Core__igObject__vfunc_45(void);
extern "C" void Gap__Core__igObject__vfunc_44(void);
extern "C" void Gap__Core__igObject__vfunc_43(void);
extern "C" void Gap__Core__igObject__vfunc_41(void);
extern "C" void Gap__Core__igObject__vfunc_40(void);
extern "C" void Gap__Core__igObject__vfunc_42(void);
extern "C" int Gap__Core__igObject__vfunc_47(void);
extern "C" int Gap__Core__igObject__vfunc_25(...);
extern "C" int Gap__Bec__beModelCtrl__vfunc_25(void **arg0, void *arg1);
extern "C" int beMessenger_RegisterReceiverFromInfo(...);
extern "C" void * igProperty_FindByName(...);
extern "C" void Gap__Bec__beNDMWMdlMapCursor__vfunc_37(void);
extern "C" int FUN_002eb010(...);
extern "C" int StringPool_Construct(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int FUN_003a7e90(void *, void *);
extern "C" int FUN_003a6750(void *, void *);
extern "C" int FUN_003a65f0(void *, void *, void *);
extern "C" float FUN_003a68d0(...);
extern "C" float FUN_003a68e0(int, int, int, float);
extern "C" int FUN_003a7a20(...);
extern "C" int __fixsfdi(float);
extern "C" int strcmp(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int Matrix44_Copy(...);
extern "C" void igObject_Destroy(void *);
extern "C" void Matrix44_SetTranslation(float *matrix, void *vec3);
extern "C" int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void);
extern "C" float sqrtf(float);
extern "C" int Matrix44_GetTranslation(int, float *);
extern "C" void *FUN_00351e20(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_GetInt(...);
extern "C" int beMessenger_GetStringCount(...);
extern "C" float FUN_003a8140(...);
extern "C" int Matrix44_TranslateLocal(...);
extern "C" int FUN_003a7d80(...);
extern "C" void *FUN_00352940(...);
extern "C" float atan2f(float, float);
extern "C" int FUN_00192f50(...);
extern "C" void * StringPool_Intern(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int FUN_00393c80(...);
extern "C" int sprintf(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int FUN_003a8580(...);
extern "C" unsigned char FUN_00394ad0(int, int, void *, void *);
extern "C" int FUN_0039a130(int, int, int);
extern "C" void FUN_003951e0(int a0, int a1, float *a2);
extern "C" int FUN_00190ed0(int, float, float, float);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int FUN_001904f0(...);
extern "C" int FUN_001906d0(...);
extern "C" int FUN_00191f30(...);
extern "C" int FUN_00391cf0(...);
extern "C" int FUN_00399e20(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetMatrix(...);
extern "C" int beMessenger_GetMatrixCount(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int FUN_0018ac80(...);
extern "C" bool FUN_0018b050(void *, int);
extern "C" void FUN_00191670(void *, void *, float);
extern "C" int FUN_00356ab0(void);
extern "C" void FUN_0039a750(int, const char *, float);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_AppendInt(int, int);
extern "C" void beMessenger_AppendMatrix(int, void *);
extern "C" void beMessenger_AppendObject(int, void *);
extern "C" float beMessenger_GetFloat(int, int);
extern "C" int beMessenger_GetIntCount(int);
extern "C" const char * beMessenger_GetString(...);
extern "C" int beMessenger_GetVec3Count(int);
extern "C" void beMessenger_PopArgContext(int);
extern "C" void beMessenger_PushArgContext(int);
extern "C" unsigned beMessenger_ResolveEnumValue(int, int, const char *);
extern "C" int Gap__Bec__beModelCtrlInfoRideOn4__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrlInfoRideOn3__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrl__vfunc_20(void);
extern "C" int FUN_00390320(void *node, igCommonTraversal *traversal, void *data);
extern "C" int FUN_003902f0(igCommonTraversal *traversal, void *node);
extern "C" int DAT_00562640[4];
/* FUN_003908e0 is beModelCtrlInfoHitBody's per-frame box builder; receiver evidence: +8 bool, +16 long, +24 count, +28..+40 the four lists.
 * arg1 is a beBaseInfoRam (+12 parent info, whose +20 is its data list); the "HIT" record is a beModelCtrlInfoDataHit (+20 AABox list).
 * igAABox's _min / _max are the reflected igVec3f fields (float[3] in include/dw4/reflected.h), read and written as floats here.
 * matching construct: the first-loop minuend is spelled `*(float *)&pc[0]`; other spellings change MWCC's operand/load order and swap the arg0 and i registers.
 * Arena refs stay 4-byte handles in the reflected structs, so each list is reached through a cast of the handle to its list class. */

struct AABoxExtent { float x, y, z; };
extern "C" igAABox * FUN_0018a660(...);
extern "C" void FUN_0018b990(igAABox *, float *);
extern "C" int DAT_00585be0[4];
extern "C" int DAT_0050ef10[4];
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
extern "C" igAABoxList *FUN_003908e0(beModelCtrlInfoHitBody *arg0, beBaseInfoRam *arg1, int arg2, long long arg3);
struct S { char pad[12]; int f12; char pad2[16]; int f32; int f36; };
extern "C" int DAT_00587ce8[4];
extern "C" int DAT_00589208[4];
extern "C" void FUN_00390d70(S *arg0);
extern "C" int g_beModelCtrlInfo_metaObject[4];
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(); };
class DW4VC_148_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(int); };
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset (slot 36 of beModelCtrl) */
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void vX(void *); };
extern "C" int DAT_0050ef18[4];
extern "C" int DAT_0050ef30[4];
extern "C" int DAT_0050ef40[4];
extern "C" int DAT_0050ef50[4];
extern "C" void Gap__Core__igObject__vfunc_29(beModelCtrl *arg0, beBaseInfoRam *arg1);
extern "C" int g_beNDMWMdlMapCursor_metaObject[4];
extern "C" igObject * beBaseInfoDataList_Create(...);
extern "C" int DAT_004e0858[4];
extern "C" int DAT_0050ef60[4];
extern "C" int DAT_0050ef68[4];
extern "C" int DAT_0050ef70[4];
extern "C" int DAT_0050ef78[4];
extern "C" int DAT_0050ef80[4];
extern "C" int DAT_0050ef88[4];
extern "C" int DAT_00586f20[4];
class Ctl { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference. */

/* Owning stack reference to a pooled string token (count at p[-1], chunk header at p[-2]). */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    StringRef() {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
struct DataListInstall { static inline void go(beBaseInfoRam *ram, const igSmartPointer<igObject> &fresh) {
    igObject *o = fresh.p;
    igObject *old;
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    old = (igObject *)ram->_dataList;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    ram->_dataList = (int)o;
}
static inline void make(beBaseInfoRam *ram, int v) { igSmartPointer<igObject> fresh(beBaseInfoDataList_Create(v)); go(ram, fresh); }
};
extern "C" void FUN_00390f80(beModelCtrl *arg0, void *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlInfoDataAIM *arg4);
typedef struct NamedEntry { int p0[2]; char *name; } NamedEntry;
typedef struct LogoSeqState { char p0[60]; int mode; int sub; char p68[150]; unsigned char flag; } LogoSeqState;
extern "C" int DAT_0050efa8[4];
extern "C" int DAT_0050efb0[4];
extern "C" int DAT_0050efb8[4];
extern "C" int DAT_0050efc0[4];
extern "C" int DAT_0050efc8[4];
extern "C" int DAT_0050efd0[4];
extern "C" int FUN_00391a10(int arg0, LogoSeqState *arg1, NamedEntry *arg2);
/* beModelCtrl per-instance hook. Makes sure the ram has a data list (created on demand, pooled
 * allocator unless the global selector flag is clear), then dispatches on which named property the
 * parent info carries: FUN_00390f80 when the first property's node is armed, FUN_003915a0 for the
 * second property. */

/* Minimal view of the property node: only the word at +8 is tested here. */
struct NodeView : public igObject { int f8; };
extern "C" int FUN_003915a0(int, beBaseInfo *, beBaseInfoRam *, int, beModelCtrlInfoRamData *);
extern "C" int DAT_0050efd8[4];
extern "C" int DAT_0050efe0[4];
extern "C" void Gap__Core__igObject__vfunc_38(int arg0, beBaseInfoRam *arg1);
extern "C" int DAT_0050eff8[4];
extern "C" int FUN_00391fe0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlACTION *arg3);
extern "C" igObject * beMessenger_GetObject(...);
extern "C" int DAT_0050f000[4];
extern "C" void FUN_00392050(beModelCtrlInfoRideOn *arg0, int arg1, int arg2, int arg3);
extern "C" int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2);
extern "C" int g_beModelCtrlInfoRideOn2_metaObject[4];
extern "C" int g_vec3Zero[4];
extern "C" void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self);
extern "C" float DAT_004e1058[4];
typedef struct { float x, y, z; } Vec3Float;
extern "C" void Gap__Bec__beModelCtrlInfoRideOn3__vfunc_21(beModelCtrlInfoRideOn3 *self, void *m);
extern "C" int DAT_0050f010[4];
extern "C" int DAT_0050f018[4];
extern "C" int DAT_0050f028[4];
extern "C" int DAT_0050f038[4];
extern "C" int DAT_0050f040[4];
extern "C" int DAT_0050f050[4];
extern "C" int DAT_0050f058[4];
extern "C" int DAT_0050f068[4];
extern "C" int DAT_0050f070[4];
extern "C" int DAT_0050f078[4];
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(void *, void *); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(void *); };
struct Slot { beModelCtrlInfoRideOn4 *p; void set(beModelCtrlInfoRideOn4 *n) { beModelCtrlInfoRideOn4 *o = p; if (o) { --o->_refCount; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } p = n; } };
/* Scope holder for the freshly built ride-on record. The constructor takes the allocation result,
 * so the protected range starts after the allocation call. */
struct RideOnRef { beModelCtrlInfoRideOn4 *p; RideOnRef(beModelCtrlInfoRideOn4 *x) { p = x; } ~RideOnRef() { beModelCtrlInfoRideOn4 *o = p; if (o) { --o->_refCount; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
extern "C" void FUN_003926d0(beModelCtrl *arg0, beBaseInfoRam *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3);
extern "C" unsigned char FUN_00392be0(int unused0, int unused1, beModelCtrlInfoWork *owner, unsigned int sel);
extern "C" void FUN_00392d20(beModelCtrlMoveObject *, int, float, float, float);
extern "C" void FUN_00392d90(beModelCtrlMoveObject *s);
extern "C" float FUN_00392e10(beModelCtrlMoveObject *arg0, float arg1);
/* matching construct: PropV carries 35 dummy virtuals so vX() dispatches through vtable offset 148 (lw t9,0(a0); lw t9,148(t9); jalr t9); the (int) self-assignment of var_v0 keeps the GPR_00554c14 select shape */

struct PropV { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(void *); };
typedef beModelCtrlMoveObject *MoveObjRef;
extern "C" int DAT_0050f0b8[4];
extern "C" void FUN_00392fa0(beModelCtrl *arg0, int arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3);
struct Prop { char pad16[16]; char *f16; };
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset 88 */
struct Msg {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX();
};
extern "C" int DAT_004e1098[4];
extern "C" int DAT_0050f0c8[4];
extern "C" int DAT_0050f0d0[4];
extern "C" int DAT_0050f0d8[4];
extern "C" int DAT_0050f0e0[4];
extern "C" int DAT_0050f0e8[4];
extern "C" int DAT_0050f0f0[4];
extern "C" int DAT_0050f0f8[4];
extern "C" int DAT_0050f100[4];
extern "C" int DAT_00588da0[4];
extern "C" int DAT_00588dd8[4];
/* Owning references live across calls (retail exception table 0x543a8c): igSmartPointer<igObject> is the ObjectRef copy at
 * 0x33e9c0 (slot 152), MoveRef the copy emitted behind this function at 0x393aa0 (slot 156). */

struct MoveRef {
    igObject *p;
    MoveRef() { p = 0; }
    ~MoveRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* matching construct: the code reads the refcount as a signed int, the header declares it unsigned */



/* matching construct: the data-list holder (slot 152) must sit below the move-object holder (slot 156), so it is
 * a local of a static inline member (allocated after the caller's).
 * al/p/old stay the caller's locals so the register order matches. Found by trial (no permuter). */
struct Locals {
    static inline void CreateDataList(beBaseInfoRam *arg1, int &al, igObject *&p, igObject *&old) {
        ALLOC(al, arg1);
        {
            igSmartPointer<igObject> sp98((igObject *)((void *)beBaseInfoDataList_Create(al)));
            p = sp98.p;
            if (p != 0) p->_refCount = p->_refCount + 1;
            old = (igObject *)arg1->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
            }
            arg1->_dataList = (int)p;
        }
    }
};
extern "C" unsigned char FUN_00393260(beModelCtrl *arg0, beBaseInfoRam *arg1, beModelCtrlInfoWork *arg2, Msg *arg3);
typedef struct FL { char pad[8]; int n; int cap; float *data; } FL;
typedef struct A2 { char pad[72]; FL *list; } A2;
typedef struct A3 { char pad[8]; char *name; float f12; float f16; } A3;
extern "C" char D_004e0858[];
extern "C" char D_0050f0d0[];
extern "C" float D_004c8fa0[4];
extern "C" int FUN_00393b20(int a0, int a1, A2 *arg2, A3 *arg3);
extern "C" int FUN_003943c0(int arg0, int arg1, int arg2, beModelCtrlLABELCTRL *arg3);
/* Publishes a model-control event to the Lua side. arg0 is the beModelCtrl (_luaManager), arg1 a
 * beBaseInfoRam (_ramNo, _dataList = the property list, created lazily and installed through an
 * owning stack reference). The event arguments are staged in a fixed block, the chunk name is
 * formatted from arg2/arg4 and run; the second cell of the property is refreshed from the block
 * afterwards when the chunk left it untouched. */

typedef struct Cell { char pad12[12]; int value; } Cell;
typedef struct PropData { char pad8[8]; Cell *first; Cell *second; int third; } PropData;
typedef struct Prop_394400 { char pad16[16]; int base; PropData *data; } Prop_394400;
extern "C" int DAT_0050f110[4];
extern "C" beBaseInfoRam *DAT_0058a1e0[4];
extern "C" int DAT_0058a1e4[4];
extern "C" int DAT_0058a1e8[4];
extern "C" int DAT_0058a1ec[4];
extern "C" int DAT_0058a1f0[4];
extern "C" int DAT_0058a1f4[4];
extern "C" int DAT_0058a1f8[4];
extern "C" int DAT_0058a1fc[4];
extern "C" int DAT_0058a200[4];
extern "C" int DAT_0058a204[4];
extern "C" int DAT_0058a208[4];
extern "C" int DAT_0058a20c[4];
extern "C" char DAT_0058a210[16];
extern "C" int DAT_0058a214[4];
extern "C" void FUN_00394400(beModelCtrl *arg0, beBaseInfoRam *arg1, const char *arg2, const char *arg3, const char *arg4, int arg5, int arg6, const char *arg7, int arg8, int arg9);
extern "C" int DAT_0050f120[4];
extern "C" int FUN_00394640(beModelCtrl *arg0, beBaseInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlLUACALL *arg4);
extern "C" int DAT_0050f128[4];
extern "C" int DAT_0050f130[4];
struct V3 { float x, y, z; };
extern "C" V3 *DAT_0058a218[4];
extern "C" int FUN_00394920(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlMSGBOX *arg4);
class DW4VC_140_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int, int); };
extern "C" int FUN_00394ae0(void **arg0, int arg1, beModelCtrlJUMP *arg2);
extern "C" int FUN_00394b30(int arg0, beModelCtrlInfoWork *arg1, igNamedObject *arg2);
extern "C" int DAT_0050f138[4];
extern "C" int DAT_0050f140[4];
extern "C" int DAT_0050f148[4];
extern "C" int DAT_0050f150[4];
extern "C" int DAT_0050f160[4];
extern "C" int DAT_0050f168[4];
class VO_394bf0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(void *); };
extern "C" void FUN_00394bf0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3);
typedef struct B { char pad[8]; char *f8; } B;
typedef struct A { char pad[228]; int f228; } A;
extern "C" int FUN_0039a500(int, B *);
extern "C" char DAT_0050f178[];
extern "C" char DAT_0050f188[];
extern "C" int DAT_005887c8[4];
extern "C" int FUN_00394fa0(int arg0, int arg1, A *arg2, B *arg3);
extern "C" int DAT_0050f190[4];
extern "C" int DAT_0050f198[4];
extern "C" int DAT_0050f1a0[4];
extern "C" int DAT_0050f1b0[4];
struct MutekiNameOf { static int *Get(beModelCtrlMUTEKI *m) { if (m->_name != 0) { return (int *)m->_name; } return &DAT_004e0858[0]; } };
extern "C" int FUN_00395070(int arg0, int arg1, beModelCtrlInfoWork *arg2, beModelCtrlMUTEKI *arg3);
struct VO_395250 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" int DAT_00588df8[4];
extern "C" int DAT_00588e08[4];
extern "C" int DAT_00588d88[4];
extern "C" int DAT_00588d70[4];
extern "C" int DAT_00588d68[4];
extern "C" int DAT_00588d20[4];
extern "C" int DAT_00588d50[4];
extern "C" int DAT_00588e10[4];
extern "C" int DAT_00588e28[4];
extern "C" int DAT_00588d60[4];
extern "C" int DAT_00588df0[4];
extern "C" int DAT_00588e20[4];
extern "C" int DAT_00588e00[4];
extern "C" void FUN_00395250(int arg0, int arg1, int arg2, beModelCtrlInfoWork *arg3);
/* Steps the model's direction toward its target (per-axis rate limit, wrapping at 2*pi), then
 * writes the new rotation into the ram object's transform. The ram object's data list is created
 * on first use. */



struct Ref : public igObject { };
struct Prop_3956e0 { char pad[16]; int f16; };
extern "C" void FUN_003956e0(int a0, int a1, beBaseInfoRam *obj, beModelCtrlInfoWork *st, int force);
struct MsgView {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual int v33(beBaseInfoRam *, int *);
};
struct UpdView {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual int v46(beBaseInfoRam *);
};
struct NodeView_395b50 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual int v35(int *);
};
struct RideView {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual int v21(int *);
};
extern "C" int DAT_0050efe8[4];
extern "C" int DAT_0050f1b8[4];
extern "C" int DAT_0050f1c0[4];
extern "C" int DAT_0050f1c8[4];
extern "C" void * DAT_00561288[4];
extern "C" void Gap__Core__igObject__vfunc_31(beModelCtrl *arg0, beBaseInfoRam *arg1);
extern "C" int FUN_001cafc0(int list, StringRef *key, int);
extern "C" StringRef StringList_CopyRetained(int list, int index);
struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad; int nm; };
extern "C" int FUN_003960f0(int arg0, beModelCtrlInfoWork *self);
struct Rel { static inline void go(igAABox *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void FUN_00396940(beModelCtrl *arg0, beModelCtrlNode2 *arg1, igAABox *arg2);
struct V4 { float x, y, z; };
extern "C" beModelCtrlNode2 *FUN_0034fd00(int);
extern "C" beModelCtrlInfoRideOn4 *FUN_00351420(int);
extern "C" beModelCtrlInfoRideOn3 *FUN_00351780(int);
extern "C" beModelCtrlInfoRideOn2 *FUN_00351ad0(int);
extern "C" beModelCtrlInfoAI *FUN_00352140(int);
extern "C" beModelCtrlInfoHitBody *FUN_003523d0(int);
extern "C" void FUN_00399f20(int, beBaseInfoRam *);
extern "C" void FUN_0039a250(int, const char *, const char *, V4 *, V4 *, int, float, int);
extern "C" void FUN_003a84a0(beBaseInfoRam *, float);
extern "C" void FUN_003a8760(beBaseInfoRam *);
extern "C" void Matrix44_FromTranslation(void *, V4 *);
extern "C" void beMessenger_GetVec3(V4 *, int, int);
extern "C" float DAT_004c8fb8[4];
extern "C" float DAT_004e0ef0[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" float DAT_004e1078[4];
extern "C" float DAT_004e1088[4];
extern "C" char DAT_0050eff0[];
extern "C" char DAT_0050f1d8[];
extern "C" char DAT_0050f1e0[];
extern "C" char DAT_0050f1e8[];
extern "C" char DAT_0050f1f0[];
extern "C" char DAT_0050f200[];
extern "C" char DAT_0050f210[];
extern "C" char DAT_0050f220[];
extern "C" char DAT_0050f228[];
extern "C" char DAT_0050f230[];
extern "C" int DAT_00561898[4];
/* matching construct: RAII holder; its mangled destructor name pins the class name igSmartPointer<igObject> */

/* Owning stack references to the objects this handler creates before binding them: kind 0 the AI
 * info, 1 the hit-body info, 2..4 the ride-on infos of commands 25..27 and 5 their model node. */
template <int kind> struct ObjRef {
    igObject *p;
    ObjRef(igObject *q) : p(q) {}
    ~ObjRef() { igObject *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};
/* matching construct: dummy-virtual views so the calls dispatch through the retail vtable offsets (no fields) */
struct CtlV {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32();
    virtual int v33(beBaseInfoRam *, const char *);
    virtual void d34(); virtual void d35();
    virtual void v36(beBaseInfoRam *);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void v40(beBaseInfoRam *);
    virtual void v41(beBaseInfoRam *);
    virtual void v42(beBaseInfoRam *);
    virtual void v43(beBaseInfoRam *);
    virtual void v44(beBaseInfoRam *);
    virtual void v45(beBaseInfoRam *);
    virtual void d46();
    virtual unsigned char v47(beBaseInfoRam *, const char *);
};
struct NodeV {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void v35(void *);
};
struct LodV {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int v20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void v29();
};
/* reflection types the vec3 fields as int words; the code reads and writes them as floats */






/* first child of the model node: an igLod (its meta is compared in case 22) */




struct Hp {
    static inline void Ensure(beBaseInfoRam *e, beModelCtrlInfoRideOn *&s) {
        if (e->_dataList == 0) {
            int a = igObject_GetAllocator(e);
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            igSmartPointer<igObject> r((igObject *)((beBaseInfoDataList *)beBaseInfoDataList_Create(a)));
            s = (beModelCtrlInfoRideOn *)r.p;
            RET(s)
            REL(e->_dataList)
            e->_dataList = (int)s;
        }
    }
};
extern "C" int Gap__Bec__beModelCtrl__vfunc_33(beModelCtrl *self, beBaseInfoRam *ent, const char *msgname);
extern "C" int g_beModelCtrlInfoRideOn4_metaObject[4];
extern "C" int g_beModelCtrlInfoRideOn3_metaObject[4];
extern "C" int g_beModelCtrl_metaObject[4];

int FUN_003902f0(igCommonTraversal *traversal, void *node)
{
    return FUN_00390320(node, traversal, node);
}

void FUN_00390890(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_00356d10(), (void (*)())FUN_003902f0);
}

void FUN_003908d0(void)
{
}

igAABoxList *FUN_003908e0(beModelCtrlInfoHitBody *arg0, beBaseInfoRam *arg1, int arg2, long long arg3) {
    if (arg0->_isFirst != 0) {
        beModelCtrlInfoDataHit *pr = ((beModelCtrlInfoDataHit *)igProperty_FindByName(((beBaseInfo *)arg1->_parentInfo)->_dataList, DAT_00585be0[0], DAT_0050ef10));
        igAABoxList *q = (igAABoxList *)pr->_hitBulletAABoxList;
        arg0->_orgAABoxList = (int)q;
        arg0->_count = q->_count;
        int n = arg0->_count;
        int i;
        for (i = 0; i < n; i++) {
            igAABox *b = ((igAABox **)((igAABoxList *)arg0->_orgAABoxList)->_data)[i];
            float c[3];
            float e1[3];
            float e2[3];
            int j;
            FUN_0018b990(b, (float *)c);
            j = 0;
            {
                float *pc = c, *p1 = e1, *p2 = e2; igAABox *pb = b;
                for (; j < 3; j++) {
                    float d = *(float *)&pc[0] - pb->_min[0];
                    *p1 = d < 0.0f ? -d : d;
                    d = pb->_max[0] - *pc;
                    *p2 = d < 0.0f ? -d : d;
                    pb = (igAABox *)((char *)pb + 4); pc++; p1++; p2++;
                }
            }
            {
                int k;
                igDataList *l = (igDataList *)arg0->_AABoxMinList;
                k = l->_count;
                if (k < l->_capacity) l->_count = k + 1; else List_Resize(l, k + 1, 12);
                AABoxExtent *p = &((AABoxExtent *)l->_data)[k];
                p->x = e1[0]; p->y = e1[1]; p->z = e1[2];
            }
            {
                int k;
                igDataList *l = (igDataList *)arg0->_AABoxMaxList;
                k = l->_count;
                if (k < l->_capacity) l->_count = k + 1; else List_Resize(l, k + 1, 12);
                AABoxExtent *p = &((AABoxExtent *)l->_data)[k];
                p->x = e2[0]; p->y = e2[1]; p->z = e2[2];
            }
            {
                int alloc = igObject_GetAllocator(arg0);
                int a;
                if (GPR_00554c14 != 0) a = alloc; else a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                igSmartPointer<igAABox> ob(FUN_0018a660(a));
                { igAABox *t = ob.p; igAABoxList *ol = (igAABoxList *)arg0->_AABoxList; ObjectList_AppendRetained(ol, t); }
            }
        }
        arg0->_isFirst = 0;
    }
    if (arg3 != arg0->_calcTime) {
        int n;
        int i;
        arg0->_calcTime = arg3;
        n = arg0->_count;
        for (i = 0; i < n; i++) {
            igAABox *src = ((igAABox **)((igAABoxList *)arg0->_orgAABoxList)->_data)[i];
            igAABox *dst = ((igAABox **)((igAABoxList *)arg0->_AABoxList)->_data)[i];
            float c[3];
            float e1[3];
            float e2[3];
            int k;
            for (k = 0; k < 3; k++) { float *a = &dst->_min[k]; float *b = &dst->_max[k]; *a = src->_min[k]; *b = src->_max[k]; }
            thunk_FUN_0018ac80(dst, arg2);
            c[0] = (dst->_min[0]) * 0.5f + (dst->_max[0]) * 0.5f;
            c[1] = (dst->_min[1]) * 0.5f + (dst->_max[1]) * 0.5f;
            c[2] = (dst->_min[2]) * 0.5f + (dst->_max[2]) * 0.5f;
            *(AABoxExtent *)e1 = ((AABoxExtent *)((igDataList *)arg0->_AABoxMinList)->_data)[i];
            *(AABoxExtent *)e2 = ((AABoxExtent *)((igDataList *)arg0->_AABoxMaxList)->_data)[i];
            for (k = 0; k < 3; k++) { float *a = &dst->_min[k]; float *b = &dst->_max[k]; *a = c[k] - e1[k]; *b = c[k] + e2[k]; }
        }
    }
    return (igAABoxList *)arg0->_AABoxList;
}

void FUN_00390d70(S *arg0) {
    if (arg0->f32 == 0) {
        arg0->f32 = FUN_00236f80(arg0->f12, DAT_00589208[0]);
    }
    if (arg0->f36 == 0) {
        arg0->f36 = FUN_00236f80(arg0->f12, DAT_00587ce8[0]);
    }
}

/* Slot 30 default: first word of the beModelCtrlInfo MetaObject record. */
int Gap__Core__igObject__vfunc_30(void)
{
    return g_beModelCtrlInfo_metaObject[0];
}

int Gap__Bec__beModelCtrl__vfunc_25(void **arg0, void *arg1) {
    int temp_s0;

    temp_s0 = ((DW4VC_128_0 *)(arg0))->vX();
    if ((temp_s0 == ((DW4VC_88_0 *)(((char *)(arg1) + 0)))->vX()) && ((((DW4VC_148_1 *)(arg0))->vX((int)(*(int *)((char *)(arg1) + 28))) & 0xFF) == 1)) {
        Gap__Core__igObject__vfunc_25(arg0, arg1);
        return 1;
    }
    return 0;
}

void Gap__Core__igObject__vfunc_29(beModelCtrl *arg0, beBaseInfoRam *arg1) {
    beBaseInfo *temp_s0;
    beModelCtrlInfoDataHit *temp_v0;

    temp_s0 = (beBaseInfo *)arg1->_parentInfo;
    beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef18[0]);
    temp_v0 = (beModelCtrlInfoDataHit *)igProperty_FindByName(temp_s0->_dataList, DAT_00585be0[0], &DAT_0050ef10[0]);
    if (temp_v0 != 0) {
        if (temp_v0->_isHitPlayerBullet != 0) {
            beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef30[0]);
        }
        if (temp_v0->_isHitPlayerTalk != 0) {
            beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef40[0]);
        }
        if (temp_v0->_isHitEnemyBullet != 0) {
            beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_0050ef50[0]);
        }
    }
    ((C *)arg0)->vX(arg1);
}

void Gap__Bec__beNDMWMdlMapCursor__vfunc_37(void)
{
}

void FUN_00390f80(beModelCtrl *arg0, void *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlInfoDataAIM *arg4) {
    float vec[3];
    igObject *o;
    igObject *old;
    beModelCtrlInfoRamData *prop;
    beModelCtrlAIData *seg;
    beModelCtrlInfoAI *cur;
    beModelCtrlAIMap *e;
    beModelCtrlAIDataList *lst;
    beModelCtrlAIData **pp;
    int v;
    int i;
    int cnt;
    int sel;
    char *nm;
    char *nm2;
    char *newv;
    char *oldv;
    float fv;
    if (arg2->_dataList == 0) {
        v = igObject_GetAllocator(arg2);
        v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        DataListInstall::make(arg2, v);
    }
    prop = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)arg2->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]));
    cur = (beModelCtrlInfoAI *)arg3->_aI;
    StringRef str(0);
    if (FUN_003a7e90(arg2, &DAT_0050ef68[0]) != 0) {
        e = ((beModelCtrlAIMap **)((beModelCtrlAIMapList *)arg4->_aIMapList)->_data)[cur->_mapNo];
        if ((char *)e->_targetType == 0) {
            if (DAT_00586f20[0] == 0) {
                v = FUN_002eb010(16);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20[0] = v;
            }
            newv = (char *)StringPool_Intern(DAT_00586f20[0], (char *)&DAT_0050ef70[0]);
            oldv = (char *)e->_targetType;
            if (oldv != 0) {
                int *a1 = (int *)oldv - 2;
                int v0 = ((int *)oldv)[-1] - 1;
                ((int *)oldv)[-1] = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            e->_targetType = (int)newv;
        }
        if (strcmp((char *)e->_targetType, &DAT_0050ef78[0]) == 0) {
            beModelCtrlInfoAI *c2 = (beModelCtrlInfoAI *)arg3->_aI;
            vec[0] = ((float *)c2->_worldPos)[0];
            vec[1] = ((float *)c2->_worldPos)[1];
            vec[2] = ((float *)c2->_worldPos)[2];
            if ((FUN_003a6750((char *)prop->_node + 32, vec) & 0xff) == 0) {
                return;
            }
        } else {
            if ((FUN_003a65f0((char *)prop->_node + 32, &DAT_0050ef80[0], (char *)e->_targetType) & 0xff) == 0) {
                return;
            }
        }
        fv = FUN_003a68d0();
        ((float *)arg3->_directionLimiter)[1] = e->_rotLimiter;
        if (!(e->_x1Square <= fv)) {
            lst = (beModelCtrlAIDataList *)e->_zoneA;
        } else if (!(e->_x2Square <= fv)) {
            lst = (beModelCtrlAIDataList *)e->_zoneB;
        } else if (!(e->_x3Square <= fv)) {
            lst = (beModelCtrlAIDataList *)e->_zoneC;
        } else {
            lst = (beModelCtrlAIDataList *)e->_zoneD;
        }
        sel = ((Ctl *)((beSystem *)arg0->_system)->_random)->vX() & 0xf;
        cnt = lst->_count;
        i = 0;
        if (i < cnt) {
            pp = (beModelCtrlAIData **)lst->_data;
            do {
                seg = *pp;
                if (sel < seg->_limit) break;
                pp = pp + 1;
            } while (++i < cnt);
        }
        ((float *)arg3->_targetDirection)[1] = FUN_003a68e0(cnt, i, sel, seg->_dirRadian);
        nm2 = (char *)seg->_name;
        if (nm2 != 0) {
            nm = nm2;
        } else {
            nm = (char *)&DAT_004e0858[0];
        }
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
        oldv = str.p;
        if (oldv != 0) {
            int *a1 = (int *)oldv - 2;
            int v0 = ((int *)oldv)[-1] - 1;
            ((int *)oldv)[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        str.p = newv;
        fv = seg->_time; fv = fv; FUN_003a7a20(arg2, &DAT_0050ef68[0], __fixsfdi((1e9f * fv) / 60.0f));
    } else {
        nm = (char *)cur->_seqName;
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
        oldv = str.p;
        if (oldv != 0) {
            int *a1 = (int *)oldv - 2;
            int v0 = ((int *)oldv)[-1] - 1;
            ((int *)oldv)[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        str.p = newv;
    }
    arg3->_keyInput = strcmp(str.p, &DAT_0050ef88[0]) == 0;
    nm = str.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
    oldv = (char *)arg3->_keyEventName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg3->_keyEventName = (int)newv;
    nm = str.p;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    newv = (char *)StringPool_Intern(DAT_00586f20[0], nm);
    oldv = (char *)cur->_seqName;
    if (oldv != 0) {
        int *a1 = (int *)oldv - 2;
        int v0 = ((int *)oldv)[-1] - 1;
        ((int *)oldv)[-1] = v0;
        if (v0 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    cur->_seqName = (int)newv;
}

int FUN_00391a10(int arg0, LogoSeqState *arg1, NamedEntry *arg2) {
    char *s;
    if (arg2->name != 0) s = arg2->name;
    else s = (char *)&DAT_004e0858[0];
    if (strcmp(s, &DAT_0050efa8[0]) == 0) {
        arg1->mode = 1;
        arg1->sub = 0;
    } else if (strcmp(s, &DAT_0050efb0[0]) == 0) {
        arg1->mode = 2;
        arg1->sub = 0;
    } else if (strcmp(s, &DAT_0050efb8[0]) == 0) {
        arg1->mode = 3;
        arg1->sub = 0;
    } else if (strcmp(s, &DAT_0050efc0[0]) == 0) {
        arg1->mode = 4;
        arg1->sub = 0;
    } else if (strcmp(s, &DAT_0050efc8[0]) == 0) {
        arg1->flag = 1;
    } else if (strcmp(s, &DAT_0050efd0[0]) == 0) {
        arg1->flag = 0;
    }
    return 1;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void Gap__Core__igObject__vfunc_38(int arg0, beBaseInfoRam *arg1) {
    beBaseInfo *info;
    int work;
    beModelCtrlInfoRamData *prop;
    int allocator;
    igObject *list;
    igObject *old;
    info = (beBaseInfo *)arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        allocator = igObject_GetAllocator(arg1);
        allocator = (GPR_00554c14 != 0) ? allocator : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(allocator));
        list = ref.p;
        if (list != 0) {
            list->_refCount = list->_refCount + 1;
        }
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg1->_dataList = (int)list;
    }
    work = ((beModelCtrlInfoRamData *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]))->_work;
    prop = ((beModelCtrlInfoRamData *)igProperty_FindByName(info->_dataList, DAT_00585be0[0], &DAT_0050efd8[0]));
    if (prop != 0) {
        if (((NodeView *)prop->_node)->f8 != 0) {
            FUN_00390f80((beModelCtrl *)arg0, (void *)info, arg1, (beModelCtrlInfoWork *)work, (beModelCtrlInfoDataAIM *)prop);
        }
    } else {
        prop = ((beModelCtrlInfoRamData *)igProperty_FindByName(info->_dataList, DAT_00585be0[0], &DAT_0050efe0[0]));
        if (prop != 0) {
            FUN_003915a0(arg0, info, arg1, work, prop);
        }
    }
}

int FUN_00391fe0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlACTION *arg3) {
    int var_a2;
    int var_a4;
    int t;

    var_a4 = arg3->_name ? arg3->_name : (int)&DAT_004e0858[0];
    t = arg2->_ramNo;
    var_a2 = arg1->_name ? arg1->_name : (int)&DAT_004e0858[0];
    beMessenger_SendNamed(arg0->_messenger, &DAT_0050eff8[0], var_a2, t, var_a4);
    return 1;
}

void FUN_00392050(beModelCtrlInfoRideOn *arg0, int arg1, int arg2, int arg3) {
    int sp60[16];
    igObject *s1;
    int s0, v;
    int *hd;
    int old;
    igObject *a0;
    beMessenger_SendNamed(arg3, &DAT_0050ef18[0], arg1, arg2, &DAT_0050f000[0]);
    s1 = beMessenger_GetObject(arg3, 0);
    Matrix44_Copy(sp60, (char *)s1 + 32);
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s0 = ((int)StringPool_Intern(DAT_00586f20[0], arg1));
    old = arg0->_modelName;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    arg0->_modelName = s0;
    arg0->_modelRamNo = arg2;
    if (s1 != 0) {
        s1->_refCount = s1->_refCount + 1;
    }
    a0 = (igObject *)arg0->_modelNode;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if (((unsigned long long)(long long)a0->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)a0);
    }
    arg0->_modelNode = (int)s1;
    Matrix44_Copy(&arg0->_oldMatrix, sp60);
}

int FUN_003921a0(beModelCtrlInfoRideOn *arg0, int arg1, int arg2) {
    if (strcmp(arg0->_modelName, arg1) != 0) return 0;
    if (arg2 == arg0->_modelRamNo) return 1;
    return 0;
}

/* Resets the ride-on pose: clears the translation of `_oldMatrix` to (0,0,0) and writes `_vector`
 * into the translation of the model node's matrix (+0x20 of a node, the igTransform `_m` offset).
 * Matrix44_SetTranslation copies vec3 into matrix words 12..14. */
void Gap__Bec__beModelCtrlInfoRideOn2__vfunc_21(beModelCtrlInfoRideOn2 *self) {
    Matrix44_SetTranslation(self->_oldMatrix, &g_vec3Zero[0]);
    Matrix44_SetTranslation((float *)(self->_modelNode + 0x20), &self->_vector);
}

void Gap__Bec__beModelCtrlInfoRideOn3__vfunc_21(beModelCtrlInfoRideOn3 *self, void *m) {
    Vec3Float t;
    Vec3Float d;
    float e, x, g, k, b, z, len, inv, y, c, a;
    Matrix44_SetTranslation((float *)((char *)self->_oldMatrix), DAT_004e1058);
    Matrix44_GetTranslation((int)m, (float *)&t);
    d.x = ((Vec3Float *)self->_worldPosition)->x;
    d.y = ((Vec3Float *)self->_worldPosition)->y;
    d.z = ((Vec3Float *)self->_worldPosition)->z;
    d.x = d.x - t.x;
    d.y = d.y - t.y;
    d.z = d.z - t.z;
    y = ((Vec3Float *)&d)->y; x = d.x; z = ((Vec3Float *)&d)->z;
    len = sqrtf(x * x + y * y + z * z);
    inv = 1.0f / len;
    d.x = d.x * inv;
    d.y = d.y * inv;
    d.z = d.z * inv;
    k = self->_minSpeed;
    a = self->_maxSpeed;
    b = self->_minKyori;
    c = self->_maxKyori;
    e = a - k;
    g = c - b;
    if (len < 0.0f) {
        len = -len;
    }
    if (!(len < c)) {
        k = k;
    } else {
        k = a;
        if (len <= b) {
            k = k;
        } else {
            k = a - ((len - b) / (g / e));
        }
    }
    d.x = d.x * k;
    d.y = d.y * k;
    d.z = d.z * k;
    Matrix44_SetTranslation((float *)((char *)self->_modelNode + 32), &d);
}

void FUN_003926d0(beModelCtrl *arg0, beBaseInfoRam *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3) {
    unsigned char b0;
    bool s8;
    int s7;
    int s6;
    int s5;
    int s0;
    s8 = false;
    if (arg3->_isWallCheck) {
        int *t0;
        int a2, a3;
        if (arg3->_rideOnData == 0) t0 = DAT_0050f010; else t0 = DAT_0050f018;
        a2 = arg1->_ramNo;
        a3 = arg2->_ramNo;
        a2 = a2 ? a2 : (int)DAT_004e0858;
        beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, t0);
        if (arg3->_luaWHit != 0 && beMessenger_GetBool(arg0->_messenger, 1) != 0) {
            int s = arg1->_ramNo;
            s = s ? s : (int)DAT_004e0858;
            FUN_00394400(arg0, arg2, (const char *)arg3->_luaWHit, (const char *)DAT_0050f038, (const char *)s, 0, 0, (const char *)0, 0, 0);
        }
    }
    if (arg3->_isFloorCheck) {
        if (((int)FUN_00392be0((int)arg0, (int)arg2, arg3, 3))) return;
        {
            int a2 = arg1->_ramNo;
            int a3 = arg2->_ramNo;
            a2 = a2 ? a2 : (int)DAT_004e0858;
            beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, DAT_0050f040);
        }
        if (beMessenger_GetBoolCount(arg0->_messenger) == 0) return;
        s0 = 0;
        s6 = beMessenger_GetStringCount(arg0->_messenger);
        if (s6 != 0) {
            s0 = ((int)beMessenger_GetString(arg0->_messenger, 0));
            if (strcmp(s0, DAT_0050f050) != 0) {
                s5 = beMessenger_GetInt(arg0->_messenger, 0);
            } else {
                s6 = 0;
            }
        }
        b0 = beMessenger_GetBool(arg0->_messenger, 0);
        s7 = beMessenger_GetBool(arg0->_messenger, 1) & 0xFF;
        s8 = false;
        if (arg3->_isFallCheck) {
            if (((int)FUN_00392be0((int)arg0, (int)arg2, arg3, 4))) {
                if (s7 != 0) {
                    int a2 = arg1->_ramNo;
                    int a3 = arg2->_ramNo;
                    a2 = a2 ? a2 : (int)DAT_004e0858;
                    beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, DAT_0050f058);
                    FUN_00392be0((int)arg0, (int)arg2, arg3, 5);
                    s8 = true;
                }
            } else if (b0) {
                int a2 = arg1->_ramNo;
                int a3 = arg2->_ramNo;
                a2 = a2 ? a2 : (int)DAT_004e0858;
                beMessenger_SendNamed(arg0->_messenger, DAT_0050f028, a2, a3, DAT_0050f058);
                FUN_00392be0((int)arg0, (int)arg2, arg3, 5);
                return;
            } else {
                if (strcmp(arg3->_seqCodeName, DAT_0050f068) == 0) return;
                ((VO *)arg0)->d33(arg2, DAT_0050f070);
                return;
            }
        }
        if (arg3->_luaFHit != 0 && s7 != 0) {
            int s = arg1->_ramNo;
            s = s ? s : (int)DAT_004e0858;
            FUN_00394400(arg0, arg2, (const char *)arg3->_luaFHit, (const char *)DAT_0050f078, (const char *)s, 0, 0, (const char *)0, 0, 0);
        }
        if (s8) {
            beModelCtrlInfoRideOn4 *a0 = (beModelCtrlInfoRideOn4 *)arg3->_rideOnData;
            if (a0 == 0 || a0->_modelRamNo < 100) {
                if (s6 == 0) {
                    if (a0 != 0) {
                        ((Slot *)&arg3->_rideOnData)->set(0);
                    }
                } else if (a0 == 0) {
                    int alloc = igObject_GetAllocator(arg0);
                    int a;
                    beModelCtrlInfoRideOn4 *n;
                    if (GPR_00554c14 != 0) a = alloc; else a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    RideOnRef holder((beModelCtrlInfoRideOn4 *)FUN_00351e20(a));
                    FUN_00392050((beModelCtrlInfoRideOn *)holder.p, s0, s5, arg0->_messenger);
                    n = holder.p;
                    if (n != 0) n->_refCount++;
                    ((Slot *)&arg3->_rideOnData)->set(n);
                } else if (!(FUN_003921a0((beModelCtrlInfoRideOn *)a0, s0, s5) & 0xFF)) {
                    FUN_00392050((beModelCtrlInfoRideOn *)((beModelCtrlInfoRideOn4 *)arg3->_rideOnData), s0, s5, arg0->_messenger);
                }
            }
        }
    }
}

/* Movement query on the work's beModelCtrlMoveObjectList (_moveObjectList, +200): the list is
 * enabled when _count != 0 and _data holds four beModelCtrlMoveObject handles (0 move, 1 rotation,
 * 2 turn-Y/landing, 3 fourth channel); selector 5 also clears entry 1 (_isRun and _speed). _data
 * is an array of arena handles, so entries are reached via casts. */
unsigned char FUN_00392be0(int unused0, int unused1, beModelCtrlInfoWork *owner, unsigned int sel) {
    beModelCtrlMoveObjectList *p;
    beModelCtrlMoveObject **l;
    beModelCtrlMoveObject *r;
    p = (beModelCtrlMoveObjectList *)owner->_moveObjectList;
    if (p->_count == 0) {
        return 0;
    }
    switch (sel) {
    case 0:
        l = (beModelCtrlMoveObject **)p->_data;
        if (l[0]->_isRun != 0) {
            return 1;
        }
        if (l[1]->_isRun != 0) {
            return 1;
        }
        r = l[2];
        if (r->_isRun) {
            return r->_isRun;
        }
        return r->_isRun;
    case 1:
        return ((beModelCtrlMoveObject **)p->_data)[3]->_isRun;
    case 2:
        return ((beModelCtrlMoveObject **)p->_data)[1]->_isRun;
    case 3:
        r = ((beModelCtrlMoveObject **)p->_data)[1];
        if (r->_isRun != 0 && r->_mode == 4) {
            return 1;
        }
        return 0;
    case 4:
        r = ((beModelCtrlMoveObject **)p->_data)[1];
        if (r->_isRun != 0 && r->_mode == 1) {
            return 1;
        }
        return 0;
    case 5:
        r = ((beModelCtrlMoveObject **)p->_data)[1];
        r->_isRun = 0;
        r->_speed = 0;
    default:
        return 1;
    }
}

void FUN_00392d90(beModelCtrlMoveObject *s) {
    float z = 0.0f;
    s->_endTime = z;
    if (s->_mode == 0) { FUN_00392d20(s, 2, s->_stopValue, s->_stopFrame, z); } else if (s->_mode == 1) { FUN_00392d20(s, 3, s->_stopValue, s->_stopFrame, z); } else { s->_isRun = 0; s->_speed = z; }
    s->_isSeqStop = 0;
}

float FUN_00392e10(beModelCtrlMoveObject *arg0, float arg1) {
    float f1, f2, f0;
    if (arg0->_isRun == 0) { return 0.0f; }
    f1 = arg0->_endTime;
    if (f1 != 0.0f) {
        f1 = f1 - arg1;
        if (f1 < 0.0f) {
            FUN_00392d90((beModelCtrlMoveObject *)arg0);
            if (arg0->_isRun == 0) { return 0.0f; }
        } else {
            arg0->_endTime = f1;
        }
    }
    if (!(arg1 <= 3.0f)) { arg1 = 3.0f; }
    f1 = arg0->_speed;
    f2 = arg1 * arg0->_acc;
    switch (arg0->_mode) {
    case 2:
    case 4:
        f1 = f1 - f2;
        if (f1 < 0.0f) { arg0->_isRun = 0; f1 = 0.0f; arg0->_speed = 0.0f; }
        break;
    case 3:
    case 5:
        f1 = f1 + f2;
        if (!(f1 <= 0.0f)) { arg0->_isRun = 0; f1 = 0.0f; arg0->_speed = 0.0f; }
        break;
    case 0:
        f0 = arg0->_value;
        f1 = f1 + f2;
        if (!(f1 <= f0)) { f1 = f0; }
        break;
    case 1:
        f1 = f1 - f2;
        f0 = -arg0->_value;
        if (f1 < f0) { f1 = f0; }
        break;
    }
    arg0->_speed = f1;
    return f1 * arg1;
}

#define MOVES(w) ((MoveObjRef *)((beModelCtrlMoveObjectList *)(w)->_moveObjectList)->_data)
void FUN_00392fa0(beModelCtrl *arg0, int arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3) {
    float vec[3];
    int sp70[16];
    float f20;
    float f3;
    int var_v0;
    beModelCtrlMoveObjectList *info;
    MoveObjRef *lst;
    beModelCtrlInfoRamData *prop;
    igObject *s1;
    igObject *t;
    void *a2;

    info = (beModelCtrlMoveObjectList *)arg3->_moveObjectList;
    arg3->_isHitCheck = 0;
    if (info->_count != 0) {
        f20 = FUN_003a8140(arg2, &DAT_0050f0b8[0]);
        if (((MoveObjRef *)info->_data)[3]->_isRun != 0) {
            f3 = 0.017453292f * FUN_00392e10((beModelCtrlMoveObject *)(MOVES(arg3)[3]), f20);
            *(float *)&arg3->_targetDirection[1] = *(float *)&arg3->_targetDirection[1] + f3;
            if (f3 < 0.0f) {
                f3 = -f3;
            }
            *(float *)&arg3->_directionLimiter[1] = 1.25f * f3;
        }
        FUN_003956e0((int)arg0, arg1, arg2, arg3, 0);
        lst = (MoveObjRef *)info->_data;
        if (lst[0]->_isRun != 0 || lst[1]->_isRun != 0 || lst[2]->_isRun != 0) {
            if (arg2->_dataList == 0) {
                var_v0 = igObject_GetAllocator(arg2);
                if (GPR_00554c14 != 0) {
                    var_v0 = (int)var_v0;
                } else {
                    var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                {
                    igSmartPointer<igObject> r(beBaseInfoDataList_Create(var_v0));
                    s1 = r.p;
                    if (s1 != 0) {
                        s1->_refCount = s1->_refCount + 1;
                    }
                    t = (igObject *)arg2->_dataList;
                    if (t != 0) {
                        t->_refCount = t->_refCount - 1;
                        if ((t->_refCount & 0x7FFFFF) == 0) {
                            igObject_Destroy(t);
                        }
                    }
                    arg2->_dataList = (int)s1;
                }
            }
            prop = ((beModelCtrlInfoRamData *)igProperty_FindByName((igObject *)arg2->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]));
            Matrix44_Copy(sp70, (char *)prop->_node + 0x20);
            vec[0] = FUN_00392e10((beModelCtrlMoveObject *)(MOVES(arg3)[0]), f20);
            vec[1] = FUN_00392e10((beModelCtrlMoveObject *)(MOVES(arg3)[1]), f20);
            vec[2] = FUN_00392e10((beModelCtrlMoveObject *)(MOVES(arg3)[2]), f20);
            Matrix44_TranslateLocal(sp70, vec);
            ((PropV *)prop->_node)->vX(sp70);
            arg3->_isHitCheck = 1;
            a2 = (void *)arg3->_baseAABox;
            if (a2 != 0) {
                FUN_00396940(arg0, (beModelCtrlNode2 *)((PropV *)prop->_node), (igAABox *)a2);
            }
        }
    }
}

#undef MOVES

#define MOVES(c) ((beModelCtrlMoveObject **)((beModelCtrlMoveObjectList *)(c)->_moveObjectList)->_data)
unsigned char FUN_00393260(beModelCtrl *arg0, beBaseInfoRam *arg1, beModelCtrlInfoWork *arg2, Msg *arg3)
{
    float sp88[3];
    int k;
    if (!(FUN_003a7d80(arg1, &DAT_0050f0b8[0]) & 0xFF)) {
        FUN_003a7a20(arg1, &DAT_0050f0b8[0], 0);
    }
    if (arg2->_isPosLock != 0) {
        arg2->_isPosLock = 0;
        if (arg1->_dataList == 0) {
            int al;
            igObject *p, *old;
            Locals::CreateDataList(arg1, al, p, old);
        }
        FUN_00192f50(&sp88[0], &DAT_004e1098[0], ((Prop *)igProperty_FindByName((igObject *)arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]))->f16 + 32);
        {
            float r = atan2f(sp88[0], sp88[2]);
            *(float *)&arg2->_direction[1] = r;
            *(float *)&arg2->_targetDirection[1] = r;
        }
    }
    if (((beModelCtrlMoveObjectList *)arg2->_moveObjectList)->_count == 0) {
        int al;
        igObject *o;
        MoveRef sp9C;
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList **)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList **)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList **)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
        ALLOC(al, arg0);
        o = sp9C.p;
        if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); }
        sp9C.p = (igObject *)FUN_00352940(al);
        { igObject *q_ = sp9C.p; beModelCtrlMoveObjectList *l_ = *(beModelCtrlMoveObjectList **)&arg2->_moveObjectList; ObjectList_AppendRetained(l_, q_); }
    }
    k = DAT_00588dd8[0];
    if (k == arg3->vX()) {
        char *nm;
        float fa, fb;
        beModelCtrlMOVE *m = (beModelCtrlMOVE *)arg3;
        nm = m->_name ? (char *)m->_name : (char *)&DAT_004e0858[0];
        fa = m->_value;
        fb = m->_frame;
        if (strcmp(nm, &DAT_0050f0c8[0]) == 0) {
            FUN_00392d20((beModelCtrlMoveObject *)(MOVES(arg2)[2]), 2, fa, fb, 0.0f);
        } else if (strcmp(nm, &DAT_0050f0d0[0]) == 0) {
            FUN_00392d20((beModelCtrlMoveObject *)(MOVES(arg2)[2]), 0, fa, fb, 0.0f);
        } else if (strcmp(nm, &DAT_0050f0d8[0]) == 0) {
            FUN_00392d20((beModelCtrlMoveObject *)(MOVES(arg2)[2]), 4, fa, fb, 0.0f);
        } else if (strcmp(nm, &DAT_0050f0e0[0]) == 0) {
            FUN_00392d20((beModelCtrlMoveObject *)(MOVES(arg2)[2]), 5, fa, fb, 0.0f);
        } else if (strcmp(nm, &DAT_0050f0e8[0]) == 0) {
            FUN_00392d20((beModelCtrlMoveObject *)(MOVES(arg2)[1]), 4, fa, fb, 0.0f);
        } else if (strcmp(nm, &DAT_0050f0f0[0]) == 0) {
            FUN_00392d20((beModelCtrlMoveObject *)(MOVES(arg2)[1]), 1, fa, fb, 0.0f);
        }
    } else {
        k = DAT_00588da0[0];
        if (k == arg3->vX()) {
            char *s;
            int idx, mode, off;
            unsigned char cb;
            float fa, fb, fc, fd, fe;
            beModelCtrlMoveObject *obj;
            beModelCtrlMOVEEX *m = (beModelCtrlMOVEEX *)arg3;
            s = m->_name ? (char *)m->_name : (char *)&DAT_004e0858[0];
            fa = m->_value;
            fb = m->_frame;
            fc = m->_playTime;
            cb = m->_isSeqStop;
            fd = m->_stopValue;
            fe = m->_stopFrame;
            off = (s[0] == 0x54) ? 0 : 2;
            idx = s[1] - 0x58 + off;
            switch (s[3]) {
            case 0x41: mode = 0; break;
            case 0x44: mode = 2; break;
            case 0x54: mode = 4; break;
            }
            if (s[2] == 0x4d) mode += 1;
            obj = MOVES(arg2)[idx];
            FUN_00392d20(obj, mode, fa, fb, fc);
            obj->_isSeqStop = cb;
            obj->_stopValue = fd;
            obj->_stopFrame = fe;
        } else {
            char *s;
            beModelCtrlMOVERL *m = (beModelCtrlMOVERL *)arg3;
            s = m->_name ? (char *)m->_name : (char *)&DAT_004e0858[0];
            if (strcmp(s, &DAT_0050f0f8[0]) == 0) {
                igObject *ob, *old;
                beMessenger_SendNamed(arg0->_messenger, &DAT_0050ef18[0], (char *)m->_modelName, arg1->_ramNo, &DAT_0050f100[0]);
                if (beMessenger_GetObjectCount(arg0->_messenger) == 1) {
                    arg2->_isPosLock = 1;
                    ob = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
                    if (ob != 0) ob->_refCount = ob->_refCount + 1;
                    old = (igObject *)arg2->_posLockTrc;
                    if (old != 0) {
                        old->_refCount = old->_refCount - 1;
                        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
                    }
                    arg2->_posLockTrc = (int)ob;
                }
            } else {
                char *n1, *n2;
                char *old1, *old2;
                n1 = (char *)m->_modelName;
                if (DAT_00586f20[0] == 0) {
                    int p = FUN_002eb010(16);
                    if (p != 0) p = StringPool_Construct(p);
                    DAT_00586f20[0] = p;
                }
                n1 = (char *)StringPool_Intern(DAT_00586f20[0], n1);
                old1 = (char *)arg2->_posLockModelName;
                if (old1 != 0) {
                    int *h = (int *)(old1 - 8);
                    int r = *(int *)(old1 - 4) - 1;
                    *(int *)(old1 - 4) = r;
                    if (r == 0) StringChunk_ReleaseHeader(*h, h);
                }
                arg2->_posLockModelName = (int)n1;
                n2 = (char *)m->_boneName;
                if (DAT_00586f20[0] == 0) {
                    int p = FUN_002eb010(16);
                    if (p != 0) p = StringPool_Construct(p);
                    DAT_00586f20[0] = p;
                }
                n2 = (char *)StringPool_Intern(DAT_00586f20[0], n2);
                old2 = (char *)arg2->_posLockBoneName;
                if (old2 != 0) {
                    int *h = (int *)(old2 - 8);
                    int r = *(int *)(old2 - 4) - 1;
                    *(int *)(old2 - 4) = r;
                    if (r == 0) StringChunk_ReleaseHeader(*h, h);
                }
                arg2->_posLockBoneName = (int)n2;
                arg2->_isPosLock = 1;
            }
        }
    }
    return 1;
}

#undef MOVES

int FUN_00393b20(int a0, int a1, A2 *arg2, A3 *arg3) {
    char *s;
    int idx, i, n, k, t;
    FL *l;
    const FL *view;
    FL *l2;
    int n2;
    FL *l3;
    int n3;
    int k3;
    float x, y;
    s = arg3->name ? arg3->name : D_004e0858;
    t = strcmp(s, D_0050f0d0);
    l = arg2->list;
    idx = t == 0 ? 2 : 0;
    if (l->n == 0) {
        for (i = 0; i < 4; i++) {
            l = arg2->list;
            view = l;
            k = view->n;
            if (k < l->cap) {
                l->n = l->n + 1;
            } else {
                List_Resize(l, k + 1, 4);
            }
            l->data[k] = D_004c8fa0[0];
        }
    }
    l2 = arg2->list;
    n2 = l2->n;
    x = arg3->f12;
    if (n2 != 0 && idx >= 0 && idx < n2) {
        l2->data[idx] = x;
    }
    l3 = arg2->list;
    n3 = l3->n;
    y = arg3->f16;
    if (n3 != 0) {
        k3 = idx + 1;
        if (k3 >= 0 && k3 < n3) {
            l3->data[idx + 1] = y;
        }
    }
    return 1;
}

int FUN_003943c0(int arg0, int arg1, int arg2, beModelCtrlLABELCTRL *arg3) {
    int *p = (int *)arg3->_name;
    p = p != 0 ? p : &DAT_004e0858[0];
    FUN_00393c80(arg0, arg1, arg2, arg3->_seqName, p);
    return 1;
}

/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void FUN_00394400(beModelCtrl *arg0, beBaseInfoRam *arg1, const char *arg2, const char *arg3, const char *arg4, int arg5, int arg6, const char *arg7, int arg8, int arg9) {
    int spA0[11];
    int t;
    int var_v0;
    igObject *p;
    igObject *old;
    Prop_394400 *prop;
    PropData *q;
    int saved;
    Cell *h;

    if (arg1->_dataList == 0) {
        t = igObject_GetAllocator(arg1);
        if (GPR_00554c14 != 0) {
            var_v0 = t;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(var_v0));
        p = created.p;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        arg1->_dataList = (int)p;
    }
    prop = ((Prop_394400 *)igProperty_FindByName((igObject *)arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]));
    q = prop->data;
    DAT_0058a1e0[0] = arg1;
    DAT_0058a1e4[0] = arg1->_ramNo;
    DAT_0058a1e8[0] = prop->base + 0x20;
    DAT_0058a1ec[0] = q->first->value;
    DAT_0058a1f0[0] = q->second->value;
    DAT_0058a1f4[0] = q->third;
    DAT_0058a1f8[0] = (int)arg4;
    DAT_0058a1fc[0] = arg5;
    DAT_0058a200[0] = arg6;
    DAT_0058a204[0] = (int)arg7;
    DAT_0058a208[0] = arg8;
    DAT_0058a20c[0] = arg9;
    DAT_0058a210[0] = 1;
    DAT_0058a214[0] = (int)arg3;
    saved = q->second->value;
    sprintf(spA0, &DAT_0050f110[0], arg2, arg4);
    beLua__RunNamedChunk(arg0->_luaManager, spA0, 0);
    h = q->second;
    if (saved == h->value) {
        h->value = DAT_0058a1f0[0];
    }
}

#define SETSTR(fld, lit) { \
    int *p; \
    s = (int *)arg4->_name; \
    if (s != 0) { s = (int *)s; } else { s = &DAT_004e0858[0]; } \
    if (DAT_00586f20[0] == 0) { \
        int pool = FUN_002eb010(0x10); \
        if (pool != 0) pool = StringPool_Construct(pool); \
        DAT_00586f20[0] = pool; \
    } \
    s = (int *)StringPool_Intern(DAT_00586f20[0], s); \
    p = (int *)arg3->fld; \
    if (p != 0) { \
        int *hd = p - 2; \
        int c = p[-1] - 1; \
        p[-1] = c; \
        if (c == 0) StringChunk_ReleaseHeader(*hd, hd); \
    } \
    arg3->fld = (int)s; }
int FUN_00394640(beModelCtrl *arg0, beBaseInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlLUACALL *arg4) {
    unsigned char ok;
    int *a2;
    int *a4;
    int t;
    int *s;
    ok = 0;
    t = arg4->_modeName;
    if (t == 0) {
        ok = 1;
    } else if (strcmp(t, &DAT_0050f120[0]) == 0) {
        SETSTR(_luaBHit, 0)
    } else if (strcmp(arg4->_modeName, &DAT_0050f038[0]) == 0) {
        SETSTR(_luaWHit, 0)
    } else if (strcmp(arg4->_modeName, &DAT_0050f078[0]) == 0) {
        SETSTR(_luaFHit, 0)
    } else {
        ok = 1;
    }
    if (ok) {
        a4 = (int *)arg1->_name;
        if (a4 != 0) { a4 = (int *)a4; } else { a4 = &DAT_004e0858[0]; }
        t = arg4->_modeName;
        a2 = (int *)arg4->_name;
        if (a2 != 0) { a2 = (int *)a2; } else { a2 = &DAT_004e0858[0]; }
        FUN_00394400(arg0, arg2, (const char *)a2, (const char *)t, (const char *)a4, 0, 0, (const char *)0, 0, 0);
    }
    return 1;
}

#undef SETSTR

int FUN_00394920(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlMSGBOX *arg4) {
    V3 vec;
    int i;
    int cnt;
    int idx;
    beModelCtrlAIMapList *lst;
    int *name;
    int *name2;
    beModelCtrlInfoAI *o;
    beModelCtrlAIMap *prop;
    lst = (beModelCtrlAIMapList *)((beModelCtrlInfoDataAIM *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050efd8[0]))->_aIMapList;
    name = (int *)arg4->_name;
    name = name != 0 ? name : &DAT_004e0858[0];
    prop = (beModelCtrlAIMap *)igProperty_FindByName(lst, DAT_00585be0[0], name);
    beModelCtrlAIMap *key = prop;
    cnt = lst->_count;
    for (i = 0; i < cnt; i++) { if (*(beModelCtrlAIMap **)&key == ((beModelCtrlAIMap **)lst->_data)[i]) { idx = i; goto found; } }
    idx = -1;
found:
    o = (beModelCtrlInfoAI *)arg3->_aI;
    if (o != 0) {
        o->_mapNo = idx;
        if (prop->_targetType != 0 && strcmp(prop->_targetType, &DAT_0050ef78[0]) == 0) {
            DAT_0058a218[0] = &vec;
            name2 = (int *)arg1->_name;
            name2 = name2 != 0 ? name2 : &DAT_004e0858[0];
            FUN_00394400(arg0, arg2, (const char *)&DAT_0050f128[0], (const char *)&DAT_0050f130[0], (const char *)name2, 0, 0, (const char *)0, 0, 0);
            { beModelCtrlInfoAI *oo = (beModelCtrlInfoAI *)arg3->_aI; ((float *)oo->_worldPos)[0] = vec.x; ((float *)oo->_worldPos)[1] = vec.y; ((float *)oo->_worldPos)[2] = vec.z; }
            DAT_0058a218[0] = 0;
        }
    }
    FUN_003a8580(arg2, &DAT_0050ef68[0]);
    return 1;
}

unsigned char FUN_00394ad0(int, int, void *, void *)
{
    return 1;
}

int FUN_00394ae0(void **arg0, int arg1, beModelCtrlJUMP *arg2) {
    int *var_a2;

    var_a2 = (int *)(arg2->_name);
    var_a2 = var_a2 ? var_a2 : (int *)&DAT_004e0858[0];
    ((DW4VC_140_1 *)(arg0))->vX(arg1, (int)(var_a2));
    return 1;
}

int FUN_00394b30(int arg0, beModelCtrlInfoWork *arg1, igNamedObject *arg2) {
    int *var_s0;
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_s0;
    char *temp_v1;
    var_s0 = (int *)arg2->_name;
    var_s0 = var_s0 != 0 ? var_s0 : (int *)(&DAT_004e0858[0]);
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (void *)(StringPool_Intern(DAT_00586f20[0], var_s0));
    temp_v1 = (char *)arg1->_wCheckName;
    if (temp_v1 != 0) {
        temp_a1 = (int *)(temp_v1 - 8);
        temp_v0 = *(int *)(temp_v1 - 4) - 1;
        *(int *)(temp_v1 - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg1->_wCheckName = (int)temp_s0;
    return 0;
}

#define SETSTR() do { \
    int v; int s4; int old; int *hd; \
    if (DAT_00586f20[0] == 0) { v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); DAT_00586f20[0] = v; } \
    s4 = ((int)StringPool_Intern(DAT_00586f20[0], 0)); \
    old = arg3->_wCheckName; \
    if (old != 0) { hd = (int *)(old - 8); v = *(int *)(old - 4) - 1; *(int *)(old - 4) = v; if (v == 0) StringChunk_ReleaseHeader(*hd, hd); } \
    arg3->_wCheckName = s4; \
    FUN_00395250((int)arg0, (int)arg1, (int)arg2, arg3); \
} while (0)
void FUN_00394bf0(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3) {
    if (strcmp(arg3->_wCheckName, DAT_0050f138) == 0 || strcmp(arg3->_wCheckName, DAT_0050f140) == 0) {
        if (!(FUN_00392be0((int)arg0, (int)arg2, arg3, 2) & 0xFF)) {
            SETSTR();
        }
    } else if (strcmp(arg3->_wCheckName, DAT_0050f148) == 0) {
        int a2 = arg1->_name;
        int a3 = arg2->_ramNo;
        a2 = a2 ? a2 : (int)DAT_004e0858;
        beMessenger_SendNamed(arg0->_messenger, DAT_0050eff8, a2, a3, DAT_0050f150);
        if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
            SETSTR();
        }
    } else if (strcmp(arg3->_wCheckName, DAT_0050f160) == 0) {
        if (!(FUN_00392be0((int)arg0, (int)arg2, arg3, 0) & 0xFF)) {
            SETSTR();
        }
    } else if (strcmp(arg3->_wCheckName, DAT_0050f168) == 0) {
        if (!(FUN_00392be0((int)arg0, (int)arg2, arg3, 1) & 0xFF)) {
            SETSTR();
        }
    } else {
        ((VO_394bf0 *)arg0)->vX(arg2);
    }
}

#undef SETSTR

/* Slot 39 default: empty. */
void Gap__Core__igObject__vfunc_39(void)
{
}

int FUN_00394fa0(int arg0, int arg1, A *arg2, B *arg3) {
    char *var_a0;
    char *var_a0_2;
    char *t;

    t = arg3->f8;
    if (t != 0) {
        var_a0 = t;
    } else {
        var_a0 = ((char *)DAT_004e0858);
    }
    if (strcmp(var_a0, DAT_0050f178) == 0) {
        FUN_0039a130(arg2->f228, arg1, DAT_005887c8[0]);
    } else {
        t = arg3->f8;
        if (t != 0) {
            var_a0_2 = t;
        } else {
            var_a0_2 = ((char *)DAT_004e0858);
        }
        if (strcmp(var_a0_2, DAT_0050f188) == 0) {
            FUN_0039a500(arg2->f228, arg3);
        }
    }
    return 1;
}

int FUN_00395070(int arg0, int arg1, beModelCtrlInfoWork *arg2, beModelCtrlMUTEKI *arg3) {
    if (!(FUN_003a7d80(arg1, &DAT_0050f0b8[0]) & 0xFF)) { FUN_003a7a20(arg1, &DAT_0050f0b8[0], 0); }
    if (strcmp(MutekiNameOf::Get(arg3), &DAT_0050f190[0]) == 0) { arg2->_isWallCheck = 0; }
    else if (strcmp(MutekiNameOf::Get(arg3), &DAT_0050f198[0]) == 0) { arg2->_isWallCheck = 1; }
    else if (strcmp(MutekiNameOf::Get(arg3), &DAT_0050f1a0[0]) == 0) { arg2->_isFloorCheck = 0; }
    else if (strcmp(MutekiNameOf::Get(arg3), &DAT_0050f1b0[0]) == 0) { arg2->_isFloorCheck = 1; }
    else { arg2->_mutekiCount = arg3->_frame; }
    return 1;
}

void FUN_003951e0(int a0, int a1, float *a2) {
    float f = a2[31];
    if (!(f <= 0.0f)) {
        float v = f - FUN_003a8140(a1, &DAT_0050f0b8[0]);
        if (v < 0.0f) v = 0.0f;
        a2[31] = v;
    }
}

void FUN_00395250(int arg0, int arg1, int arg2, beModelCtrlInfoWork *arg3) {
    int s7;
    const beModelCtrlData *spA0;
    int s2;
    unsigned char s1;
    VO_395250 *s0;
    s7 = 0;
    spA0 = (beModelCtrlData *)arg3->_comData;
    s2 = arg3->_comIndex;
    if (s2 != ((igObjectList *)spA0->_comList)->_count) {
        do {
            s1 = 1;
            s0 = ((VO_395250 **)((igObjectList *)spA0->_comList)->_data)[s2];
            if (DAT_00588df8[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00391a10(arg0, (LogoSeqState *)arg3, (NamedEntry *)s0));
                s2 += 1;
            } else if (DAT_00588e08[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00391fe0((beModelCtrl *)arg0, (beModelCtrlInfo *)arg1, (beBaseInfoRam *)arg2, (beModelCtrlACTION *)s0));
                s2 += 1;
            } else if (DAT_00588dd8[0] == s0->vX()) {
                s1 = FUN_00393260((beModelCtrl *)arg0, (beBaseInfoRam *)arg2, arg3, (Msg *)s0);
                s2 += 1;
            } else if (DAT_00588da0[0] == s0->vX()) {
                s1 = FUN_00393260((beModelCtrl *)arg0, (beBaseInfoRam *)arg2, arg3, (Msg *)s0);
                s2 += 1;
            } else if (DAT_00588d88[0] == s0->vX()) {
                s1 = FUN_00393260((beModelCtrl *)arg0, (beBaseInfoRam *)arg2, arg3, (Msg *)s0);
                s2 += 1;
            } else if (DAT_00588d70[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00393b20(arg0, arg2, (A2 *)arg3, (A3 *)s0));
                s2 += 1;
            } else if (DAT_00588d68[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00394b30(arg0, arg3, (igNamedObject *)s0));
                s2 += 1;
            } else if (DAT_00588d20[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00394fa0(arg0, arg2, (A *)arg3, (B *)s0));
                s2 += 1;
            } else if (DAT_00588d50[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00395070(arg0, arg2, arg3, (beModelCtrlMUTEKI *)s0));
                s2 += 1;
            } else if (DAT_00588e10[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_003943c0(arg0, arg2, (int)arg3, (beModelCtrlLABELCTRL *)s0));
                s2 += 1;
            } else if (DAT_00588e28[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00394640((beModelCtrl *)arg0, (beBaseInfo *)arg1, (beBaseInfoRam *)arg2, arg3, (beModelCtrlLUACALL *)s0));
                s2 += 1;
            } else if (DAT_00588d60[0] == s0->vX()) {
                s1 = ((unsigned char)FUN_00394920((beModelCtrl *)arg0, (beModelCtrlInfo *)arg1, (beBaseInfoRam *)arg2, arg3, (beModelCtrlMSGBOX *)s0));
                s2 += 1;
            } else if (DAT_00588df0[0] == s0->vX()) {
                s1 = FUN_00394ad0(arg0, arg1, arg3, s0);
                s2 += 1;
            } else if (DAT_00588e20[0] == s0->vX()) {
                if (arg3->_comLabelCount != 0) {
                    s1 = 0;
                } else {
                    arg3->_comLabelCount = 1;
                    s2 += 1;
                }
            } else if (DAT_00588e00[0] == s0->vX()) {
                s7 = ((unsigned char)FUN_00394ae0((void **)arg0, arg2, (beModelCtrlJUMP *)s0)) & 0xFF;
            }
        } while (s7 == 0 && (s1 & 0xFF) && s2 != ((igObjectList *)spA0->_comList)->_count);
    }
    if (!(s7 & 0xFF)) {
        arg3->_comIndex = s2;
    }
}

/* Owning stack reference to the freshly created data list, released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void FUN_003956e0(int a0, int a1, beBaseInfoRam *obj, beModelCtrlInfoWork *st, int force) {
    V3 v;
    float tmp[4];
    int i;
    float *pt;
    float *pc;
    float *spp;
    int off;
    float *pv;
    float *cp;
    int m;
    float step;
    float c;
    float t;
    float d2;
    float d1;
    float e;
    pt = (float *)&st->_targetDirection[0];
    ((float*)&v)[0] = *(float *)&st->_targetDirection[0];
    ((float*)&v)[1] = *(float *)&st->_targetDirection[1];
    ((float*)&v)[2] = *(float *)&st->_targetDirection[2];
    if (!(force & 0xff)) {
        i = 0;
        goto pre;
    body:
        if (*pc != *pt) {
            spp = (float *)((char *)&st->_directionLimiter[0] + off);
            if (*spp == 0.0f) {
                *pv = *(float *)((char *)&st->_direction[0] + off);
            } else {
                step = *spp * FUN_003a8140(obj, &DAT_0050f0b8[0]);
                c = *(float *)((char *)&st->_direction[0] + off);
                t = *(float *)((char *)&st->_targetDirection[0] + off);
                while (c < 0.0f) c += 6.2831855f;
                while (c >= 6.2831855f) c -= 6.2831855f;
                while (t < 0.0f) t += 6.2831855f;
                while (t >= 6.2831855f) t -= 6.2831855f;
                if (c <= t) {
                    d2 = t - c;
                    d1 = c - (t - 6.2831855f);
                } else {
                    d1 = c - t;
                    e = t; e += 6.2831855f; d2 = e - c;
                }
                if (d2 < d1) {
                    if (d2 > step) t = c + step;
                    else t = t;
                } else if (d1 > step) {
                    t = c - step;
                } else t = t;
                *pv = t;
            }
        }
        pt++; pc++; off += 4; pv++; i++;
    test:
        if (i < 3) goto body;
    }
    if (force == 0) {
        bool diff;
        cp = (float *)&st->_direction[0];
        diff = v.x != cp[0] || v.y != cp[1] || v.z != cp[2];
        if (!diff) goto done;
    }
    if (((Ref *)obj->_dataList) == 0) {
        int alloc = igObject_GetAllocator(obj);
        int a2;
        if (GPR_00554c14 != 0) a2 = alloc; else a2 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<igObject> created(((Ref *)beBaseInfoDataList_Create(a2)));
        Ref *r = (Ref *)created.p;
        if (r != 0) r->_refCount = r->_refCount + 1;
        Ref *old = ((Ref *)obj->_dataList);
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        obj->_dataList = (int)r;
    }
    m = ((Prop_3956e0 *)igProperty_FindByName(((Ref *)obj->_dataList), DAT_00585be0[0], &DAT_0050ef60[0]))->f16 + 32;
    Matrix44_GetTranslation(m, tmp);
    FUN_00190ed0(m, v.x, ((float*)&v)[1], ((float*)&v)[2]);
    Matrix44_SetTranslation((float *)m, (void *)tmp);
    *(float *)&st->_direction[0] = v.x;
    *(float *)&st->_direction[1] = v.y;
    *(float *)&st->_direction[2] = v.z;
done:
    return;
pre:
    pc = (float *)&st->_direction[0];
    off = 0;
    pv = &v.x;
    goto test;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void Gap__Core__igObject__vfunc_31(beModelCtrl *arg0, beBaseInfoRam *arg1) {
    int sp27C;
    float sp268[3];
    float sp258[3];
    float sp248[3];
    float sp238[3];
    int sp1F0[16];
    int sp1B0[16];
    int sp170[16];
    int sp130[16];
    int spF0[16];
    int spB0[16];
    int sp70[16];
    int s2 = arg1->_parentInfo;
    if (arg1->_dataList == 0) {
        int base = igObject_GetAllocator(arg1);
        int a;
        igObject *o;
        igObject *old;
        if (GPR_00554c14 != 0) { a = base; } else { a = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
        igSmartPointer<igObject> ref(beBaseInfoDataList_Create(a));
        o = ref.p;
        if (o != 0) o->_refCount = o->_refCount + 1;
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)o;
    }
    beModelCtrlInfoRamData *prop = (beModelCtrlInfoRamData *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]);
    beModelCtrlInfoWork *q = (beModelCtrlInfoWork *)prop->_work;
    if (arg1->_isRun != 0 && q->_isOnFreeze == 0) {
        int t;
        int posNode;
        beModelCtrlInfoRideOn4 *p;
        if (strcmp(q->_seqCodeName, &DAT_0050f1b8[0]) == 0) {
            ((MsgView *)arg0)->v33(arg1, &DAT_0050f1c0[0]);
            return;
        }
        q->_keyInput = 0;
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        t = ((int)StringPool_Intern(DAT_00586f20[0], &DAT_0050efe8[0]));
        if (q->_keyEventName != 0) {
            int *hdr = (int *)(q->_keyEventName - 8);
            int c = *(int *)(q->_keyEventName - 4) - 1;
            *(int *)(q->_keyEventName - 4) = c;
            if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
        }
        q->_keyEventName = t;
        if (q->_ctrlSt0 != 0) {
            FUN_00391cf0((VO *)arg0, s2, (int)arg1, q);
        } else if (q->_aI != 0) {
            FUN_003a8580(arg1, &DAT_0050ef68[0]);
        }
        ((UpdView *)arg0)->v46(arg1);
        if (q->_isPosLock == 0) {
            FUN_00392fa0(arg0, s2, arg1, q);
        } else {
            if (q->_posLockNode != 0) {
                Matrix44_Copy(sp1F0, q->_posLockNode + 32);
                Matrix44_TranslateLocal(sp1F0, &q->_posLockOffset[0]);
                ((NodeView_395b50 *)prop->_node)->v35(sp1F0);
            } else if (q->_posLockTrc != 0) {
                ((NodeView_395b50 *)prop->_node)->v35((int *)(*(int *)(q->_posLockTrc + 16) + *(int *)((char *)DAT_00561288[0] + 8)));
            } else if (q->_posLockModelName != 0) {
                beMessenger_SelectReceivers(arg0->_messenger, &DAT_0050eff8[0], q->_posLockModelName, arg1->_ramNo);
                beMessenger_AppendString(arg0->_messenger, q->_posLockBoneName);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050f1c8[0]);
                if (beMessenger_GetMatrixCount(arg0->_messenger) == 1) {
                    beMessenger_GetMatrix(sp1B0, arg0->_messenger, 0);
                    beMessenger_SendNamed(arg0->_messenger, &DAT_0050ef18[0], q->_posLockModelName, arg1->_ramNo, &DAT_0050f000[0]);
                    if (beMessenger_GetMatrixCount(arg0->_messenger) == 1) {
                        beMessenger_GetMatrix(sp170, arg0->_messenger, 0);
                        FUN_001906d0(sp170, sp1B0);
                        ((NodeView_395b50 *)prop->_node)->v35(sp170);
                    }
                }
            }
            if (q->_baseAABox != 0) FUN_00396940(arg0, (beModelCtrlNode2 *)prop->_node, (igAABox *)q->_baseAABox);
        }
        p = (beModelCtrlInfoRideOn4 *)q->_rideOnData;
        if (p != 0) {
            ((RideView *)p)->v21((int *)(prop->_node + 32));
            Matrix44_GetTranslation((int)p->_oldMatrix, (float *)sp268);
            Matrix44_GetTranslation(prop->_node + 32, sp258);
            sp248[0] = sp258[0] - sp268[0];
            sp248[1] = sp258[1] - sp268[1];
            sp248[2] = sp258[2] - sp268[2];
            Matrix44_Copy(sp130, p->_oldMatrix);
            Matrix44_Copy(spF0, prop->_node + 32);
            Matrix44_SetTranslation((float *)sp130, (void *)&DAT_004e1058[0]);
            FUN_00191f30(&sp27C, sp130, sp130);
            Matrix44_SetTranslation((float *)spF0, (void *)sp248);
            igMatrix44f_SetIdentity(spB0);
            FUN_001904f0(spB0, spF0, sp130);
            igMatrix44f_SetIdentity(sp70);
            FUN_001904f0(sp70, spB0, p->_modelNode + 32);
            ((NodeView_395b50 *)prop->_node)->v35(sp70);
            Matrix44_Copy(p->_oldMatrix, p->_modelNode + 32);
            q->_isHitCheck = 1;
        }
        if (q->_wCheckName != 0) FUN_00394bf0(arg0, (beModelCtrlInfo *)s2, arg1, q);
        FUN_003951e0((int)arg0, (int)arg1, (float *)q);
        FUN_00399e20(q->_subCommand, arg1);
        if (q->_isHitCheck != 0) FUN_003926d0(arg0, (beBaseInfoRam *)s2, arg1, q);
        p = (beModelCtrlInfoRideOn4 *)q->_rideOnData;
        if (p != 0 && p->_modelRamNo == 0x68) {
            Matrix44_GetTranslation(prop->_node + 32, sp238);
            ((float *)&p->_oldPlayerPos[0])[0] = sp238[0];
            ((float *)&p->_oldPlayerPos[0])[1] = sp238[1];
            ((float *)&p->_oldPlayerPos[0])[2] = sp238[2];
        }
    }
}

/* Slot 46 default: empty. */
void Gap__Core__igObject__vfunc_46(void)
{
}

int FUN_003960f0(int arg0, beModelCtrlInfoWork *self) {
    int result = 0;
    if (self->_labelSeqList != 0) {
        int name = self->_seqCodeName;
        int v;
        int idx;
        if (name == 0) {
            v = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int al = FUN_002eb010(16);
                if (al != 0) al = StringPool_Construct(al);
                DAT_00586f20[0] = al;
            }
            v = ((int)StringPool_Intern(DAT_00586f20[0], name));
        }
        {
            StringRef key((char *)v);
            idx = FUN_001cafc0(self->_labelSeqList, &key, 0);
        }
        if (idx != -1) {
            result = ((int *)((igIntList *)self->_labelOffsetList)->_data)[idx];
            if (result == -1) {
                int s2;
                beModelCtrlData *lst;
                int n, j;
                /* the copied token is a temporary: only the pointer outlives it (the list keeps its share) */
                s2 = (int)StringList_CopyRetained(self->_labelNameList, idx).p;
                lst = (beModelCtrlData *)self->_comData;
                n = ((igObjectList *)lst->_comList)->_count;
                for (j = 0; j < n; j++) {
                    Obj *o = (Obj *)((int *)((igObjectList *)lst->_comList)->_data)[j];
                    if (DAT_00588e20[0] == o->vX()) {
                        if (strcmp(o->nm != 0 ? (int *)o->nm : &DAT_004e0858[0], s2) == 0) {
                            igIntList *ia = (igIntList *)self->_labelOffsetList;
                            result = j;
                            if (ia->_count != 0 && idx >= 0 && idx < ia->_count) {
                                ((int *)ia->_data)[idx] = j;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return result;
}

/* Owning stack reference to the freshly created bound box; released on scope exit once the node
 * holds its own reference (reference count in the low 23 bits of _refCount). */

void FUN_00396940(beModelCtrl *arg0, beModelCtrlNode2 *arg1, igAABox *arg2) {
    igAABox *s0;
    s0 = (igAABox *)arg1->_bound;
    if (s0 == 0) {
        int alloc = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igAABox> created(FUN_0018a660(a));
        s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go((igAABox *)arg1->_bound);
        arg1->_bound = (int)s0;
        /* matching construct: the box is re-read from the reference before it leaves scope, so the release
         * below works on that register copy (retail 0x003969ec) */
        s0 = created.p;
    }
    s0->_min[0] = arg2->_min[0];
    s0->_min[1] = arg2->_min[1];
    s0->_min[2] = arg2->_min[2];
    s0->_max[0] = arg2->_max[0];
    s0->_max[1] = arg2->_max[1];
    s0->_max[2] = arg2->_max[2];
    FUN_0018ac80(s0, arg1->_m);
}

#define ALLOC(a, o) int a = igObject_GetAllocator(o); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
#define POOL() if (((void * *)DAT_00586f20)[0] == 0) { void *pl_ = ((void *)FUN_002eb010(0x10)); if (pl_ != 0) pl_ = ((void *)StringPool_Construct(pl_)); ((void * *)DAT_00586f20)[0] = pl_; }
#define SREL(old) if (old) { int *h_ = (int *)old - 2; int c_ = ((int *)old)[-1] - 1; ((int *)old)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*h_, h_); }
#define SETSTR(fld, txt) { POOL() const char *tk_ = ((const char *)StringPool_Intern(((void * *)DAT_00586f20)[0], txt)); const char *old_ = (const char *)d->fld; SREL(old_) d->fld = (int)tk_; }
#define NAMEOF(b) const char *b; { const char *a_ = (const char *)nm->_name; if (a_ != 0) b = a_; else b = ((char *)DAT_004e0858); }
#define FLT(x) (*(float *)&(x))
#define M (self->_messenger)
#define CV ((CtlV *)self)
#define O3 ((beModelCtrlNode2 *)node->_node)
#define OV3 ((NodeV *)node->_node)
#define LOD0(n) (((igLod **)((igObjectList *)(n)->_childList)->_data)[0])
#define MOVES(d_) ((beModelCtrlMoveObjectList *)(d_)->_moveObjectList)
#define ENSURE(ent_) Hp::Ensure(ent_, tf_);
int Gap__Bec__beModelCtrl__vfunc_33(beModelCtrl *self, beBaseInfoRam *ent, const char *msgname) {
    beBaseInfo *nm = (beBaseInfo *)ent->_parentInfo;
    V4 c0_v, c5_v, c24_p, c24_r, c6_t1, c6_t2, c26_t, c27_t, c8_258, c8_248, c8_238, c25_v, c26_v;
    float c5_m[16], c24_m[16], c6_m[16], c26_m[16], c27_m[16];
    int c6_obj;
    igObjectList *c6_lst;
    int c6_hit;
    igObject *s_;
    beModelCtrlInfoRideOn *tf_;
    ENSURE(ent)
    beModelCtrlInfoRamData *node = (beModelCtrlInfoRamData *)((beBaseInfoData *)igProperty_FindByName(ent->_dataList, DAT_00585be0[0], ((char *)DAT_0050ef60)));
    beModelCtrlInfoWork *d = (beModelCtrlInfoWork *)node->_work;
    if (CV->v47(ent, msgname) == 1) return 1;
    unsigned sel = beMessenger_ResolveEnumValue(M, FUN_00356ab0(), msgname);
    switch (sel) {
    case 0: {
        StringRef sp30C;
        sp30C.p = 0;
        ent->_isRun = 1;
        ent->_st0 = 0; ent->_st3 = 0; ent->_st2 = 0; ent->_st1 = 0;
        if (beMessenger_GetStringCount(M) == 1) {
            const char *t = beMessenger_GetString(M, 0);
            POOL()
            const char *tk = ((const char *)StringPool_Intern(((void * *)DAT_00586f20)[0], t));
            const char *o = sp30C.p;
            SREL(o)
            sp30C.p = (char *)tk;
        } else if (beMessenger_GetStringCount(M) >= 2) {
            const char *t = beMessenger_GetString(M, 1);
            POOL()
            const char *tk = ((const char *)StringPool_Intern(((void * *)DAT_00586f20)[0], t));
            const char *o = sp30C.p;
            SREL(o)
            sp30C.p = (char *)tk;
        }
        CV->v36(ent);
        beModelCtrlInfoWork *d2 = (beModelCtrlInfoWork *)node->_work;
        beDataObjInt *y = (beDataObjInt *)d2->_mHp;
        if (y->_data == 0) {
            y->_data = 0x64;
            ((beDataObjInt *)d2->_hp)->_data = 0x64;
        }
        igObject *z = (igObject *)LOD0(O3)->_bound;
        RET(z)
        REL(d2->_baseAABox)
        d2->_baseAABox = (int)z;
        beModelCtrlNode2 *o3 = O3;
        REL(o3->_bound)
        o3->_bound = 0;
        FUN_00192f50(&c0_v, ((float *)DAT_004e1098), O3->_m);
        float ang = atan2f(c0_v.x, c0_v.z);
        FLT(d2->_direction[1]) = ang;
        FLT(d2->_targetDirection[1]) = ang;
        if (((beBaseInfoData *)igProperty_FindByName(nm->_dataList, DAT_00585be0[0], ((char *)DAT_0050efd8))) != 0 ||
            ((beBaseInfoData *)igProperty_FindByName(nm->_dataList, DAT_00585be0[0], ((char *)DAT_0050efe0))) != 0) {
            ALLOC(a, self)
            ObjRef<0> r((igObject *)FUN_00352140(a));
            igObject *s = r.p;
            RET(s)
            REL(d2->_aI)
            d2->_aI = (int)s;
        }
        if (sp30C.p == 0)
            CV->v33(ent, DAT_0050eff0);
        else
            CV->v33(ent, sp30C.p);
        igObject *w = (igObject *)d2->_baseAABox;
        if (w != 0) FUN_00396940(self, O3, (igAABox *)w);
        return 1;
    }
    case 2:
        if (ent->_isRun != 0) {
            CV->v42(ent);
            beMessenger_PushArgContext(M);
            int id = ent->_ramNo;
            NAMEOF(n)
            beMessenger_SendNamed(M, ((char *)DAT_0050eff8), n, id, DAT_0050f1d8);
            if (d != 0) FUN_00399f20(d->_subCommand, ent);
            REL(node->_work)
            node->_work = 0;
            beModelCtrlNode2 *o3 = O3;
            REL(o3->_bound)
            o3->_bound = 0;
            FUN_003a8760(ent);
            ent->_isRun = 0;
            beMessenger_PopArgContext(M);
        }
        return 1;
    case 28: {
        unsigned char f = ent->_isRun;
        beMessenger_AppendBool(M, f);
        return 1;
    }
    case 29:
        if (ent->_isRun == 0) {
            beMessenger_AppendBool(M, 0);
        } else if (d == 0) {
            beMessenger_AppendBool(M, 0);
        } else if (strcmp((const char *)d->_seqCodeName, beMessenger_GetString(M, 0)) == 0) {
            beMessenger_AppendBool(M, 1);
        } else {
            beMessenger_AppendBool(M, 0);
        }
        return 1;
    case 8:
        if (ent->_isRun != 0 && d != 0) {
            float *p;
            if (beMessenger_GetVec3Count(M) == 2) {
                beMessenger_GetVec3(&c8_238, M, 1);
                p = &c8_238.x;
            } else {
                p = DAT_004e1058;
            }
            c8_248.x = p[0]; c8_248.y = p[1]; c8_248.z = p[2];
            int sub = d->_subCommand;
            const char *s2 = beMessenger_GetString(M, 0);
            const char *s1 = beMessenger_GetString(M, 1);
            float f20 = beMessenger_GetFloat(M, 0);
            beMessenger_GetVec3(&c8_258, M, 0);
            int b0 = beMessenger_GetBool(M, 0);
            FUN_0039a250(sub, s2, s1, &c8_258, &c8_248, b0, f20, beMessenger_GetBool(M, 1));
        }
        return 1;
    case 9:
        if (ent->_isRun != 0 && d != 0) {
            int sub = d->_subCommand;
            const char *s0 = beMessenger_GetString(M, 0);
            FUN_0039a750(sub, s0, beMessenger_GetFloat(M, 0));
        }
        return 1;
    case 32: {
        beModelCtrlInfoDataSeq *seq = (beModelCtrlInfoDataSeq *)((beBaseInfoData *)igProperty_FindByName(nm->_dataList, DAT_00585be0[0], DAT_0050f1e0));
        igObjectList *l = (igObjectList *)seq->_dataList;
        int n = l->_count;
        beMessenger_AppendString(M, ((char *)DAT_0050f1b8));
        int i;
        for (i = 0; i < n; i++) {
            beModelCtrlData *entry = (beModelCtrlData *)((void **)l->_data)[i];
            const char *b;
            const char *a_ = (const char *)entry->_name;
            if (a_ != 0) b = a_; else b = ((char *)DAT_004e0858);
            beMessenger_AppendString(M, b);
        }
        return 1;
    }
    case 30:
        self->_isDebugHitBox = 1;
        return 1;
    case 31:
        self->_isDebugHitBox = 0;
        return 1;
    case 3: {
        NAMEOF(n)
        beMessenger_AppendString(M, n);
        return 1;
    }
    case 4:
        if (ent->_isRun != 0) {
            NAMEOF(n)
            beMessenger_AppendString(M, n);
        }
        return 1;
    case 5:
        if (ent->_isRun != 0 && d != 0 && beMessenger_GetMatrixCount(M) != 0) {
            beMessenger_GetMatrix(c5_m, M, 0);
            OV3->v35(c5_m);
            if (d != 0) {
                FUN_00192f50(&c5_v, ((float *)DAT_004e1098), c5_m);
                float ang = atan2f(c5_v.x, c5_v.z);
                FLT(d->_direction[1]) = ang;
                FLT(d->_targetDirection[1]) = ang;
            }
            igObject *a2 = (igObject *)d->_baseAABox;
            if (a2 != 0) FUN_00396940(self, O3, (igAABox *)a2);
        }
        return 1;
    case 10:
        if (ent->_isRun == 0) return 1;
    case 11:
        beMessenger_AppendInt(M, ent->_ramNo);
        beMessenger_AppendMatrix(M, O3->_m);
        beMessenger_AppendObject(M, O3);
        return 1;
    case 12:
        if (ent->_isRun != 0 && d != 0 && d->_mutekiCount == 0.0f)
            beMessenger_AppendMatrix(M, O3->_m);
        return 1;
    case 13:
        if (ent->_isRun != 0) {
            ENSURE(ent)
            beBaseInfoData *t = ((beBaseInfoData *)igProperty_FindByName(ent->_dataList, DAT_00585be0[0], DAT_0050f1e8));
            if (t != 0) beMessenger_AppendObject(M, t);
        }
        return 1;
    case 18:
        if (ent->_isRun != 0 && d != 0) d->_isOnCtrl = 1;
        return 1;
    case 19:
        if (ent->_isRun != 0 && d != 0) {
            d->_isOnCtrl = 0;
            CV->v40(ent);
        }
        return 1;
    case 20:
        if (ent->_isRun != 0 && d != 0) {
            FUN_003a84a0(ent, 0.0f);
            int id = ent->_ramNo;
            NAMEOF(n)
            beMessenger_SendNamed(M, ((char *)DAT_0050eff8), n, id, DAT_0050f1f0);
            d->_isOnFreeze = 1;
            CV->v41(ent);
        }
        return 1;
    case 21:
        if (ent->_isRun != 0 && d != 0) {
            FUN_003a84a0(ent, 1.0f);
            int id = ent->_ramNo;
            NAMEOF(n)
            beMessenger_SendNamed(M, ((char *)DAT_0050eff8), n, id, DAT_0050f200);
            d->_isOnFreeze = 0;
        }
        return 1;
    case 22:
        if (ent->_isRun != 0 && d != 0 && d->_svLODHighRange == -1.0f) {
            int t = DAT_00561898[0];
            igLod *o = LOD0(O3);
            if (t == ((LodV *)o)->v20()) {
                igNodeList *yc = (igNodeList *)o->_childList;
                int cnt = 0;
                if (yc != 0) cnt = yc->_count;
                if (cnt == 3) {
                    igFloatList *yb = (igFloatList *)o->_rangeList;
                    d->_svLODHighRange = ((float *)yb->_data)[2];
                    int n = yb->_count;
                    if (n != 0 && n > 2) ((float *)yb->_data)[2] = DAT_004c8fb8[0];
                    ((LodV *)o)->v29();
                }
            }
        }
        return 1;
    case 23:
        if (ent->_isRun != 0 && d != 0) {
            float f = d->_svLODHighRange;
            if (f != -1.0f) {
                igLod *o = LOD0(O3);
                igFloatList *yb = (igFloatList *)o->_rangeList;
                int n = yb->_count;
                if (n != 0 && n > 2) ((float *)yb->_data)[2] = f;
                d->_svLODHighRange = -1.0f;
                ((LodV *)o)->v29();
            }
        }
        return 1;
    case 24:
        if (ent->_isRun != 0 && d != 0) {
            beMessenger_GetVec3(&c24_p, M, 0);
            beMessenger_GetVec3(&c24_r, M, 1);
            igMatrix44f_SetIdentity(c24_m);
            Matrix44_FromTranslation(c24_m, &c24_p);
            if (c24_r.x != 0.0f) FUN_00191670(c24_m, DAT_004e1078, 0.017453292f * c24_r.x);
            if (c24_r.y != 0.0f) FUN_00191670(c24_m, DAT_004e1088, 0.017453292f * c24_r.y);
            { float rz = c24_r.z; if (rz != 0.0f) FUN_00191670(c24_m, ((float *)DAT_004e1098), 0.017453292f * rz); }
            OV3->v35(c24_m);
            FLT(d->_targetDirection[1]) = 0.017453292f * c24_r.y;
            FUN_003956e0((int)self, (int)nm, ent, d, 1);
            igObject *a2 = (igObject *)d->_baseAABox;
            if (a2 != 0) FUN_00396940(self, O3, (igAABox *)a2);
        }
        return 1;
    case 7:
        if (ent->_isRun != 0 && d != 0) {
            const char *s1 = beMessenger_GetString(M, 0);
            FUN_00393c80(self, ent, d, s1, beMessenger_GetString(M, 1));
        }
        return 1;
    case 14:
        if (ent->_isRun == 0) {
            beMessenger_AppendInt(M, 0);
        } else if (d == 0) {
            beMessenger_AppendInt(M, 0);
        } else {
            beMessenger_AppendInt(M, ((beDataObjInt *)d->_hp)->_data);
            beMessenger_AppendObject(M, (void *)d->_hp);
            beMessenger_AppendObject(M, (void *)d->_mHp);
        }
        return 1;
    case 15:
        if (ent->_isRun != 0 && d != 0) {
            int v = beMessenger_GetInt(M, 0);
            ((beDataObjInt *)d->_hp)->_data = v;
            beDataObjInt *y = (beDataObjInt *)d->_mHp;
            if (y->_data < v) y->_data = v;
        }
        return 1;
    case 16:
        if (ent->_isRun != 0 && d != 0) beMessenger_AppendInt(M, d->_recNo);
        return 1;
    case 6:
        if (d->_mutekiCount != 0.0f) {
            unsigned char ok = 0;
            NAMEOF(n)
            if (*n == 0x70 && *beMessenger_GetString(M, 0) == 0x70 && d->_hp != 0) ok = 1;
            if (!(ok & 0xFF)) return 1;
        }
        if (d->_isOnCtrl == 0 || strcmp((const char *)d->_seqCodeName, ((char *)DAT_0050f1b8)) == 0) return 1;
        {
            igObject *hitbody = (igObject *)d->_hitBody;
            if (hitbody == 0) {
                ALLOC(a, self)
                ObjRef<1> r((igObject *)FUN_003523d0(a));
                igObject *s = r.p;
                RET(s)
                REL(d->_hitBody)
                d->_hitBody = (int)s;
                hitbody = r.p;
            }
            c6_obj = ((int)beMessenger_GetObject(M, 0));
            c6_lst = ((igObjectList *)FUN_003908e0((beModelCtrlInfoHitBody *)hitbody, ent, (int)O3->_m, ((igInsightCore *)self->_insight)->_worldTime));
            unsigned char found = 0;
            int idx = 0;
            int cnt = c6_lst->_count;
            for (idx = 0; idx < cnt; idx++) {
                if (!FUN_0018b050(((void **)c6_lst->_data)[idx], c6_obj)) continue;
                {
                    c6_hit = idx;
                    found = 1;
                    break;
                }
            }
            if (found) {
                int s8 = beMessenger_GetInt(M, 0);
                beMessenger_GetMatrix(c6_m, M, 0);
                const char *s5 = beMessenger_GetString(M, 0);
                int s7 = beMessenger_GetInt(M, 1);
                int r6 = -1;
                Matrix44_GetTranslation((int)c6_m, (float *)&c6_t1);
                Matrix44_GetTranslation((int)O3->_m, (float *)&c6_t2);
                beMessenger_PushArgContext(M);
                if (*s5 != 0x70) {
                    beMessenger_SendNamed(M, ((char *)DAT_0050ef18), s5, s7, DAT_0050f210);
                    if (beMessenger_GetIntCount(M) == 1)
                        r6 = beMessenger_GetInt(M, 0);
                    else
                        r6 = -9;
                }
                if (r6 != -9) {
                    NAMEOF(n)
                    FUN_00394400(self, ent, DAT_0050f220, DAT_0050f228, n, s8, c6_hit, s5, s7, r6);
                    if (((unsigned char *)DAT_0058a210)[0] != 0) {
                        FLT(d->_targetDirection[1]) = atan2f(c6_t1.x - c6_t2.x, c6_t1.z - c6_t2.z);
                        FUN_003956e0((int)self, (int)nm, ent, d, 1);
                    }
                }
                beMessenger_PopArgContext(M);
                if (beMessenger_GetBoolCount(M) == 0) beMessenger_AppendBool(M, 1);
            }
        }
        return 1;
    case 1:
    default:
        if (ent->_isRun != 0) {
            if (strcmp(msgname, ((char *)DAT_0050f1b8)) == 0) {
                CV->v43(ent);
                POOL()
                const char *tk = ((const char *)StringPool_Intern(((void * *)DAT_00586f20)[0], ((char *)DAT_0050f1b8)));
                const char *old = (const char *)d->_seqCodeName;
                SREL(old)
                d->_seqCodeName = (int)tk;
            } else if (strcmp(msgname, DAT_0050f230) == 0) {
                beMessenger_PushArgContext(M);
                int id = ent->_ramNo;
                NAMEOF(n)
                beMessenger_SendNamed(M, ((char *)DAT_0050eff8), n, id, DAT_0050f1d8);
                if (d != 0) FUN_00399f20(d->_subCommand, ent);
                beModelCtrlNode2 *o3 = O3;
                REL(o3->_bound)
                o3->_bound = 0;
                FUN_003a8760(ent);
                beMessenger_PopArgContext(M);
            } else {
                const char *tk;
                beModelCtrlInfoDataSeq *fb = (beModelCtrlInfoDataSeq *)((beBaseInfoData *)igProperty_FindByName(nm->_dataList, DAT_00585be0[0], DAT_0050f1e0));
                beModelCtrlData *t = (beModelCtrlData *)((beBaseInfoData *)igProperty_FindByName(fb->_dataList, DAT_00585be0[0], msgname));
                POOL()
                tk = ((const char *)StringPool_Intern(((void * *)DAT_00586f20)[0], msgname));
                const char *old = (const char *)d->_seqCodeName;
                SREL(old)
                d->_seqCodeName = (int)tk;
                RET(t)
                REL(d->_comData)
                d->_comData = (int)t;
                d->_comIndex = FUN_003960f0((int)self, d);
                d->_comLabelCount = 0;
                d->_ctrlSt0 = 0;
                d->_ctrlSt1 = 0;
                d->_ctrlSt1 = 0;
                ((igDataList *)d->_pdMoveDataList)->_count = 0;
                SETSTR(_wCheckName, 0)
                FUN_00399f20(d->_subCommand, ent);
                SETSTR(_luaBHit, 0)
                SETSTR(_luaWHit, 0)
                SETSTR(_luaFHit, 0)
                d->_isWallCheck = 1; d->_isFloorCheck = 1; d->_isFallCheck = 1;
                if (d->_mutekiCount < 0.0f) d->_mutekiCount = 0.0f;
                int n = MOVES(d)->_count;
                int i;
                for (i = 0; i < n; i++) {
                    beModelCtrlMoveObject *c = (beModelCtrlMoveObject *)((void **)MOVES(d)->_data)[i];
                    if (i != 3) {
                        if (c->_isSeqStop != 0) FUN_00392d90((beModelCtrlMoveObject *)c);
                    } else {
                        c->_isRun = 0;
                        c->_speed = 0;
                    }
                }
                FUN_00395250((int)self, (int)nm, (int)ent, d);
                CV->v44(ent);
            }
        }
        return 1;
    case 17:
        CV->v45(ent);
        return 1;
    case 25:
        if (d != 0) {
            if (beMessenger_GetInt(M, 0) != 0) {
                if (d->_rideOnData == 0) {
                    ALLOC(a, self)
                    ObjRef<2> r((igObject *)FUN_00351ad0(a));
                                        float *mt = (float *)O3->_m;
                    {
                        ALLOC(b, self)
                        ObjRef<5> r2((igObject *)FUN_0034fd00(b));
                        ((NodeV *)r2.p)->v35(mt);
                        s_ = r2.p;
                        tf_ = (beModelCtrlInfoRideOn *)r.p;
                        RET(s_)
                        REL(tf_->_modelNode)
                        tf_->_modelNode = (int)s_;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn2 *)r.p)->_oldMatrix, mt);
                    beMessenger_GetVec3(&c25_v, M, 0);
                    { beModelCtrlInfoRideOn2 *f2 = (beModelCtrlInfoRideOn2 *)r.p; FLT(f2->_vector) = c25_v.x; ((float *)&f2->_vector)[1] = c25_v.y; ((float *)&f2->_vector)[2] = c25_v.z; }
                    {
                        igObject *s = r.p;
                        RET(s)
                        REL(d->_rideOnData)
                        d->_rideOnData = (int)s;
                    }
                }
            } else {
                REL(d->_rideOnData)
                d->_rideOnData = 0;
            }
        }
        return 1;
    case 26:
        if (d != 0) {
            if (beMessenger_GetInt(M, 0) != 0) {
                if (d->_rideOnData == 0) {
                    ALLOC(a, self)
                    ObjRef<3> r((igObject *)FUN_00351780(a));
                                        Matrix44_GetTranslation((int)O3->_m, (float *)&c26_t);
                    Matrix44_Copy(c26_m, DAT_004e0ef0);
                    Matrix44_SetTranslation((float *)c26_m, (void *)&c26_t);
                    {
                        ALLOC(b, self)
                        ObjRef<5> r2((igObject *)FUN_0034fd00(b));
                        ((NodeV *)r2.p)->v35(c26_m);
                        s_ = r2.p;
                        tf_ = (beModelCtrlInfoRideOn *)r.p;
                        RET(s_)
                        REL(tf_->_modelNode)
                        tf_->_modelNode = (int)s_;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn3 *)r.p)->_oldMatrix, c26_m);
                    beMessenger_GetVec3(&c26_v, M, 0);
                    { beModelCtrlInfoRideOn3 *f3 = (beModelCtrlInfoRideOn3 *)r.p; FLT(f3->_worldPosition[0]) = c26_v.x; FLT(f3->_worldPosition[1]) = c26_v.y; FLT(f3->_worldPosition[2]) = c26_v.z; }
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minKyori = beMessenger_GetFloat(M, 0);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxKyori = beMessenger_GetFloat(M, 1);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minSpeed = beMessenger_GetFloat(M, 2);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxSpeed = beMessenger_GetFloat(M, 3);
                    {
                        igObject *s = r.p;
                        RET(s)
                        REL(d->_rideOnData)
                        d->_rideOnData = (int)s;
                    }
                }
            } else {
                REL(d->_rideOnData)
                d->_rideOnData = 0;
            }
        }
        return 1;
    case 27:
        if (d != 0) {
            if (beMessenger_GetInt(M, 0) != 0) {
                if (d->_rideOnData == 0) {
                    ALLOC(a, self)
                    ObjRef<4> r((igObject *)FUN_00351420(a));
                                        Matrix44_GetTranslation((int)O3->_m, (float *)&c27_t);
                    Matrix44_Copy(c27_m, DAT_004e0ef0);
                    Matrix44_SetTranslation((float *)c27_m, (void *)&c27_t);
                    {
                        ALLOC(b, self)
                        ObjRef<5> r2((igObject *)FUN_0034fd00(b));
                        ((NodeV *)r2.p)->v35(c27_m);
                        s_ = r2.p;
                        tf_ = (beModelCtrlInfoRideOn *)r.p;
                        RET(s_)
                        REL(tf_->_modelNode)
                        tf_->_modelNode = (int)s_;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn4 *)r.p)->_oldMatrix, c27_m);
                    ((int *)&c27_t)[1] = 0;
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; FLT(f4->_oldPlayerPos[0]) = c27_t.x; FLT(f4->_oldPlayerPos[1]) = c27_t.y; FLT(f4->_oldPlayerPos[2]) = c27_t.z; }
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; FLT(f4->_vector[0]) = DAT_004e1058[0]; FLT(f4->_vector[1]) = DAT_004e105c[0]; FLT(f4->_vector[2]) = DAT_004e1060[0]; }
                    ((beModelCtrlInfoRideOn4 *)r.p)->_scalar = beMessenger_GetFloat(M, 0);
                    ((beModelCtrlInfoRideOn4 *)r.p)->_limitter = beMessenger_GetFloat(M, 1);
                    {
                        igObject *s = r.p;
                        RET(s)
                        REL(d->_rideOnData)
                        d->_rideOnData = (int)s;
                    }
                }
            } else {
                REL(d->_rideOnData)
                d->_rideOnData = 0;
            }
        }
        return 1;
    }
}

#undef ENSURE
#undef MOVES
#undef LOD0
#undef OV3
#undef O3
#undef CV
#undef M
#undef FLT
#undef NAMEOF
#undef SETSTR
#undef SREL
#undef POOL
#undef ALLOC

/* Slot 45 default: empty. */
void Gap__Core__igObject__vfunc_45(void)
{
}

/* Slot 44 default: empty. */
void Gap__Core__igObject__vfunc_44(void)
{
}

/* Slot 43 default: empty. */
void Gap__Core__igObject__vfunc_43(void)
{
}

/* Slot 41 default: empty. */
void Gap__Core__igObject__vfunc_41(void)
{
}

/* Slot 40 default: empty. */
void Gap__Core__igObject__vfunc_40(void)
{
}

/* Slot 42 default: empty. */
void Gap__Core__igObject__vfunc_42(void)
{
}

/* Slot 47 default: always 0. */
int Gap__Core__igObject__vfunc_47(void) {
    return 0;
}

int Gap__Bec__beModelCtrlInfoRideOn4__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn4_metaObject[0];
}

int Gap__Bec__beModelCtrlInfoRideOn3__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn3_metaObject[0];
}

int Gap__Bec__beModelCtrlInfoRideOn2__vfunc_20(void)
{
    return g_beModelCtrlInfoRideOn2_metaObject[0];
}

int Gap__Bec__beModelCtrl__vfunc_20(void)
{
    return g_beModelCtrl_metaObject[0];
}
