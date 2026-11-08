int ObjectList_AppendRetained();
struct L { char pad[8]; int n; int p12; int *arr; };
struct A { char pad[24]; struct L *f24; };
static inline int indexOf(struct L *list, const int *value) {
    int i = 0;
    int n = list->n;
    if (0 < n) {
        int *p = list->arr;
        int wanted = *value;
        do {
            if (wanted == *p) {
                return i;
            }
            i++;
            p++;
        } while (i < n);
    }
    return -1;
}
void FUN_00467030(struct A *arg0, int arg1) {
    struct L *list = arg0->f24;
    /* matching construct: retail keeps the value in a stack slot */
    volatile int value = arg1;
    if (indexOf(list, (const int *)&value) < 0) {
        ObjectList_AppendRetained(arg0->f24, arg1);
    }
}
