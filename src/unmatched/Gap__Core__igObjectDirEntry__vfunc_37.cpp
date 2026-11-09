class igObjectSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void vfunc_15();
};
class igObjectDirEntryView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[16];
    igObjectSlots *_ref;
};

extern "C" void Gap__Core__igObjectDirEntry__vfunc_37(igObjectDirEntryView *self)
{
    self->_ref->vfunc_15();
}
