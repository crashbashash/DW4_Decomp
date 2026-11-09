class igGuiComponentControllerView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual void *vfunc_23(void *component, void *context);
};
class igGuiComponentView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[4];
    igGuiComponentControllerView *_controller;
};

extern "C" void *FUN_004555c0(igGuiComponentView *self, void *component, void *context)
{
    return self->_controller->vfunc_23(component, context);
}
