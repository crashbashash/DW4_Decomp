struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct O { char pad[20]; int f20; struct Ref *f24; struct Ref *f28; };
void *FUN_0019f480();
void *FUN_0019f630();
int FUN_001c5730();
int FUN_001d6410();
int igObject_Destroy();
void *igObject_GetAllocator();
void FUN_001d65e0(struct O *arg0) {
    struct Ref *volatile sp3C;
    struct Ref *temp_v0;
    struct Ref *p;
    temp_v0 = (struct Ref *)FUN_0019f480(igObject_GetAllocator(arg0));
    if (temp_v0 != 0) {
        temp_v0->u.w = temp_v0->u.w + 1;
    }
    p = arg0->f28;
    if (p != 0) {
        p->u.w = p->u.w - 1;
        if (p->u.b.cnt == 0) igObject_Destroy(p);
    }
    arg0->f28 = temp_v0;
    p = arg0->f28;
    p->u.w = p->u.w - 1;
    if (p->u.b.cnt == 0) igObject_Destroy(p);
    sp3C = (struct Ref *)FUN_0019f630(igObject_GetAllocator(arg0));
    FUN_001c5730(sp3C, arg0->f20);
    FUN_001d6410(arg0, *(volatile int *)&arg0->f20, sp3C);
    p = sp3C;
    if (p != 0) {
        p->u.w = p->u.w - 1;
        if (p->u.b.cnt == 0) igObject_Destroy(p);
    }
}
