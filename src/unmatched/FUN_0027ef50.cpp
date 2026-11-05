extern "C" {
int FUN_0027eed0(...);
int FUN_0027f1c0(void *);
int FUN_0027f200(void *);
int FUN_0027f240(void *);
int FUN_0027f280(void *);
int FUN_0027f2d0(void *);
int FUN_0027f310(void *);
int FUN_002800e0(...);
}
struct P {
  virtual void d0();
  virtual int v1();
  int p4; int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48, f52, f56, f60, f64, f68, f72, f76;
};
struct S {
  int f0; int f4; int f8; P *f12; int f16; int f20; int f24; int f28; int f32; int f36;
  int p40[2]; int f48; int p52[16]; int f116, f120, f124, f128, f132, f136, f140, f144, f148, f152, f156, f160, f164; char f168; char f169;
};
extern "C" void FUN_0027ef50(S *s, P *p, unsigned char c)
{
  P *q;
  s->f32 = 0xBF800000;
  s->f0 = -1;
  s->f4 = 0xBF800000;
  s->f8 = 0xBF800000;
  s->f12 = p;
  *(float *)&s->f36 = 1.0f / (float)s->f12->f16;
  s->f169 = 0;
  s->f20 = s->f12->v1();
  q = s->f12;
  s->f48 = FUN_0027f310(q) - -q->f60;
  s->f116 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28 - -s->f12->f48 - -s->f12->f64;
  s->f120 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28 - -s->f12->f48 - -s->f12->f64 - -s->f12->f20;
  s->f124 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68;
  s->f128 = s->f12->f76;
  q = s->f12;
  s->f132 = FUN_0027f2d0(q) - -q->f24;
  q = s->f12;
  s->f136 = FUN_0027f280(q) - -q->f36;
  q = s->f12;
  s->f140 = FUN_0027f240(q) - -q->f40;
  s->f144 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28;
  s->f148 = s->f12->f76 - -s->f12->f32;
  q = s->f12;
  s->f152 = FUN_0027f200(q) - -q->f44;
  q = s->f12;
  s->f156 = FUN_0027f1c0(q) - -q->f56;
  s->f160 = s->f12->f76 - -s->f12->f32 - -s->f12->f52 - -s->f12->f68 - -s->f12->f28 - -s->f12->f48;
  s->f164 = s->f12->f76 - -s->f12->f32 - -s->f12->f52;
  s->f24 = c;
  FUN_002800e0(s);
  FUN_0027eed0(s);
}
