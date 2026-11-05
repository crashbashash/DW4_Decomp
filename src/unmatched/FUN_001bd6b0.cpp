extern "C" int List_Resize(...);
struct Arr { char p[8]; int n; int cap; int *data;
    int Find(int pv, int i) {
        int c = n;
        int w = pv;
        for (; i < c; i++) {
            if (data[i] == w) return i;
        }
        return -1;
    }
};
struct B { char p[472]; Arr *list; };
struct A { char p[32]; Arr *f32; Arr *f36; Arr *f40; };

extern "C" void FUN_001bd6b0(A *arg0, B *arg1);
void FUN_001bd6b0(A *arg0, B *arg1) {
    int idx;
    Arr *o;
    int n;
    int i;
    int j;
    int *p;
    int v;
    int idx2;
    Arr *o2;
    volatile int t1, t2;
    n = arg1->list->n;
    for (i = 0; i < n; i++) {
        v = arg1->list->data[i];
        t1 = v;
        j = arg0->f32->Find(t1, 0);
        while (j != -1) {
            o = arg0->f36;
            idx = o->n;
            if (idx < o->cap) {
                o->n = ((volatile Arr *)o)->n + 1;
            } else {
                List_Resize(o, idx + 1, 4);
            }
            o->data[idx] = i;
            p = arg0->f32->data + j;
            o2 = arg0->f40;
            idx2 = o2->n;
            if (idx2 < o2->cap) {
                o2->n = ((volatile Arr *)o2)->n + 1;
            } else {
                List_Resize(o2, idx2 + 1, 4);
            }
            o2->data[idx2] = (int)p;
            t2 = v;
            j = arg0->f32->Find(t2, j + 1);
        }
    }
}
