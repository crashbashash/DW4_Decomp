class igFilterMessageDispatcherView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_21();
    virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void vfunc_26(void *message);
};
struct igMessageDispatcherOwnerView {
    char _pad0[8];
    igFilterMessageDispatcherView *f8;
};

extern "C" void FUN_00237e80(igMessageDispatcherOwnerView *self)
{
    self->f8->vfunc_21();
}
