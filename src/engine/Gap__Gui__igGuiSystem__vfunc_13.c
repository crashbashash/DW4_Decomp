typedef struct R { int w0; int refs; int w8; int wc; } R;
typedef struct X { char p[12]; R *f12; R *f16; } X;
typedef struct A { char p[8]; X *f8; int f12; int f16; R *f20; char q[4]; int f28; } A;
int FUN_001c5d10();
R *FUN_0044e990();
R *FUN_0044ecb0();
R *FUN_0044f0b0();
int FUN_00457e90();
int Gap__Core__igObject__vfunc_11();
int ObjectList_AppendRetained();
int igObject_Destroy();
int igObject_GetAllocator();
#define REL(p) if ((p) != 0) { (p)->refs = (p)->refs - 1; if (((unsigned long long) ((long long) (p)->refs << 0x29) >> 0x29) == 0) igObject_Destroy(p); }
void Gap__Gui__igGuiSystem__vfunc_13(A *arg0) {
    R * volatile sp4C;
    R * volatile sp48;
    int s0;
    R *s1;
    X *x;
    R *r;
    Gap__Core__igObject__vfunc_11();
    sp4C = 0;
    s0 = igObject_GetAllocator(arg0);
    r = sp4C; REL(r)
    sp4C = FUN_0044f0b0(s0);
    FUN_00457e90(sp4C, arg0->f12);
    { R *t = sp4C; ObjectList_AppendRetained(*(volatile int *)&arg0->f16, t); }
    sp48 = FUN_0044ecb0(igObject_GetAllocator(arg0));
    ((int *)sp48)[3] = (int)arg0;
    FUN_00457e90(sp48, arg0->f12);
    { R *t = sp48; ObjectList_AppendRetained(*(volatile int *)&arg0->f16, t); }
    s0 = igObject_GetAllocator(arg0);
    r = sp4C; REL(r)
    sp4C = FUN_0044e990(s0);
    FUN_00457e90(sp4C, arg0->f12);
    { R *t = sp4C; ObjectList_AppendRetained(*(volatile int *)&arg0->f16, t); }
    FUN_001c5d10(arg0->f20, arg0->f28);
    s1 = arg0->f20;
    x = arg0->f8;
    if (s1 != 0) s1->refs = s1->refs + 1;
    r = x->f12; REL(r)
    x->f12 = s1;
    s1 = (R *)arg0->f12;
    x = arg0->f8;
    if (s1 != 0) s1->refs = s1->refs + 1;
    r = x->f16; REL(r)
    x->f16 = s1;
    r = sp48; REL(r)
    r = sp4C; REL(r)
}
