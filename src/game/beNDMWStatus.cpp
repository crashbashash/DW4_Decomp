#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#define RELEASE_WIN(p_) { beNDMWWindow *rw = (p_); if (rw) { --rw->_refCount; if (!(rw->_refCount & 0x7fffff)) igObject_Destroy(rw); } }
#define GET_ALLOC(v) { void *ga = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { v = ga; } else { v = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }
#define NEXT() { info->_st0 = info->_st0 + 1; info->_st3 = 0; info->_st2 = 0; info->_st1 = 0; }
#define MK(fn) { void *al; GET_ALLOC(al) RELEASE_WIN(w.p) w.p = fn(al); }
#define RELEASE_REF(q) { igObject *rr = (igObject *)(q); if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#if __MWERKS__ >= 0x3000
#define COPY_BYTES(d, s, n) __memcpy(d, s, n)
#else
#define COPY_BYTES(d, s, n) { char *cd_ = (char *)(d); const char *cs_ = (const char *)(s); int k_; for (k_ = 0; k_ < (n); k_++) cd_[k_] = cs_[k_]; }
#endif
#define M (arg0->_messenger)
#define SEL(g) beMessenger_SelectGroup(M, g)
#define APS(s) beMessenger_AppendString(M, s)
#define DSP(d) beMessenger_DispatchSelected(M, d)
#define REC(o, s) (igProperty_GetRecord(o, &s[0])[3])
#define APPENDL(val) { igIntList *lst = (igIntList *)work->_parameter; idx = lst->_count; if (idx < lst->_capacity) lst->_count = countOf(lst) + 1; else List_Resize(lst, idx + 1, 4); ((int *)lst->_data)[idx] = (val); }
#define APPEND(val) { int idx; igIntList *lst = (igIntList *)work->_parameter; idx = lst->_count; if (idx < lst->_capacity) lst->_count = countOf(lst) + 1; else List_Resize(lst, idx + 1, 4); ((int *)lst->_data)[idx] = (val); }
#define LISTDATA(i) (((int *)((igIntList *)work->_parameter)->_data)[i])
#define COLOR(a, ref) { if (a == ref) { r = 0.9f; g = 0.9f; b = 0.9f; } else if (a < ref) { r = 0.94f; g = 0.4f; b = 0.25f; } else { g = 0.96f; b = 1.0f; r = 0.0f; } }
#define WL(f) ((igObjectList *)work->f)
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define ALLOC(a, sel) { a = igObject_GetAllocator(owner); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(sel); }
#define ITEM4(K, sp, fac, init, lst, id) { ALLOC(alloc, DAT_00587108[0]) ItemRef<K> sp((igObject *)fac(alloc)); init(sp.p, id, owner, level); ObjectList_AppendRetained(lst, sp.p); }
#define ITEM2(K, sp, fac, init, lst, id) { ALLOC(alloc, DAT_00587108[0]) ItemRef<K> sp((igObject *)fac(alloc)); init(sp.p, id); ObjectList_AppendRetained(lst, sp.p); }

extern "C" void igObject_Destroy(void *);
extern "C" int Gap__Bec__beNDMWStatus__vfunc_30(void);
extern "C" int Gap__Bec__beNDMWStatus__vfunc_20(void);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, void *, int *);
extern "C" void * igObject_GetAllocator(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" int FUN_00236f80(int, int);
extern "C" int beLua__RunNamedChunk(int, int *, int);
extern "C" void beMessenger_SelectGroup(...);
extern "C" void beMessenger_AppendString(...);
extern "C" void beMessenger_AppendInt(...);
extern "C" void beMessenger_DispatchSelected(...);
extern "C" void beMessenger_SendGroup(...);
extern "C" void beMessenger_SetFreezeTime(int, int);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_GetBool(int, int);
extern "C" void beNDMWWindow_UpdateTree(int);
extern "C" int sprintf(...);
extern "C" int FUN_003b1d70(void);
extern "C" int FUN_003bb730(void);
extern "C" int List_Resize(void *, int, int);
extern "C" int *beDataBase_GetRecordString(int, int, const void *);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_AppendObject(int, void *);
extern "C" void beMessenger_AppendVec3(int, const void *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_GetString(int, int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, int);
extern "C" void beMessenger_SendDelayedGroup(int, const void *, const void *, int);
extern "C" void beMessenger_SendNamed(...);
extern "C" int * igProperty_GetRecord(...);
extern "C" void *FUN_003b5ec0(...);
extern "C" void *FUN_003c87f0(...);
extern "C" void *FUN_003c8970(...);
extern "C" void *FUN_003c8b00(...);
extern "C" void *FUN_003c8c90(...);
extern "C" int FUN_004482e0(...);
extern "C" int FUN_00448430(...);
extern "C" int FUN_00448580(...);
extern "C" int FUN_00448660(...);
extern "C" int strcat(...);
extern "C" int List_Reserve(...);
extern "C" int ObjectList_FillRetained(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beDataBase_GetRecordInt(...);
typedef struct RefCountedObject { char pad4[4]; int f4; } RefCountedObject;
extern "C" void Gap__Bec__beNDMWStatus__vfunc_32(beNDMWStatus *arg0);
extern "C" int g_beNDMWStatusInfo_metaObject[4];
extern "C" int g_beNDMWStatus_metaObject[4];
extern "C" int DAT_00516788[4];
extern "C" void Gap__Bec__beNDMWStatus__vfunc_29(beNDMWStatus *arg0, void *arg1);
extern "C" beNDMWWindow *FUN_003b7750(void *);
extern "C" beNDMWWindow *FUN_003b7eb0(void *);
extern "C" beNDMWWindow *FUN_003bb1d0(void *);
extern "C" beNDMWWindow *beNDMWShopCtrl00_Create(void *);
extern "C" beDataObjBool * igProperty_GetRecordByte(...);
extern "C" void beNDMWWindow_BindContext(beNDMWWindow *, int, int, int, int);
extern "C" int DAT_00516790[4];
extern "C" int DAT_005167a0[4];
extern "C" int DAT_005167a8[4];
extern "C" int DAT_005167b8[4];
extern "C" int DAT_005167c8[4];
extern "C" int DAT_005167d0[4];
extern "C" int DAT_005167d8[4];
extern "C" int DAT_005167e0[4];
extern "C" int DAT_005167e8[4];
extern "C" int DAT_005167f0[4];
extern "C" int DAT_005167f8[4];
extern "C" int DAT_00516800[4];
extern "C" int DAT_00516810[4];
extern "C" int DAT_00516818[4];
extern "C" int DAT_00516828[4];
extern "C" int DAT_00516838[4];
extern "C" int DAT_00516848[4];
extern "C" int DAT_00516850[4];
extern "C" int DAT_00516860[4];
extern "C" int DAT_00516868[4];
extern "C" int DAT_00516870[4];
extern "C" int DAT_00516878[4];
extern "C" int DAT_00516888[4];
extern "C" int DAT_00516898[4];
extern "C" int DAT_005168a8[4];
extern "C" int DAT_005168b8[4];
extern "C" int DAT_005168c8[4];
extern "C" int DAT_005168d0[4];
extern "C" int DAT_00587110[4];
extern "C" int DAT_00589208[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void Gap__Bec__beNDMWStatus__vfunc_31(beNDMWStatus *self, beNDMWStatusInfoRam *info);
struct Folder { int pad[3]; igObjectList *list; };
extern "C" Folder *igProperty_GetRecordFolder(int, const void *);
extern "C" int DAT_00516910[4];
extern "C" int DAT_00516920[4];
extern "C" int DAT_00516928[4];
extern "C" int DAT_00516938[4];
extern "C" int DAT_00516940[4];
extern "C" int DAT_00516950[4];
extern "C" int DAT_00516958[4];
extern "C" int DAT_00516960[4];
extern "C" int DAT_00516968[4];
extern "C" int DAT_00516970[4];
extern "C" int DAT_00516980[4];
extern "C" int DAT_00516990[4];
extern "C" int DAT_00516998[4];
extern "C" int DAT_005169a8[4];
extern "C" int DAT_005169b8[4];
extern "C" int DAT_005169c0[4];
extern "C" int DAT_005169c8[4];
extern "C" int DAT_005169d0[4];
extern "C" int DAT_005169e0[4];
extern "C" int DAT_005169e8[4];
extern "C" int DAT_005169f0[4];
extern "C" int DAT_005169f8[4];
extern "C" int DAT_00516a00[4];
extern "C" int DAT_00516a08[4];
extern "C" int DAT_00516a10[4];
extern "C" int DAT_00516a18[4];
extern "C" int DAT_00516a20[4];
extern "C" int DAT_00516a28[4];
extern "C" int DAT_00516a38[4];
extern "C" int DAT_00516a40[4];
extern "C" int DAT_00516a48[4];
extern "C" int DAT_00516a50[4];
extern "C" int DAT_00516a60[4];
extern "C" int DAT_00516a68[4];
extern "C" int DAT_00516a78[4];
extern "C" int DAT_00516a80[4];
extern "C" int DAT_00516a90[4];
extern "C" int DAT_00516a98[4];
extern "C" int DAT_00516aa8[4];
extern "C" int DAT_00516ab0[4];
extern "C" int DAT_00516ac0[4];
extern "C" int DAT_00516ac8[4];
extern "C" int DAT_00516ad0[4];
extern "C" int DAT_00516ad8[4];
extern "C" int DAT_00516ae0[4];
extern "C" int DAT_00516ae8[4];
extern "C" int DAT_00516af0[4];
extern "C" int DAT_00516af8[4];
extern "C" int DAT_00516b00[4];
extern "C" int DAT_00516b08[4];
extern "C" int DAT_00516b10[4];
extern "C" int DAT_00516b18[4];
/* Owning stack reference to the first record of the selected folder: constructed from the object
 * (then retained) and released on scope exit (reference count in the low 23 bits of _refCount). */

struct MsgArg { int pad[5]; int f20; };
extern "C" int Gap__Bec__beNDMWStatus__vfunc_34(beNDMWStatus *arg0, beNDMWStatusInfoRam *arg1, MsgArg *arg2);
/* SUBWND service-menu work creation, BIT/XDATA caps and shop-stock list preparation. owner is
 * beNDMWStatus (the SUBWND manager) and ram is its beNDMWStatusInfoRam; _subWndNo 6..9 selects
 * weapon / armor / chip / junk stock (WPU / APU / CHIP / JUNK). U::Reserve takes a const list
 * so the count is re-read for the reserve test; the caps use '>' compares and a separate record local; the level
 * tier chains are else-if chains; row8 is declared before the loop counters; each item holder is
 * constructed at its use site from the new object and released by its destructor at scope exit;
 * the dispatch switches list their arms in ascending order. */


struct Rec { int p[3]; int f12; };
struct RecB { char p[12]; unsigned char f12; };
struct IRec { int p[3]; igDataList *f12; };
extern "C" IRec *FUN_003a9250(...);
extern "C" int DAT_00516b50[4];
extern "C" int DAT_00516b60[4];
extern "C" int DAT_00516b70[4];
extern "C" int DAT_00516b80[4];
extern "C" int DAT_00516b90[4];
extern "C" int DAT_00516b98[4];
extern "C" int DAT_00516ba8[4];
extern "C" int DAT_00587108[4];
/* Owning reference to a freshly created object: the destructor drops one reference and destroys at
 * zero. Every item kind is its own class, so the compiler emits one destructor per kind. */

template <int K> struct ItemRef { igObject *p; ItemRef(igObject *o) : p(o) {} ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
struct U { static inline void Reserve(const igObjectList *l) { if (l->_count < 37) List_Reserve(l, 36, 4); } };
extern "C" void FUN_003d8740(beNDMWStatus *owner, beNDMWStatusInfoRam *ram);

void Gap__Bec__beNDMWStatus__vfunc_32(beNDMWStatus *arg0) {
    RefCountedObject *temp_a0;

    temp_a0 = (RefCountedObject *)arg0->_windowPro;
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_windowPro = 0;
}

int Gap__Bec__beNDMWStatus__vfunc_30(void)
{
    return g_beNDMWStatusInfo_metaObject[0];
}

void Gap__Bec__beNDMWStatus__vfunc_29(beNDMWStatus *arg0, void *arg1) {
    if (((beBaseInfoList *)arg0->_infoList)->_count == 1) {
        beMessenger_RegisterReceiverFromInfo(arg0->_messenger, arg1, &DAT_00516788[0]);
        *(char *)((char *)(arg1) + 20) = 0;
    }
}

void Gap__Bec__beNDMWStatus__vfunc_31(beNDMWStatus *self, beNDMWStatusInfoRam *info)
{
    int st;
    if (info->_isRun == 0) return;
    st = info->_st0;
    switch (st) {
    case 0:
        FUN_003d8740((beNDMWStatus *)self, (beNDMWStatusInfoRam *)info);
        beMessenger_SelectGroup(self->_messenger, DAT_00516790);
        beMessenger_AppendString(self->_messenger, DAT_005167a0);
        beMessenger_DispatchSelected(self->_messenger, DAT_005167a8);
        {
        igSmartPointer<beNDMWWindow> w(0);
        switch (self->_subWndNo) {
        case 0:
            beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
            beMessenger_AppendString(self->_messenger, DAT_005167c8);
            beMessenger_AppendString(self->_messenger, DAT_005167d0);
            beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
            beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
            beMessenger_AppendString(self->_messenger, DAT_005167e0);
            beMessenger_AppendString(self->_messenger, DAT_005167d0);
            beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
            MK(FUN_003bb1d0)
            break;
        case 1: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
            MK(beNDMWShopCtrl00_Create)
            break;
        case 2:
            MK(FUN_003b7750)
            break;
        case 10:
            MK(FUN_003b7eb0)
            break;
        }
        beNDMWWindow_BindContext(w.p, 0, self->_insight, self->_whoGenerate, 0);
        w.p->_entCode = self->_subWndNo;
        {
            beNDMWWindow *s2 = w.p;
            if (s2) ++s2->_refCount;
            RELEASE_WIN((beNDMWWindow *)self->_windowPro)
            self->_windowPro = (int)s2;
        }
        if (self->_subWndNo != 0) {
            beMessenger_SendGroup(self->_messenger, DAT_005167e8, DAT_005167f0);
            beMessenger_SendGroup(self->_messenger, DAT_005167e8, DAT_005167f8);
            beMessenger_SelectGroup(self->_messenger, DAT_005167e8);
            beMessenger_AppendString(self->_messenger, DAT_00516800);
            beMessenger_DispatchSelected(self->_messenger, DAT_00516810);
        }
        }
        NEXT()
    case 1:
        if (self->_windowPro != 0) beNDMWWindow_UpdateTree(self->_windowPro);
        if (((beNDMWWindow *)self->_windowPro)->_isRun != 0) return;
        NEXT()
    default:
        {
            int i;
            RELEASE_WIN((beNDMWWindow *)self->_windowPro)
            self->_windowPro = 0;
            beMessenger_SendGroup(self->_messenger, DAT_005167e8, DAT_00516818);
            beMessenger_SendGroup(self->_messenger, DAT_00516828, DAT_00516818);
            beMessenger_SendGroup(self->_messenger, DAT_00516838, DAT_00516818);
            beMessenger_SetFreezeTime(self->_messenger, 0);
            info->_isRun = 0;
            i = 0;
            do {
                beMessenger_SelectGroup(self->_messenger, DAT_00516848);
                beMessenger_AppendInt(self->_messenger, i);
                beMessenger_DispatchSelected(self->_messenger, DAT_00516850);
                if (igProperty_GetRecordByte(beMessenger_GetObject(self->_messenger, 0), DAT_00516860)->_data != 0) {
                    beMessenger_SelectGroup(self->_messenger, DAT_00516848);
                    beMessenger_AppendInt(self->_messenger, i);
                    beMessenger_AppendInt(self->_messenger, 0);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00516868);
                    beMessenger_SelectGroup(self->_messenger, DAT_00516848);
                    beMessenger_AppendInt(self->_messenger, i);
                    beMessenger_AppendInt(self->_messenger, 0);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00516870);
                }
                i++;
            } while (i < 4);
            if (self->_subWndNo == 10) {
                beMessenger_SendGroup(self->_messenger, DAT_00516790, DAT_00516878);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xff) == 0) {
                    beMessenger_SelectGroup(self->_messenger, DAT_00516888);
                    beMessenger_AppendInt(self->_messenger, 4);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00516898);
                    beMessenger_SelectGroup(self->_messenger, DAT_00516790);
                    beMessenger_AppendString(self->_messenger, DAT_005168a8);
                    beMessenger_DispatchSelected(self->_messenger, DAT_005168b8);
                }
            } else {
                beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
                beMessenger_AppendString(self->_messenger, DAT_005167c8);
                beMessenger_AppendString(self->_messenger, DAT_005168c8);
                beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
                beMessenger_SelectGroup(self->_messenger, DAT_005167b8);
                beMessenger_AppendString(self->_messenger, DAT_005167e0);
                beMessenger_AppendString(self->_messenger, DAT_005168c8);
                beMessenger_DispatchSelected(self->_messenger, DAT_005167d8);
                if (self->_subWndNo != 0)
                    beLua__RunNamedChunk(FUN_00236f80(self->_insight, DAT_00589208[0]), DAT_005168d0, 0);
            }
        }
    }
}

/* Message handler of the status screen (enum-dispatched). Every DAT_ string is declared int[4] on
 * purpose: a small object (<= 8 bytes) is addressed gp-relative, which makes gp a live physical
 * neighbour of every node and shifts the whole s-register colouring. The block-local order `int
 * idx; int v = ...; { igIntList *lst = ...; idx = ...; }` gives the per-row nodes the ids idx < v
 * < lst, the push order needed (colours idx s5, v s4, lst s3). beMessenger_AppendBool takes an
 * unsigned char and beMessenger_AppendObject a pointer: the argument type decides which of the two
 * argument loads lands in the delay slot. The 5 and 2 byte copies are the compiler's __memcpy
 * intrinsic (alternate compiler only; the default compiler crashes on it). */

static inline int countOf(const igIntList *l) { return l->_count; }

int Gap__Bec__beNDMWStatus__vfunc_34(beNDMWStatus *arg0, beNDMWStatusInfoRam *arg1, MsgArg *arg2) {
    unsigned int kind = beMessenger_ResolveEnumValue(arg0->_messenger, FUN_003bb730(), arg2->f20);
    float v0[3];
    float v1[3];
    float v2[3];
    float v3[3];
    float v4[3];
    float v5[3];
    float v6[3];
    float v7[3];
    float v8[3];
    float v9[3];
    float v10[3];
    char b2[16];
    char b4[16];
    char b5[16];
    int s3;
    int cnt;
    int s7;
    int s8;
    beNDMWStatusInfoWork *work;
    int obj;
    switch (kind) {
    case 6:
        beMessenger_AppendBool(M, arg1->_isRun);
        return 1;
    case 0:
        if (arg1->_isRun == 0) {
            int a = beMessenger_GetInt(M, 0);
            int b = beMessenger_GetString(M, 0);
            unsigned int c = beMessenger_ResolveEnumValue(M, FUN_003b1d70(), b);
            arg1->_isRun = 1;
            arg1->_st0 = 0;
            arg1->_st3 = 0;
            arg1->_st2 = 0;
            arg1->_st1 = 0;
            arg0->_subWndNo = c;
            arg0->_whoGenerate = a;
            beMessenger_SendGroup(M, &DAT_00516838[0], &DAT_00516910[0]);
            beMessenger_SendGroup(M, &DAT_00516828[0], &DAT_00516910[0]);
            beMessenger_SetFreezeTime(M, 1);
            beMessenger_SendGroup(M, &DAT_005167e8[0], &DAT_00516910[0]);
        }
        return 1;
    case 1:
        if (arg1->_isRun == 1) {
            beNDMWWindow *wp = (beNDMWWindow *)arg0->_windowPro;
            if (wp != 0) {
                wp->_st0 = 2;
                wp->_st3 = 0;
                wp->_st2 = 0;
                wp->_st1 = 0;
            } else {
                beMessenger_SetFreezeTime(M, 0);
                beMessenger_SendDelayedGroup(M, &DAT_00516788[0], &DAT_00516920[0], 1);
            }
        }
        return 1;
    case 2: {
        work = (beNDMWStatusInfoWork *)arg1->_work;
        s3 = beMessenger_GetInt(M, 0);
        if (work == 0) {
            FUN_003d8740((beNDMWStatus *)arg0, (beNDMWStatusInfoRam *)arg1);
            work = (beNDMWStatusInfoWork *)arg1->_work;
        }
        ((igIntList *)work->_parameter)->_count = 0;
        SEL(&DAT_00516848[0]);
        beMessenger_AppendInt(M, s3);
        DSP(&DAT_00516850[0]);
        obj = beMessenger_GetObject(M, 0);
        igSmartPointer<igObject> ref(((igObject **)igProperty_GetRecordFolder(obj, &DAT_00516928[0])->list->_data)[0]);
        if (ref.p != 0) ref.p->_refCount = ref.p->_refCount + 1;
        SEL(&DAT_00516938[0]);
        APS(&DAT_00516940[0]);
        APS(&DAT_00516950[0]);
        beMessenger_AppendObject(M, ref.p);
        DSP(&DAT_00516958[0]);
        cnt = REC(obj, DAT_00516960);
        if (cnt > 999) cnt = 999;
        sprintf(b2, &DAT_00516968[0], cnt);
        SEL(&DAT_00516938[0]);
        APS(&DAT_00516970[0]);
        APS(&DAT_00516950[0]);
        APS(b2);
        DSP(&DAT_00516958[0]);
        beMessenger_SendNamed(M, &DAT_00516980[0], &DAT_00516990[0], 0, &DAT_00516998[0]);
        {
            int db = beMessenger_GetObject(M, 0);
            int *str = beDataBase_GetRecordString(db, REC(obj, DAT_005169a8), &DAT_005169b8[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_00516970[0]);
            APS(&DAT_005169c0[0]);
            APS(str);
            DSP(&DAT_00516958[0]);
        }
        s7 = REC(obj, DAT_005169c8);
        sprintf(b2, &DAT_00516968[0], s7);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516950[0]);
        APS(b2);
        DSP(&DAT_00516958[0]);
        s8 = REC(obj, DAT_005169e0);
        sprintf(b2, &DAT_00516968[0], s8);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_005169c0[0]);
        APS(b2);
        DSP(&DAT_00516958[0]);
        {
            int idx; int v = REC(obj, DAT_005169e8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_005169f0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_005169f8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a00[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a08);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a10[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a18);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a20[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a28);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a38[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a40);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a48[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a50);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a60[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a68);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a78[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a80);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a90[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516a98);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516aa8[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516ab0);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ac0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
            APPENDL(v);
        }
        {
            int idx; int v = REC(obj, DAT_00516ac8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ad0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
        }
        {
            int idx; int v = REC(obj, DAT_00516ad8);
            sprintf(b2, &DAT_00516968[0], v);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ae0[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
        }
        {
            int lo = REC(obj, DAT_00516ae8);
            int diff = REC(obj, DAT_00516af0) - lo;
            if (cnt >= 999) {
                COPY_BYTES(b2, DAT_00516af8, 5);
            } else if (diff < 0) {
                COPY_BYTES(b2, DAT_00516b00, 2);
            } else {
                sprintf(b2, &DAT_00516968[0], diff);
            }
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516b08[0]);
            APS(b2);
            DSP(&DAT_00516958[0]);
        }
        APPEND(s7);
        APPEND(s8);
        return 1;
    }
    case 4: {
        int s1;
        int obj;
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)arg1->_work;
        s1 = beMessenger_GetInt(M, 0);
        float r, g, b;
        SEL(&DAT_00516848[0]);
        beMessenger_AppendInt(M, s1);
        DSP(&DAT_00516850[0]);
        obj = beMessenger_GetObject(M, 0);
        {
            int a2 = REC(obj, DAT_005169e8);
            int ref = LISTDATA(0);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_005169f0[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_005169f0[0]);
            v0[0] = r; v0[1] = g; v0[2] = b;
            beMessenger_AppendVec3(M, v0);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_005169f8);
            int ref = LISTDATA(1);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a00[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a00[0]);
            v1[0] = r; v1[1] = g; v1[2] = b;
            beMessenger_AppendVec3(M, v1);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a08);
            int ref = LISTDATA(2);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a10[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a10[0]);
            v2[0] = r; v2[1] = g; v2[2] = b;
            beMessenger_AppendVec3(M, v2);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a18);
            int ref = LISTDATA(3);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a20[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a20[0]);
            v3[0] = r; v3[1] = g; v3[2] = b;
            beMessenger_AppendVec3(M, v3);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a28);
            int ref = LISTDATA(4);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a38[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a38[0]);
            v4[0] = r; v4[1] = g; v4[2] = b;
            beMessenger_AppendVec3(M, v4);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a40);
            int ref = LISTDATA(5);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a48[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a48[0]);
            v5[0] = r; v5[1] = g; v5[2] = b;
            beMessenger_AppendVec3(M, v5);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a50);
            int ref = LISTDATA(6);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a60[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a60[0]);
            v6[0] = r; v6[1] = g; v6[2] = b;
            beMessenger_AppendVec3(M, v6);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a68);
            int ref = LISTDATA(7);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a78[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a78[0]);
            v7[0] = r; v7[1] = g; v7[2] = b;
            beMessenger_AppendVec3(M, v7);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a80);
            int ref = LISTDATA(8);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a90[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516a90[0]);
            v8[0] = r; v8[1] = g; v8[2] = b;
            beMessenger_AppendVec3(M, v8);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516a98);
            int ref = LISTDATA(9);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516aa8[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516aa8[0]);
            v9[0] = r; v9[1] = g; v9[2] = b;
            beMessenger_AppendVec3(M, v9);
            DSP(&DAT_00516b10[0]);
        }
        {
            int a2 = REC(obj, DAT_00516ab0);
            int ref = LISTDATA(10);
            COLOR(a2, ref)
            sprintf(b4, &DAT_00516968[0], a2);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ac0[0]);
            APS(b4);
            DSP(&DAT_00516958[0]);
            SEL(&DAT_00516938[0]);
            APS(&DAT_005169d0[0]);
            APS(&DAT_00516ac0[0]);
            v10[0] = r; v10[1] = g; v10[2] = b;
            beMessenger_AppendVec3(M, v10);
            DSP(&DAT_00516b10[0]);
        }
        return 1;
    }
    case 5: {
        int s1;
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)arg1->_work;
        s1 = beMessenger_GetInt(M, 0);
        int *pv;
        int s4, s3, obj;
        sprintf(b5, &DAT_00516968[0], LISTDATA(0));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_005169f0[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_005169f0[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(1));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a00[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a00[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(2));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a10[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a10[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(3));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a20[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a20[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(4));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a38[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a38[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(5));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a48[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a48[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(6));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a60[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a60[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(7));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a78[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a78[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(8));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a90[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516a90[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(9));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516aa8[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516aa8[0]);
        DSP(&DAT_00516b18[0]);
        sprintf(b5, &DAT_00516968[0], LISTDATA(10));
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516ac0[0]);
        APS(b5);
        DSP(&DAT_00516958[0]);
        SEL(&DAT_00516938[0]);
        APS(&DAT_005169d0[0]);
        APS(&DAT_00516ac0[0]);
        DSP(&DAT_00516b18[0]);
        pv = (int *)((igIntList *)work->_parameter)->_data;
        s4 = pv[11];
        s3 = pv[12];
        SEL(&DAT_00516848[0]);
        beMessenger_AppendInt(M, s1);
        DSP(&DAT_00516850[0]);
        obj = beMessenger_GetObject(M, 0);
        REC(obj, DAT_005169c8) = s4;
        REC(obj, DAT_005169e0) = s3;
        return 1;
    }
    case 3: {
        beNDMWStatusInfoWork *work = (beNDMWStatusInfoWork *)arg1->_work;
        int what = beMessenger_GetInt(M, 0);
                switch (what) {
        case 6:
            beMessenger_AppendObject(M, (void *)work->_weaponSalesList);
            break;
        case 7:
            beMessenger_AppendObject(M, (void *)work->_armorSalesList);
            break;
        case 8:
            beMessenger_AppendObject(M, (void *)work->_chipSalesList);
            break;
        case 9:
            beMessenger_AppendObject(M, (void *)work->_junkSalesList);
            beMessenger_AppendInt(M, work->_junkGift);
            break;
        }
        return 1;
    }
    default:
        return 0;
    }
}

void FUN_003d8740(beNDMWStatus *owner, beNDMWStatusInfoRam *ram) {
    char buf6[8];
    char buf7[8];
    char buf8[8];
    char buf9[8];
    beNDMWStatusInfoWork *work;
    void *alloc;
    int joined;
    int pl;
    int folder;
    int level;
    int base;
    int row;
    int data;
    int row8;
    int i6, i7a, i7b, i8, i9;
    int id;
    int kind;
    int rowIdx;
    int common;
    int invested;
    int jrow;
    IRec *prop;

    work = (beNDMWStatusInfoWork *)ram->_work;
    if (work == 0) {
        ALLOC(alloc, DAT_00587110[0])
        igSmartPointer<beNDMWStatusInfoWork> spWork((beNDMWStatusInfoWork *)FUN_003b5ec0(alloc));
        igObject *w = spWork.p;
        if (w != 0) w->_refCount = w->_refCount + 1;
        { igObject *old = (igObject *)ram->_work; REL(old) }
        ram->_work = (int)w;
        work = (beNDMWStatusInfoWork *)ram->_work;
    }
    joined = 0;
    pl = 0;
    do {
        beMessenger_SelectGroup(owner->_messenger, &DAT_00516848[0]);
        beMessenger_AppendInt(owner->_messenger, pl);
        beMessenger_DispatchSelected(owner->_messenger, &DAT_00516850[0]);
        folder = beMessenger_GetObject(owner->_messenger, 0);
        if (((RecB *)igProperty_GetRecordByte(folder, &DAT_00516860[0]))->f12 != 0) {
            joined += 1;
            if (((Rec *)igProperty_GetRecord(folder, &DAT_00516ad8[0]))->f12 > 9999999) {
                Rec *r1 = ((Rec *)igProperty_GetRecord(folder, &DAT_00516ad8[0]));
                r1->f12 = 9999999;
            }
            if (((Rec *)igProperty_GetRecord(folder, &DAT_00516ac8[0]))->f12 > 9999) {
                Rec *r2 = ((Rec *)igProperty_GetRecord(folder, &DAT_00516ac8[0]));
                r2->f12 = 9999;
            }
        }
        pl += 1;
    } while (pl < 4);
    beMessenger_SelectGroup(owner->_messenger, &DAT_00516848[0]);
    beMessenger_AppendInt(owner->_messenger, 0);
    beMessenger_DispatchSelected(owner->_messenger, &DAT_00516850[0]);
    folder = beMessenger_GetObject(owner->_messenger, 0);
    level = ((Rec *)igProperty_GetRecord(folder, &DAT_00516960[0]))->f12;
    switch (owner->_subWndNo) {
    case 6:
        if (WL(_weaponSalesList)->_count <= 0) {
            U::Reserve(WL(_weaponSalesList));
            ObjectList_FillRetained(WL(_weaponSalesList), 0);
            if (joined > 1) {
                base = 150;
            } else {
                switch (((Rec *)igProperty_GetRecord(folder, &DAT_005169a8[0]))->f12) {
                case 15: default: base = 0; break;
                case 1: case 4: case 12: base = 25; break;
                case 2: case 7: case 14: base = 50; break;
                case 3: case 9: base = 75; break;
                case 8: case 11: case 13: base = 125; break;
                case 6: case 10: base = 100; break;
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
            beMessenger_SendNamed(owner->_messenger, &DAT_00516980[0], &DAT_00516b50[0], 0, &DAT_00516998[0]);
            data = beMessenger_GetObject(owner->_messenger, 0);
            rowIdx = base + row;
            i6 = 0;
            do {
                buf6[0] = i6 / 10 + 48; buf6[1] = i6 % 10 + 48; buf6[2] = 0;
                id = beDataBase_GetRecordInt(data, rowIdx, buf6);
                if (id != -1) {
                    ITEM4(1, spWpn, FUN_003c8c90, FUN_004482e0, WL(_weaponSalesList), id)
                } else {
                    ObjectList_AppendRetained(WL(_weaponSalesList), 0);
                }
                i6 += 1;
            } while (i6 < 36);
        }
        break;
    case 7:
        if (WL(_armorSalesList)->_count <= 0) {
            U::Reserve(WL(_armorSalesList));
            ObjectList_FillRetained(WL(_armorSalesList), 0);
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
            beMessenger_SendNamed(owner->_messenger, &DAT_00516980[0], &DAT_00516b60[0], 0, &DAT_00516998[0]);
            data = beMessenger_GetObject(owner->_messenger, 0);
            i7a = 0;
            do {
                buf7[0] = i7a / 10 + 48; buf7[1] = i7a % 10 + 48; buf7[2] = 0;
                id = beDataBase_GetRecordInt(data, row, buf7);
                ITEM4(2, spBlue, FUN_003c8b00, FUN_00448430, WL(_armorSalesList), id)
                i7a += 1;
            } while (i7a < 12);
            i7b = 12;
            do {
                buf7[0] = i7b / 10 + 48; buf7[1] = i7b % 10 + 48; buf7[2] = 0;
                kind = beDataBase_GetRecordInt(data, row, buf7);
                if (kind != -1) {
                    ITEM4(3, spYel, FUN_003c8970, FUN_00448580, WL(_armorSalesList), kind)
                } else {
                    ObjectList_AppendRetained(WL(_armorSalesList), 0);
                }
                i7b += 1;
            } while (i7b < 36);
        }
        break;
    case 8:
        if (WL(_chipSalesList)->_count <= 0) {
            U::Reserve(WL(_chipSalesList));
            ObjectList_FillRetained(WL(_chipSalesList), 0);
            if (level < 10) row8 = 0;
            else if (level < 17) row8 = 1;
            else if (level < 22) row8 = 2;
            else if (level < 27) row8 = 3;
            else if (level < 32) row8 = 4;
            else if (level < 37) row8 = 5;
            else if (level < 42) row8 = 6;
            else if (level < 47) row8 = 7;
            else if (level < 52) row8 = 8;
            else if (level < 61) row8 = 9;
            else if (level < 68) row8 = 10;
            else if (level < 73) row8 = 11;
            else if (level < 78) row8 = 12;
            else if (level < 83) row8 = 13;
            else if (level < 88) row8 = 14;
            else if (level < 93) row8 = 15;
            else if (level < 98) row8 = 16;
            else if (level < 103) row8 = 17;
            else if (level < 108) row8 = 18;
            else if (level < 113) row8 = 19;
            else if (level < 118) row8 = 20;
            else if (level < 128) row8 = 21;
            else if (level < 138) row8 = 22;
            else if (level < 148) row8 = 23;
            else if (level < 158) row8 = 24;
            else if (level < 168) row8 = 25;
            else if (level < 178) row8 = 26;
            else if (level < 188) row8 = 27;
            else if (level < 198) row8 = 28;
            else row8 = 29;
            beMessenger_SendNamed(owner->_messenger, &DAT_00516980[0], &DAT_00516b70[0], 0, &DAT_00516998[0]);
            data = beMessenger_GetObject(owner->_messenger, 0);
            i8 = 0;
            do {
                buf8[0] = i8 / 10 + 48; buf8[1] = i8 % 10 + 48; buf8[2] = 0;
                id = beDataBase_GetRecordInt(data, row8, buf8);
                if (id != -1) {
                    ITEM2(4, spChip, FUN_003c87f0, FUN_00448660, WL(_chipSalesList), id)
                } else {
                    ObjectList_AppendRetained(WL(_chipSalesList), 0);
                }
                i8 += 1;
            } while (i8 < 36);
        }
        break;
    case 9:
        beMessenger_SendGroup(owner->_messenger, &DAT_00516848[0], &DAT_00516b80[0]);
        common = beMessenger_GetObject(owner->_messenger, 0);
        prop = FUN_003a9250(common, &DAT_00516b90[0]);
        invested = ((int *)prop->f12->_data)[1];
        if (invested >= 3956000) jrow = 8;
        else if (invested >= 1956000) jrow = 7;
        else if (invested >= 956000) jrow = 6;
        else if (invested >= 456000) jrow = 5;
        else if (invested >= 206000) jrow = 4;
        else if (invested >= 86000) jrow = 3;
        else if (invested >= 26000) jrow = 2;
        else if (invested >= 6000) jrow = 1;
        else if (invested >= 1000) jrow = 0;
        else jrow = -1;
        if (WL(_junkSalesList)->_count <= 0) {
            work->_junkGift = invested;
            U::Reserve(WL(_junkSalesList));
            ObjectList_FillRetained(WL(_junkSalesList), 0);
            if (jrow != -1) {
                beMessenger_SendNamed(owner->_messenger, &DAT_00516980[0], &DAT_00516b98[0], 0, &DAT_00516998[0]);
                data = beMessenger_GetObject(owner->_messenger, 0);
                i9 = 0;
                do {
                    buf9[0] = i9 / 10 + 48; buf9[1] = i9 % 10 + 48; buf9[2] = 0;
                    id = beDataBase_GetRecordInt(data, jrow, buf9);
                    if (id != -1) {
                        strcat(buf9, &DAT_00516ba8[0]);
                        kind = beDataBase_GetRecordInt(data, jrow, buf9);
                        switch (kind) {
                        case 0:
                            ITEM4(1, spJWpn, FUN_003c8c90, FUN_004482e0, WL(_junkSalesList), id)
                            break;
                        case 1:
                            ITEM4(2, spJBlue, FUN_003c8b00, FUN_00448430, WL(_junkSalesList), id)
                            break;
                        case 2:
                            ITEM4(3, spJYel, FUN_003c8970, FUN_00448580, WL(_junkSalesList), id)
                            break;
                        }
                    }
                    i9 += 1;
                } while (i9 < 36);
            }
        }
        break;
    }
}

int Gap__Bec__beNDMWStatus__vfunc_20(void)
{
    return g_beNDMWStatus_metaObject[0];
}
