class V168 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(int, char *); };
struct Q { char p0[12]; int count; };
struct M { char p0[12]; V168 *obj; };
struct O { char p0[24]; char buf[1]; char p1[23]; M *m; };
extern "C" void Gap__Gui__igTextElement__vfunc_24(O *arg0);
void Gap__Gui__igTextElement__vfunc_24(O *arg0) {
    int i;
    int n;
    struct Q *q = (struct Q *)arg0->m->obj;
    if (q != 0) {
        n = q->count;
        for (i = 0; i < n; i++) {
            arg0->m->obj->vX(i, arg0->buf);
        }
    }
}
