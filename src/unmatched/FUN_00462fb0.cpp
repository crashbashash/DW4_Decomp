typedef struct O { int w0; int references; } O;
typedef struct P { char pad0[20]; O *f20; char pad24[20]; O *f44; } P;
#define REL(o) if ((o) != 0) { (o)->references = (o)->references - 1; if (((unsigned long long)(long long)(o)->references & 0x7fffffULL) == 0) igObject_Destroy(o); }
typedef struct Q { char pad[20]; int f20; } Q;
typedef struct X { char p0[76]; O *f76; O *f80; O *f84; char p1[48]; O *f136; } X;
typedef struct Y { char p0[117]; char f117; char p1[18]; O *f136; } Y;
typedef struct T { char p0[12]; struct T2 *f12; int pad; struct S *f20; } T;
struct T2 { char p[20]; O *f20; char q[28]; int f52; };
struct Cfg { char p[16]; int *f16; };
struct S { char p[212]; int f212; int f216; struct Cfg *f220; };
struct A0;
typedef struct A0 { char p0[12]; struct T2 *f12; int pad16; struct S *f20; char p1[16]; int f40; O *f44; int f48; char p2[84]; int f136; } A0;
extern "C" {
void *FUN_0045c170(int);
void *FUN_0045c5a0(int);
void *FUN_0045c8e0(int);
void *FUN_0045cc40(int);
int FUN_0045eda0(void *, int, int);
int FUN_00463fd0(int, void *);
int FUN_00465260(void *, int);
int igObject_Destroy(void *);
void FUN_00462fb0(struct A0 *arg0);
}
struct Mem { O *p; ~Mem() {} };

extern "C" void FUN_00462fb0(A0 *arg0) {
    X * volatile sp6C;
    Y * volatile sp68;
    O * volatile sp64;
    Y * volatile sp60;
    Mem sp5C;
    O * volatile sp58;
    volatile char sp54[1]; volatile char sp50[1]; volatile char sp4C[1]; volatile char sp48[1]; volatile char sp44[1];
    int a1;
    struct S *s = arg0->f20;
    a1 = s->f212;
    switch (a1) {
    case 0: {
        O *t, *u; X *x;
        sp54[0] = 0;
        sp6C = (X *)FUN_0045c170(0);
        FUN_0045eda0((void *)&sp58, arg0->f48, 1);
        t = sp58;
        x = sp6C;
        if (t != 0) t->references = t->references + 1;
        u = x->f84;
        REL(u);
        x->f84 = t;
        t = sp58;
        if (t != 0) { t->references = t->references - 1; u = sp58; if (((unsigned long long)(long long)u->references & 0x7fffffULL) == 0) igObject_Destroy(u); }
        t = (O *)arg0->f20;
        x = sp6C;
        if (t != 0) t->references = t->references + 1;
        u = x->f76;
        REL(u);
        x->f76 = t;
        t = arg0->f44;
        x = sp6C;
        if (t != 0) t->references = t->references + 1;
        u = x->f80;
        REL(u);
        x->f80 = t;
        FUN_00463fd0(arg0->f136, (void *)sp6C);
        t = (O *)sp6C;
        REL(t);
        break;
    }
    case 2: {
        O *t, *u; Y *y;
        sp50[0] = 0;
        sp68 = (Y *)FUN_0045c8e0(0);
        t = arg0->f12->f20;
        y = sp68;
        if (t != 0) t->references = t->references + 1;
        u = y->f136;
        REL(u);
        y->f136 = t;
        FUN_00463fd0(arg0->f136, (void *)sp68);
        t = (O *)sp68;
        REL(t);
        break;
    }
    case 1: {
        O *t;
        sp4C[0] = 0;
        sp64 = (O *)FUN_0045c5a0(0);
        FUN_00463fd0(arg0->f136, (void *)sp64);
        t = sp64;
        REL(t);
        break;
    }
    case 3: {
        O *t;
        sp48[0] = 0;
        sp60 = (Y *)FUN_0045c5a0(0);
        sp60->f117 = 1;
        FUN_00463fd0(arg0->f136, (void *)sp60);
        t = (O *)sp60;
        REL(t);
        break;
    }
    default: {
        int a0 = s->f216;
        if (a1 >= a0) {
            O *t;
            sp44[0] = 0;
            a0 = a1 - a0;
            sp5C.p = (O *)FUN_0045cc40(0);
            FUN_00465260((void *)sp5C.p, ((int *)arg0->f20->f220->f16)[a0]);
            FUN_00463fd0(arg0->f136, (void *)sp5C.p);
            arg0->f40 = arg0->f12->f52 + 1;
            t = sp5C.p;
            REL(t);
        }
        break;
    }
    }
}
