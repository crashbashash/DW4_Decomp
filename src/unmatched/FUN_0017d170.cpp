struct Obj { int w0; unsigned refs; };
extern "C" {
Obj *FUN_001527c0(...);
Obj *FUN_002c9130(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
}
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned *g(); char pad[44]; Obj *f48; Obj *f52; Obj *f56; };
extern "C" void FUN_0017d170(V *arg0);
void FUN_0017d170(V *arg0) {
    unsigned *flags = arg0->g();
    if ((unsigned char)((*flags & 0xF0) >> 4) > 0) {
        Obj *o;
        int a;
        a = igObject_GetAllocator(arg0);
        o = arg0->f56;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->f56 = FUN_001527c0(a);
        a = igObject_GetAllocator(arg0);
        o = arg0->f48;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->f48 = FUN_002c9130(a);
        if (*flags & 2) {
            a = igObject_GetAllocator(arg0);
            o = arg0->f52;
            if (o != 0) {
                o->refs = o->refs - 1;
                if ((o->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
            arg0->f52 = FUN_002c9130(a);
        }
    }
}
