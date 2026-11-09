class CrtHeapView {
public:
    virtual void d0(); virtual void d1();
    virtual void *vfunc_2(unsigned int size);
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6();
    virtual void vfunc_7(void *block);
    virtual void vfunc_8(void *block);
    virtual void *vfunc_9(void *block, unsigned int size);
    virtual void vfunc_10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void vfunc_15(int flags, void *block);
};

extern "C" void *FUN_0032ac40(CrtHeapView *self, unsigned int size)
{
    return self->vfunc_2(size);
}
