int FUN_001af860();
int FUN_001b0dc0();
struct A { int p0; int p1; int p2; int p3; int *arr; };
struct B { int p0; int p1; int f8; int p3; int p4; int f20; };
struct O { int p0; int p1; int p2; int n; struct A *l16; int p5; struct B *b24; struct B *b28; char pad[12]; struct B *b44; char pad2[16]; struct B *b64; };
void Gap__Sg__igAttrStackManager__vfunc_23(struct O *arg0) {
    int var_s0;
    if (arg0->n > 0) {
        for (var_s0 = 0; var_s0 < arg0->n; var_s0++) {
            FUN_001af860(arg0->l16->arr[var_s0]);
        }
        arg0->b24->f8 = 0;
        arg0->b28->f8 = 0;
        FUN_001b0dc0(arg0);
        arg0->b44->f8 = 0;
        arg0->b64->f20 = 0;
    }
}
