struct T { void m(); };
typedef void (T::*PM)();
struct S { char pad[8]; T *obj; PM pm; };
extern "C" void FUN_00237940(S *s) {
    if (s->obj) { PM pm = s->pm; (s->obj->*pm)(); }
}
