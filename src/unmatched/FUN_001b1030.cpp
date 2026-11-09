struct L { char pad8[8]; volatile int n; int cap; int *data; };
struct Y { char p16[16]; struct L **f16; };
struct X { char p16[16]; struct Y *f16; char p20[48]; int *f68; };
struct E { char p8[8]; short a; short b; };
int FUN_001b1490(struct X *, struct L *, int, struct E *);
int List_Resize(struct L *, int, int);

void FUN_001b1030(struct X *arg0, struct E *arg1) {
    struct E * volatile sp5C;
    int s2;
    struct L *s1;
    int s0;
    struct E *t;

    s0 = arg1->b + arg0->f68[arg1->a];
    s1 = arg0->f16->f16[s0];
    sp5C = arg1;
    s2 = s1->n;
    if (s2 < s1->cap) {
        s1->n = s1->n + 1;
    } else {
        List_Resize(s1, s2 + 1, 4);
    }
    t = sp5C;
    s1->data[s2] = (int)t;
    FUN_001b1490(arg0, s1, s0, t);
}
