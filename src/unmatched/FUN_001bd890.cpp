#include "dw4/igTDataList.h"
typedef igTDataList<void *> RemapIndexList;
struct RemapObject {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int getMeta();
    unsigned int _refCount;
    char _pad8[16];
    RemapIndexList *_indices;
};
struct RemapObjectList { int _vtable; unsigned int _refCount; int _count; int _capacity; RemapObject **_data; };
struct RemapTable { int _vtable; unsigned int _refCount; int _pad8; void *_storage; int *_data; int _count; unsigned int _capacity; };
struct RemapEntry { int _vtable; unsigned int _refCount; void *_target; RemapObject **_slot; };
struct RemapContext { char _pad0[480]; RemapIndexList *_pool; };
struct RemapOwner { char _pad0[32]; RemapObjectList *_items; char _pad24[12]; RemapObjectList *_entries; char _pad34[32]; RemapObject *_fallback; };
extern int DAT_0055ec28[4];
extern int DAT_0055f360[4];
extern int DAT_0055f000[4];
extern "C" {
int igObject_IsKindOf(void *, int);
void *igObject_GetAllocator(void *);
RemapEntry *FUN_001a2c70(void *);
RemapTable *FUN_00139990(void *);
void ObjectList_AppendRetained(RemapObjectList *, void *);
void igObject_Destroy(void *);
void FUN_00300f50(void *, void *);
int *igObject_AllocateStorage(void *, int);
}
template <class T> static inline void release(T *p) {
    p->_refCount = (int)p->_refCount - 1;
    if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(p);
    }
}
template <class T> static inline void retain(T *p) {
    if (p != 0) {
        p->_refCount = p->_refCount + 1;
    }
}
static inline void setTarget(RemapEntry *e, void *t) {
    unsigned int *old;
    retain((RemapObject *)t);
    old = (unsigned int *)e->_target;
    if (old != 0) {
        release((RemapObject *)old);
    }
    e->_target = t;
}
static inline void setAt(RemapObjectList *l, int i, RemapObject *v) {
    if (l->_count != 0 && i >= 0 && i < l->_count) {
        l->_data[i] = v;
    }
}
static inline void setCount(RemapTable *t, unsigned int n) {
    if (t->_capacity < n) {
        if (t->_storage != 0) {
            FUN_00300f50(t, t->_storage);
        }
        if (t->_data != 0) {
            FUN_00300f50(t, t->_data);
        }
        t->_data = igObject_AllocateStorage(t, n * 4);
        t->_capacity = n;
    }
    t->_count = n;
}
extern "C" int FUN_001bd890(RemapOwner *o, RemapContext *ctx) {
    int count = o->_items->_count;
    int i;
    for (i = 0; i < count; i++) {
        RemapObject *item = o->_items->_data[i];
        if (igObject_IsKindOf(item, DAT_0055ec28[0]) != 0) {
            RemapEntry *e = FUN_001a2c70(igObject_GetAllocator(ctx));
            RemapTable *t;
            unsigned int n;
            int j;
            ObjectList_AppendRetained(o->_entries, e);
            release(e);
            t = FUN_00139990(igObject_GetAllocator(ctx));
            setTarget(e, t);
            release(t);
            e->_slot = &o->_items->_data[i];
            setAt(o->_items, i, (RemapObject *)t);
            n = item->_indices->_count;
            setCount(t, n);
            for (j = 0; j < (int)n; j++) {
                int r = ctx->_pool->find(item->_indices->_data[j]);
                if (r == -1) {
                    r = 0;
                }
                t->_data[(unsigned int)j] = r;
            }
        } else if (igObject_IsKindOf(item, DAT_0055f360[0]) != 0) {
            RemapEntry *e = FUN_001a2c70(igObject_GetAllocator(ctx));
            ObjectList_AppendRetained(o->_entries, e);
            release(e);
            setTarget(e, item);
            e->_slot = &o->_items->_data[i];
            setAt(o->_items, i, item);
        } else if (DAT_0055f000[0] == item->getMeta()) {
            RemapObject *v = o->_fallback;
            setAt(o->_items, i, v);
        }
    }
    return 0;
}
