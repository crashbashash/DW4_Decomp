extern "C" {
int igObject_Destroy(void *);
int List_RemoveWordAt(void *, int);
void FUN_002d8230(char *arg0, int arg1);
}
struct O { int vt; int rc; };
struct L {
    int p0, p1; int n; int p3; int *data;
    static int FindKey(L *l, int key) {
        volatile int v = key;
        int i; int m = l->n; int k = v;
        for (i = 0; i < m; i++) { if (k == l->data[i]) { return i; } }
        return -1;
    }
};
void FUN_002d8230(char *arg0, int arg1) {
    int idx;
    idx = L::FindKey(*(L * volatile *)(arg0 + 28), arg1);
    if (-1 < idx) {
        L *l = *(L * volatile *)(arg0 + 28);
        O *o = (O *)l->data[idx];
        if (o != 0) {
            o->rc = o->rc - 1;
            if (((unsigned long long)((long long)o->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(l, idx);
        l->data[l->n] = 0;
    }
}
