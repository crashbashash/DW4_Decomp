struct R { int f0; unsigned int f4; };
struct G { char pad[56]; int f38; };
struct Res {
    int v;
    Res() {}
    Res(const Res &o) { v = o.v; }
    bool operator==(const Res &o) const { return v == o.v; }
};
class Dev {
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
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual Res get(int, int);
};
extern "C" {
extern Res DAT_004fb418[4];
extern Res DAT_004fb410[4];
extern char *DAT_004c2228[4];
extern G *DAT_00586dc8[4];
int FUN_00306360(int, char *, int);
void igObject_Destroy(void *);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer() : p(0) {}
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
};
extern "C" Res Gap__Core__igMemoryPoolContextInfo__vfunc_25(Dev *arg1, int arg2, char *arg3) {
    igSmartPointer<R> unused;
    int index;
    char *name;
    if (arg2 == 0) {
        arg2 = DAT_00586dc8[0]->f38;
    }
    if (arg2 == 0) {
        return DAT_004fb418[0];
    }
    if ((arg3 == 0) || (name = arg3, (*arg3 == 0))) {
        arg3 = DAT_004c2228[0];
        name = arg3;
    }
    index = FUN_00306360(arg2, name, 0);
    if (index == -1) {
        return DAT_004fb418[0];
    }
    if (arg1->get(arg2, index) == DAT_004fb410[0]) {
        return DAT_004fb410[0];
    }
    return DAT_004fb418[0];
}
