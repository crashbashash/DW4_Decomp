#include "dw4/reflected.h"
#define APPENDSTR(list, text) { const char *tok; if ((text) == 0) { tok = 0; } else { if (g_stringPool[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); g_stringPool[0] = pool; } tok = (const char *)StringPool_Intern(g_stringPool[0], (void *)(text)); } StringList_AppendRetained(list, StringRef(tok)); }
#define DEREF(o) if (o) { (o)->rc = (o)->rc - 1; if (((unsigned long long)((long long)(o)->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o); }
#define NEWWIN(kind, w, ctor, code) int alloc; int a; alloc = ((int)igObject_GetAllocator(self)); a = GPR_00554c14 != 0 ? alloc : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])); igSmartPointer<kind> w((kind *)ctor(a)); beNDMWWindow_BindContext(w.p, self, self->_insight, self->_playerNo, code); ObjectList_AppendRetained(self->_subWindow, w.p);
#define INC(l, n) { int ix = n; int cnt; int *dp; int *pp; int nv; dp = (int *)(l)->_data; pp = &dp[ix]; cnt = (l)->_count; nv = *pp + 1; if (cnt != 0 && ix < cnt) *pp = nv; }
#define CEILD(dst, e) { int m = (e); int r = (m - 45) % 5; int q = (m - 45 - r) / 5; dst = q + (r != 0); }
#define CNT ((igObjectList *)self->_subWindow)->_count
#define BUMP(sub) self->_st2 = self->_st2 + 1; self->_st3 = 0;
#define PRICE(rec, key, lim) { }
#define LCNT(l) (((igObjectList *)(l))->_count)
#define LDAT(l) ((int *)((igObjectList *)(l))->_data)
#define REL(o) { igObject *rr = (o); if (rr != 0) { *(int *)&rr->_refCount = *(int *)&rr->_refCount - 1; if (((unsigned long long)((long long)*(int *)&rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define FINDWINV(w, i) { w = 0; i = 0; if (0 < LCNT(arg0->_subWindow)) { do { beNDMWStatusCtrlD0 *c = (beNDMWStatusCtrlD0 *)((int *)((igObjectList *)*(int *)&arg0->_subWindow)->_data)[i]; if (c != 0 && igObject_IsKindOf(c, g_beNDMWStatusCtrlD0_metaObject[0]) != 0) { w = c; } else { w = 0; } if (w != 0) break; i++; } while (i < LCNT(arg0->_subWindow)); } }
#define FINDWIN(w, i) { w = 0; i = 0; if (0 < LCNT(((beNDMWShopCtrl30 *)arg0)->_subWindow)) { do { beNDMWStatusCtrlD0 *c = (beNDMWStatusCtrlD0 *)LDAT(arg0->_subWindow)[i]; if (c != 0 && igObject_IsKindOf(c, g_beNDMWStatusCtrlD0_metaObject[0]) != 0) { w = c; } else { w = 0; } if (w != 0) break; i++; } while (i < LCNT(arg0->_subWindow)); } }
#define RELS(o) { char *rs = (o); if (rs != 0) { int *hd = (int *)rs - 2; int rc = hd[1] - 1; hd[1] = rc; if (rc == 0) { StringChunk_ReleaseHeader(hd[0], hd); } } }
#define FINDWIN_429630(w, i) { w = 0; i = 0; if (0 < LCNT(((beNDMWShopCtrl30 *)arg0)->_subWindow)) { do { beNDMWWindow *c = (beNDMWWindow *)LDAT(arg0->_subWindow)[i]; if (c != 0 && igObject_IsKindOf(c, g_beNDMWStatusCtrlD0_metaObject[0]) != 0) { w = c; } else { w = 0; } if (w != 0) break; i++; } while (i < LCNT(arg0->_subWindow)); } }
#include "dw4/igSmartPointer.h"
#define INTERN_APPEND(lst, text) { char *tok = U::InternStr((char *)(text)); StringList_AppendRetained(lst, StringRef(tok)); }
#define ALLOC(a, self) { \
    a = igObject_GetAllocator(self); \
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define REL_42a2e0(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define VCNT(l) ((l)->_count)
#define SUBCNT(s) (((beNDMWWindowList *)(s)->_subWindow)->_count)
#define W(p, off) (*(int *)((int)(p) + (off)))
#define CLEAR_LIST(L, lst) { \
    int n = L->_count; int k = 0; \
    if (0 < n) { int off = 0; do { \
        char **e = (char **)((int)L->_data + off); \
        if (g_stringPool[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); g_stringPool[0] = pool; } \
        char *nw = StringPool_Intern(g_stringPool[0], 0); char *old = *e; \
        if (old != 0) { int *hd = (int *)old - 2; int cnt = ((int *)old)[-1] - 1; ((int *)old)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } \
        k += 1; *e = nw; off += 4; \
    } while (k < n); } }
#define CLEAR1(L, lst) { \
    int n; \
    int k; \
    char **e; \
    char *nw; \
    int off; \
    char *old; \
    n = L->_count; k = 0; \
    if (0 < n) { off = 0; do { \
        e = (char **)((int)L->_data + off); \
        if (g_stringPool[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); g_stringPool[0] = pool; } \
        nw = StringPool_Intern(g_stringPool[0], 0); old = *e; \
        if (old != 0) { int *hd = (int *)old - 2; int cnt = ((int *)old)[-1] - 1; ((int *)old)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } \
        k += 1; *e = nw; off += 4; \
    } while (k < n); } }
#define REL_42bc70(o) { Rc_42bc70 *rr = (o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define PUSHB(lp, v) { igBoolList *L = (igBoolList *)(lp); int n = L->_count; if (n < L->_capacity) L->_count = n + 1; else List_Resize(L, n + 1, 1); n[(unsigned char *)L->_data] = (v); }
#define REL_42eb80(o) { Rc_42eb80 *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define CLEAR(L) { igStringRefList *l = (igStringRefList *)(L); int n = l->_count; int i; int *slot; int nw; for (i = 0; i < n; i++) { slot = (int *)l->_data + i; if (g_stringPool[0] == 0) { int v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); g_stringPool[0] = v; } nw = ((int)StringPool_Intern(g_stringPool[0], 0)); { int *old = (int *)*slot; if (old != 0) { int *hdr = old - 2; int c = hdr[1] - 1; hdr[1] = c; if (c == 0) StringChunk_ReleaseHeader(hdr[0], hdr); } } *slot = nw; } l->_count = 0; }
#define ALLOC_42f710(a, self) { a = igObject_GetAllocator(self); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); }
#define APPENDSTR_42f710(list, text) { char *tok; if ((text) == 0) { tok = 0; } else { if (g_stringPool[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); g_stringPool[0] = pool; } tok = StringPool_Intern(g_stringPool[0], (void *)(text)); } StringList_AppendRetained(list, StringRef(tok)); }
#define APPENDSTRV(list, text) { char *tx = (char *)(text); APPENDSTR_42f710(list, tx) }
#define SLIST(self) ((beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)(self)->_shinkaCtrl)->_list)
#define SUB(self) ((igObjectList *)(self)->_subWindow)
#define SUBN(self) (((igObjectList *)(self)->_subWindow)->_count)
#define PLN(self) (((igIntList *)(self)->_playerNoList)->_count)
#define PL(self, i) (((int *)((igIntList *)(self)->_playerNoList)->_data)[i])
#define CNT_432d30(x) ((x)->_count)
#define REL_432d30(t) if ((t) != 0) { (t)->_refCount = (t)->_refCount - 1; if (((t)->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t); }
#define INTERN_APPEND_4332d0(lst, text) { \
    char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool[0] == 0) { \
            int pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool[0] = pool; \
        } \
        tok = StringPool_Intern(g_stringPool[0], (char *)(text)); \
    } \
    StringList_AppendRetained(lst, StringRef(tok)); }
#define REL_4332d0(o) { Rc_42bc70 *rr = (o); if (rr != 0) { *(int *)&rr->_refCount = *(int *)&rr->_refCount - 1; if (((unsigned long long)((long long)*(int *)&rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#include "dw4/igobject_release.h"
#define RELEASE(p) IG_OBJECT_RELEASE((igObject *)(p));
#define PUSH_BOOL(list, value) { int idx = (list)->_count; \
    if (idx < (list)->_capacity) { (list)->_count = idx + 1; } else { List_Resize(list, idx + 1, 1); } \
    ((unsigned char *)(list)->_data)[idx] = (value); }
#define RELEASE_436ac0(p) { if ((p) != 0) { \
        ((igObject *)(p))->_refCount = ((igObject *)(p))->_refCount - 1; \
        if (((unsigned long long) ((long long) ((igObject *)(p))->_refCount << 0x29) >> 0x29) == 0) { \
            igObject_Destroy(p); \
        } \
    } }
#define LIST(p) ((igObjectList *)(p))
#define INTERN_APPEND_43aae0(field, text) { \
    int *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool[0] == 0) { \
            int pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool[0] = pool; \
        } \
        tok = (int *)StringPool_Intern(g_stringPool[0], (int *)(text)); \
    } \
    StringList_AppendRetained(field, StringRef(tok)); }
#define RELEASE_43aae0(t) { \
    if ((t) != 0) { \
        (t)->_refCount = (t)->_refCount - 1; \
        if (((unsigned long long)((long long)(int)(t)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t); \
    } }
#define ALLOC_43aae0(al) { \
    al = ((int)igObject_GetAllocator(arg0)); \
    al = (GPR_00554c14 != 0) ? al : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])); }
#define MSG3(group, sel) { \
    beMessenger_SelectGroup(arg0->_messenger, group); \
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo); \
    beMessenger_DispatchSelected(arg0->_messenger, sel); }
#define CHIPS_PER_PAGE 12
#define LST(d) ((igObjectList *)(d)->_subWindow)

extern "C" void *FUN_003b31b0(...);
extern "C" void *FUN_003b3370(...);
extern "C" void *FUN_003b36f0(...);
extern "C" void *FUN_003b3900(...);
extern "C" void * FUN_003b3ac0(...);
extern "C" void *FUN_003b6310(...);
extern "C" void *FUN_003b6650(...);
extern "C" void *FUN_003b81d0(...);
extern "C" void *FUN_003b8400(...);
extern "C" void *FUN_003b8630(...);
extern "C" void *FUN_003b8b60(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int beNDMWWindow_BindContext(...);
extern "C" int beNDMWWindow_ClearQueuedText(...);
extern "C" int beNDMWWindow_PlayQueuedModelClose(...);
extern "C" int beNDMWWindow_PollCloseComplete(...);
extern "C" int beNDMWWindow_RequestChildrenClose(...);
extern "C" void * igObject_GetAllocator(...);
extern "C" int FUN_00100610(...);
extern "C" int FUN_002eb010(...);
extern "C" int StringPool_Construct(...);
extern "C" char * StringPool_Intern(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int beNDMWWindow_RunMessageScript(...);
extern "C" int beNDMWWindow_QueueText(...);
extern "C" void * FUN_003b4d90(...);
extern "C" void *FUN_003b4790(int);
extern "C" void * FUN_003b4f50(...);
extern "C" void *FUN_003b6940(int);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" void beMessenger_AppendBool(int, int);
extern "C" int beMessenger_GetObject(...);
extern "C" int sprintf(...);
extern "C" int igObject_IsKindOf(...);
extern "C" void *FUN_003baf10(void *);
extern "C" void *FUN_003b7520(void *);
extern "C" int FUN_00418ac0(void *, int, int);
struct igResult { int value; };
extern "C" igResult ObjectList_RemoveFirstRetained(void *, void *, int);
extern "C" int beDataBase_GetRecordInt(...);
extern "C" void * FUN_00236f80(...);
extern "C" int FUN_003b4410(...);
extern "C" int FUN_003b51b0(...);
extern "C" int beNDMWWindow_QueueNumberText(...);
extern "C" char * beDataBase_GetRecordString(...);
extern "C" int beNDMWWindow_PresentModel(...);
extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" void beMessenger_AppendVec3(int, float *);
extern "C" void FUN_0042bae0(int *arg0, int arg1);
extern "C" void * FUN_003b6bc0(...);
extern "C" void * FUN_002cb0d0(...);
extern "C" int beLua__RunNamedChunk(...);
extern "C" int List_Resize(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_SendGroup(...);
extern "C" void *FUN_003b2c00(...);
extern "C" void * FUN_003b4b10(...);
extern "C" void *FUN_003b7c00(...);
extern "C" int FUN_00425fb0(...);
extern "C" int FUN_00426530(...);
extern "C" void * FUN_003b4950(...);
extern "C" int igProperty_GetRecordArray(...);
extern "C" int beNDMWWindow_SendModelSequence(...);
extern "C" int strcmp(...);
extern "C" int beDataBase_GetRecordCount(int);
extern "C" int FUN_00443110(...);
extern "C" int beNDMWWindowSelect_CanRequestFO2TOP(...);
extern "C" void *FUN_003a9310(...);
extern "C" void *FUN_003b8860(...);
extern "C" void *FUN_003bace0(...);
extern "C" int FUN_00425e60(...);
extern "C" void * FUN_002caa70(...);
extern "C" void FUN_00433290(void *window);
extern "C" int FUN_003b45d0(...);
extern "C" int FUN_00440110(...);
extern "C" int FUN_004402e0(...);
extern "C" void *FUN_003b3f40(...);
extern "C" void *FUN_003b6e60(...);
extern "C" void *FUN_003b70e0(...);
extern "C" void FUN_00435250(int *arg0, int arg1);
extern "C" int strlen(...);
extern "C" int FUN_0030b3c0(...);
extern "C" int FUN_0030b460(...);
extern "C" int beNDMWItemBase_GetRevisionColor(...);
extern "C" int beNDMWItemRevisionPocketBase_GetPrice(...);
extern "C" char * beNDMWItemBase_GetRecordString(...);
extern "C" int beNDMWItemBase_GetRecordInt(...);
extern "C" int FUN_003c90f0(...);
extern "C" void FUN_0043a950(int *arg0, int arg1);
extern "C" int *FUN_002b90e0(...);
extern "C" int *FUN_003c87f0(...);
extern "C" int beNDMWItemAbilityChip_Set(...);
extern "C" int Gap__Bec__beNDMWShopDevice__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlSales__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlDiskSell__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlDeviceSell__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlSell__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlEditBit__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlDigilabo__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlEvolve__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlA2__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlA1__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrlA0__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopJunk__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrl50__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrl40__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrl30__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrl10__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopCtrl00__vfunc_20(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int DAT_0051b308[4];
extern "C" int DAT_0051b318[4];
extern "C" int DAT_0051b328[4];
extern "C" int DAT_0051b338[4];
extern "C" int DAT_0051b348[4];
extern "C" int DAT_0051b358[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef() : p(0) {}
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    ~StringRef() { release(); }
    void release() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    void Set(char *n) { release(); p = n; }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" StringRef StringList_CopyRetained(...);
extern "C" void Gap__Bec__beNDMWShopCtrl00__vfunc_21(beNDMWShopCtrl00 *arg0);

extern "C" int DAT_0051b220[4];
extern "C" int DAT_0051b248[4];
extern "C" int DAT_0051b398[4];
extern "C" int DAT_0051b3a0[4];
extern "C" int DAT_0051b3b0[4];
extern "C" char TEXTCTL_3[];
extern "C" char STWINFONT14[];
extern "C" int DAT_0051b3d8[4];
extern "C" int DAT_0051b3e8[4];
extern "C" int DAT_0051b3f8[4];
extern "C" char DAT_0051b400[];
extern "C" int DAT_0051b408[4];
extern "C" int DAT_0051b418[4];
extern "C" int DAT_0051b420[4];
extern "C" char DAT_0051b430[];
extern "C" char DAT_0051b438[];
extern "C" int DAT_0051b440[4];
extern "C" int DAT_0051b448[4];
extern "C" char DAT_0051b458[];
extern "C" int DAT_0051b460[4];
extern "C" char percent_d[];
extern "C" char STWINFONT29[];
extern "C" char DAT_0051b480[];
extern "C" char DAT_0051b488[];
extern "C" char DAT_0051b490[];
extern "C" int DAT_0051b498[4];
extern "C" int DAT_0051b4a0[4];
extern "C" int g_stringPool[4];
struct Tbl7 { int v[7]; };
extern "C" Tbl7 DAT_004cf950;
extern "C" Tbl7 DAT_004cf970;
extern "C" void Gap__Bec__beNDMWShopCtrl10__vfunc_21(beNDMWShopCtrl10 *self);
struct Rec;
extern "C" Rec * igProperty_GetRecord(...);
struct Fld;
extern "C" int DAT_0051b528[4];
extern "C" int DAT_0051b538[4];
extern "C" int DAT_0051b548[4];
extern "C" char DISPOFF[];
extern "C" char SWITCH_2[];
extern "C" int DAT_0051b560[4];
extern "C" int DAT_0051b568[4];
extern "C" int g_beNDMWStatusCtrlD0_metaObject[4];
struct Rec { int pad[3]; int f12; };
struct Fld { int pad[3]; igObjectList *f12; };
extern "C" void Gap__Bec__beNDMWShopCtrl30__vfunc_21(beNDMWShopCtrl30 *arg0);
struct Fld_429630;
struct P1;
extern "C" int DAT_0051b590[4];
extern "C" int DAT_0051b598[4];
extern "C" int DAT_0051b5a0[4];
extern "C" int DAT_0051b5a8[4];
extern "C" int DAT_0051b5b8[4];
extern "C" int DAT_0051b5c8[4];
extern "C" int DAT_0051b5d8[4];
extern "C" int DAT_0051b5e8[4];
extern "C" int DAT_0051b5f8[4];
extern "C" int DAT_0051b600[4];
extern "C" int DAT_0051b608[4];
extern "C" int g_beNDMWStatus_metaObject[4];
struct Rc;
struct Rc { int w0; int references; char pad[101]; char f109; char p110; char f111; };
struct Lst { int pad[2]; int cnt; int p12; int *data; };
struct Fld_429630 { int pad[3]; Lst *f12; };
struct Item { int pad[2]; int f8; int f12; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned v22(); };
struct P2 { int pad[12]; V *f48; };
struct P1 { int pad[4]; P2 *f16; };
extern "C" void Gap__Bec__beNDMWShopCtrl40__vfunc_21(beNDMWShopCtrl40 *arg0);
struct Item_42a2e0 { int p[3]; int f12; int p16; int f20; };
struct Rec_42a2e0 { int p[3]; igObjectList *f12; };
extern "C" Rec_42a2e0 * igProperty_GetRecordFolder(...);
extern "C" const char *g_fontNames[];
extern "C" int DAT_0051b610[4];
extern "C" int DAT_0051b618[4];
extern "C" int DAT_0051b620[4];
extern "C" int DAT_0051b630[4];
extern "C" int DAT_0051b640[4];
extern "C" int DAT_0051b650[4];
extern "C" int DAT_0051b660[4];
extern "C" int DAT_0051b668[4];
extern "C" char NAME_2[];
extern "C" char STWINFONT17[];
extern "C" int DAT_0051b690[4];
extern "C" int DAT_0051b698[4];
extern "C" char TXT[];
extern "C" char TEXTSET[];
extern "C" char DISPON[];
extern "C" int DAT_0051b6c0[4];
extern "C" int DAT_0051b6d0[4];
struct U { static inline char *InternStr(char *text) {
    if (text == 0) return 0;
    if (g_stringPool[0] == 0) {
        int pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
} };

extern "C" void Gap__Bec__beNDMWShopCtrl50__vfunc_21(beNDMWShopCtrl50 *self);
extern "C" const char DAT_0051b218[];
extern "C" const char DAT_0051b288[];
extern "C" int DAT_0051b6f8[4];
extern "C" void FUN_0042b880(beNDMWShopCtrl50 *owner);
extern "C" int DAT_0051b278[4];
extern "C" void FUN_0042b9d0(beNDMWShopCtrl50 *arg0);
typedef struct Tbl { const char *s[12]; } __attribute__((aligned(16))) Tbl;
extern "C" Tbl DAT_004cf990;
extern "C" char DAT_0051b7c8[];
extern "C" char DAT_0051b7d8[];
extern "C" char DAT_0051b7e0[];
typedef igObject Rc_42bc70;
struct P { int pad[3]; igIntList *f12; };
extern "C" P * FUN_003a9250(...);
extern "C" int DAT_0051b7f0[4];
extern "C" int DAT_0051b800[];
extern "C" int DAT_0051b810[4];
extern "C" int DAT_0051b820[4];
extern "C" int DAT_0051b828[4];
extern "C" int DAT_0051b838[4];
struct Tbl_42bc70 { int v[10]; };
extern "C" Tbl_42bc70 DAT_004cf9c0;
extern "C" int g_beLua_metaObject[4];
extern "C" unsigned char GPR_00554a38;
extern "C" unsigned char GPR_00554a3c;
extern "C" unsigned char GPR_00554a40;
extern "C" unsigned char GPR_00554a44;
extern "C" unsigned char GPR_00554a48;
struct Lst_42bc70 { int pad[2]; int cnt; };
extern "C" void Gap__Bec__beNDMWShopJunk__vfunc_21(beNDMWShopJunk *arg0);
typedef struct S_obj { char pad4[4]; int f4; char pad8[0x68]; igIntList *f112; } S_obj;
typedef struct S_rec { char pad12[12]; unsigned char f12; } S_rec;
extern "C" S_rec * igProperty_GetRecordByte(...);
extern "C" int DAT_0051b848[4];
extern "C" int DAT_0051b858[4];
extern "C" int DAT_0051b868[4];
extern "C" int DAT_0051b870[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beNDMWStatusTitle01_metaObject[4];
extern "C" void Gap__Bec__beNDMWShopCtrlA0__vfunc_21(beNDMWShopCtrlA0 *arg0);
extern "C" igObject *FUN_003b4250(void *);
extern "C" igObject *FUN_003b7a40(void *);
extern "C" void *DAT_004cf8a8[4];
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int DAT_0051b1c8[4];
extern "C" int DAT_0051b1d0[4];
extern "C" int DAT_0051b878[4];
extern "C" int DAT_0051b888[4];
extern "C" int DAT_0051b890[4];
extern "C" int DAT_0051b8a0[4];
extern "C" int DAT_0051b8a8[4];
extern "C" int DAT_0051b8b8[4];
extern "C" int DAT_0051b8c8[4];
extern "C" int DAT_0051b8d8[4];
extern "C" int DAT_0051b8e8[4];
extern "C" int DAT_0051b8f0[4];
extern "C" int DAT_0051b8f8[4];
extern "C" void Gap__Bec__beNDMWShopCtrlA1__vfunc_21(beNDMWShopCtrlA1 *arg0);
extern "C" int DAT_004cf9e8[4];
extern "C" int DAT_0051b908[4];
extern "C" int DAT_0051b918[4];
extern "C" int DAT_0051b920[4];
extern "C" int DAT_0051b930[4];
extern "C" int DAT_0051b938[4];
struct Str { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        ref = ((int)StringPool_Intern(g_stringPool[0], s));
    }
    return ref;
}
};
struct Arr { char p0[16]; unsigned char *f16; };
struct Rec_42df70 { char p0[12]; Arr *f12; };
extern "C" void FUN_0042df70(beNDMWShopCtrlA1 *arg0);
extern "C" int DAT_004cf9f0[4];
extern "C" int DAT_004cf9f8[4];
extern "C" int DAT_0051b948[4];
/* Stores a retained card name into slot `index` of the card-info list. */
static inline void StoreCardName(beNDMWShopCtrlA1 *self, int index, int token) {
    StringRef name(token);
    igDataList *list = (igDataList *)self->_cardInfoList;
    int count = list->_count;
    if (count != 0 && index >= 0 && index < count) {
        int *slot = &((int *)list->_data)[index];
        int text = (int)name.p;
        if (text) *(int *)(text - 4) = *(int *)(text - 4) + 1;
        RELS((char *)*slot);
        *slot = (int)name.p;
    }
}
extern "C" void FUN_0042e330(beNDMWShopCtrlA1 *arg0);
extern "C" void FUN_0042e9e0(beNDMWShopCtrlA1 *arg0);
struct Rec_42eb80 { int p[3]; igDataList *f12; };
struct FRec { int p[3]; igDataList *f12; };
struct VObj {
#define V4(a) virtual int a##0(); virtual int a##1(); virtual int a##2(); virtual int a##3();
V4(a) V4(b) V4(c) V4(d) V4(e) virtual int g0(); virtual int g1();
    virtual unsigned f24();
};
struct P3 { void *p[3]; };
extern "C" P3 DAT_004cfa00;
extern "C" P3 DAT_004cfa10;
extern "C" P3 DAT_004cfa20;
extern "C" int DAT_0051b708[4];
extern "C" int DAT_0051b718[4];
extern "C" int DAT_0051b728[4];
extern "C" int DAT_0051b738[4];
extern "C" int DAT_0051b748[4];
extern "C" int DAT_0051b758[4];
extern "C" int DAT_0051b768[4];
extern "C" int DAT_0051b778[4];
extern "C" int DAT_0051b788[4];
extern "C" int DAT_0051b9c0[4];
extern "C" int DAT_0051b9d0[4];
extern "C" int DAT_0051b9e0[4];
extern "C" int DAT_0051b9e8[4];
extern "C" int DAT_0051b9f8[];
extern "C" unsigned char GPR_00554a4c;
struct Rc_42eb80 : public igObject { };

extern "C" void Gap__Bec__beNDMWShopCtrlA2__vfunc_21(beNDMWShopCtrlA2 *arg0);
extern "C" char *g_fontName1[];
extern "C" char *DAT_004cf8d0[];
extern "C" int DAT_0051ba28[4];
extern "C" int DAT_0051ba38[4];
extern "C" int DAT_0051ba48[4];
extern "C" int DAT_0051ba60[4];
extern "C" int DAT_0051ba70[4];
extern "C" int DAT_0051ba80[4];
extern "C" int DAT_0051ba90[4];
extern "C" int DAT_0051baa0[4];
extern "C" int DAT_0051bab0[4];
extern "C" int DAT_0051bac0[4];
extern "C" int DAT_0051bad0[4];
extern "C" int DAT_0051bae8[4];
extern "C" int DAT_0051baf0[4];
extern "C" int g_beNDMWStatusSelectE1_metaObject[4];
struct DummyVirtual {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void v24(void *, void *); virtual int v25(); virtual int v26();
};
extern "C" void Gap__Bec__beNDMWShopCtrlEvolve__vfunc_21(beNDMWShopCtrlEvolve *self);
struct NamePair { int unused; char *name; };
extern "C" char DAT_0051bb20[];
extern "C" void FUN_00430d20(beNDMWShopCtrlEvolve *ctl, int sendNames, int sendStats);
extern "C" int DAT_0051bb28[4];
extern "C" int DAT_0051bb38[4];
extern "C" int DAT_0051bb48[4];
extern "C" int DAT_0051bb60[4];
extern "C" int DAT_0051bb78[4];
extern "C" int DAT_0051bb88[4];
extern "C" int DAT_0051bb90[4];
extern "C" int DAT_0051bba0[4];
extern "C" void FUN_004313b0(beNDMWShopCtrlEvolve *arg0);
extern "C" void FUN_00431670(beNDMWShopCtrlEvolve *arg0, igObjectList *arg1);
extern "C" int DAT_0051bbb0[4];
extern "C" int DAT_0051bbc0[4];
extern "C" int DAT_0051bbd0[4];
extern "C" int DAT_0051bbe8[4];
struct Rec12 { char p[12]; int f12; };
extern "C" void Gap__Bec__beNDMWShopCtrlDigilabo__vfunc_21(beNDMWShopCtrlDigilabo *self);
struct Item_4329d0 { int p[3]; int f12; };
struct RecB { int p[3]; unsigned char f12; };
struct RecI { int p[3]; int f12; };
extern "C" int DAT_0051bc40[4];
extern "C" int DAT_0051bc48[4];
extern "C" void FUN_004329d0(beNDMWShopCtrlDigilabo *self);
extern "C" void FUN_00432c90(beNDMWShopCtrlDigilabo *arg0);
extern "C" int DAT_004cfa30[4];
typedef struct { char pad[12]; int f12; } Rec2;
extern "C" int FUN_00432d30(beNDMWShopCtrlDigilabo *arg0);
extern "C" void FUN_00433120(beNDMWWindow *arg0, int arg1, int arg2);
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" int DAT_0051b1d8[4];
extern "C" int DAT_0051bc60[4];
extern "C" int DAT_0051bc70[4];
extern "C" int DAT_0051bc80[4];
extern "C" int DAT_0051bc98[4];
extern "C" int DAT_0051bca8[4];
extern "C" int DAT_0051bcb8[4];
extern "C" int DAT_0051bcc8[4];
extern "C" int DAT_0051bcd8[4];
extern "C" int DAT_0051bce8[4];
extern "C" int DAT_0051bcf8[4];
extern "C" int DAT_0051bd08[4];
extern "C" int DAT_0051bd18[4];
extern "C" void Gap__Bec__beNDMWShopCtrlEditBit__vfunc_21(beNDMWShopCtrlEditBit *self);
struct Item_434790 { int p[5]; int f20; };
extern "C" unsigned char GPR_00554a50;
extern "C" unsigned char GPR_00554a54;
extern "C" unsigned char GPR_00554a58;
extern "C" unsigned char GPR_00554a5c;
extern "C" void Gap__Bec__beNDMWShopCtrlSell__vfunc_21(beNDMWShopCtrlSell *self);
extern "C" Tbl DAT_004cfa40;
extern "C" char *DAT_004c22f0[4];
extern "C" int DAT_0051bd50[4];
extern "C" char STWINFONT30[];
extern "C" int DAT_0051bd70[];
extern "C" char DAT_0051bd78[];
extern "C" char DAT_0051bd80[];
/* matching construct: raw view of the property-record folder (list at +12). */
struct RecordFolder { int w0; int w4; int w8; igDataList *list; };
struct V3 { float x, y, z; };
extern "C" void Gap__Bec__beNDMWShopCtrlDeviceSell__vfunc_21(beNDMWShopCtrlDeviceSell *self);
extern "C" void FUN_00436060(beNDMWShopCtrlDeviceSell *self, int full, unsigned char sel);
typedef struct Obj { int pad0[4]; unsigned char flag; } Obj;
typedef struct Folder { int pad0[2]; int count; int pad1; Obj **items; } Folder;
extern "C" int FUN_004367c0(beNDMWShopCtrlDeviceSell *self);
typedef struct O_4369f0 { char p[12]; int m; } O_4369f0;
extern "C" void FUN_004369f0(O_4369f0 *arg0);
extern "C" int DAT_0051bd88[4];
extern "C" int DAT_0051bd98[4];
extern "C" int DAT_0051bda0[4];
extern "C" int DAT_0051bdb0[4];
extern "C" unsigned char GPR_00554a60;
extern "C" unsigned char GPR_00554a64;

extern "C" void Gap__Bec__beNDMWShopCtrlDiskSell__vfunc_21(beNDMWShopCtrlDiskSell *self);
extern "C" void FUN_00437ae0(beNDMWShopCtrlDiskSell *arg0, int arg1, int arg2);
extern "C" void FUN_00437f50(beNDMWShopCtrlDiskSell *arg0);
extern "C" void FUN_00438050(beNDMWShopCtrlDiskSell *arg0);
struct ChipPriceText { char text[5]; } __attribute__((aligned(16)));
extern "C" ChipPriceText DAT_0051bdc0;
struct Vec3 { float x, y, z; } __attribute__((aligned(16)));
struct Pool { static char *Intern(char *s) { if (g_stringPool[0] == 0) { int v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); g_stringPool[0] = v; } return StringPool_Intern(g_stringPool[0], s); } };
extern "C" void FUN_004393e0(beNDMWShopCtrlSales *arg0, int arg1, unsigned char arg2);
extern "C" unsigned char GPR_00554a68;
extern "C" unsigned char GPR_00554a6c;
extern "C" unsigned char GPR_00554a70;
extern "C" int FUN_00439aa0(beNDMWShopCtrlSales *self);
extern "C" int DAT_0051bdc8[4];
extern "C" int DAT_0051bdd0[4];
extern "C" int DAT_0051bdd8[4];
extern "C" int DAT_0051bde8[4];
struct Rec_439d60 { char pad[12]; int f12; };
/* matching construct: the retail bool result (daddiu) comes from an inline member function with early returns */
struct SalesChk {
    static bool Chk(beNDMWShopCtrlSales *self, beNDMWItemBase *arg1, int obj) {
        int rec;
        int s3, s0;
        igIntList *l;
        int a, b;
        if (arg1 == 0) return false;
        if (arg1->_kindNo == 3) return true;
        rec = ((int)FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]));
        if (arg1->_kindNo == 0) {
            int sh = ((Rec_439d60 *)((void *)igProperty_GetRecord(obj, &DAT_0051bac0[0])))->f12;
            s3 = (1 << sh) & beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bdc8[0]);
            l = (igIntList *)((Rec_439d60 *)((void *)FUN_003a9250(obj, &DAT_0051bdd0[0])))->f12;
            a = beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bdd0[0]);
            b = beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bdd8[0]);
            if (s3 != 0 && ((int *)l->_data)[a] >= b) return true;
            return false;
        } else if (arg1->_kindNo == 1 || arg1->_kindNo == 2) {
            s0 = ((Rec_439d60 *)((void *)igProperty_GetRecord(obj, &DAT_0051b5a0[0])))->f12;
            if (s0 >= beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bde8[0])) return true;
            return false;
        }
        return false;
    }
};
extern "C" bool FUN_00439d60(beNDMWShopCtrlSales *arg0, beNDMWItemBase *arg1);
extern "C" int DAT_0051bdf0[4];
extern "C" int DAT_0051be00[4];
/* matching construct: allocator pick kept as an in-class method so it inlines as in the retail unit */
struct ShopAlloc {
    static int Pool(beNDMWShopCtrlSales *self) { int a = ((int)igObject_GetAllocator(self)); if (GPR_00554c14 != 0) return a; return ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])); }
};
extern "C" void FUN_00439f30(beNDMWShopCtrlSales *arg0, int arg1);
struct RC { int p0; unsigned refs; char p8[8]; char f16; };
typedef igObjectList OL;
extern "C" void FUN_0043a450(void *arg0, OL *arg1, OL *arg2, OL *arg3, OL *arg4);
extern "C" void FUN_0043a660(void *arg0, igDataList *arg1, igDataList *arg2, igDataList *arg3, igDataList *arg4);
extern "C" Tbl DAT_004cfa70;
extern "C" int *DAT_004cf8ac[4];
extern "C" int DAT_004cfaa0[8];
extern "C" int DAT_0051be10[4];
extern "C" int DAT_0051be20[4];
extern "C" char NEXTX[];
extern "C" int DAT_0051be40[4];
extern "C" int DAT_0051be50[4];
extern "C" int DAT_0051be58[4];
extern "C" int DAT_0051be68[4];
extern "C" int DAT_0051be78[4];
extern "C" int DAT_0051be88[4];
extern "C" int DAT_0051be90[4];
extern "C" int DAT_0051be98[4];
struct ChipVT {
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
    virtual void v22(int *, int *);
    virtual int v23();
    virtual int v24();
};
typedef struct ChipRecord {
    char p[12];
    int f12;
} ChipRecord;
struct ChipUtil { static inline bool IsChip(beNDMWItemBase *e) { if (e != 0) { return e->_kindNo == 3; } return false; } static inline int *CastSel(int *p) { if (p != 0 && igObject_IsKindOf(p, g_beNDMWStatusSelectE1_metaObject[0]) != 0) return p; return 0; } };
extern "C" void Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_21(beNDMWShopCtrlXdataChip *arg0);
extern "C" int beNDMWShopCtrlXdataChip_UpdatePageCount(beNDMWShopCtrlXdataChip *self);
extern "C" char *g_fontName1[];
extern "C" char DISPON[];
extern "C" int g_beNDMWStatus_metaObject[];
extern "C" void beNDMWShopCtrlXdataChip_RefreshText(beNDMWShopCtrlXdataChip *self, long long refreshRows, long long refreshDescription);
extern "C" igObject * FUN_003b7360(...);
typedef beNDMWShopDevice S;
extern "C" void Gap__Bec__beNDMWShopDevice__vfunc_21(S *arg0);
extern "C" int g_beNDMWShopDevice_metaObject[4];
extern "C" int g_beNDMWShopCtrlXdataChip_metaObject[4];
extern "C" int g_beNDMWShopCtrlSales_metaObject[4];
extern "C" int g_beNDMWShopCtrlDiskSell_metaObject[4];
extern "C" int g_beNDMWShopCtrlDeviceSell_metaObject[4];
extern "C" int g_beNDMWShopCtrlSell_metaObject[4];
extern "C" int g_beNDMWShopCtrlEditBit_metaObject[4];
extern "C" int g_beNDMWShopCtrlDigilabo_metaObject[4];
extern "C" int g_beNDMWShopCtrlEvolve_metaObject[4];
extern "C" int g_beNDMWShopCtrlA2_metaObject[4];
extern "C" int g_beNDMWShopCtrlA1_metaObject[4];
extern "C" int g_beNDMWShopCtrlA0_metaObject[4];
extern "C" int g_beNDMWShopJunk_metaObject[4];
extern "C" int g_beNDMWShopCtrl50_metaObject[4];
extern "C" int g_beNDMWShopCtrl40_metaObject[4];
extern "C" int g_beNDMWShopCtrl30_metaObject[4];
extern "C" int g_beNDMWShopCtrl10_metaObject[4];
extern "C" int g_beNDMWShopCtrl00_metaObject[4];

void Gap__Bec__beNDMWShopCtrl00__vfunc_21(beNDMWShopCtrl00 *arg0) {
    S_ref *t;
    int x;

    switch (arg0->_st0) {
    case 0:
        x = ((int)igObject_GetAllocator(arg0));
        { igSmartPointer<beNDMWShopTitle00> r1((beNDMWShopTitle00 *)FUN_003b3370(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
        beNDMWWindow_BindContext(r1.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r1.p);
        }
        x = ((int)igObject_GetAllocator(arg0));
        { igSmartPointer<beNDMWStatusTitle01> r2((beNDMWStatusTitle01 *)FUN_003b3ac0(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
        beNDMWWindow_BindContext(r2.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r2.p);
        }
        x = ((int)igObject_GetAllocator(arg0));
        { igSmartPointer<beNDMWStatusTitle02> r3((beNDMWStatusTitle02 *)FUN_003b3900(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
        beNDMWWindow_BindContext(r3.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r3.p);
        }
        x = ((int)igObject_GetAllocator(arg0));
        { igSmartPointer<beNDMWStatusTitle03> r4((beNDMWStatusTitle03 *)FUN_003b36f0(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
        beNDMWWindow_BindContext(r4.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        ObjectList_AppendRetained(arg0->_subWindow, r4.p);
        }
        x = ((int)igObject_GetAllocator(arg0));
        { igSmartPointer<beNDMWShopTitle01> r5((beNDMWShopTitle01 *)FUN_003b31b0(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
        beNDMWWindow_BindContext(r5.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
        ObjectList_AppendRetained(arg0->_subWindow, r5.p);
        }
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 1:
        switch (arg0->_st1) {
        case 0:
            beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051b328[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b338[0]);
            if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                return;
            } else {
                {
                igSmartPointer<beNDMWWindow> r6(0);
                switch (arg0->_entCode) {
                case 1:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b8b60(x);
                    break;
                case 3:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b8630(x);
                    break;
                case 4:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b8400(x);
                    break;
                case 5:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b81d0(x);
                    break;
                case 6:
                case 7:
                case 8:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b6650(x);
                    break;
                case 9:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b6310(x);
                    break;
                default:
                x = ((int)igObject_GetAllocator(arg0));
                x = GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                t = (S_ref *)r6.p;
                if (t != 0) {
                    t->f4 = (int)((int)(t->f4 - 1));
                    if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(t);
                    }
                }
                r6.p = (beNDMWWindow *)FUN_003b8b60(x);
                    break;
                }
                beNDMWWindow_BindContext(r6.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
                ObjectList_AppendRetained(arg0->_subWindow, r6.p);
                }
                arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                arg0->_st1 = arg0->_st1 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
            }
        case 1:
            if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                arg0->_st0 = arg0->_st0 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beMessenger_SendNamed(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b348[0], 0, &DAT_0051b358[0]);
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}



static inline int st0(const beNDMWShopCtrl10 *self) { return self->_st0; }

void Gap__Bec__beNDMWShopCtrl10__vfunc_21(beNDMWShopCtrl10 *self)
{
    Tbl7 names;
    char buf[128];
    Tbl7 arr2;
    switch (self->_st0) {
    default:
        return;
    case 0:
        self->_st0 = st0(self) + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                {
                NEWWIN(beNDMWShopSelect01, w364, FUN_003b4d90, 1150)
                ((beNDMWShopSelect01 *)w364.p)->_startPoint = self->_xdataMenu;
                }
                self->_nowProcKazu = CNT;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (CNT != self->_nowProcKazu) {
                    self->_parameter = 0;
                    switch (self->_retCode) {
                    case 0:
                        self->_xdataMenu = 0;
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 1:
                        self->_xdataMenu = 1;
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 2:
                    default:
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_AppendBool(self->_messenger, 0);
                beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3a0));
                {
                NEWWIN(beNDMWShopSelect11, w360, FUN_003b4790, self->_parameter)
                }
                self->_nowProcKazu = CNT;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_parameter;
                return;
            case 1:
                if (CNT == self->_nowProcKazu) {
                    int rc = self->_retCode;
                    if (rc != -1 && rc != self->_st3) {
                        beNDMWWindow_RunMessageScript(self, ((char *)DAT_0051b3b0), rc + 1154);
                        self->_st3 = self->_retCode;
                    }
                    break;
                } else {
                    int obj;
                    int limit;
                    int need;
                    int have;
                    int money;
                    char *key;
                    int i;
                    int *np;
                    int *q;
                    names = DAT_004cf950;
                    np = names.v;
                    i = 0;
                    q = np;
                    for (; i < 7; i++) {
                        beMessenger_SelectGroup(self->_messenger, ((char *)TEXTCTL_3));
                        beMessenger_AppendString(self->_messenger, ((char *)STWINFONT14));
                        beMessenger_AppendString(self->_messenger, (void *)*q);
                        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3d8));
                        q++;
                    }
                    beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3e8));
                    obj = beMessenger_GetObject(self->_messenger, 0);
                    limit = 9999;
                    switch (self->_retCode) {
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 0: key = ((char *)DAT_0051b3f8); break;
                    case 1: key = DAT_0051b400; break;
                    case 2: key = ((char *)DAT_0051b408); break;
                    case 3: key = ((char *)DAT_0051b418); break;
                    case 4: key = ((char *)DAT_0051b420); break;
                    case 5: key = DAT_0051b430; limit = 99999; break;
                    case 6: key = DAT_0051b438; limit = 99999; break;
                    }
                    money = *(int *)(((int)igProperty_GetRecord(obj, key)) + 12);
                    CEILD(need, money)
                    need = need > 400 ? 400 : (need < 0 ? 1 : need);
                    self->_parameter = self->_retCode;
                    {
                    NEWWIN(beNDMWShopSelect00, w356, FUN_003b4f50, 0)
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    have = *(int *)(((int)igProperty_GetRecord(obj, ((char *)DAT_0051b440))) + 12);
                    if (money >= limit) {
                        ((beNDMWWindow *)w356.p)->_entCode = 1162;
                        self->_st3 = 0;
                    } else if (have < need) {
                        ((beNDMWWindow *)w356.p)->_entCode = 1161;
                        self->_st3 = 0;
                    } else {
                        int j;
                        beNDMWWindow_QueueText(w356.p, ((char *)DAT_0051b448), ((char *)DAT_0051b220), DAT_0051b458, ((char *)DAT_0051b460));
                        sprintf(buf, ((char *)percent_d), have - need);
                        beNDMWWindow_QueueText(w356.p, ((char *)DAT_0051b448), ((char *)DAT_0051b248), buf, ((char *)DAT_0051b460));
                        for (j = 0; j < 4; j++) {
                            APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, ((char *)DAT_0051b448))
                            { int *t = (int *)*np; APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, t) }
                            np++;
                        }
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, ((char *)DAT_0051b448))
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, ((char *)DAT_0051b220))
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, ((char *)DAT_0051b448))
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, ((char *)DAT_0051b248))
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, ((char *)STWINFONT29))
                        { int *t = (int *)names.v[2]; APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, t) }
                        arr2 = DAT_004cf970;
                        ((beNDMWWindow *)w356.p)->_entCode = arr2.v[self->_retCode];
                        self->_st3 = 1;
                    }
                    }
                    self->_nowProcKazu = CNT;
                    return;
                }
                break;
            case 2:
                if (CNT != self->_nowProcKazu) {
switch (self->_st3) { case 0: default: { self->_st1 = 1; self->_st3 = 0; self->_st2 = 0; return; } case 1: break; }
                    {
                    NEWWIN(beNDMWShopSelect01, w352, FUN_003b4d90, 1163)
                    }
                    self->_nowProcKazu = CNT;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 3:
                if (CNT != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0: {
                        int obj;
                        char *key;
                        int need;
                        int have;
                        igIntList *lst;
                        beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3e8));
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        switch (self->_parameter) {
                        case 0: key = ((char *)DAT_0051b3f8); break;
                        case 1: key = DAT_0051b400; break;
                        case 2: key = ((char *)DAT_0051b408); break;
                        case 3: key = ((char *)DAT_0051b418); break;
                        case 4: key = ((char *)DAT_0051b420); break;
                        case 5: key = DAT_0051b430; break;
                        case 6: key = DAT_0051b438; break;
                        }
                        CEILD(need, *(int *)(((int)igProperty_GetRecord(obj, key)) + 12))
                        need = need > 400 ? 400 : (need < 0 ? 1 : need);
                        have = *(int *)(((int)igProperty_GetRecord(obj, ((char *)DAT_0051b440))) + 12);
                        { int rec = ((int)igProperty_GetRecord(obj, ((char *)DAT_0051b440))); *(int *)(rec + 12) = have - need; }
                        lst = (igIntList *)*(int *)(((int)FUN_003a9250(obj, DAT_0051b480)) + 12);
                        switch (self->_parameter) {
                        case 0: INC(lst, 2) break;
                        case 1: INC(lst, 3) break;
                        case 2: INC(lst, 4) break;
                        case 3: INC(lst, 5) break;
                        case 4: INC(lst, 6) break;
                        case 5: INC(lst, 0) break;
                        case 6: INC(lst, 1) break;
                        }
                        beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3a0));
                        beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3e8));
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        {
                            int a = *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b430)) + 12);
                            *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b488)) + 12) = a;
                            a = *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b438)) + 12);
                            *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b490)) + 12) = a;
                        }
                        beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b498));
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b4a0));
                        {
                        NEWWIN(beNDMWShopSelect00, w348, FUN_003b4f50, 1165)
                        }
                        self->_nowProcKazu = CNT;
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        return;
                    }
                    case 1:
                    default:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            case 4:
                if (CNT != self->_nowProcKazu) {
                    {
                    NEWWIN(beNDMWShopSelect01, w344, FUN_003b4d90, 1166)
                    }
                    self->_nowProcKazu = CNT;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 5:
                if (CNT != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 1:
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3a0));
                {
                NEWWIN(beNDMWShopCtrlXdataChip, w340, FUN_003b6940, 0)
                }
                self->_nowProcKazu = CNT;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (CNT != self->_nowProcKazu) {
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st3 = 1;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2: {
        int obj;
        int a;
        beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3a0));
        beMessenger_SelectGroup(self->_messenger, ((char *)DAT_0051b398));
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, ((char *)DAT_0051b3e8));
        obj = beMessenger_GetObject(self->_messenger, 0);
        a = *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b430)) + 12);
        *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b488)) + 12) = a;
        a = *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b438)) + 12);
        *(int *)(((int)igProperty_GetRecord(obj, DAT_0051b490)) + 12) = a;
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    }
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}




static inline int st0_428790(const beNDMWShopCtrl30 *ctrl) { return ctrl->_st0; }

void Gap__Bec__beNDMWShopCtrl30__vfunc_21(beNDMWShopCtrl30 *arg0) {
    void *alloc;
    beNDMWStatusCtrlD0 *wa; int ia;
    beNDMWStatusCtrlD0 *wb; int ib;
    beNDMWStatusCtrlD0 *wc; int ic;
    int amt;
    void *pl;
    int x;
    int y;
    switch (arg0->_st0) {
    case 0:
        arg0->_st0 = st0_428790(arg0) + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect01> win((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x546);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win.p);
                ((beNDMWShopSelect01 *)win.p)->_startPoint = arg0->_bankMenu;
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                    case 1:
                        arg0->_bankMenu = arg0->_retCode;
                        arg0->_st1 = 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 2:
                    default:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect01> win((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x54B);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0: {
                        void *pl;
                        igObjectList *l;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        pl = ((void *)beMessenger_GetObject(arg0->_messenger, 0));
                        igProperty_GetRecordFolder(pl, &DAT_0051b528[0]);
                        l = ((Fld *)igProperty_GetRecordFolder(pl, &DAT_0051b538[0]))->f12;
                        if (arg0->_bankMenu == 0) {
                            arg0->_st1 = 2;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        }
                        if (l->_count <= 0) {
                            arg0->_st1 = 6;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            arg0->_st3 = 0x55E;
                            return;
                        }
                        arg0->_st1 = 3;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                    case 1:
                        if (arg0->_bankMenu == 0) {
                            arg0->_st1 = 4;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        }
                        arg0->_st1 = 5;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
        case 3:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWStatusCtrlD0> win((beNDMWStatusCtrlD0 *)FUN_003baf10(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win.p);
                ((beNDMWStatusCtrlD0 *)win.p)->_isAutoClose = 0;
                ((beNDMWStatusCtrlD0 *)win.p)->_isEquipDisable = 1;
                if (arg0->_st1 == 3) ((beNDMWStatusCtrlD0 *)win.p)->_isBankFolder = 1;
                }
                switch (arg0->_st1) {
                case 2:
                    beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x54D);
                    break;
                case 3:
                    beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x554);
                    break;
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                FINDWIN(wa, ia)
                if (wa != 0) {
                    if (arg0->_retCode == -1) {
                        wa->_st0 = wa->_st0 + 1;
                        wa->_st3 = 0;
                        wa->_st2 = 0;
                        wa->_st1 = 0;
                        arg0->_st2 = 5;
                        arg0->_st3 = 0;
                        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(arg0->_messenger, STWINFONT29);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                        beMessenger_AppendString(arg0->_messenger, DISPOFF);
                        beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                        return;
                    }
                    if (wa->_st0 == 1 && wa->_st1 == 2) {
                        void *pl;
                        igObjectList *la;
                        igObjectList *lb;
                        beNDMWItemBase *it;
                        int sw, rc;
                        Fld *fb;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        pl = ((void *)beMessenger_GetObject(arg0->_messenger, 0));
                        la = ((Fld *)igProperty_GetRecordFolder(pl, &DAT_0051b528[0]))->f12;
                        fb = ((Fld *)igProperty_GetRecordFolder(pl, &DAT_0051b538[0]));
                        sw = arg0->_st1;
                        lb = fb->f12;
                        rc = arg0->_retCode;
                        switch (sw) {
                        case 2:
                            it = (beNDMWItemBase *)((int *)la->_data)[rc];
                            if (lb->_count >= 0x60) {
                                arg0->_st2 = 2;
                                arg0->_st3 = 0;
                                arg0->_st3 = 0x54E;
                                return;
                            }
                            if (it->_isEquip == 0) {
                                ObjectList_AppendRetained(lb, it);
                                ObjectList_RemoveFirstRetained(la, it, 0);
                            }
                            wa->_st2 = 1;
                            wa->_st3 = 0;
                            return;
                        case 3:
                            it = (beNDMWItemBase *)((int *)lb->_data)[rc];
                            if (la->_count >= 0x24) {
                                arg0->_st2 = 2;
                                arg0->_st3 = 0;
                                arg0->_st3 = 0x555;
                                return;
                            }
                            ObjectList_AppendRetained(la, it);
                            ObjectList_RemoveFirstRetained(lb, it, 0);
                            if (lb->_count <= 0) {
                                arg0->_st2 = 2;
                                arg0->_st3 = 0;
                                arg0->_st3 = 0x55E;
                                FUN_00418ac0(wa, 1, 0);
                                return;
                            }
                            wa->_st2 = 1;
                            wa->_st3 = 0;
                            return;
                        }
                    }
                }
                break;
            case 2:
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, STWINFONT29);
                beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                beMessenger_AppendString(arg0->_messenger, DISPOFF);
                beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 3:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    FINDWINV(wb, ib)
                    if (wb != 0) {
                        wb->_st0 = wb->_st0 + 1;
                        wb->_st3 = 0;
                        wb->_st2 = 0;
                        wb->_st1 = 0;
                        arg0->_st2 = 5;
                        arg0->_st3 = 0;
                        return;
                    }
                }
                break;
            case 5:
                FINDWIN(wc, ic)
                if (wc == 0) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 4:
        case 5:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopCtrlEditBit> win((beNDMWShopCtrlEditBit *)FUN_003b7520(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_bankMenu);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    if (arg0->_retCode != -1) {
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        pl = ((void *)beMessenger_GetObject(arg0->_messenger, 0));
                        amt = arg0->_retCode;
                        if (arg0->_bankMenu == 0) {
                            x = igProperty_GetRecord(pl, &DAT_0051b560[0])->f12;
                            y = igProperty_GetRecord(pl, &DAT_0051b568[0])->f12;
                            x = x - amt;
                            y = y + amt;
                            igProperty_GetRecord(pl, &DAT_0051b560[0])->f12 = x;
                            igProperty_GetRecord(pl, &DAT_0051b568[0])->f12 = y;
                        } else {
                            x = igProperty_GetRecord(pl, &DAT_0051b560[0])->f12;
                            y = igProperty_GetRecord(pl, &DAT_0051b568[0])->f12;
                            x = x + amt;
                            y = y - amt;
                            igProperty_GetRecord(pl, &DAT_0051b560[0])->f12 = x;
                            igProperty_GetRecord(pl, &DAT_0051b568[0])->f12 = y;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b4a0[0]);
                    }
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 6:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}

void Gap__Bec__beNDMWShopCtrl40__vfunc_21(beNDMWShopCtrl40 *arg0) {
    void *alloc;
    beNDMWWindow *wa;
    int ia;
    beNDMWWindow *wb;
    int ib;
    beNDMWWindow *wc;
    int ic;
    switch (arg0->_st0) {
    case 0:
        beNDMWWindow_QueueText(arg0, STWINFONT29, &DAT_0051b548[0], &DAT_0051b590[0], &DAT_0051b598[0]);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                    igSmartPointer<beNDMWStatusCtrlD0> spBC((beNDMWStatusCtrlD0 *)FUN_003baf10(alloc));
                    beNDMWWindow_BindContext(spBC.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                    ObjectList_AppendRetained((void *)arg0->_subWindow, spBC.p);
                    ((Rc *)spBC.p)->f111 = 0;
                    ((Rc *)spBC.p)->f109 = 1;
                }
                beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x5AA);
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                FINDWIN_429630(wa, ia)
                if (wa != 0) {
                    if (arg0->_retCode == -1) {
                        arg0->_st1 = 3;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                    if (wa->_st0 == 1 && wa->_st1 == 2) {
                        arg0->_selectCursor = arg0->_retCode;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        if (igProperty_GetRecord(((void *)beMessenger_GetObject(arg0->_messenger, 0)), &DAT_0051b560[0])->f12 < 300) {
                            arg0->_st1 = 2;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                        } else {
                            arg0->_st1 = 1;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(arg0->_messenger, STWINFONT29);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                        beMessenger_AppendString(arg0->_messenger, DISPOFF);
                        beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                    igSmartPointer<beNDMWShopSelect00> spB8((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                    beNDMWWindow_BindContext(spB8.p, arg0, arg0->_insight, arg0->_playerNo, 0x5AC);
                    ObjectList_AppendRetained((void *)arg0->_subWindow, spB8.p);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    alloc = igObject_GetAllocator(arg0);
                    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    {
                        igSmartPointer<beNDMWShopSelect01> spB4((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                        beNDMWWindow_BindContext(spB4.p, arg0, arg0->_insight, arg0->_playerNo, 0x5AD);
                        ObjectList_AppendRetained((void *)arg0->_subWindow, spB4.p);
                    }
                    arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                    arg0->_st2 = arg0->_st2 + 1;
                    arg0->_st3 = 0;
            case 2:
                    if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                        if (arg0->_retCode == 0) {
                            int base;
                            void *db;
                            int lvl;
                            int lim;
                            int tier;
                            int sum;
                            int cnt;
                            int j;
                            void *pl;
                            Item *it;
                            int id;
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                            pl = ((void *)beMessenger_GetObject(arg0->_messenger, 0));
                            { int cur = igProperty_GetRecord(pl, &DAT_0051b560[0])->f12;
                              Rec *r = igProperty_GetRecord(pl, &DAT_0051b560[0]);
                              r->f12 = cur - 300; }
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b4a0[0]);
                            it = (Item *)((Fld_429630 *)igProperty_GetRecordFolder(pl, &DAT_0051b528[0]))->f12->data[arg0->_selectCursor];
                            lvl = igProperty_GetRecord(pl, &DAT_0051b5a0[0])->f12;
                            if (lvl < 0x29) tier = 1;
                            else if (lvl < 0x65) tier = 2;
                            else if (lvl < 0xC9) tier = 3;
                            else if (lvl < 0x12D) tier = 4;
                            else if (lvl < 0x191) tier = 5;
                            else tier = 6;
                            StringRef spB0(0);
                            if (it->f8 == 0) {
                                if (g_stringPool[0] == 0) {
                                    void *o = ((void *)FUN_002eb010(0x10));
                                    if (o != 0) o = ((void *)StringPool_Construct(o));
                                    g_stringPool[0] = (int)o;
                                }
                                { char *ns = StringPool_Intern((void *)g_stringPool[0], &DAT_0051b5a8[0]);
                                  { char *os = spB0.p; RELS(os) }
                                  spB0.p = ns; }
                            } else if (it->f8 == 1) {
                                if (g_stringPool[0] == 0) {
                                    void *o = ((void *)FUN_002eb010(0x10));
                                    if (o != 0) o = ((void *)StringPool_Construct(o));
                                    g_stringPool[0] = (int)o;
                                }
                                { char *ns = StringPool_Intern((void *)g_stringPool[0], &DAT_0051b5b8[0]);
                                  { char *os = spB0.p; RELS(os) }
                                  spB0.p = ns; }
                            } else if (it->f8 == 2) {
                                if (g_stringPool[0] == 0) {
                                    void *o = ((void *)FUN_002eb010(0x10));
                                    if (o != 0) o = ((void *)StringPool_Construct(o));
                                    g_stringPool[0] = (int)o;
                                }
                                { char *ns = StringPool_Intern((void *)g_stringPool[0], &DAT_0051b5c8[0]);
                                  { char *os = spB0.p; RELS(os) }
                                  spB0.p = ns; }
                            }
                            beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], spB0.p, 0, &DAT_0051b5e8[0]);
                            db = ((void *)beMessenger_GetObject(arg0->_messenger, 0));
                            base = tier * 100;
                            cnt = beDataBase_GetRecordInt(db, base, &DAT_0051b5f8[0]);
                            lim = (int)(((P1 *)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0]))->f16->f48->v22() % 10000U);
                            sum = 0;
                            j = 1;
                            if (cnt > 0) {
                                do {
                                    id = base + j;
                                    sum += beDataBase_GetRecordInt(db, id, &DAT_0051b600[0]);
                                    if (sum >= lim) {
                                        int v = beDataBase_GetRecordInt(db, id, &DAT_0051b5f8[0]);
                                        beDataBase_GetRecordInt(db, id, &DAT_0051b608[0]);
                                        it->f12 = v;
                                        break;
                                    }
                                    j++;
                                } while (cnt >= j);
                            }
                        }
                        arg0->_retCode = arg0->_selectCursor;
                        FINDWIN_429630(wb, ib)
                        if (wb != 0) {
                            arg0->_st1 = 0;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            arg0->_st2 = 1;
                            arg0->_st3 = 0;
                            wb->_st2 = 1;
                            wb->_st3 = 0;
                            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                            beMessenger_AppendString(arg0->_messenger, STWINFONT29);
                            beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                            beMessenger_AppendString(arg0->_messenger, DISPOFF);
                            beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                            return;
                        }
                    }
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                    igSmartPointer<beNDMWShopSelect00> spAC((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                    beNDMWWindow_BindContext(spAC.p, arg0, arg0->_insight, arg0->_playerNo, 0x5AB);
                    ObjectList_AppendRetained((void *)arg0->_subWindow, spAC.p);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    arg0->_st1 = 3;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            FINDWIN_429630(wc, ic)
            switch (arg0->_st2) {
            case 0:
                if (wc != 0) {
                    wc->_st0 = 2;
                    wc->_st3 = 0;
                    wc->_st2 = 0;
                    wc->_st1 = 0;
                }
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                if (wc == 0) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}

static inline int f20Of(const Item_42a2e0 *item) { return item->f20; }

void Gap__Bec__beNDMWShopCtrl50__vfunc_21(beNDMWShopCtrl50 *self) {
    int vA[3];
    int vB[3];
    const igObjectList *fa;
    void *alloc;
    int obj;
    int i;
    int cost0;
    int cost2;
    int objm;
    int found;
    int j;
    int money;
    int rec2;
    const igObjectList *fb;
    int jb;
    Item_42a2e0 *it;
    Item_42a2e0 *ib;
    char **fp;
    igStringRefList *la;
    igStringRefList *lb;

    switch (self->_st0) {
    case 0:
        beNDMWWindow_PlayQueuedModelClose(self);
        la = (igStringRefList *)self->_modelCloseInfoNameList;
        CLEAR1(la, 0)
        la->_count = 0;
        ((igIntList *)self->_modelCloseRamNoList)->_count = 0;
        lb = (igStringRefList *)self->_modelCloseSeqNameList;
        CLEAR_LIST(lb, 0)
        lb->_count = 0;
        beNDMWWindow_ClearQueuedText(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            default:
                return;
            case 0:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect01> spCC((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(spCC.p, self, self->_insight, self->_playerNo, 0x60E);
                ObjectList_AppendRetained(self->_subWindow, spCC.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_cursor = 0;
                        return;
                    case 1:
                        self->_st1 = 4;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 2: default:
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051b618[0], &DAT_0051b620[0]);
                vA[0] = 0xC3120000;
                vA[1] = 0x41C80000;
                vA[2] = 0;
                beNDMWWindow_PresentModel(self, &DAT_0051b630[0], 0, &DAT_0051b640[0], &DAT_0051b620[0], &vA[0]);
                vB[0] = 0x436C0000;
                vB[1] = 0x41C80000;
                vB[2] = 0;
                beNDMWWindow_PresentModel(self, &DAT_0051b650[0], 0, &DAT_0051b640[0], &DAT_0051b620[0], &vB[0]);
                beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
                obj = beMessenger_GetObject(self->_messenger, 0);
                INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b668[0])
                INTERN_APPEND(self->_textCloseNameList, ((char * *)g_fontNames)[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x5DD);
                i = 0;
                fp = &((char * *)g_fontNames)[0];
                do {
                    beNDMWWindow_QueueText(self, STWINFONT14, *fp, beDataBase_GetRecordString(obj, i, NAME_2), &DAT_0051b598[0]);
                    beNDMWWindow_QueueNumberText(self, STWINFONT17, *fp, beDataBase_GetRecordInt(obj, i, &DAT_0051b690[0]), &DAT_0051b460[0]);
                    i += 1;
                    fp += 1;
                } while (i < 10);
                beNDMWWindow_QueueText(self, STWINFONT29, ((char * *)g_fontNames)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                FUN_0042bae0((int *)self, -1);
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051b698[0]);
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWStatusSelectE1> spC8((beNDMWStatusSelectE1 *)FUN_003b51b0(alloc));
                beNDMWWindow_BindContext(spC8.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, spC8.p);
                { beNDMWWindowSelect *w = (beNDMWWindowSelect *)spC8.p; w->_offsetPos[0] = -121.0f; w->_offsetPos[1] = 128.0f; w->_offsetPos[2] = 0.0f; }
                ((beNDMWWindowSelect *)spC8.p)->_startPoint = self->_cursor;
                ((beNDMWWindowSelect *)spC8.p)->_selectMax = 10;
                INTERN_APPEND(((beNDMWWindow *)spC8.p)->_textCloseTypeList, STWINFONT29)
                INTERN_APPEND(((beNDMWWindow *)spC8.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(spC8.p, &DAT_0051b3b0[0], 0x611);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_retCode = self->_cursor;
            case 2:
                if (self->_retCode != -1) {
                    beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
                    obj = beMessenger_GetObject(self->_messenger, 0);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
                    { int ms = self->_messenger; beMessenger_AppendString(ms, beDataBase_GetRecordString(obj, self->_retCode, TXT)); }
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
                    beMessenger_AppendString(self->_messenger, &((int *)DISPON)[0]);
                    beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                }
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_retCode;
            case 3:
                if (SUBCNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_retCode != self->_st3) {
                            self->_st2 = 2;
                            self->_st3 = 0;
                            return;
                        }
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_cursor = self->_retCode;
                        FUN_0042bae0((int *)self, self->_cursor);
                        self->_conItemNo = self->_retCode;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        fa = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12;
                        found = 0;
                        j = 0;
                        if (0 < VCNT(fa)) {
                            do {
                                it = ((Item_42a2e0 **)fa->_data)[j];
                                if (it != 0 && self->_conItemNo == it->f12) {
                                    found = it->f20;
                                    break;
                                }
                                j += 1;
                            } while (j < VCNT(fa));
                        }
                        if (found == 9) {
                            self->_st1 = 5;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            self->_st3 = 0x623;
                            return;
                        }
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_diskCnt = found;
                        return;
                    }
                    self->_st0 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051b6d0[0]);
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect52> spC4((beNDMWShopSelect52 *)FUN_003b4410(alloc));
                beNDMWWindow_BindContext(spC4.p, self, self->_insight, self->_playerNo, 9 - self->_diskCnt);
                ObjectList_AppendRetained(self->_subWindow, spC4.p);
                { beNDMWWindowSelect *w = (beNDMWWindowSelect *)spC4.p; w->_offsetPos[0] = 52.0f; w->_offsetPos[1] = -69.0f; w->_offsetPos[2] = 0.0f; }
                INTERN_APPEND(((beNDMWWindow *)spC4.p)->_textCloseTypeList, STWINFONT29)
                INTERN_APPEND(((beNDMWWindow *)spC4.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x624);
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x5DE);
                self->_retCode = 8 - self->_diskCnt;
                FUN_0042b880(self);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            FUN_0042b880(self);
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    switch (self->_retCode) {
                    default:
                        self->_st1 = 3;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st3 = (9 - self->_diskCnt) - self->_retCode;
                        return;
                    case -1:
                    FUN_0042b9d0(self);
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st2 = 1;
                    self->_st3 = 0;
                    }
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
                self->_tanka = beDataBase_GetRecordInt(beMessenger_GetObject(self->_messenger, 0), self->_conItemNo, &DAT_0051b690[0]);
                self->_kazu = self->_st3;
                cost0 = self->_tanka * self->_kazu;
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                if (cost0 <= W(((int)igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b560[0])), 12)) {
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                self->_st1 = 5;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st3 = 0x622;
                return;
            case 1:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> spC0((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(spC0.p, self, self->_insight, self->_playerNo, 0x613);
                ObjectList_AppendRetained(self->_subWindow, spC0.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 2:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    ALLOC(alloc, self)
                    {
                    igSmartPointer<beNDMWShopSelect01> spBC((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                    beNDMWWindow_BindContext(spBC.p, self, self->_insight, self->_playerNo, 0x614);
                    ObjectList_AppendRetained(self->_subWindow, spBC.p);
                    }
                    self->_nowProcKazu = SUBCNT(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 3:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    FUN_0042b9d0(self);
                    switch (self->_retCode) {
                    case 0:
                        cost2 = self->_tanka * self->_kazu;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        objm = beMessenger_GetObject(self->_messenger, 0);
                        money = W(((int)igProperty_GetRecord(objm, &DAT_0051b560[0])), 12);
                        rec2 = ((int)igProperty_GetRecord(objm, &DAT_0051b560[0]));
                        W(rec2, 12) = money - cost2;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b498[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b4a0[0]);
                        fb = igProperty_GetRecordFolder(objm, &DAT_0051b6c0[0])->f12;
                        jb = 0;
                        if (0 < VCNT(fb)) {
                            do {
                                ib = ((Item_42a2e0 **)fb->_data)[jb];
                                if (ib != 0 && self->_conItemNo == ib->f12) {
                                    ib->f20 = self->_kazu + f20Of(ib);
                                    break;
                                }
                                jb += 1;
                            } while (jb < VCNT(fb));
                        }
                        break;
                    case 1: default:
                        break;
                    }
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st2 = 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> spB8((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(spB8.p, self, self->_insight, self->_playerNo, self->_st3);
                ObjectList_AppendRetained(self->_subWindow, spB8.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    FUN_0042b9d0(self);
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 4:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopCtrlSell> spB4((beNDMWShopCtrlSell *)FUN_003b7360(alloc));
                beNDMWWindow_BindContext(spB4.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, spB4.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void FUN_0042b880(beNDMWShopCtrl50 *owner) {
    char sp40[16];
    int obj;
    int remaining;
    int unitCount;
    beNDMWShopCtrl50 *me;

    me = (beNDMWShopCtrl50 *)owner;
    beMessenger_SendNamed(me->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
    obj = beMessenger_GetObject(me->_messenger, 0);
    remaining = (9 - me->_diskCnt) - me->_retCode;
    unitCount = beDataBase_GetRecordInt(obj, me->_conItemNo, &DAT_0051b690[0], 9, me->_diskCnt);
    sprintf(sp40, percent_d, remaining);
    beMessenger_SelectGroup(me->_messenger, TEXTCTL_3);
    beMessenger_AppendString(me->_messenger, &((const char *)DAT_0051b6f8)[0]);
    beMessenger_AppendString(me->_messenger, &DAT_0051b218[0]);
    beMessenger_AppendString(me->_messenger, sp40);
    beMessenger_DispatchSelected(me->_messenger, TEXTSET);
    sprintf(sp40, percent_d, remaining * unitCount);
    beMessenger_SelectGroup(me->_messenger, TEXTCTL_3);
    beMessenger_AppendString(me->_messenger, &((const char *)DAT_0051b6f8)[0]);
    beMessenger_AppendString(me->_messenger, &DAT_0051b288[0]);
    beMessenger_AppendString(me->_messenger, sp40);
    beMessenger_DispatchSelected(me->_messenger, TEXTSET);
}

void FUN_0042b9d0(beNDMWShopCtrl50 *arg0) {
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b278[0]);
    beMessenger_AppendString(arg0->_messenger, DISPOFF);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(arg0->_messenger, &((int *)DAT_0051b218)[0]);
    beMessenger_AppendString(arg0->_messenger, DISPOFF);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b6f8[0]);
    beMessenger_AppendString(arg0->_messenger, &((int *)DAT_0051b288)[0]);
    beMessenger_AppendString(arg0->_messenger, DISPOFF);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
}

void FUN_0042bae0(int *arg0, int arg1) {
    Tbl sp30;
    float v[3];
    if (arg1 > -1) {
        sp30 = DAT_004cf990;
        beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, DAT_0051b7d8);
        if (beMessenger_GetBool(arg0[3], 0) != 0) {
            beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, (char *)sp30.s[arg1]);
            return;
        }
        beMessenger_SelectReceivers(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0);
        beMessenger_AppendString(arg0[3], sp30.s[arg1]);
        v[2] = 0;
        v[0] = -121.0f;
        v[1] = 128.0f;
        beMessenger_AppendVec3(arg0[3], v);
        beMessenger_DispatchSelected(arg0[3], DAT_0051b7e0);
        return;
    }
    beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, DAT_0051b7d8);
    if (beMessenger_GetBool(arg0[3], 0) != 0) {
        beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, ((char *)DAT_0051b620));
    }
}

void Gap__Bec__beNDMWShopJunk__vfunc_21(beNDMWShopJunk *arg0) {
    void *alloc;
    Tbl_42bc70 sp50;
    switch (arg0->_st0) {
    case 0:
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b498);
        beMessenger_AppendInt(arg0->_messenger, 9);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b7f0);
        if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
            Rc_42bc70 *o = ((Rc_42bc70 *)beMessenger_GetObject(arg0->_messenger, 0));
            if (o != 0) o->_refCount = (int)o->_refCount + 1;
            { Rc_42bc70 *t = (Rc_42bc70 *)arg0->_junkItemList; REL_42bc70(t) }
            arg0->_junkItemList = (int)o;
            arg0->_totalGift = beMessenger_GetInt(arg0->_messenger, 1);
        }
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect01> sp8C((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(sp8C.p, arg0, arg0->_insight, arg0->_playerNo, 0x79e);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp8C.p);
                ((beNDMWShopSelect01 *)sp8C.p)->_startPoint = arg0->_junkMenu;
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                igSmartPointer<igBoolList> sp88((igBoolList *)FUN_002cb0d0(alloc));

                if (arg0->_totalGift >= 3956000) {
                    PUSHB(sp88.p, GPR_00554a38)
                } else {
                    PUSHB(sp88.p, GPR_00554a3c)
                }
                if (((igObjectList *)arg0->_junkItemList)->_count <= 0) {
                    PUSHB(sp88.p, GPR_00554a40)
                } else {
                    PUSHB(sp88.p, GPR_00554a44)
                }
                PUSHB(sp88.p, GPR_00554a48)
                int i;
                Rc_42bc70 *src;
                {
                    for (i = 0; (src = sp88.p, i < ((igBoolList *)src)->_count); i++) {
                        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(arg0->_messenger, (const char *)STWINFONT29);
                        beMessenger_AppendString(arg0->_messenger, g_fontNames[i]);
                        if (*(unsigned char *)(((igBoolList *)sp88.p)->_data + i) != 0) {
                            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3d8);
                        } else {
                            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b800);
                        }
                    }
                }
                {
                    beNDMWShopSelect01 *dst = (beNDMWShopSelect01 *)sp8C.p;
                    if (src != 0) src->_refCount = (int)src->_refCount + 1;
                    { Rc_42bc70 *t = (Rc_42bc70 *)dst->_decideList; REL_42bc70(t) }
                    dst->_decideList = (int)src;
                }
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    {
                        int i = 0;
                        const char **q = g_fontNames;
                        do {
                            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                            beMessenger_AppendString(arg0->_messenger, (const char *)STWINFONT29);
                            beMessenger_AppendString(arg0->_messenger, g_fontNames[i]);
                            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3d8);
                            i++;
                            q++;
                        } while (i < 3);
                    }
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_junkMenu = 0;
                        arg0->_st1 = 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        arg0->_junkMenu = 1;
                        arg0->_st1 = 2;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 2:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopCtrlEditBit> sp84((beNDMWShopCtrlEditBit *)FUN_003b7520(alloc));
                beNDMWWindow_BindContext(sp84.p, arg0, arg0->_insight, arg0->_playerNo, 2);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp84.p);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    if (arg0->_retCode != -1) {
                        igIntList *l;
                        beMessenger_SendGroup(arg0->_messenger, DAT_0051b398, DAT_0051b810);
                        l = FUN_003a9250(((Rc_42bc70 *)beMessenger_GetObject(arg0->_messenger, 0)), DAT_0051b820)->f12;
                        {
                            int c = l->_count;
                            int *p = &((int *)l->_data)[1];
                            int v = *p + (int)arg0->_retCode;
                            if (c != 0 && c > 1) *p = v;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
                        {
                            Rc_42bc70 *o = ((Rc_42bc70 *)beMessenger_GetObject(arg0->_messenger, 0));
                            int s = igProperty_GetRecord(o, DAT_0051b560)->f12 - arg0->_retCode;
                            igProperty_GetRecord(o, DAT_0051b560)->f12 = s;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b498);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b4a0);
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        {
                            int *p;
                            sp50 = DAT_004cf9c0;
                            p = sp50.v;
                            if (*p != -1) {
                                do {
                                    if (arg0->_totalGift < *p && !(((int *)l->_data)[1] < *p)) {
                                        beLua__RunNamedChunk(FUN_00236f80(arg0->_insight, g_beLua_metaObject[0]), DAT_0051b828, DAT_0051b838);
                                        arg0->_st1 = 3;
                                        arg0->_st3 = 0;
                                        arg0->_st2 = 0;
                                        return;
                                    }
                                    p++;
                                } while (*p != -1);
                            }
                        }
                    } else {
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopCtrlSales> sp80((beNDMWShopCtrlSales *)FUN_003b6bc0(alloc));
                beNDMWWindow_BindContext(sp80.p, arg0, arg0->_insight, arg0->_playerNo, 9);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp80.p);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect00> sp7C((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(sp7C.p, arg0, arg0->_insight, arg0->_playerNo, 0x7b2);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp7C.p);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}


static inline int countOf(const igIntList *l) { return l->_count; }

void Gap__Bec__beNDMWShopCtrlA0__vfunc_21(beNDMWShopCtrlA0 *arg0) {
    S_ref *t;
    int x;
    int i;

    switch (arg0->_st0) {
    case 0:
        switch (arg0->_st1) {
        case 0:
            beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b848[0], 0, &DAT_0051b858[0], &DAT_0051b620[0]);
            beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b348[0], 0, &DAT_0051b868[0], &DAT_0051b620[0]);
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            return;
        case 1:
            beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b848[0], 0);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051b858[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b338[0]);
            if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) != 1) {
                x = ((int)igObject_GetAllocator(arg0));
                { igSmartPointer<beNDMWShopTitle03> r1((beNDMWShopTitle03 *)FUN_003b2c00(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                beNDMWWindow_BindContext(r1.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, r1.p);
                }  
                x = ((int)igObject_GetAllocator(arg0));
                { igSmartPointer<beNDMWStatusTitle03> r2((beNDMWStatusTitle03 *)FUN_003b36f0(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                beNDMWWindow_BindContext(r2.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, r2.p);
                {
                    S_ref *n = (S_ref *)r2.p;
                    if (n != 0) { n->f4 = (int)((int)(n->f4 + 1)); }
                    t = (S_ref *)(arg0->_account);
                    if (t != 0) {
                        t->f4 = (int)((int)(t->f4 - 1));
                        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                            igObject_Destroy(t);
                        }
                    }
                    arg0->_account = (int)n;
                }
                FUN_00426530(arg0->_account, 0);
                }  
                x = ((int)igObject_GetAllocator(arg0));
                { igSmartPointer<beNDMWShopTitle01> r3((beNDMWShopTitle01 *)FUN_003b31b0(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                beNDMWWindow_BindContext(r3.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
                ObjectList_AppendRetained(arg0->_subWindow, r3.p);
                }  
                i = 0;
                do {
                    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                    beMessenger_AppendInt(arg0->_messenger, i);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                    if (igProperty_GetRecordByte(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b870[0])->f12 != 0) {
                        int c;
                        igIntList *l;
                        l = (igIntList *)arg0->_playerNoList;
                        c = l->_count;
                        if (c < l->_capacity) {
                            l->_count = countOf(l) + 1;
                        } else {
                            List_Resize(l, c + 1, 4);
                        }
                        ((int *)l->_data)[c] = i;
                    }
                    i += 1;
                } while (i < 4);
                x = ((int)igObject_GetAllocator(arg0));
                { igSmartPointer<beNDMWStatusTitle01> r4((beNDMWStatusTitle01 *)FUN_003b3ac0(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                beNDMWWindow_BindContext(r4.p, arg0, arg0->_insight, arg0->_playerNo, 1);
                ObjectList_AppendRetained(arg0->_subWindow, r4.p);
                }  
                arg0->_st0 = arg0->_st0 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 1:
        switch (arg0->_st1) {
        case 0:
            beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051b868[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b338[0]);
            if (((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) != 1) && (arg0->_entCode == 0xA)) {
                arg0->_st1 = 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                return;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                x = ((int)igObject_GetAllocator(arg0));
                { igSmartPointer<beNDMWShopSelect02> r5((beNDMWShopSelect02 *)FUN_003b4b10(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                beNDMWWindow_BindContext(r5.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D3);
                ObjectList_AppendRetained(arg0->_subWindow, r5.p);
                FUN_00426530(arg0->_account, 0);
                }  
                arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;

            case 1:
                if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_st1 = 2;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 1:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        ((beSystem *)FUN_00236f80(arg0->_insight, g_beSystem_metaObject[0]))->_isSResetEnable = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                x = ((int)igObject_GetAllocator(arg0));
                { igSmartPointer<beNDMWShopSelect02> r6((beNDMWShopSelect02 *)FUN_003b4b10(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                beNDMWWindow_BindContext(r6.p, arg0, arg0->_insight, arg0->_playerNo, -1);
                ObjectList_AppendRetained(arg0->_subWindow, r6.p);
                i = 0;
                {
                    int j;
                    int c;
                    igIntList *l;
                    int *src;
                    for (j = 0; j < ((igIntList *)arg0->_playerNoList)->_count; j++) {
                        src = (int *)((igIntList *)arg0->_playerNoList)->_data + j;
                        l = ((S_obj *)r6.p)->f112;
                        c = l->_count;
                        if (c < l->_capacity) {
                            l->_count = countOf(l) + 1;
                        } else {
                            List_Resize(l, c + 1, 4);
                        }
                        ((int *)l->_data)[c] = *src;
                    }
                }
                }  
                FUN_00426530(arg0->_account, 1);
                arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;

            case 1:
                {
                    if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                        switch (arg0->_retCode) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            {
                                int *found = 0;
                                int *obj;
                                int idx;
                                for (idx = 0; idx < ((igObjectList *)arg0->_subWindow)->_count; idx++) {
                                    obj = (int *)((int *)((igObjectList *)(*(int *)&arg0->_subWindow))->_data)[idx];
                                    if ((obj != 0) && (igObject_IsKindOf(obj, g_beNDMWStatusTitle01_metaObject[0]) != 0)) {
                                        found = obj;
                                    } else {
                                        found = 0;
                                    }
                                    if (found != 0) break;
                                }
                                if (found != 0) {
                                    found[5] = ((int *)((igIntList *)arg0->_playerNoList)->_data)[arg0->_retCode];
                                    FUN_00425fb0(found);
                                    arg0->_playerNo = ((int *)((igIntList *)arg0->_playerNoList)->_data)[arg0->_retCode];
                                }
                            }
                            x = ((int)igObject_GetAllocator(arg0));
                            { igSmartPointer<beNDMWShopCtrlA1> r7((beNDMWShopCtrlA1 *)FUN_003b7c00(GPR_00554c14 != 0 ? x : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]))));
                            beNDMWWindow_BindContext(r7.p, arg0, arg0->_insight, ((int *)((igIntList *)arg0->_playerNoList)->_data)[arg0->_retCode], 0);
                            ObjectList_AppendRetained(arg0->_subWindow, r7.p);
                            }  
                            arg0->_nowProcKazu = ((igObjectList *)arg0->_subWindow)->_count;
                            arg0->_st1 = 3;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        default:
                            arg0->_st1 = 1;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        }
                    }
                }
                break;
            }
            break;
        case 3:
            if (((igObjectList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                arg0->_st1 = 2;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        t = (S_ref *)(arg0->_account);
        if (t != 0) {
            t->f4 = (int)((int)(t->f4 - 1));
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->_account = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}




static inline int st0_42d450(const beNDMWShopCtrlA1 *self) { return self->_st0; }

void Gap__Bec__beNDMWShopCtrlA1__vfunc_21(beNDMWShopCtrlA1 *arg0) {
    void *alloc;
    float sp40[3];
    float sp30[3];
    const igObjectList *a;
    int s0;
    int i;
    Item_42a2e0 *it;
    switch (arg0->_st0) {
    case 0:
        arg0->_st0 = st0_42d450(arg0) + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 4;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        return;
    case 1:
        switch (arg0->_st1) {
        case 4:
            switch (arg0->_st2) {
            case 0:
                beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b878, arg0->_playerNo);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b338);
                if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                    return;
                }
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect02> win((beNDMWShopSelect02 *)FUN_003b4b10(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D5);
                ObjectList_AppendRetained(arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_st1 = 5;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        arg0->_st1 = 6;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 5:
            switch (arg0->_st2) {
            case 0:
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
                beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
                a = igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051b6c0)->f12;
                s0 = 0;
                i = 0;
                while (i < a->_count) {
                    it = ((Item_42a2e0 **)((igObjectList *)a)->_data)[i];
                    if (it != 0 && it->f12 == 10) {
                        s0 = it->f20;
                        break;
                    }
                    i++;
                }
                if (s0 > 0) {
                    alloc = igObject_GetAllocator(arg0);
                    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beNDMWShopCtrlA2> win((beNDMWShopCtrlA2 *)FUN_003b7a40(alloc));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, s0);
                    ObjectList_AppendRetained(arg0->_subWindow, win.p);
                } else {
                    alloc = igObject_GetAllocator(arg0);
                    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                    igSmartPointer<beNDMWShopSelect03> win((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D7);
                    ObjectList_AppendRetained(arg0->_subWindow, win.p);
                    beMessenger_SelectGroup(arg0->_messenger, DAT_0051b888);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b890);
                    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b8a0);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 6:
                        arg0->_st1 = 6;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 4:
                        arg0->_st1 = 4;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 0:
                        arg0->_st1 = 4;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 6:
            switch (arg0->_st2) {
            case 0:
                beMessenger_SendNamed(arg0->_messenger, DAT_0051b308, DAT_0051b8a8, 0, DAT_0051b620);
                beMessenger_SendNamed(arg0->_messenger, DAT_0051b308, DAT_0051b318, 0, DAT_0051b620);
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8b8);
                beMessenger_AppendString(arg0->_messenger, DAT_004cf8a8[0]);
                beMessenger_AppendString(arg0->_messenger, DISPOFF);
                beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelectA0> win((beNDMWShopSelectA0 *)FUN_003b4250(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, win.p);
                }
                FUN_0042df70((beNDMWShopCtrlA1 *)arg0);
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b8c8, 0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b338);
                if ((beMessenger_GetBool(arg0->_messenger, 0) & 0xFF) == 1) {
                    return;
                }
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8d8);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b1c8);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8e8);
                beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8d8);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b1d0);
                beMessenger_AppendString(arg0->_messenger, DAT_0051b8f0);
                beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 2:
                if (((igDataList *)arg0->_subWindow)->_count == arg0->_nowProcKazu) {
                    if (arg0->_retCode != -1 && arg0->_st3 != arg0->_retCode) {
                        FUN_0042e330((beNDMWShopCtrlA1 *)arg0);
                        arg0->_st3 = arg0->_retCode;
                        return;
                    }
                } else {
                    FUN_0042e9e0((beNDMWShopCtrlA1 *)arg0);
                    beNDMWWindow_RunMessageScript(arg0, DAT_0051b8f8, 0);
                    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b8b8);
                    beMessenger_AppendString(arg0->_messenger, DAT_004cf8a8[0]);
                    beMessenger_AppendString(arg0->_messenger, ((int *)DISPON));
                    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                    beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b8a8, 0);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                    sp40[0] = g_vec3Zero[0];
                    sp40[1] = DAT_004e105c[0];
                    sp40[2] = DAT_004e1060[0];
                    beMessenger_AppendVec3(arg0->_messenger, (float *)sp40);
                    beMessenger_DispatchSelected(arg0->_messenger, ((int *)DAT_0051b7e0));
                    beMessenger_SelectReceivers(arg0->_messenger, DAT_0051b308, DAT_0051b318, 0);
                    beMessenger_AppendString(arg0->_messenger, DAT_0051b868);
                    sp30[0] = g_vec3Zero[0];
                    sp30[1] = DAT_004e105c[0];
                    sp30[2] = DAT_004e1060[0];
                    beMessenger_AppendVec3(arg0->_messenger, (float *)sp30);
                    beMessenger_DispatchSelected(arg0->_messenger, ((int *)DAT_0051b7e0));
                    arg0->_st1 = 4;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}




void FUN_0042df70(beNDMWShopCtrlA1 *arg0) {
    Arr *s2;
    int s1;
    int s4;
    int s0;
    int c;
    int tt;
    igIntList *l;
    int c2;
    igIntList *l2;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    s2 = ((Rec_42df70 *)igProperty_GetRecordArray(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b908[0]))->f12;
    beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], &DAT_0051b918[0], 0, &DAT_0051b5e8[0]);
    if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
        s1 = beMessenger_GetObject(arg0->_messenger, 0);
    } else {
        return;
    }
    {
        s0 = 0;
        do {
            beDataBase_GetRecordString(s1, s0, &DAT_0051b920[0]);
            beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0]);
            if (s2->f16[s0] != 0) {
                s4 = ((int)beDataBase_GetRecordString(s1, s0, &DAT_0051b920[0]));
                tt = Str::intern((int *)s4);
                StringRef name(tt);
                beNDMWWindow_PresentModelAtOrigin(arg0, name.p, 0, ((int)beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0])), 0);
                {
                    StringRef copy((int)name.p);
                    tt = (int)copy.p;
                    if (tt)
                        *(int *)(tt - 4) = *(int *)(tt - 4) + 1;
                    StringList_AppendRetained(arg0->_cardInfoList, copy);
                }
                l = (igIntList *)arg0->_cardRamNoList;
                c = l->_count;
                if (c < l->_capacity) {
                    l->_count = countOf(l) + 1;
                } else {
                    List_Resize(l, c + 1, 4);
                }
                ((int *)l->_data)[c] = DAT_004cf9e8[0];
            } else {
                beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b938[0], s0, ((int)beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0])), 0);
                { int tok = Str::intern(&DAT_0051b938[0]); StringList_AppendRetained(arg0->_cardInfoList, StringRef(tok)); }
                l2 = (igIntList *)arg0->_cardRamNoList;
                c2 = l2->_count;
                if (c2 < l2->_capacity) {
                    l2->_count = countOf(l2) + 1;
                } else {
                    List_Resize(l2, c2 + 1, 4);
                }
                ((int *)l2->_data)[c2] = s0;
            }
            s0++;
        } while (s0 < 6);
    }
}

void FUN_0042e330(beNDMWShopCtrlA1 *self) {
    char pageText[2];
    igDataList *list;
    Arr *flags;
    int page;
    int record;
    int i;
    int count;
    int model;
    int card;
    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
    flags = ((Rec_42df70 *)igProperty_GetRecordArray(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b908[0]))->f12;
    page = self->_retCode;
    beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b918[0], 0, &DAT_0051b5e8[0]);
    if (beMessenger_GetObjectCount(self->_messenger) > 0) {
        record = beMessenger_GetObject(self->_messenger, 0);
    } else {
        return;
    }
    pageText[1] = 0;
    pageText[0] = page + '1';
    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
    beMessenger_AppendString(self->_messenger, &DAT_0051b8d8[0]);
    beMessenger_AppendString(self->_messenger, &DAT_0051b1c8[0]);
    beMessenger_AppendString(self->_messenger, pageText);
    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
    switch (page) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        for (i = 0; i < 6; i++) {
            StringRef name = StringList_CopyRetained(((igDataList *)self->_cardInfoList), i);
            /* matching construct: variant search — `card` before the ram-number load (induction register order) */
            card = page * 6 + i;
            model = ((int *)((igIntList *)self->_cardRamNoList)->_data)[i];
            if (card > 49) {
                beNDMWWindow_SendModelSequence(self, name.p, model, &DAT_0051b620[0]);
                StoreCardName(self, i, Str::intern(&DAT_0051b948[0]));
                list = ((igDataList *)self->_cardRamNoList);
                count = list->_count;
                if (count != 0 && i >= 0 && i < count) ((int *)list->_data)[i] = DAT_004cf9f0[0];
            } else if (flags->f16[card] != 0) {
                if (model != -1) beNDMWWindow_SendModelSequence(self, name.p, model, &DAT_0051b620[0]);
                StringRef cardName(Str::intern((int *)beDataBase_GetRecordString(record, card, &DAT_0051b920[0])));
                beNDMWWindow_PresentModelAtOrigin(self, cardName.p, 0, ((int)beDataBase_GetRecordString(record, card, &DAT_0051b930[0])), 0);
                list = ((igDataList *)self->_cardInfoList);
                count = list->_count;
                if (count != 0 && i >= 0 && i < count) {
                    int *slot = &((int *)list->_data)[i];
                    int text = (int)cardName.p;
                    if (text) *(int *)(text - 4) = *(int *)(text - 4) + 1;
                    RELS((char *)*slot);
                    *slot = (int)cardName.p;
                }
                list = ((igDataList *)self->_cardRamNoList);
                count = list->_count;
                if (count != 0 && i >= 0 && i < count) ((int *)list->_data)[i] = DAT_004cf9f8[0];
            } else {
                if (model != -1) {
                    if (strcmp(name.p, &DAT_0051b938[0]) == 0)
                        continue;
                    beNDMWWindow_SendModelSequence(self, name.p, model, &DAT_0051b620[0]);
                }
                beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b938[0], i, ((int)beDataBase_GetRecordString(record, i, &DAT_0051b930[0])), 0);
                StoreCardName(self, i, Str::intern(&DAT_0051b938[0]));
                list = ((igDataList *)self->_cardRamNoList);
                count = list->_count;
                if (count != 0 && i >= 0 && i < count) ((int *)list->_data)[i] = i;
            }
        }
        break;
    }
}

void FUN_0042e9e0(beNDMWShopCtrlA1 *arg0) {
    int *temp_a1_2;
    int temp_a2;
    int var_s2;
    int temp_v1_2;
    int var_s1;
    igDataList *l2;
    int temp_s5;
    int var_s4;
    int var_v0;
    int **temp_s3;
    int *temp_a0;
    int *temp_s2;
    igDataList *var_a1;
    int var_s1_2;

    var_s2 = 0;
    var_a1 = (igDataList *)arg0->_cardInfoList;
    if (0 < var_a1->_count) {
        var_s1 = 0;
        do {
            {
                StringRef name = (StringList_CopyRetained(var_a1, var_s2));
                temp_a2 = *(int *)(((igDataList *)arg0->_cardRamNoList)->_data + var_s1);
                if (temp_a2 != -1) {
                    beNDMWWindow_SendModelSequence(arg0, name.p, temp_a2, &DAT_0051b620[0]);
                }
            }
            var_a1 = (igDataList *)arg0->_cardInfoList;
            var_s2 += 1;
            var_s1 += 4;
        } while (var_s2 < var_a1->_count);
    }
    temp_s5 = *(int *)&var_a1->_count;
    l2 = (igDataList *)var_a1;
    var_s4 = 0;
    if (0 < temp_s5) {
        var_s1_2 = 0;
        do {
            temp_s3 = (int **)(l2->_data + var_s1_2);
            if (g_stringPool[0] == 0) {
                var_v0 = FUN_002eb010(0x10);
                if (var_v0 != 0) {
                    var_v0 = StringPool_Construct(var_v0);
                }
                g_stringPool[0] = var_v0;
            }
            temp_s2 = (int *)StringPool_Intern(g_stringPool[0], 0);
            temp_a0 = *temp_s3;
            if (temp_a0 != 0) {
                temp_a1_2 = temp_a0 - 2;
                temp_v1_2 = temp_a0[-1] - 1;
                temp_a0[-1] = temp_v1_2;
                if (temp_v1_2 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
                }
            }
            var_s4 += 1;
            *temp_s3 = temp_s2;
            var_s1_2 += 4;
        } while (var_s4 < temp_s5);
    }
    l2->_count = 0;
    ((igDataList *)arg0->_cardRamNoList)->_count = 0;
}

static inline int st0_42eb80(const beNDMWShopCtrlA2 *ctrl) { return ctrl->_st0; }

void Gap__Bec__beNDMWShopCtrlA2__vfunc_21(beNDMWShopCtrlA2 *arg0) {
    void *alloc;
    void *a3;
    unsigned times[3];
    P3 names1;
    P3 names2;
    P3 names3;
    float vec[3];
    int obj;
    beNDMWStatus *ctx;
    int maxv;
    int i;
    switch (arg0->_st0) {
    case 0:
        arg0->_st0 = st0_42eb80(arg0) + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 7;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        return;
    case 1:
        switch (arg0->_st1) {
        case 7:
            switch (arg0->_st2) {
            case 0:
                switch ((unsigned)arg0->_entCode) {
                case 1: a3 = DAT_0051b708; break;
                case 2: a3 = DAT_0051b718; break;
                case 3: a3 = DAT_0051b728; break;
                case 4: a3 = DAT_0051b738; break;
                case 5: a3 = DAT_0051b748; break;
                case 6: a3 = DAT_0051b758; break;
                case 7: a3 = DAT_0051b768; break;
                case 8: a3 = DAT_0051b778; break;
                case 9: a3 = DAT_0051b788; break;
                }
                beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051b9c0, 0, a3, DAT_0051b620);
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                    igSmartPointer<beNDMWShopSelect03> win((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x7DD);
                    ObjectList_AppendRetained(arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st2 = arg0->_st2 + 1;
                    arg0->_st3 = 0;
                }
                break;
            case 2:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                    igSmartPointer<beNDMWShopSelect02> win((beNDMWShopSelect02 *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0x7D8);
                    ObjectList_AppendRetained(arg0->_subWindow, win.p);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 3:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        beNDMWWindow_PlayQueuedModelClose(arg0);
                        CLEAR(arg0->_modelCloseInfoNameList)
                        ((igIntList *)arg0->_modelCloseRamNoList)->_count = 0;
                        CLEAR(arg0->_modelCloseSeqNameList)
                        arg0->_st1 = 8;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        ((beNDMWWindow *)arg0->_mother)->_retCode = 6;
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    default:
                        ((beNDMWWindow *)arg0->_mother)->_retCode = 4;
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 8:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect03> win((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, win.p);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
                beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
                obj = beMessenger_GetObject(arg0->_messenger, 0);
                {
                    const igDataList *a = ((FRec *)igProperty_GetRecordFolder(obj, DAT_0051b6c0))->f12;
                    int j = 0;
                    while (j < a->_count) {
                        Item_42a2e0 *it = ((Item_42a2e0 **)a->_data)[j];
                        if (it != 0 && it->f12 == 10) {
                            if (it->f20 > 0) it->f20 = it->f20 - 1;
                            break;
                        }
                        j++;
                    }
                }
                beMessenger_SendNamed(arg0->_messenger, DAT_0051b5d8, DAT_0051b918, 0, DAT_0051b5e8);
                {
                int db = beMessenger_GetObject(arg0->_messenger, 0);
                ctx = (beNDMWStatus *)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0]);
                maxv = 0;
                names1 = DAT_004cfa00;
                names2 = DAT_004cfa10;
                for (i = 0; i < 3; i++) {
                    unsigned char found;
                    int acc;
                    int idx;
                    int cnt;
                    times[i] = (((VObj *)((beSystem *)ctx->_system)->_random)->f24() % 1000U) * 1000;
                    found = 0;
                    acc = 0;
                    idx = 0;
                    cnt = beDataBase_GetRecordCount(db);
                    for (; idx < cnt; idx++) {
                        acc += beDataBase_GetRecordInt(db, idx, DAT_0051b9d0) * 1000;
                        if (times[i] < (unsigned)acc) { found = 1; break; }
                    }
                    if (found == 0) idx = cnt - 1;
                    {
                        igDataList *ar = ((Rec_42eb80 *)igProperty_GetRecordArray(obj, DAT_0051b908))->f12;
                        if (ar->_count != 0 && idx >= 0 && idx < ar->_count) ((char *)ar->_data)[idx] = GPR_00554a4c;
                    }
                    if (maxv < beDataBase_GetRecordInt(db, idx, DAT_0051b9e0)) maxv = beDataBase_GetRecordInt(db, idx, DAT_0051b9e0);
                    beNDMWWindow_QueueText((beNDMWShopSelect03 *)win, DAT_0051b9e8, names1.p[i], ((void *)beDataBase_GetRecordString(db, idx, NAME_2)), DAT_0051b598);
                    beNDMWWindow_PresentModelAtOrigin(win.p, ((void *)beDataBase_GetRecordString(db, idx, DAT_0051b920)), i, names2.p[i], DAT_0051b620);
                    {
                        float x, y, z;
                        switch (beDataBase_GetRecordInt(db, idx, DAT_0051b9e0)) {
                        case 2: x = 0.0f; y = 1.0f; z = 0.0f; break;
                        case 1: x = 1.0f; y = 1.0f; z = 0.0f; break;
                        default: x = 1.0f; y = 1.0f; z = 1.0f; break;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(arg0->_messenger, DAT_0051b9e8);
                        beMessenger_AppendString(arg0->_messenger, names1.p[i]);
                        vec[0] = x; vec[1] = y; vec[2] = z;
                        beMessenger_AppendVec3(arg0->_messenger, (float *)vec);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b9f8);
                    }
                }
                }
                switch (maxv) {
                case 2: ((beNDMWShopSelect03 *)win)->_entCode = 0x7DA; break;
                case 1: ((beNDMWShopSelect03 *)win)->_entCode = 0x7DB; break;
                default: ((beNDMWShopSelect03 *)win)->_entCode = 0x7DC; break;
                }
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    int k;
                    names3 = DAT_004cfa20;
                    for (k = 0; k < 3; k++) {
                        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                        beMessenger_AppendString(arg0->_messenger, DAT_0051b9e8);
                        beMessenger_AppendString(arg0->_messenger, names3.p[k]);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3d8);
                    }
                    ((beNDMWWindow *)arg0->_mother)->_retCode = 4;
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}

void Gap__Bec__beNDMWShopCtrlEvolve__vfunc_21(beNDMWShopCtrlEvolve *self) {
    int vB[3];
    int vA[3];
    void *alloc;
    int v;
    beNDMWShinkaObject *el;
    int money;

    switch (self->_st0) {
    case 0:
        switch (self->_st1) {
        case 0:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b318[0], 0, &DAT_0051b328[0], &DAT_0051ba28[0]);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            beMessenger_SelectReceivers(self->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
            beMessenger_AppendString(self->_messenger, &DAT_0051b328[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b338[0]);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                FUN_00443110(self->_shinkaCtrl, self->_insight, self->_playerNo);
                if (SLIST(self)->_count > 8) {
                    self->_maxPage = 2;
                } else {
                    self->_maxPage = 1;
                }
                self->_nowPage = 0;
                self->_cursor = 0;
                if (self->_maxPage > 1) {
                    beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051ba38[0], &DAT_0051b620[0]);
                    vA[0] = 0xC24C0000;
                    vA[2] = 0;
                    vA[1] = 0x41C80000;
                    vB[0] = 0xC39A0000;
                    vB[1] = 0x41C80000;
                    vB[2] = 0;
                    ((DummyVirtual *)self)->v24(vB, vA);
                    beNDMWWindow_QueueText(self, &DAT_0051ba48[0], ((char * *)g_fontNames)[0], &DAT_0051b590[0], &DAT_0051b460[0]);
                    beNDMWWindow_QueueText(self, &DAT_0051ba48[0], g_fontName1[0], &DAT_0051b590[0], &DAT_0051b460[0]);
                } else {
                    beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051ba60[0], &DAT_0051b620[0]);
                }
                APPENDSTR_42f710(self->_textCloseTypeList, STWINFONT29)
                APPENDSTR_42f710(self->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4E6);
                APPENDSTR_42f710(self->_textCloseTypeList, &DAT_0051ba70[0])
                APPENDSTRV(self->_textCloseNameList, ((char * *)g_fontNames)[0])
                APPENDSTR_42f710(self->_textCloseTypeList, &DAT_0051ba70[0])
                APPENDSTRV(self->_textCloseNameList, g_fontName1[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4C2);
                {
                int i = 0;
                char **fp = ((char * *)g_fontNames);
                do {
                    beNDMWWindow_QueueText(self, &DAT_0051ba80[0], *fp, &DAT_0051b590[0], &DAT_0051b598[0]);
                    beNDMWWindow_QueueText(self, &DAT_0051ba90[0], *fp, &DAT_0051b590[0], &DAT_0051b598[0]);
                    beNDMWWindow_QueueText(self, &DAT_0051baa0[0], *fp, &DAT_0051b590[0], &DAT_0051b460[0]);
                    i += 1;
                    fp += 1;
                } while (i < 8);
                }
                {
                int j = 0;
                char **gp = DAT_004cf8d0;
                do {
                    beNDMWWindow_QueueText(self, &DAT_0051bab0[0], gp[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                    beNDMWWindow_QueueText(self, &DAT_0051bab0[0], gp[1], &DAT_0051b590[0], &DAT_0051b460[0]);
                    j += 1;
                    gp += 2;
                } while (j < 16);
                }
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4B2);
                beNDMWWindow_QueueText(self, STWINFONT29, ((char * *)g_fontNames)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                self->_st1 = 0;
                self->_st3 = 0;
                self->_st2 = 0;
                return;
            }
            break;
        }
        break;
    case 1:
        switch (self->_st1) {
        case 0:
            ALLOC_42f710(alloc, self)
            {
            igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)FUN_003b51b0(alloc));
            beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, win.p);
            {
            float *pos = ((beNDMWWindowSelect *)win.p)->_offsetPos;
            pos[0] = -283.0f;
            pos[1] = 92.0f;
            pos[2] = 0.0f;
            ((beNDMWWindowSelect *)win.p)->_startPoint = self->_cursor;
            v = SLIST(self)->_count;
            if (v == 0) {
                ((beNDMWWindowSelect *)win.p)->_selectMax = 2;
            } else {
                switch (self->_nowPage) {
                case 0:
                    if (v > 8) {
                        ((beNDMWWindowSelect *)win.p)->_selectMax = 8;
                    } else {
                        ((beNDMWWindowSelect *)win.p)->_selectMax = v;
                    }
                    break;
                case 1:
                    ((beNDMWWindowSelect *)win.p)->_selectMax = v - 8;
                    break;
                }
            }
            }
            }
            self->_nowProcKazu = SUB(self)->_count;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_retCode = self->_cursor;
            FUN_00430d20(self, 1, 0);
        case 1:
            if (self->_retCode != -1) {
                FUN_00430d20(self, 0, 1);
            }
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st3 = self->_retCode;
        case 2:
            if (SUB(self)->_count == self->_nowProcKazu) {
                if (self->_retCode != -1) {
                    if (self->_st3 != self->_retCode) {
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                    {
                    int *found = 0;
                    int i = 0;
                    int *obj;
                    if (0 < SUB(self)->_count) {
                        do {
                            obj = (int *)((int *)((igObjectList *)*(int *)&self->_subWindow)->_data)[i];
                            if ((obj != 0) && (igObject_IsKindOf(obj, g_beNDMWStatusSelectE1_metaObject[0]) != 0)) {
                                found = obj;
                            } else {
                                found = 0;
                            }
                            if (found != 0) break;
                            i += 1;
                        } while (i < SUB(self)->_count);
                    }
                    if (beNDMWWindowSelect_CanRequestFO2TOP(found) != 0) {
                        bool flag = false;
                        if (((DummyVirtual *)self)->v25() != 0) {
                            flag = true;
                        } else if (((DummyVirtual *)self)->v26() != 0) {
                            flag = true;
                        }
                        if (flag) {
                            ((beNDMWWindowSelect *)found)->_st0 = 4;
                            ((beNDMWWindowSelect *)found)->_st3 = 0;
                            ((beNDMWWindowSelect *)found)->_st2 = 0;
                            ((beNDMWWindowSelect *)found)->_st1 = 0;
                            v = SLIST(self)->_count;
                            if (v == 0) {
                                ((beNDMWWindowSelect *)found)->_selectMax = 2;
                            } else {
                                switch (self->_nowPage) {
                                case 0:
                                    if (v > 8) {
                                        ((beNDMWWindowSelect *)found)->_selectMax = 8;
                                    } else {
                                        ((beNDMWWindowSelect *)found)->_selectMax = v;
                                    }
                                    break;
                                case 1:
                                    ((beNDMWWindowSelect *)found)->_selectMax = v - 8;
                                    break;
                                }
                            }
                            self->_st1 = 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            self->_retCode = 0;
                            FUN_00430d20(self, 1, 0);
                            return;
                        }
                    }
                    }
                }
            } else {
                switch (self->_retCode) {
                case -1:
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                default:
                    self->_cursor = self->_retCode;
                    el = (beNDMWShinkaObject *)((int *)SLIST(self)->_data)[self->_cursor + self->_nowPage * 8];
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                    money = W(((int *)igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051bac0[0])), 12);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_AppendInt(self->_messenger, el->_id);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051bad0[0]);
                    if (money == el->_id) {
                        self->_st1 = 4;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st2 = 0;
                        self->_st3 = 0;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b888[0]);
                        beMessenger_AppendString(self->_messenger, &DAT_0051b890[0]);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b8a0[0]);
                        return;
                    }
                    if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                        self->_st1 = 4;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st2 = 1;
                        self->_st3 = 0;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b888[0]);
                        beMessenger_AppendString(self->_messenger, &DAT_0051b890[0]);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b8a0[0]);
                        return;
                    }
                    self->_st1 = 3;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                ALLOC_42f710(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect01> win((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0x4E7);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        return;
                    case 1:
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            case 2:
                ALLOC_42f710(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0x4E9);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 3:
                if (SUB(self)->_count == self->_nowProcKazu) break;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 4:
                ALLOC_42f710(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect01> win((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0x4EA);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 5:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        return;
                    case 1:
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            case 6: {
                beNDMWShinkaObjectList *ar;
                int cnt;
                int idx;
                ALLOC_42f710(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                APPENDSTR_42f710(((beNDMWWindowSelect *)win.p)->_textCloseTypeList, STWINFONT29)
                APPENDSTR_42f710(((beNDMWWindowSelect *)win.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4EC);
                }
                ar = SLIST(self);
                idx = self->_cursor + self->_nowPage * 8;
                cnt = ar->_count;
                if (cnt > 0 && idx < cnt) {
                    beNDMWShinkaObject *e = (beNDMWShinkaObject *)((int *)ar->_data)[idx];
                    char *rs;
                    beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051bae8[0], 0, &DAT_0051b5e8[0]);
                    rs = beDataBase_GetRecordString(beMessenger_GetObject(self->_messenger, 0), e->_id, &DAT_0051baf0[0]);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
                    beMessenger_AppendString(self->_messenger, rs);
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
                    beMessenger_AppendString(self->_messenger, &((int *)DISPON)[0]);
                    beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                    FUN_004313b0(self);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            }
            case 7:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    ((beNDMWWindow *)self->_mother)->_retCode = 1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 4:
            switch (self->_st3) {
            case 0:
                ALLOC_42f710(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                APPENDSTR_42f710(((beNDMWWindowSelect *)win.p)->_textCloseTypeList, STWINFONT29)
                APPENDSTR_42f710(((beNDMWWindowSelect *)win.p)->_textCloseNameList, &DAT_0051b1c8[0])
                if (self->_st2 == 0) {
                    beNDMWWindow_RunMessageScript(win.p, &DAT_0051b3b0[0], 0x7E4);
                } else {
                    beNDMWWindow_RunMessageScript(win.p, &DAT_0051b3b0[0], 0x7E5);
                }
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st3 = self->_st3 + 1;
            case 1:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

void FUN_00430d20(beNDMWShopCtrlEvolve *ctl, int sendNames, int sendStats) {
    char countBuf[28];
    int statVals[16];
    char valueBuf[16];
    char pageDigits[4];
    beNDMWShinkaObjectList *itemList;
    int slot;
    char *itemName;
    char **labelPtr;
    int statIdx;
    int digitChar;
    int pageBase;
    int cursor;
    int selIndex;
    beNDMWShinkaObjectList *selList;
    int listIndex;
    beNDMWShinkaObject *item;
    beNDMWShinkaObject *selItem;
    char *recordName;
    int *valuePtr;
    struct NamePair *labelPair;
    if (sendNames != 0) {
        itemList = (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)ctl->_shinkaCtrl)->_list;
        for (slot = 0, labelPtr = ((char * *)g_fontNames); slot < 8; slot++, labelPtr++) {
            listIndex = slot + ctl->_nowPage * 8;
            if (itemList->_count - 1 < listIndex) {
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba80));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, ((char *)DISPOFF));
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba90));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, ((char *)DISPOFF));
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051baa0));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, ((char *)DISPOFF));
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
            } else {
                item = (beNDMWShinkaObject *)((int *)itemList->_data)[listIndex];
                itemName = (char *)item->_name;
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba80));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, itemName);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba80));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DISPON);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba90));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DAT_0051bb20);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba90));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DISPON);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
                sprintf(countBuf, ((char *)percent_d), ((beNDMWShinkaObject *)((int *)itemList->_data)[listIndex])->_level);
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051baa0));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, countBuf);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051baa0));
                beMessenger_AppendString(ctl->_messenger, *labelPtr);
                beMessenger_AppendString(ctl->_messenger, DISPON);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
            }
        }
        if (ctl->_maxPage > 1) {
            pageDigits[1] = 0;
            digitChar = ctl->_nowPage; digitChar += 0x31;
            pageDigits[0] = digitChar;
            beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
            beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba48));
            beMessenger_AppendString(ctl->_messenger, ((char * *)g_fontNames)[0]);
            beMessenger_AppendString(ctl->_messenger, pageDigits);
            beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
            digitChar = ctl->_maxPage; digitChar += 0x30;
            pageDigits[0] = digitChar;
            beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
            beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051ba48));
            beMessenger_AppendString(ctl->_messenger, ((char * *)g_fontNames)[1]);
            beMessenger_AppendString(ctl->_messenger, pageDigits);
            beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
        }
    }
    if (sendStats != 0) {
        cursor = ctl->_retCode;
        if (cursor != -1) {
            selList = (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)ctl->_shinkaCtrl)->_list;
            pageBase = ctl->_nowPage * 8;
            selIndex = pageBase + cursor;
            if (selIndex < selList->_count) {
                selItem = (beNDMWShinkaObject *)((int *)selList->_data)[selIndex];
                statVals[0] = selItem->_hpMax;
                statVals[1] = selItem->_mpMax;
                statVals[2] = selItem->_tsuyosa;
                statVals[3] = selItem->_mamori;
                statVals[4] = selItem->_kashikosa;
                statVals[5] = selItem->_seishin;
                statVals[6] = selItem->_subayasa;
                statVals[7] = selItem->_blunt;
                statVals[8] = selItem->_slash;
                statVals[9] = selItem->_stab;
                statVals[10] = selItem->_bash;
                statVals[11] = selItem->_shot;
                statVals[12] = selItem->_crush;
                statVals[13] = selItem->_blast;
                statVals[14] = selItem->_heal;
                statVals[15] = selItem->_force;
                for (statIdx = 0, valuePtr = statVals, labelPair = ((struct NamePair *)DAT_004cf8d0); statIdx < 16; statIdx++, valuePtr++, labelPair++) {
                    sprintf(valueBuf, ((char *)percent_d), *valuePtr);
                    beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                    beMessenger_AppendString(ctl->_messenger, ((char *)DAT_0051bab0));
                    beMessenger_AppendString(ctl->_messenger, labelPair->name);
                    beMessenger_AppendString(ctl->_messenger, valueBuf);
                    beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
                }
                beMessenger_SendNamed(ctl->_messenger, ((char *)DAT_0051b5d8), ((char *)DAT_0051bae8), 0, ((char *)DAT_0051b5e8));
                recordName = (char *)((int)beDataBase_GetRecordString(beMessenger_GetObject(ctl->_messenger, 0), selItem->_id, ((char *)DAT_0051baf0)));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)STWINFONT29));
                beMessenger_AppendString(ctl->_messenger, ((char * *)g_fontNames)[0]);
                beMessenger_AppendString(ctl->_messenger, recordName);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)TEXTSET));
                beMessenger_SelectGroup(ctl->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(ctl->_messenger, ((char *)STWINFONT29));
                beMessenger_AppendString(ctl->_messenger, ((char * *)g_fontNames)[0]);
                beMessenger_AppendString(ctl->_messenger, DISPON);
                beMessenger_DispatchSelected(ctl->_messenger, ((char *)SWITCH_2));
            }
        }
    }
}

void FUN_004313b0(beNDMWShopCtrlEvolve *arg0) {
    int temp_s0;
    int temp_s2_2;
    int temp_s3;
    beNDMWShinkaObjectList *temp_a5;
    beNDMWShinkaObject *temp_s2;

    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    temp_s0 = beMessenger_GetObject(arg0->_messenger, 0);
    temp_a5 = (beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)arg0->_shinkaCtrl)->_list;
    temp_s2 = (beNDMWShinkaObject *)((int *)temp_a5->_data)[arg0->_cursor + arg0->_nowPage * 8];
    beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], &DAT_0051bae8[0], 0, &DAT_0051b5e8[0]);
    temp_s3 = beMessenger_GetObject(arg0->_messenger, 0);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bb28[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    temp_s2_2 = arg0->_messenger;
    beMessenger_AppendString(temp_s2_2, ((int)beDataBase_GetRecordString(temp_s3, temp_s2->_id, &DAT_0051bb38[0])));
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bb48[0]);
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bb60[0]);
    FUN_00431670(arg0, (igObjectList *)(*(int *)((char *)(((void *)igProperty_GetRecordFolder(temp_s0, &DAT_0051bb78[0]))) + 12)));
    FUN_00431670(arg0, (igObjectList *)(*(int *)((char *)(((void *)igProperty_GetRecordFolder(temp_s0, &DAT_0051bb88[0]))) + 12)));
    FUN_00431670(arg0, (igObjectList *)(*(int *)((char *)(((void *)igProperty_GetRecordFolder(temp_s0, &DAT_0051bb90[0]))) + 12)));
    FUN_00431670(arg0, (igObjectList *)(*(int *)((char *)(((void *)igProperty_GetRecordFolder(temp_s0, &DAT_0051bba0[0]))) + 12)));
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b4a0[0]);
    FUN_00433120((beNDMWWindow *)arg0->_mother, arg0->_playerNo, 1);
}

void FUN_00431670(beNDMWShopCtrlEvolve *arg0, igObjectList *arg1) {
    int i;
    int off;
    beNDMWItemBase *o;
    beNDMWItemBase *p;
    i = 0;
    goto guard;
body:
    o = *(beNDMWItemBase **)(arg1->_data + off);
    if (o != 0) o->_isEquip = 0;
    p = *(beNDMWItemBase **)(arg1->_data + off);
    if (p != 0) {
        p->_refCount = (int)p->_refCount - 1;
        if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(p);
    }
    if (arg1->_count != 0 && i >= 0 && i < arg1->_count) *(beNDMWItemBase **)(arg1->_data + off) = 0;
    off += 4;
    i++;
cond:
    if (i < arg1->_count) goto body;
done:
    return;
guard:
    if (0 < arg1->_count) { off = 0; goto cond; }
    goto done;
}

void Gap__Bec__beNDMWShopCtrlDigilabo__vfunc_21(beNDMWShopCtrlDigilabo *self) {
    void *alloc;
    igObject *found;
    int i;
    int j;
    int idx;
    int *src;
    igIntList *l;
    igIntList *pl;

    switch (self->_st0) {
    default:
        return;
    case 0:
        self->_isDigimonChange = 0;
        self->_isWeaponChange = 0;
        FUN_004329d0(self);
        ALLOC_42f710(alloc, self)
        {
            igSmartPointer<beNDMWShopTitle00> spAC((beNDMWShopTitle00 *)FUN_003b3370(alloc));
        beNDMWWindow_BindContext(spAC.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, spAC.p);
        }
        ALLOC_42f710(alloc, self)
        {
            igSmartPointer<beNDMWStatusTitle03> spA8((beNDMWStatusTitle03 *)FUN_003b36f0(alloc));
        beNDMWWindow_BindContext(spA8.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, spA8.p);
        }
        ALLOC_42f710(alloc, self)
        {
            igSmartPointer<beNDMWShopTitle01> spA4((beNDMWShopTitle01 *)FUN_003b31b0(alloc));
        beNDMWWindow_BindContext(spA4.p, self, self->_insight, self->_playerNo, self->_entCode);
        ObjectList_AppendRetained(self->_subWindow, spA4.p);
        }
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                FUN_00433290(self);
                FUN_00433120((beNDMWWindow *)self, self->_playerNo, 0);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 1:
                beMessenger_SelectReceivers(self->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
                beMessenger_AppendString(self->_messenger, &DAT_0051b868[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b338[0]);
                if (((unsigned char)beMessenger_GetBool(self->_messenger, 0)) != 1) {
                    ALLOC_42f710(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect02> spA0((beNDMWShopSelect02 *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(spA0.p, self, self->_insight, self->_playerNo, PLN(self));
                    ObjectList_AppendRetained(self->_subWindow, spA0.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
                break;
            case 2:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    case 1:
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    case 2:
                        if (PLN(self) == 1) {
                            self->_st1 = 6;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        } else {
                            self->_st1 = 5;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        }
                        break;
                    default:
                    case 3:
                        self->_st1 = 6;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    }
                    self->_topMenu = self->_retCode;
                    return;
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                ALLOC_42f710(alloc, self)
                {
                    igSmartPointer<beNDMWShopCtrlEvolve> sp9C((beNDMWShopCtrlEvolve *)FUN_003b8860(alloc));
                beNDMWWindow_BindContext(sp9C.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, sp9C.p);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 1:
                        self->_isDigimonChange = 1;
                        self->_st1 = 3;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    }
                    FUN_00433290(self);
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 0:
                found = 0;
                i = 0;
                if (0 < SUBN(self)) {
                    do {
                        igObject *e = (igObject *)((int *)((igObjectList *)(*(int *)&self->_subWindow))->_data)[i];
                        if (e != 0 && igObject_IsKindOf(e, g_beNDMWStatusTitle01_metaObject[0]) != 0) {
                            found = e;
                        } else {
                            found = 0;
                        }
                        if (found != 0) break;
                        i += 1;
                    } while (i < SUBN(self));
                }
                if (found != 0) {
                    ((beNDMWStatusTitle01 *)found)->_playerNo = self->_playerNo;
                    FUN_00425e60(found);
                }
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 1:
                ALLOC_42f710(alloc, self)
                {
                    igSmartPointer<beNDMWStatusCtrlEquip> sp98((beNDMWStatusCtrlEquip *)FUN_003bace0(alloc));
                beNDMWWindow_BindContext(sp98.p, self, self->_insight, self->_playerNo, 1);
                ObjectList_AppendRetained(self->_subWindow, sp98.p);
                beNDMWWindow_PresentModelAtOrigin(sp98.p, &DAT_0051b318[0], 0, &DAT_0051b328[0], &DAT_0051ba28[0]);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 2:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 100:
                        self->_isWeaponChange = 1;
                        break;
                    }
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    FUN_00433290(self);
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectReceivers(self->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
                beMessenger_AppendString(self->_messenger, &DAT_0051b868[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b338[0]);
                if (((unsigned char)beMessenger_GetBool(self->_messenger, 0)) == 1) break;
                {
                    ALLOC_42f710(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect03> sp94((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(sp94.p, self, self->_insight, self->_playerNo, 0x4ED);
                    ObjectList_AppendRetained(self->_subWindow, sp94.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 1:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    ALLOC_42f710(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect02> sp90((beNDMWShopSelect02 *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(sp90.p, self, self->_insight, self->_playerNo, 0x4EE);
                    ObjectList_AppendRetained(self->_subWindow, sp90.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 2:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0:
                if (1 < PLN(self)) {
                    ALLOC_42f710(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect03> sp8C((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(sp8C.p, self, self->_insight, self->_playerNo, 0x4E2);
                    ObjectList_AppendRetained(self->_subWindow, sp8C.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                self->_st1 = 0;
                self->_st3 = 0;
                self->_st2 = 0;
                return;
            case 1:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    ALLOC_42f710(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect02> sp88((beNDMWShopSelect02 *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(sp88.p, self, self->_insight, self->_playerNo, -1);
                    ObjectList_AppendRetained(self->_subWindow, sp88.p);
                    pl = (igIntList *)self->_playerNoList;
                    j = 0;
                    if (0 < pl->_count) {
                        do {
                            src = &((int *)pl->_data)[j];
                            l = (igIntList *)((beNDMWShopSelect02 *)sp88.p)->_playerNoList;
                            idx = l->_count;
                            if (idx < l->_capacity) {
                                l->_count = countOf(l) + 1;
                            } else {
                                List_Resize(l, idx + 1, 4);
                            }
                            j += 1;
                            ((int *)l->_data)[idx] = *src;
                            pl = (igIntList *)self->_playerNoList;
                        } while (j < pl->_count);
                    }
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 2:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    default:
                        self->_playerNo = PL(self, self->_retCode);
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case -1:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 6:
            switch (self->_st2) {
            case 0:
                if (FUN_00432d30(self) != 0) {
                    self->_st2 = 2;
                    self->_st3 = 0;
                    return;
                }
                ALLOC_42f710(alloc, self)
                {
                    igSmartPointer<beNDMWShopSelect03> sp84((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                beNDMWWindow_BindContext(sp84.p, self, self->_insight, self->_playerNo, 0x4FB);
                ObjectList_AppendRetained(self->_subWindow, sp84.p);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                FUN_00432c90(self);
                int k = 0;
                if (0 < PLN(self)) {
                    do {
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, PL(self, k));
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        /* matching construct: the copied token is an expression temporary; a named local would take a higher stack slot than retail's */
                        beMessenger_SendNamed(self->_messenger, &DAT_0051bbc0[0], (StringList_CopyRetained(((Rec12 *)FUN_003a9310(beMessenger_GetObject(self->_messenger, 0), &DAT_0051bbb0[0]))->f12, 0)).p, PL(self, k), &((int *)DAT_0051b7e0)[0]);
                        k += 1;
                    } while (k < PLN(self));
                }
                break;
            case 1:
                if (SUBN(self) != self->_nowProcKazu) {
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                }
                break;
            case 2:
                ALLOC_42f710(alloc, self)
                {
                    igSmartPointer<beNDMWShopSelect03> sp80((beNDMWShopSelect03 *)FUN_003b4950(alloc));
                beNDMWWindow_BindContext(sp80.p, self, self->_insight, self->_playerNo, 0x4F3);
                ObjectList_AppendRetained(self->_subWindow, sp80.p);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 3:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    ALLOC_42f710(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect02> sp7C((beNDMWShopSelect02 *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(sp7C.p, self, self->_insight, self->_playerNo, 0x4F4);
                    ObjectList_AppendRetained(self->_subWindow, sp7C.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 4:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        ((beSystem *)FUN_00236f80(self->_insight, g_beSystem_metaObject[0]))->_isSResetEnable = 0;
                        break;
                    default:
                        self->_st1 = 5;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    }
                }
                break;
            case 5:
                FUN_00432c90(self);
                self->_isDemoRun = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b348[0], 0, &DAT_0051b358[0]);
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        if (self->_isDemoRun != 0) {
            beLua__RunNamedChunk(FUN_00236f80(self->_insight, g_beLua_metaObject[0]), &DAT_0051bbd0[0], &DAT_0051bbe8[0]);
            return;
        }
        break;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}



void FUN_004329d0(beNDMWShopCtrlDigilabo *self) {
    void *obj;
    RecB *rb;
    int i;
    int val;
    igObjectList *fold;
    void *alloc;
    int j;
    Item_4329d0 *it;
    int idx;

    beMessenger_SendGroup(self->_messenger, &DAT_0051b398[0], &DAT_0051b810[0]);
    igProperty_GetRecord(((void *)beMessenger_GetObject(self->_messenger, 0)), &DAT_0051bc40[0]);
    i = 0;
    do {
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
        beMessenger_AppendInt(self->_messenger, i);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
        obj = ((void *)beMessenger_GetObject(self->_messenger, 0));
        rb = ((RecB *)igProperty_GetRecordByte(obj, &DAT_0051b870[0]));
        if (rb->f12 != 0) {
            {
                igIntList *l = (igIntList *)self->_playerNoList;
                idx = l->_count;
                if (idx < l->_capacity) {
                    l->_count = countOf(l) + 1;
                } else {
                    List_Resize(l, idx + 1, 4);
                }
                ((int *)l->_data)[idx] = i;
            }
            {
                int idx2;
                igIntList *l;
                val = ((RecI *)igProperty_GetRecord(obj, &DAT_0051bac0[0]))->f12;
                l = (igIntList *)self->_digimonNoList;
                idx2 = l->_count;
                if (idx2 < l->_capacity) {
                    l->_count = countOf(l) + 1;
                } else {
                    List_Resize(l, idx2 + 1, 4);
                }
                ((int *)l->_data)[idx2] = val;
            }
            fold = igProperty_GetRecordFolder(obj, &DAT_0051bc48[0])->f12;
            alloc = igObject_GetAllocator(self);
            alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igSmartPointer<igIntList> lst((igIntList *)((int)FUN_002caa70(alloc)));
            j = 0;
            if (0 < fold->_count) {
                idx = 0;
                do {
                    it = *(Item_4329d0 **)&((char *)fold->_data)[idx];
                    if (it != 0) {
                        int idx3;
                        igIntList *l = lst.p;
                        val = it->f12;
                        idx3 = l->_count;
                        if (idx3 < l->_capacity) {
                            l->_count = countOf(l) + 1;
                        } else {
                            List_Resize(l, idx3 + 1, 4);
                        }
                        ((int *)l->_data)[idx3] = val;
                    }
                    j += 1;
                    idx += 4;
                } while (j < fold->_count);
            }
            ObjectList_AppendRetained(self->_wpuNoListList, lst.p);
        }
        i += 1;
    } while (i < 4);
}

void FUN_00432c90(beNDMWShopCtrlDigilabo *arg0) {
    int i;
    for (i = 0; i < ((igIntList *)arg0->_playerNoList)->_count; i++) {
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
        beMessenger_AppendInt(arg0->_messenger, ((int *)((igIntList *)arg0->_playerNoList)->_data)[i]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    }
}

/* Working list reference held across the List_Resize call. */
static inline int count(const igIntList *list) { return list->_count; }

int FUN_00432d30(beNDMWShopCtrlDigilabo *arg0) {
    int cn;
    int v1;
    igObjectList *folder;
    int j;
    igIntList *list;
    Rec2 *e;
    int v0;
    int k2;
    int al;
    int *rec;
    int o4;
    int o5;
    int off;
    void *obj;
    int c;
    int *src;
    igIntList *t;
    int al2;
    int w;
    igIntList *l;
    int k;
    int o2;
    int o3;
    int *arr;
    int s0;
    igIntList *l2;
    igIntList *t2;
    int r;
    if (arg0->_isDigimonChange != 0 || arg0->_isWeaponChange != 0) {
        cn = 0;
        off = 0;
        if (0 < ((igIntList *)arg0->_playerNoList)->_count) {
            do {
                s0 = *(int *)(((igIntList *)arg0->_playerNoList)->_data + off);
                beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                beMessenger_AppendInt(arg0->_messenger, s0);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                obj = (void *)beMessenger_GetObject(arg0->_messenger, 0);
                rec = (int *)((void *)igProperty_GetRecord(obj, &DAT_0051bac0[0]));
                if (rec[3] != *(int *)(((igIntList *)arg0->_digimonNoList)->_data + off)) return 1;
                folder = (igObjectList *)(((int *)((void *)igProperty_GetRecordFolder(obj, &DAT_0051bc48[0])))[3]);
                list = (igIntList *)*(int *)(((igIntList *)arg0->_wpuNoListList)->_data + off);
                al = ((int)igObject_GetAllocator(arg0));
                if (GPR_00554c14 != 0) {
                    al2 = al;
                } else {
                    al2 = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                }
                {
                igSmartPointer<igIntList> sp((igIntList *)FUN_002caa70(al2));
                v0 = 0;
                if (0 < list->_count) {
                    o2 = 0;
                    do {
                        src = (int *)((char *)list->_data + o2);
                        l = sp.p;
                        c = l->_count;
                        if (c < l->_capacity) {
                            l->_count = count(l) + 1;
                        } else {
                            List_Resize(l, c + 1, 4);
                        }
                        ((int *)l->_data)[c] = *src;
                        v0++;
                        o2 += 4;
                    } while (v0 < list->_count);
                }
                v1 = 0;
                j = 0;
                if (0 < folder->_count) {
                    o3 = 0;
                    do {
                        e = *(Rec2 **)(folder->_data + o3);
                        if (e != 0) {
                            w = e->f12;
                            v1++;
                            l = sp.p;
                            o4 = 0;
                            if (0 < CNT_432d30(l)) {
                                k = 0;
                                l2 = l;
                                do {
                                    int x = *(int *)(l2->_data + k);
                                    if (x != -1 && w == x) {
                                        if (CNT_432d30(l) != 0 && o4 >= 0 && o4 < CNT_432d30(l)) {
                                            ((int *)l->_data)[o4] = DAT_004cfa30[0];
                                        }
                                        break;
                                    }
                                    o4++;
                                    k += 4;
                                    l2 = l;
                                } while (o4 < CNT_432d30(l));
                            }
                        }
                        j++;
                        o3 += 4;
                    } while (j < folder->_count);
                }
                if (v1 != list->_count) {
                    return 1;
                }
                t = sp.p;
                k2 = 0;
                if (0 < CNT_432d30(t)) {
                    o5 = 0;
                    t2 = t;
                    do {
                        if (*(int *)(t2->_data + o5) != -1) {
                            return 1;
                        }
                        k2++;
                        o5 += 4;
                        t2 = t;
                    } while (k2 < CNT_432d30(t));
                }
                }
                cn = cn + 1;
                off += 4;
                r = ((igIntList *)arg0->_playerNoList)->_count > cn;
            } while (r);
        }
    }
    return 0;
}


void FUN_00433120(beNDMWWindow *arg0, int arg1, int arg2) {
    beNDMWWindow *var_s2;
    int var_s1;
    int var_s0;
    int var_v0;
    int w;
    beNDMWWindow *e;

    var_s2 = 0;
    var_s1 = 0;
    if (0 < ((igObjectList *)*(int *)&arg0->_subWindow)->_count) {
        var_s0 = 0;
        do {
            e = (beNDMWWindow *)((int *)((igObjectList *)arg0->_subWindow)->_data)[var_s1];
            if ((e != 0) && (igObject_IsKindOf(e, g_beNDMWStatusTitle01_metaObject[0]) != 0)) {
                var_s2 = e;
            } else {
                var_s2 = 0;
            }
            if (var_s2 != 0) break;
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < ((igObjectList *)arg0->_subWindow)->_count);
    }
    if (var_s2 == 0) {
        var_v0 = ((int)igObject_GetAllocator(arg0));
        if (GPR_00554c14 != 0) {
            w = var_v0;
        } else {
            w = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        }
        /* The new window is owned by the stack reference until the sub-window list has taken its own. */
        igSmartPointer<beNDMWStatusTitle01> created((beNDMWStatusTitle01 *)FUN_003b3ac0(w));
        beNDMWWindow_BindContext(created.p, arg0, arg0->_insight, arg1, 1);
        ObjectList_AppendRetained(arg0->_subWindow, (igObject *)created.p);
    } else {
        var_s2->_playerNo = arg1;
        FUN_00425fb0(var_s2);
    }
}

void FUN_00433290(void *window)
{
    beNDMWWindow_PresentModelAtOrigin(window, ((char *)DAT_0051b318), 0, ((char *)DAT_0051b868), ((char *)DAT_0051b620));
}

static inline int st2(const beNDMWShopCtrlEditBit *self) { return self->_st2; }

void Gap__Bec__beNDMWShopCtrlEditBit__vfunc_21(beNDMWShopCtrlEditBit *self) {
    char sp50[20];
    void *alloc;
    int obj;
    int s2v;
    int s1v;
    int s0v;
    int i;
    int mult;
    int cnt;
    bePadData *pad;
    int pa;
    int pb;
    int oldv;
    int v;
    int lim;
    int a2v;
    int rc;
    int h;

    switch (self->_st0) {
    default:
        return;
    case 0:
        switch (self->_entCode) {
        case 0:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051bc60[0], &DAT_0051b620[0]);
            INTERN_APPEND_4332d0(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b1c8[0])
            INTERN_APPEND_4332d0(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b1d0[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x515);
            INTERN_APPEND_4332d0(self->_textCloseTypeList, STWINFONT29)
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b548[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x550);
            break;
        case 1:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051bc80[0], &DAT_0051b620[0]);
            INTERN_APPEND_4332d0(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b1c8[0])
            INTERN_APPEND_4332d0(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b1d0[0])
            INTERN_APPEND_4332d0(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b1d8[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x55F);
            INTERN_APPEND_4332d0(self->_textCloseTypeList, STWINFONT29)
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b548[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x557);
            break;
        case 2:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051bc98[0], &DAT_0051b620[0]);
            INTERN_APPEND_4332d0(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND_4332d0(self->_textCloseNameList, &DAT_0051b1c8[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x562);
            break;
        }
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st2) {
        case 0:
            ALLOC(alloc, self)
            {
            igSmartPointer<beNDMWShopSelect34> spAC((beNDMWShopSelect34 *)FUN_003b45d0(alloc));
            beNDMWWindow_BindContext(spAC.p, self, self->_insight, self->_playerNo, self->_entCode);
            ObjectList_AppendRetained(self->_subWindow, spAC.p);
            }
            self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 1:
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
            beMessenger_AppendInt(self->_messenger, self->_playerNo);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
            obj = beMessenger_GetObject(self->_messenger, 0);
            self->_editBit = 0;
            s2v = ((int *)((igObjectList *)self->_subWindow)->_data)[0];
            s1v = W(((int)igProperty_GetRecord(obj, &DAT_0051b560[0])), 12);
            s0v = W(((int)igProperty_GetRecord(obj, &DAT_0051b568[0])), 12);
            switch (self->_entCode) {
            case 0:
                FUN_004402e0(s2v, self->_editBit, 1, &DAT_0051bca8[0]);
                v = 9999999 - s0v;
                s1v = s1v < v ? s1v : v;
                self->_editMax = s1v;
                FUN_00440110(s2v, self->_entCode, s0v);
                break;
            case 1:
                FUN_004402e0(s2v, self->_editBit, 1, &DAT_0051bcb8[0]);
                v = 9999999 - s1v;
                self->_editMax = s0v < v ? s0v : v;
                FUN_00440110(s2v, self->_entCode, s1v);
                FUN_004402e0(s2v, s0v, 1, &DAT_0051bcc8[0]);
                break;
            case 2:
                FUN_004402e0(s2v, self->_editBit, 1, &DAT_0051bca8[0]);
                v = 999999999 - s1v;
                s1v = s1v < v ? s1v : v;
                self->_editMax = s1v;
                break;
            }
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 2:
            if (((igObjectList *)self->_subWindow)->_count == self->_nowProcKazu) {
                rc = self->_retCode;
                if (rc != -1) {
                    if (self->_st3 == rc) {
                        beMessenger_SendNamed(self->_messenger, &DAT_0051bcd8[0], &DAT_0051bce8[0], self->_playerNo, &DAT_0051bcf8[0]);
                        if (beMessenger_GetBool(self->_messenger, 0) & 0xFF) {
                            pad = bePadManager_GetPadForPlayer(self->_padManager, self->_playerNo);
                            pa = pad->_trigger;
                            pb = pad->_repeat;
                            cnt = pad->_lTrg | pad->_lRpt;
                            bool up = true;
                            if (!(cnt & 1) && !((pa | pb) & 0x10)) up = false;
                            bool dn = true;
                            if (!(cnt & 4) && !((pa | pb) & 0x40)) dn = false;
                            if (up || dn) {
                                oldv = self->_editBit;
                                mult = 1;
                                a2v = 7 - self->_retCode;
                                for (i = a2v; i > 1; i--) mult *= 10;
                                if (up) {
                                    self->_editBit = self->_editBit + mult;
                                    lim = self->_editMax;
                                    if (self->_editBit >= lim) self->_editBit = lim;
                                } else if (dn) {
                                    self->_editBit = self->_editBit - mult;
                                    if (self->_editBit <= 0) self->_editBit = 0;
                                }
                                v = self->_editBit;
                                if (v != oldv) {
                                    h = ((int *)((igObjectList *)self->_subWindow)->_data)[0];
                                    switch (self->_entCode) {
                                    case 2:
                                    case 0:
                                        FUN_004402e0(h, v, a2v, &DAT_0051bca8[0]);
                                        break;
                                    case 1:
                                        FUN_004402e0(h, v, a2v, &DAT_0051bcb8[0]);
                                        break;
                                    }
                                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b888[0]);
                                    beMessenger_AppendString(self->_messenger, &DAT_0051bd08[0]);
                                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b8a0[0]);
                                    return;
                                }
                            }
                        }
                    } else {
                        h = ((int *)((igObjectList *)self->_subWindow)->_data)[0];
                        a2v = 7 - rc;
                        switch (self->_entCode) {
                        case 2:
                        case 0:
                            FUN_004402e0(h, self->_editBit, a2v, &DAT_0051bca8[0]);
                            break;
                        case 1:
                            FUN_004402e0(h, self->_editBit, a2v, &DAT_0051bcb8[0]);
                            break;
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                }
            } else {
                if (self->_retCode == -1 || self->_editBit <= 0) {
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                } else {
                    ((beNDMWWindow *)self->_mother)->_retCode = self->_editBit;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b548[0]);
                    beMessenger_AppendString(self->_messenger, DISPOFF);
                    beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
                    return;
                }
            }
            break;
        case 3:
            ALLOC(alloc, self)
            {
            igSmartPointer<beNDMWShopSelect00> spA8((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
            beNDMWWindow_BindContext(spA8.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, spA8.p);
            switch (self->_entCode) {
            case 0:
                ((beNDMWShopSelect00 *)spA8.p)->_entCode = 0x552;
                break;
            case 1:
                ((beNDMWShopSelect00 *)spA8.p)->_entCode = 0x559;
                break;
            case 2:
                ((beNDMWShopSelect00 *)spA8.p)->_entCode = 0x7A9;
                break;
            }
            }
            self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 4:
            if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                if (self->_entCode == 2) {
                    self->_st2 = st2(self) + 1;
                    self->_st3 = 0;
                    return;
                }
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                return;
            }
            break;
        case 5:
            ALLOC(alloc, self)
            {
            igSmartPointer<beNDMWShopSelect01> spA4((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
            beNDMWWindow_BindContext(spA4.p, self, self->_insight, self->_playerNo, 0x7AA);
            ObjectList_AppendRetained(self->_subWindow, spA4.p);
            }
            self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 6:
            if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                if (self->_retCode != 0) {
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                }
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        i = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        do {
            sprintf(&sp50[0], &DAT_0051bca8[0], i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, &DAT_0051bd18[0]);
            beMessenger_AppendString(self->_messenger, &sp50[0]);
            beMessenger_AppendString(self->_messenger, DISPOFF);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            sprintf(&sp50[0], &DAT_0051bcb8[0], i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, &DAT_0051bd18[0]);
            beMessenger_AppendString(self->_messenger, &sp50[0]);
            beMessenger_AppendString(self->_messenger, DISPOFF);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            sprintf(&sp50[0], &DAT_0051bcc8[0], i);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, &DAT_0051bd18[0]);
            beMessenger_AppendString(self->_messenger, &sp50[0]);
            beMessenger_AppendString(self->_messenger, DISPOFF);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            i += 1;
        } while (i < 7);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

static inline int st0_434790(const beNDMWShopCtrlSell *ctrl) { return ctrl->_st0; }

void Gap__Bec__beNDMWShopCtrlSell__vfunc_21(beNDMWShopCtrlSell *self) {
    void *alloc;
    igObjectList *devices;
    const igObjectList *disks;
    Item_434790 *item;
    bool hasDevice;
    bool hasDisk;
    int i;
    int rec;

    switch (st0_434790(self)) {
    case 0:
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
        rec = beMessenger_GetObject(self->_messenger, 0);
        devices = igProperty_GetRecordFolder(rec, &DAT_0051b528[0])->f12;
        disks = igProperty_GetRecordFolder(rec, &DAT_0051b6c0[0])->f12;
        hasDevice = 0;
        if (devices->_count > 0) {
            hasDevice = 1;
        }
        hasDisk = 0;
        for (i = 0; i < disks->_count; i++) {
            item = ((Item_434790 **)disks->_data)[i];
            if (item != 0 && item->f20 > 0) {
                hasDisk = 1;
                break;
            }
        }
        if (hasDevice || hasDisk) {
            self->_st1 = 0;
            self->_st3 = 0;
            self->_st2 = 0;
            if (hasDevice == 0) {
                self->_st3 = 1;
            } else if (hasDisk == 0) {
                self->_st3 = 2;
            }
        } else {
            self->_st1 = 3;
            self->_st3 = 0;
            self->_st2 = 0;
        }
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelectB0> sp5C((beNDMWShopSelectB0 *)FUN_003b3f40(alloc));
                beNDMWWindow_BindContext(sp5C.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, sp5C.p);
                switch (self->_st3) {
                case 1: {
                    ALLOC(alloc, self)
                    igSmartPointer<igBoolList> sp58((igBoolList *)FUN_002cb0d0(alloc));
                    { igBoolList *l = (igBoolList *)sp58.p; PUSH_BOOL(l, GPR_00554a50) }
                    { igBoolList *l = (igBoolList *)sp58.p; PUSH_BOOL(l, GPR_00554a54) }
                    {
                        igBoolList *l = (igBoolList *)sp58.p;
                        beNDMWShopSelect00 *w = (beNDMWShopSelect00 *)sp5C.p;
                        if (l != 0) {
                            l->_refCount = l->_refCount + 1;
                        }
                        {
                            igObject *old = (igObject *)w->_decideList;
                            RELEASE(old)
                        }
                        w->_decideList = (int)l;
                    }
                    break;
                }
                case 2: {
                    ALLOC(alloc, self)
                    igSmartPointer<igBoolList> sp54((igBoolList *)FUN_002cb0d0(alloc));
                    { igBoolList *l = (igBoolList *)sp54.p; PUSH_BOOL(l, GPR_00554a58) }
                    { igBoolList *l = (igBoolList *)sp54.p; PUSH_BOOL(l, GPR_00554a5c) }
                    {
                        igBoolList *l = (igBoolList *)sp54.p;
                        beNDMWShopSelect00 *w = (beNDMWShopSelect00 *)sp5C.p;
                        if (l != 0) {
                            l->_refCount = l->_refCount + 1;
                        }
                        {
                            igObject *old = (igObject *)w->_decideList;
                            RELEASE(old)
                        }
                        w->_decideList = (int)l;
                    }
                    break;
                }
                }
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3d8[0]);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, STWINFONT29);
                    beMessenger_AppendString(self->_messenger, g_fontName1[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3d8[0]);
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 1:
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    default:
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
        case 2:
            switch (self->_st2) {
            case 0:
                if (self->_st1 == 1) {
                    ALLOC(alloc, self)
                    igSmartPointer<beNDMWShopCtrlDeviceSell> sp50((beNDMWShopCtrlDeviceSell *)FUN_003b70e0(alloc));
                    beNDMWWindow_BindContext(sp50.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, sp50.p);
                } else {
                    ALLOC(alloc, self)
                    igSmartPointer<beNDMWShopCtrlDiskSell> sp4C((beNDMWShopCtrlDiskSell *)FUN_003b6e60(alloc));
                    beNDMWWindow_BindContext(sp4C.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, sp4C.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_st0 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> sp48((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(sp48.p, self, self->_insight, self->_playerNo, 0x628);
                ObjectList_AppendRetained(self->_subWindow, sp48.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    ((beNDMWShopCtrlSell *)self->_mother)->_retCode = -1;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

void FUN_00435250(int *arg0, int arg1) {
    Tbl sp30;
    float v[3];
    if (arg1 > -1) {
        sp30 = DAT_004cfa40;
        beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, DAT_0051b7d8);
        if (beMessenger_GetBool(arg0[3], 0) != 0) {
            beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, (char *)sp30.s[arg1]);
            return;
        }
        beMessenger_SelectReceivers(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0);
        beMessenger_AppendString(arg0[3], sp30.s[arg1]);
        v[2] = 0;
        v[0] = -121.0f;
        v[1] = 128.0f;
        beMessenger_AppendVec3(arg0[3], v);
        beMessenger_DispatchSelected(arg0[3], DAT_0051b7e0);
        return;
    }
    beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, DAT_0051b7d8);
    if (beMessenger_GetBool(arg0[3], 0) != 0) {
        beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, ((char *)DAT_0051b620));
    }
}

void Gap__Bec__beNDMWShopCtrlDeviceSell__vfunc_21(beNDMWShopCtrlDeviceSell *self)
{
    switch (self->_st0) {
    case 0: {
        int vB[3];
        int vA[3];
        int i;
        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051b610, 0, DAT_0051bd50, DAT_0051b620);
        FUN_004367c0(self);
        vA[0] = 0x436C0000;
        vA[2] = 0;
        vA[1] = 0x41C80000;
        vB[0] = 0xC3120000;
        vB[1] = 0x41C80000;
        vB[2] = 0;
        ((DummyVirtual *)self)->v24(vB, vA);
        APPENDSTR(self->_textCloseTypeList, STWINFONT29)
        APPENDSTR(self->_textCloseNameList, DAT_0051b548)
        beNDMWWindow_RunMessageScript(self, DAT_0051b3b0, 0x676);
        APPENDSTR(self->_textCloseTypeList, DAT_0051b668)
        {
            const char *name = g_fontNames[0];
            APPENDSTR(self->_textCloseNameList, name)
        }
        beNDMWWindow_RunMessageScript(self, DAT_0051b3b0, 0x3E8);
        i = 0;
        {
            const char **p = g_fontNames;
            do {
                beNDMWWindow_QueueText(self, STWINFONT14, *p, DAT_0051b590, DAT_0051b598);
                beNDMWWindow_QueueText(self, STWINFONT17, *p, DAT_0051b590, DAT_0051b460);
                i++;
                p += 1;
            } while (i < 12);
        }
        beNDMWWindow_QueueText(self, STWINFONT30, g_fontNames[0], DAT_0051b590, DAT_0051b460);
        beNDMWWindow_QueueText(self, STWINFONT30, g_fontName1[0], DAT_0051b590, DAT_0051b460);
        self->_cursor = 0;
        self->_nowPage = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 4;
        self->_st3 = 0;
        self->_st2 = 0;
    }
    case 1:
        switch (self->_st1) {
        case 4:
            switch (self->_st2) {
            case 0: {
                void *alloc;
                ALLOC(alloc, self)
                {
                    igSmartPointer<beNDMWStatusSelectE1> selectWin((beNDMWStatusSelectE1 *)FUN_003b51b0(alloc));
                    self->_retCode = self->_cursor;
                    beNDMWWindow_BindContext(selectWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, selectWin.p);
                    { beNDMWStatusSelectE1 *w = selectWin.p; w->_offsetPos[0] = -121.0f; w->_offsetPos[1] = 128.0f; w->_offsetPos[2] = 0.0f; }
                    selectWin.p->_startPoint = self->_cursor;
                    beNDMWWindow_QueueText(selectWin.p, STWINFONT29, g_fontNames[0], DAT_0051b590, DAT_0051b598);
                    selectWin.p->_selectMax = FUN_004367c0(self);
                    {
                        igObject *d = (igObject *)self->_decideList;
                        beNDMWStatusSelectE1 *w = selectWin.p;
                        igObject *o;
                        if (d) d->_refCount = d->_refCount + 1;
                        o = (igObject *)w->_decideList;
                        REL_42a2e0(o)
                        w->_decideList = (int)d;
                    }
                }
                self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            }
            case 1:
                FUN_00436060(self, 1, 1);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 2: {
                igObjectList *sub = (igObjectList *)self->_subWindow;
                if (sub->_count == self->_nowProcKazu) {
                    int rc = self->_retCode;
                    if (rc != -1) {
                        if (rc != self->_st3) {
                            FUN_00436060(self, 0, 1);
                            self->_st3 = self->_retCode;
                            return;
                        }
                        {
                            beNDMWStatusSelectE1 *w = (beNDMWStatusSelectE1 *)*(int *)sub->_data;
                            if (beNDMWWindowSelect_CanRequestFO2TOP(w, 5, sub) != 0) {
                                bool flag = false;
                                if (((DummyVirtual *)self)->v25() != 0) {
                                    flag = true;
                                } else if (((DummyVirtual *)self)->v26() != 0) {
                                    flag = true;
                                }
                                if (flag) {
                                    igObject *d;
                                    igObject *o;
                                    w->_st0 = 4;
                                    w->_st3 = 0;
                                    w->_st2 = 0;
                                    w->_st1 = 0;
                                    w->_selectMax = FUN_004367c0(self);
                                    d = (igObject *)self->_decideList;
                                    if (d) d->_refCount = d->_refCount + 1;
                                    o = (igObject *)w->_decideList;
                                    REL_42a2e0(o)
                                    w->_decideList = (int)d;
                                    self->_st2 = 1;
                                    self->_st3 = 0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    switch (self->_retCode) {
                    default:
                        self->_st1 = 5;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_cursor = self->_retCode;
                        FUN_00435250((int *)self->_mother, self->_cursor);
                        return;
                    case -1:
                        ((beNDMWWindow *)self->_mother)->_retCode = -1;
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0: {
                void *alloc;
                ALLOC(alloc, self)
                {
                    igSmartPointer<beNDMWShopSelect00> confirmWin((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                    beNDMWWindow_BindContext(confirmWin.p, self, self->_insight, self->_playerNo, 0x619);
                    ObjectList_AppendRetained(self->_subWindow, confirmWin.p);
                }
            }
                self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    void *alloc;
                    ALLOC(alloc, self)
                    {
                        igSmartPointer<beNDMWShopSelect01> noticeWin((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                        beNDMWWindow_BindContext(noticeWin.p, self, self->_insight, self->_playerNo, 0x61A);
                        ObjectList_AppendRetained(self->_subWindow, noticeWin.p);
                    }
                    self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 2:
                if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    int rc = self->_retCode;
                    switch (rc) {
                    case 0: {
                        int obj;
                        igIntList *fold;
                        int total;
                        int idx;
                        int money;
                        int price;
                        int ins;
                        int item;
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3e8);
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        fold = (igIntList *)igProperty_GetRecordFolder(obj, DAT_0051b528)->f12;
                        idx = self->_cursor + self->_nowPage * 12;
                        if (idx < fold->_count) {
                            ins = (int)FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
                            item = ((int *)fold->_data)[idx];
                            price = beNDMWItemRevisionPocketBase_GetPrice(item, ins, DAT_0051bd70);
                            money = igProperty_GetRecord(obj, DAT_0051b560)->f12;
                            money = money + price;
                            if (money > 9999999) money = 9999999;
                            igProperty_GetRecord(obj, DAT_0051b560)->f12 = money;
                            ObjectList_RemoveFirstRetained(fold, (void *)item, 0);
                            beMessenger_SelectGroup(self->_messenger, DAT_0051b498);
                            beMessenger_AppendInt(self->_messenger, self->_playerNo);
                            beMessenger_DispatchSelected(self->_messenger, DAT_0051b4a0);
                            total = fold->_count;
                            if (total <= 0) {
                                self->_st0 = self->_st0 + 1;
                                self->_st3 = 0;
                                self->_st2 = 0;
                                self->_st1 = 0;
                            } else {
                                if (idx >= total) {
                                    if (self->_cursor == 0) {
                                        if (self->_nowPage > 0) self->_nowPage = self->_nowPage - 1;
                                    } else {
                                        self->_cursor = self->_cursor - 1;
                                    }
                                }
                                if (self->_nowPage == 0)
                                    beMessenger_SendNamed(self->_messenger, DAT_0051b308, DAT_0051b630, 0, DAT_0051b640);
                                if (fold->_count <= (self->_nowPage + 1) * 12)
                                    beMessenger_SendNamed(self->_messenger, DAT_0051b308, DAT_0051b650, 0, DAT_0051b640);
                            }
                        } else {
                            self->_st0 = self->_st0 + 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            self->_st1 = 0;
                        }
                        break;
                    }
                    case 1:
                        break;
                    }
                    self->_st1 = 4;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    FUN_00435250((int *)self->_mother, -1);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        FUN_004369f0((O_4369f0 *)self);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

void FUN_00436060(beNDMWShopCtrlDeviceSell *self, int full, unsigned char sel)
{
    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
    igDataList *folder = ((RecordFolder *)((char *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b528[0])))->list;
    igSmartPointer<igStringObj> str((igStringObj *)((int *)FUN_00236f80(self->_insight, g_beSystem_metaObject[0]))[18]);
    if (str.p != 0) str.p->_refCount = str.p->_refCount + 1;
    char numbuf[2];
    char nb2[2];
    char nb3[2];
    char name[16];
    V3 vA;
    V3 vB;
    if (full != 0) {
        int i = 0;
        do {
            int idx = i + self->_nowPage * 12;
            const char *s;
            if (idx < folder->_count) {
                void *c = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
                beNDMWItemBase *o = *(beNDMWItemBase **)(folder->_data + idx * 4);
                FUN_0030b3c0(str.p, beNDMWItemBase_GetRecordString(o, c, NAME_2));
                if (o->_isEquip != 0) { igStringObj *t = str.p; FUN_0030b460(t, &DAT_0051bd78[0], 0, strlen(&DAT_0051bd78[0])); }
                else { igStringObj *t = str.p; FUN_0030b460(t, &DAT_0051bd80[0], 0, strlen(&DAT_0051bd80[0])); }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, &((char *)STWINFONT14)[0]);
                beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
                {
                    int m = self->_messenger;
                    char *t0 = (char *)str.p->_buffer;
                    char *t;
                    if (t0 == 0) t = DAT_004c22f0[0]; else t = t0;
                    beMessenger_AppendString(m, t);
                }
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                sprintf(name, percent_d, beNDMWItemRevisionPocketBase_GetPrice(o, c, &DAT_0051bd70[0]));
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, &((char *)STWINFONT17)[0]);
                beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                beNDMWItemBase_GetRevisionColor(&vA, o);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, &((char *)STWINFONT14)[0]);
                beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
                vB = vA;
                beMessenger_AppendVec3(self->_messenger, (float *)&vB);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b9f8[0]);
                if (*(unsigned char *)(((igUnsignedCharList *)self->_decideList)->_data + i) != 0) {
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, &((char *)STWINFONT17)[0]);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3d8[0]);
                } else {
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                    beMessenger_AppendString(self->_messenger, &((char *)STWINFONT17)[0]);
                    beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b800[0]);
                }
                s = &DISPON[0];
            } else {
                s = &((char *)DISPOFF)[0];
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, &((char *)STWINFONT14)[0]);
            beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
            beMessenger_AppendString(self->_messenger, s);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, &((char *)STWINFONT17)[0]);
            beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[i]);
            beMessenger_AppendString(self->_messenger, s);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            i++;
        } while (i < 12);
        numbuf[1] = 0;
        numbuf[0] = self->_nowPage + 0x31;
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, &((char *)STWINFONT30)[0]);
        beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
        beMessenger_AppendString(self->_messenger, numbuf);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET);
        numbuf[0] = self->_maxPage + 0x30;
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, &((char *)STWINFONT30)[0]);
        beMessenger_AppendString(self->_messenger, g_fontName1[0]);
        beMessenger_AppendString(self->_messenger, numbuf);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET);
    }
    if (sel) {
        int rc = self->_retCode; int pg = self->_nowPage * 12; int idx = pg + rc;
        const char *s;
        if (idx < folder->_count) {
            char *txt;
            void *c2 = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
            beNDMWItemBase *o = *(beNDMWItemBase **)(folder->_data + idx * 4);
            int kind;
            txt = beNDMWItemBase_GetRecordString(o, c2, TXT);
            kind = o->_kindNo;
            if (kind == 0) {
                if (o->_recNo != 0x114) {
                    nb2[1] = 0;
                    nb2[0] = ((beNDMWItemBlueArmor *)o)->_pocket + 0x30;
                    FUN_0030b3c0(str.p, txt);
                    {
                        int t = (int)str.p;
                        int n = ((igStringObj *)t)->_length;
                        FUN_0030b460((igStringObj *)t, nb2, n, strlen(nb2));
                    }
                    { char *x = (char *)str.p->_buffer; txt = (x == 0) ? DAT_004c22f0[0] : x; }
                }
            } else if (kind == 1 && o->_recNo != 0x1f) {
                nb3[1] = 0;
                nb3[0] = ((beNDMWItemBlueArmor *)o)->_pocket + 0x30;
                FUN_0030b3c0(str.p, txt);
                {
                    int t = (int)str.p;
                    int n = ((igStringObj *)t)->_length;
                    FUN_0030b460((igStringObj *)t, nb3, n, strlen(nb3));
                }
                { char *x = (char *)str.p->_buffer; txt = (x == 0) ? DAT_004c22f0[0] : x; }
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, &((char *)STWINFONT29)[0]);
            beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
            beMessenger_AppendString(self->_messenger, txt);
            beMessenger_DispatchSelected(self->_messenger, TEXTSET);
            s = &DISPON[0];
        } else {
            s = &((char *)DISPOFF)[0];
        }
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, &((char *)STWINFONT29)[0]);
        beMessenger_AppendString(self->_messenger, ((char * *)g_fontNames)[0]);
        beMessenger_AppendString(self->_messenger, s);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
    }
}

int FUN_004367c0(beNDMWShopCtrlDeviceSell *self) {
    Folder *fold; int n; int v; int rem; int rows; int i; int idx; int c; Obj *o; bool mark; int k; igCharList *l;
    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
    fold = *(Folder **)(((char *)igProperty_GetRecordFolder(((void *)beMessenger_GetObject(self->_messenger, 0)), &DAT_0051b528[0])) + 12);
    n = fold->count;
    if (n % 12 != 0) v = n / 12 + 1; else v = n / 12;
    self->_maxPage = v;
    rem = n - self->_nowPage * 12;
    rows = (rem >= 12) ? 12 : rem % 12;
    i = 0;
    ((igCharList *)self->_decideList)->_count = 0;
    do {
        idx = i + self->_nowPage * 12;
        if (idx < n) {
            c = ((int)FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]));
            o = fold->items[idx];
            mark = true;
            if (o->flag != 0) mark = false;
            else if (beNDMWItemRevisionPocketBase_GetPrice(o, c, &DAT_0051bd70[0]) <= 0) mark = false;
            l = (igCharList *)self->_decideList;
            k = l->_count;
            if (k < l->_capacity) l->_count = k + 1; else List_Resize(l, k + 1, 1);
            *(char *)(k + (int)l->_data) = mark;
        }
        i++;
    } while (i < 12);
    return rows;
}

void FUN_004369f0(O_4369f0 *arg0) {
    int i;
    int **p = ((int * *)g_fontNames);
    for (i = 0; i < 12; i++) {
        beMessenger_SelectGroup(arg0->m, TEXTCTL_3);
        beMessenger_AppendString(arg0->m, STWINFONT14);
        beMessenger_AppendString(arg0->m, *p);
        beMessenger_DispatchSelected(arg0->m, &DAT_0051b3d8[0]);
        beMessenger_SelectGroup(arg0->m, TEXTCTL_3);
        beMessenger_AppendString(arg0->m, STWINFONT17);
        beMessenger_AppendString(arg0->m, *p);
        beMessenger_DispatchSelected(arg0->m, &DAT_0051b3d8[0]);
        p++;
    }
}

void Gap__Bec__beNDMWShopCtrlDiskSell__vfunc_21(beNDMWShopCtrlDiskSell *self) {
    int vA[3];
    int vB[3];
    void *alloc;
    igObjectList *temp_s3;
    igObjectList *fa;
    Item_434790 *rc;
    int folder;
    int i;
    int j;
    int obj;
    igObjectList *fb;
    int newv;
    int cost;
    int tot;
    int rec;
    int row;
    char **fp;
    unsigned char *dst;
    unsigned char val;

    switch (self->_st0) {
    default:
        return;
    case 0:
        beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051b618[0], &DAT_0051b620[0]);
        vA[0] = 0xC3120000;
        vA[1] = 0x41C80000;
        vA[2] = 0;
        beNDMWWindow_PresentModel(self, &DAT_0051b630[0], 0, &DAT_0051b640[0], &DAT_0051b620[0], &vA[0]);
        vB[0] = 0x436C0000;
        vB[1] = 0x41C80000;
        vB[2] = 0;
        beNDMWWindow_PresentModel(self, &DAT_0051b650[0], 0, &DAT_0051b640[0], &DAT_0051b620[0], &vB[0]);
        INTERN_APPEND(self->_textCloseTypeList, STWINFONT29)
        INTERN_APPEND(self->_textCloseNameList, &DAT_0051b548[0])
        INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b668[0])
        INTERN_APPEND(self->_textCloseNameList, ((char * *)g_fontNames)[0])
        beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x3E9);
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
        temp_s3 = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12;
        i = 0;
        if (0 < temp_s3->_count) {
            fp = &((char * *)g_fontNames)[0];
            do {
                beNDMWWindow_QueueText(self, STWINFONT14, *fp, &DAT_0051b590[0], &DAT_0051b598[0]);
                beNDMWWindow_QueueText(self, &DAT_0051bd88[0], *fp, &DAT_0051b590[0], &DAT_0051bd98[0]);
                beNDMWWindow_QueueText(self, STWINFONT17, *fp, &DAT_0051b590[0], &DAT_0051b460[0]);
                i += 1;
                fp += 1;
            } while (i < temp_s3->_count);
        }
        self->_cursor = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 6;
        self->_st3 = 0;
        self->_st2 = 0;
    case 1:
        switch (self->_st1) {
        case 6:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051bda0[0]);
                FUN_00435250((int *)self->_mother, -1);
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWStatusSelectE1> spBC((beNDMWStatusSelectE1 *)FUN_003b51b0(alloc));
                self->_retCode = self->_cursor;
                beNDMWWindow_BindContext(spBC.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, spBC.p);
                { beNDMWStatusSelectE1 *w = (beNDMWStatusSelectE1 *)spBC.p; w->_offsetPos[0] = -121.0f; w->_offsetPos[1] = 128.0f; w->_offsetPos[2] = 0.0f; }
                ((beNDMWStatusSelectE1 *)spBC.p)->_startPoint = self->_cursor;
                beNDMWWindow_QueueText(spBC.p, STWINFONT29, ((char * *)g_fontNames)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                fa = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12;
                ((beNDMWStatusSelectE1 *)spBC.p)->_selectMax = fa->_count;
                ALLOC(alloc, self)
                igSmartPointer<igBoolList> spB8((igBoolList *)FUN_002cb0d0(alloc));
                j = 0;
                if (0 < fa->_count) {
                    do {
                        if (((Item_434790 **)fa->_data)[j]->f20 > 0) {
                            { int idx; igBoolList *l = (igBoolList *)spB8.p; idx = l->_count;
                            if (idx < l->_capacity) {
                                l->_count = idx + 1;
                            } else {
                                List_Resize(l, idx + 1, 1);
                            }
                            ((unsigned char *)l->_data)[idx] = GPR_00554a60; }
                        } else {
                            { int idx; igBoolList *l = (igBoolList *)spB8.p; idx = l->_count;
                            if (idx < l->_capacity) {
                                l->_count = idx + 1;
                            } else {
                                List_Resize(l, idx + 1, 1);
                            }
                            ((unsigned char *)l->_data)[idx] = GPR_00554a64; }
                        }
                        j += 1;
                    } while (j < fa->_count);
                }
                {
                    igBoolList *l2 = (igBoolList *)spB8.p;
                    beNDMWStatusSelectE1 *w = (beNDMWStatusSelectE1 *)spBC.p;
                    if (l2 != 0) {
                        l2->_refCount = l2->_refCount + 1;
                    }
                    { igObject *old = (igObject *)w->_decideList; REL_42a2e0(old) }
                    w->_decideList = (int)l2;
                }
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x676);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                FUN_00437ae0(self, 1, 1);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 2:
                if (((beNDMWWindowList *)self->_subWindow)->_count == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            FUN_00437ae0(self, 0, 1);
                            self->_st3 = self->_retCode;
                            return;
                        }
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_st1 = 7;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_cursor = self->_retCode;
                        FUN_00435250((int *)self->_mother, self->_cursor);
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        self->_maxSell = ((Item_434790 **)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12->_data)[self->_cursor]->f20;
                        if (self->_maxSell == 0) {
                            self->_st1 = 6;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            return;
                        }
                        break;
                    }
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 7:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051bdb0[0]);
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect52> spB4((beNDMWShopSelect52 *)FUN_003b4410(alloc));
                beNDMWWindow_BindContext(spB4.p, self, self->_insight, self->_playerNo, self->_maxSell);
                ObjectList_AppendRetained(self->_subWindow, spB4.p);
                { beNDMWShopSelect52 *w = (beNDMWShopSelect52 *)spB4.p; w->_offsetPos[0] = 52.0f; w->_offsetPos[1] = -104.0f; w->_offsetPos[2] = 0.0f; }
                INTERN_APPEND(((beNDMWShopSelect52 *)spB4.p)->_textCloseTypeList, STWINFONT29)
                INTERN_APPEND(((beNDMWShopSelect52 *)spB4.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x624);
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x5E1);
                self->_retCode = self->_maxSell - 1;
                FUN_00437f50(self);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            FUN_00437f50(self);
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_st1 = 8;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_kazu = self->_maxSell - self->_retCode;
                        return;
                    }
                    FUN_00438050(self);
                    self->_st1 = 6;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 8:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                igSmartPointer<beNDMWShopSelect00> spB0((beNDMWShopSelect00 *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(spB0.p, self, self->_insight, self->_playerNo, 0x619);
                ObjectList_AppendRetained(self->_subWindow, spB0.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    ALLOC(alloc, self)
                    {
                    igSmartPointer<beNDMWShopSelect01> spAC((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                    beNDMWWindow_BindContext(spAC.p, self, self->_insight, self->_playerNo, 0x61A);
                    ObjectList_AppendRetained(self->_subWindow, spAC.p);
                    }
                    self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 2:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    FUN_00438050(self);
                    switch (self->_retCode) {
                    case 0:
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        fb = igProperty_GetRecordFolder(obj, &DAT_0051b6c0[0])->f12;
                        cost = self->_tanka * self->_kazu;
                        tot = W(((int)igProperty_GetRecord(obj, &DAT_0051b560[0])), 12);
                        tot = tot + cost;
                        if (tot > 9999999) {
                            tot = 9999999;
                        }
                        W(((int)igProperty_GetRecord(obj, &DAT_0051b560[0])), 12) = tot;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b498[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b4a0[0]);
                        rc = ((Item_434790 **)fb->_data)[self->_cursor]; { unsigned int q = rc->f20; tot = q - self->_kazu; rc->f20 = tot; }
                        break;
                    case 1:
                        break;
                    }
                    self->_st1 = 6;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        FUN_00435250((int *)self->_mother, -1);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

void FUN_00437ae0(beNDMWShopCtrlDiskSell *arg0, int arg1, int arg2) {
    char spA0[28];
    char spBC[2];
    igObjectList *temp_s6;
    int temp_s7;
    int i;
    beNDMWItemDisk *it;
    char *s;
    int off;
    char **p;

    beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
    temp_s6 = *(igObjectList **)((char *)((void *)igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051b6c0)) + 12);
    temp_s7 = ((int)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0]));
    if (arg1 != 0) {
        i = 0;
        if (i < temp_s6->_count) {
            off = 0;
            p = ((char * *)g_fontNames);
            do {
                it = *(beNDMWItemDisk **)((char *)temp_s6->_data + off);
                s = beNDMWItemBase_GetRecordString(it, temp_s7, NAME_2);
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT14));
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, s);
                beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
                spBC[0] = it->_kazu + 0x30;
                spBC[1] = 0;
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, ((char *)DAT_0051bd88));
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, spBC);
                beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
                sprintf(spA0, percent_d, beNDMWItemRevisionPocketBase_GetPrice(it, temp_s7, DAT_0051bd70));
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT17));
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, spA0);
                beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT14));
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, DISPON);
                beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, ((char *)DAT_0051bd88));
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, DISPON);
                beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT17));
                beMessenger_AppendString(arg0->_messenger, *p);
                beMessenger_AppendString(arg0->_messenger, DISPON);
                beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
                i += 1;
                off += 4;
                p += 1;
            } while (i < temp_s6->_count);
        }
    }
    if (arg2 != 0) {
        int idx = arg0->_retCode;
        it = 0;
        if (idx != -1) {
            it = ((beNDMWItemDisk **)temp_s6->_data)[idx];
        }
        if (it != 0) {
            s = beNDMWItemBase_GetRecordString(it, temp_s7, TXT);
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
            beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT29));
            beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[0]);
            beMessenger_AppendString(arg0->_messenger, s);
            beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
            beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT29));
            beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[0]);
            beMessenger_AppendString(arg0->_messenger, DISPON);
            beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
            arg0->_tanka = beNDMWItemRevisionPocketBase_GetPrice(it, temp_s7, DAT_0051bd70);
            return;
        }
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
        beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT29));
        beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[0]);
        beMessenger_AppendString(arg0->_messenger, ((char *)DISPOFF));
        beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
    }
}

void FUN_00437f50(beNDMWShopCtrlDiskSell *arg0) {
    char sp30[16];
    int temp_s0;

    temp_s0 = arg0->_maxSell - arg0->_retCode;
    sprintf(sp30, percent_d, temp_s0);
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, &((const char *)STWINFONT30)[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b218[0]);
    beMessenger_AppendString(arg0->_messenger, sp30);
    beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
    sprintf(sp30, percent_d, temp_s0 * arg0->_tanka);
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, &((const char *)STWINFONT30)[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b288[0]);
    beMessenger_AppendString(arg0->_messenger, sp30);
    beMessenger_DispatchSelected(arg0->_messenger, TEXTSET);
}

void FUN_00438050(beNDMWShopCtrlDiskSell *arg0) {
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, STWINFONT30);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b278[0]);
    beMessenger_AppendString(arg0->_messenger, DISPOFF);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, STWINFONT30);
    beMessenger_AppendString(arg0->_messenger, &((int *)DAT_0051b218)[0]);
    beMessenger_AppendString(arg0->_messenger, DISPOFF);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_3);
    beMessenger_AppendString(arg0->_messenger, STWINFONT30);
    beMessenger_AppendString(arg0->_messenger, &((int *)DAT_0051b288)[0]);
    beMessenger_AppendString(arg0->_messenger, DISPOFF);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_2);
}

void FUN_004393e0(beNDMWShopCtrlSales *arg0, int arg1, unsigned char arg2) {
    int rec;
    int i;
    beNDMWItemRevisionPocketBase *it;
    char *name;
    rec = ((int)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0]));
    if (arg1 != 0) {
        i = 0;
        do {
            StringRef str;
            it = 0;
            int idx = i + arg0->_nowPage * 12;
            if (idx < LIST(arg0->_salesItemList)->_count) it = (beNDMWItemRevisionPocketBase *)((int *)LIST(arg0->_salesItemList)->_data)[idx];
            if (it != 0) {
                Vec3 pos;
                Vec3 pos2;
                ChipPriceText buf;
                name = beNDMWItemBase_GetRecordString(it, rec, ((char *)NAME_2));
                beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT14));
                beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[i]);
                beMessenger_AppendString(arg0->_messenger, name);
                beMessenger_DispatchSelected(arg0->_messenger, ((char *)TEXTSET));
                beNDMWItemBase_GetRevisionColor(&pos, it);
                beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT14));
                beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[i]);
                pos2.x = pos.x; pos2.y = pos.y; pos2.z = pos.z;
                beMessenger_AppendVec3(arg0->_messenger, (float *)&pos2);
                beMessenger_DispatchSelected(arg0->_messenger, ((char *)DAT_0051b9f8));
                if (it->_kindNo == 3 && it->_recNo == 185) {
                    buf = DAT_0051bdc0;
                } else {
                    sprintf(&buf, ((char *)percent_d), beNDMWItemRevisionPocketBase_GetPrice(it, rec, ((char *)DAT_0051b690)));
                }
                beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
                beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT17));
                beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[i]);
                beMessenger_AppendString(arg0->_messenger, (char *)&buf);
                beMessenger_DispatchSelected(arg0->_messenger, ((char *)TEXTSET));
                str.Set(Pool::Intern(DISPON));
            } else {
                str.Set(Pool::Intern(((char *)DISPOFF)));
            }
            beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
            beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT14));
            beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[i]);
            beMessenger_AppendString(arg0->_messenger, str.p);
            beMessenger_DispatchSelected(arg0->_messenger, ((char *)SWITCH_2));
            beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
            beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT17));
            beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[i]);
            beMessenger_AppendString(arg0->_messenger, str.p);
            beMessenger_DispatchSelected(arg0->_messenger, ((char *)SWITCH_2));
        } while (++i < 12);
        char dig[2];
        dig[1] = 0;
        dig[0] = arg0->_nowPage + 49;
        beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
        beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT30));
        beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[0]);
        beMessenger_AppendString(arg0->_messenger, dig);
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)TEXTSET));
        dig[0] = arg0->_maxPage + 48;
        beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
        beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT30));
        beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[1]);
        beMessenger_AppendString(arg0->_messenger, dig);
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)TEXTSET));
    }
    if (arg2) {
        int base = arg0->_nowPage * 12; it = (beNDMWItemRevisionPocketBase *)((int *)LIST(arg0->_salesItemList)->_data)[base + arg0->_retCode];
        char *label;
        if (it != 0) {
            name = beNDMWItemBase_GetRecordString(it, rec, ((char *)TXT));
            if (it->_kindNo == 0 || it->_kindNo == 1) {
                char dig[2];
                dig[1] = 0;
                dig[0] = it->_pocket + 48;
                igSmartPointer<igStringObj> rc((igStringObj *)(((beSystem *)((int)FUN_00236f80(arg0->_insight, g_beSystem_metaObject[0])))->_globalStrObj));
                if (rc.p != 0) rc.p->_refCount = rc.p->_refCount + 1;
                FUN_0030b3c0(rc.p, name);
                igStringObj *t = rc.p;
                i = t->_length;
                FUN_0030b460(t, dig, i, strlen(dig));
                name = (rc.p->_buffer == 0) ? DAT_004c22f0[0] : (char *)rc.p->_buffer;
            }
            beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
            beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT29));
            beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[0]);
            beMessenger_AppendString(arg0->_messenger, name);
            beMessenger_DispatchSelected(arg0->_messenger, ((char *)TEXTSET));
            label = DISPON;
            FUN_00439f30(arg0, 1);
        } else {
            label = ((char *)DISPOFF);
            FUN_00439f30(arg0, 0);
        }
        beMessenger_SelectGroup(arg0->_messenger, ((char *)TEXTCTL_3));
        beMessenger_AppendString(arg0->_messenger, ((char *)STWINFONT29));
        beMessenger_AppendString(arg0->_messenger, ((char * *)g_fontNames)[0]);
        beMessenger_AppendString(arg0->_messenger, label);
        beMessenger_DispatchSelected(arg0->_messenger, ((char *)SWITCH_2));
    }
}

int FUN_00439aa0(beNDMWShopCtrlSales *self) {
    int cnt;
    int pg;
    int k;
    int n;
    igUnsignedCharList *q;
    int i;
    int off;
    igObjectList *l;
    int idx;
    int base;
    int s1;
    igObjectList *l2;
    int lim;
    int j;
    int N2;
    igUnsignedCharList *Q2;
    int N3;
    igUnsignedCharList *Q3;
    char *d;
    int *e;
    igObjectList *lx;
    lx = (igObjectList *)self->_salesItemList;
    cnt = lx->_count;
    i = 0;
    if (i < cnt) {
    off = 0;
    do {
        if (*(int *)(lx->_data + off) != 0) cnt = i + 1;
        i++;
        off += 4;
        lx = (igObjectList *)self->_salesItemList;
    } while (i < lx->_count);
    }
    if (cnt % 12 != 0) pg = cnt / 12 + 1;
    else pg = cnt / 12;
    self->_maxPage = pg;
    s1 = 12;
    base = self->_nowPage * 12;
    l2 = (igObjectList *)self->_salesItemList;
    for (k = 0; k < 12; k++) {
        idx = base + k;
        if (idx > l2->_count - 1 || ((int *)l2->_data)[idx] == 0) { s1 = k; break; }
        l2 = (igObjectList *)self->_salesItemList;
    }
    if (s1 <= 0) s1 = 1;
    else if (s1 > 12) s1 = 12;
    ((igUnsignedCharList *)self->_decideList)->_count = 0;
    for (j = 0; j < s1; j++) {
        e = (int *)((int *)((igObjectList *)self->_salesItemList)->_data)[base + j];
        if (e == 0) {
            q = (igUnsignedCharList *)self->_decideList;
            n = q->_count;
            if (n < q->_capacity) q->_count = n + 1; else List_Resize(q, n + 1, 1);
            ((unsigned char *)q->_data)[n] = GPR_00554a68;
        } else if (e[2] == 3 && e[3] == 0xb9) {
            Q2 = (igUnsignedCharList *)self->_decideList;
            N2 = Q2->_count;
            if (N2 < Q2->_capacity) Q2->_count = N2 + 1; else List_Resize(Q2, N2 + 1, 1);
            ((unsigned char *)Q2->_data)[N2] = GPR_00554a6c;
        } else {
            Q3 = (igUnsignedCharList *)self->_decideList;
            N3 = Q3->_count;
            if (N3 < Q3->_capacity) Q3->_count = N3 + 1; else List_Resize(Q3, N3 + 1, 1);
            ((unsigned char *)Q3->_data)[N3] = GPR_00554a70;
        }
    }
    return s1;
}

bool FUN_00439d60(beNDMWShopCtrlSales *arg0, beNDMWItemBase *arg1) {
    int obj;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    obj = beMessenger_GetObject(arg0->_messenger, 0);
    return SalesChk::Chk(arg0, arg1, obj);
}

void FUN_00439f30(beNDMWShopCtrlSales *arg0, int arg1) {
    int obj;
    beNDMWItemBase *item;
    igObjectList *l0, *l1, *l2;
    igObjectList *m0, *m1;
    int kind;
    beNDMWItemBase *o;
    int ix;
    int col;
    int a2;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    obj = beMessenger_GetObject(arg0->_messenger, 0);
    a2 = arg1 & 0xff;
    item = 0;
    if (a2 == 1) {
        ix = arg0->_nowPage * 12; item = ((beNDMWItemBase **)((igObjectList *)arg0->_salesItemList)->_data)[ix + arg0->_retCode];
    }
    if (a2 == 1 && item != 0) {
        l0 = (igObjectList *)((Rec_439d60 *)igProperty_GetRecordFolder(obj, &DAT_0051bc48[0]))->f12;
        m0 = (igObjectList *)((Rec_439d60 *)igProperty_GetRecordFolder(obj, &DAT_0051bb90[0]))->f12;
        l1 = (igObjectList *)((Rec_439d60 *)igProperty_GetRecordFolder(obj, &DAT_0051bb78[0]))->f12;
        m1 = (igObjectList *)((Rec_439d60 *)igProperty_GetRecordFolder(obj, &DAT_0051bba0[0]))->f12;
        l2 = (igObjectList *)((Rec_439d60 *)igProperty_GetRecordFolder(obj, &DAT_0051bb88[0]))->f12;
        igSmartPointer<beNDMWItemBaseList> a((beNDMWItemBaseList *)FUN_003c90f0(ShopAlloc::Pool(arg0)));
        igSmartPointer<beNDMWItemBaseList> b((beNDMWItemBaseList *)FUN_003c90f0(ShopAlloc::Pool(arg0)));
        kind = item->_kindNo;
        if (kind == 0) {
            FUN_0043a450(arg0, (OL *)l0, (OL *)a.p, (OL *)m0, (OL *)b.p);
            if (item != 0) item->_refCount++;
            o = ((beNDMWItemBase **)l0->_data)[0];
            if (o != 0) { o->_refCount--; if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o); }
            if (l0->_count != 0 && 0 < l0->_count) ((beNDMWItemBase **)l0->_data)[0] = item;
        } else if (kind == 1) {
            FUN_0043a450(arg0, (OL *)l1, (OL *)a.p, (OL *)m1, (OL *)b.p);
            if (item != 0) item->_refCount++;
            o = ((beNDMWItemBase **)l1->_data)[0];
            if (o != 0) { o->_refCount--; if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o); }
            if (l1->_count != 0 && 0 < l1->_count) ((beNDMWItemBase **)l1->_data)[0] = item;
        } else if (kind == 2) {
            FUN_0043a450(arg0, (OL *)l2, (OL *)a.p, (OL *)0, (OL *)0);
            if (item != 0) item->_refCount++;
            o = ((beNDMWItemBase **)l2->_data)[0];
            if (o != 0) { o->_refCount--; if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o); }
            if (l2->_count != 0 && 0 < l2->_count) ((beNDMWItemBase **)l2->_data)[0] = item;
        }
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051bdf0[0]);
        kind = item->_kindNo;
        if (kind == 0) FUN_0043a660(arg0, (igDataList *)l0, (igDataList *)a.p, (igDataList *)m0, (igDataList *)b.p);
        else if (kind == 1) FUN_0043a660(arg0, (igDataList *)l1, (igDataList *)a.p, (igDataList *)m1, (igDataList *)b.p);
        else if (kind == 2) FUN_0043a660(arg0, (igDataList *)l2, (igDataList *)a.p, (igDataList *)0, (igDataList *)0);
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    } else {
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051be00[0]);
    }
}

void FUN_0043a450(void *arg0, OL *arg1, OL *arg2, OL *arg3, OL *arg4) {
    int i2;
    int off2;
    igObject *r;
    int i;
    RC *o;
    int off;
    i = 0;
    goto guard1;
body1:
    o = ((RC **)(arg1->_data + off))[0];
    ObjectList_AppendRetained(arg2, o);
    if (o != 0) o->f16 = 0;
    r = ((igObject **)(arg1->_data + off))[0];
    if (r != 0) {
        r->_refCount--;
        if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
    }
    if (arg1->_count != 0 && i >= 0 && i < arg1->_count) {
        ((RC **)(arg1->_data + off))[0] = 0;
    }
    off += 4;
    i++;
cond1:
    if (i < arg1->_count) goto body1;
after1:
    if (arg3 != 0) {
        if (arg4 != 0) {
            i2 = 0;
            goto guard2;
body2:
            o = ((RC **)(arg3->_data + off2))[0];
            ObjectList_AppendRetained(arg4, o);
            if (o != 0) o->f16 = 0;
            r = ((igObject **)(arg3->_data + off2))[0];
            if (r != 0) {
                r->_refCount--;
                if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
            }
            if (arg3->_count != 0 && i2 >= 0 && i2 < arg3->_count) {
                ((RC **)(arg3->_data + off2))[0] = 0;
            }
            off2 += 4;
            i2++;
cond2:
            if (i2 < arg3->_count) goto body2;
        }
    }
done:
    return;
guard2:
    if (0 < arg3->_count) { off2 = 0; goto cond2; }
    goto done;
guard1:
    if (0 < arg1->_count) { off = 0; goto cond1; }
    goto after1;
}

void FUN_0043a660(void *arg0, igDataList *arg1, igDataList *arg2, igDataList *arg3, igDataList *arg4) {
    int i2;
    igObject *o2;
    int i;
    igObject *r2;
    igObject *r;
    igObject *o;
    i = 0;
    goto guard1;
body1:
    o = ((igObject **)arg2->_data)[i];
    if (o != 0) o->_refCount++;
    r = ((igObject **)arg1->_data)[i];
    if (r != 0) {
        r->_refCount--;
        if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
    }
    if (arg1->_count != 0 && i >= 0 && i < arg1->_count) {
        ((igObject **)arg1->_data)[i] = o;
    }
    if (o != 0) *((char *)o + 16) = 1;
    r = ((igObject **)arg2->_data)[i];
    if (r != 0) {
        r->_refCount--;
        if (!(r->_refCount & 0x7fffff)) igObject_Destroy(r);
    }
    if (arg2->_count != 0 && i >= 0 && i < arg2->_count) {
        ((igObject **)arg2->_data)[i] = 0;
    }
    i++;
cond1:
    if (i < arg2->_count) goto body1;
after1:
    if (arg3 != 0) {
        if (arg4 != 0) {
            i2 = 0;
            goto guard2;
body2:
            o2 = ((igObject **)arg4->_data)[i2];
            if (o2 != 0) o2->_refCount++;
            r2 = ((igObject **)arg3->_data)[i2];
            if (r2 != 0) {
                r2->_refCount--;
                if (!(r2->_refCount & 0x7fffff)) igObject_Destroy(r2);
            }
            if (arg3->_count != 0 && i2 >= 0 && i2 < arg3->_count) {
                ((igObject **)arg3->_data)[i2] = o2;
            }
            if (o2 != 0) *((char *)o2 + 16) = 1;
            r2 = ((igObject **)arg4->_data)[i2];
            if (r2 != 0) {
                r2->_refCount--;
                if (!(r2->_refCount & 0x7fffff)) igObject_Destroy(r2);
            }
            if (arg4->_count != 0 && i2 >= 0 && i2 < arg4->_count) {
                ((igObject **)arg4->_data)[i2] = 0;
            }
                    i2++;
cond2:
            if (i2 < arg4->_count) goto body2;
        }
    }
done:
    return;
guard2:
    if (0 < arg4->_count) goto cond2;
    goto done;
guard1:
    if (0 < arg2->_count) goto cond1;
    goto after1;
}

void FUN_0043a950(int *arg0, int arg1) {
    Tbl sp30;
    float v[3];
    if (arg1 > -1) {
        sp30 = DAT_004cfa70;
        beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, DAT_0051b7d8);
        if (beMessenger_GetBool(arg0[3], 0) != 0) {
            beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, (char *)sp30.s[arg1]);
            return;
        }
        beMessenger_SelectReceivers(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0);
        beMessenger_AppendString(arg0[3], sp30.s[arg1]);
        v[2] = 0;
        v[0] = -121.0f;
        v[1] = 128.0f;
        beMessenger_AppendVec3(arg0[3], v);
        beMessenger_DispatchSelected(arg0[3], DAT_0051b7e0);
        return;
    }
    beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, DAT_0051b7d8);
    if (beMessenger_GetBool(arg0[3], 0) != 0) {
        beMessenger_SendNamed(arg0[3], ((char *)DAT_0051b308), DAT_0051b7c8, 0, ((char *)DAT_0051b620));
    }
}

static inline void ReleaseObject(igObject *o)
{
    if (o) {
        --o->_refCount;
        if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o);
    }
}

void Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_21(beNDMWShopCtrlXdataChip *arg0) {
    int vecB[3];
    int vecA[3];
    char sp90[16];
    int sp70[8];
    int al;
    int i;
    int n;
    int **p;
    int *src;
    igObjectList *folder;
    igObjectList *list;
    igStringRefList *slist;
    beNDMWItemBase *item;
    ChipRecord *rec;
    int pages;
    int ret;
    int have;
    int s0;
    bool s1;
    int s1i;
    int idx;
    int sel;
    int cost;
    int cur;
    int pocket;
    int *sub;
    int *first;
    int k;
    int li;
    int cst;
    int q;

    switch (arg0->_st0) {
    case 0:
        INTERN_APPEND_43aae0(arg0->_textCloseTypeList, &DAT_0051b668[0])
        INTERN_APPEND_43aae0(arg0->_textCloseNameList, &DAT_0051b1c8[0])
        INTERN_APPEND_43aae0(arg0->_textCloseTypeList, &DAT_0051be10[0])
        INTERN_APPEND_43aae0(arg0->_textCloseNameList, &DAT_0051b1c8[0])
        i = 0;
        p = &((int * *)g_fontNames)[0];
        do {
            beNDMWWindow_QueueText(arg0, STWINFONT14, *p, &DAT_0051b590[0], &DAT_0051b598[0]);
            beNDMWWindow_QueueText(arg0, STWINFONT17, *p, &DAT_0051b590[0], &DAT_0051b460[0]);
            i += 1;
            p += 1;
        } while (i < 12);
        beNDMWWindow_QueueText(arg0, STWINFONT29, ((int * *)g_fontNames)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
        beNDMWWindow_QueueText(arg0, STWINFONT29, &DAT_0051b548[0], &DAT_0051b590[0], &DAT_0051b598[0]);
        beNDMWWindow_QueueText(arg0, STWINFONT30, ((int * *)g_fontNames)[0], &DAT_0051b590[0], &DAT_0051bd98[0]);
        beNDMWWindow_QueueText(arg0, STWINFONT30, ((int * *)g_fontName1)[0], &DAT_0051b590[0], &DAT_0051bd98[0]);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
            rec = (ChipRecord *)((int *)igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b528[0]));
            list = (igObjectList *)arg0->_itemBaseList;
            folder = (igObjectList *)rec->f12;
            n = list->_count;
            k = 0;
            if (0 < n) {
                do {
                    igObject *o = (igObject *)((int *)list->_data)[k];
                    RELEASE_43aae0(o)
                    k += 1;
                } while (k < n);
            }
            { int m = list->_count; int j; for (j = 0; j < m; j++) ((int *)list->_data)[j] = 0; }
            list->_count = 0;
            for (q = 0; q < folder->_count; q++) {
                beNDMWItemBase *e = (beNDMWItemBase *)((int *)folder->_data)[q];
                if (e != 0) { int ok = e->_kindNo == 3; if (ok) ObjectList_AppendRetained(arg0->_itemBaseList, e); }
            }
            if (((igObjectList *)arg0->_itemBaseList)->_count <= 0) {
                arg0->_st1 = 0xA;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st3 = 0x491;
                return;
            }
            pages = beNDMWShopCtrlXdataChip_UpdatePageCount(arg0);
            if (arg0->_st2 == 0) {
                beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b610[0], 0, &DAT_0051be20[0], &DAT_0051b620[0]);
                beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x456);
                vecA[0] = 0x436C0000;
                vecA[2] = 0;
                vecA[1] = 0x41C80000;
                vecB[0] = 0xC3120000;
                vecB[1] = 0x41C80000;
                vecB[2] = 0;
                ((ChipVT *)arg0)->v22(vecB, vecA);
            }
            ALLOC_43aae0(al)
            {
            igSmartPointer<beNDMWStatusSelectE1> pageWin((beNDMWStatusSelectE1 *)FUN_003b51b0(al));
            beNDMWWindow_BindContext(pageWin.p, arg0, arg0->_insight, arg0->_playerNo, 0);
            ObjectList_AppendRetained((unsigned)arg0->_subWindow, pageWin.p);
            {
                beNDMWStatusSelectE1 *t = pageWin.p;
                t->_offsetPos[0] = -121.0f;
                t->_offsetPos[1] = 128.0f;
                t->_offsetPos[2] = 0.0f;
            }
            pageWin.p->_selectMax = pages;
            pageWin.p->_startPoint = arg0->_cursor;
            }
            arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            return;
        case 1:
            if (arg0->_retCode != -1) {
                beNDMWShopCtrlXdataChip_RefreshText(arg0, 1, 1);
            }
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        case 2:
            sub = (int *)arg0->_subWindow;
            if (sub[2] == arg0->_nowProcKazu) {
                cur = arg0->_retCode;
                if (cur != -1) {
                    if (arg0->_st3 != cur) {
                        beNDMWShopCtrlXdataChip_RefreshText(arg0, 0, 1);
                        arg0->_st3 = arg0->_retCode;
                        return;
                    }
                    first = ChipUtil::CastSel((int *)*(int *)sub[4]);
                    if (first != 0 && beNDMWWindowSelect_CanRequestFO2TOP(first) != 0) {
                        s1 = false;
                        if (((ChipVT *)arg0)->v23() != 0) {
                            s1 = true;
                        } else if (((ChipVT *)arg0)->v24() != 0) {
                            s1 = true;
                        }
                        if (s1) {
                            ((beNDMWWindowSelect *)first)->_st0 = 4;
                            ((beNDMWWindowSelect *)first)->_st3 = 0;
                            ((beNDMWWindowSelect *)first)->_st2 = 0;
                            ((beNDMWWindowSelect *)first)->_st1 = 0;
                            arg0->_st1 = 1;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            first[21] = beNDMWShopCtrlXdataChip_UpdatePageCount(arg0);
                            return;
                        }
                    }
                }
            } else {
                cur = arg0->_retCode;
                switch (cur) {
                case -1:
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                default:
                    arg0->_cursor = cur;
                    arg0->_st1 = arg0->_st1 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
            }
            break;
        case 3:
            MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
            have = ((ChipRecord *)((int *)igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b440[0])))->f12;
            pages = arg0->_nowPage;
            idx = arg0->_cursor + pages * 0xC;
            ret = beNDMWItemBase_GetRecordInt(((int *)((igObjectList *)arg0->_itemBaseList)->_data)[idx], ((int)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0], pages)), NEXTX);
            if (ret == -1) {
                arg0->_st1 = 0xB;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st3 = 0x492;
                return;
            }
            if (have < ret) {
                arg0->_st1 = 0xB;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st3 = 0x489;
                return;
            }
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            return;
        case 4:
            switch (arg0->_st2) {
            case 0: {
                beNDMWItemBase *chip;
                int status;
                int recNo;
                {
                ALLOC_43aae0(al)
                igSmartPointer<beNDMWShopSelect00> infoWin((beNDMWShopSelect00 *)FUN_003b4f50(al));
                beNDMWWindow_BindContext(infoWin.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, infoWin.p);
                int pages0 = arg0->_nowPage;
                int idx0 = arg0->_cursor + pages0 * 0xC;
                status = ((int)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0], pages0));
                chip = (beNDMWItemBase *)((int *)((igObjectList *)arg0->_itemBaseList)->_data)[idx0];
                recNo = chip->_recNo;
                if (chip->_isEquip != 0) {
                    chip->_recNo = recNo + 1;
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
                    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
                    MSG3(&DAT_0051b498[0], &DAT_0051bdf0[0])
                    chip->_recNo = recNo;
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
                    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
                }
                ALLOC_43aae0(al)
                igSmartPointer<beNDMWItemAbilityChip> abilityChip((beNDMWItemAbilityChip *)FUN_003c87f0(al));
                beNDMWItemAbilityChip_Set(abilityChip.p, recNo + 1);
                beNDMWWindow_QueueText(infoWin.p, STWINFONT29, ((int * *)g_fontNames)[0], ((int *)beNDMWItemBase_GetRecordString(abilityChip.p, status, NAME_2)), &DAT_0051b598[0]);
                beNDMWWindow_QueueText(infoWin.p, &DAT_0051b448[0], ((int * *)g_fontName1)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                beNDMWWindow_QueueText(infoWin.p, &DAT_0051b448[0], ((int * *)DAT_004cf8a8)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                beNDMWWindow_QueueText(infoWin.p, &DAT_0051b448[0], DAT_004cf8ac[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                beNDMWWindow_QueueText(infoWin.p, STWINFONT29, ((int * *)DAT_004cf8a8)[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                {
                ALLOC_43aae0(al)
                igSmartPointer<igStringRefList> statNames((igStringRefList *)FUN_002b90e0(al));
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051b3f8[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051b408[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051b418[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051b420[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be40[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be50[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be58[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be68[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be78[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be88[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be90[0])
                INTERN_APPEND_43aae0((int)statNames.p, &DAT_0051be98[0])
                s1i = ((int)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0]));
                ALLOC_43aae0(al)
                igSmartPointer<igIntList> costs = igSmartPointer<igIntList>((igIntList *)FUN_002caa70(al));
                slist = statNames.p;
                li = 0;
                if (0 < slist->_count) {
                    do {
                        cst = beNDMWItemBase_GetRecordInt(abilityChip.p, s1i, (StringList_CopyRetained(slist, li)).p);
                        if (cst > 0) {
                            sprintf(sp90, percent_d, cst);
                            beNDMWWindow_QueueText(infoWin.p, &DAT_0051b448[0], &DAT_0051b220[0], sp90, &DAT_0051b460[0]);
                            if (li >= 8) li = 7;
                            {
                                struct Q2 { unsigned __int128 a[2]; }; *(Q2 *)sp70 = *(Q2 *)&DAT_004cfaa0[0];
                            }
                            infoWin.p->_entCode = sp70[li];
                            break;
                        }
                        slist = statNames.p;
                        li += 1;
                    } while (li < slist->_count);
                }
                }
                MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
                s0 = ((ChipRecord *)((int *)igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b440[0])))->f12;
                sprintf(sp90, percent_d, s0 - beNDMWItemBase_GetRecordInt(chip, status, NEXTX));
                beNDMWWindow_QueueText(infoWin.p, &DAT_0051b448[0], &DAT_0051b248[0], sp90, &DAT_0051b460[0]);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            }
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    ALLOC_43aae0(al)
                    {
                    igSmartPointer<beNDMWShopSelect01> buyWin((beNDMWShopSelect01 *)FUN_003b4d90(al));
                    beNDMWWindow_BindContext(buyWin.p, arg0, arg0->_insight, arg0->_playerNo, 0x493);
                    ObjectList_AppendRetained((unsigned)arg0->_subWindow, buyWin.p);
                    }
                    arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                    arg0->_st2 = arg0->_st2 + 1;
                    arg0->_st3 = 0;
                case 2:
                    if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                        MSG3(&DAT_0051b498[0], &DAT_0051be00[0])
                        switch (arg0->_retCode) {
                        case 0: {
                            beNDMWItemBase *chip2;
                            int st2;
                            int cost2;
                            int sel2;
                            int cur2;
                            int pages2 = arg0->_nowPage;
                            int idx2 = arg0->_cursor + pages2 * 0xC;
                            st2 = ((int)FUN_00236f80(arg0->_insight, g_beNDMWStatus_metaObject[0], pages2));
                            chip2 = (beNDMWItemBase *)((int *)((igObjectList *)arg0->_itemBaseList)->_data)[idx2];
                            MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
                            sel2 = beMessenger_GetObject(arg0->_messenger, 0);
                            cur2 = ((ChipRecord *)((int *)igProperty_GetRecord(sel2, &DAT_0051b440[0])))->f12;
                            cost2 = beNDMWItemBase_GetRecordInt(chip2, st2, NEXTX);
                            ChipRecord *r2 = (ChipRecord *)((int *)igProperty_GetRecord(sel2, &DAT_0051b440[0]));
                            r2->f12 = cur2 - cost2;
                            chip2->_recNo = chip2->_recNo + 1;
                            MSG3(&DAT_0051b398[0], &DAT_0051b3a0[0])
                            MSG3(&DAT_0051b498[0], &DAT_0051b4a0[0])
                            break;
                        }
                        default:
                            break;
                        }
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st2 = 1;
                        arg0->_st3 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 10:
            switch (arg0->_st2) {
            case 0:
                ALLOC_43aae0(al)
                {
                igSmartPointer<beNDMWShopSelect00> refusalWin((beNDMWShopSelect00 *)FUN_003b4f50(al));
                beNDMWWindow_BindContext(refusalWin.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, refusalWin.p);
                beNDMWShopSelect00 *w = refusalWin.p;
                if (g_stringPool[0] == 0) {
                    int pool = FUN_002eb010(0x10);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    g_stringPool[0] = pool;
                }
                {
                    int *nw = (int *)StringPool_Intern(g_stringPool[0], &DAT_0051b548[0]);
                    int *old = (int *)w->_panelName;
                    if (old != 0) {
                        int *hd = old - 2;
                        int c = old[-1] - 1;
                        old[-1] = c;
                        if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
                    }
                    w->_panelName = (int)nw;
                }
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 11:
            switch (arg0->_st2) {
            case 0:
                ALLOC_43aae0(al)
                {
                igSmartPointer<beNDMWShopSelect00> shortageWin((beNDMWShopSelect00 *)FUN_003b4f50(al));
                beNDMWWindow_BindContext(shortageWin.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, shortageWin.p);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st2 = 1;
                    arg0->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}

/* Chip list pagination: refresh maximum pages and return current row count. */

int beNDMWShopCtrlXdataChip_UpdatePageCount(beNDMWShopCtrlXdataChip *self){
    int count=((igObjectList *)self->_itemBaseList)->_count,pages,remaining,result;
    if(count%12)pages=count/12+1;
    else pages=count/12;
    self->_maxPage=pages;
    remaining=(int)((unsigned)((igObjectList *)self->_itemBaseList)->_count-(unsigned)self->_nowPage*12);
    if(remaining>=12){
        result=12;
    }
    else result=remaining%12;
    if(result<1){result=1;}
    return result;
}

/* "----" */

void beNDMWShopCtrlXdataChip_RefreshText(beNDMWShopCtrlXdataChip *self, long long refreshRows,
                                         long long refreshDescription) {
    char page[4];
    ChipPriceText priceText;
    int status;
    int row;
    int index;
    char *name;
    int item;
    int nextX;
    char *visibility;
    char **font;
    int selectedIndex;
    int selectedItem;
    char *description;

    /* Status is captured even when neither refresh flag is set. */
    status = ((int)FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]));
    if (refreshRows != 0) {
        font = (char **)(g_fontNames);
        for (row = 0; row < CHIPS_PER_PAGE; row++, font++) {
            index = row + self->_nowPage * CHIPS_PER_PAGE;
            if (index < ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
                item = *(int *)(((beNDMWItemBaseList *)self->_itemBaseList)->_data + (index * 4));
                if (item == 0) {
                    continue;
                }
                name = beNDMWItemBase_GetRecordString(item, status, NAME_2);
                nextX = beNDMWItemBase_GetRecordInt(item, status, NEXTX);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT14);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                if (nextX > 0) {
                    sprintf((char *)&priceText, percent_d, nextX);
                } else {
                    priceText = DAT_0051bdc0;
                }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT17);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, (char *)&priceText);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                visibility = &DISPON[0];
            } else {
                visibility = DISPOFF;
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT14);
            beMessenger_AppendString(self->_messenger, *font);
            beMessenger_AppendString(self->_messenger, visibility);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
            beMessenger_AppendString(self->_messenger, STWINFONT17);
            beMessenger_AppendString(self->_messenger, *font);
            beMessenger_AppendString(self->_messenger, visibility);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
        }
        page[1] = 0;
        page[0] = self->_nowPage + '1';
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT30);
        beMessenger_AppendString(self->_messenger, g_fontNames[0]);
        beMessenger_AppendString(self->_messenger, page);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET);
        page[0] = self->_maxPage + '0';
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
        beMessenger_AppendString(self->_messenger, STWINFONT30);
        beMessenger_AppendString(self->_messenger, g_fontName1[0]);
        beMessenger_AppendString(self->_messenger, page);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET);
    }
    if (refreshDescription != 0) {
        /* matching construct: hand sweep — the subtraction of a negation keeps the retail addu operand order */
        selectedIndex = self->_nowPage * CHIPS_PER_PAGE - -self->_retCode;
        if (selectedIndex < ((beNDMWItemBaseList *)self->_itemBaseList)->_count) {
            selectedItem = *(int *)(((beNDMWItemBaseList *)self->_itemBaseList)->_data + (selectedIndex * 4));
            if (selectedItem != 0) {
                description = beNDMWItemBase_GetRecordString(selectedItem, status, TXT);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT29);
                beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                beMessenger_AppendString(self->_messenger, description);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_3);
                beMessenger_AppendString(self->_messenger, STWINFONT29);
                beMessenger_AppendString(self->_messenger, g_fontNames[0]);
                beMessenger_AppendString(self->_messenger, &DISPON[0]);
                beMessenger_DispatchSelected(self->_messenger, SWITCH_2);
            }
        }
    }
}

static inline int st0Of(const S *s) { return s->_st0; }

void Gap__Bec__beNDMWShopDevice__vfunc_21(S *arg0) {
    void *alloc;
    switch (arg0->_st0) {
    case 0:
        arg0->_st0 = st0Of(arg0) + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopSelect01> win((beNDMWShopSelect01 *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(LST(arg0), win.p);
                switch (arg0->_entCode) {
                case 6: ((beNDMWShopSelect01 *)win.p)->_entCode = 0x672; break;
                case 7: ((beNDMWShopSelect01 *)win.p)->_entCode = 0x6D6; break;
                case 8: ((beNDMWShopSelect01 *)win.p)->_entCode = 0x73A; break;
                }
                }
                arg0->_nowProcKazu = LST(arg0)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LST(arg0)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_st1 = 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        arg0->_st1 = 2;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 2:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopCtrlSales> win((beNDMWShopCtrlSales *)FUN_003b6bc0(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_entCode);
                ObjectList_AppendRetained(LST(arg0), win.p);
                }
                arg0->_nowProcKazu = LST(arg0)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LST(arg0)->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<beNDMWShopCtrlSell> win((beNDMWShopCtrlSell *)FUN_003b7360(alloc));
                beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(LST(arg0), win.p);
                }
                arg0->_nowProcKazu = LST(arg0)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LST(arg0)->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}

int Gap__Bec__beNDMWShopDevice__vfunc_20(void)
{
    return g_beNDMWShopDevice_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_20(void)
{
    return g_beNDMWShopCtrlXdataChip_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlSales__vfunc_20(void)
{
    return g_beNDMWShopCtrlSales_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlDiskSell__vfunc_20(void)
{
    return g_beNDMWShopCtrlDiskSell_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlDeviceSell__vfunc_20(void)
{
    return g_beNDMWShopCtrlDeviceSell_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlSell__vfunc_20(void)
{
    return g_beNDMWShopCtrlSell_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlEditBit__vfunc_20(void)
{
    return g_beNDMWShopCtrlEditBit_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlDigilabo__vfunc_20(void)
{
    return g_beNDMWShopCtrlDigilabo_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlEvolve__vfunc_20(void)
{
    return g_beNDMWShopCtrlEvolve_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlA2__vfunc_20(void)
{
    return g_beNDMWShopCtrlA2_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlA1__vfunc_20(void)
{
    return g_beNDMWShopCtrlA1_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrlA0__vfunc_20(void)
{
    return g_beNDMWShopCtrlA0_metaObject[0];
}

int Gap__Bec__beNDMWShopJunk__vfunc_20(void)
{
    return g_beNDMWShopJunk_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrl50__vfunc_20(void)
{
    return g_beNDMWShopCtrl50_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrl40__vfunc_20(void)
{
    return g_beNDMWShopCtrl40_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrl30__vfunc_20(void)
{
    return g_beNDMWShopCtrl30_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrl10__vfunc_20(void)
{
    return g_beNDMWShopCtrl10_metaObject[0];
}

int Gap__Bec__beNDMWShopCtrl00__vfunc_20(void)
{
    return g_beNDMWShopCtrl00_metaObject[0];
}

