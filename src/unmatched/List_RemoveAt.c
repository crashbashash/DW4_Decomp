typedef struct L { int f0; int f4; int n; int cap; int data; } L;
int memmove(int, int, int, int);
void List_RemoveAt(L *l, int i, int sz) {
    int n = l->n; int d;
 if (n <= 0 || i < 0 || i >= n) return; if (i != n - 1) { d = l->data + i * sz; memmove(d, d + sz, sz * (n - (i + 1)), n); } l->n = l->n - 1;
}
