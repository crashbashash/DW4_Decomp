typedef struct FL { char pad[8]; int n; int cap; float *data; } FL;
typedef struct A2 { char pad[72]; FL *list; } A2;
typedef struct A3 { char pad[8]; char *name; float f12; float f16; } A3;
extern "C" {
int strcmp(char *, char *);
int List_Resize(FL *, int, int);
extern char D_004e0858[];
extern char D_0050f0d0[];
extern float D_004c8fa0[4];
int FUN_00393b20(int a0, int a1, A2 *arg2, A3 *arg3);
}
int FUN_00393b20(int a0, int a1, A2 *arg2, A3 *arg3) {
    char *s;
    int idx, i, n, k, t;
    FL *l;
    const FL *view;
    FL *l2;
    int n2;
    FL *l3;
    int n3;
    int k3;
    float x, y;
    s = arg3->name ? arg3->name : D_004e0858;
    t = strcmp(s, D_0050f0d0);
    l = arg2->list;
    idx = t == 0 ? 2 : 0;
    if (l->n == 0) {
        for (i = 0; i < 4; i++) {
            l = arg2->list;
            view = l;
            k = view->n;
            if (k < l->cap) {
                l->n = l->n + 1;
            } else {
                List_Resize(l, k + 1, 4);
            }
            l->data[k] = D_004c8fa0[0];
        }
    }
    l2 = arg2->list;
    n2 = l2->n;
    x = arg3->f12;
    if (n2 != 0 && idx >= 0 && idx < n2) {
        l2->data[idx] = x;
    }
    l3 = arg2->list;
    n3 = l3->n;
    y = arg3->f16;
    if (n3 != 0) {
        k3 = idx + 1;
        if (k3 >= 0 && k3 < n3) {
            l3->data[idx + 1] = y;
        }
    }
    return 1;
}
