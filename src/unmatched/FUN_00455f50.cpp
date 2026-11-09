struct Obj { int w0; unsigned refs; };
struct Y { char pad[8]; int f8; char pad2[8]; float f20; };
struct Z { char pad[24]; float f24; unsigned char f28; char pad2[3]; Obj *f32; };
extern "C" {
Obj *FUN_0019f630(...);
int FUN_001c5790(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void FUN_00455f50(Z *arg0, Y *arg1);
}
struct ObjRef {
    Obj *p;
    ObjRef(Obj *object) : p(object) {}
    ~ObjRef() {
        if (p != 0) {
            p->refs = p->refs - 1;
            if ((p->refs & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
    Obj *get() const { return p; }
};
static inline void setPick(Z *z, const ObjRef &value) {
    Obj *held = value.get();
    Obj *old;
    if (held != 0) held->refs = held->refs + 1;
    old = z->f32;
    if (old != 0) {
        old->refs = old->refs - 1;
        if ((old->refs & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    z->f32 = held;
}
void FUN_00455f50(Z *arg0, Y *arg1) {
    int s1 = arg1->f8;
    if (arg1->f20 <= arg0->f24) {
        arg0->f28 = 1;
        arg0->f24 = arg1->f20;
        {
            ObjRef made(FUN_0019f630(igObject_GetAllocator(arg0)));
            setPick(arg0, made);
        }
        FUN_001c5790(arg0->f32, s1);
    }
}
