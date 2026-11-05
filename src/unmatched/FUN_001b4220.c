int FUN_001b0ea0();
int FUN_001b4090();
struct Q { char p0[8]; int count; char pc[4]; int *data; };
struct A { char p0[144]; struct Q *f144; };
struct B { char p0[52]; int f52; };

void FUN_001b4220(struct A *arg0, struct B *arg1) {
    int temp_s2;
    int n;
    int i;
    struct Q *q;

    q = arg0->f144;
    temp_s2 = arg1->f52;
    n = 0;
    if (q != 0) {
        n = q->count;
    }
    if (n > 8) {
        n = 8;
    }
    for (i = 0; i < n; i++) {
        FUN_001b4090(arg0, i, FUN_001b0ea0(temp_s2, arg0->f144->data[i]));
    }
}
