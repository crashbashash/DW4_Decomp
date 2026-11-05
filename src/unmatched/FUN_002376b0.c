struct L { char pad[8]; int count; int pad2; int *items; };
struct M { char pad[8]; struct L *list; };
struct H { char pad[28]; struct M *m; };
int FUN_0013c110();
int FUN_00457ca0();

void FUN_002376b0(struct H *arg0) {
    int n;
    int i;

    n = arg0->m->list->count;
    for (i = 0; i < n; i++) {
        FUN_00457ca0(arg0->m->list->items[i], 0);
    }
    FUN_0013c110();
}
