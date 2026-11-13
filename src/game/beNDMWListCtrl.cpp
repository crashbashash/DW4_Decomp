#include "dw4/reflected.h"
#define STICK_UP 1
#define STICK_RIGHT 2
#define STICK_DOWN 4
#define STICK_LEFT 8
#define BUTTON_RIGHT 0x20
#define BUTTON_LEFT 0x80
#define NEWWIN(H, var, ctor, ga) { al = igObject_GetAllocator(ga);  al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);  igSmartPointer<H> var((H *)ctor(al));  beNDMWWindow_BindContext(var.p, self, self->_insight, self->_playerNo, 0);  lst = self->_subWindow;  ObjectList_AppendRetained(lst, var.p); }
#define GRP(a, b) { beMessenger_SelectGroup(self->_messenger, LAYERCTL);  beMessenger_AppendString(self->_messenger, &a[0]);  beMessenger_AppendString(self->_messenger, &b[0]);  beMessenger_DispatchSelected(self->_messenger, SWITCH_4); }
#define NEXT0() { self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0; }
#define FIN(a) { self->_st1 = a; self->_st3 = 0; self->_st2 = 0; }
#define RELEASE_OBJ(o) { \
    if (o) { \
        --(o)->_refCount; \
        if (((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(o); \
    } }
#define SELALLOC(fb) (g_useOwnerAllocator ? (fb) : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])))
#define SEL(d) beMessenger_SelectGroup(p->_messenger, d)
#define APS(d) beMessenger_AppendString(p->_messenger, d)
#define API(d) beMessenger_AppendInt(p->_messenger, d)
#define DSP(d) beMessenger_DispatchSelected(p->_messenger, d)
#define SUBCOUNT (((igObjectList *)p->_subWindow)->_count)
#define PUSHB(LP, B) { int n_; igUnsignedCharList *l_ = (igUnsignedCharList *)(LP); n_ = l_->_count; if (n_ < l_->_capacity) { l_->_count = n_ + 1; } else { List_Resize(l_, n_ + 1, 1); } ((unsigned char *)l_->_data)[n_] = (B); }
#define SETB(LP, IDX, B) { igUnsignedCharList *l_ = (igUnsignedCharList *)(LP); if (l_->_count != 0 && (IDX) >= 0 && (IDX) < l_->_count) { ((unsigned char *)l_->_data)[(IDX)] = (B); } }
#define SWV(h) ((igObjectList *)*(int *)&(h))
#define FIND(W) { int i_; (W) = 0; for (i_ = 0; i_ < ((igObjectList *)p->_subWindow)->_count; i_++) { (W) = ((int *)SWV(p->_subWindow)->_data)[i_]; if ((W) && igObject_IsKindOf((W), g_beNDMWStatusCtrlD0_metaObject[0])) { (W) = (int)(int *)(W); } else { (W) = 0; } if ((W)) break; } }
#define SETSLOT(L, IDX, V_) { Obj *v_ = (V_); Obj *old_; if (v_ != 0) { v_->_refCount = v_->_refCount + 1; } old_ = ((Obj **)(L)->_data)[(IDX)]; if (old_ != 0) { --old_->_refCount; if (((unsigned long long)(long long)(int)old_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old_); } if ((L)->_count != 0 && (IDX) >= 0 && (IDX) < (L)->_count) { ((Obj **)(L)->_data)[(IDX)] = v_; } }
/* matching construct: cxx_sweep — the item is read inside its retain test */
#define SET_ITEM(IDX, ITEM) { Obj *v; int r = (IDX); igObjectList *l = (igObjectList *)p->_powerSocket; \
    if ((v = (ITEM).p) != 0) { v->_refCount = v->_refCount + 1; } \
    ReleaseObject(((Obj **)l->_data)[r]); \
    if (l->_count != 0 && r >= 0 && r < l->_count) { ((Obj **)l->_data)[r] = v; } }
#define V(p) ((VC *)(p))
#define ADV() { p->_st0 = p->_st0 + 1; p->_st3 = 0; p->_st2 = 0; p->_st1 = 0; }
#define SETST(a, b) { p->_st0 = a; p->_st3 = 0; p->_st2 = 0; p->_st1 = 0; p->_st1 = b; p->_st3 = 0; p->_st2 = 0; }
#define NEXT2() { p->_st2 = p->_st2 + 1; p->_st3 = 0; }
#define REFRESH() { SEL(SUBWND_2); API(p->_playerNo); DSP(OFPREVIEW); }
#define PUBLISH() { beMessenger_SelectReceivers(p->_messenger, GAMERAM_9, 0, 0); API(p->_playerNo); DSP(RECALCPLAYER_4); SEL(SUBWND_2); API(p->_playerNo); DSP(UPDATE); }
#include "dw4/igSmartPointer.h"
#include "dw4/igobject_release.h"
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define LIST_CLEAR_AT(L, i) { REL((L)->_data[i]); \
    if ((L)->_count != 0 && (i) >= 0 && (i) < (L)->_count) (L)->_data[i] = 0; }
#define REL_413c20(P) { igObject *q = (igObject *)(P); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) { igObject_Destroy(q); } } }
#define APPEND(V) { igBoolList *l = flags.p; int n = l->_count; if (n < l->_capacity) { l->_count = n + 1; } else { List_Resize(l, n + 1, 1); } *(unsigned char *)(n + l->_data) = (V); }
#define REL_414a00(P) { igObject *q = (P); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffffU) == 0) { igObject_Destroy(q); } } }
#define GET_ALLOC(v) { void *ga = igObject_GetAllocator(self); if (g_useOwnerAllocator != 0) { v = ga; } else { v = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]); } }
#define RELEASE_STR(slot) { const char *held = slot; \
    if (held != 0) { int *hd = (int *)held - 2; \
        int cnt = ((int *)held)[-1] - 1; ((int *)held)[-1] = cnt; \
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define RETAIN_OBJ(o) { RefHeader *rr = (RefHeader *)(o); if (rr != 0) rr->_refCount = rr->_refCount + 1; }
#define RELEASE_OBJ_418090(o) { RefHeader *rr = (RefHeader *)(o); \
    if (rr != 0) { rr->_refCount = rr->_refCount - 1; \
        if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define NEXT_ST0() { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
#define REL_4196c0(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define ALLOC(al) al = igObject_GetAllocator(arg0); al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
#define MSG() { beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5); beMessenger_AppendString(arg0->_messenger, STWINFONT29_3); beMessenger_AppendString(arg0->_messenger, font100_2); beMessenger_AppendString(arg0->_messenger, DISPOFF_2); beMessenger_DispatchSelected(arg0->_messenger, SWITCH_4); }
#define CLEAR(lst) { igDataList *l = (igDataList *)(lst); int n = l->_count; int i; int *slot; int *nw; int o; int *old; if (0 < n) { i = 0; o = 0; do { slot = (int *)(l->_data + o); if (((int *)g_stringPool)[0] == 0) { int v = ((int)StringPool_Allocate(0x10)); if (v != 0) { v = ((int)StringPool_Construct(v)); } ((int *)g_stringPool)[0] = v; } nw = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0); old = (int *)*slot; if (old != 0) { int *hd = old - 2; int c = old[-1] - 1; old[-1] = c; if (c == 0) { StringChunk_ReleaseHeader(*hd, hd); } } i++; *slot = (int)nw; o += 4; } while (i < n); } l->_count = 0; }
#define WSETI84(w, v) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); wt->_selectMax = (v); }
#define WSETI100(w, v) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); wt->_startPoint = (v); }
#define WSETPOS(w, x, y, z) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); *(float *)&wt->_offsetPos[0] = (x); *(float *)&wt->_offsetPos[1] = (y); *(float *)&wt->_offsetPos[2] = (z); }
#define MSG_SELECT_INT(v) { beMessenger_SelectGroup(self->_messenger, GAMERAM_9); \
    beMessenger_AppendInt(self->_messenger, v); beMessenger_DispatchSelected(self->_messenger, GETPLAYER_6); }
#define NEXT_ST2() { self->_st2 = self->_st2 + 1; self->_st3 = 0; }
#define SYNC_COUNT() { self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count; }
#define WIN_PENDING() (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu)
#define BLIST_ADD(r, v) { int n; igDataList *dl = (igDataList *)(r).p; n = dl->_count; \
    if (n < dl->_capacity) dl->_count = n + 1; else List_Resize(dl, n + 1, 1); \
    ((unsigned char *)dl->_data)[n] = (v); }
#define LIST_ADD(decided, val) { int n_ = ((igDataList *)(decided))->_count; igDataList *l_ = (igDataList *)(decided); \
    if (n_ < l_->_capacity) l_->_count = countOf(l_) + 1; else List_Resize(l_, n_ + 1, 4); \
    ((int *)l_->_data)[n_] = (val); }
#define SEND_CLOSE() beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3)
#define RESET_ST1() { self->_st1 = 0; self->_st3 = 0; self->_st2 = 0; }
#define MSG_STR3(a, b, c, d) { beMessenger_SelectGroup(self->_messenger, TEXTCTL_5); \
    beMessenger_AppendString(self->_messenger, a); beMessenger_AppendString(self->_messenger, b); \
    beMessenger_AppendString(self->_messenger, c); beMessenger_DispatchSelected(self->_messenger, d); }
#define CLOSE_LISTS() { igStringRefList *l1 = (igStringRefList *)self->_modelCloseInfoNameList; \
    StringRefList_ResetRange(l1, 0, l1->_count); l1->_count = 0; \
    ((igObjectList *)self->_modelCloseRamNoList)->_count = 0; \
    igStringRefList *l2 = (igStringRefList *)self->_modelCloseSeqNameList; \
    StringRefList_ResetRange(l2, 0, l2->_count); l2->_count = 0; }
#define APO(d) beMessenger_AppendObject(p->_messenger, d)
#define SW(h) ((igObjectList *)(h))
#define WSETI84_4207a0(T, w, v) { T *wt = (T *)(w); wt->_selectMax = (v); }
#define WSETI100_4207a0(T, w, v) { T *wt = (T *)(w); wt->_startPoint = (v); }
#define WSETPOS_4207a0(T, w, x, y, z) { T *wt = (T *)(w); *(float *)&wt->_offsetPos[0] = (x); *(float *)&wt->_offsetPos[1] = (y); wt->_offsetPos[2] = (z); }
#define LIST_ADD_4207a0(lst, val) { int n_ = ((igDataList *)(lst))->_count; igDataList *l_ = (igDataList *)(lst); \
    if (n_ < l_->_capacity) l_->_count = count_4207a0(l_) + 1; else List_Resize(l_, n_ + 1, 4); \
    ((int *)l_->_data)[n_] = (val); }
#define LIST_REMOVE(lst, idx) { igObjectList *l_ = (igObjectList *)(lst); int ix_ = (idx); \
    ObjectRef_Release_003e9110(ObjectList_GetAt_003e9260(l_, ix_)); ObjectList_RemoveAt_00406f20(l_, ix_); \
    ((int *)l_->_data)[l_->_count] = 0; }

extern "C" void beMessenger_SendNamed(...);
extern "C" int beNDMWListCtrl_GetMeta(void);
extern "C" beNDMWStatusTitle03 *beNDMWStatusTitle03_Create(void *allocator);
extern "C" beNDMWStatusTitle02 *beNDMWStatusTitle02_Create(void *allocator);
extern "C" beNDMWStatusTitle01 *beNDMWStatusTitle01_Create(void *allocator);
extern "C" beNDMWStatusTitle00 *beNDMWStatusTitle00_Create(void *allocator);
extern "C" beNDMWStatusSelect00 *beNDMWStatusSelect00_Create(void *allocator);
extern "C" beNDMWStatusCtrlSkill *beNDMWStatusCtrlSkill_Create(void *allocator);
extern "C" beNDMWStatusCtrlFolder *beNDMWStatusCtrlFolder_Create(void *allocator);
extern "C" beNDMWStatusCtrlEquip *beNDMWStatusCtrlEquip_Create(void *allocator);
extern "C" int beNDMWWindow_QueueText(...);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beNDMWWindow_BindContext(...);
extern "C" int beNDMWWindow_ClearQueuedText(...);
extern "C" int beNDMWWindow_PlayQueuedModelClose(...);
extern "C" int beNDMWWindow_PollCloseComplete(...);
extern "C" int beNDMWWindow_RequestChildrenClose(...);
extern "C" void * igObject_GetAllocator(...);
extern "C" int beNDMWWindow_RunMessageScript(...);
extern "C" int igObject_IsKindOf(...);
extern "C" beDataObjStringList *igProperty_GetRecordStringList(...);
extern "C" beNDMWShopSelect00 *beNDMWShopSelect00_Create(void *allocator);
extern "C" beNDMWStatusSelectE1 *beNDMWStatusSelectE1_Create(void *allocator);
extern "C" void beNDMWStatusCtrlBaseEquip_PreviewSocketSwap(beNDMWStatusCtrlBaseEquip *p);
extern "C" int List_Resize(...);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_GetObject(...);
extern "C" beDataObjObjectList *igProperty_GetRecordFolder(...);
extern "C" void beMessenger_AppendVec3(int, float *);
extern "C" void beNDMWStatusCtrlBaseEquip_ShowKindCursor(beNDMWStatusCtrlBaseEquip *self, int kind);
extern "C" void beNDMWStatusCtrlBaseEquip_QueuePanelText(beNDMWStatusCtrlBaseEquip *self);
extern "C" void * StringPool_Allocate(...);
extern "C" void * StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" int igInsightCore_FindManager(...);
extern "C" int igStringRefList_Create(...);
extern "C" int igIntList_Create(...);
extern "C" int beNDMWItemBase_GetRecordInt(...);
extern "C" int beNDMWItemBase_GetRecordString(...);
extern "C" void beNDMWWindow_PresentModelAtOrigin(...);
extern "C" int beNDMWItemBase_GetRevisionColor(...);
extern "C" int strlen(const void *);
extern "C" int igStringObj_Set(void *, const char *);
extern "C" int igStringObj_Insert(void *, const void *, int, int);
extern "C" int FUN_00100610(...);
extern "C" void beNDMWStatus_PreviewEquipment(...);
extern "C" int ObjectList_FillRetained(...);
extern "C" int beNDMWStatusMainSlot_GetMeta(void);
extern "C" void beNDMWStatusSubSlot_PreviewPocketDevice(void);
extern "C" void beNDMWStatusSubSlot_OpenPocketList(void);
extern "C" void beNDMWStatusSubSlot_ShowPocketDescription(void);
extern "C" void beNDMWStatusSubSlot_OpenPocketMenu(void);
extern "C" void beNDMWStatusSubSlot_OpenPocketFolder(void);
extern "C" void beNDMWStatusSubSlot_EquipPocket(void);
extern "C" void beNDMWStatusSubSlot_ClearPocket(void);
extern "C" int beNDMWStatusSubSlot_GetMeta(void);
extern "C" int beNDMWWindowSelect_CanRequestFO2TOP(...);
extern "C" int beNDMWItemBase_GetRecordBool(...);
extern "C" int beNDMWStatusCtrlD0_GetSelectedIndex(void *arg0);
extern "C" void *beNDMWStatusSubMenu_Create(void *);
extern "C" void *beNDMWStatusCtrlFlag_Create(void *);
extern "C" void *beNDMWStatusCtrlDisk_Create(void *);
extern "C" void *beNDMWStatusCtrlBit_Create(void *);
extern "C" int beMessenger_SendGroup(...);
extern "C" beDataObjBoolList *igProperty_GetRecordArray(...);
extern "C" const char * beDataBase_GetRecordString(...);
extern "C" void ObjectList_SetAtRetained_003e9160(...);
extern "C" void ObjectRef_Release_003e9110(...);
extern "C" void ObjectRef_Retain_003e90d0(...);
extern "C" void *beNDMWShopSelect52_Create(void *);
extern "C" beDataObjBool *igProperty_GetRecordByte(...);
extern "C" int beNDMWStatusCtrlSendBit_Create(int);
extern "C" void sprintf(...);
extern "C" int beNDMWShopSelect34_Create(...);
extern "C" int FUN_004402e0(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" void beNDMWShinkaCtrl_Setup(int, int, int);
extern "C" void beNDMWWindow_SendModelSequence(...);
extern "C" void *ObjectList_GetAt_003e9260(...);
extern "C" void ObjectList_RemoveAt_00406f20(...);
extern "C" void *beNDMWItemBaseList_Create(void *);
extern "C" int beNDMWStatusSubMenu_GetMeta(void);
extern "C" int beNDMWStatusCtrlSkill_GetMeta(void);
extern "C" int beNDMWStatusCtrlSendBit_GetMeta(void);
extern "C" int beNDMWStatusCtrlBit_GetMeta(void);
extern "C" int beNDMWStatusCtrlDisk_GetMeta(void);
extern "C" int beNDMWStatusCtrlFlag_GetMeta(void);
extern "C" int beNDMWStatusCtrlFolder_GetMeta(void);
extern "C" int beNDMWStatusCtrlD0_GetMeta(void);
extern "C" int beNDMWStatusPowerSocket_GetMeta(void);
extern "C" int beNDMWStatusCtrlBaseEquip_GetMeta(void);
extern "C" int beNDMWStatusCtrlEquip_GetMeta(void);
extern "C" int beNDMWStatusCtrl00_GetMeta(void);
extern "C" int g_beNDMWListCtrl_metaObject[4];
extern "C" char i_stcursorleft[];
extern "C" char SQ_HIDE[];
extern "C" char SQ_CLOSE_3[];
extern "C" char i_stcursorright[];
extern "C" char SQ_SELECT[];
extern "C" char MODELCTRL_3[];
extern "C" char SQ_MOVEEND[];
extern "C" char SQ_MOVENEXT[];
extern "C" void beNDMWWindow_PresentModel(beNDMWListCtrl *, const char *, int, const char *, const char *, float *);
extern "C" bePadData * bePadManager_GetPadForPlayer(...);
extern "C" void Gap__Bec__beNDMWListCtrl__vfunc_22(beNDMWListCtrl *self,const float *leftArrowPos,const float *rightArrowPos);
extern "C" bool Gap__Bec__beNDMWListCtrl__vfunc_23(beNDMWListCtrl *self);
extern "C" bool Gap__Bec__beNDMWListCtrl__vfunc_24(beNDMWListCtrl *self);
/* The window holders are memory-resident stack objects (slots in declaration order w1..w8); each
 * releases its window in its destructor. The offset/index/count loop locals are declared in the
 * order n, i, off with c before them. */

typedef igObject Obj;
extern "C" char *g_statusFontNames[12];
extern "C" char i_stback[];
extern "C" char SQ_OPEN_5[];
extern "C" char ISSEQNAME_4[];
extern "C" char LAYERCTL[];
extern "C" char BG01[];
extern "C" char DISPOFF_2[];
extern "C" char SWITCH_4[];
extern "C" char BG02[];
extern "C" char BG03[];
extern "C" char GM01[];
extern "C" char GM03[];
extern "C" char i_messwn[];
extern "C" char SQ_STOPEN[];
extern "C" char STWINFONT29_3[];
extern "C" char space[];
extern "C" char LEFT_3[];
extern "C" char ISRUN_5[];
extern "C" char DISPON_2[];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void beNDMWStatusCtrl00_Update(beNDMWStatusCtrl00 *self);
extern "C" void beNDMWStatusCtrlEquip_Update(beNDMWStatusCtrlEquip *self);
extern "C" beNDMWStatusTitle04 *beNDMWStatusTitle04_Create(void *allocator);
extern "C" beNDMWStatusSelect01 *beNDMWStatusSelect01_Create(void *allocator);
extern "C" beNDMWStatusPowerSocket *beNDMWStatusPowerSocket_Create(void *allocator);
extern "C" beNDMWStatusMainSlot *beNDMWStatusMainSlot_Create(void *allocator);
extern "C" beNDMWStatusSubSlot *beNDMWStatusSubSlot_Create(void *allocator);
extern "C" char i_sttitle[];
extern "C" char txt_status_lua_2[];
extern "C" char font000_2[];
extern "C" char font001_2[];
extern "C" char GAMERAM_9[];
extern "C" char GETPLAYER_6[];
extern "C" char POWERSOCKET_3[];
extern "C" char MAINSLOT_3[];
extern "C" char SUBSLOT_3[];
extern "C" char POWERPOCKET_3[];
extern "C" char MAINPOCKET_3[];
extern "C" char DEVICEFOLDER_3[];
extern "C" char SUBWND_2[];
extern "C" char OFPREVIEW[];
extern "C" char TEXTCTL_5[];
extern "C" char DEFAULTCOLOR_2[];
extern "C" char RECALCPLAYER_4[];
extern "C" char UPDATE[];
extern "C" char POWERSOCKETNAME_3[];
extern "C" char PLAYERARMS_2[];
extern "C" char GENERATE_7[];
extern "C" char ONPREVIEW[];
extern "C" int g_beNDMWStatusCtrlD0_metaObject[4];
struct VC { virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();
 virtual void v96(); virtual void v100(int); virtual void v104(); virtual void v108(); virtual void v112(); virtual void v116(); virtual void v120(); virtual void v124(); virtual int v128(int); virtual void v132(); virtual void v136(int); virtual void v140(); virtual void v144(); virtual void v148(); virtual void v152(); virtual void v156(); virtual void v160(); virtual void v164(int); };
extern "C" void *g_stringPool[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef() : p(0) {}
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    StringRef(const StringRef &o) : p(o.p) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
    StringRef &operator=(const char *text) {
        if (g_stringPool[0] == 0) {
            void *pool = StringPool_Allocate(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        const char *token = StringPool_Intern(g_stringPool[0], text);
        const char *old = p;
        if (old) { int *h = (int *)old - 2; int r = ((int *)old)[-1] - 1; ((int *)old)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); }
        p = (char *)token;
        return *this;
    }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" StringRef StringList_CopyRetained(...);

/* Interns a string in the shared string pool; a null text interns as null. */
static inline const char *InternString(const char *text)
{
    const char *token;
    if (text == 0) {
        token = 0;
    } else {
        if (g_stringPool[0] == 0) {
            void *pool = StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        token = StringPool_Intern(g_stringPool[0], text);
    }
    return token;
}
struct H {
static inline int PickAlloc(beNDMWStatusCtrlBaseEquip *q) {
    int a = ((int)igObject_GetAllocator(q));
    int al;
    if (g_useOwnerAllocator != 0) { al = a; } else { al = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])); }
    return al;
}
static inline void SendName(beNDMWStatusCtrlBaseEquip *q) {
    StringRef sv(StringList_CopyRetained(igProperty_GetRecordStringList(q->_playerList, POWERSOCKETNAME_3)->_data, 0));
    beMessenger_SendNamed(q->_messenger, PLAYERARMS_2, sv.p, q->_playerNo, GENERATE_7);
}
static inline void AssignRef(int *slot, Obj *v) {
    Obj *old;
    if (v != 0) { v->_refCount = v->_refCount + 1; }
    old = (Obj *)*slot;
    if (old != 0) { --old->_refCount; if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old); }
    *slot = (int)v;
}
};
extern "C" void Gap__Bec__beNDMWStatusCtrlBaseEquip__vfunc_21(beNDMWStatusCtrlBaseEquip *p);
typedef struct Tbl { const char *s[12]; } __attribute__((aligned(16))) Tbl;
extern "C" char i_stcursor04[];
extern "C" char font002_2[];
extern "C" char font100_2[];
extern "C" char STWINFONT10[];
extern "C" char STWINFONT11[];
extern "C" char font101[];
extern "C" char font102[];
extern "C" char font103[];
extern "C" char font104[];
extern "C" int g_beNDMWStatus_metaObject[4];
extern "C" char TSUYOSA_2[];
extern "C" char KASHIKOSA_2[];
extern "C" char SEISHIN_2[];
extern "C" char SUBAYASA_2[];
extern "C" char RES_FIRE_2[];
extern "C" char RES_ICE_2[];
extern "C" char RES_THUNDER_2[];
extern "C" char RES_DARK_2[];
extern "C" char CHIMEIRITSU_2[];
extern "C" char HPDRAIN_2[];
extern "C" char MPDRAIN_2[];
extern "C" char CHOHATURITSU_2[];
/* An inventory item: kind at +8, equipped flag at +16. */
struct EquipItem : public igObject {
    
    int _kind;
    int _pad;
    unsigned char _equipped;
};
/* igObjectList of EquipItem pointers. */
struct ItemList : public igObject {
    
    int _count;
    int _capacity;
    EquipItem **_data;
};
struct StatusPanel : public igObject {
    
    int _insight;
    char _pad[0x6c];
    ItemList *_equipList;   /* +0x78 */
};
struct StrList;

struct StrList : public igObject {
    
    int _count;
};
extern "C" void beNDMWStatus_AssignEquipment(StatusPanel *self, ItemList *slotList, int slot, int equipIdx);
extern "C" char i_stpocket[];
extern "C" char SQ_0LINEOPEN[];
extern "C" char SQ_1LINEOPEN[];
extern "C" char SQ_2LINEOPEN[];
extern "C" char SQ_3LINEOPEN[];
extern "C" char SQ_4LINEOPEN_2[];
extern "C" char SQ_5LINEOPEN[];
extern "C" char NAME_3[];
extern "C" char TEXTSET_3[];
extern "C" char i_stsoubi[];
extern "C" char SQ_POWEROPEN[];
struct SlotKind { char p[24]; int lineCount; };
extern "C" void beNDMWStatusPowerSocket_PresentPanel(beNDMWStatusPowerSocket *self, int open);
extern "C" char COLOR[];
struct V3 { float x, y, z; };
struct L { char p[8]; int count; char p2[4]; int *data; };
class S { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v26(); char p4[4]; int w8; int w12; char p16[16]; int w32; char p36[64]; L *l100; };
extern "C" void beNDMWStatusPowerSocket_RefreshSlotList(S *arg0);
/* igObject-style string object: refcount, data pointer and length are not reflected fields */
struct Str : public igObject { int data; int len; };
extern "C" char *g_stringObjEmptyText[4];
extern "C" char TXT_2[];
extern "C" int g_beSystem_metaObject[4];
extern "C" void beNDMWStatusPowerSocket_ShowSlotDescription(beNDMWStatusPowerSocket *a);
extern "C" void beNDMWStatusPowerSocket_OpenSlotList(beNDMWStatusPowerSocket *arg0);
extern "C" void beNDMWStatusPowerSocket_RefreshPocket(beNDMWStatusPowerSocket *self);
extern "C" beNDMWStatusSelectE0 * beNDMWStatusSelectE0_Create(...);
extern "C" igBoolList *igBoolList_Create(void *allocator);
extern "C" char CANCELCOLOR_2[];
extern "C" unsigned char GPR_00554a0c;
extern "C" void beNDMWStatusPowerSocket_OpenSlotMenu(beNDMWStatusPowerSocket *arg0);
/* matching construct: dummy-virtual receivers (DW4VC_*) for the vX() calls */
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class DW4VC_132_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
extern "C" void beNDMWStatusPowerSocket_OnSlotMenuDecided(beNDMWStatusPowerSocket *arg0);
extern "C" int DAT_004cf6d0[4];

extern "C" beNDMWStatusCtrlD0 * beNDMWStatusCtrlD0_Create(...);
extern "C" void beNDMWStatusPowerSocket_OpenDeviceFolder(beNDMWStatusPowerSocket *arg0);

typedef struct PropertyRecord { char p12[12]; int f12; } PropertyRecord;
typedef struct PropertyRecordTable { char p16[16]; int *data; } PropertyRecordTable;
typedef struct PropertyRecordHolder { char p12[12]; PropertyRecordTable *f12; } PropertyRecordHolder;
extern "C" beDataObjIntList *igProperty_GetRecordIntList(...);
extern "C" char DIGIMONNO_3[];
extern "C" char SOUBI_2[];
extern "C" char SKILL_2[];
extern "C" char SKILLPOINT_2[];
extern "C" int beNDMWStatusPowerSocket_CanEquip(beNDMWStatusPowerSocket *arg0, int arg1);
/* matching construct: dummy-virtual class (38 slots) so vX() compiles to the retail vtable call; no data. */
class beNDMWStatusPowerSocketVTable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void vX(); };
extern "C" void beNDMWStatusPowerSocket_EquipSelected(beNDMWStatusPowerSocket *arg0);
extern "C" void beNDMWStatusPowerSocket_PreviewPocketDevice(beNDMWStatusPowerSocket *self, char *index, char *unusedArg2, int unusedArg3);
extern "C" void beNDMWStatusPowerSocket_EquipPocket(beNDMWStatusPowerSocket *self, char *unusedArg1, char *unusedArg2, char *unusedArg3);
extern "C" void beNDMWStatusPowerSocket_PreviewSlotDevice(beNDMWStatusPowerSocket *arg0, int arg1);
struct Item { char p[24]; int f24; };
struct List { char p[8]; int n; int pad; Item **data; };
struct Sh { char p[8]; int f8; char p2[8]; int f20; char p3[28]; int f52; char p4[28]; int f84; char p5[4]; int f92; char p6[4]; List *f100; };
struct Win : public igObject { char p[52]; int f60; int f64; char p2[16]; int f84; int f88; int f92; int f96; int f100; };
extern "C" void beNDMWStatusPowerSocket_OpenPocketList(Sh *arg0);
extern "C" void beNDMWStatusPowerSocket_ShowPocketDescription(beNDMWStatusPowerSocket *arg0);
extern "C" unsigned char GPR_00554a10;
extern "C" unsigned char GPR_00554a14;
extern "C" unsigned char GPR_00554a18;
extern "C" void beNDMWStatusPowerSocket_OpenPocketMenu(beNDMWStatusPowerSocket *arg0);
extern "C" int DAT_004cf6d8[4];
struct UnidentifiedChildWindow : public igObject { char p8[92]; igDataList *list; int f104; char f108; char pad109; char f110; };
extern "C" void beNDMWStatusPowerSocket_OpenPocketFolder(beNDMWStatusPowerSocket *arg0);
struct PowerSocketItem { char p[16]; char f16; };
struct PowerSocketList { char p[8]; int count; int pad; PowerSocketItem **items; };
struct PowerSocketView { char p[112]; PowerSocketList *list; PowerSocketList *getList() const { return list; } };
extern "C" void beNDMWStatusPowerSocket_ClearPocket(PowerSocketView *self);
extern "C" char SQ_MAINOPEN[];
extern "C" void beNDMWStatusMainSlot_PresentPanel(beNDMWStatusMainSlot *self, int open);
class S_415440 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v26(); char p4[4]; int w8; int w12; char p16[16]; int w32; char p36[68]; L *l100; };
extern "C" void beNDMWStatusMainSlot_RefreshSlotList(S_415440 *arg0);
/* reference-counted string-chunk header: refcount at +4, length at +12 */
struct RefCountedHeader : public igObject { int w8; int w12; };
/* Slot record: digit byte at +24. */
struct Slot { char p0[24]; int f24; };
/* Element-buffer list header: buffer pointer at +16. */
struct SlotList { char p[16]; Slot **arr; };
extern "C" void beNDMWStatusMainSlot_ShowSlotDescription(beNDMWStatusMainSlot *a);
extern "C" int g_beNDMWStatusMainSlot_metaObject[4];
extern "C" void beNDMWStatusMainSlot_OpenSlotList(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_RefreshPocket(beNDMWStatusMainSlot *self);
extern "C" unsigned char GPR_00554a1c;
extern "C" void beNDMWStatusMainSlot_OpenSlotMenu(beNDMWStatusMainSlot *arg0);
extern "C" void beNDMWStatusMainSlot_OnSlotMenuDecided(beNDMWStatusMainSlot *arg0);
extern "C" int DAT_004cf6e0[4];
extern "C" void beNDMWStatusMainSlot_OpenDeviceFolder(beNDMWStatusMainSlot *arg0);
extern "C" void beNDMWStatusMainSlot_PreviewPocketDevice(beNDMWStatusMainSlot * self, char * extra, char * unusedA, int unusedB);
extern "C" void beNDMWStatusMainSlot_EquipPocket(beNDMWStatusMainSlot * self, char * unusedA, char * unusedB, char * unusedC);
/* A property record: the value sits at +12. */
typedef struct PropertyRecord_4164d0 { char pad0[12]; int value; } PropertyRecord_4164d0;
extern "C" int g_beNDMWStatus_metaObject[4];
extern "C" char LEVEL_3[];
extern "C" char LVPOINT[];
extern "C" beDataObjInt *igProperty_GetRecord(...);
extern "C" int beNDMWStatusMainSlot_CanEquip(beNDMWStatusMainSlot *self, int index);
/* matching construct: dummy-virtual class (38 slots) so arg0->vX() compiles to the retail vtable call; data is read through the reflected view below. */
class beNDMWStatusMainSlotVTable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void vX(); };
extern "C" void beNDMWStatusMainSlot_EquipSelected(beNDMWStatusMainSlotVTable *arg0);
struct SlotKind_4168f0 { char p[24]; int startPoint; };
extern "C" void beNDMWStatusMainSlot_OpenPocketList(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_ShowPocketDescription(beNDMWStatusMainSlot *arg0);
extern "C" unsigned char GPR_00554a20;
extern "C" unsigned char GPR_00554a24;
extern "C" unsigned char GPR_00554a28;
extern "C" void beNDMWStatusMainSlot_OpenPocketMenu(beNDMWStatusMainSlot *arg0);
extern "C" int DAT_004cf6e8[4];
extern "C" void beNDMWStatusMainSlot_OpenPocketFolder(beNDMWStatusMainSlot *arg0);
extern "C" void beNDMWStatusMainSlot_ClearPocket(beNDMWStatusMainSlot *arg0);
extern "C" char SQ_SUBOPEN[];
extern "C" void beNDMWStatusSubSlot_PresentPanel(beNDMWStatusSubSlot *w, int arg1);
class S_417350 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v26(); char p4[4]; int w8; int w12; char p16[16]; int w32; char p36[72]; L *l100; };
extern "C" void beNDMWStatusSubSlot_RefreshSlotList(S_417350 *arg0);
extern "C" void beNDMWStatusSubSlot_ShowSlotDescription(beNDMWStatusSubSlot *a);
extern "C" int g_beNDMWStatusSubSlot_metaObject[4];
extern "C" void beNDMWStatusSubSlot_OpenSlotList(beNDMWStatusSubSlot *self);
extern "C" char font200[];
extern "C" char font201[];
extern "C" char font202[];
extern "C" char font203[];
extern "C" char font204[];
extern "C" void beNDMWStatusSubSlot_RefreshPocket(beNDMWStatusSubSlot *self);
extern "C" unsigned char GPR_00554a2c;

extern "C" void beNDMWStatusSubSlot_OpenSlotMenu(beNDMWStatusSubSlot *arg0);
extern "C" void beNDMWStatusSubSlot_OnSlotMenuDecided(beNDMWStatusSubSlot *arg0);
extern "C" int DAT_004cf6f0[4];
struct ElementBufferList { char p[8]; int n; int cap; int *data; int getN() const { return n; } };
/* window object: close-text lists at +60/+64 are beNDMWWindow fields; the rest (list at +104, flag bytes at +108/+110/+111) belongs to an unreflected subclass */
struct WindowObject : public igObject { char p8[52]; int f60; int f64; char p9[32]; ElementBufferList *list; int f104; char f108; char pad109; char f110; char f111; };
extern "C" void beNDMWStatusSubSlot_OpenDeviceFolder(beNDMWStatusSubSlot *arg0);
extern "C" void beNDMWStatusSubSlot_EquipSelected(beNDMWStatusSubSlot *self, char *unusedArg1, char *unusedArg2, char *unusedArg3);
extern "C" void beNDMWStatusSubSlot_PreviewSlotDevice(beNDMWStatusSubSlot *self, char *index, char *unusedArg2, int unusedArg3);
extern "C" int beNDMWStatusSubSlot_CanEquip(beNDMWStatusSubSlot *self, int entryIndex);
struct Rec { int p[3]; igObjectList *f12; };
extern "C" char STWINFONT13[];
extern "C" char txt_shop_lua[];
extern "C" char STWINFONT14_2[];
extern "C" char STWINFONT16[];
extern "C" char RIGHT_2[];
extern "C" char STWINFONT40[];
extern "C" char STWINFONT23[];
extern "C" char i_stfolder[];
extern "C" char SQ_AWINONOPEN[];
extern "C" char BANKDEVICE_2[];
typedef igObject RefHeader;
struct HA { static int Add(int a, int b) { return a + b; } };
struct DummyVirtual {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void v24(void *, void *); virtual int v25(); virtual int v26();
};
extern "C" void beNDMWStatusCtrlD0_Update(beNDMWStatusCtrlD0 *self);
extern "C" int equippedMark[4];
extern "C" int unequippedMark[4];
/* matching construct: raw view for the property-record folder (list at +12; no reflected class). */
struct RecordFolder { int w0; int w4; int w8; igDataList *list; };
extern "C" void beNDMWStatusCtrlD0_RefreshText(beNDMWStatusCtrlD0 *p0, int arg1, int arg2);
extern "C" char WU[];
extern "C" char BLUEAB[];
extern "C" int beNDMWStatusCtrlD0_UpdatePageCount(beNDMWStatusCtrlD0 *arg0);
/* matching construct: inline type-checked cast; its early return gives the retail empty-arm branch. */
struct FolderHelpers {
static beNDMWStatusCtrlD0 *CastTo(beNDMWStatusCtrlD0 *p) { if (p != 0) { if (igObject_IsKindOf(p, g_beNDMWStatusCtrlD0_metaObject[0]) != 0) { return p; } } return 0; }
static beNDMWStatusCtrlD0 *FindSub(beNDMWStatusCtrlFolder *w) { beNDMWStatusCtrlD0 *f = 0; int fi = 0; if (0 < ((igDataList *)w->_subWindow)->_count) { L:  f = CastTo(((beNDMWStatusCtrlD0 **)(*(igDataList **)&w->_subWindow)->_data)[fi]); if (f == 0) { fi++; if (fi < (*(igDataList **)&w->_subWindow)->_count) goto L; } } return f; }
};
extern "C" void beNDMWStatusCtrlFolder_Update(beNDMWStatusCtrlFolder *arg0);
extern "C" char GETCOMMON_6[];
extern "C" char FLAGFOLDER_2[];
extern "C" char SQ_FLAGOPEN[];
typedef struct PropertyRecordList { int p0, p4; int cnt; int cap; unsigned char *data; } PropertyRecordList;
typedef struct PropertyRecord_41a400 { char p[12]; PropertyRecordList *f12; } PropertyRecord_41a400;

extern "C" void beNDMWStatusCtrlFlag_Update(beNDMWStatusCtrlFlag *arg0);
extern "C" char DATABASE_7[];
extern "C" char impItem_2[];
extern "C" char GETDATABASE_7[];
extern "C" void beNDMWStatusCtrlFlag_RefreshText(beNDMWStatusCtrlFlag *arg0, int arg1, int arg2);
extern "C" unsigned char GPR_00554a30;
extern "C" unsigned char GPR_00554a34;
extern "C" int DAT_004cf700[12];
extern "C" char SQ_OPEN00[];
extern "C" char SQ_OPEN01[];
extern "C" char SQ_OPEN02[];
extern "C" char SQ_OPEN03[];
extern "C" char SQ_OPEN04[];
extern "C" char SQ_OPEN05[];
extern "C" char SQ_OPEN06[];
extern "C" char SQ_OPEN07[];
extern "C" char SQ_OPEN08[];
extern "C" char SQ_OPEN09[];
extern "C" char SQ_OPEN10[];
extern "C" char SQ_OPEN11[];
extern "C" char DISKFOLDER_3[];
extern "C" char SQ_AWINOFFOPEN[];
extern "C" char STWINFONT15[];
extern "C" char i_stmenu02[];
extern "C" char STWINFONT26[];
extern "C" char ISUSE_7[];
extern "C" char SQ_1ITEMOPEN[];
extern "C" char SQ_2ITEMOPEN[];
extern "C" char SQ_3ITEMOPEN[];
extern "C" char STWINFONT39[];
extern "C" char PLAYERNAME_3[];
extern "C" char CENTER_2[];
extern "C" char STWINFONT38[];
extern "C" char text_0[];
typedef unsigned __int128 Q128;
struct Str3 { const char *v[3]; };
extern "C" Str3 DAT_004cf730;
static inline void ReleaseObject(igObject *o)
{
    if (o) {
        --o->_refCount;
        if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o);
    }
}
class SwapRef {
public:
    igObject *p;
    SwapRef(void *o) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    ~SwapRef() { ReleaseObject((igObject *)p); }
};
class DeviceRef {
public:
    igObject *p;
    DeviceRef(void *o) : p((igObject *)o) {}
    DeviceRef(void *o, RetainReference) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    DeviceRef(const DeviceRef &r) : p(r.p) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~DeviceRef() { ReleaseObject((igObject *)p); }
};
extern "C" void beNDMWWindow_QueueObjectText(void *, void *, const char *, const DeviceRef &, void *);
struct Q48 { Q128 q[3]; };
extern "C" void beNDMWStatusCtrlDisk_Update(beNDMWStatusCtrlDisk *self);
extern "C" void StringRefList_ResetRange(igStringRefList *arg0, int arg1, int arg2);
extern "C" void ObjectList_ZeroRange(igObjectList *arg0, int arg1, int arg2);
extern "C" void ObjectList_ReleaseRange(igObjectList *arg0, int arg1, int arg2);
extern "C" void **ObjectRef_AssignRetained(void **arg0, igObject *arg1);
extern "C" void beNDMWStatusCtrlDisk_RefreshText(beNDMWStatusCtrlDisk *arg0, int arg1, int arg2);
struct ChildWindow;
extern "C" char NINZU_4[];
typedef struct PropertyRecord_41d810 { char p[12]; unsigned char f12; } PropertyRecord_41d810;
typedef struct ChildWindow : public igObject { char p8[52]; int f60; int f64; char p68[24]; int f92; } ChildWindow;

extern "C" void beNDMWStatusCtrlBit_Update(beNDMWStatusCtrlBit *arg0);
typedef struct { int v[3]; } Tri;
extern "C" Tri DAT_004cf740[4];
extern "C" Tri DAT_004cf750[4];
extern "C" char SQ_1BITOPEN[];
extern "C" char SQ_2BITOPEN[];
extern "C" char SQ_3BITOPEN[];
extern "C" char STWINFONT28[];
extern "C" char STWINFONT27[];
extern "C" char BIT_5[];
extern "C" char percent_d_3[];
extern "C" char font_03d[];
extern "C" char ALIGN_2[];
extern "C" char SELECTCTRL_2[];
extern "C" char i_stcursor03[];
extern "C" char ISSELECTNOW[];
extern "C" char SOUND_4[];
extern "C" char CURSOR_MOVE[];
extern "C" char PLAY_3[];
typedef igObject RefObj;
/* Interned-string reference (count at p[-1], header at p[-2]). */
/* matching construct: allocator selection inlined as in retail (object allocator when the global flag is set, else selector 0x587110) */
struct H_41de40 {
static inline int AllocFor(beNDMWStatusCtrlSendBit *q) {
    int base = ((int)igObject_GetAllocator(q));
    int al;
    if (g_useOwnerAllocator != 0) { al = base; } else { al = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])); }
    return al;
}

static inline void AddTextType(beNDMWStatusCtrlSendBit *q, const char *s) {
    void *v;
    int t;
    if (s == 0) { v = (void *)0; } else { if (((int *)g_stringPool)[0] == 0) { t = ((int)StringPool_Allocate(0x10)); if (t != 0) { t = ((int)StringPool_Construct(t)); } ((int *)g_stringPool)[0] = t; } v = ((void *)StringPool_Intern(((int *)g_stringPool)[0], s)); }
    StringRef sv(v);
    StringList_AppendRetained(q->_textCloseTypeList, sv);
}

static inline void AddTextName(beNDMWStatusCtrlSendBit *q, const char *s) {
    void *v;
    int t;
    if (s == 0) { v = (void *)0; } else { if (((int *)g_stringPool)[0] == 0) { t = ((int)StringPool_Allocate(0x10)); if (t != 0) { t = ((int)StringPool_Construct(t)); } ((int *)g_stringPool)[0] = t; } v = ((void *)StringPool_Intern(((int *)g_stringPool)[0], s)); }
    StringRef sv(v);
    StringList_AppendRetained(q->_textCloseNameList, sv);
}

};
extern "C" void beNDMWStatusCtrlSendBit_Update(beNDMWStatusCtrlSendBit *p);
extern "C" int g_beNDMWStatusSelectE1_metaObject[4];
extern "C" char SQ_BWINONOPEN[];
extern "C" char SQ_BWINOFFOPEN[];
extern "C" char SQ_WAZAOPEN[];
extern "C" char STWINFONT24[];
extern "C" char STWINFONT42[];
extern "C" char STWINFONT18[];
extern "C" char WAZALIST_2[];
extern "C" char STWINFONT12[];
struct VC_41f190 { virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21(); virtual void v22(void *, void *); virtual int v23(); virtual int v24(); };
/* Interned-string reference (count at p[-1], header at p[-2]). */
struct H_41f190 {
static inline int intern(int *s)
{
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (((int *)g_stringPool)[0] == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool)
                pool = ((int)StringPool_Construct(pool));
            ((int *)g_stringPool)[0] = pool;
        }
        ref = ((int)StringPool_Intern(((int *)g_stringPool)[0], s));
    }
    return ref;
}
static inline void release(int ref)
{
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
}
static inline void ClearStrList(int listHandle)
{
    igStringRefList *l = (igStringRefList *)listHandle;
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (((int *)g_stringPool)[0] == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool) pool = ((int)StringPool_Construct(pool));
            ((int *)g_stringPool)[0] = pool;
        }
        ref = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        *slot = ref;
    }
    l->_count = 0;
}

static inline int PickAllocator(void *obj)
{
    int a = ((int)igObject_GetAllocator(obj));
    return g_useOwnerAllocator != 0 ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
}

static inline int Scale(int v)
{
    int r = v < 37 ? v * 30 : v < 108 ? v * 20 + 360 : v < 228 ? v * 10 + 1430 : v * 8 + 1884;
    return r;
}

};
extern "C" void beNDMWStatusCtrlSkill_Update(beNDMWStatusCtrlSkill *self);
extern "C" char Lv[];
extern "C" char shinka_3[];
extern "C" char EXPLANATION[];
extern "C" void beNDMWStatusCtrlSkill_RefreshText(beNDMWStatusCtrlSkill *self, int refreshRows, int refreshText);
struct ModelNames { int v[12]; };
extern "C" ModelNames DAT_004cf760;
extern "C" char ISHAKAI[];
extern "C" char ISJYOUDO[];
extern "C" char SQ_1CHIPOPEN[];
extern "C" char SQ_2CHIPOPEN[];
extern "C" char SQ_3CHIPOPEN[];
extern "C" Str3 DAT_004cf790;
class ItemListRef {
public:
    igObject *p;
    ItemListRef(void *fresh) : p((igObject *)fresh) {}
    ItemListRef(igObjectList *shared) : p((igObject *)shared) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~ItemListRef() { ReleaseObject((igObject *)p); }
};
class MovedItemRef {
public:
    igObject *p;
    MovedItemRef(void *o) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    ~MovedItemRef() { ReleaseObject((igObject *)p); }
};
struct Helpers {
static inline void AppendBoth(ItemListRef &dst, igObjectList *a, igObjectList *b)
{
    int i, j;
    for (i = 0; i < a->_count; i++) {
        int *e = (int *)((int *)a->_data)[i];
        if (e != 0) ObjectList_AppendRetained(dst.p, e);
        if (i == 0) {
            for (j = 0; j < b->_count; j++) {
                int *e2 = (int *)((int *)b->_data)[j];
                if (e2 != 0) ObjectList_AppendRetained(dst.p, e2);
            }
        }
    }
}
};
struct RemovedSlot { int index; };
extern "C" RemovedSlot ObjectList_RemoveFirstRetained(void *, int, int);
extern "C" void List_RemoveWordAt(void *, int);
class ItemListRef;
class DeviceRef;
extern "C" void beNDMWStatusSubMenu_SortByRevision(void *, const ItemListRef &);
extern "C" void beNDMWStatusSubMenu_SortByRecordNo(void *, const ItemListRef &);
extern "C" void beNDMWStatusSubMenu_Update(beNDMWStatusSubMenu *self);
extern "C" int g_beNDMWStatusSubMenu_metaObject[4];
extern "C" int g_beNDMWStatusCtrlSkill_metaObject[4];
extern "C" int g_beNDMWStatusCtrlSendBit_metaObject[4];
extern "C" int g_beNDMWStatusCtrlBit_metaObject[4];
extern "C" int g_beNDMWStatusCtrlDisk_metaObject[4];
extern "C" int g_beNDMWStatusCtrlFlag_metaObject[4];
extern "C" int g_beNDMWStatusCtrlFolder_metaObject[4];
extern "C" int g_beNDMWStatusCtrlD0_metaObject[4];
extern "C" int g_beNDMWStatusPowerSocket_metaObject[4];
extern "C" int g_beNDMWStatusCtrlBaseEquip_metaObject[4];
extern "C" int g_beNDMWStatusCtrlEquip_metaObject[4];
extern "C" int g_beNDMWStatusCtrl00_metaObject[4];

/* Window step state: _st0 is the phase (0 open, 1 run, 2 close, 3 wait for the close), _st1/_st2 the
 * nested steps and _st3 a per-step scratch value; entering a step clears the levels below it. */
template <class Window> static inline void SetStep0(Window *window, int step)
{
    window->_st0 = step;
    window->_st3 = 0;
    window->_st2 = 0;
    window->_st1 = 0;
}

template <class Window> static inline void SetStep1(Window *window, int step)
{
    window->_st1 = step;
    window->_st3 = 0;
    window->_st2 = 0;
}

template <class Window> static inline void SetStep2(Window *window, int step)
{
    window->_st2 = step;
    window->_st3 = 0;
}

/* The allocator new child windows come from. */
static inline void *WindowAllocator(void *owner)
{
    void *allocator = igObject_GetAllocator(owner);
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
}

/* Number of child windows; a child that finished has removed itself from the list. */
#define CHILD_COUNT(window) (((igObjectList *)(window)->_subWindow)->_count)

/* The reference release as retail expands it in these windows: the count is decremented in place and
 * its low 23 bits are tested as a 64-bit value. */
#define RELEASE_REFERENCE(object) { \
    if (object) { \
        --(object)->_refCount; \
        if (((unsigned long long)(long long)(int)(object)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(object); \
    } }

/* The first child window of a class (the result's type is the caller's), or null. */
#define FIND_CHILD(found, window, metaObject) { \
    int i_; \
    int child_ = 0; \
    for (i_ = 0; i_ < CHILD_COUNT(window); i_++) { \
        child_ = ((int *)((igObjectList *)(window)->_subWindow)->_data)[i_]; \
        if (child_ == 0 || igObject_IsKindOf(child_, metaObject) == 0) child_ = 0; \
        if (child_ != 0) break; \
    } \
    (found) = (beNDMWStatusCtrlD0 *)child_; }

/* Asks MODELCTRL whether `model` is playing `sequence`; the answer is read with beMessenger_GetBool. */
template <class Window> static inline void QueryModelSequence(Window *window, const char *model, const char *sequence)
{
    beMessenger_SelectReceivers(window->_messenger, MODELCTRL_3, model, 0);
    beMessenger_AppendString(window->_messenger, sequence);
    beMessenger_DispatchSelected(window->_messenger, ISSEQNAME_4);
}

/* Shows or hides a background layer through LAYERCTL. */
template <class Window> static inline void SwitchLayer(Window *window, const char *layer, const char *onOff)
{
    beMessenger_SelectGroup(window->_messenger, LAYERCTL);
    beMessenger_AppendString(window->_messenger, layer);
    beMessenger_AppendString(window->_messenger, onOff);
    beMessenger_DispatchSelected(window->_messenger, SWITCH_4);
}

/* Virtual slots 0-21, which every window class inherits; 20 is GetMeta and 21 the per-frame Update. */
class beNDMWWindowVirtuals {
public:
    virtual void InheritedSlot0(); virtual void InheritedSlot1(); virtual void InheritedSlot2();
    virtual void InheritedSlot3(); virtual void InheritedSlot4(); virtual void InheritedSlot5();
    virtual void InheritedSlot6(); virtual void InheritedSlot7(); virtual void InheritedSlot8();
    virtual void InheritedSlot9(); virtual void InheritedSlot10(); virtual void InheritedSlot11();
    virtual void InheritedSlot12(); virtual void InheritedSlot13(); virtual void InheritedSlot14();
    virtual void InheritedSlot15(); virtual void InheritedSlot16(); virtual void InheritedSlot17();
    virtual void InheritedSlot18(); virtual void InheritedSlot19();
    virtual int GetMeta();
    virtual void Update();
};

/* The equipment panels' own slots: beNDMWStatusCtrlBaseEquip's Update drives them and
 * beNDMWStatusPowerSocket, beNDMWStatusMainSlot and beNDMWStatusSubSlot implement them. */
class EquipPanelVirtuals : public beNDMWWindowVirtuals {
public:
    virtual void RefreshPocket();
    virtual void PresentPanel(int open);
    virtual void RefreshSlotList();
    virtual void OpenSlotList();
    virtual void ShowSlotDescription();
    virtual void OpenSlotMenu();
    virtual void OnSlotMenuDecided();
    virtual void OpenDeviceFolder();
    virtual int CanEquip(int index);
    virtual void EquipSelected();
    virtual void PreviewSlotDevice(int index);
    virtual void OpenPocketList();
    virtual void ShowPocketDescription();
    virtual void OpenPocketMenu();
    virtual void OpenPocketFolder();
    virtual void EquipPocket();
    virtual void ClearPocket();
    virtual void PreviewPocketDevice(int index);
};

static inline EquipPanelVirtuals *AsEquipPanel(beNDMWStatusCtrlBaseEquip *panel)
{
    return (EquipPanelVirtuals *)panel;
}

/* SUBWND_2 messages carry the player number: OFPREVIEW and ONPREVIEW end and show the stat preview
 * of a device, UPDATE redraws the status sub-windows. */
template <class Window> static inline void SendSubWindowCommand(Window *window, const char *command)
{
    beMessenger_SelectGroup(window->_messenger, SUBWND_2);
    beMessenger_AppendInt(window->_messenger, window->_playerNo);
    beMessenger_DispatchSelected(window->_messenger, command);
}

/* GAMERAM: recompute the player's stats from the equipment. */
template <class Window> static inline void RecalcPlayer(Window *window)
{
    beMessenger_SelectReceivers(window->_messenger, GAMERAM_9, 0, 0);
    beMessenger_AppendInt(window->_messenger, window->_playerNo);
    beMessenger_DispatchSelected(window->_messenger, RECALCPLAYER_4);
}

/* GAMERAM: select a player's data object, read back with beMessenger_GetObject. */
template <class Window> static inline void SelectPlayer(Window *window, int playerNo)
{
    beMessenger_SelectGroup(window->_messenger, GAMERAM_9);
    beMessenger_AppendInt(window->_messenger, playerNo);
    beMessenger_DispatchSelected(window->_messenger, GETPLAYER_6);
}

/* TEXTCTL command without a value (DEFAULTCOLOR, CANCELCOLOR) to a text cell. */
template <class Window> static inline void SendCellCommand(Window *window, const char *textType, const char *cell, const char *command)
{
    beMessenger_SelectGroup(window->_messenger, TEXTCTL_5);
    beMessenger_AppendString(window->_messenger, textType);
    beMessenger_AppendString(window->_messenger, cell);
    beMessenger_DispatchSelected(window->_messenger, command);
}

/* Holds a new reference to `object` in `*slot`, releasing the one it replaces. */
static inline void AssignReference(int *slot, igObject *object)
{
    igObject *old;
    if (object != 0) { object->_refCount = object->_refCount + 1; }
    old = (igObject *)*slot;
    RELEASE_REFERENCE(old);
    *slot = (int)object;
}

static inline void BoolList_Append(igBoolList *list, const bool &value)
{
    int count = list->_count;
    if (count < list->_capacity) {
        list->_count = count + 1;
    } else {
        List_Resize(list, count + 1, 1);
    }
    ((bool *)list->_data)[count] = value;
}

static inline void BoolList_Set(igBoolList *list, int index, const bool &value)
{
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((bool *)list->_data)[index] = value;
    }
}

/* Stores `object` at `index` of an object list with a new reference, releasing the old one. */
static inline void ObjectList_Set(igObjectList *list, int index, igObject *object)
{
    igObject *old;
    if (object != 0) { object->_refCount = object->_refCount + 1; }
    old = ((igObject **)list->_data)[index];
    RELEASE_REFERENCE(old);
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((igObject **)list->_data)[index] = object;
    }
}

/* Generates the PLAYERARMS_2 model for the name of the power chip in socket 0. */
static inline void SendPowerSocketName(beNDMWStatusCtrlBaseEquip *self)
{
    StringRef name(StringList_CopyRetained(igProperty_GetRecordStringList(self->_playerList, POWERSOCKETNAME_3)->_data, 0));
    beMessenger_SendNamed(self->_messenger, PLAYERARMS_2, name.p, self->_playerNo, GENERATE_7);
}

/* The player's status record service (the insight's beNDMWStatus). */
static inline int FindStatus(int insight)
{
    return igInsightCore_FindManager(insight, g_beNDMWStatus_metaObject[0]);
}

/* Item `index` of an item list held as an object reference. */
static inline beNDMWItemBase *ItemAt(int itemList, int index)
{
    return ((beNDMWItemBase **)((beNDMWItemBaseList *)itemList)->_data)[index];
}

/* TEXTCTL messages to a window's text cell (text type, cell name). */
template <class Window> static inline void SetCellText(Window *window, const char *textType, const char *cell, const char *text)
{
    beMessenger_SelectGroup(window->_messenger, TEXTCTL_5);
    beMessenger_AppendString(window->_messenger, textType);
    beMessenger_AppendString(window->_messenger, cell);
    beMessenger_AppendString(window->_messenger, text);
    beMessenger_DispatchSelected(window->_messenger, TEXTSET_3);
}

template <class Window> static inline void SwitchCell(Window *window, const char *textType, const char *cell, const char *onOff)
{
    beMessenger_SelectGroup(window->_messenger, TEXTCTL_5);
    beMessenger_AppendString(window->_messenger, textType);
    beMessenger_AppendString(window->_messenger, cell);
    beMessenger_AppendString(window->_messenger, onOff);
    beMessenger_DispatchSelected(window->_messenger, SWITCH_4);
}

/* Create the previous/next page arrow models. The left arrow starts hidden; the right arrow is
 * shown when the list spans more than one page (_maxPage) and hidden otherwise. */
void Gap__Bec__beNDMWListCtrl__vfunc_22(beNDMWListCtrl *self,const float *leftArrowPos,const float *rightArrowPos){
    float leftPos[4],rightShownPos[4],rightHiddenPos[4];
    leftPos[0]=leftArrowPos[0];leftPos[1]=leftArrowPos[1];leftPos[2]=leftArrowPos[2];
    beNDMWWindow_PresentModel(self,i_stcursorleft,0,SQ_HIDE,SQ_CLOSE_3,leftPos);
    if(self->_maxPage>1){
        rightShownPos[0]=rightArrowPos[0];rightShownPos[1]=rightArrowPos[1];rightShownPos[2]=rightArrowPos[2];
        beNDMWWindow_PresentModel(self,i_stcursorright,0,SQ_SELECT,SQ_CLOSE_3,rightShownPos);
    }else{
        rightHiddenPos[0]=rightArrowPos[0];rightHiddenPos[1]=rightArrowPos[1];rightHiddenPos[2]=rightArrowPos[2];
        beNDMWWindow_PresentModel(self,i_stcursorright,0,SQ_HIDE,SQ_CLOSE_3,rightHiddenPos);
    }
}

/* Previous page. */
bool Gap__Bec__beNDMWListCtrl__vfunc_23(beNDMWListCtrl *self){
    bool changed;
    bool upDownHeld;
    unsigned stickRepeat;
    unsigned stickTrigger;
    unsigned trigger;
    unsigned repeat;
    unsigned stickHeld;
    bool leftPressed;
    bePadData *pad;
    pad=bePadManager_GetPadForPlayer(self->_padManager,self->_playerNo);
    trigger=pad->_trigger;repeat=pad->_repeat;stickHeld=pad->_lStk;stickTrigger=pad->_lTrg;stickRepeat=pad->_lRpt;
    leftPressed=true;
    if(!((stickTrigger|stickRepeat)&STICK_LEFT)){
        if(!((trigger|repeat)&BUTTON_LEFT)){
            leftPressed=false;
        }
    }
    upDownHeld=true;if(!(stickHeld&STICK_UP)&&!(stickHeld&STICK_DOWN)){upDownHeld=false;}
    changed=false;
    if(self->_nowPage>0&&leftPressed&&!upDownHeld){
        self->_nowPage--;changed=true;
        if(self->_nowPage==0){
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_MOVEEND);
        }else{
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_MOVENEXT);
        }
        beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_SELECT);
    }
    return changed;
}

/* Next page. */
bool Gap__Bec__beNDMWListCtrl__vfunc_24(beNDMWListCtrl *self){
    bool changed;
    bool upDownHeld;
    unsigned stickRepeat;
    unsigned stickTrigger;
    unsigned trigger;
    unsigned stickHeld;
    bool rightPressed;
    unsigned repeat;
    int page;
    bePadData *pad;
    pad=bePadManager_GetPadForPlayer(self->_padManager,self->_playerNo);
    trigger=pad->_trigger;repeat=pad->_repeat;stickHeld=pad->_lStk;stickTrigger=pad->_lTrg;stickRepeat=pad->_lRpt;
    rightPressed=true;
    if(!((stickTrigger|stickRepeat)&STICK_RIGHT)){
        if(!((trigger|repeat)&BUTTON_RIGHT)){
            rightPressed=false;
        }
    }
    upDownHeld=true;if(!(stickHeld&STICK_UP)&&!(stickHeld&STICK_DOWN)){upDownHeld=false;}
    changed=false;
    page=self->_nowPage;
    if(page<(self->_maxPage-1)&&rightPressed&&!upDownHeld){
        self->_nowPage=(page+1);changed=true;
        if(self->_nowPage==(self->_maxPage-1)){
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_MOVEEND);
        }else{
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_MOVENEXT);
        }
        beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_SELECT);
    }
    return changed;
}

/* The status screen root: opens the title windows over the hidden field layers, runs the status menu
 * (equipment, folder, skill) and restores the layers when the menu closes. */
void beNDMWStatusCtrl00_Update(beNDMWStatusCtrl00 *self) {
    if (self->_st0 != 3) {
        switch (self->_st0) {
        case 0:
            switch (self->_st1) {
            case 0:
                {
                    igSmartPointer<beNDMWStatusTitle00> title(beNDMWStatusTitle00_Create(WindowAllocator(self)));
                    beNDMWWindow_BindContext(title.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, title.p);
                }
                SetStep1(self, self->_st1 + 1);
                return;
            case 1:
                QueryModelSequence(self, i_stback, SQ_OPEN_5);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                    SwitchLayer(self, BG01, DISPOFF_2);
                    SwitchLayer(self, BG02, DISPOFF_2);
                    SwitchLayer(self, BG03, DISPOFF_2);
                    SwitchLayer(self, GM01, DISPOFF_2);
                    SwitchLayer(self, GM03, DISPOFF_2);
                    {
                        igSmartPointer<beNDMWStatusTitle01> title(beNDMWStatusTitle01_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(title.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, title.p);
                    }
                    {
                        igSmartPointer<beNDMWStatusTitle02> title(beNDMWStatusTitle02_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(title.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, title.p);
                    }
                    {
                        igSmartPointer<beNDMWStatusTitle03> title(beNDMWStatusTitle03_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(title.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, title.p);
                    }
                    self->_statusMenu = 0;
                    SetStep1(self, self->_st1 + 1);
                    return;
                }
                break;
            case 2:
                QueryModelSequence(self, i_messwn, SQ_STOPEN);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                    SetStep0(self, self->_st0 + 1);
                    return;
                }
                break;
            }
            break;
        case 1:
            switch (self->_st1) {
            case 0:
                switch (self->_st2) {
                case 0: {
                    {
                        igSmartPointer<beNDMWStatusSelect00> menu(beNDMWStatusSelect00_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, menu.p);
                        menu.p->_startPoint = self->_statusMenu;
                        beNDMWWindow_QueueText(menu.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    SetStep2(self, self->_st2 + 1);
                }
                case 1:
                    SetStep2(self, self->_st2 + 1);
                case 2:
                    if (CHILD_COUNT(self) != self->_nowProcKazu) {
                        if (self->_retCode != -1) self->_statusMenu = self->_retCode;
                        switch (self->_retCode) {
                        case 0: SetStep1(self, 1); return;
                        case 1: SetStep1(self, 2); return;
                        case 2: SetStep1(self, 3); return;
                        default: SetStep1(self, 4); return;
                        }
                    }
                    break;
                }
                break;
            case 1:
                switch (self->_st2) {
                case 0: {
                    {
                        igSmartPointer<beNDMWStatusCtrlEquip> equip(beNDMWStatusCtrlEquip_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(equip.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, equip.p);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    SetStep2(self, self->_st2 + 1);
                }
                case 1:
                    if (CHILD_COUNT(self) != self->_nowProcKazu) {
                        SetStep1(self, 0);
                        return;
                    }
                    break;
                }
                break;
            case 2:
                switch (self->_st2) {
                case 0: {
                    {
                        igSmartPointer<beNDMWStatusCtrlFolder> folder(beNDMWStatusCtrlFolder_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(folder.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, folder.p);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    SetStep2(self, self->_st2 + 1);
                }
                case 1:
                    if (CHILD_COUNT(self) != self->_nowProcKazu) {
                        SetStep1(self, 0);
                        return;
                    }
                    break;
                }
                break;
            case 3:
                switch (self->_st2) {
                case 0: {
                    {
                        igSmartPointer<beNDMWStatusCtrlSkill> skill(beNDMWStatusCtrlSkill_Create(WindowAllocator(self)));
                        beNDMWWindow_BindContext(skill.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, skill.p);
                    }
                    self->_nowProcKazu = CHILD_COUNT(self);
                    SetStep2(self, self->_st2 + 1);
                }
                case 1:
                    if (CHILD_COUNT(self) != self->_nowProcKazu) {
                        SetStep1(self, 0);
                        return;
                    }
                    break;
                }
                break;
            case 4:
                switch (self->_st2) {
                case 0: {
                    int count = CHILD_COUNT(self);
                    int i;
                    for (i = 1; i < count; i++) {
                        beNDMWWindow *child = ((beNDMWWindow **)((igObjectList *)self->_subWindow)->_data)[i];
                        if (child->_st0 < 2) SetStep0(child, 2);
                    }
                    SetStep2(self, self->_st2 + 1);
                    return;
                }
                case 1:
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_messwn, 0, ISRUN_5);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                        SwitchLayer(self, BG01, DISPON_2);
                        SwitchLayer(self, BG02, DISPON_2);
                        SwitchLayer(self, BG03, DISPON_2);
                        SwitchLayer(self, GM01, DISPON_2);
                        SwitchLayer(self, GM03, DISPON_2);
                        SetStep0(self, self->_st0 + 1);
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
            SetStep0(self, self->_st0 + 1);
            return;
        }
    } else if (beNDMWWindow_PollCloseComplete(self) != 0) {
        self->_isRun = 0;
    }
}

/* Equipment menu: power socket, main slot and sub slot panels. Opened from the status menu
 * (_entCode 0) or from a shop (_entCode 1), which picks the title window and the model the menu
 * waits for. */
void beNDMWStatusCtrlEquip_Update(beNDMWStatusCtrlEquip *self)
{
    switch (self->_st0) {
    case 0:
        switch (self->_entCode) {
        case 0:
        default: {
            igSmartPointer<beNDMWStatusTitle04> title(beNDMWStatusTitle04_Create(WindowAllocator(self)));
            beNDMWWindow_BindContext(title.p, self, self->_insight, self->_playerNo, 30);
            ObjectList_AppendRetained(self->_subWindow, title.p);
            break;
        }
        case 1: {
            igSmartPointer<beNDMWStatusTitle02> title(beNDMWStatusTitle02_Create(WindowAllocator(self)));
            beNDMWWindow_BindContext(title.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, title.p);
            break;
        }
        }
        self->_equipMenu = 0;
        SetStep0(self, self->_st0 + 1);
        return;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0: {
                const char *model;
                const char *sequence;
                switch (self->_entCode) {
                default:
                    model = i_sttitle;
                    sequence = SQ_OPEN_5;
                    break;
                case 1:
                    model = i_messwn;
                    sequence = SQ_STOPEN;
                    break;
                }
                QueryModelSequence(self, model, sequence);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xff) == 1) return;
                {
                    igSmartPointer<beNDMWStatusSelect01> menu(beNDMWStatusSelect01_Create(WindowAllocator(self)));
                    beNDMWWindow_BindContext(menu.p, self, self->_insight, self->_playerNo, 31);
                    ObjectList_AppendRetained(self->_subWindow, menu.p);
                    menu.p->_startPoint = self->_equipMenu;
                    beNDMWWindow_QueueText(menu.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                SetStep2(self, self->_st2 + 1);
            }
            case 1:
                if (self->_retCode != -1)
                    beNDMWWindow_RunMessageScript(self, txt_status_lua_2, self->_retCode + 35);
                SetStep2(self, self->_st2 + 1);
                self->_st3 = self->_retCode;
            case 2:
                if (CHILD_COUNT(self) == self->_nowProcKazu) {
                    if (self->_retCode == -1) return;
                    if (self->_st3 == self->_retCode) return;
                    SetStep2(self, 1);
                    return;
                }
                if (self->_retCode != -1) self->_equipMenu = self->_retCode;
                switch (self->_retCode) {
                case 0:
                    SetStep1(self, 1);
                    return;
                case 1:
                    SetStep1(self, 2);
                    return;
                case 2:
                    SetStep1(self, 3);
                    return;
                default:
                    SetStep0(self, self->_st0 + 1);
                    return;
                }
            }
            break;
        case 1:
        case 2:
        case 3:
            switch (self->_st2) {
            case 0: {
                {
                    igSmartPointer<beNDMWStatusCtrlBaseEquip> panel(0);
                    switch (self->_st1) {
                    case 1: {
                        void *allocator = WindowAllocator(self);
                        { igObject *old = panel.p; RELEASE_OBJ(old) }
                        panel.p = (beNDMWStatusCtrlBaseEquip *)beNDMWStatusPowerSocket_Create(allocator);
                        panel.p->_kindListMax = 3;
                        break;
                    }
                    case 2: {
                        void *allocator = WindowAllocator(self);
                        { igObject *old = panel.p; RELEASE_OBJ(old) }
                        panel.p = (beNDMWStatusCtrlBaseEquip *)beNDMWStatusMainSlot_Create(allocator);
                        break;
                    }
                    case 3: {
                        void *allocator = WindowAllocator(self);
                        { igObject *old = panel.p; RELEASE_OBJ(old) }
                        panel.p = (beNDMWStatusCtrlBaseEquip *)beNDMWStatusSubSlot_Create(allocator);
                        break;
                    }
                    }
                    beNDMWWindow_BindContext(panel.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, panel.p);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                SetStep2(self, self->_st2 + 1);
            }
            case 1:
                if (CHILD_COUNT(self) != self->_nowProcKazu) {
                    self->_retCode = self->_equipMenu;
                    SetStep1(self, 0);
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
        SetStep0(self, self->_st0 + 1);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) self->_isRun = 0;
        break;
    }
}

void Gap__Bec__beNDMWStatusCtrlBaseEquip__vfunc_21(beNDMWStatusCtrlBaseEquip *p)
{
    switch (p->_st0) {
    default: return;
    case 0: {
        igObject *player;
        SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
        player = (igObject *)beMessenger_GetObject(p->_messenger, 0);
        AssignReference(&p->_playerList, player);
        AssignReference(&p->_powerSocket, (igObject *)igProperty_GetRecordFolder(p->_playerList, POWERSOCKET_3)->_data);
        AssignReference(&p->_mainSlot, (igObject *)igProperty_GetRecordFolder(p->_playerList, MAINSLOT_3)->_data);
        AssignReference(&p->_subSlot, (igObject *)igProperty_GetRecordFolder(p->_playerList, SUBSLOT_3)->_data);
        AssignReference(&p->_wpuPocket, (igObject *)igProperty_GetRecordFolder(p->_playerList, POWERPOCKET_3)->_data);
        AssignReference(&p->_apuPocket, (igObject *)igProperty_GetRecordFolder(p->_playerList, MAINPOCKET_3)->_data);
        AssignReference(&p->_deviceFolder, (igObject *)igProperty_GetRecordFolder(p->_playerList, DEVICEFOLDER_3)->_data);
        switch (p->_st1) { case 0: AsEquipPanel(p)->PresentPanel(1); beNDMWStatusCtrlBaseEquip_QueuePanelText(p); break; default: beNDMWStatusCtrlBaseEquip_ShowKindCursor(p, -1); break; }
        {
            igSmartPointer<beNDMWStatusSelectE1> h(beNDMWStatusSelectE1_Create(WindowAllocator(p)));
            beNDMWWindow_BindContext(h.p, p, p->_insight, p->_playerNo, 0);
            ObjectList_AppendRetained(p->_subWindow, h.p);
            h.p->_selectMax = p->_kindListMax;
            { float *q = h.p->_offsetPos; q[0] = -83.0f; q[1] = 148.0f; q[2] = 0.0f; }
            h.p->_startPoint = p->_kindListPos;
        }
        p->_nowProcKazu = CHILD_COUNT(p);
        SetStep0(p, p->_st0 + 1);
        SetStep1(p, 0);
        return;
    }
    case 1:
        switch (p->_st1) {
        case 0:
            switch (p->_st2) {
            case 0:
                AsEquipPanel(p)->RefreshSlotList();
                SetStep2(p, p->_st2 + 1);
            case 1:
                AsEquipPanel(p)->ShowSlotDescription();
                SetStep2(p, p->_st2 + 1);
                p->_st3 = p->_retCode;
            case 2:
                if (CHILD_COUNT(p) == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) { SetStep2(p, 1); return; }
                } else {
                    if (p->_retCode == -1) { SetStep0(p, p->_st0 + 1); return; }
                    AsEquipPanel(p)->OpenSlotList();
                    p->_kindListPos = p->_retCode;
                    beNDMWStatusCtrlBaseEquip_ShowKindCursor(p, p->_retCode);
                    return;
                }
                break;
            }
            break;
        case 1:
            switch (p->_st2) {
            case 0:
                AsEquipPanel(p)->OpenSlotMenu();
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
            case 1:
                if (CHILD_COUNT(p) == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) {
                        if (p->_retCode == 2) { AsEquipPanel(p)->PreviewSlotDevice(-1); } else { SendSubWindowCommand(p, OFPREVIEW); }
                        p->_st3 = p->_retCode;
                        return;
                    }
                } else {
                    int i;
                    SendSubWindowCommand(p, OFPREVIEW);
                    for (i = 0; i < 3; i++) { SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(g_statusFontNames[i]); DSP(DEFAULTCOLOR_2); }
                    if (p->_retCode == -1) { SetStep0(p, 0);
                SetStep1(p, 1); return; }
                    AsEquipPanel(p)->OnSlotMenuDecided();
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (p->_st2) {
            case 0:
                AsEquipPanel(p)->OpenPocketList();
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
                return;
            case 1:
                AsEquipPanel(p)->ShowPocketDescription();
                SetStep2(p, p->_st2 + 1);
                p->_st3 = p->_retCode;
            case 2:
                if (CHILD_COUNT(p) == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_retCode != p->_st3) { SetStep2(p, 1); return; }
                } else {
                    if (p->_retCode != -1) { p->_pocketPos = p->_retCode; SetStep2(p, p->_st2 + 1); return; }
                    p->_pocketPos = 0;
                    SetStep0(p, 0);
                SetStep1(p, 1);
                    return;
                }
                break;
            case 3:
                AsEquipPanel(p)->OpenPocketMenu();
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
                return;
            case 4:
                beNDMWWindow_RunMessageScript(p, txt_status_lua_2, 0x7F);
                SetStep2(p, p->_st2 + 1);
                p->_st3 = 0x3E7;
                return;
            case 5:
                if (CHILD_COUNT(p) == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) {
                        if (p->_retCode == 1) { AsEquipPanel(p)->PreviewPocketDevice(-1); } else { SendSubWindowCommand(p, OFPREVIEW); }
                        p->_st3 = p->_retCode;
                        return;
                    }
                } else {
                    SendSubWindowCommand(p, OFPREVIEW);
                    SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(font001_2); DSP(DEFAULTCOLOR_2);
                    switch (p->_retCode) {
                    case 0:
                        SetStep2(p, p->_st2 + 1);
                        AsEquipPanel(p)->PresentPanel(0);
                        beNDMWStatusCtrlBaseEquip_ShowKindCursor(p, -1);
                        return;
                    case 1:
                        p->_retCode = -1;
                        AsEquipPanel(p)->EquipPocket();
                        p->_retCode = p->_pocketPos;
                        AsEquipPanel(p)->RefreshSlotList();
                        RecalcPlayer(p);
                        SendSubWindowCommand(p, UPDATE);
                    default:
                        SetStep1(p, 2);
                        return;
                    }
                }
                break;
            case 6:
                AsEquipPanel(p)->OpenPocketFolder();
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
                p->_st3 = 0x3E7;
            case 7:
                if (CHILD_COUNT(p) == p->_nowProcKazu) { AsEquipPanel(p)->PreviewPocketDevice(0); return; }
                SendSubWindowCommand(p, OFPREVIEW);
                if (p->_retCode != -1) { AsEquipPanel(p)->EquipPocket(); RecalcPlayer(p);
                        SendSubWindowCommand(p, UPDATE); }
                AsEquipPanel(p)->PresentPanel(1);
                beNDMWStatusCtrlBaseEquip_QueuePanelText(p);
                SetStep2(p, p->_st2 + 1);
                return;
            case 8:
                AsEquipPanel(p)->RefreshSlotList();
                beNDMWStatusCtrlBaseEquip_ShowKindCursor(p, p->_kindListPos);
                SetStep1(p, 2);
                return;
            }
            break;
        case 3:
            switch (p->_st2) {
            case 0: {
                int i;
                igSmartPointer<beNDMWStatusSelectE1> hw(beNDMWStatusSelectE1_Create(WindowAllocator(p)));
                beNDMWWindow_BindContext(hw.p, p, p->_insight, p->_playerNo, 0);
                ObjectList_AppendRetained(p->_subWindow, hw.p);
                hw.p->_selectMax = p->_kindListMax;
                { float *q = hw.p->_offsetPos; q[0] = -83.0f; q[1] = 148.0f; q[2] = 0.0f; }
                hw.p->_startPoint = p->_kindListPos;
                igSmartPointer<igBoolList> hl(igBoolList_Create(WindowAllocator(p)));
                for (i = 0; i < p->_kindListMax; i++) {
                    if (i == p->_kindListPos) {
                        BoolList_Append(hl.p, false);
                    } else {
                        BoolList_Append(hl.p, true);
                    }
                }
                if (p->_kindListPos == 0) {
                    if (((int *)((igObjectList *)p->_powerSocket)->_data)[1] == 0) { BoolList_Set(hl.p, 1, false); }
                    if (((int *)((igObjectList *)p->_powerSocket)->_data)[2] == 0) { BoolList_Set(hl.p, 2, false); }
                } else if (((int *)((igObjectList *)p->_powerSocket)->_data)[p->_kindListPos] == 0) {
                    BoolList_Set(hl.p, 0, false);
                }
                {
                    int list = (int)hl.p;
                    beNDMWStatusSelectE1 *window = hw.p;
                    igObject *old;
                    if (list != 0) { ((igObject *)list)->_refCount = ((igObject *)list)->_refCount + 1; }
                    old = (igObject *)window->_decideList;
                    RELEASE_REFERENCE(old);
                    window->_decideList = list;
                }
            }
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
                return;
            case 1:
                AsEquipPanel(p)->RefreshSlotList();
                SetStep2(p, p->_st2 + 1);
                p->_st3 = p->_retCode;
            case 2:
                if (CHILD_COUNT(p) == p->_nowProcKazu) {
                    if (p->_retCode != -1 && p->_st3 != p->_retCode) {
                        beNDMWStatusCtrlBaseEquip_PreviewSocketSwap(p);
                        SetStep2(p, 1);
                        return;
                    }
                } else {
                    SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(g_statusFontNames[0]); APS(DISPOFF_2); DSP(SWITCH_4);
                    SendSubWindowCommand(p, OFPREVIEW);
                    switch (p->_retCode) { case 0: case 1: case 2: {
                        Obj * b_;
                        Obj * a_;
                        igObjectList * ps_;
                        int pos_;
                        ps_ = (igObjectList *)p->_powerSocket; pos_ = p->_kindListPos;
                        b_ = ((Obj **)ps_->_data)[pos_];
                        a_ = ((Obj **)ps_->_data)[p->_retCode];
                        SETSLOT(ps_, pos_, a_);
                        { int r_ = p->_retCode; igObjectList *ps2_ = (igObjectList *)p->_powerSocket; SETSLOT(ps2_, r_, b_); }
                        if (p->_retCode == 0 || p->_kindListPos == 0) { AsEquipPanel(p)->ClearPocket(); }
                        RecalcPlayer(p);
                        SendSubWindowCommand(p, UPDATE);
                        if ((p->_retCode == 0 || p->_kindListPos == 0) && ((beNDMWWindow *)p->_mother)->_entCode == 0) {
                            H::SendName(p);
                        }
                        AsEquipPanel(p)->RefreshPocket();
                    } break; default: break; }
                    SEL(SUBWND_2); API(p->_playerNo); DSP(UPDATE);
                    SetStep0(p, 0);
                SetStep1(p, 1);
                    return;
                }
                break;
            }
            break;
        case 4:
            switch (p->_st2) {
            case 0:
                AsEquipPanel(p)->PresentPanel(0);
                beNDMWStatusCtrlBaseEquip_ShowKindCursor(p, -1);
                AsEquipPanel(p)->OpenDeviceFolder();
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
                p->_st3 = 0x3E7;
            case 1: {
                int fw;
                FIND(fw);
                beNDMWStatusCtrlD0 *w = (beNDMWStatusCtrlD0 *)fw;
                if (p->_retCode == -1) {
                    SendSubWindowCommand(p, OFPREVIEW);
                    SetStep0(w, 2);
                    SetStep2(p, 10);
                    return;
                }
                if (w->_st0 == 1 && w->_st1 == 2) {
                    SendSubWindowCommand(p, OFPREVIEW);
                    if (AsEquipPanel(p)->CanEquip(p->_retCode) != 0) {
                        SetStep2(p, 9);
                        SetStep0(w, 2);
                        return;
                    }
                    SetStep2(p, 12);
                    return;
                }
                AsEquipPanel(p)->PreviewSlotDevice(0);
                return;
            }
            case 9:
                AsEquipPanel(p)->EquipSelected();
                RecalcPlayer(p);
                        SendSubWindowCommand(p, UPDATE);
                SetStep2(p, p->_st2 + 1);
                return;
            case 10:
                if (CHILD_COUNT(p) != p->_nowProcKazu) {
                    AsEquipPanel(p)->PresentPanel(1);
                    beNDMWStatusCtrlBaseEquip_QueuePanelText(p);
                    SetStep2(p, p->_st2 + 1);
                    return;
                }
                break;
            case 11:
                AsEquipPanel(p)->RefreshSlotList();
                SetStep0(p, 0);
                SetStep1(p, 1);
                return;
            case 12: {
                int al = H::PickAlloc(p);
                igSmartPointer<beNDMWShopSelect00> h((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((void *)al));
                beNDMWWindow_BindContext(h.p, p, p->_insight, p->_playerNo, 0);
                ObjectList_AppendRetained(p->_subWindow, h.p);
                beNDMWWindow_RunMessageScript(p, txt_status_lua_2, 0x82);
            }
                p->_nowProcKazu = CHILD_COUNT(p);
                SetStep2(p, p->_st2 + 1);
                p->_st3 = p->_retCode;
            case 13:
                if (CHILD_COUNT(p) != p->_nowProcKazu) {
                    int fw;
                    beNDMWStatusCtrlD0 *w;
                    SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(font000_2); APS(DISPOFF_2); DSP(SWITCH_4);
                    FIND(fw);
                    w = (beNDMWStatusCtrlD0 *)fw;
                    if (w != 0) {
                        p->_retCode = p->_st3;
                        p->_nowProcKazu = CHILD_COUNT(p);
                        SetStep2(w, 1);
                        SetStep2(p, 1);
                        return;
                    }
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(p);
        beNDMWWindow_RequestChildrenClose(p);
        SetStep0(p, p->_st0 + 1);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) { p->_isRun = 0; }
        break;
    }
}

/* Swaps the power-socket items at the kind-list and return positions, publishes, then swaps them back and
 * publishes again. A swap with itself, or one that would leave slot 0 empty, only refreshes. */
void beNDMWStatusCtrlBaseEquip_PreviewSocketSwap(beNDMWStatusCtrlBaseEquip *p)
{
    MovedItemRef kindItem(((void **)((igObjectList *)p->_powerSocket)->_data)[p->_kindListPos]);
    MovedItemRef retItem(((void **)((igObjectList *)p->_powerSocket)->_data)[p->_retCode]);
    if (p->_kindListPos == p->_retCode || ((p->_kindListPos == 0 || p->_retCode == 0) && (kindItem.p == 0 || retItem.p == 0))) {
        REFRESH();
    } else {
        SET_ITEM(p->_kindListPos, retItem)
        SET_ITEM(p->_retCode, kindItem)
        beMessenger_SelectReceivers(p->_messenger, GAMERAM_9, 0, 0); API(p->_playerNo); DSP(RECALCPLAYER_4);
        SEL(SUBWND_2); API(p->_playerNo); DSP(ONPREVIEW);
        SET_ITEM(p->_kindListPos, kindItem)
        SET_ITEM(p->_retCode, retItem)
        beMessenger_SelectReceivers(p->_messenger, GAMERAM_9, 0, 0); API(p->_playerNo); DSP(RECALCPLAYER_4);
    }
}

/* Moves the kind-list cursor (the i_stcursor04 model) to kind `kind`, generating the model at the
 * list position the first time; -1 closes it. */
void beNDMWStatusCtrlBaseEquip_ShowKindCursor(beNDMWStatusCtrlBaseEquip *self, int kind) {
    float position[3];
    if (kind > -1) {
        const char *sequences[12] = {
            SQ_OPEN00, SQ_OPEN01, SQ_OPEN02, SQ_OPEN03, SQ_OPEN04, SQ_OPEN05,
            SQ_OPEN06, SQ_OPEN07, SQ_OPEN08, SQ_OPEN09, SQ_OPEN10, SQ_OPEN11,
        };
        beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursor04, 0, ISRUN_5);
        if (beMessenger_GetBool(self->_messenger, 0) != 0) {
            beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursor04, 0, sequences[kind]);
            return;
        }
        beMessenger_SelectReceivers(self->_messenger, MODELCTRL_3, i_stcursor04, 0);
        beMessenger_AppendString(self->_messenger, sequences[kind]);
        position[2] = 0;
        position[0] = -83.0f;
        position[1] = 148.0f;
        beMessenger_AppendVec3(self->_messenger, position);
        beMessenger_DispatchSelected(self->_messenger, GENERATE_7);
        return;
    }
    beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursor04, 0, ISRUN_5);
    if (beMessenger_GetBool(self->_messenger, 0) != 0) {
        beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
    }
}

/* Queues the panel's text cells: the description line, the kind-list rows and the pocket rows. */
void beNDMWStatusCtrlBaseEquip_QueuePanelText(beNDMWStatusCtrlBaseEquip *self) {
    beNDMWWindow_QueueText(self, STWINFONT29_3, font100_2, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT10, g_statusFontNames[0], space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT10, g_statusFontNames[1], space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font000_2, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font001_2, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font002_2, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font100_2, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font101, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font102, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font103, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT11, font104, space, LEFT_3);
    beNDMWWindow_QueueText(self, STWINFONT29_3, font100_2, space, LEFT_3);
}

void beNDMWStatus_AssignEquipment(StatusPanel *self, ItemList *slotList, int slot, int equipIdx) {
    EquipItem *oldItem = 0;
    EquipItem *newItem = 0;
    ItemList *held;
    void *alloc;
    int i;
    int rec;
    int hit;
    int cat;

    held = slotList;
    if (slot < slotList->_count) oldItem = slotList->_data[slot];
    if (equipIdx >= 0) {
        held = self->_equipList;
        if (equipIdx < held->_count) newItem = held->_data[equipIdx];
    }
    if (oldItem == newItem) {
        LIST_CLEAR_AT(slotList, slot)
        if (oldItem != 0) oldItem->_equipped = 0;
    } else {
        if (oldItem != 0) {
            oldItem->_equipped = 0;
            LIST_CLEAR_AT(slotList, slot)
        }
        if (newItem != 0) {
            i = 0;
            if (0 < slotList->_count) {
                int off = 0;
                do {
                    EquipItem *it = *(EquipItem **)((char *)slotList->_data + off);
                    if (it != 0 && it == newItem) {
                        it->_equipped = 0;
                        REL(*(EquipItem **)((char *)slotList->_data + off))
                        if (slotList->_count != 0 && i >= 0 && i < slotList->_count)
                            *(EquipItem **)((char *)slotList->_data + off) = 0;
                    }
                    i += 1;
                    off += 4;
                } while (i < slotList->_count);
            }
            if ((newItem->_kind == 3) == 1) {
                alloc = igObject_GetAllocator(self);
                alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                {
                igSmartPointer<igObject> names((igObject *)igStringRefList_Create(alloc));
                StringList_AppendRetained((int)names.p, StringRef(InternString(TSUYOSA_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(KASHIKOSA_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(SEISHIN_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(SUBAYASA_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(RES_FIRE_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(RES_ICE_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(RES_THUNDER_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(RES_DARK_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(CHIMEIRITSU_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(HPDRAIN_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(MPDRAIN_2)));
                StringList_AppendRetained((int)names.p, StringRef(InternString(CHOHATURITSU_2)));
                rec = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                alloc = igObject_GetAllocator(self);
                alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                igSmartPointer<igIntList> tmp = (igIntList *)igIntList_Create(alloc);
                cat = -1;
                i = 0;
                if (0 < ((StrList *)names.p)->_count) {
                    do {
                        hit = beNDMWItemBase_GetRecordInt(newItem, rec, (int)(StringList_CopyRetained(names.p, i)).p) > 0;
                        if (hit != 0) { cat = i; break; }
                        i += 1;
                    } while (i < ((StrList *)names.p)->_count);
                }
                int k = 0;
                if (0 < slotList->_count) {
                    EquipItem *it;
                    int off = 0;
                    do {
                        it = *(EquipItem **)((char *)slotList->_data + off);
                        if (it != 0) {
                            hit = beNDMWItemBase_GetRecordInt(it, rec, (int)(StringList_CopyRetained(names.p, cat)).p) > 0;
                            if (hit != 0) {
                                it->_equipped = 0;
                                REL(*(EquipItem **)((char *)slotList->_data + off))
                                if (slotList->_count != 0 && k >= 0 && k < slotList->_count)
                                    *(EquipItem **)((char *)slotList->_data + off) = 0;
                            }
                        }
                        k += 1;
                        off += 4;
                    } while (k < slotList->_count);
                }
                }
            }
            newItem->_equipped = 1;
        }
        if (newItem != 0) newItem->_refCount = newItem->_refCount + 1;
        REL(slotList->_data[slot])
        if (slotList->_count != 0 && slot >= 0 && slot < slotList->_count)
            slotList->_data[slot] = newItem;
    }
}

void beNDMWStatusPowerSocket_PresentPanel(beNDMWStatusPowerSocket *self, int open) {
    int *a1;
    int v1;
    void *pool;
    int *old;
    igDataList *l;
    int n;
    int i;
    int **slot;
    int *nw;
    int *a12;
    int v12;
    void *pool2;
    int *old2;
    igDataList *l2;
    int n2;
    int i2;
    int **slot2;
    int *nw2;
    if (open) {
        beNDMWWindow_PresentModelAtOrigin(self, i_stsoubi, 0, SQ_POWEROPEN, SQ_CLOSE_3);
        int lines = -1;
        igObjectList *kinds = (igObjectList *)self->_powerSocket;
        if (kinds->_count > 0) {
            SlotKind *kind = ((SlotKind **)kinds->_data)[0];
            if (kind != 0 && kind->lineCount > -1) lines = kind->lineCount;
        }
        {
            StringRef sequence;
            switch (lines) {
            case 0:
            default: sequence = SQ_0LINEOPEN; break;
            case 1: sequence = SQ_1LINEOPEN; break;
            case 2: sequence = SQ_2LINEOPEN; break;
            case 3: sequence = SQ_3LINEOPEN; break;
            case 4: sequence = SQ_4LINEOPEN_2; break;
            case 5: sequence = SQ_5LINEOPEN; break;
            }
            beNDMWWindow_PresentModelAtOrigin(self, i_stpocket, 0, sequence.p, SQ_CLOSE_3);
        }

    } else {
        beNDMWWindow_PlayQueuedModelClose();
        l = (igDataList *)self->_modelCloseInfoNameList;
        n = l->_count;
        for (i = 0; i < n; i++) {
            slot = &((int **)l->_data)[i];
            if (g_stringPool[0] == 0) {
                pool = StringPool_Allocate(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                g_stringPool[0] = pool;
            }
            nw = (int *)StringPool_Intern(g_stringPool[0], (const char *)0);
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            *slot = nw;
        }
        l->_count = 0;
        ((igDataList *)self->_modelCloseRamNoList)->_count = 0;
        l2 = (igDataList *)self->_modelCloseSeqNameList;
        n2 = l2->_count;
        for (i2 = 0; i2 < n2; i2++) {
            slot2 = &((int **)l2->_data)[i2];
            if (g_stringPool[0] == 0) {
                pool2 = StringPool_Allocate(0x10);
                if (pool2 != 0) {
                    pool2 = StringPool_Construct(pool2);
                }
                g_stringPool[0] = pool2;
            }
            nw2 = (int *)StringPool_Intern(g_stringPool[0], (const char *)0);
            old2 = *slot2;
            if (old2 != 0) {
                a12 = old2 - 2;
                v12 = old2[-1] - 1;
                old2[-1] = v12;
                if (v12 == 0) {
                    StringChunk_ReleaseHeader(*a12, a12);
                }
            }
            *slot2 = nw2;
        }
        l2->_count = 0;
        beNDMWWindow_ClearQueuedText(self);
    }
}

void beNDMWStatusPowerSocket_RefreshSlotList(S *arg0) {
    V3 b, a;
    int s7 = igInsightCore_FindManager(arg0->w8, g_beNDMWStatus_metaObject[0]);
    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x88);
    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x26);
    int i = 0;
    if (0 < (*(L **)&arg0->l100)->count) {
        int item;
        const char *name;
        int off;
        char **row;
        off = 0;
        row = g_statusFontNames;
        do {
            item = *(int *)((char *)arg0->l100->data + off);
            if (item == 0) {
                name = DISPOFF_2;
            } else {
                int rs;
                name = DISPON_2;
                rs = beNDMWItemBase_GetRecordString(item, s7, NAME_3);
                beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
                beMessenger_AppendString(arg0->w12, STWINFONT11);
                beMessenger_AppendString(arg0->w12, *row);
                beMessenger_AppendString(arg0->w12, rs);
                beMessenger_DispatchSelected(arg0->w12, TEXTSET_3);
                beNDMWItemBase_GetRevisionColor(&b, item);
                beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
                beMessenger_AppendString(arg0->w12, STWINFONT11);
                beMessenger_AppendString(arg0->w12, *row);
                a = b;
                beMessenger_AppendVec3(arg0->w12, (float *)&a);
                beMessenger_DispatchSelected(arg0->w12, COLOR);
            }
            beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
            beMessenger_AppendString(arg0->w12, STWINFONT11);
            beMessenger_AppendString(arg0->w12, *row);
            beMessenger_AppendString(arg0->w12, name);
            beMessenger_DispatchSelected(arg0->w12, SWITCH_4);
            i++;
            off += 4;
            row++;
        } while (i < arg0->l100->count);
    }
    arg0->v22();
    if (arg0->w32 == 3) {
        arg0->v26();
    }
}

/* Retained share of the system's global string object. */

void beNDMWStatusPowerSocket_ShowSlotDescription(beNDMWStatusPowerSocket *a) {
    int *temp_s1;
    int *var_s1_2;
    int temp_v1;
    int var_s1;
    int temp_v0; /* matching construct: one register serves the record string and then the held string's length */
    char sp4C[2];
    Str *t2;
    Str *t3;
    beNDMWItemBaseList *items;

    var_s1 = 0;
    temp_v1 = a->_retCode;
    if (temp_v1 != -1) {
        items = (beNDMWItemBaseList *)a->_powerSocket;
        var_s1 = *(int *)(items->_data + (temp_v1 * 4));
    }
    if (var_s1 != 0) {
        temp_v0 = beNDMWItemBase_GetRecordString(var_s1, igInsightCore_FindManager(a->_insight, g_beNDMWStatus_metaObject[0]), TXT_2);
        sp4C[1] = 0;
        sp4C[0] = *(int *)(var_s1 + 24) + 0x30;
        {
        igSmartPointer<igStringObj> sp48((igStringObj *)(((beSystem *)igInsightCore_FindManager(a->_insight, g_beSystem_metaObject[0]))->_globalStrObj), kRetainReference);
        igStringObj_Set(sp48.p, (const char *)temp_v0);
        t2 = (Str *)sp48.p;
        temp_v0 = t2->len;
        igStringObj_Insert(t2, sp4C, temp_v0, strlen(sp4C));
        t3 = (Str *)sp48.p;
        temp_s1 = (int *)t3->data;
        temp_s1 = (temp_s1 == 0) ? ((int * *)g_stringObjEmptyText)[0] : temp_s1;
        }
        beMessenger_SelectGroup(a->_messenger, TEXTCTL_5);
        beMessenger_AppendString(a->_messenger, STWINFONT29_3);
        beMessenger_AppendString(a->_messenger, font000_2);
        beMessenger_AppendString(a->_messenger, temp_s1);
        beMessenger_DispatchSelected(a->_messenger, TEXTSET_3);
        var_s1_2 = (int *)(DISPON_2);
    } else {
        var_s1_2 = (int *)(DISPOFF_2);
    }
    beMessenger_SelectGroup(a->_messenger, TEXTCTL_5);
    beMessenger_AppendString(a->_messenger, STWINFONT29_3);
    beMessenger_AppendString(a->_messenger, font000_2);
    beMessenger_AppendString(a->_messenger, var_s1_2);
    beMessenger_DispatchSelected(a->_messenger, SWITCH_4);
}

void beNDMWStatusPowerSocket_OpenSlotList(beNDMWStatusPowerSocket *arg0) {
    switch (arg0->_retCode) {
    case 0:
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 1:
    case 2:
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st3 = 1;
        break;
    }
}

void beNDMWStatusPowerSocket_RefreshPocket(beNDMWStatusPowerSocket *self) {
    int lines = -1;
    igObjectList *kinds = (igObjectList *)self->_powerSocket;
    if (kinds->_count > 0) {
        SlotKind *kind = ((SlotKind **)kinds->_data)[0];
        if (kind != 0 && kind->lineCount > -1) lines = kind->lineCount;
    }
    {
        StringRef sequence;
        switch (lines) {
        case 0:
        default: sequence = SQ_0LINEOPEN; break;
        case 1: sequence = SQ_1LINEOPEN; break;
        case 2: sequence = SQ_2LINEOPEN; break;
        case 3: sequence = SQ_3LINEOPEN; break;
        case 4: sequence = SQ_4LINEOPEN_2; break;
        case 5: sequence = SQ_5LINEOPEN; break;
        }
        beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stpocket, 0, sequence.p);
    }
    int i = 0;
    /* matching construct: the loop guard reads the pocket list through a const view, so the body reloads it as retail does */
    const beNDMWStatusPowerSocket *view = self;
    if (0 < ((igObjectList *)view->_wpuPocket)->_count) {
        do {
            const char *font;
            const char *show;
            switch (i) {
            default: font = (font100_2); break;
            case 1: font = font101; break;
            case 2: font = font102; break;
            case 3: font = font103; break;
            case 4: font = font104; break;
            }
            void *item = ((void **)((igObjectList *)self->_wpuPocket)->_data)[i];
            if (item == 0) {
                show = (DISPOFF_2);
            } else {
                show = (DISPON_2);
                const char *name = ((const char *)beNDMWItemBase_GetRecordString(item, ((void *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0])), NAME_3));
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT11);
                beMessenger_AppendString(self->_messenger, font);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT11);
            beMessenger_AppendString(self->_messenger, font);
            beMessenger_AppendString(self->_messenger, show);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
            i++;
        } while (i < ((igObjectList *)self->_wpuPocket)->_count);
    }
}

void beNDMWStatusPowerSocket_OpenSlotMenu(beNDMWStatusPowerSocket *arg0) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl0;
    bool fl;
    int i;
    char **p;
    const char *s3;
    igIntList *t;

    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow /* matching construct: unsigned argument keeps the retail load order */, win.p);
    switch (((beNDMWWindow *)arg0->_mother)->_entCode) {
    case 0:
        win.p->_entCode = 124;
        win.p->_selectMax = 2;
        break;
    case 1:
        win.p->_entCode = 46;
        win.p->_selectMax = 3;
        break;
    }
    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<igBoolList> flags((igBoolList *)igBoolList_Create((void *)a));
    APPEND(GPR_00554a0c)
    t = (igIntList *)arg0->_powerSocket;
    fl0 = false;
    fl = false;
    if (t->_count > 0) {
        if (arg0->_st3 == 0) {
            SlotKind *kind = ((SlotKind **)t->_data)[0];
            if (kind != 0 && kind->lineCount > 0) fl0 = true;
        }
        if (((int *)t->_data)[arg0->_kindListPos] != 0 && arg0->_kindListPos != 0) fl = true;
    }
    APPEND(fl0)
    if (((beNDMWWindow *)arg0->_mother)->_entCode == 1) APPEND(fl)
    /* matching construct: a const view of the holder keeps the retail reload of the list */
    { const igSmartPointer<igBoolList> &view = flags; l0 = view.p; }
    w = win.p;
    if (l0 != 0) {
        l0->_refCount = l0->_refCount + 1;
    }
    REL_413c20(w->_decideList)
    w->_decideList = (int)l0;
    i = 0;
    l0 = flags.p;
    if (0 < l0->_count) {
        p = &g_statusFontNames[0];
        do {
            if (*(unsigned char *)(l0->_data + i) != 0) {
                s3 = DEFAULTCOLOR_2;
            } else {
                s3 = CANCELCOLOR_2;
            }
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
            beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
            beMessenger_AppendString(arg0->_messenger, *p);
            beMessenger_DispatchSelected(arg0->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}


void beNDMWStatusPowerSocket_OnSlotMenuDecided(beNDMWStatusPowerSocket *arg0) {
    int temp_a2;

    temp_a2 = arg0->_retCode;
    switch (temp_a2) {
    case 0:
        /* matching construct: cast from the 4-byte _mother reference to its window type */
        beNDMWWindow *mother = (beNDMWWindow *)arg0->_mother;
        switch (mother->_entCode) {
        case 0:
            arg0->_st1 = 3;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        default:
            arg0->_st1 = 4;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            break;
        }
        break;
    case 1:
        arg0->_st1 = 2;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_retCode = -1;
        ((DW4VC_132_2 *)(((char *)(arg0) + 0)))->vX((int)(2), (int)(temp_a2));
        arg0->_retCode = (int)((int) arg0->_kindListPos);
        ((DW4VC_104_0 *)(((char *)(arg0) + 0)))->vX();
        beMessenger_SelectReceivers(arg0->_messenger, GAMERAM_9, 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, RECALCPLAYER_4);
        beMessenger_SelectGroup(arg0->_messenger, SUBWND_2);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, UPDATE);
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    }
}

static inline int count(const igIntList *list) { return list->_count; }

void beNDMWStatusPowerSocket_OpenDeviceFolder(beNDMWStatusPowerSocket *arg0) {
    int alloc;
    int a;
    int s1;
    igIntList *s0;
    alloc = ((int)igObject_GetAllocator(arg0));
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    }
    igSmartPointer<beNDMWStatusCtrlD0> win(beNDMWStatusCtrlD0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, win.p);
    StringList_AppendRetained(win.p->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
    StringList_AppendRetained(win.p->_textCloseNameList, StringRef(InternString(font100_2)));
    beNDMWWindow_RunMessageScript(win.p, txt_status_lua_2, 0x8B);
    s0 = (igIntList *)win.p->_kindList;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
        s0->_count = count(s0) + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    ((int *)s0->_data)[s1] = DAT_004cf6d0[0];
    win.p->_isEquipDisable = 1;
    win.p->_isUnknownDisable = 1;
    win.p->_isAutoClose = 0;
}


int beNDMWStatusPowerSocket_CanEquip(beNDMWStatusPowerSocket *arg0, int arg1) {
    int s0b;
    int s0;
    int fl;
    PropertyRecordTable *s1;
    int s3;
    int v0;
    int s2;

    s3 = ((int *)((beNDMWItemBaseList *)arg0->_deviceFolder)->_data)[arg1];
    s0 = igInsightCore_FindManager(arg0->_insight, g_beNDMWStatus_metaObject[0]);
    s2 = igProperty_GetRecord(arg0->_playerList, DIGIMONNO_3)->_data;
    fl = (1 << s2) & beNDMWItemBase_GetRecordInt(s3, s0, SOUBI_2);
    s1 = (PropertyRecordTable *)igProperty_GetRecordIntList(arg0->_playerList, SKILL_2)->_data;
    s0b = beNDMWItemBase_GetRecordInt(s3, s0, SKILL_2);
    v0 = beNDMWItemBase_GetRecordInt(s3, s0, SKILLPOINT_2);
    if ((fl != 0) && (s1->data[s0b] >= v0)) {
        return 1;
    }
    return 0;
}

void beNDMWStatusPowerSocket_EquipSelected(beNDMWStatusPowerSocket *arg0) {
    beNDMWStatus_AssignEquipment((StatusPanel *)arg0, (ItemList *)arg0->_powerSocket, arg0->_kindListPos, arg0->_retCode);
    if (arg0->_kindListPos == 0) {
        ((beNDMWStatusPowerSocketVTable *)arg0)->vX();
    }
    ((beNDMWWindow *)((beNDMWWindow *)arg0->_mother)->_mother)->_retCode = 0x64;
}

/* Runs the shared helper beNDMWStatus_PreviewEquipment (the DEVICE row selection step; -1 is its "no row" case)
 * over the power socket's WPU pocket list at the current pocket position, passing the first
 * argument through as the row index. The MainSlot sibling does the same with its APU pocket. The
 * other two arguments are unused. */
void beNDMWStatusPowerSocket_PreviewPocketDevice(beNDMWStatusPowerSocket *self, char *index, char *unusedArg2, int unusedArg3)
{
    beNDMWStatus_PreviewEquipment(self, self->_wpuPocket, self->_pocketPos, index);
}

void beNDMWStatusPowerSocket_PreviewSlotDevice(beNDMWStatusPowerSocket *arg0, int arg1) {
    if (arg1 != -1) {
        beNDMWStatus_PreviewEquipment(arg0, arg0->_powerSocket, 0, arg1);
    }
}

void beNDMWStatusPowerSocket_OpenPocketList(Sh *arg0) {
    int alloc;
    int a2;
    alloc = (int)igObject_GetAllocator();
    if (g_useOwnerAllocator != 0) {
        alloc = (int)alloc;
    } else {
        alloc = (int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((void *)alloc));
    beNDMWWindow_BindContext(win.p, arg0, arg0->f8, arg0->f20, 0);
    { Win *t = (Win *)win.p; ObjectList_AppendRetained(arg0->f52, t); }
    StringList_AppendRetained(((Win *)win.p)->f60, StringRef(InternString(STWINFONT29_3)));
    StringList_AppendRetained(((Win *)win.p)->f64, StringRef(InternString(font100_2)));
    beNDMWWindow_RunMessageScript(win.p, txt_status_lua_2, 0x8A);
    a2 = 1;
    if (arg0->f100->n > 0) {
        Item *it = arg0->f100->data[arg0->f84];
        if (it != 0) a2 = it->f24;
    }
    ((Win *)win.p)->f84 = a2;
    { Win *t = (Win *)win.p;
    t->f88 = 0xC2A60000;
    t->f92 = 0x425C0000;
    t->f96 = 0; }
    ((Win *)win.p)->f100 = arg0->f92;
}

void beNDMWStatusPowerSocket_ShowPocketDescription(beNDMWStatusPowerSocket *self) {
    const char *onOff;
    beNDMWItemBase *item = 0;
    if (self->_retCode != -1) item = ItemAt(self->_wpuPocket, self->_retCode);
    if (item != 0) {
        SetCellText(self, STWINFONT29_3, font000_2, (const char *)beNDMWItemBase_GetRecordString(item, FindStatus(self->_insight), TXT_2));
        onOff = DISPON_2;
    } else {
        onOff = DISPOFF_2;
    }
    SwitchCell(self, STWINFONT29_3, font000_2, onOff);
}

static inline void append(const igSmartPointer<igBoolList> &list, const unsigned char &value) {
    igBoolList *l = list.p;
    int n = l->_count;
    if (n < l->_capacity) {
        l->_count = n + 1;
    } else {
        List_Resize(l, n + 1, 1);
    }
    ((unsigned char *)l->_data)[n] = value;
}

static inline void setDecideList(const igSmartPointer<beNDMWStatusSelectE0> &win, const igSmartPointer<igBoolList> &list) {
    igBoolList *l0 = list.p;
    beNDMWStatusSelectE0 *w = win.p;
    if (l0 != 0) {
        l0->_refCount = l0->_refCount + 1;
    }
    REL_414a00((igObject *)w->_decideList)
    w->_decideList = (int)l0;
}

void beNDMWStatusPowerSocket_OpenPocketMenu(beNDMWStatusPowerSocket *arg0) {
    int a;

    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow, win.p);
    win.p->_selectMax = 2;
    beNDMWWindow_QueueText(win.p, STWINFONT29_3, font000_2, space, LEFT_3);
    beNDMWWindow_QueueText(win.p, STWINFONT29_3, font001_2, space, LEFT_3);
    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<igBoolList> decide((igBoolList *)igBoolList_Create((void *)a));
    setDecideList(win, decide);
    append(decide, GPR_00554a10);
    if (((int *)((beNDMWItemBaseList *)arg0->_wpuPocket)->_data)[arg0->_pocketPos] != 0) {
        append(decide, GPR_00554a14);
    } else {
        append(decide, GPR_00554a18);
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
        beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
        beMessenger_AppendString(arg0->_messenger, font001_2);
        beMessenger_DispatchSelected(arg0->_messenger, CANCELCOLOR_2);
    }
}

static inline int countOf(const igDataList *l) { return l->_count; }

void beNDMWStatusPowerSocket_OpenPocketFolder(beNDMWStatusPowerSocket *arg0) {
    int alloc;
    int a;
    int s1;
    igDataList *s0;
    alloc = ((int)igObject_GetAllocator(arg0));
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    }
    igSmartPointer<beNDMWStatusCtrlD0> child((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(a));
    beNDMWWindow_BindContext(child.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, child.p);
    s0 = ((UnidentifiedChildWindow *)child.p)->list;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
                s0->_count = countOf(s0) + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    ((int *)s0->_data)[s1] = DAT_004cf6d8[0];
    ((UnidentifiedChildWindow *)child.p)->f104 = 0;
    ((UnidentifiedChildWindow *)child.p)->f108 = 1;
    ((UnidentifiedChildWindow *)child.p)->f110 = 1;
}

/* Equipment assignment for the power socket's WPU pocket list: the shared helper
 * beNDMWStatus_AssignEquipment gets the pocket list, the pocket position and the device-folder
 * index chosen in _retCode. The MainSlot sibling does the same with its APU pocket. The three
 * arguments are unused. */
void beNDMWStatusPowerSocket_EquipPocket(beNDMWStatusPowerSocket *self, char *unusedArg1, char *unusedArg2, char *unusedArg3)
{
    beNDMWStatus_AssignEquipment((StatusPanel *)self, (ItemList *)self->_wpuPocket, self->_pocketPos, self->_retCode);
}

void beNDMWStatusPowerSocket_ClearPocket(PowerSocketView *self) {
    int i;
    for (i = 0; i < self->getList()->count; i++) {
        PowerSocketItem *it = self->list->items[i];
        if (it != 0) {
            it->f16 = 0;
        }
    }
    ObjectList_FillRetained(self->list, 0);
}

void beNDMWStatusMainSlot_PresentPanel(beNDMWStatusMainSlot *self, int open) {
    int *a1;
    int v1;
    void *pool;
    int *old;
    igDataList *l;
    int n;
    int i;
    int **slot;
    int *nw;
    int *a12;
    int v12;
    void *pool2;
    int *old2;
    igDataList *l2;
    int n2;
    int i2;
    int **slot2;
    int *nw2;
    if (open) {
        beNDMWWindow_PresentModelAtOrigin(self, i_stsoubi, 0, SQ_MAINOPEN, SQ_CLOSE_3);
        int lines = -1;
        igObjectList *kinds = (igObjectList *)self->_mainSlot;
        if (kinds->_count > 0) {
            SlotKind *kind = ((SlotKind **)kinds->_data)[0];
            if (kind != 0 && kind->lineCount > -1) lines = kind->lineCount;
        }
        {
            StringRef sequence;
            switch (lines) {
            case 0:
            default: sequence = SQ_0LINEOPEN; break;
            case 1: sequence = SQ_1LINEOPEN; break;
            case 2: sequence = SQ_2LINEOPEN; break;
            case 3: sequence = SQ_3LINEOPEN; break;
            case 4: sequence = SQ_4LINEOPEN_2; break;
            case 5: sequence = SQ_5LINEOPEN; break;
            }
            beNDMWWindow_PresentModelAtOrigin(self, i_stpocket, 0, sequence.p, SQ_CLOSE_3);
        }

    } else {
        beNDMWWindow_PlayQueuedModelClose();
        l = (igDataList *)self->_modelCloseInfoNameList;
        n = l->_count;
        for (i = 0; i < n; i++) {
            slot = &((int **)l->_data)[i];
            if (g_stringPool[0] == 0) {
                pool = StringPool_Allocate(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                g_stringPool[0] = pool;
            }
            nw = (int *)StringPool_Intern(g_stringPool[0], (const char *)0);
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            *slot = nw;
        }
        l->_count = 0;
        ((igDataList *)self->_modelCloseRamNoList)->_count = 0;
        l2 = (igDataList *)self->_modelCloseSeqNameList;
        n2 = l2->_count;
        for (i2 = 0; i2 < n2; i2++) {
            slot2 = &((int **)l2->_data)[i2];
            if (g_stringPool[0] == 0) {
                pool2 = StringPool_Allocate(0x10);
                if (pool2 != 0) {
                    pool2 = StringPool_Construct(pool2);
                }
                g_stringPool[0] = pool2;
            }
            nw2 = (int *)StringPool_Intern(g_stringPool[0], (const char *)0);
            old2 = *slot2;
            if (old2 != 0) {
                a12 = old2 - 2;
                v12 = old2[-1] - 1;
                old2[-1] = v12;
                if (v12 == 0) {
                    StringChunk_ReleaseHeader(*a12, a12);
                }
            }
            *slot2 = nw2;
        }
        l2->_count = 0;
        beNDMWWindow_ClearQueuedText(self);
    }
}

void beNDMWStatusMainSlot_RefreshSlotList(S_415440 *arg0) {
    V3 b, a;
    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x89);
    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x28);
    int i = 0;
    if (0 < (*(L **)&arg0->l100)->count) {
        int item;
        const char *name;
        int off;
        char **row;
        off = 0;
        row = g_statusFontNames;
        do {
            item = *(int *)((char *)arg0->l100->data + off);
            if (item == 0) {
                name = DISPOFF_2;
            } else {
                int rs;
                name = DISPON_2;
                rs = beNDMWItemBase_GetRecordString(item, igInsightCore_FindManager(arg0->w8, g_beNDMWStatus_metaObject[0]), NAME_3);
                beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
                beMessenger_AppendString(arg0->w12, STWINFONT11);
                beMessenger_AppendString(arg0->w12, *row);
                beMessenger_AppendString(arg0->w12, rs);
                beMessenger_DispatchSelected(arg0->w12, TEXTSET_3);
                beNDMWItemBase_GetRevisionColor(&b, item);
                beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
                beMessenger_AppendString(arg0->w12, STWINFONT11);
                beMessenger_AppendString(arg0->w12, *row);
                a = b;
                beMessenger_AppendVec3(arg0->w12, (float *)&a);
                beMessenger_DispatchSelected(arg0->w12, COLOR);
            }
            beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
            beMessenger_AppendString(arg0->w12, STWINFONT11);
            beMessenger_AppendString(arg0->w12, *row);
            beMessenger_AppendString(arg0->w12, name);
            beMessenger_DispatchSelected(arg0->w12, SWITCH_4);
            i++;
            off += 4;
            row++;
        } while (i < arg0->l100->count);
    }
    arg0->v22();
}

void beNDMWStatusMainSlot_ShowSlotDescription(beNDMWStatusMainSlot *a) {
    Slot *s2 = 0;
    int temp; /* matching construct: one register serves the record string and then the held string's length */
    char buf[2];
    RefCountedHeader *p;
    RefCountedHeader *q;
    char *str;
    const char *var;
    if (a->_retCode != -1) {
        s2 = ((SlotList *)a->_mainSlot)->arr[a->_retCode];
    }
    if (s2 != 0) {
        temp = beNDMWItemBase_GetRecordString(s2, ((RefCountedHeader *)igInsightCore_FindManager(a->_insight, g_beNDMWStatus_metaObject[0])), TXT_2);
        buf[1] = 0;
        buf[0] = s2->f24 + 0x30;
        {
        igSmartPointer<igStringObj> sp48((igStringObj *)(*(int *)((char *)((RefCountedHeader *)igInsightCore_FindManager(a->_insight, g_beSystem_metaObject[0])) + 72)), kRetainReference);
        igStringObj_Set(sp48.p, (const char *)temp);
        q = (RefCountedHeader *)sp48.p;
        temp = q->w12;
        igStringObj_Insert(q, buf, temp, strlen(buf));
        p = (RefCountedHeader *)sp48.p;
        str = (p->w8 == 0) ? g_stringObjEmptyText[0] : (char *)p->w8;
        }
        beMessenger_SelectGroup(a->_messenger, TEXTCTL_5);
        beMessenger_AppendString(a->_messenger, STWINFONT29_3);
        beMessenger_AppendString(a->_messenger, font000_2);
        beMessenger_AppendString(a->_messenger, str);
        beMessenger_DispatchSelected(a->_messenger, TEXTSET_3);
        var = DISPON_2;
    } else {
        var = DISPOFF_2;
    }
    beMessenger_SelectGroup(a->_messenger, TEXTCTL_5);
    beMessenger_AppendString(a->_messenger, STWINFONT29_3);
    beMessenger_AppendString(a->_messenger, font000_2);
    beMessenger_AppendString(a->_messenger, var);
    beMessenger_DispatchSelected(a->_messenger, SWITCH_4);
}

/* Enter state 1; the later state levels restart at 0 */
void beNDMWStatusMainSlot_OpenSlotList(beNDMWStatusMainSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
}

void beNDMWStatusMainSlot_RefreshPocket(beNDMWStatusMainSlot *self) {
    int lines = -1;
    igObjectList *kinds = (igObjectList *)self->_mainSlot;
    if (kinds->_count > 0) {
        SlotKind *kind = ((SlotKind **)kinds->_data)[0];
        if (kind != 0 && kind->lineCount > -1) lines = kind->lineCount;
    }
    {
        StringRef sequence;
        switch (lines) {
        case 0:
        default: sequence = SQ_0LINEOPEN; break;
        case 1: sequence = SQ_1LINEOPEN; break;
        case 2: sequence = SQ_2LINEOPEN; break;
        case 3: sequence = SQ_3LINEOPEN; break;
        case 4: sequence = SQ_4LINEOPEN_2; break;
        case 5: sequence = SQ_5LINEOPEN; break;
        }
        beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stpocket, 0, sequence.p);
    }
    int i = 0;
    /* matching construct: the loop guard reads the pocket list through a const view, so the body reloads it as retail does */
    const beNDMWStatusMainSlot *view = self;
    if (0 < ((igObjectList *)view->_apuPocket)->_count) {
        do {
            const char *font;
            const char *show;
            switch (i) {
            default: font = (font100_2); break;
            case 1: font = font101; break;
            case 2: font = font102; break;
            case 3: font = font103; break;
            case 4: font = font104; break;
            }
            void *item = ((void **)((igObjectList *)self->_apuPocket)->_data)[i];
            if (item == 0) {
                show = (DISPOFF_2);
            } else {
                show = (DISPON_2);
                const char *name = ((const char *)beNDMWItemBase_GetRecordString(item, ((void *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0])), NAME_3));
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT11);
                beMessenger_AppendString(self->_messenger, font);
                beMessenger_AppendString(self->_messenger, name);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT11);
            beMessenger_AppendString(self->_messenger, font);
            beMessenger_AppendString(self->_messenger, show);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
            i++;
        } while (i < ((igObjectList *)self->_apuPocket)->_count);
    }
}

void beNDMWStatusMainSlot_OpenSlotMenu(beNDMWStatusMainSlot *arg0) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl0;
    bool fl;
    int i;
    char **p;
    const char *s3;
    igIntList *t;

    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow /* matching construct: unsigned argument keeps the retail load order */, win.p);
    win.p->_selectMax = 3;
    win.p->_entCode = 0x78;
    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<igBoolList> flags((igBoolList *)igBoolList_Create((void *)a));
    APPEND(GPR_00554a1c)
    t = (igIntList *)arg0->_mainSlot;
    fl0 = false;
    fl = false;
    if (t->_count > 0) {
        if (arg0->_st3 == 0) {
            SlotKind *kind = ((SlotKind **)t->_data)[0];
            if (kind != 0 && kind->lineCount > 0) fl0 = true;
        }
        if (((int *)t->_data)[arg0->_kindListPos] != 0) fl = true;
    }
    APPEND(fl0)
    APPEND(fl)
    /* matching construct: a const view of the holder keeps the retail reload of the list */
    { const igSmartPointer<igBoolList> &view = flags; l0 = view.p; }
    w = win.p;
    if (l0 != 0) {
        l0->_refCount = l0->_refCount + 1;
    }
    REL_413c20(w->_decideList)
    w->_decideList = (int)l0;
    i = 0;
    l0 = flags.p;
    if (0 < l0->_count) {
        p = &g_statusFontNames[0];
        do {
            if (*(unsigned char *)(l0->_data + i) != 0) {
                s3 = DEFAULTCOLOR_2;
            } else {
                s3 = CANCELCOLOR_2;
            }
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
            beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
            beMessenger_AppendString(arg0->_messenger, *p);
            beMessenger_DispatchSelected(arg0->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}

void beNDMWStatusMainSlot_OnSlotMenuDecided(beNDMWStatusMainSlot *arg0) {
    int temp_a2;

    temp_a2 = arg0->_retCode;
    switch (temp_a2) {
    case 0:
        arg0->_st1 = 4;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 1:
        arg0->_st1 = 2;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_retCode = -1;
        ((DW4VC_132_2 *)(((char *)(arg0) + 0)))->vX((int)(2), (int)(temp_a2));
        arg0->_retCode = (int)((int) arg0->_kindListPos);
        ((DW4VC_104_0 *)(((char *)(arg0) + 0)))->vX();
        beMessenger_SelectReceivers(arg0->_messenger, GAMERAM_9, 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, RECALCPLAYER_4);
        beMessenger_SelectGroup(arg0->_messenger, SUBWND_2);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, UPDATE);
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    }
}

void beNDMWStatusMainSlot_OpenDeviceFolder(beNDMWStatusMainSlot *arg0) {
    int al;
    int c;
    igDataList *l;

    al = ((int)igObject_GetAllocator(arg0));
    al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusCtrlD0> win(beNDMWStatusCtrlD0_Create(al));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, win.p);
    StringList_AppendRetained(win.p->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
    StringList_AppendRetained(win.p->_textCloseNameList, StringRef(InternString(font100_2)));
    beNDMWWindow_RunMessageScript(win.p, txt_status_lua_2, 139);
    l = (igDataList *)win.p->_kindList;
    c = l->_count;
    if (c < l->_capacity) {
        l->_count = countOf(l) + 1;
    } else {
        List_Resize(l, c + 1, 4);
    }
    ((int *)l->_data)[c] = DAT_004cf6e0[0];
    win.p->_isEquipDisable = 1;
    win.p->_isUnknownDisable = 1;
    win.p->_isAutoClose = 0;
}

/* The equipment eligibility test: the item at a list index may be equipped when the player's LEVEL
 * property is at least the item's LVPOINT record. */
int beNDMWStatusMainSlot_CanEquip(beNDMWStatusMainSlot *self, int index) {
    int status;
    int item;
    int player_level;

    item = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (index * 4));
    status = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
    player_level = igProperty_GetRecord(self->_playerList, LEVEL_3)->_data;
    return player_level >= beNDMWItemBase_GetRecordInt(item, status, LVPOINT);
}

void beNDMWStatusMainSlot_EquipSelected(beNDMWStatusMainSlotVTable *arg0) {
    beNDMWStatusMainSlot *s = (beNDMWStatusMainSlot *)arg0;
    beNDMWStatus_AssignEquipment((StatusPanel *)arg0, (ItemList *)s->_mainSlot, s->_kindListPos, s->_retCode);
    if (s->_kindListPos == 0) {
        arg0->vX();
    }
}

/* Only the first argument is used. */
void beNDMWStatusMainSlot_PreviewPocketDevice(beNDMWStatusMainSlot * self, char * extra, char * unusedA, int unusedB)
{
    /* matching construct: (int) cast because the callee takes the receiver as an int */
    beNDMWStatus_PreviewEquipment((int)self, self->_apuPocket, self->_pocketPos, extra);
}

void beNDMWStatusMainSlot_OpenPocketList(beNDMWStatusMainSlot *self) {
    void *alloc;
    int startPoint;
    alloc = igObject_GetAllocator();
    alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    igSmartPointer<beNDMWStatusSelectE1> win(((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(alloc)));
    beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
    { beNDMWStatusSelectE1 *window = win.p; ObjectList_AppendRetained(self->_subWindow, window); }
    StringList_AppendRetained(win.p->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
    StringList_AppendRetained(win.p->_textCloseNameList, StringRef(InternString(font100_2)));
    beNDMWWindow_RunMessageScript(win.p, txt_status_lua_2, 0x8A);
    startPoint = 1;
    igObjectList *kinds = (igObjectList *)self->_mainSlot;
    if (kinds->_count > 0) {
        SlotKind_4168f0 *kind = ((SlotKind_4168f0 **)kinds->_data)[self->_kindListPos];
        if (kind != 0) startPoint = kind->startPoint;
    }
    win.p->_selectMax = startPoint;
    { beNDMWStatusSelectE1 *window = win.p;
    window->_offsetPos[0] = -83.0f;
    window->_offsetPos[1] = 55.0f;
    window->_offsetPos[2] = 0.0f; }
    win.p->_startPoint = self->_pocketPos;
}

void beNDMWStatusMainSlot_ShowPocketDescription(beNDMWStatusMainSlot *arg0) {
    int *temp_s1;
    const char *var_s1_2;
    int temp_v1;
    int var_s1;

    var_s1 = 0;
    temp_v1 = arg0->_retCode;
    if (temp_v1 != -1) {
        var_s1 = ((int *)((beNDMWItemBaseList *)arg0->_apuPocket)->_data)[temp_v1];
    }
    if (var_s1 != 0) {
        temp_s1 = ((int *)beNDMWItemBase_GetRecordString(var_s1, igInsightCore_FindManager(arg0->_insight, g_beNDMWStatus_metaObject[0]), TXT_2));
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
        beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
        beMessenger_AppendString(arg0->_messenger, font000_2);
        beMessenger_AppendString(arg0->_messenger, temp_s1);
        beMessenger_DispatchSelected(arg0->_messenger, TEXTSET_3);
        var_s1_2 = DISPON_2;
    } else {
        var_s1_2 = DISPOFF_2;
    }
    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
    beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
    beMessenger_AppendString(arg0->_messenger, font000_2);
    beMessenger_AppendString(arg0->_messenger, var_s1_2);
    beMessenger_DispatchSelected(arg0->_messenger, SWITCH_4);
}

void beNDMWStatusMainSlot_OpenPocketMenu(beNDMWStatusMainSlot *arg0) {
    int a;

    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow, win.p);
    win.p->_selectMax = 2;
    beNDMWWindow_QueueText(win.p, STWINFONT29_3, font000_2, space, LEFT_3);
    beNDMWWindow_QueueText(win.p, STWINFONT29_3, font001_2, space, LEFT_3);
    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<igBoolList> decide((igBoolList *)igBoolList_Create((void *)a));
    setDecideList(win, decide);
    append(decide, GPR_00554a20);
    if (((int *)((beNDMWItemBaseList *)arg0->_apuPocket)->_data)[arg0->_pocketPos] != 0) {
        append(decide, GPR_00554a24);
    } else {
        append(decide, GPR_00554a28);
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
        beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
        beMessenger_AppendString(arg0->_messenger, font001_2);
        beMessenger_DispatchSelected(arg0->_messenger, CANCELCOLOR_2);
    }
}

/* BeNDMWStatusMainSlot vfunc 36: creates the D0 status sub-window (held across its binding, the
 * sub-window append and the kind-list push) and marks it as the ability-type variant with
 * equipment and unknown entries disabled. */

static inline int countOf_416f90(const igIntList *l) { return l->_count; }


void beNDMWStatusMainSlot_OpenPocketFolder(beNDMWStatusMainSlot *arg0) {
    int al;
    int c;
    igIntList *l;
    beNDMWStatusCtrlD0 *w;

    al = ((int)igObject_GetAllocator(arg0));
    al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusCtrlD0> window(beNDMWStatusCtrlD0_Create(al));
    beNDMWWindow_BindContext(window.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, window.p);
    w = window.p;
    l = (igIntList *)w->_kindList;
    c = l->_count;
    if (c < l->_capacity) {
        l->_count = countOf_416f90(l) + 1;
    } else {
        List_Resize(l, c + 1, 4);
    }
    ((int *)l->_data)[c] = DAT_004cf6e8[0];
    window.p->_isAbType = 1;
    window.p->_isEquipDisable = 1;
    window.p->_isUnknownDisable = 1;
}

/* All three arguments are unused. */
void beNDMWStatusMainSlot_EquipPocket(beNDMWStatusMainSlot * self, char * unusedA, char * unusedB, char * unusedC)
{
    /* matching construct: (int) cast because the callee takes the receiver as an int */
    beNDMWStatus_AssignEquipment((StatusPanel *)((int)self), (ItemList *)self->_apuPocket, self->_pocketPos, self->_retCode);
}

void beNDMWStatusMainSlot_ClearPocket(beNDMWStatusMainSlot *arg0) {
    int i;
    beNDMWItemBase *e;
    i = 0;
    if (0 < ((beNDMWItemBaseList *)(*(int *)&arg0->_apuPocket))->_count) {
        do {
            e = ((beNDMWItemBase **)((beNDMWItemBaseList *)(arg0->_apuPocket))->_data)[i];
            if (e != 0) {
                e->_isEquip = 0;
            }
            i += 1;
        } while (i < ((beNDMWItemBaseList *)(arg0->_apuPocket))->_count);
    }
    ObjectList_FillRetained((void *)(arg0->_apuPocket), 0);
}

void beNDMWStatusSubSlot_PresentPanel(beNDMWStatusSubSlot *w, int arg1)
{
    int *a1;
    int v1;
    int pool;
    int *old;
    igDataList *l;
    int n;
    int i;
    int **slot;
    int *nw;
    int *a12;
    int v12;
    int pool2;
    int *old2;
    igDataList *l2;
    int n2;
    int i2;
    int **slot2;
    int *nw2;

    if (arg1 != 0) {
        beNDMWWindow_PresentModelAtOrigin(w, i_stsoubi, 0, SQ_SUBOPEN, SQ_CLOSE_3);
        return;
    }
    beNDMWWindow_PlayQueuedModelClose();
    l = (igDataList *)w->_modelCloseInfoNameList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (((int *)g_stringPool)[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct(pool));
            }
            ((int *)g_stringPool)[0] = pool;
        }
        nw = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0);
        old = *slot;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        *slot = nw;
    }
    l->_count = 0;
    ((igDataList *)w->_modelCloseRamNoList)->_count = 0;
    l2 = (igDataList *)w->_modelCloseSeqNameList;
    n2 = l2->_count;
    for (i2 = 0; i2 < n2; i2++) {
        slot2 = &((int **)l2->_data)[i2];
        if (((int *)g_stringPool)[0] == 0) {
            pool2 = ((int)StringPool_Allocate(0x10));
            if (pool2 != 0) {
                pool2 = ((int)StringPool_Construct(pool2));
            }
            ((int *)g_stringPool)[0] = pool2;
        }
        nw2 = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0);
        old2 = *slot2;
        if (old2 != 0) {
            a12 = old2 - 2;
            v12 = old2[-1] - 1;
            old2[-1] = v12;
            if (v12 == 0) {
                StringChunk_ReleaseHeader(*a12, a12);
            }
        }
        *slot2 = nw2;
    }
    l2->_count = 0;
    beNDMWWindow_ClearQueuedText(w);
}

void beNDMWStatusSubSlot_RefreshSlotList(S_417350 *arg0) {
    V3 b, a;
    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x89);
    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x2A);
    int i = 0;
    if (0 < (*(L **)&arg0->l100)->count) {
        int item;
        const char *name;
        int off;
        char **row;
        off = 0;
        row = g_statusFontNames;
        do {
            item = *(int *)((char *)arg0->l100->data + off);
            if (item == 0) {
                name = DISPOFF_2;
            } else {
                int rs;
                name = DISPON_2;
                rs = beNDMWItemBase_GetRecordString(item, igInsightCore_FindManager(arg0->w8, g_beNDMWStatus_metaObject[0]), NAME_3);
                beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
                beMessenger_AppendString(arg0->w12, STWINFONT11);
                beMessenger_AppendString(arg0->w12, *row);
                beMessenger_AppendString(arg0->w12, rs);
                beMessenger_DispatchSelected(arg0->w12, TEXTSET_3);
                beNDMWItemBase_GetRevisionColor(&b, item);
                beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
                beMessenger_AppendString(arg0->w12, STWINFONT11);
                beMessenger_AppendString(arg0->w12, *row);
                a = b;
                beMessenger_AppendVec3(arg0->w12, (float *)&a);
                beMessenger_DispatchSelected(arg0->w12, COLOR);
            }
            beMessenger_SelectGroup(arg0->w12, TEXTCTL_5);
            beMessenger_AppendString(arg0->w12, STWINFONT11);
            beMessenger_AppendString(arg0->w12, *row);
            beMessenger_AppendString(arg0->w12, name);
            beMessenger_DispatchSelected(arg0->w12, SWITCH_4);
            i++;
            off += 4;
            row++;
        } while (i < arg0->l100->count);
    }
}

void beNDMWStatusSubSlot_ShowSlotDescription(beNDMWStatusSubSlot *a) {
    int *temp_s1;
    int *var_s1_2;
    int temp_v1;
    int var_s1;
    beNDMWItemBaseList *items;

    var_s1 = 0;
    temp_v1 = a->_retCode;
    if (temp_v1 != -1) {
        items = (beNDMWItemBaseList *)a->_subSlot;
        var_s1 = *(int *)(items->_data + (temp_v1 * 4));
    }
    if (var_s1 != 0) {
        temp_s1 = (int *)(((int *)beNDMWItemBase_GetRecordString(var_s1, igInsightCore_FindManager(a->_insight, g_beNDMWStatus_metaObject[0]), TXT_2)));
        beMessenger_SelectGroup(a->_messenger, TEXTCTL_5);
        beMessenger_AppendString(a->_messenger, STWINFONT29_3);
        beMessenger_AppendString(a->_messenger, font000_2);
        beMessenger_AppendString(a->_messenger, temp_s1);
        beMessenger_DispatchSelected(a->_messenger, TEXTSET_3);
        var_s1_2 = (int *)(DISPON_2);
    } else {
        var_s1_2 = (int *)(DISPOFF_2);
    }
    beMessenger_SelectGroup(a->_messenger, TEXTCTL_5);
    beMessenger_AppendString(a->_messenger, STWINFONT29_3);
    beMessenger_AppendString(a->_messenger, font000_2);
    beMessenger_AppendString(a->_messenger, var_s1_2);
    beMessenger_DispatchSelected(a->_messenger, SWITCH_4);
}

/* Resets the slot's state counters; st1 and st3 end up 1, st2 0 (the _st3 = 0 store is dead but
 * kept). */
void beNDMWStatusSubSlot_OpenSlotList(beNDMWStatusSubSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st3 = 1;
}

void beNDMWStatusSubSlot_RefreshPocket(beNDMWStatusSubSlot *self) {
    int i;
    for (i = 0; i < 5; i++) {
        const char *off = (DISPOFF_2);
        const char *upper;
        const char *lower;
        switch (i) {
        default: upper = (font100_2); lower = font200; break;
        case 1: upper = font101; lower = font201; break;
        case 2: upper = font102; lower = font202; break;
        case 3: upper = font103; lower = font203; break;
        case 4: upper = font104; lower = font204; break;
        }
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
        beMessenger_AppendString(self->_messenger, STWINFONT11);
        beMessenger_AppendString(self->_messenger, upper);
        beMessenger_AppendString(self->_messenger, off);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
        beMessenger_AppendString(self->_messenger, STWINFONT11);
        beMessenger_AppendString(self->_messenger, lower);
        beMessenger_AppendString(self->_messenger, off);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
    }
}

void beNDMWStatusSubSlot_OpenSlotMenu(beNDMWStatusSubSlot *arg0) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl;
    int i;
    char **p;
    const char *s3;
    igIntList *t;

    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow /* matching construct: unsigned argument keeps the retail load order */, win.p);
    win.p->_selectMax = 3;
    win.p->_entCode = 0x78;
    a = ((int)igObject_GetAllocator(arg0));
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    igSmartPointer<igBoolList> flags((igBoolList *)igBoolList_Create((void *)a));
    APPEND(GPR_00554a2c)
    t = (igIntList *)arg0->_subSlot;
    fl = false;
    if (t->_count > 0 && ((int *)t->_data)[arg0->_kindListPos] != 0) fl = true;
    APPEND(0)
    APPEND(fl)
    l0 = *(igBoolList **)&flags.p;
    w = win.p;
    if (l0 != 0) {
        l0->_refCount = l0->_refCount + 1;
    }
    REL_413c20(w->_decideList)
    w->_decideList = (int)l0;
    i = 0;
    l0 = flags.p;
    if (0 < l0->_count) {
        p = &g_statusFontNames[0];
        do {
            if (*(unsigned char *)(l0->_data + i) != 0) {
                s3 = DEFAULTCOLOR_2;
            } else {
                s3 = CANCELCOLOR_2;
            }
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
            beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
            beMessenger_AppendString(arg0->_messenger, *p);
            beMessenger_DispatchSelected(arg0->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}

void beNDMWStatusSubSlot_OnSlotMenuDecided(beNDMWStatusSubSlot *arg0) {
    int temp_a2;

    temp_a2 = arg0->_retCode;
    switch (temp_a2) {
    case 0:
        arg0->_st1 = 4;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 1:
        arg0->_st1 = 2;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_retCode = -1;
        ((DW4VC_132_2 *)(arg0))->vX((int)(2), (int)(temp_a2));
        arg0->_retCode = (int)((int) arg0->_kindListPos);
        ((DW4VC_104_0 *)(arg0))->vX();
        beMessenger_SelectReceivers(arg0->_messenger, GAMERAM_9, 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, RECALCPLAYER_4);
        beMessenger_SelectGroup(arg0->_messenger, SUBWND_2);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, UPDATE);
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    }
}

void beNDMWStatusSubSlot_OpenDeviceFolder(beNDMWStatusSubSlot *arg0) {
    int alloc;
    int a;
    int s1;
    ElementBufferList *s0;
    alloc = ((int)igObject_GetAllocator(arg0));
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
    }
    igSmartPointer<beNDMWStatusCtrlD0> win((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, win.p);
    StringList_AppendRetained(((beNDMWWindow *)win.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
    StringList_AppendRetained(((beNDMWWindow *)win.p)->_textCloseNameList, StringRef(InternString(font100_2)));
    beNDMWWindow_RunMessageScript(win.p, txt_status_lua_2, 139);
    s0 = ((WindowObject *)win.p)->list;
    s1 = s0->n;
    if (s1 < s0->cap) {
        s0->n = s0->getN() + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    s0->data[s1] = DAT_004cf6f0[0];
    ((WindowObject *)win.p)->f108 = 1;
    ((WindowObject *)win.p)->f110 = 1;
    ((WindowObject *)win.p)->f111 = 0;
}

/* True when the player's LEVEL is at least the LVPOINT record of device folder entry `entryIndex`;
 * the same check is in beNDMWStatusMainSlot. */
int beNDMWStatusSubSlot_CanEquip(beNDMWStatusSubSlot *self, int entryIndex) {
    int status;
    int entry;
    int playerLevel;

    entry = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (entryIndex * 4));
    status = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
    playerLevel = igProperty_GetRecord(self->_playerList, LEVEL_3)->_data;
    return playerLevel >= beNDMWItemBase_GetRecordInt(entry, status, LVPOINT);
}

/* Equipment assignment for the sub slot. beNDMWStatus_AssignEquipment (equip by shared item
 * identity, toggle-off, chip-family exclusion) takes the slot list (_subSlot), the entry position
 * in it (_kindListPos) and the index chosen in the device folder (_retCode, bounds-checked against
 * the list at +120, _deviceFolder). The PowerSocket and MainSlot siblings have the same body. The
 * three arguments are unused. */
void beNDMWStatusSubSlot_EquipSelected(beNDMWStatusSubSlot *self, char *unusedArg1, char *unusedArg2, char *unusedArg3)
{
    beNDMWStatus_AssignEquipment((StatusPanel *)self, (ItemList *)self->_subSlot, self->_kindListPos, self->_retCode);
}

void beNDMWStatusSubSlot_PreviewPocketDevice(void)
{
}

/* Runs the shared helper beNDMWStatus_PreviewEquipment (the DEVICE row selection step; -1 is its "no row" case)
 * over the sub slot's list at the current list position, passing the first argument through as the
 * row index. The other two arguments are unused. */
void beNDMWStatusSubSlot_PreviewSlotDevice(beNDMWStatusSubSlot *self, char *index, char *unusedArg2, int unusedArg3)
{
    beNDMWStatus_PreviewEquipment(self, self->_subSlot, self->_kindListPos, index);
}

void beNDMWStatusSubSlot_OpenPocketList(void)
{
}

void beNDMWStatusSubSlot_ShowPocketDescription(void)
{
}

void beNDMWStatusSubSlot_OpenPocketMenu(void)
{
}

void beNDMWStatusSubSlot_OpenPocketFolder(void)
{
}

void beNDMWStatusSubSlot_EquipPocket(void)
{
}

void beNDMWStatusSubSlot_ClearPocket(void)
{
}

void beNDMWStatusCtrlD0_Update(beNDMWStatusCtrlD0 *self)
{
    float vecA[3];
    float vecB[3];
    void *alloc;
    int i;
    char **fp;
    beNDMWWindowSelect *mother;
    igObjectList *list;
    int rec;

    switch (self->_st0) {
    case 0:
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT13)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
        if (self->_isBankFolder != 0) {
            beNDMWWindow_RunMessageScript(self, txt_shop_lua, 0x517);
        } else {
            beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x46);
        }
        i = 0;
        fp = &g_statusFontNames[0];
        do {
            beNDMWWindow_QueueText(self, STWINFONT14_2, *fp, space, LEFT_3);
            i += 1;
            fp += 1;
        } while (i < 12);
        i = 0;
        fp = &g_statusFontNames[0];
        do {
            beNDMWWindow_QueueText(self, STWINFONT16, *fp, space, RIGHT_2);
            i += 1;
            fp += 1;
        } while (i < 12);
        if (self->_isBankFolder != 0) {
            beNDMWWindow_QueueText(self, STWINFONT40, g_statusFontNames[0], space, RIGHT_2);
            beNDMWWindow_QueueText(self, STWINFONT40, g_statusFontNames[1], space, RIGHT_2);
        } else {
            beNDMWWindow_QueueText(self, STWINFONT23, g_statusFontNames[0], space, RIGHT_2);
            beNDMWWindow_QueueText(self, STWINFONT23, g_statusFontNames[1], space, RIGHT_2);
        }
        beNDMWWindow_QueueText(self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
        GET_ALLOC(alloc)
        {
        igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(alloc));
        beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, win.p);
        ((beNDMWWindowSelect *)win.p)->_selectMax = beNDMWStatusCtrlD0_UpdatePageCount(self);
        {
            RefHeader *dl = (RefHeader *)self->_decideList;
            beNDMWWindowSelect *w;
            w = (beNDMWWindowSelect *)win.p;
            RETAIN_OBJ(dl)
            { RefHeader *old = (RefHeader *)w->_decideList; RELEASE_OBJ_418090(old) }
            w->_decideList = (int)dl;
        }
        { beNDMWWindowSelect *wp = (beNDMWWindowSelect *)win.p; wp->_offsetPos[0] = -121.0f; wp->_offsetPos[1] = 128.0f; wp->_offsetPos[2] = 0.0f; }
        ((beNDMWWindowSelect *)win.p)->_startPoint = 0;
        }
        self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
        beNDMWWindow_PresentModelAtOrigin(self, i_stfolder, 0, SQ_AWINONOPEN, SQ_CLOSE_3);
        vecB[0] = 85.0f;
        vecB[2] = 0.0f;
        vecB[1] = 25.0f;
        vecA[0] = -146.0f;
        vecA[1] = 25.0f;
        vecA[2] = 0.0f;
        ((DummyVirtual *)self)->v24(&vecA[0], &vecB[0]);
        NEXT_ST0()
    case 1:
        switch (self->_st1) {
        case 0:
            beNDMWStatusCtrlD0_RefreshText(self, 1, 1);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            if (((igObjectList *)self->_subWindow)->_count == self->_nowProcKazu) {
                if (self->_retCode != -1) {
                    if (self->_retCode != self->_st3) {
                        beNDMWStatusCtrlD0_RefreshText(self, 0, 1);
                        self->_st3 = self->_retCode;
                        return;
                    }
                    mother = (beNDMWWindowSelect *)*(int *)((int)((igObjectList *)self->_subWindow)->_data);
                    if (beNDMWWindowSelect_CanRequestFO2TOP(mother, self->_subWindow) != 0) {
                        bool ready = false;
                        if (((DummyVirtual *)self)->v25() != 0) {
                            ready = true;
                        } else if (((DummyVirtual *)self)->v26() != 0) {
                            ready = true;
                        }
                        if (ready) {
                            ((beNDMWStatusCtrlD0 *)mother)->_st0 = 4;
                            ((beNDMWStatusCtrlD0 *)mother)->_st3 = 0;
                            ((beNDMWStatusCtrlD0 *)mother)->_st2 = 0;
                            ((beNDMWStatusCtrlD0 *)mother)->_st1 = 0;
                            mother->_selectMax = beNDMWStatusCtrlD0_UpdatePageCount(self);
                            {
                                RefHeader *dl = (RefHeader *)self->_decideList;
                                RETAIN_OBJ(dl)
                                { RefHeader *old = (RefHeader *)mother->_decideList; RELEASE_OBJ_418090(old) }
                                mother->_decideList = (int)dl;
                            }
                            self->_st1 = 0;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            return;
                        }
                    }
                }
            } else {
                if (self->_retCode != -1) {
                    ((beNDMWWindowSelect *)self->_mother)->_retCode = HA::Add(self->_nowPage * 12, self->_retCode);
                    self->_cursor = self->_retCode;
                } else {
                    ((beNDMWWindowSelect *)self->_mother)->_retCode = -1;
                }
                if (self->_isAutoClose != 0) {
                    NEXT_ST0()
                    return;
                }
                self->_st1 = self->_st1 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                return;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 1:
                GET_ALLOC(alloc)
                {
                igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                beMessenger_SelectGroup(self->_messenger, GAMERAM_9);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, GETPLAYER_6);
                rec = beMessenger_GetObject(self->_messenger, 0);
                if (self->_isBankFolder != 0) {
                    beDataObjObjectList *folder = igProperty_GetRecordFolder(rec, BANKDEVICE_2);
                    list = (igObjectList *)folder->_data;
                } else {
                    beDataObjObjectList *folder = igProperty_GetRecordFolder(rec, DEVICEFOLDER_3);
                    list = (igObjectList *)folder->_data;
                }
                if (self->_cursor + self->_nowPage * 12 >= list->_count) {
                    if (self->_cursor == 0) {
                        if (self->_nowPage > 0) {
                            self->_nowPage = self->_nowPage - 1;
                        }
                    } else {
                        self->_cursor = self->_cursor - 1;
                    }
                }
                if (self->_nowPage == 0) {
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursorleft, 0, SQ_HIDE);
                }
                if (list->_count <= (self->_nowPage + 1) * 12) {
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursorright, 0, SQ_HIDE);
                }
                ((beNDMWWindowSelect *)win.p)->_selectMax = beNDMWStatusCtrlD0_UpdatePageCount(self);
                {
                    RefHeader *dl = (RefHeader *)self->_decideList;
                    beNDMWWindowSelect *w;
                    w = (beNDMWWindowSelect *)win.p;
                    RETAIN_OBJ(dl)
                    { RefHeader *old = (RefHeader *)w->_decideList; RELEASE_OBJ_418090(old) }
                    w->_decideList = (int)dl;
                }
                { beNDMWWindowSelect *wp = (beNDMWWindowSelect *)win.p; wp->_offsetPos[0] = -121.0f; wp->_offsetPos[1] = 128.0f; wp->_offsetPos[2] = 0.0f; }
                ((beNDMWWindowSelect *)win.p)->_startPoint = self->_cursor;
                }
                self->_st0 = 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        i = 0;
        fp = &g_statusFontNames[0];
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        do {
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT14_2);
            beMessenger_AppendString(self->_messenger, *fp);
            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_2);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT16);
            beMessenger_AppendString(self->_messenger, *fp);
            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_2);
            i += 1;
            fp += 1;
        } while (i < 12);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void beNDMWStatusCtrlD0_RefreshText(beNDMWStatusCtrlD0 *p0, int arg1, int arg2) {
    beNDMWStatusCtrlD0 *self;
    igDataList *folder;
    int i;
    igStringObj *r;
    beNDMWItemBase *item;
    int m;
    void *tail;
    void *ctx;
    char *s;
    char *nm;
    char *nm2;
    char *s2;
    int mm;
    int o;
    int idx;
    int base;
    beDataObjObjectList *t;
    beDataObjObjectList *t2;
    self = p0;
    beMessenger_SelectGroup(self->_messenger, GAMERAM_9);
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_6);
    o = beMessenger_GetObject(self->_messenger, 0);
    if (self->_isBankFolder != 0) {
        t = igProperty_GetRecordFolder(o, BANKDEVICE_2);
        folder = (igDataList *)t->_data;
    } else {
        t2 = igProperty_GetRecordFolder(o, DEVICEFOLDER_3);
        folder = (igDataList *)t2->_data;
    }
    ctx = ((void *)igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]));
    igSmartPointer<igStringObj> sp((igStringObj *)((int *)((void *)igInsightCore_FindManager(self->_insight, g_beSystem_metaObject[0])))[18]);
    /* matching construct: the text buffers are declared after the holder so they lie below it in the frame as retail. */
    char buf1[2];
    char buf2[2];
    char buf3[2];
    int vec[4];
    if (sp.p != 0) {
        sp.p->_refCount = sp.p->_refCount + 1;
    }
    if (arg1 != 0) {
        i = 0;
        do {
            idx = self->_nowPage * 12 + i;
            if (idx < folder->_count) {
                item = *(beNDMWItemBase **)(folder->_data + idx * 4);
                s = ((char *)beNDMWItemBase_GetRecordString(item, ctx, NAME_3));
                igStringObj_Set(sp, s);
                if (item->_isEquip != 0) {
                    igStringObj_Insert(sp, equippedMark, 0, strlen(equippedMark));
                } else {
                    igStringObj_Insert(sp, unequippedMark, 0, strlen(unequippedMark));
                }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                beMessenger_AppendString(self->_messenger, g_statusFontNames[i]);
                mm = self->_messenger;
                nm2 = (char *)sp.p->_buffer;
                if (nm2 == 0) nm = g_stringObjEmptyText[0]; else nm = nm2;
                beMessenger_AppendString(mm, nm);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                beMessenger_AppendString(self->_messenger, g_statusFontNames[i]);
                if (*(unsigned char *)(((igBoolList *)self->_decideList)->_data + i) != 0) {
                    m = self->_messenger;
                    beNDMWItemBase_GetRevisionColor(vec, item);
                    beMessenger_AppendVec3(m, (float *)vec);
                    beMessenger_DispatchSelected(self->_messenger, COLOR);
                } else {
                    beMessenger_DispatchSelected(self->_messenger, CANCELCOLOR_2);
                }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT16);
                beMessenger_AppendString(self->_messenger, g_statusFontNames[i]);
                beMessenger_AppendString(self->_messenger, space);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                tail = DISPON_2;
            } else {
                tail = DISPOFF_2;
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT14_2);
            beMessenger_AppendString(self->_messenger, g_statusFontNames[i]);
            beMessenger_AppendString(self->_messenger, tail);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT16);
            beMessenger_AppendString(self->_messenger, g_statusFontNames[i]);
            beMessenger_AppendString(self->_messenger, tail);
            beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
            i++;
        } while (i < 12);
        buf1[0] = self->_nowPage + 49;
        buf1[1] = 0;
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
        if (self->_isBankFolder != 0) {
            beMessenger_AppendString(self->_messenger, STWINFONT40);
        } else {
            beMessenger_AppendString(self->_messenger, STWINFONT23);
        }
        beMessenger_AppendString(self->_messenger, g_statusFontNames[0]);
        beMessenger_AppendString(self->_messenger, buf1);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
        buf1[0] = self->_maxPage + 48;
        buf1[1] = 0;
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
        if (self->_isBankFolder != 0) {
            beMessenger_AppendString(self->_messenger, STWINFONT40);
        } else {
            beMessenger_AppendString(self->_messenger, STWINFONT23);
        }
        beMessenger_AppendString(self->_messenger, g_statusFontNames[1]);
        beMessenger_AppendString(self->_messenger, buf1);
        beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
    }
    if (arg2 != 0) {
        base = self->_nowPage * 12;
        idx = base + self->_retCode;
        if (idx < folder->_count) {
            item = *(beNDMWItemBase **)(folder->_data + idx * 4);
            s = ((char *)beNDMWItemBase_GetRecordString(item, ctx, TXT_2));
            if (item->_kindNo == 0) {
                if (item->_recNo != 0x114) {
                    buf2[1] = 0;
                    buf2[0] = ((beNDMWItemBlueArmor *)item)->_pocket + 48;
                    igStringObj_Set(sp, s);
                    r = sp.p;
                    i = r->_length;
                    igStringObj_Insert(r, buf2, i, strlen(buf2));
                    s2 = (char *)sp.p->_buffer;
                    s = s2 == 0 ? g_stringObjEmptyText[0] : s2;
                }
            } else if (item->_kindNo == 1 && item->_recNo != 0x1f) {
                buf3[1] = 0;
                buf3[0] = ((beNDMWItemBlueArmor *)item)->_pocket + 48;
                igStringObj_Set(sp, s);
                r = sp.p;
                idx = r->_length;
                igStringObj_Insert(r, buf3, idx, strlen(buf3));
                s2 = (char *)sp.p->_buffer;
                s = s2 == 0 ? g_stringObjEmptyText[0] : s2;
            }
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT29_3);
            beMessenger_AppendString(self->_messenger, g_statusFontNames[0]);
            if (s != 0) {
                beMessenger_AppendString(self->_messenger, s);
            } else {
                beMessenger_AppendString(self->_messenger, space);
            }
            beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
            tail = DISPON_2;
        } else {
            tail = DISPOFF_2;
        }
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
        beMessenger_AppendString(self->_messenger, STWINFONT29_3);
        beMessenger_AppendString(self->_messenger, g_statusFontNames[0]);
        beMessenger_AppendString(self->_messenger, tail);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
    }
}

int beNDMWStatusCtrlD0_UpdatePageCount(beNDMWStatusCtrlD0 *arg0) {
    int n;
    void *obj;
    int idx;
    int pages;
    bool ok;
    int rem;
    igObjectList *fold;
    int k;
    igDataList *out;
    int shown;
    int t; int a; unsigned char b1; unsigned char b2; unsigned char w;
    beNDMWItemBase *rec;
    beMessenger_SelectGroup(arg0->_messenger, GAMERAM_9);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, GETPLAYER_6);
    obj = ((void *)beMessenger_GetObject(arg0->_messenger, 0));
    if (arg0->_isBankFolder != 0) {
        int tmp = igProperty_GetRecordFolder(obj, BANKDEVICE_2)->_data;
        fold = (igObjectList *)tmp;
    } else {
        int tmp = igProperty_GetRecordFolder(obj, DEVICEFOLDER_3)->_data;
        fold = (igObjectList *)tmp;
    }
    if (fold->_count % 12 != 0) {
        pages = fold->_count / 12 + 1;
    } else {
        pages = fold->_count / 12;
    }
    arg0->_maxPage = pages;
    rem = fold->_count - arg0->_nowPage * 12;
    if (rem >= 12) {
        shown = 12;
    } else {
        shown = rem % 12;
    }
    ((igDataList *)arg0->_decideList)->_count = 0;
    for (idx = 0; idx < shown; idx++) {
        rec = *(beNDMWItemBase **)(fold->_data + (arg0->_nowPage * 12 + idx) * 4);
        ok = true;
        if (((igDataList *)arg0->_kindList)->_count > 0) {
            ok = false;
            for (k = 0; k < ((igDataList *)arg0->_kindList)->_count; k++) {
                t = *(int *)(((igDataList *)arg0->_kindList)->_data + k * 4);
                if (t == 3) {
                    if (rec->_kindNo == 3) {
                        a = igInsightCore_FindManager(arg0->_insight, g_beNDMWStatus_metaObject[0]);
                        b1 = beNDMWItemBase_GetRecordBool(rec, a, WU);
                        b2 = beNDMWItemBase_GetRecordBool(rec, a, BLUEAB);
                        switch (arg0->_isAbType) {
                        default: w = 1; break;
                        case 0: w = b1; break;
                        case 1: w = b2; break;
                        }
                        if (w == 1) { ok = true; break; }
                    }
                } else if ((t == 0 && rec->_kindNo == 0) || (t == 1 && rec->_kindNo == 1) || (t == 2 && rec->_kindNo == 2)) {
                    ok = true;
                    break;
                }
            }
        }
        if (arg0->_isEquipDisable != 0 && rec->_isEquip != 0) ok = false;
        if (arg0->_isUnknownDisable != 0) {
            if ((rec->_kindNo == 0 && rec->_recNo == 276) || (rec->_kindNo == 1 && rec->_recNo == 31) || (rec->_kindNo == 2 && rec->_recNo == 44)) ok = false;
        }
        if (arg0->_isUnknownEnable != 0) {
            if ((rec->_kindNo == 0 && rec->_recNo == 276) || (rec->_kindNo == 1 && rec->_recNo == 31) || (rec->_kindNo == 2 && rec->_recNo == 44)) ok = true;
            else ok = false;
        }
        out = (igDataList *)arg0->_decideList;
        n = out->_count;
        if (n < out->_capacity) out->_count = n + 1;
        else List_Resize(out, n + 1, 1);
        *(unsigned char *)(n + out->_data) = ok;
    }
    if (arg0->_maxPage == 0) arg0->_maxPage = 1;
    if (shown == 0) shown = 1;
    return shown;
}

int beNDMWStatusCtrlD0_GetSelectedIndex(void *arg0)
{
  unsigned int new_var2;
  int temp_a1;
  int new_var;
  new_var = -1;
  temp_a1 = *((int *) (((char *) arg0) + 48));
 do { } while (0);
  if (temp_a1 == new_var)
  {
    return -1;
  }
  new_var2 = (*((int *) (((char *) arg0) + 84))) * 0xC;
  return new_var2 + temp_a1;
}

void beNDMWStatusCtrlFolder_Update(beNDMWStatusCtrlFolder *arg0) {
    void *alloc;
    beNDMWStatusCtrlD0 *found;
    switch (arg0->_st0) {
    case 0:
        ALLOC(alloc)
        {
        igSmartPointer<beNDMWStatusTitle04> sp9C((beNDMWStatusTitle04 *)beNDMWStatusTitle04_Create(alloc));
        beNDMWWindow_BindContext(sp9C.p, arg0, arg0->_insight, arg0->_playerNo, 0x3C);
        ObjectList_AppendRetained(arg0->_subWindow, sp9C.p);
        }
        arg0->_folderMenu = 0;
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
                ALLOC(alloc)
                {
                igSmartPointer<beNDMWStatusSelect01> sp98((beNDMWStatusSelect01 *)beNDMWStatusSelect01_Create(alloc));
                beNDMWWindow_BindContext(sp98.p, arg0, arg0->_insight, arg0->_playerNo, 0x3D);
                ObjectList_AppendRetained(arg0->_subWindow, sp98.p);
                ((beNDMWStatusSelect01 *)sp98.p)->_startPoint = arg0->_folderMenu;
                beNDMWWindow_QueueText(sp98.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (arg0->_retCode != -1) {
                    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, arg0->_retCode + 0x51);
                }
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                arg0->_st3 = arg0->_retCode;
            case 2:
                if (((igDataList *)arg0->_subWindow)->_count == arg0->_nowProcKazu) {
                    if (arg0->_retCode == -1) { return; }
                    if (arg0->_st3 == arg0->_retCode) { return; }
                    arg0->_st2 = 1;
                    arg0->_st3 = 0;
                    return;
                }
                if (arg0->_retCode != -1) {
                    arg0->_folderMenu = arg0->_retCode;
                }
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
                case 2:
                    arg0->_st1 = 3;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                case 3:
                    arg0->_st1 = 4;
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
        case 1:
            switch (arg0->_st2) {
            case 0:
                ALLOC(alloc)
                {
                igSmartPointer<beNDMWStatusCtrlD0> sp94((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(alloc));
                beNDMWWindow_BindContext(sp94.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, sp94.p);
                ((beNDMWStatusCtrlD0 *)sp94.p)->_isAutoClose = 0;
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (arg0->_st3 == 0) {
                    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x2B);
                    arg0->_st3 = 1;
                }
                found = FolderHelpers::FindSub(arg0);
                if (found != 0) {
                    if (arg0->_retCode == -1) {
                        MSG()
                        ((beNDMWWindow *)found)->_st0 = 2;
                        ((beNDMWWindow *)found)->_st3 = 0;
                        ((beNDMWWindow *)found)->_st2 = 0;
                        ((beNDMWWindow *)found)->_st1 = 0;
                        arg0->_st2 = 3;
                        arg0->_st3 = 0;
                        return;
                    }
                    if (((beNDMWWindow *)found)->_st0 == 1 && ((beNDMWWindow *)found)->_st1 == 2) {
                        MSG()
                        ALLOC(alloc)
                        {
                        igSmartPointer<beNDMWStatusSubMenu> sp90((beNDMWStatusSubMenu *)beNDMWStatusSubMenu_Create(alloc));
                        beNDMWWindow_BindContext(sp90.p, arg0, arg0->_insight, arg0->_playerNo, arg0->_retCode);
                        ObjectList_AppendRetained(arg0->_subWindow, sp90.p);
                        ((beNDMWStatusSubMenu *)sp90.p)->_selectDevice = arg0->_retCode;
                        {
                            beNDMWStatusSubMenu *o = (beNDMWStatusSubMenu *)sp90.p;
                            igObject *old;
                            if (found != 0) { found->_refCount = (int)found->_refCount + 1; }
                            old = (igObject *)o->_deviceFolderList;
                            REL_4196c0(old)
                            o->_deviceFolderList = (int)found;
                        }
                        }
                        arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                        arg0->_st2 = arg0->_st2 + 1;
                        arg0->_st3 = 0;
                        return;
                    }
                }
                break;
            case 2:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                    arg0->_retCode = 0;
                    beNDMWWindow_PlayQueuedModelClose(arg0);
                    CLEAR(arg0->_modelCloseInfoNameList)
                    ((igDataList *)arg0->_modelCloseRamNoList)->_count = 0;
                    CLEAR(arg0->_modelCloseSeqNameList)
                    beNDMWWindow_ClearQueuedText(arg0);
                    found = FolderHelpers::FindSub(arg0);
                    if (found != 0) {
                        ((beNDMWWindow *)found)->_st2 = 1;
                        ((beNDMWWindow *)found)->_st3 = 0;
                        arg0->_st2 = 1;
                        arg0->_st3 = 0;
                        return;
                    }
                    arg0->_st2 = 4;
                    arg0->_st3 = 0;
                    return;
                }
                break;
            case 3:
                found = FolderHelpers::FindSub(arg0);
                if (found == 0) {
                    arg0->_retCode = arg0->_folderMenu;
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            case 4:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st2 = 0;
                    arg0->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
        case 3:
        case 4:
            switch (arg0->_st2) {
            case 0:
                {
                igSmartPointer<beNDMWWindow> sp8C(0);
                switch (arg0->_st1) {
                case 2:
                    ALLOC(alloc)
                    { igObject *t = sp8C.p; REL_4196c0(t) }
                    sp8C.p = (beNDMWWindow *)beNDMWStatusCtrlFlag_Create(alloc);
                    break;
                case 3:
                    ALLOC(alloc)
                    { igObject *t = sp8C.p; REL_4196c0(t) }
                    sp8C.p = (beNDMWWindow *)beNDMWStatusCtrlDisk_Create(alloc);
                    break;
                case 4:
                    ALLOC(alloc)
                    { igObject *t = sp8C.p; REL_4196c0(t) }
                    sp8C.p = (beNDMWWindow *)beNDMWStatusCtrlBit_Create(alloc);
                    break;
                }
                beNDMWWindow_BindContext(sp8C.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, sp8C.p);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_retCode = arg0->_folderMenu;
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


void beNDMWStatusCtrlFlag_Update(beNDMWStatusCtrlFlag *arg0) {
    PropertyRecordList *lst;
    int s2;
    int s1;
    int a;
    int al;
    igIntList *l4;
    char *src;
    int k;
    char **p;
    switch (arg0->_st0) {
    case 0:
        beMessenger_SendGroup(arg0->_messenger, GAMERAM_9, GETCOMMON_6);
        lst = (PropertyRecordList *)igProperty_GetRecordArray(beMessenger_GetObject(arg0->_messenger, 0), FLAGFOLDER_2)->_data;
        s2 = 0;
        if (0 < lst->cnt) {
            do {
                if (lst->data[s2] != 0) {
                    l4 = (igIntList *)arg0->_impItems;
                    s1 = l4->_count;
                    if (s1 < l4->_capacity) {
                        l4->_count = countOf_416f90(l4) + 1;
                    } else {
                        List_Resize(l4, s1 + 1, 4);
                    }
                    ((int *)l4->_data)[s1] = s2;
                }
                s2 += 1;
            } while (s2 < lst->cnt);
        }
        StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(InternString(STWINFONT13)));
        src = g_statusFontNames[0];
        StringList_AppendRetained(arg0->_textCloseNameList, StringRef(InternString(src)));
        beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x47);
        k = 0;
        p = &g_statusFontNames[0];
        do {
            beNDMWWindow_QueueText(arg0, STWINFONT14_2, *p, space, LEFT_3);
            k += 1;
            p += 1;
        } while (k < 12);
        beNDMWWindow_QueueText(arg0, STWINFONT23, g_statusFontNames[0], space, RIGHT_2);
        beNDMWWindow_QueueText(arg0, STWINFONT23, g_statusFontNames[1], space, RIGHT_2);
        beNDMWWindow_QueueText(arg0, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
        al = ((int)igObject_GetAllocator(arg0));
        al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
        {
        /* the list window is owned by the stack reference while it is bound, listed and set up; its
         * share is released at the block end */
        igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((void *)al));
        beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
        /* matching construct: (unsigned) cast on the reference steers retail operand order */
        ObjectList_AppendRetained((unsigned)arg0->_subWindow, win.p);
        a = ((igIntList *)arg0->_impItems)->_count;
        if (a == 0) {
            win.p->_selectMax = 1;
        } else {
            win.p->_selectMax = a;
        }
        {
            beNDMWWindowSelect *t = (beNDMWWindowSelect *)win.p;
            t->_offsetPos[0] = -121.0f;
            t->_offsetPos[1] = 128.0f;
            t->_offsetPos[2] = 0.0f;
        }
        win.p->_startPoint = 0;
        StringList_AppendRetained(win.p->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
        StringList_AppendRetained(win.p->_textCloseNameList, StringRef(InternString(font100_2)));
        beNDMWWindow_RunMessageScript(win.p, txt_status_lua_2, 0x87);
        }
        arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
        beNDMWWindow_PresentModelAtOrigin(arg0, i_stfolder, 0, SQ_FLAGOPEN, SQ_CLOSE_3);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            beNDMWStatusCtrlFlag_RefreshText(arg0, 1, 1);
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        case 1:
            if (((beNDMWWindowList *)(arg0->_subWindow))->_count == arg0->_nowProcKazu) {
                a = arg0->_retCode;
                if (a != -1 && arg0->_st2 != a) {
                    beNDMWStatusCtrlFlag_RefreshText(arg0, 0, 1);
                    arg0->_st2 = arg0->_retCode;
                    arg0->_st3 = 0;
                }
            } else {
                arg0->_st0 = arg0->_st0 + 1;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st1 = 0;
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

void beNDMWStatusCtrlFlag_RefreshText(beNDMWStatusCtrlFlag *arg0, int arg1, int arg2) {
    int s0;
    int v6;
    igDataList *l;
    int s5;
    int w3;
    char **v4;
    char **w4;
    int v3;
    beMessenger_SendNamed(arg0->_messenger, DATABASE_7, impItem_2, 0, GETDATABASE_7);
    s0 = beMessenger_GetObject(arg0->_messenger, 0);
    if (arg1 != 0) {
        v6 = 0;
        l = (igDataList *)arg0->_impItems;
        if (0 < l->_count) {
            v3 = 0;
            v4 = g_statusFontNames;
            do {
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
                beMessenger_AppendString(arg0->_messenger, STWINFONT14_2);
                beMessenger_AppendString(arg0->_messenger, *v4);
                s5 = arg0->_messenger;
                beMessenger_AppendString(s5, beDataBase_GetRecordString(s0, *(int *)&((unsigned char *)((igDataList *)arg0->_impItems)->_data)[v3], NAME_3));
                beMessenger_DispatchSelected(arg0->_messenger, TEXTSET_3);
                v6++;
                v4++;
                v3 += 4;
            } while (v6 < (l = (igDataList *)arg0->_impItems)->_count);
        }
        w3 = l->_count;
        if (w3 < 12) {
            w4 = &g_statusFontNames[w3];
            do {
                beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
                beMessenger_AppendString(arg0->_messenger, STWINFONT14_2);
                beMessenger_AppendString(arg0->_messenger, *w4);
                beMessenger_AppendString(arg0->_messenger, DISPOFF_2);
                beMessenger_DispatchSelected(arg0->_messenger, SWITCH_4);
                w3++;
                w4++;
            } while (w3 < 12);
        }
    }
    if (arg2 != 0 && ((igDataList *)arg0->_impItems)->_count > 0) {
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
        beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
        beMessenger_AppendString(arg0->_messenger, g_statusFontNames[0]);
        s5 = arg0->_messenger;
        beMessenger_AppendString(s5, beDataBase_GetRecordString(s0, ((int *)((igDataList *)arg0->_impItems)->_data)[arg0->_retCode], TXT_2));
        beMessenger_DispatchSelected(arg0->_messenger, TEXTSET_3);
    }
}

static inline int st1Of(const beNDMWStatusCtrlDisk *w) { return w->_st1; }

void beNDMWStatusCtrlDisk_Update(beNDMWStatusCtrlDisk *self)
{
    Str3 names;
    char bufC[8];
    float vecA[3];
    float vecB[3];
    float vecC[3];
    float vecD[3];
    int tq[12];
    switch (self->_st0) {
    case 0: {
        int i, j;
        if (self->_st1 == 0) self->_cursor = 0;
        MSG_SELECT_INT(self->_playerNo)
        igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_3);
        beNDMWWindow_PresentModelAtOrigin(self, i_stfolder, 0, SQ_AWINOFFOPEN, SQ_CLOSE_3);
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT13)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
        beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x48);
        for (i = 0; i < 12; i++)
            beNDMWWindow_QueueText(self, STWINFONT14_2, g_statusFontNames[i], space, LEFT_3);
        for (j = 0; j < 12; j++)
            beNDMWWindow_QueueText(self, STWINFONT15, g_statusFontNames[j], space, RIGHT_2);
        beNDMWWindow_QueueText(self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
        NEXT_ST0()
    }
    case 1:
        switch (st1Of(self)) {
        case 0: {
            void *al;
            int cnt;
            GET_ALLOC(al)
            { igSmartPointer<beNDMWStatusSelectE1> diskWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(al));
            beNDMWWindow_BindContext(diskWin.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, diskWin.p);
            MSG_SELECT_INT(self->_playerNo)
            igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_3);
            WSETI84(diskWin.p, 10)
            WSETPOS(diskWin.p, -121.0f, 128.0f, 0.0f)
            WSETI100(diskWin.p, self->_cursor)
            StringList_AppendRetained(((beNDMWWindowSelect *)diskWin.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
            StringList_AppendRetained(((beNDMWWindowSelect *)diskWin.p)->_textCloseNameList, StringRef(InternString(font100_2)));
            beNDMWWindow_RunMessageScript(diskWin.p, txt_status_lua_2, 0x2B);
            }
            cnt = ((igObjectList *)self->_subWindow)->_count;
            self->_nowProcKazu = cnt;
            self->_st1 = 2; self->_st3 = 0; self->_st2 = 0;
            self->_st2 = self->_cursor; self->_st3 = 0;
            self->_st3 = 0x3E7;
            beNDMWStatusCtrlDisk_RefreshText(self, 1, 0);
            return;
        }
        case 2:
            if (!WIN_PENDING()) {
                if (self->_retCode != -1 && (self->_st2 != self->_retCode || self->_st3 == 0x3E7)) {
                    beNDMWStatusCtrlDisk_RefreshText(self, 0, 1);
                    self->_st2 = self->_retCode;
                    self->_st3 = 0;
                    return;
                }
                break;
            }
            switch (self->_retCode) {
            case -1:
                NEXT_ST0()
                return;
            default:
                self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
                self->_cursor = self->_retCode;
                return;
            }
        case 3:
            switch (self->_st2) {
            case 0: {
                void *al;
                *(Q48 *)tq = *(const Q48 *)DAT_004cf700;
                vecA[0] = -121.0f; vecA[1] = 128.0f; vecA[2] = 0.0f;
                beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, (const char *)tq[self->_cursor], (const char *)0, (float *)vecA);
                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> actionWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(al));
                beNDMWWindow_BindContext(actionWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, actionWin.p);
                WSETI84(actionWin.p, 2)
                WSETPOS(actionWin.p, 115.0f, 145.0f, 0.0f)
                WSETI100(actionWin.p, 0)
                beNDMWWindow_PresentModelAtOrigin(actionWin.p, i_stmenu02, 0, SQ_2LINEOPEN, SQ_CLOSE_3);
                beNDMWWindow_QueueText(actionWin.p, STWINFONT26, g_statusFontNames[0], space, LEFT_3);
                beNDMWWindow_QueueText(actionWin.p, STWINFONT26, g_statusFontNames[1], space, LEFT_3);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 1:
                beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x41);
                NEXT_ST2()
            case 2:
                if (WIN_PENDING()) {
                    switch (self->_retCode) {
                    case 0: self->_st1 = 4; self->_st3 = 0; self->_st2 = 0; return;
                    case 1: self->_st1 = 5; self->_st3 = 0; self->_st2 = 0; return;
                    default:
                        SEND_CLOSE();
                        RESET_ST1()
                        return;
                    }
                }
                break;
            }
            break;
        case 4:
            switch (self->_st2) {
            case 0: {
                void *al;
                int i;
                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> orderWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(al));
                beNDMWWindow_BindContext(orderWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, orderWin.p);
                MSG_SELECT_INT(self->_playerNo)
                igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_3);
                WSETI84(orderWin.p, 10)
                WSETPOS(orderWin.p, -121.0f, 128.0f, 0.0f)
                WSETI100(orderWin.p, self->_cursor)
                GET_ALLOC(al)
                igSmartPointer<igBoolList> decided((igBoolList *)igBoolList_Create(al));
                for (i = 0; i < 10; i++) {
                    if (i == self->_cursor) { BLIST_ADD(decided, GPR_00554a30) } else { BLIST_ADD(decided, GPR_00554a34) }
                }
                ObjectRef_AssignRetained((void **)&((beNDMWWindowSelect *)orderWin.p)->_decideList, decided.p);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 1:
                NEXT_ST2()
                self->_st3 = self->_cursor;
                return;
            case 2:
                if (!WIN_PENDING()) {
                    if (self->_retCode != -1 && self->_st3 != self->_retCode) {
                        beNDMWStatusCtrlDisk_RefreshText(self, 0, 1);
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    if (self->_retCode != -1) {
                        igObjectList *l;
                        MSG_SELECT_INT(self->_playerNo)
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_3)->_data;
                        SwapRef cursorDisk(((void **)l->_data)[self->_cursor]);
                        SwapRef targetDisk(((void **)l->_data)[self->_retCode]);
                        ObjectList_SetAtRetained_003e9160(l, self->_cursor, targetDisk.p);
                        ObjectList_SetAtRetained_003e9160(l, self->_retCode, cursorDisk.p);
                    }
                    SEND_CLOSE();
                    RESET_ST1()
                    return;
                }
                break;
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0: {
                void *al;
                int i;
                beNDMWItemDisk *item;
                MSG_SELECT_INT(self->_playerNo)
                item = (beNDMWItemDisk *)((int *)((igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_3)->_data)->_data)[self->_cursor];
                if (item->_kazu <= 0) {
                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWShopSelect00> emptyWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                    beNDMWWindow_BindContext(emptyWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, emptyWin.p);
                    NEXT_ST2()
                    StringList_AppendRetained(((beNDMWWindowSelect *)emptyWin.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
                    StringList_AppendRetained(((beNDMWWindowSelect *)emptyWin.p)->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
                    beNDMWWindow_RunMessageScript(emptyWin.p, txt_status_lua_2, 0x8D);
                    }
                } else {
                    igObjectList *dk;
                    ((igObjectList *)self->_playerNoList)->_count = 0;
                    dk = (igObjectList *)self->_diskList;
                    ObjectList_ReleaseRange(dk, 0, dk->_count);
                    ObjectList_ZeroRange(dk, 0, dk->_count);
                    dk->_count = 0;
                    for (i = 0; i < 4; i++) {
                        int obj;
                        MSG_SELECT_INT(i)
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        if (igProperty_GetRecordByte(obj, ISUSE_7)->_data != 0 && i != self->_playerNo) {
                            LIST_ADD(self->_playerNoList, i)
                            {
                            igObjectList *fl = (igObjectList *)igProperty_GetRecordFolder(obj, DISKFOLDER_3)->_data;
                            beNDMWItemDisk *found = 0;
                            int k;
                            for (k = 0; k < fl->_count; k++) {
                                beNDMWItemDisk *e = ((beNDMWItemDisk **)fl->_data)[k];
                                if (e->_recNo == item->_recNo) { found = e; break; }
                            }
                            if (found != 0) ObjectList_AppendRetained(self->_diskList, found);
                            else ObjectList_AppendRetained(self->_diskList, 0);
                            }
                        }
                    }
                    if (((igObjectList *)self->_playerNoList)->_count <= 0) {
                        GET_ALLOC(al)
                        { igSmartPointer<beNDMWShopSelect00> noPlayerWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                        beNDMWWindow_BindContext(noPlayerWin.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, noPlayerWin.p);
                        NEXT_ST2()
                        StringList_AppendRetained(((beNDMWWindowSelect *)noPlayerWin.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
                        StringList_AppendRetained(((beNDMWWindowSelect *)noPlayerWin.p)->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
                        beNDMWWindow_RunMessageScript(noPlayerWin.p, txt_status_lua_2, 0x8E);
                        }
                    } else {
                        self->_st1 = 6; self->_st3 = 0; self->_st2 = 0;
                        self->_receipt = 0;
                        return;
                    }
                }
                break;
            }
            case 1:
                SYNC_COUNT()
                NEXT_ST2()
            case 2:
                if (WIN_PENDING()) {
                    SEND_CLOSE();
                    RESET_ST1()
                    return;
                }
                break;
            }
            break;
        case 6:
            switch (self->_st2) {
            case 0:
                SEND_CLOSE();
                beNDMWWindow_PlayQueuedModelClose(self);
                CLOSE_LISTS()
                beNDMWWindow_ClearQueuedText(self);
            case 1:
                NEXT_ST2()
                return;
            case 2: {
                int i;
                beNDMWItemBase *item;
                igObjectList *lsx;
                switch (((igObjectList *)self->_playerNoList)->_count) {
                case 1:
                default:
                    beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_1ITEMOPEN, SQ_CLOSE_3);
                    break;
                case 2:
                    beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_2ITEMOPEN, SQ_CLOSE_3);
                    break;
                case 3:
                    beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_3ITEMOPEN, SQ_CLOSE_3);
                    break;
                }
                StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT39)));
                StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(font000_2)));
                StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT39)));
                StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(font001_2)));
                beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x4A);
                MSG_SELECT_INT(self->_playerNo)
                lsx = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DISKFOLDER_3)->_data;
                beNDMWWindow_QueueText(self, STWINFONT14_2, font000_2, beNDMWItemBase_GetRecordString(item = (beNDMWItemBase *)((int *)lsx->_data)[self->_cursor], igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]), NAME_3), LEFT_3);
                ObjectRef_Retain_003e90d0(item);
                ObjectRef_Release_003e9110(self->_sendDisk);
                self->_sendDisk = (int)item;
                names = DAT_004cf730;
                for (i = 0; i < ((igObjectList *)self->_playerNoList)->_count; i++) {
                    int pno = ((int *)((igObjectList *)self->_playerNoList)->_data)[i];
                    igObjectList *l2;
                    MSG_SELECT_INT(pno)
                    l2 = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), PLAYERNAME_3)->_data;
                    if (l2->_count > 0) {
                        DeviceRef firstDevice((void *)*(int *)l2->_data, kRetainReference);
                        beNDMWWindow_QueueObjectText(self, STWINFONT14_2, names.v[i], DeviceRef(firstDevice), LEFT_3);
                    }
                    bufC[0] = ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[i])->_kazu + 0x30;
                    bufC[1] = 0;
                    beNDMWWindow_QueueText(self, STWINFONT15, names.v[i], bufC, CENTER_2);
                }
                {
                    char bufA[2];
                    bufA[0] = ((beNDMWItemDisk *)self->_sendDisk)->_kazu + 0x30;
                    bufA[1] = 0;
                    beNDMWWindow_QueueText(self, STWINFONT38, font000_2, bufA, CENTER_2);
                }
                beNDMWWindow_QueueText(self, STWINFONT38, font001_2, text_0, CENTER_2);
                NEXT_ST2()
            }
            case 3: {
                void *al;
                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> playerWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(al));
                beNDMWWindow_BindContext(playerWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, playerWin.p);
                WSETPOS(playerWin.p, -121.0f, 109.0f, 0.0f)
                WSETI84(playerWin.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100(playerWin.p, self->_receipt)
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 4:
                if (WIN_PENDING()) {
                    if (self->_retCode == -1) {
                        self->_st1 = 7; self->_st3 = 0; self->_st2 = 0;
                        return;
                    }
                    self->_receipt = self->_retCode;
                    if (((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[self->_receipt])->_kazu >= 9) {
                        self->_st2 = 10; self->_st3 = 0;
                        return;
                    }
                    switch (self->_receipt) {
                    case 0:
                        vecB[0] = -121.0f; vecB[1] = 109.0f; vecB[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, SQ_OPEN00, (const char *)0, (float *)vecB);
                        break;
                    case 1:
                        vecC[0] = -121.0f; vecC[1] = 109.0f; vecC[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, SQ_OPEN01, (const char *)0, (float *)vecC);
                        break;
                    case 2:
                        vecD[0] = -121.0f; vecD[1] = 109.0f; vecD[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, SQ_OPEN02, (const char *)0, (float *)vecD);
                        break;
                    }
                    NEXT_ST2()
                    return;
                }
                break;
            case 5: {
                void *al;
                int a1, v0;
                GET_ALLOC(al)
                { igSmartPointer<beNDMWShopSelect52> quantityWin((beNDMWShopSelect52 *)beNDMWShopSelect52_Create(al));
                a1 = ((beNDMWItemDisk *)self->_sendDisk)->_kazu;
                v0 = 9 - ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[self->_receipt])->_kazu;
                self->_sendMax = (a1 < v0) ? a1 : v0;
                beNDMWWindow_BindContext(quantityWin.p, self, self->_insight, self->_playerNo, self->_sendMax);
                ObjectList_AppendRetained(self->_subWindow, quantityWin.p);
                WSETPOS(quantityWin.p, 68.0f, -3.0f, 0.0f)
                }
                SYNC_COUNT()
                NEXT_ST2()
                return;
            }
            case 6: {
                char bufB[2];
                bufB[0] = (self->_sendMax + 0x30) - self->_retCode;
                bufB[1] = 0;
                MSG_STR3(STWINFONT38, font001_2, bufB, TEXTSET_3)
            }
                NEXT_ST2()
                self->_st3 = self->_retCode;
            case 7:
                if (!WIN_PENDING()) {
                    if (self->_retCode != -1 && self->_retCode != self->_st3) {
                        self->_st2 = 6; self->_st3 = 0;
                        return;
                    }
                } else {
                    int rc = self->_retCode;
                    if (rc == -1) {
                        MSG_STR3(STWINFONT38, font001_2, text_0, TEXTSET_3)
                        SEND_CLOSE();
                        self->_st2 = 3; self->_st3 = 0;
                        return;
                    }
                    {
                        void *al;
                        rc = self->_sendMax - rc;
                        beNDMWItemDisk *sd = (beNDMWItemDisk *)self->_sendDisk;
                        beNDMWItemDisk *tg = ((beNDMWItemDisk **)((igObjectList *)self->_diskList)->_data)[self->_receipt];
                        { unsigned q = sd->_kazu; sd->_kazu = q - rc; }
                        { unsigned q = tg->_kazu; tg->_kazu = rc + q; }
                        GET_ALLOC(al)
                        { igSmartPointer<beNDMWShopSelect00> sentWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                        beNDMWWindow_BindContext(sentWin.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, sentWin.p);
                        beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x84);
                        }
                        SYNC_COUNT()
                        NEXT_ST2()
                        return;
                    }
                }
                break;
            case 8:
                if (WIN_PENDING()) {
                    MSG_STR3(STWINFONT29_3, font000_2, DISPOFF_2, SWITCH_4)
                    MSG_STR3(STWINFONT38, font001_2, text_0, TEXTSET_3)
                    SEND_CLOSE();
                    self->_st1 = 7; self->_st3 = 0; self->_st2 = 0;
                    return;
                }
                break;
            case 10: {
                void *al;
                GET_ALLOC(al)
                { igSmartPointer<beNDMWShopSelect00> fullWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                beNDMWWindow_BindContext(fullWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, fullWin.p);
                StringList_AppendRetained(((beNDMWWindowSelect *)fullWin.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
                StringList_AppendRetained(((beNDMWWindowSelect *)fullWin.p)->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
                beNDMWWindow_RunMessageScript(fullWin.p, txt_status_lua_2, 0x8F);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 11:
                if (WIN_PENDING()) {
                    MSG_STR3(STWINFONT38, font001_2, text_0, TEXTSET_3)
                    SEND_CLOSE();
                    self->_st2 = 3; self->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 7:
            switch (self->_st2) {
            case 0:
                beNDMWWindow_PlayQueuedModelClose(self);
                CLOSE_LISTS()
                beNDMWWindow_ClearQueuedText(self);
                NEXT_ST2()
            case 1:
                self->_st0 = 0; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
                self->_st1 = 1; self->_st3 = 0; self->_st2 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_ST0()
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void StringRefList_ResetRange(igStringRefList *arg0, int arg1, int arg2) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int temp_s4;
    int var_s3;
    void **temp_s2;
    void *temp_s1;
    int var_s0;
    void *temp_a0;

    temp_s4 = arg1 + arg2;
    var_s3 = arg1;
    if (arg1 < temp_s4) {
        var_s0 = arg1 * 4;
        do {
            temp_s2 = (void **)(arg0->_data + var_s0);
            if (((int *)g_stringPool)[0] == 0) {
                var_v0 = ((int)StringPool_Allocate(0x10));
                if (var_v0 != 0) {
                    var_v0 = ((int)StringPool_Construct(var_v0));
                }
                ((int *)g_stringPool)[0] = var_v0;
            }
            temp_s1 = (void *)(((void *)StringPool_Intern(((int *)g_stringPool)[0], 0)));
            temp_a0 = (void *)(*temp_s2);
            if (temp_a0 != 0) {
                temp_a1 = (int *)((char *)temp_a0 - 8);
                temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
                *(int *)((char *)(temp_a0) - 4) = temp_v1;
                if (temp_v1 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                }
            }
            var_s3 += 1;
            *temp_s2 = temp_s1;
            var_s0 += 4;
        } while (var_s3 < temp_s4);
    }
}

void ObjectList_ZeroRange(igObjectList *arg0, int arg1, int arg2) {
    int temp_a4;
    int var_a1;
    int var_a3;

    var_a1 = arg1;
    temp_a4 = var_a1 + arg2;
    var_a3 = var_a1 * 4;
    if (var_a1 < temp_a4) {
        do {
            var_a1 += 1;
            *(int *)((char *)arg0->_data + var_a3) = 0;
            var_a3 += 4;
        } while (var_a1 < temp_a4);
    }
}

void ObjectList_ReleaseRange(igObjectList *arg0, int arg1, int arg2) {
    int temp_s2;
    int var_s1;
    int var_s0;
    igObject *temp_a0;

    temp_s2 = arg1 + arg2;
    var_s1 = arg1;
    if (arg1 < temp_s2) {
        var_s0 = arg1 * 4;
        do {
            temp_a0 = *(igObject **)(arg0->_data + var_s0);
            if (temp_a0 != 0) {
                temp_a0->_refCount = temp_a0->_refCount - 1;
                if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < temp_s2);
    }
}

void **ObjectRef_AssignRetained(void **arg0, igObject *arg1) {
    igObject *temp_a0;

    if (arg1 != 0) {
        arg1->_refCount = (unsigned int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)(*arg0);
    if (temp_a0 != 0) {
        temp_a0->_refCount = (unsigned int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long) (int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *arg0 = arg1;
    return arg0;
}

void beNDMWStatusCtrlDisk_RefreshText(beNDMWStatusCtrlDisk *arg0, int arg1, int arg2) {
    char spAC[2];
    int i;
    beNDMWItemDisk *it;
    int s7;
    char *str;
    int off;
    int v1;
    igObjectList *s6;
    char **s0;
    beMessenger_SelectGroup(arg0->_messenger, GAMERAM_9);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, GETPLAYER_6);
    s6 = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), DISKFOLDER_3)->_data;
    s7 = igInsightCore_FindManager(arg0->_insight, g_beNDMWStatus_metaObject[0]);
    if (arg1 != 0) {
        spAC[1] = 0;
        i = 0;
        if (0 < s6->_count) {
            off = 0;
            s0 = &g_statusFontNames[0];
            do {
                it = *(beNDMWItemDisk **)((char *)s6->_data + off);
                if (it != 0) {
                    str = ((char *)beNDMWItemBase_GetRecordString(it, s7, NAME_3));
                    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(arg0->_messenger, STWINFONT14_2);
                    beMessenger_AppendString(arg0->_messenger, *s0);
                    beMessenger_AppendString(arg0->_messenger, str);
                    beMessenger_DispatchSelected(arg0->_messenger, TEXTSET_3);
                    spAC[0] = it->_kazu + 0x30;
                    beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(arg0->_messenger, STWINFONT15);
                    beMessenger_AppendString(arg0->_messenger, *s0);
                    beMessenger_AppendString(arg0->_messenger, spAC);
                    beMessenger_DispatchSelected(arg0->_messenger, TEXTSET_3);
                }
                i++;
                off += 4;
                s0 += 1;
            } while (i < s6->_count);
        }
    }
    if (arg2 != 0) {
        v1 = arg0->_retCode;
        if (v1 != -1) {
            str = ((char *)beNDMWItemBase_GetRecordString(((beNDMWItemDisk **)s6->_data)[v1], s7, TXT_2));
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
            beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
            beMessenger_AppendString(arg0->_messenger, g_statusFontNames[0]);
            beMessenger_AppendString(arg0->_messenger, str);
            beMessenger_DispatchSelected(arg0->_messenger, TEXTSET_3);
            beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
            beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
            beMessenger_AppendString(arg0->_messenger, g_statusFontNames[0]);
            beMessenger_AppendString(arg0->_messenger, DISPON_2);
            beMessenger_DispatchSelected(arg0->_messenger, SWITCH_4);
            return;
        }
        beMessenger_SelectGroup(arg0->_messenger, TEXTCTL_5);
        beMessenger_AppendString(arg0->_messenger, STWINFONT29_3);
        beMessenger_AppendString(arg0->_messenger, g_statusFontNames[0]);
        beMessenger_AppendString(arg0->_messenger, DISPOFF_2);
        beMessenger_DispatchSelected(arg0->_messenger, SWITCH_4);
    }
}

void beNDMWStatusCtrlBit_Update(beNDMWStatusCtrlBit *arg0) {
    int s2;
    int al;
    int i;
    int s1;
    igIntList *l4;
    switch (arg0->_st0) {
    case 0:
        beMessenger_SendGroup(arg0->_messenger, GAMERAM_9, GETCOMMON_6);
        igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), NINZU_4);
        i = 0;
        do {
            beMessenger_SelectGroup(arg0->_messenger, GAMERAM_9);
            beMessenger_AppendInt(arg0->_messenger, i);
            beMessenger_DispatchSelected(arg0->_messenger, GETPLAYER_6);
            if (igProperty_GetRecordByte(beMessenger_GetObject(arg0->_messenger, 0), ISUSE_7)->_data != 0 && i != arg0->_playerNo) {
                l4 = (igIntList *)arg0->_playerNoList;
                s1 = l4->_count;
                if (s1 < l4->_capacity) {
                    l4->_count = count(l4) + 1;
                } else {
                    List_Resize(l4, s1 + 1, 4);
                }
                ((int *)l4->_data)[s1] = i;
            }
            i += 1;
        } while (i < 4);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        if (((igIntList *)arg0->_playerNoList)->_count == 0) {
            arg0->_st1 = 0;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        } else {
            arg0->_st1 = 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        }
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                al = ((int)igObject_GetAllocator(arg0));
                al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                {
                    igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((void *)al));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                    ObjectList_AppendRetained((unsigned)arg0->_subWindow, win.p);
                    StringList_AppendRetained(((beNDMWWindow *)win.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
                    s2 = (int)g_statusFontNames[0];
                    StringList_AppendRetained(((beNDMWWindow *)win.p)->_textCloseNameList, StringRef(InternString((const char *)s2)));
                    beNDMWWindow_RunMessageScript(arg0, txt_status_lua_2, 0x58);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                al = ((int)igObject_GetAllocator(arg0));
                al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
                {
                    igSmartPointer<beNDMWStatusCtrlSendBit> win((beNDMWStatusCtrlSendBit *)beNDMWStatusCtrlSendBit_Create(al));
                    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
                    ObjectList_AppendRetained((unsigned)arg0->_subWindow, win.p);
                    {
                        igIntList *lst = (igIntList *)arg0->_playerNoList;
                        ChildWindow *w = (ChildWindow *)win.p;
                        ChildWindow *old;
                        if (lst != 0) lst->_refCount = lst->_refCount + 1;
                        old = (ChildWindow *)w->f92;
                        if (old != 0) {
                            old->_refCount = old->_refCount - 1;
                            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
                        }
                        w->f92 = (int)lst;
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


void beNDMWStatusCtrlSendBit_Update(beNDMWStatusCtrlSendBit *p) {
    Tri spF0;
    Tri spE0;
    int spD0[3], spC0[3], spB0[3];
    int spA0[4], sp90[4], sp80[4], sp70[4], sp60[4];
    int k, i, n, cnt;
    int *tbl;
    int k2, n2, oe;
    int o, al, rec, t, mx, b, sw;
    int pad, c0, c1, c3, c2, dig, e;
    bool up, dn;
    int i2; 

    switch (p->_st0) {
    case 0:
        t = ((igIntList *)p->_playerNoList)->_count;
        switch (t) { case 1: default: beNDMWWindow_PresentModelAtOrigin(p, i_stmenu02, 0, SQ_1BITOPEN, SQ_CLOSE_3); break; case 2: beNDMWWindow_PresentModelAtOrigin(p, i_stmenu02, 0, SQ_2BITOPEN, SQ_CLOSE_3); break; case 3: beNDMWWindow_PresentModelAtOrigin(p, i_stmenu02, 0, SQ_3BITOPEN, SQ_CLOSE_3); break; }
        StringList_AppendRetained(p->_textCloseTypeList, StringRef(InternString(STWINFONT39)));
        StringList_AppendRetained(p->_textCloseNameList, StringRef(InternString(font000_2)));
        StringList_AppendRetained(p->_textCloseTypeList, StringRef(InternString(STWINFONT39)));
        StringList_AppendRetained(p->_textCloseNameList, StringRef(InternString(font001_2)));
        beNDMWWindow_RunMessageScript(p, txt_status_lua_2, 0x4C);
        beNDMWWindow_QueueText(p, STWINFONT28, font000_2, space, CENTER_2);
        beNDMWWindow_QueueText(p, STWINFONT27, font000_2, space, RIGHT_2);
        tbl = spF0.v;
        spF0 = DAT_004cf740[0];
        k = 0;
        if (0 < ((igIntList *)p->_playerNoList)->_count) {
            i = 0;
            do {
                n = *(int *)(((igIntList *)p->_playerNoList)->_data + i);
                SEL(GAMERAM_9);
                API(n);
                DSP(GETPLAYER_6);
                n = beMessenger_GetObject(p->_messenger, 0);
                beNDMWWindow_QueueText(p, STWINFONT14_2, *tbl, space, LEFT_3);
                sprintf(spA0, percent_d_3, igProperty_GetRecord(n, BIT_5)->_data);
                beNDMWWindow_QueueText(p, STWINFONT27, *tbl, space, RIGHT_2);
                k += 1;
                i += 4;
                tbl += 1;
            } while (k < ((igIntList *)p->_playerNoList)->_count);
        }
        p->_receipt = 0;
        p->_st0 = p->_st0 + 1;
        p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
    case 1:
        switch (p->_st2) {
        case 0:
            k = 0;
            do {
                sprintf(sp90, font_03d, k);
                SEL(TEXTCTL_5);
                APS(STWINFONT28);
                APS(sp90);
                APS(DISPOFF_2);
                DSP(SWITCH_4);
                k += 1;
            } while (k < 7);
            p->_editBit = 0;
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(font000_2); APS(CENTER_2); DSP(ALIGN_2);
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(font000_2); APS(text_0); DSP(TEXTSET_3);
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(font000_2); APS(DISPON_2); DSP(SWITCH_4);
            SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
            sprintf(sp80, percent_d_3, igProperty_GetRecord(beMessenger_GetObject(p->_messenger, 0), BIT_5)->_data);
            SEL(TEXTCTL_5); APS(STWINFONT27); APS(font000_2); APS(sp80); DSP(TEXTSET_3);
            tbl = spE0.v;
            spE0 = DAT_004cf750[0];
            k2 = 0;
            if (0 < ((igIntList *)p->_playerNoList)->_count) {
                i2 = 0;
                do {
                    oe = *(int *)(((igIntList *)p->_playerNoList)->_data + i2);
                    SEL(GAMERAM_9); API(oe); DSP(GETPLAYER_6);
                    n2 = beMessenger_GetObject(p->_messenger, 0);
                    {
                    DeviceRef r11C((void *)*(int *)(*(int *)(igProperty_GetRecordFolder(n2, PLAYERNAME_3)->_data + 16)));
                    if (r11C.p != 0) {
                        r11C.p->_refCount = r11C.p->_refCount + 1;
                    }
                    SEL(TEXTCTL_5); APS(STWINFONT14_2); APS(*tbl); APO(r11C.p); DSP(TEXTSET_3);
                    sprintf(sp70, percent_d_3, igProperty_GetRecord(n2, BIT_5)->_data);
                    SEL(TEXTCTL_5); APS(STWINFONT27); APS(*tbl); APS(sp70); DSP(TEXTSET_3);
                    }
                    k2 += 1;
                    i2 += 4;
                    tbl += 1;
                } while (k2 < ((igIntList *)p->_playerNoList)->_count);
            }
            al = H_41de40::AllocFor(p);
            {
            float *q118;
            igSmartPointer<beNDMWStatusSelectE1> r118((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((void *)al));
            beNDMWWindow_BindContext(r118.p, p, p->_insight, p->_playerNo, 0);
            ObjectList_AppendRetained(p->_subWindow, r118.p);
            q118 = (float *)((beNDMWStatusSelectE1 *)r118.p)->_offsetPos;
            q118[0] = -121.0f;
            q118[1] = 109.0f;
            q118[2] = 0.0f;
            ((beNDMWStatusSelectE1 *)r118.p)->_selectMax = ((igIntList *)p->_playerNoList)->_count;
            ((beNDMWStatusSelectE1 *)r118.p)->_startPoint = p->_receipt;
            }
            p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
            p->_st2 = p->_st2 + 1;
            p->_st3 = 0;
        case 1:
            if (((igObjectList *)p->_subWindow)->_count != p->_nowProcKazu) {
                t = p->_retCode;
                if (t == -1) {
                    p->_st0 = p->_st0 + 1;
                    p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
                    return;
                }
                p->_receipt = t;
                switch (p->_receipt) {
                case 0:
                    spD0[0] = 0xC2F20000; spD0[1] = 0x42DA0000; spD0[2] = 0;
                    beNDMWWindow_PresentModel((beNDMWListCtrl *)p, i_stcursor04, 0, SQ_OPEN00, (const char *)0, (float *)spD0);
                    break;
                case 1:
                    spC0[0] = 0xC2F20000; spC0[1] = 0x42DA0000; spC0[2] = 0;
                    beNDMWWindow_PresentModel((beNDMWListCtrl *)p, i_stcursor04, 0, SQ_OPEN01, (const char *)0, (float *)spC0);
                    break;
                case 2:
                    spB0[0] = 0xC2F20000; spB0[1] = 0x42DA0000; spB0[2] = 0;
                    beNDMWWindow_PresentModel((beNDMWListCtrl *)p, i_stcursor04, 0, SQ_OPEN02, (const char *)0, (float *)spB0);
                    break;
                }
                al = H_41de40::AllocFor(p);
                {
                igSmartPointer<beNDMWShopSelect34> r114((beNDMWShopSelect34 *)beNDMWShopSelect34_Create(al));
                beNDMWWindow_BindContext(r114.p, p, p->_insight, p->_playerNo, 3);
                ObjectList_AppendRetained(p->_subWindow, r114.p);
                FUN_004402e0(r114.p, p->_editBit, 1, font_03d);
                }
                p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
                SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
                mx = igProperty_GetRecord(beMessenger_GetObject(p->_messenger, 0), BIT_5)->_data;
                if (mx >= 0x98967F) {
                    mx = 0x98967F;
                }
                o = ((int *)((igIntList *)p->_playerNoList)->_data)[p->_receipt];
                SEL(GAMERAM_9); API(o); DSP(GETPLAYER_6);
                b = 0x98967F - igProperty_GetRecord(beMessenger_GetObject(p->_messenger, 0), BIT_5)->_data;
                p->_editMax = (mx < b) ? mx : b;
                p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
                p->_st2 = p->_st2 + 1;
                p->_st3 = 0;
                return;
            }
            break;
        case 2:
            sw = p->_subWindow;
            if (((igObjectList *)sw)->_count == p->_nowProcKazu) {
                t = p->_retCode;
                if (t != -1) {
                    if (p->_st3 == t) {
                        beMessenger_SendNamed(p->_messenger, SELECTCTRL_2, i_stcursor03, p->_playerNo, ISSELECTNOW);
                        if (beMessenger_GetBool(p->_messenger, 0) & 0xFF) {
                            pad = ((int)bePadManager_GetPadForPlayer(p->_padManager, p->_playerNo));
                            c3 = ((bePadData *)pad)->_trigger;
                            c2 = ((bePadData *)pad)->_repeat;
                            c0 = ((bePadData *)pad)->_lTrg | ((bePadData *)pad)->_lRpt;
                            up = (c0 & 1) || ((c3 | c2) & 0x10);
                            dn = (c0 & 4) || ((c3 | c2) & 0x40);
                            if (up || dn) {
                                e = p->_editBit;
                                dig = 1;
                                t = 7 - p->_retCode;
                                cnt = t;
                                for (; cnt > 1; cnt--) { dig *= 10; }
                                if (up) {
                                    p->_editBit = p->_editBit + dig;
                                    c1 = p->_editMax;
                                    if (p->_editBit >= c1) {
                                        p->_editBit = c1;
                                    }
                                } else if (dn) {
                                    p->_editBit = p->_editBit - dig;
                                    if (p->_editBit <= 0) {
                                        p->_editBit = 0;
                                    }
                                }
                                c1 = p->_editBit;
                                if (c1 != e) {
                                    FUN_004402e0(((int *)((igObjectList *)p->_subWindow)->_data)[0], c1, t, font_03d, e, dig);
                                    SEL(SOUND_4); APS(CURSOR_MOVE); DSP(PLAY_3);
                                    return;
                                }
                            }
                        }
                    } else {
                        FUN_004402e0(((int *)((igObjectList *)sw)->_data)[0], p->_editBit, 7 - t, font_03d);
                        p->_st3 = p->_retCode;
                        return;
                    }
                }
            } else {
                if (p->_retCode == -1 || p->_editBit <= 0) {
                    beMessenger_SendNamed(p->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
                    p->_st2 = 0;
                    p->_st3 = 0;
                    return;
                }
                SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(font100_2); APS(DISPOFF_2); DSP(SWITCH_4);
                SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
                n = beMessenger_GetObject(p->_messenger, 0);
                t = igProperty_GetRecord(n, BIT_5)->_data - p->_editBit;
                igProperty_GetRecord(n, BIT_5)->_data = t;
                o = ((int *)((igIntList *)p->_playerNoList)->_data)[p->_receipt];
                SEL(GAMERAM_9); API(o); DSP(GETPLAYER_6);
                n = beMessenger_GetObject(p->_messenger, 0);
                mx = igProperty_GetRecord(n, BIT_5)->_data;
                t = mx + p->_editBit;
                igProperty_GetRecord(n, BIT_5)->_data = t;
                p->_st2 = p->_st2 + 1;
                p->_st3 = 0;
                return;
            }
            break;
        case 3:
            al = H_41de40::AllocFor(p);
            {
            igSmartPointer<beNDMWShopSelect00> r110((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((void *)al));
            beNDMWWindow_BindContext(r110.p, p, p->_insight, p->_playerNo, 0);
            ObjectList_AppendRetained(p->_subWindow, r110.p);
            beNDMWWindow_RunMessageScript(p, txt_status_lua_2, 0x85);
            }
            p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
            p->_st2 = p->_st2 + 1;
            p->_st3 = 0;
            return;
        case 4:
            if (((igObjectList *)p->_subWindow)->_count != p->_nowProcKazu) {
                SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(font000_2); APS(DISPOFF_2); DSP(SWITCH_4);
                SEL(SUBWND_2); API(p->_playerNo); DSP(UPDATE);
                beMessenger_SendNamed(p->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
                p->_st2 = 0;
                p->_st3 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(p);
        beNDMWWindow_RequestChildrenClose(p);
        k = 0;
        p->_st0 = p->_st0 + 1;
        p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
        do {
            sprintf(sp60, font_03d, k);
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(sp60); APS(DISPOFF_2); DSP(SWITCH_4);
            k += 1;
        } while (k < 7);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            p->_isRun = 0;
        }
        break;
    }
}

void beNDMWStatusCtrlSkill_Update(beNDMWStatusCtrlSkill *self)
{
    int st0 = self->_st0;
    switch (st0) {
    case 0:
        beNDMWWindow_PresentModelAtOrigin(self, i_sttitle, 0, SQ_OPEN_5, 0);
        beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 90);
        self->_skillMenu = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st1) {
        case 0: {
            igSmartPointer<beNDMWStatusSelect01> wr((beNDMWStatusSelect01 *)beNDMWStatusSelect01_Create((void *)H_41f190::PickAllocator(self)));
            beNDMWWindow_BindContext((int)wr.p, self, self->_insight, self->_playerNo, 91);
            ObjectList_AppendRetained(self->_subWindow, wr.p);
            ((int *)wr.p)[25] = self->_skillMenu;
            beNDMWWindow_QueueText(wr.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
            
            }
            self->_nowProcKazu = SW(self->_subWindow)->_count;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            if (self->_retCode != -1)
                beNDMWWindow_RunMessageScript(self, txt_status_lua_2, self->_retCode + 98);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st3 = self->_retCode;
        case 2:
            if (SW(self->_subWindow)->_count == self->_nowProcKazu) {
                if (self->_retCode != -1 && self->_st3 != self->_retCode) {
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else
            switch (self->_retCode) {
            case 0:
                beNDMWShinkaCtrl_Setup(self->_shinkaCtrl, self->_insight, self->_playerNo);
                if (SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list)->_count > 8)
                    self->_maxPage = 2;
                else
                    self->_maxPage = 1;
                self->_nowPage = 0;
                self->_cursor = 0;
            case 1:
            case 2:
                self->_skillMenu = self->_retCode;
                self->_st1 = 3;
                self->_st3 = 0;
                self->_st2 = 0;
                break;
            default:
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0: {
                void *model;
                switch (self->_skillMenu) {
                default: {
                    int b[3];
                    int a[3];
                    if (self->_maxPage > 1)
                        model = SQ_BWINONOPEN;
                    else
                        model = SQ_BWINOFFOPEN;
                    a[0] = 0x42FE0000;
                    a[1] = 0x42820000;
                    a[2] = 0;
                    b[0] = 0xC3120000;
                    b[1] = 0x42820000;
                    b[2] = 0;
                    ((VC_41f190 *)self)->v22(b, a);
                    break;
                }
                case 1:
                    model = SQ_BWINOFFOPEN;
                    break;
                case 2:
                    model = SQ_WAZAOPEN;
                    break;
                }
                beNDMWWindow_PresentModelAtOrigin(self, i_stfolder, 0, model, SQ_CLOSE_3);
                igSmartPointer<beNDMWStatusSelectE1> wr((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((void *)H_41f190::PickAllocator(self)));
                beNDMWWindow_BindContext((int)wr.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, wr.p);
                { int *t = (int *)wr.p; t[22] = 0xC2F20000;
                t[23] = 0x43000000;
                t[24] = 0; }
                ((int *)wr.p)[25] = 0;
                StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT13)));
                StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
                beNDMWWindow_RunMessageScript(self, txt_status_lua_2, self->_skillMenu + 95);
                switch (self->_skillMenu) {
                case 0: {
                    int n;
                    int i;
                    igObjectList *sl = SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list);
                    if (self->_maxPage > 1) {
                        n = 8;
                        beNDMWWindow_QueueText(self, STWINFONT24, g_statusFontNames[0], space, CENTER_2);
                        beNDMWWindow_QueueText(self, STWINFONT24, g_statusFontNames[1], space, CENTER_2);
                    } else {
                        if (sl->_count == 0) n = 2; else n = sl->_count;
                    }
                    for (i = 0; i < n; i++) {
                        beNDMWWindow_QueueText(self, STWINFONT14_2, g_statusFontNames[i], space, LEFT_3);
                        beNDMWWindow_QueueText(self, STWINFONT42, g_statusFontNames[i], space, LEFT_3);
                        beNDMWWindow_QueueText(self, STWINFONT18, g_statusFontNames[i], space, RIGHT_2);
                    }
                    beNDMWStatusCtrlSkill_RefreshText((beNDMWStatusCtrlSkill *)self, 1, 0);
                    ((int *)wr.p)[21] = n;
                    break;
                }
                case 1: {
                    int obj;
                    igObjectList *recs;
                    int level;
                    int limit;
                    int i;
                    char buf[24];
                    beMessenger_SelectGroup(self->_messenger, GAMERAM_9);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_6);
                    obj = beMessenger_GetObject(self->_messenger, 0);
                    recs = (igObjectList *)igProperty_GetRecordIntList(obj, SKILL_2)->_data;
                    level = igProperty_GetRecord(obj, LEVEL_3)->_data;
                    limit = H_41f190::Scale(level);
                    for (i = 0; i < recs->_count; i++) {
                        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT14_2)));
                        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[i])));
                        sprintf(buf, percent_d_3, ((int *)recs->_data)[i]);
                        beNDMWWindow_QueueText(self, STWINFONT18, g_statusFontNames[i], buf, RIGHT_2);
                        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                        beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                        beMessenger_AppendString(self->_messenger, (void *)g_statusFontNames[i]);
                        if (((int *)recs->_data)[i] >= limit) {
                            float col[3];
                            col[0] = 0.9f;
                            col[1] = 0.4f;
                            col[2] = 0.2f;
                            beMessenger_AppendVec3(self->_messenger, (float *)col);
                            beMessenger_DispatchSelected(self->_messenger, COLOR);
                        } else {
                            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_2);
                        }
                    }
                    beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 101);
                    ((int *)wr.p)[21] = recs->_count;
                    break;
                }
                case 2: {
                    igObjectList *recs;
                    int ctx;
                    int i;
                    int n;
                    beMessenger_SelectGroup(self->_messenger, GAMERAM_9);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, GETPLAYER_6);
                    recs = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), WAZALIST_2)->_data;
                    ctx = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                    for (i = 0; i < recs->_count; i++) {
                        beNDMWWindow_QueueText(self, STWINFONT14_2, g_statusFontNames[i],
                                     (void *)beNDMWItemBase_GetRecordString(((int *)recs->_data)[i], ctx, NAME_3),
                                     LEFT_3);
                    }
                    n = *(unsigned *)&recs->_count;
                    if (n == 0)
                        ((int *)wr.p)[21] = 1;
                    else
                        ((int *)wr.p)[21] = n;
                    break;
                }
                }
                beNDMWWindow_QueueText(self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                
                }
                self->_nowProcKazu = SW(self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_retCode = 0;
            case 1:
                if (self->_retCode != -1)
                    beNDMWStatusCtrlSkill_RefreshText((beNDMWStatusCtrlSkill *)self, 0, 1);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_retCode;
            case 2: {
                int n = SW(self->_subWindow)->_count;
                if (n == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                    if (self->_st3 != self->_retCode) {
                        self->_st2 = 1;
                        self->_st3 = 0;
                    } else
                    if (self->_skillMenu == 0) {
                        int found = 0;
                        int i;
                        for (i = 0; i < SW(self->_subWindow)->_count; i++) {
                            found = ((int *)SWV(self->_subWindow)->_data)[i];
                            if (found && igObject_IsKindOf(found, g_beNDMWStatusSelectE1_metaObject[0])) {
                                found = (int)(int *)found;
                            } else
                                found = 0;
                            if (found)
                                break;
                        }
                        if (found) {
                            bool ok = false;
                            if (beNDMWWindowSelect_CanRequestFO2TOP(found)) {
                                if (((VC_41f190 *)self)->v23())
                                    ok = true;
                                else if (((VC_41f190 *)self)->v24())
                                    ok = true;
                            }
                            if (ok) {
                                int *f = (int *)found;
                                f[7] = 4;
                                f[10] = 0;
                                f[9] = 0;
                                f[8] = 0;
                                switch (self->_nowPage) {
                                default:
                                    f[21] = 8;
                                    break;
                                case 1:
                                    f[21] = SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list)->_count - 8;
                                    break;
                                }
                                self->_st2 = 1;
                                self->_st3 = 0;
                                self->_retCode = 0;
                                beNDMWStatusCtrlSkill_RefreshText((beNDMWStatusCtrlSkill *)self, 1, 0);
                            }
                        }
                    }
                    }
                } else {
                    if (self->_skillMenu == 1) {
                        int i;
                        for (i = 0; i < 9; i++) {
                            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                            beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                            beMessenger_AppendString(self->_messenger, (void *)g_statusFontNames[i]);
                            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_2);
                        }
                    }
                    beNDMWWindow_PlayQueuedModelClose(self);
                    H_41f190::ClearStrList(self->_modelCloseInfoNameList);
                    SW(self->_modelCloseRamNoList)->_count = 0;
                    H_41f190::ClearStrList(self->_modelCloseSeqNameList);
                    beNDMWWindow_ClearQueuedText(self);
                    self->_retCode = self->_skillMenu;
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
                break;
            }
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
        beNDMWWindow_SendModelSequence(self, i_sttitle, 0, SQ_CLOSE_3);
        beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
        beMessenger_AppendString(self->_messenger, STWINFONT12);
        beMessenger_AppendString(self->_messenger, (void *)g_statusFontNames[0]);
        beMessenger_AppendString(self->_messenger, DISPOFF_2);
        beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self))
            self->_isRun = 0;
        break;
    }
}

void beNDMWStatusCtrlSkill_RefreshText(beNDMWStatusCtrlSkill *self, int refreshRows, int refreshText) {
    igObjectList *list;
    int row;
    int name;
    char **font;
    int offs;
    char *text;
    beNDMWShinkaObject *item;
    int index;
    char cost[28];
    char page[4];
    int pg;
    int pg2;
    if (self->_retCode != -1) {
        if (refreshRows != 0) {
            row = 0;
            font = g_statusFontNames;
            list = (igObjectList *)((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list;
            do {
                index = row + self->_nowPage * 8;
                if (list->_count > 0 && index < list->_count) {
                    offs = index * 4;
                    item = ((beNDMWShinkaObject **)list->_data)[index];
                    name = item->_name;
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, (const char *)name);
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(self->_messenger, STWINFONT42);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, Lv);
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                    sprintf(cost, percent_d_3, ((beNDMWShinkaObject **)list->_data)[index]->_level);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(self->_messenger, STWINFONT18);
                    beMessenger_AppendString(self->_messenger, *font);
                    beMessenger_AppendString(self->_messenger, cost);
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                    text = DISPON_2;
                } else {
                    text = DISPOFF_2;
                }
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT42);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT18);
                beMessenger_AppendString(self->_messenger, *font);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, SWITCH_4);
                row++;
                font++;
            } while (row < 8);
            if (self->_maxPage > 1) {
                page[1] = 0;
                pg = self->_nowPage; pg += 0x31; page[0] = pg;
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT24);
                beMessenger_AppendString(self->_messenger, g_statusFontNames[0]);
                beMessenger_AppendString(self->_messenger, page);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                pg2 = self->_maxPage; pg2 += 0x30; page[0] = pg2;
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT24);
                beMessenger_AppendString(self->_messenger, g_statusFontNames[1]);
                beMessenger_AppendString(self->_messenger, page);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
            }
        }
        if (refreshText != 0) {
            switch (self->_skillMenu) {
            case 0:
                beMessenger_SendNamed(self->_messenger, DATABASE_7, shinka_3, 0, GETDATABASE_7);
                name = beMessenger_GetObject(self->_messenger, 0);
                list = (igObjectList *)((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list;
                index = self->_nowPage << 3; index += self->_retCode;
                if (list->_count > 0 && index < list->_count) {
                    text = (char *)beDataBase_GetRecordString(name, ((beNDMWShinkaObject **)list->_data)[index]->_id, EXPLANATION);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(self->_messenger, STWINFONT29_3);
                    beMessenger_AppendString(self->_messenger, g_statusFontNames[0]);
                    beMessenger_AppendString(self->_messenger, text);
                    beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                }
                break;
            case 1:
                beNDMWWindow_RunMessageScript(self, txt_status_lua_2, self->_retCode + 111);
                break;
            case 2:
                beMessenger_SelectGroup(self->_messenger, GAMERAM_9);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, GETPLAYER_6);
                list = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), WAZALIST_2)->_data;
                text = (char *)beNDMWItemBase_GetRecordString(((int *)list->_data)[self->_retCode], igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]), TXT_2);
                beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                beMessenger_AppendString(self->_messenger, STWINFONT29_3);
                beMessenger_AppendString(self->_messenger, g_statusFontNames[0]);
                beMessenger_AppendString(self->_messenger, text);
                beMessenger_DispatchSelected(self->_messenger, TEXTSET_3);
                break;
            }
        }
    }
}

/* The select windows made here are beNDMWStatusSelectE1 and beNDMWStatusSelectE0; their
 * +84/+88/+100 words are _selectMax, _offsetPos (an igVec3f: two floats and a zero word, reflected
 * as int[3]) and _startPoint. */






static inline int count_4207a0(const igDataList *list) { return list->_count; }

void beNDMWStatusSubMenu_Update(beNDMWStatusSubMenu *self)
{
    ModelNames tq;
    float vec[3];
    Str3 names;
    float v0[3];
    float vecb[3];
    float vF[3];
    float v100[3];
    float v110[3];
    switch (self->_st0) {
    case 0: {
        void *al;
        tq = DAT_004cf760;

        v0[0] = -121.0f; v0[1] = 128.0f; v0[2] = 0.0f;
        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, (const char *)(tq.v[self->_entCode % 12]), SQ_CLOSE_3, (float *)v0);
        beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_3LINEOPEN, SQ_CLOSE_3);
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT26)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT26)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[1])));
        StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT26)));
        StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(g_statusFontNames[2])));
        beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x43);
        GET_ALLOC(al)
        { igSmartPointer<beNDMWStatusSelectE1> menuWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(al));
        beNDMWWindow_BindContext(menuWin.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, menuWin.p);
        WSETI84_4207a0(beNDMWStatusSelectE1, menuWin.p, 3)
        WSETPOS_4207a0(beNDMWStatusSelectE1, menuWin.p, 115.0f, 145.0f, 0.0f)
        WSETI100_4207a0(beNDMWStatusSelectE1, menuWin.p, 0)
        }
        SYNC_COUNT()
        NEXT_ST0()
        self->_st1 = 0; self->_st3 = 0; self->_st2 = 0;
    }
    case 1:
        switch (self->_st1) {
        case 0:
            if (!WIN_PENDING()) break;
            switch (self->_retCode) {
            case 0: self->_st1 = 1; self->_st3 = 0; self->_st2 = 0; return;
            case 1: self->_st1 = 2; self->_st3 = 0; self->_st2 = 0; return;
            case 2: self->_st1 = 3; self->_st3 = 0; self->_st2 = 0; return;
            default: NEXT_ST0() return;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0: {
                void *al;

                beDataObjObjectList *rec;
                beNDMWItemBase *item;
                int ctx;
                GET_ALLOC(al)
                { igSmartPointer<beNDMWShopSelect00> messageWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                beNDMWWindow_BindContext(messageWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, messageWin.p);
                StringList_AppendRetained(((beNDMWShopSelect00 *)messageWin.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
                StringList_AppendRetained(((beNDMWShopSelect00 *)messageWin.p)->_textCloseNameList, StringRef(InternString(font000_2)));
                MSG_SELECT_INT(self->_playerNo)
                rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_3);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec->_data)->_data)[self->_selectDevice];
                ctx = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                if (item->_isEquip != 0) {
                    beNDMWWindow_RunMessageScript(messageWin.p, txt_status_lua_2, 0x90);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else if ((item->_kindNo == 0) == 1 && !(beNDMWItemBase_GetRecordBool(item, ctx, ISHAKAI) & 0xFF)) {
                    beNDMWWindow_RunMessageScript(messageWin.p, txt_status_lua_2, 0x91);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else {
                    beNDMWWindow_RunMessageScript(messageWin.p, txt_status_lua_2, 0x4E);
                    NEXT_ST2()
                }
                }
                SYNC_COUNT()
            }
            case 1:
                if (WIN_PENDING()) {
                    void *al;

                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWStatusSelectE0> yesNoWin((beNDMWStatusSelectE0 *)beNDMWStatusSelectE0_Create(al));
                    beNDMWWindow_BindContext(yesNoWin.p, self, self->_insight, self->_playerNo, 0x4F);
                    ObjectList_AppendRetained(self->_subWindow, yesNoWin.p);
                    WSETI84_4207a0(beNDMWStatusSelectE0, yesNoWin.p, 2)
                    }
                    SYNC_COUNT()
                    NEXT_ST2()
                case 2:
                    if (WIN_PENDING()) {
                        if (self->_retCode == 0) {
                            beDataObjObjectList *rec;
                            MSG_SELECT_INT(self->_playerNo)
                            rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_3);
                            LIST_REMOVE(rec->_data, self->_selectDevice)
                        }
                    default:
                        if (WIN_PENDING()) {
                            NEXT_ST0()
                            return;
                        }
                    }
                }
                break;
            }
            break;
        case 2: {
            int obj;
            igObjectList *L;
            igObjectList *a7;
            igObjectList *a8;
            igObjectList *aA;
            igObjectList *a5;
            igObjectList *a6;
            void *al;
            int i, j, k;
            MSG_SELECT_INT(self->_playerNo)
            obj = beMessenger_GetObject(self->_messenger, 0);
            L = (igObjectList *)igProperty_GetRecordFolder(obj, DEVICEFOLDER_3)->_data;
            GET_ALLOC(al)
            { ItemListRef keptItems(beNDMWItemBaseList_Create(al));
            a7 = (igObjectList *)igProperty_GetRecordFolder(obj, POWERSOCKET_3)->_data;
            a8 = (igObjectList *)igProperty_GetRecordFolder(obj, MAINSLOT_3)->_data;
            aA = (igObjectList *)igProperty_GetRecordFolder(obj, SUBSLOT_3)->_data;
            a5 = (igObjectList *)igProperty_GetRecordFolder(obj, POWERPOCKET_3)->_data;
            a6 = (igObjectList *)igProperty_GetRecordFolder(obj, MAINPOCKET_3)->_data;
            beNDMWStatusSubMenu_SortByRecordNo(self, ItemListRef(L));
            Helpers::AppendBoth(keptItems, a7, a5);
            Helpers::AppendBoth(keptItems, a8, a6);
            for (k = 0; k < aA->_count; k++) {
                int *e = (int *)((int *)aA->_data)[k];
                if (e != 0) ObjectList_AppendRetained(keptItems.p, e);
            }
            for (i = 0; i < ((igObjectList *)keptItems.p)->_count; i++)
                ObjectList_RemoveFirstRetained(L, ((int *)((igObjectList *)keptItems.p)->_data)[i], 0);
            GET_ALLOC(al) ItemListRef kind0Items(beNDMWItemBaseList_Create(al));
            GET_ALLOC(al) ItemListRef kind1Items(beNDMWItemBaseList_Create(al));
            GET_ALLOC(al) ItemListRef kind2Items(beNDMWItemBaseList_Create(al));
            GET_ALLOC(al) ItemListRef kind3Items(beNDMWItemBaseList_Create(al));
            if (L->_count > 0) do {
                beNDMWItemBase *e = (beNDMWItemBase *)((int *)L->_data)[0];
                int t = e->_kindNo;
                if (t == 0) ObjectList_AppendRetained(kind0Items.p, e);
                else if (t == 1) ObjectList_AppendRetained(kind1Items.p, e);
                else if (t == 2) ObjectList_AppendRetained(kind2Items.p, e);
                else if (t == 3) ObjectList_AppendRetained(kind3Items.p, e);
                else igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                LIST_REMOVE(L, 0)
            } while (L->_count > 0);
            beNDMWStatusSubMenu_SortByRevision(self, ItemListRef((igObjectList *)kind0Items.p));
            beNDMWStatusSubMenu_SortByRevision(self, ItemListRef((igObjectList *)kind1Items.p));
            beNDMWStatusSubMenu_SortByRevision(self, ItemListRef((igObjectList *)kind2Items.p));
            beNDMWStatusSubMenu_SortByRecordNo(self, ItemListRef((igObjectList *)kind3Items.p));
            while (((igObjectList *)keptItems.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)keptItems.p)->_data)[0]); LIST_REMOVE(keptItems.p, 0) }
            while (((igObjectList *)kind0Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind0Items.p)->_data)[0]); LIST_REMOVE(kind0Items.p, 0) }
            while (((igObjectList *)kind1Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind1Items.p)->_data)[0]); LIST_REMOVE(kind1Items.p, 0) }
            while (((igObjectList *)kind2Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind2Items.p)->_data)[0]); LIST_REMOVE(kind2Items.p, 0) }
            while (((igObjectList *)kind3Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind3Items.p)->_data)[0]); LIST_REMOVE(kind3Items.p, 0) }
            }
            NEXT_ST0()
            return;
        }
        case 3:
            switch (self->_st2) {
            case 0: {
                beDataObjObjectList *rec;
                int i;
                int nN;
                beNDMWItemBase *item;
                igDataList *lL;
                int ctx;
                bool flag;
                MSG_SELECT_INT(self->_playerNo)
                rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_3);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec->_data)->_data)[self->_selectDevice];
                ctx = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                for (i = 0; i < 4; i++) {
                    MSG_SELECT_INT(i)
                    if (igProperty_GetRecordByte(beMessenger_GetObject(self->_messenger, 0), ISUSE_7)->_data != 0 && i != self->_playerNo) {
                        nN = ((igDataList *)(self->_playerNoList))->_count; lL = (igDataList *)(self->_playerNoList);
                        if (nN < lL->_capacity) lL->_count = count_4207a0(lL) + 1; else List_Resize(lL, nN + 1, 4);
                        ((int *)lL->_data)[nN] = i;
                    }
                }
                flag = false;
                if (item->_isEquip != 0) {
                    flag = true;
                    self->_st3 = 0x92;
                } else if (!(beNDMWItemBase_GetRecordBool(item, ctx, ISJYOUDO) & 0xFF)) {
                    flag = true;
                    self->_st3 = 0x93;
                } else if (((igObjectList *)self->_playerNoList)->_count == 0) {
                    flag = true;
                    self->_st3 = 0x94;
                }
                if (flag) {
                    void *al;

                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWShopSelect00> refusalWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                    beNDMWWindow_BindContext(refusalWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, refusalWin.p);
                    beNDMWWindow_RunMessageScript(refusalWin.p, txt_status_lua_2, self->_st3);
                    SYNC_COUNT()
                    self->_st2 = 4;
                    self->_st3 = 0;
                    }
                } else {
                    beNDMWWindow *win;
                    win = (beNDMWWindow *)self->_deviceFolderList;
                    if (win != 0) {
                        win->_st0 = 2;
                        win->_st3 = 0;
                        win->_st2 = 0;
                        win->_st1 = 0;
                        beNDMWWindow_SendModelSequence(self, i_stcursor04, 0, SQ_CLOSE_3);
                        NEXT_ST2()
                    } else {
                        NEXT_ST0()
                    }
                    beNDMWWindow_ClearQueuedText(self);
                    return;
                }
                break;
            }
            case 1:
                if (beNDMWWindow_PollCloseComplete(self->_deviceFolderList) != 0) {
                    int cnt;
                    beDataObjObjectList *rec;
                    beNDMWItemBase *item;
                    int i;
                    ObjectRef_Retain_003e90d0(0);
                    ObjectRef_Release_003e9110(self->_deviceFolderList);
                    self->_deviceFolderList = 0;
                    cnt = ((igObjectList *)self->_playerNoList)->_count;
                    switch (cnt) {
                    case 1:
                    default:
                        beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_1CHIPOPEN, SQ_CLOSE_3);
                        break;
                    case 2:
                        beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_2CHIPOPEN, SQ_CLOSE_3);
                        break;
                    case 3:
                        beNDMWWindow_PresentModelAtOrigin(self, i_stmenu02, 0, SQ_3CHIPOPEN, SQ_CLOSE_3);
                        break;
                    }
                    StringList_AppendRetained(self->_textCloseTypeList, StringRef(InternString(STWINFONT39)));
                    StringList_AppendRetained(self->_textCloseNameList, StringRef(InternString(font000_2)));
                    beNDMWWindow_RunMessageScript(self, txt_status_lua_2, 0x49);
                    MSG_SELECT_INT(self->_playerNo)
                    rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_3);
                    {
                        igObjectList *dl = (igObjectList *)rec->_data;
                        int cx = igInsightCore_FindManager(self->_insight, g_beNDMWStatus_metaObject[0]);
                        item = (beNDMWItemBase *)((int *)dl->_data)[self->_selectDevice];
                        beNDMWWindow_QueueText(self, STWINFONT14_2, font000_2, beNDMWItemBase_GetRecordString(item, cx, NAME_3), LEFT_3);
                    }
                    beNDMWItemBase_GetRevisionColor(vec, item);
                    beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString(self->_messenger, STWINFONT14_2);
                    beMessenger_AppendString(self->_messenger, font000_2);
                    vecb[0] = vec[0]; vecb[1] = vec[1]; vecb[2] = vec[2];
                    beMessenger_AppendVec3(self->_messenger, vecb);
                    beMessenger_DispatchSelected(self->_messenger, COLOR);
                    names = DAT_004cf790;
                    for (i = 0; i < ((igObjectList *)self->_playerNoList)->_count; i++) {
                        int pno = ((int *)((igObjectList *)self->_playerNoList)->_data)[i];
                        int obj;
                        igObjectList *folder;
                        igObjectList *lst;
                        int c;
                        MSG_SELECT_INT(pno)
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        folder = (igObjectList *)igProperty_GetRecordFolder(obj, DEVICEFOLDER_3)->_data;
                        lst = (igObjectList *)igProperty_GetRecordFolder(obj, PLAYERNAME_3)->_data;
                        if (lst->_count > 0) {
                            DeviceRef firstDevice((void *)*(int *)lst->_data, kRetainReference);
                            beNDMWWindow_QueueObjectText(self, STWINFONT14_2, names.v[i], DeviceRef(firstDevice), LEFT_3);
                        }
                        c = folder->_count;
                        LIST_ADD_4207a0(self->_playerDeviceCnt, c)
                    }
                    NEXT_ST2()
                    return;
                }
                break;
            case 2: {
                void *al;

                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> playerWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create(al));
                beNDMWWindow_BindContext(playerWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, playerWin.p);
                WSETPOS_4207a0(beNDMWStatusSelectE1, playerWin.p, -121.0f, 109.0f, 0.0f)
                WSETI84_4207a0(beNDMWStatusSelectE1, playerWin.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100_4207a0(beNDMWStatusSelectE1, playerWin.p, self->_receipt)
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 3:
                if (WIN_PENDING()) {
                    void *al;

                    if (self->_retCode == -1) {
                        NEXT_ST0()
                        return;
                    }
                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWShopSelect00> resultWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create(al));
                    beNDMWWindow_BindContext(resultWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, resultWin.p);
                    SYNC_COUNT()
                    NEXT_ST2()
                    self->_st3 = -1;
                    StringList_AppendRetained(((beNDMWShopSelect00 *)resultWin.p)->_textCloseTypeList, StringRef(InternString(STWINFONT29_3)));
                    StringList_AppendRetained(((beNDMWShopSelect00 *)resultWin.p)->_textCloseNameList, StringRef(InternString(g_statusFontNames[0])));
                    self->_receipt = self->_retCode;
                    if (((int *)((igObjectList *)self->_playerDeviceCnt)->_data)[self->_receipt] >= 0x24) {
                        beNDMWWindow_RunMessageScript(resultWin.p, txt_status_lua_2, 0x95);
                    } else {
                        beDataObjObjectList *rec;
                        igObjectList *l;

                        int idx, val;
                        beNDMWWindow_RunMessageScript(resultWin.p, txt_status_lua_2, 0x83);
                        MSG_SELECT_INT(self->_playerNo)
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_3)->_data;
                        MovedItemRef movedItem((void *)((int *)l->_data)[self->_selectDevice]);
                        idx = self->_selectDevice;
                        LIST_REMOVE(l, idx)
                        val = ((int *)((igObjectList *)self->_playerNoList)->_data)[self->_receipt];
                        MSG_SELECT_INT(val)
                        ObjectList_AppendRetained(igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DEVICEFOLDER_3)->_data, movedItem.p);
                    }
                    switch (self->_retCode) {
                    case 0: {
                        vF[0] = -121.0f; vF[1] = 109.0f; vF[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, SQ_OPEN00, (const char *)0, (float *)vF);
                        break;
                    }
                    case 1: {
                        v100[0] = -121.0f; v100[1] = 109.0f; v100[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, SQ_OPEN01, (const char *)0, (float *)v100);
                        break;
                    }
                    case 2: {
                        v110[0] = -121.0f; v110[1] = 109.0f; v110[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWListCtrl *)self, i_stcursor04, 0, SQ_OPEN02, (const char *)0, (float *)v110);
                        break;
                    }
                    }
                    }
                }
                break;
            case 4:
            default:
                if (WIN_PENDING()) {
                    int keep;
                    beMessenger_SendNamed(self->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
                    keep = self->_st3;
                    NEXT_ST0()
                    self->_st3 = keep;
                    return;
                }
                break;
            }
            break;
        default:
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        if (self->_st3 == -1) {
            beMessenger_SelectGroup(self->_messenger, TEXTCTL_5);
            beMessenger_AppendString(self->_messenger, STWINFONT14_2);
            beMessenger_AppendString(self->_messenger, font000_2);
            beMessenger_DispatchSelected(self->_messenger, DEFAULTCOLOR_2);
        }
        NEXT_ST0()
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Releases entry i of an object list and closes the gap, clearing the vacated last word. */
static inline void RemoveItemAt(igObjectList *l, int i)
{
    ReleaseObject(((igObject **)l->_data)[i]);
    List_RemoveWordAt(l, i);
    ((int *)l->_data)[l->_count] = 0;
}

/* Sorts the items by revision, highest first: the best remaining one moves to a scratch list until none
 * is left, and the scratch list moves back. The placeholder records (kind 0 record 276, kind 1 record 31,
 * kind 2 record 44) then go to the end. */
void beNDMWStatusSubMenu_SortByRevision(void *self, const ItemListRef &items)
{
    void *al;
    igObjectList *l;
    igObjectList *src;
    beNDMWItemRevisionBase *best;
    int i;
    beNDMWItemRevisionBase *t;
    /* matching construct: variant sweep — one counter and bound per loop, declared in this order */
    int n, i2;
    int c, j;
    int k;
    GET_ALLOC(al)
    ItemListRef sorted(beNDMWItemBaseList_Create(al));
    /* matching construct: variant sweep — the list is re-read from the holder in each loop test, so its count loads on every pass */
    while ((l = (igObjectList *)items.p)->_count > 0) {
        best = ((beNDMWItemRevisionBase **)l->_data)[0];
        for (i = 1; i < (l = (igObjectList *)items.p)->_count; i++) {
            t = ((beNDMWItemRevisionBase **)l->_data)[i];
            if (t->_revision > best->_revision) best = t;
        }
        ObjectList_AppendRetained(sorted.p, best);
        ObjectList_RemoveFirstRetained(items.p, (int)best, 0);
    }
    n = l->_count;
    for (i2 = 0; i2 < n; i2++) ReleaseObject(((igObject **)l->_data)[i2]);
    c = l->_count;
    for (j = 0; j < c; j++) ((int *)l->_data)[j] = 0;
    l->_count = 0;
    while ((src = (igObjectList *)sorted.p)->_count > 0) {
        ObjectList_AppendRetained(items.p, ((int *)src->_data)[0]);
        RemoveItemAt((igObjectList *)sorted.p, 0);
    }
    for (k = ((igObjectList *)items.p)->_count - 1; k > -1; k--) {
        beNDMWItemBase *e = ((beNDMWItemBase **)((igObjectList *)items.p)->_data)[k];
        if ((e->_kindNo == 0 && e->_recNo == 276) || (e->_kindNo == 1 && e->_recNo == 31) || (e->_kindNo == 2 && e->_recNo == 44)) {
            ObjectList_AppendRetained(items.p, e);
            RemoveItemAt((igObjectList *)items.p, k);
        }
    }
}

/* Sorts the items by record number, lowest first, the same way. */
void beNDMWStatusSubMenu_SortByRecordNo(void *self, const ItemListRef &items)
{
    void *al;
    igObjectList *l;
    igObjectList *src;
    beNDMWItemBase *best;
    int i;
    beNDMWItemBase *t;
    /* matching construct: variant sweep — one counter and bound per loop, declared in this order */
    int n, i2;
    int c, j;
    GET_ALLOC(al)
    ItemListRef sorted(beNDMWItemBaseList_Create(al));
    /* matching construct: variant sweep — the list is re-read from the holder in each loop test, so its count loads on every pass */
    while ((l = (igObjectList *)items.p)->_count > 0) {
        best = ((beNDMWItemBase **)l->_data)[0];
        for (i = 1; i < (l = (igObjectList *)items.p)->_count; i++) {
            t = ((beNDMWItemBase **)l->_data)[i];
            if (t->_recNo < best->_recNo) best = t;
        }
        ObjectList_AppendRetained(sorted.p, best);
        ObjectList_RemoveFirstRetained(items.p, (int)best, 0);
    }
    n = l->_count;
    for (i2 = 0; i2 < n; i2++) ReleaseObject(((igObject **)l->_data)[i2]);
    c = l->_count;
    for (j = 0; j < c; j++) ((int *)l->_data)[j] = 0;
    l->_count = 0;
    while ((src = (igObjectList *)sorted.p)->_count > 0) {
        ObjectList_AppendRetained(items.p, ((int *)src->_data)[0]);
        RemoveItemAt((igObjectList *)sorted.p, 0);
    }
}

int beNDMWStatusSubMenu_GetMeta(void)
{
    return g_beNDMWStatusSubMenu_metaObject[0];
}

int beNDMWStatusCtrlSkill_GetMeta(void)
{
    return g_beNDMWStatusCtrlSkill_metaObject[0];
}

int beNDMWStatusCtrlSendBit_GetMeta(void)
{
    return g_beNDMWStatusCtrlSendBit_metaObject[0];
}

int beNDMWStatusCtrlBit_GetMeta(void)
{
    return g_beNDMWStatusCtrlBit_metaObject[0];
}

int beNDMWStatusCtrlDisk_GetMeta(void)
{
    return g_beNDMWStatusCtrlDisk_metaObject[0];
}

int beNDMWStatusCtrlFlag_GetMeta(void)
{
    return g_beNDMWStatusCtrlFlag_metaObject[0];
}

int beNDMWStatusCtrlFolder_GetMeta(void)
{
    return g_beNDMWStatusCtrlFolder_metaObject[0];
}

int beNDMWStatusCtrlD0_GetMeta(void)
{
    return g_beNDMWStatusCtrlD0_metaObject[0];
}

/* Class meta-object handle getter */
int beNDMWStatusSubSlot_GetMeta(void)
{
    return g_beNDMWStatusSubSlot_metaObject[0];
}

/* Class metaObject accessor */
int beNDMWStatusMainSlot_GetMeta(void) {
    return g_beNDMWStatusMainSlot_metaObject[0];
}

int beNDMWStatusPowerSocket_GetMeta(void)
{
    return g_beNDMWStatusPowerSocket_metaObject[0];
}

int beNDMWStatusCtrlBaseEquip_GetMeta(void)
{
    return g_beNDMWStatusCtrlBaseEquip_metaObject[0];
}

int beNDMWStatusCtrlEquip_GetMeta(void)
{
    return g_beNDMWStatusCtrlEquip_metaObject[0];
}

int beNDMWStatusCtrl00_GetMeta(void)
{
    return g_beNDMWStatusCtrl00_metaObject[0];
}

int beNDMWListCtrl_GetMeta(void)
{
    return g_beNDMWListCtrl_metaObject[0];
}

