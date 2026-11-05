typedef struct RC { int p0; unsigned refs; } RC;
typedef struct Item { char p[28]; int f28; int f32; } Item;
typedef struct OL { char p[8]; int count; int cap; Item **data; } OL;
typedef struct OL2 { char p[8]; int count; int cap; RC **data; } OL2;
typedef struct T { char p[60]; int f60; } T;
typedef struct A { char p[32]; OL *l; } A;
typedef struct B { char p[36]; T *t; } B;
extern "C" {
int FUN_001c5d10(T *, int);
int List_Reserve(OL *, int, int);
int ObjectList_AppendRetained(int, int);
int igObject_Destroy(RC *);
void FUN_0039e090(A *arg0, B *arg1);
}
void FUN_0039e090(A *arg0, B *arg1) {
    RC *r;
    Item *it;
    T *t;
    int n;
    int i;
    int off;
    OL2 *l;
    int n2;
    int i2;
    int n3;
    int i3;
    i = 0;
    t = arg1->t;
    n = arg0->l->count;
    if (0 < n) {
        off = 0;
        do {
            it = *(Item **)((char *)arg0->l->data + off);
            if (it->f32 != 0) ObjectList_AppendRetained(t->f60, it->f32);
            if (it->f28 != 0) FUN_001c5d10(t, it->f28);
            i += 1;
            off += 4;
        } while (i < n);
    }
    l = (OL2 *)arg0->l;
    n2 = l->count;
    i2 = 0;
    if (0 < n2) {
        off = 0;
        do {
            r = *(RC **)((char *)l->data + off);
            if (r != 0) {
                r->refs--;
                if (!(r->refs & 0x7fffff)) igObject_Destroy(r);
            }
            i2 += 1;
            off += 4;
        } while (i2 < n2);
    }
    n3 = l->count;
    for (i3 = 0; i3 < n3; i3++) {
        l->data[i3] = 0;
    }
    l->count = 0;
    if (!(0 < arg0->l->count)) List_Reserve(arg0->l, 0, 4);
}
