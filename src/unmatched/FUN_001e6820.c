struct L { char pad[8]; int count; int pad2; int *items; };
struct D { char pad[8]; int f8; };
int ObjectList_AppendRetained();

int FUN_001e6820(struct D *arg0, struct L *arg1) {
    int n;
    int i;

    n = arg1->count;
    for (i = 0; i < n; i++) {
        ObjectList_AppendRetained(arg0->f8, arg1->items[i]);
    }
    return 1;
}
