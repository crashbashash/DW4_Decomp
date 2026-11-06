typedef struct { char pad[4]; int f4; } R;
typedef struct { char pad[12]; R *fc; } A;
typedef struct { int a; int b; int c; } V3;
R *FUN_0018a660();
int FUN_001900d0();
int FUN_001d3550();
int igObject_Destroy();
int igObject_GetAllocator();
void Gap__Sg__igGuiComponentNode__vfunc_13(A *arg0) {
    V3 s30;
    R *volatile sp3C;
    R *t;
    R *u;
    FUN_001d3550();
    sp3C = FUN_0018a660(igObject_GetAllocator(arg0));
    s30.a = 0;
    s30.b = 0;
    s30.c = 0;
    FUN_001900d0(sp3C, &s30);
    t = sp3C;
    if (t != 0) {
        t->f4 = t->f4 + 1;
    }
    u = arg0->fc;
    if (u != 0) {
        u->f4 = u->f4 - 1;
        if (((unsigned long long)((long long)u->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(u);
        }
    }
    arg0->fc = t;
    t = sp3C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
}
