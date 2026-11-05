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
struct List { int pad0; int pad1; volatile int count; int cap; int *data; };
struct Ref2 {
    Obj *o;
    ~Ref2() {
        Obj *object = o;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct Self { char pad[44]; Obj *f44; List *f48; };
#define REL3(p) { Obj *t = p; if (t) { t->rc = t->rc - 1; Obj *u = p; if (((unsigned long long)((long long)u->rc << 0x29) >> 0x29) == 0) igObject_Destroy(u); } }
#define ASSIGN(field, src) { Obj *s0 = (src); if (s0) s0->rc = s0->rc + 1; Obj *old = (field); if (old) { old->rc = old->rc - 1; if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); } (field) = s0; }
extern "C" void FUN_00308860(Self *arg0, int arg1, int arg2) {
    Ref2 sp5C;
    Obj *volatile sp58;
    Obj *volatile sp54;
    if (arg0->f44 == 0) {
        sp58 = (Obj *)FUN_002b9350(igObject_GetAllocator(arg0));
        ASSIGN(arg0->f44, sp58);
        REL3(sp58);
        sp54 = (Obj *)FUN_002caa70(igObject_GetAllocator(arg0));
        ASSIGN(*(Obj **)&arg0->f48, sp54);
        REL3(sp54);
    }
    sp5C.o = (Obj *)FUN_002b9500(igObject_GetAllocator(arg0));
    FUN_0030b3c0(sp5C.o, arg1);
    ObjectList_AppendRetained(arg0->f44, sp5C.o);
    List *s0 = arg0->f48;
    int s2 = s0->count;
    if (s2 < s0->cap) {
        s0->count = s0->count + 1;
    } else {
        List_Resize(s0, s2 + 1, 4);
    }
    s0->data[s2] = arg2;
}
