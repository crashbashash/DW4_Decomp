extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
}
struct Item { char p[12]; T *f12; };
struct Lst { char p[8]; int count; char q[4]; Item **data; };
struct Own { char p[28]; Lst *f28; };
class V {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25();
    virtual bool v26(T **);
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual int v31(T *);
};
extern "C" bool FUN_0022b910(Own *arg0, V *arg1) {
    T *o;
    bool r;
    bool ok;
    Lst *l;
    int n;
    T *old;
    int i;
    T *s0;
    Item *it;
    T *t;
    T *volatile sp;
    T *e;
    ok = true;
    l = arg0->f28;
    n = l->count;
    for (i = 0; i < n; i++) {
        sp = 0;
        t = l->data[i]->f12;
        if (t) ++t->references;
        o = sp;
        if (o) {
            --o->references;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0)
                igObject_Destroy(o);
        }
        sp = t;
        if (arg1->v31(sp)) {
            r = arg1->v26((T **)&sp);
            it = l->data[i];
            s0 = sp;
            if (s0) ++s0->references;
            old = it->f12;
            if (old) {
                --old->references;
                if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
                    igObject_Destroy(old);
            }
            it->f12 = s0;
            ok = ok || r;
        }
        e = sp;
        if (e) {
            --e->references;
            if (((unsigned long long)(long long)e->references & 0x7fffffULL) == 0)
                igObject_Destroy(e);
        }
    }
    return ok;
}
