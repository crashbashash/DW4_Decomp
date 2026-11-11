int Gap__igCreateCollisionDatabase__vfunc_31(void) {
    return 1;
}

int Gap__igCreateCollisionDatabase__vfunc_33(void) {
    return 1;
}

/* Selects the constructor that takes over the factory's reference. */

void FUN_0023c250(int *arg0) {    igSmartPointer<Rc> a(FUN_002c37e0(0), AdoptReference());
    FUN_002d8fe0(a.get(), arg0[13]);
    igSmartPointer<Rc> b(FUN_002397a0(0), AdoptReference());
    {
    Rc *s1 = (Rc *)arg0[14];
    Inst *s0 = (Inst *)b.get();
    if (s1) s1->_refCount = s1->_refCount + 1;
    Rc *t = s0->f20;
    if (t) { t->_refCount = t->_refCount - 1; if ((t->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t); }
    s0->f20 = s1;
    }
    FUN_002d8310(a.get(), b.get());
    ((Obj_23c250 *)a.get())->vX(arg0[13]);
}

