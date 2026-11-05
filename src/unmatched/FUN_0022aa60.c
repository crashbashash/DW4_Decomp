struct A { char pad[8]; int *arr; int cnt; };
struct B { char pad[8]; int p; int idx; };
int FUN_0022aa60(struct B *arg0) {
    struct A *a;
    int i;
    a = *(struct A **)((char *)arg0->p + 40);
    i = arg0->idx;
    if ((i >= a->cnt) || (i < 0)) {
        return 0;
    }
    return a->arr[i];
}
