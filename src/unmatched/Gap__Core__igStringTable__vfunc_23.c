struct T { char pad[8]; unsigned int n; };
struct S { char pad[20]; struct T *t; };
unsigned int Gap__Core__igStringTable__vfunc_23(struct S *self, char *s) {
    unsigned int h = 0; unsigned int n;
    if (self->t != 0) { n = self->t->n; } else { n = 0; }
    if (s != 0 && n != 0) {
        while (*s != 0) { h ^= (h << 5) + (h >> 2) + (char)*s; s++; }
        h = h % n;
    } else { h = 0; }
    return h;
}
