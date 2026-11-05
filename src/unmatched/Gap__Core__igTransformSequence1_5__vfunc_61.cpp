typedef struct V { float x, y, z; } V;
typedef struct L { int pad[2]; int count; int cap; V *data; } L;
typedef struct LL { int pad[2]; int count; } LL;
typedef struct T { char pad[56]; LL *tl; L *a; L *b; L *c; unsigned char flags; } T;
extern "C" int List_Resize(...);
struct Set { static inline void put(L *l, int i, V *p) {
    V *e;
    if (l->count != 0 && i >= 0 && i < l->count) {
        e = l->data + i; e->x = p->x; e->y = p->y; e->z = p->z;
    }
} };
extern "C" void Gap__Core__igTransformSequence1_5__vfunc_61(T *t, int idx, int ch, V *p, V *q) {
    L *l;
    int n;
    int i;
    V *e;
    if (t->flags & ch) {
        l = 0;
        if (ch & 1) {
            l = t->a;
        } else if ((ch & 2) || (ch & 4)) {
            l = t->b;
        } else if (ch & 8) {
            l = t->c;
        }
        if (l->count == 0) {
            n = t->tl->count * 2;
            if (n >= 0) {
                if (n <= l->cap) {
                    l->count = n;
                } else {
                    List_Resize(l, n, 12);
                }
            }
        }
        Set::put(l, idx * 2, p);
        Set::put(l, (idx << 1) + 1, q);
    }
}
