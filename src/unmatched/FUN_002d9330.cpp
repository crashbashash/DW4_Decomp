struct ConfigureResult { int value; };
struct Driver {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20();
    virtual ConfigureResult configure();
    int references;
};
extern "C" {
Driver *FUN_002ba650(int);
int igObject_Destroy(Driver *);
}
struct DriverOwner { char pad[68]; Driver *driver; };
struct DriverType {};
static inline Driver *recreateDriver(DriverOwner *owner, DriverType) {
    Driver *old = owner->driver;
    if (old != 0) {
        old->references = old->references - 1;
        if ((old->references & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    owner->driver = FUN_002ba650(0);
    return owner->driver;
}
extern "C" void FUN_002d9330(DriverOwner *owner) {
    if (owner->driver == 0) {
        recreateDriver(owner, DriverType())->configure();
    }
}
