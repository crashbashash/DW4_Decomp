int igObject_IsKindOf();
int List_Resize();
extern int DAT_0055f208[4];
struct Arr { char p[8]; int n; int cap; int *data; };
struct B { char p[12]; struct Arr *list; };
struct A { char p[32]; struct Arr *out; };
void FUN_001bd170(struct A *arg0, struct B *arg1) {
    int i;
    int n;
    int idx;
    struct B *c;
    struct Arr *o;
    n = arg1->list->n;
    for (i = 0; i < n; i++) {
        c = (struct B *)arg1->list->data[i];
        if (igObject_IsKindOf(c, DAT_0055f208[0]) != 0) {
            FUN_001bd170(arg0, c);
        } else {
            o = arg0->out;
            idx = o->n;
            if (idx < o->cap) {
                o->n = ((const struct Arr *)o)->n + 1;
            } else {
                List_Resize(o, idx + 1, 4);
            }
            o->data[idx] = (int)c;
        }
    }
}
