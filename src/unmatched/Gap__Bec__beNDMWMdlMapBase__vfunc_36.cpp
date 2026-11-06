#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
void *FUN_00350020(...);
void *beBaseInfoDataList_Create(...);
int FUN_00396740(...);
int Memory_GetAllocatorBySelector(int);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int beMessenger_GetInt(...);
int beMessenger_GetIntCount(...);
int beMessenger_GetString(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *igProperty_FindByName(...);
extern int DAT_0051dba8[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Property record: reference at +20. */
struct Prop { char pad[20]; igObject *f20; };
struct Tgt { char pad[220]; int f220; int f224; };
struct Rel { static inline void go(igObject *o) { igObject *t = o; if (t != 0) { --t->_refCount; if ((t->_refCount & 0x7fffff) == 0) igObject_Destroy(t); } } };
/* Owning stack reference to the slot's new data list; released on scope exit (reference count in
 * the low 23 bits of _refCount). */
class DataListRef {
public:
    igObject *p;
    DataListRef(igObject *o) : p(o) {}
    ~DataListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new map info work; released on scope exit. */
class InfoWorkRef {
public:
    igObject *p;
    InfoWorkRef(igObject *o) : p(o) {}
    ~InfoWorkRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Slot { static inline void setDataList(beBaseInfoRam *ram, const DataListRef &r) {
    igObject *t = r.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    Rel::go((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
} };
extern "C" void Gap__Bec__beNDMWMdlMapBase__vfunc_36(beNDMWMdlMapBase *arg0, beBaseInfoRam *arg1) {
    if (arg1->_dataList == 0) {
        int a = igObject_GetAllocator(arg1);
        int al = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(al);
        /* matching construct: the new list is a temporary bound to the setter's reference parameter (it
         * takes the stack slot below the named info-work reference, as retail's +0x58 does) */
        Slot::setDataList(arg1, DataListRef(created));
    }
    Prop *s3 = (Prop *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0051dba8);
    {
        int a2 = igObject_GetAllocator(arg0);
        int al2 = GPR_00554c14 != 0 ? a2 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        InfoWorkRef w((igObject *)FUN_00350020(al2));
        igObject *t2 = w.p;
        if (t2 != 0) t2->_refCount = t2->_refCount + 1;
        Rel::go(s3->f20);
        s3->f20 = t2;
        if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
            int str = beMessenger_GetString(arg0->_messenger, 0);
            int ns;
            Tgt *tg = (Tgt *)w.p;
            if (DAT_00586f20[0] == 0) {
                int v = FUN_002eb010(16);
                if (v != 0) v = StringPool_Construct(v);
                DAT_00586f20[0] = v;
            }
            ns = (int)StringPool_Intern(DAT_00586f20[0], str);
            int old = tg->f220;
            if (old != 0) {
                int *hdr = (int *)(old - 8);
                int c = hdr[1] - 1;
                hdr[1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
            }
            tg->f220 = ns;
            ((Tgt *)w.p)->f224 = beMessenger_GetInt(arg0->_messenger, 0);
        }
    }
    FUN_00396740(arg0, arg1);
}
