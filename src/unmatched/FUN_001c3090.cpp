struct Obj { int w0; unsigned refs; };
struct X { char pad[96]; int f96; };
extern "C" {
Obj *FUN_0013aec0(...);
int FUN_00140c00(...);
int FUN_00141190(...);
int FUN_001c31e0(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00562730[4];
}
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void a(int); virtual void d48(); virtual void b(int); virtual void c(); char pad[28]; X *f32; char pad2[24]; unsigned char f60; char pad3[3]; int f64; int f68; char pad4[1]; unsigned char f73; char pad5[2]; int f76; int f80; int f84; };
extern "C" void FUN_001c3090(V *arg0, int arg1);
void FUN_001c3090(V *arg0, int arg1) {
    Obj *o;
    arg0->c();
    arg0->a(arg1);
    arg0->b(arg1);
    arg0->f60 = 1;
    if (arg0->f32 != 0) {
        o = FUN_0013aec0(igObject_GetAllocator(arg0));
        ObjectList_AppendRetained(arg0->f64, o);
        ObjectList_AppendRetained(arg0->f68, o);
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
        arg0->f32->f96 = 2;
        if ((FUN_00140c00(arg0->f32, 0) != 0) == 0) {
            FUN_001c31e0(arg0->f32);
            if (arg0->f73 != 0) {
                FUN_00141190(arg0->f32, 1);
            }
        }
        ObjectList_AppendRetained(o, arg0->f80);
        ObjectList_AppendRetained(o, DAT_00562730[0]);
        ObjectList_AppendRetained(o, arg0->f76);
        ObjectList_AppendRetained(o, arg0->f84);
    }
}
