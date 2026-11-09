/* 0x003f7310: beNDMWGameRam per-player data reset. arg1 == 0 also clears the common data list.
 * A fresh player data object (FUN_00364050) is filled in - record defaults, 12 item records
 * (FUN_003c85b0) appended to its item folder, the 960th skill byte - and replaces the entry at
 * arg1 of the player data list.  The new player data and each new item live on the stack in
 * owning references whose releases the retail exception table records.
 * Matching constructs: the identity (int) branch keeps the allocator select diamond; the per-loop locals and their
 * declaration order fix the saved-register colouring. */
#include "dw4/reflected.h"
extern "C" {
igObject *FUN_00364050(int);
igObject *FUN_003c85b0(int);
void *FUN_003a9250(igObject *, int *);
void *igProperty_GetRecordFolder(igObject *, int *);
void *igProperty_GetRecordArray(igObject *, int *);
int FUN_003f6620(beNDMWGameRam *, void *, int *);
int FUN_00448710(igObject *, int);
int List_Reserve(void *, int, int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, igObject *);
int ObjectList_ResizeRetained(int, int);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(void *);
extern int DAT_004ced40[4];
extern int DAT_004cedf0[4];
extern int DAT_004cf110[4];
extern int DAT_004cf118[4];
extern int DAT_00518a50[4];
extern int DAT_00518ae8[4];
extern int DAT_00518b30[4];
extern int DAT_00518b50[4];
extern int DAT_00587108[4];
extern unsigned char GPR_005549e8;
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the new player data object, released on scope exit (reference count in
 * the low 23 bits of _refCount). */
static inline int count(const igObjectList *list) { return list->_count; }
class PlayerDataRef {
public:
    igObject *p;
    PlayerDataRef(igObject *o) : p(o) {}
    ~PlayerDataRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to one new item record, released at the end of each loop pass. */
class ItemRef {
public:
    igObject *p;
    ItemRef(igObject *o) : p(o) {}
    ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
static inline void storePlayerData(beNDMWGameRam *self, int index, const PlayerDataRef &value) {
    igObject *s2 = value.p;
    igObjectList *pl = (igObjectList *)self->_playerDataListList;
    igObject *o;
    if (s2 != 0) s2->_refCount = s2->_refCount + 1;
    o = ((igObject **)pl->_data)[index];
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
    if (pl->_count != 0 && index >= 0 && index < pl->_count)
        ((igObject **)pl->_data)[index] = s2;
}
extern "C" void FUN_003f7310(beNDMWGameRam *arg0, int arg1) {
    igObjectList *common;
    igObjectList *ta;
    igObjectList *players;
    igObjectList *recs;
    igObjectList *arr;
    igObject *o;
    igObject *s1;
    igObject *s2;
    igObjectList *pl;
    int n, a, m, b, c, d, e, f, v; igObject *p7; int cn;
    int a0, a1;
    if (arg1 == 0) {
        common = (igObjectList *)arg0->_commonDataList;
        n = common->_count;
        for (a = 0; a < n; a++) {
            o = ((igObject **)common->_data)[a];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
            }
        }
        m = common->_count;
        for (b = 0; b < m; b++) ((int *)common->_data)[b] = 0;
        common->_count = 0;
        FUN_003f6620(arg0, (void *)arg0->_commonDataList, &DAT_004ced40[0]);
    }
    players = (igObjectList *)arg0->_playerDataListList;
    if (players->_count != 4) {
        if (count(players) < 5) List_Reserve(players, 4, 4);
        ObjectList_ResizeRetained(arg0->_playerDataListList, 4);
    }
    a0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a0 = (int)a0;
    } else {
        a0 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    PlayerDataRef data(FUN_00364050(a0));
    FUN_003f6620(arg0, data.p, &DAT_004cedf0[0]);
    for (c = 0; c < 16; c++) {
        recs = (igObjectList *)((igObject **)FUN_003a9250(data.p, &DAT_00518b30[0]))[3];
        if (recs->_count != 0 && c >= 0 && c < recs->_count)
            ((int *)recs->_data)[c] = DAT_004cf110[0];
    }
    for (d = 0; d < 16; d++) {
        for (e = 0; e < 9; e++) {
            arr = (igObjectList *)((igObject **)FUN_003a9250(data.p, &DAT_00518b50[0]))[3];
            v = e + d * 9;
            if (arr->_count != 0 && v >= 0 && v < arr->_count)
                ((int *)arr->_data)[v] = DAT_004cf118[0];
        }
    }
    for (f = 0; f < 12; f++) {
        a1 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            a1 = (int)a1;
        } else {
            a1 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
        }
        ItemRef item(FUN_003c85b0(a1));
        FUN_00448710(item.p, f);
        p7 = data.p;
        s1 = item.p;
        igObject **folder = (igObject **)igProperty_GetRecordFolder(p7, &DAT_00518a50[0]);
        ObjectList_AppendRetained(folder[3], s1);
    }
    ta = (igObjectList *)((igObject **)igProperty_GetRecordArray(data.p, &DAT_00518ae8[0]))[3];
    if (ta->_count != 0) {
        if (ta->_count > 960)
            ((unsigned char *)ta->_data)[960] = GPR_005549e8;
    }
    storePlayerData(arg0, arg1, data);
}
