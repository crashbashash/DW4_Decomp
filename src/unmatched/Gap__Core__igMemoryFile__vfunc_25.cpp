extern "C" {
int FUN_002e30b0(...);
int strcmp(...);
extern int DAT_004f96a8[4];
extern int DAT_004f9c48[4];
extern int DAT_004fb410[4];
}
struct R { int code; inline int Ok() { return code == DAT_004fb410[0]; } };
class MF { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual R vX(int); };
extern "C" MF *Gap__Core__igMemoryFile__vfunc_25(MF *arg0, int arg1, int arg2) {
    int ok;
    FUN_002e30b0(arg0);
    if (strcmp(arg2, &DAT_004f96a8[0]) == 0) {
        ok = arg0->vX(0).Ok();
    } else if (strcmp(arg2, &DAT_004f9c48[0]) == 0) {
        ok = arg0->vX(4).Ok();
    } else {
        return 0;
    }
    return ok ? arg0 : 0;
}
