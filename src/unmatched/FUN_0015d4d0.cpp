struct Cam { virtual void d0(); };
extern "C" {
int FUN_001904f0(void*,void*,void*);
int FUN_00190d80(void*,float*,int);
int FUN_00191860(void*,float,float,float,float,float,float);
int FUN_00192510(void*,float*,float*,float*,float*,float*,float*);
}
struct V {
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
  virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
  virtual int v48();
  virtual void d49(); virtual void d50();
  virtual void v51(int, int *, int *);
};
struct S {
  char p0[20]; V *o;
  char p1[272];
  float m[16];
  int w, h;
  float nl, nr, nb, nt, nn, nf;
};
extern "C" void FUN_0015d4d0(S *s)
{
  int sw, sh;
  int r = s->o->v48();
  s->o->v51(r, &sw, &sh);
  if (s->w == sw) { if (s->h != sh) goto L; } else { L:
    s->w = sw; s->h = sh;
    float hw = (float)sw / 2.0f;
    float hh = (float)sh / 2.0f;
    FUN_00192510((char*)s + 0x68, &s->nl, &s->nr, &s->nb, &s->nt, &s->nn, &s->nf);
    FUN_00191860((char*)s + 0xA8, -hw, hw, -hh, hh, s->nn, s->nf);
    float rw = 1.0f / (s->nr - s->nl);
    s->m[0] = 2.0f * s->nn * rw;
    s->m[4] = 0;
    s->m[8] = rw * (s->nr + s->nl);
    s->m[12] = 0;
    float rh = 1.0f / (s->nt - s->nb);
    s->m[1] = 0;
    s->m[5] = 2.0f * s->nn * rh;
    s->m[9] = rh * (s->nt + s->nb);
    s->m[13] = 0;
    s->m[2] = 0; s->m[6] = 0; s->m[10] = 0; s->m[14] = -1.0f;
    s->m[3] = 0; s->m[7] = 0; s->m[11] = -1.0f; s->m[15] = 0;
    float v[3];
    v[2] = 1.0f;
    v[0] = 0.5f * (float)sw;
    v[1] = 0.5f * (float)sh;
    FUN_00190d80((char*)s + 0x128, v, 0x3f800000);
  }
  FUN_001904f0((char*)s + 0xE8, (char*)s + 0x28, (char*)s + 0x128);
}
