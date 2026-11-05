int List_Resize();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
struct L { char pad8[8]; int n; int cap; int *data; };
struct S { char pad16[16]; struct L *f16; };
void FUN_002d3aa0(int *arg0, struct S *arg1, int arg2) {
    struct L *l; int t, n, *data, cnt, i;
    l = arg1->f16;
    data = l->data;
    n = l->n;
    cnt = 0;
    if (arg2 == 0) {
        if (0 <= l->cap) { l->n = 0; } else { List_Resize(l, 0, 4); }
        *arg0 = DAT_004fb410[0];
        return;
    }
    for (i = 0; i < n; i++) {
        if (data[0] == 0) {
            cnt = cnt + 1;
            if (cnt == arg2) {
                t = i + 1;
                if (t >= 0) {
                    if (t <= l->cap) { l->n = t; } else { List_Resize(l, t, 4); }
                }
                *arg0 = DAT_004fb410[0];
                return;
            }
        }
    }
    *arg0 = DAT_004fb418[0];
}
