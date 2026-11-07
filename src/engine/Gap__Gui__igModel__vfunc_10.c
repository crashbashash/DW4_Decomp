int FUN_00457e90();
struct L { char pad[8]; int n; int pad2; int *arr; };
struct O { char pad[8]; struct L *l; };
void Gap__Gui__igModel__vfunc_10(struct O *arg0) {
    int n;
    int i;
    int p;

    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        p = arg0->l->arr[i];
        if (p != 0) {
            FUN_00457e90(p, 0);
        }
    }
}
