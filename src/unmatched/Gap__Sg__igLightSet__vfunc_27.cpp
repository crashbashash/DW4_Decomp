struct L { char pad0[8]; unsigned int n; char pad1[4]; char **data; };
struct S { char pad[28]; L *list; };
struct D { char pad[8]; int off; };
class LS { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vA(void *); virtual int vB(void *); };
extern "C" {
int FUN_00192f50(void *, void *, int);
int FUN_00192fc0(void *, void *, int);
extern D *DAT_0055f0a0[4];
extern D *DAT_0055f0c0[4];
void Gap__Sg__igLightSet__vfunc_27(S *arg0, int arg1) {
    int sp70[4];
    int sp60[4];
    unsigned int n;
    unsigned int i;
    LS *o;

    n = arg0->list->n;
    for (i = 0; i < n; i++) {
        o = (LS *)arg0->list->data[i];
        FUN_00192fc0(sp70, (char *)o + DAT_0055f0a0[0]->off, arg1);
        o->vA(sp70);
        FUN_00192f50(sp60, (char *)o + DAT_0055f0c0[0]->off, arg1);
        o->vB(sp60);
    }
}
}
