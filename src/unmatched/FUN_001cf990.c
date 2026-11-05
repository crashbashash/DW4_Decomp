int FUN_001ceab0();
int FUN_001e07a0();
int List_RemoveWordAt();
int ObjectList_AppendRetained();
int igObject_Destroy();
typedef struct S { char pad4[4]; int f4; } S;
typedef struct Ls { char pad8[8]; int n; char pad12[4]; S **data; } Ls;
typedef struct A { char pad36[36]; Ls *f36; } A;
typedef struct B { char pad28[28]; Ls *f28; } B;
int FUN_001cf990(A *arg0, B *arg1) {
    Ls *l;
    int n;
    int r;
    int k;
    Ls *m;
    S *o;
    l = arg1->f28;
    if (l != 0) {
        n = l->n;
    } else {
        n = 0;
    }
    if (n == 0) return 0;
    ObjectList_AppendRetained(arg0->f36, arg1);
    r = FUN_001ceab0(arg0, arg1);
    if (r == 0) {
        r = FUN_001e07a0(arg0, arg1);
    }
    m = arg0->f36;
    k = m->n - 1;
    o = m->data[k];
    if (o != 0) {
        o->f4 = o->f4 - 1;
        if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    List_RemoveWordAt(m, k);
    m->data[m->n] = 0;
    if (r == 2) return 2;
    return 0;
}
