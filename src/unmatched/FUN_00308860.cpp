extern "C" {
void *FUN_002b9350(void *);
void *FUN_002b9500(void *);
void *FUN_002caa70(void *);
int FUN_0030b3c0(void *, int);
void List_Resize(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
}
struct Obj { int vt; int rc; };
struct List { int pad0; int pad1; int count; int cap; int *data; };
static inline int countOf(const List *list) { return list->count; }
struct NameRef {
    Obj *p;
    NameRef() {}
    ~NameRef() {
        Obj *o;
        if ((o = p) != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
struct MemberRef {
    Obj *p;
    MemberRef(Obj *object) : p(object) {}
    ~MemberRef() {
        if (p != 0) {
            p->rc = p->rc - 1;
            if ((p->rc & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
};
struct Self { char pad[44]; Obj *names; List *values; };
static inline void setNames(Self *self, const MemberRef &value) {
    Obj *held = value.p;
    Obj *old;
    if (held) held->rc = held->rc + 1;
    old = self->names;
    if (old) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->names = held;
}
static inline void setValues(Self *self, const MemberRef &value) {
    Obj *held = value.p;
    Obj *old;
    if (held) held->rc = held->rc + 1;
    old = (Obj *)self->values;
    if (old) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->values = (List *)held;
}
extern "C" void FUN_00308860(Self *self, int name, int value) {
    NameRef entry;
    if (self->names == 0) {
        {
            MemberRef names((Obj *)FUN_002b9350(igObject_GetAllocator(self)));
            setNames(self, names);
        }
        {
            MemberRef values((Obj *)FUN_002caa70(igObject_GetAllocator(self)));
            setValues(self, values);
        }
    }
    entry.p = (Obj *)FUN_002b9500(igObject_GetAllocator(self));
    FUN_0030b3c0(entry.p, name);
    ObjectList_AppendRetained(self->names, entry.p);
    List *values = self->values;
    int top = countOf(values);
    if (top < values->cap) {
        values->count = values->count + 1;
    } else {
        List_Resize(values, top + 1, 4);
    }
    values->data[top] = value;
}
