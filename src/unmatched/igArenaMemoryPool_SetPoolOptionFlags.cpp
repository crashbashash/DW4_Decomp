extern "C" {
int FUN_002f8870(...);
int FUN_003081d0(...);
extern int DAT_004fd7a0[4];
extern unsigned char GPR_00554d78;
}
class P { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();  virtual int vX(int);
 char pad[184]; int cnt; int flags; };
extern "C" void igArenaMemoryPool_SetPoolOptionFlags(P *p, int f) {
    int r;
    if ((f & 1) != (p->flags & 1)) {
        if (p->vX(f & 1) != 0) {
            if (p->cnt > 0) {
                FUN_002f8870(0, p);
                if (GPR_00554d78 == 0) {
                    r = FUN_003081d0(DAT_004fd7a0);
                    if (r != 1) { if (r == 2) { GPR_00554d78 = 1; } }
                }
            }
            return;
        }
    }
    p->flags = f;
}
