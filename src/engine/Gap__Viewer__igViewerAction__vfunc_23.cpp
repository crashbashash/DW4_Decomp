struct T { void f(); };
struct O { int p0, p1; T *t; void (T::*pmf)(); };
extern "C" void Gap__Viewer__igViewerAction__vfunc_23(O *o) {
    void (T::*m)() = o->pmf;
    (o->t->*m)();
}
