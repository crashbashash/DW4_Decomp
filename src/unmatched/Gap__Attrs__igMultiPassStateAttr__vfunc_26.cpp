class igMultiPassStateAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void vfunc_30(int passes);
};
class igPsx2VisualContextView {
public:
    virtual void d0();
    unsigned int _refCount;
    char _pad8[1444];
    int _bMultiPassNum;
};

extern "C" void Gap__Attrs__igMultiPassStateAttr__vfunc_26(igMultiPassStateAttrView *self, igPsx2VisualContextView *context)
{
    self->vfunc_30(context->_bMultiPassNum);
}
