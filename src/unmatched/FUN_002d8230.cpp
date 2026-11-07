extern "C" {
int igObject_Destroy(void *);
int List_RemoveWordAt(void *, int);
void FUN_002d8230(char *arg0, int arg1);
}
struct O { int vt; int rc; };
struct L { int p0, p1; int n; int p3; int *data; };
struct H { char pad[28]; L * volatile list; };
void FUN_002d8230(char *arg0, int arg1) {
    int i;
    H *h = (H *)arg0;
    volatile int v;
    int idx;
    O *o;
    L *f;
    int m;
    int k;
    L *l;
    f = h->list;
    v = arg1;
    m = f->n;
    k = v;
    for (i = 0; i < m; i++) { if (k == f->data[i]) { idx = i; goto found; } }
    idx = -1;
found:
    if (-1 < idx) {
        l = h->list;
        o = (O *)l->data[idx];
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
