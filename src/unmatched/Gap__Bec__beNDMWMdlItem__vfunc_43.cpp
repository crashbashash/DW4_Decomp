#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendNamed(...);
int beMessenger_SelectReceivers(...);
int beMessenger_AppendMatrix(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBoolCount(...);
int beMessenger_GetBool(...);
int beMessenger_SelectGroup(...);
int beMessenger_AppendInt(...);
int igObject_GetAllocator(...);
struct PropertyValueObj { char p[252]; int f252; unsigned char f256; char p257[3]; int f260; };
struct PropertyEntry { char p[16]; int f16; PropertyValueObj *q; };
PropertyEntry *igProperty_FindByName(...);
extern int DAT_0051cf58[4];
extern int DAT_0051cfd0[4];
extern int DAT_0051cfd8[4];
extern int DAT_0051d018[4];
extern int DAT_0051d0a8[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: inline release helper reproduces the retail inlined refcount release */
struct RefRelease { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_43(beNDMWMdlItem *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlItem__vfunc_43(beNDMWMdlItem *arg0, beBaseInfoRam *arg1) {
    PropertyEntry *s3;
    PropertyValueObj *q;
    int idx;
    igObjectList *s2;
    int cnt, off;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        RefRelease::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
    }
    s3 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_0051cf58);
    q = s3->q;
    if (q->f256 != 0) {
        q->f256 = 0;
        s2 = (igObjectList *)arg0->_lockRamList;
        idx = q->f252;
        off = idx * 4;
        RefRelease::go(*(igObject **)((char *)s2->_data + off));
        cnt = s2->_count;
        if (cnt != 0 && idx >= 0 && idx < cnt) {
            *(igObject **)((char *)s2->_data + off) = 0;
        }
        q->f252 = -1;
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051cfd0);
        beMessenger_AppendString(arg0->_messenger, DAT_0051cfd8);
        beMessenger_AppendString(arg0->_messenger, q->f260);
        beMessenger_AppendString(arg0->_messenger, DAT_0051d0a8);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d018);
    }
}
