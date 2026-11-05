extern "C" {
int List_RemoveWordAt(void *, int);
int igObject_Destroy(void *);
}
struct L {
    int w0; int w4; int n; int w12; int *data;
    inline int IndexOf(int v, int start, int cnt) {
        int i;
        for (i = start; i < cnt; i++) {
            if (v == data[i]) {
                return i;
            }
        }
        return -1;
    }
};
struct R { int w0; unsigned rc; };
extern "C" int ObjectList_RemoveAllRetained(L *l, int arg1, int arg2) {
    int removed = 0;
    volatile int k1;
    volatile int k2;
    k1 = arg1;
    int cnt = l->n;
    int key = k1;
    int i = l->IndexOf(key, arg2, cnt);
    while (i >= 0) {
        R *o = (R *)l->data[i];
        if (o != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(l, i);
        l->data[l->n] = 0;
        k2 = arg1;
        int cnt2 = l->n;
        int key2 = k2;
        removed++;
        i = l->IndexOf(key2, i, cnt2);
    }
    return removed;
}
