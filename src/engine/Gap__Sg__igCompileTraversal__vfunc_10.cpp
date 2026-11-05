/* 0x001bb510 — igCompileTraversal slot 10: run the base-class hook, then
 * dispatch the traversal's own virtual slot 31 on self.
 *
 * The base call is Gap::Core::igObject::vfunc_08, which in retail is a bare
 * `jr ra` (asm/Gap__Core__igObject__vfunc_08__002ff0f0.s).  Slot 31 (vtable
 * offset 124, the 0x7c load in the retail bytes) is igCompileTraversal's
 * Gap__Sg__igCompileTraversal__vfunc_31, which empties the traversal's
 * per-run object lists and clears its flags (src/unmatched).  The wrapper
 * class below only gives the C++ front end 29 placeholder slots in front of
 * slot31 so the call loads from +124; the placeholder names carry no meaning. */
extern "C" {
int Gap__Core__igObject__vfunc_08(...);
void Gap__Sg__igCompileTraversal__vfunc_10(void **self);
}
class igCompileTraversalVSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int slot31(); };
void Gap__Sg__igCompileTraversal__vfunc_10(void **self) {
    Gap__Core__igObject__vfunc_08();
    ((igCompileTraversalVSlots *)(self))->slot31();
}
