typedef struct { char pad[8]; int cnt; int cap; int *data; } L;
typedef struct { char pad[12]; L *l12; L *l16; } T;
int List_Resize();
int FUN_0022aac0(T *arg0, int arg1) {
    L *a;
    int n;
    L *b;
    a = arg0->l12;
    if (0 <= a->cap) {
        a->cnt = 0;
    } else {
        List_Resize(a, 0, 4);
    }
    b = arg0->l12;
    n = (*(int const *)&b->cnt);
    if (n < b->cap) {
        b->cnt = b->cnt + 1;
    } else {
        List_Resize(b, n + 1, 4);
    }
    b->data[n] = arg1;
    a = arg0->l16;
    if (0 <= a->cap) {
        a->cnt = 0;
    } else {
        List_Resize(a, 0, 4);
    }
    return arg1;
}
