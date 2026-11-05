extern "C" {
int FUN_001db500(...);
int List_Resize(...);
}
struct Sorter;
class DW4VC_112_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
struct List { char pad8[8]; int f8; int f12; int *f16; };
struct Ent { char pad28[28]; List *f28; };
struct EL { char pad8[8]; int f8; char pad16[4]; Ent **f16; int f20; };
struct Sorter {
  char pad8[8]; DW4VC_112_0 *f8; char pad12[4]; EL *f16; char pad20[4]; List *f24; List *f28; List *f32; DW4VC_112_0 *f36; DW4VC_112_0 *f40; DW4VC_112_0 *f44; DW4VC_112_0 *f48; char pad52[40]; DW4VC_112_0 *f92; DW4VC_112_0 *f96; char pad100[4]; List *f104; List *f108; unsigned char f112; char pad113[11]; int f124; unsigned char f128;
};
extern "C" void Gap__Core__igSorter__vfunc_24(Sorter *arg0);
void Gap__Core__igSorter__vfunc_24(Sorter *arg0) {
    int i;
    List *l;
    EL *e;
    if (arg0->f112 != 0) { arg0->f112 = 0; }
    arg0->f128 = 0;
    i = 0;
    arg0->f32->f8 = 0;
    arg0->f24->f8 = 0;
    arg0->f28->f8 = 0;
    for (; i < arg0->f16->f8; i++) {
        l = arg0->f16->f16[i]->f28;
        if (0 <= l->f12) { l->f8 = 0; } else { List_Resize(l, 0, 4); }
    }
    arg0->f16->f20 = 0;
    arg0->f40->vX();
    arg0->f44->vX();
    arg0->f48->vX();
    arg0->f92->vX();
    arg0->f96->vX();
    arg0->f36->vX();
    arg0->f8->vX();
    FUN_001db500(arg0);
    arg0->f104->f8 = 0;
    arg0->f108->f8 = 0;
    arg0->f124 = 0;
}
