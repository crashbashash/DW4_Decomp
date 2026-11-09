extern "C" {
void *FUN_002ba650(...);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
extern int DAT_004fb410[4];
}
struct R { int v; R() {} R(int x) { v = x; } };
class Rc {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual R v92();
    virtual R v96();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual R v132(int);
    unsigned int refCount;
};
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    igSmartPointer(const igSmartPointer &other) : p(other.p) {
        if (p != 0) {
            p->refCount = p->refCount + 1;
        }
    }
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->refCount = o->refCount - 1;
            if ((o->refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    void clear() {
        T *old = p;
        if (old != 0) {
            old->refCount = old->refCount - 1;
            if ((old->refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        p = 0;
    }
    igSmartPointer &operator=(const igSmartPointer &other) {
        T *object = other.p;
        T *old;
        if (object != 0) {
            object->refCount = object->refCount + 1;
        }
        old = p;
        if (old != 0) {
            old->refCount = old->refCount - 1;
            if ((old->refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        p = object;
        return *this;
    }
};
struct OB { char pad[116]; igSmartPointer<Rc> lock; };
extern "C" {
R Gap__Core__igMallocMemoryPool__vfunc_34(OB *arg1, unsigned char arg2) {
    R a;
    R b;
    R c;
    if (arg2 == 0) {
        igSmartPointer<Rc> held(arg1->lock);
        arg1->lock.clear();
        if (held.p != 0) {
            a = held.p->v132(1);
            b = held.p->v96();
        }
        arg1->lock.clear();
    } else if (arg2 == 1) {
        if (arg1->lock.p != 0) return R(DAT_004fb410[0]);
        igSmartPointer<Rc> created((Rc *)FUN_002ba650(igObject_GetAllocator(arg1)));
        c = created.p->v92();
        arg1->lock = created;
    }
    return R(DAT_004fb410[0]);
}
}
