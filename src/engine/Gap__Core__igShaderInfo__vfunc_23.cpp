extern "C" {
int FUN_002e2d30(int, void *, int *, int, int, void *, void *);
extern int DAT_004e0858[4];
}
struct L {
    int a, b; int n; int c; int *items;
    int IndexOf(int k, int cnt) { int i; for (i = 0; i < cnt; i++) { if (k == items[i]) { return i; } } return -1; }
};
struct I { char pad[8]; int *p8; char pad2[8]; int f20; };
struct O { char pad[20]; L *list; };
extern "C" int Gap__Core__igShaderInfo__vfunc_23(O *arg0, int arg1, int arg2) {
    L *temp_a5 = arg0->list;
    volatile int key = arg2;
    int cnt = temp_a5->n;
    int kk = key;
    int idx = temp_a5->IndexOf(kk, cnt);
    I *temp_a0;
    int *var_a2;
    if (idx == -1) {
        return 0;
    }
    temp_a0 = (I *)(*(L * volatile *)&arg0->list)->items[idx];
    if (temp_a0->f20 == 2) {
        return 0;
    }
    var_a2 = temp_a0->p8;
    if (var_a2 != 0) {
        var_a2 = (int *)var_a2;
    } else {
        var_a2 = &DAT_004e0858[0];
    }
    FUN_002e2d30(arg1, arg0, var_a2, arg2, idx, temp_a5, arg0);
    return 1;
}
