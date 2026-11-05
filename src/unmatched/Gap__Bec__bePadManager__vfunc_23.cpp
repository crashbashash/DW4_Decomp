struct Rc { int vt; int rc; };
extern "C" {
void *FUN_00236f80(...);
void *FUN_0034ce50(...);
int FUN_00454290(...);
int FUN_004542d0(...);
int FUN_004574f0(...);
int FUN_00462e90(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00587108[4];
extern int DAT_00587d08[4];
extern int DAT_0058c790[4];
extern unsigned char GPR_00554c14;
}
struct Ref {
    Rc *p;
    Ref(Rc *x) : p(x) {}
    ~Ref() {
        Rc *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct M { char p[32]; int f32; int f36; };
struct O { char p[12]; M *f12; Rc *f16; int f20; int f24; };
extern "C" void Gap__Bec__bePadManager__vfunc_23(O *o) {
    Rc *t0 = (Rc *)FUN_00236f80(o->f12, DAT_00587d08[0]);
    if (t0 != 0) t0->rc = t0->rc + 1;
    {
        Rc *a0 = o->f16;
        if (a0 != 0) {
            a0->rc = a0->rc - 1;
            if (((unsigned long long)((long long)a0->rc << 0x29) >> 0x29) == 0) igObject_Destroy(a0);
        }
    }
    o->f16 = t0;
    for (int i = 0; i < 5; i++) {
        int v0 = igObject_GetAllocator(o);
        Ref sp3C((Rc *)FUN_0034ce50(GPR_00554c14 != 0 ? v0 : Memory_GetAllocatorBySelector(DAT_00587108[0])));
        ObjectList_AppendRetained(o->f20, sp3C.p);
    }
    M *m = o->f12;
    int s0 = m->f32;
    FUN_004542d0(s0, o->f24, m->f36);
    FUN_00454290(s0, o->f24);
    char *v = (char *)FUN_00236f80(o->f12, DAT_0058c790[0]);
    int s = *(int *)(v + 132);
    FUN_004574f0(s, 15);
    FUN_004574f0(s, 3);
    FUN_004574f0(s, 0);
    FUN_004574f0(s, 10);
    FUN_004574f0(s, 11);
    FUN_004574f0(s, 1);
    FUN_004574f0(s, 2);
    FUN_004574f0(s, 12);
    FUN_00462e90(v);
}
