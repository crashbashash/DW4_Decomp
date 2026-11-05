class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
struct L { char p0[8]; int count; char pc[4]; V **items; };
struct O { char p0[8]; L *list; };
extern "C" void Gap__Core__igPsx2ControllerManager__vfunc_23(O *arg0, int arg1);
void Gap__Core__igPsx2ControllerManager__vfunc_23(O *arg0, int arg1) {
    int i;
    int n;
    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        arg0->list->items[i]->vX(arg1);
    }
}
