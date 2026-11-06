class V132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
struct L { char p0[8]; int count; char p1[4]; V132 **items; };
struct M { char p0[8]; L *list; };
struct O { char p0[12]; M *m; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_29(O *arg0, int arg1, int arg2, int arg3);
void Gap__Gui__igEventDispatcher__vfunc_29(O *arg0, int arg1, int arg2, int arg3) {
    int i;
    int n = arg0->m->list->count;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->items[i]->vX(arg2, arg3) & 0xFF) break;
    }
}
