class igMetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22(void *object, const void *value);
    unsigned int _refCount;
    int _offset;
};

extern "C" void FUN_002fd150(igMetaFieldView *self, void *object, igMetaFieldView *field, char *source)
{
    self->vfunc_22(object, source + field->_offset);
}
