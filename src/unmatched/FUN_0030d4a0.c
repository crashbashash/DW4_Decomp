struct In { int p0, p4; int len; int p12; char *buf; };
struct Out { int p0, p4, p8, p12; struct In *in; };
int FUN_0030d4a0(struct Out *o, int i) {
    struct In *s = o->in;
    char *p = s->buf + i;
    int n = s->len;
    if (p == 0 || i < 0) return -1;
    while (i < n) {
        char c = *p;
        i++;
        if (c == 0) {
            if (i >= n) goto bad;
            return i;
        }
        p++;
    }
bad:
    return -1;
}
