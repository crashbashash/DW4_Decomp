extern "C" {
int ObjectList_AppendRetained(void *, int);
}
struct L {
    int a, b; int n; int c; int *items;
    int IndexOf(int k) { int i; for (i = 0; i < n; i++) { if (k == items[i]) { return i; } } return -1; }
};
extern "C" int ObjectList_AppendUniqueRetained(L *arg0, int arg1) {
    volatile int key = arg1;
    int n = arg0->n;
    int kk = key;
    int r = arg0->IndexOf(kk);
    if (r == -1) {
        r = n;
        ObjectList_AppendRetained(arg0, arg1);
    }
    return r;
}
