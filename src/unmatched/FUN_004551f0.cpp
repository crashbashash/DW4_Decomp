extern "C" {
void *FUN_00450de0(...);
int FUN_00457e90(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void FUN_004551f0(void *arg0, int arg1, void *arg2);
}
struct Rc { int vt; int rc; int p8; int f12; int f16; };
struct Ref {
    Rc *p;
    ~Ref() {
        Rc *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct A { char pad8[8]; int f8; };
void FUN_004551f0(void *arg0v, int arg1, void *arg2v) {
    A *arg0 = (A *)arg0v;
    Rc *arg2 = (Rc *)arg2v;
    Ref sp4C;
    sp4C.p = (Rc *)FUN_00450de0(igObject_GetAllocator());
    ObjectList_AppendRetained(arg0->f8, sp4C.p);
    sp4C.p->f12 = (int)arg0;
    Rc *t = sp4C.p;
    if (arg2 != 0) {
        arg2->rc = arg2->rc + 1;
    }
    Rc *old = (Rc *)t->f16;
    if (old != 0) {
        old->rc = old->rc - 1;
        if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    t->f16 = (int)arg2;
    FUN_00457e90(sp4C.p, arg1);
}
