extern "C" {
int List_Resize(struct Rc *, int, int);
int igObject_Destroy(struct Rc *);
}
struct Rc { int vt; int rc; int n; int cap; int *data; };
struct E { int p0; int p4; int n; int p12; int *data; int def; int idx; int p28; int p32; int p36; char flag; };
struct B { int p0; int p4; int p8; int p12; struct E **data; };
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(const igSmartPointer &other) : p(other.p) {
        if (p != 0) p->rc = p->rc + 1;
    }
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    igSmartPointer &operator=(const igSmartPointer &other) {
        T *next = other.p;
        T *o;
        if (next != 0) next->rc = next->rc + 1;
        if ((o = p) != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
};
struct A { int p0; int p4; char f8; int p12; struct B *f16; int p20; int p24; igSmartPointer<Rc> f28; igSmartPointer<Rc> f32; };
extern "C" void FUN_001b0450(A *arg0, Rc *arg1) {
    Rc *a;
    int n, j;
    int *vals;
    int *keys;
    int *out;
    E **ents;
    int i;
    arg1->n = 0;
    n = arg0->f28.p->n;
    a = arg0->f32.p;
    if (n >= 0) {
        if (n <= a->cap) a->n = n; else List_Resize(a, n, 4);
    }
    j = 0;
    if (n >= 0) {
        if (n <= arg1->cap) arg1->n = n; else List_Resize(arg1, n, 4);
    }
    keys = arg0->f28.p->data;
    out = arg0->f32.p->data;
    vals = arg1->data;
    ents = arg0->f16->data;
    for (i = 0; i < n; i++) {
        int v = keys[i];
        E *e = ents[v];
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
    a = arg0->f32.p;
    if (j >= 0) {
        if (j <= a->cap) a->n = j; else List_Resize(a, j, 4);
    }
    {
        igSmartPointer<Rc> swapped(arg0->f32);
        arg0->f32 = arg0->f28;
        arg0->f28 = swapped;
    }
    arg0->f8 = 0;
}
