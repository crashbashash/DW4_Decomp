extern char *DAT_004c22f0[4];
extern "C" void FUN_0030b3c0(void *, char *);
static inline char *pick(char *a, char *d) { if (a == 0) { return d; } return a; }
struct O { char pad[8]; char *s; int len; };
extern "C" void FUN_0030b8a0(O *o) {
    int i;
    char *e;
    char *t;
    char *base;
    base = o->s;
    if (base != 0) {
        i = o->len - 1;
        e = DAT_004c22f0[0];
        for (; i != 0; i--) {
            if (pick(base, e)[i] == '.') {
                t = ((volatile O *)o)->s; FUN_0030b3c0(o, (t == 0 ? e : t) + i);
                return;
            }
            if (pick(base, e)[i] == '/' || pick(base, e)[i] == '\\') break;
        }
        FUN_0030b3c0(o, e);
    }
}
