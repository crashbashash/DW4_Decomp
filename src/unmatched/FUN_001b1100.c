/* 0x001b1100 - FUN_001b1100. Pops the top entry of a stack in a table, with an optional callback; element read hoisted; alternate compiler. Verified byte-identical by tools/verify.py. */
int FUN_001b1490();
struct Q { char p[8]; int n; char r[4]; int *a; char s[8]; int (*cb)(int, int); };
struct X { char p[16]; struct Q **q; };
struct A { char p[16]; struct X *f16; char q[28]; int f48; char r[16]; int *f68; };
struct B { char p[8]; short idx; short off; };
void FUN_001b1100(struct A *arg0, struct B *arg1) {
    int (*temp_a2)(int, int);
    int temp_s1;
    struct Q *temp_s0;
    int x; int n1; int *a;

    temp_s1 = arg0->f68[arg1->idx] + arg1->off;
    temp_s0 = arg0->f16->q[temp_s1];
n1 = temp_s0->n - 1; a = temp_s0->a; x = a[n1];
    temp_a2 = temp_s0->cb;
    if (temp_a2 != 0) {
        temp_a2(x, arg0->f48);
    }
    temp_s0->n = temp_s0->n - 1;
    FUN_001b1490(arg0, temp_s0, temp_s1);
}

