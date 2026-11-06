struct Lst { int a; int b; int n; int c; int *d; };
struct M {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    
    virtual int v30(int);
    int f1, f2, f3; Lst *l;
};
extern "C" void Gap__igMovieManager__vfunc_26(M *m) {
Lst *l; while ((l = m->l, (bool)l) && l->n != 0) { if (m->v30(*l->d) == 0) break; }
}
