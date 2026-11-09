class VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *vX(); };
struct V3 { float x, y, z; };
struct X { char pad[4]; unsigned int f4; V3 a; V3 b; };
struct Y { char pad[12]; VC_100_0 *f12; };
extern "C" {
X *FUN_0018a660(...);
int FUN_00190060(...);
int FUN_001b1fa0(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
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
extern "C" int FUN_001b23e0(int arg0, Y *arg1) {
    V3 sp40;
    V3 sp30;
    igSmartPointer<X> created(FUN_0018a660(igObject_GetAllocator()));
    FUN_001b1fa0(arg1, &sp40, &sp30);
    created.get()->a = sp40;
    created.get()->b = sp30;
    FUN_00190060(arg0, created.get());
    return (((int)((unsigned int) (*arg1->f12->vX() & 0xF0) >> 4)) & 0xFF) <= 0;
}
