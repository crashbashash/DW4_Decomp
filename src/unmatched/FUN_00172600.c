typedef struct L { int p0; int p4; int count; int cap; char *data; } L;
typedef struct S { char p[972]; L *l972; L *l976; L *l980; int p984; L *l988; L *l992; L *l996; L *l1000; } S;
int List_Resize();
int Matrix44_Copy();
#define PUSH(f) do { int n; L *l; int v; l = arg0->f; v = l->count; if (v != 0) { n = ((volatile L *)l)->count; if (n < l->cap) { l->count = v + 1; } else { List_Resize(l, n + 1, 64); } Matrix44_Copy(l->data + (n << 6), l->data + ((n - 1) << 6)); } } while (0)
void FUN_00172600(S *arg0, int arg1) {
    switch (arg1) {
    case 0:
        PUSH(l972);
        break;
    case 1:
        PUSH(l976);
        break;
    case 2:
        PUSH(l980);
        break;
    case 10:
        PUSH(l988);
        break;
    case 11:
        PUSH(l992);
        break;
    case 12:
        PUSH(l996);
        break;
    case 13:
        PUSH(l1000);
        break;
    }
}
