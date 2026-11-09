class VC_220_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(); };
class VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(void *); };
typedef struct R { char pad[4]; unsigned int f4; char pad2[36]; char f44; } R;
extern "C" {
void *FUN_002b7b70(int);
R *FUN_002b7f40(int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(void *);
extern int DAT_00587038[4];
extern void *DAT_005871d0[4];
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
extern "C" void FUN_0030e480(void) {
    DAT_005871d0[0] = FUN_002b7b70(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    igSmartPointer<R> added(FUN_002b7f40(Memory_GetAllocatorBySelector(DAT_00587038[0])));
    added.get()->f44 = 1;
    ((VC_220_0 *)added.get())->vX();
    ((VC_96_1 *)DAT_005871d0[0])->vX(added.get());
}
