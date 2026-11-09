typedef struct { int p[2]; int cnt; int p2; void **arr; } I;
typedef struct { int p[4]; I * list; } H;
typedef struct { int p[2]; int id; int p2[3]; unsigned busy; } T;
int FUN_001ab920(H *a, int id, T **out) {
    int i;
    int n = (*(I * const *)&a->list)->cnt;
    for (i = 0; i < n; i++) {
        T *t = (T *)a->list->arr[i];
        unsigned b = t->busy != 0u;
        if (!b && t->id == id) { *out = t; return i; }
    }
    *out = 0;
    return -1;
}
