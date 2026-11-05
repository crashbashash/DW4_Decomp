int igStrCmp();
extern int DAT_004e0858[4];
struct Item { char p[8]; int *name; };
struct L { char p0[8]; int count; char p1[4]; struct Item **items; };
struct O { char p0[20]; struct L *list; };
struct Item *FUN_002f8be0(struct O *arg0, int arg1) {
    int i;
    int n;
    struct Item *it;
    int *name;
    i = 0;
    n = arg0->list->count;
    for (; i < n; i++) {
        it = arg0->list->items[i];
        if (it != 0) {
            name = it->name != 0 ? it->name : DAT_004e0858;
            if (igStrCmp(name, arg1) == 0) return it;
        }
    }
    return 0;
}
