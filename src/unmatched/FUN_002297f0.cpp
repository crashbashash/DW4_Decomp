#pragma inline_depth(4)
extern "C" int igObject_Destroy(...);
struct Obj { int w0; unsigned refs; };
template <class T> struct igSmartPointer {
    T *p;
    ~igSmartPointer() {
        T *q = p;
        if (q != 0) {
            q->refs = q->refs - 1;
            if ((q->refs & 0x7fffff) == 0) igObject_Destroy(q);
        }
    }
    void operator=(T *n) {
        T *q = p;
        if (q != 0) {
            q->refs = q->refs - 1;
            if ((q->refs & 0x7fffff) == 0) igObject_Destroy(q);
        }
        p = n;
    }
};
struct S {
    igSmartPointer<Obj> a; igSmartPointer<Obj> b; igSmartPointer<Obj> c;
    ~S() { a = 0; b = 0; c = 0; }
};
extern "C" S *FUN_002297f0(S *s);
S *FUN_002297f0(S *s) {
    s->~S();
    return s;
}
