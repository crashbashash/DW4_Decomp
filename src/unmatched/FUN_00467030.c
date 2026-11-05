int ObjectList_AppendRetained();
struct L { char pad[8]; int n; int p12; int *arr; };
struct A { char pad[24]; struct L *f24; };
void FUN_00467030(struct A *arg0, int arg1) {
    volatile int sp1C;
    struct L *l;
    int i;
    int n;
    int *p;
    int k;

    l = arg0->f24;
    sp1C = arg1;
    n = l->n;
    i = 0;
    if (0 < n) {
        p = l->arr;
        k = sp1C;
loop:
        if (k == *p) {
            asm { nop }
        } else {
            i += 1;
            p += 1;
            if (i >= n) {
                goto nf;
            }
            goto loop;
        }
    } else {
nf:
        i = -1;
    }
    if (i < 0) {
        ObjectList_AppendRetained(*(struct L * volatile *)&arg0->f24, arg1);
    }
}
