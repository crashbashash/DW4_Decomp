extern "C" {
typedef struct PoolObject { int _vtable; int _refCount; } PoolObject;
typedef struct EnbayaIntList { int _pad0[2]; int _count; int _capacity; int *_data; int count() const { return _count; } } EnbayaIntList;
typedef struct EnbayaContextPoolView { int _pad0[2]; int _poolList; EnbayaIntList *_boneCountList; EnbayaIntList *_freeIndexList; } EnbayaContextPoolView;
extern PoolObject *FUN_002c9130(int);
extern void List_Resize(EnbayaIntList *, int, int);
extern void ObjectList_AppendRetained(int, PoolObject *);
extern void igObject_Destroy(PoolObject *);
extern int igObject_GetAllocator(EnbayaContextPoolView *);
extern int DAT_0048da08[4];
}
struct PoolListHolder { PoolObject *p; ~PoolListHolder() {} };
static inline int findIndex(EnbayaIntList *l0, int n0, int boneCount, int &i) {
    for (i = 0; i < n0; i++) {
        if (boneCount == l0->_data[i]) return i;
    }
    i = -1;
    return -1;
}
extern "C" void FUN_001c17e0(EnbayaContextPoolView *o, int boneCount) {
    EnbayaIntList *l0;
    int n1;
    EnbayaIntList *l1;
    int n2;
    int i;
    PoolObject *held;
    int n0;
    EnbayaIntList *l2;
    l0 = o->_boneCountList;
    n0 = l0->_count;
    if (findIndex(l0, n0, boneCount, i) == -1) {
        PoolListHolder list;
        list.p = FUN_002c9130(igObject_GetAllocator(o));
        ObjectList_AppendRetained(o->_poolList, list.p);
        l1 = o->_boneCountList;
        n1 = l1->_count;
        if (n1 < l1->_capacity) {
            l1->_count = l1->count() + 1;
        } else {
            List_Resize(l1, n1 + 1, 4);
        }
        l1->_data[n1] = boneCount;
        l2 = o->_freeIndexList;
        n2 = l2->_count;
        if (n2 < l2->_capacity) {
            l2->_count = l2->count() + 1;
        } else {
            List_Resize(l2, n2 + 1, 4);
        }
        l2->_data[n2] = DAT_0048da08[0];
        held = list.p;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
}
