int FUN_001b1490();
int FUN_001d7b70();
int List_Resize();
typedef struct Lst { int w0; int w4; int count; int cap; int *data; int w20; int w24; int (*cb)(int, int, void *); } Lst;
typedef struct Hdr { int w[4]; Lst **data; } Hdr;
typedef struct S { int w[4]; Hdr *f16; int w20[7]; int f48; int w52[4]; int *f68; } S;
typedef struct Cur { int w[2]; short s8; short s10; } Cur;
typedef struct O { int w[13]; S *f52; int w56[44]; Cur *f232; } O;
int FUN_001ba6e0(O *arg0, int arg1) {
    Cur *volatile sp7C;
    int n;
    S *s;
    Cur *t;
    Lst *l;
    int idx;
    Cur *cur;
    int item;

    cur = arg0->f232;
    s = arg0->f52;
    idx = cur->s10 + s->f68[cur->s8];
    l = s->f16->data[idx];
    sp7C = cur;
    n = *(volatile int *)&l->count;
    if (n < l->cap) {
        l->count = l->count + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    t = sp7C;
    l->data[n] = (int)t;
    FUN_001b1490(s, l, idx, t);
    FUN_001d7b70(arg1, arg0);
    cur = arg0->f232;
    s = arg0->f52;
    idx = cur->s10 + s->f68[cur->s8];
    l = s->f16->data[idx];
    n = l->count - 1;
    item = l->data[n];
    if (l->cb != 0) {
        l->cb(item, s->f48, l->cb);
    }
    l->count = l->count - 1;
    FUN_001b1490(s, l, idx);
    return 0;
}
