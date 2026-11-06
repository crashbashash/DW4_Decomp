struct L { int pad[2]; int count; int cap; };
struct T { char pad[8]; struct L *a; struct L *b; struct L *c; char pad2[36]; struct L *d; char pad3[12]; unsigned char flags; };
int List_Resize();
void Gap__Core__igTransformSequence1_5__vfunc_38(struct T *t, int n) {
    struct L *l;
    l = t->d;
    if (n >= 0) {
        if (n <= l->cap) {
            l->count = n;
        } else {
            List_Resize(l, n, 8);
        }
    }
    if (t->flags & 1) {
        l = t->a;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                List_Resize(l, n, 12);
            }
        }
    }
    if ((t->flags & 2) || (t->flags & 4)) {
        l = t->b;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                List_Resize(l, n, 16);
            }
        }
    }
    if (t->flags & 8) {
        l = t->c;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                List_Resize(l, n, 12);
            }
        }
    }
}
