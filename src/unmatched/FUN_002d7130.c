typedef struct Rc { int w0; int rc; } Rc;
typedef struct L { int w0; int rc; int n; int cap; Rc **data; } L;
typedef struct O { char p8[8]; L *f8; } O;
L *FUN_002bd680();
int FUN_002d6f50();
int ObjectList_AppendRetainedList();
int igObject_Destroy();
int igObject_GetAllocator();

void FUN_002d7130(O *arg0) {
    L *t;
    int n2;
    L *s2;
    int s1;
    Rc *a0;
    int s0;
    int a1;
    L * volatile sp5C;

    sp5C = FUN_002bd680(igObject_GetAllocator(arg0));
    ObjectList_AppendRetainedList(sp5C, arg0->f8);
    s2 = arg0->f8;
    s1 = s2->n;
    for (s0 = 0; s0 < s1; s0++) {
        a0 = s2->data[s0];
        if (a0 != 0) {
            a0->rc = a0->rc - 1;
            if ((a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    n2 = s2->n;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->n = 0;
    for (s0 = 0; t = sp5C, s0 < t->n; s0++) {
        FUN_002d6f50(arg0, t->data[s0], 0);
    }
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
}
