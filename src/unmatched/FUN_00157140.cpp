class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();  virtual int vm(int, int, int, int, int); };
struct P { char pad[12]; int f12; };
struct O { char pad[8]; int f8; int f12; char pad2[8]; int f24; char pad3[16]; int f44; char pad4[20]; P *f68; };
extern "C" bool FUN_00157140(O *arg0, int arg1, V **arg2) {
    bool r = false;
    if (arg1 == arg0->f44) {
        return true;
    }
    if ((*arg2)->vm(arg0->f24, arg0->f44, arg1, arg0->f8, arg0->f12) != 0) {
        r = true;
        if (arg0->f44 == 0x10000 && arg1 == 0x10001) {
            P *p = arg0->f68;
            if (p == 0) {
                r = false;
            } else if (16 < p->f12) {
                r = false;
            }
        }
    }
    return r;
}
