struct X { char pad[4]; unsigned int f4; };
template <class T> class igSmartPointer;
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual X *v84(int); };
extern "C" {
int igObject_Destroy(...);
}
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *object) : p(object) {
        if (p != 0) {
            p->f4 = p->f4 + 1;
        }
    }
    igSmartPointer(const igSmartPointer &other) : p(other.p) {
        if (p != 0) {
            p->f4 = p->f4 + 1;
        }
    }
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    void release() {
        T *o;
        if ((o = p) != 0) {
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
};
extern "C" igSmartPointer<X> FUN_00301010(VC *arg1, int arg2) {
    igSmartPointer<X> created(arg1->v84(arg2));
    created.release();
    return created;
}
