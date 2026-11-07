extern "C" {
void FUN_002ea290(void **arg0, int arg1);
}
class DW4VC_140_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int); };
struct S { void **vt; char pad[28]; int *arr; char pad2[16]; int n; };
void FUN_002ea290(void **arg0, int arg1) {
    int *p;
    S *o = (S *)arg0;
    ((DW4VC_140_1 *)arg0)->vX(0);
    int i;
    p = o->arr;
    for (i = 0; i < o->n; i++) {
        p[i] = arg1;
    }
}
