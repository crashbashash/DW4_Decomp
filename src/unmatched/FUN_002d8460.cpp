struct R { char pad[4]; int f4; };
extern "C" {
R *FUN_002d7c50();
int igObject_Destroy(R *);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {
        T *o = p;
        if (o != 0) {
            o->f4 = o->f4 + 1;
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
    T *get() const { return p; }
};
extern "C" int FUN_002d8460(void) {
    igSmartPointer<R> h(FUN_002d7c50());
    if (h.get() != 0) {
        return 1;
    }
    return 0;
}
