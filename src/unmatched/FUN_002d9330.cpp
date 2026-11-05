struct R { int v; };
class C23 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual R vX(); };
struct Rc { int vt; int rc; };
struct O { char pad[68]; Rc * volatile f68; };
extern "C" {
void *FUN_002ba650(int);
int igObject_Destroy(void *);
void FUN_002d9330(O *arg0);
}
void FUN_002d9330(O *arg0) {
    volatile char c[9];
    if (arg0->f68 == 0) {
        Rc *a;
        c[8] = 0;
        a = arg0->f68;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->f68 = (Rc *)FUN_002ba650(0);
        R r = ((C23 *)arg0->f68)->vX();
    }
}
