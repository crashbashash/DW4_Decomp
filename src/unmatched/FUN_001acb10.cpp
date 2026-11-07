class igSceneMgrView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long slot24();
};
extern igSceneMgrView *DAT_005871d8;
struct igTimeView { char pad[16]; long long t; };
extern "C" long long FUN_001acb10(igTimeView *a) {
    if (a->t != -1) {
        return a->t;
    }
    return DAT_005871d8->slot24();
}
