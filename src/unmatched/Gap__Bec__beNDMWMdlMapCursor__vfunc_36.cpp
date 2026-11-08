/* Applies a ram to the map-cursor model controller. The ram's data list is created on demand, a
 * fresh value object (FUN_00350020) replaces the named property's value, and when the messenger
 * carries a reply the value takes the interned string and the integer from it; FUN_00396740 then
 * refreshes the model. */
#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int);
int FUN_002eb010(int);
int FUN_00396740(void *, void *);
int beMessenger_GetInt(int, int);
int beMessenger_GetIntCount(int);
int beMessenger_GetString(int, int);
igObject *beBaseInfoDataList_Create(int);
struct CursorValue;
CursorValue *FUN_00350020(int);
struct PropertyEntry;
PropertyEntry *igProperty_FindByName(int, int, int *);
extern int DAT_0051dc38[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* The value object FUN_00350020 creates: an igObject whose string token sits at +220 and whose
 * integer at +224. */
struct CursorValue { igObject base; char pad[212]; int *f220; int f224; };   /* igObject is 8 bytes */
struct PropertyEntry { char pad[20]; CursorValue *f20; };
/* matching construct: inline retain/release helpers reproduce the retail inlined refcount code */
struct RefCount { static inline void addref(igObject *o) { if (o != 0) o->_refCount = o->_refCount + 1; }
 static inline void release(igObject *o) { if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o); } } };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    CursorValue *p;
    ValueRef(CursorValue *o) : p(o) {}
    ~ValueRef() { igObject *o = &p->base; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own value reference (+0x58 below +0x5c), as retail does.
 * matching construct: inline_depth(2) lets the list reference's destructor inline inside the inlined
 * helper (the default depth leaves an out-of-line call to __dt__9ObjectRefFv). */
struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        int al = igObject_GetAllocator(ram);
        al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        ObjectRef list(beBaseInfoDataList_Create(al));
        igObject *t = list.p;
        RefCount::addref(t);
        RefCount::release((igObject *)ram->_dataList);
        ram->_dataList = (int)t;
    }
} };
extern "C" void Gap__Bec__beNDMWMdlMapCursor__vfunc_36(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlMapCursor__vfunc_36(beNDMWMdlMapCursor *arg0, beBaseInfoRam *arg1) {
    CursorValue *t;
    void *nw;
    CursorValue *t2;
    int al;
    PropertyEntry *pr;
    int s;
    RamDataList::Ensure(arg1);
    pr = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0051dc38[0]);
    al = igObject_GetAllocator(arg0);
    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    {
    /* The new value object is owned by the stack reference while it replaces the record's value and
     * takes the messenger's reply; released at the block end, before the model refresh. */
    ValueRef value(FUN_00350020(al));
    t = value.p;
    RefCount::addref(&t->base);
    RefCount::release(&pr->f20->base);
    pr->f20 = t;
    if (beMessenger_GetIntCount(arg0->_messenger) != 0) {
        s = beMessenger_GetString(arg0->_messenger, 0);
        t2 = value.p;
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        nw = StringPool_Intern(DAT_00586f20[0], s);
        int *oldstr = t2->f220;
        if (oldstr != 0) {
            int *hdr = oldstr - 2;
            int c = oldstr[-1] - 1;
            oldstr[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*hdr, hdr);
        }
        t2->f220 = (int *)nw;
        value.p->f224 = beMessenger_GetInt(arg0->_messenger, 0);
    }
    }
    FUN_00396740(arg0, arg1);
}
