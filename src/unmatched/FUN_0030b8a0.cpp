extern char *DAT_004c22f0[4];
extern "C" void FUN_0030b3c0(void *, char *);
struct O { char pad[8]; char *s; int len; };
extern "C" void FUN_0030b8a0(O *o) {
char *base;char *e;int i;char *t;
    base = o->s;
    if (base != 0) {
        i = o->len - 1;
        e = DAT_004c22f0[0];
        for (; i != 0; i--) {
            if ((base == 0 ? e : base)[i] == '.') {
                t = ((volatile O *)o)->s; FUN_0030b3c0(o, (t == 0 ? e : t) + i);
                return;
            }
            if ((base == 0 ? e : base)[i] == '/' || (base == 0 ? e : base)[i] == '\\') break;
        }
        FUN_0030b3c0(o, e);
    }
}
