#include "dw4/igSmartPointer.h"

extern "C" {
typedef struct BuildResource : public igObject { int w8; struct BuildResource *f12; int f16; int f20; int f24; int f28; } BuildResource;
typedef struct ResourceBuilder { char pad[644]; int f644; char pad2[692]; unsigned char f1340; char pad3[83]; unsigned char f1424; } ResourceBuilder;
typedef struct ResourceList : public igObject { int count; int cap; } ResourceList;
typedef struct ResourceSource { char pad[20]; int f20; } ResourceSource;
BuildResource *FUN_0014b390(int);
BuildResource *FUN_0015f4a0(int, int, int);
BuildResource *FUN_0015f510(int, int, int, int);
int FUN_00162ca0(BuildResource *);
int FUN_00180020(ResourceSource *);
int FUN_00180060(ResourceBuilder *);
int FUN_00180ab0(ResourceBuilder *, BuildResource *, BuildResource *, BuildResource *, BuildResource *, BuildResource *, BuildResource *, int);
BuildResource *FUN_0018a060(int);
int List_Resize(BuildResource *, int, int);
int ObjectList_AppendRetained(int, BuildResource *);
}
#define RELEASE(x) { BuildResource *q = (x); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7FFFFF) == 0) igObject_Destroy(q); } }

static inline void createOwned(igSmartPointer<BuildResource> &holder, AdoptReference) {
    RELEASE(holder.p);
    holder.p = FUN_0014b390(0);
}
static inline void setMember(const igSmartPointer<BuildResource> &owner, const igSmartPointer<BuildResource> &value) {
    BuildResource *held = value.p;
    BuildResource *target = owner.p;
    BuildResource *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = target->f12;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    target->f12 = held;
}
extern "C" void FUN_001805a0(ResourceBuilder *arg0, ResourceSource *arg1, int arg2) {
BuildResource *s2;
BuildResource *s1;
ResourceList *ll;
BuildResource *s0o;
int s0;
BuildResource *s7;
    s0 = arg1->f20;
    s2 = 0;
    igSmartPointer<BuildResource> first((BuildResource *)0, kRetainReference);
    igSmartPointer<BuildResource> second((BuildResource *)0, kRetainReference);
    s7 = FUN_0015f4a0(s0, 5, 0);
    s1 = FUN_0015f4a0(s0, 6, 0);
    if (arg0->f1340 != 0 || arg0->f644 == 2) {
        if (arg0->f1424 != 0) FUN_00180060(arg0);
        second = FUN_0015f510(s0, 3, 0, 0x7734);
        if (second.p == 0) {
            igSmartPointer<BuildResource> values(FUN_0018a060(0), AdoptReference());
            ll = (ResourceList *)values.p;
            if (arg2 >= 0) {
                if (arg2 <= ll->cap) ll->count = arg2;
                else List_Resize((BuildResource *)ll, arg2, 12);
            }
            createOwned(second, AdoptReference());
            setMember(second, values);
            second.p->f16 = 3;
            second.p->f28 = 0x7734;
            ObjectList_AppendRetained(s0, second.p);
            s2 = FUN_0015f4a0(s0, 3, 0);
            s2->f20 = 0x7734;
        } else {
            s2 = FUN_0015f4a0(s0, 3, 0x7734);
        }
    }
    first = FUN_0015f510(s0, 1, 0, 0x7734);
    if (first.p == 0) {
        igSmartPointer<BuildResource> values(FUN_0018a060(0), AdoptReference());
        ll = (ResourceList *)values.p;
        if (arg2 >= 0) {
            if (arg2 <= ll->cap) ll->count = arg2;
            else List_Resize((BuildResource *)ll, arg2, 12);
        }
        createOwned(first, AdoptReference());
        setMember(first, values);
        first.p->f16 = 1;
        first.p->f28 = 0x7734;
        ObjectList_AppendRetained(s0, first.p);
        s0o = FUN_0015f4a0(s0, 1, 0);
        s0o->f20 = 0x7734;
    } else {
        s0o = FUN_0015f4a0(s0, 1, 0x7734);
    }
    FUN_00180020(arg1);
    FUN_00180ab0(arg0, s0o, first.p, s2, second.p, s7, s1, FUN_00162ca0(s1));
}
