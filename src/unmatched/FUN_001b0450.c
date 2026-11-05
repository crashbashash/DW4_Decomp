int List_Resize();
int igObject_Destroy();
struct Rc { int vt; int rc; int n; int cap; int *data; };
struct E { int p0; int p4; int n; int p12; int *data; int def; int idx; int p28; int p32; int p36; char flag; };
struct B { int p0; int p4; int p8; int p12; struct E **data; };
struct A { int p0; int p4; char f8; int p12; struct B *f16; int p20; int p24; struct Rc *f28; struct Rc *f32; };
void FUN_001b0450(struct A *arg0, struct Rc *arg1) {
    struct Rc * volatile sp5C;
    struct Rc *t;
    struct Rc *a;
    int n, j;
    int *vals;
    int *keys;
    int *out;
    struct E **ents;
    int i;
    arg1->n = 0;
    n = arg0->f28->n;
    a = arg0->f32;
    if (n >= 0) {
        if (n <= a->cap) a->n = n; else List_Resize(a, n, 4);
    }
    j = 0;
    if (n >= 0) {
        if (n <= arg1->cap) arg1->n = n; else List_Resize(arg1, n, 4);
    }
    keys = arg0->f28->data;
    out = arg0->f32->data;
    vals = arg1->data;
    ents = arg0->f16->data;
    for (i = 0; i < n; i++) {
        int v = keys[i];
        struct E *e = ents[v];
        int x;
        int m;
        if (e->idx >= 0) x = e->data[e->idx];
        else { m = e->n; if (m != 0) { int k = m - 1; x = e->data[k]; } else x = e->def; }
        if (x != e->def) {
            out[j] = v;
            vals[j] = x;
            j++;
        } else {
            e->flag = 0;
        }
    }
    if (j >= 0) {
        if (j <= arg1->cap) arg1->n = j; else List_Resize(arg1, j, 4);
    }
    a = arg0->f32;
    if (j >= 0) {
        if (j <= a->cap) a->n = j; else List_Resize(a, j, 4);
    }
    sp5C = arg0->f32;
    a = sp5C;
    if (a != 0) a->rc = a->rc + 1;
    t = arg0->f28;
    if (t != 0) t->rc = t->rc + 1;
    a = arg0->f32;
    if (a != 0) {
        a->rc = a->rc - 1;
        if ((a->rc & 0x7FFFFF) == 0) igObject_Destroy(a);
    }
    arg0->f32 = t;
    t = sp5C;
    if (t != 0) t->rc = t->rc + 1;
    a = arg0->f28;
    if (a != 0) {
        a->rc = a->rc - 1;
        if ((a->rc & 0x7FFFFF) == 0) igObject_Destroy(a);
    }
    arg0->f28 = t;
    a = sp5C;
    if (a != 0) {
        a->rc = a->rc - 1;
        if ((a->rc & 0x7FFFFF) == 0) igObject_Destroy(a);
    }
    arg0->f8 = 0;
}
