extern "C" {
typedef struct BuildResource { int w0; int references; int w8; struct BuildResource *f12; int f16; int f20; int f24; int f28; } BuildResource;
typedef struct ResourceBuilder { char pad[644]; int f644; char pad2[692]; unsigned char f1340; char pad3[83]; unsigned char f1424; } ResourceBuilder;
typedef struct ResourceList { int w0; int references; int count; int cap; } ResourceList;
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
int igObject_Destroy(BuildResource *);
}
#define RELEASE(x) { BuildResource *q = (x); if (q != 0) { q->references = q->references - 1; if ((q->references & 0x7FFFFF) == 0) igObject_Destroy(q); } }
struct AdoptReference { };
struct ResourceRef {
    BuildResource *p;
    ResourceRef(BuildResource *object) : p(object) {
        if (p != 0) p->references = p->references + 1;
    }
    ResourceRef(BuildResource *object, AdoptReference) : p(object) {}
    ~ResourceRef() {
        BuildResource *o;
        if ((o = p) != 0) {
            o->references = o->references - 1;
            if ((o->references & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    void assign(BuildResource *next) {
        if (next != 0) next->references = next->references + 1;
        RELEASE(p);
        p = next;
    }
    void createOwned(AdoptReference) {
        RELEASE(p);
        p = FUN_0014b390(0);
    }
};
static inline void setMember(const ResourceRef &owner, const ResourceRef &value) {
    BuildResource *held = value.p;
    BuildResource *target = owner.p;
    BuildResource *old;
    if (held != 0) held->references = held->references + 1;
    old = target->f12;
    if (old != 0) {
        old->references = old->references - 1;
        if ((old->references & 0x7FFFFF) == 0) igObject_Destroy(old);
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
    ResourceRef first((BuildResource *)0);
    ResourceRef second((BuildResource *)0);
    s7 = FUN_0015f4a0(s0, 5, 0);
    s1 = FUN_0015f4a0(s0, 6, 0);
    if (arg0->f1340 != 0 || arg0->f644 == 2) {
        if (arg0->f1424 != 0) FUN_00180060(arg0);
        second.assign(FUN_0015f510(s0, 3, 0, 0x7734));
        if (second.p == 0) {
            ResourceRef values(FUN_0018a060(0), AdoptReference());
            ll = (ResourceList *)values.p;
            if (arg2 >= 0) {
                if (arg2 <= ll->cap) ll->count = arg2;
                else List_Resize((BuildResource *)ll, arg2, 12);
            }
            second.createOwned(AdoptReference());
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
    first.assign(FUN_0015f510(s0, 1, 0, 0x7734));
    if (first.p == 0) {
        ResourceRef values(FUN_0018a060(0), AdoptReference());
        ll = (ResourceList *)values.p;
        if (arg2 >= 0) {
            if (arg2 <= ll->cap) ll->count = arg2;
            else List_Resize((BuildResource *)ll, arg2, 12);
        }
        first.createOwned(AdoptReference());
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
