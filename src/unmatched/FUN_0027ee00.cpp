extern "C" void *FUN_00280240(unsigned sz, void *p);
struct E { char pad[0x60]; E() {} };
struct O {
    int f0, f4, f8, f12; void *f16; int f20, f24, f28, f32, f36, f40, f44, f48;
    int f52, f56, f60; int f64; char f68; char p69[3]; int f72, f76, f80, f84, f88;
    char f92, f93; char p94[2]; int f96, f100, f104; int f108; char f112; char p113[55];
    char f168, f169, f170, f171; int f172; E e[1];
    static void *operator new(unsigned sz, void *p) { return FUN_00280240(sz, p); }
    O() : f40(-1), f44(-1), f52(0), f56(0), f60(0), f68(0), f72(0), f76(0), f80(0), f84(0), f92(0), f93(0), f96(0), f100(0), f104(0), f112(0) {
        f12 = 0; f32 = 0; f36 = 0;
    }
};
extern "C" void FUN_0027ee00(void *pool, int n) {
    O *o = new (pool) O;
    o->f169 = 0; o->f16 = &o->e; o->f170 = 0; o->f171 = 0;
    o->f28 = n * 0x60;
}
