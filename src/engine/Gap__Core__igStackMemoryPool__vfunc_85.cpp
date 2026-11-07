struct S { char pad[116]; unsigned start; unsigned long long len; };
extern "C" bool Gap__Core__igStackMemoryPool__vfunc_85(S *s, unsigned a) {
    bool r = false;
    if (a >= s->start) {
        if ((unsigned long long)a < (unsigned long long)s->start + s->len) r = true;
    }
    return r;
}
