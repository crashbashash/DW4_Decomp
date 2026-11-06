/* SUBWND service-menu work creation, BIT/XDATA caps and shop-stock list preparation. owner is
 * beNDMWStatus (the SUBWND manager) and ram is its beNDMWStatusInfoRam; _subWndNo 6..9 selects
 * weapon / armor / chip / junk stock (WPU / APU / CHIP / JUNK). Lst::count is volatile so it is
 * re-read for the reserve test; the caps use '>' compares and a separate record local; the level
 * tier chains are else-if chains; row8 is declared before the loop counters; each item holder is
 * constructed at its use site from the new object and released by its destructor at scope exit;
 * the dispatch switches list their arms in ascending order. */
#include "dw4/reflected.h"
extern "C" {
struct Rec { int p[3]; int f12; };
struct RecB { char p[12]; unsigned char f12; };
struct IRec { int p[3]; igDataList *f12; };
void *igObject_GetAllocator(...);
void *Memory_GetAllocatorBySelector(...);
void *FUN_003b5ec0(...);
void *FUN_003c87f0(...);
void *FUN_003c8970(...);
void *FUN_003c8b00(...);
void *FUN_003c8c90(...);
int FUN_004482e0(...);
int FUN_00448430(...);
int FUN_00448580(...);
int FUN_00448660(...);
int FUN_0012a1e8(...);
int List_Reserve(...);
int ObjectList_FillRetained(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendGroup(...);
int beMessenger_SendNamed(...);
int beDataBase_GetRecordInt(...);
int igObject_Destroy(...);
Rec *igProperty_GetRecord(...);
RecB *igProperty_GetRecordByte(...);
IRec *FUN_003a9250(...);
extern int DAT_00516848[4];
extern int DAT_00516850[4];
extern int DAT_00516860[4];
extern int DAT_00516960[4];
extern int DAT_00516980[4];
extern int DAT_00516998[4];
extern int DAT_005169a8[4];
extern int DAT_00516ac8[4];
extern int DAT_00516ad8[4];
extern int DAT_00516b50[4];
extern int DAT_00516b60[4];
extern int DAT_00516b70[4];
extern int DAT_00516b80[4];
extern int DAT_00516b90[4];
extern int DAT_00516b98[4];
extern int DAT_00516ba8[4];
extern int DAT_00587108[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;

void FUN_003d8740(beNDMWStatus *owner, beNDMWStatusInfoRam *ram);
}
/* Owning reference to a freshly created object: the destructor drops one reference and destroys at
 * zero. Every item kind is its own class, so the compiler emits one destructor per kind. */
struct ObjectRef { igObject *p; ObjectRef(igObject *o) : p(o) {} ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
template <int K> struct ItemRef { igObject *p; ItemRef(igObject *o) : p(o) {} ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
struct U { static inline void Reserve(volatile igObjectList *l) { if (l->_count < 37) List_Reserve(l, 36, 4); } };
#define WL(f) ((volatile igObjectList *)work->f)
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define ALLOC(a, sel) { a = igObject_GetAllocator(owner); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(sel); }
#define ITEM4(K, sp, fac, init, lst, id) { ALLOC(alloc, DAT_00587108[0]) ItemRef<K> sp((igObject *)fac(alloc)); init(sp.p, id, owner, level); ObjectList_AppendRetained(lst, sp.p); }
#define ITEM2(K, sp, fac, init, lst, id) { ALLOC(alloc, DAT_00587108[0]) ItemRef<K> sp((igObject *)fac(alloc)); init(sp.p, id); ObjectList_AppendRetained(lst, sp.p); }

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
        ObjectRef spWork((igObject *)FUN_003b5ec0(alloc));
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
        if (igProperty_GetRecordByte(folder, &DAT_00516860[0])->f12 != 0) {
            joined += 1;
            if (igProperty_GetRecord(folder, &DAT_00516ad8[0])->f12 > 9999999) {
                Rec *r1 = igProperty_GetRecord(folder, &DAT_00516ad8[0]);
                r1->f12 = 9999999;
            }
            if (igProperty_GetRecord(folder, &DAT_00516ac8[0])->f12 > 9999) {
                Rec *r2 = igProperty_GetRecord(folder, &DAT_00516ac8[0]);
                r2->f12 = 9999;
            }
        }
        pl += 1;
    } while (pl < 4);
    beMessenger_SelectGroup(owner->_messenger, &DAT_00516848[0]);
    beMessenger_AppendInt(owner->_messenger, 0);
    beMessenger_DispatchSelected(owner->_messenger, &DAT_00516850[0]);
    folder = beMessenger_GetObject(owner->_messenger, 0);
    level = igProperty_GetRecord(folder, &DAT_00516960[0])->f12;
    switch (owner->_subWndNo) {
    case 6:
        if (WL(_weaponSalesList)->_count <= 0) {
            U::Reserve(WL(_weaponSalesList));
            ObjectList_FillRetained(WL(_weaponSalesList), 0);
            if (joined > 1) {
                base = 150;
            } else {
                switch (igProperty_GetRecord(folder, &DAT_005169a8[0])->f12) {
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
                        FUN_0012a1e8(buf9, &DAT_00516ba8[0]);
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
