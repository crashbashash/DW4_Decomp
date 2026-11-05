typedef struct Rc { int w0; int refs; } Rc;
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void v28(int); virtual void d29(); char p[40]; int f44; };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v30(int); virtual void v31(int); };
typedef struct S { char p0[32]; int f32; char p1[16]; int f52; char p2[17]; unsigned char f73; char p3[6]; B *f80; char p4[28]; B *f112; Rc *f116; Rc *f120; } S;
extern "C" {
int FUN_001c20b0(S *);
A *FUN_00140c00(int, int);
int FUN_001c31e0(int);
int FUN_00141190(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(void *);
Rc *FUN_00133160(int);
B *FUN_00139ed0(int);
Rc *FUN_00135190(int);
extern int DAT_00587038[4];
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_51(S *self);
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_51(S *self) {
    int alloc;
    Rc *t;
    A *a;
    FUN_001c20b0(self);
    *(int *)((char *)self->f32 + 96) = 2;
    if ((FUN_00140c00(self->f32, 0) != 0) == 0) FUN_001c31e0(self->f32);
    if (self->f52 != 0 && FUN_00140c00(self->f52, 0) != 0 && *(int *)((char *)FUN_00140c00(self->f52, 0) + 44) == 0) {
        a = FUN_00140c00(self->f52, 0);
        a->v28(1);
    }
    if (self->f73 != 0) FUN_00141190(self->f32, 1);
    self->f80->v30(2);
    alloc = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = self->f116;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
    self->f116 = FUN_00133160(alloc);
    alloc = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = (Rc *)self->f112;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
    self->f112 = FUN_00139ed0(alloc);
    self->f112->v30(1);
    self->f112->v31(1);
    alloc = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = self->f120;
    if (t != 0) {
        t->refs = t->refs - 1;
        if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
    }
    self->f120 = FUN_00135190(alloc);
}
}
