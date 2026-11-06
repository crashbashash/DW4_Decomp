/* Run a callback over a list into a stack-held pooled object, then flush it and report whether the
 * first flag byte is clear; the stack Ref releases on return (compiler-emitted duplicate
 * destructor, exceptions off). Alternate compiler -O3. */
extern "C" {
void igObject_Destroy(void *);
struct Obj { int word0; unsigned refs; };
struct Arr { int pad[2]; int count; int pad2; int *items; };
struct Owner { char pad[52]; char *p52; };
Obj *FUN_002baff0(int);
int FUN_002da770(Owner *);
Arr *FUN_002da780(Owner *);
int FUN_002da850(Owner *, Arr *);
int FUN_002db040(Owner *, int, Obj *, int);
int FUN_003061c0(int, Obj *, int);
int igObject_GetAllocator();
}
struct Ref {
    Obj *p;
    ~Ref() { Obj *o; if ((o = p) != 0) { --o->refs; if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int FUN_002da990(Owner *arg0, int arg1, int arg2, int arg3) {
    Ref sp7C;
    int r;
    Arr *a;
    int i;
    sp7C.p = FUN_002baff0(igObject_GetAllocator());
    a = FUN_002da780(arg0);
    for (i = 0; i < a->count; i++) {
        FUN_002db040(arg0, a->items[i], sp7C.p, arg2);
    }
    FUN_003061c0(arg1, sp7C.p, arg3);
    r = *arg0->p52 == 0;
    FUN_002da850(arg0, a);
    FUN_002da770(arg0);
    return r;
}
