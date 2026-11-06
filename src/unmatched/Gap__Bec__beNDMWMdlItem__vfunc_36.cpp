/* Attach the model-item work record to a base-info RAM entry. Creates the per-info data list on
 * first use, creates a beNDMWMdlItemInfoWork under the "item work" property, reads its db id /
 * kind from the messenger arguments, classifies the parent info's name against the ten item-
 * category names (kind 0..2 are plain, 3..9 flag _isNamed), then builds the concrete item object
 * for the db id (ids 0, 1, 2 and 6 take only the record number; 3, 4 and 5 are initialised from
 * the "item roll" record the messenger carries). Ends by running the shared base-info setup
 * (FUN_00396740). */
#include "dw4/reflected.h"
extern "C" {
struct Prop { char pad[20]; igObject *f20; };
struct ParentInfo { int _vtable; unsigned int _refCount; char *_name; };
struct Rec { int p[3]; int f12; };
igObject *beBaseInfoDataList_Create(...);
igObject *FUN_003c13f0(...);
igObject *FUN_003c85b0(...);
igObject *FUN_003c83c0(...);
igObject *FUN_003c8240(...);
igObject *FUN_003c87f0(...);
igObject *FUN_003c8c90(...);
igObject *FUN_003c8b00(...);
igObject *FUN_003c8970(...);
int FUN_004482e0(...);
int FUN_00448430(...);
int FUN_00448580(...);
int FUN_00448660(...);
int FUN_00448710(...);
int FUN_00448ad0(...);
int FUN_00448f00(...);
int FUN_00396740(...);
void *Memory_GetAllocatorBySelector(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
int beMessenger_GetObject(...);
int beMessenger_PopArgContext(...);
int beMessenger_PushArgContext(...);
int beMessenger_SendGroup(...);
void igObject_Destroy(igObject *);
void *igObject_GetAllocator(...);
Prop *igProperty_FindByName(...);
Rec *igProperty_GetRecord(...);
int igStrCmp(...);
extern char *DAT_004cfc10[10];
extern char DAT_004e0858[];
extern int DAT_0051cf58[4];
extern int DAT_0051cf60[4];
extern int DAT_0051cf68[4];
extern int DAT_0051cf78[4];
extern int DAT_00585be0[4];
extern int DAT_00587108[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

/* matching construct: one RAII releasing holder per retail destructor copy (cleanup table 0x546dac: 0x33e9c0 list hold,
 * 0x442010 work record, 0x3b9ba0/0x441f90/0x441f10 item kinds 0..2, 0x3d9bd0/0x3d9d50/0x3d9cd0/0x3d9c50 item kinds 6,3,4,5);
 * the spelling is that of FUN_003d8740's ItemRef.
 * matching construct: the item holders keep `p` volatile so each use reloads it from the frame slot, as retail does. */
#define HOLDER_BODY { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
struct ObjectRef { igObject *p; ObjectRef(igObject *o) : p(o) {} ~ObjectRef() HOLDER_BODY };
struct WorkRef { beNDMWMdlItemInfoWork *p; WorkRef(beNDMWMdlItemInfoWork *o) : p(o) {} ~WorkRef() { igObject *o = (igObject *)p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
struct ItemRef { igObject *volatile p; ItemRef(igObject *o) : p(o) {} ~ItemRef() HOLDER_BODY };
struct ItemRefB { igObject *volatile p; ItemRefB(igObject *o) : p(o) {} ~ItemRefB() HOLDER_BODY };
struct ItemRefC { igObject *volatile p; ItemRefC(igObject *o) : p(o) {} ~ItemRefC() HOLDER_BODY };
template <int K> struct ItemRefK { igObject *volatile p; ItemRefK(igObject *o) : p(o) {} ~ItemRefK() HOLDER_BODY };
#define ALLOC_OF(owner, a, sel) { a = igObject_GetAllocator(owner); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(sel[0]); }
#define ALLOC(a, sel) ALLOC_OF(self, a, sel)
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
/* hold `fresh` (+1), store it in `slot` after dropping the old reference, then drop the hold (-1) */
#define STORE_ITEM(fresh) { igObject *held2 = fresh; beNDMWMdlItemInfoWork *w2 = work.p; if (held2 != 0) held2->_refCount = held2->_refCount + 1; REL((igObject *)w2->_itemObject) w2->_itemObject = (int)held2; }
#define STORE_REF(slot, fresh) { igObject *held2 = fresh; if (held2 != 0) held2->_refCount = held2->_refCount + 1; REL((igObject *)slot) slot = (int)held2; }

struct Store {
    static inline void assign(int &slot, igObject *fresh) {
        igObject *held2 = fresh;
        if (held2 != 0) held2->_refCount = held2->_refCount + 1;
        REL((igObject *)slot)
        slot = (int)held2;
    }
};
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_36(beNDMWMdlItem *self, beBaseInfoRam *info);
void Gap__Bec__beNDMWMdlItem__vfunc_36(beNDMWMdlItem *self, beBaseInfoRam *info) {
    ParentInfo *parent = (ParentInfo *)info->_parentInfo;
    void *alloc;
    Prop *prop;
    igObject *held;
    char *name;
    int i;
    int roll;

    if (info->_dataList == 0) {
        ALLOC_OF(info, alloc, DAT_00587110)
        /* matching construct: the list holder is a temporary of this statement (releases after the store), which takes the lowest frame slot as in retail */
        Store::assign(info->_dataList, ObjectRef(beBaseInfoDataList_Create(alloc)).p);
    }
    prop = igProperty_FindByName((void *)info->_dataList, DAT_00585be0[0], &DAT_0051cf58[0]);
    ALLOC(alloc, DAT_00587110)
    {
    WorkRef work((beNDMWMdlItemInfoWork *)FUN_003c13f0(alloc));
    held = (igObject *)work.p;
    if (held != 0) held->_refCount = held->_refCount + 1;
    REL(prop->f20)
    prop->f20 = held;
    if (beMessenger_GetIntCount(self->_messenger) != 0) {
        work.p->_recNo = beMessenger_GetInt(self->_messenger, 0);
        work.p->_dbId = beMessenger_GetInt(self->_messenger, 1);
    }
    i = 0;
    do {
        name = parent->_name;
        name = name != 0 ? name : DAT_004e0858;
        if (igStrCmp(name, DAT_004cfc10[i]) == 0) {
            work.p->_kind = i;
            break;
        }
        i += 1;
    } while (i < 10);
    {
        beNDMWMdlItemInfoWork *w = work.p;
        if (w->_kind < 3) {
            w->_isNamed = 0;
        } else {
            w->_isNamed = 1;
        }
    }
    switch ((unsigned int)work.p->_dbId) {
    case 0: {
        ALLOC(alloc, DAT_00587108)
        ItemRef h(FUN_003c85b0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448710(h.p, w->_recNo); }
        STORE_ITEM(h.p)
        break;
    }
    case 1: {
        ALLOC(alloc, DAT_00587108)
        ItemRefB h(FUN_003c83c0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448ad0(h.p, w->_recNo); }
        STORE_ITEM(h.p)
        break;
    }
    case 2: {
        ALLOC(alloc, DAT_00587108)
        ItemRefC h(FUN_003c8240(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448f00(h.p, w->_recNo); }
        STORE_ITEM(h.p)
        break;
    }
    case 6: {
        ALLOC(alloc, DAT_00587108)
        ItemRefK<4> h(FUN_003c87f0(alloc));
        { beNDMWMdlItemInfoWork *w = work.p; FUN_00448660(h.p, w->_recNo); }
        STORE_ITEM(h.p)
        break;
    }
    case 3:
    case 4:
    case 5:
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SendGroup(self->_messenger, &DAT_0051cf60[0], &DAT_0051cf68[0]);
        roll = igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051cf78[0])->f12;
        switch ((unsigned int)work.p->_dbId) {
        case 3: {
            ALLOC(alloc, DAT_00587108)
            ItemRefK<1> h(FUN_003c8c90(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; FUN_004482e0(h.p, w->_recNo, self, roll); }
            STORE_ITEM(h.p)
            break;
        }
        case 4: {
            ALLOC(alloc, DAT_00587108)
            ItemRefK<2> h(FUN_003c8b00(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; FUN_00448430(h.p, w->_recNo, self, roll); }
            STORE_ITEM(h.p)
            break;
        }
        case 5: {
            ALLOC(alloc, DAT_00587108)
            ItemRefK<3> h(FUN_003c8970(alloc));
            { beNDMWMdlItemInfoWork *w = work.p; FUN_00448580(h.p, w->_recNo, self, roll); }
            STORE_ITEM(h.p)
            break;
        }
        }
        beMessenger_PopArgContext(self->_messenger);
        break;
    }
    }
    FUN_00396740(self, info);
}
