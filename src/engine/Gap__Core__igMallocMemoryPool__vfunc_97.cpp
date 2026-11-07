extern "C" int igObject_Destroy(void *);
extern unsigned char GPR_00554dbc;
struct Ref { int pad; int rc; };
class O { public:virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void v49();
union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } f4; char pad[104]; char f112; int f116; int f120; int f124; long long f128; long long f136; short f144; Ref *f148; int f152; int f156;
};
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_97(O *o) {
    Ref *r;
    o->f4.w = 0;
    o->f4.b.cnt = 1;
    *((char *)o + 7) = 0;
    o->f120 = 0;
    o->v49();
    o->f124 = 0;
    o->f128 = (long long)(unsigned __int128)(unsigned long long)-1LL;
    o->f136 = 0;
    o->f144 = 1;
    r = o->f148;
    if (r != 0) {
        r->rc = r->rc - 1;
        if (((unsigned long long)((long long)r->rc << 0x29) >> 0x29) == 0) igObject_Destroy(r);
    }
    o->f148 = 0;
    o->f112 = 0;
    GPR_00554dbc += 1;
    r = (Ref *)o->f116;
    if (r != 0) {
        r->rc = r->rc - 1;
        if (((unsigned long long)((long long)r->rc << 0x29) >> 0x29) == 0) igObject_Destroy(r);
    }
    o->f116 = 0;
    o->f152 = 1;
    o->f156 = 12;
}
