extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer() : p(0) {}
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            --o->references;
            if ((o->references & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    igSmartPointer &operator=(T *next) {
        T *o;
        if (next) ++next->references;
        if ((o = p) != 0) {
            --o->references;
            if ((o->references & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
};
struct Item { char p[12]; T *held; };
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
    virtual bool v26(igSmartPointer<T> &);
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual int v31(T *);
};
static inline void storeHeld(Lst *list, int index, const igSmartPointer<T> &value) {
    T *held = value.p;
    Item *it = list->data[index];
    T *old;
    if (held) ++held->references;
    old = it->held;
    if (old) {
        --old->references;
        if ((old->references & 0x7FFFFF) == 0)
            igObject_Destroy(old);
    }
    it->held = held;
}
extern "C" bool FUN_0022b910(Own *arg0, V *arg1) {
    bool r;
    bool ok;
    Lst *l;
    int n;
    int i;
    T *t;
    ok = true;
    l = arg0->f28;
    n = l->count;
    for (i = 0; i < n; i++) {
        igSmartPointer<T> held;
        t = l->data[i]->held;
        held = t;
        if (arg1->v31(held.p)) {
            r = arg1->v26(held);
            storeHeld(l, i, held);
            ok = ok || r;
        }
    }
    return ok;
}
