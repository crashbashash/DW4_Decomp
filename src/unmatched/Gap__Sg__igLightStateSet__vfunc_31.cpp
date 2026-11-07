class igLightStateEntry {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void apply();
};
struct igLightStateList {
    char pad0[8];
    unsigned int count;
    char pad1[4];
    igLightStateEntry **data;
};
struct igLightStateSetView {
    char pad0[32];
    igLightStateList *lights;
};
extern "C" void Gap__Sg__igLightStateSet__vfunc_31(igLightStateSetView *self) {
    unsigned int n;
    unsigned int i;

    n = self->lights->count;
    for (i = 0; i < n; i++) {
        self->lights->data[i]->apply();
    }
}
