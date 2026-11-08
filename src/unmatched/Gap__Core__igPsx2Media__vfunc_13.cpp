struct R { int v; R() {} R(const R &o) : v(o.v) {}
  bool operator==(const R &o) const { return v == o.v; }
  bool operator!=(const R &o) const { return v != o.v; }
};
class Sub { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R v92(); };
struct Media { void *vt; int f4; int f8; int f12; Sub *f16; char p20[16]; char f36; };
extern "C" {
void Gap__Core__igObject__vfunc_11(Media *);
R FUN_0032cf50(void *, int, int, int);
R FUN_0032d640(int, int);
R FUN_0032d850(int, int, int, int, int);
void FUN_00113f20(void);
void FUN_00113f78(void);
void sceSifAddCmdHandler(int, void *, int);
void FUN_0032db00(void);
extern R DAT_004fb410;
extern int DAT_004f9498[4];
extern int DAT_004ffd30[4];
extern int DAT_004ffbd8[2];
extern int DAT_004ffbe0[2];
extern int DAT_00587338;
extern Media *DAT_00587360;
extern int *DAT_00587368;
extern char GPR_00554de0;
}
extern "C" void Gap__Core__igPsx2Media__vfunc_13(Media *self) {
    Gap__Core__igObject__vfunc_11(self);
    if (FUN_0032cf50(DAT_004f9498, 1, 0, 0) != DAT_004fb410) {
        return;
    }
    if (FUN_0032cf50(DAT_004ffd30, 2, 0, 0) != DAT_004fb410) {
        return;
    }
    self->f36 = 1;
    FUN_0032d640(self->f12, 0x12114);
    FUN_0032d850(self->f12, 19, (int)(unsigned)self->f8, (char)0, (char)0);
    FUN_00113f20();
    sceSifAddCmdHandler(4, (void *)FUN_0032db00, 0);
    FUN_00113f78();
    DAT_00587360 = self;
    self->f16->v92();
    if (DAT_00587338 == 0) {
        GPR_00554de0 = 0;
        if (DAT_00587368 == 0) {
            DAT_00587368 = DAT_004ffbd8;
        }
    } else {
        GPR_00554de0 = 1;
        DAT_00587368 = DAT_004ffbe0;
    }
}
