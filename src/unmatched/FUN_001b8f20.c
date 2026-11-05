int FUN_001904f0();
int FUN_001b1030();
int FUN_001b1100();
int FUN_001b1aa0();
int FUN_001dca40();
int FUN_001e07a0();
int igObject_Destroy();
int FUN_001356b0();
extern char DAT_004e0ef0[];
typedef struct RC { int p0; unsigned refs; } RC;
typedef struct G { char p[8]; int f8; } G;
extern G *DAT_0055efe8[4];
typedef struct Arr { char p[8]; int count; int p12; int *data; } Arr;
typedef struct LB { char p[8]; int cap; int p12; RC **data; int count; } LB;
typedef struct X { char p[16]; Arr *a16; char q[48]; int *a68; } X;
typedef struct C { char p[52]; X *x; char q[16]; LB *l72; char r[24]; char v100[64]; char v164[16]; } C;
typedef struct D { char p[60]; RC *f60; } D;
int FUN_001b8f20(C *arg0, D *arg1) {
    char sp80[64];
    char sp40[64];
    X *x;
    Arr *a;
    int v;
    LB *lb;
    RC *o;
    RC *old;
    int r;
    int n;
    char *s0;
    x = arg0->x;
    a = (Arr *)x->a16->data[x->a68[DAT_0055efe8[0]->f8]];
    s0 = arg0->v164;
    n = a->count;
    if (n == 0) v = 0; else v = *(int *)((char *)a->data + (n - 1) * 4);
    if (v != 0) {
        FUN_001904f0(sp40, v + 12, s0);
        FUN_001b1aa0(arg1, sp80, sp40, s0);
    } else {
        FUN_001b1aa0(arg1, sp80, DAT_004e0ef0, s0);
    }
    lb = arg0->l72;
    if (lb->count >= lb->cap) FUN_001dca40(lb, (void *)&FUN_001356b0);
    o = lb->data[lb->count++];
    if (o != 0) o->refs++;
    old = arg1->f60;
    if (old != 0) {
        old->refs--;
        if (!(old->refs & 0x7fffff)) igObject_Destroy(old);
    }
    arg1->f60 = o;
    FUN_001904f0((char *)o + 12, sp80, arg0->v100);
    FUN_001b1030(arg0->x, o);
    r = FUN_001e07a0(arg0, arg1);
    FUN_001b1100(arg0->x, o);
    if (r == 2) return 2;
    return 0;
}
