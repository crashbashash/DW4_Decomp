struct L { char pad[8]; int count; int pad2; void ***items; };
struct H { char pad[52]; struct L *list; };
class V156 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(int, int); };
extern "C" void FUN_002d5340(H *arg0, int arg1, int arg2) {
    int i;
    void **o;
    for (i = 0; i < arg0->list->count; i++) {
        o = arg0->list->items[i];
        ((V156 *)o)->vX(arg1, arg2);
    }
}
