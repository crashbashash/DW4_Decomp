/* 0x003e9430 - Gap__Bec__beNDMWLoadIntf2__vfunc_34 (typed attempt 1) */
#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
void *beBaseInfoDataList_Create(...);
void *FUN_003c27c0(...);
void *FUN_003c2e60(...);
void *FUN_003c31e0(...);
void *FUN_003c3560(...);
void *FUN_003c3900(...);
void *FUN_003c3e40(...);
void *FUN_003c40c0(...);
void *FUN_003c43c0(...);
int FUN_003c46a0(...);
void *FUN_003c6b00(...);
void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
void *beNDMWLoadIntf2TextOrder_Create(...);
int FUN_003d9de0(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
void *beMessenger_GetObject(...);
unsigned int beMessenger_ResolveEnumValue(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beMessenger_SetInt(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
void *igProperty_FindByName(...);
extern float DAT_004cd0a0[];
extern float DAT_004cd0a4[];
extern float DAT_004cd0a8[];
extern int DAT_005172a0[4];
extern int DAT_005172b0[4];
extern int DAT_005172b8[4];
extern int DAT_005172c0[4];
extern int DAT_005172d0[4];
extern int DAT_005172e8[4];
extern int DAT_005172f8[4];
extern int DAT_00517338[4];
extern int DAT_005175f8[4];
extern int DAT_00517608[4];
extern int DAT_00517618[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern int DAT_00587d08[4];
extern int DAT_00588518[4];
extern int DAT_00589208[4];
extern unsigned char GPR_00554c14;

int Gap__Bec__beNDMWLoadIntf2__vfunc_34(beNDMWLoadIntf2 *self, void *ctx, void *msg);
}

struct Rc { int w0; int references; };
/* Owning stack references to the freshly created controller objects while the list is wired up: each releases its
 * object on scope exit (reference count in the low 23 bits of references).  One class per retail destructor copy:
 * DataListRef 0x0033e9c0 (the property list, also the ensure-list temporaries), CtrlDataRef 0x003eb980,
 * ItemListRef 0x003eb900, ComMdlRef 0x003eb880, TextOrderRef 0x003eb800, SelSlotRef 0x003eb780, NameSelRef 0x003eb700,
 * MesWinRef 0x003eb680, DegiStateRef 0x003eb600, StatDataRef 0x003eb580 (both stat entries), DataSelRef 0x003eb500,
 * DiffSelRef 0x003eb480 (duplicates in config/SLUS-20836/unit-objects.json). */
class DataListRef {
public:
    Rc *p;
    DataListRef(Rc *o) : p(o) {}
    ~DataListRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class CtrlDataRef {
public:
    Rc *p;
    CtrlDataRef(Rc *o) : p(o) {}
    ~CtrlDataRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class ItemListRef {
public:
    Rc *p;
    ItemListRef(Rc *o) : p(o) {}
    ~ItemListRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class ComMdlRef {
public:
    Rc *p;
    ComMdlRef(Rc *o) : p(o) {}
    ~ComMdlRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class TextOrderRef {
public:
    Rc *p;
    TextOrderRef(Rc *o) : p(o) {}
    ~TextOrderRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class SelSlotRef {
public:
    Rc *p;
    SelSlotRef(Rc *o) : p(o) {}
    ~SelSlotRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class NameSelRef {
public:
    Rc *p;
    NameSelRef(Rc *o) : p(o) {}
    ~NameSelRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class MesWinRef {
public:
    Rc *p;
    MesWinRef(Rc *o) : p(o) {}
    ~MesWinRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DegiStateRef {
public:
    Rc *p;
    DegiStateRef(Rc *o) : p(o) {}
    ~DegiStateRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class StatDataRef {
public:
    Rc *p;
    StatDataRef(Rc *o) : p(o) {}
    ~StatDataRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DataSelRef {
public:
    Rc *p;
    DataSelRef(Rc *o) : p(o) {}
    ~DataSelRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DiffSelRef {
public:
    Rc *p;
    DiffSelRef(Rc *o) : p(o) {}
    ~DiffSelRef() { Rc *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Ctx { int p0; int p4; int kind; int p12[7]; Rc *list; };
struct Msg { int p[5]; int f20; };
struct Ent { char p[13]; unsigned char b13; };
struct Arr { char p[16]; Ent **f16; };
struct Rec { char p[40]; Arr *f40; };

#define ALLOC(a, o) { a = igObject_GetAllocator(o); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }
#define REL(o) { Rc *rr = (o); if (rr != 0) { rr->references = rr->references - 1; if (((unsigned long long)((long long)rr->references << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
/* Installs a freshly created property list into the controller context: retain the new list, release the old one,
 * store.  The owning reference to the new list is the caller's temporary (retail keeps one stack slot per use). */
struct ListInstall { static inline void go(Ctx *o, const DataListRef &fresh) {
    Rc *n = fresh.p;
    if (n != 0) n->references = n->references + 1;
    REL(o->list)
    o->list = n;
} };
#define ENSURE(o) { void *al; ALLOC(al, o) ListInstall::go(o, DataListRef((Rc *)beBaseInfoDataList_Create(al))); }
#define FIND(n) igProperty_FindByName(a1->list, DAT_00585be0[0], &n[0])

#pragma opt_propagation off
int Gap__Bec__beNDMWLoadIntf2__vfunc_34(beNDMWLoadIntf2 *self, void *ctx, void *msg) {
    Ctx *a1 = (Ctx *)ctx;
    Msg *a2 = (Msg *)msg;
    void *al;
    unsigned int v;
    void *s0;
    void *s4;
    void *s3;
    void *s0b;
    void *s4b;
    int k;
    float fx;
    float fy;
    float fz;
    beNDMWLoadIntf2CtrlData *fl;

    v = beMessenger_ResolveEnumValue(self->_messenger, FUN_003c46a0(), a2->f20);
    if (v == 0) {
        if (a1->list == 0) {
            ALLOC(al, self)
            {
            DataListRef spFC((Rc *)beBaseInfoDataList_Create(al));
            { Rc *n = spFC.p; if (n != 0) n->references = n->references + 1; REL(a1->list) a1->list = n; }
            self->_system_ = FUN_00236f80(self->_insight, DAT_00587d08[0]);
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
            k = a1->kind * 3; { beNDMWLoadIntf2ComMdlCtrl *t = (beNDMWLoadIntf2ComMdlCtrl *)spF0.p; 
            float y, z, x; z = DAT_004cd0a8[k]; y = DAT_004cd0a4[k]; x = DAT_004cd0a0[k];
            *(float *)&t->_pos = x;
            *(float *)((char *)t + 32) = y;
            *(float *)((char *)t + 36) = z; }
            }
            ALLOC(al, self)
            {
            TextOrderRef spEC((Rc *)beNDMWLoadIntf2TextOrder_Create(al));
            ((beNDMWLoadIntf2TextOrder *)spEC.p)->_messenger = self->_messenger;
            { beNDMWLoadIntf2TextOrder *t = (beNDMWLoadIntf2TextOrder *)spEC.p; t->_lua = FUN_00236f80(self->_insight, DAT_00589208[0]); }
            ObjectList_AppendRetained(a1->list, spEC.p);
            }
            ALLOC(al, self)
            {
            SelSlotRef spE8((Rc *)FUN_003c2e60(al));
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_ramNo = a1->kind;
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_messenger = self->_messenger;
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_padManager = FUN_00236f80(self->_insight, DAT_00588518[0]);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_comMdlCtrl = (int)FIND(DAT_005172c0);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_textOrder = (int)FIND(DAT_005172e8);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2SelSlot *)spE8.p)->_commonIntf = (int)FIND(DAT_005172a0);
            ObjectList_AppendRetained(a1->list, spE8.p);
            }
            ALLOC(al, self)
            {
            NameSelRef spE4((Rc *)FUN_003c27c0(al));
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_ramNo = a1->kind;
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_messenger = self->_messenger;
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_padManager = FUN_00236f80(self->_insight, DAT_00588518[0]);
            if (a1->list == 0) ENSURE(a1)
            s3 = FIND(DAT_005172c0);
            if (a1->list == 0) ENSURE(a1)
            s0 = FIND(DAT_005172e8);
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_comMdlCtrl = (int)s3;
            ((beNDMWLoadIntf2NameSel *)spE4.p)->_textOrder = (int)s0;
            ObjectList_AppendRetained(a1->list, spE4.p);
            }
            ALLOC(al, self)
            {
            MesWinRef spE0((Rc *)FUN_003c6b00(al));
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_ramNo = a1->kind;
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_messenger = self->_messenger;
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_padManager = FUN_00236f80(self->_insight, DAT_00588518[0]);
            ObjectList_AppendRetained(a1->list, spE0.p);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2MesWin *)spE0.p)->_textOrder = (int)FIND(DAT_005172e8);
            }
            ALLOC(al, self)
            {
            DegiStateRef spDC((Rc *)FUN_003c3900(al));
            ALLOC(al, self)
            {
            StatDataRef spD8((Rc *)FUN_003c3e40(al));
            if (a1->list == 0) ENSURE(a1)
            s0 = FIND(DAT_005172a0);
            if (a1->list == 0) ENSURE(a1)
            s4 = FIND(DAT_005172e8);
            if (a1->list == 0) ENSURE(a1)
            FUN_003d9de0(spD8.p, a1->kind, s0, s4, FIND(DAT_005172c0), self->_messenger, 0);
            ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)spDC.p)->_statDataList, spD8.p);
            }
            ALLOC(al, self)
            {
            StatDataRef spD4((Rc *)FUN_003c3e40(al));
            if (a1->list == 0) ENSURE(a1)
            s0b = FIND(DAT_005172a0);
            if (a1->list == 0) ENSURE(a1)
            s4b = FIND(DAT_005172e8);
            if (a1->list == 0) ENSURE(a1)
            FUN_003d9de0(spD4.p, a1->kind, s0b, s4b, FIND(DAT_005172c0), self->_messenger, 1);
            ObjectList_AppendRetained(((beNDMWLoadIntf2DegiStateCtrl *)spDC.p)->_statDataList, spD4.p);
            }
            ObjectList_AppendRetained(a1->list, spDC.p);
            }
            ALLOC(al, self)
            {
            DataSelRef spD0((Rc *)FUN_003c3560(al));
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_padManager = FUN_00236f80(self->_insight, DAT_00588518[0]);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_comMdlCtrl = (int)FIND(DAT_005172c0);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_textOrder = (int)FIND(DAT_005172e8);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_commonIntf = (int)FIND(DAT_005172a0);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_mesWin = (int)FIND(DAT_005172d0);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2DataSelIntf *)spD0.p)->_statDisp = (int)FIND(DAT_005172f8);
            ObjectList_AppendRetained(a1->list, spD0.p);
            }
            ALLOC(al, self)
            {
            DiffSelRef spCC((Rc *)FUN_003c31e0(al));
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_padManager = FUN_00236f80(self->_insight, DAT_00588518[0]);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_comMdlCtrl = (int)FIND(DAT_005172c0);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_textOrder = (int)FIND(DAT_005172e8);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_commonIntf = (int)FIND(DAT_005172a0);
            if (a1->list == 0) ENSURE(a1)
            ((beNDMWLoadIntf2Diffselect *)spCC.p)->_mesWin = (int)FIND(DAT_005172d0);
            ObjectList_AppendRetained(a1->list, spCC.p);
            }
            }
        }
        return 1;
    }
    if (a1->list == 0) return 1;
    if (a1->list == 0) ENSURE(a1)
    fl = (beNDMWLoadIntf2CtrlData *)FIND(DAT_005172b0);
    if (a1->list == 0) ENSURE(a1)
    FIND(DAT_005172b8);
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
        if (((Rec *)FIND(DAT_005172a0))->f40->f16[a1->kind]->b13 != 1) {
            beMessenger_SelectGroup(self->_messenger, &DAT_00517338[0]);
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

#pragma opt_propagation reset
