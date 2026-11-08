typedef struct { char pad[40]; int *f40; char pad2[8]; int *f52; } Obj;
extern int D_004f57f0[];
extern int D_004f5820[];
extern int D_004f5840[];
extern int D_004bec28;
extern Obj *FUN_002b39e0(void);
extern int FUN_002b3ad8(int a, int b, int c);
extern void FUN_002b3b38(void *h, int a, int *tbl);
extern void FUN_002b3a30(Obj *o, int a, int b);
extern int *FUN_002b4270(void);
extern int *FUN_002b2f48(void);
extern void FUN_002b3ae8(Obj *o);

Obj *FUN_002b38c8(int a0, int a1, int a2, int a3) {
    Obj *o;
    int *p;
    int *q;
    o = FUN_002b39e0();
    if (o == 0) return o;
    if (FUN_002b3ad8(a1, a2, a3) != 1) {
        FUN_002b3b38(0, 0, D_004f57f0);
        return 0;
    }
    FUN_002b3a30(o, a0, a1);
    p = FUN_002b4270();
    if (p == 0) {
        FUN_002b3b38(0, 0, D_004f5820);
        FUN_002b3ae8(o);
        return 0;
    }
    o->f40 = p;
    q = FUN_002b2f48();
    if (q == 0) {
        FUN_002b3b38(0, 0, D_004f5840);
        FUN_002b3ae8(o);
        return 0;
    }
    o->f52 = q;
    D_004bec28++;
    return o;
}
