class igVertexArrayView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40();
    virtual void vfunc_41(unsigned int index);
    virtual void vfunc_42(unsigned int index);
    virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void vfunc_51(unsigned int index, float value);
    virtual void d52(); virtual void d53(); virtual void d54();
    virtual void vfunc_55();
    virtual void vfunc_56();
};
class igPointSpriteExtView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[16];
    igVertexArrayView *_vertexArray;
};

extern "C" void FUN_0015db60(igPointSpriteExtView *self)
{
    self->_vertexArray->vfunc_56();
}
