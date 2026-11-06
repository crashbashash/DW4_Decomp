#include "dw4/reflected.h"
extern "C" {
struct Rec { char pad[12]; int f12; };
int FUN_0043a450(void *, igObjectList *, igObject *, igObjectList *, igObject *);
int FUN_0043a660(void *, igObjectList *, igObject *, igObjectList *, igObject *);
int FUN_003c90f0(...);
int Memory_GetAllocatorBySelector(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
Rec *igProperty_GetRecordFolder(...);
extern int DAT_0051b398[4];
extern int DAT_0051b3a0[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b498[4];
extern int DAT_0051bb78[4];
extern int DAT_0051bb88[4];
extern int DAT_0051bb90[4];
extern int DAT_0051bba0[4];
extern int DAT_0051bc48[4];
extern int DAT_0051bdf0[4];
extern int DAT_0051be00[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: allocator pick kept as an in-class method so it inlines as in the retail unit */
struct ShopAlloc {
    static int Pool(beNDMWShopCtrlSales *self) { int a = igObject_GetAllocator(self); if (GPR_00554c14 != 0) return a; return Memory_GetAllocatorBySelector(DAT_00587110[0]); }
};

/* Owning stack reference to one scratch object; released on scope exit (reference count in the low
 * 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_00439f30(beNDMWShopCtrlSales *arg0, int arg1);
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
        l0 = (igObjectList *)igProperty_GetRecordFolder(obj, &DAT_0051bc48[0])->f12;
        m0 = (igObjectList *)igProperty_GetRecordFolder(obj, &DAT_0051bb90[0])->f12;
        l1 = (igObjectList *)igProperty_GetRecordFolder(obj, &DAT_0051bb78[0])->f12;
        m1 = (igObjectList *)igProperty_GetRecordFolder(obj, &DAT_0051bba0[0])->f12;
        l2 = (igObjectList *)igProperty_GetRecordFolder(obj, &DAT_0051bb88[0])->f12;
        ObjectRef a((igObject *)FUN_003c90f0(ShopAlloc::Pool(arg0)));
        ObjectRef b((igObject *)FUN_003c90f0(ShopAlloc::Pool(arg0)));
        kind = item->_kindNo;
        if (kind == 0) {
            FUN_0043a450(arg0, l0, a.p, m0, b.p);
            if (item != 0) item->_refCount++;
            o = ((beNDMWItemBase **)l0->_data)[0];
            if (o != 0) { o->_refCount--; if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o); }
            if (l0->_count != 0 && 0 < l0->_count) ((beNDMWItemBase **)l0->_data)[0] = item;
        } else if (kind == 1) {
            FUN_0043a450(arg0, l1, a.p, m1, b.p);
            if (item != 0) item->_refCount++;
            o = ((beNDMWItemBase **)l1->_data)[0];
            if (o != 0) { o->_refCount--; if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o); }
            if (l1->_count != 0 && 0 < l1->_count) ((beNDMWItemBase **)l1->_data)[0] = item;
        } else if (kind == 2) {
            FUN_0043a450(arg0, l2, a.p, 0, 0);
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
        if (kind == 0) FUN_0043a660(arg0, l0, a.p, m0, b.p);
        else if (kind == 1) FUN_0043a660(arg0, l1, a.p, m1, b.p);
        else if (kind == 2) FUN_0043a660(arg0, l2, a.p, 0, 0);
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    } else {
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051be00[0]);
    }
}
