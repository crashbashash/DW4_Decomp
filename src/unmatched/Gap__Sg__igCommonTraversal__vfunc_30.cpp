class igTraversalStackView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual int slot21(void *other);
};
struct igCommonTraversalView {
    char pad0[52];
    void *f52;
    char pad1[12];
    igTraversalStackView *f68;
};
extern "C" int Gap__Sg__igCommonTraversal__vfunc_30(igCommonTraversalView *self) {
    return self->f68->slot21(self->f52);
}
