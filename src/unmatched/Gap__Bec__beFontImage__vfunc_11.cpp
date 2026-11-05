extern "C" {
void *FUN_00131390(int);
void *FUN_00139600(int);
int Gap__Core__igObject__vfunc_11(void *);
int ObjectList_AppendRetained(unsigned, void *);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v30(int);
  unsigned rc; };
struct B { char pad[20]; int f20; int f24; char pad3[4]; int f32; };
extern "C" void Gap__Bec__beFontImage__vfunc_11(B *arg0, int arg1) {
    Obj * volatile sp3C;
    Obj * volatile sp38;
    Obj *t;
    Gap__Core__igObject__vfunc_11(arg0);
    if (arg1 != 0) {
        ObjectList_AppendRetained((unsigned)arg0->f20, (void *)arg0->f32);
        sp3C = (Obj *)FUN_00139600(igObject_GetAllocator(arg0));
        sp3C->v30(1);
        ObjectList_AppendRetained((unsigned)arg0->f20, sp3C);
        sp38 = (Obj *)FUN_00131390(igObject_GetAllocator(arg0));
        sp38->v30(1);
        ObjectList_AppendRetained((unsigned)arg0->f20, sp38);
        arg0->f24 = 0x10001;
        t = sp38;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        t = sp3C;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
}
