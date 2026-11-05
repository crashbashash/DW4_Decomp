typedef struct L { int f0; int f4; int n; int cap; int data; } L;
int memmove(int, int, int);
void List_RemoveWordAt(L *l, int i) {
    int n = l->n; int d;
    if (n <= 0 || i < 0 || i >= n) return;
    if (i != n - 1) { d = l->data + i * 4; memmove(d, d + 4, 4 * (n - (i + 1))); }
    l->n = l->n - 1; }
