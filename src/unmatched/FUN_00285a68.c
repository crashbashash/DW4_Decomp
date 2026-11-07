struct B { int a; int b; int c; };
struct S { char p[0x148]; struct B b; };
void FUN_00285a68(struct S *arg0, int *arg1, int *arg2) {
    struct B *p = &arg0->b;
    if (arg1 != 0) {
        *arg1 = p->a;
    }
    if (arg2 != 0) {
        *arg2 = p->c;
    }
}
