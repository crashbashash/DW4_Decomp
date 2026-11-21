#include "dw4/support/reflected.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlD0.h"
#include "dw4/game/ndmw/beNDMWWindowSelect.h"
#define STICK_UP 1
#define STICK_RIGHT 2
#define STICK_DOWN 4
#define STICK_LEFT 8
#define BUTTON_RIGHT 0x20
#define BUTTON_LEFT 0x80
#define NEWWIN(H, var, ctor, ga) { al = ((Gap::Core::igObject *)(ga))->getMemoryPool();  al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);  igSmartPointer<H> var((H *)ctor(al));  beNDMWWindow_BindContext(var.p, self, self->_insight, self->_playerNo, 0);  lst = self->_subWindow;  ((Gap::Core::igObjectList *)lst)->append((Gap::Core::igObject *)var.p); }
#define GRP(a, b) { beMessenger_SelectGroup((beMessenger *)self->_messenger, LAYERCTL);  beMessenger_AppendString((beMessenger *)self->_messenger, &a[0]);  beMessenger_AppendString((beMessenger *)self->_messenger, &b[0]);  beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4); }
#define NEXT0() { self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0; }
#define FIN(a) { self->_st1 = a; self->_st3 = 0; self->_st2 = 0; }
#define RELEASE_OBJ(o) { \
    if (o) { \
        --(o)->_refCount; \
        if (((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(o); \
    } }
#define SELALLOC(fb) (g_useOwnerAllocator ? (fb) : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1)))
#define SEL(d) beMessenger_SelectGroup((beMessenger *)p->_messenger, d)
#define APS(d) beMessenger_AppendString((beMessenger *)p->_messenger, (const char *)d)
#define API(d) beMessenger_AppendInt((beMessenger *)p->_messenger, d)
#define DSP(d) beMessenger_DispatchSelected((beMessenger *)p->_messenger, d)
#define SUBCOUNT (((igObjectList *)p->_subWindow)->_count)
#define PUSHB(LP, B) { int n_; igUnsignedCharList *l_ = (igUnsignedCharList *)(LP); n_ = l_->_count; if (n_ < l_->_capacity) { l_->_count = n_ + 1; } else { ((Gap::Core::igDataList *)l_)->resizeAndSetCount(n_ + 1, 1); } ((unsigned char *)l_->_data)[n_] = (B); }
#define SETB(LP, IDX, B) { igUnsignedCharList *l_ = (igUnsignedCharList *)(LP); if (l_->_count != 0 && (IDX) >= 0 && (IDX) < l_->_count) { ((unsigned char *)l_->_data)[(IDX)] = (B); } }
#define SWV(h) ((igObjectList *)*(int *)&(h))
#define FIND(W) { int i_; (W) = 0; for (i_ = 0; i_ < ((igObjectList *)p->_subWindow)->_count; i_++) { (W) = ((int *)SWV(p->_subWindow)->_data)[i_]; if ((W) && ((Gap::Core::igObject *)(W))->isOfType(g_beNDMWStatusCtrlD0_metaObject)) { (W) = (int)(int *)(W); } else { (W) = 0; } if ((W)) break; } }
#define SETSLOT(L, IDX, V_) { Obj *v_ = (V_); Obj *old_; if (v_ != 0) { v_->_refCount = v_->_refCount + 1; } old_ = ((Obj **)(L)->_data)[(IDX)]; if (old_ != 0) { --old_->_refCount; if (((unsigned long long)(long long)(int)old_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old_); } if ((L)->_count != 0 && (IDX) >= 0 && (IDX) < (L)->_count) { ((Obj **)(L)->_data)[(IDX)] = v_; } }
/* matching construct: cxx_sweep — the item is read inside its retain test */
#define SET_ITEM(IDX, ITEM) { Obj *v; int r = (IDX); igObjectList *l = (igObjectList *)p->_powerSocket; \
    if ((v = (ITEM).p) != 0) { v->_refCount = v->_refCount + 1; } \
    ReleaseObject(((Obj **)l->_data)[r]); \
    if (l->_count != 0 && r >= 0 && r < l->_count) { ((Obj **)l->_data)[r] = v; } }
#define ADV() { p->_st0 = p->_st0 + 1; p->_st3 = 0; p->_st2 = 0; p->_st1 = 0; }
#define SETST(a, b) { p->_st0 = a; p->_st3 = 0; p->_st2 = 0; p->_st1 = 0; p->_st1 = b; p->_st3 = 0; p->_st2 = 0; }
#define NEXT2() { p->_st2 = p->_st2 + 1; p->_st3 = 0; }
#define REFRESH() { SEL(SUBWND_2); API(p->_playerNo); DSP(OFPREVIEW); }
#define PUBLISH() { beMessenger_SelectReceivers((beMessenger *)p->_messenger, GAMERAM_9, 0, 0); API(p->_playerNo); DSP(RECALCPLAYER_4); SEL(SUBWND_2); API(p->_playerNo); DSP(UPDATE); }
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igTDataList.h"
#include "dw4/core/igResult.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igobject_release.h"
#include "dw4/game/ndmw/beNDMWWindowDispatchView.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/ndmw/beNDMWGameRam.h"
#include "dw4/game/ndmw/beNDMWItemBaseList.h"
#include "dw4/game/ndmw/beNDMWItemBase.h"
#include "dw4/game/ndmw/beNDMWListCtrl.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2.h"
#include "dw4/game/ndmw/beNDMWShinkaCtrl.h"
#include "dw4/game/ndmw/beNDMWShopSelect00.h"
#include "dw4/game/ndmw/beNDMWShopSelect34.h"
#include "dw4/game/ndmw/beNDMWShopSelect52.h"
#include "dw4/game/ndmw/beNDMWStatus.h"
#include "dw4/game/ndmw/beNDMWStatusCtrl00.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlBaseEquip.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlBit.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlDisk.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlEquip.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlFlag.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlFolder.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlSendBit.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlSkill.h"
#include "dw4/game/ndmw/beNDMWStatusMainSlot.h"
#include "dw4/game/ndmw/beNDMWStatusPowerSocket.h"
#include "dw4/game/ndmw/beNDMWStatusSelect00.h"
#include "dw4/game/ndmw/beNDMWStatusSelect01.h"
#include "dw4/game/ndmw/beNDMWStatusSelectE0.h"
#include "dw4/game/ndmw/beNDMWStatusSelectE1.h"
#include "dw4/game/ndmw/beNDMWStatusSubMenu.h"
#include "dw4/game/ndmw/beNDMWStatusSubSlot.h"
#include "dw4/game/ndmw/beNDMWStatusTitle00.h"
#include "dw4/game/ndmw/beNDMWStatusTitle01.h"
#include "dw4/game/ndmw/beNDMWStatusTitle02.h"
#include "dw4/game/ndmw/beNDMWStatusTitle03.h"
#include "dw4/game/ndmw/beNDMWStatusTitle04.h"
#include "dw4/game/ndmw/beNDMWWindow.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igStringObj.h"
#include <stdio.h>
#include <string.h>
#include "dw4/support/list-services.h"
#include "dw4/core/igBoolList.h"
/* The element count of a list, read through a const view. */
template <class List> static inline int ListCount(const List *list) { return list->_count; }
/* The list index of a row shown on a page: the index of the page's first entry plus the row. */
static inline int RowIndex(int pageBase, int row) { return pageBase + row; }
#define REL(o) { igObject *rr = (igObject *)(o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if ((rr->_refCount & 0x7FFFFF) == 0) { igObject_Destroy(rr); } } }
#define LIST_CLEAR_AT(L, i) { REL((L)->_data[i]); \
    if ((L)->_count != 0 && (i) >= 0 && (i) < (L)->_count) (L)->_data[i] = 0; }
#define GET_ALLOC(v) { void *ga = ((Gap::Core::igObject *)self)->getMemoryPool(); if (g_useOwnerAllocator != 0) { v = ga; } else { v = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1); } }
#define RELEASE_STR(slot) { const char *held = slot; \
    if (held != 0) { int *hd = (int *)held - 2; \
        int cnt = ((int *)held)[-1] - 1; ((int *)held)[-1] = cnt; \
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define RETAIN_OBJ(o) { igObject *rr = (igObject *)(o); if (rr != 0) rr->_refCount = rr->_refCount + 1; }
#define NEXT_ST0() { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
#define ALLOC(al) al = ((Gap::Core::igObject *)self)->getMemoryPool(); al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
#define MSG() { beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5); beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3); beMessenger_AppendString((beMessenger *)self->_messenger, font100_2); beMessenger_AppendString((beMessenger *)self->_messenger, DISPOFF_2); beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4); }
#define CLEAR(lst) { igDataList *l = (igDataList *)(lst); int n = l->_count; int i; int *slot; int *nw; int o; int *old; if (0 < n) { i = 0; o = 0; do { slot = (int *)(l->_data + o); if (g_stringPool == 0) { int v = ((int)StringPool_Allocate(0x10)); if (v != 0) { v = ((int)StringPool_Construct((StringPool *)v)); } g_stringPool = (StringPool *)v; } nw = (int *)StringPool_Intern(g_stringPool, 0); old = (int *)*slot; if (old != 0) { int *hd = old - 2; int c = old[-1] - 1; old[-1] = c; if (c == 0) { StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); } } i++; *slot = (int)nw; o += 4; } while (i < n); } l->_count = 0; }
#define WSETI84(w, v) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); wt->_selectMax = (v); }
#define WSETI100(w, v) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); wt->_startPoint = (v); }
#define WSETPOS(w, x, y, z) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); *(float *)&wt->_offsetPos[0] = (x); *(float *)&wt->_offsetPos[1] = (y); *(float *)&wt->_offsetPos[2] = (z); }
#define MSG_SELECT_INT(v) { beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9); \
    beMessenger_AppendInt((beMessenger *)self->_messenger, v); beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6); }
#define NEXT_ST2() { self->_st2 = self->_st2 + 1; self->_st3 = 0; }
#define SYNC_COUNT() { self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count; }
#define WIN_PENDING() (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu)
#define LIST_ADD(decided, val) { int n_ = ((igDataList *)(decided))->_count; igDataList *l_ = (igDataList *)(decided); \
    if (n_ < l_->_capacity) l_->_count = ListCount(l_) + 1; else ((Gap::Core::igDataList *)l_)->resizeAndSetCount(n_ + 1, 4); \
    ((int *)l_->_data)[n_] = (val); }
#define SEND_CLOSE() beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3)
#define RESET_ST1() { self->_st1 = 0; self->_st3 = 0; self->_st2 = 0; }
#define MSG_STR3(a, b, c, d) { beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5); \
    beMessenger_AppendString((beMessenger *)self->_messenger, a); beMessenger_AppendString((beMessenger *)self->_messenger, b); \
    beMessenger_AppendString((beMessenger *)self->_messenger, c); beMessenger_DispatchSelected((beMessenger *)self->_messenger, d); }
#define CLOSE_LISTS() { igStringRefList *l1 = (igStringRefList *)self->_modelCloseInfoNameList; \
    StringRefList_ResetRange(l1, 0, l1->_count); l1->_count = 0; \
    ((igObjectList *)self->_modelCloseRamNoList)->_count = 0; \
    igStringRefList *l2 = (igStringRefList *)self->_modelCloseSeqNameList; \
    StringRefList_ResetRange(l2, 0, l2->_count); l2->_count = 0; }
#define APO(d) beMessenger_AppendObject((beMessenger *)p->_messenger, d)
#define SW(h) ((igObjectList *)(h))
#define LIST_REMOVE(lst, idx) { igObjectList *l_ = (igObjectList *)(lst); int ix_ = (idx); \
    beNDMWLoadIntf2_igObject_Release((igObject *)beNDMWLoadIntf2_igObjectList_Get((igDataList *)l_, ix_)); beNDMWGameRam_igObjectList_Remove(l_, ix_); \
    ((int *)l_->_data)[l_->_count] = 0; }

extern "C" int beNDMWListCtrl_GetMeta(void);
extern "C" void beNDMWStatusCtrlBaseEquip_PreviewSocketSwap(beNDMWStatusCtrlBaseEquip *p);
extern "C" void beNDMWStatusCtrlBaseEquip_ShowKindCursor(beNDMWStatusCtrlBaseEquip *self, int kind);
extern "C" void beNDMWStatusCtrlBaseEquip_QueuePanelText(beNDMWStatusCtrlBaseEquip *self);
/* kept local: no include/dw4 home (only CoreLibrary.h declares these). */
extern "C" int beNDMWStatusMainSlot_GetMeta(void);
extern "C" void beNDMWStatusSubSlot_PreviewPocketDevice(void);
extern "C" void beNDMWStatusSubSlot_OpenPocketList(void);
extern "C" void beNDMWStatusSubSlot_ShowPocketDescription(void);
extern "C" void beNDMWStatusSubSlot_OpenPocketMenu(void);
extern "C" void beNDMWStatusSubSlot_OpenPocketFolder(void);
extern "C" void beNDMWStatusSubSlot_EquipPocket(void);
extern "C" void beNDMWStatusSubSlot_ClearPocket(void);
extern "C" int beNDMWStatusSubSlot_GetMeta(void);
extern "C" int beNDMWStatusCtrlD0_GetSelectedIndex(beNDMWStatusCtrlD0 *self);
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
extern "C" char i_stcursorleft[];
extern "C" char SQ_HIDE[];
extern "C" char SQ_CLOSE_3[];
extern "C" char i_stcursorright[];
extern "C" char SQ_SELECT[];
extern "C" char MODELCTRL_3[];
extern "C" char SQ_MOVEEND[];
extern "C" char SQ_MOVENEXT[];
extern "C" void beNDMWListCtrl_PresentPageArrows(beNDMWListCtrl *self,const float *leftArrowPos,const float *rightArrowPos);
extern "C" bool beNDMWListCtrl_PrevPage(beNDMWListCtrl *self);
extern "C" bool beNDMWListCtrl_NextPage(beNDMWListCtrl *self);
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
extern "C" void beNDMWStatusCtrl00_Update(beNDMWStatusCtrl00 *self);
extern "C" void beNDMWStatusCtrlEquip_Update(beNDMWStatusCtrlEquip *self);
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

extern "C" void beNDMWStatusCtrlBaseEquip_Update(beNDMWStatusCtrlBaseEquip *p);
extern "C" char i_stcursor04[];
extern "C" char font002_2[];
extern "C" char font100_2[];
extern "C" char STWINFONT10[];
extern "C" char STWINFONT11[];
extern "C" char font101[];
extern "C" char font102[];
extern "C" char font103[];
extern "C" char font104[];
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
extern "C" void beNDMWStatus_PreviewEquipment(beNDMWStatusCtrlBaseEquip *self, ItemList *slotList, int slot, int index);
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
extern "C" void beNDMWStatusPowerSocket_PresentPanel(beNDMWStatusPowerSocket *self, int open);
extern "C" char COLOR[];
extern "C" void beNDMWStatusPowerSocket_RefreshSlotList(beNDMWStatusPowerSocket *self);
extern "C" char TXT_2[];
extern "C" void beNDMWStatusPowerSocket_ShowSlotDescription(beNDMWStatusPowerSocket *a);
extern "C" void beNDMWStatusPowerSocket_OpenSlotList(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_RefreshPocket(beNDMWStatusPowerSocket *self);
extern "C" char CANCELCOLOR_2[];
extern "C" void beNDMWStatusPowerSocket_OpenSlotMenu(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_OnSlotMenuDecided(beNDMWStatusPowerSocket *self);

extern "C" void beNDMWStatusPowerSocket_OpenDeviceFolder(beNDMWStatusPowerSocket *self);

typedef struct PropertyRecordTable { char p16[16]; int *data; } PropertyRecordTable;
extern "C" char DIGIMONNO_3[];
extern "C" char SOUBI_2[];
extern "C" char SKILL_2[];
extern "C" char SKILLPOINT_2[];
extern "C" int beNDMWStatusPowerSocket_CanEquip(beNDMWStatusPowerSocket *self, int index);
extern "C" void beNDMWStatusPowerSocket_EquipSelected(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_PreviewPocketDevice(beNDMWStatusPowerSocket *self, char *index, char *unusedArg2, int unusedArg3);
extern "C" void beNDMWStatusPowerSocket_EquipPocket(beNDMWStatusPowerSocket *self, char *unusedArg1, char *unusedArg2, char *unusedArg3);
extern "C" void beNDMWStatusPowerSocket_PreviewSlotDevice(beNDMWStatusPowerSocket *self, int index);
extern "C" void beNDMWStatusPowerSocket_OpenPocketList(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_ShowPocketDescription(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_OpenPocketMenu(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_OpenPocketFolder(beNDMWStatusPowerSocket *self);
extern "C" void beNDMWStatusPowerSocket_ClearPocket(beNDMWStatusPowerSocket *self);
extern "C" char SQ_MAINOPEN[];
extern "C" void beNDMWStatusMainSlot_PresentPanel(beNDMWStatusMainSlot *self, int open);
extern "C" void beNDMWStatusMainSlot_RefreshSlotList(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_ShowSlotDescription(beNDMWStatusMainSlot *a);
extern "C" void beNDMWStatusMainSlot_OpenSlotList(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_RefreshPocket(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_OpenSlotMenu(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_OnSlotMenuDecided(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_OpenDeviceFolder(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_PreviewPocketDevice(beNDMWStatusMainSlot * self, char * extra, char * unusedA, int unusedB);
extern "C" void beNDMWStatusMainSlot_PreviewSlotDevice(beNDMWStatusMainSlot *self, int index);
extern "C" void beNDMWStatusMainSlot_EquipPocket(beNDMWStatusMainSlot * self, char * unusedA, char * unusedB, char * unusedC);
extern "C" char LEVEL_3[];
extern "C" char LVPOINT[];
extern "C" int beNDMWStatusMainSlot_CanEquip(beNDMWStatusMainSlot *self, int index);
extern "C" void beNDMWStatusMainSlot_EquipSelected(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_OpenPocketList(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_ShowPocketDescription(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_OpenPocketMenu(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_OpenPocketFolder(beNDMWStatusMainSlot *self);
extern "C" void beNDMWStatusMainSlot_ClearPocket(beNDMWStatusMainSlot *self);
extern "C" char SQ_SUBOPEN[];
extern "C" void beNDMWStatusSubSlot_PresentPanel(beNDMWStatusSubSlot *w, int open);
extern "C" void beNDMWStatusSubSlot_RefreshSlotList(beNDMWStatusSubSlot *self);
extern "C" void beNDMWStatusSubSlot_ShowSlotDescription(beNDMWStatusSubSlot *a);
extern "C" void beNDMWStatusSubSlot_OpenSlotList(beNDMWStatusSubSlot *self);
extern "C" char font200[];
extern "C" char font201[];
extern "C" char font202[];
extern "C" char font203[];
extern "C" char font204[];
extern "C" void beNDMWStatusSubSlot_RefreshPocket(beNDMWStatusSubSlot *self);

extern "C" void beNDMWStatusSubSlot_OpenSlotMenu(beNDMWStatusSubSlot *self);
extern "C" void beNDMWStatusSubSlot_OnSlotMenuDecided(beNDMWStatusSubSlot *self);
extern "C" void beNDMWStatusSubSlot_OpenDeviceFolder(beNDMWStatusSubSlot *self);
extern "C" void beNDMWStatusSubSlot_EquipSelected(beNDMWStatusSubSlot *self, char *unusedArg1, char *unusedArg2, char *unusedArg3);
extern "C" void beNDMWStatusSubSlot_PreviewSlotDevice(beNDMWStatusSubSlot *self, char *index, char *unusedArg2, int unusedArg3);
extern "C" int beNDMWStatusSubSlot_CanEquip(beNDMWStatusSubSlot *self, int entryIndex);
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
extern "C" void beNDMWStatusCtrlD0_Update(beNDMWStatusCtrlD0 *self);
extern "C" int equippedMark[4];
extern "C" int unequippedMark[4];
extern "C" char WU[];
extern "C" char BLUEAB[];
extern "C" int beNDMWStatusCtrlD0_UpdatePageCount(beNDMWStatusCtrlD0 *self);
/* matching construct: inline type-checked cast; its early return gives the retail empty-arm branch. */
struct FolderHelpers {
static beNDMWStatusCtrlD0 *CastTo(beNDMWStatusCtrlD0 *p) { if (p != 0) { if (((Gap::Core::igObject *)p)->isOfType(g_beNDMWStatusCtrlD0_metaObject) != 0) { return p; } } return 0; }
static beNDMWStatusCtrlD0 *FindSub(beNDMWStatusCtrlFolder *w) { beNDMWStatusCtrlD0 *f = 0; int fi = 0; if (0 < ((igDataList *)w->_subWindow)->_count) { L:  f = CastTo(((beNDMWStatusCtrlD0 **)(*(igDataList **)&w->_subWindow)->_data)[fi]); if (f == 0) { fi++; if (fi < (*(igDataList **)&w->_subWindow)->_count) goto L; } } return f; }
};
extern "C" void beNDMWStatusCtrlFolder_Update(beNDMWStatusCtrlFolder *self);
extern "C" char GETCOMMON_6[];
extern "C" char FLAGFOLDER_2[];
extern "C" char SQ_FLAGOPEN[];
typedef struct PropertyRecordList { int p0, p4; int cnt; int cap; unsigned char *data; } PropertyRecordList;

extern "C" void beNDMWStatusCtrlFlag_Update(beNDMWStatusCtrlFlag *self);
extern "C" char DATABASE_7[];
extern "C" char impItem_2[];
extern "C" char GETDATABASE_7[];
extern "C" void beNDMWStatusCtrlFlag_RefreshText(beNDMWStatusCtrlFlag *self, int refreshRows, int refreshDescription);
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
extern "C" char font003_2[];
struct CellNameRow { const char *v[3]; };
struct ModelNameTable { const char *v[12]; };
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
extern "C" void beNDMWStatusCtrlDisk_Update(beNDMWStatusCtrlDisk *self);
extern "C" void StringRefList_ResetRange(igStringRefList *list, int first, int count);
static inline void ZeroRange(igObjectList *list, int first, int count)
{
    int end = first + count;
    for (int i = first; i < end; i++) {
        ((igObject **)list->_data)[i] = 0;
    }
}

static inline void ReleaseRange(igObjectList *list, int first, int count)
{
    int end = first + count;
    for (int i = first; i < end; i++) {
        REL(((igObject **)list->_data)[i])
    }
}

extern "C" void ObjectList_ZeroRange(igObjectList *list, int first, int count);
extern "C" void ObjectList_ReleaseRange(igObjectList *list, int first, int count);

/* Drops the list's share of every object it holds, clears the slots and empties it.
 * matching construct: inline budget — in retail beNDMWStatusCtrlDisk_Update passes
 * inline_max_total_size, so its removeAll leaves the two range helpers as the out-of-line calls
 * ObjectList_ReleaseRange and ObjectList_ZeroRange; this unit's spelling of that function counts
 * fewer nodes, so it makes those calls itself and only this inline expands the helpers. */
static inline void ObjectList_RemoveAll(igObjectList *list)
{
    ReleaseRange(list, 0, list->_count);
    ZeroRange(list, 0, list->_count);
    list->_count = 0;
}
extern "C" void **ObjectRef_AssignRetained(void **slot, igObject *object);
extern "C" void beNDMWStatusCtrlDisk_RefreshText(beNDMWStatusCtrlDisk *self, int refreshRows, int refreshDescription);
extern "C" char NINZU_4[];

extern "C" void beNDMWStatusCtrlBit_Update(beNDMWStatusCtrlBit *self);
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
extern "C" void beNDMWStatusCtrlSendBit_Update(beNDMWStatusCtrlSendBit *p);
extern "C" char SQ_BWINONOPEN[];
extern "C" char SQ_BWINOFFOPEN[];
extern "C" char SQ_WAZAOPEN[];
extern "C" char STWINFONT24[];
extern "C" char STWINFONT42[];
extern "C" char STWINFONT18[];
extern "C" char WAZALIST_2[];
extern "C" char STWINFONT12[];
/* Releases every string in the list, puts the empty string token back in each slot and empties
 * the list. */
static inline void ClearStringRefList(int listHandle)
{
    igStringRefList *l = (igStringRefList *)listHandle;
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool) pool = ((int)StringPool_Construct((StringPool *)pool));
            g_stringPool = (StringPool *)pool;
        }
        ref = (int *)StringPool_Intern(g_stringPool, 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1); }
        *slot = ref;
    }
    l->_count = 0;
}

/* The skill cap for a character level: the cap rises in four bands of levels. */
static inline int SkillLimitForLevel(int level)
{
    int limit = level < 37 ? level * 30 : level < 108 ? level * 20 + 360 : level < 228 ? level * 10 + 1430 : level * 8 + 1884;
    return limit;
}
extern "C" void beNDMWStatusCtrlSkill_Update(beNDMWStatusCtrlSkill *self);
extern "C" char Lv[];
extern "C" char shinka_3[];
extern "C" char EXPLANATION[];
extern "C" void beNDMWStatusCtrlSkill_RefreshText(beNDMWStatusCtrlSkill *self, int refreshRows, int refreshText);
extern "C" char ISHAKAI[];
extern "C" char ISJYOUDO[];
extern "C" char SQ_1CHIPOPEN[];
extern "C" char SQ_2CHIPOPEN[];
extern "C" char SQ_3CHIPOPEN[];
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
        if (e != 0) ((Gap::Core::igObjectList *)dst.p)->append((Gap::Core::igObject *)e);
        if (i == 0) {
            for (j = 0; j < b->_count; j++) {
                int *e2 = (int *)((int *)b->_data)[j];
                if (e2 != 0) ((Gap::Core::igObjectList *)dst.p)->append((Gap::Core::igObject *)e2);
            }
        }
    }
}
};
/* kept local: no include/dw4 home (only CoreLibrary.h declares these). */
class ItemListRef;
class DeviceRef;
extern "C" void beNDMWStatusSubMenu_SortByRevision(void *, const ItemListRef &);
extern "C" void beNDMWStatusSubMenu_SortByRecordNo(void *, const ItemListRef &);
extern "C" void beNDMWStatusSubMenu_Update(beNDMWStatusSubMenu *self);

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
    void *allocator = ((Gap::Core::igObject *)owner)->getMemoryPool();
    return g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
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
        if (child_ == 0 || ((Gap::Core::igObject *)child_)->isOfType(metaObject) == 0) child_ = 0; \
        if (child_ != 0) break; \
    } \
    (found) = (beNDMWStatusCtrlD0 *)child_; }

/* Asks MODELCTRL whether `model` is playing `sequence`; the answer is read with beMessenger_GetBool. */
template <class Window> static inline void QueryModelSequence(Window *window, const char *model, const char *sequence)
{
    beMessenger_SelectReceivers((beMessenger *)window->_messenger, MODELCTRL_3, model, 0);
    beMessenger_AppendString((beMessenger *)window->_messenger, sequence);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, ISSEQNAME_4);
}

/* Shows or hides a background layer through LAYERCTL. */
template <class Window> static inline void SwitchLayer(Window *window, const char *layer, const char *onOff)
{
    beMessenger_SelectGroup((beMessenger *)window->_messenger, LAYERCTL);
    beMessenger_AppendString((beMessenger *)window->_messenger, layer);
    beMessenger_AppendString((beMessenger *)window->_messenger, onOff);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, SWITCH_4);
}

/* The equipment panels' own slots 22-30, below igObject's 0-20 and the window's per-frame Update
 * (slot 21): beNDMWStatusCtrlBaseEquip's Update drives them and beNDMWStatusPowerSocket,
 * beNDMWStatusMainSlot and beNDMWStatusSubSlot implement them. */
class beNDMWStatusCtrlBaseEquipDispatchView : public beNDMWWindowDispatchView {
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
};

/* Slots 31-39, as the update step calls them. */
class beNDMWStatusEquipPanelDispatchView : public beNDMWStatusCtrlBaseEquipDispatchView {
public:
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

template <class Panel> static inline beNDMWStatusEquipPanelDispatchView *AsEquipPanel(Panel *panel)
{
    return (beNDMWStatusEquipPanelDispatchView *)panel;
}

/* The scrolling list windows' own slots, 22-24: the page arrows and the page turns (the
 * beNDMWListCtrl functions). */
class beNDMWListCtrlDispatchView : public beNDMWWindowDispatchView {
public:
    virtual void PresentPageArrows(const float *leftArrowPos, const float *rightArrowPos);
    virtual bool PrevPage();
    virtual bool NextPage();
};

template <class Window> static inline beNDMWListCtrlDispatchView *AsListCtrl(Window *window)
{
    return (beNDMWListCtrlDispatchView *)window;
}

/* SUBWND_2 messages carry the player number: OFPREVIEW and ONPREVIEW end and show the stat preview
 * of a device, UPDATE redraws the status sub-windows. */
template <class Window> static inline void SendSubWindowCommand(Window *window, const char *command)
{
    beMessenger_SelectGroup((beMessenger *)window->_messenger, SUBWND_2);
    beMessenger_AppendInt((beMessenger *)window->_messenger, window->_playerNo);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, command);
}

/* GAMERAM: recompute the player's stats from the equipment. */
template <class Window> static inline void RecalcPlayer(Window *window)
{
    beMessenger_SelectReceivers((beMessenger *)window->_messenger, GAMERAM_9, 0, 0);
    beMessenger_AppendInt((beMessenger *)window->_messenger, window->_playerNo);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, RECALCPLAYER_4);
}

/* GAMERAM: select a player's data object, read back with beMessenger_GetObject. */
template <class Window> static inline void SelectPlayer(Window *window, int playerNo)
{
    beMessenger_SelectGroup((beMessenger *)window->_messenger, GAMERAM_9);
    beMessenger_AppendInt((beMessenger *)window->_messenger, playerNo);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, GETPLAYER_6);
}

/* TEXTCTL command without a value (DEFAULTCOLOR, CANCELCOLOR) to a text cell. */
template <class Window> static inline void SendCellCommand(Window *window, const char *textType, const char *cell, const char *command)
{
    beMessenger_SelectGroup((beMessenger *)window->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)window->_messenger, textType);
    beMessenger_AppendString((beMessenger *)window->_messenger, cell);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, command);
}

/* Holds a new reference to `object` in `*slot`, releasing the one it replaces. */
static inline void AssignReference(int *slot, igObject *object)
{
    igObject *old;
    igObject::ref(object);
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
        ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, 1);
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
    igObject::ref(object);
    old = ((igObject **)list->_data)[index];
    RELEASE_REFERENCE(old);
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((igObject **)list->_data)[index] = object;
    }
}

/* Generates the PLAYERARMS_2 model for the name of the power chip in socket 0. */
static inline void SendPowerSocketName(beNDMWStatusCtrlBaseEquip *self)
{
    igStringRef name = StringList_CopyRetained((igStringRefList *)igProperty_GetRecordStringList((igObject *)self->_playerList, POWERSOCKETNAME_3)->_data, 0);
    beMessenger_SendNamed((beMessenger *)self->_messenger, PLAYERARMS_2, name.p, self->_playerNo, GENERATE_7);
}

/* The player's status record service (the insight's beNDMWStatus). */
static inline int FindStatus(int insight)
{
    return (int)igInsightCore_FindManager((igInsightCore *)insight, g_beNDMWStatus_metaObject);
}

/* Item `index` of an item list held as an object reference. */
static inline beNDMWItemBase *ItemAt(int itemList, int index)
{
    return ((beNDMWItemBase **)((beNDMWItemBaseList *)itemList)->_data)[index];
}

/* TEXTCTL messages to a window's text cell (text type, cell name). */
template <class Window> static inline void SetCellText(Window *window, const char *textType, const char *cell, const char *text)
{
    beMessenger_SelectGroup((beMessenger *)window->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)window->_messenger, textType);
    beMessenger_AppendString((beMessenger *)window->_messenger, cell);
    beMessenger_AppendString((beMessenger *)window->_messenger, text);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, TEXTSET_3);
}

template <class Window> static inline void SwitchCell(Window *window, const char *textType, const char *cell, const char *onOff)
{
    beMessenger_SelectGroup((beMessenger *)window->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)window->_messenger, textType);
    beMessenger_AppendString((beMessenger *)window->_messenger, cell);
    beMessenger_AppendString((beMessenger *)window->_messenger, onOff);
    beMessenger_DispatchSelected((beMessenger *)window->_messenger, SWITCH_4);
}

/* Create the previous/next page arrow models. The left arrow starts hidden; the right arrow is
 * shown when the list spans more than one page (_maxPage) and hidden otherwise. */
void beNDMWListCtrl_PresentPageArrows(beNDMWListCtrl *self,const float *leftArrowPos,const float *rightArrowPos){
    float leftPos[4],rightShownPos[4],rightHiddenPos[4];
    leftPos[0]=leftArrowPos[0];leftPos[1]=leftArrowPos[1];leftPos[2]=leftArrowPos[2];
    beNDMWWindow_PresentModel((beNDMWWindow *)self,i_stcursorleft,0,SQ_HIDE,SQ_CLOSE_3,leftPos);
    if(self->_maxPage>1){
        rightShownPos[0]=rightArrowPos[0];rightShownPos[1]=rightArrowPos[1];rightShownPos[2]=rightArrowPos[2];
        beNDMWWindow_PresentModel((beNDMWWindow *)self,i_stcursorright,0,SQ_SELECT,SQ_CLOSE_3,rightShownPos);
    }else{
        rightHiddenPos[0]=rightArrowPos[0];rightHiddenPos[1]=rightArrowPos[1];rightHiddenPos[2]=rightArrowPos[2];
        beNDMWWindow_PresentModel((beNDMWWindow *)self,i_stcursorright,0,SQ_HIDE,SQ_CLOSE_3,rightHiddenPos);
    }
}

/* Previous page. */
bool beNDMWListCtrl_PrevPage(beNDMWListCtrl *self){
    bool changed;
    bool upDownHeld;
    unsigned stickRepeat;
    unsigned stickTrigger;
    unsigned trigger;
    unsigned repeat;
    unsigned stickHeld;
    bool leftPressed;
    bePadData *pad;
    pad=bePadManager_GetPadForPlayer((bePadManager *)self->_padManager,self->_playerNo);
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
            beMessenger_SendNamed((beMessenger *)self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_MOVEEND);
        }else{
            beMessenger_SendNamed((beMessenger *)self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_MOVENEXT);
        }
        beMessenger_SendNamed((beMessenger *)self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_SELECT);
    }
    return changed;
}

/* Next page. */
bool beNDMWListCtrl_NextPage(beNDMWListCtrl *self){
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
    pad=bePadManager_GetPadForPlayer((bePadManager *)self->_padManager,self->_playerNo);
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
            beMessenger_SendNamed((beMessenger *)self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_MOVEEND);
        }else{
            beMessenger_SendNamed((beMessenger *)self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_MOVENEXT);
        }
        beMessenger_SendNamed((beMessenger *)self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_SELECT);
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
                    igSmartPointer<beNDMWStatusTitle00> title(beNDMWStatusTitle00_Create((int)WindowAllocator(self)));
                    beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
                }
                SetStep1(self, self->_st1 + 1);
                return;
            case 1:
                QueryModelSequence(self, i_stback, SQ_OPEN_5);
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) != 1) {
                    SwitchLayer(self, BG01, DISPOFF_2);
                    SwitchLayer(self, BG02, DISPOFF_2);
                    SwitchLayer(self, BG03, DISPOFF_2);
                    SwitchLayer(self, GM01, DISPOFF_2);
                    SwitchLayer(self, GM03, DISPOFF_2);
                    {
                        igSmartPointer<beNDMWStatusTitle01> title(beNDMWStatusTitle01_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
                    }
                    {
                        igSmartPointer<beNDMWStatusTitle02> title(beNDMWStatusTitle02_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
                    }
                    {
                        igSmartPointer<beNDMWStatusTitle03> title(beNDMWStatusTitle03_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
                    }
                    self->_statusMenu = 0;
                    SetStep1(self, self->_st1 + 1);
                    return;
                }
                break;
            case 2:
                QueryModelSequence(self, i_messwn, SQ_STOPEN);
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) != 1) {
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
                        igSmartPointer<beNDMWStatusSelect00> menu(beNDMWStatusSelect00_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)menu.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)menu.p);
                        menu.p->_startPoint = self->_statusMenu;
                        beNDMWWindow_QueueText((beNDMWWindow *)menu.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
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
                        igSmartPointer<beNDMWStatusCtrlEquip> equip(beNDMWStatusCtrlEquip_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)equip.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)equip.p);
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
                        igSmartPointer<beNDMWStatusCtrlFolder> folder(beNDMWStatusCtrlFolder_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)folder.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)folder.p);
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
                        igSmartPointer<beNDMWStatusCtrlSkill> skill(beNDMWStatusCtrlSkill_Create((int)WindowAllocator(self)));
                        beNDMWWindow_BindContext((beNDMWWindow *)skill.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)skill.p);
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
                    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_messwn, 0, ISRUN_5);
                    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) != 1) {
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
            beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
            beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
            beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
            SetStep0(self, self->_st0 + 1);
            return;
        }
    } else if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
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
            igSmartPointer<beNDMWStatusTitle04> title(beNDMWStatusTitle04_Create((int)WindowAllocator(self)));
            beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 30);
            ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
            break;
        }
        case 1: {
            igSmartPointer<beNDMWStatusTitle02> title(beNDMWStatusTitle02_Create((int)WindowAllocator(self)));
            beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 0);
            ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
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
                if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) return;
                {
                    igSmartPointer<beNDMWStatusSelect01> menu(beNDMWStatusSelect01_Create((int)WindowAllocator(self)));
                    beNDMWWindow_BindContext((beNDMWWindow *)menu.p, (igObject *)self, self->_insight, self->_playerNo, 31);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)menu.p);
                    menu.p->_startPoint = self->_equipMenu;
                    beNDMWWindow_QueueText((beNDMWWindow *)menu.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                }
                self->_nowProcKazu = CHILD_COUNT(self);
                SetStep2(self, self->_st2 + 1);
            }
            case 1:
                if (self->_retCode != -1)
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, self->_retCode + 35);
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
                        panel.p = (beNDMWStatusCtrlBaseEquip *)beNDMWStatusPowerSocket_Create((int)allocator);
                        panel.p->_kindListMax = 3;
                        break;
                    }
                    case 2: {
                        void *allocator = WindowAllocator(self);
                        { igObject *old = panel.p; RELEASE_OBJ(old) }
                        panel.p = (beNDMWStatusCtrlBaseEquip *)beNDMWStatusMainSlot_Create((int)allocator);
                        break;
                    }
                    case 3: {
                        void *allocator = WindowAllocator(self);
                        { igObject *old = panel.p; RELEASE_OBJ(old) }
                        panel.p = (beNDMWStatusCtrlBaseEquip *)beNDMWStatusSubSlot_Create((int)allocator);
                        break;
                    }
                    }
                    beNDMWWindow_BindContext((beNDMWWindow *)panel.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)panel.p);
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        SetStep0(self, self->_st0 + 1);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) self->_isRun = 0;
        break;
    }
}

void beNDMWStatusCtrlBaseEquip_Update(beNDMWStatusCtrlBaseEquip *p)
{
    switch (p->_st0) {
    default: return;
    case 0: {
        igObject *player;
        SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
        player = (igObject *)beMessenger_GetObject((beMessenger *)p->_messenger, 0);
        AssignReference(&p->_playerList, player);
        AssignReference(&p->_powerSocket, (igObject *)igProperty_GetRecordFolder((igObject *)p->_playerList, POWERSOCKET_3)->_data);
        AssignReference(&p->_mainSlot, (igObject *)igProperty_GetRecordFolder((igObject *)p->_playerList, MAINSLOT_3)->_data);
        AssignReference(&p->_subSlot, (igObject *)igProperty_GetRecordFolder((igObject *)p->_playerList, SUBSLOT_3)->_data);
        AssignReference(&p->_wpuPocket, (igObject *)igProperty_GetRecordFolder((igObject *)p->_playerList, POWERPOCKET_3)->_data);
        AssignReference(&p->_apuPocket, (igObject *)igProperty_GetRecordFolder((igObject *)p->_playerList, MAINPOCKET_3)->_data);
        AssignReference(&p->_deviceFolder, (igObject *)igProperty_GetRecordFolder((igObject *)p->_playerList, DEVICEFOLDER_3)->_data);
        switch (p->_st1) { case 0: AsEquipPanel(p)->PresentPanel(1); beNDMWStatusCtrlBaseEquip_QueuePanelText(p); break; default: beNDMWStatusCtrlBaseEquip_ShowKindCursor(p, -1); break; }
        {
            igSmartPointer<beNDMWStatusSelectE1> h(beNDMWStatusSelectE1_Create((int)WindowAllocator(p)));
            beNDMWWindow_BindContext((beNDMWWindow *)h.p, (igObject *)p, p->_insight, p->_playerNo, 0);
            ((Gap::Core::igObjectList *)p->_subWindow)->append((Gap::Core::igObject *)h.p);
            h.p->_selectMax = p->_kindListMax;
            { float *q = h.p->_offsetPos.vec; q[0] = -83.0f; q[1] = 148.0f; q[2] = 0.0f; }
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
                beNDMWWindow_RunMessageScript((beNDMWWindow *)p, txt_status_lua_2, 0x7F);
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
                igSmartPointer<beNDMWStatusSelectE1> hw(beNDMWStatusSelectE1_Create((int)WindowAllocator(p)));
                beNDMWWindow_BindContext((beNDMWWindow *)hw.p, (igObject *)p, p->_insight, p->_playerNo, 0);
                ((Gap::Core::igObjectList *)p->_subWindow)->append((Gap::Core::igObject *)hw.p);
                hw.p->_selectMax = p->_kindListMax;
                { float *q = hw.p->_offsetPos.vec; q[0] = -83.0f; q[1] = 148.0f; q[2] = 0.0f; }
                hw.p->_startPoint = p->_kindListPos;
                igSmartPointer<igBoolList> hl(igBoolList_Create((int)WindowAllocator(p)));
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
                    igObject::ref(((igObject *)list));
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
                            SendPowerSocketName(p);
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
                int al = (int)WindowAllocator(p);
                igSmartPointer<beNDMWShopSelect00> h((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)h.p, (igObject *)p, p->_insight, p->_playerNo, 0);
                ((Gap::Core::igObjectList *)p->_subWindow)->append((Gap::Core::igObject *)h.p);
                beNDMWWindow_RunMessageScript((beNDMWWindow *)p, txt_status_lua_2, 0x82);
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)p);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)p);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)p);
        SetStep0(p, p->_st0 + 1);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)p) != 0) { p->_isRun = 0; }
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
        beMessenger_SelectReceivers((beMessenger *)p->_messenger, GAMERAM_9, 0, 0); API(p->_playerNo); DSP(RECALCPLAYER_4);
        SEL(SUBWND_2); API(p->_playerNo); DSP(ONPREVIEW);
        SET_ITEM(p->_kindListPos, kindItem)
        SET_ITEM(p->_retCode, retItem)
        beMessenger_SelectReceivers((beMessenger *)p->_messenger, GAMERAM_9, 0, 0); API(p->_playerNo); DSP(RECALCPLAYER_4);
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
        beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0, ISRUN_5);
        if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
            beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0, sequences[kind]);
            return;
        }
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0);
        beMessenger_AppendString((beMessenger *)self->_messenger, sequences[kind]);
        position[2] = 0;
        position[0] = -83.0f;
        position[1] = 148.0f;
        beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)position);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, GENERATE_7);
        return;
    }
    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0, ISRUN_5);
    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
        beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
    }
}

/* Queues the panel's text cells: the description line, the kind-list rows and the pocket rows. */
void beNDMWStatusCtrlBaseEquip_QueuePanelText(beNDMWStatusCtrlBaseEquip *self) {
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_3, font100_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT10, g_statusFontNames[0], space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT10, g_statusFontNames[1], space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font000_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font001_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font002_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font100_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font101, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font102, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font103, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT11, font104, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_3, font100_2, space, LEFT_3);
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
                alloc = ((Gap::Core::igObject *)self)->getMemoryPool();
                alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                {
                igSmartPointer<igObject> names((igObject *)igStringRefList_Create((int)alloc));
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(TSUYOSA_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(KASHIKOSA_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(SEISHIN_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(SUBAYASA_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(RES_FIRE_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(RES_ICE_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(RES_THUNDER_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(RES_DARK_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(CHIMEIRITSU_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(HPDRAIN_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(MPDRAIN_2).ref());
                StringList_AppendRetained((igStringRefList *)(int)names.p, igStringRef(CHOHATURITSU_2).ref());
                rec = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                alloc = ((Gap::Core::igObject *)self)->getMemoryPool();
                alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                igSmartPointer<igIntList> tmp = (igIntList *)igIntList_Create((int)alloc);
                cat = -1;
                i = 0;
                if (0 < ((StrList *)names.p)->_count) {
                    do {
                        hit = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)newItem, (beNDMWStatus *)rec, StringList_CopyRetained((igStringRefList *)names.p, i).p) > 0;
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
                            hit = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)it, (beNDMWStatus *)rec, StringList_CopyRetained((igStringRefList *)names.p, cat).p) > 0;
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

/* Stores `item` in slot `index` of the list, retaining it, and releases the item the slot held. */
static inline void SetItemRetained(ItemList *list, int index, EquipItem *const &item)
{
    if (item != 0) item->_refCount = item->_refCount + 1;
    REL(list->_data[index])
    if (list->_count != 0 && index >= 0 && index < list->_count) list->_data[index] = item;
}

static inline igObjectList *SubWindows(const beNDMWStatusCtrlBaseEquip &window) { return (igObjectList *)window._subWindow; }

/* The object as a device-folder list window, or null for any other kind of window. */
static inline beNDMWStatusCtrlD0 *AsStatusCtrlD0(igObject *object)
{
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType(g_beNDMWStatusCtrlD0_metaObject) != 0) return (beNDMWStatusCtrlD0 *)object;
    return 0;
}

/* Previews the stats of a device row of the device folder: equips it into `slotList` (slot `slot`)
 * for the stat preview, then puts the slot list back as it was. Index -1 previews the slot empty. */
void beNDMWStatus_PreviewEquipment(beNDMWStatusCtrlBaseEquip *self, ItemList *slotList, int slot, int index) {
    if (index == -1) {
        MovedItemRef held(slotList->_data[slot]);
        SetItemRetained(slotList, slot, 0);
        RecalcPlayer(self);
        SendSubWindowCommand(self, ONPREVIEW);
        {
            EquipItem *saved = (EquipItem *)held.p;
            SetItemRetained(slotList, slot, saved);
        }
        RecalcPlayer(self);
    } else if (self->_retCode != -1) {
        beNDMWStatusCtrlD0 *folder = 0;
        int child;
        for (child = 0; child < SubWindows(*self)->_count; child++) {
            folder = AsStatusCtrlD0(((igObject **)SubWindows(*self)->_data)[child]);
            if (folder != 0) break;
        }
        if (folder->_st0 == 1 && folder->_st1 == 1) {
            int row = beNDMWStatusCtrlD0_GetSelectedIndex(folder);
            if (row != -1 && (row != self->_st3 || self->_st3 == 999)) {
                EquipItem *device;
                bool equippable;
                FindStatus(self->_insight);
                device = ((ItemList *)self->_deviceFolder)->_data[row];
                ItemListRef before(beNDMWItemBaseList_Create((int)WindowAllocator(self)));
                for (int i = 0; i < slotList->_count; i++) {
                    ((Gap::Core::igObjectList *)before.p)->append((Gap::Core::igObject *)slotList->_data[i]);
                }
                equippable = false;
                /* matching construct: tvpe variant search — the index conversion keeps the flag list first in the addu */
                if (((bool *)((igBoolList *)folder->_decideList)->_data)[(unsigned int)folder->_retCode]) {
                    if (device->_kind == 3) {
                        equippable = true;
                    } else if (AsEquipPanel(self)->CanEquip(row) != 0) {
                        equippable = true;
                    }
                }
                if (equippable) {
                    beNDMWStatus_AssignEquipment((StatusPanel *)self, slotList, slot, row);
                    RecalcPlayer(self);
                    SendSubWindowCommand(self, ONPREVIEW);
                    for (int i = 0; i < slotList->_count; i++) {
                        if (slotList->_data[i] != 0) slotList->_data[i]->_equipped = 0;
                        SetItemRetained(slotList, i, 0);
                    }
                    for (int i = 0; i < ((ItemList *)before.p)->_count; i++) {
                        EquipItem *item = ((ItemList *)before.p)->_data[i];
                        if (item != 0) item->_equipped = 1;
                        SetItemRetained(slotList, i, item);
                    }
                    RecalcPlayer(self);
                } else {
                    SendSubWindowCommand(self, OFPREVIEW);
                }
                self->_st3 = row;
            }
        }
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
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stsoubi, 0, SQ_POWEROPEN, SQ_CLOSE_3);
        int lines = -1;
        igObjectList *kinds = (igObjectList *)self->_powerSocket;
        if (kinds->_count > 0) {
            beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)kinds->_data)[0];
            if (kind != 0 && kind->_pocket > -1) lines = kind->_pocket;
        }
        {
            igStringRef sequence;
            switch (lines) {
            case 0:
            default: sequence = SQ_0LINEOPEN; break;
            case 1: sequence = SQ_1LINEOPEN; break;
            case 2: sequence = SQ_2LINEOPEN; break;
            case 3: sequence = SQ_3LINEOPEN; break;
            case 4: sequence = SQ_4LINEOPEN_2; break;
            case 5: sequence = SQ_5LINEOPEN; break;
            }
            beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stpocket, 0, sequence.p, SQ_CLOSE_3);
        }

    } else {
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        l = (igDataList *)self->_modelCloseInfoNameList;
        n = l->_count;
        for (i = 0; i < n; i++) {
            slot = &((int **)l->_data)[i];
            if (g_stringPool == 0) {
                pool = StringPool_Allocate(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct((StringPool *)pool);
                }
                g_stringPool = (StringPool *)pool;
            }
            nw = (int *)StringPool_Intern(g_stringPool, (const char *)0);
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
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
            if (g_stringPool == 0) {
                pool2 = StringPool_Allocate(0x10);
                if (pool2 != 0) {
                    pool2 = StringPool_Construct((StringPool *)pool2);
                }
                g_stringPool = (StringPool *)pool2;
            }
            nw2 = (int *)StringPool_Intern(g_stringPool, (const char *)0);
            old2 = *slot2;
            if (old2 != 0) {
                a12 = old2 - 2;
                v12 = old2[-1] - 1;
                old2[-1] = v12;
                if (v12 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*a12, (StringTokenHeader *)a12);
                }
            }
            *slot2 = nw2;
        }
        l2->_count = 0;
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
    }
}

void beNDMWStatusPowerSocket_RefreshSlotList(beNDMWStatusPowerSocket *self) {
    igVec3f b, a;
    int status = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x88);
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x26);
    int i = 0;
    if (0 < (*(igObjectList **)&self->_powerSocket)->_count) {
        int item;
        const char *name;
        int off;
        char **row;
        off = 0;
        row = g_statusFontNames;
        do {
            item = *(int *)(((igObjectList *)self->_powerSocket)->_data + off);
            if (item == 0) {
                name = DISPOFF_2;
            } else {
                int itemName;
                name = DISPON_2;
                itemName = (int)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)status, NAME_3);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, *row);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)itemName);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                beNDMWItemBase_GetRevisionColor(&b, (beNDMWItemBase *)item);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, *row);
                a = b;
                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&a);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, COLOR);
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
            beMessenger_AppendString((beMessenger *)self->_messenger, *row);
            beMessenger_AppendString((beMessenger *)self->_messenger, name);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            i++;
            off += 4;
            row++;
        } while (i < ((igObjectList *)self->_powerSocket)->_count);
    }
    AsEquipPanel((beNDMWStatusCtrlBaseEquip *)self)->RefreshPocket();
    if (self->_st1 == 3) {
        AsEquipPanel((beNDMWStatusCtrlBaseEquip *)self)->ShowSlotDescription();
    }
}

/* Retained share of the system's global string object. */

void beNDMWStatusPowerSocket_ShowSlotDescription(beNDMWStatusPowerSocket *a) {
    int *text;
    int *onOff;
    int slot;
    int item;
    const char *recordString;
    char digit[2];
    igStringObj *t2;
    igStringObj *t3;
    beNDMWItemBaseList *items;

    item = 0;
    slot = a->_retCode;
    if (slot != -1) {
        items = (beNDMWItemBaseList *)a->_powerSocket;
        item = *(int *)(items->_data + (slot * 4));
    }
    if (item != 0) {
        recordString = (const char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)a->_insight, g_beNDMWStatus_metaObject), TXT_2);
        digit[1] = 0;
        digit[0] = ((beNDMWItemRevisionPocketBase *)item)->_pocket + 0x30;
        {
        igSmartPointer<igStringObj> description((igStringObj *)(((beSystem *)igInsightCore_FindManager((igInsightCore *)a->_insight, g_beSystem_metaObject))->_globalStrObj), kRetainReference);
        igStringObj_Set(description.p, recordString);
        t2 = (igStringObj *)description.p;
        int length = t2->_length;
        igStringObj_Insert(t2, digit, length, strlen(digit));
        t3 = (igStringObj *)description.p;
        text = (int *)t3->_buffer;
        text = (text == 0) ? ((int *)g_stringObjEmptyText) : text;
        }
        beMessenger_SelectGroup((beMessenger *)a->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)a->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)a->_messenger, font000_2);
        beMessenger_AppendString((beMessenger *)a->_messenger, (const char *)text);
        beMessenger_DispatchSelected((beMessenger *)a->_messenger, TEXTSET_3);
        onOff = (int *)(DISPON_2);
    } else {
        onOff = (int *)(DISPOFF_2);
    }
    beMessenger_SelectGroup((beMessenger *)a->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)a->_messenger, STWINFONT29_3);
    beMessenger_AppendString((beMessenger *)a->_messenger, font000_2);
    beMessenger_AppendString((beMessenger *)a->_messenger, (const char *)onOff);
    beMessenger_DispatchSelected((beMessenger *)a->_messenger, SWITCH_4);
}

void beNDMWStatusPowerSocket_OpenSlotList(beNDMWStatusPowerSocket *self) {
    switch (self->_retCode) {
    case 0:
        self->_st1 = 1;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    case 1:
    case 2:
        self->_st1 = 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st3 = 1;
        break;
    }
}

void beNDMWStatusPowerSocket_RefreshPocket(beNDMWStatusPowerSocket *self) {
    int lines = -1;
    igObjectList *kinds = (igObjectList *)self->_powerSocket;
    if (kinds->_count > 0) {
        beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)kinds->_data)[0];
        if (kind != 0 && kind->_pocket > -1) lines = kind->_pocket;
    }
    {
        igStringRef sequence;
        switch (lines) {
        case 0:
        default: sequence = SQ_0LINEOPEN; break;
        case 1: sequence = SQ_1LINEOPEN; break;
        case 2: sequence = SQ_2LINEOPEN; break;
        case 3: sequence = SQ_3LINEOPEN; break;
        case 4: sequence = SQ_4LINEOPEN_2; break;
        case 5: sequence = SQ_5LINEOPEN; break;
        }
        beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stpocket, 0, sequence.p);
    }
    int i = 0;
    /* matching construct: the loop guard reads the pocket list through a const view, so the body reloads it as retail
     * does; a plain guard, a for loop over the field or a const count() accessor leave the function 8 bytes short */
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
                const char *name = ((const char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)((void *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject)), NAME_3));
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, font);
                beMessenger_AppendString((beMessenger *)self->_messenger, name);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
            beMessenger_AppendString((beMessenger *)self->_messenger, font);
            beMessenger_AppendString((beMessenger *)self->_messenger, show);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            i++;
        } while (i < ((igObjectList *)self->_wpuPocket)->_count);
    }
}

void beNDMWStatusPowerSocket_OpenSlotMenu(beNDMWStatusPowerSocket *self) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl0;
    bool fl;
    int i;
    char **p;
    const char *s3;
    igIntList *t;

    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    switch (((beNDMWWindow *)self->_mother)->_entCode) {
    case 0:
        win.p->_entCode = 124;
        win.p->_selectMax = 2;
        break;
    case 1:
        win.p->_entCode = 46;
        win.p->_selectMax = 3;
        break;
    }
    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<igBoolList> flags(igBoolList_Create((int)a));
    BoolList_Append(flags.p, true);
    t = (igIntList *)self->_powerSocket;
    fl0 = false;
    fl = false;
    if (t->_count > 0) {
        if (self->_st3 == 0) {
            beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)t->_data)[0];
            if (kind != 0 && kind->_pocket > 0) fl0 = true;
        }
        if (((int *)t->_data)[self->_kindListPos] != 0 && self->_kindListPos != 0) fl = true;
    }
    BoolList_Append(flags.p, fl0);
    if (((beNDMWWindow *)self->_mother)->_entCode == 1) BoolList_Append(flags.p, fl);
    /* matching construct: the decide list goes into the window's reference written out, the list read through a const
     * view of the holder before the window is fetched; through igSmartPointer::operator= or an inline setter the window
     * and the list exchange registers */
    { const igSmartPointer<igBoolList> &view = flags; l0 = view.p; }
    w = win.p;
    igObject::ref(l0);
    REL(w->_decideList)
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
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
            beMessenger_AppendString((beMessenger *)self->_messenger, *p);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}


void beNDMWStatusPowerSocket_OnSlotMenuDecided(beNDMWStatusPowerSocket *self) {
    int entry;

    entry = self->_retCode;
    switch (entry) {
    case 0: {
        /* matching construct: cast from the 4-byte _mother reference to its window type */
        beNDMWWindow *mother = (beNDMWWindow *)self->_mother;
        switch (mother->_entCode) {
        case 0:
            self->_st1 = 3;
            self->_st3 = 0;
            self->_st2 = 0;
            break;
        default:
            self->_st1 = 4;
            self->_st3 = 0;
            self->_st2 = 0;
            break;
        }
        break;
    }
    case 1:
        self->_st1 = 2;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    case 2:
        self->_retCode = -1;
        AsEquipPanel(self)->EquipSelected();
        self->_retCode = self->_kindListPos;
        AsEquipPanel(self)->RefreshSlotList();
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, GAMERAM_9, 0, 0);
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, RECALCPLAYER_4);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, SUBWND_2);
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, UPDATE);
        self->_st0 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 1;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    }
}


void beNDMWStatusPowerSocket_OpenDeviceFolder(beNDMWStatusPowerSocket *self) {
    int alloc;
    int a;
    int s1;
    igIntList *s0;
    alloc = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    }
    igSmartPointer<beNDMWStatusCtrlD0> win(beNDMWStatusCtrlD0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseNameList, igStringRef(font100_2).ref());
    beNDMWWindow_RunMessageScript((beNDMWWindow *)win.p, txt_status_lua_2, 0x8B);
    s0 = (igIntList *)win.p->_kindList;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
        s0->_count = ListCount(s0) + 1;
    } else {
        ((Gap::Core::igDataList *)s0)->resizeAndSetCount(s1 + 1, 4);
    }
    static const int kindFilter[1] = {0};
    ((int *)s0->_data)[s1] = kindFilter[0];
    win.p->_isEquipDisable = 1;
    win.p->_isUnknownDisable = 1;
    win.p->_isAutoClose = 0;
}


int beNDMWStatusPowerSocket_CanEquip(beNDMWStatusPowerSocket *self, int index) {
    int s0b;
    int s0;
    int fl;
    PropertyRecordTable *s1;
    int s3;
    int v0;
    int s2;

    s3 = ((int *)((beNDMWItemBaseList *)self->_deviceFolder)->_data)[index];
    s0 = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
    s2 = igProperty_GetRecord((igObject *)self->_playerList, DIGIMONNO_3)->_data;
    fl = (1 << s2) & beNDMWItemBase_GetRecordInt((beNDMWItemBase *)s3, (beNDMWStatus *)s0, SOUBI_2);
    s1 = (PropertyRecordTable *)igProperty_GetRecordIntList((igObject *)self->_playerList, SKILL_2)->_data;
    s0b = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)s3, (beNDMWStatus *)s0, SKILL_2);
    v0 = beNDMWItemBase_GetRecordInt((beNDMWItemBase *)s3, (beNDMWStatus *)s0, SKILLPOINT_2);
    if ((fl != 0) && (s1->data[s0b] >= v0)) {
        return 1;
    }
    return 0;
}

void beNDMWStatusPowerSocket_EquipSelected(beNDMWStatusPowerSocket *self) {
    beNDMWStatus_AssignEquipment((StatusPanel *)self, (ItemList *)self->_powerSocket, self->_kindListPos, self->_retCode);
    if (self->_kindListPos == 0) {
        AsEquipPanel(self)->ClearPocket();
    }
    ((beNDMWWindow *)((beNDMWWindow *)self->_mother)->_mother)->_retCode = 0x64;
}

/* Runs the shared helper beNDMWStatus_PreviewEquipment (the DEVICE row selection step; -1 is its "no row" case)
 * over the power socket's WPU pocket list at the current pocket position, passing the first
 * argument through as the row index. The MainSlot sibling does the same with its APU pocket. The
 * other two arguments are unused. */
void beNDMWStatusPowerSocket_PreviewPocketDevice(beNDMWStatusPowerSocket *self, char *index, char *unusedArg2, int unusedArg3)
{
    beNDMWStatus_PreviewEquipment((beNDMWStatusCtrlBaseEquip *)self, (ItemList *)self->_wpuPocket, self->_pocketPos, (int)index);
}

void beNDMWStatusPowerSocket_PreviewSlotDevice(beNDMWStatusPowerSocket *self, int index) {
    if (index != -1) {
        beNDMWStatus_PreviewEquipment((beNDMWStatusCtrlBaseEquip *)self, (ItemList *)self->_powerSocket, 0, index);
    }
}

void beNDMWStatusPowerSocket_OpenPocketList(beNDMWStatusPowerSocket *self) {
    int alloc;
    int pocketCount;
    alloc = (int)((Gap::Core::igObject *)self)->getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        alloc = (int)alloc;
    } else {
        alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)alloc));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseNameList, igStringRef(font100_2).ref());
    beNDMWWindow_RunMessageScript((beNDMWWindow *)win.p, txt_status_lua_2, 0x8A);
    pocketCount = 1;
    if (((igObjectList *)self->_powerSocket)->_count > 0) {
        beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)((igObjectList *)self->_powerSocket)->_data)[self->_kindListPos];
        if (kind != 0) pocketCount = kind->_pocket;
    }
    win.p->_selectMax = pocketCount;
    {
        beNDMWStatusSelectE1 *list = win.p;
        list->_offsetPos[0] = -83.0f;
        list->_offsetPos[1] = 55.0f;
        list->_offsetPos[2] = 0.0f;
    }
    win.p->_startPoint = self->_pocketPos;
}

void beNDMWStatusPowerSocket_ShowPocketDescription(beNDMWStatusPowerSocket *self) {
    const char *onOff;
    beNDMWItemBase *item = 0;
    if (self->_retCode != -1) item = ItemAt(self->_wpuPocket, self->_retCode);
    if (item != 0) {
        SetCellText(self, STWINFONT29_3, font000_2, (const char *)beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)FindStatus(self->_insight), TXT_2));
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
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(n + 1, 1);
    }
    ((unsigned char *)l->_data)[n] = value;
}

static inline void setDecideList(const igSmartPointer<beNDMWStatusSelectE0> &win, const igSmartPointer<igBoolList> &list) {
    igBoolList *l0 = list.p;
    beNDMWStatusSelectE0 *w = win.p;
    igObject::ref(l0);
    REL((igObject *)w->_decideList)
    w->_decideList = (int)l0;
}

void beNDMWStatusPowerSocket_OpenPocketMenu(beNDMWStatusPowerSocket *self) {
    int a;

    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)((unsigned int)self->_subWindow))->append((Gap::Core::igObject *)win.p);
    win.p->_selectMax = 2;
    beNDMWWindow_QueueText((beNDMWWindow *)win.p, STWINFONT29_3, font000_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)win.p, STWINFONT29_3, font001_2, space, LEFT_3);
    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<igBoolList> decide(igBoolList_Create((int)a));
    setDecideList(win, decide);
    append(decide, true);
    if (((int *)((beNDMWItemBaseList *)self->_wpuPocket)->_data)[self->_pocketPos] != 0) {
        append(decide, true);
    } else {
        append(decide, false);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)self->_messenger, font001_2);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, CANCELCOLOR_2);
    }
}


void beNDMWStatusPowerSocket_OpenPocketFolder(beNDMWStatusPowerSocket *self) {
    int alloc;
    int a;
    int s1;
    igDataList *s0;
    alloc = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    }
    igSmartPointer<beNDMWStatusCtrlD0> child((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)child.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)child.p);
    s0 = (igDataList *)child.p->_kindList;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
                s0->_count = ListCount(s0) + 1;
    } else {
        ((Gap::Core::igDataList *)s0)->resizeAndSetCount(s1 + 1, 4);
    }
    static const int kindFilter[1] = {3};
    ((int *)s0->_data)[s1] = kindFilter[0];
    child.p->_isAbType = 0;
    child.p->_isEquipDisable = 1;
    child.p->_isUnknownDisable = 1;
}

/* Equipment assignment for the power socket's WPU pocket list: the shared helper
 * beNDMWStatus_AssignEquipment gets the pocket list, the pocket position and the device-folder
 * index chosen in _retCode. The MainSlot sibling does the same with its APU pocket. The three
 * arguments are unused. */
void beNDMWStatusPowerSocket_EquipPocket(beNDMWStatusPowerSocket *self, char *unusedArg1, char *unusedArg2, char *unusedArg3)
{
    beNDMWStatus_AssignEquipment((StatusPanel *)self, (ItemList *)self->_wpuPocket, self->_pocketPos, self->_retCode);
}

void beNDMWStatusPowerSocket_ClearPocket(beNDMWStatusPowerSocket *self) {
    int i;
    beNDMWItemBase *item;
    i = 0;
    if (0 < ((beNDMWItemBaseList *)(*(int *)&self->_wpuPocket))->_count) {
        do {
            item = ((beNDMWItemBase **)((beNDMWItemBaseList *)(self->_wpuPocket))->_data)[i];
            if (item != 0) {
                item->_isEquip = 0;
            }
            i += 1;
        } while (i < ((beNDMWItemBaseList *)(self->_wpuPocket))->_count);
    }
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(void *)(self->_wpuPocket)))->setAll(0);
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
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stsoubi, 0, SQ_MAINOPEN, SQ_CLOSE_3);
        int lines = -1;
        igObjectList *kinds = (igObjectList *)self->_mainSlot;
        if (kinds->_count > 0) {
            beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)kinds->_data)[0];
            if (kind != 0 && kind->_pocket > -1) lines = kind->_pocket;
        }
        {
            igStringRef sequence;
            switch (lines) {
            case 0:
            default: sequence = SQ_0LINEOPEN; break;
            case 1: sequence = SQ_1LINEOPEN; break;
            case 2: sequence = SQ_2LINEOPEN; break;
            case 3: sequence = SQ_3LINEOPEN; break;
            case 4: sequence = SQ_4LINEOPEN_2; break;
            case 5: sequence = SQ_5LINEOPEN; break;
            }
            beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stpocket, 0, sequence.p, SQ_CLOSE_3);
        }

    } else {
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        l = (igDataList *)self->_modelCloseInfoNameList;
        n = l->_count;
        for (i = 0; i < n; i++) {
            slot = &((int **)l->_data)[i];
            if (g_stringPool == 0) {
                pool = StringPool_Allocate(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct((StringPool *)pool);
                }
                g_stringPool = (StringPool *)pool;
            }
            nw = (int *)StringPool_Intern(g_stringPool, (const char *)0);
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v1 = old[-1] - 1;
                old[-1] = v1;
                if (v1 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
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
            if (g_stringPool == 0) {
                pool2 = StringPool_Allocate(0x10);
                if (pool2 != 0) {
                    pool2 = StringPool_Construct((StringPool *)pool2);
                }
                g_stringPool = (StringPool *)pool2;
            }
            nw2 = (int *)StringPool_Intern(g_stringPool, (const char *)0);
            old2 = *slot2;
            if (old2 != 0) {
                a12 = old2 - 2;
                v12 = old2[-1] - 1;
                old2[-1] = v12;
                if (v12 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*a12, (StringTokenHeader *)a12);
                }
            }
            *slot2 = nw2;
        }
        l2->_count = 0;
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
    }
}

void beNDMWStatusMainSlot_RefreshSlotList(beNDMWStatusMainSlot *self) {
    igVec3f b, a;
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x89);
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x28);
    int i = 0;
    if (0 < (*(igObjectList **)&self->_mainSlot)->_count) {
        int item;
        const char *name;
        int off;
        char **row;
        off = 0;
        row = g_statusFontNames;
        do {
            item = *(int *)(((igObjectList *)self->_mainSlot)->_data + off);
            if (item == 0) {
                name = DISPOFF_2;
            } else {
                int rs;
                name = DISPON_2;
                rs = (int)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject), NAME_3);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, *row);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)rs);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                beNDMWItemBase_GetRevisionColor(&b, (beNDMWItemBase *)item);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, *row);
                a = b;
                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&a);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, COLOR);
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
            beMessenger_AppendString((beMessenger *)self->_messenger, *row);
            beMessenger_AppendString((beMessenger *)self->_messenger, name);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            i++;
            off += 4;
            row++;
        } while (i < ((igObjectList *)self->_mainSlot)->_count);
    }
    AsEquipPanel(self)->RefreshPocket();
}

void beNDMWStatusMainSlot_ShowSlotDescription(beNDMWStatusMainSlot *a) {
    beNDMWItemRevisionPocketBase *item = 0;
    const char *recordString;
    char buf[2];
    igStringObj *p;
    igStringObj *q;
    char *str;
    const char *var;
    if (a->_retCode != -1) {
        item = ((beNDMWItemRevisionPocketBase **)((igObjectList *)a->_mainSlot)->_data)[a->_retCode];
    }
    if (item != 0) {
        recordString = (const char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)a->_insight, g_beNDMWStatus_metaObject), TXT_2);
        buf[1] = 0;
        buf[0] = item->_pocket + 0x30;
        {
        igSmartPointer<igStringObj> description((igStringObj *)(((beSystem *)igInsightCore_FindManager((igInsightCore *)a->_insight, g_beSystem_metaObject))->_globalStrObj), kRetainReference);
        igStringObj_Set(description.p, recordString);
        /* matching construct: the held pointer is read through a cast, as the power socket's description reads it;
         * read plainly, the length takes another register */
        q = (igStringObj *)description.p;
        int length = q->_length;
        igStringObj_Insert(q, buf, length, strlen(buf));
        p = description.p;
        str = (p->_buffer == 0) ? g_stringObjEmptyText : (char *)p->_buffer;
        }
        beMessenger_SelectGroup((beMessenger *)a->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)a->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)a->_messenger, font000_2);
        beMessenger_AppendString((beMessenger *)a->_messenger, str);
        beMessenger_DispatchSelected((beMessenger *)a->_messenger, TEXTSET_3);
        var = DISPON_2;
    } else {
        var = DISPOFF_2;
    }
    beMessenger_SelectGroup((beMessenger *)a->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)a->_messenger, STWINFONT29_3);
    beMessenger_AppendString((beMessenger *)a->_messenger, font000_2);
    beMessenger_AppendString((beMessenger *)a->_messenger, var);
    beMessenger_DispatchSelected((beMessenger *)a->_messenger, SWITCH_4);
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
        beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)kinds->_data)[0];
        if (kind != 0 && kind->_pocket > -1) lines = kind->_pocket;
    }
    {
        igStringRef sequence;
        switch (lines) {
        case 0:
        default: sequence = SQ_0LINEOPEN; break;
        case 1: sequence = SQ_1LINEOPEN; break;
        case 2: sequence = SQ_2LINEOPEN; break;
        case 3: sequence = SQ_3LINEOPEN; break;
        case 4: sequence = SQ_4LINEOPEN_2; break;
        case 5: sequence = SQ_5LINEOPEN; break;
        }
        beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stpocket, 0, sequence.p);
    }
    int i = 0;
    /* matching construct: the loop guard reads the pocket list through a const view, so the body reloads it as retail
     * does; a plain guard, a for loop over the field or a const count() accessor leave the function 8 bytes short */
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
                const char *name = ((const char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)((void *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject)), NAME_3));
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, font);
                beMessenger_AppendString((beMessenger *)self->_messenger, name);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
            beMessenger_AppendString((beMessenger *)self->_messenger, font);
            beMessenger_AppendString((beMessenger *)self->_messenger, show);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            i++;
        } while (i < ((igObjectList *)self->_apuPocket)->_count);
    }
}

void beNDMWStatusMainSlot_OpenSlotMenu(beNDMWStatusMainSlot *self) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl0;
    bool fl;
    int i;
    char **p;
    const char *s3;
    igIntList *t;

    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    win.p->_selectMax = 3;
    win.p->_entCode = 0x78;
    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<igBoolList> flags(igBoolList_Create((int)a));
    BoolList_Append(flags.p, true);
    t = (igIntList *)self->_mainSlot;
    fl0 = false;
    fl = false;
    if (t->_count > 0) {
        if (self->_st3 == 0) {
            beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)t->_data)[0];
            if (kind != 0 && kind->_pocket > 0) fl0 = true;
        }
        if (((int *)t->_data)[self->_kindListPos] != 0) fl = true;
    }
    BoolList_Append(flags.p, fl0);
    BoolList_Append(flags.p, fl);
    /* matching construct: the decide list goes into the window's reference written out, the list read through a const
     * view of the holder before the window is fetched; through igSmartPointer::operator= or an inline setter the window
     * and the list exchange registers */
    { const igSmartPointer<igBoolList> &view = flags; l0 = view.p; }
    w = win.p;
    igObject::ref(l0);
    REL(w->_decideList)
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
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
            beMessenger_AppendString((beMessenger *)self->_messenger, *p);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}

void beNDMWStatusMainSlot_OnSlotMenuDecided(beNDMWStatusMainSlot *self) {
    int entry;

    entry = self->_retCode;
    switch (entry) {
    case 0:
        self->_st1 = 4;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    case 1:
        self->_st1 = 2;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    case 2:
        self->_retCode = -1;
        AsEquipPanel(self)->EquipSelected();
        self->_retCode = self->_kindListPos;
        AsEquipPanel(self)->RefreshSlotList();
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, GAMERAM_9, 0, 0);
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, RECALCPLAYER_4);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, SUBWND_2);
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, UPDATE);
        self->_st0 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 1;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    }
}

void beNDMWStatusMainSlot_OpenDeviceFolder(beNDMWStatusMainSlot *self) {
    int al;
    int c;
    igDataList *l;

    al = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusCtrlD0> win(beNDMWStatusCtrlD0_Create(al));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseNameList, igStringRef(font100_2).ref());
    beNDMWWindow_RunMessageScript((beNDMWWindow *)win.p, txt_status_lua_2, 139);
    l = (igDataList *)win.p->_kindList;
    c = l->_count;
    if (c < l->_capacity) {
        l->_count = ListCount(l) + 1;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(c + 1, 4);
    }
    static const int kindFilter[1] = {1};
    ((int *)l->_data)[c] = kindFilter[0];
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
    status = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
    player_level = igProperty_GetRecord((igObject *)self->_playerList, LEVEL_3)->_data;
    return player_level >= beNDMWItemBase_GetRecordInt((beNDMWItemBase *)item, (beNDMWStatus *)status, LVPOINT);
}

void beNDMWStatusMainSlot_EquipSelected(beNDMWStatusMainSlot *self) {
    beNDMWStatus_AssignEquipment((StatusPanel *)self, (ItemList *)self->_mainSlot, self->_kindListPos, self->_retCode);
    if (self->_kindListPos == 0) {
        AsEquipPanel(self)->ClearPocket();
    }
}

/* Only the first argument is used. */
void beNDMWStatusMainSlot_PreviewPocketDevice(beNDMWStatusMainSlot * self, char * extra, char * unusedA, int unusedB)
{
    beNDMWStatus_PreviewEquipment((beNDMWStatusCtrlBaseEquip *)self, (ItemList *)self->_apuPocket, self->_pocketPos, (int)extra);
}

static inline ItemList *ApuPocket(const beNDMWStatusMainSlot &slot) { return (ItemList *)slot._apuPocket; }

/* Previews a device row for the main slot. Index -1 previews the slot empty, with the APU pocket's
 * devices put aside for the preview and put back afterwards. */
void beNDMWStatusMainSlot_PreviewSlotDevice(beNDMWStatusMainSlot *self, int index) {
    if (index == -1) {
        ItemListRef pocketDevices(beNDMWItemBaseList_Create((int)WindowAllocator(self)));
        for (int i = 0; i < ApuPocket(*self)->_count; i++) {
            ((Gap::Core::igObjectList *)pocketDevices.p)->append((Gap::Core::igObject *)ApuPocket(*self)->_data[i]);
        }
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(ItemList *)self->_apuPocket))->setAll(0);
        beNDMWStatus_PreviewEquipment((beNDMWStatusCtrlBaseEquip *)self, (ItemList *)self->_mainSlot, self->_kindListPos, index);
        for (int i = 0; i < ((ItemList *)pocketDevices.p)->_count; i++) {
            EquipItem *device = ((ItemList *)pocketDevices.p)->_data[i];
            SetItemRetained((ItemList *)self->_apuPocket, i, device);
        }
        ObjectList_RemoveAll((igObjectList *)pocketDevices.p);
    } else {
        beNDMWStatus_PreviewEquipment((beNDMWStatusCtrlBaseEquip *)self, (ItemList *)self->_mainSlot, self->_kindListPos, index);
    }
}

void beNDMWStatusMainSlot_OpenPocketList(beNDMWStatusMainSlot *self) {
    void *alloc;
    int pocketCount;
    alloc = ((Gap::Core::igObject *)self)->getMemoryPool();
    alloc = g_useOwnerAllocator ? alloc : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    igSmartPointer<beNDMWStatusSelectE1> win(((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)alloc)));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    { beNDMWStatusSelectE1 *window = win.p; ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)window); }
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseNameList, igStringRef(font100_2).ref());
    beNDMWWindow_RunMessageScript((beNDMWWindow *)win.p, txt_status_lua_2, 0x8A);
    pocketCount = 1;
    igObjectList *kinds = (igObjectList *)self->_mainSlot;
    if (kinds->_count > 0) {
        beNDMWItemRevisionPocketBase *kind = ((beNDMWItemRevisionPocketBase **)kinds->_data)[self->_kindListPos];
        if (kind != 0) pocketCount = kind->_pocket;
    }
    win.p->_selectMax = pocketCount;
    { beNDMWStatusSelectE1 *window = win.p;
    window->_offsetPos[0] = -83.0f;
    window->_offsetPos[1] = 55.0f;
    window->_offsetPos[2] = 0.0f; }
    win.p->_startPoint = self->_pocketPos;
}

void beNDMWStatusMainSlot_ShowPocketDescription(beNDMWStatusMainSlot *self) {
    int *text;
    const char *onOff;
    int index;
    int item;

    item = 0;
    index = self->_retCode;
    if (index != -1) {
        item = ((int *)((beNDMWItemBaseList *)self->_apuPocket)->_data)[index];
    }
    if (item != 0) {
        text = ((int *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject), TXT_2));
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)self->_messenger, font000_2);
        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)text);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
        onOff = DISPON_2;
    } else {
        onOff = DISPOFF_2;
    }
    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
    beMessenger_AppendString((beMessenger *)self->_messenger, font000_2);
    beMessenger_AppendString((beMessenger *)self->_messenger, onOff);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
}

void beNDMWStatusMainSlot_OpenPocketMenu(beNDMWStatusMainSlot *self) {
    int a;

    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)((unsigned int)self->_subWindow))->append((Gap::Core::igObject *)win.p);
    win.p->_selectMax = 2;
    beNDMWWindow_QueueText((beNDMWWindow *)win.p, STWINFONT29_3, font000_2, space, LEFT_3);
    beNDMWWindow_QueueText((beNDMWWindow *)win.p, STWINFONT29_3, font001_2, space, LEFT_3);
    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<igBoolList> decide(igBoolList_Create((int)a));
    setDecideList(win, decide);
    append(decide, true);
    if (((int *)((beNDMWItemBaseList *)self->_apuPocket)->_data)[self->_pocketPos] != 0) {
        append(decide, true);
    } else {
        append(decide, false);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)self->_messenger, font001_2);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, CANCELCOLOR_2);
    }
}

/* BeNDMWStatusMainSlot vfunc 36: creates the D0 status sub-window (held across its binding, the
 * sub-window append and the kind-list push) and marks it as the ability-type variant with
 * equipment and unknown entries disabled. */



void beNDMWStatusMainSlot_OpenPocketFolder(beNDMWStatusMainSlot *self) {
    int al;
    int c;
    igIntList *l;
    beNDMWStatusCtrlD0 *w;

    al = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusCtrlD0> window(beNDMWStatusCtrlD0_Create(al));
    beNDMWWindow_BindContext((beNDMWWindow *)window.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)window.p);
    w = window.p;
    l = (igIntList *)w->_kindList;
    c = l->_count;
    if (c < l->_capacity) {
        l->_count = ListCount(l) + 1;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(c + 1, 4);
    }
    static const int kindFilter[1] = {3};
    ((int *)l->_data)[c] = kindFilter[0];
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

void beNDMWStatusMainSlot_ClearPocket(beNDMWStatusMainSlot *self) {
    int i;
    beNDMWItemBase *e;
    i = 0;
    if (0 < ((beNDMWItemBaseList *)(*(int *)&self->_apuPocket))->_count) {
        do {
            e = ((beNDMWItemBase **)((beNDMWItemBaseList *)(self->_apuPocket))->_data)[i];
            if (e != 0) {
                e->_isEquip = 0;
            }
            i += 1;
        } while (i < ((beNDMWItemBaseList *)(self->_apuPocket))->_count);
    }
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(void *)(self->_apuPocket)))->setAll(0);
}

void beNDMWStatusSubSlot_PresentPanel(beNDMWStatusSubSlot *w, int open)
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

    if (open != 0) {
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)w, i_stsoubi, 0, SQ_SUBOPEN, SQ_CLOSE_3);
        return;
    }
    beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)w);
    l = (igDataList *)w->_modelCloseInfoNameList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        nw = (int *)StringPool_Intern(g_stringPool, 0);
        old = *slot;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
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
        if (g_stringPool == 0) {
            pool2 = ((int)StringPool_Allocate(0x10));
            if (pool2 != 0) {
                pool2 = ((int)StringPool_Construct((StringPool *)pool2));
            }
            g_stringPool = (StringPool *)pool2;
        }
        nw2 = (int *)StringPool_Intern(g_stringPool, 0);
        old2 = *slot2;
        if (old2 != 0) {
            a12 = old2 - 2;
            v12 = old2[-1] - 1;
            old2[-1] = v12;
            if (v12 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*a12, (StringTokenHeader *)a12);
            }
        }
        *slot2 = nw2;
    }
    l2->_count = 0;
    beNDMWWindow_ClearQueuedText((beNDMWWindow *)w);
}

void beNDMWStatusSubSlot_RefreshSlotList(beNDMWStatusSubSlot *self) {
    igVec3f b, a;
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x89);
    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x2A);
    int i = 0;
    if (0 < (*(igObjectList **)&self->_subSlot)->_count) {
        int item;
        const char *name;
        int off;
        char **row;
        off = 0;
        row = g_statusFontNames;
        do {
            item = *(int *)(((igObjectList *)self->_subSlot)->_data + off);
            if (item == 0) {
                name = DISPOFF_2;
            } else {
                int itemName;
                name = DISPON_2;
                itemName = (int)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject), NAME_3);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, *row);
                beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)itemName);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                beNDMWItemBase_GetRevisionColor(&b, (beNDMWItemBase *)item);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
                beMessenger_AppendString((beMessenger *)self->_messenger, *row);
                a = b;
                beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)&a);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, COLOR);
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
            beMessenger_AppendString((beMessenger *)self->_messenger, *row);
            beMessenger_AppendString((beMessenger *)self->_messenger, name);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            i++;
            off += 4;
            row++;
        } while (i < ((igObjectList *)self->_subSlot)->_count);
    }
}

void beNDMWStatusSubSlot_ShowSlotDescription(beNDMWStatusSubSlot *a) {
    int *text;
    int *onOff;
    int slot;
    int item;
    beNDMWItemBaseList *items;

    item = 0;
    slot = a->_retCode;
    if (slot != -1) {
        items = (beNDMWItemBaseList *)a->_subSlot;
        item = *(int *)(items->_data + (slot * 4));
    }
    if (item != 0) {
        text = (int *)(((int *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)item, (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)a->_insight, g_beNDMWStatus_metaObject), TXT_2)));
        beMessenger_SelectGroup((beMessenger *)a->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)a->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)a->_messenger, font000_2);
        beMessenger_AppendString((beMessenger *)a->_messenger, (const char *)text);
        beMessenger_DispatchSelected((beMessenger *)a->_messenger, TEXTSET_3);
        onOff = (int *)(DISPON_2);
    } else {
        onOff = (int *)(DISPOFF_2);
    }
    beMessenger_SelectGroup((beMessenger *)a->_messenger, TEXTCTL_5);
    beMessenger_AppendString((beMessenger *)a->_messenger, STWINFONT29_3);
    beMessenger_AppendString((beMessenger *)a->_messenger, font000_2);
    beMessenger_AppendString((beMessenger *)a->_messenger, (const char *)onOff);
    beMessenger_DispatchSelected((beMessenger *)a->_messenger, SWITCH_4);
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
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
        beMessenger_AppendString((beMessenger *)self->_messenger, upper);
        beMessenger_AppendString((beMessenger *)self->_messenger, off);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT11);
        beMessenger_AppendString((beMessenger *)self->_messenger, lower);
        beMessenger_AppendString((beMessenger *)self->_messenger, off);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
    }
}

void beNDMWStatusSubSlot_OpenSlotMenu(beNDMWStatusSubSlot *self) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl0;
    bool fl;
    int i;
    char **p;
    const char *s3;
    igIntList *t;

    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<beNDMWStatusSelectE0> win(beNDMWStatusSelectE0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    win.p->_selectMax = 3;
    win.p->_entCode = 0x78;
    a = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    a = g_useOwnerAllocator ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    igSmartPointer<igBoolList> flags(igBoolList_Create((int)a));
    BoolList_Append(flags.p, true);
    t = (igIntList *)self->_subSlot;
    fl0 = false;
    fl = false;
    if (t->_count > 0 && ((int *)t->_data)[self->_kindListPos] != 0) fl = true;
    BoolList_Append(flags.p, fl0);
    BoolList_Append(flags.p, fl);
    /* matching construct: as in the power socket's menu, the list is read through a const view of the holder */
    { const igSmartPointer<igBoolList> &view = flags; l0 = view.p; }
    w = win.p;
    igObject::ref(l0);
    REL(w->_decideList)
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
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
            beMessenger_AppendString((beMessenger *)self->_messenger, *p);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}

void beNDMWStatusSubSlot_OnSlotMenuDecided(beNDMWStatusSubSlot *self) {
    int entry;

    entry = self->_retCode;
    switch (entry) {
    case 0:
        self->_st1 = 4;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    case 1:
        self->_st1 = 2;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    case 2:
        self->_retCode = -1;
        AsEquipPanel(self)->EquipSelected();
        self->_retCode = self->_kindListPos;
        AsEquipPanel(self)->RefreshSlotList();
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, GAMERAM_9, 0, 0);
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, RECALCPLAYER_4);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, SUBWND_2);
        beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, UPDATE);
        self->_st0 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 1;
        self->_st3 = 0;
        self->_st2 = 0;
        break;
    }
}

void beNDMWStatusSubSlot_OpenDeviceFolder(beNDMWStatusSubSlot *self) {
    int alloc;
    int a;
    int s1;
    igDataList *s0;
    alloc = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
    if (g_useOwnerAllocator != 0) {
        a = alloc;
    } else {
        a = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
    }
    igSmartPointer<beNDMWStatusCtrlD0> win((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create(a));
    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
    StringList_AppendRetained((igStringRefList *)win.p->_textCloseNameList, igStringRef(font100_2).ref());
    beNDMWWindow_RunMessageScript((beNDMWWindow *)win.p, txt_status_lua_2, 139);
    s0 = (igDataList *)win.p->_kindList;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
        s0->_count = ListCount(s0) + 1;
    } else {
        ((Gap::Core::igDataList *)s0)->resizeAndSetCount(s1 + 1, 4);
    }
    static const int kindFilter[1] = {2};
    ((int *)s0->_data)[s1] = kindFilter[0];
    win.p->_isEquipDisable = 1;
    win.p->_isUnknownDisable = 1;
    win.p->_isAutoClose = 0;
}

/* True when the player's LEVEL is at least the LVPOINT record of device folder entry `entryIndex`;
 * the same check is in beNDMWStatusMainSlot. */
int beNDMWStatusSubSlot_CanEquip(beNDMWStatusSubSlot *self, int entryIndex) {
    int status;
    int entry;
    int playerLevel;

    entry = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (entryIndex * 4));
    status = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
    playerLevel = igProperty_GetRecord((igObject *)self->_playerList, LEVEL_3)->_data;
    return playerLevel >= beNDMWItemBase_GetRecordInt((beNDMWItemBase *)entry, (beNDMWStatus *)status, LVPOINT);
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
    beNDMWStatus_PreviewEquipment((beNDMWStatusCtrlBaseEquip *)self, (ItemList *)self->_subSlot, self->_kindListPos, (int)index);
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
        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT13).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
        if (self->_isBankFolder != 0) {
            beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_shop_lua, 0x517);
        } else {
            beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x46);
        }
        i = 0;
        fp = &g_statusFontNames[0];
        do {
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, *fp, space, LEFT_3);
            i += 1;
            fp += 1;
        } while (i < 12);
        i = 0;
        fp = &g_statusFontNames[0];
        do {
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT16, *fp, space, RIGHT_2);
            i += 1;
            fp += 1;
        } while (i < 12);
        if (self->_isBankFolder != 0) {
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT40, g_statusFontNames[0], space, RIGHT_2);
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT40, g_statusFontNames[1], space, RIGHT_2);
        } else {
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT23, g_statusFontNames[0], space, RIGHT_2);
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT23, g_statusFontNames[1], space, RIGHT_2);
        }
        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
        GET_ALLOC(alloc)
        {
        igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)alloc));
        beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
        ((beNDMWWindowSelect *)win.p)->_selectMax = beNDMWStatusCtrlD0_UpdatePageCount(self);
        {
            igObject *dl = (igObject *)self->_decideList;
            beNDMWWindowSelect *w;
            w = (beNDMWWindowSelect *)win.p;
            RETAIN_OBJ(dl)
            { igObject *old = (igObject *)w->_decideList; IG_OBJECT_RELEASE(old); }
            w->_decideList = (int)dl;
        }
        { beNDMWWindowSelect *wp = (beNDMWWindowSelect *)win.p; wp->_offsetPos[0] = -121.0f; wp->_offsetPos[1] = 128.0f; wp->_offsetPos[2] = 0.0f; }
        ((beNDMWWindowSelect *)win.p)->_startPoint = 0;
        }
        self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stfolder, 0, SQ_AWINONOPEN, SQ_CLOSE_3);
        vecB[0] = 85.0f;
        vecB[2] = 0.0f;
        vecB[1] = 25.0f;
        vecA[0] = -146.0f;
        vecA[1] = 25.0f;
        vecA[2] = 0.0f;
        AsListCtrl(self)->PresentPageArrows(&vecA[0], &vecB[0]);
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
                    if (beNDMWWindowSelect_CanRequestFO2TOP(mother)) {
                        bool ready = false;
                        if (AsListCtrl(self)->PrevPage()) {
                            ready = true;
                        } else if (AsListCtrl(self)->NextPage()) {
                            ready = true;
                        }
                        if (ready) {
                            ((beNDMWStatusCtrlD0 *)mother)->_st0 = 4;
                            ((beNDMWStatusCtrlD0 *)mother)->_st3 = 0;
                            ((beNDMWStatusCtrlD0 *)mother)->_st2 = 0;
                            ((beNDMWStatusCtrlD0 *)mother)->_st1 = 0;
                            mother->_selectMax = beNDMWStatusCtrlD0_UpdatePageCount(self);
                            {
                                igObject *dl = (igObject *)self->_decideList;
                                RETAIN_OBJ(dl)
                                { igObject *old = (igObject *)mother->_decideList; IG_OBJECT_RELEASE(old); }
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
                    ((beNDMWWindowSelect *)self->_mother)->_retCode = RowIndex(self->_nowPage * 12, self->_retCode);
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
                igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)alloc));
                beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)win.p);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
                beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
                rec = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                if (self->_isBankFolder != 0) {
                    beDataObjObjectList *folder = igProperty_GetRecordFolder((igObject *)rec, BANKDEVICE_2);
                    list = (igObjectList *)folder->_data;
                } else {
                    beDataObjObjectList *folder = igProperty_GetRecordFolder((igObject *)rec, DEVICEFOLDER_3);
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
                    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursorleft, 0, SQ_HIDE);
                }
                if (list->_count <= (self->_nowPage + 1) * 12) {
                    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursorright, 0, SQ_HIDE);
                }
                ((beNDMWWindowSelect *)win.p)->_selectMax = beNDMWStatusCtrlD0_UpdatePageCount(self);
                {
                    igObject *dl = (igObject *)self->_decideList;
                    beNDMWWindowSelect *w;
                    w = (beNDMWWindowSelect *)win.p;
                    RETAIN_OBJ(dl)
                    { igObject *old = (igObject *)w->_decideList; IG_OBJECT_RELEASE(old); }
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        i = 0;
        fp = &g_statusFontNames[0];
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        do {
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
            beMessenger_AppendString((beMessenger *)self->_messenger, *fp);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, DEFAULTCOLOR_2);
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT16);
            beMessenger_AppendString((beMessenger *)self->_messenger, *fp);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, DEFAULTCOLOR_2);
            i += 1;
            fp += 1;
        } while (i < 12);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void beNDMWStatusCtrlD0_RefreshText(beNDMWStatusCtrlD0 *self, int refreshRows, int refreshDescription) {
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
    beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
    beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
    o = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
    if (self->_isBankFolder != 0) {
        t = igProperty_GetRecordFolder((igObject *)o, BANKDEVICE_2);
        folder = (igDataList *)t->_data;
    } else {
        t2 = igProperty_GetRecordFolder((igObject *)o, DEVICEFOLDER_3);
        folder = (igDataList *)t2->_data;
    }
    ctx = ((void *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject));
    igSmartPointer<igStringObj> sp((igStringObj *)((beSystem *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject))->_globalStrObj);
    /* matching construct: the text buffers are declared after the holder so they lie below it in the frame as retail. */
    char buf1[2];
    char buf2[2];
    char buf3[2];
    igVec3f vec;
    igObject::ref(sp.p);
    if (refreshRows != 0) {
        i = 0;
        do {
            idx = self->_nowPage * 12 + i;
            if (idx < folder->_count) {
                item = *(beNDMWItemBase **)(folder->_data + idx * 4);
                s = ((char *)beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)ctx, NAME_3));
                igStringObj_Set(sp, s);
                if (item->_isEquip != 0) {
                    igStringObj_Insert(sp, (char *)equippedMark, 0, strlen((const char *)equippedMark));
                } else {
                    igStringObj_Insert(sp, (char *)unequippedMark, 0, strlen((const char *)unequippedMark));
                }
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[i]);
                mm = self->_messenger;
                nm2 = (char *)sp.p->_buffer;
                if (nm2 == 0) nm = g_stringObjEmptyText; else nm = nm2;
                beMessenger_AppendString((beMessenger *)mm, nm);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[i]);
                if (*(unsigned char *)(((igBoolList *)self->_decideList)->_data + i) != 0) {
                    m = self->_messenger;
                    beNDMWItemBase_GetRevisionColor(&vec, item);
                    beMessenger_AppendVec3((beMessenger *)m, vec.vec);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, COLOR);
                } else {
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, CANCELCOLOR_2);
                }
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT16);
                beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[i]);
                beMessenger_AppendString((beMessenger *)self->_messenger, space);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                tail = DISPON_2;
            } else {
                tail = DISPOFF_2;
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
            beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[i]);
            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)tail);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT16);
            beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[i]);
            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)tail);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            i++;
        } while (i < 12);
        buf1[0] = self->_nowPage + 49;
        buf1[1] = 0;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        if (self->_isBankFolder != 0) {
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT40);
        } else {
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT23);
        }
        beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
        beMessenger_AppendString((beMessenger *)self->_messenger, buf1);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
        buf1[0] = self->_maxPage + 48;
        buf1[1] = 0;
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        if (self->_isBankFolder != 0) {
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT40);
        } else {
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT23);
        }
        beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[1]);
        beMessenger_AppendString((beMessenger *)self->_messenger, buf1);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
    }
    if (refreshDescription != 0) {
        base = self->_nowPage * 12;
        idx = base + self->_retCode;
        if (idx < folder->_count) {
            item = *(beNDMWItemBase **)(folder->_data + idx * 4);
            s = ((char *)beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)ctx, TXT_2));
            if (item->_kindNo == 0) {
                if (item->_recNo != 0x114) {
                    buf2[1] = 0;
                    buf2[0] = ((beNDMWItemBlueArmor *)item)->_pocket + 48;
                    igStringObj_Set(sp, s);
                    r = sp.p;
                    i = r->_length;
                    igStringObj_Insert(r, buf2, i, strlen(buf2));
                    s2 = (char *)sp.p->_buffer;
                    s = s2 == 0 ? g_stringObjEmptyText : s2;
                }
            } else if (item->_kindNo == 1 && item->_recNo != 0x1f) {
                buf3[1] = 0;
                buf3[0] = ((beNDMWItemBlueArmor *)item)->_pocket + 48;
                igStringObj_Set(sp, s);
                r = sp.p;
                idx = r->_length;
                igStringObj_Insert(r, buf3, idx, strlen(buf3));
                s2 = (char *)sp.p->_buffer;
                s = s2 == 0 ? g_stringObjEmptyText : s2;
            }
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
            beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
            if (s != 0) {
                beMessenger_AppendString((beMessenger *)self->_messenger, s);
            } else {
                beMessenger_AppendString((beMessenger *)self->_messenger, space);
            }
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
            tail = DISPON_2;
        } else {
            tail = DISPOFF_2;
        }
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)tail);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
    }
}

int beNDMWStatusCtrlD0_UpdatePageCount(beNDMWStatusCtrlD0 *self) {
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
    beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
    beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
    obj = ((void *)beMessenger_GetObject((beMessenger *)self->_messenger, 0));
    if (self->_isBankFolder != 0) {
        int tmp = igProperty_GetRecordFolder((igObject *)obj, BANKDEVICE_2)->_data;
        fold = (igObjectList *)tmp;
    } else {
        int tmp = igProperty_GetRecordFolder((igObject *)obj, DEVICEFOLDER_3)->_data;
        fold = (igObjectList *)tmp;
    }
    if (fold->_count % 12 != 0) {
        pages = fold->_count / 12 + 1;
    } else {
        pages = fold->_count / 12;
    }
    self->_maxPage = pages;
    rem = fold->_count - self->_nowPage * 12;
    if (rem >= 12) {
        shown = 12;
    } else {
        shown = rem % 12;
    }
    ((igDataList *)self->_decideList)->_count = 0;
    for (idx = 0; idx < shown; idx++) {
        rec = *(beNDMWItemBase **)(fold->_data + (self->_nowPage * 12 + idx) * 4);
        ok = true;
        if (((igDataList *)self->_kindList)->_count > 0) {
            ok = false;
            for (k = 0; k < ((igDataList *)self->_kindList)->_count; k++) {
                t = *(int *)(((igDataList *)self->_kindList)->_data + k * 4);
                if (t == 3) {
                    if (rec->_kindNo == 3) {
                        a = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                        b1 = beNDMWItemBase_GetRecordBool(rec, (beNDMWStatus *)a, WU);
                        b2 = beNDMWItemBase_GetRecordBool(rec, (beNDMWStatus *)a, BLUEAB);
                        switch (self->_isAbType) {
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
        if (self->_isEquipDisable != 0 && rec->_isEquip != 0) ok = false;
        if (self->_isUnknownDisable != 0) {
            if ((rec->_kindNo == 0 && rec->_recNo == 276) || (rec->_kindNo == 1 && rec->_recNo == 31) || (rec->_kindNo == 2 && rec->_recNo == 44)) ok = false;
        }
        if (self->_isUnknownEnable != 0) {
            if ((rec->_kindNo == 0 && rec->_recNo == 276) || (rec->_kindNo == 1 && rec->_recNo == 31) || (rec->_kindNo == 2 && rec->_recNo == 44)) ok = true;
            else ok = false;
        }
        out = (igDataList *)self->_decideList;
        n = out->_count;
        if (n < out->_capacity) out->_count = n + 1;
        else ((Gap::Core::igDataList *)out)->resizeAndSetCount(n + 1, 1);
        *(unsigned char *)(n + out->_data) = ok;
    }
    if (self->_maxPage == 0) self->_maxPage = 1;
    if (shown == 0) shown = 1;
    return shown;
}

int beNDMWStatusCtrlD0_GetSelectedIndex(beNDMWStatusCtrlD0 *self)
{
    int row = self->_retCode;
    if (row == -1) {
        return -1;
    }
    return RowIndex(self->_nowPage * 12, row);
}

void beNDMWStatusCtrlFolder_Update(beNDMWStatusCtrlFolder *self) {
    void *alloc;
    beNDMWStatusCtrlD0 *found;
    switch (self->_st0) {
    case 0:
        ALLOC(alloc)
        {
        igSmartPointer<beNDMWStatusTitle04> title((beNDMWStatusTitle04 *)beNDMWStatusTitle04_Create((int)alloc));
        beNDMWWindow_BindContext((beNDMWWindow *)title.p, (igObject *)self, self->_insight, self->_playerNo, 0x3C);
        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)title.p);
        }
        self->_folderMenu = 0;
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
            case 0:
                ALLOC(alloc)
                {
                igSmartPointer<beNDMWStatusSelect01> menu((beNDMWStatusSelect01 *)beNDMWStatusSelect01_Create((int)alloc));
                beNDMWWindow_BindContext((beNDMWWindow *)menu.p, (igObject *)self, self->_insight, self->_playerNo, 0x3D);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)menu.p);
                ((beNDMWStatusSelect01 *)menu.p)->_startPoint = self->_folderMenu;
                beNDMWWindow_QueueText((beNDMWWindow *)menu.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                }
                self->_nowProcKazu = ((igDataList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (self->_retCode != -1) {
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, self->_retCode + 0x51);
                }
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_retCode;
            case 2:
                if (((igDataList *)self->_subWindow)->_count == self->_nowProcKazu) {
                    if (self->_retCode == -1) { return; }
                    if (self->_st3 == self->_retCode) { return; }
                    self->_st2 = 1;
                    self->_st3 = 0;
                    return;
                }
                if (self->_retCode != -1) {
                    self->_folderMenu = self->_retCode;
                }
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
                case 2:
                    self->_st1 = 3;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                case 3:
                    self->_st1 = 4;
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
        case 1:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc)
                {
                igSmartPointer<beNDMWStatusCtrlD0> deviceList((beNDMWStatusCtrlD0 *)beNDMWStatusCtrlD0_Create((int)alloc));
                beNDMWWindow_BindContext((beNDMWWindow *)deviceList.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)deviceList.p);
                ((beNDMWStatusCtrlD0 *)deviceList.p)->_isAutoClose = 0;
                }
                self->_nowProcKazu = ((igDataList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (self->_st3 == 0) {
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x2B);
                    self->_st3 = 1;
                }
                found = FolderHelpers::FindSub(self);
                if (found != 0) {
                    if (self->_retCode == -1) {
                        MSG()
                        ((beNDMWWindow *)found)->_st0 = 2;
                        ((beNDMWWindow *)found)->_st3 = 0;
                        ((beNDMWWindow *)found)->_st2 = 0;
                        ((beNDMWWindow *)found)->_st1 = 0;
                        self->_st2 = 3;
                        self->_st3 = 0;
                        return;
                    }
                    if (((beNDMWWindow *)found)->_st0 == 1 && ((beNDMWWindow *)found)->_st1 == 2) {
                        MSG()
                        ALLOC(alloc)
                        {
                        igSmartPointer<beNDMWStatusSubMenu> subMenu((beNDMWStatusSubMenu *)beNDMWStatusSubMenu_Create((int)alloc));
                        beNDMWWindow_BindContext((beNDMWWindow *)subMenu.p, (igObject *)self, self->_insight, self->_playerNo, self->_retCode);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)subMenu.p);
                        ((beNDMWStatusSubMenu *)subMenu.p)->_selectDevice = self->_retCode;
                        {
                            beNDMWStatusSubMenu *o = (beNDMWStatusSubMenu *)subMenu.p;
                            igObject *old;
                            igObject::ref(found);
                            old = (igObject *)o->_deviceFolderList;
                            IG_OBJECT_RELEASE(old);
                            o->_deviceFolderList = (int)found;
                        }
                        }
                        self->_nowProcKazu = ((igDataList *)self->_subWindow)->_count;
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        return;
                    }
                }
                break;
            case 2:
                if (((igDataList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_nowProcKazu = ((igDataList *)self->_subWindow)->_count;
                    self->_retCode = 0;
                    beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
                    CLEAR(self->_modelCloseInfoNameList)
                    ((igDataList *)self->_modelCloseRamNoList)->_count = 0;
                    CLEAR(self->_modelCloseSeqNameList)
                    beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
                    found = FolderHelpers::FindSub(self);
                    if (found != 0) {
                        ((beNDMWWindow *)found)->_st2 = 1;
                        ((beNDMWWindow *)found)->_st3 = 0;
                        self->_st2 = 1;
                        self->_st3 = 0;
                        return;
                    }
                    self->_st2 = 4;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 3:
                found = FolderHelpers::FindSub(self);
                if (found == 0) {
                    self->_retCode = self->_folderMenu;
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            case 4:
                if (((igDataList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_st2 = 0;
                    self->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
        case 3:
        case 4:
            switch (self->_st2) {
            case 0:
                {
                igSmartPointer<beNDMWWindow> child(0);
                switch (self->_st1) {
                case 2:
                    ALLOC(alloc)
                    { igObject *t = child.p; IG_OBJECT_RELEASE(t); }
                    child.p = (beNDMWWindow *)beNDMWStatusCtrlFlag_Create((int)alloc);
                    break;
                case 3:
                    ALLOC(alloc)
                    { igObject *t = child.p; IG_OBJECT_RELEASE(t); }
                    child.p = (beNDMWWindow *)beNDMWStatusCtrlDisk_Create((int)alloc);
                    break;
                case 4:
                    ALLOC(alloc)
                    { igObject *t = child.p; IG_OBJECT_RELEASE(t); }
                    child.p = (beNDMWWindow *)beNDMWStatusCtrlBit_Create((int)alloc);
                    break;
                }
                beNDMWWindow_BindContext(child.p, self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)child.p);
                }
                self->_nowProcKazu = ((igDataList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((igDataList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_retCode = self->_folderMenu;
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void beNDMWStatusCtrlFlag_Update(beNDMWStatusCtrlFlag *self) {
    PropertyRecordList *lst;
    int s2;
    int s1;
    int a;
    int al;
    igIntList *l4;
    char *src;
    int k;
    char **p;
    switch (self->_st0) {
    case 0:
        beMessenger_SendGroup((beMessenger *)self->_messenger, GAMERAM_9, GETCOMMON_6);
        lst = (PropertyRecordList *)igProperty_GetRecordArray(beMessenger_GetObject((beMessenger *)self->_messenger, 0), FLAGFOLDER_2)->_data;
        s2 = 0;
        if (0 < lst->cnt) {
            do {
                if (lst->data[s2] != 0) {
                    l4 = (igIntList *)self->_impItems;
                    s1 = l4->_count;
                    if (s1 < l4->_capacity) {
                        l4->_count = ListCount(l4) + 1;
                    } else {
                        ((Gap::Core::igDataList *)l4)->resizeAndSetCount(s1 + 1, 4);
                    }
                    ((int *)l4->_data)[s1] = s2;
                }
                s2 += 1;
            } while (s2 < lst->cnt);
        }
        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT13).ref());
        src = g_statusFontNames[0];
        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(src).ref());
        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x47);
        k = 0;
        p = &g_statusFontNames[0];
        do {
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, *p, space, LEFT_3);
            k += 1;
            p += 1;
        } while (k < 12);
        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT23, g_statusFontNames[0], space, RIGHT_2);
        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT23, g_statusFontNames[1], space, RIGHT_2);
        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
        al = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
        al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
        {
        /* the list window is owned by the stack reference while it is bound, listed and set up; its
         * share is released at the block end */
        igSmartPointer<beNDMWStatusSelectE1> win((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
        beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
        /* matching construct: (unsigned) cast on the reference steers retail operand order */
        ((Gap::Core::igObjectList *)((unsigned)self->_subWindow))->append((Gap::Core::igObject *)win.p);
        a = ((igIntList *)self->_impItems)->_count;
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
        StringList_AppendRetained((igStringRefList *)win.p->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
        StringList_AppendRetained((igStringRefList *)win.p->_textCloseNameList, igStringRef(font100_2).ref());
        beNDMWWindow_RunMessageScript((beNDMWWindow *)win.p, txt_status_lua_2, 0x87);
        }
        self->_nowProcKazu = ((beNDMWWindowList *)(self->_subWindow))->_count;
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stfolder, 0, SQ_FLAGOPEN, SQ_CLOSE_3);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            beNDMWStatusCtrlFlag_RefreshText(self, 1, 1);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            if (((beNDMWWindowList *)(self->_subWindow))->_count == self->_nowProcKazu) {
                a = self->_retCode;
                if (a != -1 && self->_st2 != a) {
                    beNDMWStatusCtrlFlag_RefreshText(self, 0, 1);
                    self->_st2 = self->_retCode;
                    self->_st3 = 0;
                }
            } else {
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

void beNDMWStatusCtrlFlag_RefreshText(beNDMWStatusCtrlFlag *self, int refreshRows, int refreshDescription) {
    int s0;
    int v6;
    igDataList *l;
    int s5;
    int w3;
    char **v4;
    char **w4;
    int v3;
    beMessenger_SendNamed((beMessenger *)self->_messenger, DATABASE_7, impItem_2, 0, GETDATABASE_7);
    s0 = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
    if (refreshRows != 0) {
        v6 = 0;
        l = (igDataList *)self->_impItems;
        if (0 < l->_count) {
            v3 = 0;
            v4 = g_statusFontNames;
            do {
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                beMessenger_AppendString((beMessenger *)self->_messenger, *v4);
                s5 = self->_messenger;
                beMessenger_AppendString((beMessenger *)s5, beDataBase_GetRecordString((beDataBase *)s0, *(int *)&((unsigned char *)((igDataList *)self->_impItems)->_data)[v3], NAME_3));
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                v6++;
                v4++;
                v3 += 4;
            } while (v6 < (l = (igDataList *)self->_impItems)->_count);
        }
        w3 = l->_count;
        if (w3 < 12) {
            w4 = &g_statusFontNames[w3];
            do {
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                beMessenger_AppendString((beMessenger *)self->_messenger, *w4);
                beMessenger_AppendString((beMessenger *)self->_messenger, DISPOFF_2);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
                w3++;
                w4++;
            } while (w3 < 12);
        }
    }
    if (refreshDescription != 0 && ((igDataList *)self->_impItems)->_count > 0) {
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
        s5 = self->_messenger;
        beMessenger_AppendString((beMessenger *)s5, beDataBase_GetRecordString((beDataBase *)s0, ((int *)((igDataList *)self->_impItems)->_data)[self->_retCode], TXT_2));
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
    }
}

static inline int st1Of(const beNDMWStatusCtrlDisk *w) { return w->_st1; }

void beNDMWStatusCtrlDisk_Update(beNDMWStatusCtrlDisk *self)
{
    CellNameRow names;
    char bufC[8];
    float vecA[3];
    float vecB[3];
    float vecC[3];
    float vecD[3];
    ModelNameTable tq;
    switch (self->_st0) {
    case 0: {
        int i, j;
        if (self->_st1 == 0) self->_cursor = 0;
        MSG_SELECT_INT(self->_playerNo)
        igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3);
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stfolder, 0, SQ_AWINOFFOPEN, SQ_CLOSE_3);
        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT13).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x48);
        for (i = 0; i < 12; i++)
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, g_statusFontNames[i], space, LEFT_3);
        for (j = 0; j < 12; j++)
            beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT15, g_statusFontNames[j], space, RIGHT_2);
        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
        NEXT_ST0()
    }
    case 1:
        switch (st1Of(self)) {
        case 0: {
            void *al;
            int cnt;
            GET_ALLOC(al)
            { igSmartPointer<beNDMWStatusSelectE1> diskWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
            beNDMWWindow_BindContext((beNDMWWindow *)diskWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
            ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)diskWin.p);
            MSG_SELECT_INT(self->_playerNo)
            igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3);
            WSETI84(diskWin.p, 10)
            WSETPOS(diskWin.p, -121.0f, 128.0f, 0.0f)
            WSETI100(diskWin.p, self->_cursor)
            StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)diskWin.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
            StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)diskWin.p)->_textCloseNameList, igStringRef(font100_2).ref());
            beNDMWWindow_RunMessageScript((beNDMWWindow *)diskWin.p, txt_status_lua_2, 0x2B);
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
                static const ModelNameTable models = {{SQ_OPEN00, SQ_OPEN01, SQ_OPEN02, SQ_OPEN03, SQ_OPEN04, SQ_OPEN05, SQ_OPEN06, SQ_OPEN07, SQ_OPEN08, SQ_OPEN09, SQ_OPEN10, SQ_OPEN11}};
                tq = models;
                vecA[0] = -121.0f; vecA[1] = 128.0f; vecA[2] = 0.0f;
                beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, (const char *)tq.v[self->_cursor], (const char *)0, (float *)vecA);
                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> actionWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)actionWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)actionWin.p);
                WSETI84(actionWin.p, 2)
                WSETPOS(actionWin.p, 115.0f, 145.0f, 0.0f)
                WSETI100(actionWin.p, 0)
                beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)actionWin.p, i_stmenu02, 0, SQ_2LINEOPEN, SQ_CLOSE_3);
                beNDMWWindow_QueueText((beNDMWWindow *)actionWin.p, STWINFONT26, g_statusFontNames[0], space, LEFT_3);
                beNDMWWindow_QueueText((beNDMWWindow *)actionWin.p, STWINFONT26, g_statusFontNames[1], space, LEFT_3);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 1:
                beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x41);
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
                { igSmartPointer<beNDMWStatusSelectE1> orderWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)orderWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)orderWin.p);
                MSG_SELECT_INT(self->_playerNo)
                igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3);
                WSETI84(orderWin.p, 10)
                WSETPOS(orderWin.p, -121.0f, 128.0f, 0.0f)
                WSETI100(orderWin.p, self->_cursor)
                GET_ALLOC(al)
                igSmartPointer<igBoolList> decided(igBoolList_Create((int)al));
                for (i = 0; i < 10; i++) {
                    if (i == self->_cursor) { BoolList_Append(decided.p, false); } else { BoolList_Append(decided.p, true); }
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
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3)->_data;
                        SwapRef cursorDisk(((void **)l->_data)[self->_cursor]);
                        SwapRef targetDisk(((void **)l->_data)[self->_retCode]);
                        beNDMWLoadIntf2_igObjectList_Set((igDataList *)l, self->_cursor, (ObjectRefTarget *)targetDisk.p);
                        beNDMWLoadIntf2_igObjectList_Set((igDataList *)l, self->_retCode, (ObjectRefTarget *)cursorDisk.p);
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
                item = (beNDMWItemDisk *)((int *)((igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3)->_data)->_data)[self->_cursor];
                if (item->_kazu <= 0) {
                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWShopSelect00> emptyWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                    beNDMWWindow_BindContext((beNDMWWindow *)emptyWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)emptyWin.p);
                    NEXT_ST2()
                    StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)emptyWin.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
                    StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)emptyWin.p)->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)emptyWin.p, txt_status_lua_2, 0x8D);
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
                        obj = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                        if (igProperty_GetRecordByte((igObject *)obj, ISUSE_7)->_data != 0 && i != self->_playerNo) {
                            LIST_ADD(self->_playerNoList, i)
                            {
                            igObjectList *fl = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, DISKFOLDER_3)->_data;
                            beNDMWItemDisk *found = 0;
                            int k;
                            for (k = 0; k < fl->_count; k++) {
                                beNDMWItemDisk *e = ((beNDMWItemDisk **)fl->_data)[k];
                                if (e->_recNo == item->_recNo) { found = e; break; }
                            }
                            if (found != 0) ((Gap::Core::igObjectList *)self->_diskList)->append((Gap::Core::igObject *)found);
                            else ((Gap::Core::igObjectList *)self->_diskList)->append(0);
                            }
                        }
                    }
                    if (((igObjectList *)self->_playerNoList)->_count <= 0) {
                        GET_ALLOC(al)
                        { igSmartPointer<beNDMWShopSelect00> noPlayerWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                        beNDMWWindow_BindContext((beNDMWWindow *)noPlayerWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)noPlayerWin.p);
                        NEXT_ST2()
                        StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)noPlayerWin.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
                        StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)noPlayerWin.p)->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
                        beNDMWWindow_RunMessageScript((beNDMWWindow *)noPlayerWin.p, txt_status_lua_2, 0x8E);
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
                beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
                CLOSE_LISTS()
                beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
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
                    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_1ITEMOPEN, SQ_CLOSE_3);
                    break;
                case 2:
                    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_2ITEMOPEN, SQ_CLOSE_3);
                    break;
                case 3:
                    beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_3ITEMOPEN, SQ_CLOSE_3);
                    break;
                }
                StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT39).ref());
                StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(font000_2).ref());
                StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT39).ref());
                StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(font001_2).ref());
                beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x4A);
                MSG_SELECT_INT(self->_playerNo)
                lsx = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3)->_data;
                beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, font000_2, (const char *)beNDMWItemBase_GetRecordString(item = (beNDMWItemBase *)((int *)lsx->_data)[self->_cursor], (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject), NAME_3), LEFT_3);
                beNDMWLoadIntf2_igObject_Retain((ObjectRefTarget *)item);
                beNDMWLoadIntf2_igObject_Release((igObject *)self->_sendDisk);
                self->_sendDisk = (int)item;
                static const CellNameRow playerCells = {{font001_2, font002_2, font003_2}};
                names = playerCells;
                for (i = 0; i < ((igObjectList *)self->_playerNoList)->_count; i++) {
                    int pno = ((int *)((igObjectList *)self->_playerNoList)->_data)[i];
                    igObjectList *l2;
                    MSG_SELECT_INT(pno)
                    l2 = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), PLAYERNAME_3)->_data;
                    if (l2->_count > 0) {
                        DeviceRef firstDevice((void *)*(int *)l2->_data, kRetainReference);
                        beNDMWWindow_QueueObjectText((beNDMWWindow *)self, STWINFONT14_2, names.v[i], (const igSmartPointer<igObject> &)DeviceRef(firstDevice), LEFT_3);
                    }
                    bufC[0] = ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[i])->_kazu + 0x30;
                    bufC[1] = 0;
                    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT15, names.v[i], bufC, CENTER_2);
                }
                {
                    char bufA[2];
                    bufA[0] = ((beNDMWItemDisk *)self->_sendDisk)->_kazu + 0x30;
                    bufA[1] = 0;
                    beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT38, font000_2, bufA, CENTER_2);
                }
                beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT38, font001_2, text_0, CENTER_2);
                NEXT_ST2()
            }
            case 3: {
                void *al;
                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> playerWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)playerWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)playerWin.p);
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
                        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, SQ_OPEN00, (const char *)0, (float *)vecB);
                        break;
                    case 1:
                        vecC[0] = -121.0f; vecC[1] = 109.0f; vecC[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, SQ_OPEN01, (const char *)0, (float *)vecC);
                        break;
                    case 2:
                        vecD[0] = -121.0f; vecD[1] = 109.0f; vecD[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, SQ_OPEN02, (const char *)0, (float *)vecD);
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
                { igSmartPointer<beNDMWShopSelect52> quantityWin((beNDMWShopSelect52 *)beNDMWShopSelect52_Create((int)al));
                a1 = ((beNDMWItemDisk *)self->_sendDisk)->_kazu;
                v0 = 9 - ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[self->_receipt])->_kazu;
                self->_sendMax = (a1 < v0) ? a1 : v0;
                beNDMWWindow_BindContext((beNDMWWindow *)quantityWin.p, (igObject *)self, self->_insight, self->_playerNo, self->_sendMax);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)quantityWin.p);
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
                        { igSmartPointer<beNDMWShopSelect00> sentWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                        beNDMWWindow_BindContext((beNDMWWindow *)sentWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)sentWin.p);
                        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x84);
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
                { igSmartPointer<beNDMWShopSelect00> fullWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)fullWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)fullWin.p);
                StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)fullWin.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
                StringList_AppendRetained((igStringRefList *)((beNDMWWindowSelect *)fullWin.p)->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
                beNDMWWindow_RunMessageScript((beNDMWWindow *)fullWin.p, txt_status_lua_2, 0x8F);
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
                beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
                CLOSE_LISTS()
                beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        NEXT_ST0()
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void StringRefList_ResetRange(igStringRefList *list, int first, int count) {
    int *header;
    int refCount;
    int pool;
    int end;
    int index;
    void **slot;
    void *empty;
    int offset;
    void *held;

    end = first + count;
    index = first;
    if (first < end) {
        offset = first * 4;
        do {
            slot = (void **)(list->_data + offset);
            if (g_stringPool == 0) {
                pool = ((int)StringPool_Allocate(0x10));
                if (pool != 0) {
                    pool = ((int)StringPool_Construct((StringPool *)pool));
                }
                g_stringPool = (StringPool *)pool;
            }
            empty = (void *)(((void *)StringPool_Intern(g_stringPool, 0)));
            held = (void *)(*slot);
            if (held != 0) {
                header = (int *)((char *)held - 8);
                refCount = *(int *)((char *)(held) - 4) - 1;
                *(int *)((char *)(held) - 4) = refCount;
                if (refCount == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
            }
            index += 1;
            *slot = empty;
            offset += 4;
        } while (index < end);
    }
}

void ObjectList_ZeroRange(igObjectList *list, int first, int count) {
    ZeroRange(list, first, count);
}

void ObjectList_ReleaseRange(igObjectList *list, int first, int count) {
    ReleaseRange(list, first, count);
}

void **ObjectRef_AssignRetained(void **slot, igObject *object) {
    igObject *old;

    igObject::ref(object);
    old = (igObject *)(*slot);
    igObject::release(old);
    *slot = object;
    return slot;
}

void beNDMWStatusCtrlDisk_RefreshText(beNDMWStatusCtrlDisk *self, int refreshRows, int refreshDescription) {
    char digit[2];
    int i;
    beNDMWItemDisk *it;
    int s7;
    char *str;
    int off;
    int v1;
    igObjectList *s6;
    char **s0;
    beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
    beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
    s6 = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DISKFOLDER_3)->_data;
    s7 = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
    if (refreshRows != 0) {
        digit[1] = 0;
        i = 0;
        if (0 < s6->_count) {
            off = 0;
            s0 = &g_statusFontNames[0];
            do {
                it = *(beNDMWItemDisk **)((char *)s6->_data + off);
                if (it != 0) {
                    str = ((char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)it, (beNDMWStatus *)s7, NAME_3));
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                    beMessenger_AppendString((beMessenger *)self->_messenger, *s0);
                    beMessenger_AppendString((beMessenger *)self->_messenger, str);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                    digit[0] = it->_kazu + 0x30;
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT15);
                    beMessenger_AppendString((beMessenger *)self->_messenger, *s0);
                    beMessenger_AppendString((beMessenger *)self->_messenger, digit);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                }
                i++;
                off += 4;
                s0 += 1;
            } while (i < s6->_count);
        }
    }
    if (refreshDescription != 0) {
        v1 = self->_retCode;
        if (v1 != -1) {
            str = ((char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)((beNDMWItemDisk **)s6->_data)[v1], (beNDMWStatus *)s7, TXT_2));
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
            beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
            beMessenger_AppendString((beMessenger *)self->_messenger, str);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
            beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
            beMessenger_AppendString((beMessenger *)self->_messenger, DISPON_2);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
            return;
        }
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
        beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
        beMessenger_AppendString((beMessenger *)self->_messenger, DISPOFF_2);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
    }
}

void beNDMWStatusCtrlBit_Update(beNDMWStatusCtrlBit *self) {
    int s2;
    int al;
    int i;
    int s1;
    igIntList *l4;
    switch (self->_st0) {
    case 0:
        beMessenger_SendGroup((beMessenger *)self->_messenger, GAMERAM_9, GETCOMMON_6);
        igProperty_GetRecord(beMessenger_GetObject((beMessenger *)self->_messenger, 0), NINZU_4);
        i = 0;
        do {
            beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
            beMessenger_AppendInt((beMessenger *)self->_messenger, i);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
            if (igProperty_GetRecordByte(beMessenger_GetObject((beMessenger *)self->_messenger, 0), ISUSE_7)->_data != 0 && i != self->_playerNo) {
                l4 = (igIntList *)self->_playerNoList;
                s1 = l4->_count;
                if (s1 < l4->_capacity) {
                    l4->_count = ListCount(l4) + 1;
                } else {
                    ((Gap::Core::igDataList *)l4)->resizeAndSetCount(s1 + 1, 4);
                }
                ((int *)l4->_data)[s1] = i;
            }
            i += 1;
        } while (i < 4);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        if (((igIntList *)self->_playerNoList)->_count == 0) {
            self->_st1 = 0;
            self->_st3 = 0;
            self->_st2 = 0;
        } else {
            self->_st1 = 1;
            self->_st3 = 0;
            self->_st2 = 0;
        }
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                al = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
                al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
                {
                    igSmartPointer<beNDMWShopSelect00> win((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)((unsigned)self->_subWindow))->append((Gap::Core::igObject *)win.p);
                    StringList_AppendRetained((igStringRefList *)((beNDMWWindow *)win.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
                    s2 = (int)g_statusFontNames[0];
                    StringList_AppendRetained((igStringRefList *)((beNDMWWindow *)win.p)->_textCloseNameList, igStringRef((const char *)s2).ref());
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x58);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)(self->_subWindow))->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 1:
                if (((beNDMWWindowList *)(self->_subWindow))->_count != self->_nowProcKazu) {
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                al = ((int)((Gap::Core::igObject *)self)->getMemoryPool());
                al = (g_useOwnerAllocator != 0) ? al : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
                {
                    igSmartPointer<beNDMWStatusCtrlSendBit> win((beNDMWStatusCtrlSendBit *)beNDMWStatusCtrlSendBit_Create(al));
                    beNDMWWindow_BindContext((beNDMWWindow *)win.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)((unsigned)self->_subWindow))->append((Gap::Core::igObject *)win.p);
                    {
                        igIntList *lst = (igIntList *)self->_playerNoList;
                        beNDMWStatusCtrlSendBit *w = win.p;
                        igObject *old;
                        if (lst != 0) lst->_refCount = lst->_refCount + 1;
                        old = (igObject *)w->_playerNoList;
                        igObject::release(old);
                        w->_playerNoList = (int)lst;
                    }
                }
                self->_nowProcKazu = ((beNDMWWindowList *)(self->_subWindow))->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)(self->_subWindow))->_count != self->_nowProcKazu) {
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}


void beNDMWStatusCtrlSendBit_Update(beNDMWStatusCtrlSendBit *p) {
    CellNameRow cellNames;
    CellNameRow cellNamesInRow;
    int cursorPos0[3], cursorPos1[3], cursorPos2[3];
    int bitsText[4], cellText[4], playerBitsText[4], rowBitsText[4], clearCellText[4];
    int k, i, n, cnt;
    const char **tbl;
    int k2, n2, oe;
    int o, al, rec, t, mx, b, sw;
    int pad, c0, c1, c3, c2, dig, e;
    bool up, dn;
    int i2; 

    switch (p->_st0) {
    case 0:
        t = ((igIntList *)p->_playerNoList)->_count;
        switch (t) { case 1: default: beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)p, i_stmenu02, 0, SQ_1BITOPEN, SQ_CLOSE_3); break; case 2: beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)p, i_stmenu02, 0, SQ_2BITOPEN, SQ_CLOSE_3); break; case 3: beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)p, i_stmenu02, 0, SQ_3BITOPEN, SQ_CLOSE_3); break; }
        StringList_AppendRetained((igStringRefList *)p->_textCloseTypeList, igStringRef(STWINFONT39).ref());
        StringList_AppendRetained((igStringRefList *)p->_textCloseNameList, igStringRef(font000_2).ref());
        StringList_AppendRetained((igStringRefList *)p->_textCloseTypeList, igStringRef(STWINFONT39).ref());
        StringList_AppendRetained((igStringRefList *)p->_textCloseNameList, igStringRef(font001_2).ref());
        beNDMWWindow_RunMessageScript((beNDMWWindow *)p, txt_status_lua_2, 0x4C);
        beNDMWWindow_QueueText((beNDMWWindow *)p, STWINFONT28, font000_2, space, CENTER_2);
        beNDMWWindow_QueueText((beNDMWWindow *)p, STWINFONT27, font000_2, space, RIGHT_2);
        static const CellNameRow playerCells = {{font001_2, font002_2, font003_2}};
        tbl = cellNames.v;
        cellNames = playerCells;
        k = 0;
        if (0 < ((igIntList *)p->_playerNoList)->_count) {
            i = 0;
            do {
                n = *(int *)(((igIntList *)p->_playerNoList)->_data + i);
                SEL(GAMERAM_9);
                API(n);
                DSP(GETPLAYER_6);
                n = (int)beMessenger_GetObject((beMessenger *)p->_messenger, 0);
                beNDMWWindow_QueueText((beNDMWWindow *)p, STWINFONT14_2, *tbl, space, LEFT_3);
                sprintf((char *)bitsText, percent_d_3, igProperty_GetRecord((igObject *)n, BIT_5)->_data);
                beNDMWWindow_QueueText((beNDMWWindow *)p, STWINFONT27, *tbl, space, RIGHT_2);
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
                sprintf((char *)cellText, font_03d, k);
                SEL(TEXTCTL_5);
                APS(STWINFONT28);
                APS(cellText);
                APS(DISPOFF_2);
                DSP(SWITCH_4);
                k += 1;
            } while (k < 7);
            p->_editBit = 0;
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(font000_2); APS(CENTER_2); DSP(ALIGN_2);
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(font000_2); APS(text_0); DSP(TEXTSET_3);
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(font000_2); APS(DISPON_2); DSP(SWITCH_4);
            SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
            sprintf((char *)playerBitsText, percent_d_3, igProperty_GetRecord(beMessenger_GetObject((beMessenger *)p->_messenger, 0), BIT_5)->_data);
            SEL(TEXTCTL_5); APS(STWINFONT27); APS(font000_2); APS(playerBitsText); DSP(TEXTSET_3);
            static const CellNameRow playerCells = {{font001_2, font002_2, font003_2}};
            tbl = cellNamesInRow.v;
            cellNamesInRow = playerCells;
            k2 = 0;
            if (0 < ((igIntList *)p->_playerNoList)->_count) {
                i2 = 0;
                do {
                    oe = *(int *)(((igIntList *)p->_playerNoList)->_data + i2);
                    SEL(GAMERAM_9); API(oe); DSP(GETPLAYER_6);
                    n2 = (int)beMessenger_GetObject((beMessenger *)p->_messenger, 0);
                    {
                    DeviceRef r11C((void *)*(int *)(*(int *)(igProperty_GetRecordFolder((igObject *)n2, PLAYERNAME_3)->_data + 16)));
                    igObject::ref(r11C.p);
                    SEL(TEXTCTL_5); APS(STWINFONT14_2); APS(*tbl); APO(r11C.p); DSP(TEXTSET_3);
                    sprintf((char *)rowBitsText, percent_d_3, igProperty_GetRecord((igObject *)n2, BIT_5)->_data);
                    SEL(TEXTCTL_5); APS(STWINFONT27); APS(*tbl); APS(rowBitsText); DSP(TEXTSET_3);
                    }
                    k2 += 1;
                    i2 += 4;
                    tbl += 1;
                } while (k2 < ((igIntList *)p->_playerNoList)->_count);
            }
            al = (int)WindowAllocator(p);
            {
            float *q118;
            igSmartPointer<beNDMWStatusSelectE1> r118((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
            beNDMWWindow_BindContext((beNDMWWindow *)r118.p, (igObject *)p, p->_insight, p->_playerNo, 0);
            ((Gap::Core::igObjectList *)p->_subWindow)->append((Gap::Core::igObject *)r118.p);
            q118 = ((beNDMWStatusSelectE1 *)r118.p)->_offsetPos.vec;
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
                    cursorPos0[0] = 0xC2F20000; cursorPos0[1] = 0x42DA0000; cursorPos0[2] = 0;
                    beNDMWWindow_PresentModel((beNDMWWindow *)p, i_stcursor04, 0, SQ_OPEN00, (const char *)0, (float *)cursorPos0);
                    break;
                case 1:
                    cursorPos1[0] = 0xC2F20000; cursorPos1[1] = 0x42DA0000; cursorPos1[2] = 0;
                    beNDMWWindow_PresentModel((beNDMWWindow *)p, i_stcursor04, 0, SQ_OPEN01, (const char *)0, (float *)cursorPos1);
                    break;
                case 2:
                    cursorPos2[0] = 0xC2F20000; cursorPos2[1] = 0x42DA0000; cursorPos2[2] = 0;
                    beNDMWWindow_PresentModel((beNDMWWindow *)p, i_stcursor04, 0, SQ_OPEN02, (const char *)0, (float *)cursorPos2);
                    break;
                }
                al = (int)WindowAllocator(p);
                {
                igSmartPointer<beNDMWShopSelect34> r114((beNDMWShopSelect34 *)beNDMWShopSelect34_Create(al));
                beNDMWWindow_BindContext((beNDMWWindow *)r114.p, (igObject *)p, p->_insight, p->_playerNo, 3);
                ((Gap::Core::igObjectList *)p->_subWindow)->append((Gap::Core::igObject *)r114.p);
                beNDMWWindow_ShowPaddedDigits((beNDMWWindow *)r114.p, p->_editBit, 1, font_03d);
                }
                p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
                SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
                mx = igProperty_GetRecord(beMessenger_GetObject((beMessenger *)p->_messenger, 0), BIT_5)->_data;
                if (mx >= 0x98967F) {
                    mx = 0x98967F;
                }
                o = ((int *)((igIntList *)p->_playerNoList)->_data)[p->_receipt];
                SEL(GAMERAM_9); API(o); DSP(GETPLAYER_6);
                b = 0x98967F - igProperty_GetRecord(beMessenger_GetObject((beMessenger *)p->_messenger, 0), BIT_5)->_data;
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
                        beMessenger_SendNamed((beMessenger *)p->_messenger, SELECTCTRL_2, i_stcursor03, p->_playerNo, ISSELECTNOW);
                        if (beMessenger_GetBool((beMessenger *)p->_messenger, 0) != 0) {
                            pad = ((int)bePadManager_GetPadForPlayer((bePadManager *)p->_padManager, p->_playerNo));
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
                                    beNDMWWindow_ShowPaddedDigits((beNDMWWindow *)((int *)((igObjectList *)p->_subWindow)->_data)[0], c1, t, font_03d);
                                    SEL(SOUND_4); APS(CURSOR_MOVE); DSP(PLAY_3);
                                    return;
                                }
                            }
                        }
                    } else {
                        beNDMWWindow_ShowPaddedDigits((beNDMWWindow *)((int *)((igObjectList *)sw)->_data)[0], p->_editBit, 7 - t, font_03d);
                        p->_st3 = p->_retCode;
                        return;
                    }
                }
            } else {
                if (p->_retCode == -1 || p->_editBit <= 0) {
                    beMessenger_SendNamed((beMessenger *)p->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
                    p->_st2 = 0;
                    p->_st3 = 0;
                    return;
                }
                SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(font100_2); APS(DISPOFF_2); DSP(SWITCH_4);
                SEL(GAMERAM_9); API(p->_playerNo); DSP(GETPLAYER_6);
                n = (int)beMessenger_GetObject((beMessenger *)p->_messenger, 0);
                t = igProperty_GetRecord((igObject *)n, BIT_5)->_data - p->_editBit;
                igProperty_GetRecord((igObject *)n, BIT_5)->_data = t;
                o = ((int *)((igIntList *)p->_playerNoList)->_data)[p->_receipt];
                SEL(GAMERAM_9); API(o); DSP(GETPLAYER_6);
                n = (int)beMessenger_GetObject((beMessenger *)p->_messenger, 0);
                mx = igProperty_GetRecord((igObject *)n, BIT_5)->_data;
                t = mx + p->_editBit;
                igProperty_GetRecord((igObject *)n, BIT_5)->_data = t;
                p->_st2 = p->_st2 + 1;
                p->_st3 = 0;
                return;
            }
            break;
        case 3:
            al = (int)WindowAllocator(p);
            {
            igSmartPointer<beNDMWShopSelect00> r110((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
            beNDMWWindow_BindContext((beNDMWWindow *)r110.p, (igObject *)p, p->_insight, p->_playerNo, 0);
            ((Gap::Core::igObjectList *)p->_subWindow)->append((Gap::Core::igObject *)r110.p);
            beNDMWWindow_RunMessageScript((beNDMWWindow *)p, txt_status_lua_2, 0x85);
            }
            p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
            p->_st2 = p->_st2 + 1;
            p->_st3 = 0;
            return;
        case 4:
            if (((igObjectList *)p->_subWindow)->_count != p->_nowProcKazu) {
                SEL(TEXTCTL_5); APS(STWINFONT29_3); APS(font000_2); APS(DISPOFF_2); DSP(SWITCH_4);
                SEL(SUBWND_2); API(p->_playerNo); DSP(UPDATE);
                beMessenger_SendNamed((beMessenger *)p->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
                p->_st2 = 0;
                p->_st3 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)p);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)p);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)p);
        k = 0;
        p->_st0 = p->_st0 + 1;
        p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
        do {
            sprintf((char *)clearCellText, font_03d, k);
            SEL(TEXTCTL_5); APS(STWINFONT28); APS(clearCellText); APS(DISPOFF_2); DSP(SWITCH_4);
            k += 1;
        } while (k < 7);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)p) != 0) {
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
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_sttitle, 0, SQ_OPEN_5, 0);
        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 90);
        self->_skillMenu = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st1) {
        case 0: {
            igSmartPointer<beNDMWStatusSelect01> wr((beNDMWStatusSelect01 *)beNDMWStatusSelect01_Create((int)WindowAllocator(self)));
            beNDMWWindow_BindContext((beNDMWWindow *)(int)wr.p, (igObject *)self, self->_insight, self->_playerNo, 91);
            ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)wr.p);
            wr.p->_startPoint = self->_skillMenu;
            beNDMWWindow_QueueText((beNDMWWindow *)wr.p, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
            
            }
            self->_nowProcKazu = SW(self->_subWindow)->_count;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            if (self->_retCode != -1)
                beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, self->_retCode + 98);
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
                beNDMWShinkaCtrl_Setup((beNDMWShinkaCtrl *)self->_shinkaCtrl, self->_insight, self->_playerNo);
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
                    float b[3];
                    float a[3];
                    if (self->_maxPage > 1)
                        model = SQ_BWINONOPEN;
                    else
                        model = SQ_BWINOFFOPEN;
                    a[0] = 127.0f;
                    a[1] = 65.0f;
                    a[2] = 0.0f;
                    b[0] = -146.0f;
                    b[1] = 65.0f;
                    b[2] = 0.0f;
                    AsListCtrl(self)->PresentPageArrows(b, a);
                    break;
                }
                case 1:
                    model = SQ_BWINOFFOPEN;
                    break;
                case 2:
                    model = SQ_WAZAOPEN;
                    break;
                }
                beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stfolder, 0, (const char *)model, SQ_CLOSE_3);
                igSmartPointer<beNDMWStatusSelectE1> wr((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)WindowAllocator(self)));
                beNDMWWindow_BindContext((beNDMWWindow *)(int)wr.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)wr.p);
                { beNDMWStatusSelectE1 *t = wr.p; t->_offsetPos[0] = -121.0f;
                t->_offsetPos[1] = 128.0f;
                t->_offsetPos[2] = 0.0f; }
                wr.p->_startPoint = 0;
                StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT13).ref());
                StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
                beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, self->_skillMenu + 95);
                switch (self->_skillMenu) {
                case 0: {
                    int n;
                    int i;
                    igObjectList *sl = SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list);
                    if (self->_maxPage > 1) {
                        n = 8;
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT24, g_statusFontNames[0], space, CENTER_2);
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT24, g_statusFontNames[1], space, CENTER_2);
                    } else {
                        if (sl->_count == 0) n = 2; else n = sl->_count;
                    }
                    for (i = 0; i < n; i++) {
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, g_statusFontNames[i], space, LEFT_3);
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT42, g_statusFontNames[i], space, LEFT_3);
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT18, g_statusFontNames[i], space, RIGHT_2);
                    }
                    beNDMWStatusCtrlSkill_RefreshText((beNDMWStatusCtrlSkill *)self, 1, 0);
                    wr.p->_selectMax = n;
                    break;
                }
                case 1: {
                    int obj;
                    igObjectList *recs;
                    int level;
                    int limit;
                    int i;
                    char buf[24];
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
                    obj = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                    recs = (igObjectList *)igProperty_GetRecordIntList((igObject *)obj, SKILL_2)->_data;
                    level = igProperty_GetRecord((igObject *)obj, LEVEL_3)->_data;
                    limit = SkillLimitForLevel(level);
                    for (i = 0; i < recs->_count; i++) {
                        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT14_2).ref());
                        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[i]).ref());
                        sprintf(buf, percent_d_3, ((int *)recs->_data)[i]);
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT18, g_statusFontNames[i], buf, RIGHT_2);
                        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)(void *)g_statusFontNames[i]);
                        if (((int *)recs->_data)[i] >= limit) {
                            float col[3];
                            col[0] = 0.9f;
                            col[1] = 0.4f;
                            col[2] = 0.2f;
                            beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)col);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, COLOR);
                        } else {
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, DEFAULTCOLOR_2);
                        }
                    }
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 101);
                    wr.p->_selectMax = recs->_count;
                    break;
                }
                case 2: {
                    igObjectList *recs;
                    int ctx;
                    int i;
                    int n;
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
                    beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
                    recs = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), WAZALIST_2)->_data;
                    ctx = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                    for (i = 0; i < recs->_count; i++) {
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, g_statusFontNames[i],
                                     (const char *)(void *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)((int *)recs->_data)[i], (beNDMWStatus *)ctx, NAME_3),
                                     LEFT_3);
                    }
                    n = *(unsigned *)&recs->_count;
                    if (n == 0)
                        wr.p->_selectMax = 1;
                    else
                        wr.p->_selectMax = n;
                    break;
                }
                }
                beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT29_3, g_statusFontNames[0], space, LEFT_3);
                
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
                            if (found && ((Gap::Core::igObject *)found)->isOfType(g_beNDMWStatusSelectE1_metaObject)) {
                                found = (int)(int *)found;
                            } else
                                found = 0;
                            if (found)
                                break;
                        }
                        if (found) {
                            bool ok = false;
                            if (beNDMWWindowSelect_CanRequestFO2TOP((beNDMWWindowSelect *)found)) {
                                if (AsListCtrl(self)->PrevPage())
                                    ok = true;
                                else if (AsListCtrl(self)->NextPage())
                                    ok = true;
                            }
                            if (ok) {
                                beNDMWStatusSelectE1 *f = (beNDMWStatusSelectE1 *)found;
                                f->_st0 = 4;
                                f->_st3 = 0;
                                f->_st2 = 0;
                                f->_st1 = 0;
                                switch (self->_nowPage) {
                                default:
                                    f->_selectMax = 8;
                                    break;
                                case 1:
                                    f->_selectMax = SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list)->_count - 8;
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
                            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)(void *)g_statusFontNames[i]);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, DEFAULTCOLOR_2);
                        }
                    }
                    beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
                    ClearStringRefList(self->_modelCloseInfoNameList);
                    SW(self->_modelCloseRamNoList)->_count = 0;
                    ClearStringRefList(self->_modelCloseSeqNameList);
                    beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        beNDMWWindow_SendModelSequence((beNDMWWindow *)self, i_sttitle, 0, SQ_CLOSE_3);
        beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
        beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT12);
        beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)(void *)g_statusFontNames[0]);
        beMessenger_AppendString((beMessenger *)self->_messenger, DISPOFF_2);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self))
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
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                    beMessenger_AppendString((beMessenger *)self->_messenger, *font);
                    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)name);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT42);
                    beMessenger_AppendString((beMessenger *)self->_messenger, *font);
                    beMessenger_AppendString((beMessenger *)self->_messenger, Lv);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                    sprintf(cost, percent_d_3, ((beNDMWShinkaObject **)list->_data)[index]->_level);
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT18);
                    beMessenger_AppendString((beMessenger *)self->_messenger, *font);
                    beMessenger_AppendString((beMessenger *)self->_messenger, cost);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                    text = DISPON_2;
                } else {
                    text = DISPOFF_2;
                }
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                beMessenger_AppendString((beMessenger *)self->_messenger, *font);
                beMessenger_AppendString((beMessenger *)self->_messenger, text);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT42);
                beMessenger_AppendString((beMessenger *)self->_messenger, *font);
                beMessenger_AppendString((beMessenger *)self->_messenger, text);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT18);
                beMessenger_AppendString((beMessenger *)self->_messenger, *font);
                beMessenger_AppendString((beMessenger *)self->_messenger, text);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_4);
                row++;
                font++;
            } while (row < 8);
            if (self->_maxPage > 1) {
                page[1] = 0;
                pg = self->_nowPage; pg += 0x31; page[0] = pg;
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT24);
                beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
                beMessenger_AppendString((beMessenger *)self->_messenger, page);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                pg2 = self->_maxPage; pg2 += 0x30; page[0] = pg2;
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT24);
                beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[1]);
                beMessenger_AppendString((beMessenger *)self->_messenger, page);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
            }
        }
        if (refreshText != 0) {
            switch (self->_skillMenu) {
            case 0:
                beMessenger_SendNamed((beMessenger *)self->_messenger, DATABASE_7, shinka_3, 0, GETDATABASE_7);
                name = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                list = (igObjectList *)((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list;
                index = self->_nowPage << 3; index += self->_retCode;
                if (list->_count > 0 && index < list->_count) {
                    text = (char *)beDataBase_GetRecordString((beDataBase *)name, ((beNDMWShinkaObject **)list->_data)[index]->_id, EXPLANATION);
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
                    beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
                    beMessenger_AppendString((beMessenger *)self->_messenger, text);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                }
                break;
            case 1:
                beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, self->_retCode + 111);
                break;
            case 2:
                beMessenger_SelectGroup((beMessenger *)self->_messenger, GAMERAM_9);
                beMessenger_AppendInt((beMessenger *)self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETPLAYER_6);
                list = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), WAZALIST_2)->_data;
                text = (char *)beNDMWItemBase_GetRecordString((beNDMWItemBase *)((int *)list->_data)[self->_retCode], (beNDMWStatus *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject), TXT_2);
                beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT29_3);
                beMessenger_AppendString((beMessenger *)self->_messenger, g_statusFontNames[0]);
                beMessenger_AppendString((beMessenger *)self->_messenger, text);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, TEXTSET_3);
                break;
            }
        }
    }
}

/* The select windows made here are beNDMWStatusSelectE1 and beNDMWStatusSelectE0; their
 * +84/+88/+100 words are _selectMax, _offsetPos (an igVec3f: two floats and a zero word, reflected
 * as int[3]) and _startPoint. */







void beNDMWStatusSubMenu_Update(beNDMWStatusSubMenu *self)
{
    ModelNameTable tq;
    igVec3f vec;
    CellNameRow names;
    float v0[3];
    float vecb[3];
    float vF[3];
    float v100[3];
    float v110[3];
    switch (self->_st0) {
    case 0: {
        void *al;
        static const ModelNameTable models = {{SQ_OPEN00, SQ_OPEN01, SQ_OPEN02, SQ_OPEN03, SQ_OPEN04, SQ_OPEN05, SQ_OPEN06, SQ_OPEN07, SQ_OPEN08, SQ_OPEN09, SQ_OPEN10, SQ_OPEN11}};
        tq = models;

        v0[0] = -121.0f; v0[1] = 128.0f; v0[2] = 0.0f;
        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, tq.v[self->_entCode % 12], SQ_CLOSE_3, (float *)v0);
        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_3LINEOPEN, SQ_CLOSE_3);
        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT26).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT26).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[1]).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT26).ref());
        StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(g_statusFontNames[2]).ref());
        beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x43);
        GET_ALLOC(al)
        { igSmartPointer<beNDMWStatusSelectE1> menuWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
        beNDMWWindow_BindContext((beNDMWWindow *)menuWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
        ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)menuWin.p);
        WSETI84(menuWin.p, 3)
        WSETPOS(menuWin.p, 115.0f, 145.0f, 0.0f)
        WSETI100(menuWin.p, 0)
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
                { igSmartPointer<beNDMWShopSelect00> messageWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)messageWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)messageWin.p);
                StringList_AppendRetained((igStringRefList *)((beNDMWShopSelect00 *)messageWin.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
                StringList_AppendRetained((igStringRefList *)((beNDMWShopSelect00 *)messageWin.p)->_textCloseNameList, igStringRef(font000_2).ref());
                MSG_SELECT_INT(self->_playerNo)
                rec = igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DEVICEFOLDER_3);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec->_data)->_data)[self->_selectDevice];
                ctx = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                if (item->_isEquip != 0) {
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)messageWin.p, txt_status_lua_2, 0x90);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else if ((item->_kindNo == 0) == 1 && !(beNDMWItemBase_GetRecordBool(item, (beNDMWStatus *)ctx, ISHAKAI) & 0xFF)) {
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)messageWin.p, txt_status_lua_2, 0x91);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else {
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)messageWin.p, txt_status_lua_2, 0x4E);
                    NEXT_ST2()
                }
                }
                SYNC_COUNT()
            }
            case 1:
                if (WIN_PENDING()) {
                    void *al;

                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWStatusSelectE0> yesNoWin((beNDMWStatusSelectE0 *)beNDMWStatusSelectE0_Create((int)al));
                    beNDMWWindow_BindContext((beNDMWWindow *)yesNoWin.p, (igObject *)self, self->_insight, self->_playerNo, 0x4F);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)yesNoWin.p);
                    WSETI84(yesNoWin.p, 2)
                    }
                    SYNC_COUNT()
                    NEXT_ST2()
                case 2:
                    if (WIN_PENDING()) {
                        if (self->_retCode == 0) {
                            beDataObjObjectList *rec;
                            MSG_SELECT_INT(self->_playerNo)
                            rec = igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DEVICEFOLDER_3);
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
            obj = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
            L = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, DEVICEFOLDER_3)->_data;
            GET_ALLOC(al)
            { ItemListRef keptItems(beNDMWItemBaseList_Create((int)al));
            a7 = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, POWERSOCKET_3)->_data;
            a8 = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, MAINSLOT_3)->_data;
            aA = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, SUBSLOT_3)->_data;
            a5 = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, POWERPOCKET_3)->_data;
            a6 = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, MAINPOCKET_3)->_data;
            beNDMWStatusSubMenu_SortByRecordNo(self, ItemListRef(L));
            Helpers::AppendBoth(keptItems, a7, a5);
            Helpers::AppendBoth(keptItems, a8, a6);
            for (k = 0; k < aA->_count; k++) {
                int *e = (int *)((int *)aA->_data)[k];
                if (e != 0) ((Gap::Core::igObjectList *)keptItems.p)->append((Gap::Core::igObject *)e);
            }
            for (i = 0; i < ((igObjectList *)keptItems.p)->_count; i++)
                ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)L))->removeByValue((Gap::Core::igObject *)((int *)((igObjectList *)keptItems.p)->_data)[i], 0);
            GET_ALLOC(al) ItemListRef kind0Items(beNDMWItemBaseList_Create((int)al));
            GET_ALLOC(al) ItemListRef kind1Items(beNDMWItemBaseList_Create((int)al));
            GET_ALLOC(al) ItemListRef kind2Items(beNDMWItemBaseList_Create((int)al));
            GET_ALLOC(al) ItemListRef kind3Items(beNDMWItemBaseList_Create((int)al));
            if (L->_count > 0) do {
                beNDMWItemBase *e = (beNDMWItemBase *)((int *)L->_data)[0];
                int t = e->_kindNo;
                if (t == 0) ((Gap::Core::igObjectList *)kind0Items.p)->append((Gap::Core::igObject *)e);
                else if (t == 1) ((Gap::Core::igObjectList *)kind1Items.p)->append((Gap::Core::igObject *)e);
                else if (t == 2) ((Gap::Core::igObjectList *)kind2Items.p)->append((Gap::Core::igObject *)e);
                else if (t == 3) ((Gap::Core::igObjectList *)kind3Items.p)->append((Gap::Core::igObject *)e);
                else igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                LIST_REMOVE(L, 0)
            } while (L->_count > 0);
            beNDMWStatusSubMenu_SortByRevision(self, ItemListRef((igObjectList *)kind0Items.p));
            beNDMWStatusSubMenu_SortByRevision(self, ItemListRef((igObjectList *)kind1Items.p));
            beNDMWStatusSubMenu_SortByRevision(self, ItemListRef((igObjectList *)kind2Items.p));
            beNDMWStatusSubMenu_SortByRecordNo(self, ItemListRef((igObjectList *)kind3Items.p));
            while (((igObjectList *)keptItems.p)->_count > 0) { ((Gap::Core::igObjectList *)L)->append((Gap::Core::igObject *)((int *)((igObjectList *)keptItems.p)->_data)[0]); LIST_REMOVE(keptItems.p, 0) }
            while (((igObjectList *)kind0Items.p)->_count > 0) { ((Gap::Core::igObjectList *)L)->append((Gap::Core::igObject *)((int *)((igObjectList *)kind0Items.p)->_data)[0]); LIST_REMOVE(kind0Items.p, 0) }
            while (((igObjectList *)kind1Items.p)->_count > 0) { ((Gap::Core::igObjectList *)L)->append((Gap::Core::igObject *)((int *)((igObjectList *)kind1Items.p)->_data)[0]); LIST_REMOVE(kind1Items.p, 0) }
            while (((igObjectList *)kind2Items.p)->_count > 0) { ((Gap::Core::igObjectList *)L)->append((Gap::Core::igObject *)((int *)((igObjectList *)kind2Items.p)->_data)[0]); LIST_REMOVE(kind2Items.p, 0) }
            while (((igObjectList *)kind3Items.p)->_count > 0) { ((Gap::Core::igObjectList *)L)->append((Gap::Core::igObject *)((int *)((igObjectList *)kind3Items.p)->_data)[0]); LIST_REMOVE(kind3Items.p, 0) }
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
                rec = igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DEVICEFOLDER_3);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec->_data)->_data)[self->_selectDevice];
                ctx = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                for (i = 0; i < 4; i++) {
                    MSG_SELECT_INT(i)
                    if (igProperty_GetRecordByte(beMessenger_GetObject((beMessenger *)self->_messenger, 0), ISUSE_7)->_data != 0 && i != self->_playerNo) {
                        nN = ((igDataList *)(self->_playerNoList))->_count; lL = (igDataList *)(self->_playerNoList);
                        if (nN < lL->_capacity) lL->_count = ListCount(lL) + 1; else ((Gap::Core::igDataList *)lL)->resizeAndSetCount(nN + 1, 4);
                        ((int *)lL->_data)[nN] = i;
                    }
                }
                flag = false;
                if (item->_isEquip != 0) {
                    flag = true;
                    self->_st3 = 0x92;
                } else if (!(beNDMWItemBase_GetRecordBool(item, (beNDMWStatus *)ctx, ISJYOUDO) & 0xFF)) {
                    flag = true;
                    self->_st3 = 0x93;
                } else if (((igObjectList *)self->_playerNoList)->_count == 0) {
                    flag = true;
                    self->_st3 = 0x94;
                }
                if (flag) {
                    void *al;

                    GET_ALLOC(al)
                    { igSmartPointer<beNDMWShopSelect00> refusalWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                    beNDMWWindow_BindContext((beNDMWWindow *)refusalWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)refusalWin.p);
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)refusalWin.p, txt_status_lua_2, self->_st3);
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
                        beNDMWWindow_SendModelSequence((beNDMWWindow *)self, i_stcursor04, 0, SQ_CLOSE_3);
                        NEXT_ST2()
                    } else {
                        NEXT_ST0()
                    }
                    beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
                    return;
                }
                break;
            }
            case 1:
                if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self->_deviceFolderList) != 0) {
                    int cnt;
                    beDataObjObjectList *rec;
                    beNDMWItemBase *item;
                    int i;
                    beNDMWLoadIntf2_igObject_Retain(0);
                    beNDMWLoadIntf2_igObject_Release((igObject *)self->_deviceFolderList);
                    self->_deviceFolderList = 0;
                    cnt = ((igObjectList *)self->_playerNoList)->_count;
                    switch (cnt) {
                    case 1:
                    default:
                        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_1CHIPOPEN, SQ_CLOSE_3);
                        break;
                    case 2:
                        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_2CHIPOPEN, SQ_CLOSE_3);
                        break;
                    case 3:
                        beNDMWWindow_PresentModelAtOrigin((beNDMWWindow *)self, i_stmenu02, 0, SQ_3CHIPOPEN, SQ_CLOSE_3);
                        break;
                    }
                    StringList_AppendRetained((igStringRefList *)self->_textCloseTypeList, igStringRef(STWINFONT39).ref());
                    StringList_AppendRetained((igStringRefList *)self->_textCloseNameList, igStringRef(font000_2).ref());
                    beNDMWWindow_RunMessageScript((beNDMWWindow *)self, txt_status_lua_2, 0x49);
                    MSG_SELECT_INT(self->_playerNo)
                    rec = igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DEVICEFOLDER_3);
                    {
                        igObjectList *dl = (igObjectList *)rec->_data;
                        int cx = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beNDMWStatus_metaObject);
                        item = (beNDMWItemBase *)((int *)dl->_data)[self->_selectDevice];
                        beNDMWWindow_QueueText((beNDMWWindow *)self, STWINFONT14_2, font000_2, (const char *)beNDMWItemBase_GetRecordString(item, (beNDMWStatus *)cx, NAME_3), LEFT_3);
                    }
                    beNDMWItemBase_GetRevisionColor(&vec, item);
                    beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
                    beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
                    beMessenger_AppendString((beMessenger *)self->_messenger, font000_2);
                    vecb[0] = vec[0]; vecb[1] = vec[1]; vecb[2] = vec[2];
                    beMessenger_AppendVec3((beMessenger *)self->_messenger, (float *)vecb);
                    beMessenger_DispatchSelected((beMessenger *)self->_messenger, COLOR);
                    static const CellNameRow playerCells = {{font001_2, font002_2, font003_2}};
                    names = playerCells;
                    for (i = 0; i < ((igObjectList *)self->_playerNoList)->_count; i++) {
                        int pno = ((int *)((igObjectList *)self->_playerNoList)->_data)[i];
                        int obj;
                        igObjectList *folder;
                        igObjectList *lst;
                        int c;
                        MSG_SELECT_INT(pno)
                        obj = (int)beMessenger_GetObject((beMessenger *)self->_messenger, 0);
                        folder = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, DEVICEFOLDER_3)->_data;
                        lst = (igObjectList *)igProperty_GetRecordFolder((igObject *)obj, PLAYERNAME_3)->_data;
                        if (lst->_count > 0) {
                            DeviceRef firstDevice((void *)*(int *)lst->_data, kRetainReference);
                            beNDMWWindow_QueueObjectText((beNDMWWindow *)self, STWINFONT14_2, names.v[i], (const igSmartPointer<igObject> &)DeviceRef(firstDevice), LEFT_3);
                        }
                        c = folder->_count;
                        LIST_ADD(self->_playerDeviceCnt, c)
                    }
                    NEXT_ST2()
                    return;
                }
                break;
            case 2: {
                void *al;

                GET_ALLOC(al)
                { igSmartPointer<beNDMWStatusSelectE1> playerWin((beNDMWStatusSelectE1 *)beNDMWStatusSelectE1_Create((int)al));
                beNDMWWindow_BindContext((beNDMWWindow *)playerWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)playerWin.p);
                WSETPOS(playerWin.p, -121.0f, 109.0f, 0.0f)
                WSETI84(playerWin.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100(playerWin.p, self->_receipt)
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
                    { igSmartPointer<beNDMWShopSelect00> resultWin((beNDMWShopSelect00 *)beNDMWShopSelect00_Create((int)al));
                    beNDMWWindow_BindContext((beNDMWWindow *)resultWin.p, (igObject *)self, self->_insight, self->_playerNo, 0);
                    ((Gap::Core::igObjectList *)self->_subWindow)->append((Gap::Core::igObject *)resultWin.p);
                    SYNC_COUNT()
                    NEXT_ST2()
                    self->_st3 = -1;
                    StringList_AppendRetained((igStringRefList *)((beNDMWShopSelect00 *)resultWin.p)->_textCloseTypeList, igStringRef(STWINFONT29_3).ref());
                    StringList_AppendRetained((igStringRefList *)((beNDMWShopSelect00 *)resultWin.p)->_textCloseNameList, igStringRef(g_statusFontNames[0]).ref());
                    self->_receipt = self->_retCode;
                    if (((int *)((igObjectList *)self->_playerDeviceCnt)->_data)[self->_receipt] >= 0x24) {
                        beNDMWWindow_RunMessageScript((beNDMWWindow *)resultWin.p, txt_status_lua_2, 0x95);
                    } else {
                        beDataObjObjectList *rec;
                        igObjectList *l;

                        int idx, val;
                        beNDMWWindow_RunMessageScript((beNDMWWindow *)resultWin.p, txt_status_lua_2, 0x83);
                        MSG_SELECT_INT(self->_playerNo)
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DEVICEFOLDER_3)->_data;
                        MovedItemRef movedItem((void *)((int *)l->_data)[self->_selectDevice]);
                        idx = self->_selectDevice;
                        LIST_REMOVE(l, idx)
                        val = ((int *)((igObjectList *)self->_playerNoList)->_data)[self->_receipt];
                        MSG_SELECT_INT(val)
                        ((Gap::Core::igObjectList *)(igProperty_GetRecordFolder(beMessenger_GetObject((beMessenger *)self->_messenger, 0), DEVICEFOLDER_3)->_data))->append((Gap::Core::igObject *)movedItem.p);
                    }
                    switch (self->_retCode) {
                    case 0: {
                        vF[0] = -121.0f; vF[1] = 109.0f; vF[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, SQ_OPEN00, (const char *)0, (float *)vF);
                        break;
                    }
                    case 1: {
                        v100[0] = -121.0f; v100[1] = 109.0f; v100[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, SQ_OPEN01, (const char *)0, (float *)v100);
                        break;
                    }
                    case 2: {
                        v110[0] = -121.0f; v110[1] = 109.0f; v110[2] = 0.0f;
                        beNDMWWindow_PresentModel((beNDMWWindow *)self, i_stcursor04, 0, SQ_OPEN02, (const char *)0, (float *)v110);
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
                    beMessenger_SendNamed((beMessenger *)self->_messenger, MODELCTRL_3, i_stcursor04, 0, SQ_CLOSE_3);
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
        beNDMWWindow_PlayQueuedModelClose((beNDMWWindow *)self);
        beNDMWWindow_ClearQueuedText((beNDMWWindow *)self);
        beNDMWWindow_RequestChildrenClose((beNDMWWindow *)self);
        if (self->_st3 == -1) {
            beMessenger_SelectGroup((beMessenger *)self->_messenger, TEXTCTL_5);
            beMessenger_AppendString((beMessenger *)self->_messenger, STWINFONT14_2);
            beMessenger_AppendString((beMessenger *)self->_messenger, font000_2);
            beMessenger_DispatchSelected((beMessenger *)self->_messenger, DEFAULTCOLOR_2);
        }
        NEXT_ST0()
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete((beNDMWWindow *)self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}

/* Releases entry i of an object list and closes the gap, clearing the vacated last word. */
static inline void RemoveItemAt(igObjectList *l, int i)
{
    ReleaseObject(((igObject **)l->_data)[i]);
    List_RemoveWordAt((igDataList *)l, i);
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
    ItemListRef sorted(beNDMWItemBaseList_Create((int)al));
    /* matching construct: variant sweep — the list is re-read from the holder in each loop test, so its count loads on every pass */
    while ((l = (igObjectList *)items.p)->_count > 0) {
        best = ((beNDMWItemRevisionBase **)l->_data)[0];
        for (i = 1; i < (l = (igObjectList *)items.p)->_count; i++) {
            t = ((beNDMWItemRevisionBase **)l->_data)[i];
            if (t->_revision > best->_revision) best = t;
        }
        ((Gap::Core::igObjectList *)sorted.p)->append((Gap::Core::igObject *)best);
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)items.p))->removeByValue((Gap::Core::igObject *)(int)best, 0);
    }
    n = l->_count;
    for (i2 = 0; i2 < n; i2++) ReleaseObject(((igObject **)l->_data)[i2]);
    c = l->_count;
    for (j = 0; j < c; j++) ((int *)l->_data)[j] = 0;
    l->_count = 0;
    while ((src = (igObjectList *)sorted.p)->_count > 0) {
        ((Gap::Core::igObjectList *)items.p)->append((Gap::Core::igObject *)((int *)src->_data)[0]);
        RemoveItemAt((igObjectList *)sorted.p, 0);
    }
    for (k = ((igObjectList *)items.p)->_count - 1; k > -1; k--) {
        beNDMWItemBase *e = ((beNDMWItemBase **)((igObjectList *)items.p)->_data)[k];
        if ((e->_kindNo == 0 && e->_recNo == 276) || (e->_kindNo == 1 && e->_recNo == 31) || (e->_kindNo == 2 && e->_recNo == 44)) {
            ((Gap::Core::igObjectList *)items.p)->append((Gap::Core::igObject *)e);
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
    ItemListRef sorted(beNDMWItemBaseList_Create((int)al));
    /* matching construct: variant sweep — the list is re-read from the holder in each loop test, so its count loads on every pass */
    while ((l = (igObjectList *)items.p)->_count > 0) {
        best = ((beNDMWItemBase **)l->_data)[0];
        for (i = 1; i < (l = (igObjectList *)items.p)->_count; i++) {
            t = ((beNDMWItemBase **)l->_data)[i];
            if (t->_recNo < best->_recNo) best = t;
        }
        ((Gap::Core::igObjectList *)sorted.p)->append((Gap::Core::igObject *)best);
        ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)items.p))->removeByValue((Gap::Core::igObject *)(int)best, 0);
    }
    n = l->_count;
    for (i2 = 0; i2 < n; i2++) ReleaseObject(((igObject **)l->_data)[i2]);
    c = l->_count;
    for (j = 0; j < c; j++) ((int *)l->_data)[j] = 0;
    l->_count = 0;
    while ((src = (igObjectList *)sorted.p)->_count > 0) {
        ((Gap::Core::igObjectList *)items.p)->append((Gap::Core::igObject *)((int *)src->_data)[0]);
        RemoveItemAt((igObjectList *)sorted.p, 0);
    }
}

int beNDMWStatusSubMenu_GetMeta(void)
{
    return (int)g_beNDMWStatusSubMenu_metaObject;
}

int beNDMWStatusCtrlSkill_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlSkill_metaObject;
}

int beNDMWStatusCtrlSendBit_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlSendBit_metaObject;
}

int beNDMWStatusCtrlBit_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlBit_metaObject;
}

int beNDMWStatusCtrlDisk_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlDisk_metaObject;
}

int beNDMWStatusCtrlFlag_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlFlag_metaObject;
}

int beNDMWStatusCtrlFolder_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlFolder_metaObject;
}

int beNDMWStatusCtrlD0_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlD0_metaObject;
}

/* Class meta-object handle getter */
int beNDMWStatusSubSlot_GetMeta(void)
{
    return (int)g_beNDMWStatusSubSlot_metaObject;
}

/* Class metaObject accessor */
int beNDMWStatusMainSlot_GetMeta(void) {
    return (int)g_beNDMWStatusMainSlot_metaObject;
}

int beNDMWStatusPowerSocket_GetMeta(void)
{
    return (int)g_beNDMWStatusPowerSocket_metaObject;
}

int beNDMWStatusCtrlBaseEquip_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlBaseEquip_metaObject;
}

int beNDMWStatusCtrlEquip_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrlEquip_metaObject;
}

int beNDMWStatusCtrl00_GetMeta(void)
{
    return (int)g_beNDMWStatusCtrl00_metaObject;
}

int beNDMWListCtrl_GetMeta(void)
{
    return (int)g_beNDMWListCtrl_metaObject;
}

