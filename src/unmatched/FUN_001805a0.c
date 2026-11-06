typedef struct Obj { int w0; int references; int w8; struct Obj *f12; int f16; int f20; int f24; int f28; } Obj;
typedef struct O { char pad[644]; int f644; char pad2[692]; unsigned char f1340; char pad3[83]; unsigned char f1424; } O;
typedef struct Lst { int w0; int references; int count; int cap; } Lst;
typedef struct Q { char pad[20]; int f20; } Q;
extern Obj *FUN_0014b390(int);
extern Obj *FUN_0015f4a0(int, int, int);
extern Obj *FUN_0015f510(int, int, int, int);
extern int FUN_00162ca0(Obj *);
extern int FUN_00180020(Q *);
extern int FUN_00180060(O *);
extern int FUN_00180ab0(O *, Obj *, Obj *, Obj *, Obj *, Obj *, Obj *, int);
extern Obj *FUN_0018a060(int);
extern int List_Resize(Obj *, int, int);
extern int ObjectList_AppendRetained(int, Obj *);
extern int igObject_Destroy(Obj *);
#define REL(x) { Obj *q = (x); if (q != 0) { q->references = q->references - 1; if (((unsigned long long)((long long)q->references << 0x29) >> 0x29) == 0) igObject_Destroy(q); } }
#define RELF(x, f) { Obj *q = (x); f[0] = 0; if (q != 0) { q->references = q->references - 1; if (((unsigned long long)((long long)q->references << 0x29) >> 0x29) == 0) igObject_Destroy(q); } }
#define INC(x) { Obj *q = (x); if (q != 0) q->references = q->references + 1; }
void FUN_001805a0(O *arg0, Q *arg1, int arg2) {
    volatile char sp90[1];
    volatile char sp94[1];
    volatile char sp98[1];
    volatile char sp9C[1];
    Obj * volatile spA0;
    Obj * volatile spA4;
    Obj * volatile spA8;
    Obj * volatile spAC;
    Obj *s0o;
    Obj *t8;
    Lst *ll;
    Obj *s7;
    Obj *s5;
    Obj *v;
    Obj *t4;
    Obj *s2;
    int s0;
    Obj *s1;
    s0 = arg1->f20;
    spAC = 0;
    s2 = 0;
    INC(spAC);
    spA8 = 0;
    INC(spA8);
    s7 = FUN_0015f4a0(s0, 5, 0);
    s1 = FUN_0015f4a0(s0, 6, 0);
    if (arg0->f1340 != 0 || arg0->f644 == 2) {
        if (arg0->f1424 != 0) FUN_00180060(arg0);
        s2 = FUN_0015f510(s0, 3, 0, 0x7734);
        if (s2 != 0) s2->references = s2->references + 1;
        REL(spA8);
        spA8 = s2;
        if (spA8 == 0) {
            sp9C[0] = 0;
            spA4 = FUN_0018a060(0);
            ll = (Lst *)spA4;
            if (arg2 >= 0) {
                if (arg2 <= ll->cap) ll->count = arg2;
 else List_Resize((Obj *)ll, arg2, 12);
            }
            RELF(spA8, sp98);
            spA8 = FUN_0014b390(0);
            t4 = spA4;
            t8 = spA8;
            if (t4 != 0) t4->references = t4->references + 1;
            REL(t8->f12);
            t8->f12 = t4;
            spA8->f16 = 3;
            spA8->f28 = 0x7734;
            ObjectList_AppendRetained(s0, spA8);
            s2 = FUN_0015f4a0(s0, 3, 0);
            s2->f20 = 0x7734;
            REL(spA4);
        } else {
            s2 = FUN_0015f4a0(s0, 3, 0x7734);
        }
    }
    v = FUN_0015f510(s0, 1, 0, 0x7734);
    s5 = v;
    if (s5 != 0) s5->references = s5->references + 1;
    REL(spAC);
    spAC = s5;
    if (spAC == 0) {
        sp94[0] = 0;
        spA0 = FUN_0018a060(0);
        ll = (Lst *)spA0;
            if (arg2 >= 0) {
                if (arg2 <= ll->cap) ll->count = arg2;
 else List_Resize((Obj *)ll, arg2, 12);
            }
        RELF(spAC, sp90);
        spAC = FUN_0014b390(0);
        s5 = spA0;
        s0o = spAC;
        if (s5 != 0) s5->references = s5->references + 1;
        REL(s0o->f12);
        s0o->f12 = s5;
        spAC->f16 = 1;
        spAC->f28 = 0x7734;
        ObjectList_AppendRetained(s0, spAC);
        s0o = FUN_0015f4a0(s0, 1, 0);
        s0o->f20 = 0x7734;
        REL(spA0);
    } else {
        s0o = FUN_0015f4a0(s0, 1, 0x7734);
    }
    FUN_00180020(arg1);
    FUN_00180ab0(arg0, s0o, spAC, s2, spA8, s7, s1, FUN_00162ca0(s1));
    REL(spA8);
    REL(spAC);
}
