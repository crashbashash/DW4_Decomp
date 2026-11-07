extern "C" {
int ObjectList_AppendRetained(void *, int);
}
struct K { volatile int p; K(int x) { p = x; } };
struct L {
    int a, b; int n; int c; int *items;
};
inline int indexOf(L *l, const K &v) {
    int i;
    int n = l->n;
    int key = v.p;
    for (i = 0; i < n; i++) {
        if (key == l->items[i]) {
            return i;
        }
    }
    return -1;
}
extern "C" int ObjectList_AppendUniqueRetained(L *arg0, int arg1) {
    int r = indexOf(arg0, K(arg1));
    if (r == -1) {
        r = arg0->n;
        ObjectList_AppendRetained(arg0, arg1);
    }
    return r;
}
