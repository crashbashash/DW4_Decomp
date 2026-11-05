typedef struct L { int f0; int f4; int n; int cap; int data; } L;
int memcpy(int a, int b, int c);
int List_Resize(L *l, int n, int sz);
void List_AppendBytes(L *l, int cnt, int src, int sz) {
    int old;
    int nn;
    if (cnt >= 0 && cnt != 0) {
        old = l->n;
        nn = old + cnt;
        if (nn <= l->cap) { l->n = nn; } else { List_Resize(l, nn, sz); }
        memcpy(l->data + old * sz, src, cnt * sz);
    }
}
