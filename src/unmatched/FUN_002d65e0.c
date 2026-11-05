struct L { int p0; int p4; int n; int pc; int *arr; };
struct O { int p0; int p4; int p8; int pc; struct L *list; };
int igObject_IsKindOf();
int FUN_002d65e0(struct O *arg0, int arg1) {
    int i;
    for (i = 0; i < arg0->list->n; i++) {
        if (igObject_IsKindOf(arg0->list->arr[i], arg1) != 0) {
            return arg0->list->arr[i];
        }
    }
    return 0;
}
