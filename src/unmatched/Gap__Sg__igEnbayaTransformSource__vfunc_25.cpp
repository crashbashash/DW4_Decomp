class EnbayaSourceSlots {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual int f(int a, int b, int t);
};
struct EnbayaTransformSourceView {
    void *vtable;
    int _pad4;
    int _trackId;
    EnbayaSourceSlots *_enbayaAnimationSource;
};
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_25(EnbayaTransformSourceView *o, int a, int b) {
    return o->_enbayaAnimationSource->f(a, b, o->_trackId);
}
