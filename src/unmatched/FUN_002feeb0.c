struct L { int a, b; int n; int c; int *items; };
struct K { int a, b; int off; };
int FUN_002feeb0(struct L *arg0, struct K *arg1, int arg2) {
    int i;
    int v;
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < arg0->n; i++) {
        v = arg0->items[i];
        if (v != 0 && arg2 == *(int *)(v + arg1->off)) {
            return v;
        }
    }
    return 0;
}
