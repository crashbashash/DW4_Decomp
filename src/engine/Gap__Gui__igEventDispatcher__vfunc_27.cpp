class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();  virtual int vX(int, int); };
struct L { char pad8[8]; int cnt; char pad[4]; VC **arr; };
struct M { char pad8[8]; L *list; };
struct S { char pad12[12]; M *m; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_27(S *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__Gui__igEventDispatcher__vfunc_27(S *arg0, int arg1, int arg2, int arg3) {
    int i;
    int n = arg0->m->list->cnt;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->arr[i]->vX(arg3, 1) & 0xFF) break;
    }
}
