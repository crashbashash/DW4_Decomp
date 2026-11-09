typedef struct { char p[8]; int n; char q[4]; char *arr; } T;
static inline int n_of(const T *list) { return list->n; }
void Gap__Sg__igCommonTraversal__vfunc_27(void *arg0, long long arg1) {
    T *t;

    t = *(T **)((char *)(arg0) + 240);
    if (n_of(t) == 0) {
        *(char *)((char *)(arg0) + 48) = 0;
        *(long long *)((char *)(arg0) + 16) = arg1;
    } else {
        *(long long *)(t->arr + t->n * 8 - 8) = arg1;
    }
}
