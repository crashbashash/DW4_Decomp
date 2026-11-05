struct E { int p; int f4; };
struct S { char p[76]; int n; };
struct E *FUN_00320ea0();
int FUN_00320ee0(struct S *arg0, int arg1, int arg2) {
    int i;
    int t;
    for (i = 0; i < arg0->n; i++) {
        t = FUN_00320ea0(arg0, i)->f4;
        if (t == arg1) {
            if (arg2-- == 0) {
                return i;
            }
        }
    }
    return -1;
}
