#include "dw4/reflected.h"
struct TravObject { int _vtable; unsigned int _refCount; int _id; };
struct TravObjectList { char pad[8]; int _count; int _capacity; TravObject **_data; };
struct TravFunctionTable { char pad[16]; int *_data; };
struct TravFlattenView { char pad[40]; TravObjectList *_a; TravObjectList *_b; };
extern TravFunctionTable *DAT_00562640;
extern int DAT_00561a38;
extern void *DAT_005625f0;
extern "C" {
int igMetaObject_CountTree(int);
TravObject *FUN_002fe300(int, int);
void FUN_001e06c0(TravFunctionTable *, TravObject *, void *);
void FUN_001b3ad0(void);
int igObject_Destroy(TravObject *);
void FUN_001e07a0(int, TravFlattenView *);
void FUN_001b42c0(TravFlattenView *self, int root);
}
static inline void clearRetained(TravObjectList *l) {
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        TravObject *o = l->_data[i];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int total = l->_count;
        for (i = 0; i < total; i++) {
            l->_data[i] = 0;
        }
    }
    l->_count = 0;
}
void FUN_001b42c0(TravFlattenView *self, int root) {
    int saved[32];
    TravFunctionTable *table = DAT_00562640;
    int meta = DAT_00561a38;
    int n = igMetaObject_CountTree(meta);
    int i;
    for (i = 0; i < n; i++) {
        TravObject *m = FUN_002fe300(meta, i);
        saved[i] = table->_data[m->_id];
        FUN_001e06c0(table, m, (void *)FUN_001b3ad0);
    }
    DAT_005625f0 = self;
    clearRetained(self->_a);
    clearRetained(self->_b);
    FUN_001e07a0(root, self);
    for (i = 0; i < n; i++) {
        FUN_001e06c0(table, FUN_002fe300(meta, i), (void *)saved[i]);
    }
}
